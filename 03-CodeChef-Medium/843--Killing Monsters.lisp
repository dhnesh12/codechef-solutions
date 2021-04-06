#-swank
(unless (member :child-sbcl *features*)
  (quit
   :unix-status
   (process-exit-code
    (run-program *runtime-pathname*
                 `("--control-stack-size" "256MB"
                   "--dynamic-space-size" "2GB"
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

(defpackage :cp/zeta-transform
  (:use :cl)
  (:export #:zeta-subtransform! #:zeta-supertransform!
           #:moebius-subtransform! #:moebius-supertransform!)
  (:documentation "Provides Zeta/Moebius transforms w.r.t. subsets and
supersets."))
(in-package :cp/zeta-transform)

;; TODO: Should we integrate zeta- and moebius- into a function?

(declaim (inline zeta-subtransform!))
(defun zeta-subtransform! (vector &optional (plus #'+))
  "Does the fast zeta transform w.r.t. subsets. The length of VECTOR must be a
power of two."
  (declare (vector vector))
  (let* ((n (length vector))
         ;; cardinality of the underlying set
         (card (- (integer-length n) 1)))
    (assert (= 1 (logcount n)))
    (dotimes (i card)
      (let ((mask (ash 1 i)))
        (dotimes (j n)
          (unless (zerop (logand j mask))
            (setf (aref vector j)
                  (funcall plus
                           (aref vector j)
                           (aref vector (logxor j mask))))))))
    vector))

(declaim (inline zeta-supertransform!))
(defun zeta-supertransform! (vector &optional (plus #'+))
  "Does the fast zeta transform w.r.t. supersets. The length of VECTOR must be a
power of two."
  (declare (vector vector))
  (let* ((n (length vector))
         (card (- (integer-length n) 1)))
    (assert (= 1 (logcount n)))
    (dotimes (i card)
      (let ((mask (ash 1 i)))
        (dotimes (j n)
          (when (zerop (logand j mask))
            (setf (aref vector j)
                  (funcall plus
                           (aref vector j)
                           (aref vector (logior j mask))))))))
    vector))

(declaim (inline moebius-subtransform!))
(defun moebius-subtransform! (vector &optional (minus #'-))
  "Does the inverse of ZETA-SUBTRANSFORM! The length of VECTOR must be a power
of two."
  (declare (vector vector))
  (let* ((n (length vector))
         (card (- (integer-length n) 1)))
    (assert (= 1 (logcount n)))
    (dotimes (i card)
      (let ((mask (ash 1 i)))
        (dotimes (j n)
          (unless (zerop (logand j mask))
            (setf (aref vector j)
                  (funcall minus
                           (aref vector j)
                           (aref vector (logxor j mask))))))))
    vector))

(declaim (inline moebius-supertransform!))
(defun moebius-supertransform! (vector &optional (minus #'-))
  "Does the inverse of ZETA-SUPERTRANSFORM!. The length of VECTOR must be a
power of two."
  (declare (vector vector))
  (let* ((n (length vector))
         (card (- (integer-length n) 1)))
    (assert (= 1 (logcount n)))
    (dotimes (i card)
      (let ((mask (ash 1 i)))
        (dotimes (j n)
          (when (zerop (logand j mask))
            (setf (aref vector j)
                  (funcall minus
                           (aref vector j)
                           (aref vector (logior j mask))))))))
    vector))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/zeta-transform :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defconstant +bsize+ 3000)
(defconstant +mask+ (ldb (byte 17 0) -1))

(defun main ()
  (declare #.*opt*)
  (let* ((n (read))
         (hs (make-array n :element-type 'uint31 :initial-element 0)))
    (declare (uint31 n))
    (dotimes (i n)
      (setf (aref hs i) (read-fixnum)))
    (let* ((q (read))
           (buckets (make-array (ceiling q +bsize+) :element-type t))
           (xs (make-array q :element-type 'uint31 :initial-element 0))
           (ys (make-array q :element-type 'uint31 :initial-element 0))
           (dp (make-array (+ 1 +mask+) :element-type 'uint62 :initial-element 0))
           (cum (make-array (+ 1 q) :element-type 'uint31 :initial-element 0)))
      (declare (uint31 q))
      (dotimes (i q)
        (multiple-value-bind (quot rem) (floor i +bsize+)
          (when (zerop rem)
            (let ((dp (copy-seq dp)))
              (zeta-supertransform! dp)
              (setf (aref buckets quot) dp))))
        (let ((x (logand (read-fixnum) +mask+))
              (y (read-fixnum)))
          (setf (aref xs i) x
                (aref ys i) y)
          (incf (aref dp x) y)))
      ;; #>buckets
      (dotimes (k n)
        (let ((b 0)
              (h (aref hs k)))
          (declare (uint31 b))
          (loop (when (= b (length buckets))
                  (return))
                (let ((bucket (aref buckets b)))
                  (declare ((simple-array uint62 (*)) bucket))
                  (when (>= (aref bucket k) h)
                    (return)))
                (incf b))
          (decf b)
          (let ((damage (aref (aref buckets b) k))
                (j (* b +bsize+)))
            (declare (uint62 damage j))
            (loop (when (= j q)
                    (return))
                  (when (>= damage h)
                    (return))
                  (when (= k (logand (aref xs j) k))
                    (incf damage (aref ys j)))
                  (incf j))
            (if (< damage h)
                (incf (aref cum q))
                (incf (aref cum (- j 1)))))))
      (loop for j from (- q 1) downto 0
            do (incf (aref cum j) (aref cum (+ j 1))))
      (write-string
       (with-output-to-string (*standard-output* nil :element-type 'base-char)
         (loop for j from 1 to q
               do (println (aref cum j))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/MONSTER"))

#+swank
(defun gen-dat ()
  (uiop:with-output-file (out *dat-pathname* :if-exists :supersede)
    (let ((n (ash 1 17))
          (q (ash 1 18)))
      (format out "~D~%" n)
      (dotimes (_ n)
        (println (+ 1 (random #.(expt 10 9))) out))
      (println q out)
      (dotimes (_ q)
        (println (random #.(expt 10 9)) out)
        (println (random (+ 1 (random #.(expt 10 9)))) out)))))

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
