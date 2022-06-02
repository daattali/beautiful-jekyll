---
layout: post
title: Backup best practices for SMBs
description: Like in any company size, SMBs are recommended to follow a few best practices for their Backup environment
date: 2022-05-30T04:56:56.806Z
fb-img: null
---

Setting up a backup environment is among the most important aspects of an SDDC and this is a valid statement whether you are a 5 people startup or a 40.000 employees corporation. Backups can make or break businesses. There has been several occurences of businesses going under following a data loss event because they didn't have a proper backup strategy and weren't able to recover critical data. Best practices offer solid guidelines for SMBs to follow in order to protect their data with Nakivo Backup and Replication.

## 1 - Define RTOs and RPOs

Before starting, it is important for SMBs to discuss the data protection strategy and business needs as these will rule how the backup environment and the jobs will be configured. While most departments in an organization relies on data and needs to ensure that it is safe, establishing an order of importance will allow you to define recovery time objectives (RTO) and recovery point objectives (RPO) for each category.

RTO represents the time it takes to get the service back online (i.e. downtime), this depends on the backup infrastructure itself, the tier of storage, priority... While the RPO refers to the amount of data is deemed affordable to lose (i.e. duration between backup jobs), this is controlled by the frequency of the backup jobs. For instance, if you run a backup job every 24 hours and a failure occurs 1 hour before the job's schedule, you'll have lost 23 hours worth of data.

## 2 - Follow the 3-2-1-1 rule

The 3-2-1 rule has been around for a long time and is a rule of thumb when it comes to backups. Since a few years, we now talk about 3-2-1-1:

* Keep at least 3 copies of your data at any given time.
* Store these copies on at least 2 different media types (Disks, tape, cloud...)
* Send at least 1 copy to a remote site or to the cloud (offsite)
* Keep 1 air-gapped and immutable copy of your backup.

Ensuring that the 3-2-1-1 rule is in place means you can afford losing parts of your SDDC without losing your data.

![nakivo 3-2-1-1](/img/nakivo-3-3.png)

## 3 - Secure your environment

The threat of ransomware has been a subject of concern these last few years as attacks get more sophisticated and target backups as a priority to ensure that the victim cannot recover from the encryption. [Nakivo Backup and Replication](/posts\2021-11-15-how-nakivo-backup-replication-can-help-you-with-ransomware.md) puts several measures in place to mitigate the risk of ransomware and offers an array of best practices to abide by. Especially given the fact that MSPs and SMBs were prime victimes for bad actors.

Securing the environment means secruring both the VMware backups and the backup infrastructure infrastructure. Such measures include to use 2-factor authentication on the backup server, store immutable backup copies offsite, use role based access control, encrypt data at-rest/in-transit and several more.

## 4 - Test your recovery process regularly

Because having backups is great, having backups that work is even better! If you never test your recovery procedures, you will never know for sure that it will work the day you actually need it. For that reason, it is important to regularly test your VMare backup recovery procedures. Nakivo Backup and Replication lets you test your backups without interfering with the live workload by restoring in an isolated "bubble" environment. That way you can check that the VM boots up and the VMware tools start at the very least.

One way to avoid consistency issues is to leverage application-aware backups to ensure that databases and applications running in the virtual machine don't get backed up in a transitional state that they couldn't recover to.

## 5 - Ensure everything is backed up with policy based jobs

Having a backup infrastructure is great, but having backups of your VMs is even better. What do I mean by that? Well, if you need to manually configure the backup for each VM, you will eventually reach a point where something will be forgotten due to an oversight and some new VM won't get backed up and no one will know about it. Nakivo B&R has the concept of policies to create jobs where you can specify dynamic groups of VMs to be backed up based on parameters such as names, tag, size, location, resources, IP addresses and so on.

![Nakivo policy backup job](/img/Nakivo%20policy%20backup%20job.png)

## 6 - Keep the environment up to date

Although pretty obvious at first sight, SMBs usually put most of the focus on the core of the business for good reasons and tend to overlook the IT infrastructure. This is true for both the VMware infrastructure and the Nakivo Backup infrastructure. While the latest version always include new features, more importantly, it includes security patches and fixes for known vulnerabilities.

## 7 - Leverage product features to optimize resource usage

Nakivo Backup and Replication includes a plethora of features to improve your backup workflow that you should enable such as:

* Deduplication
* Compression
* Incremental backups
* Swap data and unused block exclusion
* Log truncation
* Network acceleration

## 8 - Establish backup windows

It is best practice to configure your backup jobs to run at times where the infrastructure is not under high load to avoid any tempering with the production as Nakivo B&R will be creating snapshots, moving data around and deleting snapshots. The most common framework for this is to run the jobs at night when the resource usage is the lowest. It is not to say that it fits all use case as some departments run stress tests on their applications at night for the same reason so this will be a business decision that must be discussed with all the stakeholders.

![backup job windows](/img/2022-06-02-08-12-55.png)

## Conclusion

Many SMBs manage to focus on their core business by offloading the duty of managing backups to an MSP. However, it is not an acceptable option for every organization as some may have sensitive data requirements, budget restrictions or simply want to take that on themselves to learn and have more control over the backup infrastructure.

Nakivo Backup and Replication is a popular choice among SMBs due to its ease of use while remaining a powerful and highly customizable product through backup job policies for instance.