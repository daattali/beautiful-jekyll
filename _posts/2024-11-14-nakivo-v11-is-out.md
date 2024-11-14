---
layout: post
title: NAKIVO v11 with Agentless Proxmox backup and more
date: 2024-11-14T12:42:20.305Z
nobanner: "yes"
fb-img: null
---

The world of virtualisation has been shaken up in the last year and a half with Broadcom acquiring VMware and pushing many customers to look for alternatives, along with the growing need for multi-tenancy and saas. Following its 3 months release cycle, Nakivo recently released major version NAKIVO Backup & Replication v11 which is available already. This new version brings several interesting features to stay at the tip of the spear including Agentless Backup for Proxmox VE, Backup to Cloud for Microsoft 365, Source-Side Backup Encryption and more.

[![Try Nakivo v11](https://www.nakivo.com/res/images/pages/vmware-backup/v2/ques.webp)](https://www.nakivo.com/resources/releases/v11/)

## Agentless Backup for Proxmox VE 8.0 to 8.2

The Proxmox hypervisor has gained a great deal of traction since Broadcom acquired VMware and customers started feeling it through licenses revocations and price increases. As a result, Nakivo added support for Proxmox to offer those organisations a way out on the backups front. 

* Discover supported Proxmox VE items: clusters and standalone hosts (nodes) and add them to the Inventory
* Back up Proxmox VE VMs
* Copy Proxmox VE VM backups
* Recover Full Proxmox VE VM from backups
* Perform File recovery from Proxmox VE VM backups to source or custom VMs
* Perform Object recovery from Proxmox VE VM backups to a custom destination
* Perform Universal Object recovery from Proxmox VE VM backups for a VM disk
* Perform Export disks from Proxmox VE VM backups.

## Microsoft 365 Backup to Cloud

With Nakivo v11, you can back up Microsoft 365 data to and from public clouds like Amazon S3, Wasabi, Azure Blob, Backblaze B2 and S3-compatible. It is now supported to recover from all incremental with periodic full data storage type repositories.

Enable encryption and immutability for backups stored locally or in the cloud to ensure data remains intact and recoverable in case of accidental deletions or ransomware attacks.

## Federated Repository

A Federated repository is a backup repository that consists of one or more existing backup repositories (members) with identical attributes. It can be scaled horizontally to consume more backup repositories without interrupting data protection workflows. You can now create those federated repositories as destinations for new and existing backup or backup copy jobs.

## Backup Encryption

Nakivo v11 brings source-side backup encryption. It allows you to protect backups, backup copies and solution configurations against breaches by encrypting data before it leaves the source. This can apply across various backup destinations, including local folders, cloud storage, NAS and tape, to maintain data integrity and security.

It is also now possible to integrate the solution with AWS KMS for enhanced key management and password loss protection. 

## Backup from NetApp Storage Snapshots

To reduce the overhead and impact on hosts and the vSphere environment, you can now backup VMware vSphere VMs directly from NetApp storage snapshots.

Seamlessly integrate with NetApp FAS and AFF storage arrays to enhance data management capabilities. It will also speed up data recovery to meet recovery time objectives (RTO) and recovery point objectives (RPO).


## Other improvements

* Comprehensive localization support in Spanish
* The MSP Console v2 is now available to MSPs as the centralized control hub that enables service providers to manage the entire cloud backup and replication processes.
* Adding a layer of security with two-factor authentication (2FA) is now available in all product editions.
* Real-time replication is now available for VMware vSphere 8.0.
* The recovery points can now be made immutable in the Backup Repositories located in the NEC HYDRAstor deduplication appliances.

Also note that, starting from NAKIVO Backup & Replication v11.0, the solution can no longer be installed on Raspberry Pi.

## Wrap up

With Nakivo Backup & Replication v11, the focuse is back on value add features and improves proxmox support for those customers that migrated or are migrating away from VMware. MSPs keep getting more value out of the product thanks to enhanced multi-tenancy capabilities and Microsoft 365 can finally be backed up to cloud, which makes a lot of sense for those customers using it.

As usual, updating to Nakivo v11 is as easy as it gets and you can find all the details you need in the [documentation](https://helpcenter.nakivo.com/User-Guide/Content/Deployment/Updating-NAKIVO-Backup-and-Replication/Updating-NAKIVO-Backup-and-Replication.htm).