---
layout: post
title: What's new in BDRSuite v5.5
date: 2022-11-27T09:58:04.234Z
nobanner: no
fb-img: null
---
BDRSuite is a complete Backup and disaster recovery solution tailored to protect workloads across Virtual, Physical, on-premises, Cloud services, and SaaS applications. The world of data protection kept gaining traction in the past decade with the rise of cloud services and then the threat of Ransomware. BDRSuite carved a place for the company among the leading backup software vendors for the SMB sector with a robust virtual machine backup and recovery solution.

[![BDRSuite download](/img/vembu-download.png)](https://www.bdrsuite.com/vembu-bdr-suite-download/?utm_source=vxav&utm_medium=blog&utm_campaign=download)

BDRSuite v5.5 is a Windows or Linux installer and you can use it unrestricted for free during a **30 days trial period**.

## Support for VMware vSphere v8.x

As you most likely know, VMware launched vSphere 8.0 during VMware Explore 2022 which brought a plethora of new features and enhancements with a new release process. BDRSuite v5.5 supports Backup and Replication for VMs running VMware vSphere v8.x.

## Backup and Recovery of VMware VM Templates

This feature is interesting as it addresses an area of the SDDC that is as old as time; VM templates. BDRSuite for VMware now supports backing up VMware VM Templates. VM Templates will show up in the list of VMware entities that can be selected for backup. You can then configure backup for VM Templates and restore then when required.

![Backup and Recovery of VMware VM Templates](/img/2022-11-27-11-20-39.png)

## ConnectWise Integration

ConnectWise helps MSPs manage their assets and customers. BDRSuite now supports ConnectWise Integration which allows you to create service tickets automatically in ConnectWise Manage for BDRSuite activities. The tickets can be created for various tasks (Backup/Restore/Replication) and different task status (Success/Failed/Warning) on relevant service boards.

![ConnectWise Integration](/img/2022-11-27-11-21-38.png)

## Google Cloud as Backup Repository

I recently wrote a [blog about Google Cloud Storage](https://www.bdrsuite.com/blog/data-protection-with-google-cloud-object-storage/) for BDRSuite in preparation of this announcement. Google Cloud Storage (Object Storage) is now supported in BDRSuite v5.5 to store backup data, backup copy and offsite copy data. Note that it already supported other cloud storage providers like Amazon S3, Azure Blog, S3 Compatible storages such as Wasabi, MinIO, etc.

![Google Cloud as Backup Repository](/img/2022-11-27-11-23-34.png)

## Backup and Recovery of cloud resources

* Google Workspace Shared Drive: BDRSuite v5.5 supports backup and recovery of Shared Drives in Google Workspace Organization for MailBackup, Calendar Backup, Contacts/ Peoples Backup, Google Drive Backup.

* [Microsoft 365 Archive Mailbox](https://www.bdrsuite.com/blog/bdrsuite-v5-5-new-feature-update-how-to-restore-microsoft-365-user-mailbox-to-different-organization/): BDRSuite v5.5 supports backup and recovery of user mails in the Archive Mailbox (In-place Archive) of Microsoft 365.

![BDRSuite Microsoft 365 Archive Mailbox](/img/2022-11-27-11-16-51.png)

* Deduplication for Microsoft 365 User Mails: Reduced bandwidth and storage utilization by using the mail-level deduplication feature at the source while backing up Microsoft 365 user mailboxes. With this, BDRSuite v5.5 avoids transmitting duplicate email data and saves bandwidth and storage.

## Other Enhancements

A number of other important improvements have been added to BDRSuite v5.5 such as:

* **VMware Backup Performance increased by 2x**
* VMware CBT Reset
* Parallel Disk Image Backup
* Parallel Synthetic Full Backup
* Auxiliary Applications for Microsoft 365 Backup
* Restore to a mailbox in different Organization (Microsoft 365 & Google Workspace)
* Restore the backed up user mails directly from Microsoft 365 console through BDRSuite Add-in for Outlook
* Download Restore Logs for Microsoft 365 and Google Workspace
* Breadcrumbs view for OneDrive and Group OneDrive Restore
* Enhanced progress window for Offsite Replication

## BDRSuite v5.5 update

Updating your BDRSuite server is pretty straightforward as usual. However, it is recommended to review the [Software Update Guide](https://www.bdrsuite.com/pdf/release-notes/vembu-bdr-automatic-software-update.pdf) to make sure your scenario is covered and the [Upgrade Checklist](https://www.bdrsuite.com/pdf/release-notes/vembu-bdr-automatic-software-update.pdf) before upgrading to BDRSuite v5.5. Note that the BDRSuite installations below v5.0 should upgrade to v5.0 first before upgrading to v5.5.0 GA.
