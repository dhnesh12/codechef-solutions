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
;;; Mo's algorithm
;;;

(defpackage :cp/mo
  (:use :cl)
  (:export #:mo-integer #:mo #:make-mo #:mo-get-current #:mo-get-previous
           #:mo-process2 #:mo-process4))
(in-package :cp/mo)

(deftype mo-integer () '(signed-byte 32))

(defstruct (mo (:constructor %make-mo
                   (lefts rights order width))
               (:conc-name %mo-)
               (:copier nil)
               (:predicate nil))
  (lefts nil :type (simple-array mo-integer (*)))
  (rights nil :type (simple-array mo-integer (*)))
  (order nil :type (simple-array (integer 0 #.most-positive-fixnum) (*)))
  (width 0 :type (integer 0 #.most-positive-fixnum))
  (index 0 :type (integer 0 #.most-positive-fixnum))
  (posl 0 :type mo-integer)
  (posr 0 :type mo-integer))

(defun make-mo (bucket-width lefts rights)
  "LEFTS := vector of indices of left-end of queries (inclusive)
RIGHTS := vector of indices of right-end of queries (exclusive)

BUCKET-WIDTH would be better set to N/sqrt(Q) where N is the width of the
universe and Q is the number of queries."
  (declare (optimize (speed 3))
           ((simple-array mo-integer (*)) lefts rights)
           ((mod #.array-total-size-limit) bucket-width)
           (inline sort))
  (let* ((q (length lefts))
         (order (make-array q :element-type '(integer 0 #.most-positive-fixnum))))
    (assert (= q (length rights)))
    (dotimes (i q) (setf (aref order i) i))
    (setf order (sort order
                      (lambda (x y)
                        (if (= (floor (aref lefts x) bucket-width)
                               (floor (aref lefts y) bucket-width))
                            ;; Even-number [Odd-number] block is in ascending
                            ;; [descending] order w.r.t. the right end.
                            (if (evenp (floor (aref lefts x) bucket-width))
                                (< (aref rights x) (aref rights y))
                                (> (aref rights x) (aref rights y)))
                            (< (aref lefts x) (aref lefts y))))))
    (%make-mo lefts rights order bucket-width)))

(declaim (inline mo-get-current))
(defun mo-get-current (mo)
  "Returns the original index of the current (not yet proessed) query."
  (aref (%mo-order mo) (%mo-index mo)))

(declaim (inline mo-get-previous))
(defun mo-get-previous (mo)
  "Returns the original index of the previous (= last processed) query. Returns
the initial index instead when no queries are processed yet."
  (aref (%mo-order mo) (max 0 (- (%mo-index mo) 1))))

(declaim (inline mo-process4))
(defun mo-process4 (mo extend-l extend-r shrink-l shrink-r)
  "Processes the next query. EXTEND and SHRINK take three arguments: the <index>
added/removed right now, and both ends of the next range: [<left>, <right>)"
  (declare (function extend-l extend-r shrink-l shrink-r))
  (let* ((ord (mo-get-current mo))
         (left (aref (%mo-lefts mo) ord))
         (right (aref (%mo-rights mo) ord))
         (posl (%mo-posl mo))
         (posr (%mo-posr mo)))
    (declare ((mod #.array-total-size-limit) posl posr))
    (loop while (< left posl)
          do (decf posl)
             (funcall extend-l posl))
    (loop while (< posr right)
          do (funcall extend-r posr)
             (incf posr))
    (loop while (< posl left)
          do (funcall shrink-l posl)
             (incf posl))
    (loop while (< right posr)
          do (decf posr)
             (funcall shrink-r posr))
    (setf (%mo-posl mo) posl
          (%mo-posr mo) posr)
    (incf (%mo-index mo))))

(declaim (inline mo-process2))
(defun mo-process2 (mo extend shrink)
  "Processes the next query. EXTEND and SHRINK take three arguments: the <index>
added/removed right now, and both ends of the next range: [<left>, <right>)"
  (declare (function extend shrink))
  (mo-process4 mo extend extend shrink shrink))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/mo :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (write-string
     (with-output-to-string (*standard-output* nil :element-type 'base-char)
       (dotimes (_ tt)
         (let* ((n (read-fixnum))
                (q (read-fixnum))
                (as (make-array n :element-type 'uint31 :initial-element 0))
                (end 0)
                (table (make-hash-table :test #'eq)))
           (declare (uint31 end))
           (dotimes (i n)
             (let ((a (read-fixnum)))
               (unless (gethash a table)
                 (setf (gethash a table) end)
                 (incf end))
               (setf (aref as i) (gethash a table))))
           (let* ((ls (make-array q :element-type 'mo-integer :initial-element 0))
                  (rs (make-array q :element-type 'mo-integer :initial-element 0))
                  (ks (make-array q :element-type 'uint31 :initial-element 0))
                  (counter (make-array end :element-type 'uint31 :initial-element 0))
                  (cum (make-array (+ n 2) :element-type 'uint31 :initial-element 0))
                  (res (make-array q :element-type 'uint31 :initial-element 0)))
             (dotimes (i q)
               (let ((l (- (read-fixnum) 1))
                     (r (read-fixnum))
                     (k (read-fixnum)))
                 (setf (aref ls i) l
                       (aref rs i) r
                       (aref ks i) k)))
             (setf (aref cum 0) end)
             (let ((mo (make-mo 447 ls rs)))
               (dotimes (_ q)
                 (let* ((qi (mo-get-current mo))
                        (k (aref ks qi)))
                   (mo-process2 mo
                                (lambda (pos)
                                  (let ((a (aref as pos)))
                                    (incf (aref counter a))
                                    (incf (aref cum (aref counter a)))))
                                (lambda (pos)
                                  (let ((a (aref as pos)))
                                    (decf (aref cum (aref counter a)))
                                    (decf (aref counter a)))))
                   (setf (aref res qi)
                         (- (aref cum 1) (aref cum (+ k 1)))))))
             (map () #'println res))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/CHEFNUMK"))

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
