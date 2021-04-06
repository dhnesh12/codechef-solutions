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
;;; Sort multiple vectors
;;;

(defpackage :cp/parallel-sort
  (:use :cl)
  (:export #:parallel-sort!))
(in-package :cp/parallel-sort)

(declaim (inline %median3))
(defun %median3 (x y z order)
  (if (funcall order x y)
      (if (funcall order y z)
          y
          (if (funcall order z x)
              x
              z))
      (if (funcall order z y)
          y
          (if (funcall order x z)
              x
              z))))

(defun parallel-sort! (vector order &rest vectors)
  "Destructively sorts VECTOR by ORDER and applies the same permutation to all
the vectors in VECTORS.

- Not randomized; shuffle the inputs if necessary.
- The consequence is undefined when two or more identical vectors (w.r.t. EQ)
  are given."
  (declare (vector vector))
  (labels
      ((recur (left right)
         (when (< left right)
           (let* ((l left)
                  (r right)
                  (pivot (%median3 (aref vector l)
                                   (aref vector (ash (+ l r) -1))
                                   (aref vector r)
                                   order)))
             (declare ((integer 0 #.most-positive-fixnum) l r))
             (loop (loop while (funcall order (aref vector l) pivot)
                         do (incf l 1))
                   (loop while (funcall order pivot (aref vector r))
                         do (decf r 1))
                   (when (>= l r)
                     (return))
                   (rotatef (aref vector l) (aref vector r))
                   (dolist (v vectors)
                     (rotatef (aref v l) (aref v r)))
                   (incf l 1)
                   (decf r 1))
             (recur left (- l 1))
             (recur (+ r 1) right)))))
    (recur 0 (- (length vector) 1))
    vector))

#+sbcl
(eval-when (:compile-toplevel :load-toplevel :execute)
  (locally (declare (sb-ext:muffle-conditions warning))
    (sb-c:define-source-transform parallel-sort! (vector order &rest vectors)
      (let ((vec (gensym))
            (vecs (loop for _ in vectors collect (gensym))))
        `(let ((,vec ,vector)
               ,@(loop for v in vectors
                       for sym in vecs
                       collect `(,sym ,v)))
           (labels
               ((recur (left right)
                  (when (< left right)
                    (let* ((l left)
                           (r right)
                           (pivot (%median3 (aref ,vec l)
                                            (aref ,vec (ash (+ l r) -1))
                                            (aref ,vec r)
                                            ,order)))
                      (declare ((integer 0 #.most-positive-fixnum) l r))
                      (loop (loop while (funcall ,order (aref ,vec l) pivot)
                                  do (incf l 1))
                            (loop while (funcall ,order pivot (aref ,vec r))
                                  do (decf r 1))
                            (when (>= l r)
                              (return))
                            (rotatef (aref ,vec l) (aref ,vec r))
                            ,@(loop for sym in vecs
                                    collect `(rotatef (aref ,sym l) (aref ,sym r)))
                            (incf l 1)
                            (decf r 1))
                      (recur left (- l 1))
                      (recur (+ r 1) right)))))
             (recur 0 (- (length ,vec) 1))
             ,vec))))))

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
  (use-package :cp/parallel-sort :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (dotimes (_ tt)
      (let* ((n (read))
             (as (make-array n :element-type 'uint31 :initial-element 0))
             (bs (make-array n :element-type 'uint31 :initial-element 0))
             (dp (make-array (+ n 1)
                             :element-type 'fixnum
                             :initial-element most-negative-fixnum)))
        (declare (uint31 n))
        (dotimes (i n)
          (setf (aref as i) (read-fixnum)))
        (dotimes (i n)
          (setf (aref bs i) (read-fixnum)))
        (parallel-sort! bs #'> as)
        (setf (aref dp 0) 0)
        (dotimes (x n)
          (let ((a (aref as x))
                (b (aref bs x)))
            (loop for y from (- n 1) downto 0
                  do (maxf (aref dp (+ y 1))
                           (+ (aref dp y) (+ (* y b) a))))))
        (write-string
         (with-output-to-string (*standard-output* nil :element-type 'base-char)
           (loop for y from 1 to n
                 unless (= y 1)
                 do (write-char #\ )
                 do (princ (aref dp y))
                 finally (terpri))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/REIGN2"))

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
