---
title: "How to Open Jupyter Notebooks with a Double Click (Mac OS)"
date: "2020-01-31"
categories: ["data-science"]
author: "Sam Edwardes"
tags: ["jupyter"]
type: "post"
---

### Background

Jupyter Notebooks are an awesome tool. The standard way to open a Jupyter Notebook is from the command line. For example:

```bash
jupyter lab my_awesome_notebook.ipynb
```

This is a simple step. But sometimes it would be nice to have a quicker option to open a Jupyter Notebook file from your finder. This would save you the several seconds of opening a terminal, navigating to the correct folder, and then opening the file.

I have found a simple trick for Mac users that lets you open a `.ipynb` with a double click. The idea is to use the Mac Automator tool to create a simple application that will pass the correct commands into a bash script.

My code is just a slightly modified version of an example I found from Stack Overflow: [https://stackoverflow.com/questions/30953227/double-click-to-open-an-ipython-notebook](https://stackoverflow.com/questions/30953227/double-click-to-open-an-ipython-notebook).

### Step by Step Instructions

1. Open up Automator, click new document

   ![Imgur](https://i.imgur.com/gS9qBZi.png)


2. Click on Application

   ![Imgur](https://i.imgur.com/qkuxAw0.png)


3. Drag and drop `Run Shell Script` into the workflow area

   ![Imgur](https://i.imgur.com/ylrzvIi.png)


4. Set *Pass inputs* drop down menu to `as arguments`.

   ![Imgur](https://i.imgur.com/Ablq5mT.png)


5. Copy and paste in the code below:

   ```
   variable="'$1'"
   the_script='tell application "terminal" to do script "jupyter lab '
   osascript -e "${the_script}${variable}\""
   ```

   ![Imgur](https://i.imgur.com/DI0sOxq.png)


6. Save the file as `jupyter_lab_open` and choose *File Format* `Application`. The the file to your Applications folder.

   ![Imgur](https://i.imgur.com/0qPWZmX.png)


7. Find a Jupyter Notebook in your finder that you wish to open. Right click on the file and click on *Get Info*. Click the *Open with* dropdown menu and select `other`. Then navigate to your applications folder and select `jupyter_lab_open`. Click *Change All...* so that all `.ipynb` files when double clicked on are opened with Jupyter lab.

   ![Imgur](https://i.imgur.com/7YRp1cK.png)



Now, when ever you click on a file with extension `.ipynb` it should open up the document in Jupyter Lab.

### Full Disclosure

- There are limitations. For example if I double click on a new file it opens a whole new server instead of creating a new tab which may be preferred.
- I have only tested this on my machine, so there may be required dependencies that I am not aware of.
- Tested on MacBook Pro, macOS Catalina 10.15.2, python 3.6.7 from Anaconda.
- I welcome any comments you have on how to improve this script!