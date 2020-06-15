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


The installation of pi-hole is easy, but I ran into some difficulties of getting the pi-hole to work with my TP Link Archer C6 router (I am using a Raspberry Pi Zero W). In this post, I am going to talk about how to make sure your router pushes the traffic through your rasperry pi,  so the pi-hole can do it's job and filter all the ads and internet trackers. I will briefly go over how to install the pi-hole as well.

It is essentially a one line code:
```curl -sSL https://install.pi-hole.net | bash```

You will need to click through some options and pick an upstream DNS provider. I picked Quad9, but any provider will do. Make sure to write down your Raspberry Pi's ip address as you will need this when we adjust the router settings.

Once installation is complete and you have rebooted your raspberry pi, you will need to update your DNS settings in the TP Link router settings. To access your router settings, type "192.168.0.1" into your URL bar. Log in to your router and click on "Advanced Settings". In the left hand panel, click on "Network" and then click on "DHCP Server". 

In this screen, you should see Primary DNS and Secondary DNS. Enter your raspberry pi's IP address here and click "Save". You can test if the pi-hole is working by visiting this page: https://ads-blocker.com/testing/

If you want to block the Youtube ads using the pi-hole (note: this will not block the video ads. Only the in-video pop-up ads.
Go to pi.hole and login. Click on "Blacklist" and type in "youtube.com".

Enjoy an ad-free internet!

<script data-ad-client="ca-pub-2898027545206399" async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
