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

First off, implementing a solid backup infrastructure is paramount to ensure that you have access to backups in case of recovery post ransomware. However, ensuring that the backup infrastructure is secured and isolated from the rest of the network is even more important as it will be no use if your backups have been hit as well. 

This is what is called air-gapped backups. It can be achieved through network isolation or by using the backups to tape feature of NAKIVO Backup and replication.

![](/img/nakivo-3-1.png)

On top of this, you can schedule when the repository is attached to create an "air gap" between the attacker and your backups.

![](/img/nakivo-3-4.png)

### Immutable repository

The other area to look out for is Backup Immutability. NAKIVO Backup & Replication allows you to make the recovery points in repositories immutable for local folders and S3 storage.

When immutability is enabled, the recovery points are stored using the _write-once-read-many_ (WORM) model. The result is that you make recovery points immutable for x days. The recovery points remain immutable for the specified number of days, effectively protecting them from ransomware attack targeting backup systems.

![](/img/nakivo-3-2.png)

### Hardened Virtual Appliance

NAKIVO Backup & Replication [v10.5 (currently in beta as of October 2021)](https://www.nakivo.com/fr/resources/releases/10.5-beta/) offers the Hardened Virtual Appliance (VA). A simple way to deploy NAKIVO Backup & Replication and protect data against ransomware.

You can simply deploy the NAKIVO Backup & Replication as a pre-configured virtual appliance powered by Ubuntu Server and protect your data from deletion and encryption by ransomware. Backups sent to a repository deployed as part of the VA can be made immutable for a specified period of time.

### Two-Factor authentication (2FA)

Many [Ransomware attacks](https://www.nakivo.com/blog/10-recent-ransomware-attacks-facts-figures-and-lessons/) related by organizations that got hit involved compromised credentials, be it Active Directory or local authentication. By enabling two-factor you essentially add an extra layer of security to your backups.

With 2FA enabled, users need a code provided by the Google Authenticator mobile app or by email to access the solution and backups. Paired with the role-based access control (RBAC) feature in NAKIVO Backup & Replication, you also make that no one is able to perform unauthorized operation

### Best practices implementation

This one is true not only for NAKIVO Backup & Replication  but for every single backup solution out there. Ensuring that you are following Backup best practices doesn't mean you will never get owned, however it will make it significantly harder for bad actors which will most likely move on to easier targets.

![](/img/nakivo-3-3.png)

1. **Create Regular Backups**: You don't want to find yourself left with a 2 months old copy of your data when it is time to restore from backup. NAKIVO Backup & Replication  lets you set aggressive RPO and RTO to ensure minimal data loss and downtime.
2. **Follow the 3-2-1-1 Rule**: You probably heard of the 3-2-1 rule, keep 3 copies of data on 2 different media types, 1 copy offsite. Well now you need to add 1 last line of defense; an immutable copy on S3, local Linux-based repository or on tape.
3. **Create an Effective Retention Policy**: Regular backups are great but you also need to tune your retention policies. You can save up to 4,000 recovery points for each backup job with NAKIVO Backup & Replication and rotate them with the grandfather-father-son (GFS) retention scheme.
4. **Set Up Automated Workflows**: With the Policy-Based Data Protection feature, NAKIVO Backup & Replication lets you create rules to automatically protect your VMs and EC2 instances which match certain criteria. That way no VM is left on the side of the road.
5. **Control Access to Backup Data (2FA)**: I shall reiterate here the importance of 2FA to connect to NAKIVO Backup & Replication with the role-based access control (RBAC) feature and the principle of least privilege (PoLP).
6. **Verify Recoverability of Your Backups and Replicas**: Test your backups and replicas regularly and verify that they are valid with the instant verification capability of NAKIVO Backup & Replication and be alerted if something went wrong. That way you won't discover it when it's time to restore the VM.

There are obviously a whole lot more actions you can take to further harden your backup infrastructure by implementing secured Active Directory, network segmentation, Email and browser hygiene, antivirus software, least privelege access policy...