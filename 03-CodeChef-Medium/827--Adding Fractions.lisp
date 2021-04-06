#-swank
(unless (member :child-sbcl *features*)
  (quit
   :unix-status
   (process-exit-code
    (run-program *runtime-pathname*
                 `("--control-stack-size" "256MB"
                   "--noinform" "--disable-ldb" "--lose-on-corruption" "--end-runtime-options"
                   "--eval" "(push :child-sbcl *features*)"
                   "--script" ,(namestring *load-pathname*))
                 :output t :error t :input t))))
(in-package :cl-user)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter *opt*
    #+swank '(optimize (speed 3) (safety 2))
    #-swank '(optimize (speed 3) (safety 0) (debug 0)))
  #+swank (ql:quickload '(:cl-debug-print :fiveam :cp/util) :silent t)
  #+swank (use-package :cp/util :cl-user)
  #-swank (set-dispatch-macro-character
           #\# #\> (lambda (s c p) (declare (ignore c p)) `(values ,(read s nil nil t))))
  #+sbcl (dolist (f '(:popcnt :sse4)) (pushnew f sb-c:*backend-subfeatures*))
  #+sbcl (setq *random-state* (seed-random-state (nth-value 1 (get-time-of-day)))))
#-swank (eval-when (:compile-toplevel)
          (setq *break-on-signals* '(and warning (not style-warning))))
#+swank (set-dispatch-macro-character #\# #\> #'cl-debug-print:debug-print-reader)

(macrolet ((def (b)
             `(progn (deftype ,(intern (format nil "UINT~A" b)) () '(unsigned-byte ,b))
                     (deftype ,(intern (format nil "INT~A" b)) () '(signed-byte ,b))))
           (define-int-types (&rest bits) `(progn ,@(mapcar (lambda (b) `(def ,b)) bits))))
  (define-int-types 2 4 7 8 15 16 31 32 62 63 64))

(defconstant +mod+ 1000000007)

(defmacro dbg (&rest forms)
  (declare (ignorable forms))
  #+swank (if (= (length forms) 1)
              `(format *error-output* "~A => ~A~%" ',(car forms) ,(car forms))
              `(format *error-output* "~A => ~A~%" ',forms `(,,@forms))))

(declaim (inline println))
(defun println (obj &optional (stream *standard-output*))
  (let ((*read-default-float-format*
          (if (typep obj 'double-float) 'double-float *read-default-float-format*)))
    (prog1 (princ obj stream) (terpri stream))))

;; BEGIN_INSERTED_CONTENTS
(defpackage :cp/read-fixnum
  (:use :cl)
  (:export #:read-fixnum))
(in-package :cp/read-fixnum)

(declaim (ftype (function * (values fixnum &optional)) read-fixnum))
(defun read-fixnum (&optional (in *standard-input*))
  "NOTE: cannot read -2^62"
  (declare #.cl-user::*opt*)
  (macrolet ((%read-byte ()
               `(the (unsigned-byte 8)
                     #+swank (char-code (read-char in nil #\Nul))
                     #-swank (sb-impl::ansi-stream-read-byte in nil #.(char-code #\Nul) nil))))
    (let* ((minus nil)
           (result (loop (let ((byte (%read-byte)))
                           (cond ((<= 48 byte 57)
                                  (return (- byte 48)))
                                 ((zerop byte) ; #\Nul
                                  (error "Read EOF or #\Nul."))
                                 ((= byte #.(char-code #\-))
                                  (setq minus t)))))))
      (declare ((integer 0 #.most-positive-fixnum) result))
      (loop
        (let* ((byte (%read-byte)))
          (if (<= 48 byte 57)
              (setq result (+ (- byte 48)
                              (* 10 (the (integer 0 #.(floor most-positive-fixnum 10))
                                         result))))
              (return (if minus (- result) result))))))))

;;;
;;; Binary heap
;;;

(defpackage :cp/binary-heap
  (:use :cl)
  (:export #:define-binary-heap #:heap-empty-error #:heap-empty-error-heap))
(in-package :cp/binary-heap)

(define-condition heap-empty-error (error)
  ((heap :initarg :heap :reader heap-empty-error-heap))
  (:report
   (lambda (condition stream)
     (format stream "Attempted to get an element from empty heap ~W"
             (heap-empty-error-heap condition)))))

(defmacro define-binary-heap (name &key order (element-type 'fixnum))
  "Defines a binary heap specialized for the given order and the element
type. This macro defines a structure of the given NAME and relevant functions:
MAKE-<NAME>, <NAME>-PUSH, <NAME>-POP, <NAME>-CLEAR, <NAME>-EMPTY-P,
<NAME>-COUNT, and <NAME>-PEEK.

If ORDER is not given, heap for dynamic order is defined instead, and the
constructor takes an order function as an argument. Note that it will be
slightly slower than a static order, as it cannot be inlined."
  (check-type name symbol)
  (let* ((string-name (string name))
         (fname-push (intern (format nil "~A-PUSH" string-name)))
         (fname-pop (intern (format nil "~A-POP" string-name)))
         (fname-clear (intern (format nil "~A-CLEAR" string-name)))
         (fname-empty-p (intern (format nil "~A-EMPTY-P" string-name)))
         (fname-count (intern (format nil "~A-COUNT" string-name)))
         (fname-peek (intern (format nil "~A-PEEK" string-name)))
         (fname-make (intern (format nil "MAKE-~A" string-name)))
         (acc-position (intern (format nil "~A-POSITION" string-name)))
         (acc-data (intern (format nil "~A-DATA" string-name)))
         (acc-order (intern (format nil "~A-ORDER" string-name)))
         (dynamic-order (null order))
         (order (or order 'order)))
    `(progn
       (defstruct (,name
                   (:constructor ,fname-make
                       (size
                        ,@(when dynamic-order '(order))
                        &aux
                        (data
                         (locally
                             (declare #+sbcl (sb-ext:muffle-conditions style-warning))
                           (make-array (1+ size) :element-type ',element-type))))))
         (data nil :type (simple-array ,element-type (*)))
         (position 1 :type (integer 1 #.array-total-size-limit))
         ,@(when dynamic-order
             `((order nil :type function))))

       (declaim #+sbcl (sb-ext:maybe-inline ,fname-push))
       (defun ,fname-push (obj heap)
         "Adds OBJ to HEAP."
         (declare (optimize (speed 3))
                  (type ,name heap))
         (symbol-macrolet ((position (,acc-position heap)))
           (when (>= position (length (,acc-data heap)))
             (setf (,acc-data heap)
                   (adjust-array (,acc-data heap)
                                 (min (- array-total-size-limit 1)
                                      (* position 2)))))
           (let ((data (,acc-data heap))
                 ,@(when dynamic-order `((order (,acc-order heap)))))
             (declare ((simple-array ,element-type (*)) data))
             (labels ((heapify (pos)
                        (declare (optimize (speed 3) (safety 0))
                                 ((mod #.array-total-size-limit) pos))
                        (unless (= pos 1)
                          (let ((parent-pos (ash pos -1)))
                            (when (funcall ,order (aref data pos) (aref data parent-pos))
                              (rotatef (aref data pos) (aref data parent-pos))
                              (heapify parent-pos))))))
               (setf (aref data position) obj)
               (heapify position)
               (incf position)
               heap))))

       (declaim #+sbcl (sb-ext:maybe-inline ,fname-pop))
       (defun ,fname-pop (heap)
         "Removes and returns the element at the top of HEAP. Signals
HEAP-EMPTY-ERROR if HEAP is empty."
         (declare (optimize (speed 3))
                  (type ,name heap))
         (symbol-macrolet ((position (,acc-position heap)))
           (let ((data (,acc-data heap))
                 ,@(when dynamic-order `((order (,acc-order heap)))))
             (declare ((simple-array ,element-type (*)) data))
             (labels ((heapify (pos)
                        (declare (optimize (speed 3) (safety 0))
                                 ((mod #.array-total-size-limit) pos))
                        (let* ((child-pos1 (+ pos pos))
                               (child-pos2 (1+ child-pos1)))
                          (declare ((mod #.array-total-size-limit) child-pos1 child-pos2))
                          (when (<= child-pos1 position)
                            (if (<= child-pos2 position)
                                (if (funcall ,order (aref data child-pos1) (aref data child-pos2))
                                    (unless (funcall ,order (aref data pos) (aref data child-pos1))
                                      (rotatef (aref data pos) (aref data child-pos1))
                                      (heapify child-pos1))
                                    (unless (funcall ,order (aref data pos) (aref data child-pos2))
                                      (rotatef (aref data pos) (aref data child-pos2))
                                      (heapify child-pos2)))
                                (unless (funcall ,order (aref data pos) (aref data child-pos1))
                                  (rotatef (aref data pos) (aref data child-pos1))))))))
               (when (= position 1)
                 (error 'heap-empty-error :heap heap))
               (prog1 (aref data 1)
                 (decf position)
                 (setf (aref data 1) (aref data position))
                 (heapify 1))))))

       (declaim (inline ,fname-clear))
       (defun ,fname-clear (heap)
         "Makes HEAP empty."
         (setf (,acc-position heap) 1)
         heap)

       (declaim (inline ,fname-empty-p))
       (defun ,fname-empty-p (heap)
         "Returns true iff HEAP is empty."
         (= 1 (,acc-position heap)))

       (declaim (inline ,fname-count))
       (defun ,fname-count (heap)
         "Returns the current number of the elements in HEAP."
         (- (,acc-position heap) 1))

       (declaim (inline ,fname-peek))
       (defun ,fname-peek (heap)
         "Returns the topmost element of HEAP. Signals HEAP-EMPTY-ERROR if HEAP
is empty."
         (if (= 1 (,acc-position heap))
             (error 'heap-empty-error :heap heap)
             (aref (,acc-data heap) 1))))))

#+(or)
(define-binary-heap heap
  :order #'>
  :element-type fixnum)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (when (find-symbol "DOUBLE-FLOAT-BITS" :sb-kernel)
    (pushnew :double-float-bits *features*)))

(defpackage :cp/complex-pack
  (:use :cl)
  (:export #:define-complex-pack)
  (:import-from :sb-kernel
                #:make-double-float
                #+double-float-bits #:double-float-bits)
  (:documentation "See cp/integer-pack for documentation."))
(in-package :cp/complex-pack)

;; TODO: unify define-cons-pack and define-complex-pack

#-double-float-bits
(eval-when (:compile-toplevel :load-toplevel :execute)
  (sb-c:defknown double-float-bits (double-float)
      (signed-byte 64)
      (sb-c:movable sb-c:foldable sb-c:flushable)
    :overwrite-fndb-silently t)
  (declaim (inline double-float-bits))
  (defun double-float-bits (x)
    (logior (ash (sb-kernel:double-float-high-bits x) 32)
            (sb-kernel:double-float-low-bits x))))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun %concat-name (&rest args)
    (if (cdr args)
        (format nil "~A-~A"
                (car args)
                (apply #'%concat-name (cdr args)))
        (car args)))
  (defun %concat+name+ (&rest args)
    (format nil "+~A+" (apply #'%concat-name args)))
  (defun extract-62bit-slots (list)
    (let ((position 0))
      (loop for (slot-name slot-size) in list
            while (<= (+ position slot-size) 62)
            collect (list slot-name slot-size position)
            do (incf position slot-size)))))

(defmacro define-complex-pack (name &rest slot-descriptions)
  (assert slot-descriptions () "~A has no slots." name)
  (let* ((packer-name (intern (%concat-name "PACK" name)))
         (unpacker-macro-name (intern (%concat-name "WITH-UNPACKING" name)))
         (tmp1 (gensym))
         (tmp2 (gensym))
         (tmp (gensym))
         ;; slot := (slot-name slot-size position)
         (real-slots (extract-62bit-slots slot-descriptions))
         (real-revslots (reverse real-slots))
         (imag-slots (extract-62bit-slots (nthcdr (length real-slots) slot-descriptions)))
         (imag-revslots (reverse imag-slots))
         (slots (append real-slots imag-slots))
         (slot-names (mapcar #'car slots)))
    (assert (= (+ (length real-slots) (length imag-slots))
               (length slot-descriptions))
            () "Size restriction violated: slot size <= 62 bit and total size <= 124 bit")
    (unless (> (length imag-slots) 0)
      (error "Total size is too small. Use DEFINE-INTEGER-PACK instead."))
    (let ((real-width (+ (second (first real-revslots))
                         (third (first real-revslots))))
          (imag-width (+ (second (first imag-revslots))
                         (third (first imag-revslots)))))
      `(progn
         (deftype ,name () '(complex double-float))
         ;; define most positive integer for every slot as constant
         ,@(loop for (slot-name slot-size _) in slots
                 collect `(defconstant ,(intern (%concat+name+ "MAX" name slot-name))
                            (- (ash 1 ,slot-size) 1)))
         ;; getter
         ;; TODO: define setter with define-setf-expander
         ,@(loop for slot in real-slots
                 for (slot-name slot-size slot-position) = slot
                 for accessor-name = (intern (%concat-name name slot-name))
                 append `((declaim (inline ,accessor-name (setf ,accessor-name)))
                          (defun ,accessor-name (,name)
                            (declare (type ,name ,name))
                            (ldb (byte ,slot-size ,slot-position)
                                 (the (unsigned-byte ,real-width)
                                      (double-float-bits (realpart ,name)))))))
         ,@(loop for slot in imag-slots
                 for (slot-name slot-size slot-position) = slot
                 for accessor-name = (intern (%concat-name name slot-name))
                 append `((declaim (inline ,accessor-name (setf ,accessor-name)))
                          (defun ,accessor-name (,name)
                            (declare (type ,name ,name))
                            (ldb (byte ,slot-size ,slot-position)
                                 (the (unsigned-byte ,imag-width)
                                      (double-float-bits (imagpart ,name)))))))
         ;; constructor
         (declaim (inline ,packer-name))
         (defun ,packer-name ,(loop for slot in slots collect (car slot))
           (declare ,@(loop for (slot-name slot-size slot-position) in slots
                            collect `(type (unsigned-byte ,slot-size) ,slot-name)))
           (let ((,tmp1 ,(caar real-revslots))
                 (,tmp2 ,(caar imag-revslots)))
             (declare (type (unsigned-byte ,real-width) ,tmp1)
                      (type (unsigned-byte ,imag-width) ,tmp2))
             ,@(loop for (slot-name slot-size _) in (rest real-revslots)
                     collect `(setq ,tmp1 (logxor ,slot-name
                                                  (the (unsigned-byte ,real-width)
                                                       (ash ,tmp1 ,slot-size)))))
             ,@(loop for (slot-name slot-size _) in (rest imag-revslots)
                     collect `(setq ,tmp2 (logxor ,slot-name
                                                  (the (unsigned-byte ,imag-width)
                                                       (ash ,tmp2 ,slot-size)))))
             (complex (make-double-float (ldb (byte 30 32) ,tmp1)
                                         (ldb (byte 32 0) ,tmp1))
                      (make-double-float (ldb (byte 30 32) ,tmp2)
                                         (ldb (byte 32 0) ,tmp2)))))
         ;; destructuring-bind-style macro
         (defmacro ,unpacker-macro-name (,slot-names ,name &body body)
           `(let* ((,',tmp ,,name)
                   (,',tmp1 (double-float-bits (realpart ,',tmp)))
                   (,',tmp2 (double-float-bits (imagpart ,',tmp))))
              (declare (type (unsigned-byte ,,real-width) ,',tmp1)
                       (type (unsigned-byte ,,imag-width) ,',tmp2))
              (let* ,(loop for var in (list ,@slot-names)
                           for rest on ',real-slots
                           for (slot-name slot-size _) = (car rest)
                           collect `(,var
                                     (prog1 (the (unsigned-byte ,slot-size)
                                                 (ldb (byte ,slot-size 0) ,',tmp1))
                                       ,@(when (cdr rest)
                                           `((setq ,',tmp1 (ash ,',tmp1 ,(- slot-size))))))))
                (let* ,(loop for var in (list ,@(nthcdr (length real-slots) slot-names))
                             for rest on ',imag-slots
                             for (slot-name slot-size _) = (car rest)
                             collect `(,var
                                       (prog1 (the (unsigned-byte ,slot-size)
                                                   (ldb (byte ,slot-size 0) ,',tmp2))
                                         ,@(when (cdr rest)
                                             `((setq ,',tmp2 (ash ,',tmp2 ,(- slot-size))))))))
                  ,@body))))))))

(defpackage :cp/tzcount
  (:use :cl)
  (:export #:tzcount))
(in-package :cp/tzcount)

(declaim (inline tzcount))
(defun tzcount (x)
  "Returns the number of trailing zero bits. Note that (TZCOUNT 0) = -1."
  (- (integer-length (logand x (- x))) 1))

;;;
;;; GCD and LCM
;;; Reference:
;;; https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/
;;;

(defpackage :cp/fast-gcd
  (:use :cl :cp/tzcount)
  (:export #:fast-gcd #:fast-lcm #:%fast-gcd))
(in-package :cp/fast-gcd)

(declaim (inline %fast-gcd fast-gcd fast-lcm))

(declaim (ftype (function * (values (integer 1 #.most-positive-fixnum) &optional)) %fast-gcd))
(defun %fast-gcd (u v)
  (declare ((integer 0 #.most-positive-fixnum) u v))
  (let ((shift (tzcount (logior u v))))
    (declare (optimize (safety 0)))
    (setq u (ash u (- (tzcount u))))
    (loop (setq v (ash v (- (tzcount v))))
          (when (> u v)
            (rotatef u v))
          (decf v u)
          (when (zerop v)
            (return (the (integer 1 #.most-positive-fixnum)
                         (ash u shift)))))))

(declaim (ftype (function * (values (integer 0 #.most-positive-fixnum) &optional)) fast-gcd))
(defun fast-gcd (u v)
  (declare (optimize (speed 3))
           ((integer 0 #.most-positive-fixnum) u v))
  (cond ((zerop u) v)
        ((zerop v) u)
        (t (%fast-gcd u v))))

(declaim (ftype (function * (values (integer 0) &optional)) fast-lcm))
(defun fast-lcm (u v)
  (declare (optimize (speed 3))
           ((integer 0 #.most-positive-fixnum) u v))
  (if (or (zerop u) (zerop v))
      0
      (multiple-value-bind (max min)
          (if (> u v)
              (values u v)
              (values v u))
        (* (truncate max (%fast-gcd u v)) min))))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/fast-gcd :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/complex-pack :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/binary-heap :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(define-complex-pack node (num 40) (denom 40) (index 20))

;; num denom . index
(define-binary-heap heap
  :order (lambda (node1 node2)
           (with-unpacking-node (a b _) node1
             (with-unpacking-node (c d _) node2
               (> (the uint62 (* a d))
                  (the uint62 (* b c))))))
  :element-type node)

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (dotimes (i tt)
      (unless (zerop i)
        (terpri))
      (let* ((n (read))
             (nums (make-array n :element-type 'uint62))
             (denoms (make-array n :element-type 'uint62))
             (que (make-heap n))
             (prevs (make-array n :element-type 'int32 :initial-element -1))
             (nexts (make-array n :element-type 'int32 :initial-element -1))
             (res-nums (make-array n :element-type 'uint62))
             (res-denoms (make-array n :element-type 'uint62)))
        (dotimes (i n)
          (setf (aref prevs i) (- i 1)
                (aref nexts i) (+ i 1)))
        (dotimes (i n)
          (let* ((num (read-fixnum))
                 (denom (read-fixnum)))
            (setf (aref nums i) num
                  (aref denoms i) denom)
            (heap-push (pack-node num denom i) que)))
        (loop until (heap-empty-p que)
              for node = (heap-pop que)
              do (with-unpacking-node (num denom i) node
                   (when (zerop (aref res-denoms i))
                     (setf (aref res-nums i) num
                           (aref res-denoms i) denom)
                     (let ((p-i (aref prevs i))
                           (n-i (aref nexts i)))
                       (when (>= p-i 0)
                         (setf (aref nexts p-i) n-i))
                       (when (< n-i n)
                         (setf (aref prevs n-i) p-i))
                       (when (>= p-i 0)
                         (let* ((pnum (aref nums p-i))
                                (pdenom (aref denoms p-i))
                                (new-num (+ num pnum))
                                (new-denom (+ denom pdenom)))
                           (setf (aref nums p-i) new-num
                                 (aref denoms p-i) new-denom)
                           (heap-push (pack-node new-num new-denom p-i) que)))))))
        (write-string
         (with-output-to-string (*standard-output* nil :element-type 'base-char)
           (loop for num across res-nums
                 for denom across res-denoms
                 for gcd = (%fast-gcd num denom)
                 do (princ (floor num gcd))
                    (write-char #\/)
                    (princ (floor denom gcd))
                    (terpri))))))))

#-swank (main)

;;;
;;; Test
;;;

#+swank
(progn
  (defparameter *lisp-file-pathname* (uiop:current-lisp-file-pathname))
  (setq *default-pathname-defaults* (uiop:pathname-directory-pathname *lisp-file-pathname*))
  (uiop:chdir *default-pathname-defaults*)
  (defparameter *dat-pathname* (uiop:merge-pathnames* "test.dat" *lisp-file-pathname*))
  (defparameter *problem-url* "https://www.codechef.com/problems/ADDFRAC"))

#+swank
(defun gen-dat ()
  (uiop:with-output-file (out *dat-pathname* :if-exists :supersede)
    (format out "")))

#+swank
(defun bench (&optional (out (make-broadcast-stream)))
  (time (run *dat-pathname* out)))

#+(and sbcl (not swank))
(eval-when (:compile-toplevel)
  (when sb-c::*undefined-warnings*
    (error "undefined warnings: ~{~A~^ ~}" sb-c::*undefined-warnings*)))

;; To run: (5am:run! :sample)
#+swank
(5am:test :sample)
