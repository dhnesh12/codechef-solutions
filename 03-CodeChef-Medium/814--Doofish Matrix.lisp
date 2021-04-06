#-swank
(unless (member :child-sbcl *features*)
  (quit
   :unix-status
   (process-exit-code
    (run-program *runtime-pathname*
                 `("--control-stack-size" "256MB"
                   "--dynamic-space-size" "2GB"
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
;; BEGIN_USE_PACKAGE
(in-package :cl-user)

;;;
;;; Body
;;;

;; (defun valid-p (mat)
;;   (let* ((n (array-dimension mat 0))
;;          (marked (make-array (- (* 2 n) 1) :element-type 'bit :initial-element 0)))
;;     (dotimes (pivot-i n)
;;       (fill marked 0)
;;       (dotimes (j n)
;;         (setf (aref marked (aref mat pivot-i j)) 1))
;;       (dotimes (i n)
;;         (setf (aref marked (aref mat i pivot-i)) 1))
;;       #>marked
;;       #>pivot-i
;;       (unless (loop for x across marked
;;                     always (= x 1))
;;         (return-from valid-p nil)))
;;     t))


(defun round-robin-map (n function)
  "Maps each list of N-1 matches of a round-robin tournement by N players.

- N must be even.
- FUNCTION takes two arguments: a vector that maps an opponent to each player,
and the number of the round.
- Consequence is undefined when the vector passed FUNCTION is modified."
  (declare #.*opt*
           (uint31 n))
  (assert (evenp n))
  (let ((res (make-array n :element-type 'uint16)))
    (dotimes (round (- n 1))
      (declare (uint31 round))
      (labels ((calc (x)
                 (declare (uint31 x))
                 (if (zerop x)
                     0
                     (+ 1 (mod (+ x -1 round) (- n 1))))))
        (dotimes (j (ash n -1))
          (let ((p1 (calc j))
                (p2 (calc (- n j 1))))
            (setf (aref res p1) p2
                  (aref res p2) p1))))
      (funcall function res round))))

(defun main ()
  (declare #.*opt*)
  (let* ((cases (read))
         (out (make-string-output-stream :element-type 'base-char)))
    (dotimes (_ cases)
      (let* ((n (read)))
        (declare (uint31 n))
        (cond ((= n 1)
               (write-line "Hooray" out)
               (println 1 out))
              ((oddp n)
               (write-line "Boo" out))
              (t
               (let ((mat (make-array (list n n) :element-type 'uint16)))
                 (dotimes (i n)
                   (setf (aref mat i i) (- (* 2 n) 2)))
                 (round-robin-map
                  n
                  (lambda (vector round)
                    (declare ((simple-array uint16 (*)) vector)
                             (uint31 round))
                    (dotimes (i n)
                      (let ((j (aref vector i)))
                        (setf (aref mat i j)
                              (if (< i j)
                                  round
                                  (- (* 2 n) round 3)))))))
                 (write-line "Hooray" out)
                 (dotimes (i n)
                   (dotimes (j n (terpri out))
                     (unless (zerop j)
                       (write-char #\  out))
                     (princ (+ 1 (aref mat i j)) out))))))))
    (write-string (get-output-stream-string out))))

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
  (defparameter *problem-url* "https://www.codechef.com/problems/DFMTRX"))

#+swank
(defun gen-dat ()
  (uiop:with-output-file (out *dat-pathname* :if-exists :supersede)
    (format out "1 2000~%")))

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
   (equal "Hooray
1
Hooray
3 1
2 3
"
          (run "2
1
2
" nil))))
