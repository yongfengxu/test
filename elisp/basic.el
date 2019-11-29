;;c+x c+e
(+ 64 1)
(message "hello world, my first elisp")
(message "64 + 1 = %d %s" (+ 64 1) "he")
(message "My list is: %S" (list (- 6 5) "ddd" 111))


(setq mylist (list 1 "b" 3))
;(setq mylist1 '(1 "b" 3))
(setq mylist1 (list 1 "b" 3))
(equal 'mylist 'mylist1)
(eq 'mylist 'mylist1)
(eq mylist mylist1)
(equal 'abc 'abc)
(equal '(1 "b" 3) '(1 "b" 3))
(if (equal mylist mylist1) (print "equal") (print "no equal"))

;; print a line many times
(setq xx 1)
(while (< xx 20)
  (message "yay")
  (setq xx (1+ xx))
  )
(switch-to-buffer "*Messages*")

(setq xbuff (generate-new-buffer "*my output*"))
(print "something" xbuff)
(switch-to-buffer xbuff )

(mapc
 ;;(lambda (x) (insert x "\n"))
 (lambda (x) (insert x "\n"))
 (directory-files "~/test/cpp_test/" nil "\.cpp$" t))

(mapc (lambda (x) (message x "\n"))
      (directory-files-recursively "~/test/cpp_test/" "\.cpp$" ))

(setq
 skipDirs
 [
  "~/test/c_test"
  "~/test/cmake_test"
  "~/test/design_pattern"
  ])

(seq-filter
 (lambda (path)
   (not (seq-some
         (lambda (x) (string-match x path))
         skipDirs )))
 (directory-files-recursively "~/test" "\.cpp$" ))


; call a shell command
(shell-command "touch new.txt")

; call a shell command and get its output
(shell-command-to-string "ls")

(message "ls result:%s\n" (shell-command-to-string "ls"))

(mapc
 (lambda (x)
   (let ((process-connection-type nil))
     (start-process "" nil "xdg-open" x)) )
 filePathList)


;; get the current elisp script's name at run time
(or load-file-name buffer-file-name)
(message "current run script file: %s" (or load-file-name buffer-file-name))

(message "skip dirs: %S" skipDirs)

(let (a b)
  (setq a 3)
  (setq b 4)
  (+ a b)
  )

(let (a 3) (b 4)
     (+ a b))
(setq a 3 b 4)
(message "a = %d, b = %d" a b)

(if (< 2 3) 8 9)
(if (< 3 2) (message"hello"))


(progn (print "The first form")
       (print "The second form")
       (print "The third form"))

(prog1 (print "The first form")
       (print "The second form")
       (print "The third form"))

(when (equal "a" "a") (print "a") (print "b"))

(setq a "hack1")
(message "%S" a)
(cond ((eq a 'hack) 'foo)
      ((eq a 5) (print "hello"))
      (t (print "default")))


(setq x 0)
(while (< x 4)
  (print (format "number is %d" x))
  (setq x (1+ x)))

;; inserts Unicode chars 32 to 126
(let ((x 32))
  (while (< x 127)
    (insert-char x)
    (setq x (+ x 1))))

;(lambda (args) body)
(mapcar
 (lambda (x) (1+ x))
 (list 1 2 3 4)
 )


(defun echo-file-name (filePath)
  (message (format "file: %s" filePath))
  )

(mapc 'echo-file-name
      (list
       "~/.cshrc"
       "~/.cshrc.user")
      )
