(eval-when (:compile-toplevel :load-toplevel :execute)
  #+swank (ql:quickload '(:cl-debug-print :fiveam :cp/util) :silent t)
  #+swank (use-package :cp/util :cl-user))

(macrolet ((def (b)
             `(progn (deftype ,(intern (format nil "UINT~A" b)) () '(unsigned-byte ,b))
                     (deftype ,(intern (format nil "INT~A" b)) () '(signed-byte ,b))))
           (define-int-types (&rest bits) `(progn ,@(mapcar (lambda (b) `(def ,b)) bits))))
  (define-int-types 2 4 7 8 15 16 31 32 62 63 64))

(declaim (inline println))
(defun println (obj &optional (stream *standard-output*))
  (let ((*read-default-float-format*
          (if (typep obj 'double-float) 'double-float *read-default-float-format*)))
    (prog1 (princ obj stream) (terpri stream))))

;; BEGIN_INSERTED_CONTENTS
;; BEGIN_USE_PACKAGE
(in-package :cl-user)

(define-modify-macro minf (new-value) min)
(defconstant +inf+ #x7fffffff)
(defun main ()
  (let* ((n (read))
         (total (read))
         (is (make-array n :element-type 'uint31))
         (types (make-array n :element-type 'uint31))
         (ps (make-array n :element-type 'uint31))
         (qs (make-array n :element-type 'uint31))
         (mins (make-array 6 :element-type 'uint31 :initial-element +inf+)))
    (declare (uint31 n total))
    (dotimes (i n)
      (setf (aref types i) (- (read *standard-input* nil 1) 1)
            (aref ps i) (read *standard-input* nil 1)
            (aref qs i) (read *standard-input* nil 1)
            (aref is i) i))
    (setq is (sort is #'> :key (lambda (i) (aref qs i))))
    (loop for i across is
          for p = (aref ps i)
          for q = (aref qs i)
          for type = (aref types i)
          do (minf (aref mins type) p)
             (when (<= (reduce #'+ mins) total)
               (println q)
               (return-from main)))
    (println 0)))

#-swank (main)
