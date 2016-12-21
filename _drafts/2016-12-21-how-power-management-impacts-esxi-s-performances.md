---
layout: post
published: false
title: How Power management impacts ESXi's performances
---
Recently at work we've been noticing erratic performance on VMs eventhough the host's CPU wasn't running hot. In order to check if there was contention I looked at the DRS chart and discovered that the CPU, not even hitting the 50% bar was not delivering half the resources.

The calculation of the resource delivered is a percentage of the consumed CPU to the entitled/demanded CPU (minimum of demand or DRS entitled).

> Delivered CPU = Consumed / Min(Demand,DRS entitled)

the color of the bars in the DRS chart change according to this delivered CPU percentage.

![pwrmgt-legend]({{site.baseurl}}/img/pwrmgt-legend)

The screenshot below shows the DRS CPU utilization chart when we had performance issues.

![pwrmgt-before.png]({{site.baseurl}}/img/pwrmgt-before.png)

It clearly shows a lot of yellow and not enough green. This behaviour was happening only on these two hosts.

After a bit of sniffing around we noticed that the Power management on these two was set to:

- Technology: ACPI C-States
- Active Policy: Performance

But the other hosts were displaying only "Performance".

So I rebooted on the BIOS of the server and browsed to "System BIOS Settings" > "System Profile" and found the the profile set to "Performance Per Watt (DAPC)".

- Quickly changed it to Performance (which disables the power saving features).
- Rebooted the host
- Loaded it with a bunch of VMs

I then checked the DRS chart and everything was green again, all entitled resources delivered by the host, no more CPU throttling incurred by the power saving features.

![pwrmgt-after.png]({{site.baseurl}}/img/pwrmgt-after.png)

----

Now
