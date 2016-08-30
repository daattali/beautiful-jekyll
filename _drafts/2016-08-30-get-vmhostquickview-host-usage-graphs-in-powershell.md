---
layout: post
published: false
title: Get-VMHostQuickView - Host usage graphs in PowerShell
---
At work I spend a lot of time on PowerCLI for day to day administration as it is often that it is much quicker to just run a command than log on the web client (wait for it to take its time), browse to the right menu, etc... 

For that reason I wanted an easy and quick way to get an overview of the hosts' resources usage without having to log in a client or "brain process" numbers, so I wrote a little function that will display the CPU and memory usage of one or more hosts.

I have put that function in my powercli module where I store all my vmware related functions.

To call the quickview on all the hosts with default values:

```Powershell
Get-VMHostQuickView (Get-VMHost)
```

![Get-vmhostvisual.jpg]({{site.baseurl}}/img/Get-vmhostvisual.jpg)

Available parameters:

```Powershell
- LengthBar
	Length of the colored bars in characters
    Default 30

- CPURed
	Threshold at which the CPU bar is red
    Default 80

- CPUYellow
	Threshold at which the CPU bar is yellow
    Default 60

- MEMRed
	Threshold at which the memory bar is red
    Default 80

- MEMYellow
	Threshold at which the memory bar is yellow
    Default 60

```

