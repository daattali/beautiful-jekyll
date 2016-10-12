---
layout: post
title: Useful Linux Command - tee
subtitle: Various and interesting usage of tee command
bigimg: /img/tee-tea.jpg
---

The function of `tee` command, as described in its man page, is

```
tee - read from standard input and write to standard output and files
```

The first time I saw this command, I was wondering why I need that. If I want to check what was written into the file, just use `cat` to show the content of the file. Well, one obvious situation where you may want to use `tee` is to display the output of a command and save the output to file for later reference.

In addition to this common usage, there are some special cases where `tee` can come in handy.

### Pipe needs root privilege

Sometimes you need to send the output to a file which requires root privilege. Say you are downloading some domain resolution entries for your organization's internal servers. You want to add them to the `/etc/hosts` file. Normally you issue a command like this

```
wget -O- http://example.com/hostsfile >> /etc/hosts
```

Unfortunately this does not work and you are told that

```
bash: /etc/hosts: Permission denied
```

because you don't have write permission to the hosts file. Now you will probably try this

```
sudo wget -O- http://example.com/hostsfile  >> /etc/hosts
```

Again it does not work because `sudo` only applies to `wget` and it cannot reach the redirection target. With `tee` you can achieve your goal with

```
wget -O- http://example.com/hostsfile | sudo tee -a /etc/hosts
```

The `-a` option sets the output to be *appended*.

### Vim needs root privilege

Another situation is that people like me often forget to run `vim` with `sudo` to modify system config files. For example, you want to modify some configuration entries for PHP, with the following command

```
vim /etc/php5/apache2/php.ini
```

Once you've done the changes, you start type `:wq` to save and exit the editor. Oops! Vim tells you that you don't have permission:

```
E45: 'readonly' option is set (add ! to override)
```

Is it unfortunate that you have to close the editor without saving the changes and reopen it with `sudo` and redo all the changes? Absolutely not. What I used to do was to use `:save` command to save the current content to somewhere I have write permission and then use `sudo mv` to overwrite the actual config file I would like to change. But that seems a little bit too much typing. Now you can solve this problem in place with `tee`. Type the following command in Vim:

```
:w !sudo tee %
```

This basically tells vim to run a shell command `sudo tee` with the current file name `%`. Note that Vim will warn you that the file content has changed. This is because the overwrite is conducted outside Vim. But that's fine.
