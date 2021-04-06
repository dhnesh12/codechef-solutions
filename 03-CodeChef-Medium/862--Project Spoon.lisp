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

;;;
;;; Compute binomial coefficient by direct bignum arithmetic
;;;

(defpackage :cp/binomial-coefficient
  (:use :cl)
  (:export #:factorial #:binomial-coefficient))
(in-package :cp/binomial-coefficient)

;; dead copy of alexandria::%multiply-range
(declaim (inline %multiply-range))
(defun %multiply-range (i j)
  (labels ((bisect (j k)
             (declare (type (integer 1 #.most-positive-fixnum) j k)
                      (values integer))
             (if (< (- k j) 8)
                 (multiply-range j k)
                 (let ((middle (+ j (truncate (- k j) 2))))
                   (* (bisect j middle)
                      (bisect (+ middle 1) k)))))
           (multiply-range (j k)
             (declare (type (integer 1 #.most-positive-fixnum) j k))
             (do ((f k (* f m))
                  (m (1- k) (1- m)))
                 ((< m j) f)
               (declare (type (integer 0 (#.most-positive-fixnum)) m)
                        (type unsigned-byte f)))))
    (bisect i j)))

(declaim (inline factorial))
(defun factorial (n)
  (cond ((< n 0) 0)
        ((zerop n) 1)
        (t (%multiply-range 1 n))))

(defun binomial-coefficient (n k)
  (declare (fixnum n k))
  (cond ((or (< n 0) (< k 0) (< n k)) 0)
        ((or (zerop k) (= n k)) 1)
        (t (let ((n-k (- n k)))
             (when (< k n-k)
               (rotatef k n-k))
             (if (= 1 n-k)
                 n
                 (floor (%multiply-range (+ k 1) n)
                        (%multiply-range 1 n-k)))))))

(defpackage :cp/bisect
  (:use :cl)
  (:export #:bisect-left #:bisect-right))
(in-package :cp/bisect)

(declaim (inline bisect-left))
(defun bisect-left (target value &key (start 0) end (order #'<) (key #'identity))
  "TARGET := vector | function (taking an integer argument)
ORDER := strict order

Analogue of lower_bound() of C++ or bisect_left() of Python: Returns the
smallest index (or input) i that fulfills TARGET[i] >= VALUE, where '>=' is the
complement of ORDER. In other words, this function returns the leftmost index at
which VALUE can be inserted with keeping the order. Therefore, TARGET must be
monotonically non-decreasing with respect to ORDER.

- This function returns END if VALUE exceeds TARGET[END-1]. 
- The range [START, END) is half-open.
- END must be explicitly specified if TARGET is function.
- KEY is applied to each element of TARGET before comparison."
  (declare (integer start)
           ((or null integer) end))
  (macrolet
      ((frob (accessor &optional declaration)
         `(labels
              ((%bisect-left (ng ok)
                 ;; TARGET[OK] >= VALUE always holds (assuming
                 ;; TARGET[END] = +infinity)
                 ,@(when declaration (list declaration))
                 (if (<= (- ok ng) 1)
                     ok
                     (let ((mid (ash (+ ng ok) -1)))
                       (if (funcall order (funcall key (,accessor target mid)) value)
                           (%bisect-left mid ok)
                           (%bisect-left ng mid))))))
            (assert (<= start end))
            (%bisect-left (- start 1) end))))
    (etypecase target
      (vector
       (let ((end (or end (length target))))
         (frob aref (declare ((integer -1 (#.most-positive-fixnum)) ng ok)))))
      (function
       (assert end () "Requires END argument if TARGET is a function.")
       (frob funcall)))))

(declaim (inline bisect-right))
(defun bisect-right (target value &key (start 0) end (order #'<) (key #'identity))
  "TARGET := vector | function (taking an integer argument)
ORDER := strict order

Analogue of upper_bound() of C++ or bisect_right() of Python: Returns the
smallest index (or input) i that fulfills TARGET[i] > VALUE. In other words,
this function returns the rightmost index at which VALUE can be inserted with
keeping the order. Therefore, TARGET must be monotonically non-decreasing with
respect to ORDER.

- This function returns END if VALUE >= TARGET[END-1].
- The range [START, END) is half-open.
- END must be explicitly specified if TARGET is function.
- KEY is applied to each element of TARGET before comparison."
  (declare (integer start)
           ((or null integer) end))
  (macrolet
      ((frob (accessor &optional declaration)
         `(labels
              ((%bisect-right (ng ok)
                 ;; TARGET[OK] > VALUE always holds (assuming
                 ;; TARGET[END] = +infinity)
                 ,@(when declaration (list declaration))
                 (if (<= (- ok ng) 1)
                     ok
                     (let ((mid (ash (+ ng ok) -1)))
                       (if (funcall order value (funcall key (,accessor target mid)))
                           (%bisect-right ng mid)
                           (%bisect-right mid ok))))))
            (assert (<= start end))
            (%bisect-right (- start 1) end))))
    (etypecase target
      (vector
       (let ((end (or end (length target))))
         (frob aref (declare ((integer -1 (#.array-total-size-limit)) ng ok)))))
      (function
       (assert end () "Requires END argument if TARGET is a function.")
       (frob funcall)))))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/bisect :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/binomial-coefficient :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read))
         (ns (make-array 67 :element-type 'uint62 :initial-element 0)))
    (declare (uint31 tt))
    (dotimes (k (length ns))
      (setf (aref ns k)
            (min most-positive-fixnum
                 (binomial-coefficient k (floor k 2)))))
    #>ns
    (write-string
     (with-output-to-string (*standard-output* nil :element-type 'base-char)
       (dotimes (_ tt)
         (let ((n (read-fixnum)))
           (println (bisect-left ns n))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/SPOONS"))

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
