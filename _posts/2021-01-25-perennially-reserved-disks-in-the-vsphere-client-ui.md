---
layout: post
title: Perennially reserved disks in the vSphere client UI
DATE: 

---
In 2018 I wrote a [blog ](https://www.vembu.com/blog/wsfc-clusters-and-how-to-fix-esxi-long-boot-times/)for Vembu about how LUNs used as RDMs by Windows Server Failover Cluster (WSFC) can significantly slow down the boot time of your vSphere hosts. This is due to the active node of the Windows cluster holding a lock on the LUN and VMFS trying to get a hold of it with no success through several retries, hence the long time to boot.

This can be easily avoided by setting the "perenniallyReserved" flag to true on the concerned LUNs. This can be done with esxcli so it can be scripted in PowerCLI. While this is still probably the best method as you can process a whole cluster at once if you are careful, I noticed in vSphere 7.0 that you can now do it in the vSphere client!

When on a host object in the device view, when you click on one you will see a new "**_Mark as Perennially Reserved_**" button that will let you do just that.

![](/img/perenially.png)

Thankfully a warning message pops up when you click on it to let you know that your action could have adverse effects should you do it on the wrong LUN.

![](/img/perenially2.png)

**_Edit_**: There is also a new column in the device view to see which devices are set as perennially reserved.

![](/img/peren1.png)

Most people reading this already know that but it's never a bad thing to repeat it: **Be careful and double check everything when performing an action on a storage Lun in production !**