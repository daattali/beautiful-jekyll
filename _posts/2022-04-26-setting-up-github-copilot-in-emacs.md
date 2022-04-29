---
layout: post
title: "Setting up GitHub Copilot in Emacs"
---

I was invited to the [Copilot](https://copilot.github.com/) a long time back, however, I never got round to setting it up since it did not appear to support my IDE of choice.
Currently, the [docs](https://github.com/github/copilot-docs) only specify the following:
1. VS Code
1. Visual Studio
1. JetBrains
1. Neovim

To my disappointment, Emacs was not listed there. This morning I took some time to figure out if it was possible to setup copilot in Emacs. I'm glad to say it is!

## Setting up Github Copilot in Emacs
I use [Doom Emacs](https://github.com/hlissner/doom-emacs), but these instructions will work for any Emacs distribution.

1. Setup `straight.el`

`straigh.el` is a package manager, that enables you to directly install Emacs packages from git repos. The package we will install, is currently not available in melpa. In Doom Emacs, you need to bootstrap this in your `~/.doom.d/init.el` file. Bootstrapping involves adding the following code:

```lisp
(defvar bootstrap-version)
(let ((bootstrap-file
       (expand-file-name "straight/repos/straight.el/bootstrap.el" user-emacs-directory))
      (bootstrap-version 5))
  (unless (file-exists-p bootstrap-file)
    (with-current-buffer
        (url-retrieve-synchronously
         "https://raw.githubusercontent.com/raxod502/straight.el/develop/install.el"
         'silent 'inhibit-cookies)
      (goto-char (point-max))
      (eval-print-last-sexp)))
```

2. Install `zerolfx/copilot.el`

Copilot is supported in Emacs thanks to the wonderful work at [zerolfx/copilot.el](https://github.com/zerolfx/copilot.el). This is a port of the NeoVim plugin and requires `node`. To install this, add the following to your `init.el`:

```lisp
(use-package copilot
  :straight (:host github :repo "zerolfx/copilot.el"
                   :files ("dist" "copilot.el"))
  :ensure t)
```

Additionally, to enable copilot-mode automatically:

```lisp
(load bootstrap-file nil 'nomessage))(add-hook 'prog-mode-hook 'copilot-mode)
```

And since, I use `evil` in Doom Emacs, you want completions only to trigger in insert mode:

```lisp
(customize-set-variable 'copilot-enable-predicates '(evil-insert-state-p))
```

To accept completions, you can bind the TAB key and chain it with say `company`:

```lisp
; complete by copilot first, then company-mode
(defun my-tab ()
  (interactive)
  (or (copilot-accept-completion)
      (company-indent-or-complete-common nil)))

; modify company-mode behaviors
(with-eval-after-load 'company
  ; disable inline previews
  (delq 'company-preview-if-just-one-frontend company-frontends)
  ; enable tab completion
  (define-key company-mode-map (kbd "<tab>") 'my-tab)
  (define-key company-mode-map (kbd "TAB") 'my-tab)
  (define-key company-active-map (kbd "<tab>") 'my-tab)
  (define-key company-active-map (kbd "TAB") 'my-tab))
```

Putting it all together:

```lisp
;; bootstrap straight.el
(defvar bootstrap-version)
(let ((bootstrap-file
       (expand-file-name "straight/repos/straight.el/bootstrap.el" user-emacs-directory))
      (bootstrap-version 5))
  (unless (file-exists-p bootstrap-file)
    (with-current-buffer
        (url-retrieve-synchronously
         "https://raw.githubusercontent.com/raxod502/straight.el/develop/install.el"
         'silent 'inhibit-cookies)
      (goto-char (point-max))
      (eval-print-last-sexp)))

;; install copilot.el
(use-package copilot
  :straight (:host github :repo "zerolfx/copilot.el"
                   :files ("dist" "copilot.el"))
  :ensure t)

;; enable completion automatically
(load bootstrap-file nil 'nomessage))(add-hook 'prog-mode-hook 'copilot-mode)

;; enable completion in insert mode
(customize-set-variable 'copilot-enable-predicates '(evil-insert-state-p))

; complete by copilot first, then company-mode
(defun my-tab ()
  (interactive)
  (or (copilot-accept-completion)
      (company-indent-or-complete-common nil)))

; modify company-mode behaviors
(with-eval-after-load 'company
  ; disable inline previews
  (delq 'company-preview-if-just-one-frontend company-frontends)
  ; enable tab completion
  (define-key company-mode-map (kbd "<tab>") 'my-tab)
  (define-key company-mode-map (kbd "TAB") 'my-tab)
  (define-key company-active-map (kbd "<tab>") 'my-tab)
  (define-key company-active-map (kbd "TAB") 'my-tab))
```

After first setting up, login to GitHub, by `SPC :` (in `evil` mode, `C-:` otherwise) then `copilot-login`. This will paste a one time password into your clipboard and open the browser where you need to login with you account and paste the code.

Thats it! Enjoy!
