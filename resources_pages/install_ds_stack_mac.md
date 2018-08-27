---
layout: page
title: macOS
subtitle: MDS software stack install instructions for macOS
---
These instructions will walk you through installing the required Data Science software stack for the UBC Master of Data Science program. Before starting, ensure that your laptop meets our program requirements:
- runs one of the following operating systems: macOS Yosemite 10.10.3 or later, Ubuntu 14.04 or later, Windows 10 Professional, Enterprise or Education (1511 November update, Build 10586 or later).
- can connect to networks via a wireless connection (and preferably also a wired connection)
- has at least 40 GB disk space available
- has at least 4 GB of RAM
- uses a 64-bit CPU
- is 4 years old or newer at the start of the program
- uses English as the default language

## Table of Contents
- [GitHub](#github)
- [Git](#git)
- [Python and Jupyter](#python)
- [R, IRkernel and RStudio](#r-ir-kernel-and-rstudio)
- [Atom Text Editor](#atom-text-editor)
- [LaTeX](#latex)
- [SQLite](#sqlite)
- [Make](#make)
- [Docker](#docker)

## GitHub

In MDS we will use [GitHub.com](https://github.com/) as well as an Enterprise version of GitHub hosted here at UBC, [GitHub.ubc.ca](https://github.ubc.ca). Please follow the set-up instructions for both below.

#### GitHub.com
If you do not yet have one, sign up for a free account at https://github.com/ .

#### GitHub.ubc.ca
For us to add you to the MDS organization on [Github.ubc.ca](https://github.ubc.ca) we need you to login using your CWL:

visit [Github.ubc.ca](https://github.ubc.ca) to do this.

This step is required for
- being able to store your work
- all homework submission and grading
- working collaboratively




## Git

We will be using the command line version of Git as well as Git through RStudio. 

Open Terminal ([how to video](https://www.youtube.com/watch?v=zw7Nd67_aFw)) and type the following command:
```
xcode-select --install
```

This will install git and many other very useful applications as well (including Make).

After installation, in terminal type the following to ask for the version:
```
git --version
```
you should see something like this if you were successful:

```
git version 2.17.0
```

If you run into trouble, please see that Install Git > Mac OS section from [Happy Git and GitHub for the useR](http://happygitwithr.com/install-git.html#mac-os) for additional help or strategies for Git installation.

## Python

We will be using Python for a large part of the program, including many popular 3rd party Python libraries for scientific computing. [__Anaconda__](https://www.anaconda.com/download/#macos) is an easy-to-install distribution of Python and most of these libraries (as well as Jupyter notebooks, one of the developing environments we will be using). We __require__ that you use Anaconda for this program. If you insist on using your own Python setup instead of Anaconda, we will not be able to provide technical support with installation or later issues. For this program we are using __Python 3__ , not __Python 2__, so please choose the Anaconda versions that include Python 3.6

Head to https://www.anaconda.com/download/#macos and download the Anaconda version for Mac OS with **Python 3.6**. Follow the instructions on that page to run the installer.

After installation, in terminal type the following to ask for the version:
```
python --version
```
you should see something like this if you were successful:

```
Python 3.6.5 :: Anaconda custom (64-bit)
```

If instead you see `Python 2.7.X :: Anaconda custom (64-bit)` you installed the wrong version. Follow [these instructions](https://docs.anaconda.com/anaconda/install/uninstall) to delete this installation and try the installation again, selecting **Python 3.6**.

To see if Jupyter was successfully installed in the Anaconda Python distribution type the following in the terminal:

```
jupyter notebook
```

A browser should have launched and you should see a page that looks like the screenshot below. 

![](/resources_pages/imgs/jupyter.png)


If you already have installed Anaconda at some point in the past, we recommend that you update to the latest Anaconda version by updating conda, then Anaconda in terminal as follows:
```
    conda update conda
    conda update anaconda
```

## R, IRkernel and RStudio
We will be using R, another programming language, a lot in the program. We will use R both in Jupyter notebooks and in RStudio. To have R work in Jupyter notebooks we will also have to install the IR kernel.

#### R
Go to https://cran.r-project.org/bin/macosx/ and download the latest version of R for Mac (Should look something like this: R-3.5.1.pkg). Open the file and follow the installer instructions.

After installation, in terminal type the following to ask for the version:
```
R --version
```

you should see something like this if you were successful:
```
R version 3.5.0 (2018-04-23) -- "Joy in Playing"
Copyright (C) 2018 The R Foundation for Statistical Computing
Platform: x86_64-apple-darwin15.6.0 (64-bit)

R is free software and comes with ABSOLUTELY NO WARRANTY.
You are welcome to redistribute it under the terms of the
GNU General Public License versions 2 or 3.
For more information about these matters see
http://www.gnu.org/licenses/.
```

#### RStudio
Chose and download the Mac version of RStudio from https://www.rstudio.com/products/rstudio/download/#download. Open the file and follow the installer instructions.

To see if you were successful, try opening RStudio by clicking on its icon (from Finder, Applications or Launchpad). It should open and looks something like this picture below:

![](/resources_pages/imgs/RStudio.png)

#### IR kernel

Open RStudio and type the following commands into the Console panel:

```
install.packages(c('repr', 'IRdisplay', 'evaluate', 'crayon', 'pbdZMQ', 'devtools', 'uuid', 'digest'))
devtools::install_github('IRkernel/IRkernel')
```

Next, open terminal and type the following:

```
R -e "IRkernel::installspec()"
```

To see if you were successful, try running Jupyter Notebook and seeing if you have working R kernel. To launch the Jupyter type the following in the terminal:

```
jupyter notebook
```

A browser should have launched and you should see a page that looks like the screenshot below. Now click on "New" and then "R" (circled in red on the screenshot below) to launch an Jupyter notebook with an R kernel.

![](/resources_pages/imgs/IR_kernel_1.png)

A notebook is using the R kernel if you see R in the right-hand side of the notebook (circled in red on the screenshot below).

![](/resources_pages/imgs/IR_kernel_2.png)

Sometimes a kernel loads, but doesn't work if installation was not done correctly. To test whether your installation was done correctly now type `(x <- 5)` in the code cell and click on the run button to run the cell. If your R kernel works you should see the number 5 printed below the cell.

![](/resources_pages/imgs/IR_kernel_3.png)


## Atom Text Editor
We need a text editor to be able to write complete applications. One is available through Jupyter, but sometimes it is helpful to have a standalone text editor, for this we will be using the open-source text editor Atom.

Got to https://flight-manual.atom.io/getting-started/sections/installing-atom/ and follow the installation instructions. 

To test that atom is installed and can be opened from the command line/terminal, in terminal type the following to ask for the version:

```
which atom
```

you should see something like this if you were successful:
```
/usr/local/bin/atom
```

If `which atom ` command doesn't return anything then you need to do more work to install the `atom` and `apm` commands. Open Atom by clicking on its icon (from Finder, Applications or Launchpad) and then type Cmd+Shift+P to get the "Command Palette" (a free form text prompt - see the image below) and in that type: "Window: Install Shell Commands". You will be prompted for an administrator password.

![](/resources_pages/imgs/atom_cp.png)

## LaTeX

LaTeX allows to use syntax to write nicely formatted mathematical expressions and equations. For this program we only need the smaller BasicTeX package.

1. Download the BasicTeX package from [here](http://tug.org/cgi-bin/mactex-download/BasicTeX.pkg ).
2. Open the ```.pkg``` file and run the installer with default options.
3. BasicTeX has a few missing files we'll need. To install these files, open terminal and run:
```
$ sudo tlmgr update --self
$ sudo tlmgr install framed
$ sudo tlmgr install titling
```

After installation, in terminal type the following to ask for the version:
```
latex --version
```
you should see something like this if you were successful:

```
Primary author of pdfTeX: Han The Thanh (pdfTeX) et al.
Compiled with libpng 1.6.21; using libpng 1.6.21
Compiled with zlib 1.2.8; using zlib 1.2.8
Compiled with xpdf version 3.04
```

## SQLite

SQLite should already be installed on your Mac. To be sure, in terminal type the following to open SQLite:

```
sqlite3
```

you should see something like this if it is installed:
```
SQLite version 3.13.0 2016-05-18 10:57:30
Enter ".help" for usage hints.
Connected to a transient in-memory database.
Use ".open FILENAME" to reopen on a persistent database.
sqlite>
```

Type `.quit` to exit.

If for some reason SQLite is not already installed, follow the instructions [here](http://www.tutorialspoint.com/sqlite/sqlite_installation.htm) under the "Install SQLite on Mac OS X" header


## Make
We will be using Make to automate our analysis scripts. More on this later! You should have this installed if you ran the command ```xcode-select --install``` from the [Git installation instructions](#git). If you didn't yet install Git, do this now!

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

After installation, in terminal type the following to ask for the version:
```
docker run hello-world
```
you should see something like this if you were successful:

```
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
c04b14da8d14: Pull complete
Digest: sha256:0256e8a36e2070f7bf2d0b0763dbabdd67798512411de4cdcf9431a1feb60fd9
Status: Downloaded newer image for hello-world:latest

Hello from Docker!
```

## Attributions
* [Harvard CS109](http://cs109.github.io/2015/)
* [UBC STAT 545](http://stat545.com/packages01_system-prep.html#mac-os-system-prep) licensed under the [CC BY-NC 3.0](https://creativecommons.org/licenses/by-nc/3.0/legalcode).
* [Software Carpentry](https://software-carpentry.org/)
