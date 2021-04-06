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
;;; Disjoint set (union by size & path compression)
;;;

(defpackage :cp/disjoint-set
  (:use :cl)
  (:export #:disjoint-set #:make-disjoint-set #:ds-data
           #:ds-root #:ds-unite! #:ds-connected-p #:ds-size #:ds-clear))
(in-package :cp/disjoint-set)

(defstruct (disjoint-set
            (:constructor make-disjoint-set
                (size &aux (data (make-array size :element-type 'fixnum :initial-element -1))))
            (:conc-name ds-)
            (:predicate nil)
            (:copier nil))
  (data nil :type (simple-array fixnum (*))))

(declaim (inline ds-root))
(defun ds-root (disjoint-set x)
  "Returns the root of X."
  (declare ((mod #.array-total-size-limit) x))
  (let ((data (ds-data disjoint-set)))
    (labels ((recur (x)
               (if (< (aref data x) 0)
                   x
                   (setf (aref data x)
                         (recur (aref data x))))))
      (recur x))))

(declaim (inline ds-unite!))
(defun ds-unite! (disjoint-set x1 x2)
  "Destructively unites X1 and X2 and returns true iff X1 and X2 become
connected for the first time."
  (let ((root1 (ds-root disjoint-set x1))
        (root2 (ds-root disjoint-set x2)))
    (unless (= root1 root2)
      (let ((data (ds-data disjoint-set)))
        ;; NOTE: If you want X1 to always be root, just delete this form. (Time
        ;; complexity becomes worse, however.)
        (when (> (aref data root1) (aref data root2))
          (rotatef root1 root2))
        (incf (aref data root1) (aref data root2))
        (setf (aref data root2) root1)))))

(declaim (inline ds-connected-p))
(defun ds-connected-p (disjoint-set x1 x2)
  "Returns true iff X1 and X2 have the same root."
  (= (ds-root disjoint-set x1) (ds-root disjoint-set x2)))

(declaim (inline ds-size))
(defun ds-size (disjoint-set x)
  "Returns the size of the connected component to which X belongs."
  (- (aref (ds-data disjoint-set)
           (ds-root disjoint-set x))))

(declaim (inline ds-clear))
(defun ds-clear (disjoint-set)
  "Deletes all connections."
  (fill (ds-data disjoint-set) -1)
  disjoint-set)

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

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/modify-macro :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/disjoint-set :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defconstant +nan+ #xff)
(defconstant +inf+ #x7fffffff)

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read))
         (mat (make-array '(200 200) :element-type 'uint8)))
    (dotimes (_ tt)
      (fill (array-storage-vector mat) +nan+)
      (let* ((m (read))
             (k (read))
             (n (read))
             (dp (make-array m :element-type 'uint31 :initial-element +inf+))
             (dset (make-disjoint-set m))
             (as (make-array n :element-type 'uint8 :initial-element 0)))
        (declare (uint31 m k n)
                 ((simple-array uint31 (*)) dp))
        (dotimes (_ k)
          (let ((x (- (read-fixnum) 1))
                (y (- (read-fixnum) 1)))
            (ds-unite! dset x y)))
        (dotimes (i n)
          (setf (aref as i) (- (read-fixnum) 1)))
        (dotimes (i m)
          (dotimes (j m)
            (when (ds-connected-p dset i j)
              (setf (aref mat i j) j))))
        (dotimes (i m)
          (loop for j from (- m 2) downto 0
                do (minf (aref mat i j) (aref mat i (+ j 1)))))
        (setf (aref dp 0) 0)
        (dotimes (x n)
          (let ((a (aref as x)))
            (loop for y from (- m 1) downto 0
                  for value = (aref dp y)
                  do (setf (aref dp y) +inf+)
                  unless (= +inf+ value)
                  do (when (<= y a)
                       (minf (aref dp a) value))
                     (let ((new-y (aref mat a y)))
                       (unless (= +nan+ new-y)
                         (minf (aref dp new-y) (+ value 1)))))))
        (let ((res (loop for y below m
                         minimize (aref dp y))))
          (println (if (= res +inf+)
                       -1
                       res)))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/CARLOS"))

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
