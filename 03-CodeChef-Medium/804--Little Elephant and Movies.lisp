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

(defpackage :cp/binomial-coefficient-mod
  (:use :cl)
  (:export #:binom #:perm #:multinomial #:stirling2 #:catalan #:multichoose
           #:+binom-mod+ #:*fact* #:*fact-inv* #:*inv*)
  (:documentation
   "Provides tables of factorials, inverses, inverses ot factorials etc.
modulo prime.

build: O(n)
query: O(1)
"))
(in-package :cp/binomial-coefficient-mod)

;; TODO: non-global handling

(defconstant +binom-size+ 500)
(defconstant +binom-mod+ (if (boundp 'cl-user::+mod+)
                             (symbol-value 'cl-user::+mod+)
                             #.(+ (expt 10 9) 7)))

(declaim ((simple-array (unsigned-byte 31) (*)) *fact* *fact-inv* *inv*))
(sb-ext:define-load-time-global *fact*
  (make-array +binom-size+ :element-type '(unsigned-byte 31))
  "table of factorials")
(sb-ext:define-load-time-global *fact-inv*
  (make-array +binom-size+ :element-type '(unsigned-byte 31))
  "table of inverses of factorials")
(sb-ext:define-load-time-global *inv*
  (make-array +binom-size+ :element-type '(unsigned-byte 31))
  "table of inverses of non-negative integers")

(defun initialize-binom ()
  (declare (optimize (speed 3) (safety 0)))
  (setf (aref *fact* 0) 1
        (aref *fact* 1) 1
        (aref *fact-inv* 0) 1
        (aref *fact-inv* 1) 1
        (aref *inv* 1) 1)
  (loop for i from 2 below +binom-size+
        do (setf (aref *fact* i) (mod (* i (aref *fact* (- i 1))) +binom-mod+)
                 (aref *inv* i) (- +binom-mod+
                                   (mod (* (aref *inv* (rem +binom-mod+ i))
                                           (floor +binom-mod+ i))
                                        +binom-mod+))
                 (aref *fact-inv* i) (mod (* (aref *inv* i)
                                             (aref *fact-inv* (- i 1)))
                                          +binom-mod+))))

(initialize-binom)

(declaim (inline binom))
(defun binom (n k)
  "Returns nCk, the number of k-combinations of n things without repetition."
  (if (or (< n k) (< n 0) (< k 0))
      0
      (mod (* (aref *fact* n)
              (mod (* (aref *fact-inv* k) (aref *fact-inv* (- n k))) +binom-mod+))
           +binom-mod+)))

(declaim (inline perm))
(defun perm (n k)
  "Returns nPk, the number of k-permutations of n things without repetition."
  (if (or (< n k) (< n 0) (< k 0))
      0
      (mod (* (aref *fact* n) (aref *fact-inv* (- n k))) +binom-mod+)))

(declaim (inline multichoose))
(defun multichoose (n k)
  "Returns the number of k-combinations of n things with repetition."
  (binom (+ n k -1) k))

(declaim (inline multinomial))
(defun multinomial (&rest ks)
  "Returns the multinomial coefficient K!/k_1!k_2!...k_n! for K = k_1 + k_2 +
... + k_n. K must be equal to or smaller than
MOST-POSITIVE-FIXNUM. (multinomial) returns 1."
  (let ((sum 0)
        (result 1))
    (declare ((integer 0 #.most-positive-fixnum) result sum))
    (dolist (k ks)
      (incf sum k)
      (setq result
            (mod (* result (aref *fact-inv* k)) +binom-mod+)))
    (mod (* result (aref *fact* sum)) +binom-mod+)))

(define-compiler-macro multinomial (&rest args)
  (case (length args)
    ((0 1) (mod 1 +binom-mod+))
    (otherwise
     `(mod (* ,(reduce (lambda (x y) `(mod (* ,x ,y) +binom-mod+))
                       args
                       :key (lambda (x) `(aref *fact-inv* ,x)))
              (aref *fact* (+ ,@args)))
           +binom-mod+))))

(declaim (inline stirling2))
(defun stirling2 (n k)
  "Returns the stirling number of the second kind S2(n, k). Time complexity is
O(klog(n))."
  (declare ((integer 0 #.most-positive-fixnum) n k))
  (labels ((mod-power (base exp)
             (declare ((integer 0 #.most-positive-fixnum) base exp))
             (loop with res of-type (integer 0 #.most-positive-fixnum) = 1
                   while (> exp 0)
                   when (oddp exp)
                   do (setq res (mod (* res base) +binom-mod+))
                   do (setq base (mod (* base base) +binom-mod+)
                            exp (ash exp -1))
                   finally (return res))))
    (loop with result of-type fixnum = 0
          for i from 0 to k
          for delta = (mod (* (binom k i) (mod-power i n)) +binom-mod+)
          when (evenp (- k i))
          do (incf result delta)
             (when (>= result +binom-mod+)
               (decf result +binom-mod+))
          else
          do (decf result delta)
             (when (< result 0)
               (incf result +binom-mod+))
          finally (return (mod (* result (aref *fact-inv* k)) +binom-mod+)))))

(declaim (inline catalan))
(defun catalan (n)
  "Returns the N-th Catalan number."
  (declare ((integer 0 #.most-positive-fixnum) n))
  (mod (* (aref *fact* (* 2 n))
          (mod (* (aref *fact-inv* (+ n 1))
                  (aref *fact-inv* n))
               +binom-mod+))
       +binom-mod+))

(defpackage :cp/run-length
  (:use :cl)
  (:export #:map-run-length))
(in-package :cp/run-length)

(deftype fixnum+ () '(integer 1 #.most-positive-fixnum))

(declaim (inline map-run-length))
(defun map-run-length (function seq &key (test #'eql))
  "Applies FUNCTION to each equal successive element of SEQ. FUNCTION must take
two arguments: the first one receives an element in SEQ and the second one
receives the number of the successive elements equal to the first one.

Example:
\(map-run-length (lambda (x c) (format t \"~D ~D~%\" x c)) #(1 1 1 2 2 1 3))
1 3
2 2
1 1
3 1
"
  (declare (sequence seq)
           ((or function symbol) test function))
  (unless (sb-sequence:emptyp seq)
    (let ((prev (elt seq 0))
          (start 0)
          (pos 0))
      (declare ((integer 0 #.most-positive-fixnum) start pos))
      (sb-sequence:dosequence (elm seq)
        (unless (or (zerop pos) (funcall test prev elm))
          (funcall function prev (the fixnum+ (- pos start)))
          (setq prev elm
                start pos))
        (incf pos))
      (funcall function prev (the fixnum+ (- pos start)))
      nil)))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/run-length :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/binomial-coefficient-mod :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/mod-operations :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read))
         (dp (make-array '(201 201) :element-type 'uint31 :initial-element 0)))
    (dotimes (_ tt)
      (fill (array-storage-vector dp) 0)
      (let* ((n (read))
             (k (read))
             (ps (make-array n :element-type 'uint8 :initial-element 0))
             (rles (make-array n :element-type 'uint8 :fill-pointer 0)))
        (declare (uint8 n k))
        (dotimes (i n)
          (setf (aref ps i) (read)))
        (setq ps (sort ps #'<))
        (map-run-length (lambda (p count)
                          (declare (ignore p))
                          (assert (vector-push count rles)))
                        ps)
        (let* ((len (length rles))
               (cum (make-array (+ len 1) :element-type 'uint31 :initial-element 0)))
          (loop for i from (- len 1) downto 0
                do (setf (aref cum i)
                         (+ (aref cum (+ i 1)) (aref rles i))))
          (setf (aref dp len 0) 1)
          (loop for x from (- len 1) downto 0
                for count = (aref rles x)
                for sum = (aref cum x)
                do (dotimes (y (+ k 1))
                     (setf (aref dp x y)
                           (mod+ (if (zerop y)
                                     0
                                     (mod* (multichoose (+ 1 (- sum count)) (- count 1))
                                           (aref dp (+ x 1) (- y 1))))
                                 (mod* (multichoose (- sum count) count)
                                       (aref dp (+ x 1) y))))))
          (let ((res 0))
            (declare (uint31 res))
            (dotimes (y (+ k 1))
              (incfmod res (aref dp 0 y)))
            (sb-int:dovector (count rles)
              (mulfmod res (aref *fact* count)))
            (println res)))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/LEMOVIE"))

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
