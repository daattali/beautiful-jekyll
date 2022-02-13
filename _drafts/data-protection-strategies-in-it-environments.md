---
layout: post
title: Data protection strategies in IT environments
DATE: 
subtitle: ''
metadescription: Find out about the different ways to protect data in your IT organisation's
  environments.
image: ''

---
Every IT department recognises that data is key and it can make or break an organisation should something happen to it. The cases of businesses closing down following a disaster or [ransomware attack ](https://www.vxav.fr/2021-12-09-nakivo-v10.5-brings-vmware-monitoring-and-anti-ransomware-resilience/)are unfortunately too many and could have been avoided if a proper data protection strategy was in place. While my blog is generally mostly focused on virtualization, it is worth sidetracking a bit to cover other environments.

#### Virtual environments

Backing up virtual machines is a well oiled process based on snapshots, change based tracking, backup proxies and repositories offered by several companies. Such products include [Nakivo Backup and Replication ](https://www.nakivo.com/vmware-backup/)which supports VMware vSphere, VMware Cloud Director, Hyper-V and Nutanix AHV and offers all the features you need from such a solution including:

* image-based, incremental and app-aware backups of live VMs
* Backup job automation based on backup policies
* Instantly recovery of entire VMs, files, and application objects directly from backups
* Copy of backups to tapes, offsite or to cloud providers to ensure the 3-2-1 rule.
* Tests to ensure immutability and consistency of backups.

Protecting virtual environments is made easy and flexible with policies and the ability to quiclly scale-out the solution with more proxies to increase the concurrency of jobs. You can find more details on Nakivo B&R for VMware in [this blog](https://www.vxav.fr/2021-10-19-backup-and-restore-vms-with-nakivo/).

#### Physical environments

While IT organizations mostly run hypervisors to consolidate the workloads and improve efficiency, a number of duties still need to remain on dedicated physical servers. In which case, a different, more traditional approach needs to be taken by running backup agents inside the OS which will in turn copy the data to a backup repository. The same recommendations as in a virtual environment obviously apply when it comes to securing your backups. Such as air-gapped environment, 3-2-1 rule, automation...

Nakivo B&R supports backups of Windows Server and Linux OSes and a fair number of features we find in VM backups are also made available for your bare metal machines such as:

* Incremental backups with only changed data blocks transferred to a backup repositoryin order to shorten backup windows, save storage space.
* Instant granular recovery of files and application objects from backups directly to the OS. 
* 