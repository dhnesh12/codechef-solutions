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
;;;
;;; Matrix multiplication over semiring
;;;

(defpackage :cp/gemm
  (:use :cl)
  (:export #:gemm! #:gemm #:matrix-power #:gemv))
(in-package :cp/gemm)

;; NOTE: not tested

;; NOTE: These funcions are slow on SBCL version earlier than 1.5.6 as the type
;; propagation of MAKE-ARRAY doesn't work. The following files are required to
;; enable the optimization.
;; version < 1.5.0: array-element-type.lisp, make-array-header.lisp
;; version < 1.5.6: make-array-header.lisp
(declaim (inline gemm!))
(defun gemm! (a b c &key (op+ #'+) (op* #'*) (identity+ 0))
  "Computes C := A*B. This function destructively modifies C. (OP+, OP*) must
comprise a semiring. IDENTITY+ is the identity element w.r.t. OP+."
  (declare ((array * (* *)) a b c))
  (dotimes (row (array-dimension a 0))
    (dotimes (col (array-dimension b 1))
      (let ((value identity+))
        (dotimes (k (array-dimension a 1))
          (setq value
                (funcall op+ value (funcall op* (aref a row k) (aref b k col)))))
        (setf (aref c row col) value))))
  c)

(declaim (inline gemm))
(defun gemm (a b &key (op+ #'+) (op* #'*) (identity+ 0))
  "Computes A*B. (OP+, OP*) must comprise a semiring. IDENTITY+ is the identity
element w.r.t. OP+."
  (declare ((array * (* *)) a b)
           (function op+ op*))
  (let ((c (make-array (list (array-dimension a 0) (array-dimension b 1))
                       :element-type 'double-float)))
    (dotimes (row (array-dimension a 0))
      (dotimes (col (array-dimension b 1))
        (let ((value identity+))
          (dotimes (k (array-dimension a 1))
            (setq value
                  (funcall op+ value (funcall op* (aref a row k) (aref b k col)))))
          (setf (aref c row col) value))))
    c))

(declaim (inline matrix-power))
(defun matrix-power (base power &key (op+ #'+) (op* #'*) (identity+ 0) (identity* 1))
  "Computes BASE^POWER. (OP+, OP*) must form a semiring. IDENTITY+ [IDENTITY*]
is the identity element w.r.t. OP+ [OP*]."
  (declare ((array * (* *)) base)
           (function op+ op*)
           ((integer 0 #.most-positive-fixnum) power))
  (let ((size (array-dimension base 0)))
    (assert (= size (array-dimension base 1)))
    (let ((iden (make-array (array-dimensions base)
                            :element-type 'double-float
                            :initial-element identity+)))
      (dotimes (i size)
        (setf (aref iden i i) identity*))
      (labels ((recur (p)
                 (declare ((integer 0 #.most-positive-fixnum) p))
                 (cond ((zerop p) iden)
                       ((evenp p)
                        (let ((res (recur (ash p -1))))
                          (gemm res res :op+ op+ :op* op* :identity+ identity+)))
                       (t
                        (gemm base (recur (- p 1))
                              :op+ op+ :op* op* :identity+ identity+)))))
        (recur power)))))

(declaim (inline gemv))
(defun gemv (a x &key (op+ #'+) (op* #'*) (identity+ 0))
  "Calculates A*x for a matrix A and a vector x. (OP+, OP*) must form a
semiring. IDENTITY+ is the identity element w.r.t. OP+."
  (declare ((array * (* *)) a)
           ((array * (*)) x)
           (function op+ op*))
  (let ((res (make-array (array-dimension a 0) :element-type (array-element-type x))))
    (dotimes (i (length res))
      (let ((value identity+))
        (dotimes (j (length x))
          (setq value
                (funcall op+ value (funcall op* (aref a i j) (aref x j)))))
        (setf (aref res i) value)))
    res))

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
  (use-package :cp/gemm :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun calc (c)
  (- (char-code c) 97))

(defun main ()
  (let* ((tt (read)))
    (dotimes (_ tt)
      (let ((n (read))
            (k (read))
            (s (read-line))
            (mat (make-array '(26 26) :element-type 'double-float))
            (table (make-hash-table :test #'equal))
            (res 0d0))
        (declare (uint31 n k)
                 (simple-string s)
                 (double-float res))
        (assert (every #'lower-case-p s))
        (let ((*read-default-float-format* 'double-float))
          (dotimes (i 26)
            (dotimes (j 26)
              (setf (aref mat i j) (float (read) 1d0)))))
        #>mat
        (let ((mat (matrix-power mat k :identity+ 0d0 :identity* 1d0)))
          #>mat
          (dotimes (_ n)
            (let ((dest (read-line))
                  (prob 1d0))
              (declare (simple-string dest)
                       (double-float prob))
              (assert (every #'lower-case-p dest))
              
              (when (and (= (length s) (length dest))
                         (not (gethash dest table)))
                (setf (gethash dest table) t)
                (dotimes (i (length s))
                  (mulf prob (aref mat
                                   (calc (aref s i))
                                   (calc (aref dest i)))))
                (incf res prob)))))
        (format t "~F~%" res)))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/CHEFWORD"))

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
