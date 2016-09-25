---
layout: post
published: false
title: 'Snapshot consolidation: vsphere 5 vs vSphere 6'
---
vSphere 6 came with a train of new features , the biggest ones like Vvol or new maximums being the face of the marketing campaign, lot's of others "less cool" at first glance were less promoted like the new snapshot consolidation mecanism.

Prior to vSphere 6 the consolidation mecanism  worked such a way that it could lead to issues where the consolidation would fail and retry over and over again and could lead to crazy long stun times with unresponsive guest OS.

Let's take a look at the process of snapshot consolidation on a high IO virtual machine in vSphere 5 and in vSphere 6.

When I say "high IO VM" I mean the VM's write to disk rate is greater than its consolidation rate.

The VM is made of one base VMDK and currently running on one snapshot.  
The administrator orders to delete all snapshots o the VM.

-----

## vSphere 5

1.A helper snapshot is created and all IOs are redirected to this snapshot
2.The first snapshot is merged into the base VMDK (in the meantime the VM writes to the helper file)
3.An estimate of the time required to merge the helper is made. If it is under 12 seconds the VM is stunned to stop all IOs and the helper is merged into the base VMDK
4.If it is over 12 seconds, a new helper is created and all IOs are redirected to it
5.The previous helper snapshot is merged into the base VMDK (in the meantime the VM writes to the new helper file)
6.Back to step 3 for a maximum of 10 iterations, at every iteration the timeout is increased (5 mins, 10 mins, 20 mins, ...)

There we can get into an endless loop ending in a "maximum consolidate retries was exceeded for scsix:x" error in ESXi and the snapshots never consolidate for this VM.

### Why it is bad if it fails
This issue is bad, if the consolidation keeps failing the VM runs on snapshot all the time, the host spends time doing the same useless thing over and over again, ...  

### Why it can be worse if it succeeds after x iterations
At each consolidation iteration, the maximum stun time is raised (step 4). So at first the stun time must be less than 12 seconds

Sometimes it can work if for example the VMs calms down at night and has less activity, then the consolidation can catch up on the write rate and the consolidation succeeds.

The consolidation can also be forced by shutting down the VM, if it doesn't work in this case then something's not right.