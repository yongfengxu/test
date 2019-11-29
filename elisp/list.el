(setq mylist (list 1 "b" 3))
(message "%S" mylist)
(message "%S" 'mylist)
(message "%S" '(a b c))

;; create a list of values of variables
(let ((x 3) (y 4) (z 5))
  (message "%S" (list x y z))
  ) ; prints "(3 4 5)"

(make-list 4 1)

;; (list) nil '() are equivalent
(eq (list) nil)
(eq '() nil)
(eq (list) '())

;; creating a range of numbers

;; just 1 element
(number-sequence 5) ; (5)

;; n to m, inclusive
(number-sequence 2 5) ; (2 3 4 5)

;; using 3 as step
(number-sequence 0 9 3) ; (0 3 6 9)

;; step can be negative
(number-sequence 5 0 -1) ; (5 4 3 2 1 0)

;; boundaries can be float but will not include
(number-sequence 2.2 5.3) ; (2.2 3.2 4.2 5.2)

(length '("a" "b" "c")) ; 3
(car (list "a" "b" "c"))   ; "a"
(nth 1 (list "a" "b" "c")) ; "b"
(car (last (list "a" "b" "c")))   ; "c"

;;Get Sublist
;(cdr list) → 2nd to last elements.
;(nthcdr n list) → nth to last elements.
;(butlast list n) → without the last n elements.
(setq cclist1 (list "a" "b" "c" "d" "e" "f"))
(cdr cclist1)
(nthcdr 2 cclist1)

(butlast cclist1 2)
(butlast cclist1)

(cons "a" '("b" "c"))
(cons "a" cclist1 )

(equal
 (list 1 2 3 4)
 (append (list 1 2) (list 3 4))
 )

(let ((x '(1)))
  (push 2 x)
  (equal x '(2 1))
  )

(setq mylist '("a" "b" "c"))
(pop mylist)
(print mylist)


(mapconcat 'number-to-string '(1 2 3) ",")
(mapconcat 'identity '("a" "b" "c") ",")

(format "%s" '(1 "two" 3))
(substring (format "%s" '(1 "two" 3)) 1 -1)
(substring (format "%s" '(1 "two" 3)) 1 4)
