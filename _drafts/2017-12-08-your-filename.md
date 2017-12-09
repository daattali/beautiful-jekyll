---
layout: post
published: false
title: Untitled
---
In this article I would like to cover a failure scenario that I recently dealt with and that I suspect is maybe not that common for several reasons. The environment is made of 2 sites in a metro cluster sharing a virtualised storage over a multiplexed fiber. Half of the 8 wavelength of that fiber are used for storage synchronisation and the other half for passing VLANs (including vSphere management).   Following an incident somewhere along that fiber (the ISP confirmed), it is believed that only some of the wavelengths went down (not confirmed). The storage nodes on the 2 sites could communicate fine after a few minutes following the outage and restart synchronisation but the only vCenter located on the first site could not reach the ESXi hosts located on the second site nor could the VLANs.

![Outage-dci.jpg]({{site.baseurl}}/img/Outage-ijb.jpg)

In short, everything running on the second is isolated in a bubble and cannot be reached except the storage which was a VERY good thing. So we are left with half of the cluster in a partitioned state but a full access to the storage from all hosts across the 2 sites. A few things to note to fully understand the extent of the situation:

-The metro cluster was configured with DRS with no particular attention given to virtual machine location which makes the consequences of a failure scenario completely left to luck (DRS), i.e. all the components of an app stack could be located on 1 site because DRS decided to balance the load (this is were you wonder "Drs rules ?").
-No DR plan in place so there is no way to easily power on replicas on the first site. Remember that the VMs running on the partitioned site still hold a lock on their files
-No backup or external link to connect remotely into the second site (the good stuff).

## Objectives

My 2 major objectives were:

1. **Recover the VMs from the second site to the first** site in order to restore service asap as we didn't know how long it would take for the ISP to fix the fiber (could be an hour, could be a week...).
2. **Avoid at all cost having duplicate similar VMs** (Infrastructure 101 > Big no-no). This could happen if your second site came back to life with the VMs still running after restoring them on the first site. This scenario could potentially be very destructive as it is more than likely that you would end up with corrupted data, leaving a restore from backup your only solution to recover, and it takes a LOT more time and data loss.

## Manual recovery plan

Here was the plan to recover safely on the first site:

  **1-** Send someone with a laptop to the second site (80s style) to connect locally on the vSphere hosts one by one and do the following:

- **Shut down** all the VMs.
- **Unregister** them from the inventory.
- Place the host in **maintenance mode.**

As mentionned above, this action is of major importance as it released the locks on the VM files (remember the storage synchronization still works) and prevented turning up with 2 sets of similar VMs once the second site would come back.

  **2-** Recover the VMs on the hosts in the first site:

- Save the pathes to the .vmx files of the disconnected VMs into a variable in PowerCLI for later use when I will need to register them. If you remove the hosts straight away you won't know which VMs were running nor which datastore they resided on and good luck with the "vms file treasure hunt".

```Powershell
$PartitionedVMHosts = Get-VMHost | where {ConnectionState -eq "Disconnected" -or ConnectionState -eq "NotResponding"}

$VMsToRecover = $PartitionedVMHosts | Get-VM | where powerstate -eq poweredon | select @(l="VM";e={$_}),@(l="Folder";e={$_ | Get-Folder})
```

Remove from the vCenter inventory the hosts of the second site being in a disconnected state.

```Powershell
$PartitionedVMHosts | Remove-VMHost -Confirm:$false
```

Register the VMs previously running on the second site on the hosts in the first using the variable mentionned above and power it on.

I don't pay too much attention to the resource pools here as there is none configured but it is something you may want to consider in a different environment.

```Powershell
$RP = Get-Cluster | Get-ResourcePool

$VMsToRecover | ForEach-Object {New-VM -Name $_.vm.name -ResourcePool $RP -VMFilePath $_.VM.extensiondata.config.files.vmpathname -location $_.folder.name | Start-VM -Confirm:$false}
```

 **3-**Once it is done, all the VMs from the second site are recovered on the first one. That's good, but we  are not out of the woods yet. Say a bunch of web nodes or middletier nodes on the first site and the db was recovered during the outage, you probably want to restart the whole app stack in the right order to avoid any unpredicted state: shut down web nodes, then middletier nodes, restart the db, power on the middletier nodes then the web nodes. It is a cumbersome process but I would say worth doing for peace of mind's sake.

  **4-** Use your favorite monitoring tool to ensure all services are back online and troubleshoot those having problems (there will be some). This step is down to the team managing the apps and services.

  **5-** Once the ISP fixed the problem on the link, just connect the hosts on the second site back in vCenter.

## What should be in place to avoid such situation or mitigate the consequences and improve RTO?

- **The DCI should not be a single point of failure (spof).**

For a piece of infrastructure as critical as the DCI, being a spof is not an option at all. I bet pretty much every "architecture 101" documents out there recommend to have at least 2 different links using 2 different geographical pathes with different ISPs. I would even vouch for a third 10Mbps adsl link over an IPsec tunnel simply to maintain communication between the vCenter server and the hosts.

- **Remote access to the second site should be available.**

Pretty obvious but still worth mentionning, having to get the car and drive 12 miles to connect to the critical components of infrastructure in the second site is not an option either. Following the previous recommendation, there should always be a way to access it via a cheap adsl link, a vpn, you name it.

- **VM location awareness.**

Metro clusters are great, you can migrate a VM from a site to another (yay..), you can do planned maintenance on a site, you can leverage HA ... Yes, all of these are great, but if you lose everything at the first outage it is not much use. Here, VM location awareness is just a fancy name for vSphere DRS rules. A group of hosts for site A, a group of hosts for site B, a group of VMs for site A and one for B, easy. Keep half of "X" on each site. "X" meaning DCs, web servers, app servers, hot/warm DBs, again you name it. The idea is be able to survive a site failure (active-active DC 101).

Regarding the "swag" of VM mobility and all the headaches that comes with it I highly recommend checking  out the knowledgeable [Ivan Pepelnjak's blog](https://blog.ipspace.net/) that will make you think twice about whether you really need it or not, great content!

- **DR Plan.**

I was lucky enough that the storage kept synchronising and that shutting down the VMs on the other side released the locks, and the few lines of PowerCLI above allowed me to recover fairly quickly. But if the second had been blown up by an asteroid I would have been screwed. In a 2 sites architecture a DR plan with cross replication is an absolute must have.

## It is not all bad

I painted a pretty grim picture of the situation but a few things remain very positive:

- Even though luck was a decisive factor regarding storage synchronisation, the RPO of this recovery was very good because of it. The storage having been up to date, little to no data loss occurred and the RTO was only a few hours.

- Lessons were learnt. Some things take a large amount of sweat, produced by an outage like this one, to get people out of their comfort zone and assign resources to find solutions to the "What if" situations and pay more attention to best practices. Also, if higher management could not be convinced to put some money into it, it is definitely going to happen.

Anyway, nice little case study that I thought would be worth sharing!