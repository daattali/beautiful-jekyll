---
layout: post
published: true
title: 'Migrating Essentials host to new Standard cluster '
date: '2016-06-09'
subtitle: 'EVC, license issue and cold vMotion script'
---
At work we are currently in the process of completely rebuilding the development cluster that was composed of 3 hosts running ESXi 5.1 with vSphere Essentials license managed by a vCenter Essentials.  
I have built and configured my new cluster running the last build of vSphere Standard 6.0 (3825889 at the date of this post) managed by a vCenter. The clusted is composed of a bunch of recently bought servers and older ones running at the **Westmere EVC level** (some have x5660 CPUs). But I wanted to keep the ones from the old dev cluster as well as they have pretty good hardware configurations (E5-26xx) but reinstall them from scratch.

Because these 3 hosts were running the developers/testers' virtual machines, I couldn't just nuke them. So I had to migrate the VMs to the new cluster with the least downtime possible as they are actively used, and even though I don't mind for the production I'm not really keen to work at night for the pre-prod.

During the migration, I stumbled into two small problems that I didn't really think about beforehand.

----------

**vSphere Standard license not usable on Essential licensed host**  
Note that I had already added the newly bought vSphere standard licenses for 3 CPUs in  the inventory in vCenter.
This is a step I thought would be a case of assigning the standard license and start migrating some stuff but when I got to the screen to select the license my only choice was the Essentials license (the evaluation one had been expired for a long time).

![EssNoStd.jpg]({{site.baseurl}}/img/EssNoStd.jpg)

so no point continuing as an Essentials licensed host can only be managed by an Essentials vCenter. The host would be immediately disconnected from vCenter with the error "The host is licensed with VMware vSphere 5 Essentials. The license edition of vCenter Server does not support VMware vSphere 5 Essentials".

![licCompare.jpg]({{site.baseurl}}/img/licCompare.jpg)

In order to connect the host to the vCenter to be able to vMotion out the VMs, I used a little hack to reset the evaluation period (sorry VMware it was for the good cause):  
The credit of that procedure goes to [this post](esxi.oeey.com/2013/11/how-to-reset-esxi-trial-license.html):  

- SSH on the host.
- remove or rename the license config file.
- Replace by the hidden base license.cfg file.
- restart the vpxa service (+ check the status).

```Bash
CP /etc/vmware/license.cfg /etc/vmware/license.cfg.old
CP /etc/vmware/.#license.cfg /etc/vmware/license.cfg
/etc/init.d/vpxa restart
/etc/init.d/vpxa status
```

When I retried to add my host to the vCenter the (Enterprise plus) evaluation license was available again, wondeful!

----------

**The host cannot be admitted to the cluster's current Enhanced vMotion Compatibility mode**   
Why did I wrote the **Westmere** EVC level in bold in the introduction?  
When I added the host to the cluster I got an error preventing me to do so stating that the VMs running on this host might be using CPU instructions not supported by the EVC level on the target cluster. No EVC level was set in the Essentials cluster indeed as it was not needed because the license doesn't include live vMotion so it was using all of the available CPU instructions on each host.

![evcwarning.jpg]({{site.baseurl}}/img/evcwarning.jpg)

The migratee is equipped with a E5-2660 codename **Sandy Bridge**.  
Quick reminder on Intel's codenames:

  | Codename                        | Year |
  | ------------------------------- |:----:|
  | Older Intel processors          |/     |
  | Intel "Nehalem" Generation      |2008  |
  | Intel "Westmere" Generation     |2010  |
  | Intel "Sandy Bridge" Generation |2011  |
  | Intel "Ivy Bridge" Generation   |2012  |
  | Intel "Avoton" Generation       |2013  |
  | Intel "Haswell" Generation      |2013  |
  | Future Intel processors         |/     |

Not a lot of options in this case. I created a TEMP cluster in my datacenter with EVC disabled and added the host succesfully to it.  
The only way now to get these VMs to the right cluster was to migrate the VMs while powered off (cold migration) to the hosts in the EVC level enabled cluster and power them back on there.

As a good lazy admin I wrote a script to do it for me that you will find [here in my Github](https://github.com/vxav/Scripting/blob/master/Move-VMCold.ps1).  
This script will perform these steps on every VM specified one by one:  

- Ask for confirmation with built-in ```Powershell SupportsShouldProcess```.  
- UPDATE : Checks for resources on destination (Port groups and Datastores).
- Shut down the guest OS and wait for PowerOff state.  
- Move the VM to destination.  
- Restart the VM if specified (by default in the parameters).  
- Go to the next VM, etc...

Example of the command usage:  

```Powershell 
Get-VMHost MyHostSource | Get-VM | Move-VMCold -Destination (Get-VMHost MyHostTarget)
```

----------

Once all of the VMs were migrated automatically and the host empty I was able to disconnect it, power it off and rebuild it the way I wanted it.
