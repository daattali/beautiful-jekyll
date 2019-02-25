---
layout: post
title: Speed up PowerCLI
DATE: ''
date: 2019-02-25 11:27:32 +0100

---
A few weeks ago while working on a Nagios integration to monitor Horizon View. I ran into a problem where my script would time out after 60 seconds, very annoying. It made me notice that the server running the scripts was very slow in PowerShell.

After checking out google I came across this [blog by Alan Renouf](http://www.virtu-al.net/2010/07/05/speed-up-powercli/) stating that servers with no access to internet may experience slowness in PowerShell due to the internet explorer settings. Here is the procedure to follow:

1. Start Internet Explorer
2. Go to the Tools menu
3. Go to Internet Options
4. Go to the Advanced tab and uncheck “Check for publisher’s certificate revocation” so there is no tick in the box.

![](/img/checkrevoc.JPG)

After this quick fix my command went from over 60 seconds to 18 seconds. 