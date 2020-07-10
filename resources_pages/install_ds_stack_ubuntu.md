---
layout: page
title: Ubuntu
subtitle: MDS software stack install instructions for Ubuntu
---
These instructions will walk you through installing the required Data Science software stack for the UBC Master of Data Science program. Before starting, ensure that your laptop meets our program requirements:

- runs one of the following operating systems: macOS 10.15.X (Catalina) or later, Ubuntu 20.04 or later, Windows 10 Professional, Enterprise or Education; version 1909 or later. Please note that Windows 10 Home is not sufficient as not all the software required for the program can be installed on that OS.
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

We will be using Python for a large part of the program, including many popular 3rd party Python libraries for scientific computing. [__Anaconda__](https://www.anaconda.com/download/#linux) is an easy-to-install distribution of Python and most of these libraries (as well as Jupyter notebooks, one of the developing environments we will be using). We __require__ that you use Anaconda for this program. If you insist on using your own Python setup instead of Anaconda, we will not be able to provide technical support with installation or later issues. For this program we are using __Python 3__ , not __Python 2__, so please choose the Anaconda versions that include Python 3.7

Head to https://www.anaconda.com/download/#linux and download the Anaconda version for Linux with **Python 3.7** (make sure the linux tab is selected). Once the download is finished, open Terminal and execute the following commands:
```
bash path/to/the/file
```

For example,
```
bash Downloads/Anaconda3-2019.07-Linux-x86_64.sh
```
The instructions for the installation will then appear: (1) press Enter; (2) once the licence agreement shows, you can keep pressing enter to go through the whole document, or press Q to quit; (3) Type `yes` to accept the licence agreement; (4) you can accept the default installation location (just press Enter once again); (5) Type `yes` once again to accept the installer to run `conda init`.

After installation, restart Terminal and type:
```
python3
```
you should see something like this if you were successful:

```
Python 3.7.3 (default, Mar 27 2019, 22:11:17) 
[GCC 7.3.0] :: Anaconda, Inc. on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> 
```

If instead you see `Python 2.7.X` you installed the wrong version. Follow [these instructions](https://docs.anaconda.com/anaconda/install/uninstall) to delete this installation and try the installation again, selecting **Python 3.7**.

To see if Jupyter was successfully installed in the Anaconda Python distribution type the following in the terminal:

```
jupyter lab
```

A browser should have launched and you should see a page that looks like the screenshot below. 

![](/resources_pages/imgs/jupyter_lab.PNG)


If you already have installed Anaconda at some point in the past, we recommend that you update to the latest Anaconda version by updating conda, then Anaconda in terminal as follows:
```
    conda update conda
    conda update anaconda
```

## R, IRkernel and RStudio
We will be using R, another programming language, a lot in the program. We will use R both in Jupyter notebooks and in RStudio. To have R work in Jupyter notebooks we will also have to install the IR kernel.

#### R

Type `sudo apt-add-repository` in Terminal followed by the corresponding line for your version:
  - for Ubuntu 19.04 (Disco) add: `'deb https://cloud.r-project.org/bin/linux/ubuntu disco-cran35/'`
  - for Ubuntu 18.04.1 (Bionic Beaver) add: `'deb https://cloud.r-project.org/bin/linux/ubuntu bionic-cran35/'`
  - for Ubuntu 17.10.1 (Artful Aardvark) add: `'deb https://cloud.r-project.org/bin/linux/ubuntu bionic-cran35/'`
  - for Ubuntu 16.04.4 (Xenial Xerus) add: `'deb https://cloud.r-project.org/bin/linux/ubuntu xenial-cran35/'`
  - for Ubuntu 14.04.5 (Trusty Tahr) add: `'deb https://cloud.r-project.org/bin/linux/ubuntu trusty-cran35/'`

For example, for Ubuntu 18.04 (Bionic Beaver):
```
sudo apt-add-repository 'deb https://cloud.r-project.org/bin/linux/ubuntu bionic-cran35/'
```

Next, add the key ID for the CRAN network:
```
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys E298A3A825C0D65DFD57CBB651716619E084DAB9
```

Then, update the repository:
```
sudo apt-get update
 ```

Next, install the following packages:
```
sudo apt-get install curl libssl-dev libcurl4-openssl-dev libpq-dev libxml2-dev r-base
 ```

After installation, in terminal type the following to ask for the version:
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

#### RStudio
Chose and download the appropriate Ubuntu version of [RStudio](www.rstudio.com/products/rstudio/download/#download). 

Double click the file and click `install` or, alternatively, run the following command:
```
sudo apt install ./Downloads/rstudio-1.2.1335-amd64.deb
```
and you should be able to open RStudio. 

To see if you were successful, try opening RStudio by clicking on its icon (from Finder, Applications or Launchpad). It should open and looks something like this picture below:

![](/resources_pages/imgs/RStudio.png)

#### IR kernel
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

## PostgreSQL
We will be using PostgreSQL as our database management system. To install PostgreSQL in Ubuntu type the following commands:
- for Ubuntu 18.04
```
sudo add-apt-repository 'deb http://apt.postgresql.org/pub/repos/apt/ bionic-pgdg main'
```
- for Ubuntu 16.04
```
sudo add-apt-repository 'deb http://apt.postgresql.org/pub/repos/apt/ xenial-pgdg main'
```

Then, 
```
wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
sudo apt-get update
sudo apt-get install postgresql-11
```
That's it! You can test if the installation worked by running
```
sudo su -c psql postgres
```

## Visual Studio Code

### Installing

We need a text editor to be able to write complete applications. One is available through Jupyter, but sometimes it is helpful to have a standalone text editor, for this we will be using the open-source text editor Visual Studio Code (VS Code). You can download VS Code at https://code.visualstudio.com/download. Double-click the item, and click in install. That's it!

You can test that VS code is installed and can be opened from Terminal by running the following command:

```
code --version
```

you should see something like this if you were successful:
```
1.36.1
2213894ea0415ee8c85c5eea0d0ff81ecc191529
x64
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

## Make

We will be using Make to automate our analysis scripts. More on this later!
Make already comes installed in Ubutun 18.04, you can check by executing the following command in Terminal:
```
make --version
```
you should see something like this if you were successful:

```
GNU Make 4.2.1
Built for x86_64-pc-linux-gnu
Copyright (C) 1988-2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

If not, to install Make open Terminal and type the following command:
```
sudo apt-get install build-essential
```

After, type `make --version` to make sure you were successful. 

## Docker

You will use Docker to create reproducible, sharable and shippable computing environments for your analyses. For this you will need a Docker account. You can sign up for a free one [here](https://store.docker.com/signup?next=%2F%3Fref%3Dlogin).

After signing-up, you also need to install Docker **CE** for Ubuntu. Follow the installation instructions [here](https://docs.docker.com/install/linux/docker-ce/ubuntu/).

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
