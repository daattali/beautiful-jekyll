---
layout: post
title:  "Make my Terminal pretty"
date:   2017-10-03
categories: posts
author: devonorourke
tags: 'computery'
---

# Why modify? Because it's cool, that's why.
- Do you use a Mac? If yes, continue. If no, ... well [you](https://media.giphy.com/media/ARj2OMThsPoAw/giphy.gif) get nothing, you lose, good day sir.  
- Do you use Terminal? If yes, continue. If no, [try here](http://mac.appstorm.net/how-to/utilities-how-to/how-to-use-terminal-the-basics/).  
- Do you hate the Terminal default parameters and [the available alternatives](http://osxdaily.com/2011/05/02/change-the-appearance-of-terminal-windows-quickly/)? If yes, continue!  

So what's this about? Really it's about me not liking the color palette of my Terminal and wanting to change two basic features:  
1. Get access to a much larger set of potential color palettes to use within Terminal.  
2. Specify the colors in the output of a few commands like `grep` and especially `ls`. It turns out this is way easier with Linux than with Mac, which, well, of course.  

Let's deal with each of these separately...  

## Get a big palette
There are a lot of sites out there that will help you generate a suite of custom colors. I wanted to be as simple as possible and not design any of them myself, rather, just look through a list of these custom palettes and pick which one (or ten) I wanted. [This color editor](https://github.com/lysyi3m/osx-terminal-themes) does exactly that, and because it's through a Git repository it's very straightforward to implement. Install directions are right on the README.md page but I didn't follow them exactly. Here's what I did instead:  

**Step 1** - scroll through the main page and find a palette you like. Remember the name. I liked [this one](https://github.com/lysyi3m/osx-terminal-themes#birdsofparadise) because apparently I subconsiously wish I went to Tufts given that color scheme...  

**Step 2** - Open up your Terminal program and clone the repo as follows:

*Side note: I have a generic `gitstuff` subdirectory within `My Documents` to pace cloned repos for little projects just like these... that's used in the example below*  
```
cd $HOME/Documents/GitStuff/
git clone https://github.com/lysyi3m/osx-terminal-themes.git
```

**Step 3** - Continue using terminal to find the path to the file you want specifically. Remember the name from **Step 1**?  
```
cd $HOME/Documents/GitStuff/osx-terminal-themes/schemes
pwd
```

**Step 4** - Click on the "Terminal" icon and open up `Preferences`. There are four main icons across the top of the Preferences window - click on the one labeled `Profiles`. From that Profiles window, click on the gear-shaped icon at the bottom (often called a `settings` icon in a lot of software), then click "*import*". From that point you just navigate to whatever directory your output of the `pwd` command generated from **Step 3** and select the file name you wanted from **Step 1**. This should generate a new icon in that *Profiles* window and you can click on the `Default` icon right next to the gear you clicked on previously to make this new color scheme the one that you get every time you open the Terminal program (otherwise you just need to go into *Preferences* and select it each time).  
