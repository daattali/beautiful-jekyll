---
layout: page
title: Windows
subtitle: MDS software stack install instructions for Windows
---

These instructions will walk you through installing the required Data Science software stack for the UBC Master of Data Science program. Before starting, ensure that your laptop meets our program requirements:
 - runs one of the following operating systems: macOS 10.15.X (Catalina), Ubuntu 20.04, Windows 10 Professional, Enterprise or Education; version 2004. *Note that Windows 10 Home is not sufficient as not all the software required for the program can be installed on that OS. Also note that when installing Ubuntu, checking the box "Install third party..." will (among other things) install proprietary drivers, which can be helpful for wifi and graphics cards.*
- can connect to networks via a wireless connection
- has at least 50 GB disk space available
- has at least 8 GB of RAM
- uses a 64-bit CPU
- is 4 years old or newer at the start of the program
- uses English as the default language

 **Students' whose laptops do not meet the requirements specified above will not be able to receive technical assistance from the MDS team in troubleshooting installation issues.**

## Table of Contents

- [Google Chrome browser](#google-chrome-browser)
- [LastPass password manager](#lastpass-password-manager)
- [Slack](#slack)
- [Visual Studio code](#visual-studio-code)
- [GitHub](#github)
- [Git and Bash](#git-and-bash)
- [Python, Conda, and JupyterLab](#python-conda-and-jupyterlab)
- [R, IRkernel, Rtools, and RStudio](#r-irkernel-rtools-and-rstudio)
- [LaTeX](#latex)
- [Make](#make)
- [PostgreSQL](#postgresql)
- [Docker](#docker)

## Google Chrome browser

In MDS we will be using many tools that work most reliably on the Google Chrome browser (including our online quiz software). To install it, go to [https://www.google.com/chrome/](https://www.google.com/chrome/), click on "Download Chrome", download it to your computer and click on the downloaded file to install it.

## LastPass password manager

In MDS we share credentials via the password manager LastPass. This can also be useful for helping keep secure passwords and efficient authentication. Sign up for a free LastPass account here: [https://lastpass.com/create-account.php](https://lastpass.com/create-account.php). We also recommend installing the LastPass Chrome Extension available here: [https://chrome.google.com/webstore/detail/lastpass-free-password-ma/hdokiejnpimakedhajhdlcegeplioahd](https://chrome.google.com/webstore/detail/lastpass-free-password-ma/hdokiejnpimakedhajhdlcegeplioahd)

## Slack

For MDS program announcements, course forums, and correspondence we use the communication tool Slack. Slack can be accessed via the web browser, but we recommend using the Slack app, which can be installed via downloadable file from the slack website [https://slack.com/intl/en-ca/downloads/windows](https://slack.com/intl/en-ca/downloads/windows).


## Visual Studio Code

The open-source text editor Visual Studio Code (VS Code) is both a powerful text editor and a full-blown Python ADE, which we will use for more complex analysis. Go to [https://code.visualstudio.com/download](https://code.visualstudio.com/download) and download the windows version of VS Code. After the download has finished, run the installer and accept the default configuration for all pages except for the following:
    - On the **Select Additional Tasks** check all four boxes under "Other"
        - "Add 'Open with Code' action to Windows file context menu"
        - "Add 'Open with Code' action to Windows directory context menu"
        - "Register Code as an editor for supported file types"
        - "Add to PATH" (this should selected by default).

![](/resources_pages/imgs/vs_code.png)

## GitHub

In MDS we will use the publicly available [GitHub.com](https://github.com/) as well as an Enterprise version of GitHub hosted here at UBC, [GitHub.ubc.ca](https://github.ubc.ca). Please follow the set-up instructions for both below.

### GitHub.com

Sign up for a free account at [GitHub.com](https://github.com/) if you don't have one already.

### GitHub.ubc.ca

To add you to the MDS organization on [Github.ubc.ca](https://github.ubc.ca) we need you to login to [Github.ubc.ca](https://github.ubc.ca) using your CWL credentials.

This step is required for
- being able to store your work
- all homework submission and grading
- working collaboratively

## Git and Bash

These two programs are in the same section since they are packaged together in the same installer.
Briefly, we will be using the Bash shell to interact with our computers via a command line interface.
We will be using the command line version of Git as well as Git through RStudio and Jupyter lab. Some of the Git commands we will use are only available since Git 2.23, so if you're Git is older than this version, we ask you to update it.

Go to <https://git-scm.com/download/win> and download the windows version of git. After the download has finished, run the installer and accept the default configuration for all pages except for the following:
  - On the **Choosing the default editor used by Git** page, select "Use Visual Studio Code as Git's default editor" from the drop-down menu'

After installation, test if you were successful by opening the Git Bash program. Below is a picture of the Git Bash icon on the Desktop and an opened instance of the Git Bash terminal (we will often refer to this as just "the terminal"):

![](/resources_pages/imgs/gitbash.png)

In the terminal, type the following to check which version of Bash you just installed:

```
bash --version
```

The output should look similar to this:

```
GNU bash, version 4.4.23(1)-release (x86_64-pc-sys)
Copyright (C) 2019 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

This is free software; you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

Let's also check which version of git was installed:

```
git --version
```

```
git version 2.28.0.windows.1
```

You can launch many windows programs from the Bash terminal, e.g. to launch VS Code that we installed previously, you would type in `code`, let's use this to check the version of vscode that we installed:

```
code --version
```

```
1.47.3
91899dcef7b8110878ea59626991a18c8a6a1b3e
x64
```

## Python, Conda, and JupyterLab

### Python and Conda

We will be using Python for a large part of the program, and `conda` as our Python package manager. To install Python and the `conda` package manager, we will use the [Miniconda platform (read more here)](https://docs.conda.io/en/latest/miniconda.html), for which the [Python 3.7 64-bit version can be downloaded here](https://repo.anaconda.com/miniconda/Miniconda3-latest-Windows-x86_64.exe). After the download has finished, run the installer and accept the default configuration for all pages.

> Do *not* add miniconda to PATH. We will set this up later.

After installation, open the Start Menu and search for the program called "Anaconda Prompt (miniconda3)". When this open you will see a prompt similar to `(base) C:\Users\your_name`. Type the following to check that your Python installation is working:

```
python --version
```

which should return something like this:

```
Python 3.8.3
```

> If instead you see `Python 2.7.X` you installed the wrong version. Follow [these instructions](https://docs.anaconda.com/anaconda/install/uninstall) to delete this installation and try the installation again, selecting **Python 3.7**.

### Integrating Python with the Git Bash terminal

To avoid having to open the separate Anaconda Prompt every time we want to use Python, we can make it available from the (Git Bash) terminal, which is what we will be using most of the time. To set this up, open the "Anaconda Prompt (miniconda3)" again and type:

```
conda init bash
```

You will see that this modified a few configuration files, which makes `conda` visible to the terminal. Close all open terminal windows and launch a new one, you should now see that the prompt string has changed to include the word `(base)` as in the screenshot below:

![](/resources_pages/imgs/add-conda-env-to-ps1.png)

If you type

```
python --version
```

you should now see the same output as above:

```
Python 3.8.3
```

And if you type

```
conda --version
```

you should see something like this

```
conda 4.8.3
```

> Note that if you want to run Python directly from the command line on Windows, you need to append the `-i` flag, so the full command would be `python -i`. Running just `python` will freeze the Git Bash terminal.

One annoyance with our current terminal setup is that the word `(base)` is not on the same row as the rest of the prompt string (the part with `your_name@your_computer`. To fix this we can edit the `.bash_profile` configuration file to indicate that we do not want a newline at the beginning of the prompt string. Open up the configuration file using VS Code by typing the following command into a terminal:

```
code "/c/Program Files/Git/etc/profile.d/git-prompt.sh"
```

Delete the line that reads the following (it should be line 13):

```
PS1="$PS1"'\n'       # new line
```

Click to save the file,
when VS Code prompts you that the saving failed,
click "Retry as Admin" and then "Yes".
That's it!
Now if you launch a new terminal instance,
you will see `(base)` on the same line as the rest of the prompt string as in the screenshot below.

![](/resources_pages/imgs/remove-newline-from-ps1.png)

### Essential Python packages

`conda` installs Python packages from different online repositories which are called "channels".
A package needs to go through thorough testing before it is included in the default channel,
which is good for stability,
but also means that new versions will be delayed and fewer packages are available overall.
There is a community-driven effort called the [conda-forge (read more here)](https://conda-forge.org/),
which provides more up to date packages
To enable us to access the most up to date version of the Python packages we are going to use,
we will add the more up to date  channel,
To add the conda-forge channel by typing the following in the terminal:

```
conda config --add channels conda-forge

```

To install packages individually, we can now use the following command: `conda install <package-name>`. Let's install the key packages needed for the start of the MDS program:

```
conda install \
 jupyterlab=2.* \
 numpy=1.* \
 pandas=1.* \
 flake8=3.* \
 black=19.*
```

`conda` will show you the packages that will be downloaded,
and you can press enter to proceed with the installation.
If you want to answer `yes` by default and skip this confirmation step,
you can replace `conda install` with `conda install -y`.

> Note: we will use many more packages than those listed above across the MDS program, however we will manage these using virtual environments (which you will learn about in DSCI 521: Platforms for Data Science).

### JupyterLab setup

We will be using the Jupytext Python package and the JupyterLab git extension to facilitate using Jupyter notebooks with Git & GitHub. Install them via the following commands:

```
conda install nodejs=10.*
pip install --upgrade jupyterlab-git
conda install jupytext=1.*
jupyter lab build
```

To test that your JupyerLab installation is functional, you can type `jupyter lab` into a terminal, which should open a new tab in your default browser with the JupyterLab interface.

![](/resources_pages/imgs/jupyter_lab.PNG)

## R, IRkernel, Rtools, and RStudio

R is another programming language that we will be using a lot in the MDS program. We will use R both in Jupyter notebooks and in RStudio.

### R

Go to <https://cran.r-project.org/bin/windows/base/> and download the latest version of R for Windows (4.0.2 at the time of writing). Open the file and follow the installer instructions accepting the default configuration.

After the installation is complete, we will add the R executables to the PATH variable in terminal so that your can use it without typing the full path to R each time. Open a terminal and type:

```
code ~/.bash_profile
```

Append the following line to the file

```
# Add R and Rscript to PATH
export PATH="/c/Program Files/R/R-4.0.2/bin/x64":$PATH
```

> Note: Although it is possible to install R through Anaconda, we highly recommend not doing so. In case you have already installed R using Anaconda you can remove it by executing `conda uninstall r-base`.

### RStudio

Download the Windows version of RStudio from <https://www.rstudio.com/products/rstudio/download/preview>. Open the file and follow the installer instructions.

To see if you were successful, try opening RStudio by clicking on its icon. It should open and looks something like this picture below:

![](/resources_pages/imgs/RStudio.png)

By default, RStudio installs packages to `C:/Users/your_username/Documents/R/win-library/4.0`, but when it is run directly from the terminal it instead uses  `C:/Users/your_username/R/win-library/4.0`. To make sure that R from terminal uses the same package directory as R studio, we will edit `~/.Rprofile` by typing:

```
code ~/.Rprofile
```

And adding the following

```
# Make R from terminal use the same package directory as RStudio
.libPaths(c(paste("C:/Users/", Sys.getenv("USERNAME"), "/Documents/R/win-library/4.0" , sep=''), .libPaths()))
```

### Essential R packages

Next, install the key R packages needed for the start of MDS program,
by typing the following into the R terminal in RStudio:

```
install.packages(c('tidyverse', 'blogdown', 'xaringan', 'renv'))
```

If you get a prompt asking if you want to install packages that need compilation from sources, click "Yes".

> Note: we will use many more packages than those listed above across the MDS program, however we will manage these using the `renv` package manager (which you will learn about in DSCI 521: Platforms for Data Science).

### Rtools

Windows users will also need to install Rtools, which will allow you to use external libraries. Go to <http://cran.r-project.org/bin/windows/Rtools/> and download the latest version (e.g., Rtools40.exe). After the download has finished, run the installer with the default configuration. After the installation has completed, follow the steps on the Rtools page under the heading "Putting Rtools on the PATH".

To use Rtools from R in terminal, edit `~/.Rprofile`:

```
code ~/.Rprofile
```

and append the following:

```
# Enable Rtools from R in the terminal
Sys.setenv(PATH = paste("C:/rtools40/usr/bin/", Sys.getenv("PATH"), sep=";"))
```

### IR kernel

The `IRkernel` package is needed to make R work in Jupyter notebooks. To enable this kernel in the notebooks, open R *from a terminal* and run the setup via the following two commands:

```
install.packages('IRkernel')
IRkernel::installspec()
```

When asked to select a mirror, pick one at a location close to where you live for faster downloads.

> Note that you cannot use RStudio for this step because it will not be able to find the jupyter installation. R from terminal will since the correct PATH for jupyter is set when the terminal is launched.

To see if you were successful, try running Jupyter Lab and seeing if you have working R kernel. To launch the Jupyter Lab type the following in the terminal:

```
jupyter lab
```

A browser should have launched and you should see a page that looks like the screenshot below. Now click on "R" notebook (circled in red on the screenshot below) to launch an Jupyter Lab with an R kernel.

![](/resources_pages/imgs/jupyter_lab_r_kernel.png)

Sometimes a kernel loads, but doesn't work as expected. To test whether your installation was done correctly now type `library(tidyverse)` in the code cell and click on the run button to run the cell. If your R kernel works you should see something like the image below:

![](/resources_pages/imgs/jupyter_lab_r_kernel2.png)

## LaTeX

We will install the lightest possible version of LaTeX and it's necessary packages as possible so that we can render Jupyter notebooks and R Markdown documents to html and PDF. If you have previously installed LaTeX, please uninstall it before proceeding with these instructions.

First, open RStudio and run the following commands to install the `tinytex` package and setup `tinytex`:

```
install.packages('tinytex')
tinytex::install_tinytex()
```

Note that you might see two error messages regarding lua during the installation, you can safely ignore these, the installation will complete successfully after clicking "OK".


You can check that the installation is working by typing the following in a terminal to ask for the version of latex:

```
latex --version
```

You should see something like this if you were successful:

```
pdfTeX 3.14159265-2.6-1.40.21 (TeX Live 2020)
kpathsea version 6.3.2
Copyright 2020 Han The Thanh (pdfTeX) et al.
There is NO warranty.  Redistribution of this software is
covered by the terms of both the pdfTeX copyright and
the Lesser GNU General Public License.
For more information about these matters, see the file
named COPYING and the pdfTeX source.
Primary author of pdfTeX: Han The Thanh (pdfTeX) et al.
Compiled with libpng 1.6.37; using libpng 1.6.37
Compiled with zlib 1.2.11; using zlib 1.2.11
Compiled with xpdf version 4.02
```

The above is all we need to have LaTeX work with R Markdown documents, however for Jupyter we need to add several more packages. Before we do this, please sign out of Windows and back in again in order for the Git Bash terminal to be able to find the location of TinyTex.

When you sign back in,
install the additional LaTeX packages needed for Jupyter by pasting the following into the new terminal instance and press enter:
by pasting the following:

```
tlmgr.bat install eurosym \
  adjustbox \
  caption \
  collectbox \
  enumitem \
  environ \
  fp \
  jknapltx \
  ms \
  parskip \
  pgf \
  rsfs \
  tcolorbox \
  titling \
  trimspaces \
  ucs \
  ulem \
  upquote
```

To test that your latex installation is working with jupyter notebooks,
launch `jupyter lab` from a terminal and open either a new notebook
or the same one you used to test IRkernel above.
Go to `File -> Export notebook as... -> Export Notebook to PDF`.
If the PDF file is created,
your LaTeX environment is set up correctly.

> Note if you see an error that says "Undefined control sequence", you need to edit a configuration file for Jupyter's PDF export. Open a terminal and paste `code "/c/Users/${USERNAME}/miniconda3/Lib/site-packages/nbconvert/exporters/pdf.py"`. On line 66, it says `writer = Instance("nbconvert.writers.FilesWriter", args=(), kw={'build_directory': '.'})`, replace this line with the following line `writer = Instance("nbconvert.writers.FilesWriter", args=(), kw={'build_directory': ''})` (removing the period close to the end). Now try to generate a PDF from JupyterLab again.

## Make
We will be using Make to automate our analysis scripts. More on this later!

Go to https://github.com/gnu-mcu-eclipse/windows-build-tools/releases and download `gnu-mcu-eclipse-windows-build-tools-2.12-20190422-1053-win64.zip`. 

Unpack the archive and copy it into the %userprofile%\AppData\Roaming\GNU MCU Eclipse (for example C:\Users\\`user_name`\AppData\Roaming\GNU MCU Eclipse) folder. 

Next, like you did when installing [Rscript](https://github.com/UBC-MDS/UBC-MDS.github.io/blob/master/resources_pages/install_ds_stack_windows.md#rscript), you need to add the folder where `make.exe` is located to the _PATH_ variable. The `make.exe` file is located in C:\Users\\`user_name`\AppData\Roaming\GNU MCU Eclipse\Build Tools\2.12-20190422-1053\bin.

After installation, restart Powershell and type the following to ask for the version:

```
make --version
```

you should see something like this if you were successful:

```
GNU Make 4.2.1
Built for i686-pc-msys
Copyright (C) 1988-2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

## Docker

You will use Docker to create reproducible, sharable and shippable computing environments for your analyses. For this you will need a Docker account. You can sign up for a free one [here](https://store.docker.com/signup?next=%2F%3Fref%3Dlogin).

After signing-up and signing into the Docker Store, go [here](https://store.docker.com/editions/community/docker-ce-desktop-windows) and click on the "Get Docker" button on the right hand side of the screen. Then follow the installation instructions on that screen.

After installation, restart Powershell and type the following to ask for the version:

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
