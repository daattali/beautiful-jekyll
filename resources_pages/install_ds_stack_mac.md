---
layout: page
title: macOS
subtitle: MDS software stack install instructions for macOS
---
These instructions will walk you through installing the required Data Science software stack for the UBC Master of Data Science program. Before starting, ensure that your laptop meets our program requirements:
- runs one of the following operating systems: macOS 10.15.X (Catalina) or later, Ubuntu 18.X or later, Windows 10 Professional, Enterprise or Education; version 1909 or later. Please note that Windows 10 Home is not sufficient as not all the software required for the program can be installed on that OS.
- can connect to networks via a wireless connection
- has at least 50 GB disk space available
- has at least 8 GB of RAM
- uses a 64-bit CPU
- is 4 years old or newer at the start of the program
- uses English as the default language
- user has full administrative access to the laptop

## Table of Contents
- [Google Chrome browser](#chrome-browswer)
- [LastPass password manager](#lastpass-password-manager)
- [Bash shell](#bash-shell)
- [GitHub](#github)
- [Git](#git)
- [Python and Jupyter](#python)
- [R, IRkernel and RStudio](#r-ir-kernel-and-rstudio)
- [PostgreSQL](#postgresql)
- [Visual Studio Code](#visual-studio-code)
- [LaTeX](#latex)
- [Make](#make)
- [Docker](#docker)

## Google Chrome browser
In MDS we will be using many tools that work most reliably on the Google Chrome browser (including our online quiz software). To install it, go to [https://www.google.com/chrome/](https://www.google.com/chrome/), click on "Download Chrome" and follow the instructions on the website to finish the installation.

## LastPass password manager
In MDS we share credentials via the password manager LastPass. This can also be useful for helping keep secure passwords and efficient authentication. Sign up for a free LastPass account here: https://lastpass.com/create-account.php. We also recommend installing the LastPass Chrome Extension available here: https://chrome.google.com/webstore/detail/lastpass-free-password-ma/hdokiejnpimakedhajhdlcegeplioahd.

## Bash shell
Apple recently changed the Mac default shell in the Terminal to Zsh, however, we aim to teach with the same shell across all three operating systems we support, which is the Bash shell. Thus, we ask that you change the default shell in your Terminal to Bash by opening the Terminal ([how to video](https://www.youtube.com/watch?v=zw7Nd67_aFw)) and typing: 

```
chsh -s /bin/bash
```

You will have to quit all instances of open Terminals and then restart the Terminal for this to take effect. 

## GitHub

In MDS we will use [GitHub.com](https://github.com/) as well as an Enterprise version of GitHub hosted here at UBC, [GitHub.ubc.ca](https://github.ubc.ca). Please follow the set-up instructions for both below.

#### GitHub.com
If you do not yet have one, sign up for a free account at [GitHub.com](https://github.com/).

#### GitHub.ubc.ca
For us to add you to the MDS organization on [Github.ubc.ca](https://github.ubc.ca) we need you to login using your CWL:

visit [Github.ubc.ca](https://github.ubc.ca) to do this.

This step is required for
- being able to store your work
- all homework submission and grading
- working collaboratively

## Git

We will be using the command line version of Git as well as Git through RStudio and JupyterLab. There are some new Git commands that we will use that are only available as of Git 2.23 (or newer), thus to get this newest version we will ask you to install Xcode command line tools (not all of Xcode), which includes Git.

Open Terminal and type the following command to install Xcode command line tools:
```
xcode-select --install
```

After installation, in terminal type the following to ask for the version:
```
git --version
```
you should see something like this (does not have to be the exact same version) if you were successful:

```
git version 2.24.2 (Apple Git-127)
```

If you run into trouble, please see that Install Git > Mac OS section from [Happy Git and GitHub for the useR](http://happygitwithr.com/install-git.html#mac-os) for additional help or strategies for Git installation.

## Python

We will be using Python for a large part of the program, including many popular 3rd party Python libraries for scientific computing. [__Anaconda__](https://www.anaconda.com/download/#macos) is an easy-to-install distribution of Python and most of these libraries (as well as Jupyter notebooks, one of the developing environments we will be using). We __require__ that you use Anaconda for this program. If you insist on using your own Python setup instead of Anaconda, we will not be able to provide technical support with installation or later issues. For this program we are using __Python 3__ , not __Python 2__, so please choose the Anaconda versions that include Python 3.7

Head to [https://www.anaconda.com/download/#macos](https://www.anaconda.com/download/#macos) and download the Anaconda version for Mac OS with **Python 3.7**. Follow the instructions on that page to run the installer.

After installation, in terminal type the following to ask for the version of conda:
```
conda --version
```
you should see something like this if you were successful at installing conda (a Python package manager):

```
conda 4.8.2
```

If you see `zsh: command not found: conda`, see the section on [Bash](#bash-shell) above to set your default Terminal shell to Bash as opposed to Zsh.

After installation, in terminal type the following to ask for the version of Python:
```
python --version
```
you should see something like this if you were successful at installing Python:

```
Python 3.7.6
```

If instead you see `Python 2.7.X` you installed the wrong version. Follow [these instructions](https://docs.anaconda.com/anaconda/install/uninstall) to delete this installation and try the installation again, selecting **Python 3.7**.

To see if Jupyter was successfully installed in the Anaconda Python distribution, **quit and restart Terminal** and type the following:

```
jupyter lab
```

A browser should have launched and you should see a page that looks like the screenshot below. 

![](/resources_pages/imgs/jupyter_lab.PNG)


If you already have installed Anaconda at some point in the past, we recommend that you update to the latest Anaconda version by updating conda. In Terminal, type the following:
```
conda update conda
conda update anaconda
```

## R, IRkernel and RStudio
We will be using R, another programming language, a lot in the program. We will use R both in Jupyter notebooks and in RStudio. To have R work in Jupyter notebooks we will also have to install the IR kernel.

#### R
Go to [https://cran.r-project.org/bin/macosx/](https://cran.r-project.org/bin/macosx/) and download the latest version of R for Mac (Should look something like this: R-3.6.1.pkg). Open the file and follow the installer instructions.

After installation, in Terminal type the following to ask for the version:
```
R --version
```

you should see something like this if you were successful:
```
R version 3.6.1 (2019-07-05) -- "Action of the Toes"
Copyright (C) 2019 The R Foundation for Statistical Computing
Platform: x86_64-pc-linux-gnu (64-bit)

R is free software and comes with ABSOLUTELY NO WARRANTY.
You are welcome to redistribute it under the terms of the
GNU General Public License versions 2 or 3.
For more information about these matters see
https://www.gnu.org/licenses/.
```

Note: Although it is possible to install R through Anaconda, we highly recommend not doing so. In case you have already installed R using Anaconda you can remove it by executing `conda uninstall r-base`.


#### RStudio
Chose and download the Mac version of RStudio from [https://www.rstudio.com/products/rstudio/download/#download](https://www.rstudio.com/products/rstudio/download/#download). Open the file and follow the installer instructions.

To see if you were successful, try opening RStudio by clicking on its icon (from Finder, Applications or Launchpad). It should open and looks something like this picture below:

![](/resources_pages/imgs/RStudio.png)

#### IR kernel

Open RStudio and type the following commands into the Console panel:

```
install.packages(c('IRkernel', 'tidyverse'))
```

Next, open **terminal** and type the following:

```
R -e "IRkernel::installspec()"
```

To see if you were successful, try running Jupyter Lab and seeing if you have working R kernel. To launch the Jupyter Lab type the following in Terminal:

```
jupyter lab
```

A browser should have launched and you should see a page that looks like the screenshot below. Now click on "R" notebook (circled in red on the screenshot below) to launch an Jupyter Lab with an R kernel.

![](/resources_pages/imgs/jupyter_lab_r_kernel.png)

Sometimes a kernel loads, but doesn't work as expected. To test whether your installation was done correctly now type `library(tidyverse)` in the code cell and click on the run button to run the cell. If your R kernel works you should see something like the image below:

![](/resources_pages/imgs/jupyter_lab_r_kernel2.png)

## PostgreSQL 

We will be using PostgreSQL as our database management system. You can download it from [here](https://www.enterprisedb.com/thank-you-downloading-postgresql?anid=1256715). Follow the instructions for the installation. In the password page, type whatever password you want, but make sure you'll remember it later. For all the other options, use the default. You can execute `SQL Shell` after the installation to test if the installation was successful.

## Visual Studio Code

We need a text editor to be able to write complete applications. One is available through Jupyter, but sometimes it is helpful to have a standalone text editor, for this we will be using the open-source text editor Visual Studio Code (VS Code). You can download VS Code at [https://code.visualstudio.com/download](https://code.visualstudio.com/download). Follow the installation instructions.

Once the installation finishes, copy the Visual Code Studio app from the Downloads folder to the Applications folder. Next run the following command in Terminal:
```
cat << EOF >> ~/.bash_profile
# Add Visual Studio Code (code)
export PATH="\$PATH:/Applications/Visual Studio Code.app/Contents/Resources/app/bin"
EOF
```

You can test that VS code is installed and can be opened from Terminal by restarting terminal and typing the following command:

```
code --version
```

you should see something like this if you were successful:
```
1.36.1
2213894ea0415ee8c85c5eea0d0ff81ecc191529
x64
```

## LaTeX

LaTeX allows to use syntax to write nicely formatted mathematical expressions and equations. For this program we only need the smaller BasicTeX package.

1. Download the BasicTeX package from [here](http://tug.org/cgi-bin/mactex-download/BasicTeX.pkg). 
2. Open the ```.pkg``` file and run the installer with default options.
3. BasicTeX has a few missing files we'll need. To install these files, restart terminal and run:
```
sudo tlmgr update --self
sudo tlmgr install framed
sudo tlmgr install titling
```

After installation, in terminal type the following to ask for the version:
```
latex --version
```
you should see something like this if you were successful:

```
pdfTeX 3.14159265-2.6-1.40.20 (TeX Live 2019)
kpathsea version 6.3.1
Copyright 2019 Han The Thanh (pdfTeX) et al.
There is NO warranty.  Redistribution of this software is
covered by the terms of both the pdfTeX copyright and
the Lesser GNU General Public License.
For more information about these matters, see the file
named COPYING and the pdfTeX source.
Primary author of pdfTeX: Han The Thanh (pdfTeX) et al.
Compiled with libpng 1.6.36; using libpng 1.6.36
Compiled with zlib 1.2.11; using zlib 1.2.11
Compiled with xpdf version 4.01
```

## Make
We will be using Make to automate our analysis scripts. More on this later! To install Make type the following in the Terminal:

```
xcode-select --install
``` 

To test if Make is successfully installed, in Terminal type the following to ask for the version:
```
make --version
```
you should see something like this if it is successfully installed:

```
GNU Make 3.81
Copyright (C) 2006  Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.

This program built for i386-apple-darwin11.3.0
```

## Docker

You will use Docker to create reproducible, sharable and shippable computing environments for your analyses. For this you will need a Docker account. You can sign up for a free one here: https://store.docker.com/signup?next=%2F%3Fref%3Dlogin

After signing-up and signing into the Docker Store, go here: https://store.docker.com/editions/community/docker-ce-desktop-mac and click on the "Get Docker" button on the right hand side of the screen. Then follow the installation instructions on that screen. 

To test if Docker is working, after installation open the Docker app by clicking on its icon (from Finder, Applications or Launchpad). Next open Terminal and type the following:
```
docker run hello-world
```
you should see something like this if you were successful:

```
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
1b930d010525: Pull complete 
Digest: sha256:451ce787d12369c5df2a32c85e5a03d52cbcef6eb3586dd03075f3034f10adcd
Status: Downloaded newer image for hello-world:latest

Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/
```

## Attributions
* [Harvard CS109](http://cs109.github.io/2015/)
* [UBC STAT 545](http://stat545.com/packages01_system-prep.html#mac-os-system-prep) licensed under the [CC BY-NC 3.0](https://creativecommons.org/licenses/by-nc/3.0/legalcode).
* [Software Carpentry](https://software-carpentry.org/)
