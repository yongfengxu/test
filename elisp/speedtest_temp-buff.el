;; 2011-12-20
;; Speed test script
;; 
;; What the script do:
;; Creates a 〔sitemap.xml〕 file.
;; Open each files in a dir, if the file doesn't contain the word “refresh”, add a entry of the file to 〔sitemap.xml〕.

;; Must end in a slash. Must not start with ~
(setq webroot "/Users/h3/web/xahlee_org/emacs_manual/elisp/")

;; ------------------------

(defun my-process-file (fPath destBuff)
  "Process the file at fullpath FPATH.
Write result to buffer DESTBUFF."
  (with-temp-buffer
      (insert-file-contents fPath)
      (goto-char 1)
      (when (not (search-forward "refresh" nil "noerror"))
        (with-current-buffer destBuff
          (insert "<url><loc>")
          (insert (concat "http://example.org/" (substring fPath (length webroot))))
          (insert "</loc></url>\n") )) ) )

;; ------------------------

(print
 (benchmark-run 1
     ;; create sitemap buffer
     (let (filePath sitemapBuf)
       (setq filePath (concat webroot "sitemap.xml"))
       (setq sitemapBuf (find-file filePath))
       (erase-buffer)
       (set-buffer-file-coding-system 'unix)
       (insert "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">
")

       (require 'find-lisp)
       (mapc
        (lambda ($x) (my-process-file $x sitemapBuf))
        (find-lisp-find-files webroot "\\.html$"))

       (insert "</urlset>")
       (save-buffer)
       )
   ))

(message "%s" "Yay, Done!")
