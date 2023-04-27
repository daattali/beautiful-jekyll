---
layout: post
title: Release of BDRSuite v5.6
date: 2023-04-27T16:00:20.305Z
---

Data protection and recovery remains a critical component of the SDDC in most organizations as losing data due to an outage with no restore capabilities can have catastrophic consequences. Keeping up with current trends is paramount to Backup vendors as ransomware attacks become more and more sophisticated. Modern cloud services as part of data protection policies offer flexibility and security to ensure a consistent set of the backed up data. Another batch of customers requested features were delivered in BDRSuite v5.6 with a number of additions to the product.

[![BDRSuite download](/img/vembu-download.png)](https://www.bdrsuite.com/vembu-bdr-suite-download/?utm_source=vxav&utm_medium=blog&utm_campaign=download)

BDRSuite v5.6 is a Windows or Linux installer and you can use it unrestricted for free during a **30 days trial period**.

## What's new in BDRSuite v5.3

It wasn't long ago that [BDRSuite v5.5](./2022-11-27-what's-new-in-bdrsuite-v5.5.md) was released thanks to the more agressive release cycle adopted by Vembu starting with v5.0 in order to bring more features to BDRSuite. This new version focuses on enhancing platforms support and quality of life enhancements. The goal is to offer MSPs a better experience in managing and monitoring tenants jobs from a centralized console.

## Active Directory (AD) Integration for Host Addition and CSV import

BDRSuite now offers support for importing hosts (Windows, Linux, Mac) from AD/LDAP servers. This could be seen as a quality of life enhancement as enabling administrators to add hosts quickly and easily to the list of data sources for backup will likely save them considerable time and effort.

This is done by importing machine details from the AD/LDAP servers. With this feature, multiple machines can be managed for backup and recovery from a single console on the backup server.

While importing hosts through a CSV file was possible for Endpoints in earlier versions, BDRSuite v5.6 now allows the same feature to work with importing Windows and Linux Servers. This automates the bulk host addition process & simplifies host management, making it fast and efficient.

## Backup Templates support for Files/Folders

Backup templates are useful to create a blueprint of an entity to back so it can be reused to save time on configuring options such as scheduling, retention, and exclusion. While templates have been around for a while for VMware, Hyper-V, and Microsoft Windows, BDRSuite v5.6 now supports templates for Files and Folders backups.

## Centralized Backup Management for Mac

In BDRSuite v5.6, support is added for Mac endpoint to backup configuration and restore. SysAdmins can now configure and manage backups directly from a centralized backup server instead of relying on multiple clients.

## Multi-tenancy for File Servers & Endpoints

With BDRSuite v5.6, the latest release now includes multi-tenancy support for File Servers and Endpoints. The goal is to extend the capabilities that were previously available for other products. This feature does enable greater flexibility by allowing administrators and managed service providers to customize BDRSuite to their specific needs for easier management.

IT admins can now group the selected servers and endpoints to create a separate tenant with Read-Only or Restore-Only permission.

## Backup Windows machines directly from Linux BDRSuite Backup Server

BDRSuite v5.6 offers users the capability to directly manage backup and restore operations of Microsoft Windows (DiskImage Backup only). This integration will streamline operations by eliminating the need for separate clients while and managing backups and restores from a single interface. 

## Other enhancements

- Users can now schedule an on-demand incremental backup for a specific host(s)/VM(s) and failed host(s)/VM(s) in a backup job
- List of all Protected Host(s)/VMs in the BDRSuite Backup Server for Host/VM level backup and direct restore
- Microsoft 365 backup support for permanently deleted mails and litigation hold items
- Users can now choose the Azure Environment (Azure Default Cloud, Azure US Government clouds, Azure China) while adding Microsoft 365 Organization
- Users can now add Microsoft 365 Organization with Certificate Based MS Graph API authorization instead of Application secret Key
- End-user self recovery via BDRSuite’s MS Outlook addon and end-user login for SaaS application backup
- Deleted items retention handling for OneDrive, Group OneDrive and Sharepoint Sites
- Backup speed optimization for OneDrive, Group OneDrive and Sharepoint Sites
- Where-it-left-off feature support for Microsoft 365 user mailbox
- Backup parallel limit & queue/retry mechanism for endpoints
- Users can now search for specific Backup/ VMs from the reports page (Recent Job Schedule, Recent Host/VM Schedule reports, etc…)
- Enhanced filter option in List Jobs / Recovery pages to search in name of backups, and filter by the status of backup (active, idle, etc…)
- End-user restore based on Online Authorization for SaaS applications


## BDRSuite v5.6 update

Updating your BDRSuite server is pretty straightforward as usual. However, it is recommended to review the [Software Update Guide](https://www.bdrsuite.com/pdf/release-notes/vembu-bdr-automatic-software-update.pdf) to make sure your scenario is covered and the [Upgrade Checklist](https://www.bdrsuite.com/pdf/release-notes/vembu-bdr-automatic-software-update.pdf) before upgrading to BDRSuite v5.6. Note that the BDRSuite installations below v5.0 should upgrade to v5.0 first before upgrading to v5.6.0 GA.