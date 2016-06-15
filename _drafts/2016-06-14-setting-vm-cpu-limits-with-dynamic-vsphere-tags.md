---
layout: post
published: false
title: Setting VM CPU limits with dynamic vSphere tags
---
In the majority of VMware environments, the use of limits (especially memory limits) is strongly discouraged as it can lead to several misbehaviours such as CPU ready or memory swapping, which no one wants.  
But in some cases it can be useful to leverage them, provided it is implemented with sensibility. For example, if you host customer VMs running the same piece of software, it is likely that you want to serve them equally as they probably pay the same amount of money.  

Managing limits can sometimes be a hassle as there is no view in the client for the limits or reservations, you need to check and set on a per-vm basis.

In order to simplify the process of assigning CPU limits to the virtual machines I came up with a PowerCLI script that is called every night by a scheduled task from a "task box" under a "VMware" service account I use for my PowerCLI tasks.  
The interesting feature with this script is that if the tag's name respects the naming convention, the VM CPU limit will be set accordingly, for example:

| Tag name    | CPU limit set  |
|-------------|----------------|
| QOS_1000    | 1000 MHz       |
| QOS_2549    | 2549 MHz       |
| QOS_5000    | 5000 MHz       |
| QOS_NOLIMIT | Unlimited (-1) |

The script retrieves all the VMs per QOS tag one by one and updates there resources configuration if they are not already set according to the number in the tag's name.  
To assign a limit to a VM, you just need to assign the right tag to it and the next run of the scheduled task will set it. Personnaly I've set it to run every day at 9pm, but it is possible to configure it for more or less often.

![tag-limits.jpg]({{site.baseurl}}/img/tag-limits.jpg)

