---
layout: post
title: How NAKIVO Backup & Replication can help you with Ransomware
DATE: 
subtitle: ''
metadescription: Learn how NAKIVO Backup & Replication can help you protect your data
  from Ransomware

---
Ransomware have been part of the IT landscape for a long time now, however, it has become more prominent in the last two years with an ever increasing number of attacks that get more and more clever over the iterations. In this blog we will see how [Nakivo Backup and Replication ](https://www.vxav.fr/2021-09-27-nakivo-backup-and-replication-for-vmware-and-more/)can help you mitigate the risk of data loss in case of Ransowmare attack.

We already talked about vSphere environments in the Ransomware landscape in a [previous blog](https://www.vxav.fr/2021-09-29-vsphere-environments-in-the-ransomware-landscape/) and what VMware is doing about it.

Before getting stuck in, note that you can get an unrestricted 15-days free trial of Nakivo Backup and Replication. Check out [this blog ](https://www.vxav.fr/2021-10-19-backup-and-restore-vms-with-nakivo/)for guidance on how to get started with it.

[![](/img/2021-10-18_11h14_34.png)](https://www.nakivo.com/resources/download/trial-download/)  

### Air-Gapped Backups

First off, implementing a solid backup infrastructure is paramount to ensure that you have access to backups in case of recovery post ransomware. However, ensuring that the backup infrastructure is secured and isolated from the rest of the network is even more important as it will be no use if your backups have been hit as well. This is what we call air-gapped backups. This can be achieved through network isolation or by using the backups to tape feature of NAKIVO Backup and replication.

![](/img/nakivo-3-1.png)

### Immutable repository

The other area to look out for is Backup Immutability. NAKIVO Backup & Replication allows you to make the recovery points in repositories immutable for local folders and S3 storage. 

When immutability is enabled, the recovery points are stored using the _write-once-read-many_ (WORM) model. The result is that you make recovery points immutable for x days. The recovery points remain immutable for the specified number of days, effectively protecting them from ransomware attack targeting backup systems.

![](/img/nakivo-3-2.png)

### Hardened Virtual Appliance

NAKIVO Backup & Replication [v10.5 (currently in beta as of October 2021)](https://www.nakivo.com/fr/resources/releases/10.5-beta/) offers the Hardened Virtual Appliance (VA). A simple way to deploy NAKIVO Backup & Replication and protect data against ransomware. 

You can simply deploy the NAKIVO Backup & Replication as a pre-configured virtual appliance powered by Ubuntu Server and protect your data from deletion and encryption by ransomware. Backups sent to a repository deployed as part of the VA can be made immutable for a specified period of time.