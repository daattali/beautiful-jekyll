---
layout: post
published: true
title: 'Migrating Essentials host to new Standard cluster '
date: '2016-06-09'
subtitle: 'EVC, license issue and cold vMotion script'
---
At work we are currently in the process of completely rebuilding the development cluster that was a 3 hosts running ESXi 5.1 with vSphere Essentials license connected to a vCenter Essentials.  
I have built and configured my new cluster running the last build of vSphere Standard 6.0 (3825889 at the date of this post) managed by a vCenter. The clusted is composed of a bunch of recently bought servers and older ones running at the **Westmere EVC level** (some have x5660 CPUs). But I wanted to keep the ones from the old dev cluster as well as they have pretty good hardware configurations (E5-26xx) but reinstall them from scratch.

These 3 hosts were running the developpers/testers' virtual machines, I couldn't just nuke them. So I had to migrate the VMs to the new cluster with the least downtime possible as they are actively used, and even though I don't mind for the production I'm not really keen to work at night for the pre-prod.

The two clusters are in separate racks in the same room and have shared storage, the main steps are the following:  

	- 1.Disconnect and remove the host from the Essentials vCenter.
    
    - 2.Re-patch the management NIC to the new cluster's management switch 

	- 3.change the management IP address and dns config.

	- 4.The interesting part here: **Connect the host to the new vCenter (after updating DNS & co...)**

----------

Note that I already added the newly bought vSphere standard licenses for 3 CPUs in  the inventory in vCenter.
This is a step I thought was gonna be a case of assigning the standard license and start migrating some stuff but when I got to the screen to select the license my only choice was the Essentials license (the evaluation one had been expired for a long time).

![EssNoStd.jpg]({{site.baseurl}}/img/EssNoStd.jpg)

so no point continuing as an Essentials licensed host cannot be managed by a vCenter Standard, the host would be immediately disconnected from vCenter.

![licCompare.jpg]({{site.baseurl}}/img/licCompare.jpg)

**Reset evaluation license period**  
In order to connect the host to the vCenter to be able to vMotion out the VMs, I used a little hack to reset the evaluation period (sorry VMware it was for the good cause):  
The credit of that procedure goes to [this post](esxi.oeey.com/2013/11/how-to-reset-esxi-trial-license.html):  

	- SSH on the host.
	- remove or copy the license config file.
	- restart the vpxa service (check).

```Powershell
CP /etc/vmware/license.cfg /etc/vmware/license.cfg.old
CP /etc/vmware/.#license.cfg /etc/vmware/license.cfg
/etc/init.d/vpxa restart
/etc/init.d/vpxa status
```

When I retried to add my host to the vCenter the evaluation license was available again, wondeful!

----------

Why did I wrote the Westmere EVC level in bold in the introduction?  
When I added the host to the cluster I got an error preventing me to do so stating that the VMs running on this host might be using CPU instructions disabled by the EVC level on the target cluster. I forgot indeed this detail while planning my host move, no big deal though.

![evcwarning.jpg]({{site.baseurl}}/img/evcwarning.jpg)

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

Not a lot of options in this case. I created a TEMP cluster in my datacenter with EVC disabled and added the host succesfully into it.  
The only way now to get these VMs to my cluster was to migrate the VMs while powered off (cold migration) to the host in the EVC level enabled cluster and power them back on.  
As a good lazy admin I obviously wrote a script to do it for me that you will find [here in my Github](https://github.com/vxav/Scripting/blob/master/Move-VMCold.ps1).  
This script will perform these steps to every VM specified one after the other:  

	-Ask for confirmation with built-in ```Powershell SupportsShouldProcess```.  
	-Shut down the guest OS and wait for PowerOff state.  
	-Move the VM to destination.  
	-Restart the VM is specified (by default in the parameters).  
	-Go to the next VM, etc...

For example:  

```Powershell 
Get-VMHost MyHostSource | Get-VM | Move-VMCold -Destination (Get-VMHost MyHostTarget)
```

We were still in step 4 of my migration and I got a little bit carried away. I won't dig deeper in the rest of my actions as it is not really relevant to our matter but basically they were :

----------

	- 5.Cold migrate all the VMs to the proper cluster (the script above did it for me).
    
	- 6.Disconnect and remove the host from the vCenter.
    
	- 7.Power off the server, move it to the new rack and redo the physical patching.
    
	- 8.Update the DNS record.
    
	- 9.Reinstall and configure ESXi6 from scratch.
    
	- 10.Add it to the EVC enabled cluster in the vCenter and update it with Update Manager to the last build.
    
	- 11.Do the same for the 2 other hosts and remove the TEMP cluster.
