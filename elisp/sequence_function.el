;;vector
(setq v '["1" "b" "3" "5"])
(setq v1 '["2" "g2"])
(setq v2 '["ds" "dc"])
;;list
(setq l '("a" "2" "c" "4" "d"))
(setq l1 '("dd" "ee"))
(setq l2 '("cc" "aa"))

;;length
(length v) ; ==> 4
(length l) ; ==> 5

;;number-sequence
;;(number-sequence n m step) → returns a list of a range of numbers, from n to m, in increment of step.
(number-sequence 1 20 3)

;;List to Vector

(vconcat l1 l2)
(vconcat l1 v2)
(vconcat l1 l2)

;;Vector to List
(append v v1)
(append v l1)

;;To String
(format "%s" v1)
(format "%s" l1)

;;Get 1 Element
;;(car list) → first element
(car l) ; ==> "a"

;;(nth n list) → nth element
(nth 3 l) ; ==> "4"

;;(car (last list)) → last element
(last l) ; ==> ("d")
(car (last l)) ; ==> "d"

;;Sublist
;;cdr → rest. (without 1st)
(cdr l) ; ==> ("2" "c" "4" "d")
;;nthcdr → rest starting at n.
(nthcdr 2 l) ; ==> ("c" "4" "d")
;;last → last as a list. i.e. return (cons lastElement nil)
(last l) ; ==> ("d")


(setq l '("a" "2" "c" "4" "d"))
(setq l1 '("dd" "ee"))
(setq l2 '("cc" "aa"))

;; Prepend, Append, Join
;;(cons x list) → Return a new list, with x added to front. (prepend)
;;(append sequence1 sequence2 …) → join any sequence types and return a list. Warning: if you want it to return a propert list, the last element must be a list, or nil.

(cons 3 l1) ;; ==> (3 "dd" "ee")

;;Modify List Variable
;;(push list) → Add a element to the front variable. Returns the new list.
(push 3 l1) ;; ==> (3 "dd" "ee")

;;(pop list) → Remove first element from the variable. Returns the removed element.
(pop l2) ;; ==> "cc"

;;(nbutlast list n) → Remove last n elements from the variable. Returns the new value of the variable.
(print l1)
(nbutlast l1 1)

;;(setcar list x) → replaces the first element in list with x. Returns x.
(setcar l "ch")

;;(setcdr list x) → replaces the rest of elements in list with x. Returns x.
(setcdr l "jj")


(setq l '("a" "2" 1.2 "4" "d"))
(setq x 1)
(setq y "bb")
(push y l)
(push x l)
(print l)

(sequencep l)
(sequencep x)

(elt l 3) ; ==> 4
(reverse l)
(nreverse l)

;;(member x list) → check if x is in list. If so, return a list starting with the first occurrence of object. Else return nil. Comparison done using equal.
(member "2" l)
(member x l)
(member 1 l)

(member "A" '("b" "a")) ; nil
(member-ignore-case "A" '("b" "a")) ; ("a")

;;(memq x list) → same as member, but comparison done using eq.
;; eq returns t if two arguments are the same lisp object
(memq y l)
(memq "2" l)
(memq x l)
(memq 1 l)

(eq 1 1) ;; ==> t
(eq 1.2 1.2) ;; ==> nil
(eql 1.2 1.2) ;; ==> t
(eql 1 1) ;; ==> t
(memq 1.2 l) ;; ==> nil

;;(memql x list) → same as member, but comparison done using eql.
(memql "2" l)
(memql x l)
(memql 1 l)
(memql 1.2 l) ;; ==> (1.2 "4" "d")

;; (delete x sequence) → remove all x in sequence. The original sequence is destroyed. Returns a new sequence. The comparison is done with equal.
(setq xx '(3 4 5))
xx
(delete 5 xx)
xx
;; always set result to the same var. because original is usually destroyed
(setq xx (delete 4 xx)) ; (3 5)

;; on vector
(setq xx [3 4 5])
(setq xx (delete 4 xx)) ; [3 5]

;;(remove x sequence) → same as delete, except sequence is not destroyed.
(setq xx '(3 4 5))
(remove 4 xx) ;; (3 5)
xx ; (3 4 5)

;;(delq x sequence) → Same as delete, except the comparison is done with eq.
(setq xx '(3 4 5))

;; always set result to the same var
(setq xx (delq 4 xx)) ; (3 5)

;; (remq x list) → same as delq, except it does not destroy the original list.
(setq xx '(3 4 5))
(remq 4 xx) ; (3 5)
xx ; (3 4 5)

;; (delete-dups list) → This function destructively removes all duplicates from list, return a new list. The first one is kept among duplicates.
(setq xx '(3 4 5 3 2))
(setq xx (delete-dups xx)) ; (3 4 5 2)
