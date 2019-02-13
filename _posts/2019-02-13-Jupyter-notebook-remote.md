---
layout: post
title: Using Jupyter notebooks securely on remote linux machines
gh-badge: [star, fork, follow]
tags: [Jupyter, Notebook, Python, Jupyter Notebook]
---

## Run jupyter notebook remotely first

- Start jupyter notebook within your tmux session. The --no-browser option prevents jupyter from automatically opening a browser window.

```bash
jupyter notebook --no-browser
```

- The next step is to use an SSH tunnel to forward a port on your local machine to the remote machine. You can think of this as connecting port 8157 on your local machine to port 8888 (the default jupyter notebook port) on the remote machine.

## Run from your local machine

```bash
ssh -NL 8157:localhost:8888 user@your-remote-machine
```

That`s it. Now you are working in your remote notebook from your local machine.