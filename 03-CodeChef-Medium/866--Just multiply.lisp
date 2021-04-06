#-swank
(unless (member :child-sbcl *features*)
  (quit
   :recklessly-p t
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
(defpackage :cp/mod-power
  (:use :cl)
  (:export #:mod-power))
(in-package :cp/mod-power)

(declaim (inline mod-power))
(defun mod-power (base power modulus)
  "Returns BASE^POWER mod MODULUS. Note: 0^0 = 1.

BASE := integer
POWER, MODULUS := non-negative fixnum"
  (declare ((integer 0 #.most-positive-fixnum) modulus)
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


(defpackage :cp/parse-bignum
  (:use :cl)
  (:export #:parse-bignum))
(in-package :cp/parse-bignum)

(defun parse-bignum (simple-base-string &key (start 0) end)
  "Is a variant of SBCL(x64)'s PARSE-INTEGER. Can also parse fixnum but is
optimized to big integer."
  (declare (optimize (speed 3)))
  (sb-c::with-array-data ((string simple-base-string :offset-var offset)
                          (start start)
                          (end end)
                          :check-fill-pointer t)
    (let ((index (do ((i start (1+ i)))
                     ((= i end)
                      (return-from parse-bignum (values nil end)))
                   (declare (fixnum i))
                   (unless (char= #\Space (schar string i))
                     (return i))))
          (minusp nil)
          (result 0)
          (mid-result 0)
          (index-mod18 0))
      (declare (fixnum index mid-result)
               ((integer 0 19) index-mod18)
               (integer result))
      (let ((char (schar string index)))
        (cond ((char= char #\-)
               (setq minusp t)
               (incf index))
              ((char= char #\+)
               (incf index))))
      (loop
        (when (= index-mod18 18)
          (setq result (+ mid-result (* result #.(expt 10 18))))
          (setq mid-result 0)
          (setq index-mod18 0))
        (when (= index end) (return nil))
        (let* ((char (schar string index))
               (weight (- (char-code char) 48)))
          (if (<= 0 weight 9)
              (setq mid-result
                    (+ weight (* 10 (the (integer 0 #.(expt 10 17)) mid-result))))
              (return nil)))
        (incf index)
        (incf index-mod18))
      (setq result (+ mid-result (* result (expt 10 index-mod18))))
      (values
       (if minusp (- result) result)
       (- index offset)))))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/parse-bignum :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/mod-power :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (dotimes (_ tt)
      (let ((m (read))
            (s (concatenate 'simple-base-string (read-line) "*1"))
            (res 1))
        (declare (uint62 m res))
        (labels ((calc (l r)
                   (let* ((mid (search "**" s :start2 l :end2 r))
                          (x (mod (parse-bignum s :start l :end mid) m))
                          (y (parse-bignum s :start (+ mid 2) :end r)))
                     (declare (uint62 x))
                     (mod-power x y m))))
          (let ((prev 0))
            (loop for i from 1 below (- (length s) 1)
                  when (and (digit-char-p (aref s (- i 1)))
                            (char= #\* (aref s i))
                            (digit-char-p (aref s (+ i 1))))
                  do (dbg prev i)
                     (setq res (mod (* res (calc prev i)) m))
                     (setq prev (+ i 1)))))
        (println res)))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/LCH15JEF"))

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
