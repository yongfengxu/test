
;;Hash table
(setq myHash
      #s(hash-table
         size 30
         test equal
         data (
               "joe" 3
               "jane" 9
               "liz" 5 )))

;; test
(gethash "joe" myHash ) ; 3
