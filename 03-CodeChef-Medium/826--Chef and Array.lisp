#-swank
(eval-when (:compile-toplevel)
  (unless (member :child-sbcl *features*)
    (quit
     :recklessly-p t
     :unix-status
     (process-exit-code
      (run-program *runtime-pathname*
                   `("--control-stack-size" "256MB"
                     "--noinform" "--disable-ldb" "--lose-on-corruption" "--end-runtime-options"
                     "--eval" "(push :child-sbcl *features*)"
                     "--eval" ,(format nil "(progn (compile-file ~S) (quit))" *compile-file-pathname*))
                   :output t :error t :input t)))))
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

(defpackage :cp/segment-tree
  (:use :cl)
  (:export #:define-segtree)
  (:documentation "Provides 1-dimensional segment tree on arbitrary
monoid (bottom-up implementation)."))
(in-package :cp/segment-tree)

(defmacro define-segtree (name &key (operator '#'+) (identity 0) element-type)
  "OPERATOR := binary operator (comprising a monoid)
IDENTITY := object (identity element of the monoid)
ELEMENT-TYPE := type specifier

This macro defines five functions:

- <NAME>-REF: accessor and setter
- <NAME>-FOLD: query function for range sum
- MAKE-<NAME>: linear time constructor
- <NAME>-MAX-RIGHT: binary search w.r.t. range sum in nomal order
- <NAME>-MIN-LEFT: binary search w.r.t. range sum in reverse order"
  (let* ((fname-ref (intern (format nil "~A-REF" (symbol-name name))))
         (fname-fold (intern (format nil "~A-FOLD" (symbol-name name))))
         (fname-max-right (intern (format nil "~A-MAX-RIGHT" (symbol-name name))))
         (fname-min-left (intern (format nil "~A-MIN-LEFT" (symbol-name name))))
         (fname-make (intern (format nil "MAKE-~A" (symbol-name name))))
         (fname-%make (intern (format nil "%MAKE-~A" (symbol-name name))))
         (fname-n (intern (format nil "%~A-N" (symbol-name name))))
         (fname-vector (intern (format nil "%~A-VECTOR" (symbol-name name))))
         (conc-name (intern (format nil "%~A-" (symbol-name name)))))
    `(progn
       (defstruct (,name (:constructor ,fname-%make
                             (vector &aux (n (ash (+ 1 (length vector)) -1))))
                         (:conc-name ,conc-name))
         (n nil :type (integer 0 #.(floor array-total-size-limit 2)))
         (vector nil :type (simple-array ,element-type (*))))
       (declaim (inline ,fname-make))
       (defun ,fname-make (size &key (initial-element ,identity) initial-contents)
         (declare ((mod #.array-total-size-limit) size)
                  ((or null sequence) initial-contents))
         (let ((res (make-array (max 0 (- (* 2 size) 1))
                                :element-type ',element-type
                                :initial-element initial-element)))
           (when initial-contents
             (replace res initial-contents :start1 (max 0 (- size 1))))
           (loop for i from (- size 2) downto 0
                 do (setf (aref res i)
                          (funcall ,operator
                                   (aref res (+ (* 2 i) 1)) (aref res (+ (* 2 i) 2)))))
           (,fname-%make res)))

       (declaim (inline ,fname-ref))
       (defun ,fname-ref (,name index)
         "Returns the element at INDEX."
         (declare ((integer 0 #.most-positive-fixnum) index))
         (aref (,fname-vector ,name)
               (+ index (,fname-n ,name) -1)))

       (declaim (inline (setf ,fname-ref)))
       (defun (setf ,fname-ref) (new-value ,name index)
         (declare ((mod #.array-total-size-limit) index)
                  (,element-type new-value))
         (let* ((vector (,fname-vector ,name))
                (i (+ index (- (,fname-n ,name) 1))))
           (declare ((mod #.array-total-size-limit) i))
           (setf (aref vector i) new-value)
           (loop while (> i 0)
                 do (setq i (ash (- i 1) -1))
                    (setf (aref vector i)
                          (funcall ,operator
                                   (aref vector (+ (* 2 i) 1))
                                   (aref vector (+ (* 2 i) 2)))))
           new-value))

       (declaim (ftype (function * (values ,element-type &optional)) ,fname-fold)
                (inline ,fname-fold))
       (defun ,fname-fold (,name left right)
         "Folds the given half-open range [LEFT, RIGHT)."
         (declare ((mod #.array-total-size-limit) left right))
         (let* ((vector (,fname-vector ,name))
                (l (max 0 (+ left (,fname-n ,name) -1)))
                (r (max 0 (+ right (,fname-n ,name) -1)))
                (lvalue ,identity)
                (rvalue ,identity))
           (declare ((mod #.array-total-size-limit) l r)
                    (,element-type lvalue rvalue))
           (loop while (< l r)
                 when (evenp l)
                 do (setq lvalue (funcall ,operator lvalue (aref vector l)))
                    (incf l)
                 when (evenp r)
                 do (decf r)
                    (setq rvalue (funcall ,operator (aref vector r) rvalue))
                 do (setq l (ash (- l 1) -1)
                          r (ash (- r 1) -1)))
           (funcall ,operator lvalue rvalue)))

       (declaim (ftype (function * (values (mod #.array-total-size-limit) &optional))
                       ,fname-max-right)
                (inline ,fname-max-right))
       (defun ,fname-max-right (,name test &optional (start 0))
         "Returns the rightmost index i that satisfies (FUNCALL TEST <fold of
range [START, i)>). TEST must be monotone.

Note:
- (FUNCALL TEST <identity>) must be true.
- TEST must be monotone in the target range."
         (declare ((mod #.array-total-size-limit) start))
         (assert (funcall test ,identity))
         (assert (<= start (,fname-n ,name)))
         (let* ((n (,fname-n ,name))
                (vector (,fname-vector ,name))
                (size (length vector))
                (l (max 0 (+ start (- n 1))))
                (r size)
                (value ,identity)
                (total-shift 0))
           (declare ((mod #.array-total-size-limit) l r total-shift)
                    (,element-type value))
           (labels ((recur (index)
                      (declare ((mod #.array-total-size-limit) index))
                      (loop while (< index (- n 1))
                            for new-value of-type ,element-type =
                               (funcall ,operator
                                        value
                                        (aref vector (+ 1 (* 2 index))))
                            when (funcall test new-value)
                            do (setq value new-value
                                     index (+ 2 (* 2 index)))
                            else
                            do (setq index (+ 1 (* 2 index))))
                      (return-from ,fname-max-right (- index (- n 1)))))
             (loop until (= l r)
                   when (evenp l)
                   do (let ((new-value (funcall ,operator value (aref vector l))))
                        (declare (,element-type new-value))
                        (unless (funcall test new-value)
                          (recur l))
                        (setq value new-value))
                   do (setq l (ash l -1) ; move to right block if L is even
                            r (ash (- r 1) -1)
                            total-shift (+ total-shift 1)))
             (loop for shift from (- total-shift 1) above 0
                   for r = (- (ash (+ size 1) (- shift)) 1)
                   when (evenp r)
                   do (let ((new-value (funcall ,operator value (aref vector (- r 1)))))
                        (declare (,element-type new-value))
                        (unless (funcall test new-value)
                          (recur (- r 1)))
                        (setq value new-value)))
             n)))

       (declaim (ftype (function * (values (mod #.array-total-size-limit) &optional))
                       ,fname-min-left)
                (inline ,fname-min-left))
       (defun ,fname-min-left (,name test &optional end)
         "Returns the largest index i that satisfies (FUNCALL TEST <fold of range [i,
END)>).

Note:
- (FUNCALL TEST <identity>) must be true.
- TEST must be monotone in the target range."
         (declare ((or null (mod #.array-total-size-limit)) end))
         (assert (funcall test ,identity))
         (assert (or (null end) (<= end (,fname-n ,name))))
         (let* ((n (,fname-n ,name))
                (vector (,fname-vector ,name))
                (l (max 0 (- n 1)))
                (r (max 0 (+ (or end n) (- n 1))))
                (value ,identity)
                (total-shift 0))
           (declare ((mod #.array-total-size-limit) l r total-shift)
                    (,element-type value))
           (labels ((recur (index)
                      (declare ((mod #.array-total-size-limit) index))
                      (loop while (< index (- n 1))
                            for new-value of-type ,element-type =
                               (funcall ,operator
                                        (aref vector (+ 2 (* 2 index)))
                                        value)
                            when (funcall test new-value)
                            do (setq value new-value
                                     index (+ 1 (* 2 index)))
                            else
                            do (setq index (+ 2 (* 2 index))))
                      (return-from ,fname-min-left (+ 1 (- index (- n 1))))))
             (loop until (= l r)
                   when (evenp r)
                   do (let ((new-value (funcall ,operator (aref vector (- r 1)) value)))
                        (declare (,element-type new-value))
                        (unless (funcall test new-value)
                          (recur (- r 1)))
                        (setq value new-value))
                   do (setq l (ash l -1) ; move to right block if L is even
                            r (ash (- r 1) -1)
                            total-shift (+ total-shift 1)))
             (loop for shift from (- total-shift 1) downto 0
                   for l = (ash (- n 1) (- shift))
                   when (evenp l)
                   do (let ((new-value (funcall ,operator (aref vector l) value)))
                        (declare (,element-type new-value))
                        (unless (funcall test new-value)
                          (recur l))
                        (setq value new-value)))
             0))))))

#+(or)
(define-segtree segtree
  :operator #'+
  :identity 0
  :element-type fixnum)

(defpackage :cp/integer-pack
  (:use :cl)
  (:export #:define-integer-pack #:define-cons-pack)
  (:documentation "DEFINE-INTEGER-PACK and DEFINE-CONS-PACK are so to say poor
man's variants of DEFSTRUCT. Both \"structures\" can only have slots of fixed
unsigned bytes. DEFINE-INTEGER-PACK handles the concatenated slots as
UNSIGNED-BYTE and DEFINE-CONS-PACK handles them as (CONS (UNSIGNED-BYTE
62) (UNSIGNED-BYTE 62)).

Example:
The following form defines a type NODE as (UNSIGNED-BYTE 9):

\(define-integer-pack node (slot1 3) (slot2 5) (slot3 1))

This macro in addition defines relevant utilities: NODE-SLOT1, NODE-SLOT2,
NODE-SLOT3, setters and getters, PACK-NODE, a constructor, and
WITH-UNPACKING-NODE, a destructuring-bind-style macro.

DEFINE-CONS-PACK is almost the same as DEFINE-INTEGER-PACK though it will be
suitable for the total bits in the range [63, 124].
"))
(in-package :cp/integer-pack)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun %concat-name (&rest args)
    (if (cdr args)
        (format nil "~A-~A"
                (car args)
                (apply #'%concat-name (cdr args)))
        (car args)))

  (defun %concat+name+ (&rest args)
    (format nil "+~A+" (apply #'%concat-name args))))

(defmacro define-integer-pack (name &rest slot-descriptions)
  (assert slot-descriptions () "~A has no slots." name)
  (let* ((packer-name (intern (%concat-name "PACK" name)))
         (unpacker-macro-name (intern (%concat-name "WITH-UNPACKING" name)))
         (total-size 0)
         (slots (loop with position = 0
                      for (slot-name slot-size) in slot-descriptions
                      collect (progn (check-type slot-name symbol)
                                     (check-type slot-size (integer 1))
                                     (list slot-name slot-size position))
                      do (incf position slot-size)
                      finally (setq total-size position)))
         (revslots (reverse slots))
         (new-value (gensym "NEW-VALUE"))
         (tmp (gensym)))
    `(progn
       (deftype ,name () '(unsigned-byte ,total-size))
       ;; define most positive integer for every slot as constant
       ,@(loop for (slot-name slot-size _) in slots
               collect `(defconstant ,(intern (%concat+name+ "MAX" name slot-name))
                          (- (ash 1 ,slot-size) 1)))
       ;; getter
       ;; TODO: define setter with define-setf-expander
       ,@(loop for (slot-name slot-size slot-position) in slots
               for accessor-name = (intern (%concat-name name slot-name))
               append `((declaim (inline ,accessor-name
                                         (setf ,accessor-name)))
                        (defun ,accessor-name (,name)
                          (declare (type ,name ,name))
                          (ldb (byte ,slot-size ,slot-position) ,name))))
       ;; constructor
       (declaim (inline ,packer-name))
       (defun ,packer-name ,(loop for slot in slots collect (car slot))
         (declare ,@(loop for (slot-name slot-size _) in slots
                          collect `(type (unsigned-byte ,slot-size) ,slot-name )))
         (let ((,tmp ,(caar revslots)))
           (declare (type (unsigned-byte ,total-size) ,tmp))
           ,@(loop for (slot-name slot-size _) in (cdr revslots)
                   collect `(setq ,tmp (logxor ,slot-name
                                               (the (unsigned-byte ,total-size)
                                                    (ash ,tmp ,slot-size)))))
           ,tmp))
       ;; destructuring-bind-style macro
       (defmacro ,unpacker-macro-name (vars ,name &body body)
         (check-type vars list)
         (assert (= (length vars) ,(length slots)))
         `(let ((,',tmp ,,name))
            (declare (type (unsigned-byte ,,total-size) ,',tmp))
            (let* ,(loop for var in vars
                         for rest on ',slots
                         for (slot-name slot-size _) = (car rest)
                         collect `(,var
                                   (prog1 (the (unsigned-byte ,slot-size)
                                               (ldb (byte ,slot-size 0) ,',tmp))
                                     ,@(when (cdr rest)
                                         `((setq ,',tmp (ash ,',tmp ,(- slot-size))))))))
              ,@body))))))

(defmacro define-cons-pack (name &rest slot-descriptions)
  (assert slot-descriptions () "~A has no slots." name)
  (labels ((extract-62bit-slots (list)
             (let ((position 0))
               (loop for (slot-name slot-size) in list
                     while (<= (+ position slot-size) 62)
                     collect (list slot-name slot-size position)
                     do (incf position slot-size)))))
    (let* ((packer-name (intern (%concat-name "PACK" name)))
           (unpacker-macro-name (intern (%concat-name "WITH-UNPACKING" name)))
           (new-value (gensym "NEW-VALUE"))
           (tmp1 (gensym))
           (tmp2 (gensym))
           (tmp (gensym))
           (car-slots (extract-62bit-slots slot-descriptions))
           (car-revslots (reverse car-slots))
           (cdr-slots (extract-62bit-slots (nthcdr (length car-slots) slot-descriptions)))
           (cdr-revslots (reverse cdr-slots))
           (slots (append car-slots cdr-slots)))
      (assert (= (+ (length car-slots) (length cdr-slots))
                 (length slot-descriptions))
              () "Size restriction violated: slot size <= 62 bit and total size <= 124 bit")
      (unless (> (length cdr-slots) 0)
        (error "Total size is too small. Use DEFINE-INTEGER-PACK instead."))
      (let ((car-width (+ (second (first car-revslots))
                          (third (first car-revslots))))
            (cdr-width (+ (second (first cdr-revslots))
                          (third (first cdr-revslots)))))
        `(progn
           (deftype ,name () '(cons (unsigned-byte ,car-width) (unsigned-byte ,cdr-width)))
           ;; define most positive integer for every slot as constant
           ,@(loop for (slot-name slot-size _) in slots
                   collect `(defconstant ,(intern (%concat+name+ "MAX" name slot-name))
                              (- (ash 1 ,slot-size) 1)))
           ;; setter and getter
           ,@(loop for slot in car-slots
                   for (slot-name slot-size slot-position) = slot
                   for accessor-name = (intern (%concat-name name slot-name))
                   append `((declaim (inline ,accessor-name (setf ,accessor-name)))
                            (defun ,accessor-name (,name)
                              (declare (type ,name ,name))
                              (ldb (byte ,slot-size ,slot-position)
                                   (the (unsigned-byte ,car-width) (car ,name))))
                            (defun (setf ,accessor-name) (,new-value ,name)
                              (declare (type ,name ,name))
                              (setf (ldb (byte ,slot-size ,slot-position)
                                         (the (unsigned-byte ,car-width) (car ,name)))
                                    ,new-value))))
           ,@(loop for slot in cdr-slots
                   for (slot-name slot-size slot-position) = slot
                   for accessor-name = (intern (%concat-name name slot-name))
                   append `((declaim (inline ,accessor-name (setf ,accessor-name)))
                            (defun ,accessor-name (,name)
                              (declare (type ,name ,name))
                              (ldb (byte ,slot-size ,slot-position)
                                   (the (unsigned-byte ,cdr-width) (cdr ,name))))
                            (defun (setf ,accessor-name) (,new-value ,name)
                              (declare (type ,name ,name))
                              (setf (ldb (byte ,slot-size ,slot-position)
                                         (the (unsigned-byte ,cdr-width) (cdr ,name)))
                                    ,new-value))))
           ;; constructor
           (declaim (inline ,packer-name))
           (defun ,packer-name ,(loop for slot in slots collect (car slot))
             (declare ,@(loop for (slot-name slot-size slot-position) in slots
                              collect `(type (unsigned-byte ,slot-size) ,slot-name)))
             (let ((,tmp1 ,(caar car-revslots))
                   (,tmp2 ,(caar cdr-revslots)))
               (declare (type (unsigned-byte ,car-width) ,tmp1)
                        (type (unsigned-byte ,cdr-width) ,tmp2))
               ,@(loop for (slot-name slot-size _) in (rest car-revslots)
                       collect `(setq ,tmp1 (logxor ,slot-name
                                                    (the (unsigned-byte ,car-width)
                                                         (ash ,tmp1 ,slot-size)))))
               ,@(loop for (slot-name slot-size _) in (rest cdr-revslots)
                       collect `(setq ,tmp2 (logxor ,slot-name
                                                    (the (unsigned-byte ,cdr-width)
                                                         (ash ,tmp2 ,slot-size)))))
               (cons ,tmp1 ,tmp2)))
           ;; destructuring-bind-style macro
           (defmacro ,unpacker-macro-name (vars ,name &body body)
             (check-type vars list)
             (assert (= (length vars) ,(length slots)))
             `(let* ((,',tmp ,,name)
                     (,',tmp1 (car ,',tmp))
                     (,',tmp2 (cdr ,',tmp)))
                (declare (type (unsigned-byte ,,car-width) ,',tmp1)
                         (type (unsigned-byte ,,cdr-width) ,',tmp2))
                (let* ,(loop for var in vars
                             for rest on ',car-slots
                             for (slot-name slot-size _) = (car rest)
                             collect `(,var
                                       (prog1 (the (unsigned-byte ,slot-size)
                                                   (ldb (byte ,slot-size 0) ,',tmp1))
                                         ,@(when (cdr rest)
                                             `((setq ,',tmp1 (ash ,',tmp1 ,(- slot-size))))))))
                  (let* ,(loop for var in (nthcdr ,(length car-slots) vars)
                               for rest on ',cdr-slots
                               for (slot-name slot-size _) = (car rest)
                               collect `(,var
                                         (prog1 (the (unsigned-byte ,slot-size)
                                                     (ldb (byte ,slot-size 0) ,',tmp2))
                                           ,@(when (cdr rest)
                                               `((setq ,',tmp2 (ash ,',tmp2 ,(- slot-size))))))))
                    ,@body)))))))))

;; Treap accessible by index (O(log(n)))
;; Virtually it works like std::set of C++ or TreeSet of Java. 

;; Note:
;; - You shouldn't insert duplicate keys into a treap unless you know what you
;; are doing.
;; - You cannot rely on the side effect when you call any destructive operations
;; on a treap. Always use the returned value.
;; - An empty treap is NIL.

;; TODO: abstraction

(defpackage :cp/ref-able-treap
  (:use :cl)
  (:export #:treap #:treap-count #:treap-find #:treap-position #:treap-bisect-left
           #:treap-split #:treap-insert #:treap-push #:treap-pop #:make-treap
           #:treap-delete #:treap-merge #:treap-map #:invalid-treap-index-error
           #:treap-ref #:treap-first #:treap-last #:treap-unite #:treap-reverse))
(in-package :cp/ref-able-treap)

(defstruct (treap (:constructor %make-treap (key priority &key left right (count 1)))
                  (:copier nil)
                  (:conc-name %treap-))
  (key 0 :type fixnum)
  (priority 0 :type (integer 0 #.most-positive-fixnum))
  (count 0 :type (integer 0 #.most-positive-fixnum))
  (left nil :type (or null treap))
  (right nil :type (or null treap)))

(declaim (inline treap-count))
(defun treap-count (treap)
  "Returns the size of the (nullable) TREAP."
  (declare ((or null treap) treap))
  (if (null treap)
      0
      (%treap-count treap)))

(declaim (inline update-count))
(defun update-count (treap)
  (declare (treap treap))
  (setf (%treap-count treap)
        (+ 1
           (treap-count (%treap-left treap))
           (treap-count (%treap-right treap)))))

(declaim (inline treap-find))
(defun treap-find (key treap &key (order #'<))
  "Returns KEY if TREAP contains it, otherwise NIL.

An element in TREAP is considered to be equal to KEY iff (and (not (funcall
order key <element>)) (not (funcall order <element> key))) is true."
  (declare ((or null treap) treap))
  (labels ((recur (treap)
             (cond ((null treap) nil)
                   ((funcall order key (%treap-key treap))
                    (recur (%treap-left treap)))
                   ((funcall order (%treap-key treap) key)
                    (recur (%treap-right treap)))
                   (t key))))
    (recur treap)))

(declaim (inline treap-position))
(defun treap-position (key treap &key (order #'<))
  "Returns the index if TREAP contains KEY, otherwise NIL.

An element in TREAP is considered to be equal to KEY iff (and (not (funcall
order key <element>)) (not (funcall order <element> key))) is true."
  (declare ((or null treap) treap))
  (labels ((recur (count treap)
             (declare ((integer 0 #.most-positive-fixnum) count))
             (cond ((null treap) nil)
                   ((funcall order (%treap-key treap) key)
                    (recur count (%treap-right treap)))
                   ((funcall order key (%treap-key treap))
                    (let ((left-count (- count (treap-count (%treap-right treap)) 1)))
                      (recur left-count (%treap-left treap))))
                   (t (- count (treap-count (%treap-right treap)) 1)))))
    (recur (treap-count treap) treap)))

(declaim (inline treap-bisect-left)
         (ftype (function * (values (integer 0 #.most-positive-fixnum) t &optional)) treap-bisect-left))
(defun treap-bisect-left (value treap &key (order #'<))
  "Returns two values: the smallest index and the corresponding key that
satisfies TREAP[index] >= VALUE. Returns the size of TREAP and VALUE instead if
TREAP[size-1] < VALUE."
  (labels ((recur (count treap)
             (declare ((integer 0 #.most-positive-fixnum) count))
             (cond ((null treap) (values nil nil))
                   ((funcall order (%treap-key treap) value)
                    (recur count (%treap-right treap)))
                   (t (let ((left-count (- count (treap-count (%treap-right treap)) 1)))
                        (multiple-value-bind (idx key)
                            (recur left-count (%treap-left treap))
                          (if idx
                              (values idx key)
                              (values left-count (%treap-key treap)))))))))
    (declare (ftype (function * (values t t &optional)) recur))
    (multiple-value-bind (idx key)
        (recur (treap-count treap) treap)
      (if idx
          (values idx key)
          (values (treap-count treap) value)))))

(declaim (inline treap-split)
         (ftype (function * (values (or null treap) (or null treap) &optional)) treap-split))
(defun treap-split (key treap &key (order #'<))
  "Destructively splits TREAP with reference to KEY and returns two treaps,
the smaller sub-treap (< KEY) and the larger one (>= KEY)."
  (declare ((or null treap) treap))
  (labels ((recur (treap)
             (cond ((null treap)
                    (values nil nil))
                   ((funcall order (%treap-key treap) key)
                    (multiple-value-bind (left right) (recur (%treap-right treap))
                      (setf (%treap-right treap) left)
                      (update-count treap)
                      (values treap right)))
                   (t
                    (multiple-value-bind (left right) (recur (%treap-left treap))
                      (setf (%treap-left treap) right)
                      (update-count treap)
                      (values left treap))))))
    (recur treap)))

(declaim (inline treap-insert))
(defun treap-insert (key treap &key (order #'<))
  "Destructively inserts KEY into TREAP and returns the resultant treap."
  (declare ((or null treap) treap))
  (let ((node (%make-treap key (random most-positive-fixnum))))
    (labels ((recur (treap)
               (declare (treap node))
               (cond ((null treap) node)
                     ((> (%treap-priority node) (%treap-priority treap))
                      (setf (values (%treap-left node) (%treap-right node))
                            (treap-split (%treap-key node) treap :order order))
                      (update-count node)
                      node)
                     (t
                      (if (funcall order (%treap-key node) (%treap-key treap))
                          (setf (%treap-left treap)
                                (recur (%treap-left treap)))
                          (setf (%treap-right treap)
                                (recur (%treap-right treap))))
                      (update-count treap)
                      treap))))
      (recur treap))))

(defmacro treap-push (key treap &optional (order '#'<))
  "Pushes a KEY to TREAP."
  `(setf ,treap (treap-insert ,key ,treap :order ,order)))

(defmacro treap-pop (key treap &optional (order '#'<))
  "Deletes a KEY from TREAP."
  `(setf ,treap (treap-delete ,key ,treap :order ,order)))

;; NOTE: It takes O(nlog(n)).
(defun treap (order &rest keys)
  (loop with res = nil
        for key in keys
        do (setf res (treap-insert key res :order order))
        finally (return res)))

;; Reference: https://cp-algorithms.com/data_structures/treap.html
(declaim (inline make-treap))
(defun make-treap (sorted-vector)
  "Makes a treap from the given SORTED-VECTOR in O(n) time. Note that this
function doesn't check if the SORTED-VECTOR is actually sorted w.r.t. your
intended order. The consequence is undefined when a non-sorted vector is
given."
  (declare (vector sorted-vector))
  (labels ((heapify (top)
             (when top
               (let ((prioritized-node top))
                 (when (and (%treap-left top)
                            (> (%treap-priority (%treap-left top))
                               (%treap-priority prioritized-node)))
                   (setq prioritized-node (%treap-left top)))
                 (when (and (%treap-right top)
                            (> (%treap-priority (%treap-right top))
                               (%treap-priority prioritized-node)))
                   (setq prioritized-node (%treap-right top)))
                 (unless (eql prioritized-node top)
                   (rotatef (%treap-priority prioritized-node)
                            (%treap-priority top))
                   (heapify prioritized-node)))))
           (build (l r)
             (declare ((integer 0 #.most-positive-fixnum) l r))
             (if (= l r)
                 nil
                 (let* ((mid (ash (+ l r) -1))
                        (node (%make-treap (aref sorted-vector mid)
                                           (random most-positive-fixnum))))
                   (setf (%treap-left node) (build l mid))
                   (setf (%treap-right node) (build (+ mid 1) r))
                   (heapify node)
                   (update-count node)
                   node))))
    (build 0 (length sorted-vector))))

(declaim (ftype (function * (values (or null treap) &optional)) treap-merge))
(defun treap-merge (left right)
  "Destructively concatenates two treaps. Assumes that all keys of LEFT are
smaller (or larger, depending on the order) than those of RIGHT.

Note that this `merge' is different from CL:MERGE and rather close to
CL:CONCATENATE. (TREAP-UNITE is the analogue of the former.)"
  (declare (optimize (speed 3))
           ((or null treap) left right))
  (cond ((null left) right)
        ((null right) left)
        ((> (%treap-priority left) (%treap-priority right))
         (setf (%treap-right left)
               (treap-merge (%treap-right left) right))
         (update-count left)
         left)
        (t
         (setf (%treap-left right)
               (treap-merge left (%treap-left right)))
         (update-count right)
         right)))

(declaim (inline treap-delete))
(defun treap-delete (key treap &key (order #'<))
  "Destructively deletes KEY in TREAP and returns the resultant treap."
  (declare ((or null treap) treap))
  (labels ((recur (treap)
             (cond ((null treap) nil)
                   ((funcall order key (%treap-key treap))
                    (setf (%treap-left treap) (recur (%treap-left treap)))
                    (update-count treap)
                    treap)
                   ((funcall order (%treap-key treap) key)
                    (setf (%treap-right treap) (recur (%treap-right treap)))
                    (update-count treap)
                    treap)
                   (t
                    (treap-merge (%treap-left treap) (%treap-right treap))))))
    (declare (ftype (function * (values (or null treap) &optional)) recur))
    (recur treap)))

(declaim (inline treap-map))
(defun treap-map (function treap)
  "Successively applies FUNCTION to TREAP[0], ..., TREAP[SIZE-1]. FUNCTION must
take one argument."
  (declare (function function))
  (labels ((recur (treap)
             (when treap
               (recur (%treap-left treap))
               (funcall function (%treap-key treap))
               (recur (%treap-right treap)))))
    (recur treap)))

(defmethod print-object ((object treap) stream)
  (print-unreadable-object (object stream :type t)
    (let ((init t))
      (treap-map (lambda (key)
                   (if init
                       (setq init nil)
                       (write-char #\  stream))
                   (write key :stream stream))
                 object))))

(define-condition invalid-treap-index-error (type-error)
  ((treap :initarg :treap :reader invalid-treap-index-error-treap)
   (index :initarg :index :reader invalid-treap-index-error-index))
  (:report
   (lambda (condition stream)
     (format stream "Invalid index ~W for treap ~W."
             (invalid-treap-index-error-index condition)
             (invalid-treap-index-error-treap condition)))))

(defun treap-ref (treap index)
  "Returns the INDEX-th element of TREAP."
  (declare (optimize (speed 3))
           ((or null treap) treap)
           ((integer 0 #.most-positive-fixnum) index))
  (when (>= index (treap-count treap))
    (error 'invalid-treap-index-error :treap treap :index index))
  (labels ((%ref (treap index)
             (declare (optimize (speed 3) (safety 0))
                      ((integer 0 #.most-positive-fixnum) index))
             (let ((left-count (treap-count (%treap-left treap))))
               (cond ((< index left-count)
                      (%ref (%treap-left treap) index))
                     ((> index left-count)
                      (%ref (%treap-right treap) (- index left-count 1)))
                     (t (%treap-key treap))))))
    (%ref treap index)))

(defun treap-first (treap)
  (declare (optimize (speed 3))
           (treap treap))
  (if (%treap-left treap)
      (treap-first (%treap-left treap))
      (%treap-key treap)))

(defun treap-last (treap)
  (declare (optimize (speed 3))
           (treap treap))
  (if (%treap-right treap)
      (treap-last (%treap-right treap))
      (%treap-key treap)))

(declaim (inline treap-unite))
(defun treap-unite (treap1 treap2 &key (order #'<))
  "Merges two treaps with keeping the order."
  (labels
      ((recur (l r)
         (cond ((null l) r)
               ((null r) l)
               (t (when (< (%treap-priority l) (%treap-priority r))
                    (rotatef l r))
                  (multiple-value-bind (lchild rchild)
                      ;; FIXME: To omit duplicate keys, this TREAP-SPLIT should
                      ;; be replaced by something like TREAP-EXCLUSIVE-SPLIT.
                      (treap-split (%treap-key l) r :order order)
                    (setf (%treap-left l) (recur (%treap-left l) lchild)
                          (%treap-right l) (recur (%treap-right l) rchild))
                    (update-count l)
                    l)))))
    (recur treap1 treap2)))

(declaim (inline treap-reverse))
(defun treap-reverse (treap)
  "Destructively reverses the order of the whole treap."
  (labels ((recur (treap)
             (when treap
               (let ((left (recur (%treap-left treap)))
                     (right (recur (%treap-right treap))))
                 (setf (%treap-left treap) right
                       (%treap-right treap) left)
                 treap))))
    (recur treap)))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/ref-able-treap :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/integer-pack :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/segment-tree :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(define-integer-pack node (x 31) (count 31))

(defun %merge (node1 node2)
  (declare #.*opt*
           (node node1 node2))
  (with-unpacking-node (x1 c1) node1
    (with-unpacking-node (x2 c2) node2
      (cond ((= x1 x2) (pack-node x1 (+ c1 c2)))
            ((>= c1 c2) (pack-node x1 (- c1 c2)))
            (t (pack-node x2 (- c2 c1)))))))

(defconstant +identity+ 0)

(define-segtree segtree
  :operator #'%merge
  :identity 0
  :element-type node)

(defun main ()
  (declare #.*opt*)
  (let* ((n (read))
         (q (read))
         (n* (- (* 2 n) 1))
         (as (make-array n :element-type 'uint31 :initial-element 0))
         (nodes (make-array n :element-type 'node))
         (treaps (make-hash-table :test #'eq)))
    (declare (uint31 n q))
    (dotimes (i n)
      (let ((a (read-fixnum)))
        (setf (aref as i) a
              (aref nodes i) (pack-node a 1))
        (treap-push i (gethash a treaps))))
    (let ((dp (make-segtree n :initial-contents nodes)))
      #>dp
      (write-string
       (with-output-to-string (*standard-output* nil :element-type 'base-char)
         (dotimes (_ q)
           (ecase (read-fixnum)
             (1 (let* ((x (- (read-fixnum) 1))
                       (y (read-fixnum))
                       (prev (aref as x)))
                  (setf (aref as x) y)
                  (treap-pop x (gethash prev treaps))
                  (treap-push x (gethash y treaps))
                  (setf (segtree-ref dp x) (pack-node y 1))))
             (2 (let* ((l (- (read-fixnum) 1))
                       (r (read-fixnum))
                       (dom (node-x (segtree-fold dp l r)))
                       (treap (gethash dom treaps))
                       (lo (treap-bisect-left l treap))
                       (hi (treap-bisect-left r treap)))
                  (write-line
                   (if (> (- hi lo) (ash (- r l) -1))
                       "Yes"
                       "No")))))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/CHEFLKJ"))

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
