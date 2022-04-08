HA – Z Linux Commands – Overview with Examples

## On this page

1.  [adduser/addgroup](#adduser/addgroup)
2.  [agetty](#agetty)
3.  [alias](#alias)
4.  [anacron](#anacron)
5.  [apropos](#apropos)
6.  [apt](#apt)
7.  [apt-get](#apt-get)
8.  [aptitude](#aptitude)
9.  [arch](#arch)
10.  [arp](#arp)
11.  [at](#at)
12.  [atq](#atq)
13.  [atrm](#atrm)
14.  [awk](#awk)
15.  [batch](#batch)
16.  [basename](#basename)
17.  [bc](#bc)
18.  [bg](#bg)
19.  [bzip](#bzip)
20.  [cal](#cal)
21.  [cat](#cat)
22.  [chgrp](#chgrp)
23.  [chmod](#chmod)
24.  [chown](#chown)
25.  [cksum](#cksum)
26.  [clear](#clear)
27.  [cmp](#cmp)
28.  [comm](#comm)
29.  [cp](#cp)
30.  [date](#date)
31.  [dd](#dd)
32.  [df](#df)
33.  [diff](#diff)
34.  [dir](#dir)
35.  [dmidecode](#dmidecode)
36.  [du](#du)
37.  [echo](#echo)
38.  [eject](#eject)
39.  [env](#env)
40.  [exit](#exit)
41.  [expr](#expr)
42.  [factor](#factor)
43.  [find](#find)
44.  [free](#free)
45.  [grep](#grep)
46.  [groups](#groups)
47.  [gzip](#gzip)
48.  [gunzip](#gunzip)
49.  [head](#head)
50.  [history](#history)
51.  [hostname](#hostname)
52.  [hostnamectl](#hostnamectl)
53.  [hwclock](#hwclock)
54.  [hwinfo](#hwinfo)
55.  [id](#id)
56.  [ifconfig](#ifconfig)
57.  [ionice](#ionice)
58.  [iostat](#iostat)
59.  [ip](#ip)
60.  [iptables](#iptables)
61.  [iw](#iw)
62.  [iwlist](#iwlist)
63.  [kill](#kill)
64.  [killall](#killall)
65.  [kmod](#kmod)
66.  [last](#last)
67.  [ln](#ln)
68.  [locate](#locate)
69.  [login](#login)
70.  [ls](#ls)
71.  [lshw](#lshw)
72.  [lscpu](#lscpu)
73.  [lsof](#lsof)
74.  [lsusb](#lsusb)
75.  [man](#man)
76.  [mdsum](#mdsum)
77.  [mkdir](#mkdir)
78.  [more](#more)
79.  [mv](#mv)
80.  [nano](#nano)
81.  [nc/netcat](#nc/netcat)
82.  [netstat](#netstat)
83.  [nice](#nice)
84.  [nmap](#nmap)
85.  [nproc](#nproc)
86.  [openssl](#openssl)
87.  [passwd](#passwd)
88.  [pidof](#pidof)
89.  [ping](#ping)
90.  [ps](#ps)
91.  [pstree](#pstree)
92.  [pwd](#pwd)
93.  [rdiff-backup](#rdiff-backup)
94.  [reboot](#reboot)
95.  [rename](#rename)
96.  [rm](#rm)
97.  [rmdir](#rmdir)
98.  [scp](#scp)
99.  [shutdown](#shutdown)
100.  [sleep](#sleep)
101.  [sort](#sort)
102.  [split](#split)
103.  [ssh](#ssh)
104.  [stat](#stat)
105.  [su](#su)
106.  [sudo](#sudo)
107.  [sum](#sum)
108.  [tac](#tac)
109.  [tail](#tail)
110.  [talk](#talk)
111.  [tar](#tar)
112.  [tee](#tee)
113.  [tree](#tree)
114.  [time](#time)
115.  [top](#top)
116.  [touch](#touch)
117.  [tr](#tr)
118.  [uname](#uname)
119.  [uniq](#uniq)
120.  [uptime](#uptime)
121.  [users](#users)
122.  [vim/vi](#vim/vi)
123.  [w](#w)
124.  [wall](#wall)
125.  [watch](#watch)
126.  [wc](#wc)
127.  [wget](#wget)
128.  [whatis](#whatis)
129.  [which](#which)
130.  [who](#who)
131.  [whereis](#whereis)
132.  [xargs](#xargs)
133.  [yes](#yes)
134.  [youtube-dl](#youtube-dl)
135.  [zcmp/zdiff](#zcmp/zdiff)
136.  [zip](#zip)
137.  [zz](#zz)

There are a countless number of commands in Linux. We are bound to use a number of them on a daily routine or numerous times to perform common tasks than others. It is important to note that certain commands are “distro-based” – they can only be found in specific distros. While others are generic Unix/Linux commands that you’ll find in all if not most mainstream distros.

In this article, we will introduce you a list of most frequently used Linux commands with their examples for easy learning. You can find the actual description of each Linux command in their manual page which you can access like this:

$ man command-name

## adduser/addgroup

The **adduser** and **addgroup** commands are used to add a user and group to the system respectively according to the default configuration specified in **/etc/adduser.conf** file.

$ sudo adduser tecmint

For more **adduser** and **addgroup** commands: [15 Practical Examples on adduser Command in Linux](https://www.tecmint.com/add-users-in-linux/)

## agetty

**agetty** is a program which manages physical or virtual terminals and is invoked by **init**. Once it detects a connection, it opens a tty port, asks for a user’s login name and calls up the **/bin/login** command. **Agetty** is a substitute of Linux **getty**:

$ agetty -L 9600 ttyS1 vt100

## alias

**alias** is a useful shell built-in command for creating aliases (shortcut) to a Linux command on a system. It is helpful for creating new/custom commands from existing Shell/Linux commands (including options):

$ alias home='cd /home/tecmint/public\_html'

The above command will create an alias called **home** for **/home/tecmint/public\_html** directory, so whenever you type **home** in the terminal prompt, it will put you in the **/home/tecmint/public\_html** directory.

## anacron

[anacron](https://www.tecmint.com/cron-vs-anacron-schedule-jobs-using-anacron-on-linux/) is a Linux facility used to run commands periodically with a frequency defined in days, weeks and months.

Unlike its sister [cron](https://www.tecmint.com/11-cron-scheduling-task-examples-in-linux/); it assumes that a system will not run continuously, therefore if a scheduled job is due when the system is off, it’s run once the machine is powered on.

For more information about **anacron** and **cron** read: [Cron Vs Anacron: How to Schedule Jobs Using Anacron on Linux](https://www.tecmint.com/cron-vs-anacron-schedule-jobs-using-anacron-on-linux/)

## apropos

**apropos** command is used to [search and display a short man page description](https://www.tecmint.com/find-linux-command-description-and-location/) of a command/program as follows.

$ apropos adduser

## apt

[apt](https://www.tecmint.com/apt-advanced-package-command-examples-in-ubuntu/) tool is a relatively new higher-level package manager for Debian/Ubuntu systems:

$ sudo apt update

For more apt usage read: [15 Useful Examples on APT Command](https://www.tecmint.com/apt-advanced-package-command-examples-in-ubuntu/)

## apt-get

[apt-get](https://www.tecmint.com/useful-basic-commands-of-apt-get-and-apt-cache-for-package-management/) is a powerful and free front-end package manager for Debian/Ubuntu systems. It is used to install new software packages, remove available software packages, upgrade existing software packages as well as upgrade entire operating system.

$ sudo apt-get update

For more apt-get usage, read: [25 Useful Commands of APT-GET for Package Management](https://www.tecmint.com/useful-basic-commands-of-apt-get-and-apt-cache-for-package-management/)

## aptitude

**aptitude** is a powerful text-based interface to the Debian GNU/Linux package management system. Like **apt-get** and **apt**; it can be used to install, remove or upgrade software packages on a system.

$ sudo aptitude update

For more usage on aptitude, read: [Learn Debian Package Management with Aptitude Command](https://www.tecmint.com/linux-package-management/)

## arch

**arch** is a simple command for displaying machine architecture or hardware name (similar to **uname -m**):

$ arch 

## arp

**ARP** (**Address Resolution Protocol**) is a protocol that maps IP network addresses of a network neighbor with the hardware (MAC) addresses in an IPv4 network.

You can use it as below to find all alive hosts on a network:

$ sudo arp-scan --interface=enp2s0 --localnet  

## at

[at command](https://www.tecmint.com/linux-cron-alternative-at-command-to-schedule-tasks/) is used to schedule tasks to run in a future time. It’s an alternative to **cron** and **anacron**, however, it runs a task once at a given future time without editing any config files:

For example, to shutdown the system at 23:55 today, run:

$ sudo echo "shutdown -h now" | at -m 23:55

## atq

**atq** command is used to view jobs in **at command** queue:

$ atq

## atrm

**atrm** command is used to remove/deletes jobs (identified by their job number) from at command queue:

$ atrm 2

For more usage about **at** command, read: [How to Use ‘at’ Command to Schedule a Task in Linux](https://www.tecmint.com/linux-cron-alternative-at-command-to-schedule-tasks/)

## awk

[Awk](https://www.tecmint.com/category/awk-command/) is a powerful programming language created for text processing and generally used as a data extraction and reporting tool.

$ awk '//{print}'/etc/hosts

For more Awk concepts (basic and advance) with simple and easy-to-understand, we’ve created a book that contains 13 chapters with a total of 41 pages, which covers all Awk basic and advance usage with practical examples: [Awk Getting Started Guide for Beginners](https://www.tecmint.com/linux-awk-command-book-for-beginners/)

## batch

**batch** is also used to schedule tasks to run a future time, similar to the [at command](https://www.tecmint.com/linux-cron-alternative-at-command-to-schedule-tasks/).

## basename

**basename** command helps to print the name of a file stripping of directories in the absolute path:

$ basename bin/findhosts.sh

## bc

**bc** is a simple yet powerful and arbitrary precision CLI calculator language which can be used like this:

$ echo 20.05 + 15.00 | bc

## bg

**bg** is a command used to send a process to the background.

$ tar -czf home.tar.gz .
$ bg 
$ jobs

To learn more about bg command, read: [Start Linux Command in Background and Detach Process in Terminal](https://www.tecmint.com/run-linux-command-process-in-background-detach-process/)

## bzip2

[bzip2](https://www.tecmint.com/linux-compress-decompress-bz2-files-using-bzip2/) command is used to compress or decompress file(s).

$ bzip2 -z filename      #Compress
$ bzip2 -d filename.bz2  #Decompress

To learn more examples on bzip2, read: [How to Compress and Decompress a .bz2 File in Linux](https://www.tecmint.com/linux-compress-decompress-bz2-files-using-bzip2/)

## cal

The **cal** command print a calendar on the standard output.

$ cal

## cat

[cat command](https://www.tecmint.com/13-basic-cat-command-examples-in-linux/) is used to view contents of a file or concatenate files, or data provided on standard input, and display it on the standard output.

$ cat file.txt

To learn more about cat command, read: [13 Useful Cat Command Examples on Linux](https://www.tecmint.com/13-basic-cat-command-examples-in-linux/)

## chgrp

**chgrp** command is used to change the group ownership of a file. Provide the new group name as its first argument and the name of file as the second argument like this:

$ chgrp tecmint users.txt

## chmod

**chmod** command is used to change/update file access permissions like this.

$ chmod +x sysinfo.sh

## chown

**chown** command changes/updates the user and group ownership of a file/directory like this.

$ chmod -R www-data:www-data /var/www/html

To learn more about chgrp, chmod and chwon commands, read: [Managing Users & Groups, File Permissions & Attributes in Linux](https://www.tecmint.com/manage-users-and-groups-in-linux/)

## cksum

**cksum** command is used to display the CRC checksum and byte count of an input file.

$ cksum README.txt

## clear

**clear** command lets you clear the terminal screen, simply type.

$ clear

## cmp

**cmp** performs a byte-by-byte comparison of two files like this.

$ cmp file1 file2

## comm

**comm** command is used to compare two sorted files line-by-line as shown below.

$ comm file1 file2

## cp

**cp** command is used for copying files and directories from one location to another.

$ cp /home/tecmint/file1 /home/tecmint/Personal/

For more information on how to copy files in Linux, read:

1.  [How to Copy a File to Multiple Directories in Linux](https://www.tecmint.com/copy-file-to-multiple-directories-in-linux/)
2.  [Advanced Copy Command – Shows Progress Bar While Copying Large Files/Folders in Linux](https://www.tecmint.com/advanced-copy-command-shows-progress-bar-while-copying-files/)
3.  [Progress – A Tiny Tool to Monitor Progress for (cp, mv, dd, tar, etc.) Commands in Linux](https://www.tecmint.com/progress-monitor-check-progress-of-linux-commands/)

## date

**date** command displays/sets the system date and time like this.

$ date
$ date --set="8 JUN 2017 13:00:00"

To learn more about how to set date in Linux, read: [How to Set System Date in Linux](https://www.tecmint.com/set-time-timezone-and-synchronize-time-using-timedatectl-command/)

## dd

**dd** command is used for copying files, converting and formatting according to flags provided on the command line. It can strip headers, extracting parts of binary files and so on.

The example below shows creating a boot-able USB device:

$ dd if=/home/tecmint/kali-linux-1.0.4-i386.iso of=/dev/sdc1 bs=512M; sync

## df

[df command](https://www.tecmint.com/how-to-check-disk-space-in-linux/) is used to show file system disk space usage as follows.

$ df -h

For more usage on df command, read: [12 Useful ‘df’ Command Examples to Check Disk Space](https://www.tecmint.com/how-to-check-disk-space-in-linux/)

## diff

[diff command](https://www.tecmint.com/compare-find-difference-between-two-directories-in-linux/) is used to compare two files line by line. It can also be used to [find the difference between two directories](https://www.tecmint.com/best-linux-file-diff-tools-comparison/) in Linux like this:

$ diff file1 file2

Some useful diff tools for Linux: [8 Best File Comparison and Difference (Diff) Tools for Linux](https://www.tecmint.com/best-linux-file-diff-tools-comparison/)

## dir

[dir command](https://www.tecmint.com/linux-dir-command-usage-with-examples/) works like Linux [ls command](https://www.tecmint.com/tag/linux-ls-command/), it lists the contents of a directory.

$ dir

## dmidecode

[dmidecode command](https://www.tecmint.com/how-to-get-hardware-information-with-dmidecode-command-on-linux/) is a tool for retrieving hardware information of any Linux system. It dumps a computer’s DMI (a.k.a SMBIOS) table contents in a human-readable format for easy retrieval.

To view your system hardware info, you can type:

$ sudo dmidecode --type system

Some useful tools to find out Linux system hardware info: [10 Useful Commands to Get Linux Hardware Information](https://www.tecmint.com/commands-to-collect-system-and-hardware-information-in-linux/)

## du

[du command](https://www.tecmint.com/check-linux-disk-usage-of-files-and-directories/) is used to show disk space usage of files present in a directory as well as its sub-directories as follows.

$ du /home/aaronkilik

## echo

[echo command](https://www.tecmint.com/echo-command-in-linux/) prints a text of line provided to it.

$ echo “This is TecMint - Linux How Tos”

## eject

**eject command** is used to eject removable media such as DVD/CD ROM or floppy disk from the system.

$ eject /dev/cdrom
$ eject /mnt/cdrom/
$ eject /dev/sda

## env

**env command** lists all the current environment variables and used to set them as well.

$ env

Learn more on [How to Set and Unset Environment Variables in Linux](https://www.tecmint.com/set-unset-environment-variables-in-linux/)

## exit

**exit command** is used to exit a shell like so.

$ exit

## expr

**expr command** is used to calculate an expression as shown below.

$ expr 20 + 30

## factor

**factor command** is used to show the prime factors of a number.

$ factor 10

## find

[find command](https://www.tecmint.com/35-practical-examples-of-linux-find-command/) lets you search for files in a directory as well as its sub-directories. It searches for files by attributes such as permissions, users, groups, file type, date, size and other possible criteria.

$ find /home/tecmint/ -name tecmint.txt

Learn more on how to find files in Linux:

1.  [How to Use ‘find’ Command to Search for Multiple Filenames (Extensions)](https://www.tecmint.com/linux-find-command-to-search-multiple-filenames-extensions/)
2.  [How to Find Number of Files in a Directory and Subdirectories](https://www.tecmint.com/find-number-of-files-in-directory-subdirectories-linux/)
3.  [How to Find Today’s Modified Files in Linux](https://www.tecmint.com/find-recent-modified-files-in-linux/)
4.  [How to Find and Sort Files Based on Modified Date and Time](https://www.tecmint.com/find-and-sort-files-modification-date-and-time-in-linux/)
5.  [How to Find Top Directories and Files (Disk Space) in Linux](https://www.tecmint.com/find-top-large-directories-and-files-sizes-in-linux/)

## free

[free command](https://www.tecmint.com/check-memory-usage-in-linux/) shows the system memory usage (free, used, swapped, cached, etc.) in the system including swap space. Use the `-h` option to display output in human friendly format.

$ free -h 

Learn more on how to find memory usage in Linux.

1.  [Find Top Running Processes by Highest Memory and CPU Usage in Linux](https://www.tecmint.com/find-linux-processes-memory-ram-cpu-usage/)
2.  [Smem – Reports Memory Consumption Per-Process and Per-User Basis in Linux](https://www.tecmint.com/smem-linux-memory-usage-per-process-per-user/)
3.  [How to Clear RAM Memory Cache, Buffer and Swap Space on Linux](https://www.tecmint.com/clear-ram-memory-cache-buffer-and-swap-space-on-linux/)

## grep

[grep command](https://www.tecmint.com/12-practical-examples-of-linux-grep-command/) searches for a specified pattern in a file (or files) and displays in output lines containing that pattern as follows.

$ grep ‘tecmint’ domain-list.txt

Learn more about grep command usage in Linux.

1.  [What’s Difference Between Grep, Egrep and Fgrep in Linux?](https://www.tecmint.com/difference-between-grep-egrep-and-fgrep-in-linux/)
2.  [12 Basic Linux ‘Grep’ Command Examples in Linux](https://www.tecmint.com/12-practical-examples-of-linux-grep-command/)
3.  [11 Advanced Linux ‘Grep’ Commands in Linux](https://www.tecmint.com/linux-grep-commands-character-classes-bracket-expressions/)

## groups

**groups command** displays all the names of groups a user is a part of like this.

$ groups
$ groups tecmint

## gzip

[Gzip](https://www.tecmint.com/increase-nginx-performance-enable-gzip-compression-module/) helps to compress a file, replaces it with one having a `.gz` extension as shown below:

$ gzip passwds.txt
$ cat file1 file2 | gzip > foo.gz

## gunzip

**gunzip** expands or restores files compressed with **gzip** command like this.

$ gunzip foo.gz

## head

[head command](https://www.tecmint.com/view-contents-of-file-in-linux/) is used to show first lines (10 lines by default) of the specified file or stdin to the screen:

\# ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head 

## history

[history command](https://www.tecmint.com/history-command-examples/) is used to show previously used commands or to get info about command executed by a user.

$ history

Learn more about Linux history command.

1.  [The Power of Linux “History Command” in Bash Shell](https://www.tecmint.com/history-command-examples/)
2.  [Set Date and Time for Each Command You Execute in Bash History](https://www.tecmint.com/display-linux-command-history-with-date-and-time/)
3.  [How to Use ‘Yum History’ to Find Out Installed/Removed Packages Info](https://www.tecmint.com/view-yum-history-to-find-packages-info/)

## hostname

[hostname command](https://www.tecmint.com/set-hostname-permanently-in-linux/) is used to print or set system hostname in Linux.

$ hostname
$ hostname NEW\_HOSTNAME

## hostnamectl

[hostnamectl command](https://www.tecmint.com/set-hostname-permanently-in-linux/) controls the system hostname under systemd. It is used to print or modify the system hostname and any related settings:

$ hostnamectl
$ sudo hostnamectl set-hostname NEW\_HOSTNAME

## hwclock

**hwclock** is a tool for managing the system hardware clock; read or set the hardware clock (RTC).

$ sudo hwclock
$ sudo hwclock --set --date 8/06/2017

## hwinfo

[hwinfo](https://www.tecmint.com/check-linux-cpu-information/) is used to probe for the hardware present in a Linux system like this.

$ hwinfo

Learn more about how to get Linux hardware info.

1.  [I-Nex – An Advanced Tool to Collect System/Hardware Information in Linux](https://www.tecmint.com/collect-linux-system-hardware-information/)
2.  [9 Useful Tools to Get System Information in Linux](https://www.tecmint.com/check-linux-cpu-information/)

## id

**id command** shows user and group information for the current user or specified username as shown below.

$ id tecmint

## ifconfig

[ifconfig command](https://www.tecmint.com/ifconfig-command-examples/) is used to configure a Linux systems network interfaces. It is used to configure, view and control network interfaces.

$ ifconfig
$ sudo ifconfig eth0 up
$ sudo ifconfig eth0 down
$ sudo ifconfig eth0 172.16.25.125

## ionice

[ionice command](https://www.tecmint.com/delete-huge-files-in-linux/) is used to set or view process I/O scheduling class and priority of the specified process.

If invoked without any options, it will query the current I/O scheduling class and priority for that process:

$ ionice -c 3 rm /var/logs/syslog

To understand how it works, read this article: [How to Delete HUGE (100-200GB) Files in Linux](https://www.tecmint.com/delete-huge-files-in-linux/)

## iostat

[iostat](https://www.tecmint.com/linux-performance-monitoring-with-vmstat-and-iostat-commands/) is used to show CPU and input/output statistics for devices and partitions. It produces useful reports for updating system configurations to help balance the input/output load between physical disks.

$ iostat 

## ip

[ip command](https://www.tecmint.com/ip-command-examples/) is used to display or manage routing, devices, policy routing and tunnels. It also works as a replacement for well known [ifconfig command](https://www.tecmint.com/ifconfig-command-examples/).

This command will assign an IP address to a specific interface (eth1 in this case).

$ sudo ip addr add 192.168.56.10 dev eth1

## iptables

[iptables is a terminal based firewall](https://www.tecmint.com/linux-iptables-firewall-rules-examples-commands/) for managing incoming and outgoing traffic via a set of configurable table rules.

The command below is used to check existing rules on a system (using it may require root privileges).

$ sudo iptables -L -n -v

Learn more about iptables firewall in Linux.

1.  [How to Start/Stop and Enable/Disable FirewallD and Iptables in Linux](https://www.tecmint.com/start-stop-disable-enable-firewalld-iptables-firewall/)
2.  [Basic Guide on IPTables (Linux Firewall) Tips / Commands](https://www.tecmint.com/basic-guide-on-iptables-linux-firewall-tips-commands/)
3.  [Nishita Agarwal Shares Her Interview Experience on Linux ‘iptables’ Firewall](https://www.tecmint.com/linux-firewall-iptables-interview-questions-and-answers/)

## iw

**iw command** is used to manage wireless devices and their configuration.

$ iw list 

## iwlist

**iwlist command** displays detailed wireless information from a wireless interface. The command below enables you to get detailed information about the **wlp1s0** interface.

$ iwlist wlp1s0 scanning

## kill

[kill command](https://www.tecmint.com/how-to-kill-a-process-in-linux/) is used to kill a process using its PID by sending a signal to it (default signal for kill is TERM).

$ kill -p 2300
$ kill -SIGTERM -p 2300

## killall

[killall command](https://www.tecmint.com/how-to-kill-a-process-in-linux/) is used to kill a process by its name.

$ killall firefox

Learn more about kill and killall command in Linux.

1.  [How to Find and Kill Running Processes in Linux](https://www.tecmint.com/how-to-kill-a-process-in-linux/)
2.  [A Guide to Kill, Pkill and Killall Commands to Terminate a Process](https://www.tecmint.com/how-to-kill-a-process-in-linux/)
3.  [How to Kill Processes/Unresponsive Applications Using ‘xkill’ Command](https://www.tecmint.com/kill-processes-unresponsive-programs-in-ubuntu/)

## kmod

**kmod command** is used to manage Linux kernel modules. To list all currently loaded modules, type.

$ kmod list

## last

**last command** display a listing of last logged in users.

$ last 

## ln

**ln command** is used to create a soft link between files using the `-s` flag like this.

$ ln -s /usr/bin/lscpu cpuinfo

## locate

[locate command](https://www.tecmint.com/linux-locate-command-practical-examples/) is used to find a file by name. The locate utility works better and faster than it’s **find** counterpart.

The command below will search for a file by its exact name (not \*name\*):

$ locate -b '\\domain-list.txt'

## login

**login command** is used to create a new session with the system. You’ll be asked to provide a username and a password to login as below.

$ sudo login

## ls

[ls command](https://www.tecmint.com/15-basic-ls-command-examples-in-linux/) is used to list contents of a directory. It works more or less like [dir command](https://www.tecmint.com/linux-dir-command-usage-with-examples/).

The `-l` option enables long listing format like this.

$ ls -l file1

To know more about ls command, read our guides.

1.  [15 Basic ‘ls’ Command Examples in Linux](https://www.tecmint.com/15-basic-ls-command-examples-in-linux/)
2.  [7 Quirky ‘ls’ Command Tricks Every Linux User Should Know](https://www.tecmint.com/linux-ls-command-tricks/)
3.  [How to Sort Output of ‘ls’ Command By Last Modified Date and Time](https://www.tecmint.com/sort-ls-output-by-last-modified-date-and-time/)
4.  [15 Interview Questions on Linux “ls” Command – Part 1](https://www.tecmint.com/ls-command-interview-questions/)
5.  [10 Useful ‘ls’ Command Interview Questions – Part 2](https://www.tecmint.com/ls-interview-questions/)

## lshw

[lshw command](https://www.tecmint.com/commands-to-collect-system-and-hardware-information-in-linux/) is a minimal tool to get detailed information on the hardware configuration of the machine, invoke it with superuser privileges to get a comprehensive information.

$ sudo lshw  

## lscpu

[lscpu command](https://www.tecmint.com/check-linux-cpu-information/) displays system’s CPU architecture information (such as number of CPUs, threads, cores, sockets, and more).

$ lscpu

## lsof

[lsof command](https://www.tecmint.com/10-lsof-command-examples-in-linux/) displays information related to files opened by processes. Files can be of any type, including regular files, directories, block special files, character special files, executing text reference, libraries, and stream/network files.

To view files opened by a specific user’s processes, type the command below.

$ lsof -u tecmint

## lsusb

[lsusb command](https://www.tecmint.com/commands-to-collect-system-and-hardware-information-in-linux/) shows information about USB buses in the system and the devices connected to them like this.

$ lsusb 

## man

**man command** is used to view the on-line reference manual pages for commands/programs like so.

$ man du
$ man df

## md5sum

[md5sum command](https://www.tecmint.com/check-verify-md5sum-packages-files-in-linux/) is used to [compute and print the MD5 message digest of a file](https://www.tecmint.com/generate-verify-check-files-md5-checksum-linux/). If run without arguments, debsums checks every file on your system against the stock md5sum files:

$ sudo debsums

## mkdir

[mkdir command](https://www.tecmint.com/mkdir-tar-and-kill-commands-in-linux/) is used to create single or more directories, if they do not already exist (this can be overridden with the `-p` option).

$ mkdir tecmint-files
OR 
$ mkdir -p tecmint-files

## more

[more command](https://www.tecmint.com/linux-more-command-and-less-command-examples/) enables you to view through relatively lengthy text files one screenful at a time.

$ more file.txt

Check difference between **more** and **less** command and [Learn Why ‘less’ is Faster Than ‘more’ Command](https://www.tecmint.com/linux-more-command-and-less-command-examples/)

## mv

**mv command** is used to [rename files or directories](https://www.tecmint.com/rename-multiple-files-in-linux/). It also moves a file or directory to another location in the directory structure.

$ mv test.sh sysinfo.sh 

## nano

**nano** is a popular small, free and friendly [text editor for Linux](https://www.tecmint.com/best-open-source-linux-text-editors/); a clone of **Pico**, the default editor included in the non-free Pine package.

To open a file using nano, type:

$ nano file.txt

## nc/netcat

**nc (or netcat)** is used for performing any operation relating to TCP, UDP, or UNIX-domain sockets. It can handle both IPv4 and IPv6 for opening TCP connections, sending UDP packets, listening on arbitrary TCP and UDP ports, [performing port scanning](https://www.tecmint.com/check-remote-port-in-linux/).

The command below will help us see if the port 22 is open on the host 192.168.56.5.

$ nc -zv 192.168.1.5 22

Learn more examples and usage on **nc command**.

1.  [How to Check Remote Ports are Reachable Using ‘nc’ Command](https://www.tecmint.com/check-remote-port-in-linux/)
2.  [How to Transfer Files Between Computers Using ‘nc’ Command](https://www.tecmint.com/transfer-files-between-two-linux-machines/)

## netstat

[netstat command](https://www.tecmint.com/20-netstat-commands-for-linux-network-management/) displays useful information concerning the Linux networking subsystem (network connections, routing tables, interface statistics, masquerade connections, and multicast memberships).

This command will display all open ports on the local system:

$ netstat -a | more

## nice

**nice command** is used to show or change the nice value of a running program. It runs specified command with an adjusted niceness. When run without any command specified, it prints the current niceness.

The following command starts the process “[tar command](https://www.tecmint.com/18-tar-command-examples-in-linux/)” setting the “nice” value to 12.

$ nice -12 tar -czf backup.tar.bz2 /home/\*

## nmap

[nmap](https://www.tecmint.com/nmap-command-examples/) is a popular and powerful open source tool for network scanning and security auditing. It was intended to quickly scan large networks, but it also works fine against single hosts.

The command below will probe open ports on all live hosts on the specified network.

$ nmap -sV 192.168.56.0/24

## nproc

**nproc command** shows the number of processing units present to the current process. It’s output may be less than the number of online processors on a system.

$ nproc  

## openssl

The **openssl** is a command line tool for using the different cryptography operations of OpenSSL’s crypto library from the shell. The command below will create an archive of all files in the current directory and [encrypt the contents of the archive](https://www.tecmint.com/encrypt-decrypt-files-tar-openssl-linux/) file:

$ tar -czf - \* | openssl enc -e -aes256 -out backup.tar.gz

## passwd

**passwd command** is used to create/update passwords for user accounts, it can also change the account or associated password validity period. Note that normal system users may only change the password of their own account, while root may modify the password for any account.

$ passwd tecmint

## pidof

**pidof** displays the [process ID of a running program](https://www.tecmint.com/find-process-name-pid-number-linux/)/command.

$ pidof init
$ pidof cinnamon

## ping

**ping command** is used to determine connectivity between hosts on a network (or the Internet):

$ ping google.com

## ps

ps shows useful information about [active processes running on a system](https://www.tecmint.com/linux-process-management/). The example below shows the [top running processes by highest memory and CPU usage](https://www.tecmint.com/find-linux-processes-memory-ram-cpu-usage/).

\# ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head

## pstree

**pstree** displays running processes as a tree which is rooted at either PID or init if PID is omitted.

$ pstree

## pwd

[pwd command](https://www.tecmint.com/pwd-command-examples/) displays the name of current/working directory as below.

$ pwd

## rdiff-backup

[rdiff-backup](https://www.tecmint.com/rdiff-backup-remote-incremental-backup-for-linux/) is a powerful local/remote incremental backup script written in Python. It works on any POSIX operating system such as Linux, Mac OS X.

Note that for remote backups, you must install the same version of rdiff-backup on both the local and remote machines. Below is an example of a local backup command:

$ sudo rdiff-backup /etc /media/tecmint/Backup/server\_etc.backup

## reboot

**reboot command** may be used to [halt, power-off or reboot a system](https://www.tecmint.com/shutdown-poweroff-halt-and-reboot-commands-in-linux/) as follows.

$ reboot

## rename

[rename command](https://www.tecmint.com/rename-multiple-files-in-linux/) is used to rename many files at once. If you’ve a collection of files with “**.html**” extension and you want to rename all of them with “**.php**” extension, you can type the command below.

$ rename 's/\\.html$/\\.php/' \*.html

## rm command

**rm command** is used to remove files or directories as shown below.

$ rm file1
$ rm -rf my-files

## rmdir

**rmdir command** helps to delete/remove empty directories as follows.

$ rmdir /backup/all

## scp

[scp command](https://www.tecmint.com/scp-commands-examples/) enables you to securely copy files between hosts on a network, for example.

$ scp ~/names.txt root@192.168.56.10:/root/names.txt

## shutdown

[shutdown command](https://www.tecmint.com/shutdown-poweroff-halt-and-reboot-commands-in-linux/) schedules a time for the system to be powered down. It may be used to halt, power-off or reboot the machine like this.

$ shutdown --poweroff

Learn how to show a [Custom Message to Users Before Linux Server Shutdown](https://www.tecmint.com/show-linux-server-shutdown-message/).

## sleep

**sleep command** is used to delay or pause (specifically execution of a command) for a specified amount of time.

$ check.sh; sleep 5; sudo apt update

## sort

[sort command](https://www.tecmint.com/sort-command-linux/) is used to sort lines of text in the specified file(s) or from stdin as shown below

$ cat words.txt

Learn more examples of sort command in Linux.

1.  [7 Interesting Linux ‘sort’ Command Examples](https://www.tecmint.com/linux-sort-command-examples/)
2.  [How to Sort Output of ‘ls’ Command By Last Modified Date and Time](https://www.tecmint.com/sort-ls-output-by-last-modified-date-and-time/)
3.  [How to Find and Sort Files Based on Modification Date and Time](https://www.tecmint.com/find-and-sort-files-modification-date-and-time-in-linux/)

## split

[split](https://www.tecmint.com/split-large-tar-into-multiple-files-of-certain-size/) as the name suggests, is used to split a large file into small parts.

$ tar -cvjf backup.tar.bz2 /home/tecmint/Documents/\* 

## ssh

[ssh (SSH client)](https://www.tecmint.com/install-openssh-server-in-linux/) is an application for remotely accessing and running commands on a remote machine. It is designed to offer a secure encrypted communications between two untrusted hosts over an insecure network such as the Internet.

$ ssh tecmint@192.168.56.10

Learn more about ssh command and how to use it on Linux.

1.  [5 Best Practices to Secure and Protect SSH Server](https://www.tecmint.com/5-best-practices-to-secure-and-protect-ssh-server/)
2.  [Configure “No Password SSH Keys Authentication” with PuTTY on Linux](https://www.tecmint.com/ssh-passwordless-login-with-putty/)
3.  [SSH Passwordless Login Using SSH Keygen in 5 Easy Steps](https://www.tecmint.com/ssh-passwordless-login-using-ssh-keygen-in-5-easy-steps/)
4.  [Restrict SSH User Access to Certain Directory Using Chrooted Jail](https://www.tecmint.com/restrict-ssh-user-to-directory-using-chrooted-jail/)

## stat

stat is used to show a file or file system status like this (`-f` is used to specify a filesystem).

$ stat file1

## su

**su command** is used to switch to another user ID or become root during a login session. Note that when **su** is invoked without a username, it defaults to becoming root.

$ su 
$ su tecmint

## sudo

[sudo command](https://www.tecmint.com/sudoers-configurations-for-setting-sudo-in-linux/) allows a permitted system user to run a command as root or another user, as defined by the security policy such as sudoers.

In this case, the real (not effective) user ID of the user running **sudo** is used to determine the user name with which to query the security policy.

$ sudo apt update
$ sudo useradd tecmint
$ sudo passwd tecmint

Learn more about sudo command and how to use it on Linux.

1.  [10 Useful Sudoers Configurations for Setting ‘sudo’ in Linux](https://www.tecmint.com/sudoers-configurations-for-setting-sudo-in-linux/)
2.  [How to Run ‘sudo’ Command Without Entering a Password in Linux](https://www.tecmint.com/run-sudo-command-without-password-linux/)
3.  [How to Keep ‘sudo’ Password Timeout Session Longer in Linux](https://www.tecmint.com/set-sudo-password-timeout-session-longer-linux/)

## sum

**sum command** is used to show the checksum and block counts for each each specified file on the command line.

$ sum output file.txt 

## tac

[tac command](https://www.tecmint.com/learn-linux-cat-command-and-tac-command/) concatenates and displays files in reverse. It simply prints each file to standard output, showing last line first.

$tac file.txt

## tail

[tail command](https://www.tecmint.com/view-contents-of-file-in-linux/) is used to display the last lines (10 lines by default) of each file to standard output.

If there more than one file, precede each with a header giving the file name. Use it as follow (specify more lines to display using `-n` option).

$ tail long-file
OR
$ tail -n 15 long-file

## talk

**talk command** is used to talk to another system/network user. To talk to a user on the same machine, use their login name, however, to talk to a user on another machine use ‘user@host’.

$ talk person \[ttyname\]
OR
$ talk‘user@host’ \[ttyname\]

## tar

[tar command](https://www.tecmint.com/18-tar-command-examples-in-linux/) is a most powerful utility for archiving files in Linux.

$ tar -czf home.tar.gz .

Learn more about tar command and its usage on Linux.

1.  [18 Tar Command Examples in Linux](https://www.tecmint.com/18-tar-command-examples-in-linux/)
2.  [How to Split Large ‘tar’ Archive into Multiple Files of Certain Size](https://www.tecmint.com/split-large-tar-into-multiple-files-of-certain-size/)
3.  [How to Extract Tar Files to Specific or Different Directory in Linux](https://www.tecmint.com/extract-tar-files-to-specific-or-different-directory-in-linux/)

## tee

**tee command** is used to read from standard input and prints to standard output and files as shown below.

$ echo "Testing how tee command works" | tee file1 

## tree

The [tree command](https://www.tecmint.com/linux-tree-command-examples/) is a tiny, cross-platform command-line program used to recursively list or display the content of a directory in a tree-like format.

$ tree

## time

**time command** runs programs and summarizes system resource usage.

$ time wc /etc/hosts

## top

[top program](https://www.tecmint.com/12-top-command-examples-in-linux/) displays all processes on a Linux system in regards to memory and CPU usage and provides a dynamic real-time view of a running system.

$ top

## touch

[touch command](https://www.tecmint.com/8-pratical-examples-of-linux-touch-command/) changes file timestamps, it can also be used to create a file as follows.

$ touch file.txt

## tr

**tr command** is a useful utility used to translate (change) or delete characters from stdin, and write the result to stdout or send to a file as follows.

$ cat domain-list.txt | tr \[:lower:\] \[:upper:\]

## uname

[uname command](https://www.tecmint.com/find-linux-kernel-version-distribution-name-version-number/) displays system information such as operating system, network node hostname kernel name, version and release etc.

Use the `-a` option to show all the system information:

$ uname 

## uniq

**uniq command** displays or omits repeated lines from input (or standard input). To indicate the number of occurrences of a line, use the `-c` option.

$ cat domain-list.txt

## uptime

[uptime command](https://www.tecmint.com/find-linux-uptime-shutdown-and-reboot-time-with-tuptime/) shows how long the system has been running, number of logged on users and the system load averages as follows.

$ uptime

## users

**users command** shows the user names of users currently logged in to the current host like this.

$ users

## vim/vi

[vim (Vi Improved) popular text editor](https://www.tecmint.com/reasons-to-learn-vi-vim-editor-in-linux/) on Unix-like operating systems. It can be used to edit all kinds of plain text and program files.

$ vim file

Learn how to use vi/vim editor in Linux along with some tips and tricks.

1.  [10 Reasons Why You Should Use Vi/Vim Editor in Linux](https://www.tecmint.com/reasons-to-learn-vi-vim-editor-in-linux/)
2.  [How to Install and Use Vi/Vim Editor in Linux](https://www.tecmint.com/vi-editor-usage/)
3.  [How to Save a File in Vim Editor in Linux](https://www.tecmint.com/python-mode-a-vim-editor-plugin/)
4.  [How to Exit a File in Vim Editor in Linux](https://www.tecmint.com/exit-file-in-vi-vim-editor-in-linux/)
5.  [Learn Useful ‘Vi/Vim’ Editor Tips and Tricks to Enhance Your Skills](https://www.tecmint.com/learn-vi-and-vim-editor-tips-and-tricks-in-linux/)
6.  [8 Interesting ‘Vi/Vim’ Editor Tips and Tricks for Every Linux Administrator](https://www.tecmint.com/how-to-use-vi-and-vim-editor-in-linux/)

## w

**w command** displays system uptime, load averages and information about the users currently on the machine, and what they are doing (their processes) like this.

$ w

## wall

**wall command** is used to send/display a message to all users on the system as follows.

$ wall “This is TecMint – Linux How Tos”

## watch

[watch command](https://www.tecmint.com/run-repeat-linux-command-every-x-seconds/) runs a program repeatedly while displaying its output on fullscreen. It can also be used to watch changes to a file/directory. The example below shows how to watch the contents of a directory change.

$ watch -d ls -l

## wc

[wc command](https://www.tecmint.com/wc-command-examples/) is used to display newline, word, and byte counts for each file specified, and a total for many files.

$ wc filename

## wget

[wget command](https://www.tecmint.com/10-wget-command-examples-in-linux/) is a simple utility used to download files from the Web in a non-interactive (can work in the background) way.

$ wget -c http://ftp.gnu.org/gnu/wget/wget-1.5.3.tar.gz

## whatis

[whatis command](https://www.tecmint.com/find-linux-command-description-and-location/) searches and shows a short or one-line manual page descriptions of the provided command name(s) as follows.

$ whatis wget

## which

**which command** displays the absolute path (pathnames) of the files (or possibly links) which would be executed in the current environment.

$ which who

## who

**who command** shows information about users who are currently logged in like this.

$ who

## whereis

[whereis command](https://www.tecmint.com/find-linux-command-description-and-location/) helps us locate the binary, source and manual files for commands.

$ whereis cat

## xargs

**xargs command** is a useful utility for reading items from the standard input, delimited by blanks (protected with double or single quotes or a backslash) or newlines, and executes the entered command.

The example below show xargs being used to [copy a file to multiple directories in Linux](https://www.tecmint.com/copy-file-to-multiple-directories-in-linux/).

$ echo /home/aaronkilik/test/ /home/aaronkilik/tmp | xargs -n 1 cp -v /home/aaronkilik/bin/sys\_info.sh

## yes

**yes command** is used to display a string repeatedly until when terminated or killed using \[`Ctrl + C`\] as follows.

$ yes "This is TecMint - Linux HowTos"

## youtube-dl

[youtube-dl](https://www.tecmint.com/install-youtube-dl-command-line-video-download-tool/) is a lightweight command-line program to download videos and also [extract MP3 tracks from YouTube.com](https://www.tecmint.com/download-mp3-track-from-youtube-video-using-youtube-dl/) and a few more sites.

The command below will list available formats for the video in the provided link.

$ youtube-dl --list-formats https://www.youtube.com/watch?v=iR

## zcmp/zdiff

**zcmp** and **zdiff** minimal utilities used to compare compressed files as shown in the examples below.

$ zcmp domain-list.txt.zip basic\_passwords.txt.zip
$ zdiff domain-list.txt.zip basic\_passwords.txt.zip 

## zip

**zip** is a simple and easy-to-use utility used to package and compress (archive) files.

$ tar cf - . | zip | dd of=/dev/nrst0 obs=16k
$ zip inarchive.zip foo.c bar.c --out outarchive.zip
$ tar cf - .| zip backup -

## zz

**zz command** is an alias of the [fasd commandline tool](https://www.tecmint.com/fasd-quick-access-to-linux-files-and-directories/) that offers quick access to files and directories in Linux. It is used to quickly and interactively [cd into a previously accessed directory](https://www.tecmint.com/bd-quickly-go-back-to-a-linux-parent-directory/) by selecting the directory number from the first field as follows.

$ zz

That’s it for now! As we mentioned before, there are a countless number of commands in Linux. The list is possibly longer than we can offer. Use the feedback form below to share any useful and frequently used commands missing in this list.
