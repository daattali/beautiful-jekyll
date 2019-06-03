---
layout: post
title: Installing X2go server for i3
tags: [notes, roadwarrior]
comments: true
---

I tried to follow [this guide](https://cepa.io/2018/08/05/building-an-ultimate-remote-linux-workstation/) for creating a remote Linux workstation on a VPS. 

Here's how I modified the guide and dealt with errors.

# X2Go Server configuration

First, I installed i3 instead of xfce4:

~~~
apt install i3
~~~

Next, I created an `~/.xinitrc`:

~~~
#!/bin/sh
exec i3
~~~

and made it executable with `chmod +x ~/.xinitrc`.

Next, I copied over the default i3 config file:

~~~
cp /etc/i3/config ~/.config/i3/config
~~~

I made sure to start x2go on my server:

~~~
service x2goserver start
~~~

I edited `~/.profile`. I commented out the last line which said `mesg n || true` and replaced it with `tty -s && mesg n`. Activate it with `source .bashrc`.

# X2Go client configuration

For the session type, I selected "Custom desktop" and for the command I put `/usr/bin/i3`.

Frustratingly, I still had issues with the ssh keys.

I had some issues, though. I would be able to ssh into my host through the cli, but whenever I tried to connect via the x2go client it would prompt me for the password 3 times and throw an error, 

~~~
Access denied. Authentication that can continue:
publickey
~~~

Finally, the solution was to delete the X2go session entry and retype the information from scratch.
