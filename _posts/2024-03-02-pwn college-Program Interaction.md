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

- ELF, which stands for Executable and Linkable Format, was designed by the Unix System Laboratories and has become widely adopted in various Unix-like operating systems, including Linux. ELF files are a specific type of binary file that follows a particular structure defining how data and code are organized within the file. This structure allows the operating system to know how to load and execute the file or how an executable can utilize a shared library.

An ELF file typically contains several sections that include:

**Header**: Specifies the ELF file type (executable file, shared library, core dump), architecture (32-bit or 64-bit), and other global attributes.
**Program Header**: Contains information necessary for the operating system to execute/load the binary file, such as memory size and location.
- `INTEP` tells the computer which helper program (interpreter) it needs to use to run this file. (points to the necessary helper to run the program) 
- `LOAD` tells the computer which parts of the program need to be loaded into memory so it can run. (provides the setup instructions for placing the program's parts in the right spots in memory)

**Section Header**: Provides information about the file's sections, including code, data, symbol tables, and more.
- `.text`, `.data`
**Actual Code and Data**: The binary instructions that the CPU executes and the data it uses.

### What is symbols in binary?

- Symbols serve as a bridge between the human-readable code that a programmer writes and the binary code that a computer executes.

## Linux Processing Loading

`cat /flag`

1. A process is created

2. cat is loaded
    - Before anything loaded, the kernel checks for executable permissions. 
    - To figure out what to load, the Linux kernel reads the beginning of the file. and makes a decision
3. cat is initialized

## Linux process runtime



