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

(define-mod-operations cl-user::+mod+ :cl-user)

;;;
;;; Fast Zeta/Moebius transforms w.r.t. divisor or multiple in O(nloglog(n)) time.
;;;

(defpackage :cp/zeta-integer
  (:use :cl)
  (:export #:divisor-transform! #:inverse-divisor-transform!
           #:multiple-transform! #:inverse-multiple-transform!))
(in-package :cp/zeta-integer)

(declaim (inline divisor-transform!))
(defun divisor-transform! (vector &optional (op+ #'+) (handle-zero t))
  "Sets each VECTOR[i] to the sum of VECTOR[d] for all the divisors d of i in
O(nloglog(n)) time. Ignores VECTOR[0] when HANDLE-ZERO is NIL."
  (declare (vector vector))
  (let* ((n (length vector))
         (sieve (make-array n :element-type 'bit :initial-element 1)))
    (when handle-zero
      (loop for i from 1 below n
            do (setf (aref vector 0)
                     (funcall op+ (aref vector 0) (aref vector i)))))
    (loop for p from 2 below n
          when (= 1 (sbit sieve p))
          do (loop for k from 1 below (ceiling n p)
                   for pmult of-type fixnum = (* k p)
                   do (setf (sbit sieve pmult) 0)
                      (setf (aref vector pmult)
                            (funcall op+ (aref vector pmult) (aref vector k)))))
    vector))

(declaim (inline inverse-divisor-transform!))
(defun inverse-divisor-transform! (vector &optional (op- #'-) (handle-zero t))
  "Does the inverse transform of DIVISOR-TRANSFORM! in O(nloglog(n))
time. Ignores VECTOR[0] when HANDLE-ZERO is NIL."
  (declare (vector vector))
  (let* ((n (length vector))
         (sieve (make-array n :element-type 'bit :initial-element 1)))
    (loop for p from 2 below n
          when (= 1 (sbit sieve p))
          do (loop for k from (- (ceiling n p) 1) downto 1
                   for pmult of-type fixnum = (* k p)
                   do (setf (sbit sieve pmult) 0)
                      (setf (aref vector pmult)
                            (funcall op- (aref vector pmult) (aref vector k)))))
    (when handle-zero
      (loop for i from 1 below n
            do (setf (aref vector 0)
                     (funcall op- (aref vector 0) (aref vector i)))))
    vector))

(declaim (inline multiple-transform!))
(defun multiple-transform! (vector &optional (op+ #'+) (handle-zero t))
  "Sets each VECTOR[i] to the sum of VECTOR[m] for all the multiples m of in
O(nloglog(n)) time. (To be precise, all the multiples smaller than the length of
VECTOR.) Ignores VECTOR[0] when HANDLE-ZERO is NIL."
  (declare (vector vector))
  (let* ((n (length vector))
         (sieve (make-array n :element-type 'bit :initial-element 1)))
    (loop for p from 2 below n
          when (= 1 (sbit sieve p))
          do (loop for k from (- (ceiling n p) 1) downto 1
                   for pmult of-type fixnum = (* k p)
                   do (setf (sbit sieve pmult) 0)
                      (setf (aref vector k)
                            (funcall op+ (aref vector k) (aref vector pmult)))))
    (when handle-zero
      (loop for i from 1 below n
            do (setf (aref vector i)
                     (funcall op+ (aref vector 0) (aref vector i)))))
    vector))

(declaim (inline inverse-multiple-transform!))
(defun inverse-multiple-transform! (vector &optional (op- #'-) (handle-zero t))
  "Does the inverse transform of MULTIPLE-TRANSFORM!. Ignores VECTOR[0] when
HANDLE-ZERO is NIL."
  (declare (vector vector))
  (let* ((n (length vector))
         (sieve (make-array n :element-type 'bit :initial-element 1)))
    (when handle-zero
      (loop for i from 1 below n
            do (setf (aref vector i)
                     (funcall op- (aref vector i) (aref vector 0)))))
    (loop for p from 2 below n
          when (= 1 (sbit sieve p))
          do (loop for k from 1 below (ceiling n p)
                   for pmult of-type fixnum = (* k p)
                   do (setf (sbit sieve pmult) 0)
                      (setf (aref vector k)
                            (funcall op- (aref vector k) (aref vector pmult)))))
    vector))

;;;
;;; (Slower) Zeta/Moebius transforms w.r.t. divisor or multiple in O(nlog(n)) time
;;;

;; (declaim (inline divisor-transform!))
;; (defun divisor-transform! (vector &optional (op+ #'+) (handle-zero t))
;;   "Sets each VECTOR[i] to the sum of VECTOR[d] for all the divisors d of i in
;; O(nlog(n)) time."
;;   (declare (vector vector))
;;   (let ((n (length vector)))
;;     (when handle-zero
;;       (loop for i from 1 below n
;;             do (setf (aref vector 0)
;;                      (funcall op+ (aref vector 0) (aref vector i)))))
;;     (loop for i from (- (ceiling n 2) 1) downto 1
;;           do (loop for j from (+ i i) below n by i
;;                    do (setf (aref vector j)
;;                             (funcall op+ (aref vector i) (aref vector j)))))
;;     vector))

;; (declaim (inline inverse-divisor-transform!))
;; (defun inverse-divisor-transform! (vector &optional (op- #'-) (handle-zero t))
;;   "Does the inverse transform of DIVISOR-TRANSFORM! in O(nlog(n)) time."
;;   (declare (vector vector))
;;   (let ((n (length vector)))
;;     (loop for i from 1 below (ceiling n 2)
;;           do (loop for j from (+ i i) below n by i
;;                    do (setf (aref vector j)
;;                             (funcall op- (aref vector j) (aref vector i)))))
;;     (when handle-zero
;;       (loop for i from 1 below n
;;             do (setf (aref vector 0)
;;                      (funcall op- (aref vector 0) (aref vector i)))))
;;     vector))


;; (declaim (inline multiple-transform!))
;; (defun multiple-transform! (vector &optional (op+ #'+) (handle-zero t))
;;   "Sets each VECTOR[i] to the sum of VECTOR[m] for all the multiples m of i in
;; O(nlog(n)) time. (To be precise, all the multiples smaller than the length of
;; VECTOR.)"
;;   (declare (vector vector))
;;   (let ((n (length vector)))
;;     (loop for i from 1 below (ceiling n 2)
;;           do (loop for j from (+ i i) below n by i
;;                    do (setf (aref vector i)
;;                             (funcall op+ (aref vector i) (aref vector j)))))
;;     (when handle-zero
;;       (loop for i from 1 below n
;;             do (setf (aref vector i)
;;                      (funcall op+ (aref vector 0) (aref vector i)))))
;;     vector))


;; (declaim (inline inverse-multiple-transform!))
;; (defun inverse-multiple-transform! (vector &optional (op- #'-) (handle-zero t))
;;   "Does the inverse transform of MULTIPLE-TRANSFORM! in O(nlog(n)) time."
;;   (declare (vector vector))
;;   (let ((n (length vector)))
;;     (when handle-zero
;;       (loop for i from 1 below n
;;             do (setf (aref vector i)
;;                      (funcall op- (aref vector i) (aref vector 0)))))
;;     (loop for i from (- (ceiling n 2) 1) downto 1
;;           do (loop for j from (+ i i) below n by i
;;                    do (setf (aref vector i)
;;                             (funcall op- (aref vector i) (aref vector j)))))
;;     vector))

(defpackage :cp/mod-power
  (:use :cl)
  (:export #:mod-power))
(in-package :cp/mod-power)

(declaim (inline mod-power))
(defun mod-power (base power modulus)
  "Returns BASE^POWER mod MODULUS. Note: 0^0 = 1.

BASE := integer
POWER, MODULUS := non-negative fixnum"
  (declare ((integer 0 #.most-positive-fixnum) modulus power)
           (integer base))
  (let ((base (mod base modulus))
        (res (mod 1 modulus)))
    (declare ((integer 0 #.most-positive-fixnum) base res))
    (loop while (> power 0)
          when (oddp power)
          do (setq res (mod (* res base) modulus))
          do (setq base (mod (* base base) modulus)
                   power (ash power -1)))
    res))


(defpackage :cp/enum-quotients
  (:use :cl)
  (:export #:enum-quotients))
(in-package :cp/enum-quotients)

(declaim (ftype (function * (values (array (integer 0 #.most-positive-fixnum) (*)) &optional))
                enum-quotients))
(defun enum-quotients (n)
  "Given a positive integer N, floor(N/k) takes at most O(sqrt(N)) values for k
in {1, ..., N}. ENUM-QUOTIENTS returns the ascending vector of minimal integers
k that take `new' values compared to floor(N/(k-1)). Note that this vector
contains 1 and N+1.

Tips: Let A be the returned vector of length M+1 and an index i in {0, ..., M}
be given; then A[i]A[j] <= N iff j < M-i."
  (declare ((integer 0 #.most-positive-fixnum) n))
  (let ((k 1)
        (result (make-array (* 2 (isqrt n))
                            :element-type '(integer 0 #.most-positive-fixnum)
                            :adjustable t
                            :fill-pointer 0)))
    (loop (vector-push-extend k result)
          (when (> k n)
            (return result))
          (setq k (+ 1 (floor n (floor n k)))))))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/enum-quotients :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/mod-power :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/zeta-integer :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/mod-operations :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (dotimes (_ tt)
      (let* ((n (read))
             (m (read))
             (l (read))
             (r (read))
             (dp (make-array (+ m 1) :element-type 'uint31 :initial-element 0))
             (quots (enum-quotients m)))
        (declare (uint31 n m l r))
        (dotimes (i (- (length quots) 1))
          (let* ((denom1 (aref quots i))
                 (denom2 (aref quots (+ i 1)))
                 (value (mod-power (floor m denom1) n +mod+)))
            (loop for j from denom1 below denom2
                  do (setf (aref dp j) value))))
        (inverse-multiple-transform! dp
                                     (lambda (x y)
                                       (declare (uint31 x y))
                                       (let ((tmp (- x y)))
                                         (if (< tmp 0)
                                             (+ tmp +mod+)
                                             tmp)))
                                     nil)
        (println (mod (loop for i from l to r
                            sum (aref dp i) of-type uint62)
                      +mod+))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/SEAGCD"))

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
