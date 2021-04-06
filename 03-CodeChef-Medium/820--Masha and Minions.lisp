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

(declaim (inline op))
(defun op (a b)
  "Is a binary operator comprising a monoid."
  (declare (fixnum a b))
  (+ a b))

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
(defstruct (itreap (:constructor %make-itreap (value priority &key left right (count 1) (accumulator value)))
                   (:copier nil)
                   (:conc-name %itreap-))
  (value +op-identity+ :type fixnum)
  (accumulator +op-identity+ :type fixnum)
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

(declaim (inline itreap-accumulator))
(defun itreap-accumulator (itreap)
  "Returns the sum (w.r.t. OP) of the whole ITREAP:
ITREAP[0]+ITREAP[1]+...+ITREAP[SIZE-1]."
  (declare ((or null itreap) itreap))
  (if itreap
      (%itreap-accumulator itreap)
      +op-identity+))

(declaim (inline update-count))
(defun update-count (itreap)
  (declare (itreap itreap))
  (setf (%itreap-count itreap)
        (+ 1
           (itreap-count (%itreap-left itreap))
           (itreap-count (%itreap-right itreap)))))

(declaim (inline update-accumulator))
(defun update-accumulator (itreap)
  (declare (itreap itreap))
  (setf (%itreap-accumulator itreap)
        (if (%itreap-left itreap)
            (if (%itreap-right itreap)
                (let ((mid (op (%itreap-accumulator (%itreap-left itreap))
                               (%itreap-value itreap))))
                  (op mid (%itreap-accumulator (%itreap-right itreap))))
                (op (%itreap-accumulator (%itreap-left itreap))
                    (%itreap-value itreap)))
            (if (%itreap-right itreap)
                (op (%itreap-value itreap)
                    (%itreap-accumulator (%itreap-right itreap)))
                (%itreap-value itreap)))))

(declaim (inline force-up))
(defun force-up (itreap)
  "Propagates up the information from children."
  (declare (itreap itreap))
  (update-count itreap)
  (update-accumulator itreap))

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
  (declare #.cl-user::*opt*
           (index index))
  (unless (<= index (itreap-count itreap))
    (error 'invalid-itreap-index-error :index index :itreap itreap))
  (labels ((recur (itreap ikey)
             (unless itreap
               (return-from itreap-split (values nil nil)))
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
  (declare #.cl-user::*opt*
           ((or null itreap) left right))
  (cond ((null left) (when right (force-up right)) right)
        ((null right) (when left (force-up left)) left)
        (t (if (> (%itreap-priority left) (%itreap-priority right))
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
  (declare #.cl-user::*opt*
           ((or null itreap) itreap)
           (index index))
  (unless (<= index (itreap-count itreap))
    (error 'invalid-itreap-index-error :itreap itreap :index index))
  (let ((node (%make-itreap obj (random most-positive-fixnum))))
    (labels ((recur (itreap ikey)
               (declare (index ikey))
               (unless itreap (return-from recur node))
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

(defmacro do-itreap ((var itreap &optional result) &body body)
  "Successively binds ITREAP[0], ..., ITREAP[SIZE-1] to VAR and executes BODY
each time."
  `(block nil
     (itreap-map ,itreap (lambda (,var) ,@body))
     ,result))

(defun itreap (&rest args)
  ;; NOTE: This function takes O(nlog(n)) time. Use MAKE-ITREAP for efficiency.
  (labels ((recur (list position itreap)
             (declare (index position))
             (if (null list)
                 itreap
                 (recur (cdr list)
                        (+ 1 position)
                        (itreap-insert itreap position (car list))))))
    (recur args 0 nil)))

(declaim (inline itreap-ref))
(defun itreap-ref (itreap index)
  "Returns the element ITREAP[INDEX]."
  (declare (index index))
  (unless (< index (itreap-count itreap))
    (error 'invalid-itreap-index-error :itreap itreap :index index))
  (labels ((%ref (itreap index)
             (declare (index index))
             (force-up itreap)
             (let ((left-count (itreap-count (%itreap-left itreap))))
               (cond ((< index left-count)
                      (%ref (%itreap-left itreap) index))
                     ((> index left-count)
                      (%ref (%itreap-right itreap) (- index left-count 1)))
                     (t (%itreap-value itreap))))))
    (%ref itreap index)))

(declaim (inline (setf itreap-ref)))
(defun (setf itreap-ref) (new-value itreap index)
  "Sets ITREAP[INDEX] to the given value."
  (declare (index index))
  (unless (< index (itreap-count itreap))
    (error 'invalid-itreap-index-error :itreap itreap :index index))
  (labels ((%set (itreap index)
             (declare (index index))
             (let ((left-count (itreap-count (%itreap-left itreap))))
               (cond ((< index left-count)
                      (%set (%itreap-left itreap) index))
                     ((> index left-count)
                      (%set (%itreap-right itreap) (- index left-count 1)))
                     (t (setf (%itreap-value itreap) new-value))))
             (force-up itreap)))
    (%set itreap index)
    new-value))

(declaim (inline itreap-fold))
(defun itreap-fold (itreap l r)
  "Returns the `sum' (w.r.t. OP) of the range ITREAP[L, R)."
  (declare (index l r))
  (unless (<= l r (itreap-count itreap))
    (error 'invalid-itreap-index-error :itreap itreap :index (cons l r)))
  (labels
      ((recur (itreap l r)
         (declare (index l r))
         (unless itreap
           (return-from recur +op-identity+))
         (force-up itreap)
         (if (and (zerop l) (= r (%itreap-count itreap)))
             (itreap-accumulator itreap)
             (let ((left-count (itreap-count (%itreap-left itreap))))
               (if (<= l left-count)
                   (if (< left-count r)
                       ;; LEFT-COUNT is in [L, R)
                       (op (op (recur (%itreap-left itreap) l (min r left-count))
                               (%itreap-value itreap))
                           (recur (%itreap-right itreap) 0 (- r left-count 1)))
                       ;; LEFT-COUNT is in [R, END)
                       (recur (%itreap-left itreap) l (min r left-count)))
                   ;; LEFT-COUNT is in [0, L)
                   (recur (%itreap-right itreap) (- l left-count 1) (- r left-count 1)))))))
    (recur itreap l r)))

(declaim (ftype (function * (values index &optional)) itreap-max-right)
         (inline itreap-max-right))
(defun itreap-max-right (itreap test &optional (start 0))
  "Returns the largest index that satisfies (FUNCALL TEST (OP ITREAP[START]
ITREAP[START+1] ... ITREAP[index-1])).

Note:
- (FUNCALL TEST +OP-IDENTITY+) must be true.
- TEST must be monotone in the target range.
"
  (declare (index start))
  (assert (funcall test +op-identity+ 0))
  (when (< (itreap-count itreap) start)
    (error 'invalid-itreap-index-error :index start :itreap itreap))
  (labels
      ((fold (itreap offset)
         (declare (index offset))
         (unless itreap
           (return-from fold +op-identity+))
         (update-accumulator itreap)
         (let ((lcount (+ offset (itreap-count (%itreap-left itreap)))))
           (declare (index lcount))
           (if (< lcount start)
               (fold (%itreap-right itreap) (+ lcount 1))
               (let ((sum (fold (%itreap-left itreap) offset)))
                 (cond ((not (funcall test
                                      (setq sum (op sum (%itreap-value itreap)))
                                      (+ lcount 1)))
                        (return-from itreap-max-right lcount))
                       ((funcall test
                                 (op sum (itreap-accumulator (%itreap-right itreap)))
                                 (+ lcount 1 (itreap-count (%itreap-right itreap))))
                        sum)
                       (t (search-subtree (%itreap-right itreap) (+ lcount 1) sum)))))))
       (search-subtree (itreap offset prev-sum)
         (declare (index offset))
         (unless itreap
           (return-from itreap-max-right offset))
         (update-accumulator itreap)
         (let ((sum (op prev-sum (itreap-accumulator (%itreap-left itreap))))
               (lcount (+ offset (itreap-count (%itreap-left itreap)))))
           (declare (index lcount))
           (cond ((not (funcall test sum lcount))
                  (search-subtree (%itreap-left itreap) offset prev-sum))
                 ((not (funcall test
                                (setq sum (op sum (%itreap-value itreap)))
                                (+ lcount 1)))
                  (return-from itreap-max-right
                    (+ offset (itreap-count (%itreap-left itreap)))))
                 (t
                  (search-subtree (%itreap-right itreap)
                                  (+ offset (itreap-count (%itreap-left itreap)) 1)
                                  sum))))))
    (if (zerop start)
        (search-subtree itreap 0 +op-identity+)
        (progn (fold itreap 0)
               (itreap-count itreap)))))

(declaim (inline itreap-bisect-left)
         (ftype (function * (values index &optional)) itreap-bisect-left))
(defun itreap-bisect-left (itreap value order &key (key #'identity))
  "Takes a **sorted** treap and returns the smallest index that satisfies
ITREAP[index] >= VALUE, where >= is the complement of ORDER. In other words,
this function returns a leftmost index at which value can be inserted with
keeping the order. Returns the size of ITREAP if ITREAP[length-1] <
VALUE. The time complexity is O(log(n))."
  (labels ((recur (count itreap)
             (declare (index count))
             (cond ((null itreap) nil)
                   ((funcall order (funcall key (%itreap-value itreap)) value)
                    (recur count (%itreap-right itreap)))
                   (t
                    (let ((left-count (- count (itreap-count (%itreap-right itreap)) 1)))
                      (or (recur left-count (%itreap-left itreap))
                          left-count))))))
    (or (recur (itreap-count itreap) itreap)
        (itreap-count itreap))))

(declaim (inline itreap-insort))
(defun itreap-insort (itreap obj order)
  "Does insertion to the sorted treap with keeping the order. You cannot rely on
the side effect. Use the returned value."
  (let ((pos (itreap-bisect-left itreap obj order)))
    (itreap-insert itreap pos obj)))

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
  (use-package :cp/parallel-sort :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/implicit-treap :cl-user))
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
                (as (make-array n :element-type 'uint31 :initial-element 0))
                (bs (make-array n :element-type 'uint31 :initial-element 0))
                (res 0)
                itreap)
           (declare (uint31 res))
           (dotimes (i n)
             (setf (aref as i) (read-fixnum)
                   (aref bs i) (read-fixnum)))
           (parallel-sort! as #'> bs)
           (dotimes (i n)
             (let ((a (aref as i))
                   (b (aref bs i)))
               (setq itreap (itreap-insort itreap b #'<))
               (maxf res (itreap-max-right
                          itreap
                          (lambda (sum index)
                            (declare (fixnum sum)
                                     (uint31 index))
                            (<= sum (* index a)))))))
           (println res)))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/MINIONS"))

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
   (equal "2
0
"
          (run "2
3
1 4
3 3
2 1
2
3 5
1 4
" nil))))
