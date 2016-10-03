# MDS software installation instructions


## Table of Contents
- [GitHub](#github)
- [git](#git)
- [Getting and Installing Python](#getting-and-installing-python)
- [Installing R and RStudio](#installing-r-and-rstudio)
- [Installing Rodeo](#installing-rodeo)
- [Installing a Text Editor](#installing-a-text-editor)
- [Installing LaTeX](#installing-latex)
- [Installing SQLite](#installing-sqlite)
- [Installing Make](#installing-make)
- [Installing Pandoc](#installing-pandoc)
- [Installing Docker](#installing-docker)
- [Useful Terminal Commands](#three-useful-terminal-commands)
- [Documentation](#documentation)
- [Troubleshooting](#troubleshooting)


## GitHub Enterprise

For us to add you to the MDS organization on [Github.ubc.ca](https://github.ubc.ca) we need you to login using your CWL:

visit [Github.ubc.ca](https://github.ubc.ca) to do this.

This step is required for
- being able to store your work
- all homework submission and grading
- working collaboratively

Your next lecture and lab in this course will be a full tutorial on using Git and GitHub.

**Take a screenshot once you have logged in to "prove" you did this!**

## git

We will be using the command line version of git.


#### Mac Users
Open Terminal and run the command:
```$ xcode-select --install```
This will install git and many other very useful applications as well (including Make).


#### Ubuntu Users
On Ubuntu, open terminal (for me, terminal is on the left-hand pane on Desktop) and install git using your system package manager (yum, apt-get, etc):

```
$ sudo apt-get install git
```



#### Windows Users
Go to http://git-scm.com. Click on the download link,and accept all defaults in the installation process.
installing git will also install for you a minimal unix environment with a "bash" shell and terminal window. Voila, your windows computer is transformed into a unixy form.

#### Testing git installation

Mac/Linux Users need to open Terminal and Windows users should open Git Bash.

Mac Users can go to Applications --> Utilities folder, and then open Terminal.

Linux Users should open Terminal from their desktop side bar or by pressing ``` ctrl + alt + t ```

Windows users can open Git Bash by searching for it from their start menu.

Run ``` git --version ```(on terminal if on Mac/Linux, on Git Bash if on Windows). If you are returned the version of git, it means your install was successful!

**Take a screenshot of the successful output of `git --version` to "prove" you correctly installed Git**

## Getting and Installing Python

We will be using Python for a large part of the program, including many popular 3rd party Python libraries for scientific computing. [__Anaconda__](https://docs.continuum.io/) is an easy-to-install bundle of Python and most of these libraries. We __strongly recommend__ that you use Anaconda for this program. If you insist on using your own Python setup instead of Anaconda, we will not be able to provide the same level of support with installation.

For this program we are using __Python 3__ , not __Python 2__, so please choose the Anaconda versions that include Python 3.5

#### Mac/Linux Users

1. Head to https://www.continuum.io/downloads and download the Anaconda version for Mac OS with Python 3.5.
2. Follow the instructions on that page to run the installer.

If you already have installed Anaconda at some point in the past, you can easily update to the latest Anaconda version by updating conda, then Anaconda in terminal as follows:
```
    conda update conda
    conda update anaconda    
```


3. Test out the Jupyter notebook: open a Terminal window, and type ```jupyter notebook```. Or use the Anaconda Launcher which might have been deposited on your desktop. A new browser window should pop up.



#### Windows Users

1. Head to https://www.continuum.io/downloads and download the Anaconda version with Python 3.5.
2. Follow the instructions on that page to run the installer
3. Test out the Jupyter notebook: open Git Bash, and type ```jupyter notebook```. Or use the Anaconda Launcher which might have been deposited on your desktop. A new browser window should pop up.


### __Running Jupyter Notebook__

The Jupyter notebook is an application to build interactive computational notebooks.

When you open Jupyter, you should see a page similar to this:

![first_time](/img/installation/settingup.JPG)

To create a new notebook go to *New -> Python 3*.

Notebooks are composed of many "cells", which can contain text  or code (like the one below). Create a cell like the one below, and evaluate the python code by clicking the "play" button above, or by hitting ```Ctrl + enter```

![](/img/installation/settingup1.JPG)

Now go to *Insert -> Insert New Cell Below* and run the following code in this new cell:
```
import numpy
import scipy
import matplotlib
```

![](/img/installation/settingup2.JPG)


numpy, scipy and matplotlib are some of the important libraries that come with Anaconda that we will be using. Now instead of using ```Ctrl + enter ``` to run your code, try ```shift + enter```. Using this, Jupyter will run your code *and* create a new cell automatically. If this code runs successfully, you should have a successful installation of Anaconda!

**Take a screenshot of the successful opening of a Python kernel in the Jupyter notebook to show you correctly installed Anaconda**

## Installing R and RStudio

#### Mac Users
1. Go [here](https://cran.r-project.org/bin/macosx/) and download the latest version of R for Mac. Open the file.
2. Chose and download the Mac version of RStudio from https://www.rstudio.com/products/rstudio/download/preview/. Open and run the installer.
3. Download XQuartz from [here](https://www.xquartz.org/). Run the ```.dmg``` file.
4. We will also be installing IRKernel to be able run R code inside of Jupyter. Open terminal and type ```R```
5. Now run the following commands:
```
install.packages(c('repr', 'IRdisplay', 'crayon', 'pbdZMQ', 'devtools', 'stringr'), repos="http://cran.stat.sfu.ca/")
devtools::install_github('IRkernel/IRkernel')
IRkernel::installspec()
```


#### Ubuntu Users

1. Go to ```~etc/apt/``` and click on the ```sources.list``` file. Click on `Other Software'-> 'Add'. Depending on your version of Ubuntu, add one of the following lines and then click 'Add Source':

 **Ubuntu 16.04**: `deb http://cran.rstudio.com/bin/linux/ubuntu xenial/`

 **Ubuntu 15.10**: `deb http://cran.rstudio.com/bin/linux/ubuntu wily/`

 **Ubuntu 14.04**: `deb http://cran.rstudio.com/bin/linux/ubuntu trusty/`

 **Ubuntu 12.04**: `deb http://cran.rstudio.com/bin/linux/ubuntu precise/`

2. Then, Open terminal and issue the following commands to install the latest version of R:
 ```
 $ sudo apt-get update
 $ sudo apt-get install r-base
 ```
3. Chose and download the Ubuntu version of RStudio from https://www.rstudio.com/products/rstudio/download/
4. Ubuntu users can then install the downloaded file through the Software Center.
5. We will also be installing IRKernel to be able run R code inside of Jupyter. Open terminal and type ```R```
6. Now run the following commands:
```
install.packages(c('repr', 'IRdisplay', 'crayon', 'pbdZMQ', 'devtools', 'stringr'), repos="http://cran.stat.sfu.ca/")
devtools::install_github('IRkernel/IRkernel')
IRkernel::installspec()
```
Troubleshooting: http://askubuntu.com/a/614715

#### Windows Users

1. Go [here](https://cran.r-project.org/bin/windows/base/) and download R
2. Chose and download the Windows version of RStudio from https://www.rstudio.com/products/rstudio/download/preview/
3. Open the ```.exe``` file and install RStudio

Windows users will also need to install Rtools, which will allow you to use external libraries.

1. Go to http://cran.r-project.org/bin/windows/Rtools/ and download the latest version (for me: Rtools33.exe)
2. Run the installer; if you are only interested in building packages, you can accept the defaults throughout (_recommended_).
3. Confirm and finish. You should now have a new directory C:\Rtools on your computer.
4. Test your installation: Open R/RStudio and type ```install.packages("xtable", type="source")``` at the command line. If this runs successfully, Rtools should be installed!
5. We will also be installing IRKernel to be able run R code inside of Jupyter.
6. Run the following commands in RStudio:
```
install.packages(c('repr', 'IRdisplay', 'crayon', 'pbdZMQ', 'devtools', 'stringr'), repos="http://cran.stat.sfu.ca/")
devtools::install_github('IRkernel/IRkernel')
IRkernel::installspec()
```


#### Testing R and RStudio
1.	Do whatever is appropriate for your OS to launch RStudio.

2.	Put your cursor in the pane labelled Console, which is where you interact with the live R process. Create a simple variable with code like ```x <- 2 * 4``` (followed by enter or return). Then inspect `x`  by typing ```x``` followed by enter or return. You should see the value `8` print to screen. If yes, you’ve succeeded in installing R and RStudio!

**Take a screenshot of the successful output of these commands to "prove" you correctly installed R and R Studio**


## Installing Rodeo
Rodeo is an easy-to-use Python IDE (Integrated Development Environment) based on Jupyter. Rodeo will allow us to write our Python code and run it, and comes with other data-science specific features.


#### Mac Users
1. Download Rodeo [here](https://www.yhat.com/products/rodeo/downloads). If your download doesn't start automatically, download the Mac version.
2. Double-click the Rodeo-mac.dmg file you downloaded.
3. Drag the Rodeo app icon to your Applications folder.
4. Double-click the Rodeo icon in your Applications folder.

#### Linux Users
1. Download Rodeo [here](https://www.yhat.com/products/rodeo/downloads). If your download doesn't start automatically, select the appropriate(32-bit or 64-bit) version for Linux.
2. Unzip Rodeo into your applications directory (i.e. ```~/bin/```).
3. Add the ```Rodeo``` command to your path, then execute it to start Rodeo!

You can also execute the following commands in terminal instead:
```
wget -O tmp.zip https://www.yhat.com/products/rodeo/downloads/linux_64
sudo unzip tmp.zip -d /usr/local/bin/ && rm tmp.zip
sudo ln -s /usr/local/bin/Rodeo-linux-x64/Rodeo /usr/local/bin
```
Change 64 to 32 in the first and last command if you have a 32-bit system.

#### Windows Users
1. Download Rodeo [here](https://www.yhat.com/products/rodeo/downloads). If your download doesn't start automatically, select and download the appropriate (32-bit or 64-bit) Windows version.
2. Open the installer and install with defaults.
3. Launch Rodeo from your start-menu (or where you installed it).

**Open Rodeo by clicking on the program in your filesystem and take a screenshot of it successfully opening to "prove" you correctly installed Rodeo**

## Installing a Text Editor
We need a text editor to be able to write complete applications. We will be using the open-source editor Atom.

### Atom Installation

#### Mac Users

Download ```atom-mac.zip ``` from 'Downloads' under the [latest release](https://github.com/atom/atom/releases).

Atom will automatically update when a new release is available.

#### Ubuntu Users
Currently __only a 64-bit version__ is available.

Download ```atom-amd64.deb``` from the [Atom releases page](https://github.com/atom/atom/releases).
Run ```sudo dpkg --install atom-amd64.deb``` on the downloaded package.
Launch Atom using the installed atom command.
The Linux version does not currently automatically update so you will need to repeat these steps to upgrade to future releases(don't worry about this for now!).

#### Other Linux-Based Systems

Follow the instructions [here](https://github.com/atom/atom#red-hat-linux-fedora-21-and-under-centos-red-hat)

#### Windows Users

Download  [Atom installer](https://github.com/atom/atom/releases) ```AtomSetup.exe``` from 'Downloads' under the latest release.

Atom will automatically update when a new release is available.

You can also download an ``` atom-windows.zip``` file from the releases page. The .zip version will not automatically update.

Using chocolatey? Run cinst Atom to install the latest version of Atom.

#### Testing Atom's install
Open a terminal/Git Bash instance and type `atom`. The Atom text editor should open to an empty file.

**Take a screenshot of the successful opening of the Atom text editor after you called it from the terminal/Git Bash to prove you correctly installed it.**

## Installing LaTeX

#### Mac Users
Mac Users have two options. You can either download the full MacTeX package, or the significantly smaller BasicTeX package which only installs the necessary files for this program.

Option 1:

1. Download the MacTeX package from [here](http://tug.org/cgi-bin/mactex-download/MacTeX.pkg)
2. Install the downladed ```.pkg``` file, following default options.

Option 2:

1. Download the BasicTeX package from [here](http://tug.org/cgi-bin/mactex-download/BasicTeX.pkg ).
2. Open the ```.pkg``` file and run the installer with default options.
3. BasicTeX has a few missing files we'll need. To install these files, open terminal and run:
```
$ sudo tlmgr update --self
$ sudo tlmgr install framed
$ sudo tlmgr install titling
```

#### Ubuntu Users
1. Run ``` apt-get install texlive```

#### Other Linux Systems
1. Download [this](http://mirror.ctan.org/systems/texlive/tlnet/install-tl-unx.tar.gz) ```tar.gz``` file.
2. Unpack the archive.
3. In terminal, switch to the directory of the unpacked file and run the command: `install-tl`
4. After the installation finishes, you must add the directory of TeX Live binaries to your PATH. For example:
  PATH=/usr/local/texlive/2016/bin/i386-linux:$PATH

#### Windows Users
1. Download the installer from [here](http://mirror.ctan.org/systems/texlive/tlnet/install-tl-windows.exe)
2. Run the ```.exe``` file and proceed the installation with default options.

#### Testing LaTeX's install
Open a terminal/Git Bash instance and type `latex --version`. If you install was successful, you should see output regarding the version and copyright of the program.

**Take a screenshot of the successful output from `latex --version` to prove you correctly installed it.**


## Installing SQLite

#### Mac Users
SQLite should already be installed on your Mac. To verify this, type `sqlite3` into your Terminal. You should see the output below.
```
$ sqlite3
SQLite version 3.13.0 2016-05-18 10:57:30
Enter ".help" for usage hints.
Connected to a transient in-memory database.
Use ".open FILENAME" to reopen on a persistent database.
sqlite>
```

Type `.quit' to exit.

If for some reason SQLite is not already installed, follow the instructions [here](http://www.tutorialspoint.com/sqlite/sqlite_installation.htm)

#### Ubuntu Users
In terminal, run:
```
sudo apt-get update
sudo apt-get install sqlite3 libsqlite3-dev
```


#### Windows Users
1. Download [this](https://github.com/swcarpentry/windows-installer/releases/download/v0.3/SWCarpentryInstaller.exe) file and run the installer. This will also install other useful applications, including Make.

### Testing SQLite's install
Open a terminal/Git Bash instance and type `sqlite3 --version`. If you install was successful, you should see output regarding the version of the program.

**Take a screenshot of the successful output from `sqlite3 --version` to prove you correctly installed it.**


## Installing Make
We will be using Make to automate our analysis scripts. More on this later!

#### Mac Users

You should have this installed if you ran the command ```xcode-select --install``` from the Git instructions.

#### Ubuntu Users

Open terminal and run ``` sudo apt-get install build-essential ```


#### Windows Users
If you installed the [Software Carpentry Installer](https://github.com/swcarpentry/windows-installer/releases/download/v0.3/SWCarpentryInstaller.exe) from the SQLite instructions above, you should have Make already installed.

### Testing Make's install
Open a terminal/Git Bash instance and type `make --version`. If you install was successful, you should see output regarding the version and copyright of the program.

**Take a screenshot of the successful output from `make --version` to prove you correctly installed it.**

## Installing Pandoc

#### Mac Users

Download and install the ```.pkg``` file for the most recent version listed on [this](https://github.com/jgm/pandoc/releases) page.

#### Ubuntu Users

Open terminal and run:
```
sudo apt-get install pandoc
```

#### Windows Users

Download and install the ```.msi``` file for the most recent version listed on [this](https://github.com/jgm/pandoc/releases) page.

### Testing Pandoc's install
Open a terminal/Git Bash instance and type `pandoc --version`. If you install was successful, you should see output regarding the version of the program.

**Take a screenshot of the successful output from `pandoc --version` to prove you correctly installed it.**

## Installing Docker

#### Mac Users
1. Download the Docker for Mac ```.dmg``` file from [here](https://download.docker.com/mac/beta/Docker.dmg)
2. Double-click ```Docker.dmg``` to open the installer, then drag the folder to your Applications folder (Note:You will be asked for your password for authorization, please provide it).
3. Open ```Docker.app``` to start Docker. You should see a Whale icon in your top status bar
4. **To confirm that Docker installed correctly, open terminal and run
```docker --version```**

This should output the version of Docker you installed.

*note - if your Mac does not meet the requirements listed below, then please [install Docker Toolbox](https://www.docker.com/products/docker-toolbox) instead of Docker for Mac

**Docker for Mac requirements:**
- Mac must be a 2010 or newer model, with Intel’s hardware support for memory management unit (MMU) virtualization; i.e., Extended Page Tables (EPT)
- OS X 10.10.3 Yosemite or newer
- At least 4GB of RAM
- VirtualBox prior to version 4.3.30 must NOT be installed (it is incompatible with Docker for Mac). Docker for Mac will error out on install in this case. Uninstall the older version of VirtualBox and re-try the install.

**If you install Docker for Mac, you may have to start Docker using the Docker Quickstart Terminal to launch it. You can take a screenshot of the resulting terminal from this action (it should have a cartoon of a whale on it) to indicate you sucessfully installed it.**

#### Ubuntu Users

Open Terminal and run the following commands:

```
 $ sudo apt-get update
 $ sudo apt-get install apt-transport-https ca-certificates
 ```

 ```
 $ sudo apt-key adv --keyserver hkp://p80.pool.sks-keyservers.net:80 --recv-keys 58118E89F3A912897C070ADBF76221572C52609D
```
Chose one of the following commands based on your Ubuntu version:

On Ubuntu Precise 12.04 (LTS)

```$ echo 'deb https://apt.dockerproject.org/repo ubuntu-precise main' | sudo tee -a /etc/apt/sources.list.d/docker.list```

On Ubuntu Trusty 14.04 (LTS)

```$ echo 'deb https://apt.dockerproject.org/repo ubuntu-trusty main' | sudo tee -a /etc/apt/sources.list.d/docker.list```


On Ubuntu Wily 15.10

```$ echo 'deb https://apt.dockerproject.org/repo ubuntu-wily main' | sudo tee -a /etc/apt/sources.list.d/docker.list```

Ubuntu Xenial 16.04 (LTS)

```$ echo 'deb https://apt.dockerproject.org/repo ubuntu-xenial main' | sudo tee -a /etc/apt/sources.list.d/docker.list```

Update your ```APT``` package index:

```$ sudo apt-get update```

Then,
On Ubuntu 14.04, 15.10, 16.04, run:
```$ sudo apt-get install linux-image-extra-$(uname -r)```

On Ubuntu 12.04, run:
```
$ apt-get install linux-image-generic-lts-trusty
$ sudo reboot
```

Install Docker with:
```$ sudo apt-get install docker-engine```

Start Docker:
```$ sudo docker run hello-world```

**Verify that Docker was installed:**
```$ sudo docker run hello-world```
This installs an image and runs it in a docker container. You should expect output similar to:
```
$ sudo docker run hello-world
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
c04b14da8d14: Pull complete
Digest: sha256:0256e8a36e2070f7bf2d0b0763dbabdd67798512411de4cdcf9431a1feb60fd9
Status: Downloaded newer image for hello-world:latest

Hello from Docker!
This message shows that your installation appears to be working correctly.

**Take a screenshot of this message to show you correctly installed Docker**

#### Windows Users

1. [Download and install Docker for Windows](https://docs.docker.com/docker-for-windows/)
2. Open the installer and install with the default options.
3. **To verify that Docker was correctly installed. run the following command in this terminal:
```docker --version```
This should output the version of Docker you installed. Take a screenshot of this.**

*note - if your Windows does not meet the requirements listed below, then please [install Docker Toolbox](https://www.docker.com/products/docker-toolbox) instead of Docker for Windows

**Docker for Windows requirements:**
- 64bit Windows 10 Pro, Enterprise and Education (1511 November update, Build 10586 or later). In the future we will support more versions of Windows 10.
- The Hyper-V package must be enabled. The Docker for Windows installer will enable it for you, if needed. (This requires a reboot).

**If you install Docker for Windows, you may have to start Docker using the Docker Quickstart Terminal to launch it. You can take a screenshot of the resulting terminal from this action (it should have a cartoon of a whale on it) to indicate you sucessfully installed it.**

## Three Useful Terminal Commands (optional)


You can use the terminal to navigate through your computer’s file system and run various applications. Windows users should use Git Bash(search for it in Start Menu), while Mac/Linux Users should open their terminals. Here are some useful commands that you should be familiar with(try them out!):

- ```pwd```  - shows the path of your current directory (i.e. tells you where you are)
on Windows, the terminal prompt contains the path of your current directory
- ```ls``` shows what is in the current directory
- ```cd <directory or path> ``` - change directory to the specified directory (**NOTE**: the use of the greater than and less than signs are meant to indicate that you need to type in whatever directory or path you want to go to. You should not literally type in these symbols into the terminal)
	-	```cd ..``` goes up one level, to the parent folder
	- *extra tip*: TAB does autocomplete for file names (start typing the name of a file/folder and press TAB before you finish typing)
 	- You can use the symbol ```~```as shorthand for your home directory. So for example ```cd ~/Desktop``` will probably get you to your desktop if you're on Mac/Linux. **Note**: This references an *absolute* path rather than a *relative* path -- it points directly to your home directory regardless of what directory you are currently in, rather than some place relative to the current directory you are in. The rest of the time when you use cd to navigate around you are usually specifying relative paths (path relative to where you are right now).

1.	Chose a folder where you want to save your work for this assignment.
2.	Open Atom, and write the following code:
```print test successful!``` and then go to *File -> Save As* and save the file with the extensiion ```.py``` in the directory you chose. For example, I saved the file as *test.py*.  

3.	Now, in terminal, navigate to that folder using the commands you learned above.
4.	Once you are there, type:
```python <program name>.py ```. In this case, we type ```python test.py```. You should now see ```test successful!``` in your terminal.

You can do a lot more with a terminal. See software carpentry's [resources](http://swcarpentry.github.io/shell-novice/) on this.


## Documentation

The following resources will be very helpful in explaining how to work with the required languages and environments.

- [Python 3.5](https://docs.python.org/3/)
- [Jupyter Notebook](http://jupyter.readthedocs.io/en/latest/)
- [R](http://www.rdocumentation.org/)
- [RStudio](https://support.rstudio.com/hc/en-us/categories/200035113-Documentation)
- [Atom](https://atom.io/docs)
- [Useful UNIX commands](http://mally.stanford.edu/~sr/computing/basic-unix.html)
- [TeX Live](https://www.tug.org/texlive)
- [Docker](https://www.docker.com)

## Troubleshooting

A lot of troublshooting questions are answered on [Stack Overflow](http://stackoverflow.com/). We encourage you to use Stack Overflow throughout the program.


## Attributions
* [Harvard CS109](http://cs109.github.io/2015/)
* [UBC STAT 545](http://stat545.com/packages01_system-prep.html#mac-os-system-prep) licensed under the [CC BY-NC 3.0](https://creativecommons.org/licenses/by-nc/3.0/legalcode).
