---
layout: post
title: Proxmox VM backups with Nakivo
description: null
date: 2024-03-22T13:07:20.643Z
nobanner: "yes"
fb-img: null
---

The announcement of VMware's acquisition by Broadcom marked a significant shift in the dynamics of the virtualization market. While VMware has long been synonymous with virtualization excellence, Broadcom's acquisition introduces a level of uncertainty and apprehension among businesses reliant on VMware's suite of products. The drastic changes initiated by the chip maker and the steep license price increases have left customers and the community underwhelmed by this change of direction for a product they loved and respected so much.

As a result, alternative virtualization platform are gaining traction from customers looking to consider their options should they be forced to leave VMware because of budgetary reasons most likely. One of these solutions is Proxmox, an Open-Source hypervisor that is very popular with home labbers and some SMBs that have the in-house knowledge to maintain the platform.

Nakivo recently released Proxmox Backup Solution to protect workloads running in Proxmox. As usual, you can download **Nakivo Backup & Replication** with a 15-day free trial.

[![Try Nakivo Proxmox Backups](/img/SCR-20230705-loh.png)](https://www.nakivo.com/proxmox-backup/)

## Nakivo Proxmox Backup features

Nakivo Proxmox Backup Solution provides agent-based backups with all the benefits of the long-standing backup solution backing the feature such as:

- Full and incremental, image-based backup of Proxmox VM data.
- Backup copy to remote sites, public clouds, other S3-compatible platforms and tape.
- Instant granular recovery of files and app objects to the original or a custom location.
- Ransomware protection with data immutability.
- Flexible storage and retention options.
- Malware protection by scanning backups for viruses and ransomware before recovering the data.
- Full recovery of Proxmox VM data to an identical VM on the same hypervisor using
Bare-Metal Recovery.
- Advanced scheduling capabilities with a calendar dashboard, policy rules
to automatically back up the data that match specific criteria, pre-
and post-job scripts as well as integration with third-party tools via HTTP API.

![nakivo for proxmox](/img/nakivo-proxmox.png)

## Technical requirements

The prerequisites to leverage Nakivo Proxmox Backup Solution are lightweight and will already be met by most environments already using Nakivo.

- A physical machine agent/Transporter should be installed in each discovered VM.
- Hypervisor running Proxmox 8.0 and newer.
- Protected virtual machines should run an Operating System supported by Nakivo Backup and Replication for physical machine backup.

## Wrap up

With Nakivo Proxmox Backup Solution, the company is making sure its customers can leverage the backup capabilities on top of Proxmox hypervisors and offering their VMware customers considering a shift to Proxmox some continuity by leveraging the same platform they are already familiar with.

As usual, setting up Nakivo is as easy as it gets and you can find all the details you need in the [documentation](https://helpcenter.nakivo.com/User-Guide/Content/Deployment/Updating-NAKIVO-Backup-and-Replication/Updating-NAKIVO-Backup-and-Replication.htm).