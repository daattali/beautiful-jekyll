---
layout: post
title: First Post - Using Jekyll
subtitle: My experience setting up this blog.
category:  training
tags:  [website, training]
img: /img/avatar-icon.png
use-site-title: true
bigimg:
    - "/img/big-imgs/dragons.jpg" : "Sant Jordi, 2017"
---

My first post is about the experience learning Jekyll, Markdown and Git Pages.   I started this expedition with
the desire to create a company website.  I did not initially intend to have a blog, I wanted to expand my 
knowledge of git and saw an article to create a website using Git Pages and Cloudflare.  Now I am a convert.
What a great idea.  Other than purchasing a domain at an annual fee of $20, the website is up and runnning
with no other incurred costs, only my time.  

I tried this sample and choose a theme which creates a simple page with no header and footer and then started to add features to it, like a nice header, footer and formatting.    I finally decided that was going to take too long so I forked a copy of
beautiful-jekyll and started from a template that had a lot of the features I wanted already built in. 
https://medium.freecodecamp.com/an-illustrated-guide-for-setting-up-your-website-using-github-cloudflare-5a7a11ca9465
https://www.smashingmagazine.com/2014/08/build-blog-jekyll-github-pages/

Pagination.  This one still gets me.  Why does a page with pagination have to be called index.html. I did not really
want pagingations for my posts but what I did want was to be able to filter posts.  Finally figured out how to do that and 
I will come back later and figure out if I need pagination.
https://jekyllrb.com/docs/pagination/

You can write regular [markdown](http://markdowntutorial.com/)  and Jekyll will automatically convert it to a nice webpage.  I had a hard time with this. I know quite a bit of HTML but just could not wrap my head around markdown language and some of the rules.   I encourage you to [take 5 minutes to learn how to write in markdown](http://markdowntutorial.com/) - it'll teach you how to transform regular text into bold/italics/headings/tables/etc.

At some point you will need to learn Bootstrap CSS framework.  I wanted to have three columns on the front page and needed to understand how to do that.  This also came into play on the contact form formatting.  Markdown is ok for simple pages and text but does not really do a good job of offering solutions for nice formatting.  I also had to dig through the CSS code and change the colors to my brand colors.  
http://getbootstrap.com/css/
http://www.tutorialrepublic.com/twitter-bootstrap-tutorial/

I wanted to have a contact form.  This is really easy in Wordpress, but alas there is no CMS here. Fortunately there are solutions that offer you to link to a service with a snippet of javascript and a form from a post.  I chose one from http://formspree.io/

#### Other topics to add to this article

- Selecting a domain
- Buying a domain
- Cloudflare setup
- Git merge and master branch topic
- Images, logos, brand colors.
