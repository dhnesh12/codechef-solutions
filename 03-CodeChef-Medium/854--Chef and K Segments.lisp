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

(defpackage :cp/multiset
  (:use :cl)
  (:export #:mset #:mset-empty-error #:mset-empty-error-mset
           #:mset-concat #:mset-split #:mset-insert #:mset-delete
           #:mset-push #:mset-pop #:mset-map #:mset-map-run-length
           #:mset-find #:mset-count #:mset-first #:mset-last #:mset-size
           #:mset-bisect-left #:mset-bisect-right #:mset-bisect-left-1 #:mset-bisect-right-1
           #:mset-position-left #:mset-position-right #:mset-ref)
  (:documentation "Provides multiset implementation with access by index."))
(in-package :cp/multiset)

(define-condition mset-empty-error (error)
  ((mset :initarg :mset :reader mset-empty-error-mset))
  (:report
   (lambda (condition stream)
     (format stream "Attempted to draw excessive number of elements from multiset ~W."
             (mset-empty-error-mset condition)))))

(defstruct (mset (:constructor %make-mset
                     (key priority count &key left right (size count)))
                 (:copier nil)
                 (:conc-name %mset-))
  (key 0 :type fixnum)
  (count 0 :type (integer 0 #.most-positive-fixnum))
  (size 0 :type (integer 0 #.most-positive-fixnum))
  (priority 0 :type (mod #.most-positive-fixnum))
  (left nil :type (or null mset))
  (right nil :type (or null mset)))

(declaim (inline mset-key))
(defun mset-key (mset)
  "Returns the root key of (nullable) MSET."
  (and mset (%mset-key mset)))

(declaim (inline mset-size))
(defun mset-size (mset)
  "Returns the total number of elements in MSET."
  (declare ((or null mset) mset))
  (if (null mset)
      0
      (%mset-size mset)))

(declaim (inline update-size))
(defun update-size (mset)
  (declare (mset mset))
  (setf (%mset-size mset)
        (if (%mset-left mset)
            (if (%mset-right mset)
                (let ((tmp (+ (%mset-size (%mset-left mset))
                              (%mset-count mset))))
                  (declare ((integer 0 #.most-positive-fixnum) tmp))
                  (+ tmp (%mset-size (%mset-right mset))))
                (+ (%mset-size (%mset-left mset))
                   (%mset-count mset)))
            (if (%mset-right mset)
                (+ (%mset-count mset)
                   (%mset-size (%mset-right mset)))
                (%mset-count mset)))))

(declaim (ftype (function * (values (or null mset) (or null mset) &optional))
                mset-split)
         (inline mset-split))
(defun mset-split (mset key &key (order #'<))
  "Destructively splits MSET with reference to KEY and returns two multisets,
the smaller sub-multiset (< KEY) and the larger one (>= KEY)."
  (declare ((or null mset) mset))
  (labels ((recur (mset)
             (cond ((null mset) (values nil nil))
                   ((funcall order (%mset-key mset) key)
                    (multiple-value-bind (left right) (recur (%mset-right mset))
                      (setf (%mset-right mset) left)
                      (update-size mset)
                      (values mset right)))
                   (t
                    (multiple-value-bind (left right) (recur (%mset-left mset))
                      (setf (%mset-left mset) right)
                      (update-size mset)
                      (values left mset))))))
    (recur mset)))

(declaim (ftype (function * (values (or null mset) &optional))
                mset-concat))
(defun mset-concat (left right)
  "Destructively concatenates two multisets. Assumes that all keys of LEFT are
smaller (or larger, depending on the order) than those of RIGHT."
  (declare (optimize (speed 3))
           ((or null mset) left right))
  (cond ((null left) right)
        ((null right) left)
        ((> (%mset-priority left) (%mset-priority right))
         (setf (%mset-right left)
               (mset-concat (%mset-right left) right))
         (update-size left)
         left)
        (t
         (setf (%mset-left right)
               (mset-concat left (%mset-left right)))
         (update-size right)
         right)))

(declaim (inline mset-insert))
(defun mset-insert (mset key &key (count 1) (order #'<))
  "Destructively inserts KEY into MSET and returns the resultant multiset. You
cannot rely on the side effect. Use the returned value."
  (declare ((or null mset) mset)
           ((integer 0 #.most-positive-fixnum) count))
  (when (zerop count)
    (return-from mset-insert mset))
  (labels ((recur (new-priority mset found)
             (declare ((mod #.most-positive-fixnum) new-priority))
             (let* ((new-found (or found
                                   (null mset)
                                   (> new-priority (%mset-priority mset))))
                    (res (cond ((null mset) nil)
                               ((funcall order key (%mset-key mset))
                                (recur new-priority (%mset-left mset) new-found))
                               ((funcall order (%mset-key mset) key)
                                (recur new-priority (%mset-right mset) new-found))
                               (t
                                (incf (%mset-count mset) count)
                                t))))
               (cond ((eql res t)
                      (update-size mset)
                      t)
                     ((mset-p res)
                      (if (funcall order key (%mset-key mset))
                          (setf (%mset-left mset) res)
                          (setf (%mset-right mset) res))
                      (update-size mset)
                      mset)
                     ((not (eq found new-found))
                      (multiple-value-bind (left right) (mset-split mset key :order order)
                        (let ((res (%make-mset key new-priority count
                                               :left left :right right)))
                          (update-size res)
                          res)))
                     (t nil)))))
    (let ((res (recur (random most-positive-fixnum) mset nil)))
      (if (eql t res)
          mset
          res))))

(declaim (ftype (function * (values (or null mset) &optional))
                mset-delete)
         (inline mset-delete))
(defun mset-delete (mset key &key (count 1) (order #'<) (empty-error-p t))
  "Destructively deletes KEY in MSET and returns the resultant multiset. You
cannot rely on the side effect. Use the returned multiset.

If EMPTY-ERROR-P is true, this function throws an MSET-EMPTY-ERROR when
excessive number of KEYs are attempted to be deleted."
  (declare ((or null mset) mset)
           ((integer 0 #.most-positive-fixnum) count))
  (labels
      ((%error () (error 'mset-empty-error :mset mset))
       (recur (mset)
         (cond ((null mset)
                (when empty-error-p (%error)))
               ((funcall order key (%mset-key mset))
                (setf (%mset-left mset) (recur (%mset-left mset)))
                (update-size mset)
                mset)
               ((funcall order (%mset-key mset) key)
                (setf (%mset-right mset) (recur (%mset-right mset)))
                (update-size mset)
                mset)
               (t
                (let ((current (%mset-count mset)))
                  (cond ((and empty-error-p (< current count))
                         (%error))
                        ((> current count)
                         (decf (%mset-count mset) count)
                         (update-size mset)
                         mset)
                        (t
                         (mset-concat (%mset-left mset)
                                      (%mset-right mset)))))))))
    (recur mset)))

(defmacro mset-push (key mset &optional (order '#'<))
  "Pushes a KEY to MSET."
  `(setf ,mset (mset-insert ,mset ,key :order ,order)))

(defmacro mset-pop (key mset &optional (order '#'<))
  "Deletes a KEY from MSET."
  `(setf ,mset (mset-delete ,mset ,key :order ,order)))

(declaim (inline mset-ref))
(defun mset-count (mset key &key (order #'<))
  "Returns the number of KEYs in MSET."
  (declare ((or null mset) mset))
  (labels ((recur (mset)
             (cond ((null mset) 0)
                   ((funcall order key (%mset-key mset))
                    (recur (%mset-left mset)))
                   ((funcall order (%mset-key mset) key)
                    (recur (%mset-right mset)))
                   (t (%mset-count mset)))))
    (recur mset)))

(declaim (inline mset-map-run-length))
(defun mset-map-run-length (function mset)
  "Successively applies FUNCTION to each element of MSET in the underlying
order. FUNCTION must take two arguments: KEY and COUNT:"
  (labels ((recur (mset)
             (when mset
               (recur (%mset-left mset))
               (funcall function (%mset-key mset) (%mset-count mset))
               (recur (%mset-right mset)))))
    (recur mset)))

(declaim (inline mset-map))
(defun mset-map (function mset)
  "Successively applies FUNCTION to each element of MSET in the underlying
order. This function only passes a key to FUNCTION and calls it as many times as
the number of the key in MSET."
  (labels ((recur (mset)
             (when mset
               (recur (%mset-left mset))
               (dotimes (_ (%mset-count mset))
                 (funcall function (%mset-key mset)))
               (recur (%mset-right mset)))))
    (recur mset)))

(defmethod print-object ((object mset) stream)
  (print-unreadable-object (object stream :type t)
    (let ((init t))
      (mset-map-run-length
       (lambda (key count)
         (if init
             (setq init nil)
             (write-char #\  stream))
         (format stream "<~A . ~A>" key count))
       object))))

(defun mset-first (mset)
  "Returns the leftmost key of MSET."
  (declare (optimize (speed 3))
           (mset mset))
  (if (%mset-left mset)
      (mset-first (%mset-left mset))
      (%mset-key mset)))

(defun mset-last (mset)
  "Returns the rightmost key of MSET."
  (declare (optimize (speed 3))
           (mset mset))
  (if (%mset-right mset)
      (mset-last (%mset-right mset))
      (%mset-key mset)))

(declaim (inline mset-find))
(defun mset-find (mset key &key (order #'<))
  "Finds and returns KEY if it exists, otherwise returns NIL. Equality is here
equivalent to 'neither larger nor smaller'."
  (declare ((or null mset) mset))
  (labels ((recur (mset)
             (cond ((null mset) nil)
                   ((funcall order key (%mset-key mset))
                    (recur (%mset-left mset)))
                   ((funcall order (%mset-key mset) key)
                    (recur (%mset-right mset)))
                   (t key))))
    (recur mset)))

(declaim (ftype (function * (values (integer 0 #.most-positive-fixnum) &optional))
                mset-position-left)
         (inline mset-position-left))
(defun mset-position-left (mset key &key (order #'<))
  "Returns the leftmost index at which KEY can be inserted with keeping the
order."
  (declare ((or null mset) mset))
  (labels ((recur (mset)
             (cond ((null mset) 0)
                   ((funcall order (%mset-key mset) key)
                    (the (integer 0 #.most-positive-fixnum)
                         (+ (mset-size (%mset-left mset))
                            (%mset-count mset)
                            (recur (%mset-right mset)))))
                   (t
                    (recur (%mset-left mset))))))
    (recur mset)))

(declaim (ftype (function * (values (integer 0 #.most-positive-fixnum) &optional))
                mset-position-right)
         (inline mset-position-right))
(defun mset-position-right (mset key &key (order #'<))
  "Returns the rightmost index at which KEY can be inserted with keeping the
order."
  (declare ((or null mset) mset))
  (labels ((recur (mset)
             (cond ((null mset) 0)
                   ((funcall order key (%mset-key mset))
                    (recur (%mset-left mset)))
                   (t
                    (the (integer 0 #.most-positive-fixnum)
                         (+ (mset-size (%mset-left mset))
                            (%mset-count mset)
                            (recur (%mset-right mset))))))))
    (recur mset)))

(defun mset-ref (mset index)
  "Returns the INDEX-th element of MSET."
  (declare (optimize (speed 3))
           (mset mset)
           ((integer 0 #.most-positive-fixnum) index))
  (assert (< index (%mset-size mset)))
  (labels ((recur (mset parent-sum)
             (let ((sum parent-sum))
               (declare ((integer 0 #.most-positive-fixnum) sum))
               (cond ((< index (incf sum (mset-size (%mset-left mset))))
                      (recur (%mset-left mset) parent-sum))
                     ((< index (incf sum (%mset-count mset)))
                      (%mset-key mset))
                     (t (recur (%mset-right mset) sum))))))
    (recur mset 0)))

;;;
;;; Binary search by key
;;;

(declaim (inline mset-bisect-left))
(defun mset-bisect-left (mset key &key (order #'<))
  "Returns the smallest key equal to or larger than KEY. Returns NIL if KEY is
larger than any keys in MSET."
  (declare ((or null mset) mset)
           (function order))
  (labels ((recur (mset)
             (cond ((null mset) nil)
                   ((funcall order (%mset-key mset) key)
                    (recur (%mset-right mset)))
                   (t (or (recur (%mset-left mset))
                          mset)))))
    (mset-key (recur mset))))

(declaim (inline mset-bisect-right))
(defun mset-bisect-right (mset key &key (order #'<))
  "Returns the smallest key larger than KEY. Returns NIL if KEY is equal to or
larger than any keys in MSET."
  (declare ((or null mset) mset)
           (function order))
  (labels ((recur (mset)
             (cond ((null mset) nil)
                   ((funcall order key (%mset-key mset))
                    (or (recur (%mset-left mset))
                        mset))
                   (t (recur (%mset-right mset))))))
    (mset-key (recur mset))))

(declaim (inline mset-bisect-left-1))
(defun mset-bisect-left-1 (mset key &key (order #'<))
  "Returns the largest key smaller than KEY. Returns NIL if KEY is equal to or
smaller than any keys in MSET."
  (declare ((or null mset) mset)
           (function order))
  (labels ((recur (mset)
             (cond ((null mset) nil)
                   ((funcall order (%mset-key mset) key)
                    (or (recur (%mset-right mset))
                        mset))
                   (t (recur (%mset-left mset))))))
    (mset-key (recur mset))))

(declaim (inline mset-bisect-right-1))
(defun mset-bisect-right-1 (mset key &key (order #'<))
  "Returns the largest key equal to or smaller than KEY. Returns NIL if KEY is
smaller than any keys in MSET."
  (declare ((or null mset) mset)
           (function order))
  (labels ((recur (mset)
             (cond ((null mset) nil)
                   ((funcall order key (%mset-key mset))
                    (recur (%mset-left mset)))
                   (t (or (recur (%mset-right mset))
                          mset)))))
    (mset-key (recur mset))))

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

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/modify-macro :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/multiset :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
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
             (k (read))
             (ls (make-array n :element-type 'uint31 :initial-element 0))
             (rs (make-array n :element-type 'uint31 :initial-element 0))
             mset
             (res 0))
        (declare (uint31 n k res))
        (dotimes (i n)
          (setf (aref ls i) (read-fixnum)
                (aref rs i) (read-fixnum)))
        (parallel-sort! ls #'< rs)
        (dotimes (i (+ n 1))
          (when (>= i k)
            (maxf res (- (mset-ref mset (- k 1))
                         (aref ls (- i 1)))))
          (when (< i n)
            (mset-push (aref rs i) mset #'>)))
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
  (defparameter *problem-url* "https://www.codechef.com/problems/CHEFKO"))

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
(5am:test :sample
  (5am:is
   (equal "3
"
          (run "1
3 2
1 6
2 4
3 6
" nil))))
