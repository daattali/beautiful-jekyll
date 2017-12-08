---
layout: post
published: false
title: ''
---
In this article I would like to cover a failure scenario that I recently came across and that I suspect is not that common for several reasons. The environment is made of 2 sites in a metro cluster sharing a virtualised storage over a multiplexed fiber. Half of the wavelength used for storage and the rest used for VLANs. Following an incident somewhere along this fiber, it is believed that only some of the wavelengths went down. The storage nodes on the 2 sites could communicate fine after a few minutes following the outage but the only vCenter located on the first site could not reach the ESXi hosts located on the second site nor could the VLANs.

In short, everything running on the second is isolated in a bubble and cannot be reached.

So we are left with half of the cluster in a partitioned state but a full access to the storage from all hosts across the 2 sites. A few things to note to fully understand the extent of the situation:

-The metro cluster was configured with DRS with no particular attention given to virtual machine location which makes the consequences of a failure scenario completely left to luck, i.e. all the components of an app stack could be located on 1 site because DRS decided to balance the load (this is were you scream "Drs rules ffs!").
-No DR plan in place so there is no way to easily power on replicas of cross replicated VMs on the first site. Remember that the VMs running on the partitioned site hold a lock on their files as they are still running on their respective hosts.
-No backup or external link to remote into the second site (nervous laughter starts).

_So, quick summary of the battlefield_: We have half of our infrastructure down and no way to connect to the hosts, BUT the very good thing is that the storage synchronised which saved me a major proper hassle.

Anyway, things being the way they are I had to work with what I had. My 2 major objectives were:

1. **Recover the VMs from the second site to the first** site to restore the services.
2. **Avoid at all cost having duplicate similar VMs** (Infrastructure 101 > Big no-no). This could happen if your second site came back to life with the VMs still running after you restoring them on the first site. This scenario could lead to a catastrophe as it is more than likely that you would end up with corrupted data, leaving a restore from backup as your only solution to recover which would take a LOT more time.


1. Send someone to the second site to connect locally to the vSphere hosts one by one and do the following:

- Shut down all the VMs.
- Unregister them from the inventory.
- Place the host in maintenance mode.

This action is of major importance as it released the locks on the VM files (remember: storage synchronized) and prevented to turn up with 2 sets of similar VMs once the second site would come back