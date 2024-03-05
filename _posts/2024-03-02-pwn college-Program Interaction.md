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

I just executed `./embryoio_level1`. It was really easy.

```
hacker@program-interaction~level1:/challenge$ ./embryoio_level1
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
# Here
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
# I executed the file and input the password.

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
# making environment
hacker@program-interaction~level4:/challenge$ ./embryoio_level4
# and then executed the file
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
# outputs the string I was given as password and then redirects to the specific file path
hacker@program-interaction~level5:/challenge$ ./embryoio_level5 < /tmp/tlvzpz
# redirects the opposite direction from the above and then execute the file using the input from /tmp/tlvzpz
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
# redirect the file into the path

hacker@program-interaction~level6:/challenge$ cat /tmp/enhwpg
# and the read the redirected file
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
