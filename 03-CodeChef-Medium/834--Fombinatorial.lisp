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

(defpackage :cp/tzcount
  (:use :cl)
  (:export #:tzcount))
(in-package :cp/tzcount)

(declaim (inline tzcount))
(defun tzcount (x)
  "Returns the number of trailing zero bits. Note that (TZCOUNT 0) = -1."
  (- (integer-length (logand x (- x))) 1))

(defpackage :cp/pfactors-table
  (:use :cl :cp/tzcount)
  (:export #:make-pfactors-table))
(in-package :cp/pfactors-table)

(declaim (ftype (function * (values (simple-array list (*)) &optional))
                make-pfactors-table))
(defun make-pfactors-table (sup)
  (declare (optimize (speed 3))
           ((mod #.array-total-size-limit) sup))
  (let ((result (make-array sup :element-type 'list :initial-element nil))
        (dp (make-array sup :element-type '(integer 0 #.most-positive-fixnum))))
    (dotimes (i sup)
      (setf (aref dp i) i))
    (loop for x from 2 below sup by 2
          for exp = (tzcount x)
          do (setf (aref dp x) (ash (aref dp x) (- exp)))
             (push (cons 2 exp) (aref result x)))
    (loop for p from 3 below sup by 2
          unless (= 1 (aref dp p))
          do (loop for x from p below sup by p
                   for num of-type (integer 0 #.most-positive-fixnum) = (aref dp x)
                   do (loop for exp of-type (integer 0 #.most-positive-fixnum) from 0
                            do (multiple-value-bind (quot rem) (floor num p)
                                 (unless (zerop rem)
                                   (push (cons p exp) (aref result x))
                                   (setf (aref dp x) num)
                                   (return))
                                 (setq num quot)))))
    (dotimes (x sup)
      (setf (aref result x) (nreverse (aref result x))))
    result))

(defpackage :cp/mod-power
  (:use :cl)
  (:export #:mod-power))
(in-package :cp/mod-power)

(declaim (inline mod-power))
(defun mod-power (base power modulus)
  "Returns BASE^POWER mod MODULUS. Note: 0^0 = 1.

BASE := integer
POWER, MODULUS := non-negative fixnum"
  (declare ((integer 0 #.most-positive-fixnum) modulus power)
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


;;;
;;; Arithmetic operations with dynamic modulus
;;;

(defpackage :cp/dynamic-mod-operations
  (:use :cl)
  (:export #:*modulus* #:mod* #:mod+ #:incfmod #:decfmod #:mulfmod))
(in-package :cp/dynamic-mod-operations)

;; NOTE: Currently MOD* and MOD+ doesn't apply MOD when the number of
;; parameters is one. For simplicity I won't fix it for now.

(sb-ext:define-load-time-global *modulus* cl-user::+mod+)
(declaim ((unsigned-byte 31) *modulus*))

(defun mod* (&rest args)
  (cond ((cdr args) (reduce (lambda (x y) (mod (* x y) *modulus*)) args))
        (args (mod (car args) *modulus*))
        (t 1)))

(defun mod+ (&rest args)
  (cond ((cdr args) (reduce (lambda (x y) (mod (+ x y) *modulus*)) args))
        (args (mod (car args) *modulus*))
        (t 0)))

#+sbcl
(eval-when (:compile-toplevel :load-toplevel :execute)
  (locally (declare (sb-ext:muffle-conditions warning))
    (sb-c:define-source-transform mod* (&rest args)
      (case (length args)
        (0 1)
        (1 `(mod ,(car args) *modulus*))
        (otherwise (reduce (lambda (x y) `(mod (* ,x ,y) *modulus*)) args))))
    (sb-c:define-source-transform mod+ (&rest args)
      (case (length args)
        (0 0)
        (1 `(mod ,(car args) *modulus*))
        (otherwise (reduce (lambda (x y) `(mod (+ ,x ,y) *modulus*)) args))))))

(define-modify-macro incfmod (delta &optional (divisor '*modulus*))
  (lambda (x y divisor) (mod (+ x y) divisor)))

(define-modify-macro decfmod (delta &optional (divisor '*modulus*))
  (lambda (x y divisor) (mod (- x y) divisor)))

(define-modify-macro mulfmod (delta &optional (divisor '*modulus*))
  (lambda (x y divisor) (mod (* x y) divisor)))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/segment-tree :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/dynamic-mod-operations :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/mod-power :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/pfactors-table :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))

(in-package :cl-user)

;;;
;;; Body
;;;

(define-segtree segtree
  :operator #'mod*
  :identity 1
  :element-type uint31)

(defun main ()
  (declare #.*opt*)
  (let ((tt (read))
        (pfactors (make-pfactors-table 100001))
        (pords (make-array 100001 :element-type 'uint31 :initial-element 0))
        (end 0))
    (loop for x from 2 below (length pfactors)
          for ps = (aref pfactors x)
          when (and (= (length ps) 1)
                    (= 1 (cdar ps)))
          do (setf (aref pords x) end)
             (incf end))
    #>end
    (let ((dp (make-segtree end)))
      (write-string
       (with-output-to-string (*standard-output* nil :element-type 'base-char)
         (dotimes (_ tt)
           (let* ((n (read-fixnum))
                  (m (read-fixnum))
                  (q (read-fixnum))
                  (counter (make-hash-table :test #'eq))
                  (res (make-array n :element-type 'uint31 :initial-element 0)))
             (declare (uint31 n m q))
             (setq *modulus* m)
             (setf (aref res 0) 1)
             (loop for x from 1 below n
                   do (loop for (p . exp) of-type (uint31 . uint8) in (aref pfactors (+ 1 (- n x)))
                            for pidx = (aref pords p)
                            do (incf (the fixnum (gethash pidx counter 0))
                                     (* exp (+ 1 (- n x))))
                               (setf (segtree-ref dp pidx)
                                     (mod-power p (gethash pidx counter 0) m)))
                      (loop for (p . exp) of-type (uint31 . uint8) in (aref pfactors x)
                            for pidx = (aref pords p)
                            do (dbg pidx p)
                               (when (zerop (decf (the fixnum (gethash pidx counter))
                                                  (* exp x)))
                                 (remhash pidx counter))
                               (setf (segtree-ref dp pidx)
                                     (mod-power p (gethash pidx counter 0) m)))
                      (setf (aref res x) (segtree-fold dp 0 end)))
             (dotimes (_ q)
               (let ((r (read-fixnum)))
                 (println (aref res r))))
             (loop for pidx being each hash-key of counter
                   do (setf (segtree-ref dp pidx) 1)))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/POWERMUL"))

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
