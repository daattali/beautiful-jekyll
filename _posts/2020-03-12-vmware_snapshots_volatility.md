---
layout: post
title: Analysing a VMWare Memory image with volatility
subtitle: Get that analysis happening
tags: [dfir, vmware]
comments: false
---

# Introduction
I found recently during a CTF Memory image challenge, that analysing memory images from VMWare wasn't necessarily as easy as just having the right profile and files. Hopefully this helps anyone out there who needs to do the same. For this write-up I am using VMWare Workstation Pro v15.5.1.

# Table-of-Contents
<a name="TOC"></a>

- [Introduction](#introduction)
- [Table-of-Contents](#table-of-contents)
    - [TLDR](#tldr)
    - [Applicable VMWare File Types](#applicable-vmware-file-types)
    - [What I tried](#what-i-tried)
  - [Takeaway points](#takeaway-points)

### TLDR
For volatility to work you need the vmem and vmss files. To get these files the VM needs to be powered on, then suspended.

[*Back to table of contents*](#TOC)

### Applicable VMWare File Types

File |	Usage |	Description
--- | --- | ---
.vmx |	vmname.vmx |	Virtual machine configuration file
.vmxf |	vmname.vmxf |	Additional virtual machine configuration files
.nvram |	vmname.nvram or nvram |	Virtual machine BIOS or EFI configuration
.vmsd |	vmname.vmsd |	Virtual machine snapshots
.vmsn |	vmname.vmsn |	Virtual machine snapshot data file
.vswp |	vmname.vswp |	Virtual machine swap file
.vmss |	**vmname.vmss** |	Virtual machine suspend file
.vmem |	**vmware.vmem** |	Virtual Machine volatile memory file

[*Back to table of contents*](#TOC)

### What I tried

First, I tried to get the vmware info with the volatility plugin, and a quick pslist with no luck

![firsttry](https://angry-bender.github.io/img/vmt/firsttry.gif)

Secondly, I found [here](https://www.andreafortuna.org/2017/08/07/volatility-my-own-cheatsheet-part-7-analyze-and-convert-crash-dumps-and-hibernation-files/) that you can use raw2dmp to convert the vmemfiles, I thought it might work with volatility. I've found on ADIA forensics appliance it seems to convert, but wont read the files and on a plain Ubuntu machine it wont even convert.

![seccondtry](https://angry-bender.github.io/img/vmt/secondtry.gif)

After this, I did some more research into how vmware files work with memory, as I'm sure volatility can handle it. I noted the tool by VMWare vmss2core, dealt with vmem and vmss files. As I know volatility works with vmware files, I thought I would copy just the vmss file and see if the pslist would work again. Note: `2>/dev/null` has been placed due to a error in volatility piping on my Ubuntu workstation

![thirdtry](https://angry-bender.github.io/img/vmt/thirdtry.gif)

Thats the first win. Now... so analysts have the normal familiarity with raw memory image workflow, lets see if now we can create a raw file that works with this?

![raw2dmptry](https://angry-bender.github.io/img/vmt/raw2dmptry.gif)

Huzzah, now we have an image that analysts normally work with, just from copying some vmware files

[*Back to table of contents*](#TOC)

## Takeaway points

So, hopefully now you know how to analyse VMWare Snapshots and Images, and the minimum files required by volatility (vmem & vmss). Also, if you need to triage VMWare memory images, you can now make a .raw file that DFIR teams will know how to workflow as normal, as long as they know the operating system for the Volatility profile

[*Back to table of contents*](#TOC)



