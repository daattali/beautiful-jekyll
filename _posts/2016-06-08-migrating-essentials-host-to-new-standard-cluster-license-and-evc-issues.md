---
layout: post
published: false
title: Migrating Essentials host to new Standard cluster (license and evc issues)
---
At work we are currently in the process of completely rebuilding the development cluster that was a 3 hosts running ESXi 5.1 with vSphere Essentials license connected to a vCenter Essentials.  
I have built and configured my new cluster running the last build of vSphere Standard 6.0 (3825889 at the date of this post) managed by a vCenter. The clusted is composed of a bunch of recently bought servers and older ones running at the **Westmere EVC level** (some have x5660 CPUs). But I wanted to keep the ones from the old dev cluster as well as they have pretty good hardware configurations (E5-26xx) but reinstall them from scratch.

These 3 hosts being running the development virtual machines, I couldn't just nuke them. So I had to migrate the VMs to the new cluster with the least downtime possible as they are actively used, and even though I don't mind for the production I'm not really keen to work at night for the pre-prod.

The two clusters are in separate racks in the same room and have shared storage, the main steps were the following:
1.Patch an unused NIC from a host to the new cluster's management switch and add to it a port-group/vmkernel with management enabled in the new cluster's IP range.
2.Disconnect and remove the host from the Essentials vCenter.
3.Move management to the newly patched vmnic in the DCUI of the host.
4.Connect the host to the new vCenter (after updating DNS & co...)

Note that I already added the 3 newly bought vSphere standard licenses in  the inventory.
This is a step I thought was gonna be a case of assigning the standard license and start migrating some stuff but when I got to the screen to select the license my only choice was the Essentials license (the evaluation one had been expired for a long time).  
![EssNoStd.JPG]({{site.baseurl}}/img/EssNoStd.JPG)
so no point continuing as Essentials license doesn't allow vMotion.
![licCompare.JPG]({{site.baseurl}}/img/licCompare.JPG)

**Reset evaluation license period**
The goal being only to vMotion the VMs to the other hosts I used a little hack to re-enable the evaluation period (sorry VMware it's for the good cause):  
The credit of that procedure goes to [this post](esxi.oeey.com/2013/11/how-to-reset-esxi-trial-license.html).  
-SSH on the host.
-remove or copy the license config file.
-restart the vpxa service (check).


```Powershell
CP /etc/vmware/license.cfg /etc/vmware/license.cfg.old
CP /etc/vmware/.#license.cfg /etc/vmware/license.cfg
/etc/init.d/vpxa restart
/etc/init.d/vpxa status
```

When I retried to add my host to the vCenter the evaluation license was available again, wondeful!

Why did I wrote the Westmere EVC level in bold in the introduction?  
When I added the host to the cluster I got an error preventing me to do so stating that the VMs running on this host might be using CPU instructions disabled by the EVC level on the target cluster.

![evcwarning.JPG]({{site.baseurl}}/img/evcwarning.JPG)

The migratee is equipped with a E5-2660 codename **Sandy Bridge**.  
Quick reminder :  
Older Intel processors
Intel "Nehalem" Generation
**Intel "Westmere" Generation
Intel "Sandy Bridge" Generation**
Intel "Ivy Bridge" Generation
Intel "Avoton" Generation
Intel "Haswell" Generation
Future Intel processors

Not a lot of options in this case. I created a TEMP cluster in my datacenter with EVC disabled and added the host succesfully.  
So no choice now i have to shutdown the VMs one by one (could be scripted as well) and cold migrate them to the host in the EVC level enabled cluster.

I won't dig deeper in the rest of my actions as it is not really relevant to our matter but basically the next step will be :

5.Cold migrate all the VMs to the proper cluster.
6.Disconnect and remove the host from the vCenter.
7.Power off the server, move it to the new rack and redo the physical patching.
8.Reinstall and configure ESXi6 from scratch.
9.Add it to the EVC enabled cluster in the vCenter and update it with Update Manager.
10.Do the same for the 2 other hosts and remove the TEMP cluster.
