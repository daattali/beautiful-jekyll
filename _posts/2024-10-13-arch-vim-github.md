---
layout: post
title: Using Arch Linux with Vim and Github
subtitle: How to clone, edit, push and pull code
tags: [arch-linux, vim, github]
comments: true
---

**pushing changes from local drive to github**

I followed [this tutorial](https://medium.com/@cbates255/push-and-pull-with-github-repos-and-the-vim-editor-265ad24c9144) to connect Arch Linux to Github, however I cam across some issues.

Know that said tutorial is for Ubuntu, so we will need to change our commands slightly to follow this in Arch Linux.

**changes**

>sudo yum install vim
>sudo yum install git

These become

>sudo pacman -S vim
>sudo pacman -S git

**issue 1**

I somehow made the owner of my git repo, after cloning it to my local drive, root (I think I did this by adding sudo to the clone command). As a result, I was unable to write or read to the files in my local drive. This was annoying to find the fix for!

**fix**

I changed the permissions of the local repo to my local account (replace 'username' with your username and 'folder' with your repo's name. -R mode makes it recursive, meaning it includes all subfolders. 777 should give you both read and write access.

>sudo chmod -R 777 /home/username/folder

You may also need to use chown to change the owner of the folder to your local account.

**issue 2**

I had trouble pushing the repo changes to github. I got this error (among others):

>error: src refspec main does not match any
>error: failed to push some refs to 'myPathToRepo

**fixes**

-make sure the password you input is a classic token, not your github password or new style token
-make sure you are pushing to the correct branch, e.g. master or main, i.e.

>git commit -m “your commit”
>git remote add origin ( your repo )
>git branch -M main 
>git push
>git push -uf origin main 

-make sure you include a comment when pushing
-when you click 'pull' on the github website, make sure you pull on the correct branch
