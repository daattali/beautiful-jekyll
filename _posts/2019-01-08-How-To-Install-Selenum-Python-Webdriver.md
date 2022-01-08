---
layout: post
title: How To Install Selenum Python Webdriver - Day 08   
subtitle: Software Test Automation with Selenium & Python - 30 Minutes A Day Challenge
tags: [python tutorial, python tips, selenium, python, webdriver, python selenium webdriver]
image: /img/selenium-with-python.png
bigimg: /img/back.gif
share-img: /img/selenium-with-python.png
---

## Hello Again, 


## Selenium Python bindings provides a simple API to write functional/acceptance tests using Selenium WebDriver.
Most of the Python Selenium libraries are very similar to Selenium .Net or Java libraries. 

Selenium Python bindings offers developers and QA engineers  a convenient API to access Selenium WebDrivers like Firefox, Ie, Chrome, Remote etc.
The current supported ``` Python versions are 2.7, 3.4, 3.5, 3.6 and 3.7. ```

To use Python Selenium bindings, you need to install Python language and Python Selenium bindings. This articles explains how to install Python Selenium bindings in Windows environment.

How To Install Selenium Python Webdriver
# Step 1: Install Python 3.6 using the Windows binary installer package.
If you are using 32bit windows, download this package ``` "Python 3.6.0 Windows x86 MSI Installer" ``` and install it.
For 64 bit windows, download and install the package ``` "Python 3.6.0 Windows X86-64 MSI Installer". ```

# Step 2: 
python is installed at ``` C:\Python34 ``` folder by default. 
Start a command prompt using the "cmd.exe" program and run the "pip.exe" command as given below to install or upgrade selenium. 

``` C:\Python34\Scripts\pip.exe install -U selenium ```
Alternatively, you can download the source distribution selenium-2.41.tar.gz , unarchive it, and run the command below:

python setup.py install
# Step 3:  
test Python and Selenium library installation. Open Python 3.6.0 Shell and type the following command.
This code will launch Google page if Python and Selenium bindings are installed correctly. 

```py
from selenium import webdriver
browser = webdriver.Firefox()
browser.get('http://www.google.com')
```
*More information can be found on Python Selenium site.*



**Selenium WebDriver** is one of the most popular tools for Web UI Automation. Selenium is an open source, and its library is available in different programming languages to perform the Web UI Automation testing, and Python is one of them.

Selenium WebDriver Client Library for Python enables us to utilize all the features available with Selenium WebDriver and interact with Selenium Standalone Server to perform Automated testing (both remote and distributed testing) of browser-based applications. So let’s start by understanding what all we have to do in UI automation testing.

_Qucik Link to Specific Topic:_

- [About Web UI Automation](#about-web-ui-automation)

# About Web UI Automation

Web User Interface (UI) Automation means the automatic execution of the actions performed in a web browser window like navigating to a website, filling forms that include dealing with text boxes, radio buttons and drop downs, submitting the forms, browsing through web pages, handling pop-ups and so on. Selenium WebDriver is the one that can automate all these tasks. It can interact with all types of Web browsers available till date like Firefox, Internet Explorer, Safari, and Chrome, etc.

The Selenium Webdriver library is compatible with a series of Python versions that includes Python 2.6, 2.7, and 3.2-3.5.

In this short series we are going to learn selenium automation with with python 3

_Here are the topics we might cover this series_

- Python Configuration & Basic Idea
- Setting up Selenium Environment With Python
- Selenium Web Element
- Methods & Properties
- Data Driven Test
- Pytest
- Automation Framework
- Small Projects
- and So on



I am really a very firm believer that the practice is the only thing and the only way to learn more questions. Please participate please practice as much as possible and never hesitate to ask questions.

More practice means better learning and software is passion. Spreading knowledge is something I really love and enjoy.

So please again welcome to the most comprehensive course on the internet.

{: .box-success}
Enjoy !!!
See Yaaa, Next.


# See Yaaa, Next 

![Selenium with Python](/img/selenium-with-python.png "Selenium with Python")
