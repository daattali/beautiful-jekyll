---
layout: post
title: vSphere 7 clustered VMDK - RDM-free WSFC !
DATE: 

---
### Introduction

The end of the raw device mapping tyrannie on Windows Server Failover Clusters (WSFC) is nigh! If you managed virtual environments that contain Windows Clusters, you probably know that these are a different kind of beast compared to your usual virtual machines equipped with thick and thick virtual disks.

WSFC on vSphere has always required the use of RDM disks. This is due to the fact that WSFC uses SCSI-3 PRs (Persistent Reservations) commands to coordinate access to a clustered disk resource. It essentially uses this command to lock the volume so only the active node is allowed to write to it.

But because VMFS has its own locking mechanisms, these SCSI commands are intercepted and discarded with traditional virtual disks. Hence the need for RDM disks acting as a mapping device for the physical LUN.

Managing these RDM disks isn't that big a deal, but it represents an exotic configuration in the environment and you have to be in sync with the storage team, it adds a bunch of LUNs, host [boot times are longer](https://www.vxav.fr/2021-01-25-perennially-reserved-disks-in-the-vsphere-client-ui/)... Things are better since vSphere 6.5 that added the ability to vmotion running WSFC nodes.

### Clustered VMDK

Anyway, vSphere 7.0 brings an amazing new feature called [clustered VMDK](https://docs.vmware.com/en/VMware-vSphere/7.0/com.vmware.vsphere.wsfc.doc/GUID-97B054E2-2EB0-4E10-855B-521A38776F39.html "Clustered VMDK") that allows SCSI3-PR commands issued to a virtual disk, meaning you will no longer need an dedicated physical LUN to spin up a windows failover cluster.