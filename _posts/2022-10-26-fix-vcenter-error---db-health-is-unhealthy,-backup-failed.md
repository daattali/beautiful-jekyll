---
layout: post
title: Fix vCenter error - Db health is UNHEALTHY, Backup Failed
description: null
date: 2022-10-26T11:18:07.547Z
nobanner: "yes"
fb-img: null
---
As you know vSphere 8.0 was recently announce and brought numerous features and improvements that you can find in this [Nakivo blog](https://www.nakivo.com/blog/whats-new-in-vmware-vsphere-8-0/). Because I had a bit of time off, I decided to look into upgrading my lab to test it out. It turns out only NSX 4.0 is compatible with vSphere 8.0 and I run NSX-T 3.x, also VMware Cloud Director is not yet in the interoperability matrix so I didn't go ahead since I need this environment to match the requirements for [CAPVCD](https://github.com/vmware/cluster-api-provider-cloud-director) for my day job.

Eitherway, I still upgraded my VCSA as I hadn't done it in a while so I backed it up beforehand as a good student. Well, not so good apparently as the backup would fail for the following reason:

`Db health is UNHEALTHY, Backup Failed.Disable health check to take backup in current state.`

![Db health is UNHEALTHY vcenter backup](/img/2022-10-26-13-33-47.png)

I found details about this in KB86084. This relates to the "Database Consistency Checker" (dbcc) tool that is used to check the database not being up to date with the vCenter database schema. After a vCenter upgrade, the scema of the database is updated but not dbcc, meaning there can be new/modified tables that it is not aware of and makes it error out. It can also occur when a vSAN service writes data in new tables that are also not in dbcc.

The way to fix this is to refresh the latest database schema in DBCC.

* SSH into your vCenter appliance as root and enter the shell by typing `shell` and enter.
* Update the schema of the embedded database with the `dbcc` cli tool.

`/usr/bin/dbcc -fbss embedded`

The output should look like so if it is successful.

![dbcc update vcsa backup schema](/img/2022-10-26-13-34-25.png)

* Then you can try again backing up the VCSA with `DB Health Check` enabled and it should succeed.

![db healthcheck](/img/2022-10-26-13-36-09.png)

---

This blog is only focused on the backup of the vCenter Server appliance itself. If you are looking for options on how to protect your vSphere and VMware Cloud Director workloads, [Nakivo Backup & Replication](https://www.nakivo.com/) offers capabilities to back up vSphere VMs and VCD objects such as vApps, individual VMs and vApp metadata and ensure that remote workloads can be recovered in case of a data loss event. Not a lot of vendors out there support VCD so kuddos to that.
