---
layout: post
title: WIP - Analysing a VMWare Memory image with volatility
subtitle: Get that analysis happening
tags: [dfir,vmware]
comments: true
---

## Backround
I found recently during a CTF Memory image challenge, that analysing memory images from VMWare wasn't necesarily as easy as just having the right profile and files. Hopefully this helps anyone out there who needs to do the same. For this writeup I am using VMWare Workstation Pro v15.5.1

### VMWare File Types

`table to come`
### What I tried
First, I tried to get the vmware info with the volatility plugin, and a quick pslist with no luck

Scondly, I found [here](https://www.andreafortuna.org/2017/08/07/volatility-my-own-cheatsheet-part-7-analyze-and-convert-crash-dumps-and-hibernation-files/) that you can use raw2dmp to convert the vmemfiles, I thought it might work with volatility. I've found on ADIA foresnics appliance it seems to convert, but wont read the files and on a plain Ubuntu machine it wont even convert.

`console to come`

After this, I did some more research into how vmware files work with memory, as im sure volatility can handle it. I noted the tool by VMWare vmss2core, dealth with vmem and vmss files. As I know volatility works with vmware files, I thought I would copy just the vmss file and see if the pslist would work again. Note: `2>/dev/null` has been placed due to a error in volatility piping on my ubuntu workstation

`console to come`

Now... so analysts have the normal famililaryity with raw memory image workflow, lets see if now we can create a raw file that works with this?

`console to come`

Hazzah, now we have an imagae that analysts normally work with, just from copying some vmware files

## Takeaway points
So, hopefully now you know how to analyse VMWare Snapshots and Images, and the minimum files required by volatility. Also, if you need to traige VMWare memory images, you can now make a .raw file that DFIR teams will know how to workflow as normal, as long as they know the operating system for the Volatility profile
