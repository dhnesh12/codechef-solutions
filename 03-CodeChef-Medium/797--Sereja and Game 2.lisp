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
;; This is a decimal reader specialized for the inputs that can be handled
;; within the range of FIXNUM. The implementation is based on
;; SB-IMPL::MAKE-FLOAT.

(defpackage :cp/read-float
  (:use :cl)
  (:export #:read-decimal #:read-float))
(in-package :cp/read-float)

;; TODO: test
(declaim (ftype (function * (values rational &optional)) read-decimal))
(defun read-decimal (&optional (in *standard-input*))
  "Reads a fixed-point decimal and returns it as a rational.

Example:
CL-USER> (read-decimal)
-3.5
-> -7/2

Note: Two numbers before and after the decimal point must be within (INTEGER 0
#.MOST-POSITIVE-FIXNUM)."
  (declare (optimize (speed 3)))
  (macrolet ((%read-byte ()
               `(the (unsigned-byte 8)
                     #+swank (char-code (read-char in nil #\Nul))
                     #-swank (sb-impl::ansi-stream-read-byte in nil #.(char-code #\Nul) nil))))
    (let* ((byte 0)
           (minus nil)
           (number (loop
                     (setq byte (%read-byte))
                     (cond ((<= 48 byte 57)
                            (return (- byte 48)))
                           ((zerop byte) ; #\Nul
                            (error "Read EOF or #\Nul."))
                           ((= byte #.(char-code #\-))
                            (setq minus t)))))
           (divisor 1))
      (declare ((integer 0 #.most-positive-fixnum) number))
      (loop
        (setq byte (%read-byte))
        (if (<= 48 byte 57)
            (setq number
                  (+ (- byte 48)
                     (* 10 (the (integer 0 #.(floor most-positive-fixnum 10)) number))))
            (return)))
      (when (= byte #.(char-code #\.))
        (loop
          (setq byte (%read-byte))
          (if (<= 48 byte 57)
              (setq number
                    (+ (- byte 48)
                       (* 10 (the (integer 0 #.(floor most-positive-fixnum 10)) number)))
                    divisor
                    (* 10 (the (integer 0 #.(floor most-positive-fixnum 10)) divisor)))
              (return))))
      (if minus
          (- (/ number divisor))
          (/ number divisor)))))

(declaim (inline read-float)
         (ftype (function * (values float &optional)) read-float))
(defun read-float (&optional (in *standard-input*))
  "Reads a fixed-point decimal in the format of *READ-DEFAULT-FLOAT-FORMAT*.

NOTE: Two numbers before and after the decimal point must be within (INTEGER 0
#.MOST-POSITIVE-FIXNUM)."
  (coerce (read-decimal in) *read-default-float-format*))

(defpackage :cp/modify-macro
  (:use :cl)
  (:export #:minf #:maxf #:mulf #:divf #:iorf #:xorf #:andf))
(in-package :cp/modify-macro)

(macrolet ((def (name fname)
             `(define-modify-macro ,name (new-value) ,fname)))
  (def minf min)
  (def maxf max)
  (def mulf *)
  (def divf /)
  (def iorf logior)
  (def xorf logxor)
  (def andf logand))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/modify-macro :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-float :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (let* ((*read-default-float-format* 'double-float)
         (tt (read)))
    (dotimes (_ tt)
      (let* ((n (read))
             (m (read))
             (coefs (make-array n :element-type 'double-float))
             (exps (make-array n :element-type 'uint31)))
        (declare (uint31 n m))
        (dotimes (i n)
          (let ((prod 1d0)
                (exp 0))
            (declare (double-float prod)
                     (uint31 exp))
            (dotimes (_ m)
              (let ((p (* 10000 (the double-float (read-float)))))
                (mulf prod p)
                (incf exp 4))
              (when (>= prod 1d4)
                (mulf prod 1d-4)
                (decf exp 4)))
            (setf (aref coefs i) prod
                  (aref exps i) exp)))
        #>coefs
        #>exps
        (let ((denom 0d0))
          (declare (double-float denom))
          (dotimes (i n)
            (incf denom (* (aref coefs i)
                           (expt 10d0 (- (aref exps 0)
                                         (aref exps i))))))
          (format t "~6$~%"
                  (if (zerop denom)
                      0d0
                      (/ (aref coefs 0) denom))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/SEAGM2"))

#+swank
(defun gen-dat ()
  (uiop:with-output-file (out *dat-pathname* :if-exists :supersede)
    (let ((m 20))
      (format out "1 13 ~D~%" m)
      (let ((mat (make-array (list 13 m) :element-type 'uint31 :initial-element 0))
            (sums (make-array m :element-type 'uint62 :initial-element 0)))
        (dotimes (i 13)
          (dotimes (j m)
            (setf (aref mat i j) (+ 1 (random 1000)))))
        (dotimes (j m)
          (setf (aref sums j)
                (loop for i below 13
                      sum (aref mat i j))))
        #>sums
        (dotimes (i 13)
          (dotimes (j m (terpri out))
            (let ((rate (/ (aref mat i j) (aref sums j))))
              (format out "~4$ " (float rate 1d0)))))))))

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
