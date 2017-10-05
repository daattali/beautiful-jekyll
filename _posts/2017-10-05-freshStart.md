---
layout: post
title:  "Fresh install ideas"
date:   2017-10-05
categories: posts
author: devonorourke
tags: 'computery'
---


I spilled cranberry juice on my computer a few weeks ago; while I was able to recover my hard drive I used the experience to hit the reset button on the tangled web of programs I had installed. In my first few years of grad school I just installed under the philosophy of `JUST MAKE IT WORK NOW` without really knowing anything about package management software. After stumbling in the darkness for a little while I've come across a few really helpful blogs that illustrate what I think is a nice approach to the installation process of programs in general, but certainly there are tradeoffs and features that each user will find helpful and frustrating. Let's just say that this is what I've found works for me, as someone who tends to do work with a bunch of Python as well as a bunch of non-Python programs.  

I started by reading a trio of very helpful blogs by in this order:
- how to [install homebrew](https://www.davidculley.com/installing-software-via-homebrew/)  
- how to [install python](https://www.davidculley.com/installing-python-on-a-mac/) and related packages using [Homebrew](https://brew.sh)  
- how to [install a range of other software](http://tristanpenman.com/blog/posts/2015/10/20/installing-r-and-rstudio-on-mac-os-x/) - like R, R-studio, Spotify, Skype, etc.  

I then attempted to follow their instructions. What I've posted below is largely adapted from those blogs, albeit with a few caveats as things didn't always work exactly as described in those very well documented posts.  

# Part 0 - before installing Homebrew
Software installs get messy - that's why there are lots of package management software available to ease your pain. When I got started I thought the message was "*choose Conda or Homebrew*, but not both", and then realized that the choices could have also included Pip, Fink, and many others. I also didn't understand that Conda is not Python, but Pip is. [This blog](https://jakevdp.github.io/blog/2016/08/25/conda-myths-and-misconceptions/) does a great job differentiating the terminology and focus between package managers vs. distribution. In short, I've found that just about anything I need I can find using Homebrew, and anything I can't I can find using pip. There will come a day where I probably need Conda, but that day hasn't come yet...  

While you can install Homebrew first, you're better off installing the few dependencies that Homebrew wants: Apple's [Xcode software](https://developer.apple.com/xcode/). You can do that a few different ways, but I found the most straightforward way to do it was to navigate to the Mac App store and look for the software - hopefully [this link](https://itunes.apple.com/us/app/xcode/id497799835?mt=12) will point you in the right direction (if not, just search `Xcode` in the App Store). Warning - it's a huge file (about 5Gb at last glance) and will probably take you the longest amount of time to download relative to all the other programs on this post *combined*. Find some coffee or fast internet, or both.  

Once you've downloaded that software the install follows the traditional point and click graphical user interface (GUI) that we're all familiar with. However you're also going to want to **activate the Command Line Tools software** which comes with that download. I followed [this blog](http://railsapps.github.io/xcode-command-line-tools.html) for great info about making sure that (1) my Xcode software was installed properly; and (2) help me walk though the install process of the command line tools. In my case, the entirety of this process amounted to two things:

- 1) Navigate to the Mac App Store and install Xcode software  
- 2) Open up Terminal and type `xcode-select --install` to begin the ~2 minute installation/activation of the **Command Line Tools software**. You can confirm the install is working right - especially that `gcc` is installed properly - by typing `gcc --version` in the Terminal. If that prints something like below, you're ready to install Homebrew:  

```
$ gcc --version
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
Apple LLVM version 9.0.0 (clang-900.0.37)
Target: x86_64-apple-darwin17.0.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```

# Part 1 - installing Homebrew
Using [Homebrew](https://brew.sh) saves me loads of time making sure I keep packages in one place (as much as possible anyway). As mentioned above, [this blog](https://www.davidculley.com/installing-software-via-homebrew/) does a terrific job outlining the strategies employed. I've summarized what I did below, but check out that blog for the gory details.  

**install Homebrew**
Staight from their website:  
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

The blog goes on to mention adjusting your `$PATH` variable, which if you understand what that is, you probably don't need that help, and if you *don't* understand what that is, your not going to find that blog all that helpful. So you have two options if you don't know what to do:  
- 1) Change your $PATH, but you might need to create a file first! Just do this:  
  - First, open up Terminal and go to your $HOME directory.  
  - Second, create a `.profile` file  
  - Third, append the $PATH variable like is outlined in the blog.  

Or in other words, do the following using Terminal:  
```
cd $HOME 
nano .profile
```
Then save and close that program with `ctrl+x` and `y`.  
With that saved, you can append the $PATH variable to your `.profile` file as suggested in the blog:  
```
echo export PATH='/usr/local/bin:$PATH' >> ~/.profile
source ~/.profile
echo $PATH
```
You should see something like: `/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/Users/do/.local/bin:/Users/do/bin`.  

 
- 2) Don't do anything. Homebrew will work fine, but you won't be specifying to use Homebrew installed programs over other default-installed programs. Programs like *Python* or *Ruby* will probably use your default-installed versions, rendering a few Homebrew programs useless. However, most of your Homebrew programs will work, provided there isn't a redundant program already installed on your Mac.  

# Part 2 - use Homebrew to install lots of fun stuff
If all has gone well you should be able to run Homebrew to get lots of packages installed in just a few lines of code. To check that the program is working, try typing `brew --version` and see if you get a little print out with something like `Homebrew 1.x.y` (numbers instead of x and y, of course). All good? Let's install.  

**installing big stuff**
I followed along with the blog post and installed the big packages first and in this order - I've found that if you go out of order sometimes there are dependencies which can cause install problems, so I can at least verify that this order shouldn't produce those problems. You could run these one at a time but we'll install a suite of tools in one shot:   
```
brew install ruby python3 git atom xquartz
```
Note that you're installing a few pretty big programs so this can take ~15 minutes or so. What did you just install?  
- [ruby](https://www.ruby-lang.org/en/)
- [python3](https://www.python.org), but notably we didn't bother installing a fresh Python2
- [git](https://git-scm.com), because version control is awesome
- [atom](https://atom.io), because it's an amazing text editor that integrates seamlessly with git
- [xquartz](https://www.xquartz.org), which you'll want if you do anything with plotting in R (which I do!)  

**installing GUIs**  
Homebrew, like many package managers, has multiple places to look for programs. The `brew install` command is the default repository for things, but you won't always find things that you need there. For example, if you want to install a bunch of GUIs like Spotify or Skype, you need to use a different repo called `cask` - see [here for details](https://caskroom.github.io). Conveniently, it works pretty much just like the above command:  
```
brew cask install google-chrome spotify spotify skype
```
And that's it - in one line of commands you've done the same work as going to three different websites, determining which icons to click, and then going through the whole install process. Nice.  

**installing lots of other non-Python stuff**  
It turns out there are other places where Homebrew keeps programs - called **Taps** - which are typically third-party programs. There are many different Taps, and within any one Tap there can be many different programs. There are a few main taps, of which I tend to migrate to one all the time - *science*. We're going to use that Tap to install a few other programs now; again, the syntax is similar except you first have to install the Tap before installing the programs of choice:  
```
brew tap homebrew/science
```
Note that at this point we haven't actually downloaded anything with that `brew tap` command - we've just set ourselves up to install things within the *science* Tap. We'll now install R and specify using the xquartz support we already downloaded in our big install (`brew install`) above:  
```
brew install --with-x11 r
```
As mentioned in [this post](http://tristanpenman.com/blog/posts/2015/10/20/installing-r-and-rstudio-on-mac-os-x/), you can specify both the Tap and program in a single one-liner (effectively replacing two lines of code with one):  
```
brew install --with-x11 homebrew/science/r 
```
While we're on the topic of R, let's install the R-studio GUI to point an argument in the `install` command:  
```
brew cask install --appdir=/Applications rstudio
```
It turns out the *default directory* that `brew cask` installs go to is **not** your `/Applications` folder; rather, symbolic links are provided to that path, but not placed directly there. With the above command we tell brew to put the program directly in your Applications directory. Not sure why you'd want to bother, but if you need to, that's how you'd do it.  

**update, upgrade, cleanup**
It's always a good idea to make things current and avoid the creep of program versions you might not need. Homebrew has a few tools to deal with that:  
- Run `brew update && brew upgrade` whenever you want to get all the possible updates for *all* apps. However **THIS WILL NOT REMOVE OLD VERSIONS**
- Run `brew cleanup` to make sure you delete the outdated versions you don't need.  

# Part 3 - NOT using Homebrew to install Python things
Okay, I lied. We have *one last* thing to do with `brew install` before we can kick into gear with Python package installs - we need to set up some dependency software:
```
brew install pkg-config libpng freetype
```
Okay - on to Python packages. While we installed Python3 with `brew`, we didn't install any Python-specific packages. We'll use `pip3` to do just that. Why? To quote [David's post](https://www.davidculley.com/installing-python-on-a-mac/) about setting up Python installs with Brew:  
> "Bear in mind that you should install packages either via Homebrew or via pip, but never via both. Best practice is to generally prefer pip to brew for Python-specific packages and to use Homebrew only if the desired package couldn’t be installed via pip (because it’s general purpose and not Python-specific). In most cases, pip will give you a newer version than brew and works better with virtualenv."  

Because we've done quite a bit of leg work already with program installation, the following code is used to install things that I find really useful in my bioinformatic work as well as with plotting and sharing code. Notably, I'm *not* installing any Conda distribution, but just using `pip3` to get me all my Python-specific packages. Again, see [this post](https://www.davidculley.com/installing-python-on-a-mac/) for more of the gory details and considerations in this workflow.  

**pip3 installs**
Let's start by ensuring we have an updated set of `pip3` tools (remember it's pip3 because we're using Python3) - if you're doing this in order you probably have updated packages because you just installed it with the `brew install python3` command earlier... but to be safe:  
```
pip3 install --upgrade pip setuptools wheel
```

Next we'll install a suite of packages which are useful for different things, all using the `pip3 install` command in one big one-liner:
```
pip3 install virtualenv virtualenvwrapper numpy scipy matplotlib pandas sympy nose jupyter pandoc
```

So what did you just install? We'll break this into three parts - see [this post](https://www.davidculley.com/installing-python-on-a-mac/) for discussion of all programs:  
- `virtualenv` and `virtualenvwrapper` can be useful when setting up virtual environments. You probably don't need them if you don't know what they are, but you probably *will* need them as you start getting more comfortable with these tools. The [documentation for the wrapper package](https://virtualenvwrapper.readthedocs.io/en/latest/) does a nice job explaining what it does and why it's useful; [this blog](http://docs.python-guide.org/en/latest/dev/virtualenvs/) also offers some insights, though it's geared towards Python2.  
- The [SciPy](https://www.scipy.org) stack includes the programs `numpy scipy matplotlib pandas sympy`; these are all core packages used for math, science, and engineering applications. You'll find that when you're downloading other smaller programs they'll have dependencies which often include one or more of these tools.  
- Finally, I find `jupyter` to be an essential tool when documentation and executing Python code, but obviously it's as useful for R, Julia, and many other languages (that's why it's not *iPython* anymore...). When you want to export/share these files, `pandoc` makes that transition seamless. Check out info about using [Jupyter notebook](http://jupyter.org) - you can play with it's features right in the browser if you like.  
 

# Final thoughts
None of this worked for me the first time. No single blog worked exactly as it stated. My guess is these instructions won't either, but I hope that by providing a range of links you can cobble together what's needed to get through each step. Patience, persistence, and coffee.  

Good luck!
