---
layout: post
title: Conflict between EMC Networker client and vCenter Server (Windows)
DATE: ''
date: 2019-03-08 12:17:59 +0100

---
I sat for a good 2 minutes looking for a fun title for this post but I couldn't come up with anything worth it. I wanted to do so because I find this issue to be really lame but also a little funny somehow.

I encountered a really strange issue with a customer on a Windows based vCenter server. (I know Windows will be deprecated soon but this is another discussion and it is still supported as of now). I am going to simplify what happened and consolidate the useful bits.

The vCenter rebooted after one of the guys patched the server for Windows updates. Nothing wrong here, this usually is a routine task, but this time, after the server completed its reboot, the web client would display a single-sign-on error which made the server unusable. A few hits online on this issue but nothing really useful.

\+++ PIC

We looked at the services with **_service-control --status_** and immediately noticed that a bunch of services were not started, including _VMware Identity Management Service_. We tried a bunch of things to get them back up:

* Rebooting wouldn't change anything.
* Starting the services with **_Service-control --start --all_** would get stuck and crash after starting the psc-client service.
* Manually starting the _VMware Identity Management Service_ would work but then crash a couple minutes later.
* Uninstalling the Windows patches would make no difference.
* Restoring the database with a backup a few days old.
* Even tried resetting the password of the Windows virtual accounts created by vCenter after reading the community post: [https://communities.vmware.com/thread/550780](https://communities.vmware.com/thread/550780 "https://communities.vmware.com/thread/550780")

It is worth noting that the server had not been restarted in a while so we couldn't tell when the root cause of the issue happened (i.e. Would the same problem have occurred if the server was rebooted 2 months ago? - No way to tell at the time).

We went through the vCenter logs and always ended up with the same generic kind of error messages which were not helpful at all. The VMware support wasn't of great help either as they couldn't understand what was causing the services to crash. At this time we were running out of ideas so we decided to reinstall a new vCenter.

* Connect directly to a vSphere host (vCenter being down).
* Create a new VM (no template to deploy from).
* Install Windows and vCenter (skipping the steps).
* Install the Networker client + SQL database module.

At the time we were not suspecting the Networker agent so we tried reinstalling with the embedded database and several different things until one of the guys uninstalled the Networker client, then rebooted and all the services came back up. If you reinstall the client, vCenter keeps working and the backup software works, but if you reboot the server you will run into the same issue as described.

Sure enough we contacted the EMC support to ask what's going on and how we are supposed to backup our vCenter DB if the client keeps crashing vCenter. The response from the support was gold, it went something like this:

> We can't find any entries regarding the backup of vCenter in our documentation. You are not supposed to back up vCenter. If you want to do so you can make a dump of the DB and copy it to a shared location.

\+ PIC 96

Why am I paying for this software again? Oh yea, backups... We were really surprised and disappointed by this answer as it is a clear case of _"We have no idea what's going on so - We don't support it, deal with it - bye"_. I am used to the VMware support trying to put the blame on the third party and vice versa but that's another level here. 

So, it turns out the Networker client had been installed several months ago after the server was last rebooted, meaning the issue would have occurred anytime after that day.

Conclusion

I can't imagine that we are the first to encounter this issue. If you are going to pay the EMC premium for their backup product you might as well want to backup your vCenter DB. I went through several EMC Networker documentations looking for a statement regarding vCenter being not supported or not to install the client on it and found nothing. I couldn't find anything relating to a similar issue online.

* Thumbs down to EMC support and documentation/compatibility. Sorry guys but that sucked.
* Reboot the server after installing a new software.
* **Don't use EMC Networker Client on a Windows based vCenter.**