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
(defpackage :cp/implicit-treap
  (:use :cl)
  (:export #:itreap #:itreap-p #:itreap-count #:itreap-accumulator
           #:make-itreap #:invalid-itreap-index-error #:itreap-ref
           #:itreap-split #:itreap-merge #:itreap-insert #:itreap-delete
           #:itreap-push #:itreap-pop #:itreap-map #:do-itreap
           #:itreap-fold #:itreap-max-right #:itreap-min-left
           #:itreap-update #:itreap-reverse
           #:itreap-bisect-left #:itreap-bisect-right #:itreap-insort)
  (:documentation "Provides implicit treap.

NOTE: an empty treap is NIL.
TODO: abstraction"))
(in-package :cp/implicit-treap)

(defconstant +op-identity+ 0
  "identity element w.r.t. OP")

(declaim (inline updater-op))
(defun updater-op (lazy x)
  "Is the operator to compute and update LAZY value. LAZY is the current LAZY
value and X is an operand."
  (+ lazy x))

(defconstant +updater-identity+ 0
  "identity element w.r.t. UPDATER-OP")

(declaim (inline modifier-op))
(defun modifier-op (acc lazy size)
  "Is the operator to update ACCUMULATOR (and VALUE) based on LAZY value. ACC is
the current ACCUMULATOR value and LAZY is the LAZY value. SIZE is the length of
the target interval."
  (declare (ignorable size))
  (+ acc lazy))

(deftype index () '(integer 0 #.(floor most-positive-fixnum 2)))
(defstruct (itreap (:constructor %make-itreap (value priority &key left right (count 1) (lazy +updater-identity+)))
                   (:copier nil)
                   (:conc-name %itreap-))
  (value +op-identity+ :type fixnum)
  (lazy +updater-identity+ :type fixnum)
  (priority 0 :type (mod #.most-positive-fixnum))
  (count 1 :type index) ; size of (sub)treap
  (left nil :type (or null itreap))
  (right nil :type (or null itreap)))

(declaim (inline itreap-count))
(defun itreap-count (itreap)
  "Returns the number of the elements of ITREAP."
  (declare ((or null itreap) itreap))
  (if itreap
      (%itreap-count itreap)
      0))

(declaim (inline update-count))
(defun update-count (itreap)
  (declare (itreap itreap))
  (setf (%itreap-count itreap)
        (+ 1
           (itreap-count (%itreap-left itreap))
           (itreap-count (%itreap-right itreap)))))

(declaim (inline force-up))
(defun force-up (itreap)
  "Propagates up the information from children."
  (declare (itreap itreap))
  (update-count itreap))

(declaim (inline force-down))
(defun force-down (itreap)
  "Propagates down the information to children."
  (declare (itreap itreap))
  (unless (eql +updater-identity+ (%itreap-lazy itreap))
    (when (%itreap-left itreap)
      (setf (%itreap-lazy (%itreap-left itreap))
            (updater-op (%itreap-lazy (%itreap-left itreap))
                        (%itreap-lazy itreap))))
    (when (%itreap-right itreap)
      (setf (%itreap-lazy (%itreap-right itreap))
            (updater-op (%itreap-lazy (%itreap-right itreap))
                        (%itreap-lazy itreap))))
    (setf (%itreap-value itreap)
          (modifier-op (%itreap-value itreap)
                       (%itreap-lazy itreap)
                       1))
    (setf (%itreap-lazy itreap) +updater-identity+)))

(defun %heapify (node)
  "Makes it max-heap w.r.t. priorities by swapping the priorities of the whole
treap."
  (declare (optimize (speed 3) (safety 0)))
  (when node
    (let ((high-priority-node node))
      (when (and (%itreap-left node)
                 (> (%itreap-priority (%itreap-left node))
                    (%itreap-priority high-priority-node)))
        (setq high-priority-node (%itreap-left node)))
      (when (and (%itreap-right node)
                 (> (%itreap-priority (%itreap-right node))
                    (%itreap-priority high-priority-node)))
        (setq high-priority-node (%itreap-right node)))
      (unless (eql high-priority-node node)
        (rotatef (%itreap-priority high-priority-node)
                 (%itreap-priority node))
        (%heapify high-priority-node)))))

(declaim (inline make-itreap))
(defun make-itreap (size &key (initial-element nil supplied-p) initial-contents)
  "Makes a treap of SIZE in O(SIZE) time. Its values are filled with the
INITIAL-ELEMENT (or identity element) unless INITIAL-CONTENTS are supplied."
  (declare ((or null vector) initial-contents))
  (labels ((build (l r)
             (declare (index l r))
             (if (= l r)
                 nil
                 (let* ((mid (ash (+ l r) -1))
                        (node (%make-itreap (cond (initial-contents
                                                   (aref initial-contents mid))
                                                  (supplied-p
                                                   initial-element)
                                                  (t +op-identity+))
                                            (random most-positive-fixnum))))
                   (setf (%itreap-left node) (build l mid))
                   (setf (%itreap-right node) (build (+ mid 1) r))
                   (%heapify node)
                   (force-up node)
                   node))))
    (build 0 size)))

(define-condition invalid-itreap-index-error (type-error)
  ((itreap :initarg :itreap :reader invalid-itreap-index-error-itreap)
   (index :initarg :index :reader invalid-itreap-index-error-index))
  (:report
   (lambda (condition stream)
     (let ((index (invalid-itreap-index-error-index condition)))
       (if (consp index)
           (format stream "Invalid range [~W, ~W) for itreap ~W."
                   (car index)
                   (cdr index)
                   (invalid-itreap-index-error-itreap condition))
           (format stream "Invalid index ~W for itreap ~W."
                   index
                   (invalid-itreap-index-error-itreap condition)))))))

(defun itreap-split (itreap index)
  "Destructively splits ITREAP at INDEX and returns two treaps (in ascending
order)."
  (declare (optimize (speed 3))
           (index index))
  (unless (<= index (itreap-count itreap))
    (error 'invalid-itreap-index-error :index index :itreap itreap))
  (labels ((recur (itreap ikey)
             (unless itreap
               (return-from itreap-split (values nil nil)))
             (force-down itreap)
             (let ((left-count (itreap-count (%itreap-left itreap))))
               (if (<= ikey left-count)
                   (multiple-value-bind (left right)
                       (itreap-split (%itreap-left itreap) ikey)
                     (setf (%itreap-left itreap) right)
                     (force-up itreap)
                     (values left itreap))
                   (multiple-value-bind (left right)
                       (itreap-split (%itreap-right itreap) (- ikey left-count 1))
                     (setf (%itreap-right itreap) left)
                     (force-up itreap)
                     (values itreap right))))))
    (recur itreap index)))

(defun itreap-merge (left right)
  "Destructively concatenates two ITREAPs. Note that this `merge' is different
from CL:MERGE and rather close to CL:CONCATENATE."
  (declare (optimize (speed 3))
           ((or null itreap) left right))
  (cond ((null left) (when right (force-down right) (force-up right)) right)
        ((null right) (when left (force-down left) (force-up left)) left)
        (t (force-down left)
           (force-down right)
           (if (> (%itreap-priority left) (%itreap-priority right))
               (progn
                 (setf (%itreap-right left)
                       (itreap-merge (%itreap-right left) right))
                 (force-up left)
                 left)
               (progn
                 (setf (%itreap-left right)
                       (itreap-merge left (%itreap-left right)))
                 (force-up right)
                 right)))))

(defun itreap-insert (itreap index obj)
  "Destructively inserts OBJ into ITREAP at INDEX and returns the resultant treap.

You cannot rely on the side effect. Use the returned value."
  (declare (optimize (speed 3))
           ((or null itreap) itreap)
           (index index))
  (unless (<= index (itreap-count itreap))
    (error 'invalid-itreap-index-error :itreap itreap :index index))
  (let ((node (%make-itreap obj (random most-positive-fixnum))))
    (labels ((recur (itreap ikey)
               (declare (index ikey))
               (unless itreap (return-from recur node))
               (force-down itreap)
               (if (> (%itreap-priority node) (%itreap-priority itreap))
                   (progn
                     (setf (values (%itreap-left node) (%itreap-right node))
                           (itreap-split itreap ikey))
                     (force-up node)
                     node)
                   (let ((left-count (itreap-count (%itreap-left itreap))))
                     (if (<= ikey left-count)
                         (setf (%itreap-left itreap)
                               (recur (%itreap-left itreap) ikey))
                         (setf (%itreap-right itreap)
                               (recur (%itreap-right itreap) (- ikey left-count 1))))
                     (force-up itreap)
                     itreap))))
      (recur itreap index))))

(defun itreap-delete (itreap index)
  "Destructively deletes the object at INDEX in ITREAP.

You cannot rely on the side effect. Use the returned value."
  (declare (optimize (speed 3))
           (index index))
  (unless (< index (itreap-count itreap))
    (error 'invalid-itreap-index-error :itreap itreap :index index))
  (labels ((recur (itreap ikey)
             (declare (index ikey))
             (force-down itreap)
             (let ((left-count (itreap-count (%itreap-left itreap))))
               (cond ((< ikey left-count)
                      (setf (%itreap-left itreap)
                            (recur (%itreap-left itreap) ikey))
                      (force-up itreap)
                      itreap)
                     ((> ikey left-count)
                      (setf (%itreap-right itreap)
                            (recur (%itreap-right itreap) (- ikey left-count 1)))
                      (force-up itreap)
                      itreap)
                     (t
                      (itreap-merge (%itreap-left itreap) (%itreap-right itreap)))))))
    (recur itreap index)))

(defmacro itreap-push (itreap pos obj)
  "Pushes OBJ to ITREAP at POS."
  `(setf ,itreap (itreap-insert ,itreap ,pos ,obj)))

(defmacro itreap-pop (itreap pos)
  "Returns the object at POS and deletes it."
  (let ((p (gensym)))
    `(let ((,p ,pos))
       (prog1 (itreap-ref ,itreap ,p)
         (setf ,itreap (itreap-delete ,itreap ,p))))))

(declaim (inline itreap-map))
(defun itreap-map (itreap function &optional (start 0) end)
  "Successively applies FUNCTION to ITREAP[START], ..., ITREAP[END-1]."
  (declare (function function)
           (index start)
           ((or null index) end))
  (unless end
    (setq end (itreap-count itreap)))
  (unless (<= start end (itreap-count itreap))
    (error 'invalid-itreap-index-error :itreap itreap :index (cons start end)))
  (labels ((recur (itreap l r)
             (declare (index l r))
             (when (< l r)
               (force-down itreap)
               (force-up itreap)
               (let ((lcount (itreap-count (%itreap-left itreap))))
                 (when (< l lcount)
                   (recur (%itreap-left itreap) l (min r lcount)))
                 (when (and (<= l lcount) (< lcount r))
                   (funcall function (%itreap-value itreap)))
                 (when (< (+ lcount 1) r)
                   (recur (%itreap-right itreap) (max 0 (- l lcount 1)) (- r lcount 1)))))))
    (recur itreap start end)))

(defmethod print-object ((object itreap) stream)
  (print-unreadable-object (object stream :type t)
    (let ((init t))
      (itreap-map object
                  (lambda (x)
                    (if init
                        (setq init nil)
                        (write-char #\  stream))
                    (write x :stream stream))))))

(declaim (inline itreap-ref))
(defun itreap-ref (itreap index)
  "Returns the element ITREAP[INDEX]."
  (declare (index index))
  (labels ((%ref (itreap index)
             (declare (index index))
             (force-down itreap)
             (let ((left-count (itreap-count (%itreap-left itreap))))
               (cond ((< index left-count)
                      (%ref (%itreap-left itreap) index))
                     ((> index left-count)
                      (%ref (%itreap-right itreap) (- index left-count 1)))
                     (t (%itreap-value itreap))))))
    (%ref itreap index)))

(declaim (inline itreap-update))
(defun itreap-update (itreap operand l r)
  "Updates ITRAP by ITREAP[i] := (OP ITREAP[i] OPERAND) for all i in [l, r)"
  (declare (index l r))
  (labels
      ((recur (itreap l r)
         (declare (index l r))
         (when itreap
           (if (and (zerop l) (= r (%itreap-count itreap)))
               (progn
                 (setf (%itreap-lazy itreap)
                       (updater-op (%itreap-lazy itreap) operand))
                 (force-down itreap))
               (progn
                 (force-down itreap)
                 (let ((left-count (itreap-count (%itreap-left itreap))))
                   (if (<= l left-count)
                       (if (< left-count r)
                           ;; LEFT-COUNT is in [L, R)
                           (progn
                             (recur (%itreap-left itreap) l (min r left-count))
                             (setf (%itreap-value itreap)
                                   (modifier-op (%itreap-value itreap) operand 1))
                             (recur (%itreap-right itreap) 0 (- r left-count 1)))
                           ;; LEFT-COUNT is in [R, END)
                           (recur (%itreap-left itreap) l (min r left-count)))
                       ;; LEFT-COUNT is in [0, L)
                       (recur (%itreap-right itreap)
                              (- l left-count 1)
                              (- r left-count 1)))))))))
    (recur itreap l r)
    itreap))

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

(defpackage :cp/println-sequence
  (:use :cl)
  (:export #:println-sequence))
(in-package :cp/println-sequence)

(declaim (inline println-sequence))
(defun println-sequence (sequence &key (out *standard-output*) (key #'identity))
  (let ((init t))
    (sequence:dosequence (x sequence)
      (if init
          (setq init nil)
          (write-char #\  out))
      (princ (funcall key x) out))
    (terpri out)))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/println-sequence :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/implicit-treap :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(declaim (ftype (function * (values (simple-array list (*)) &optional)) read-graph))
(defun read-graph (n)
  (declare #.*opt*)
  (let ((graph (make-array n :element-type 'list :initial-element nil)))
    (dotimes (i (- n 1))
      (let ((u (- (read-fixnum) 1))
            (v (- (read-fixnum) 1)))
        (push u (aref graph v))
        (push v (aref graph u))))
    graph))

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (write-string
     (with-output-to-string (*standard-output* nil :element-type 'base-char)
       (dotimes (_ tt)
         (let* ((n (read-fixnum))
                (graph1 (read-graph n))
                (graph2 (read-graph n))
                (pres (make-array n :element-type 'uint31 :initial-element 0))
                (posts (make-array n :element-type 'uint31 :initial-element 0))
                (dp (make-itreap n))
                (res (make-array n :element-type 'uint31 :initial-element 0)))
           (let ((end 0))
             (sb-int:named-let dfs ((v 0) (parent -1))
               (setf (aref pres v) end)
               (incf end)
               (dolist (child (aref graph1 v))
                 (unless (eql child parent)
                   (dfs child v)))
               (setf (aref posts v) end)))
           (sb-int:named-let dfs ((v 0) (parent -1))
             (setf (aref res v) (itreap-ref dp (aref pres v)))
             (itreap-update dp 1 (aref pres v) (aref posts v))
             (dolist (child (aref graph2 v))
               (unless (eql child parent)
                 (dfs child v)))
             (itreap-update dp -1 (aref pres v) (aref posts v)))
           (println-sequence res)))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/ANCESTOR"))

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
