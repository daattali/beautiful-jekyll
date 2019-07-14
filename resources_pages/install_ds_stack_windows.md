---
layout: page
title: Windows
subtitle: MDS software stack install instructions for Windows
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

Go to <https://git-scm.com/download/win> and a download should automatically start (if not, follow the instructions on that page). After the download has finished, run the installer selecting the following options:
  - On the **Select Components** page, check "On the Desktop" under "Additional icons"
  - On the **Choosing the default editor used by Git** page, select "Use the Nano editor by default" from the drop-down menu
  - For all other pages, use the default options

After installation, test if you were successful by opening the Git Bash program (if you followed the install instructions above, you should now have an icon on your Desktop). Below is a picture of the Git Bash icon on the Desktop and an opened instance of the Git Bash program:

![](/resources_pages/imgs/gitbash.png)

## Python

We will be using Python for a large part of the program, including many popular 3rd party Python libraries for scientific computing. [__Anaconda__](https://www.anaconda.com) is an easy-to-install distribution of Python and most of these libraries (as well as Jupyter notebooks, one of the developing environments we will be using). We __strongly recommend__ that you use Anaconda for this program. If you insist on using your own Python setup instead of Anaconda, we will not be able to provide technical support with installation or later issues. For this program we are using __Python 3__ , not __Python 2__, so please choose the Anaconda versions that include Python 3.7

Head to <https://www.anaconda.com/download/#windows> and download the Anaconda version for Windows with **Python 3.7**. After the download has finished, run the installer selecting the following options:
  - On the **Advanced Installation Options** page, check both boxes (see image below)
  - For all other pages, use the default options

![](/resources_pages/imgs/anaconda_windows.png)

After installation, open Command Prompt (select the Start button, type cmd, and click Command Prompt from the list) and type the following:
```
python
```
you should see something like this (in the first line) if you were successful:

```
Python 3.7.3 (default, Mar 27 2019, 17:13:21) [MSC v.1915 64 bit (AMD64)] :: Anaconda, Inc. on win32
```

If instead you see `Python 2.7.X` you installed the wrong version. Follow [these instructions](https://docs.anaconda.com/anaconda/install/uninstall) to delete this installation and try the installation again, selecting **Python 3.7**.

To see if Jupyter was successfully installed in the Anaconda Python distribution type the following in Command Prompt:

```
jupyter lab
```

A browser should have launched and you should see a page that looks like the screenshot below. 

![](/resources_pages/imgs/jupyter_lab.PNG)


If you already have installed Anaconda at some point in the past, we recommend that you update to the latest Anaconda version by updating conda, then Anaconda in the Command Prompt follows:
```
conda update conda
conda update anaconda
```

## R, IRkernel and RStudio
We will be using R, another programming language, a lot in the program. We will use R both in Jupyter notebooks and in RStudio. To have R work in Jupyter notebooks we will also have to install the IR kernel.

#### R
Go to <https://cran.r-project.org/bin/windows/base/> and download the latest version of R for Windows (Should look something like this: Download R 3.6.1 for Windows). Open the file and follow the installer instructions.


#### RStudio
Chose and download the Windows version of RStudio from <https://www.rstudio.com/products/rstudio/download/#download>. Open the file and follow the installer instructions.

To see if you were successful, try opening RStudio by clicking on its icon. It should open and looks something like this picture below:

![](/resources_pages/imgs/RStudio.png)

#### Rtools
Windows users will also need to install Rtools, which will allow you to use external libraries. Go to http://cran.r-project.org/bin/windows/Rtools/ and download the latest version (e.g., Rtools35.exe). After the download has finished, run the installer selecting the following options:
  - On the **Select Additional Tasks** page, check the Add rtools to system PATH option (see image below)
  - For all other pages, use the default options

![](/resources_pages/imgs/Rtools.png)

To see if you were successful, open RStudio and type ```install.packages("xtable", type="source")``` into the console panel. If this install command runs successfully, Rtools should be installed!


#### IR kernel

Open RStudio and type the following commands into the console panel:

```
install.packages(c('repr', 'IRdisplay', 'evaluate', 'crayon', 'pbdZMQ', 'devtools', 'uuid', 'digest'))
devtools::install_github('IRkernel/IRkernel')
IRkernel::installspec()
```

To see if you were successful, try running Jupyter Notebook and seeing if you have working R kernel. To launch the Jupyter type the following in the Windows Command prompt:

```
jupyter notebook
```

A browser should have launched and you should see a page that looks like the screenshot below. Now click on "New" and then "R" (circled in red on the screenshot below) to launch an Jupyter notebook with an R kernel.

![](/resources_pages/imgs/IR_kernel_1.png)

A notebook is using the R kernel if you see R in the right-hand side of the notebook (circled in red on the screenshot below).

![](/resources_pages/imgs/IR_kernel_2.png)

Sometimes a kernel loads, but doesn't work if installation was not done correctly. To test whether your installation was done correctly now type `(x <- 5)` in the code cell and click on the run button to run the cell. If your R kernel works you should see the number 5 printed below the cell.

![](/resources_pages/imgs/IR_kernel_3.png)

#### Rscript

To be able to call R scripts from the CMD or Git Bash you need to be able to execute the Rscript program from there. To make this possible you need to add the the file path of the directory/folder that houses the Rscript program (i.e., location where this program lives on your computer) to the Windows PATH system variable. You can modify the PATH system variable using System Utility in control panel on Windows. We outline below how to do this:

- Hit the windows key to get to the windows search bar and type: `edit environ`
- This should bring up a menu item that will take you to where you can edit the Environment Variables. It should look something like this:

![](/resources_pages/imgs/env1.png)
  
- Double click on the "Path" entry from the top box. This should bring you to a new window titled "Edit Enviroment Variables". 

- Here, click on an empty line and then click **Browse**. This will open a dialogue box within which you can navigate to the folder where Rscript is installed (usually `C:\Program Files\R\R-3.5.1\bin`) and click **OK**. Close all remaining windows by clicking **OK**.

![](/resources_pages/imgs/env2.png)

After following the instructions above, in Command Prompt type the following to ask for the version:
``` 
Rscript --version
```
you should see something like this if you were successful:
```
R scripting front-end version 3.5.1 (2018-07-02)
```

### Atom Text Editor

We need a text editor to be able to write complete applications. One is available through Jupyter, but sometimes it is helpful to have a standalone text editor, for this we will be using the open-source text editor Atom.

Got to https://flight-manual.atom.io/getting-started/sections/installing-atom/ and follow the installation instructions. 

To test that atom is installed and can be opened from the Command Prompt, in Command Prompt the following to ask for the version:

```
atom --version
```

you should see something like this if you were successful:
```
Atom    : 1.28.2
Electron: 2.0.5
Chrome  : 61.0.3163.100
Node    : 8.9.3
```

If `which atom ` command doesn't return anything then you need to do more work to install the `atom` and `apm` commands by adding the path to them via environmental variables as you did for [Rscript](#rscript) above. Usually atom is installed in `C:\Users\UserAppData\Local\atom`.



## LaTeX

Download the installer from [http://mirror.ctan.org/systems/texlive/tlnet/install-tl-windows.exe](http://mirror.ctan.org/systems/texlive/tlnet/install-tl-windows.exe). After downloading run the `install-tl-windows.exe` file and follow the installation instructions choosing the default options.

*note - if a screen appears titled "Windows protected your PC", click on "More info" link and the "Run anyway" button*

After installation, in Command Prompt type the following to ask for the version:

```
latex --version
```

you should see something like this if you were successful:

```
pdfTeX 3.14159265-2.6-1.40.19 (TeX Live 2018/W32TeX)
kpathsea version 6.3.0
Copyright 2018 Han The Thanh (pdfTeX) et al.
There is NO warranty.  Redistribution of this software is
covered by the terms of both the pdfTeX copyright and
the Lesser GNU General Public License.
For more information about these matters, see the file
named COPYING and the pdfTeX source.
Primary author of pdfTeX: Han The Thanh (pdfTeX) et al.
Compiled with libpng 1.6.34; using libpng 1.6.34
Compiled with zlib 1.2.11; using zlib 1.2.11
Compiled with xpdf version 4.00
```

## SQLite

- Got to https://www.sqlite.org/download.html and search for “Precompiled Binaries for Windows” Section. Download the zip file called sqlite-dll-win32-x86-xxxx.zip or sqlite-dll-win64-x64-xxxx.zip (depending upon your system configuration) as well as sqlite-tools-win32-x86-xxxx.zip 
- Create a folder in your `C` directory called `sqlite` and unzip both the files which you have downloaded. You should now see the following files there:
  ```
  sqldiff.exe
  sqlite3.def 
  sqlite3.dll
  sqlite3.exe
  sqlite3_analyzer.exe
  ```
Now add `C:\sqlite` to your PATH environmental variables as you did for [Rscript](#rscript) above. After you have done this open Command Prompt and type the following to open SQLite:

```
sqlite3
```

you should see something like this if it is installed:

```
SQLite version 3.24.0 2018-06-04 19:24:41
Enter ".help" for usage hints.
Connected to a transient in-memory database.
Use ".open FILENAME" to reopen on a persistent database.
sqlite>
```

Type `.quit` to exit.

*note - if you want to use Git Bash to run SQLite3 then you need to type `winpty sqlite3` instead of `sqlite3`*

## Make
We will be using Make to automate our analysis scripts. More on this later!

Go to https://github.com/gnu-mcu-eclipse/windows-build-tools/releases and download `
gnu-mcu-eclipse-build-tools-2.10-20180103-1919-win64.zip`. 

Unpack the archive and copy it into the %userprofile%\AppData\Roaming\GNU MCU Eclipse (for example C:\Users\User\AppData\Roaming\GNU MCU Eclipse) folder.

After installation, in Command Prompt type the following to ask for the version:

```
make --version
```

you should see something like this if you were successful:

```
C:\Users\ilg\AppData\Roaming\GNU MCU Eclipse\Build Tools\2.10-20180103-1919\bin>make --version
GNU Make 4.1
Built for i686-w64-mingw32
Copyright (C) 1988-2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

## Docker

You will use Docker to create reproducible, sharable and shippable computing environments for your analyses. For this you will need a Docker account. You can sign up for a free one here: https://store.docker.com/signup?next=%2F%3Fref%3Dlogin

After signing-up and signing into the Docker Store, go here: https://store.docker.com/editions/community/docker-ce-desktop-windows and click on the "Get Docker" button on the right hand side of the screen. Then follow the installation instructions on that screen.

After installation, in Command Prompt type the following to ask for the version:

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
* [Oracle - How do I set or change the PATH system variable?](https://www.java.com/en/download/help/path.xml)
* [Numerical Methods - Getting started](https://clouds.eos.ubc.ca/~phil/numeric/python.html)
