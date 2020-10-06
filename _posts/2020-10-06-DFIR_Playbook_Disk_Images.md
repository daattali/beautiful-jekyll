---
categories:
  - blog
title: DFIR Playbook - Disk Images
subtitle: An extract from my Physical Playbook, continuing The SleuthKit (TSK), Timelines etc
tags: [dfir, disk, tsk, mft, timeline]
comments: false
header:
  teaser: /img/dsk/disk.jpg
---


# Introduction

This post aims to replicate my physical playbook on Disk Images and includes the following tools

    - The SleuthKit(TSK)
    - Ripl.pl
    - find (Hash unallocated files without extracting... find that malware)

[*Back to table of contents*](#)

## Overview

Broadly, the following overview, will show the basic fls / mmls commands. For each of the red circles, that is where we're getting the inode or offset from

Command | Description | Comments | Use
-------|--------|-------|--------
`mmls <filename>`| Show's partitions and disk offsets | Usually the largest partition that starts at approximately 63 for BIOS versions of windows, and the second partition after 2048 for EFI versions of windows | [![mmls](/img/dsk/mmls.png)](/img/dsk/mmls.png))
`fls -o <offset> <filename>`| Using the offsets identified on mmls will show the contents off the root directory (ls -lah equivalent)| - | [![flso](/img/dsk/flso.png)]([![flsd](/img/dsk/flso.png)])
`fls -o <Offset> <filename> -D`| shows only directories the directories avialable. | - | [![flsd](/img/dsk/flsd.png)](/img/dsk/flsd.png)
`fls -o <offset> <filename> <inode>`| lists the contents of a given directory. | - | - [![flsi](/img/dsk/flsi.png)](/img/dsk/flsi.png)
`fls -o <offset> <filename> <inode> -r` | lists the contents of a given directory and all its sub directories | - | [![flsr](/img/dsk/flsr.png)](/img/dsk/flsr.png)
`icat -o <offset> <filename> <inode>` | cat's out the file to STDOUT, can be redirected to make a copy of the file by adding `> file.txt`. | - | [![icat](/img/dsk/icat.png)](/img/dsk/icat.png)
`tsk_recover -o <offset> <filename> -e -d <Directory inode>` | Extracts an entire directories files, including those that are unallocated, useful for deleted files | - | [![tsk](/img/dsk/tsk.png)](/img/dsk/tsk.png)

[*Back to table of contents*](#)

# Using TSK to make a timeline

You can tsk for more than just extracting files. Its one of the best, and most lightweight tools to make a quick MFTTimeline, or, Filesystem timeline. And, whats better, is there is no mounting, period, thank the DFIR Gods. This makes this one of the best and quickest triage tools to use.

[*Back to table of contents*](#)

## Triage Timeline

Command | Description
-------|--------
`fls -o <offset> <filename> -r -p -m <PartitionLetter>:/ > <outputfile>`| Generates a tsk triage timeline bodyfile
`mactime -b <filename? -b <bodyfile> -d -y -z <Timezone> <StartTime> <EndTime> > <outputfile>.csv`| Creates a csv timeline from the body file. Tzformat = `Australia/Sydney` TimeFormat = `2000-04-20T00:00:00` NOTE: `-z` with `<timezone>` `<StartTime>` or `<EndTime>` are optional
`grep -v -i -f timeline_noise.txt <outputfile>.csv > <outfile-final>.csv` | Reduces timeline noise

[*Back to table of contents*](#)

### timeline_noise.txt

`Content.IE5`\
`Temporary\ Internet\ Files`\
`IETldCache`\
`PrivacIE`\
`ACPI`\
`MSIE\ Cache\ File`\
`\(\$FILE\_NAME\)`\
`THREAD`\  
`DLL\ LOADTIME`\

[*Back to table of contents*](#)

## MFT Timeline

Command | Description
-------|--------
`icat -o <offset> <filename> 0 > <directory>/mft.raw`| Extracts mft from disk for enhanced timeline
`analyzeMFT.py -f <directory>/mft.raw -e -o mfttl.csv`| Generates a MFT CSV Timeline

[*Back to table of contents*](#)

## Quick Registry analysis

- `rip.pl -r NTUSER.DAT -p userassist` From the files extracted with tsk_recover, you can quickly get the userassist keys. If you want to see other types you can use --help

[*Back to table of contents*](#)

## Hash all files, including unallocated with find on a live linux system

-`find . -type f -exec md5sum "{}" \;`

[*Back to table of contents*](#)
