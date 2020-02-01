---
layout: post
title: How to Open Jupyter Notebooks with a Double Click (Mac OS)
tags: [data-science]
---

### Background

Jupyter Notebooks are an awesome tool. The standard way to open a jupyter notebook is from the command line. For example:

```bash
jupyter lab my_awesome_notebook.ipynb
```

This is a simple step. But sometimes it would be nice to have a quicker option to open a Jupyter Notebook file from your finder. This would save you the several seconds of opening a terminal, navigating to the correct folder, and then opening the file.

I have found a simple trick for Mac users that lets you open a `.ipynb` with a double click. The idea is to use the Mac Automator tool to create a simple application that will pass the correct commands into a bash script.

My code is just a slightly modified version of an example I found from Stack Overflow: [https://stackoverflow.com/questions/30953227/double-click-to-open-an-ipython-notebook](https://stackoverflow.com/questions/30953227/double-click-to-open-an-ipython-notebook).

### How to

1. Open up Automator, click new document
2. Click on Application
3. Drag and drop `Run Shell Script` into the workflow area
4. Set *Pass inputs* drop down menu to `as arguments`.
5. Copy and paste in the code below:

```
variable="'$1'"
the_script='tell application "terminal" to do script "jupyter lab '
osascript -e "${the_script}${variable}\""
```

6. Save the file as `jupyter_lab_open` and choose *File Format* `Application`. The the file to your Applications folder.
7. Find a Jupyter Notebook in your finder that you wish to open. Right click on the file and click on *Get Info*. Click the *Open with* dropdown menu and select `other`. Then navigate to your applications folder and select `jupyter_lab_open`.
8. Click *Change All...* so that all `.ipynb` files when double clicked on are opened with Jupyter lab.



### Full Disclosure

- There are limitations. For example if I double click on a new file it opens a whole new server intead of creating a new tab which may be prefered.
- I have only tested this on my machine, so there may be required dependenies that I am not aware of.
- Tested on MacBook Pro, macOS Catalina 10.15.2, python 3.6.7 from Anaconda