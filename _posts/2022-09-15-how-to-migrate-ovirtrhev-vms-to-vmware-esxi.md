---
layout: post
title: How to Migrate oVirt/RHEV VMs to VMware ESXiSelect
description: Learn how to migrate VMs from oVirt/RHEV to VMware ESXi using Vinchin Backup and Recovery
date: 2022-09-15T09:36:11.686Z
nobanner: yes
fb-img: null
---
V2V (Virtual-to-Virtual) is a common occurence for IT users anymore, especially for those working in big organizations. Since virtualization technology grows in the cloud computing era, many prefer to build a multi-hypervisor environment to better handle massive projects with different system requirements. Or, just simply migrate from one platform to another for a more satisfying operation experience. These all require V2V.

Many vendors on the market offer virtualization solutions since it is an old corner of the IT landscape by now. Among all, VMware stands as the most popular one with the VMware vSphere product suite being widely used in the world due to its complete solution set and advanced features that meet most needs of a company. However, not everyone’s first choice will be it, since deployment cost, functionality, and actual production environment all need to be taken into deep consideration when choosing the best IT solution.  Maybe when the time comes, certain changes need to be made for the better. Even though a number of companies are weighing the effort of moving off of VMware following the Broadcom acquisition, let's stay positive and talk about migrating data from oVirt/RHEV to VMware.

## How to choose a V2V migration tool?

VMware vCenter Converter was the official tool provided by VMware to do fast P2V/V2V from physical machines/other virtualizations to VMware. However, in February, it had been discontinued by VMware and now is unavailable to download. We don’t know whether there will be a replacement but a powerful alternative is needed in the meantime to help users make a smooth transition.

For VMware V2V, many third-party vendors offer this feature, but none can match the compatibility offered by [Vinchin Backup & Recovery](https://vinchin.com/en/cross-platform-backup-and-recovery.html?utm_source=vxav&ad_uuid=447189b2-9b4f-5534-0fef-a3f67d10025c). Designed as a data backup and restore software for enterprise-grade IT environments especially those with workloads on virtual machines, it also supports advanced V2V across 10 virtual platforms including **VMware**, **Citrix Hypervisor** (formerly XenServer), **XCP-ng**, **oVirt**, **Red Hat Virtualization** (RHV), **Oracle Linux Virtualization Manager** (OLVM), **OpenStack**, **Sangfor HCI**, **Huawei FusionCompute**, and **H3C CAS/UIS**. All are configurable in a centralized web-based management console.

## How it works when you are performing cross-platform recovery with Vinchin Backup & Recovery?

The following diagram illustrates the 6 steps of how to perform cross-platform recovery:

![6 steps of how to perform cross-platform recovery with Vinchin](/img/2022-09-15-11-42-04.png)

* Back up your VMs from Virtual Platform A with Vinchin Backup & Recovery.
* Select the desired restore point of any VM you wish to recover to Virtual Platform B.
* Set Virtual Platform B as the recovery destination.
* Customize recovery strategies with simple clicks if needed.
* Review your configurations and submit the recovery job.
* Original VM recovered and up running on Virtual Platform B.

## How to migrate oVirt/RHEV VMs to VMware ESXi with Vinchin Backup & Recovery?

With Vinchin Backup & Recovery, any V2V job can be easily configured in 4 steps. Let’s take Red Hat Virtualization to VMware as an example here.

### Step 1: Choose a restore point

Open the Vinchin backup server web console, and go to **VM Backup > Restore** to configure a full restore job. If you have previously used the software to do RHV backups, all saved restore points will be shown in the Restore Point list. Pick the one that you want to move to VMware.

![v2v Choose a restore point](/img/2022-09-15-11-43-12.png)

### Step 2: Choose a restore destination

In the Target Host list, all added virtual infrastructure in the backup environment will be shown. For VMware V2V, you can simply select a VMware host as the restore destination, and re-allocate the VM resources in the VM Configuration section.

![Vinchin restore destination](/img/2022-09-15-11-43-34.png)

By the way, compared with vCenter Converter, Vinchin Backup & Recovery sets no strict limitation on Linux V2V. No matter whether it’s the Windows or Linux OS you are running on the source VM, the V2V job can all be configured in the same flexible way.

### Step 3: Set up the restore strategy

Configure general strategies including restore time and transmission mode for the restore job.

![Vinchin restore strategy](/img/2022-09-15-11-43-59.png)

### Step 4: Review the configurations and submit the job

Once submitted, the restore job will automatically run. Wait for the restore to complete, and you can get the VMware operation journey started with all the old RHV data!

Also, besides regular VM full restore, **cross-platform instant restore** is supported by the software. If you need to quickly restore the business from a crashed virtualization to another in a multi-hypervisor environment in less than 1 minute, the feature is just the one you need most. Its configurations are also as simple as that of a full restore job.

## Wrap up

Vinchin Backup & Recovery matches the existing and growing virtualization demands of the entire IT infrastructure and combines them well. Supported by the integration of 10+ virtual platforms, whether you want to remove an existing virtual platform and migrate data to a new one, or are just in need of switching services across multiple virtual platforms, you can both rely on the Vinchin solution to easily reach your goals, no matter how many virtual platforms you have in the data center.

When the data of a certain virtual machine is unavailable due to a disaster, you can still seamlessly restore the initial VM backups to a new virtual platform using on-premises backups, offsite backup copies, or archived data on the cloud, and use the certain part of data just like you're accessing the original VM.

**Vinchin Backup & Recovery** offers a [60-day full-featured trial](https://vinchin.com/en/support/vm-backup-free-trial.html?utm_source=vxav&ad_uuid=39561e89-9f28-e494-8a9d-094b276ed317). Download to experience its ease of use and efficiency yourself, if you need to do V2V migration from other virtualizations to VMware.
