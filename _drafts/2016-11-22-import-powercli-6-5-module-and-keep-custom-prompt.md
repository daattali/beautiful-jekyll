---
layout: post
published: false
title: Import PowerCLI 6.5 module and keep custom prompt
---
My Powershell profile has a few different things including:
- A function to add the VMware core snapin and connect quickly to a vCenter.
- A function to customize the prompt with separator and display of the connected vCenter.

![cvc-tf-vcenter.png]({{site.baseurl}}/img/cvc-tf-vcenter.png)

These are very usefull to have as I spend quite a lot of time on PowerShell to make things quicker and clearer.

When I upgraded to [PowerCLI 6.5 R1](http://blogs.vmware.com/PowerCLI/2016/11/new-release-powercli-6-5-r1.html) I noticed that the connection to vCenter failed with the error ```The Windows PowerShell snap-in 'VMware.VimAutomation.Core' is not installed on this computer.```.

![no-snapin.png]({{site.baseurl}}/img/no-snapin.png)

