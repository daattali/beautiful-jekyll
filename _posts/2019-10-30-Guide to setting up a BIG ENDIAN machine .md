---
layout: post
title: Guide to setting up a BIG ENDIAN machine
tags: [Guide, Big endian, endianness, debian]
comments: true
---

A while back I wrote a program that checks if the machine I'm running the program on is little or big endian. In order to check that the program recognizes a big endian machine, I needed to setup such a machine, and run my program on it.
This is how:
1. Go to [https://people.debian.org/~aurel32/qemu/mips/](https://people.debian.org/~aurel32/qemu/mips/), download **debian_squeeze_mips** or **debian_whezzy_mips** , and **vmlinux-3.2.0.4-5kc-malta** to your machine.
2. In order to copy your files to the big endian machine:
```
sudo mount -o loop /home/<your_user>/floppy /mnt/tmp
```
Then copy your files to ```/mnt/tmp```. 

3. In order to start the machine:
```
qemu-system-mips64 -M malta -kernel vmlinux-2.6.32-5-5kc-malta -hda debian_squeeze_mips_standard.qcow2 -append "root=/dev/sda1 console=tty0" -drive file=/home/<your_user>/floppy,if=floppy,format=raw,index=0
```
or (depends if you downloded squeeze or wheezy):
```
qemu-system-mips64 -M malta -kernel vmlinux-3.2.0-4-5kc-malta -hda debian_wheezy_mips_standard.qcow2 -append "root=/dev/sda1 console=tty0" -drive file=/home/<your_user>/floppy,if=floppy,format=raw,index=0
```
The password of root is root.

4. Mount the floppy:
```
modprobe floppy
mount -t ext2 /dev/fd0 /mnt/floppy
```
Then just ```cd``` to ```/mnt/floppy```, transfer your files from there to the machine and use them.
