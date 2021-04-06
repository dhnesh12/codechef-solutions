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
(defpackage :cp/read-digit
  (:use :cl)
  (:export #:read-digit))
(in-package :cp/read-digit)

(declaim (ftype (function * (values (integer 0 9) &optional)) read-digit))
(defun read-digit (&optional (in *standard-input*))
  "Reads a non-negative one-digit integer."
  (declare #.cl-user::*opt*)
  (macrolet ((%read-byte ()
               `(the (unsigned-byte 8)
                     #+swank (char-code (read-char in nil #\Nul))
                     #-swank (sb-impl::ansi-stream-read-byte in nil #.(char-code #\Nul) nil))))
    (loop (let ((byte (%read-byte)))
            (cond ((<= 48 byte 57)
                   (return (- byte 48)))
                  ((zerop byte) ; #\Nul
                   (error "Read EOF or #\Nul.")))))))

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
  (use-package :cp/read-digit :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (write-string
     (with-output-to-string (*standard-output* nil :element-type 'base-char)
       (dotimes (_ tt)
         (block continue
           (let* ((n (read))
                  (mat (make-array (list n n) :element-type 'bit :initial-element 0))
                  (row1 0)
                  (col1 0))
             (declare (uint31 col1 row1))
             (dotimes (i n)
               (dotimes (j n)
                 (setf (aref mat i j) (read-digit))))
             (dotimes (i n)
               (dotimes (j n)
                 (xorf (aref mat i j) (read-digit))))
             (loop for i from 1 below n
                   for count = (loop for j below n
                                     count (= (aref mat 0 j) (aref mat i j)))
                   do (cond ((= 0 count)
                             (incf row1))
                            ((= n count))
                            (t (println -1)
                               (return-from continue))))
             (dotimes (j n)
               (when (= 1 (aref mat 0 j))
                 (incf col1)))
             (let* ((num1 (+ col1 row1))
                    (val 1))
               (when (zerop num1)
                 (println 0)
                 (return-from continue))
               (when (> num1 n)
                 (setq col1 (- n col1)
                       row1 (- n row1)
                       num1 (- (* 2 n) num1)
                       val 0))
               (println row1)
               (loop for i from 0 below n
                     when (= (logxor val (aref mat 0 0)) (aref mat i 0))
                     do (println i))
               #>mat
               (println col1)
               (loop for j from 0 below n
                     when (= val (aref mat 0 j))
                     do (println j))))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/BUTTONS"))

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
