---
layout: page
title: About
---

Me
==

Find me at hectorpefo@gmail.com.


How this site works
===================

It is a [github Pages](https://pages.github.com/) site, namely, the Personal site connected with my github account.

It uses Jekyll, and in particular the Beautiful Jekyll "theme." Sounds complicated, but it's not. I created it by "cloning" the theme project's [repository](https://github.com/daattali/beautiful-jekyll), which there are simple instructions to do if you follow that link and scroll down. To make that cloned repository the Personal Site for my github account (hectorpefo) I had to name the repository hectorpefo.github.io. The personalization is straightforward, you can do everything in your browser, including writing your posts, and you don't need to worry about the background processing that turns the files into web pages; github handles all that and "re-builds" your site automatically when you make additions or changes. You write your posts in [markdown](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet), which is very simple and reasonably flexible.

I did add the ability to include $\LaTeX$ formulas in my posts, using [MathJax](https://www.mathjax.org/). Formulas can be either in-line or displayed. 

For example, the code `$\frac{1}{\sqrt{2}}$` produces: $\frac{1}{\sqrt{2}}$, and the code:

```
$$\int_{\theta = 0}^\pi \sin(\theta) d\theta$$
```

produces:

$$ \int_{\theta = 0}^\pi \sin(\theta) d\theta $$

To do that, all I had to do was to insert the following code into the file `_includes/head.html` right after the first line ("`<head>`"). 
```
    <script type="text/x-mathjax-config">
        MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}});
    </script>
    <script type="text/javascript" async
        src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS_CHTML">
    </script>
```

(You could also just clone [_my_ repository](https://github.com/hectorpefo/hectorpefo.github.io) for this site, which will give you the $\LaTeX$ functionality as well as this ABOUT page and a few other small tweaks of the Beautiful Jekyll theme.)
