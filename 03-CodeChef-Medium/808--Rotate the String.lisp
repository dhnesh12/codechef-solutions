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
(defpackage :cp/z-algorithm
  (:use :cl)
  (:export #:make-z-array)
  (:documentation "Provides Z-algorithm."))
(in-package :cp/z-algorithm)

(declaim (inline make-z-array))
(defun make-z-array (vector &key (test #'eql) end)
  "Returns a vector Z of the same length as VECTOR. Z[i] equals to the length of
the longest substring starting at i which coincides with a prefix of VECTOR."
  (declare (vector vector)
           ((or null (mod #.array-total-size-limit)) end))
  (let* ((end (or end (length vector)))
         (base 0)
         (z (make-array end :element-type '(unsigned-byte 31) :initial-element 0)))
    (declare ((mod #.array-total-size-limit) end base))
    (loop for i from 1 below end
          do (if (< (+ i (aref z (- i base)))
                    (+ base (aref z base)))
                 (setf (aref z i)
                       (aref z (- i base)))
                 (let ((delta (max 0 (- (+ base (aref z base)) i))))
                   (declare ((mod #.array-total-size-limit) delta))
                   (loop while (and (< (+ i delta) end)
                                    (funcall test
                                             (aref vector delta)
                                             (aref vector (+ i delta))))
                         do (incf delta))
                   (setf (aref z i) delta
                         base i))))
    (unless (zerop end)
      (setf (aref z 0) end))
    z))

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
  (use-package :cp/z-algorithm :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun test (s m p)
  (let ((n (length s))
        (orig-s s))
    (loop for i from 1
          do (if (oddp i)
                 (setq s (concatenate 'simple-base-string
                                      (subseq s (- n m))
                                      (subseq s 0 (- n m))))
                 (setq s (concatenate 'simple-base-string
                                      (subseq s (- n p))
                                      (subseq s 0 (- n p)))))
             #>s
             (when (string= orig-s s)
               (return-from test i)))))

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read))
         (s (make-string 1000000 :element-type 'base-char :initial-element #\Nul)))
    (dotimes (_ tt)
      (let ((end 0))
        (declare (uint31 end))
        (loop (let ((c (read-schar)))
                (when (char= c #\Newline)
                  (return))
                (setf (aref s end) c)
                (incf end)))
        (loop for i from end below (* end 2)
              do (setf (aref s i) (aref s (- i end))))
        (let ((m (read))
              (p (read))
              (z (make-z-array s :end (* 2 end) :test #'char=))
              (pos 0))
          (declare (uint31 m p)
                   (int32 pos))
          (loop for turn of-type uint31 from 0
                when (and (/= turn 0)
                          (= (aref z pos) (- (* 2 end) pos)))
                do (println turn)
                   (return)
                when (evenp turn)
                do (decf pos m)
                else
                do (decf pos p)
                when (< pos 0)
                do (incf pos end)))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/ROTSTRNG"))

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
