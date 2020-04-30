---
layout: post
title: Host randomly not responding but replies to ping
DATE: 

---
In the series of weird and annoying technical issues that I seem to be blessed with, today I bring you one that falls in the category I despise the most, random disconnects.

_TL,DR: Random ESXi disconnects after NIC replacement. The fix was to remove and recreate the management vmkernel (also did vMotion just in case)._

In short, we removed some 1Gbps cards and added 10Gbps cards to make the cluster homogeneous. The management and VMotion vmkernels were tied to these uplinks. After we did the work on the hardware I reordered the portgroup and uplinks correctly so it matches the newer hosts. Then I quickly realised that the hosts were randomly losing pings and when I rebooted a host I had to restart the management network (not normal at all).

I updated the driver and firmware of the NIC but it wasn't that.

I had a look at vodb.log on the host and found the following records:

> **2020-04-30T07:25:58.464Z: \[netCorrelator\] 842494443us: \[vob.net.pg.uplink.transition.down\] Uplink: vmnic6 is down. Affected portgroup: Management Network. 1 uplinks up. Failed criteria: 128**
>
> 2020-04-30T07:25:58.464Z: \[netCorrelator\] 842494494us: \[vob.net.vmnic.linkstate.down\] vmnic vmnic6 linkstate down
>
> 2020-04-30T07:26:00.002Z: \[netCorrelator\] 844023129us: \[esx.problem.net.redundancy.lost\] Lost uplink redundancy on virtual switch "vSwitch0". Physical NIC vmnic6 is down. Affected port groups: "Management Network"
>
> 2020-04-30T07:26:05.454Z: \[netCorrelator\] 849485075us: \[vob.net.vmnic.linkstate.up\] vmnic vmnic6 linkstate up
>
> 2020-04-30T07:26:05.556Z: \[netCorrelator\] 849587112us: \[vob.net.pg.uplink.transition.up\] Uplink:vmnic6 is up. Affected portgroup: Management Network. 1 uplinks up
>
> 2020-04-30T07:26:07.002Z: \[netCorrelator\] 851022990us: \[esx.clear.net.connectivity.restored\] Network connectivity restored on virtual switch "vSwitch0", portgroups: "Management Network". Physical NIC vmnic6 is up
>
> 2020-04-30T07:26:22.578Z: \[netCorrelator\] 866608948us: \[vob.net.pg.uplink.transition.up\] Uplink:vmnic6 is up. Affected portgroup: Management Network. 1 uplinks up
>
> 2020-04-30T07:26:24.002Z: \[netCorrelator\] 868023092us: \[esx.clear.net.connectivity.restored\] Network connectivity restored on virtual switch "vSwitch0", portgroups: "Management Network". Physical NIC vmnic6 is up
>
> 2020-04-30T07:31:31.512Z: \[GenericCorrelator\] 1175533427us: \[vob.user.dcui.network.restart\] Restarting Management Network
>
> 2020-04-30T07:31:31.512Z: \[UserLevelCorrelator\] 1175533427us: \[vob.user.dcui.network.restart\] Restarting Management Network
>
> 2020-04-30T07:31:31.512Z: \[UserLevelCorrelator\] 1175533800us: \[esx.audit.dcui.network.restart\] A management interface Management Network has been restarted. Please consult ESXi Embedded and vCenter Server Setup Guide or follow the Ask VMware link for more information.

I googled this "**_Failed criteria 128_**" that I had never encountered before and people were recommending all sorts of things like reverting to async driver but my other hosts that work fine have the native driver so didn't make sense. I think it was in an article not directly related that someone suggested recreating the management vmkernel because the hardware replacement can cause conflicts with the mac address of the vmkernel, issued based on the mac of the original NIC.

I tried removing and recreating the management vmkernel and here it was, all fixed! You need to log on the DCUI as you will lose your SSH session once you remove the uplink.

1. **Remove the vmkernel**

<code>esxcli network ip interface remove -i vmk0</code>

2. **Recreate the vmkernel**

<code>esxcli network ip interface add -i vmk0 -p "Management Network"</code>

3. **Reconfigure the network**

Now you can go back to the DCUI to configure your management interface like you would the first time.