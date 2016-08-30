---
layout: post
published: false
title: Get-VMHostQuickView - Host usage graphs in PowerShell
---
At work I spend a lot of time on PowerCLI for day to day administration as it is often much quicker to just run a command than log on the web client (wait for it to take its time), browse to where you want, wait for the interface to load... 

For that reason I wanted an easy and quick way to get an overview of my hosts' resources usage without having to log in a client or "brain process" numbers, so I wrote a little function that will display the CPU and memory usage of one or more hosts.

![Get-vmhostvisual.jpg]({{site.baseurl}}/img/Get-vmhostvisual.jpg)

I have put that function in my powercli module where I store all my vmware related functions so it's accessible anytime.

**You can download it here: [Get-VMHostQuickview.ps1](https://github.com/vxav/Scripting/blob/master/Get-VMHostQuickview.ps1)**

_Note that if you use the pipeline it will still work but the fields might not be aligned if your hostnames don't all have the same character count. as it processes them one by one_.

To call the quickview on all the hosts

```Powershell
Get-VMHostQuickView (Get-VMHost)
```

Available parameters:

```Powershell
LengthBar
	Length of the colored bars in characters
    Default 30

CPURed
	Percentage usage threshold at which the CPU bar is red
    Default 80

CPUYellow
	Percentage usage threshold at which the CPU bar is yellow
    Default 60

MEMRed
	Percentage usage threshold at which the memory bar is red
    Default 80

MEMYellow
	Percentage usage threshold at which the memory bar is yellow
    Default 60

```

