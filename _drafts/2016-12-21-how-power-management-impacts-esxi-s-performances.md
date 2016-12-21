---
layout: post
published: false
title: How Power management impacts ESXi's performances
---
Recently at work we've been noticing erratic performance on VMs eventhough the host's CPU wasn't running particularly hot. In order to check if there was contention I looked at the DRS chart and discovered that the CPU, not even hitting the 50% bar was not delivering half the resources.

The calculation of the resources delivered is a percentage of the consumed CPU to the entitled/CPU demand (minimum of demand or DRS entitled).

> Delivered CPU Percentage = Consumed / Min(Demand,DRS entitled) * 100

the color of the bars in the DRS chart change according to this percentage.

![pwrmgt-legend.png]({{site.baseurl}}/img/pwrmgt-legend.png)

The screenshot below shows the DRS CPU utilization chart when we had performance issues.

![pwrmgt-before.png]({{site.baseurl}}/img/pwrmgt-before.png)

It clearly shows a lot of yellow and not enough green. This behaviour was happening only on these two hosts.

After a bit of sniffing around we noticed that the Power management (under "Host" > "Manage" > "Settings" >  "Hardware" > "Power management") on these two was set to:

- Technology: ACPI C-States
- Active Policy: Performance

But the other hosts were displaying only "Performance".

So placed the host in maintenance mode, rebooted on the BIOS and browsed to "System BIOS Settings" > "System Profile" and found the profile set to "Performance Per Watt (DAPC)".

- Quickly changed it to Performance (which disables the power saving features).
- Rebooted the host
- Loaded a bunch of VMs on it

I then checked the DRS chart and everything was green again, all entitled resources delivered by the host, no more CPU throttling incurred by the power saving features.

![pwrmgt-after.png]({{site.baseurl}}/img/pwrmgt-after.png)

----

Now let's see what was causing the CPU to throttle down by comparing the two power management modes.  
You can find all the documentation about the power efficiency for Dell servers in [this PDF](https://www.google.co.uk/url?sa=t&rct=j&q=&esrc=s&source=web&cd=2&ved=0ahUKEwiQno_-zoXRAhXmIsAKHXxLBKcQFggkMAE&url=http%3A%2F%2Fen.community.dell.com%2Ftechcenter%2Fextras%2Fm%2Fwhite_papers%2F20109038%2Fdownload&usg=AFQjCNH4-UomnbVz9hqQoXscgX_aVuSiSQ&sig2=ay7sMTpkvN3wA-wtHE_hvg).

![pwrmgt-bios-settings.png]({{site.baseurl}}/img/pwrmgt-bios-settings.png)

The only difference between "Performance" and "Performance per Watt" is related to the C1 states which is a power saving feature.

Here is a quote of the Dell documentation about the different profiles.

> **Performance-per-watt (DAPC)** profile is the default, and represents an excellent mix of performance balanced with power consumption reduction. Dell Active Power Control (or DAPC), relies on a BIOS-centric power control mechanism which offers excellent power efficiency advantages with **minimal performance impact in most environments**, and is the CPU Power Management choice for this overall System Profile.

> **Performance-per-watt (OS)**, otherwise known as “OS Control”, is similar to the DAPC profile for all sub-options except for the CPU Power Management. The power management scheme used for this profile is called “OS DBPM”, which allows the Operating System to manipulate processor frequencies for higher power efficiency. However, the effectiveness of this profile for reducing overall system power consumption is based on how well the Operating System is able to effectively control hardware resources, so the impacts are mixed across all supported Operating Systems.

> **Performance** profile provides potentially increased performance by maximizing processor frequency and the disabling certain power saving features such as C-states and. Although not optimal for all environments, this is an excellent starting point for performance optimization baseline comparisons.

> **Dense Configuration** enhances reliability features and reduces power consumption at the cost of considerable performance. This profile is targeted for operating environments where enhanced reliability is desired and temperatures may exceed the thresholds encountered in less densely-packed data centers.

Conclusion: If the performance of your VMs is more important than saving a couple watts here and there this setting should be set to high performance.