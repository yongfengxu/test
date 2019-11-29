;; (mapcar FUNCTION SEQUENCE) → Apply FUNCTION to each element of SEQUENCE, and make a list of the results. The result is a list, with same length as SEQUENCE. SEQUENCE may be a list, a vector, a bool-vector, or a string.
;; add 1 to each vector element
(mapcar '1+ [3 4 5] ) ; (4 5 6)

;; add one to each list element
(mapcar '1+ '(3 4 5)) ; (4 5 6)

; take the 1st element of each
(mapcar 'car '((1 2) (3 4) (5 6))) ; (1 3 5)

;; get first element of each row
(mapcar
 (lambda (x) (elt x 0))
 [[1 2] [3 4]] ) ; ⇒ (1 3)

;;; add one to each list member
(mapcar
 (lambda (x) (+ x 1))
 (list 1 2 3 4 ))

;; take the 2nd element of each
(mapcar (lambda (x) (nth 1 x))
        '((1 2) (3 4) (5 6))) ; (2 4 6)

;; mapc (foreach)
;; If you don't need map to return the sequence, use mapc.
;; mapc → like mapcar, but returns nil.


(mapcar (lambda (x) (nth 1 x))
         '((1 2) (3 4) (5 6))) ; (2 4 6)

;; mapc → like mapcar, but returns nil.



;;dolist
;;(dolist (VAR LIST) BODY) → Loop over a list. Evaluate BODY with VAR bound to each element from LIST, returns nil.
;;(dolist (VAR LIST RESULT) BODY) → returns RESULT.

(let (
      (xlist (number-sequence 97 122)) ;; list 97 to 122
      )
  (dolist (n xlist) (insert n))) 






