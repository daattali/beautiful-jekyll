---
layout: post
title: Basic Git Commands
subtitle: Basic Git commands for  non programmer
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [git, github, gitlab, version controlling, git command]
---

U# Git Commands You Should Know
## Git is a tools for version controlling between local and remote (cloud) directory. 

# The Common steps are as follows:
1. Workign Directory (mkdir/ Touch). 
2. Stage (Add).
3. Repository (Commit).
4. Remote (Push/ Pull).

# CMD Command for Windoes Terminal 
- **touch filename.extension**: to create a file.
- **mkdir foldername**: to create a folder.
- **cd foldername**: to enter a folder.
- **pwd**: to check the directory currently you are working on.
# Git Basics:
- **git init**: to initiate git in your working directory (local).
- **git clone URL**: to pull (copy) a repository from the cloud.
- **git status**: to check the changes/ status in your directory.

- **git add -all**: to stage your root folder.
- or **git add -A**: to stage your root folder.
- **git add .**: to stage changes of your current directory.
- **git add \***: to stage changes all the files except the deleted one.
- **git add \*.extension**: to stage changes of all the files of specific extension.
- **git reset**: to unstage your changes in your files.
- **git commit -m"write something here"**: to commit your staged Changes.
- **git reset HEAD~**: to unstage your committed changes.
- **git reset -hard**: almost same to the **git reset** but it also gives you the deleted files.
- **git rm filename.extension**: to delete and stage the changes in your file.
- **git rm filename.extension f**: to delete the file forcefully which hasn’t been staged.
- **git rm --cached filename.extension**: to stage the changes and not to delete the file from working directory.  
- **git rm -r folder**: to remove folder.
- **git branch**:to check the current branch.
- **git branch branch-name** to create a new branch.
- **git checkout branchName**: to switch to a branch.
- **git merge branchName -m"write something"**: to merge your branch with another branch.
- **ls**: to see the list of your files.
- **Git push, fetch, pull**: command to transfering data between remote and local directory.  
- **git push origin branchName**: to storing to specif cloud branck.
- **git fetch**: to copy remote data to local
- **git pull**: to clone all files to local directory from cloud. 



Enjoy !!! 
**See Yaaa, Next.**
