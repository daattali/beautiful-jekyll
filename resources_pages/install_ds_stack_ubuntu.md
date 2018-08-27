---
layout: page
title: Ubuntu
subtitle: MDS software stack install instructions for Ubuntu
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

Open Terminal and type the following command:
```
sudo apt-get install git
```

After installation, in terminal type the following to ask for the version:
```
git --version
```
you should see something like this if you were successful:

```
git version 2.17.0
```

## Python

We will be using Python for a large part of the program, including many popular 3rd party Python libraries for scientific computing. [__Anaconda__](https://www.anaconda.com/download/#macos) is an easy-to-install distribution of Python and most of these libraries (as well as Jupyter notebooks, one of the developing environments we will be using). We __require__ that you use Anaconda for this program. If you insist on using your own Python setup instead of Anaconda, we will not be able to provide technical support with installation or later issues. For this program we are using __Python 3__ , not __Python 2__, so please choose the Anaconda versions that include Python 3.6

Head to https://www.anaconda.com/download/#linux and download the Anaconda version for Linux with **Python 3.6**. Follow the instructions on that page to run the installer.

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

Open /etc/apt/sources.list and add the following line to the end of the file (choose the correct one for your version of Ubuntu):
  - for Ubuntu 17.10.1 (Artful Aardvark) add: `deb https://cloud.r-project.org/bin/linux/ubuntu artful/`
  - for Ubuntu 16.04.4 (Xenial Xerus) add: `deb https://cloud.r-project.org/bin/linux/ubuntu xenial/`
  - for Ubuntu 14.04.5 (Trusty Tahr) add: `deb https://cloud.r-project.org/bin/linux/ubuntu trusty/`

Next, add the key ID for the CRAN network:
```
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys E084DAB9
```

Then, update the repository:
```
sudo apt-get update
 ```

Then, install the R binaries:
```
sudo apt-get install r-base
 ```

Finally, install the r-base-dev package:
```
sudo apt-get install r-base-dev
```

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
Chose and download the appropriate Ubuntu version of RStudio from https://www.rstudio.com/products/rstudio/download/#download. Open the file and follow the installer instructions.

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

### Atom Installation

Atom Text Editor
We need a text editor to be able to write complete applications. One is available through Jupyter, but sometimes it is helpful to have a standalone text editor, for this we will be using the open-source text editor Atom.

Got to https://flight-manual.atom.io/getting-started/sections/installing-atom/#platform-linux and follow the installation instructions. 

To test that atom is installed and can be opened from the command line/terminal, in terminal type the following to ask for the version:

```
which atom
```

you should see something like this if you were successful:
```
/usr/local/bin/atom
```

## LaTeX
Open Terminal and type the following command:
```
sudo apt-get install texlive
```

After installation, in terminal type the following to ask for the version:
```
latex --version
```
you should see something like this if you were successful:

```
pdfTeX 3.14159265-2.6-1.40.18 (TeX Live 2017/Debian)
kpathsea version 6.2.3
Copyright 2017 Han The Thanh (pdfTeX) et al.
There is NO warranty.  Redistribution of this software is
covered by the terms of both the pdfTeX copyright and
the Lesser GNU General Public License.
For more information about these matters, see the file
named COPYING and the pdfTeX source.
Primary author of pdfTeX: Han The Thanh (pdfTeX) et al.
Compiled with libpng 1.6.34; using libpng 1.6.34
Compiled with zlib 1.2.8; using zlib 1.2.8
Compiled with poppler version 0.62.0
```

## SQLite

Open Terminal and type the following command:
```
sudo apt-get update
sudo apt-get install sqlite3 libsqlite3-dev
```

To test that it was successfully installed, in terminal type the following to open SQLite:

```
sqlite3
```

you should see something like this if it is installed:
```
SQLite version 3.22.0 2018-01-22 18:45:57
Enter ".help" for usage hints.
Connected to a transient in-memory database.
Use ".open FILENAME" to reopen on a persistent database.
sqlite> 
```
Type `.quit` to exit.

If you run into trouble installing SQLite try doing a software update first: 
```
sudo apt-get update && sudo apt-get upgrade
```


## Make

We will be using Make to automate our analysis scripts. More on this later! 

To install Make, open Terminal and type the following command:
```
sudo apt-get install build-essential
```

After installation, in terminal type the following to ask for the version:
```
make --version
```
you should see something like this if you were successful:

```
GNU Make 4.1
Built for x86_64-pc-linux-gnu
Copyright (C) 1988-2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

This program built for i386-apple-darwin11.3.0
```

## Docker

You will use Docker to create reproducible, sharable and shippable computing environments for your analyses. For this you will need a Docker account. You can sign up for a free one here: https://store.docker.com/signup?next=%2F%3Fref%3Dlogin

After signing-up, you also need to install Docker **CE** for Ubuntu. Follow the installation instructions here: https://docs.docker.com/install/linux/docker-ce/ubuntu/

After installation, in terminal type the following to ask for the version:
```
sudo docker run hello-world
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
