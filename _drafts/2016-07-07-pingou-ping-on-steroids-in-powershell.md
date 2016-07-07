---
layout: post
published: false
title: 'Pingou: ping on steroids in powershell'
---
It is quite common to have to check the communication to an IP/hostname or check if a remote port is open. There already are the powershell cmdlets Test-Connection and Test-NetConnection, they are great on boxes where my profile isn't set up but they are very slow to output and lack a little bit of flexibility for an everyday use.

I took inspiration on a great script that one of my colleagues wrote "[tPing](http://www.nimbus117.co.uk/powershell/2015/07/06/tPing.html)".