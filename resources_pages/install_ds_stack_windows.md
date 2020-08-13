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
- is at most 6 years old at the start of the program (4 years old or newer is recommended)
- uses English as the default language

 **Students' whose laptops do not meet the requirements specified above will not be able to receive technical assistance from the MDS team in troubleshooting installation issues.**

## Table of Contents

- [Web browser](#web-browser)
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
- [VS Code extensions](#vs-code-extensions)
- [Post-installation notes](#post-installation-notes)

## Installation notes

In all the sections below,
if you are presented with the choice to download either a 64-bit (also called x64)
or a 32-bit (also called x86) version of the application **always** choose the 64-bit version.

Once you have completed these installation instructions,
make sure to follow the post-installation notes at the end
to check that all software is setup correctly.

## Web browser

In MDS we will be using many tools that work most reliably on Google Chrome and Firefox (including our online quiz software), so we recommend that you use one of these browsers.

- To install Chrome, go to [https://www.google.com/chrome/](https://www.google.com/chrome/), click on "Download Chrome" and follow the instructions on the website to finish the installation.
- To install Firefox, go to [https://www.mozilla.org/en-US/firefox/new/](https://www.mozilla.org/en-US/firefox/new/), click on "Download Firefox" and follow the instructions on the website to finish the installation.

## LastPass password manager

Some MDS courses (e.g. the capstone project) use the LastPass password manager to share credentials. Although we will not cover privacy and security topics until the second semester of the program, we recommend that you use a password manager such as LastPass to help you create strong passwords and store them securely, and to facilitate online authentication. You can sign up for a free LastPass account here: [https://lastpass.com/create-account.php](https://lastpass.com/create-account.php). We also recommend installing the LastPass Chrome or Firefox browser extension available here: [https://lastpass.com/misc_download2.php](https://lastpass.com/misc_download2.php).

## Slack

For MDS program announcements, course forums, and correspondence we use the communication tool Slack. Slack can be accessed via the web browser, but we recommend using the Slack app, which can be installed via downloadable file from the slack website [https://slack.com/intl/en-ca/downloads/windows](https://slack.com/intl/en-ca/downloads/windows).


## Visual Studio Code

The open-source text editor Visual Studio Code (VS Code) is both a powerful text editor and a full-blown Python IDE, which we will use for more complex analysis. Go to [https://code.visualstudio.com/download](https://code.visualstudio.com/download) and download the windows version of VS Code. After the download has finished, run the installer and accept the default configuration for all pages except for the following:

- *Optional* On the **Select Additional Tasks** page, check "Create a desktop icon" under "Additional icons".
- Also on the **Select Additional Tasks** page check all four boxes under "Other"
    - "Add 'Open with Code' action to Windows file context menu"
    - "Add 'Open with Code' action to Windows directory context menu"
    - "Register Code as an editor for supported file types"
    - "Add to PATH" (this should be selected by default).

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

Although Git and Bash are two separate programs,
we are including them in the same section here 
since they are packaged together in the same installer on Windows.
Briefly, we will be using the Bash shell to interact with our computers via a command line interface,
and Git to keep a version history of our files and upload to/download from to GitHub.
We will be using the command line version of Git as well as Git through RStudio and JupyterLab. Some of the Git commands we will use are only available since Git 2.23, so if you're Git is older than this version, we ask you to update it.

Go to <https://git-scm.com/download/win> and download the windows version of git. After the download has finished, run the installer and accept the default configuration for all pages except for the following:

- *Optional* On the **Select Components** page, check "On the Desktop" under "Additional icons".
- On the **Choosing the default editor used by Git** page, select "Use Visual Studio Code as Git's default editor" from the drop-down menu'

![](/resources_pages/imgs/vscode-as-git-editor.png)

> Note if you wish to pin Git Bash to the taskbar, you need to search for the program in the start menu, right click the entry and select "Pin to taskbar". If you instead first launch the program and pin it by right clicking on the taskbar icon, Git Bash will open with the wrong home directory (`/` instead of `/c/users/$USERNAME`.

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

> If you tried to paste the above into the Git Bash terminal, you will have noticed that `Ctrl+V` does not work in Git Bash. Instead you need to right click and select "Paste" or use the `Shift+Insert` shortcut. To copy from the Git Bash terminal you simply select the text you want and it is copied automatically.

> Via right click you can also reach the settings menu where you can configure Git Bash to your preferences, a couple of tips would be to check "Mouse -> Clicks place command line cursor" and change the font to something more legible, e.g. Consolas ("Text -> Select").

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

### Configuring Git user info

Next, we need to configure Git by telling it your name and email. To do this type the following into the terminal (replacing Jane Doe and janedoe@example.com, with your name and email (the same used to sign up for GitHub), respectively):

```
git config --global user.name "Jane Doe"
git config --global user.email janedoe@example.com
```

> Note: to ensure that you haven't made a typo in any of the above, you can view your global Git configurations by either opening the configuration file in a text editor (e.g. via the command `code ~/.gitconfig`) or by typing `git config --list --global`.

### Setting VS Code as the default editor

To make programs run from the terminal (such as `git`) use VS Code by default, we will modify `~/.bash_profile`. First, open it using VS Code:

```
code ~/.bash_profile
```

Append the following lines:

```
# Set the default editor for programs launch from terminal
EDITOR="code --wait"
VISUAL=$EDITOR  # Use the same value as for "EDITOR" in the line above
```

> Most terminal programs will read the `EDITOR` environmental variable when determining which editor to use, but some read `VISUAL`, so we're setting both to the same value.

## Python, Conda, and JupyterLab

### Python and Conda

We will be using Python for a large part of the program, and `conda` as our Python package manager. To install Python and the `conda` package manager, we will use the [Miniconda platform (read more here)](https://docs.conda.io/en/latest/miniconda.html), for which the [Python 3.7 64-bit version can be downloaded here](https://repo.anaconda.com/miniconda/Miniconda3-latest-Windows-x86_64.exe). After the download has finished, run the installer and accept the default configuration for all pages.

> Do *not* add miniconda to PATH. We will set this up later.

After installation, open the Start Menu and search for the program called "Anaconda Prompt (miniconda3)". When this opens you will see a prompt similar to `(base) C:\Users\your_name`. Type the following to check that your Python installation is working:

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

> Note that if you want to run Python interactively from the Git Bash terminal, you need to prepend the `winpty` command, so the full command would be `winpty python`. Running just `python` works on other setups, but will freeze the Git Bash terminal.

Let's also check the version of the `conda` package manager. If you type

```
conda --version
```

you should see something like this

```
conda 4.8.3
```

> *Optional* One annoyance with our current terminal setup is that the word `(base)` is not on the same row as the rest of the prompt string (the part with `your_name@your_computer`. To fix this we can edit the `.bash_profile` configuration file to indicate that we do not want a newline at the beginning of the prompt string. Open up the configuration file using VS Code by typing the following command into a terminal:
>
> ```
> code "/c/Program Files/Git/etc/profile.d/git-prompt.sh"
> ```
>
> Delete the line that reads the following (it should be line 13):
>
> ```
> PS1="$PS1"'\n'       # new line
> ```
>
> Click to save the file,
> when VS Code prompts you that the saving failed,
> click "Retry as Admin" and then "Yes".
> That's it!
> Now if you launch a new terminal instance,
> you will see `(base)` on the same line as the rest of the prompt string as in the screenshot below.
>
> ![](/resources_pages/imgs/remove-newline-from-ps1.png)

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
conda install -y nodejs=10.*
pip install --upgrade jupyterlab-git
conda install -y jupytext=1.*
jupyter lab build
```

To test that your JupyterLab installation is functional, you can type `jupyter lab` into a terminal, which should open a new tab in your default browser with the JupyterLab interface.

![](/resources_pages/imgs/jupyter_lab.PNG)

## R, IRkernel, Rtools, and RStudio

R is another programming language that we will be using a lot in the MDS program. We will use R both in Jupyter notebooks and in RStudio.

### R

Go to <https://cran.r-project.org/bin/windows/base/> and download the latest version of R for Windows (4.0.2 at the time of writing). Open the file and follow the installer instructions accepting the default configuration.

After the installation is complete, we will add the R executables to the PATH variable in terminal so that you can use it without typing the full path to R each time. Open a terminal and type:

```
code ~/.bash_profile
```

Append the following line to the file

```
# Add R and Rscript to PATH
export PATH="/c/Program Files/R/R-4.0.2/bin/x64":$PATH
```

Now you can open terminal and type

```
R --version
```

which should return something like:

```
R version 4.0.2 (2020-06-22) -- "Taking Off Again"
Copyright (C) 2020 The R Foundation for Statistical Computing
Platform: x86_64-w64-mingw32/x64 (64-bit)

R is free software and comes with ABSOLUTELY NO WARRANTY.
You are welcome to redistribute it under the terms of the
GNU General Public License versions 2 or 3.
For more information about these matters see
https://www.gnu.org/licenses/.
```

> Note: Although it is possible to install R through Anaconda, we highly recommend not doing so. In case you have already installed R using Anaconda you can remove it by executing `conda uninstall r-base`.

### RStudio

Download the Windows version of RStudio from <https://www.rstudio.com/products/rstudio/download/preview>. Open the file and follow the installer instructions.

To see if you were successful, try opening RStudio by clicking on its icon. It should open and looks something like this picture below:

![](/resources_pages/imgs/RStudio.png)

Next, we will make sure that Rstudio uses the same directories as R from terminal for its configuration. To do this, we will need to set an environmental variable in Windows. First, open the start menu, type "env" and select the match that reads "Edit the system environment variables". Click the button at the bottom that reads "Environmental Variables...":

![](/resources_pages/imgs/sys-props-env-vars.png)

Under "User variable" click the "New..." button:

![](/resources_pages/imgs/env-vars-new-user-var.png)

And type in `R_USER` as the "Variable name" and `C:\Users\username` as the "Variable value", replacing `username` with your actual user name (if you don't know your user name, look at the top of the screenshot above where it says "User variables for your_username"):

![](/resources_pages/imgs/new-user-var-values.png)

Click "OK" on all of the three windows we opened above and you're done! If you open RStudio and R from terminal and type

```
.libPaths()
```

both should return the same values, e.g.

```
"C:/Users/joelo/R/win-library/4.0"   "C:/Program Files/R/R-4.0.2/library"
```


### Rtools

Windows users will also need to install Rtools, which will allow you to use external libraries. Go to <http://cran.r-project.org/bin/windows/Rtools/> and download the latest version (e.g., Rtools40.exe). After the download has finished, run the installer with the default configuration. Do *not* follow the Rtools' website instructions for "Putting Rtools on the PATH". RStudio will put Rtools on the PATH automatically when it is needed.

To test if you're installation was successful, open RStudio and type the following into the Console:

```
install.packages("jsonlite", type = "source")
```

If the `jsonlite` package installs without errors, Rtools is setup correctly.

### Essential R packages

Next, install the key R packages needed for the start of MDS program,
by typing the following into the R terminal in RStudio:

```
install.packages(c('tidyverse', 'blogdown', 'xaringan', 'renv', 'devtools', 'usethis'))
```

If you get a prompt asking if you want to install packages that need compilation from sources, click "Yes".

> Note: we will use many more packages than those listed above across the MDS program, however we will manage these using the `renv` package manager (which you will learn about in DSCI 521: Platforms for Data Science).

### IR kernel

The `IRkernel` package is needed to make R work in Jupyter notebooks. To enable this kernel in the notebooks, open R *from a terminal* and run the setup via the following two commands:

```
install.packages('IRkernel')
IRkernel::installspec()
```

When asked to select a mirror, pick one at a location close to where you live for faster downloads.

> Note that you cannot use RStudio for this step because it will not be able to find the jupyter installation. R from terminal will since the correct PATH for jupyter is set when the terminal is launched.

To see if you were successful, try running JupyterLab and check if you have a working R kernel. To launch the JupyterLab type the following in the terminal:

```
jupyter lab
```

A browser should have launched and you should see a page that looks like the screenshot below. Now click on "R" notebook (circled in red on the screenshot below) to launch an JupyterLab with an R kernel.

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

Later in the program, we will be using `make` to automate our analysis scripts. [Download `make` from this URL](https://downloads.sourceforge.net/project/ezwinports/make-4.3-without-guile-w32-bin.zip). Click on the downloaded zip-file to open it in the File Explorer, click the "Extract" tab and the button in the header that says "Extract all" and accept the default extraction location.

Next we need to add the `bin` folder in this extraction location to our PATH so that we can use `make` from the terminal (like we did with R earlier). Open the bash configuration file with VS Code by pasting this into a terminal:

```
code ~/.bash_profile
```

And replace the section that reads:

```
# Add R and Rscript to path
export PATH="/c/Program Files/R/R-4.0.2/bin/x64":$PATH
```

with the following (prepending the `make` folder to the path above):

```
# Add R, Rscript, and Make to path
export PATH="/c/Users/${USERNAME}/Documents/make-4.3-without-guile-w32-bin/bin":"/c/Program Files/R/R-4.0.2/bin/x64":$PATH
```

Launch a new terminal and run

```
make --version
```

which should return something like

```
GNU Make 4.3
Built for Windows32
Copyright (C) 1988-2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

## PostgreSQL

We will be using PostgreSQL as our database management system. You can [download PostgreSQL from here](https://www.enterprisedb.com/downloads/postgres-postgresql-downloads). Follow the instructions for the installation. In the password page, type whatever password you want, but make sure you'll remember it later. For all the other options, use the default. You do not need to run "StackBuilder" at the end of the installation.

To test if the installation was successful open the `SQL Shell` app from the Start menu. You will be asked to setup your configuration, accept the default value (the one within square brackets) for the first four values by pressing enter four times, then type in your password and press enter one last time. It should look like this if it is working correctly:

![](/resources_pages/imgs/psql-windows.png)

## Docker

You will use Docker to create reproducible, sharable and shippable computing environments for your analyses. For this you will need a Docker account. You can sign up for a free one [here](https://store.docker.com/signup?next=%2F%3Fref%3Dlogin).

After signing-up and signing into the Docker Store, go [here](https://store.docker.com/editions/community/docker-ce-desktop-windows) and click on the "Get Stable" button on the right hand side of the screen. Then follow the installation instructions on that screen.

After installation (Docker will make you sign out to finish installing), launch a terminal and type

```
docker run hello-world
```

which should output something like this:

```
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
0e03bdcc26d7: Pulling fs layer
0e03bdcc26d7: Verifying Checksum
0e03bdcc26d7: Download complete
0e03bdcc26d7: Pull complete
Digest: sha256:49a1c8800c94df04e9658809b006fd8a686cab8028d33cfba2cc049724254202
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
## Improving the bash configuration

To improve your experience using bash,
we recommend appending a few lines to the end of your bash configuration file.
This is optional,
but makes it easier to use the TAB key for autocompletion
and improves how bash handles the command history
(we will talk more about these topics during class).
First,
open the configuration file:

```
code ~/.bash_profile
```

Then past the following at the end of the file
(make sure not to overwrite any existing lines):

```
# Prepend a newline to the prompt string to separate it from the last command's output
PS1="\n$PS1"

# TAB completion configuration
# TAB completion ignores case
bind "set completion-ignore-case on"
# Require only one instead of two TAB presses before showing matches
bind "set show-all-if-ambiguous on"
# If there are multiple matches for completion, cycle through them with TAB
bind 'TAB':menu-complete
# Perform partial completion on the first Tab press,
# only start cycling full results on the second Tab press
bind "set menu-complete-display-prefix on"

# History configuration
# Cycle through history based on characters already typed on the line
bind '"\e[A":history-search-backward'
bind '"\e[B":history-search-forward'
# Append to the history file, don't overwrite it.
shopt -s histappend
# Write commands to history one-by-one right after they are executed
# instead of all together when the terminal is closed.
# New terminals now see all commands run in currently open terminals
PROMPT_COMMAND='history -a'
# Increase history size
HISTSIZE=50000
HISTFILESIZE=50000

# Aliases
# Note that aliases only are in effect when you are using the shell interactively
# (e.g. opening the Git Bash terminal and typing or pasting commands).
# If you run a bash script or makefile,
# the original command is used instead of your alias.
# Run Python and Docker in compatibility mode when started from an interactive shell
alias python="winpty python"
alias docker="winpty docker"
```

## VS Code extensions

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

## Post-installation notes

You have completed the installation instructions, well done 🙌!
We have created a script to help you check that your installation was successful,
and to provide instructions for how you can troubleshoot any potential issues.
To run this script,
please execute the following command from your terminal.

```
bash <(curl -Ss https://raw.githubusercontent.com/UBC-MDS/UBC-MDS.github.io/master/resources_pages/check-setup-mds.sh)
```

> Note that in general you should be careful running scripts unless they come from a trusted source as in this case (just like how you should be careful when downloading and installing programs on your computer).

## Attributions
* [Harvard CS109](http://cs109.github.io/2015/)
* [UBC STAT 545](http://stat545.com/packages01_system-prep.html#mac-os-system-prep) licensed under the [CC BY-NC 3.0](https://creativecommons.org/licenses/by-nc/3.0/legalcode).
* [Software Carpentry](https://software-carpentry.org/)
* [Oracle - How do I set or change the PATH system variable?](https://www.java.com/en/download/help/path.xml)
* [Numerical Methods - Getting started](https://clouds.eos.ubc.ca/~phil/numeric/python.html)
