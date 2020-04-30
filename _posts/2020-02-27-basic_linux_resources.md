---
layout: post
title: Basic Linux Resources
subtitle: The resources I used to help make a basic Linux course.
tags: [sysadmin, linux]
comments: false
---


# Basic Linux courses resources (V2.0)

# Table of Contents

   * [Basic Linux courses resources (V2.0)](#basic-linux-courses-resources-v20)
   * [Bash keyboard commands](#bash-keyboard-commands)
      * [Moving Cursor](#moving-cursor)
      * [Exiting a running command or accessing another command window](#exiting-a-running-command-or-accessing-another-command-window)
      * [Search for text in a file (less, more)](#search-for-text-in-a-file-less-more)
   * [Linux Commands](#linux-commands)
      * [Navigating Linux](#navigating-linux)
      * [Command Line Tricks](#command-line-tricks)
      * [Finding a file](#finding-a-file)
      * [Reading a file](#reading-a-file)
      * [Editing a file](#editing-a-file)
      * [Moving a file](#moving-a-file)
      * [Deleting a file](#deleting-a-file)
      * [Changing Permissions on a file](#changing-permissions-on-a-file)
      * [Comparing a file](#comparing-a-file)
      * [History](#history)
      * [System Utilities](#system-utilities)
      * [Networking](#networking)
         * [The new systemd way (Manual Configuration)](#the-new-systemd-way-manual-configuration)
         * [The new legacy way (Manual Configuration)](#the-new-legacy-way-manual-configuration)
         * [Other network utilities &amp; Troubleshooting tools](#other-network-utilities--troubleshooting-tools)
      * [Ubuntu Package Management](#ubuntu-package-management)
      * [User Management](#user-management)
   * [Basic Forensics Commands](#basic-forensics-commands)
   * [Set a forensics alias.... to you know, forensicate](#set-a-forensics-alias-to-you-know-forensicate)
      * [Grep](#grep)
      * [Sed](#sed)
      * [Awk](#awk)
      * [Regex Reference](#regex-reference)
         * [A nice way to test your regex before using it](#a-nice-way-to-test-your-regex-before-using-it)
         * [IP Address regex](#ip-address-regex)
      * [Other useful tools](#other-useful-tools)
   * [Linux Resources](#linux-resources)
      * [Package Management](#package-management)
         * [Tarball Example](#tarball-example)
         * [Using Tarballs](#using-tarballs)
      * [Linux Distributions](#linux-distributions)
      * [Linux File systems](#linux-file-systems)
         * [Filesystem Heirachy Standard](#filesystem-heirachy-standard)
         * [Binary Directory Standards](#binary-directory-standards)
      * [Progams &amp; Services](#progams--services)
         * [Elf Diagram](#elf-diagram)
         * [Process Signals](#process-signals)
         * [Sysvinit](#sysvinit)
            * [if you want to plau with a sysvinit system](#if-you-want-to-plau-with-a-sysvinit-system)
         * [Sysvinit vs system d (Nice comparison graph)](#sysvinit-vs-system-d-nice-comparison-graph)
         * [Init System and Daemons (Boot Process)](#init-system-and-daemons-boot-process)
         * [Understanding the Linux Boot Process - CompTIA Linux , LPIC-1](#understanding-the-linux-boot-process---comptia-linux-lpic-1)
         * [Common Linux Processess / Daemons](#common-linux-processess--daemons)
      * [Bash Usage](#bash-usage)
         * [Special Characters](#special-characters)
         * [Grep awk and sed tutorial](#grep-awk-and-sed-tutorial)
         * [Awk tutorial](#awk-tutorial)
         * [How to Use tr, sed, and aspell: Linux Terminal 201 - HakTip 170](#how-to-use-tr-sed-and-aspell-linux-terminal-201---haktip-170)
      * [User Management](#user-management-1)
         * [Home Directory Specifications](#home-directory-specifications)
         * [Passwd file specifications](#passwd-file-specifications)
      * [Text Editors](#text-editors)
         * [Vim Cheat sheet for programmers](#vim-cheat-sheet-for-programmers)
         * [Vim Plugins / Features](#vim-plugins--features)
      * [Bash Scripting](#bash-scripting)
         * [Internal Variables](#internal-variables)
         * [Building a Program With Shell Scripting!: Linux Terminal 201 - HakTip 177](#building-a-program-with-shell-scripting-linux-terminal-201---haktip-177)
         * [HakTip - Bash Basics: Turn Long Commands into Scripts](#haktip---bash-basics-turn-long-commands-into-scripts)
         * [How to Write a Shell Script: Linux Terminal 201 - HakTip 175](#how-to-write-a-shell-script-linux-terminal-201---haktip-175)
         * [How to Use Cut, Paste, and Join: Linux Terminal 201 - HakTip 168](#how-to-use-cut-paste-and-join-linux-terminal-201---haktip-168)
      * [Basic Linux commands](#basic-linux-commands)
      * [Best troubleshooting websites](#best-troubleshooting-websites)
      * [Over the wire solutions](#over-the-wire-solutions)
      * [Scripts and Solutions from the course (Please ask the instructor for the password - Also listed on Day 3 slides  (You may need 7zip to decrypt))](#scripts-and-solutions-from-the-course-please-ask-the-instructor-for-the-password---also-listed-on-day-3-slides--you-may-need-7zip-to-decrypt)
      * [Arch Linux Installation Fixes](#arch-linux-installation-fixes)
      


# Bash keyboard commands
The mouse won’t work, use the left/right arrow keys to move around the line.

When the cursor is where you want it in the line, typing inserts text – i.e. it doesn’t always overtype what’s already there.

[*Back to table of contents*](#Table-of-Contents)

## Moving Cursor
**Ctrl + A** or Home	Moves the cursor to the Start of a line.

**Ctrl + E** or End		Moves the cursor to the End of a line.

**ESC + B**			Moves to the Beginning of the previous or current word.

**Ctrl + K**			Deletes form the current cursor position to the end of the line.

**Ctrl + U**			Deletes from the start of the line to the current cursor position.

**Ctrl + W**		Deletes the WORD before the cursor.

**ALT + B**			Moves Back one word at a time

**ALT + F**			Moves Forward one word at a time

**ALT + C**		capitalises letter where cursor is and moves to end of word

## Exiting a running command or accessing another command window

**Ctrl + C**			Kills the current Process

**Ctrl + Alt + F1-6**		Changes terminals (Up to 6)

**Ctrl + Z**		Suspends the current process (Can be bought back by typing fg)

## Search for text in a file (less, more)

**/pattern**		Searches forward n for next N for previous

# Linux Commands
## Navigating Linux

Command | Description
-------|--------
`pwd`	| Where am I
`whoami`	| who am I
`id	`| list my user and groups
`ls –al `|	What is in the location
`cd <Directory Name>` | change directory 
`cd ~` | change to home directory
`cd ..` | change up a directory
`cd -` | go back to where you were
`w` | Who is logged on and what are the doing
`who` | Who is logged onto and what is there session
`cat /etc/*release*` | System information
`uname -r` | System information
`man <command> ` | Traditional unix era help system
`info <command>` | GNU projects helps system, typically more comprehensive, not installed by default
`apropos` | search all man pages for a given keyword alias of `man -k <searchterm>`
`man <cat number> <command>` | view a man page other than the default command manpage

## Command Line Tricks

Command | Description
-------|--------
`History`	| lists command history
`!<number from history>`	| Executes that command from history
`!<string>` |	Repeat last command that started with <string>
`!?<string>` |	Repeat last command that has substring <string>
`!!:s/foo/bar/` |	Repeat last command substituting foo for bar
`grep`	 | allows you to search the output for a pattern, i.e. cat /var/log/auth.log \| grep <username> 

## Finding a file

Command | Description
-------|--------
`sudo updatedb`	| Update the locatedb
`locate <filename>` | 	locate somefilename
`find <directory>` or `. <filename>` |	find a file in a directory or where I am with a name
 
## Reading a file

Command | Description
-------|--------
`Cat <filename>`	| List the contents of a file 
`less <filename>`	| Browse through a file
`head <filename>`	| shows first 10 lines of file, can be changed with –n <number of lines>
`tail <filename>`	| shows last 10 lines of file, can be changed with –n <number of lines>
`tail –f <filename>` |	Display the last 10 lines and follow a files as it grows (Very useful for debugging)
`file <filename>` | Displays what kind of file it is
 
## Editing a file

Command | Description
-------|--------
`touch <filename>` | make an empty file
`echo "hello world" > file.txt` | create or overwrite a file with one line, saying hello world
`echo "Hello world 2" >> file.txt` | append a new line to a file
`vim <filename>`	| advanced text editor for file name
`nano <filename>`	| basic text editor for file name

## Moving a file

Command | Description
-------|--------
`cp <Source> <destination>`	| copies a file, use –r to copy directories	
`mv <source> <destination>`	| moves a file or renames a file, use –r for directories	
`scp <source> <destination>`	| Secure copy over ssh for example **scp file.txt user@server:/tmp/**
`rsync –a <source> <Destination>` |	very useful for coping LARGE files and directories, has options for retaining permissions	
`wget http://www.webserver.com/file.txt` | downloads a text file from webserver.com	
`git clone https://www.github.com/angry-bender/UbuntuLive.git` | Downloads a git project 	

## Deleting a file

Command | Description
-------|--------
`rm <filename>	`| removes a filename
`rm –r <directoryname>` |	removes a directory and all sub directories
`rm –rf <directoryname>`	| forces removal of a directory
 
## Changing Permissions on a file
![permissions](https://2.bp.blogspot.com/-V2eWUJugBJ0/Ui4Y1TJ45aI/AAAAAAAAAzQ/gwxcb-GlTGA/s1600/chmod4.png)
![usergroupother](https://www.booleanworld.com/wp-content/uploads/2018/04/classes.png)

Command | Description
-------|--------
`chown <user>:<group>` |	Changes ownership on a file
`chmod 754 <filename>` |	Changes the permissions on a file Number Sequence User, Group, Others 4 = Read,2 = Write,1 = Execute, 0 = No Permission,(4+2+1=7)
`chmod u=rwx,g=rx,o=r`	 | Changes the permissions on a file u=user,g=group,o=others r=read,w=write,x=execute
`chgrp <group> <filename>` | change the froup owner of a file or folder
 
## Comparing a file

Command | Description
-------|--------
`diff –ur <filename1> <filename2>` |	Compares the difference between two files, without –ur it will just tell us if there is a difference

## History

Command | Description
-------|--------
`History` |	lists command history
`History 5 `| Lists the 5 previous commands
`!<number from history>`	| Executes that command from history
**ctrl-r** | press to search the history, continue pressing to scroll one at a time through search results
 
## System Utilities

Command | Description
-------|--------
`fdisk –l `|	Lists disks and partitions
`df`	| Lists the mount points for inserted disks
`ps –aux` (Old way) `ps -elf` (New Way) |	Lists the running processes
`ps -lfu` | lists processess started by a user
`top`	| Lists processes in order
`kill <pid>` |	Kill a Running process
`systemctl -l --type service --all` |	Lists all the running Services
`systemctl <start / stop / restart / status> <service>`	| stop\|start\|restart or get status of a service
`systemctl list-unit-files --state=enabled` | list startup services
`journalctl –r`	| View the system log from the most recent entry, to start from the oldest entry use no –r (can be the same as cat /var/log/syslog
`journalctl -u <servicename>`	| View logs about a particular service
`journalctl -k `	| View only kernel messages
`journalctl -f`	| follow messages as they appear
`sudo mount <device> <directory>`	| mount a hard drive or usb
`systemctl <disable / enable> <service>`	| enable or disable a system service on startup
`systemctl <reboot / poweroff  /emergency / default>` |	Reboots, power’s off, enters into single user recovery mode, restores normal operation
`lsblk`	| lists basic hard drive information
`lspci`	| lists all pci hardware connected to the computer
`tar -xzf <filename>` |	extract tar.gz
`tar -zcvf <tarname>.tar.gz <source-folder-name>` |	make a tar.gz file
`zcat secure*.gz` | cats out gz log files
`ln -s <location of link> <location of file>` | make a softlink to a file

## Networking

### The new systemd way (Manual Configuration)

Command | Description | Order
-------|--------|------
`ip addr`|List your ip interfaces or addresses |	1
`sudo ip link set <interfacename> up` |	Set the interface to be up	| 2
`sudo dhclient`	| get a DHCP address	| 3
`ip addr add 192.168.0.3/24` dev <interfacename> |	Enter a static ip address	| 3
`ip addr`	| verify your configuration	| 4

### The new legacy way (Manual Configuration)

Command | Description | Order
-------|--------|------
`ifconfig	`|List your interfaces or addresses	| 1
`ifconfig <interfacename> up`	| Set the interface to be up	| 2
`ifconfig <interfacename> 0.0.0.0 0.0.0.0 && dhclient`	| get a DHCP address |	3
`ifconfig <interfacename> 192.168.0.3/24 netmask 255.255.255.0`	| Enter a static ip address |	3
`ifconfig` 	| verify your configuration	| 4

### Other network utilities & Troubleshooting tools

Command | Description
-------|--------
`dig` / `host` / `nslookup` |	DNS Lookup utility
`nslookup`	| Simple DNS record lookup
`nmtui`	 / `nmcli` | network manager terminal user interface
`whois`	| domain record lookup
`vi /etc/resolv` | edit dns servers (**Manual Override**)
`ip route` | view routes and default gateway
`ip neighbour` | equivalent to windows arp command
`ip link` | Interface status and MAC Addressess
`ip addr` | Show ip addressess
`ip route <add / del> <net / CIDR> via <IP> dev <int>` | Add or remove static route
`ip route add default via <IP>` | Add Default route
`ss` | Netstat equivalant (`-tu` minimum info, `-put` process info, `-4put` show ipv4 only, `4punt` show ports as numbers

## Ubuntu Package Management

Command | Description
-------|--------
`apt install <packagename>` |	Installs a package
`apt remove <packagename>	`| Removes a package
`apt purge <packagename>`	| Removes a package and all its configuration
`apt update`	| Updates the package lists
`apt upgrade`	| Upgrades packages
`apt autoremove`	| Removes unneeded packages after updates
`apt list --installed` |	List installed packages
`dpkg –i <packagename>`	| install a package from a <.deb> file
`dpkg –r <packagename>`	| remove a package installed by <.deb> file
`dpkg --list	` | list all installed packages
`fuser -k /var/lib/apt/lists/lock`	| Tries to kill the process accessing the package lock file gracefully
`lsof -t /var/lib/apt/lists/lock \| xargs kill -9`	| Tries to kill the process accessing the package lock file ungracefully <Use with caution>
 
## User Management
 
Command | Description
-------|--------
`useradd -m -d /home/<username> -c "Full name" <username>`	| adds a user and creates their home directory	
`usermod -aG <Groupname> <username>` |	Add user to a group	
`userdel -r -f <username>` | forces removal of user and home directory
`groupadd <groupname>`	| adds a group	
`groupdel <groupname>`	| deletes a group	
`vigr` | edits groups
`passwd <username>` | change a users password
`cat /etc/group` |	List groups on system	
`cat /etc/passwd`	| List users on system	
`echo <Username>\|<Password> \| chpassword	` | Allows passwords to be scripted in bash for new users	
`su - <username>` | switch to a new user and use their shell environment

# Basic Forensics Commands

# Set a forensics alias.... to you know, forensicate
open your `~/.bashrc`

add the following line to the end


![bash](https://angry-bender.github.io/img/lt/bash.png)

`alias forensicate="sort | uniq -c | sort -nr`

then, after using an awk, or any method of reducing data down to a single character, pipe it to forensicate, and get your quick wins

![forensicate](https://angry-bender.github.io/img/lt/forensicate.png)

## Grep

Command | Description
-------|--------
`grep “boo” <filename>`	| Standard GREP
`grep –n “boo” <filename>`| 	Prints a line number where the value is present
`grep –vn “boo” <filename>`| 	opposite of the expression you’ve entered
`grep –c “boo” <filename>`| 	prints how many times <string> is present
`grep –l “boo” *`|	prints filenames that contain boo
`grep –i  “BOO”  <filename>`|	ignores case
`grep –x “boo”  <filename>	`| Exact Matches
`grep –A2 “aara” <filename> `|	Prints extra lines for Context
`grep –E “e$” <filename>	`| Use a Regular expression 
`egrep ‘<pattern1>\|<pattern2>’ <filename>	`| enhanced grep to search for two patterns simultaneously

## Sed

Command | Description
-------|--------
`sed -e ‘s/<search>/<replace>/’ <filename>` |	Searches for <search> and replaces the first instance with <replace> on each line
`sed -e ‘s/<search>/<replace>/2’ <filename>` |	Searches for <search> and replaces the second instance with <replace> on each line
`sed -e ‘1s/<search>/<replace>/1’ <filename>` | Searches for and replaces on a single line
`sed -e ‘1,4s/<search>/<replace>/1’ <filename>` | Searches for and replaces on the first 4 lines
`sed -e ‘s/<search>/<replace>/g’ <filename>` |	Replaces every instance of <search> for with <replace> Globally
`sed -i -e  ‘s/<search>/<replace>/g’ <filename>` |	edits and existing file and replaces the string
`sed -e ‘s/[0-9]*/(&)/’ <filename>` |	Replaces ([0-9]) for a number of any length (*) and inserts a Bracket around them (&)
`sed -e ‘/s/\/etc/\/etc\/ssh\/sshd_conf/’` | <filename>	Replaces /etc/ with /etc/ssh/sshd.conf


## Awk

Command | Description
-------|--------
`awk [OPTIONS] filename`	|Pattern scanning and text processing
`awk -f <awkfile> filename` |	Allows the use of an awkfile for processing
`awk ‘{print $3}’` |	prints all the 3’rd arguments in a file


## Regex Reference

### A nice way to test your regex before using it
<https://regexr.com/>

<https://regex101.com/>

### IP Address regex

Not 100% valid, as will match all numbers outside of 255-999, but good for a quick win

`grep -E -o "([0-9]{1,3}[\.]){3}[0-9]{1,3}" file.txt`

The valid way of doing it

`grep -E -o "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)" file.txt`

Credit <https://www.shellhacks.com/regex-find-ip-addresses-file-grep/>

Symbol  | Description
-------|--------
`. `	| replaces any character 
`^` 	| matches start of string 
`$ `	| matches end of string 
`*` |	matches up zero or more times the preceding character 
`\` | 	Represent special characters 
`() `	| Groups regular expressions 
`?` |	Matches up exactly one character 
`|` | 	One OR another character / string I.E boot\|boots
`[abcde]`	| Match any of the listed characters
`[a-e]`	| Match any character in the range
`[!abcde]`	| match any character that’s not listed
`[!a-e]` | match and character not in the range
`{linux, shell}` |	match any word in the given options

## Other useful tools

Command | Description
-------|--------
`tr a-z`	| Replaces any lowercase letters with uppercase letters
`tr -s t`	| removes any duplicates of the letter t
`cut`	| Remove sections from each line of files
`paste`	| Inserts Sections into each line of files
`join`	| Join files together
`sort`	| Sort a file by a five order
`uniq ` | Report or filter out repeated lines in a file
`aspell check <filename>` |	spell checks a file interactively 

# Linux Resources
## Package Management
### Tarball Example
<ftp://ftp.lfs-matrix.net/pub/lfs/lfs-packages/9.1> 
### Using Tarballs
<https://www.tldp.org/HOWTO/Software-Building-HOWTO-3.html>

## Linux Distributions
<https://en.wikipedia.org/wiki/Comparison_of_Linux_distributions>

<https://upload.wikimedia.org/wikipedia/commons/1/1b/Linux_Distribution_Timeline.svg>

## Linux File systems
<https://en.wikipedia.org/wiki/Category:File_systems_supported_by_the_Linux_kernel>

### Filesystem Heirachy Standard
<http://www.pathname.com/fhs>

<https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard>

### Binary Directory Standards
<http://lists.busybox.net/pipermail/busybox/2010-December/074114.html>

## Progams & Services
### Elf Diagram
![ELF Diagram](https://upload.wikimedia.org/wikipedia/commons/e/e4/ELF_Executable_and_Linkable_Format_diagram_by_Ange_Albertini.png)

### Process Signals
<https://linux.die.net/man/7/signal>

<https://www.bogotobogo.com/Linux/linux_process_and_signals.php>

### Sysvinit
<https://www.oreilly.com/library/view/essential-system-administration/0596003439/ch04s02.html>

<https://wiki.gentoo.org/wiki/Sysvinit>

#### if you want to plau with a sysvinit system
http://ftp.iij.ad.jp/pub/linux/centos-vault/6.0/isos/x86_64/CentOS-6.0-x86_64-LiveDVD.iso

### Sysvinit vs system d (Nice comparison graph)
<https://access.redhat.com/articles/1189123>

### Init System and Daemons (Boot Process)
<https://opensource.com/article/17/2/linux-boot-and-startup>

<https://www.golinuxcloud.com/beginners-guide-systemd-tutorial-linux/>

### Understanding the Linux Boot Process - CompTIA Linux+, LPIC-1
[![](https://img.youtube.com/vi/mHB0Z-HUauo/maxresdefault.jpg)](https://youtu.be/mHB0Z-HUauo)

### Common Linux Processess / Daemons
<https://www.techrepublic.com/article/linux-101-a-comprehensive-list-of-available-linux-services/>

<https://meterpreter.org/common-linux-services-list/>

## Bash Usage

### Special Characters
<https://docstore.mik.ua/orelly/unix/upt/ch08_19.htm>

<https://mywiki.wooledge.org/BashGuide/SpecialCharacters>

### Grep awk and sed tutorial
<https://www-users.york.ac.uk/~mijp1/teaching/2nd_year_Comp_Lab/guides/grep_awk_sed.pdf>

### Awk tutorial
<https://www.tutorialspoint.com/awk/index.htm>

### How to Use tr, sed, and aspell: Linux Terminal 201 - HakTip 170
[![](https://img.youtube.com/vi/F7Brrn-L1Zg/maxresdefault.jpg)](https://youtu.be/F7Brrn-L1Zg)

## User Management
### Home Directory Specifications
<https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html>

### Passwd file specifications
<http://www.linfo.org/etc_passwd.html>

## Text Editors

### Vim Cheat sheet for programmers
![vim cheatsheet](http://michael.peopleofhonoronly.com/vim/vim_cheat_sheet_for_programmers_print.png)

### Vim Plugins / Features
<http://codyveal.com/posts/vim-killer-features-part-1-text-objects/>

<https://vimawesome.com>

<https://www.reddit.com/r/vimporn/>



## Bash Scripting
### Internal Variables
you can use `printenv` or for shell scripting the following may be useful
<https://www.tldp.org/LDP/abs/html/internalvariables.html>

I also have found the following variables quire useful, and have used them a lot

variable | explanation
----- | -----
` $? ` | Used for capturing the last processes exit code
`$EUID` | Captures the user id that started the script, useful for checking sudo UID 0
`$SUDO_USER ` | Captures the username that started a bash script
`$PWD ` | present working directory, saves using `$(pwd)`

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
