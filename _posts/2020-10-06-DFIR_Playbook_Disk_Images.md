---
layout: post
title: DFIR Playbook - Disk Images
subtitle: An extract from my Physical Playbook, contining The SleuthKit (TSK), Timelines etc
tags: [dfir, disk, tsk, mft, timeline]
comments: false
---

# Introduction
This post aims to replicate my physical playbook on Disk Images and includes the following tools
    - The SleuthKit(TSK)

## Overview

Broadly, the following overview, will show the basic fls / mmls commands. For each of the red circles, that is where we're getting the inode or offset from

Command | Description | Comments | Use
-------|--------|-------|--------
`mmls <filename>`| Show's partitions and disk offsets | Usually the largest partition that starts at approximatley 63 for BIOS versions of windows, and the second partition after 2048 for EFI versions of windows | [![mmls](https://angry-bender.github.io/img/dsk/mmls.png)](https://angry-bender.github.io/img/dsk/mmls.png))
`fls -o <offset> <filename>`| Using the offsets identified on mmls will show the contents off the root directory (ls -lah equivalent)| - | [![flso](https://angry-bender.github.io/img/dsk/flso.png)]([![flsd](https://angry-bender.github.io/img/dsk/flso.png)])
`fls -o <Offset> <filename> -D`| shows only directories the directories avialable. | - | [![flsd](https://angry-bender.github.io/img/dsk/flsd.png)](https://angry-bender.github.io/img/dsk/flsd.png)
`fls -o <offset> <filename> <inode>`| lists the contents of a given directory. | - | - [![flsi](https://angry-bender.github.io/img/dsk/flsi.png)](https://angry-bender.github.io/img/dsk/flsi.png)
`fls -o <offset> <filename> <inode> -r` | lists the contents of a given directory and all its sub directories | - | [![flsr](https://angry-bender.github.io/img/dsk/flsr.png)](https://angry-bender.github.io/img/dsk/flsr.png)
`icat -o <offset> <filename> <inode>` | cat's out the file to STDOUT, can be redirected to make a copy of the file by adding `> file.txt`. | - | [![icat](https://angry-bender.github.io/img/dsk/icat.png)](https://angry-bender.github.io/img/dsk/icat.png)

# Using TSK to make a timeline

You can tsk for more than just extracting files. Its one of the best, and most lightweight tools to make a quick MFTTimeline, or, Filesystem timeline. And, whats better, is there is no mounting, period, thank the DFIR Gods. This makes this one of the best and quickest triage tools to use.

Command | Description
-------|--------
`Cat <filename>`| List the contents of a file
`less <filename>`| Browse through a file
`head <filename>`| shows first 10 lines of file, can be changed with –n <number of lines>
`tail <filename>`| shows last 10 lines of file, can be changed with –n <number of lines>
`tail –f <filename>` | Display the last 10 lines and follow a files as it grows (Very useful for debugging)
`file <filename>` | Displays what kind of file it is
