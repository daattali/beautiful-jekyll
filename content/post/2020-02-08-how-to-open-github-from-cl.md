---
title: "How to Open GitHub.com Repo from the Command Line"
author: "Sam Edwardes"
categories: ["data-science"]
tags: ["command-line"]
date: "2020-02-08"
type: "post"
---

During my Masters of Data Science I was often working on many GitHub repos at the same time. Most of our homework was graded on GitHub.com, so it was important to ensure that after pushing my local repo to GitHub.com that everything rendered correctly.

I realized there was no quick way to open the repo on GitHub.com from the command line. This started to become annoying because I would constantly have to navigate to the repo in my browser.

After many months of pain, I found a very quick and simple solution. With a few lines of a bash script you can open the remote repo in your default browser.

Here is how to do it:

- Open your `.bash_profile` or `.zshrc` file.
- Copy and paste the code below into the file

```bash
gopen(){
    # open the current repo in browser
    # https://stackoverflow.com/questions/4089430/how-can-i-determine-the-url-that-a-local-git-repository-was-originally-cloned-fr
    git_url=`git config --get remote.origin.url`
    open "$git_url"
}
```

- Restart your command line.
- Test that it is working by navigating in the command line to a directory with a remote repo. Type `gopen` into the command line, and it should open your remote repo in your default browser!

*Note I am working on a Mac, these instructions may not work for Linux or Windows users.*

![screencast](https://i.imgur.com/rMNNld4.gif)
