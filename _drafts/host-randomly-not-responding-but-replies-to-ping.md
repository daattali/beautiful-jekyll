---
layout: post
title: Host randomly not responding but replies to ping
DATE: 

---
In the series of weird and annoying technical issues that I seem to be blessed with, today I bring you one that falls in the category I despise the most, random disconnects.

In short, we removed some 1Gbps cards and added 10Gbps cards to make the cluster homogeneous. The management and VMotion vmkernels were tied to these uplinks. After we did the work on the hardware I reordered the portgroup and uplinks correctly so it matches the newer hosts. Then I quickly realised that the hosts were randomly losing pings and when I rebooted a host I had to restart the management network (not normal at all). 

I had a look at vodb.log on the host and found the following records:

> 2020-04-30T07:25:58.464Z: \[netCorrelator\] 842494443us: \[vob.net.pg.uplink.transition.down\] Uplink: vmnic6 is down. Affected portgroup: Management Network. 1 uplinks up. Failed criteria: 128
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