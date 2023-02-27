---
layout: post
title:  "Ubuntu Wireless Card"
date:   2023-01-29 18:55:00 PM
categories: [Ubuntu]
---

I installed ubuntu on my MacBook Air a while ago and I was running into wireless connection issues. At that time when I did some digging around and found that lot of people were facing the issue with getting the wireless card setup correctly. So without much thought I came to conclusion that it was a general issue.

I ended up buying a new external wireless usb dongle and it had its own issue with the internet connection speed. I got really fed up with this issue as it was causing me to not use my Macbook Air at all until I realized that ubuntu gives you an option to install proprietary drivers. Actually came to know about this through some youtube recommended video (go figure!)

If you go to the  "Software and Update" program and in the Additional drivers section Ubuntu will list the propriety drivers that can be used based on the hardware. For me it was the broadband wireless card driver. After installing this driver everything is working as expected. 

Wish I knew this before or atleast tried to find a solution for this. I hope someone finds this and they can solve their wifi issues quickly.

![alt text][Additional Drivers]

[Additional Drivers]: https://loneshark99.github.io/images/Additional%20Drivers.png "Install additional drivers"

You can use the list hardware (lshw) command with Class as Network to view the Networking devices and the drivers used by them.

```bash
    lshw -C network
```

![alt text][lshw]

[lshw]: https://loneshark99.github.io/images/lshw%20network.png "Get info about network hardware"


!Happy Learning and improving one day at a time!
