---
layout: post
title: pwn college Fundamentals - Program Interaction
# subtitle: Sending HTTP requests using nc, curl, python
cover-img: /assets/img/pwnCollege.jpeg
thumbnail-img: /assets/img/pwnCollege.jpeg
# share-img: /assets/img/path.jpg
tags: [web, security, www, pwn, college, linux]
comments: true
author: Lantana Park
---

# Introduction

## Introduction to Binary Files

`/bin/cat`

### What is Binary files

- A binary file is a file that contains data in binary form. This means it is stored in a format that is directly readable by a computer, not in a human-readable format like text files.

### What is ELF files

- ELF, which stands for Executable and Linkable Format, was designed by the Unix System Laboratories and has become widely adopted in various Unix-like operating systems, including Linux. ELF files are a specific type of binary file that follows a particular structure **defining how data and code are organized within the file.** This structure allows the operating system to know how to load and execute the file or how an executable can utilize a shared library.

Tools like `readelf`, `nm`, and `patchelf` can be used to interact with ELF files.

An ELF file typically contains several sections that include:

**Program Header**: Contains information necessary for the operating system to execute/load the binary file, such as memory size and location.

- `INTEP` tells the computer which helper program (interpreter) it needs to use to run this file. (points to the necessary helper to run the program)
- `LOAD` tells the computer which parts of the program need to be loaded into memory so it can run. (provides the setup instructions for placing the program's parts in the right spots in memory)

**Section Header**: Provides information about the file's sections, including code, data, symbol tables, and more.

- `.text`, `.data`

### What is symbols in binary?

- Symbols in ELF files are used to resolve library calls and find functions and variables.

## Linux Process Loading

`cat /flag`

- A process is an individual program running on a computer, such as a browser or terminal.

- Processes are created through forking or cloning, with a parent process giving rise to child processes.

- Linux processes have attributes like state, priority, parent-child relationships, and shared resources.

- Processes have their own memory space and security context.

- The loading process involves determining the file type and loading it into memory.

- The kernel looks for shebang lines or checks the kernel configuration to determine the appropriate interpreter for script files.

- For dynamically linked ELF files, the kernel loads both the interpreter and the original binary into memory.

## Linux Process Execution

- Linux process execution involves loading a program into the virtual memory space of a process.

- The execution of a program is handled by a function called libsy start main.

- Environment variables are used to pass additional arguments to a program.

- Library functions and system calls are used to interact with the outside world and perform complex tasks.

- Symbols in a binary represent names of functions or variables that are imported or exported by the program.

- System calls are the primary way to interact with the Linux operating system.

- The strace command can be used to trace system calls and understand program execution.

Level 1

Answer: pwn.college{MM1df7-gRuQ2vzJN3-PeIj4IE0o.dFDL0MjM3QzW}

```
hacker@program-interaction~level1:/challenge$ ./embryoio_level1
<!-- just executes this file -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is the bash shell. If this is a check for the parent process, then,
[TEST] most likely, this is what you do by default anyways, but we'll check just in case...
[INFO] The process' executable is /usr/bin/bash.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be bash.
[GOOD] You have passed the checks on the parent process!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{MM1df7-gRuQ2vzJN3-PeIj4IE0o.dFDL0MjM3QzW}
```

Level 2

I just entered the given password. (Please notice the comment below)

Answer: pwn.college{0hfnIDhKT2ODaO0bTomrOLDUvU8.dJDL0MjM3QzW}

```
hacker@program-interaction~level2:/challenge$ ./embryoio_level2
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge will check for a hardcoded password over stdin : kateygrd

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is the bash shell. If this is a check for the parent process, then,
[TEST] most likely, this is what you do by default anyways, but we'll check just in case...
[INFO] The process' executable is /usr/bin/bash.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be bash.
[GOOD] You have passed the checks on the parent process!
[TEST] This program expects you to enter a simple password (specifically, kateygrd). Send it now!
[INFO] Reading in your input now...
kateygrd
<!-- here -->
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{0hfnIDhKT2ODaO0bTomrOLDUvU8.dJDL0MjM3QzW}
```

Level 3

Answer: pwn.college{skmKbsQNpO-lGxa0QszFXnsy3vs.dNDL0MjM3QzW}

```
hacker@program-interaction~level3:/challenge$ ./embryoio_level3
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge will check that argv[NUM] holds value VALUE (listed to the right as NUM:VALUE) : 1:vuharmqbcy

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is the bash shell. If this is a check for the parent process, then,
[TEST] most likely, this is what you do by default anyways, but we'll check just in case...
[INFO] The process' executable is /usr/bin/bash.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be bash.
[GOOD] You have passed the checks on the parent process!
[TEST] My argv[1] should have a value of vuharmqbcy! Let's check...
Traceback (most recent call last):
  File "/challenge/checker.py", line 516, in <module>
    do_checks(_args)
  File "/challenge/checker.py", line 380, in do_checks
    check_arg(args.old_args[1:], n, v)
  File "/challenge/checker.py", line 227, in check_arg
    assert args[n] == v, f"argv[{n}] is not '{v}' (it seems to be '{args[n]}', instead)."
IndexError: list index out of range

hacker@program-interaction~level3:/challenge$ ./embryoio_level3 vuharmqbcy
<!-- I executed the file and input the password. -->

WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge will check that argv[NUM] holds value VALUE (listed to the right as NUM:VALUE) : 1:vuharmqbcy

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is the bash shell. If this is a check for the parent process, then,
[TEST] most likely, this is what you do by default anyways, but we'll check just in case...
[INFO] The process' executable is /usr/bin/bash.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be bash.
[GOOD] You have passed the checks on the parent process!
[TEST] My argv[1] should have a value of vuharmqbcy! Let's check...
[GOOD] You successfully passed the argument value check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{skmKbsQNpO-lGxa0QszFXnsy3vs.dNDL0MjM3QzW}
```

Level 4

Answer: pwn.college{cx_aFNZCLwdhkdS2jxIdek94-lu.dRDL0MjM3QzW}

```
hacker@program-interaction~level4:/challenge$ export jqtuxe=rhdidouonf
<!-- making environment -->
hacker@program-interaction~level4:/challenge$ ./embryoio_level4
<!-- and then executed the file -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge will check that env[KEY] holds value VALUE (listed to the right as KEY:VALUE) : jqtuxe:rhdidouonf

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is the bash shell. If this is a check for the parent process, then,
[TEST] most likely, this is what you do by default anyways, but we'll check just in case...
[INFO] The process' executable is /usr/bin/bash.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be bash.
[GOOD] You have passed the checks on the parent process!
[TEST] My 'jqtuxe' environment variable should have a value of rhdidouonf! Let's check...
[GOOD] You successfully passed the environment value check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{cx_aFNZCLwdhkdS2jxIdek94-lu.dRDL0MjM3QzW}
```

Level 5

Answer: pwn.college{gXtxqLvdk0CHJhL6I64c3sgkfk0.dVDL0MjM3QzW}

```
hacker@program-interaction~level5:/challenge$ echo yorlicln > /tmp/tlvzpz
<!-- outputs the string I was given as password and then redirects to the specific file path -->
hacker@program-interaction~level5:/challenge$ ./embryoio_level5 < /tmp/tlvzpz
<!-- redirects the opposite direction from the above and then execute the file using the input from /tmp/tlvzpz -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge will check that input is redirected from a specific file path : /tmp/tlvzpz
the challenge will check for a hardcoded password over stdin : yorlicln

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is the bash shell. If this is a check for the parent process, then,
[TEST] most likely, this is what you do by default anyways, but we'll check just in case...
[INFO] The process' executable is /usr/bin/bash.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be bash.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected a file called /tmp/tlvzpz to my stdin. Checking...
[TEST] I will now check that you redirected /tmp/tlvzpz to/from my stdin.

[ADVICE] File descriptors are inherited from the parent, unless the FD_CLOEXEC is set by the parent on the file descriptor.
[ADVICE] For security reasons, some programs, such as python, do this by default in certain cases. Be careful if you are
[ADVICE] creating and trying to pass in FDs in python.
[GOOD] The file at the other end of my stdin looks okay!
[TEST] This program expects you to enter a simple password (specifically, yorlicln). Send it now!
[INFO] Reading in your input now...
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{gXtxqLvdk0CHJhL6I64c3sgkfk0.dVDL0MjM3QzW}
```

Level 6

Answer: pwn.college{IjKXSn1onXWW14aDnA_lqpW0Wq5.dZDL0MjM3QzW}

```
hacker@program-interaction~level6:/challenge$ ./embryoio_level6 > /tmp/enhwpg
<!-- redirect the file into the path -->

hacker@program-interaction~level6:/challenge$ cat /tmp/enhwpg
<!-- and the read the redirected file -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge will check that output is redirected to a specific file path : /tmp/enhwpg

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is the bash shell. If this is a check for the parent process, then,
[TEST] most likely, this is what you do by default anyways, but we'll check just in case...
[INFO] The process' executable is /usr/bin/bash.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be bash.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected my stdout to a file called /tmp/enhwpg. Checking...
[TEST] I will now check that you redirected /tmp/enhwpg to/from my stdout.

[ADVICE] File descriptors are inherited from the parent, unless the FD_CLOEXEC is set by the parent on the file descriptor.
[ADVICE] For security reasons, some programs, such as python, do this by default in certain cases. Be careful if you are
[ADVICE] creating and trying to pass in FDs in python.
[GOOD] The file at the other end of my stdout looks okay!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{IjKXSn1onXWW14aDnA_lqpW0Wq5.dZDL0MjM3QzW}
```

Level 7

Answer: pwn.college{oHiGzdU7crzuyeeCirJ1D30c2Hi.ddDL0MjM3QzW}

```
hacker@program-interaction~level7:/challenge$ env -i ./embryoio_level7
<!-- `-i` option initialize a new environment, completely empty of any inherited environment variables -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge will check that the environment is empty (except LC_CTYPE, which is impossible to get rid of in some cases)

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is the bash shell. If this is a check for the parent process, then,
[TEST] most likely, this is what you do by default anyways, but we'll check just in case...
[INFO] The process' executable is /usr/bin/bash.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be bash.
[GOOD] You have passed the checks on the parent process!
[TEST] You should launch me with an empty environment. Checking...
[GOOD] You successfully passed the empty environment check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{oHiGzdU7crzuyeeCirJ1D30c2Hi.ddDL0MjM3QzW}
```

Level 8

Answer: pwn.college{gJ6f5Gk8a3JTmOxqADQLZ6VFkma.dhDL0MjM3QzW}

In shell script,

```
#!/bin/bash
<!-- 'hashbang` indicates which interpreter should be used to execute the script. And I specified the path to the bash interpreter. Thanks to this line, users can run this script directly by its name(`./my_script.sh`) without having to explicitly invoke the interpreter(`bash my_script.sh`) -->
/challenge/embryoio_level8
```

```
hacker@program-interaction~level8:/tmp$ touch my_script.sh
<!-- makes the file -->
hacker@program-interaction~level8:/tmp$ vim my_script.sh
<!-- edits the file -->
hacker@program-interaction~level8:/tmp$ chmod 777 my_script.sh
<!-- edit  access permission -->
hacker@program-interaction~level8:/tmp$ bash my_script.sh
<!-- execute the file, I can use `./my_script.sh`, instead of the command above -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{gJ6f5Gk8a3JTmOxqADQLZ6VFkma.dhDL0MjM3QzW}
```

Level 9

Answer: pwn.college{Y4xmn15kVTEUBmgx-0htJlWcujk.dlDL0MjM3QzW}

In the shell script,

```
#!/bin/bash
PASSWORD="psndxcok"
<!-- declares the password variable -->
/challenge/embryoio_level9
<!-- and then specify path to execute the file -->
```

```
hacker@program-interaction~level9:/tmp$ echo "psndxcok" | ./my_script.sh
<!-- with this value, executes the file -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge will check for a hardcoded password over stdin : psndxcok

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] This program expects you to enter a simple password (specifically, psndxcok). Send it now!
[INFO] Reading in your input now...
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{Y4xmn15kVTEUBmgx-0htJlWcujk.dlDL0MjM3QzW}
```

Level 10

Answer: pwn.college{gF_LtU0_sXHLodCVGJlB2PGacwh.QXwEDL0MjM3QzW}

```
#!/bin/bash
/challenge/embryoio_level10 mnxlozbnvg
<!-- with the argument passed, executes the file -->
```

```
hacker@program-interaction~level10:/tmp$ bash my_script.sh
<!-- executes this file -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge will check that argv[NUM] holds value VALUE (listed to the right as NUM:VALUE) : 1:mnxlozbnvg

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] My argv[1] should have a value of mnxlozbnvg! Let's check...
[GOOD] You successfully passed the argument value check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{gF_LtU0_sXHLodCVGJlB2PGacwh.QXwEDL0MjM3QzW}
```

Level 11

Answer: pwn.college{EXTUh_1TKc0QxR0qA1YNWEx_jfU.QXxEDL0MjM3QzW}

In the shell script,

```
#!/bin/bash
export wdcxzm=bzykoxwgzx
<!-- set environment value -->
/challenge/embryoio_level11
<!-- and then run this program -->
```

```
hacker@program-interaction~level11:/tmp$ bash  my_script.sh
<!-- Again, `./my_script.sh` will generate same result -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge will check that env[KEY] holds value VALUE (listed to the right as KEY:VALUE) : wdcxzm:bzykoxwgzx

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] My 'wdcxzm' environment variable should have a value of bzykoxwgzx! Let's check...
[GOOD] You successfully passed the environment value check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{EXTUh_1TKc0QxR0qA1YNWEx_jfU.QXxEDL0MjM3QzW}
```

Level 12

Answer: pwn.college{oP1N6y4aAAqOBui3rQSRL2cpUB8.QXyEDL0MjM3QzW}

In the shell script,

```
#!/bin/bash
PASSWORD="ndalulxw"
/challenge/embryoio_level12
```

```
hacker@program-interaction~level12:/tmp$ echo "ndalulxw" > /tmp/bnitsh
<!-- creates a file with content. Printing the string to the standard output, redirects the output of the command on its left to the file on its right -->
hacker@program-interaction~level12:/tmp$ bash my_script.sh < /tmp/bnitsh
<!-- executing a shell script with input redirection -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge will check that input is redirected from a specific file path : /tmp/bnitsh
the challenge will check for a hardcoded password over stdin : ndalulxw

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected a file called /tmp/bnitsh to my stdin. Checking...
[TEST] I will now check that you redirected /tmp/bnitsh to/from my stdin.

[ADVICE] File descriptors are inherited from the parent, unless the FD_CLOEXEC is set by the parent on the file descriptor.
[ADVICE] For security reasons, some programs, such as python, do this by default in certain cases. Be careful if you are
[ADVICE] creating and trying to pass in FDs in python.
[GOOD] The file at the other end of my stdin looks okay!
[TEST] This program expects you to enter a simple password (specifically, ndalulxw). Send it now!
[INFO] Reading in your input now...
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{oP1N6y4aAAqOBui3rQSRL2cpUB8.QXyEDL0MjM3QzW}
```

Level 13

Answer: pwn.college{ISYYKiVGbvMIZhijW7U0OR96mBy.QXzEDL0MjM3QzW}

```
#!/bin/bash
/challenge/embryoio_level13 > /tmp/qvxufv
<!-- It means that the output of whatever process is running with `/challenge/embryoio_level13` is being redirected to a file named 'qvxufv' located in the '/tmp' directory. -->
```

```
hacker@program-interaction~level13:/tmp$ ./my_script.sh
<!-- trying to output redirection to the /tmp/qvxufv -->
hacker@program-interaction~level13:/tmp$ cat qvxufv
<!-- Since I redirected the output of the embryoio file to the qvxufv, I am trying to read the output by `cat  /tmp/qvxufv -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge will check that output is redirected to a specific file path : /tmp/qvxufv

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected my stdout to a file called /tmp/qvxufv. Checking...
[TEST] I will now check that you redirected /tmp/qvxufv to/from my stdout.

[ADVICE] File descriptors are inherited from the parent, unless the FD_CLOEXEC is set by the parent on the file descriptor.
[ADVICE] For security reasons, some programs, such as python, do this by default in certain cases. Be careful if you are
[ADVICE] creating and trying to pass in FDs in python.
[GOOD] The file at the other end of my stdout looks okay!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{ISYYKiVGbvMIZhijW7U0OR96mBy.QXzEDL0MjM3QzW}
```

Level 14

Answer: pwn.college{EV7piXzivY1Pyu7idNFJ1d4nyWa.QX0EDL0MjM3QzW}

```
hacker@program-interaction~level14:/tmp$ vim my_script.sh
```

```
#!/bin/bash
env -i /challenge/embryoio_level14
```

```
hacker@program-interaction~level14:/tmp$ ./my_script.sh
bash: ./my_script.sh: Permission denied
hacker@program-interaction~level14:/tmp$ chmod +x my_script.sh
hacker@program-interaction~level14:/tmp$ ./my_script.sh
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge will check that the environment is empty (except LC_CTYPE, which is impossible to get rid of in some cases)

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] You should launch me with an empty environment. Checking...
[GOOD] You successfully passed the empty environment check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{EV7piXzivY1Pyu7idNFJ1d4nyWa.QX0EDL0MjM3QzW}
```

Level 15

**What is ipython vs python?**

**IPython** is a command shell for interactive computing in multiple programming languages, originally developed for the Python programming language.

**Python** is one of programming langauge.

Why do I need to import subprocess?

- It ensures the script is executed directly by the Python interpreter used by IPython, **maintaining the necessary parent-child relationship between processes.**

- `!./embryoio_level15` can run the file in ipython script. And this shell is also a child of the IPython process but is not the same as running the command directly within the Python (IPython) process itself.

Answer: pwn.college{o0C1Whx_WrcRmufhYZWeyz94D0s.QX1EDL0MjM3QzW}

```
hacker@program-interaction~level15:/challenge$ ipython
<!-- opening ipython shell -->
Python 3.8.10 (default, Nov 22 2023, 10:22:35)
Type 'copyright', 'credits' or 'license' for more information
IPython 8.12.3 -- An enhanced Interactive Python. Type '?' for help.

In [1]: import subprocess;subprocess.run(["./embryoio_level15"])
<!-- running the ./embryoio_level15 -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : ipython

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is an interactive ipython instance.

[INFO] Since ipython runs as a script inside python, this will check a few things:
[INFO] 1. That the process itself is python.
[INFO] 2. That the module being run in python is ipython.
[INFO] If the process being checked is just a normal 'ipython', you'll be okay!

[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{o0C1Whx_WrcRmufhYZWeyz94D0s.QX1EDL0MjM3QzW}

Out[1]: CompletedProcess(args=['./embryoio_level15'], returncode=0)
```

Level 16

Answer: pwn.college{Yr-B3CW7dZZGbHy9_u4_x6VwSW6.QX2EDL0MjM3QzW}

```
hacker@program-interaction~level16:/challenge$ ipython
Python 3.8.10 (default, Nov 22 2023, 10:22:35)
Type 'copyright', 'credits' or 'license' for more information
IPython 8.12.3 -- An enhanced Interactive Python. Type '?' for help.

In [1]: import subprocess;subprocess.run(["./embryoio_level16"])
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : ipython
the challenge will check for a hardcoded password over stdin : usaxszyn

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is an interactive ipython instance.

[INFO] Since ipython runs as a script inside python, this will check a few things:
[INFO] 1. That the process itself is python.
[INFO] 2. That the module being run in python is ipython.
[INFO] If the process being checked is just a normal 'ipython', you'll be okay!

[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] This program expects you to enter a simple password (specifically, usaxszyn). Send it now!
[INFO] Reading in your input now...
usaxszyn
<!-- input password here -->
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{Yr-B3CW7dZZGbHy9_u4_x6VwSW6.QX2EDL0MjM3QzW}

Out[1]: CompletedProcess(args=['./embryoio_level16'], returncode=0)
```

Level 17

Answer: pwn.college{cKBwjI20yAOmm4UyFXIkS1VzkCT.QX3EDL0MjM3QzW}

```
hacker@program-interaction~level17:/challenge$ ipython
<!-- open ipython shell -->
Python 3.8.10 (default, Nov 22 2023, 10:22:35)
Type 'copyright', 'credits' or 'license' for more information
IPython 8.12.3 -- An enhanced Interactive Python. Type '?' for help.

In [1]: import subprocess;subprocess.run(["./embryoio_level17","woblfjdnxf"])
<!-- running file with the value -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : ipython
the challenge will check that argv[NUM] holds value VALUE (listed to the right as NUM:VALUE) : 1:woblfjdnxf

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is an interactive ipython instance.

[INFO] Since ipython runs as a script inside python, this will check a few things:
[INFO] 1. That the process itself is python.
[INFO] 2. That the module being run in python is ipython.
[INFO] If the process being checked is just a normal 'ipython', you'll be okay!

[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] My argv[1] should have a value of woblfjdnxf! Let's check...
[GOOD] You successfully passed the argument value check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{cKBwjI20yAOmm4UyFXIkS1VzkCT.QX3EDL0MjM3QzW}

Out[1]: CompletedProcess(args=['./embryoio_level17', 'woblfjdnxf'], returncode=0)
```

Level 18

Answer: pwn.college{s68uOGFKjia4b8Ta2WLJ6R_qf-U.QX4EDL0MjM3QzW}

```
hacker@program-interaction~level18:/challenge$ ipython
Python 3.8.10 (default, Nov 22 2023, 10:22:35)
Type 'copyright', 'credits' or 'license' for more information
IPython 8.12.3 -- An enhanced Interactive Python. Type '?' for help.

In [1]: import subprocess
<!-- importing subprocess module -->
In [2]: %env bxajoa=vchylivxon
env: bxajoa=vchylivxon
<!-- I used `%env` magic command in IPython to set an environment variable. It sets the variable in the environment of the IPython process itself, not in a Python variable named env that I can pass around. -->

In [3]: subprocess.run(["./embryoio_level18"])
<!-- And then run the file -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : ipython
the challenge will check that env[KEY] holds value VALUE (listed to the right as KEY:VALUE) : bxajoa:vchylivxon

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is an interactive ipython instance.

[INFO] Since ipython runs as a script inside python, this will check a few things:
[INFO] 1. That the process itself is python.
[INFO] 2. That the module being run in python is ipython.
[INFO] If the process being checked is just a normal 'ipython', you'll be okay!

[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] My 'bxajoa' environment variable should have a value of vchylivxon! Let's check...
[GOOD] You successfully passed the environment value check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{s68uOGFKjia4b8Ta2WLJ6R_qf-U.QX4EDL0MjM3QzW}

Out[3]: CompletedProcess(args=['./embryoio_level18'], returncode=0)
```

Level 19

Answer: pwn.college{IzI9oWQgZRp3x0_L9xkqNssPZPg.QX5EDL0MjM3QzW}

```
hacker@program-interaction~level19:/challenge$ ipython
<!-- open ipython shell -->
Python 3.8.10 (default, Nov 22 2023, 10:22:35)
Type 'copyright', 'credits' or 'license' for more information
IPython 8.12.3 -- An enhanced Interactive Python. Type '?' for help.

In [1]: import subprocess
<!-- importing subprocess module to run the file -->

In [2]: with open('/tmp/etksmq', 'r') as file : subprocess.run(["./embryoio_level19"], stdin=file)
<!-- opens /tmp/etksmq for reading ('r') and then runs ./embryoio_level19, passing the file as stdin. This effectively redirects the input from /tmp/etksmq to the challenge program, mimicking the input redirection you would normally do in a shell with < /tmp/etksmq. -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : ipython
the challenge will check that input is redirected from a specific file path : /tmp/etksmq
the challenge will check for a hardcoded password over stdin : tbbefvop

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is an interactive ipython instance.

[INFO] Since ipython runs as a script inside python, this will check a few things:
[INFO] 1. That the process itself is python.
[INFO] 2. That the module being run in python is ipython.
[INFO] If the process being checked is just a normal 'ipython', you'll be okay!

[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected a file called /tmp/etksmq to my stdin. Checking...
[TEST] I will now check that you redirected /tmp/etksmq to/from my stdin.

[ADVICE] File descriptors are inherited from the parent, unless the FD_CLOEXEC is set by the parent on the file descriptor.
[ADVICE] For security reasons, some programs, such as python, do this by default in certain cases. Be careful if you are
[ADVICE] creating and trying to pass in FDs in python.
[GOOD] The file at the other end of my stdin looks okay!
[TEST] This program expects you to enter a simple password (specifically, tbbefvop). Send it now!
[INFO] Reading in your input now...
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{IzI9oWQgZRp3x0_L9xkqNssPZPg.QX5EDL0MjM3QzW}
```

Level 20

Answer: pwn.college{YB8atyeBY4fDlB4Uk_LweNFMz7Z.QXwIDL0MjM3QzW}

```
hacker@program-interaction~level20:/challenge$ ipython
<!-- opening the shell -->
Python 3.8.10 (default, Nov 22 2023, 10:22:35)
Type 'copyright', 'credits' or 'license' for more information
IPython 8.12.3 -- An enhanced Interactive Python. Type '?' for help.

In [1]: import subprocess
<!-- importing subprocess module -->
In [2]: with open('/tmp/ultuey', 'w') as file: subprocess.run(["./embryoio_level20"], stdout=file)
<!-- open a file with write mode with specifies path of the redirected file and then run with the stdout to the file -->
In [3]: with open('/tmp/ultuey', 'r') as file:
   ...:     contents = file.read()
   ...:     print(contents)
   <!-- and then open the redirected file and then print the output -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : ipython
the challenge will check that output is redirected to a specific file path : /tmp/ultuey

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is an interactive ipython instance.

[INFO] Since ipython runs as a script inside python, this will check a few things:
[INFO] 1. That the process itself is python.
[INFO] 2. That the module being run in python is ipython.
[INFO] If the process being checked is just a normal 'ipython', you'll be okay!

[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected my stdout to a file called /tmp/ultuey. Checking...
[TEST] I will now check that you redirected /tmp/ultuey to/from my stdout.

[ADVICE] File descriptors are inherited from the parent, unless the FD_CLOEXEC is set by the parent on the file descriptor.
[ADVICE] For security reasons, some programs, such as python, do this by default in certain cases. Be careful if you are
[ADVICE] creating and trying to pass in FDs in python.
[GOOD] The file at the other end of my stdout looks okay!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{YB8atyeBY4fDlB4Uk_LweNFMz7Z.QXwIDL0MjM3QzW}
```
