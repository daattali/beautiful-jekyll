---
layout: post
title: pwn college Fundamentals - Program Interaction
# subtitle: Sending HTTP requests using nc, curl, python
cover-img: /assets/img/pwnCollege.jpeg
thumbnail-img: /assets/img/pwnCollege.jpeg
# share-img: /assets/img/path.jpg
tags: [web, security, pwn, college, linux]
comments: true
author: Lantana Park
---

# Introduction

## Introduction to Binary Files

`/bin/cat`

### What is Binary files

- A binary file is a file that contains data in binary form. This means it is stored in a format that is directly readable by a computer, not in a human-readable format like text files.

### What is ELF files 🧚‍♂️

- ELF(Executable and Linkable Format) files are a specific type of binary file that follows a particular structure defining how data and code are organized within the file. This structure allows the operating system to know how to load and execute the file or how an executable can utilize a shared library.

An ELF file typically contains several sections that include:

**Program Header**: Contains information necessary for the operating system to execute/load the binary file, such as memory size and location.

- `INTEP` tells the computer which helper program (interpreter) it needs to use to run this file. (points to the necessary helper to run the program)
- `LOAD` tells the computer which parts of the program need to be loaded into memory so it can run. (provides the setup instructions for placing the program's parts in the right spots in memory)

**Section Header**: Provides information about the file's sections, including code, data, symbol tables, and more.

- `.text`, `.data`

### What is symbols in binary?

- **Symbol** refer to names used to represent various elements within a piece of software. These elements can include **functions**, **variables**, and **other types of identifiers** that have been coded into a program.

- Symbols in ELF files are used to resolve library calls and find functions and variables.

### Tools to interact with ELF

`gcc` makes ELF file (allows compile)
`readelf` parses ELF header
`objdump` parses ELF header and disassemble the source code
`nm` views ELF symbols
`patchelf` changes some ELF properties
`objcopy` swaps out (replace) ELF sections
`strace` monitors the system calls and signals

## Linux Process Loading

`cat /flag`

### Process Creation

![load](/assets/img/programInteraction/Screenshot%202024-03-09%20at%2013.47.41.png)

Upon running cat /flag, the system begins by initiating a new process. This involves the allocation of resources necessary for the process to run, including the creation of a unique virtual address space for it, enabled by the operating system's virtual memory system. This space allows the process to operate as if it has its own dedicated memory, facilitating the execution of multiple applications concurrently by simulating more RAM than physically available through disk space.

### Process Loading

1. Executable Permission Check: The system checks if the cat executable has the required permissions set to allow its execution, ensuring security by preventing unauthorized file execution.

2. Identifying the File Type: The kernel reads the ELF header of /bin/cat to determine the file type, identifying it as either statically or dynamically linked. This step is crucial for understanding how to properly load the file into memory.

- Static File: Contains all necessary code within the executable, making it larger but self-contained.

- Dynamically Linked File: Requires external libraries to be loaded at runtime, reducing the file size and allowing for shared library use.
  Loading the Program and Its Interpreter: For dynamically linked files, such as cat, the kernel loads both the program and its dynamic linker into the process's virtual address space. This involves setting up the memory addresses the process will use, isolated from other processes to ensure security and stability.

5. Locating and Loading Required Libraries: The dynamic linker identifies and loads all necessary shared libraries (e.g., libc) into the virtual address space, managing dependencies to ensure the program has access to all the code it needs.

6. Relocation and Symbol Resolution: Adjusts the program's internal addresses to correspond with the actual memory locations of the loaded libraries and links program functions and variables with their real implementations in these libraries.

### `cat` is initialized

With the cat executable now loaded, along with its required libraries and all symbols resolved, control is transferred to the program's entry point. This marks the beginning of the program's execution phase.

At this point, cat is fully initialized and begins to execute its primary function: reading the contents of the /flag file and displaying them to the user. This involves reading from the specified file and writing the contents to the standard output, effectively completing the command's operation.

## Linux Process Execution

### `cat` is lauched

![lauching](/assets/img/programInteraction/Screenshot%202024-03-09%20at%2016.24.20.png)

- Linux process execution involves loading a program into the virtual memory space of a process.

- The execution of a program is handled by a function called libc start main.

### `cat` reads its arguments and environment

![arugments](/assets/img/programInteraction/Screenshot%202024-03-09%20at%2016.31.59.png)

- Environment variables are used to pass additional arguments to a program.

### `cat` does its thing.

![function](/assets/img/programInteraction/Screenshot%202024-03-09%20at%2016.38.40.png)

![syscall](/assets/img/programInteraction/Screenshot%202024-03-09%20at%2016.43.44.png)

![signals](/assets/img/programInteraction/Screenshot%202024-03-09%20at%2016.56.40.png)

![sharememory](/assets/img/programInteraction/Screenshot%202024-03-09%20at%2016.57.31.png)

- Library functions and system calls are used to interact with the outside world and perform complex tasks.

- Symbols in a binary represent names of functions or variables that are imported or exported by the program.

- System calls are the primary way to interact with the Linux operating system.

- The strace command can be used to trace system calls and understand program execution.

### `cat` terminates

![termination](/assets/img/programInteraction/Screenshot%202024-03-09%20at%2016.52.46.png)

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
<!-- makes environment -->
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
<!-- redirects the file into the path -->

hacker@program-interaction~level6:/challenge$ cat /tmp/enhwpg
<!-- and the reads the redirected file -->
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
<!-- and then running the ./embryoio_level15 -->
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
<!-- password here -->
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
<!-- and then run file with the value -->
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
<!-- import subprocess module -->
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
<!-- opens ipython shell -->
Python 3.8.10 (default, Nov 22 2023, 10:22:35)
Type 'copyright', 'credits' or 'license' for more information
IPython 8.12.3 -- An enhanced Interactive Python. Type '?' for help.

In [1]: import subprocess
<!-- imports subprocess module to run the file -->

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
<!-- opens the shell -->
Python 3.8.10 (default, Nov 22 2023, 10:22:35)
Type 'copyright', 'credits' or 'license' for more information
IPython 8.12.3 -- An enhanced Interactive Python. Type '?' for help.

In [1]: import subprocess
<!-- imports subprocess module -->
In [2]: with open('/tmp/ultuey', 'w') as file: subprocess.run(["./embryoio_level20"], stdout=file)
<!-- opens a file with write mode with specified path of the redirected file and then run with the stdout to the file -->
In [3]: with open('/tmp/ultuey', 'r') as file:
   ...:     contents = file.read()
   ...:     print(contents)
   <!-- and then opens the redirected file and then print the output -->
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

Level 21

Answer: pwn.college{wQMLkpfGh9WXvCxtL8zRocYlgct.QXxIDL0MjM3QzW}

```
hacker@program-interaction~level21:/challenge$ ipython
Python 3.8.10 (default, Nov 22 2023, 10:22:35)
Type 'copyright', 'credits' or 'license' for more information
IPython 8.12.3 -- An enhanced Interactive Python. Type '?' for help.

In [1]: import subprocess
<!-- calls the subprocess module -->
In [2]: result = subprocess.run(["./embryoio_level21"], env={})
<!-- runs this program with environment variables holds empty value  -->
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : ipython
the challenge will check that the environment is empty (except LC_CTYPE, which is impossible to get rid of in some cases)

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
[TEST] You should launch me with an empty environment. Checking...
[GOOD] You successfully passed the empty environment check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{wQMLkpfGh9WXvCxtL8zRocYlgct.QXxIDL0MjM3QzW}
```

Level 22

Answer: pwn.college{AB9gFodyapgph-pPeNcH3ZV7hU5.QXyIDL0MjM3QzW}

```
#!/usr/bin/python3.8
<!-- indicates the path to the python interpreter that should be used to run this script -->

import subprocess
<!-- calls subprocess module -->

file_path = "/challenge/embryoio_level22"
<!-- assigns the string to the file_path variable representing the path to the external program that the script intends to execute -->

result = subprocess.run([file_path])
```

```
hacker@program-interaction~level22:/tmp$ ./my_script.py
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : python

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is a non-interactive python instance (i.e., an executing python script).
[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{AB9gFodyapgph-pPeNcH3ZV7hU5.QXyIDL0MjM3QzW}
```

Level 23

Answer: pwn.college{oDX-O26HfL_HQB_ydL7Ux2c3yko.QXzIDL0MjM3QzW}

```
#!/usr/bin/python3.8

import subprocess

file_path = "/challenge/embryoio_level23"

result = subprocess.run([file_path])
```

```
hacker@program-interaction~level23:/tmp$ ./my_script.py
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : python
the challenge will check for a hardcoded password over stdin : dremewyh

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is a non-interactive python instance (i.e., an executing python script).
[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] This program expects you to enter a simple password (specifically, dremewyh). Send it now!
[INFO] Reading in your input now...
dremewyh
<!-- Password here -->
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{oDX-O26HfL_HQB_ydL7Ux2c3yko.QXzIDL0MjM3QzW}
```

Level 24

Answer: pwn.college{wtNYpZLg6YIV_VaytuZIfyyyug7.QX0IDL0MjM3QzW}

```
#!/usr/bin/python3.8

import subprocess

file_path = "/challenge/embryoio_level24"

result = subprocess.run([file_path, "mgwynwblde"])
```

```
hacker@program-interaction~level24:/tmp$ ./my_script.py
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : python
the challenge will check that argv[NUM] holds value VALUE (listed to the right as NUM:VALUE) : 1:mgwynwblde

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is a non-interactive python instance (i.e., an executing python script).
[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] My argv[1] should have a value of mgwynwblde! Let's check...
[GOOD] You successfully passed the argument value check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{wtNYpZLg6YIV_VaytuZIfyyyug7.QX0IDL0MjM3QzW}
```

Level 25

Answer: pwn.college{4OHO-tyKiKgS1xAnmP5FkmgNgDR.QX1IDL0MjM3QzW}

```
#!/usr/bin/python3.8

import subprocess

file_path = "/challenge/embryoio_level25"

result = subprocess.run([file_path], env={"qpvtwc":"eghdabuygy"})
```

```
hacker@program-interaction~level25:/tmp$ ./my_script.py
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : python
the challenge will check that env[KEY] holds value VALUE (listed to the right as KEY:VALUE) : qpvtwc:eghdabuygy

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is a non-interactive python instance (i.e., an executing python script).
[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] My 'qpvtwc' environment variable should have a value of eghdabuygy! Let's check...
[GOOD] You successfully passed the environment value check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{4OHO-tyKiKgS1xAnmP5FkmgNgDR.QX1IDL0MjM3QzW}
```

Level 26

Answer: pwn.college{QKvaAEdda7bur5DvgjUzbpt4xaB.QX2IDL0MjM3QzW}

```
#!/usr/bin/python3.8

import subprocess

file_path = "/challenge/embryoio_level26"

with open('/tmp/isodpx', 'r') as input_file:
<!-- reads /tmp/isodpx as input file and then run the embryoio file with input file. I stored the password "gkbdahrs" in the isodpx file -->
    subprocess.run(file_path, stdin=input_file)
```

```
hacker@program-interaction~level26:/tmp$ ./my_script.py
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : python
the challenge will check that input is redirected from a specific file path : /tmp/isodpx
the challenge will check for a hardcoded password over stdin : gkbdahrs

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is a non-interactive python instance (i.e., an executing python script).
[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected a file called /tmp/isodpx to my stdin. Checking...
[TEST] I will now check that you redirected /tmp/isodpx to/from my stdin.

[ADVICE] File descriptors are inherited from the parent, unless the FD_CLOEXEC is set by the parent on the file descriptor.
[ADVICE] For security reasons, some programs, such as python, do this by default in certain cases. Be careful if you are
[ADVICE] creating and trying to pass in FDs in python.
[GOOD] The file at the other end of my stdin looks okay!
[TEST] This program expects you to enter a simple password (specifically, gkbdahrs). Send it now!
[INFO] Reading in your input now...
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{QKvaAEdda7bur5DvgjUzbpt4xaB.QX2IDL0MjM3QzW}
```

Level 27

Answer: pwn.college{YtAmKwlId08HuMZbF_uBqZ7tNlf.QX3IDL0MjM3QzW}

```
#!/usr/bin/python3.8

import subprocess

file_path = "/challenge/embryoio_level27"

with open('/tmp/kvqktq', 'w') as file:
    subprocess.run(file_path, stdout=file)

with open('/tmp/kvqktq', 'r') as file:
    print(file.read())
```

```
hacker@program-interaction~level27:/tmp$ ./my_script.py
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : python
the challenge will check that output is redirected to a specific file path : /tmp/kvqktq

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is a non-interactive python instance (i.e., an executing python script).
[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected my stdout to a file called /tmp/kvqktq. Checking...
[TEST] I will now check that you redirected /tmp/kvqktq to/from my stdout.

[ADVICE] File descriptors are inherited from the parent, unless the FD_CLOEXEC is set by the parent on the file descriptor.
[ADVICE] For security reasons, some programs, such as python, do this by default in certain cases. Be careful if you are
[ADVICE] creating and trying to pass in FDs in python.
[GOOD] The file at the other end of my stdout looks okay!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{YtAmKwlId08HuMZbF_uBqZ7tNlf.QX3IDL0MjM3QzW}
```

Level 28

Answer: pwn.college{8EyUS3JW21gtPLHNkZ11-zQzA5R.QX4IDL0MjM3QzW}

```
#!/usr/bin/python3.8

import subprocess

file_path = "/challenge/embryoio_level28"

result = subprocess.run([file_path], env={})
```

```
hacker@program-interaction~level28:/tmp$ ./my_script.py
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : python
the challenge will check that the environment is empty (except LC_CTYPE, which is impossible to get rid of in some cases)

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] We will now check that that the process is a non-interactive python instance (i.e., an executing python script).
[INFO] The process' executable is /usr/bin/python3.8.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be python3.8.
[GOOD] You have passed the checks on the parent process!
[TEST] You should launch me with an empty environment. Checking...
[GOOD] You successfully passed the empty environment check!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{8EyUS3JW21gtPLHNkZ11-zQzA5R.QX4IDL0MjM3QzW}
```

Level 36

Answer: pwn.college{kXcw02yESKeQK0yJIxZ9QQ_XlaW.QX2MDL0MjM3QzW}

`./embryoio_level36 | cat`

To explain this command, it executes the file `./embryoio_level36` at first. And then, because of `|` (pipe operator), it takes the output of the command on its leftside `./embryoio_level36` and uses it as the input for the coammdn on its rightside `cat`

```
hacker@program-interaction~level36:/challenge$ ./embryoio_level36 | cat
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge checks for a specific process at the other end of stdout : cat

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
[TEST] You should have redirected my stdout to another process. Checking...
[TEST] Performing checks on that process!
[INFO] The process' executable is /usr/bin/cat.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be cat.
[GOOD] You have passed the checks on the process on the other end of my stdout!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{kXcw02yESKeQK0yJIxZ9QQ_XlaW.QX2MDL0MjM3QzW}
```

Level 37

Answer: pwn.college{s-cMYXjt4OGH4AK27FLSVkDJKqf.QX3MDL0MjM3QzW}

To explain this command, execting the file and then taking the output from the file and then, with the output, searching text which includes `pwn.college`

```
hacker@program-interaction~level37:/challenge$ ./embryoio_level37
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge checks for a specific process at the other end of stdout : grep

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
[TEST] You should have redirected my stdout to another process. Checking...
[FAIL] You did not satisfy all the execution requirements.
[FAIL] Specifically, you must fix the following issue:
[FAIL]    stdout of this process does not appear to be a pipe!
hacker@program-interaction~level37:/challenge$ ./embryoio_level37 | grep "pwn.college"
pwn.college{s-cMYXjt4OGH4AK27FLSVkDJKqf.QX3MDL0MjM3QzW}
```

Level 38

Answer: pwn.college{kJe9eEAfa4P1f7NhhzCAcKD6RBv.QX4MDL0MjM3QzW}

`sed` performs lots of functions on file like searching, find and replace, insertion or deletion.

Putting it all together, `./embryoio_level38 | sed ''` will execute the `embryoio_level38` program, then pass its output through `sed` without making any changes to the output.

```
hacker@program-interaction~level38:/challenge$ ./embryoio_level38 | sed ''
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge checks for a specific process at the other end of stdout : sed

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
[TEST] You should have redirected my stdout to another process. Checking...
[TEST] Performing checks on that process!
[INFO] The process' executable is /usr/bin/sed.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be sed.
[GOOD] You have passed the checks on the process on the other end of my stdout!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{kJe9eEAfa4P1f7NhhzCAcKD6RBv.QX4MDL0MjM3QzW}
```

Level 39

Answer: pwn.college{QSRW5Lo2YSPZY_g16jOpNtMUt1G.QX5MDL0MjM3QzW}

Reverse the flag twice

```
hacker@program-interaction~level39:/challenge$ ./embryoio_level39 | rev | sort | rev
ONWARDS TO GREATNESS!
[TEST] Performing checks on that process!
[GOOD] You have passed the checks on the parent process!
[GOOD] You have passed the checks on the process on the other end of my stdout!
[TEST] Checking to make sure the process is the bash shell. If this is a check for the parent process, then,
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[TEST] most likely, this is what you do by default anyways, but we'll check just in case...
[TEST] You should have redirected my stdout to another process. Checking...
[INFO] If you pass these checks, you will receive the flag.
[INFO] To pass the checks, the executable must be bash.
[INFO] The process' executable is /usr/bin/bash.
[INFO] This challenge will now perform a bunch of checks.
[TEST] Performing checks on the parent process of this process.
[INFO] To pass the checks, the executable must be rev.
[INFO] The process' executable is /usr/bin/rev.
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge checks for a specific process at the other end of stdout : rev
pwn.college{QSRW5Lo2YSPZY_g16jOpNtMUt1G.QX5MDL0MjM3QzW}
```

Level 40

Answer: pwn.college{AuGVkREcz6i_sMAyJiipEKjYGG0.QXwQDL0MjM3QzW}

```
hacker@program-interaction~level40:/challenge$ cat | ./embryoio_level40
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : bash
the challenge checks for a specific process at the other end of stdin : cat
the challenge will check for a hardcoded password over stdin : gycmhymh

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
[TEST] You should have redirected another process to my stdin. Checking...
[TEST] Performing checks on that process!
[INFO] The process' executable is /usr/bin/cat.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be cat.
[GOOD] You have passed the checks on the process on the other end of my stdin!
[TEST] This program expects you to enter a simple password (specifically, gycmhymh). Send it now!
[INFO] Reading in your input now...
gycmhymh
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{AuGVkREcz6i_sMAyJiipEKjYGG0.QXwQDL0MjM3QzW}
```

Level 42

Answer: pwn.college{c2I5XTffLzIZVAJ-HPTRnAV57L8.QXyQDL0MjM3QzW}

```
hacker@program-interaction~level42:/tmp$ ./my_script.sh
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge checks for a specific process at the other end of stdout : cat

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected my stdout to another process. Checking...
[TEST] Performing checks on that process!
[INFO] The process' executable is /usr/bin/cat.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be cat.
[GOOD] You have passed the checks on the process on the other end of my stdout!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{c2I5XTffLzIZVAJ-HPTRnAV57L8.QXyQDL0MjM3QzW}

hacker@program-interaction~level42:/tmp$ cat my_script.sh
#!/bin/bash
/challenge/embryoio_level42 | cat
```

Level 43

Answer: pwn.college{gt4fphgHImUpOrnexj9fMWE3irC.QXzQDL0MjM3QzW}

```
hacker@program-interaction~level43:/tmp$ ./my_script.sh
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge checks for a specific process at the other end of stdout : grep

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected my stdout to another process. Checking...
[TEST] Performing checks on that process!
[INFO] The process' executable is /usr/bin/grep.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be grep.
[GOOD] You have passed the checks on the process on the other end of my stdout!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{gt4fphgHImUpOrnexj9fMWE3irC.QXzQDL0MjM3QzW}

hacker@program-interaction~level43:/tmp$ cat my_script.sh
#!/bin/bash
/challenge/embryoio_level43 | grep ""
hacker@program-interaction~level43:/tmp$
```

Level 44

Answer: pwn.college{sH4mZqaMD_6-aCVCHR6x8HlydRv.QX0QDL0MjM3QzW}

```
hacker@program-interaction~level44:/tmp$ ./my_script.sh
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge checks for a specific process at the other end of stdout : sed

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected my stdout to another process. Checking...
[TEST] Performing checks on that process!
[INFO] The process' executable is /usr/bin/sed.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be sed.
[GOOD] You have passed the checks on the process on the other end of my stdout!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{sH4mZqaMD_6-aCVCHR6x8HlydRv.QX0QDL0MjM3QzW}

hacker@program-interaction~level44:/tmp$ cat my_script.sh
#!/bin/bash
/challenge/embryoio_level44 | sed ""
hacker@program-interaction~level44:/tmp$
```

Level 45

Answer: pwn.college{UdjxARW8N7NhSm5yGhvg6PURx10.QX1QDL0MjM3QzW}

```
hacker@program-interaction~level45:/tmp$ ./my_script.sh
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge checks for a specific process at the other end of stdout : rev

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected my stdout to another process. Checking...
[TEST] Performing checks on that process!
[INFO] The process' executable is /usr/bin/rev.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be rev.
[GOOD] You have passed the checks on the process on the other end of my stdout!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{UdjxARW8N7NhSm5yGhvg6PURx10.QX1QDL0MjM3QzW}

hacker@program-interaction~level45:/tmp$ cat my_script.sh
#!/bin/bash
/challenge/embryoio_level45 | rev | rev
hacker@program-interaction~level45:/tmp$
```

Level 46

Answer: pwn.college{Efj0EEg-C5LZsFMRB33c3IJ0niy.QX2QDL0MjM3QzW}

```
hacker@program-interaction~level46:/tmp$ ./my_script.sh
WELCOME! This challenge makes the following asks of you:
the challenge checks for a specific parent process : shellscript
the challenge checks for a specific process at the other end of stdin : cat
the challenge will check for a hardcoded password over stdin : hbdizecg

ONWARDS TO GREATNESS!

[INFO] This challenge will now perform a bunch of checks.
[INFO] If you pass these checks, you will receive the flag.
[TEST] Performing checks on the parent process of this process.
[TEST] Checking to make sure the process is a non-interactive shell script.
[GOOD] You have passed the checks on the parent process!
[TEST] You should have redirected another process to my stdin. Checking...
[TEST] Performing checks on that process!
[INFO] The process' executable is /usr/bin/cat.
[INFO] This might be different than expected because of symbolic links (for example, from /usr/bin/python to /usr/bin/python3 to /usr/bin/python3.8).
[INFO] To pass the checks, the executable must be cat.
[GOOD] You have passed the checks on the process on the other end of my stdin!
[TEST] This program expects you to enter a simple password (specifically, hbdizecg). Send it now!
[INFO] Reading in your input now...
hbdizecg
[GOOD] You successfully passed the password!
[GOOD] Success! You have satisfied all execution requirements. Here is your flag:
pwn.college{Efj0EEg-C5LZsFMRB33c3IJ0niy.QX2QDL0MjM3QzW}

hacker@program-interaction~level46:/tmp$ cat my_script.sh
#!/bin/bash
cat | /challenge/embryoio_level46
```

Level 47

Answer:
