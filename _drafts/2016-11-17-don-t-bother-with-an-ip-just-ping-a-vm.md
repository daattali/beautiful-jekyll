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

It can be used in several ways.

Ping a single VM:

```Powershell
Get-VM My-VM | VMping
```

Ping the VMs in a folder (foreach needed when more than 1 objects input):

```Powershell
Get-VM -Location MyFolder | Foreach-object {$_ | VMPing}
```

Issue 2 pings to all the VMs of a host indefinitely:

```Powershell
While ($true) {Get-VMhost Host10 | Get-VM | Foreach-object {$_ | VMping -count 2}}
```

These are just a few examples of what it can be used for.

The parameters that can be set:

- **Count** : Number of pings
- **Delayms** : Time in ms between 2 pings
- **Timeout** : Timeout ...
- **Continuous** : doesn't stop pinging (can't be used with count)
- **enableIPv6** : If you want to ping the VM on its IPv6 addresses as well