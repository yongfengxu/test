;;; esc-mode.el --- Major mode for the Ericsson StateChart language    -*- lexical-binding: t; -*-

;; Copyright (C) 2016 Ericsson AB

;; Author: David Holm <david.holm@ericsson.com>
;; Version: 0.3.1
;; Description: Major mode for ESC sources
;; Compatibility: Tested with GNU/Emacs 23.2 on GNU/Linux
;; Keywords: esc languages uml
;; Created: Apr 2016

;;; Commentary:
;;
;; A major mode for the Ericsson StateChart language.
;;
;; Right now it only does font-locking of basic ESC types and keywords in an ESC
;; buffer and doesn't handle indentation rules and C/C++-code.
;;
;; There is also support for rendering ESC in the "current" buffer as long as
;; Emacs has been built with SVG support and is running in graphical display
;; mode.
;;
;; Buffer navigation is aided by `imenu'.
;;
;; Syntax checking of ESC buffers is performed on-the-fly when `flycheck-mode'
;; is available.

;;; Change log:
;;
;; 0.3.1, 2016-05-18 Allow multiple open state charts, set default scale
;; 0.3.0, 2016-04-20 Flycheck support
;; 0.2.0, 2016-04-19 Imenu support
;; 0.1.0, 2016-04-08 First version

;;; Installation:
;;
;; Add this to your .emacs:
;;
;; (add-to-list 'load-path "/folder/containing/this/file")
;; (require 'esc-mode)

;;; Code:

(require 'flycheck nil t)
(require 'image-mode)

(defgroup esc nil
  "Ericsson StateChart support for Emacs."
  :group 'languages)

(defcustom esc-installation-path
  (concat (if (getenv "WS_ROOT")
              (getenv "WS_ROOT")
            (concat "/workspace/git/" (getenv "USER") "/epg"))
          "/tools/scripts/esc")
  "The path to the ESC installation."
  :type 'directory
  :group 'esc)

(defcustom esc-preview-scale 0.7
  "Default image scale when opening ESC preview."
  :type 'number
  :group 'esc)

(defconst esc--font-lock-keywords
  `((,(concat "^\\s *" (regexp-opt '("StateMachine" "SubStateMachine") 'words))
     . font-lock-type-face)
    (,(concat "^\\s *" (regexp-opt '("CppIncludes" "EscIncludes" "Events"
                                     "HIncludes" "Namespace"
                                     "TriggeredOperations" "choice" "connector"
                                     "default" "else" "entry" "exit" "history"
                                     "internal" "join" "junction" "state"
                                     "subentry" "subexit" "terminate"
                                     "tm") 'words))
     . font-lock-keyword-face)))

(defvar esc-mode-map
  (let ((keymap (make-keymap)))
    (define-key keymap (kbd "C-c C-c") 'esc-preview)
    keymap)
  "Keymap for `esc-mode'.")


;;; Diagram generation
(defun esc--preview-sentinel (event prefix buf esc-buffer-name)
  "ESC sentinel receiving EVENT called with PREFIX outputting to BUF from ESC-BUFFER-NAME."
  (unless (equal event "finished\n")
    (error "ESC Preview failed: %s" event))
  (cond
   ((= prefix 16)
    (switch-to-buffer-other-frame buf))
   ((= prefix 4)
    (switch-to-buffer-other-window buf))
   (t (switch-to-buffer buf)))
  (condition-case err
      (progn
        (image-mode)
        (set-buffer-multibyte t)
        (if (eq (buffer-size buf) 0)
            (progn
              (kill-buffer buf)
              (error "No output produced!"))
          (image-transform-set-scale esc-preview-scale)))
    ('error
     (message "%s: %s"
              (propertize esc-buffer-name
                          'face font-lock-comment-face)
              (propertize (error-message-string err)
                          'face font-lock-warning-face)))))

(defun esc-preview (&optional prefix)
  "Preview state machine, using PREFIX to control output.

Creates a new buffer called `*ESC: <buffer-name>*'.

The prefix has the following effect:
None - Open in a new buffer.
One  - Open in a new window.
Two  - Open in a new frame."
  (interactive "p")
  (unless (eq major-mode 'esc-mode)
    (error "Buffer is not in esc-mode!"))

  (let ((buf-name (format "*ESC: %s*" (buffer-name))))
    (let ((b (get-buffer buf-name)))
      (when b
        (kill-buffer b)))

    (let* ((process-connection-type nil)
           (buf (get-buffer-create buf-name))
           (coding-system-for-read 'binary)
           (coding-system-for-write 'binary)
           (esc-buffer-name (buffer-name))
           (esc2image-path (concat esc-installation-path "/esc2image.py")))

      (let ((ps (start-file-process "ESC" buf
                                    "python" (shell-quote-argument esc2image-path)
                                    "--base-path" default-directory "-")))
        (process-send-region ps (point-min) (point-max))
        (process-send-eof ps)
        (set-process-sentinel ps
                              (lambda (_ event)
                                (esc--preview-sentinel event prefix buf esc-buffer-name)))))))


;;; Imenu
(defconst esc--imenu-generic-expression
  (list
   (list
    nil
    (concat "^StateMachine"
            "\\s-+\\([A-Za-z:]+\\)")
    1)
   (list
    "SubStateMachine"
    (concat "^SubStateMachine"
            "\\s-+\\(\\(\\sw\\|\\s_\\)+\\)")
    1)
   )
  "Imenu generic expression for `esc-mode'.  See `imenu-generic-expression'.")


;;; Flycheck
(when (featurep 'flycheck)
  (flycheck-define-checker esc-escgen
    "A syntax checker for Ericsson ESC files."
    :command ("python" (eval (concat esc-installation-path "/escgen.py"))
              "--base-path" (eval default-directory)
              "--syntax-only"
              "-")
    :standard-input t
    :error-patterns
    ((error line-start (one-or-more not-newline) ":" line ": " (message)
            line-end))
    :modes esc-mode)

  (add-to-list 'flycheck-checkers 'esc-escgen 'append))


;;; Mode definition
;; Emacs 24.3 compatibility.
(defalias 'esc--base-mode
  (if (fboundp 'prog-mode)
      'prog-mode
    'fundamental-mode))

;;;###autoload
(define-derived-mode esc-mode esc--base-mode "esc"
  "Major mode for editing Ericsson StateChart language buffers.

\\{esc-mode-map}"
  (set (make-local-variable 'tab-width) 4)
  (set (make-local-variable 'indent-tabs-mode) nil)

  (set (make-local-variable 'comment-start) "# ")
  (set (make-local-variable 'comment-start-skip) "#+\\s-*")

  (set (make-local-variable 'font-lock-defaults)
       '(esc--font-lock-keywords nil nil nil nil))

  (set (make-local-variable 'imenu-generic-expression)
       esc--imenu-generic-expression))

;;;###autoload
(add-to-list 'auto-mode-alist '("\\.esc$" . esc-mode))

(provide 'esc-mode)

;; Local Variables:
;; coding: utf-8
;; indent-tabs-mode: nil
;; End:

;;; esc-mode.el ends here
