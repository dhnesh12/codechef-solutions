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

(defpackage :cp/quickselect
  (:use :cl)
  (:export #:quickselect!)
  (:documentation
   "Provides selection algorithm, an algorithm for finding k-th smallest (or
largest) number in a vector. Time complexity is expected O(Nlog(N))."))
(in-package :cp/quickselect)

(declaim (inline %hoare-partition!))
(defun %hoare-partition! (vector l r pivot-idx order)
  "Destructively rearranges VECTOR[L, R] and returns an index i: All the
elements smaller than VECTOR[PIVOT-IDX] are moved to the front of i and those
larger behind i. Note that this function deals with the **closed** interval [L,
R]."
  (declare (vector vector)
           ((mod #.array-total-size-limit) l r))
  (rotatef (aref vector pivot-idx)
           (aref vector l))
  (let ((pivot (aref vector l))
        (i l)
        (j (+ r 1)))
    (declare (fixnum i j))
    (loop
      (loop do (incf i)
            while (and (<= i r)
                       (funcall order (aref vector i) pivot)))
      (loop do (decf j)
            while (funcall order pivot (aref vector j)))
      (when (>= i j)
        (rotatef (aref vector l) (aref vector j))
        (return j))
      (rotatef (aref vector i) (aref vector j)))))

;; FIXME: When we use Lomuto partition scheme for QUICKSELECT!, it takes O(n^2)
;; time for a vector consisting of a single value like #(1 1 1 1 1).
(defun %lomuto-partition! (vector l r pivot-idx order)
  (rotatef (aref vector r) (aref vector pivot-idx))
  (let ((pivot (aref vector r))
        (base l))
    (loop for j from l below r
          unless (funcall order pivot (aref vector j))
          do (rotatef (aref vector base) (aref vector j))
             (incf base))
    (rotatef (aref vector base) (aref vector r))
    base))

(declaim (inline quickselect!))
(defun quickselect! (vector order i &optional (start 0) end)
  "Returns the (0-based) i-th smallest element of VECTOR (if order is #'<, for
example). Destructively modifies VECTOR.

ORDER := strict order"
  (declare (vector vector)
           ((mod #.array-total-size-limit) i start))
  (assert (< i (length vector)))
  (labels ((recur (l r i)
             (declare ((mod #.array-total-size-limit) l r i))
             (when (= l r)
               (return-from recur (aref vector r)))
             (let* ((pivot-idx (+ l (random (+ 1 (- r l)))))
                    (mid (%hoare-partition! vector l r pivot-idx order))
                    (delta (- mid l)))
               (declare ((mod #.array-total-size-limit) pivot-idx))
               (cond ((= i delta)
                      (return-from recur (aref vector mid)))
                     ((< i delta)
                      (recur l (- mid 1) i))
                     (t
                      (recur (+ mid 1) r (- i delta 1)))))))
    (recur start (or end (- (length vector) 1)) i)))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/quickselect :cl-user))
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
      (let* ((m (read))
             (n (min m (read)))
             (k (read))
             (ts (make-array m :element-type 'uint8 :initial-element 0))
             (ps (make-array m :element-type 'uint8 :initial-element 0))
             (tmp (make-array m :element-type 'fixnum :initial-element 0)))
        (declare ((simple-array fixnum (*)) tmp)
                 (uint31 m n k))
        (dotimes (i m)
          (setf (aref ts i) (read-fixnum)))
        (dotimes (i m)
          (setf (aref ps i) (read-fixnum)))
        (sb-int:named-let bisect ((ng 0) (ok (ceiling (* 100 k) n)))
          (declare (uint31 ng ok))
          (if (<= (- ok ng) 1)
              (println ok)
              (let ((mid (ash (+ ng ok) -1)))
                (if (loop for i below m
                          for tt = (aref ts i)
                          for p = (aref ps i)
                          do (setf (aref tmp i)
                                   (if (>= mid tt)
                                       (+ 1 (floor (- mid tt) p))
                                       0))
                          finally
                             (let ((min (quickselect! tmp #'> (- n 1)))
                                   (count 0)
                                   (sum 0))
                               (declare (uint31 count min)
                                        (fixnum sum))
                               (loop for x across tmp
                                     when (> x min)
                                     do (incf sum x)
                                        (incf count))
                               (incf sum (* (- n count) min))
                               (return (>= sum k))))
                    (bisect ng mid)
                    (bisect mid ok)))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/SQUIRREL"))

#+swank
(defun gen-dat ()
  (uiop:with-output-file (out *dat-pathname* :if-exists :supersede)
    (format out "20~%")
    (dotimes (_ 20)
      (let ((m 10000)
            (n 10000)
            (k (+ 1 (random 10000000))))
        (format out "~D ~D ~D~%" m n k)
        (dotimes (_ m)
          (println (+ 1 (random 100)) out))
        (dotimes (_ m)
          (println (+ 1 (random 100)) out))))))

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
