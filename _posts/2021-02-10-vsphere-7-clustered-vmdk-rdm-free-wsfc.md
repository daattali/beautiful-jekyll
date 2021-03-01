---
layout: post
title: vSphere 7 clustered VMDK - RDM-free WSFC !
DATE: 
subtitle: ''
metadescription: Find out how you can create Windows Server Failover Clusters in vSphere
  7 without RDM with the new clustered VMDK feature.

---
### Background

The end of the raw device mapping tyrannie on Windows Server Failover Clusters (WSFC) is nigh! If you managed virtual environments that contain Windows Clusters, you probably know that these are a different kind of beast compared to your usual virtual machines equipped with thick and thick virtual disks.

WSFC on vSphere has always required the use of RDM disks. This is due to the fact that WSFC uses SCSI-3 PRs (Persistent Reservations) commands to coordinate access to a clustered disk resource. It essentially uses this command to lock the volume so only the active node is allowed to write to it.

But because VMFS has its own locking mechanisms, these SCSI commands are intercepted and discarded with traditional virtual disks. Hence the need for RDM disks acting as a mapping device for the physical LUN.

Managing these RDM disks isn't that big a deal, but it represents an exotic configuration in the environment and you have to be in sync with the storage team, it adds a bunch of LUNs, host [boot times are longer](https://www.vxav.fr/2021-01-25-perennially-reserved-disks-in-the-vsphere-client-ui/)... Things are better since vSphere 6.5 that added the ability to vmotion running WSFC nodes.

### Clustered VMDK

Anyway, vSphere 7.0 brings an amazing new feature called [clustered VMDK](https://docs.vmware.com/en/VMware-vSphere/7.0/com.vmware.vsphere.wsfc.doc/GUID-97B054E2-2EB0-4E10-855B-521A38776F39.html "Clustered VMDK") that allows SCSI3-PR commands issued to a virtual disk, meaning you will no longer need an dedicated physical LUN to spin up a windows failover cluster.

Unfortunately I can't demonstrate it as it is only available on FC backed datastores as the time of this writing and I don't have that in my lab. However, here are a few things and caveats to know about clustered VMDK:

* It is enabled at the datastore level, set the attribute "_Clustered VMDK Supported_" to "_yes_". VMFS-6 required.

![](/img/clusteredvmdk2.png)

* The Windows Cluster Parameter "[_QuorumArbitrationTimeMax_](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/mscs/cluster-quorumarbitrationtimemax)_"_ must be set to 60.
* The Lun backing the datastore must support ATS SCSI commands (usually does).
* The Lun must support Write Exclusive All Resgistrants (WEAR) type reservations.
* The VMDKs must use Eager Zeroed Thick type and VMs must be in compatibility vSphere 7.0 at least.
* Don't present LUNs used for clustered VMDK to host in version lower than 7.0.
* Do not combine clustered and non-clustered VMDKs on the same clustered datastore.
* Dedicate one datastore per WSFC, as in don't share a clustered datastore between multiple WSFC instances.

Here is a small table of the maximums. As you can see it is quite limited so far and only available with FC storage but there is no doubt that future releases will improve those numbers as usual.

![](/img/clusteredvmdk1.png)

There is also a fairly long [list of limitations ](https://docs.vmware.com/en/VMware-vSphere/7.0/com.vmware.vsphere.wsfc.doc/GUID-04626D3C-A305-40BE-A7B9-4E7C7A30BA3D.html)that you can review here. The main ones being:

* Cluster in a Box (CIB) configuration is not supported (You must use anti-affinity DRS Rules to separate VMs and nodes of the cluster on different ESXi hosts.).
* Hot expansion of a VMDK that is associated with a clustered VM is not supported (not sure how that case would be handled).

Note that VMware provided a guide on how to migrate your WSFC enabled RDM disks to clustered VMDK and it's [THERE](https://core.vmware.com/resource/vsphere-7-rdm-shared-vmdk-migration).