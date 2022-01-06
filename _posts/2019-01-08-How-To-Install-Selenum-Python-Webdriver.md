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


# See Yaaa, Next 

![Selenium with Python](/img/selenium-with-python.png "Selenium with Python")
