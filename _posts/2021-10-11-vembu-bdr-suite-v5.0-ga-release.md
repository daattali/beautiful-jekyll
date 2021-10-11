---
layout: post
title: Vembu BDR Suite v5.0 GA release
DATE: 
subtitle: ''
metadescription: Backup your virtual machines with Vembu BDR Suite v5.0 and learn
  all about its new features.

---
Vembu BDR Suite v5.0 is a complete Backup and disaster recovery solution tailored to protect workloads across Virtual, Physical, on-premises, Cloud services, and SaaS applications.

After a hiatus since version 4, Vembu finally released Vembu BDR Suite v5.0, a major release which embeds many interesting features and will bring a lot of value to your infrastructure with solid virtual machines backup solution. The focus has been put on covering on-premise and cloud environments as more and more customers are moving to a hybrid cloud approach.

[![](/img/vembu5-1.png)](https://www.vembu.com/vembu-bdr-suite-download/)

Vembu BDR Suite is a Windows or Linux installer and you can use it unrestricted for free during a **30 days trial period**.

#### Vembu BDR Suite Upgrade

If you are running an earlier version of Vembu BDR Suite, you can already upgrade your deployment to Vembu BDR Suite v5.0.

#### Unified web-based management console

One of the big selling points of Vembu BDR Suite v5.0 is how it consolidates backup management for virtual, physical, cloud workloads, and SaaS applications into a single centralized management GUI.

![](/img/vembu5-2.png)

Customers can now configure backup and recovery through the unified management GUI for:

* [VMware](https://www.vembu.com/vmware-backup/)
* [Hyper-V](https://www.vembu.com/hyper-v-backup/)
* [Windows](https://www.vembu.com/windows-image-backup/)
* [Agentless and application-consistent backup of AWS EC2](https://www.vembu.com/aws-backup/)
* [Microsoft 365 (Now supports Teams and SharePoint Online Backup)](https://www.vembu.com/office-365-backup/)
* [Google Workspace with support for backup of Mails, Google Drive, Contacts, and Calendar](https://www.vembu.com/google-workspace-backup/)

#### New features in Vembu BDR Suite v5.0

This new version is packed with valued added features that span from traditional on-premise enhancements to Cloud services backup support. In the next sections we will have a look at some of these features, in the meantime, here is the complete list of what you will find new in Vembu BDR Suite v5.0.

* Microsoft 365 SharePoint Online Backup
* Microsoft 365 Teams Backup
* Backup for Google Workspace
* Backup for AWS
* Hyper-V VM Replication
* Instant Boot Live Migration
* Parallel VM Processing
* Rotated Drives as Backup Repository
* Optimized Backup with Where-it-left-off
* Synthetic Full Backup
* GFS (Grandfather-Father-Son) Retention
* Backup Job Template
* Multi-host Backup Support
* Application Item-level Recovery from web GUI

#### Disk rotate for backup repository

Set up rotated drives as the primary backup repository to store the backup data in multiple external detachable hard drives and swap them on a regular basis.

![](/img/vmworld2021-7.png)

#### Backup Job Templates

You can now create backup templates based on frequently used backup configuration settings or backup policies that you can use to create new backup jobs quickly which require similar configuration settings as that of the already created template to skip steps and save time.

You can then, in your template, add disk exclusions such as only backing up the system disk, configure guest processing, VM quiescing, scheduling, settings, encryption...

![](/img/vmworld2021-8.png)

#### Cloud services Backups

In Vembu BDR Suite v5.0, you can add Google Workspace and Microsoft 365 organizations in your data sources to start backing up your Cloud services.

![](/img/vmworld2021-9.png)

The AWS integration guides you through the process where you need to create an IAM policy with a piece of JSON provided in the Vembu management dashboard. Once done, attach it to a user, configure the access key ID with Secret Access key andyou can start backing up your instances. As you can see below my EC2 instance appears in the menu.

![](/img/vmworld2021-10.png)

#### GFS (Grandfather-Father-Son) Retention

In Vembu BDR Suite v5.0, you can use GFS retention to create restore points on a weekly, monthly, quarterly, and yearly basis which are tied to an extra Full or Synthetic Full Backup. Note that this isn't available with disk rotation repositories.

![](/img/vmworld2021-11.png)

#### Instant Boot Live Migration

Instant boot isn't a new feature as it's been around for a while now. However, you can now instantly boot VMs from backup repository while they are being fully restored in the background without any downtime. This will be particularly valuable for those critical workloads that you need recovered as soon as possible.

![](/img/vmworld2021-12.png)

#### Concurrent backup settings (Parallel VM Processing)

With Concurrent backup settings, you can now set the maximum number of backup tasks the server can process concurrently before queuing them as well as the number of tasks each backup job can process. That way you can control your backup fluxes in a more granular fashion.

![](/img/vmworld2021-12-1.png)

#### Other changes in Vembu BDR Suite v5.0

Anyway, I only scratched the surface of what's new in Vembu BDR Suite v5.0 as I'm sure you will be playing with it anyway. The [release notes](https://www.vembu.com/vembu-bdr-suite-release-notes/) also refer to additional enhancements that are brought by this new version such as:

* You can start a restore while a backup is running
* Backup and offsite copy job can run concurrently
* Specify your backup window at the job level
* File-level recovery support for dynamic disks
* Compression and encryption can be turned off at the storage repo
* Creating a backup job is significantly more user friendly
* Throttle bandwidth on backups created in BDR Backup server
* Hyper-V backup VMs can be restore with their original configuration

#### Conclusion

There you have it, Vembu BDR Suite v5.0 will help you protect those virtual machines and cloud services that run your organization. 

Putting in place a solid backup strategy is critical, especially in these days of Ransomware attacks popping up all over the place. You want to ensure that your data is safe and that you can recover should anything happen.

Feel free to give [Vembu BDR Suite v5.0 ]()a go!
