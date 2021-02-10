---
layout: post
title: vSphere 7 clustered VMDK - RDM-free WSFC !
DATE: 

---
The end of the raw device mapping tyrannie on Windows Server Failover Clusters (WSFC) is nigh! If you managed virtual environments that contain Windows Clusters, you probably know that these are a different kind of beast compared to your usual virtual machines equipped with thick and thick virtual disks.

WSFC on vSphere has always required the use of RDM disks. This is due to the fact that WSFC uses SCSI-3 PRs (Persistent Reservations) commands to coordinate access to a clustered disk resource. It essentially uses this command to lock the volume so only the active node is allowed to write to it. 

But because VMFS has its own locking mechanisms, these SCSI commands are intercepted and discarded with traditional virtual disks, hence the need for RDM disks acting as a mapping device for the physical LUN.  