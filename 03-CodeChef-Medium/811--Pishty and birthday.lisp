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
(defpackage :cp/tzcount
  (:use :cl)
  (:export #:tzcount))
(in-package :cp/tzcount)

(declaim (inline tzcount))
(defun tzcount (x)
  "Returns the number of trailing zero bits. Note that (TZCOUNT 0) = -1."
  (- (integer-length (logand x (- x))) 1))

(defpackage :cp/read-schar
  (:use :cl)
  (:export #:read-schar))
(in-package :cp/read-schar)

(declaim (inline read-schar))
(defun read-schar (&optional (stream *standard-input*))
  (declare #-swank (sb-kernel:ansi-stream stream)
           (inline read-byte))
  #+swank (read-char stream nil #\Newline) ; on SLIME
  #-swank (code-char (read-byte stream nil #.(char-code #\Newline))))

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

;;;
;;; 1-dimensional binary indexed tree on arbitrary commutative monoid
;;;

(defpackage :cp/binary-indexed-tree
  (:use :cl)
  (:export #:define-bitree))
(in-package :cp/binary-indexed-tree)

(defmacro define-bitree (name &key (operator '#'+) (identity 0) sum-type (order '#'<))
  "OPERATOR := binary operator (comprising a commutative monoid)
IDENTITY := object (identity element of the monoid)
ORDER := nil | strict comparison operator on the monoid
SUM-TYPE := nil | type specifier

Defines no structure; BIT is just a vector. This macro defines the three
functions: <NAME>-UPDATE!, point-update function, <NAME>-FOLD, query function for
prefix sum, and COERCE-TO-<NAME>!, constructor. If ORDER is specified, this
macro in addition defines <NAME>-BISECT-LEFT and <NAME>-BISECT-RIGHT, the
bisection functions for prefix sums. (Note that these functions work only when
the sequence of prefix sums (VECTOR[0], VECTOR[0]+VECTOR[1], ...) is monotone.)

SUM-TYPE is used only for the type declaration: each sum
VECTOR[i]+VECTOR[i+1]...+VECTOR[i+k] is declared to be this type. When SUM-TYPE
is NIL, type declaration is omitted. (The array-element-type of vector itself
doesn't need to be identical to SUM-TYPE.)"
  (let* ((name (string name))
         (fname-update (intern (format nil "~A-UPDATE!" name)))
         (fname-fold (intern (format nil "~A-FOLD" name)))
         (fname-build (intern (format nil "~A-BUILD!" name)))
         (fname-bisect-left (intern (format nil "~A-BISECT-LEFT" name)))
         (fname-bisect-right (intern (format nil "~A-BISECT-RIGHT" name))))
    `(progn
       (declaim (inline ,fname-update))
       (defun ,fname-update (bitree index delta)
         "Destructively increments the vector: vector[INDEX] = vector[INDEX] +
DELTA"
         (let ((len (length bitree)))
           (do ((i index (logior i (+ i 1))))
               ((>= i len) bitree)
             (declare ((integer 0 #.most-positive-fixnum) i))
             (setf (aref bitree i)
                   (funcall ,operator (aref bitree i) delta)))))

       (declaim (inline ,fname-fold))
       (defun ,fname-fold (bitree end)
         "Returns the sum of the prefix: vector[0] + ... + vector[END-1]."
         (declare ((integer 0 #.most-positive-fixnum) end))
         (let ((res ,identity))
           ,@(when sum-type `((declare (type ,sum-type res))))
           (do ((i (- end 1) (- (logand i (+ i 1)) 1)))
               ((< i 0) res)
             (declare ((integer -1 #.most-positive-fixnum) i))
             (setf res (funcall ,operator res (aref bitree i))))))

       (declaim (inline ,fname-build))
       (defun ,fname-build (vector)
         "Destructively constructs BIT from VECTOR. (You doesn't need to call
this constructor if what you need is a `zero-filled' BIT, because a vector
filled with the identity element is a valid BIT as it is.)"
         (loop with len = (length vector)
               for i below len
               for dest-i = (logior i (+ i 1))
               when (< dest-i len)
               do (setf (aref vector dest-i)
                        (funcall ,operator (aref vector dest-i) (aref vector i)))
               finally (return vector)))

       ,@(when order
           `((declaim (inline ,fname-bisect-left))
             (defun ,fname-bisect-left (bitree value)
               "Returns the smallest index that satisfies VECTOR[0]+ ... +
VECTOR[index] >= VALUE. Returns the length of VECTOR if VECTOR[0]+
... +VECTOR[length-1] < VALUE. Note that this function deals with a **closed**
interval."
               (declare (vector bitree))
               (if (not (funcall ,order ,identity value))
                   0
                   (let ((len (length bitree))
                         (index+1 0)
                         (cumul ,identity))
                     (declare ((integer 0 #.most-positive-fixnum) index+1)
                              ,@(when sum-type
                                  `((type ,sum-type cumul))))
                     (do ((delta (ash 1 (- (integer-length len) 1))
                                 (ash delta -1)))
                         ((zerop delta) index+1)
                       (declare ((integer 0 #.most-positive-fixnum) delta))
                       (let ((next-index (+ index+1 delta -1)))
                         (when (< next-index len)
                           (let ((next-cumul (funcall ,operator cumul (aref bitree next-index))))
                             ,@(when sum-type
                                 `((declare (type ,sum-type next-cumul))))
                             (when (funcall ,order next-cumul value)
                               (setf cumul next-cumul)
                               (incf index+1 delta)))))))))
             (declaim (inline ,fname-bisect-right))
             (defun ,fname-bisect-right (bitree value)
               "Returns the smallest index that satisfies VECTOR[0]+ ... +
VECTOR[index] > VALUE. Returns the length of VECTOR if VECTOR[0]+
... +VECTOR[length-1] <= VALUE. Note that this function deals with a **closed**
interval."
               (declare (vector bitree))
               (if (funcall ,order value ,identity)
                   0
                   (let ((len (length bitree))
                         (index+1 0)
                         (cumul ,identity))
                     (declare ((integer 0 #.most-positive-fixnum) index+1)
                              ,@(when sum-type
                                  `((type ,sum-type cumul))))
                     (do ((delta (ash 1 (- (integer-length len) 1))
                                 (ash delta -1)))
                         ((zerop delta) index+1)
                       (declare ((integer 0 #.most-positive-fixnum) delta))
                       (let ((next-index (+ index+1 delta -1)))
                         (when (< next-index len)
                           (let ((next-cumul (funcall ,operator cumul (aref bitree next-index))))
                             ,@(when sum-type
                                 `((declare (type ,sum-type next-cumul))))
                             (unless (funcall ,order value next-cumul)
                               (setf cumul next-cumul)
                               (incf index+1 delta))))))))))))))

#+(or)
(define-bitree bitree
  :operator #'+
  :identity 0
  :sum-type fixnum
  :order #'<)

(defpackage :cp/read-schar-until
  (:use :cl :cp/read-schar)
  (:export #:read-schar-until))
(in-package :cp/read-schar-until)

(declaim (inline read-schar-until))
(defun read-schar-until (predicate &optional (stream *standard-input*))
  (loop for c = (read-schar stream)
        until (funcall predicate c)
        finally (return c)))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-schar-until :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/binary-indexed-tree :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-fixnum :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/read-schar :cl-user))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/tzcount :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(define-bitree bitree
  :operator #'logxor
  :identity 0
  :sum-type uint8)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (declaim (ftype (function * (values (simple-array uint8 (*)) &optional)) make))
  (defun make ()
    (declare #.*opt*)
    (let ((bitsets (make-array (ash 1 16) :element-type 'uint62 :initial-element 0))
          (mexs (make-array (ash 1 16) :element-type 'uint8 :initial-element 0)))
      (dotimes (board (ash 1 16))
        (let ((mex (tzcount (+ 1 (aref bitsets board)))))
          (setf (aref mexs board) mex)
          (dotimes (x 4)
            (dotimes (y 4)
              (loop for wx from 1 to (- 4 x)
                    do (loop for wy from 1 to (- 4 y)
                             for new-board of-type uint62 = board
                             when (loop named outer
                                        for i from x below (+ x wx)
                                        do (loop for j from y below (+ y wy)
                                                 for index = (+ j (* i 4))
                                                 when (logbitp index board)
                                                 do (return-from outer nil)
                                                 do (setf (ldb (byte 1 index) new-board) 1))
                                        finally (return-from outer t))
                             do (setf (ldb (byte 1 mex) (aref bitsets new-board))
                                      1)))))))
      mexs)))

(defun %read-board ()
  (declare #.*opt*
           (inline digit-char-p))
  (let ((res 0))
    (declare (uint31 res))
    (dotimes (i 4)
      (dotimes (j 4 (read-schar))
        (let ((bit (- (char-code (read-schar-until #'digit-char-p))
                      48)))
          (setq res (logxor (ash res 1) bit)))))
    res))

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read))
         (mexs #.(make)))
    (dotimes (_ tt)
      (let* ((n (read))
             (m (read))
             (vec (make-array n :element-type 'uint8 :initial-element 0)))
        (declare (uint31 n m))
        (dotimes (i n)
          (setf (aref vec i)
                (aref mexs (%read-board))))
        (let ((dp (copy-seq vec)))
          (bitree-build! dp)
          (write-string
           (with-output-to-string (*standard-output* nil :element-type 'base-char)
             (dotimes (_ m)
               (ecase (read-fixnum)
                 (1 (let ((l (- (read-fixnum) 1))
                          (r (read-fixnum)))
                      (write-line
                       (if (zerop (logxor (bitree-fold dp r)
                                          (bitree-fold dp l)))
                           "Lotsy"
                           "Pishty"))))
                 (2 (let ((pos (- (read-fixnum) 1))
                          (mex (aref mexs (%read-board))))
                      (bitree-update! dp
                                      pos
                                      (logxor mex (aref vec pos)))
                      (setf (aref vec pos) mex))))))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/PSHTBRTH"))

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
