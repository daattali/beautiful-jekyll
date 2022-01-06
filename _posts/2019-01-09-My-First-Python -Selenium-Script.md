---
layout: post
title: Our First Scipt With Selenum Python Webdriver - Day 09   
subtitle: Software Test Automation with Selenium & Python - 30 Minutes A Day Challenge
tags: [python tutorial, python tips, selenium, python, webdriver, python selenium webdriver]
image: /img/selenium-with-python.png
bigimg: /img/back.gif
share-img: /img/selenium-with-python.png
---

## Hello Again !
{: .box-note}

Today we're going to run our first Selenium web testing with Selenium Python web bindings. 
If you have already installed Selenium Python bindings, you can start Web Automation Testing  using your Python IDE.

```py 

from selenium import webdriver
from selenium.webdriver.common.keys import Keys

driver = webdriver.Firefox()
driver.get("http://www.python.org")
assert "Python" in driver.title
elem = driver.find_element_by_name("q")
elem.clear()
elem.send_keys("pycon")
elem.send_keys(Keys.RETURN)
assert "No results found." not in driver.page_source
driver.close()

```

* This code snippet is collected from official Selenium Python Document 

The above script can be saved into a file (eg:- python_org_search.py), then it can be run like this:

```
python python_org_search.py

```

## Example Explained
The selenium.webdriver module provides all the WebDriver implementations.
Currently supported WebDriver implementations are Firefox, Chrome, IE and Remote. 
The Keys class provide keys in the keyboard like RETURN, F1, ALT etc.

```py

from selenium import webdriver
from selenium.webdriver.common.keys import Keys

```
Next, the instance of Firefox WebDriver is created.

```py
driver = webdriver.Firefox()

```
*You can change the browser from webdriver as you need*
The driver.get method will navigate to a page given by the URL.
WebDriver will wait until the page has fully loaded (that is, the “onload” event has fired) before returning control to your test or script.
It’s worth noting that if your page uses a lot of AJAX on load then WebDriver may not know when it has completely loaded.:

```py
driver.get("http://www.python.org")

```

The next line is an assertion to confirm that title has “Python” word in it:

```py
assert "Python" in driver.title

```

WebDriver offers a number of ways to find elements using one of the find_element_by_* methods. For example,
the input text element can be located by its name attribute using find_element_by_name method.

```py

elem = driver.find_element_by_name("q")

```

Next, we are sending keys, this is similar to entering keys using your keyboard. Special keys can be sent using Keys class imported from selenium.webdriver.common.keys. 
To be safe, we’ll first clear any pre-populated text in the input field (e.g. “Search”) so it doesn’t affect our search results:

```py

elem.clear()
elem.send_keys("pycon")
elem.send_keys(Keys.RETURN)

```

After submission of the page, you should get the result if there is any.
To ensure that some results are found, make an assertion:

```py

assert "No results found." not in driver.page_source

```
Finally, the browser window is closed. You can also call quit method instead of close. 
The quit will exit entire browser whereas close` will close one tab, but if just one tab was open, by default most browser will exit entirely.:

```py

driver.close()

```
# See Yaaa, Next 

![Selenium with Python](/img/selenium-with-python.png "Selenium with Python")

