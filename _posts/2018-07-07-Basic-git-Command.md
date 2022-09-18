---
layout: post
title: Basic Git Commands
subtitle: Git Command You Will Ever Need as a Programmer
cover-img: /assets/img/cover.jpg
thumbnail-img: /assets/img/diary.png
share-img: /assets/img/path.jpg
tags: [git, github, gitlab, version controlling, git command]
---

Git is a tools for managing versions of directories between local and remote (cloud) locations. It is a version control system that can efficiently manage small to very large projects and is free and open-source. Git is a tool used to log source code changes, allowing several engineers to collaborate on non-linear development.


Any development project, including test automation, benefits from version control, often known as source control. It is the process of keeping track of and granting control over alterations made to source code. Let's learn about some of the most often used Git commands since Git is one of the most widely used version control solutions.

Mastering Git takes time, however in this post you'll discover key commands that are used more regularly.

- [The Common steps are as follows:](#the-common-steps-are-as-follows)
- [Git Commands You Should Know](#git-commands-you-should-know)
- [CMD Command for Windows PC Terminal](#cmd-command-for-windows-pc-terminal)

To Install **Git** on your local computer download this from official site git:

[x]  [**Git Download link**](https://git-scm.com/downloads)


or 

You Can simply download github desktop version GUI Operation 

[x]  [**Github GUI Download link**](https://desktop.github.com/)


# The Common steps are as follows:
1. Workign Directory (mkdir/ Touch). 
2. Stage (Add).
3. Repository (Commit).
4. Remote (Push/ Pull).





# Git Commands You Should Know

 <h2> 1. git config</h2>

Tell git who you are. In the beginning, you must configure the author name and email address which shall be used for committing your changes in the git directory.

- The **user.name** and **user.email** are initially set up using the git config command. This details the login and email address that will be utilized from a local repository.
- When the —global flag is used with git config, the settings are written to all of the computer's repositories.

```
git config --global user.name "Jhon Doe"
git config --global user.email jhondoe@example.com
 ```


 <h2> 2. git init</h2>

This command is used to create a new repository on your local device
- You shall provide your new repository name as well. 

git init repositoryName


```
git init
 ```


 <h2> 3. git clone</h2>

With this command, the most recent version of a remote project is downloaded and copied to the specified place on the local computer. 
- If you want to download any repository to your local computer use this command.
 


```
git clone https://github.com/rafayethossain/rafayethossain.github.io.git
 ```

<h2>4. git status</h2>

This command lists all the files that have changed and those you still need to add or commit to your remote repository. 



```
git status
 ```

<h2>5. git add</h2>

- To stage changes of your current directory.
```
git add.
 ```
- To changes all the files except the deleted one.

```
git add \
```
- To stage changes of all the files of specific extension.

```
git add \*.extension

```

- To stage changes of all the files of specific extension.

```
git add \*.extension

```
- To stage your root folder.

```
git add -all 

```
or
```
git add -A 

```

- To stage changes of all the files of specific extension.

```
git add \*.extension

```
- To stage changes of all the files of specific extension.

```
git add \*.extension

```
- To stage changes of all the files of specific extension.

```
git add \*.extension

```


 

<h2>6. git commit</h2>

This command permanently stores a snapshot of the file in the version history. Commit does mean that changes are hosted to the remote repository

```
git commit -m "<commit message>"
 ```
 

<h2>8. git push</h2>

The next step is to send your changes to the remote server after committing your changes. Your commits are uploaded to the remote repository using git push.



```
git push
 ```


<h2>9. git pull</h2>

The remote repository's updates are downloaded using the git pull command. This command combines git fetch and git merge, so when we use git pull, it downloads the most recent updates from a remote repository (git fetch) and quickly applies them to your local repository (git merge).



```
git pull
 ```


<h2>10. More helpful git command</h2>


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



# CMD Command for Windows PC Terminal 
- **touch filename.extension**: to create a file.
- **mkdir foldername**: to create a folder.
- **cd foldername**: to enter a folder.
- **pwd**: to check the directory currently you are working on.

{: .box-success}
Enjoy !!! 
See Yaaa, Next.
