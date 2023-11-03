---
layout: post
title: Major release BDRSuite v7.0.0
date: 2023-11-03T09:58:04.234Z
nobanner: no
fb-img: null
---
After communicating only about a couple months ago about the Release Candidate of BDRSuite v7.0.0, the data protection company is rolling the major version to its customers. 

## BDRSuite v7.0.0 Download Link:

BDRSuite v7.0.0 is now ready for download and live on the official website - [Download BDRSuite v7.0.0](https://www.bdrsuite.com/vembu-bdr-suite-download/)

Note that the installer available on the above link only supports fresh installation. If you want to upgrade your BDRSuite Backup Server's version then refer to the [Software Upgrade Guide](https://www.bdrsuite.com/pdf/release-notes/vembu-bdr-automatic-software-update.pdf).

BDRSuite v7.0.0 is a Windows or Linux installer and you can use it unrestricted for free during a **30 days trial period**.

You can also use the BDRSuite Docker image to install the server as a container in your infrastructure. More information in the [documentation](https://www.bdrsuite.com/guide/vembu-bdr-suite/7-0/en/container-deployment.html).

## What's new in BDRSuite v7.0.0

To find a list of the new features and enhancements of BDRSuite v7.0.0, check out my [blog for the Release Candidate](./2023-08-28-bdrsuite-v7.0.0-RC-major-prerelease.md) that goes through the list.

On top of that, this new release includes interesting improvements to the product such as:

- **PostgreSQL Backup and Recovery**: BDRSuite v7.0.0 supports backups for PostgreSQL databases. This includes application-level backups, customizable backup policies, incremental backups, and efficient data protection for PostgreSQL database.
- **File Share Backup and Recovery**: BDRSuite v7.0.0 also supports backing up file shares hosted on NAS devices, Windows, and Linux machines. The usual features can be leveraged here with flexible scheduling options, retain backup data, and restore files/folders as needed.
- **Two-Factor Authentication (2FA)**: Given the trend of Ransomware targeting Backup servers as prime citizens, I am glad to see this one make it in the product. You can now improve security in your BDRSuite Servers with Two-Factor Authentication, ensuring only authorized individuals can login to the BDRSuite Backup Server web-console and access your critical backup jobs. Two Factor Authentication is enabled for all user accounts on the server. You can customize the two-factor authentication for individual users from the Cloud DR Server Tile -> Users menu.
- **Import Backup data**: Following up on the previous point about big-bad scenarios (e.g. Ransomware), you can now easily import backups to a new backup server from a backup repository. This can be useful if you encounter a failure of the backup server for instance. In this case, you can import backups from another backup server or if the backup job has been deleted but the backup data is retained in the backup repository.
- **File Level Recovery to Source Machine**: Previously, the FLR feature only supported files restore to the location on the backup server machine. In BDRSuite v7.0.0, you have the option to restore files/folders to the source machine directly, to the same or a different location. This enhancement simplifies data recovery and ensures that files are back where they need to be.

A lot more improvements includes the following from the release notes:

- Centralized Backup for Microsoft SQL, MySQL, and PostgreSQL Database
- Flexibly Add Folder Path as Backup Repository
- Automatic Backup Agent Installation from BDRSuite Backup Server
- Offsite copy support for backup jobs stored in object storage repository
- Standalone Tape Library Support
- Email Notifications to EndUser’s MailID associated with their Endpoints
- Missed Backup Schedule Report

## Installing BDRSuite v7.0.0

[Download BDRSuite v7.0.0](https://www.bdrsuite.com/vembu-bdr-suite-download/) and install it on a new dedicated machine or upgrade your environment by following the [Software Upgrade Guide](https://www.bdrsuite.com/pdf/release-notes/vembu-bdr-automatic-software-update.pdf).

## Wrap up 

BDRSuite offers a reliable and efficient way to backup and protect various virtual machines (KVM, cloud, vSphere, Hyper-V...) and their data. It ensures that your VMs are backed up regularly, allows for flexible recovery options, and helps you meet your business’s recovery objectives (RTO & RPO).
