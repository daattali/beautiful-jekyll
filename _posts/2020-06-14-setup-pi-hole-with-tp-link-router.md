---
layout: post
title: How to setup pi hole with a TP Link router
image: /img/hello_world.jpeg
---

What is a pi-hole? A pi-hole is a network-level advertisement and Internet tracker blocking application.
https://en.wikipedia.org/wiki/Pi-hole

Setting up a pi hole is a really fun and easy project if you want to start learning how to use the raspberry pi for really 
useful stuff, like blocking ads and malicious links that can install malware onto your computer. My pi hole also blocks 
the annoying youtube ads that pop-up at the bottom of your video that you have to x out of.

<div class="text-center">
  <img src="{{ 'img/Screen Shot 2020-06-14 at 12.32.59 PM.png' | relative_url }}" />
</div>


The installation of pi-hole is easy, but I ran into some difficulties of getting the pi-hole to work with my TP Link Archer C6 router and raspberry pi zero w. In this post, I am going to talk about how to make sure your router pushes the traffic through your rasperry pi,  so the pi-hole can do it's job and filter all the ads and internet trackers. I will briefly go over how to install the pi-hole, but I would suggest using other great tutorials on the internet to help you install pi hole. 

It is essentially a one line code:
```curl -sSL https://install.pi-hole.net | bash```

You will need to click through some options and pick an upstream DNS provider. I picked Quad9, but any provider will do.

Once installation is complete and you have rebooted (I suggest doing so.
