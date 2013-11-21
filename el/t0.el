;; This buffer is for notes you don't want to save, and for Lisp evaluation.
;; If you want to create a file, visit that file with C-x C-f,
;; then enter the text in that file's own buffer.

(defun count-words-buffer ()
  (interactive)
  (save-excursion
  (let ((count 0))
    (goto-char (point-min))
    (while (< (point) (point-max))
      (forward-word 1)
      (setq count (1+ count)))
    (message "qqq buffer contains %d words." count))))

(count-words-buffer) 
"qqq buffer contains 103 words."






(message "buffer contains %d words." 100)
"buffer contains 100 words."




(+ 2 3)

5



"yyy buffer contains 86 words."
"abc buffer contains 91 words."
"xyz buffer contains 96 words."
