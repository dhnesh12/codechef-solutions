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

(defconstant +mod+ 23102009)

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
;;;
;;; Arithmetic operations with static modulus
;;;

(defpackage :cp/mod-operations
  (:use :cl)
  (:export #:define-mod-operations))
(in-package :cp/mod-operations)

(defmacro define-mod-operations
    (divisor &optional (package #+sbcl (sb-int:sane-package) #-sbcl *package*))
  (let ((mod* (intern "MOD*" package))
        (mod+ (intern "MOD+" package))
        (mod- (intern "MOD-" package))
        (incfmod (intern "INCFMOD" package))
        (decfmod (intern "DECFMOD" package))
        (mulfmod (intern "MULFMOD" package)))
    `(progn
       (defun ,mod* (&rest args)
         (cond ((cdr args) (reduce (lambda (x y) (mod (* x y) ,divisor)) args))
               (args (mod (car args) ,divisor))
               (t 1)))
       (defun ,mod+ (&rest args)
         (cond ((cdr args) (reduce (lambda (x y) (mod (+ x y) ,divisor)) args))
               (args (mod (car args) ,divisor))
               (t 0)))
       (defun ,mod- (&rest args)
         (if (cdr args)
             (reduce (lambda (x y) (mod (- x y) ,divisor)) args)
             (mod (- (car args)) ,divisor)))

       #+sbcl
       (eval-when (:compile-toplevel :load-toplevel :execute)
         (locally (declare (sb-ext:muffle-conditions warning))
           (sb-c:define-source-transform ,mod* (&rest args)
             (case (length args)
               (0 1)
               (1 `(mod ,(car args) ,',divisor))
               (otherwise (reduce (lambda (x y) `(mod (* ,x ,y) ,',divisor)) args))))
           (sb-c:define-source-transform ,mod+ (&rest args)
             (case (length args)
               (0 0)
               (1 `(mod ,(car args) ,',divisor))
               (otherwise (reduce (lambda (x y) `(mod (+ ,x ,y) ,',divisor)) args))))
           (sb-c:define-source-transform ,mod- (&rest args)
             (case (length args)
               (0 (values nil t))
               (1 `(mod (- ,(car args)) ,',divisor))
               (otherwise (reduce (lambda (x y) `(mod (- ,x ,y) ,',divisor)) args))))))

       (define-modify-macro ,incfmod (delta)
         (lambda (x y) (mod (+ x y) ,divisor)))
       (define-modify-macro ,decfmod (delta)
         (lambda (x y) (mod (- x y) ,divisor)))
       (define-modify-macro ,mulfmod (multiplier)
         (lambda (x y) (mod (* x y) ,divisor))))))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/mod-operations :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(define-mod-operations +mod+)

(declaim (ftype (function * (values (simple-array int32 (* *)) &optional))
                make-nexts))
(defun make-nexts (s)
  (declare (simple-string s))
  (let* ((n (length s))
         (res (make-array (list n 26) :element-type 'int32 :initial-element -1)))
    (dotimes (i n)
      (let ((c (- (char-code (aref s i)) 97)))
        (loop for j from i downto 0
              while (= -1 (aref res j c))
              do (setf (aref res j c) i))))
    res))

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (dotimes (_ tt)
      (let* ((s1 (read-line))
             (n1 (length s1))
             (nexts1 (make-nexts s1))
             (s2 (read-line))
             (n2 (length s2))
             (nexts2 (make-nexts s2))
             (dp-len (make-array (list (+ n1 1) (+ n2 1))
                                 :element-type 'int32
                                 :initial-element -1))
             (dp-num (make-array (list (+ n1 1) (+ n2 1))
                                 :element-type 'uint31
                                 :initial-element 0)))
        (declare (simple-string s1 s2))
        (read-line *standard-input* nil)
        (setf (aref dp-len 0 0) 0
              (aref dp-num 0 0) 1)
        (dotimes (x n1)
          (dotimes (y n2)
            (let ((len (aref dp-len x y))
                  (num (aref dp-num x y)))
              (unless (= -1 len)
                (dotimes (c 26)
                  (let ((new-x (+ 1 (aref nexts1 x c)))
                        (new-y (+ 1 (aref nexts2 y c))))
                    (unless (or (= new-x 0) (= new-y 0))
                      (let ((dest-len (aref dp-len new-x new-y)))
                        (cond ((> (+ len 1) dest-len)
                               (setf (aref dp-len new-x new-y) (+ len 1)
                                     (aref dp-num new-x new-y) num))
                              ((= (+ len 1) dest-len)
                               (incfmod (aref dp-num new-x new-y) num)))))))))))
        (let ((max-len (reduce #'max (array-storage-vector dp-len)))
              (res 0))
          (declare (uint31 max-len)
                   (uint62 res))
          (dotimes (x (+ n1 1))
            (dotimes (y (+ n2 1))
              (when (= max-len (aref dp-len x y))
                (incf res (aref dp-num x y)))))
          (format t "~D ~D~%" max-len (mod res +mod+)))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/J2"))

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
