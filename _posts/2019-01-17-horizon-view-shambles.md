---
layout: post
title: Horizon View shambles
DATE: ''
date: 2019-01-17 09:02:13 +0100

---
I started working with Horizon View for a customer a little less than a year ago. I had never used the product before and boy was life sweet. I will consider this post a mix of self therapy and archives (I know, makes sense to me). Although before ranting at Horizon View it is worth mentioning that the environment in which it is deployed is pretty complex.

I will keep updating this post with new issues that worth the tale so I hope not a lot... If you encountered some of them or have information/ideas/theories **please share in the comments!**

### Issue #1: A taste of apocalypse

[The first issue](https://communities.vmware.com/thread/591103 "Call of duty: Horizon View") I encountered was really bad. Whenever the connection servers would lose connectivity to vCenter, even for a short amount of time, everything would go awol. Errors all over the place, no provisioning, a real battlefield with body parts everywhere. Proper messy. The only way to fix it was to shut down everything in the right order and power it back on. Not "ideal" in production... VMware later provided us with a hotfix and it's been ok since then. Fingers crossed.

### Issue #2: Pickaboo

Then we ran into hardware problems with customized VSAN ready nodes where they would just disconnect from vCenter causing a bunch of problems. What happens is that somehow the local ESXi boot disk goes missing (hence the pickaboo). This event would cause ESXi to try to bring the disk back online over and over again, eventually using up all the allocated memory causing hostd and vpxa to crash dramatically. At least that's my best theory that the VMware support confirmed with a (not convincing at all) "It makes sense".

Funnily enough VSAN would still work fine and the VMs on it too so there's that... ESXi could still run as it's loaded in RAM but no logs persist as they are store on local disk. The only way to troubleshoot was the real time vmkernel log in the DCUI (alt+F12). After reviewing the logs I found a lot of records pointing the finger at the storage controller of the 2 dedicated boot disks. (This controller is the "customized" bit of the ready node - certified by the vendor - or is it?)

VMware confirmed and recommended to upgrade the firmware driver of this controller to the latest version which I did. The issue hasn't come back since but it's not been long so I'm not putting my money on it - This is a case of wait and see. \[EDIT\] It's been over 2 months now and running fine on that front. I think we can assume the upgrade firmware/driver fixed this issue.

### Issue #3: Because why not

This third riot is rather fresh. I was happily updating the VMtools and compatibility of the connection server VMs in the second pod after our 6.5 migration. One by one. Every time I wait for it to come back to green in the admin console and I move on to the next one. I was laughing.

Then I moved to the other pod. Same process, everything goes smoothly. There's only one that I don't upgrade as there's a bunch of users connected in tunneling mode, no biggy. Thought to myself "Cool almost done" but then the "Problem vCenter VMs" count started incrementing along with error events but all components were green... oh oh. VMs provisioned would go in "Provisioning error" and VM deletion in "Error (missing)". Both suggesting an authentication problem, weird. I even got some of them in "Error" with a magnificent error message _'java.lang.IllegalArgumentException: cachedVM == null'_. Thanks, so what am I supposed to do with that exactly? I never found it on google, only a few hits that resembled it that suggested Invalid object in the ADAM database. I looked at it but couldn't find any oddity (although I didn't know what I was after so...). I checked the replication with [repadmin](https://kb.vmware.com/s/article/1021805 "KB1021805") which showed that everything was OK.

Luckily the second pod was fine so there was no doomsday kind of emergency but I didn't sleep well. This time we managed to bring everything back online by shutting down all the connection servers in the pod one by one, and then powering them back on. It is still a mystery to me why things got bad and why the "let's call it a reset" of the connection servers fixed it... I opened a case with VMware and will keep this post updated if/when new relevant information comes in.