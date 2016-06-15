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

Before getting into the script let's go through the few steps to get it ready.

**Create the tags and a tag category**

First create a tag category configured for one tag per object and associable with virtual machines only. give it a name that makes sense to you along with a quick description for the colleagues.

![tag-category.jpg]({{site.baseurl}}/img/tag-category.jpg)

_PowerCLI command_ : ```Powershell
New-TagCategory -Name "Quality of Service" -Cardinality "Single" -EntityType "VirtualMachine" -Description "Sets VMs CPU limit" ```

Then create a set of tags formatted like in the tag name column of the table above, don't forget to create the tag QOS_NOLIMIT.  
You can create as many as you want but there is not point having to many, I recommend something like:  
1500, 2500 for small VMs.  
4000, 6000 for bigger VMs.  
NOLIMIT for the VIP VMs.

**Warning**: Do not set limits equal to 0! vSphere won't prevent you from doing it but it will freeze the VM, its options will be greyed out and you will just have to wait until it powers off which can take a long time (only way come back from the deads).

![tag-in-category.jpg]({{site.baseurl}}/img/tag-in-category.jpg)

_PowerCLI command_ : ```Powershell
Get-TagCategory -Name "Quality of Service" | New-Tag -Name "QOS_2500" -Description "CPU limit of 2500MHz (set by script at 9pm)" ```

Now that the tags are created in the right category, assign it to a VM either using the GUI or PowerCLI, you can only assign one tag of this category for obvious reasons.

![assign-tagweb.jpg]({{site.baseurl}}/img/assign-tagweb.jpg)

_PowerCLI command_ : ```Powershell
Get-VM "Test-Xav*" | New-TagAssignment -Tag (Get-Tag "QOS_2500") ```



