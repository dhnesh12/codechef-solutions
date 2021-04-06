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

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-schar :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/modify-macro :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (dotimes (_ tt)
      (let* ((n (read))
             (s (make-string n :element-type 'base-char :initial-element #\Nul))
             (pp (make-array '(5001 5001) :element-type 'bit :initial-element 0))
             (dp (make-array (+ n 1) :element-type 'uint31 :initial-element #x7fffffff)))
        (declare (uint31 n))
        (dotimes (i n)
          (setf (aref s i) (read-schar)))
        (setf (aref pp 0 0) 1)
        (loop for r from 1 to n
              for c = (aref s (- r 1))
              do (setf (aref pp r r) 1
                       (aref pp (- r 1) r) 1)
                 (loop for l from (- r 2) downto 0
                       when (and (char= c (aref s l))
                                 (= 1 (aref pp (+ l 1) (- r 1))))
                       do (setf (aref pp l r) 1)))
        (setf (aref dp 0) 0)
        (dotimes (x n)
          (let ((value (aref dp x)))
            (loop for new-x from (+ x 1) to n
                  when (= 1 (aref pp x new-x))
                  do (minf (aref dp new-x) (+ 1 value)))))
        (println (aref dp n))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/CHGLSTGT"))

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
