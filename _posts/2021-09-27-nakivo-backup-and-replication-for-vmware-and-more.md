---
layout: post
title: Nakivo Backup and Replication for VMware and more
DATE: 
subtitle: ''
metadescription: Nakivo Backup and Replication for VMware, Hyper-V, physical servers
  and cloud integration.

---
Today we are going to have a look at Nakivo Backup and Replication, an all-in-one product that will let you backup, restore and replicate virtual machines in your VMware environment. The product supports a variety of environments to backup such as vSphere, Hyper-V, M365, Nutanix, Oracle...

NAKIVO is a privately held company that distributes data protection and site recovery software targeted at SMB and enterprise markets and built a solid customer base since 2012. [Nakivo Backup and Replication ](https://www.nakivo.com/)offers a suite of features for physical, virtual, and cloud environments altogether.

### Main features

Nakivo B&R includes all the features you can expect from a good backup software and more.

* **Data recovery.**

Nakivo B&R can backup and recover objects for Active Directory SQL Server, Exchange and perform instant file or VM recovery.

* **Instant verification.**

After a backup runs, Nakivo uses the Flash VM boot feature to run the VM from backup, wait until the OS has booted and make a screenshot that you can receive via email or review manually. The other verification  mechanism relies on the readiness of the VMware Tools.

* **Policy based backups.**

I mention this one because I believe it should be in every single backup product. Policy based backups offer flexibility by creating jobs based on metadata such as vSphere tags, folders, vDisks, resources etc. You can then require multiple conditions to be met for a job.

* **LAN-free data transfers.**

LAN-free transfers let you make use of usually faster storage networks by using Hot-Add or Direct SAN Access methods to bypass the TCP-IP stack of the server.

* **Wide array of deployment types.**

Nakivo B&R lets you deploy the software in many different ways such as virtual appliances, installed on server OSes, NAS packages, RPi...

* **Cloud integration.**

Cloud integration in Backup products are a good way to fool proof your investment. Nakivo offers backup to Amazon S3, backup of M365 and EC2 instances. You can also maintain exact copies (replicas) of your original EC2 instances and fail over to the replicas for near-instant disaster recovery.

* **Ransomware protection.**

Although these are not specific to [ransomware ](https://www.nakivo.com/ransomware-protection/ransomware-recovery/)and more a way to attract clients, it is good content to spread best practices and make customers aware of these.

### Deployment types

Nakivo Backup and Replication offers a surprising [number of options ](https://helpcenter.nakivo.com/User-Guide/Content/Deployment/Installing-NAKIVO-Backup-and-Replication/Installing-NAKIVO-Backup-and-Replication.htm)when it comes to deploying the solution. You can deploy it as a VMware or Nutanix appliance, install it on Windows, Linux.

The more surprising deployment models include installing it on NAS devices (Synology, QNAP, WD, ASUSTOR, Netgear ReadyNAS, FreeNAS/TrueNAS) and you can even install it on Raspberry Pi or in Amazon EC2.

### Editions and Pricing

#### Free Edition

Nakivo Backup and Replication offer a free version which includes licenses for 10 workloads and 5 Microsoft Office 365 accounts. However it is said to be completely free for one year so I assume this is a time restriction.

#### Free trial

If the free edition isn't going to cut it for you, you can start with a [15-day free trial ](https://www.nakivo.com/resources/download/trial-download/)which includes the following features on top of what the free edition offers:

* **Site Recovery** – Advanced DR workflows to recover workloads.
* **Policy-Based Data Protection** – data protection automation for virtual environments.
* **Active Directory Integration** – Mapping AD user groups to user roles.
* **HTTP APIs** – Integrate NAKIVO Backup & Replication with monitoring, automation and orchestration solutions.
* **Calendar Dashboard** – Schedule routine backups to simplify backup administration.
* **Global Search** – Search through the inventory and VM backups for quick granular recoveries.
* **Multi-Tenancy** – Possibility of several isolated tenants with BaaS and DRaaS to your customers or partners.

#### Paid editions

Nakivo Backup and Replication comes in many flavours to offer a high level of granularity with 3 differents feature-set (_Core, Extended and Complete_) and different environments sizes (_Essentials or standard_).

* **Basic (per-CPU socket only)**: _Core_ features for very small environments (limit of 4 CPU sockets).
* **Pro Essentials**: _Extended_ feature set for small environments (2-6 sockets, 10-50 physical servers, 10-150 windows workstations or 0-50 workloads with subscription).
* **Pro**: _Extended_ feature set for any environments.
* **Enterprise Essentials**: _Complete_ feature set for small environments (2-6 sockets, 10-50 physical servers, 0-150 windows workstations or 10-50 workloads with subscription).
* **Enterprise**: _Complete_ feature set for any environments.
* **Enterprise Plus**: _Complete_ feature set for any environments with Oracle RMAN protection features.

For more details on the _core, extended and complete feature sets_, refer to the complete [list of features comparison](https://www.nakivo.com/how-to-buy/pricing/).

![Nakivo Backup and Replication editions comparison - more information on their website](/img/nakivo1-2.jpg "Nakivo Backup and Replication editions comparison")

#### Pricing

Nakivo Backup and Replication offers several levels of licensing which vary according to the features set, environment size and type of support required.

**Per-Socket (CPU) licenses are perpetual** and let you backup as many VMs as you want and a number of physical target as well.

![Nakivo Backup and replication pricing](/img/nakivo1-4.jpg)

The **per-workload subscription lets you tailor** the number of virtual machines, physical server and AWS EC2 instances to backup. Note that the Basic edition isn't available with this pricing model.

![](/img/nakivo1-5.jpg)

The best way for you to get a good grasp of the licensing options available is to have a look at the [pricing calculator](https://www.nakivo.com/how-to-buy/pricing_calculator/). Adjust the sliders and values to tailor the license to your needs and get an idea of how much it would be. That way you can compare both license types and calculate your ROI to find out which one makes the most sense to your organization.

![](/img/nakivo1-1.jpg)

### Wrap up

Despite the fact that virtual machine backup and replication software is no longer niche and a crowded market, Nakivo Backup and Replication managed to carve out a solid place for themselves in this landscape. Their customer references page is a long scroll and includes a few significant names.

While the pricing may seem a little complicated at first, it is valuable to ensure you only pay for what you need. Note that they also offer options to [trade ]()your current solution to poach customers from the competition.

Anyway, a solid product at first glance that should fit in just fine in most SMB and medium sized companies environments.