---
layout: post
published: false
title: 'Don''t bother with an IP, just ping a VM'
---
One thing that we all do quite regularly is pinging servers. In a medium/big environment there can be a lot of VMs and I can't remember all the IP address or even the hostnames, which is annoying when I want to ping one of them. It's still easy to find on the web client or with PowerCLI but it would be even easier to just **ping the VM**.

The purpose of this script is to ping a VM object in PowerCLI on all its IP addresses. Of course the VMware Tools need to be installed for it to work.

Instead of looking for what is the IP or the hostname of this VM, we just **ping it using Get-VM**.

For example if a VM has 3 virtual NICs and 3 IP addresses, by pinging this VM, a ping will be issued to all 3 IPs.

![vmping.jpg]({{site.baseurl}}/img/vmping.jpg)

