---
layout: post
title: Basic Linux Resources
subtitle: The resources I used to help make a basic Linux course.
tags: [sysadmin, linux]
comments: false
---


# Basic Linux courses resources (V1.1)
## Linux Basics
## Package Management
### Tarball Example
ftp://ftp.lfs-matrix.net/pub/lfs/lfs-packages/9.1 
### Using Tarballs
https://www.tldp.org/HOWTO/Software-Building-HOWTO-3.html

## Linux Distributions
https://en.wikipedia.org/wiki/Comparison_of_Linux_distributions

https://upload.wikimedia.org/wikipedia/commons/1/1b/Linux_Distribution_Timeline.svg

## Linux File systems
https://en.wikipedia.org/wiki/Category:File_systems_supported_by_the_Linux_kernel

### Filesystem Heirachy Standard
www.pathname.com/fhs

https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard

### Binary Directory Standards
http://lists.busybox.net/pipermail/busybox/2010-December/074114.html

## Progams & Services
### Elf Diagram
![ELF Diagram](https://upload.wikimedia.org/wikipedia/commons/e/e4/ELF_Executable_and_Linkable_Format_diagram_by_Ange_Albertini.png)

### Process Signals
https://linux.die.net/man/7/signal

https://www.bogotobogo.com/Linux/linux_process_and_signals.php

### Sysvinit
https://www.oreilly.com/library/view/essential-system-administration/0596003439/ch04s02.html

https://wiki.gentoo.org/wiki/Sysvinit

### Init System and Daemons (Boot Process)
https://opensource.com/article/17/2/linux-boot-and-startup

https://www.golinuxcloud.com/beginners-guide-systemd-tutorial-linux/

### Understanding the Linux Boot Process - CompTIA Linux+, LPIC-1
[![](https://img.youtube.com/vi/mHB0Z-HUauo/maxresdefault.jpg)](https://youtu.be/mHB0Z-HUauo)

### Common Linux Processess / Daemons
https://www.techrepublic.com/article/linux-101-a-comprehensive-list-of-available-linux-services/

https://meterpreter.org/common-linux-services-list/

## Bash Usage

### Special Characters
https://docstore.mik.ua/orelly/unix/upt/ch08_19.htm

https://mywiki.wooledge.org/BashGuide/SpecialCharacters

### Grep awk and sed tutorial
<https://www-users.york.ac.uk/~mijp1/teaching/2nd_year_Comp_Lab/guides/grep_awk_sed.pdf>

### Awk tutorial
<https://www.tutorialspoint.com/awk/index.htm>

### How to Use tr, sed, and aspell: Linux Terminal 201 - HakTip 170
[![](https://img.youtube.com/vi/F7Brrn-L1Zg/maxresdefault.jpg)](https://youtu.be/F7Brrn-L1Zg)

## User Management
### Home Directory Specifications
https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html

### Passwd file specifications
http://www.linfo.org/etc_passwd.html

## Text Editors

### Vim Cheat sheet for programmers
![vim cheatsheet](http://michael.peopleofhonoronly.com/vim/vim_cheat_sheet_for_programmers_print.png)

### Vim Plugins / Features
http://codyveal.com/posts/vim-killer-features-part-1-text-objects/

https://vimawesome.com

https://www.reddit.com/r/vimporn/

## Regex
### A nice way to test your regex before using it
<https://regexr.com/>

<https://regex101.com/>

### IP Address regex
Not 100% valid, as will match all numbers outside of 255-999, but good for a quick win
`grep -E -o "([0-9]{1,3}[\.]){3}[0-9]{1,3}" file.txt`

The valid way of doing it
`grep -E -o "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)" file.txt`

Credit <https://www.shellhacks.com/regex-find-ip-addresses-file-grep/>


## Bash Scripting
### Internal Variables
you can use `printenv` or for shell scripting the following may be useful
<https://www.tldp.org/LDP/abs/html/internalvariables.html>

I also have found the following variables quire useful, and have used them a lot

variable | explanation
 --- | ---
 $? | Used for capturing the last processes exit code
 $EUID | Captures the user id that started the script, useful for checking sudo UID 0
 $SUDO_USER | Captures the username that started a bash script
 $PWD | present working directory, saves using `$(pwd)`

### Building a Program With Shell Scripting!: Linux Terminal 201 - HakTip 177
[![](https://img.youtube.com/vi/hdcQlmW70KQ/maxresdefault.jpg)](https://youtu.be/hdcQlmW70KQ)

### HakTip - Bash Basics: Turn Long Commands into Scripts
[![](https://img.youtube.com/vi/WBzF1hY0VY8/maxresdefault.jpg)](https://youtu.be/WBzF1hY0VY8)

### How to Write a Shell Script: Linux Terminal 201 - HakTip 175
[![](https://img.youtube.com/vi/hdcQlmW70KQ/maxresdefault.jpg)](https://youtu.be/hdcQlmW70KQ)

### How to Use Cut, Paste, and Join: Linux Terminal 201 - HakTip 168
[![](https://img.youtube.com/vi/k014CkDmB2A/maxresdefault.jpg)](https://youtu.be/k014CkDmB2A)


[Basic Bash guide for beginners (ebook)](https://www.tldp.org/LDP/Bash-Beginners-Guide/html/)

[Basic Bash scripting for beginners (YouTube Playlist)](https://www.youtube.com/playlist?list=PLS1QulWo1RIYmaxcEqw5JhK3b-6rgdWO_)

## Basic Linux commands

[SANS Blue team Command Line Cheat Sheet](https://wiki.sans.blue/Tools/pdfs/LinuxCLI101.pdf)

## Best troubleshooting websites
<https://wiki.archlinux.org/>

<https://askubuntu.com/>

## Over the wire solutions
<https://kongwenbin.wordpress.com/2016/08/02/overthewire-bandit/>

## Scripts and Solutions from the course (Please ask the instructor for the password - Also listed on Day 3 slides  (You may need 7zip to decrypt))
<https://github.com/angry-bender/linuxtraining>

## Arch Linux Installation Fixes

Change your VM to UEFI as per the screenshot below
![VMUEFI](https://angry-bender.github.io/img/lt/vm_uefi.png)

1.I change to pacstrap /mnt base linux linux-firmware

1.t.II install efibootmgr as well

2.b.ii remove Do not conduct

If you use gdm, and cannot get a terminal see screenshot below from <https://unix.stackexchange.com/questions/504529/arch-gnome-terminal-timeout>

![terminal_timeout](https://angry-bender.github.io/img/lt/terminal-timeout.png)



