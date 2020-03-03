;;To exit a loop or function in elisp:
;;
;;Use catch and throw to exit loop or function. These are like “break”, “goto”.
;;Use error or user-error to signal a error and exit.

(defun test-exit-f ()
  "example. using catch/throw to exit function"
  (interactive)
  (catch 'aaa
    (if (y-or-n-p "exit?")
        (progn
          (message "existing")
          (throw 'aaa 3) ; if yes, exit right away, return 3 to catch
          )
      (progn ; else, go on
        (message "went on")
        4 ; return 4
        ))))

(test-exit-f)

;;Exit by Error
;;You can exit by calling error or user-error .

(defun test-exit-f1 ()
  "example"
  (interactive)
  (if (y-or-n-p "invoke user-error to exit?")
      (user-error "Error, because: %s" "you said so!")
    (progn ; else, go on
      (message "went on")
      )))

(test-exit-f1)



;;Exit a map
;;You can also use throw and catch to exit a map or loop.
;;
;;(catch 'tagname body) → evaluates body and return body's last expression, but if body contains (throw …) and it is called, return the value throw passes.
;;
;;(throw tagName passValue) → jump to a outer (catch 'tagName) and continue there, passing the value of passValue to it. Both tagName passValue are evaluated.

(setq myList [0 1 2 3 4 5])

;; map lambda onto a list. If value 3 is found, return 3, else nil
(catch 'bbb
  (mapc
   (lambda (x)
     (message "Charlie: %s" x)
     (when (equal x 3) (throw 'bbb x)))
   myList)
  ;nil
  )


;;Exit a While Loop by Flag
(let ((myList [0 1 2 3 4 5] )
      (foundFlag-p nil )
      (i 0))

  (while (and
          (not foundFlag-p)
          (<= i (length myList)))

    ;; if found, set foundFlag-p
    (when (equal (elt myList i) 3)
      (setq foundFlag-p t ))

    (message "value: %s" i)
    (setq i (1+ i))))
