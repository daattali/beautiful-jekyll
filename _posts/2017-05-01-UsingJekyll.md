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

## My First Post

My first post is about the experience learning Jekyll, Markdown and Git Pages.   I started this expedition with
the desire to create a company website.  I did not initially intend to have a blog, instead I wanted to expand my 
knowledge of git and saw an article to create a website using Git Pages and Cloudflare.  Now I am a convert.
What a great idea.  Other than purchasing a domain at an annual fee of $20, the website is up and runnning
with no other incurred costs, only my time.  

### Following the lead

I followed the sample below and choose a theme which creates a simple page with no header and footer and then started to add features to it, like a nice header, footer and formatting.    I finally decided that was going to take too long so I forked a copy of beautiful-jekyll and started from a template that had a lot of the features I wanted already built in. 
[Setting up your website](https://medium.freecodecamp.com/an-illustrated-guide-for-setting-up-your-website-using-github-cloudflare-5a7a11ca9465) and
[Github pages](https://www.smashingmagazine.com/2014/08/build-blog-jekyll-github-pages/)

### Blogs and Pagination

This one still gets me, as soon as I moved my blog from the main page it stopped working.   Why does a page with pagination have to be called index.html. I did not really want pagingations for my posts but what I did want was to be able to filter posts.  Finally figured out how to do that and  I will come back later and figure out if I need pagination.  My insights pages filters posts with tags.  
[Pagination Rules](https://jekyllrb.com/docs/pagination/)

### You need to learn Markdown language

You can write regular [markdown](http://markdowntutorial.com/)  and Jekyll will automatically convert it to a nice webpage.  I had a hard time with this. I know quite a bit of HTML but just could not wrap my head around markdown language and some of the rules.   I encourage you to [take 5 minutes to learn how to write in markdown](http://markdowntutorial.com/) - it'll teach you how to transform regular text into bold/italics/headings/tables/etc.

### But to do really cool things you need Bootstrap

At some point you will need to learn Bootstrap CSS framework.  I wanted to have three columns on the front page and needed to understand how to do that.  This also came into play on the contact form formatting.  Markdown is ok for simple pages and text but does not really do a good job of offering solutions for nice formatting.  I also had to dig through the CSS code and change the colors to my brand colors.  
[Bootstrap](http://getbootstrap.com/css/)
[Bootstrap tutorial](http://www.tutorialrepublic.com/twitter-bootstrap-tutorial/)

### Contact forms 

I wanted to have a contact form.  This is really easy in Wordpress, but alas there is no CMS here. Fortunately there are solutions that offer you to link to a service with a snippet of javascript and a form from a post.  I chose one from http://formspree.io/

### Don't forget about images and logos

Finally images and logos for the header.  These need to be formatted correctly, sometimes with transparency.  I finally settled on [Drawsvg](http://drawsvg.org/) to do this.  I also found out that I do not need to copy images from flickr, but instead can link to them in my blog using bigimg tag.  

### Template Beautiful Jekyll

Many thanks to [Dean Attali](http://deanattali.com/beautiful-jekyll/) for Beautiful Jekyll.  It was a big step in the right direction with responsive pages and nice looking header and footers.  I do have some issues however, the header and footer seem to link to project website instead of the pretty name, and the documentation was lacking.   Also, I am not sure why you don't setup sitemap as a default.  There are little things missing, but overall it was a big help.  

### Summary

My conclusion is this is a great tool/service but not for the faint of heart or technical novice.   Without knowledge of bootstrap/CSS I think you will be disappointed with the results on the page.  Everything worked as presented here, the instructions were well written and clear, but I was looking for a nice website.    I finally did achieve the results I wanted but it took a lot of google searching and playing around with pages to get what I wanted.  

#### Other topics to add to this article

- Selecting a domain
- Buying a domain
- Cloudflare setup
- Git merge and master branch topic, don't merge to master every time
- Images, logos, brand colors.
