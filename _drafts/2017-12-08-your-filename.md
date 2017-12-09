---
layout: post
published: false
title: Untitled
---
In this article I would like to cover a failure scenario that I recently came across and that I suspect is not that common for several reasons. The environment is made of 2 sites in a metro cluster sharing a virtualised storage over a multiplexed fiber. Half of the wavelength on the fiber are used for storage and the rest are used for the VLANs (including management VLAN). Following an incident somewhere along that fiber, it is believed that only some of the wavelengths went down. The storage nodes on the 2 sites could communicate fine after a few minutes following the outage but the only vCenter located on the first site could not reach the ESXi hosts located on the second site nor could the VLANs.

In short, everything running on the second is isolated in a bubble and cannot be reached.

So we are left with half of the cluster in a partitioned state but a full access to the storage from all hosts across the 2 sites. A few things to note to fully understand the extent of the situation:

-The metro cluster was configured with DRS with no particular attention given to virtual machine location which makes the consequences of a failure scenario completely left to luck, i.e. all the components of an app stack could be located on 1 site because DRS decided to balance the load (this is were you wonder "Drs rules ?").
-No DR plan in place so there is no way to easily power on replicas of cross replicated VMs on the first site. Remember that the VMs running on the partitioned site hold a lock on their files as they are still running on their respective hosts.
-No backup or external link to remote into the second site (the good stuff).

_So, quick summary of the battlefield_: We have half of our infrastructure down and no way to connect to the hosts, BUT the very good thing is that the storage synchronised which saved me a major proper hassle.

Anyway, things being the way they are I had to work with what I had. My 2 major objectives were:

1. **Recover the VMs from the second site to the first** site in order to restore service asap as we didn't know how long it would take for the ISP to fix the fiber (could be an hour, could be a week...).
2. **Avoid at all cost having duplicate similar VMs** (Infrastructure 101 > Big no-no). This could happen if your second site came back to life with the VMs still running after restoring them on the first site. This scenario could potentially be very destructive as it is more than likely that you would end up with corrupted data, leaving a restore from backup your only solution to recover, which would take a LOT more time.

Here was the plan to recover safely on the first site:

1. Send someone with a laptop to the second site to connect locally to the vSphere hosts one by one and do the following:

- Shut down all the VMs.
- Unregister them from the inventory.
- Place the host in maintenance mode.

As mentionned above, this action is of major importance as it released the locks on the VM files (remember: storage synchronized) and prevented turning up with 2 sets of similar VMs once the second site would come back.

2. Recover the VMs on the hosts in the first site:

- Place the pathes to the .vmx files of the disconnected VMs into a variable in PowerCLI for later use when I will need to register them. If you remove the hosts straight away you won't know which VMs were running nor on which datastore they reside and then good luck with the "treasure hunt for vmx files".

```Powershell
$PartitionedVMHosts = Get-VMHost | where {ConnectionState -eq "Disconnected" -or ConnectionState -eq "NotResponding"}

$VMsToRecover = $PartitionedVMHosts | Get-VM | where powerstate -eq poweredon | select @(l="VM";e={$_}),@(l="Folder";e={$_ | Get-Folder})
```

- Remove from the vCenter inventory the hosts of the second site being in a disconnected state.

```Powershell
$PartitionedVMHosts | Remove-VMHost -Confirm:$false
```

- Register the VMs previously running on the second site on the hosts in the first using the variable mentionned above.

I don't pay attention to the resource pools here as there is none configured but it is something you may want to consider in a different environment.

```Powershell
$RP = Get-Cluster | Get-ResourcePool

$VMsToRecover | ForEach-Object {New-VM -Name $_.vm.name -ResourcePool $RP -VMFilePath $_.VM.extensiondata.config.files.vmpathname -location $_.folder.name | Start-VM -Confirm:$false}
```