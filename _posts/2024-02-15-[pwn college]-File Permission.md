---
layout: post
title: File permission in linux
subtitle: Here I want to explain about what is file permission in linux
# cover-img: /assets/img/banditlogo.png
# thumbnail-img: /assets/img/overthewire.jpeg
# share-img: /assets/img/path.jpg
tags: [file permission, security, linux, seuid]
comments: true
author: Lantana Park
---

![file permission](/assets/img/pwn-college-program-misuse/Screenshot%202024-02-23%20at%2013.32.21.png)

# Mastering File Permissions in Linux

Linux is renowned for its robust security model, a significant part of which involves file permissions. Understanding how to manage these permissions is essential for securing system and managing resources effectively. This post will guide you through the basics of Linux file permissions, how to view them, and how to modify them.

## Understanding Linux File Permissions

In Linux, each file and directory has a set of permissions that control the actions users can perform on it. These permissions determine who can read, write, or execute the file. When we talk about file permissions, we usually refer to three types of users:

- **Owner:** The user who owns the file.
- **Group:** The group that owns the file.
- **Others:** Any other user who has access to the file.

## Viewing File Permissions

To view the permissions of a file, you can use the `ls -l` command in the terminal. This command lists files and directories with detailed information, including their permissions, number of links, owner, group, size, and the time of last modification.

The permissions are displayed in the format `drwxrwxrwx`, where:
d / rwx / rwx / rwx

- `d` indicates if it's a directory (a dash `-` represents a file).
- The first `rwx` set shows the owner's permissions.
- The second `rwx` set shows the group's permissions.
- The third `rwx` set shows the permissions for others.

Each character represents:

- `r` - Read permission. (4)
- `w` - Write permission. (2)
- `x` - Execute permission. (1)
- `-` - No permission.

## Changing File Permissions

To change file permissions, you can use the `chmod` command. Permissions can be set in either symbolic mode (using letters) or numeric mode (using numbers).

### Symbolic Mode

In symbolic mode, you can add (`+`), remove (`-`), or set (`=`) permissions for the owner (`u`), group (`g`), others (`o`), or all users (`a`).

For example, to add execute permission for the owner, you would use:

```bash
chmod 750 filename
```

- It means that all permission(read, write and execute) will be assigned to the owner, users who belongs to group can read and execute and others have on permission about the file.
