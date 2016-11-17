---
layout: post
published: false
title: 'Don''t bother with an IP, just ping a VM'
---
One thing that I do all the time is pinging stuff, and usually stuff are VMs and I don't always know by heart the IP address or the hostname of this VM. It's easy to find out without even logging on the VM but it would be even easier to just ping the VM.

The purpose of this script is to ping all the IP addresses of a VM with a VM object as an input.

For example if a VM has 3 virtual NICs (3 IP addresses), by pinging this VM, a ping will be issued to all 3 IPs.