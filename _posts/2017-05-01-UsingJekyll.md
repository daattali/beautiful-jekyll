---
layout: post
title: First Post - Using Jekyll
subtitle: My experience setting up this blog.
category:  training
tags:  [website, training]
bigimg: /img/path.jpg
img: /img/avatar-icon.png
---

My first post is about my experience learning Jekyll and Markdown.   I started this expedition by
wanting to create a company website.  I did not initially intend to have a blog, I wanted to expand my 
knowledge of git and saw an article to create a website with Git Pages and Cloudflare.  Now I am a convert.
What a good idea.  

I tried this sample which creates a very simple page with no header and footer.  I finally decided to fork
beautiful-jekyll and start from this template.  

Pagination.  This one still gets me.  Why does a page with pagination have to be called index.html. 
https://jekyllrb.com/docs/pagination/

You can write regular [markdown](http://markdowntutorial.com/) here and Jekyll will automatically convert it to a nice webpage.  I strongly encourage you to [take 5 minutes to learn how to write in markdown](http://markdowntutorial.com/) - it'll teach you how to transform regular text into bold/italics/headings/tables/etc.

And here is the same code yet again but with line numbers:

{% highlight javascript linenos %}
var foo = function(x) {
  return(x + 5);
}
foo(3)
{% endhighlight %}
