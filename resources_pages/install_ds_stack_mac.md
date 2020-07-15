---
layout: page
title: macOS
subtitle: MDS software stack install instructions for macOS
---
These instructions will walk you through installing the required Data Science software stack for the UBC Master of Data Science program. Before starting, ensure that your laptop meets our program requirements:

- runs one of the following operating systems: macOS 10.15.X (Catalina) or later, Ubuntu 20.04 or later, Windows 10 Professional, Enterprise or Education; version 2004 or later. Please note that Windows 10 Home is not sufficient as not all the software required for the program can be installed on that OS.
- can connect to networks via a wireless connection
- has at least 50 GB disk space available
- has at least 8 GB of RAM
- uses a 64-bit CPU
- is 4 years old or newer at the start of the program
- uses English as the default language
- student user has full administrative access to the computer

**Students' whose laptops do not meet the requirements specified above will not be able to receive techinical assistance from the MDS team in troubleshooting installation issues.**

## Table of Contents
- [Google Chrome browser](#chrome-browswer)
- [LastPass password manager](#lastpass-password-manager)
- [Slack](#slack)
- [Bash shell](#bash-shell)
- [Visual Studio Code](#visual-studio-code)
- [GitHub](#github)
- [Git](#git)
- [Python](#python)
- [Essential python packages](#essential-python-packages)
- [Jupyter extensions](#jupyter-extensions)
- [R, XQuartz,IRkernel and RStudio](#r-xquartx-irkernel-and-rstudio)
- [LaTeX](#latex)
- [PostgreSQL](#postgresql)
- [Docker](#docker)
- [Visual Studio Code Extensions](#visual-studio-code-extensions)

## Google Chrome browser
In MDS we will be using many tools that work most reliably on the Google Chrome browser (including our online quiz software). To install it, go to [https://www.google.com/chrome/](https://www.google.com/chrome/), click on "Download Chrome" and follow the instructions on the website to finish the installation.

## LastPass password manager
In MDS we share credentials via the password manager LastPass. This can also be useful for helping keep secure passwords and efficient authentication. Sign up for a free LastPass account here: [https://lastpass.com/create-account.php](https://lastpass.com/create-account.php). We also recommend installing the LastPass Chrome Extension available here: [https://chrome.google.com/webstore/detail/lastpass-free-password-ma/hdokiejnpimakedhajhdlcegeplioahd](https://chrome.google.com/webstore/detail/lastpass-free-password-ma/hdokiejnpimakedhajhdlcegeplioahd).

## Slack
For our MDS courses and program annoucements, correspondance and course forums we use the communcation tool Slack. Slack can be accessed via the web browser, however we strongly recommend installing the Slack App. The Slack app can be installed from the Mac App Store, or from the Slack website. Installation instructions from the Slack website install method are here: [https://slack.com/intl/en-ca/help/articles/207677868-Download-Slack-for-Mac](https://slack.com/intl/en-ca/help/articles/207677868-Download-Slack-for-Mac)

## Bash shell
Apple recently changed the Mac default shell in the Terminal to Zsh, however, we aim to teach with the same shell across all three operating systems we support, which is the Bash shell. Thus, we ask that you change the default shell in your Terminal to Bash by opening the Terminal ([how to video](https://youtu.be/5AJbWEWwnbY)) and typing: 

```
chsh -s /bin/bash
```

You will have to quit all instances of open Terminals and then restart the Terminal for this to take effect. 

## Visual Studio Code

### Installing

We need a powerfull but lightwight text editor, as well as a full-blown Python IDE for more complex analysis projects, the open-source text editor Visual Studio Code (VS Code) can serve both of these purposes for us. You can download VS Code at [https://code.visualstudio.com/download](https://code.visualstudio.com/download). Follow the installation instructions here: [https://code.visualstudio.com/docs/setup/mac](https://code.visualstudio.com/docs/setup/mac). **Be sure to follow the "[Launching from the command line](https://code.visualstudio.com/docs/setup/mac#_launching-from-the-command-line)" instructions as well.**

You can test that VS code is installed and can be opened from Terminal by restarting terminal and typing the following command:

```
code --version
```

you should see something like this if you were successful:
```
1.45.1
5763d909d5f12fe19f215cbfdd29a91c0fa9208a
x64
```

> Note: If you get an error message such as `-bash: code: command not found`, but you can see the VS Code application has been installed, then something went wrong with setting up the lauch from the command line. Try following [these](https://code.visualstudio.com/docs/setup/mac#_launching-from-the-command-line) instrutions again, in particular you might want to try the described manual method of adding VS Code to your path.

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

> Note: If you run into trouble, please see that Install Git > Mac OS section from [Happy Git and GitHub for the useR](http://happygitwithr.com/install-git.html#mac-os) for additional help or strategies for Git installation.

Next, we need to configure Git by telling it who you are, your email and setting the default text editor to VS Code. To do this type the following into the terminal (replacing Jane Doe and janedoe@example.com, with your name and email, respectively):

```
git config --global user.name "Jane Doe"
git config --global user.email janedoe@example.com
git config --global core.editor code
```

> Note: to ensure you haven't made a typo in any of the above, you can view your global Git configurations by typing: `git config --list --global --show-origin`.


## Python

We will be using Python for a large part of the program, and `conda` as our Python package manager. Thus to install Python and the `conda` package manager, we will install [Miniconda](https://docs.conda.io/en/latest/miniconda.html). We recommend installing the [Miniconda MacOSX 64-bit pkg install for Python **3.7**](https://repo.anaconda.com/miniconda/Miniconda3-latest-MacOSX-x86_64.pkg).

After installation, in terminal type the following to ask for the version of conda:
```
conda --version
```
you should see something like this if you were successful at installing conda (a Python package manager):

```
conda 4.8.2
```

> Note: If you see `zsh: command not found: conda`, see the section on [Bash](#bash-shell) above to set your default Terminal shell to Bash as opposed to Zsh.

After installation, in terminal type the following to ask for the version of Python:
```
python --version
```
you should see something like this if you were successful at installing Python:

```
Python 3.7.6
```

> Note: If instead you see `Python 2.7.X` you installed the wrong version. Uninstall the Miniconda you just installed (which usually lives in the `/opt` directory), and try the installation again, selecting **Python 3.7**.

## Essential Python packages

We also prefer to use packages on the conda-forge channel, so we set that to the default by typing the following in the terminal:

```
conda config --add channels conda-forge

```

Thus, to install other pacakges individually, we can now use the following: conda install <package-name>. We will install the key packages needed for the start of our program now:

```
conda install --yes \
 jupyterlab=2.* \
 numpy=1.* \
 pandas=1.* \
 flake8=3.* \
 black=19.*
```

> Note: we will use many more packages than those listed above across the MDS program, however we will manage these using virtual environments (which you will learn about in DSCI 521: Platforms for Data Science).

## Jupyter extensions
We will be using several Jupyter extensions that help us use Juypter notebooks more smoothly with Git & GitHub. To install them, paste the following in the terminal below:

```
conda install --yes nodejs=10.*
pip install --upgrade jupyterlab-git
conda install --yes jupytext=1.*
jupyter lab build
```

## R, XQuartz,IRkernel and RStudio
We will be using R, another programming language, a lot in the program. We will use R both in Jupyter notebooks and in RStudio. To have R work in Jupyter notebooks we will also have to install the IR kernel. Finally, some R packages rely on the dependency XQuartz which no longer ships with the Mac OS, thus we need to install it separately.

### R
Go to [https://cran.r-project.org/bin/macosx/](https://cran.r-project.org/bin/macosx/) and download the latest version of R for Mac (Should look something like this: R-3.6.1.pkg). Open the file and follow the installer instructions.

After installation, in Terminal type the following to ask for the version:
```
R --version
```

you should see something like this if you were successful:
```
R version 4.0.0 (2020-04-24) -- "Arbor Day"
Copyright (C) 2020 The R Foundation for Statistical Computing
Platform: x86_64-apple-darwin17.0 (64-bit)

R is free software and comes with ABSOLUTELY NO WARRANTY.
You are welcome to redistribute it under the terms of the
GNU General Public License versions 2 or 3.
For more information about these matters see
https://www.gnu.org/licenses/.
```

Note: Although it is possible to install R through conda, we highly recommend not doing so. In case you have already installed R using conda you can remove it by executing `conda uninstall r-base`.

### XQuartz

Some R packages rely on the dependency XQuartz which no longer ships with the Mac OS, thus we need to install it separately. Download it from here: [https://www.xquartz.org/](https://www.xquartz.org/) and follow the installation instructions.

### RStudio
Chose and download the Mac version of RStudio from [https://www.rstudio.com/products/rstudio/download/#download](https://www.rstudio.com/products/rstudio/download/#download). Open the file and follow the installer instructions.

To see if you were successful, try opening RStudio by clicking on its icon (from Finder, Applications or Launchpad). It should open and looks something like this picture below:

![](/resources_pages/imgs/RStudio.png)

### IR kernel

Open RStudio and type the following commands into the Console panel:

```
install.packages(c('IRkernel', 'tidyverse', 'blogdown', 'xaringan', 'renv'))
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

## LaTeX

We will install the lightest possible version of LaTeX and it's necessary packages as possible so that we can render Jupyter notebooks and R Markdown documents to html and PDF.

First, open RStudio and run the following commands to install the `tinytex` package and install `tinytex`:

```
install.packages('tinytex')
tinytex::install_tinytex()
```

The above is all we need to have LaTeX work with R Markdown documents, however to for Jupyter we need to add several more packages. Do this by opening a terminal and copying the following there press enter:

```
tlmgr install eurosym \
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

## PostgreSQL 

We will be using PostgreSQL as our database management system. You can download the most recent version from from [here](https://www.enterprisedb.com/downloads/postgres-postgresql-downloads). Follow the instructions for the installation. In the password page, type whatever password you want, but make sure you'll remember it later. For all the other options, use the default. 

To test if the installation was succesfull open the `SQL Shell` app from the LaunchPad or applications directory. It should look like this if it is working correctly: 

![](/resources_pages/imgs/sql_shell.png)

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

## Visual Studio Code Extensions

The real magic of VS Code is in the extensions that let you add languages, debuggers, and tools to your installation to support your specific workflow. Now that we have installed all our other Data Science tools, we can intall the VS Code extensions that work really well with them. From within VS Code you can open up the [Extension Marketplace](https://code.visualstudio.com/docs/editor/extension-gallery) to browse and install extensions by clicking on the Extensions icon in the Activity Bar indicated in the figure below.

![](/resources_pages/imgs/vscode.png)

To install an extension, you simply search for it in the search bar, click the extension you want, and then click "Install". There are extensions available to make almost any workflow or task you are interested in more efficient! Here we are interested in setting up VS Code as a Python IDE. To do this, search for and install the following extensions:

- Python (everything Python: notebooks, debugging, linting, formatting, etc.)
- markdownlint (markdown linting and style checking extension)
- GitLens - Git supercharged (powerful extension that extends VS Code's native git capabilities)
- Docker (easily use Docker from VS Code)
- (Optional) Material Theme and/or Predawn Theme Kit (additional colour themes to choose from)
- (Optional) Material Icon Theme (great-looking custom file icons!)
- (Optional) Bracket Pair Colorizer 2 (add colour to help distinguish your brackets: (), [], {})

This [video tutorial](https://www.youtube.com/watch?v=06I63_p-2A4) is an excellent introduction to using VS Code in Python.

## Attributions
* [Harvard CS109](http://cs109.github.io/2015/)
* [UBC STAT 545](http://stat545.com/packages01_system-prep.html#mac-os-system-prep) licensed under the [CC BY-NC 3.0](https://creativecommons.org/licenses/by-nc/3.0/legalcode).
* [Software Carpentry](https://software-carpentry.org/)
