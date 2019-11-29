;;Vector is a ordered sequence of values.
;;Each element can be any type.
;;Element's value can be changed.
;;Number of elements cannot change. (i.e. Vector's length is fixed.)
;;Reading/Writing a element has constant random access time.

(make-vector 5 0)
(setq v (vector 3 4 5))
(setq x 7)
(setq v (vector 3 x 5))
(print v)

(setq aa [3 4 5])
(fillarray aa nil)
(length aa)

;;(aref array n) → Return the element of array at index n.
;;(elt sequence n) → Return element of sequence at index n.
;;When emacs doc mentions “ARRAY”, you can think of it as “vector or string”.
;;When emacs doc mentions “SEQUENCE”, you can think of it as “list or array”.

(aref ["a" "b" "c"]1)
(aref ["a" "b" "c"]0)
(aref ["a" "b" "c"]2)

(elt ["a" "b" "c"]1)
(elt ["a" "b" "c"]0)
(elt ["a" "b" "c"]2)

(aset aa 0 "ddd")
(print aa)

;; (vconcat sequence1 sequence2 …) → join any sequence types and return a vector. (List and vector are both sequence types.)
;; join any sequence types
(vconcat [3 4] ["a" "b"]) ; ⇒ [3 4 "a" "b"]
(vconcat [3 4] '("a" "b")) ; ⇒ [3 4 "a" "b"]
(vconcat [3 4] "ab") ; ⇒ [3 4 97 98]
;; string elements are converted to char.
;; 97 is the codepoint for the char a

;;(append sequence1 sequence2 …) → join any sequence types and return a list. (List and vector are both sequence types.)
;;Warning: if you want it to return a propert list, the last element must be a list, or nil.

(append [1 2 3] nil) ; => (1 2 3)
(append [1 2 3] [4 5]) ; => (1 2 3 . [4 5])
(append [1 2 3] [4 5] nil)
(append [1 2 3] [4 5] '(6))
