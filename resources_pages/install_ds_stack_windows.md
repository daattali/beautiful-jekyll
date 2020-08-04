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

## Visual Studio Code

### Installing

We need a text editor to be able to write complete applications. One is available through Jupyter, but sometimes it is helpful to have a standalone text editor, for this we will be using the open-source text editor Visual Studio Code (VS Code). You can download VS Code at https://code.visualstudio.com/download. At "Select Additional Tasks" make sure that "Add to path" is selected (I also like to select all the other three items - see figure below).

![](/resources_pages/imgs/vs_code.png)

You can test that VS code is installed and can be opened from the Powershell by running the following command:

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

This [video tutorial](https://www.youtube.com/watch?v=-nh9rCzPJ20) is an excellent introduction to using VS Code in Python.

## LaTeX

Download the installer from [http://mirror.ctan.org/systems/texlive/tlnet/install-tl-windows.exe](http://mirror.ctan.org/systems/texlive/tlnet/install-tl-windows.exe). After downloading run the `install-tl-windows.exe` file and follow the installation instructions choosing the default options.

*note - if a screen appears titled "Windows protected your PC", click on "More info" link and the "Run anyway" button*

After installation, restart Powershell and type the following to ask for the version:

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
