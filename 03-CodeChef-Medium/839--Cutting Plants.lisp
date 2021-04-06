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
;;; double-ended queue with ring-buffer
;;;

(defpackage :cp/deque
  (:use :cl)
  (:export #:deque-empty-error #:deque-invalid-index-error #:define-deque))
(in-package :cp/deque)

(declaim (inline %power-of-two-ceiling))
(defun %power-of-two-ceiling (x)
  (ash 1 (integer-length (- x 1))))

(deftype index () '(integer 0 #.(floor array-total-size-limit 2)))

(define-condition deque-empty-error (error)
  ((queue :initarg :queue :reader deque-empty-error-queue))
  (:report
   (lambda (condition stream)
     (format stream "Attempted to pop empty deque ~W" (deque-empty-error-queue condition)))))

(define-condition deque-invalid-index-error (error)
  ((queue :initarg :queue :reader deque-invalid-index-error-queue)
   (index :initarg :index :reader deque-invalid-index-error-index))
  (:report
   (lambda (condition stream)
     (format stream "Invalid index ~W for ~W."
             (deque-invalid-index-error-index condition)
             (deque-invalid-index-error-queue condition)))))

(defmacro define-deque (name &key (element-type 'fixnum))
  "Defines deque for given ELEMENT-TYPE.

constructor: MAKE-<NAME>.
basic operations: <NAME>-PUSH-FRONT, <NAME>-PUSH-BACK, <NAME>-POP-FRONT,
<NAME>-POP-BACK.
accessor: <NAME>-REF. <NAME>-PEEK-FRONT, <NAME>-PEEK-BACK
utilities: <NAME>-EMPTY-P, <NAME>-REINITIALIZE.
"
  (let ((push-front (intern (format nil "~A-PUSH-FRONT" name)))
        (push-back (intern (format nil "~A-PUSH-BACK" name)))
        (pop-front (intern (format nil "~A-POP-FRONT" name)))
        (pop-back (intern (format nil "~A-POP-BACK" name)))
        (peek-front (intern (format nil "~A-PEEK-FRONT" name)))
        (peek-back (intern (format nil "~A-PEEK-BACK" name)))
        (empty-p (intern (format nil "~A-EMPTY-P" name)))
        (constructor (intern (format nil "MAKE-~A" name)))
        (reinitializer (intern (format nil "~A-REINITIALIZE" name)))
        (reffer (intern (format nil "~A-REF" name)))
        (data-getter (intern (format nil "~A-DATA" name)))
        (front-getter (intern (format nil "~A-FRONT" name)))
        (count-getter (intern (format nil "~A-COUNT" name)))
        (adjuster (intern (format nil "%~A-ADJUST" name))))
    `(progn
       (defstruct (,name (:constructor ,constructor
                             (initial-size
                              &aux
                              (data (make-array (max 2 (%power-of-two-ceiling initial-size))
                                                :element-type ',element-type))))
                         (:copier nil)
                         (:predicate nil))
         (data nil :type (simple-array ,element-type (*)))
         (front 0 :type index)
         (count 0 :type index))
       (declaim (ftype (function (index) (values ,name &optional))
                       ,constructor))

       (defun ,adjuster (,name)
         ;; FIXME: Change the safety to zero when you believe this library is
         ;; stable.
         (declare (optimize (speed 3)))
         (symbol-macrolet ((front (,front-getter ,name))
                           (count (,count-getter ,name))
                           (data (,data-getter ,name)))
           (let ((length (length data)))
             (when (= count length)
               (let ((new-data (make-array (* 2 length) :element-type ',element-type)))
                 (replace new-data data :start2 front)
                 (when (< length (+ front count))
                   (replace new-data data :start1 (- length front) :end2 front))
                 (setq data new-data
                       front 0))))))

       (declaim (inline ,push-front))
       (defun ,push-front (obj ,name)
         "Adds OBJ to the front of deque."
         (symbol-macrolet ((front (,front-getter ,name))
                           (count (,count-getter ,name)))
           (,adjuster ,name)
           (let* ((data (,data-getter ,name))
                  (length (length data))
                  (mask (- length 1))
                  (next-front (logand mask (+ front mask))))
             (declare (index next-front))
             (setf (aref data next-front) obj)
             (setq front next-front)
             (incf count)
             ,name)))

       (declaim (inline ,pop-front))
       (defun ,pop-front (,name)
         "Removes and returns the first element of deque."
         (symbol-macrolet ((front (,front-getter ,name))
                           (count (,count-getter ,name)))
           (when (zerop count)
             (error 'deque-empty-error :queue ,name))
           (let* ((data (,data-getter ,name))
                  (length (length data))
                  (mask (- length 1))
                  (next (logand mask (+ front 1))))
             (declare (index next))
             (prog1 (aref data front)
               (setq front next)
               (decf count)))))

       (declaim (inline ,peek-front))
       (defun ,peek-front (,name)
         "Returns the first element of deque."
         (symbol-macrolet ((front (,front-getter ,name))
                           (count (,count-getter ,name)))
           (when (zerop count)
             (error 'deque-empty-error :queue ,name))
           (let* ((data (,data-getter ,name)))
             (aref data front))))

       (declaim (inline ,push-back))
       (defun ,push-back (obj ,name)
         "Adds OBJ to the end of deque."
         (symbol-macrolet ((front (,front-getter ,name))
                           (count (,count-getter ,name)))
           (,adjuster ,name)
           (let* ((data (,data-getter ,name))
                  (length (length data))
                  (mask (- length 1))
                  (pos (logand mask (+ front count))))
             (declare (index pos))
             (setf (aref data pos) obj)
             (incf count)
             ,name)))

       (declaim (inline ,pop-back))
       (defun ,pop-back (,name)
         "Removes and returns the last element of deque."
         (symbol-macrolet ((front (,front-getter ,name))
                           (count (,count-getter ,name)))
           (when (zerop count)
             (error 'deque-empty-error :queue ,name))
           (let* ((data (,data-getter ,name))
                  (length (length data))
                  (mask (- length 1))
                  (pos (logand mask (+ front count mask))))
             (declare (index pos))
             (decf count)
             (aref data pos))))

       (declaim (inline ,peek-back))
       (defun ,peek-back (,name)
         "Returns the last element of deque."
         (symbol-macrolet ((front (,front-getter ,name))
                           (count (,count-getter ,name)))
           (when (zerop count)
             (error 'deque-empty-error :queue ,name))
           (let* ((data (,data-getter ,name))
                  (length (length data))
                  (mask (- length 1))
                  (pos (logand mask (+ front count mask))))
             (declare (index pos))
             (aref data pos))))

       (declaim (inline ,empty-p))
       (defun ,empty-p (,name)
         "Returns true iff deque is empty."
         (zerop (,count-getter ,name)))

       (declaim (inline ,reinitializer))
       (defun ,reinitializer (,name)
         "Removes all the element of deque."
         (setf (,count-getter ,name) 0))

       (declaim (inline ,reffer))
       (defun ,reffer (,name index)
         "Returns the (0-based) INDEX-th element from the front."
         (declare (index index))
         (symbol-macrolet ((front (,front-getter ,name))
                           (count (,count-getter ,name)))
           (when (>= index count)
             (error 'deque-invalid-index-error :index index :queue ,name))
           (let* ((data (,data-getter ,name))
                  (length (length data))
                  (mask (- length 1))
                  (pos (logand mask (+ front index))))
             (declare (index pos))
             (aref data pos))))

       (declaim (inline (setf ,reffer)))
       (defun (setf ,reffer) (new-value ,name index)
         (declare (index index))
         (symbol-macrolet ((front (,front-getter ,name))
                           (count (,count-getter ,name)))
           (when (>= index count)
             (error 'deque-invalid-index-error :index index :queue ,name))
           (let* ((data (,data-getter ,name))
                  (length (length data))
                  (mask (- length 1))
                  (pos (logand mask (+ front index))))
             (declare (index pos))
             (setf (aref data pos) new-value)))))))

#+(or)
(define-deque deque :element-type fixnum)

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/deque :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(define-deque deque :element-type uint31)

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (dotimes (_ tt)
      (let* ((n (read))
             (as (make-array n :element-type 'uint31 :initial-element 0))
             (bs (make-array n :element-type 'uint31 :initial-element 0))
             (deque (make-deque n))
             (res 0))
        (declare (uint31 res))
        (dotimes (i n)
          (setf (aref as i) (read-fixnum)))
        (dotimes (i n)
          (setf (aref bs i) (read-fixnum)))
        (println
         (dotimes (i n res)
           (let ((a (aref as i))
                 (b (aref bs i)))
             (when (< a b)
               (return -1))
             (loop while (and (not (deque-empty-p deque))
                              (< a (deque-peek-back deque)))
                   do (deque-pop-back deque))
             (loop while (and (not (deque-empty-p deque))
                              (< (deque-peek-front deque) b))
                   do (deque-pop-front deque))
             (unless (or (= a b)
                         (and (not (deque-empty-p deque))
                              (= b (deque-peek-front deque))))
               (incf res)
               (deque-push-front b deque)))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/CUTPLANT"))

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
(5am:test :sample
  (5am:is
   (equal "2
3
0
-1
"
          (run "4
3
3 1 3
2 1 2
7
1 3 4 5 1 2 3
1 2 1 2 1 1 1
3
2 3 9
2 3 9
2
1 2
2 1
" nil))))
