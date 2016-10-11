---
layout: post
title: Useful Linux Command - tee
subtitle: Various and interesting usage of tee command
bigimg: /img/tea-tee.jpg
---

The function of `tee` command, as described in its man page, is
```
tee - read from standard input and write to standard output and files
```
The first time I saw this command, I was wondering why I need to that. If I want to check what was written into the file, just use `cat` to show the content of the file. Well, one obvious situation where you may want to use `tee` is to display the output of a command and save the output to file for later reference. 

In addition to this common usage, there are some special cases where `tee` can come in handy.

## Pipe needs root privilege

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
Again it does not work because `sudo` does not apply to the redirection. With `tee` you can achieve your goal with
```
wget -O- http://example.com/hostsfile | sudo tee -a /etc/hosts
```
