---
layout: post
title:  "Python String Formatting and Printing"
date:   2021-12-26 09:53:00 AM
categories: Python
---

Python has a very easy and nice way of printing text any stream like Stdout/file stream etc.  You can easily create some quick nice tabular output and push to file.

print provides an argument where you can specify the stream you want to write to. By default it will write to the StdOut stream.

To read more about python [formatting check](https://pyformat.info)


<p><a href="https://mybinder.org/v2/gh/loneshark99/PythonNotebooksCollection/HEAD?filepath=Python_String_Formatting_And_Print_Redirection.ipynb"><img alt="Binder" src="https://mybinder.org/badge_logo.svg" /></a></p>
<div><a href="https://github.com/loneshark99/PythonNotebooksCollection/blob/main/Python_String_Formatting_And_Print_Redirection.ipynb">GitHub Link</a></div><span class="annotator-hl"></span>


```python
lists = [
            ["Stock", "Count", "Price"],
            ["AA",100,32.20],
            ["IBM",50,91.10],
            ["CAT",150,83.44],
            ["MSFT",200,51.23],
            ["IBM",100,70.44]
        ]

# Template to print out the result
template = '{:>5s} | {:>5d} | {:>5.1f}'
for index, items in enumerate(lists):
    if index != 0:
        print(template.format(items[0], items[1], items[2]))

# Redirect the printout to a file using print command
with open("Output.txt", "w") as f:
    for index, items in enumerate(lists):
        if index != 0:
            print(template.format(items[0], items[1], items[2]), file=f)
        else:
            print('{:>5s} | {:>5s} | {:>5s}'.format(lists[0][0], lists[0][1], lists[0][2]), file=f)
```

One of the cool and powerful function in python is print. If you have a list and sometimes we want to print the list item on each line. Print makes this pretty easy by combining it with destructuring and adding a separator as a new line.

```python
from fnmatch import fnmatch
addresses = [
    "5412 W CLARK ST",
    "1060 W ADDISON ST",
    "4802 N BROADWAY"
]

streets = [address for address in addresses if fnmatch(address, "* ST")]
print(*streets, sep="\n", end="\n")
```

Some other cool stuff in python are documented in this notebook. 


<p><a href="https://mybinder.org/v2/gh/loneshark99/PythonNotebooksCollection/HEAD?filepath=Jupyter_Notebook_String_Tips_and_Tricks.ipynb"><img alt="Binder" src="https://mybinder.org/badge_logo.svg" /></a></p>
<a href="https://github.com/loneshark99/PythonNotebooksCollection/blob/main/Jupyter_Notebook_String_Tips_and_Tricks.ipynb" target="_blank">GitHub Link</a>


Thanks