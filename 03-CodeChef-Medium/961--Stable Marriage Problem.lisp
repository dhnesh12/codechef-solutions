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
#+swank (set-dispatch-macro-character #\# #\> #'cl-debug-print:debug-print-reader)

(macrolet ((def (b)
             `(progn (deftype ,(intern (format nil "UINT~A" b)) () '(unsigned-byte ,b))
                     (deftype ,(intern (format nil "INT~A" b)) () '(signed-byte ,b))))
           (define-int-types (&rest bits) `(progn ,@(mapcar (lambda (b) `(def ,b)) bits))))
  (define-int-types 2 4 7 8 15 16 31 32 62 63 64))

(defconstant +mod+ 1000000007)

(defmacro dbg (&rest forms)
  #+swank (if (= (length forms) 1)
              `(format *error-output* "~A => ~A~%" ',(car forms) ,(car forms))
              `(format *error-output* "~A => ~A~%" ',forms `(,,@forms)))
  #-swank (declare (ignore forms)))

(declaim (inline println))
(defun println (obj &optional (stream *standard-output*))
  (let ((*read-default-float-format*
          (if (typep obj 'double-float) 'double-float *read-default-float-format*)))
    (prog1 (princ obj stream) (terpri stream))))

;; BEGIN_INSERTED_CONTENTS
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
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (dotimes (_ tt)
      (let* ((n (read))
             (fm-ords (make-array (list n n) :element-type 'uint31 :initial-element 0))
             (m-fs (make-array (list n n) :element-type 'uint31 :initial-element 0))
             (fm-state (make-array n :element-type 'int32 :initial-element -1))
             (mposes (make-array n :element-type 'uint31 :initial-element 0))
             (mcurrent 0)
             mout)
        (declare (uint31 n mcurrent))
        (dotimes (i n)
          (let ((i (- (read-fixnum) 1)))
            (dotimes (ord n)
              (let ((j (- (read-fixnum) 1)))
                (setf (aref fm-ords i j) ord)))))
        (dotimes (i n)
          (let ((i (- (read-fixnum) 1)))
            (dotimes (ord n)
              (let ((j (- (read-fixnum) 1)))
                (setf (aref m-fs i ord) j)))))
        (loop for m = (or mout (prog1 mcurrent (incf mcurrent)))
              until (= m n)
              do (loop (let* ((mpos (aref mposes m))
                              (f (aref m-fs m mpos))
                              (prev-m (aref fm-state f)))
                         (cond ((= -1 prev-m)
                                (setf (aref fm-state f) m)
                                (setq mout nil)
                                (return))
                               ((< (aref fm-ords f m)
                                   (aref fm-ords f prev-m))
                                (setf (aref fm-state f) m)
                                (incf (aref mposes prev-m))
                                (setq mout prev-m)
                                (return)))
                         (incf (aref mposes m)))))
        (write-string
         (with-output-to-string (*standard-output* nil :element-type 'base-char)
           (dotimes (f n)
             (format t "~D ~D~%"
                     (+ 1 (aref fm-state f))
                     (+ 1 f)))))))))

#-swank (main)

;;;
;;; Test and benchmark
;;;

#+swank
(progn
  (defparameter *lisp-file-pathname* (uiop:current-lisp-file-pathname))
  (setq *default-pathname-defaults* (uiop:pathname-directory-pathname *lisp-file-pathname*))
  (uiop:chdir *default-pathname-defaults*)
  (defparameter *dat-pathname* (uiop:merge-pathnames* "test.dat" *lisp-file-pathname*))
  (defparameter *problem-url* "https://www.codechef.com/problems/STABLEMP"))

#+swank
(defun gen-dat ()
  (uiop:with-output-file (out *dat-pathname* :if-exists :supersede)
    (format out "")))

#+swank
(defun bench (&optional (out (make-broadcast-stream)))
  (time (run *dat-pathname* out)))

#+(and sbcl (not swank))
(eval-when (:compile-toplevel)
  (when (or (> sb-c::*compiler-warning-count* 0)
            sb-c::*undefined-warnings*)
    (error "count: ~D, undefined warnings: ~A"
           sb-c::*compiler-warning-count*
           sb-c::*undefined-warnings*)))

;; To run: (5am:run! :sample)
#+swank
(5am:test :sample)
