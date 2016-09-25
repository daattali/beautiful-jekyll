---
layout: post
published: false
title: 'Snapshot consolidation: vsphere 5 vs vSphere 6'
---
vSphere 6 came with a train of new features , the biggest ones like Vvol or new maximums being the face of the marketing campaign, lot's of others "less cool" at first glance were less promoted like the new snapshot consolidation mecanism.

Prior to vSphere 6 the consolidation mecanism  worked such a way that it could lead to issues where the consolidation would fail and retry over and over again and could lead to crazy long stun times with unresponsive guest OS.

Let's take a look at the process of snapshot consolidation on a high IO virtual machine in vSphere 5 and in vSphere 6.

-----

## vSphere 5


