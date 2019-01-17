---
layout: post
title: Horizon View shambles
DATE: ''
date: 2019-01-17 09:02:13 +0100

---
I started working with Horizon View for a customer a little less than a year ago. I had never used the product before and boy was it unsuspectingly sweet. Although before ranting at Horizon View it is worth mentioning that the environment in which it is deployed is unusually complex compared to most companies. 

### Issue #1: A taste of apocalypse

[The first issue](https://communities.vmware.com/thread/591103 "Call of duty: Horizon View") I encountered was really bad. Whenever the connection servers would lose connectivity to vCenter, even for a short amount of time, everything would go awol. Errors all over the place, no provisioning, a real battlefield with body parts everywhere. Proper messy. The only way to fix it was to shut down everything in the right order and power it back on, not "ideal" in production... VMware later provided us with a hotfix and it's been ok since then. Fingers crossed.

### Issue #2: Pickaboo

Then we ran into hardware problems with customized VSAN ready nodes where they would just disconnect from vCenter causing a bunch of problems. What happens is that somehow the local ESXi boot disk goes missing (hence the pickaboo). This event would cause ESXi to try to bring the disk back online over and over again, eventually using up all the allocated memory causing hostd and vpxa to crash dramatically. 

Funnily enough VSAN would still work fine and the VMs on it too so there's that... ESXi can still run as it's loaded in RAM but no logs persist. The only way to troubleshoot is the real time vmkernel log in the DCUI (alt+F12). After reviewing the logs I found a lot of records pointing to the storage controller of the 2 dedicated boot disks. This controller being the "customized" bit of the ready node. 

VMware confirmed and recommended to upgrade the firmware driver of this controller to the latest version which I did. The issue hasn't come back yet but it's not been long so I'm not putting my money on it - This is a case of wait and see.

### Issue #3: Because why not

This last one is rather fresh. I was happily updating the VMtools and compatibility of the connection servers in the second pod after our 6.5 migration. One by one. Every time I wait for it to come back to green in the admin console and I move on to the next one. All good I was laughing. 

Then I moved to the other pod, oh boy. Same process, all ok, there's only one that I don't upgrade as there's a bunch of users connected in tunneling mode, no biggy. Thought to myself "Cool almost done" but then the "Problem vCenter VMs" count started incrementing a lot more than it should, error events as well... oh oh. VMs provisioned would go in "Provisioning error" and VM deletion in "Error (missing)". Both suggesting an authentication problem, weird.