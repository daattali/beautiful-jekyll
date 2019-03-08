---
layout: post
title: Conflict between EMC Networker client and vCenter Server (Windows)
DATE: ''
date: 2019-03-08 12:17:59 +0100

---
I sat for a good 2 minutes to find a fun title for this post but I couldn't come up with anything worth it. I wanted to do so because I find this issue to be really lame but a also funny somehow.

I encountered a really strange issue with a customer with a Windows based vCenter server. Everyone knows Windows will be deprecated soon but this is another discussion and it is still supported).

The vCenter rebooted after one of the guys patched the server for Windows updates. This usually is a routine task, but this time, after the server completed its reboot, the web client would display an single-sign-on error which made the server unusable.

\+++ PIC

We looked at the services with **_service-control --status_** and immediately noticed that a bunch of services were not started, including _VMware Identity Management Service_. We tried a bunch ot things that didn't work:

* Rebooting wouldn't change anything.
* Starting the services with **_Service-control --start --all_** would get stuck and crash after starting the psc-client service. 
* Manually starting the _VMware Identity Management Service_ would work but then crash a couple minutes later.
* Uninstalling the Windows patches.
* Restoring the database with a backup a few days old.
* Resetting the password of the Windows virtual accounts created by vCenter: [https://communities.vmware.com/thread/550780](https://communities.vmware.com/thread/550780 "https://communities.vmware.com/thread/550780")

It is worth noting that the server had not been restarted in a while so we couldn't tell when the root cause of the issue happened (i.e. Would the same problem have occurred if the server was rebooted 2 months ago? - No way to tell).

We went through the vCenter logs and always ended up with the same generic kind of error messages which were not helpful at all. The VMware support wasn't of great help either as they couldn't get to the bottom of it. At this time we were running out of ideas so we decided to reinstall a new vCenter.

* Connect directly to a vSphere host (vCenter being down).
* Create a new VM (no template to deploy from).
* Install Windows and vCenter.
* Install the Networker client + SQL database module.

At the time we were not suspecting the Networker agent so we tried reinstalling with the embedded database and several different things until one of the guys uninstalled the Networker client, then rebooted and all the services came back up. If you reinstall the client, vCenter keeps working and the backup software works, but if you reboot the server you will run into the same issue as described.

Sure enough we contacted the EMC support to ask what's going on and how we are supposed to backup our vCenter DB if the client keeps crashing vCenter. The response from the support was golden, it went something like:

> We can't find any entries regarding the backup of vCenter in out documentation. You are not supposed to back up vCenter. If you want to do so you can make a dump of the DB and copy it to a shared location