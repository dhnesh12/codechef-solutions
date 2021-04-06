#-swank
(eval-when (:compile-toplevel)
  (unless (member :child-sbcl *features*)
    (quit
     :recklessly-p t
     :unix-status
     (process-exit-code
      (run-program *runtime-pathname*
                   `("--control-stack-size" "256MB"
                     "--noinform" "--disable-ldb" "--lose-on-corruption" "--end-runtime-options"
                     "--eval" "(push :child-sbcl *features*)"
                     "--eval" ,(format nil "(progn (compile-file ~S) (quit))" *compile-file-pathname*))
                   :output t :error t :input t)))))

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
;; Treap accessible by index (O(log(n)))
;; Virtually it works like std::set of C++ or TreeSet of Java. 

;; Note:
;; - You shouldn't insert duplicate keys into a treap unless you know what you
;; are doing.
;; - You cannot rely on the side effect when you call any destructive operations
;; on a treap. Always use the returned value.
;; - An empty treap is NIL.

;; TODO: abstraction

(defpackage :cp/ref-able-treap
  (:use :cl)
  (:export #:treap #:treap-count #:treap-find #:treap-position #:treap-bisect-left
           #:treap-split #:treap-insert #:treap-push #:treap-pop #:make-treap
           #:treap-delete #:treap-merge #:treap-map #:invalid-treap-index-error
           #:treap-ref #:treap-first #:treap-last #:treap-unite #:treap-reverse))
(in-package :cp/ref-able-treap)

(defstruct (treap (:constructor %make-treap (key priority &key left right (count 1)))
                  (:copier nil)
                  (:conc-name %treap-))
  (key 0 :type fixnum)
  (priority 0 :type (integer 0 #.most-positive-fixnum))
  (count 0 :type (integer 0 #.most-positive-fixnum))
  (left nil :type (or null treap))
  (right nil :type (or null treap)))

(declaim (inline treap-count))
(defun treap-count (treap)
  "Returns the size of the (nullable) TREAP."
  (declare ((or null treap) treap))
  (if (null treap)
      0
      (%treap-count treap)))

(declaim (inline update-count))
(defun update-count (treap)
  (declare (treap treap))
  (setf (%treap-count treap)
        (+ 1
           (treap-count (%treap-left treap))
           (treap-count (%treap-right treap)))))

(declaim (inline treap-bisect-left)
         (ftype (function * (values (integer 0 #.most-positive-fixnum) t &optional)) treap-bisect-left))
(defun treap-bisect-left (value treap &key (order #'<))
  "Returns two values: the smallest index and the corresponding key that
satisfies TREAP[index] >= VALUE. Returns the size of TREAP and VALUE instead if
TREAP[size-1] < VALUE."
  (labels ((recur (count treap)
             (declare ((integer 0 #.most-positive-fixnum) count))
             (cond ((null treap) (values nil nil))
                   ((funcall order (%treap-key treap) value)
                    (recur count (%treap-right treap)))
                   (t (let ((left-count (- count (treap-count (%treap-right treap)) 1)))
                        (multiple-value-bind (idx key)
                            (recur left-count (%treap-left treap))
                          (if idx
                              (values idx key)
                              (values left-count (%treap-key treap)))))))))
    (declare (ftype (function * (values t t &optional)) recur))
    (multiple-value-bind (idx key)
        (recur (treap-count treap) treap)
      (if idx
          (values idx key)
          (values (treap-count treap) value)))))

(declaim (inline treap-split)
         (ftype (function * (values (or null treap) (or null treap) &optional)) treap-split))
(defun treap-split (key treap &key (order #'<))
  "Destructively splits TREAP with reference to KEY and returns two treaps,
the smaller sub-treap (< KEY) and the larger one (>= KEY)."
  (declare ((or null treap) treap))
  (labels ((recur (treap)
             (cond ((null treap)
                    (values nil nil))
                   ((funcall order (%treap-key treap) key)
                    (multiple-value-bind (left right) (recur (%treap-right treap))
                      (setf (%treap-right treap) left)
                      (update-count treap)
                      (values treap right)))
                   (t
                    (multiple-value-bind (left right) (recur (%treap-left treap))
                      (setf (%treap-left treap) right)
                      (update-count treap)
                      (values left treap))))))
    (recur treap)))

(declaim (inline treap-insert))
(defun treap-insert (key treap &key (order #'<))
  "Destructively inserts KEY into TREAP and returns the resultant treap."
  (declare ((or null treap) treap))
  (let ((node (%make-treap key (random most-positive-fixnum))))
    (labels ((recur (treap)
               (declare (treap node))
               (cond ((null treap) node)
                     ((> (%treap-priority node) (%treap-priority treap))
                      (setf (values (%treap-left node) (%treap-right node))
                            (treap-split (%treap-key node) treap :order order))
                      (update-count node)
                      node)
                     (t
                      (if (funcall order (%treap-key node) (%treap-key treap))
                          (setf (%treap-left treap)
                                (recur (%treap-left treap)))
                          (setf (%treap-right treap)
                                (recur (%treap-right treap))))
                      (update-count treap)
                      treap))))
      (recur treap))))

(defmacro treap-push (key treap &optional (order '#'<))
  "Pushes a KEY to TREAP."
  `(setf ,treap (treap-insert ,key ,treap :order ,order)))

(defmacro treap-pop (key treap &optional (order '#'<))
  "Deletes a KEY from TREAP."
  `(setf ,treap (treap-delete ,key ,treap :order ,order)))

;; NOTE: It takes O(nlog(n)).
(defun treap (order &rest keys)
  (loop with res = nil
        for key in keys
        do (setf res (treap-insert key res :order order))
        finally (return res)))

(declaim (ftype (function * (values (or null treap) &optional)) treap-merge))
(defun treap-merge (left right)
  "Destructively concatenates two treaps. Assumes that all keys of LEFT are
smaller (or larger, depending on the order) than those of RIGHT.

Note that this `merge' is different from CL:MERGE and rather close to
CL:CONCATENATE. (TREAP-UNITE is the analogue of the former.)"
  (declare #.cl-user::*opt*
           ((or null treap) left right))
  (cond ((null left) right)
        ((null right) left)
        ((> (%treap-priority left) (%treap-priority right))
         (setf (%treap-right left)
               (treap-merge (%treap-right left) right))
         (update-count left)
         left)
        (t
         (setf (%treap-left right)
               (treap-merge left (%treap-left right)))
         (update-count right)
         right)))

(declaim (inline treap-delete))
(defun treap-delete (key treap &key (order #'<))
  "Destructively deletes KEY in TREAP and returns the resultant treap."
  (declare ((or null treap) treap))
  (labels ((recur (treap)
             (cond ((null treap) nil)
                   ((funcall order key (%treap-key treap))
                    (setf (%treap-left treap) (recur (%treap-left treap)))
                    (update-count treap)
                    treap)
                   ((funcall order (%treap-key treap) key)
                    (setf (%treap-right treap) (recur (%treap-right treap)))
                    (update-count treap)
                    treap)
                   (t
                    (treap-merge (%treap-left treap) (%treap-right treap))))))
    (declare (ftype (function * (values (or null treap) &optional)) recur))
    (recur treap)))

(declaim (inline treap-map))
(defun treap-map (function treap)
  "Successively applies FUNCTION to TREAP[0], ..., TREAP[SIZE-1]. FUNCTION must
take one argument."
  (declare (function function))
  (labels ((recur (treap)
             (when treap
               (recur (%treap-left treap))
               (funcall function (%treap-key treap))
               (recur (%treap-right treap)))))
    (recur treap)))

(defmethod print-object ((object treap) stream)
  (print-unreadable-object (object stream :type t)
    (let ((init t))
      (treap-map (lambda (key)
                   (if init
                       (setq init nil)
                       (write-char #\  stream))
                   (write key :stream stream))
                 object))))

(define-condition invalid-treap-index-error (type-error)
  ((treap :initarg :treap :reader invalid-treap-index-error-treap)
   (index :initarg :index :reader invalid-treap-index-error-index))
  (:report
   (lambda (condition stream)
     (format stream "Invalid index ~W for treap ~W."
             (invalid-treap-index-error-index condition)
             (invalid-treap-index-error-treap condition)))))

(defun treap-ref (treap index)
  "Returns the INDEX-th element of TREAP."
  (declare (optimize (speed 3))
           ((or null treap) treap)
           ((integer 0 #.most-positive-fixnum) index))
  (when (>= index (treap-count treap))
    (error 'invalid-treap-index-error :treap treap :index index))
  (labels ((%ref (treap index)
             (declare (optimize (speed 3) (safety 0))
                      ((integer 0 #.most-positive-fixnum) index))
             (let ((left-count (treap-count (%treap-left treap))))
               (cond ((< index left-count)
                      (%ref (%treap-left treap) index))
                     ((> index left-count)
                      (%ref (%treap-right treap) (- index left-count 1)))
                     (t (%treap-key treap))))))
    (%ref treap index)))

(defpackage :cp/read-schar
  (:use :cl)
  (:export #:read-schar))
(in-package :cp/read-schar)

(declaim (inline read-schar))
(defun read-schar (&optional (stream *standard-input*))
  (declare #-swank (sb-kernel:ansi-stream stream)
           (inline read-byte))
  #+swank (read-char stream nil #\Newline) ; on SLIME
  #-swank (code-char (read-byte stream nil #.(char-code #\Newline))))

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

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-schar :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/ref-able-treap :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((n (read))
         (q (read))
         (row-treaps (make-array 2 :element-type t :initial-element nil))
         (col-treaps (make-array 2 :element-type t :initial-element nil))
         (row-bits (make-array n :element-type 'bit :initial-element 0))
         (col-bits (make-array n :element-type 'bit :initial-element 0))
         (row-indices (make-array n :element-type 'int32 :initial-element -1))
         (col-indices (make-array n :element-type 'int32 :initial-element -1)))
    (declare (uint31 n q))
    (write-string
     (with-output-to-string (*standard-output* nil :element-type 'base-char)
       (dotimes (qi q)
         (ecase (prog1 (read-schar) (read-schar) (read-schar))
           (#\R (ecase (read-schar)
                  (#\Q
                   (dotimes (_ 5)
                     (read-schar))
                   (let* ((i (- (read-fixnum) 1))
                          (last-x (aref row-bits i))
                          (last-qi (aref row-indices i))
                          (treap (aref col-treaps (logxor 1 last-x)))
                          (count (- (treap-count treap)
                                    (treap-bisect-left last-qi treap))))
                     (println
                      (if (zerop last-x)
                          (- n count)
                          count))))
                  (#\S
                   (dotimes (_ 3)
                     (read-schar))
                   (let* ((i (- (read-fixnum) 1))
                          (x (read-fixnum))
                          (last-x (aref row-bits i))
                          (last-qi (aref row-indices i)))
                     (setf (aref row-bits i) x
                           (aref row-indices i) qi)
                     (treap-pop last-qi (aref row-treaps last-x))
                     (treap-push qi (aref row-treaps x))))))
           (#\C (ecase (read-schar)
                  (#\Q
                   (dotimes (_ 5)
                     (read-schar))
                   (let* ((i (- (read-fixnum) 1))
                          (last-x (aref col-bits i))
                          (last-qi (aref col-indices i))
                          (treap (aref row-treaps (logxor 1 last-x)))
                          (count (- (treap-count treap)
                                    (treap-bisect-left last-qi treap))))
                     (println
                      (if (zerop last-x)
                          (- n count)
                          count))))
                  (#\S
                   (dotimes (_ 3)
                     (read-schar))
                   (let* ((i (- (read-fixnum) 1))
                          (x (read-fixnum))
                          (last-x (aref col-bits i))
                          (last-qi (aref col-indices i)))
                     (setf (aref col-bits i) x
                           (aref col-indices i) qi)
                     (treap-pop last-qi (aref col-treaps last-x))
                     (treap-push qi (aref col-treaps x))))))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/MBOARD"))

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
