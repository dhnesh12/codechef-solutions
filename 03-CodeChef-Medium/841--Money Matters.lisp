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
;;; Memoization macro
;;;

(defpackage :cp/with-cache
  (:use :cl)
  (:export #:with-cache #:with-caches))
(in-package :cp/with-cache)

;; FIXME: *RECURSION-DEPTH* should be included within the macro.
(declaim (type (integer 0 #.most-positive-fixnum) *recursion-depth*))
(defparameter *recursion-depth* 0)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun %enclose-with-trace (fname args form)
    (let ((value (gensym)))
      `(progn
         (format t "~&~A~A: (~A ~{~A~^ ~}) =>"
                 (make-string *recursion-depth*
                              :element-type 'base-char
                              :initial-element #\ )
                 *recursion-depth*
                 ',fname
                 (list ,@args))
         (let ((,value (let ((*recursion-depth* (1+ *recursion-depth*)))
                         ,form)))
           (format t "~&~A~A: (~A ~{~A~^ ~}) => ~A"
                   (make-string *recursion-depth*
                                :element-type 'base-char
                                :initial-element #\ )
                   *recursion-depth*
                   ',fname
                   (list ,@args)
                   ,value)
           ,value))))

  (defun %extract-declarations (body)
    (remove-if-not (lambda (form) (and (consp form) (eql 'declare (car form))))
                   body))

  (defun %parse-cache-form (cache-specifier)
    (let ((cache-type (car cache-specifier))
          (cache-attribs (cdr cache-specifier)))
      (assert (member cache-type '(:hash-table :array)))
      (let* ((dims-with-* (when (eql cache-type :array) (first cache-attribs)))
             (dims (remove '* dims-with-*))
             (rank (length dims))
             (rest-attribs (ecase cache-type
                             (:hash-table cache-attribs)
                             (:array (cdr cache-attribs))))
             (key (prog1 (getf rest-attribs :key) (remf rest-attribs :key)))
             (trace-p (prog1 (getf rest-attribs :trace) (remf rest-attribs :trace)))
             (cache-form (case cache-type
                           (:hash-table `(make-hash-table ,@rest-attribs))
                           (:array `(make-array (list ,@dims) ,@rest-attribs))))
             (initial-element (when (eql cache-type :array)
                                (assert (member :initial-element rest-attribs))
                                (getf rest-attribs :initial-element))))
        (let ((cache (gensym "CACHE"))
              (value (gensym))
              (present-p (gensym))
              (args-lst (gensym))
              (indices (loop repeat rank collect (gensym))))
          (labels
              ((make-cache-querier (cache-type name args)
                 (let ((res (case cache-type
                              (:hash-table
                               `(let ((,args-lst (funcall ,(or key '#'list) ,@args)))
                                  (multiple-value-bind (,value ,present-p)
                                      (gethash ,args-lst ,cache)
                                    (if ,present-p
                                        ,value
                                        (setf (gethash ,args-lst ,cache)
                                              (,name ,@args))))))
                              (:array
                               (assert (= (length args) (length dims-with-*)))
                               (let ((memoized-args (loop for dimension in dims-with-*
                                                          for arg in args
                                                          unless (eql dimension '*)
                                                          collect arg)))
                                 (if key
                                     `(multiple-value-bind ,indices
                                          (funcall ,key ,@memoized-args)
                                        (let ((,value (aref ,cache ,@indices)))
                                          (if (eql ,initial-element ,value)
                                              (setf (aref ,cache ,@indices)
                                                    (,name ,@args))
                                              ,value)))
                                     `(let ((,value (aref ,cache ,@memoized-args)))
                                        (if (eql ,initial-element ,value)
                                            (setf (aref ,cache ,@memoized-args)
                                                  (,name ,@args))
                                            ,value))))))))
                   (if trace-p
                       (%enclose-with-trace name args res)
                       res)))
               (make-reset-form (cache-type)
                 (case cache-type
                   (:hash-table `(setf ,cache (make-hash-table ,@rest-attribs)))
                   (:array `(prog1 nil
                              ;; TODO: portable fill
                              (fill (sb-ext:array-storage-vector ,cache) ,initial-element)))))
               (make-reset-name (name)
                 (intern (format nil "RESET-~A" (symbol-name name)))))
            (values cache cache-form cache-type
                    #'make-reset-name
                    #'make-reset-form
                    #'make-cache-querier)))))))

(defmacro with-cache ((cache-type &rest cache-attribs) def-form)
  "CACHE-TYPE := :HASH-TABLE | :ARRAY.
DEF-FORM := definition form with DEFUN, LABELS, FLET, or SB-INT:NAMED-LET.

Basic usage:

\(with-cache (:hash-table :test #'equal :key #'cons)
  (defun add (a b)
    (+ a b)))

This function caches the returned values for already passed combinations of
arguments. In this case ADD stores the key (CONS A B) and the returned value to
a hash-table when (ADD A B) is evaluated for the first time. When it is called
with the same arguments (w.r.t. EQUAL) again, ADD will return the stored value
instead of recomputing it.

The storage for cache can be hash-table or array. Let's see an example for
array:

\(with-cache (:array (10 20 30) :initial-element -1 :element-type 'fixnum)
  (defun foo (a b c) ... ))

This form stores the value returned by FOO in an array, which was created
by (make-array (list 10 20 30) :initial-element -1 :element-type 'fixnum). Note
that INITIAL-ELEMENT must always be given here as it is used as the flag
expressing `not yet stored'. (Therefore INITIAL-ELEMENT should be a value FOO
never takes.)

If you want to ignore some arguments, you can put `*' in dimensions:

\(with-cache (:array (10 10 * 10) :initial-element -1)
  (defun foo (a b c d) ...)) ; then C is ignored when querying or storing cache

Available definition forms in WITH-CACHE are DEFUN, LABELS, FLET, and
SB-INT:NAMED-LET.

You can trace a memoized function by :TRACE option:

\(with-cache (:array (10 10) :initial-element -1 :trace t)
  (defun foo (x y) ...))

Then FOO is traced as with CL:TRACE.
"
  (multiple-value-bind (cache-symbol cache-form cache-type
                        make-reset-name make-reset-form
                        make-cache-querier)
      (%parse-cache-form (cons cache-type cache-attribs))
    (ecase (car def-form)
      ((defun)
       (destructuring-bind (_ name args &body body) def-form
         (declare (ignore _))
         `(let ((,cache-symbol ,cache-form))
            (defun ,(funcall make-reset-name name) ()
              ,(funcall make-reset-form cache-type))
            (defun ,name ,args
              ,@(%extract-declarations body)
              (flet ((,name ,args ,@body))
                (declare (inline ,name))
                ,(funcall make-cache-querier cache-type name args))))))
      ((labels flet)
       (destructuring-bind (_ definitions &body labels-body) def-form
         (declare (ignore _))
         (destructuring-bind (name args &body body) (car definitions)
           `(let ((,cache-symbol ,cache-form))
              (,(car def-form)
               ((,(funcall make-reset-name name) ()
                 ,(funcall make-reset-form cache-type))
                (,name ,args
                       ,@(%extract-declarations body)
                       (flet ((,name ,args ,@body))
                         (declare (inline ,name))
                         ,(funcall make-cache-querier cache-type name args)))
                ,@(cdr definitions))
               (declare (ignorable #',(funcall make-reset-name name)))
               ,@labels-body)))))
      ((nlet #+sbcl sb-int:named-let)
       (destructuring-bind (_ name bindings &body body) def-form
         (declare (ignore _))
         `(let ((,cache-symbol ,cache-form))
            (,(car def-form) ,name ,bindings
             ,@(%extract-declarations body)
             ,(let ((args (mapcar (lambda (x) (if (atom x) x (car x))) bindings)))
                `(flet ((,name ,args ,@body))
                   (declare (inline ,name))
                   ,(funcall make-cache-querier cache-type name args))))))))))

(defmacro with-caches (cache-specs def-form)
  "DEF-FORM := definition form by LABELS or FLET.

\(with-caches (cache-spec1 cache-spec2)
  (labels ((f (x) ...) (g (y) ...))))
is equivalent to the line up of
\(with-cache cache-spec1 (labels ((f (x) ...))))
and
\(with-cache cache-spec2 (labels ((g (y) ...))))

This macro will be useful to do mutual recursion between memoized local
functions."
  (assert (member (car def-form) '(labels flet)))
  (let (cache-symbol-list cache-form-list cache-type-list make-reset-name-list make-reset-form-list make-cache-querier-list)
    (dolist (cache-spec (reverse cache-specs))
      (multiple-value-bind (cache-symbol cache-form cache-type
                            make-reset-name make-reset-form make-cache-querier)
          (%parse-cache-form cache-spec)
        (push cache-symbol cache-symbol-list)
        (push cache-form cache-form-list)
        (push cache-type cache-type-list)
        (push make-reset-name make-reset-name-list)
        (push make-reset-form make-reset-form-list)
        (push make-cache-querier make-cache-querier-list)))
    (labels ((def-name (def) (first def))
             (def-args (def) (second def))
             (def-body (def) (cddr def)))
      (destructuring-bind (_ definitions &body labels-body) def-form
        (declare (ignore _))
        `(let ,(loop for cache-symbol in cache-symbol-list
                     for cache-form in cache-form-list
                     collect `(,cache-symbol ,cache-form))
           (,(car def-form)
            (,@(loop for def in definitions
                     for cache-type in cache-type-list
                     for make-reset-name in make-reset-name-list
                     for make-reset-form in make-reset-form-list
                     collect `(,(funcall make-reset-name (def-name def)) ()
                               ,(funcall make-reset-form cache-type)))
             ,@(loop for def in definitions
                     for cache-type in cache-type-list
                     for make-cache-querier in make-cache-querier-list
                     collect `(,(def-name def) ,(def-args def)
                               ,@(%extract-declarations (def-body def))
                               (flet ((,(def-name def) ,(def-args def) ,@(def-body def)))
                                 (declare (inline ,(def-name def)))
                                 ,(funcall make-cache-querier cache-type (def-name def) (def-args def))))))
            (declare (ignorable ,@(loop for def in definitions
                                        for make-reset-name in make-reset-name-list
                                        collect `#',(funcall make-reset-name
                                                             (def-name def)))))
            ,@labels-body))))))

;; BEGIN_USE_PACKAGE
(eval-when (:compile-toplevel :load-toplevel :execute)
  (use-package :cp/with-cache :cl-user))
(in-package :cl-user)

;;;
;;; Body
;;;

(defun main ()
  (declare #.*opt*)
  (let* ((tt (read)))
    (with-cache (:hash-table :size 1000000 :test #'eq :key #'identity)
      (labels ((dp (x)
                 (declare (uint62 x)
                          (values uint62))
                 (if (<= x 1)
                     1
                     (loop with sum of-type uint62 = 0
                           for k of-type uint31 from 0
                           do (multiple-value-bind (quot rem)
                                  (floor (+ x 1) (+ k 1))
                                (when (< quot (+ k 1))
                                  (return sum))
                                (when (zerop rem)
                                  (incf sum (dp k))
                                  (unless (or (= (- quot 1) k)
                                              (= (- quot 1) x))
                                    (incf sum (dp (- quot 1))))))))))
        (dotimes (_ tt)
          (let ((n (read)))
            (println (dp n))))))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/MONEY"))

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
