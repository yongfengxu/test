(defun get-string-from-file (filePath)
  "return filePath's file content"
  (with-temp-buffer
    (insert-file-contents filePath)
    (buffer-string)))


(defun read-lines (filePath)
  "Return a list of lines of a file at filePath."
  (with-temp-buffer
    (insert-file-contents filePath)
    (split-string (buffer-string) "\n" t)))

(defun my-process-file (fPath)
  "Process the file at path FPATH …"
  (let ((fileChanged-p nil))
    (with-temp-buffer
      (insert-file-contents fPath)

      ;; process text
      ;; set fileChanged-p to t or nil

      (when fileChanged-p (write-region 1 (point-max) fPath)))))
    ;;(when fileChanged-p append-to-file 1 (point-max) fPath)))))


;;(message "file contents is: %S" get-string-from-file ("/repo/elmpprv/epg/framework/CMakeLists.txt"))
