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
;;;
;;; Calculate a^n on any monoids in O(log(n)) time
;;;

(defpackage :cp/power
  (:use :cl)
  (:export #:power))
(in-package :cp/power)

(declaim (inline power))
(defun power (base exponent op identity)
  "OP := binary operation (comprising a monoid)
IDENTITY := identity element w.r.t. OP"
  (declare ((integer 0) exponent))
  (loop with res = identity
        while (> exponent 0)
        when (oddp exponent)
        do (setq res (funcall op res base))
        do (setq base (funcall op base base)
                 exponent (ash exponent -1))
        finally (return res)))

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

(defpackage :cp/mod-inverse
  (:use :cl)
  #+sbcl (:import-from :sb-c #:lvar-type #:integer-type-numeric-bounds)
  (:export #:mod-inverse))
(in-package :cp/mod-inverse)

#+sbcl
(eval-when (:compile-toplevel :load-toplevel :execute)
  (sb-c:defknown %mod-inverse ((integer 0) (integer 1)) (integer 0)
      (sb-c:flushable sb-c:foldable)
    :overwrite-fndb-silently t)
  (sb-c:defknown mod-inverse (integer (integer 1)) (integer 0)
      (sb-c:flushable sb-c:foldable)
    :overwrite-fndb-silently t)
  (defun derive-mod (modulus)
    (let ((high (nth-value 1 (integer-type-numeric-bounds (lvar-type modulus)))))
      (sb-kernel:specifier-type (if (integerp high)
                                    `(integer 0 (,high))
                                    `(integer 0)))))
  (sb-c:defoptimizer (%mod-inverse sb-c:derive-type) ((integer modulus))
    (declare (ignore integer))
    (derive-mod modulus))
  (sb-c:defoptimizer (mod-inverse sb-c:derive-type) ((integer modulus))
    (declare (ignore integer))
    (derive-mod modulus)))

(defun %mod-inverse (integer modulus)
  (declare (optimize (speed 3) (safety 0))
           #+sbcl (sb-ext:muffle-conditions sb-ext:compiler-note))
  (macrolet ((frob (utype stype)
               `(let ((a integer)
                      (b modulus)
                      (u 1)
                      (v 0))
                  (declare (,stype a b u v))
                  (loop until (zerop b)
                        for quot = (floor a b)
                        do (decf a (the ,stype (* quot b)))
                           (rotatef a b)
                           (decf u (the ,stype (* quot v)))
                           (rotatef u v))
                  (the ,utype (if (< u 0)
                                  (+ u modulus)
                                  u)))))
    (typecase modulus
      ((unsigned-byte 31) (frob (unsigned-byte 31) (signed-byte 32)))
      ((unsigned-byte 62) (frob (unsigned-byte 62) (signed-byte 63)))
      (otherwise (frob (integer 0) integer)))))

(declaim (inline mod-inverse))
(defun mod-inverse (integer modulus)
  "Solves ax = 1 mod m. Signals DIVISION-BY-ZERO when INTEGER and MODULUS are
not coprime."
  (let* ((integer (mod integer modulus))
         (result (%mod-inverse integer modulus)))
    (unless (or (= 1 (mod (* integer result) modulus)) (= 1 modulus))
      (error 'division-by-zero
             :operands (list integer modulus)
             :operation 'mod-inverse))
    result))

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
  (use-package :cp/mod-inverse :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/mod-operations :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/power :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(define-mod-operations +mod+)

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (write-string
     (with-output-to-string (*standard-output* nil :element-type 'base-char)
       (dotimes (_ tt)
         (let* ((l (read-fixnum))
                (d (read-fixnum))
                (exp (read-fixnum))
                (mat (coerce (vector (mod* 2 d (mod-inverse l +mod+)) (mod -1 +mod+) 1 0)
                             '(simple-array uint31 (*))))
                (iden (coerce (vector 1 0 0 1)
                              '(simple-array uint31 (*))))
                (pow (power mat (- exp 1)
                            (lambda (mat1 mat2)
                              (declare ((simple-array uint31 (*)) mat1 mat2))
                              (let ((res (make-array 4 :element-type 'uint31)))
                                (setf (aref res 0)
                                      (mod+ (mod* (aref mat1 0) (aref mat2 0))
                                            (mod* (aref mat1 1) (aref mat2 2)))
                                      (aref res 1)
                                      (mod+ (mod* (aref mat1 0) (aref mat2 1))
                                            (mod* (aref mat1 1) (aref mat2 3)))
                                      (aref res 2)
                                      (mod+ (mod* (aref mat1 2) (aref mat2 0))
                                            (mod* (aref mat1 3) (aref mat2 2)))
                                      (aref res 3)
                                      (mod+ (mod* (aref mat1 2) (aref mat2 1))
                                            (mod* (aref mat1 3) (aref mat2 3))))
                                res))
                            iden)))
           (declare (uint31 d l)
                    (uint62 exp)
                    ((simple-array uint31 (*)) pow))
           (println (mod* l (mod+ (mod* (aref pow 0) (mod* d (mod-inverse l +mod+)))
                                  (aref pow 1))))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/CDYN2021/problems/CHFTNS"))

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
   (equal "-1
 1     
 WW
"
          (run "2
LLLL
1 3
WL
4 6
" nil))))
