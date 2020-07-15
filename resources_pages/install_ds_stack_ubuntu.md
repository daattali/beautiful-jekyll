---
layout: page
title: Ubuntu
subtitle: MDS software stack install instructions for Ubuntu
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

> Note: ensure that you download the Chrome installer and then install it by clicking on the file after it downloads (i.e., do not select the option to open with Software install).

## LastPass password manager
In MDS we share credentials via the password manager LastPass. This can also be useful for helping keep secure passwords and efficient authentication. Sign up for a free LastPass account here: [https://lastpass.com/create-account.php](https://lastpass.com/create-account.php). We also recommend installing the LastPass Chrome Extension available here: [https://chrome.google.com/webstore/detail/lastpass-free-password-ma/hdokiejnpimakedhajhdlcegeplioahd](https://chrome.google.com/webstore/detail/lastpass-free-password-ma/hdokiejnpimakedhajhdlcegeplioahd).

## Slack
For our MDS courses and program annoucements, correspondance and course forums we use the communcation tool Slack. Slack can be accessed via the web browser, however we strongly recommend installing the Slack App. The Slack app can be installed from the the Slack website. Installation instructions are available here: [https://slack.com/intl/en-ca/downloads/linux](hhttps://slack.com/intl/en-ca/downloads/linux). Alternatively, you can download Slack from the [Snap store](https://snapcraft.io/slack).

## Visual Studio Code

We need a powerfull but lightwight text editor, as well as a full-blown Python IDE for more complex analysis projects, the open-source text editor Visual Studio Code (VS Code) can serve both of these purposes for us. You can download VS Code at [https://code.visualstudio.com/download](https://code.visualstudio.com/download). The getting started instructions are here: [https://code.visualstudio.com/docs/?dv=linux64_deb](https://code.visualstudio.com/docs/?dv=linux64_deb). 

You can test that VS code is installed and can be opened from Terminal by restarting terminal and typing the following command:

```
code --version
```

you should see something like this if you were successful:
```
1.47.0
d5e9aa0227e057a60c82568bf31c04730dc15dcd
x64
```

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

We will be using the command line version of Git as well as Git through RStudio and Jupyter lab. There are some new Git commands that we will use that are only available as of Git 2.23 (or newer), thus to get this newest version we will ask you to update your Git even if you have already installed it. 

```
sudo apt-add-repository ppa:git-core/ppa
sudo apt-get update
sudo apt-get install git
```

After installation, in terminal type the following to ask for the version:
```
git --version
```
you should see something like this if you were successful:

```
git version 2.27.0
```

Next, we need to configure Git by telling it who you are, your email and setting the default text editor to VS Code. To do this type the following into the terminal (replacing Jane Doe and janedoe@example.com, with your name and email, respectively):

```
git config --global user.name "Jane Doe"
git config --global user.email janedoe@example.com
git config --global core.editor code
```

> Note: to ensure you haven't made a typo in any of the above, you can view your global Git configurations by typing: `git config --list --global --show-origin`.

## Python

We will be using Python for a large part of the program, and `conda` as our Python package manager. Thus to install Python and the `conda` package manager, we will install [Miniconda](https://docs.conda.io/en/latest/miniconda.html). We recommend installing the [Miniconda3 Linux 64-bit install for Python **3.7**](https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh).

Once the download is finished, open Terminal and execute the following commands:
```
bash path/to/the/file
```
> Note: most often this file is downloaded to the `Downloads` directory, and thus the command above is usually: 
>
>```
>bash Downloads/Anaconda3-2019.07-Linux-x86_64.sh
>```

The instructions for the installation will then appear: (1) press Enter; (2) once the licence agreement shows, you can keep pressing enter to go through the whole document, or press Q to quit; (3) Type `yes` to accept the licence agreement; (4) you can accept the default installation location (just press Enter once again); (5) Type `yes` once again to accept the installer to run `conda init`.

After installation, restart the terminal. Then, in terminal type the following to ask for the version of conda:
```
conda --version
```
you should see something like this if you were successful at installing conda (a Python package manager):

```
conda 4.8.3
```

After installation, in terminal type the following to ask for the version of Python:
```
python --version
```
you should see something like this if you were successful at installing Python:

```
Python 3.7.7
```

> Note: If instead you see `Python 2.7.X` you installed the wrong version. Uninstall the Miniconda you just installed (which usually lives in the `/home/<USER>` directory), and try the installation again, selecting **Python 3.7**.

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

## R, IRkernel and RStudio
We will be using R, another programming language, a lot in the program. We will use R both in Jupyter notebooks and in RStudio. To have R work in Jupyter notebooks we will also have to install the IR kernel.

#### R

To obtain the latest R 4.0 packages, type the following into the terminal:

```
sudo apt-add-repository 'deb https://cloud.r-project.org/bin/linux/ubuntu focal-cran40/'
```

Next, add the key ID for the CRAN network:

```
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys E298A3A825C0D65DFD57CBB651716619E084DAB9
```
Then, update the repository:

```
sudo apt-get update
 ```

Next, install `r-base`:

```
sudo apt-get install r-base
```

And then `r-base-dev` (useful for compiling R packages from source):

```
sudo apt-get install r-base-dev
```

After installation, in terminal type the following to ask for the version:
```
R --version
```

You should see something like this if you were successful:

```
R version 4.0.2 (2020-06-22) -- "Taking Off Again"
Copyright (C) 2020 The R Foundation for Statistical Computing
Platform: x86_64-pc-linux-gnu (64-bit)

R is free software and comes with ABSOLUTELY NO WARRANTY.
You are welcome to redistribute it under the terms of the
GNU General Public License versions 2 or 3.
For more information about these matters see
https://www.gnu.org/licenses/.
```

> Note: For MDS it is important that you have R 4.0 or higher.

### RStudio

Chose and download the Ubuntu 18/Debian 10 version of RStudio Desktop from [https://www.rstudio.com/products/rstudio/download/#download](https://www.rstudio.com/products/rstudio/download/#download). Open the file and follow the installer instructions.

> Note: there is not yet a RStudio version for Ubuntu 20.04, however many users have been successfully using the Ubuntu 18/Debian 10 version of RStudio Desktop on Ubuntu 20.04 and so we will use that.

To see if you were successful, try opening RStudio by clicking on its icon. It should open and looks something like this picture below:

![](/resources_pages/imgs/RStudio.png)

### Essential R packages

The `tidyverse` R package (and some others) have external dependencies on Ubuntu outside of R. We need to install these first before we install such R packages:

```
sudo apt install libcurl4-openssl-dev libssl-dev libxml2-dev
```

We will install the key R packages needed for the start of our program now:

```
install.packages(c('tidyverse', 'tinytex', 'blogdown', 'xaringan', 'renv'))
```

> Note: we will use many more packages than those listed above across the MDS program, however we will manage these using the `renv` package manager (which you will learn about in DSCI 521: Platforms for Data Science).

### IR kernel

Open RStudio and type the following commands into the Console panel:

```
install.packages('IRkernel')
```


In Terminal window type the following commands:

```
R
```

This will open R in terminal. In R, type:

```
install.packages('tidyverse')
install.packages('IRkernel')
```

Once it is finished (it might take a minute), type
```
IRkernel::installspec()
```

To see if you were successful, try running Jupyter Lab and seeing if you have working R kernel. To launch the Jupyter Lab type the following in the Windows Powershell:

```
jupyter lab
```

A browser should have launched and you should see a page that looks like the screenshot below. Now click on "R" notebook (circled in red on the screenshot below) to launch an Jupyter Lab with an R kernel.

![](/resources_pages/imgs/jupyter_lab_r_kernel.png)

Sometimes a kernel loads, but doesn't work as expected. To test whether your installation was done correctly now type `library(tidyverse)` in the code cell and click on the run button to run the cell. If your R kernel works you should see something like the image below:

![](/resources_pages/imgs/jupyter_lab_r_kernel2.png)

## LaTeX

We will install the lightest possible version of LaTeX and it's necessary packages as possible so that we can render Jupyter notebooks and R Markdown documents to html and PDF.

First, open RStudio and run the following commands to install the tinytex package and install tinytex:

```
install.packages('tinytex')
tinytex::install_tinytex()
```

The above is all we need to have LaTeX work with R Markdown documents, however to for Jupyter we need to add the TinyTex executables to our `PATH` and install several more packages. 

To add the TinyTex executables to our `PATH` we need to edit our `.bashrc` file. The TinyTex executables are usually installed in `$HOME/bin`. Thus, add the lines below to the bottom of your `.bashrc` file (which you can open by `code $HOME/.bashrc`):

```
# add TinyTex executables to the path
export PATH="$HOME/bin:$PATH"
```
Quit your terminal program for these changes to be reflected on your system.

Next, install the additional LaTeX packages needed for Jupyter by opening terminal and copying the following there press enter:

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
We will be using PostgreSQL as our database management system. To install PostgreSQL in Ubuntu type the following commands:
- for Ubuntu 20.04
```
sudo add-apt-repository 'deb http://apt.postgresql.org/pub/repos/apt/ focal-pgdg main'
```

Then, 
```
wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
sudo apt-get update
sudo apt-get install postgresql-12
```
That's it! You can test if the installation worked by running
```
sudo su -c psql postgres
```

From a succesful install, the above should yield the prompt to change to what is shown below:
```
psql (12.3 (Ubuntu 12.3-1.pgdg18.04+1))
Type "help" for help.
postgres=# 

```

> Note: to exit from Postgres type `exit`



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

## Docker

You will use Docker to create reproducible, sharable and shippable computing environments for your analyses. For this you will need a Docker account. You can sign up for a free one [here](https://store.docker.com/signup?next=%2F%3Fref%3Dlogin).

After signing-up, you also need to install Docker **CE** for Ubuntu. Follow the installation instructions using the "Install using the repository" methods found [here](https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository).

Next, follow the Linux post installation steps [here](https://docs.docker.com/engine/install/linux-postinstall/) so that you can run Docker without typing `sudo`. 

After installation, in terminal type the following to ask for the version:

```
sudo docker run hello-world
```

you should see something like this if you were successful:

```
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
0e03bdcc26d7: Pull complete 
Digest: sha256:d58e752213a51785838f9eed2b7a498ffa1cb3aa7f946dda11af39286c3db9a9
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

### Customizing VS Code with Extensions

The real magic of VS Code is in the extensions that let you add languages, debuggers, and tools to your installation to support your specific workflow. From within VS Code you can open up the [Extension Marketplace](https://code.visualstudio.com/docs/editor/extension-gallery) to browse and install extensions by clicking on the Extensions icon in the Activity Bar indicated in the figure below.

![](/resources_pages/imgs/vscode.png)

To install an extension, you simply search for it in the search bar, click the extension you want, and then click "Install". There are extensions available to make almost any workflow or task you are interested in more efficient! Here we are interested in setting up VS Code as a Python IDE. To do this, search for and install the following extensions:

- Python (everything Python: notebooks, debugging, linting, formatting, etc.)
- markdownlint (markdown linting and style checking extension)
- GitLens (powerful extension that extends VS Code's native git capabilities)
- Docker (easily use Docker from VS Code)
- (Optional) Material Theme and/or Predawn Theme Kit (additional colour themes to choose from)
- (Optional) Material Icon Theme (great-looking custom file icons!)
- (Optional) Bracket Pair Colorizer 2 (add colour to help distinguish your brackets: (), [], {})

This [video tutorial](https://www.youtube.com/watch?v=06I63_p-2A4) is an excellent introduction to using VS Code in Python.

## Attributions
* [Harvard CS109](http://cs109.github.io/2015/)
* [UBC STAT 545](http://stat545.com/packages01_system-prep.html#mac-os-system-prep) licensed under the [CC BY-NC 3.0](https://creativecommons.org/licenses/by-nc/3.0/legalcode).
* [Software Carpentry](https://software-carpentry.org/)
