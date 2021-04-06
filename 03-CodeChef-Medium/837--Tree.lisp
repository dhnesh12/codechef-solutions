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
;;; Lowest common ancestor of tree (or forest) by binary lifting
;;; build: O(nlog(n))
;;; query: O(log(n))
;;;

(defpackage :cp/lca
  (:use :cl)
  (:export #:lca-table #:lca-table-p
           #:make-lca-table #:lca-max-level #:lca-depths #:lca-parents
           #:two-vertices-disconnected-error #:lca-get-lca #:lca-distance))
(in-package :cp/lca)

;; PAY ATTENTION TO THE STACK SIZE! THE CONSTRUCTOR DOES DFS.

(deftype lca-vertex-number () '(signed-byte 32))

(defstruct (lca-table
            (:constructor %make-lca-table
                (size
                 &aux
                 ;; requires 1 + log_2{size-1}
                 (max-level (+ 1 (integer-length (- size 2))))
                 (depths (make-array size
                                     :element-type 'lca-vertex-number
                                     :initial-element -1))
                 (parents (make-array (list size max-level)
                                      :element-type 'lca-vertex-number))))
            (:conc-name lca-)
            (:copier nil))
  (max-level nil :type (integer 0 #.most-positive-fixnum))
  (depths nil :type (simple-array lca-vertex-number (*)))
  (parents nil :type (simple-array lca-vertex-number (* *))))

(defun make-lca-table (graph &key root (key #'identity))
  "GRAPH := vector of adjacency lists
ROOT := null | non-negative fixnum

If ROOT is null, this function traverses each connected component of GRAPH from
an arbitrarily picked vertex. Otherwise this function traverses GRAPH only from
ROOT; GRAPH must be tree in the latter case."
  (declare (optimize (speed 3))
           (vector graph)
           (function key)
           ((or null (integer 0 #.most-positive-fixnum)) root))
  (let* ((size (length graph))
         (lca-table (%make-lca-table size))
         (depths (lca-depths lca-table))
         (parents (lca-parents lca-table))
         (max-level (lca-max-level lca-table)))
    (labels ((dfs (v parent depth)
               (declare (lca-vertex-number v parent))
               (setf (aref depths v) depth
                     (aref parents v 0) parent)
               (dolist (edge (aref graph v))
                 (let ((dest (funcall key edge)))
                   (declare (lca-vertex-number dest))
                   (unless (= dest parent)
                     (dfs dest v (+ 1 depth)))))))
      (if root
          (dfs root -1 0)
          (dotimes (v size)
            (when (= (aref depths v) -1)
              (dfs v -1 0))))
      (dotimes (k (- max-level 1))
        (dotimes (v size)
          (if (= -1 (aref parents v k))
              (setf (aref parents v (+ k 1)) -1)
              (setf (aref parents v (+ k 1))
                    (aref parents (aref parents v k) k)))))
      lca-table)))

(define-condition two-vertices-disconnected-error (error)
  ((lca-table :initarg :lca-table :accessor two-vertices-disconnected-error-lca-table)
   (vertex1 :initarg :vertex1 :accessor two-vertices-disconnected-error-vertex1)
   (vertex2 :initarg :vertex2 :accessor two-vertices-disconnected-error-vertex2))
  (:report
   (lambda (c s)
     (format s "~W and ~W are disconnected on lca-table ~W"
             (two-vertices-disconnected-error-vertex1 c)
             (two-vertices-disconnected-error-vertex2 c)
             (two-vertices-disconnected-error-lca-table c)))))

(declaim (ftype (function * (values (integer 0 #.most-positive-fixnum) &optional))
                lca-get-lca))
(defun lca-get-lca (lca-table vertex1 vertex2)
  "Returns the lowest common ancestor of the vertices VERTEX1 and VERTEX2."
  (declare (optimize (speed 3))
           ((and lca-vertex-number (integer 0)) vertex1 vertex2))
  (let* ((u vertex1)
         (v vertex2)
         (depths (lca-depths lca-table))
         (parents (lca-parents lca-table))
         (max-level (lca-max-level lca-table)))
    (declare (lca-vertex-number u v))
    ;; Ensures depth[u] <= depth[v]
    (when (> (aref depths u) (aref depths v))
      (rotatef u v))
    (dotimes (k max-level)
      (when (logbitp k (- (aref depths v) (aref depths u)))
        (setf v (aref parents v k))))
    (if (= u v)
        u
        (loop for k from (- max-level 1) downto 0
              unless (= (aref parents u k) (aref parents v k))
              do (setq u (aref parents u k)
                       v (aref parents v k))
              finally (if (= (aref parents u 0) -1)
                          (error 'two-vertices-disconnected-error
                                 :lca-table lca-table
                                 :vertex1 vertex1
                                 :vertex2 vertex2)
                          (return (aref parents u 0)))))))

(declaim (inline lca-distance))
(defun lca-distance (lca-table vertex1 vertex2)
  "Returns the distance between two vertices."
  (declare (optimize (speed 3)))
  (let ((depths (lca-depths lca-table))
        (lca (lca-get-lca lca-table vertex1 vertex2)))
    (+ (- (aref depths vertex1) (aref depths lca))
       (- (aref depths vertex2) (aref depths lca)))))

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
  (use-package :cp/lca :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (let* ((tt (read)))
    (dotimes (_ tt)
      (let* ((n (read))
             (graph (make-array n :element-type 'list :initial-element nil)))
        (dotimes (i (- n 1))
          (let ((p (- (read-fixnum) 1)))
            (push (+ i 1) (aref graph p))))
        (let ((lca-table (make-lca-table graph))
              (e1 0)
              (e2 0)
              (dist 0))
          (write-string
           (with-output-to-string (*standard-output* nil :element-type 'base-char)
             (loop for v from 1 below n
                   for d1 = (lca-distance lca-table v e1)
                   for d2 = (lca-distance lca-table v e2)
                   do (cond ((> d1 dist)
                             (setq dist d1
                                   e2 v))
                            ((> d2 dist)
                             (setq dist d2
                                   e1 v)))
                      (println dist)))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/RRTREE"))

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
