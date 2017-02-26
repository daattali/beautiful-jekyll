---
layout: page
title: About me
---


Me
==

Find me at hectorpefo@gmail.com.


How this site works
===================

It is a [github Pages](https://pages.github.com/) site, namely, the Personal site connected with my github account hectorpefo.

It uses Jekyll, and in particular the Beautiful Jekyll "theme." 

Sounds complicated, but it's not. I created it by "cloning" the repository of https://github.com/daattali/beautiful-jekyll, which there are simple instructions to do if you follow that link. The personalization is straightforward, and you can do everything in your browser, and you don't need to worry about the background processing that turns the files into web pages; github handles all that.

One thing I did add is the ability to include $$\LaTeX$$ formulas in my posts, using [MathJax](https://www.mathjax.org/). To do that, all I had to do was to insert the following code into the file `\_includes/head.html` right after the first line ("`\<head\>`"). 
```
    <script type="text/x-mathjax-config">
        MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}});
    </script>
    <script type="text/javascript" async
        src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS_CHTML">
    </script>
```
Then I can use $$\LaTex$$ formulas either in-line or displayed. _In both cases,_ you have to use the double dollar-sign `$$` as the delimiter.
