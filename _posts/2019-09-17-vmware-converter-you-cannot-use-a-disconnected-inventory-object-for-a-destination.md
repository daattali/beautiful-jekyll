---
layout: post
title: 'VMware Converter: "you cannot use a disconnected inventory object for a destination"'
DATE: 

---
Some vSphere environments are shared by different teams. To give them autonomy we dedicate them resources through the use of resource pools and restricted to them with granular permissions applied to the resource pool, datastore, network folder, VM folder...

For day to day work (manage virtual machines) these permissions are usually enough. However it happens that users need to copy a VM from their test workstation to the vSphere environment (we obviously recommend to create a VM from scratch on vCenter) in which case they can encounter a rather counter-intuitive error message in VMware Converter.

> "you cannot use a disconnected inventory object for a destination"

![](/img/converter-host-perm.png)

To fix this error you need to **add the Read-Only permissions on at least one host in the cluster**.