---
layout: post
title: What's new in BDRSuite v5.3
description: null
date: 2022-07-20T07:29:27.440Z
nobanner: no
fb-img: null
---

What used to be the wild west several years ago is now a pretty stable and settled landscape of Backup software vendors, Vembu being one of them with BDRSuite v5.3 that was released recently. The company adopted a more aggressive release cycle with BDRSuite 5 to address clients feature requests and security fixes more actively. That new version follows this cycle as it is distributed only 3 months after [./2022-04-26-bdrsuite-v5.2-brings-more-cloud-capabilities.md](BDRSuite v5.2) and brings a number of improvements to the product that may benefit all new and existing customers.

## File Server & Endpoints backup integrated into BDRSuite Backup Server UI

While backing up virtual machines and guest OS files has been the bread and butter of the company, the product evolved into protecting a wider range of data types with Cloud instance or Microsoft 365 integration. It is now possible to add Windows and Linux file servers to the Data Source as well as configure file & folder level backup directly from the BDRSuite Backup Server console.

The backup agents required to run on the target can be automatically deployed by the BDRSuite Backup Server if manually installing them is inconvenient. Admins will benefit from this feature as they will be able to manage backup & recovery operations of a large number of machines from the centralized BDRSuite Backup Server.

You can also configure File anf Folder Backup of multiple Windows or Linux endpoints from the BDRSuite Backup Server console. While the agents can be manually or automatically installed on the target endpoints, you can also add them in bulk using a CSV file.

## Azure Blob object storage support

When creating a new object storage repository, you can now select Azure blob storage. Azure Blob storage is an object storage solution for cloud workloads. It is optimized for storing large amounts of unstructured data (data stored in bulk with no particular organization, such as text, pictures, binary data...). Blob storage can be accessed by clients via http/https with Azure Storage REST API, Azure PowerShell, Azure CLI, or an Azure Storage client library.

In BDRSuite v5.3, Microsoft Azure Blob object storage can be used to store Primary backup data and backup copy data.

![Azure Blob object storage support](/img/2022-07-20-16-19-54.png)

## Active Directory Integration

In the latest BDRSuite v5.3, the backup Server now integrates with Active Directory. Meaning you can import and add Active Directory or LDAP users to the BDRSuite Backup Server. Doing so, managing user access will better integrate with organizations policies, simplify organization and reduce the risk of errors. It will also mitigate security vulnerability during employees offboarding operations as a disabled or deleted AD account cannot access the BDRSuite server. Like local users, AD users can be granted various access levels to the Backup infrastructure.

I expect this change to receive a warm welcome from administrators as this is a quality of life improvement on top of improving security.

![BDRSuite Active Directory Integration](/img/2022-07-20-16-21-27.png)

## Integrity Check on VMware ESXi Server

You can now run the automated boot check on VMware ESXi hosts to confirm the recoverability of the backup machines.

![Integrity Check on VMware ESXi Server](/img/2022-07-20-16-25-42.png)

## Other enhancements

The release notes document a number of smaller changes brought in BDRSuite v5.3:

* Backup data retention for deleted/excluded VMs
* Performance improvements in the server rebuild process
* Backup support for the Microsoft 365 accounts enabled with Multi-Factor Authentication(MFA)
* Parallel backup processing of Microsoft 365 & Google Workspace users
* Option to exclude Microsoft 365 mailbox folders from backup
* Breadcrumbs view for SharePoint site & Teams data restore
* Download Microsoft 365 mail data in EML and MBOX format
* Microsoft 365 & Google Workspace mail recovery based on time range
* Search option for Microsoft 365 & Google Workspace emails during the restore
* Parallelly initiate PST export for multiple Microsoft 365 & Google Workspace user’s mail data
* Logs download for Microsoft 365 & Google Workspace backups
* Enhanced backup progress window for Google Workspace backup
* Tree view for Google Drive data restore
* Enhanced report for Google Workspace backups
