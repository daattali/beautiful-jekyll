---
layout: post
published: false
title: Update from vSphere 5.5 to 6.0 Update 2 using the DCUI
---
After upgrading one of the host [in my lab with VUM](http://www.vxav.fr/2016-07-25-update-dell-host-to-vsphere-6-using-vum/) I had to update the second one in order to install the FVP extension from Pernix Data. My VMs (VUM, vCenter, DNS) were then on this host's local storage and I couldn't be bothered migrating them to the other one as it would have taken forever in this lab (currently running the whole lab on one hdd arghhhh).

So I just powered the thing off and upgraded it in interactive mode, which is actually faster, so I thought I'd write a quick post about it (while my VMs are migrating to the shared storage).

First of all insert the CD, or most likely connect the ISO to the host using iDrac/iLo & Co.

Power on the host and boot on the CD drive.

Choose again to boot on the image.

![boot-from-cd.jpg]({{site.baseurl}}/img/boot-from-cd.jpg)

Press Enter to pass the Welcome screen.

![welcomescreen.jpg]({{site.baseurl}}/img/welcomescreen.jpg)

Press F11 to accept the EULA.

![accept-eula.jpg]({{site.baseurl}}/img/accept-eula.jpg)

Choose the partition on which ESXi is currently installed.

![partochsetup.jpg]({{site.baseurl}}/img/partochsetup.jpg)

Chose to upgrade by pressing space bar on it. Be careful on that one you don't want to wipe out your host...

![upgradenotinstall.jpg]({{site.baseurl}}/img/upgradenotinstall.jpg)

Press F9 to confirm the Upgrade.

![confirmupgrade.jpg]({{site.baseurl}}/img/confirmupgrade.jpg)

Now your host will take a while to upgrade, then accept the restart.

![host-restart.jpg]({{site.baseurl}}/img/host-restart.jpg)

And that's you, the host is upgraded to the version of your ISO.  
So again, You will then want to patch the host using VUM to add the last ones not in the ISO.
