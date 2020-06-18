---
title: "The Complete Data Science Setup (macOS)"
author: "Sam Edwardes"
categories: ["data-science"]
tags: ["environment"]
date: "2020-06-08"
type: "post"
---

One of the funnest (and most frustrating) parts of data science is the vast array of tools available to us. It can be overwhelming where to start. Every now and then I like to completely wipe my computer clean, and then reinstall everything from scratch. This helps clean up my computer, and make sure everything is running smoothly.

This is a living document that captures my most up to date set up. My set up is inspired by the University of British Columbia Data Science Program which provides helpful setup guides for three operating systems ([macOS](https://ubc-mds.github.io/resources_pages/install_ds_stack_mac/), [Windows](https://ubc-mds.github.io/resources_pages/install_ds_stack_windows/), and [Ubuntu](https://ubc-mds.github.io/resources_pages/install_ds_stack_ubuntu/)).

My guide currently covers the following areas.

- [Python](#python)
- [Homebrew](#homebrew)
- [Terminal and ZSH](#terminal-and-zsh)
- [R](#r)
- [VS Code](#vs-code)

## Python

I choose to use the python distribution [Miniconda](https://docs.conda.io/en/latest/miniconda.html) from [Anaconda](https://www.anaconda.com/). I use miniconda as opposed to Anaconda because it is a stripped down version of Anaconda comes with a lot of software that I do not play to use such as [Spyder](https://www.spyder-ide.org/) and [Orange](https://orange.biolab.si/).

After I have miniconda installed I then work on setting up my python environment. I like to leave the root environment as is, and create a new environment call `ds_base` (data science base). I then load in my favourite data science libraries. Note that I never use `pip install` in the `ds_base`. If there is a package that I can not install through conda I will clone `ds_base` and then install the desired package. I do this to avoid breaking the installation of `ds_base`. [Conda recommends](https://docs.conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html?highlight=pip#using-pip-in-an-environment):

- Use `pip` only after `conda`.
- Care should be taken to avoid running `pip` in the root environment.

**Steps to setup python:**

1. Follow the [official instructions](https://docs.conda.io/en/latest/miniconda.html) to install miniconda.
2. Create a new conda environment. You can either add packages as you wish, or get started by basing your data science environment off of my own. Run one of the following commands in your shell.

```bash
# option 1: start from scratch 
conda create -name ds_base

# option 2: start with my suggested packages
# download my environment_ds_base.yml file from github
curl -o environment_ds_base.yml https://gist.githubusercontent.com/SamEdwardes/ae9fd4582d5fe213c5e2c43b68a78e12/raw/7d8c163a8d0da96602133d739d92c67337d9223a/environment_ds_base.yml
# create environment from yml file
conda env create -f environment_ds_base.yml
```

Below is a complete list of packages in my environment

{{< gist samedwardes ae9fd4582d5fe213c5e2c43b68a78e12 >}}


## Homebrew

[Homebrew](https://brew.sh/) is an open source package manager for macOS and linux. When ever possible I try and install software using Homebrew as it helps keep everything organized. Some of my favourite software that I download from homebrew include:

- `tree`: Allows you to view directories and files in a tree like structure
- `gh`: The [GitHub.com CLI](https://cli.github.com/). Great for quickly checkout PRs, or creating issues from the command line.
- `autojump`: Allows you to quickly jump between directories in the command line ([GitHub README](https://github.com/wting/autojump)).
- `node` and `npm`: I never use these directly, but lots of other tools seem to rely on them.

**Steps to install Homebrew:**

```bash
# download and install homebrew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
# install some of my favourite packages
brew install tree
brew install github/gh/gh
brew install autojump
brew install node
```


## Terminal and ZSH

Instead of the default Mac OS terminal app I use [iTerm2](https://www.iterm2.com/). It provides a lot of different options for themes, uses tabs, and allows you to have a split layout on one tab.

<a href="https://imgur.com/AsAkhjz"><img src="https://i.imgur.com/AsAkhjz.png" title="source: imgur.com" /></a>

I also use ZSH instead of bash. ZSH is now the default shell in macOS, but if you are operating on an older system it may be bash. Here is a good article from [stackabuse.com](https://stackabuse.com/zsh-vs-bash/) comparing the two.

Lastly I customize ZSH with another tool called [Oh My ZSH](https://ohmyz.sh/). The tool allows you to extend the usefulness of ZSH by adding additional features, plugins, and themes.

**Steps to setup iTerm2, ZSH, and Oh My ZSH**

1. Install iTerm2 from [https://www.iterm2.com/](https://www.iterm2.com/)

2. I will assume that you are already using ZSH, but if you are not update to the latest version of macOS and ZSH should be the default. Here is a guide from [How-To-Geek](https://www.howtogeek.com/444596/how-to-change-the-default-shell-to-bash-in-macos-catalina/) to help switch between shells.

3. Install Oh My ZSH using:

   ```bash
   sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
   ```

4. Edit the `~/.zshrc` file to add some customizations. Every time you open a new command line window/tab, or refresh your current command line by calling `zsh` this file will be run. I add a combination of functions and alias for commonly performed tasks. You can copy and paste the below into your own `.zshrc` file if you wish, or just add your own.

<script src="https://gist.github.com/SamEdwardes/958a8644b5a045a82afce80eaf6cafdc.js"></script>

5. I also add the following lines to the file to enable my desired theme and plugins:

```bash
plugins=(git autojump)
ZSH_THEME="blinks"
```

## R

Work in progress...

## VS Code

Visual Studio Code, or VS Code for short is one of the most popular editors at the moment. I enjoy listing to the [Talk Python to Me](https://talkpython.fm/) podcast and it seems like 99% of guests use VS code now. VS Code is great because it is very light weight, but has a ton of powerful extensions.

**Steps to setup VS Code**

1. Download from [https://code.visualstudio.com/](https://code.visualstudio.com/)
2. Install extensions. I currently use the following extensions. You can download them by searching for each one in the extensions sidebar.

<a href="https://imgur.com/OeacnZr"><img src="https://i.imgur.com/OeacnZr.png" title="source: imgur.com" /></a>