---
layout: post
title: Nakivo v10.5 brings VMware monitoring and anti-ransomware resilience
DATE: 
subtitle: ''
metadescription: Nakivo released v10.5 which brings a new VMware monitoring solution
  and additional anti-ransomware resilience capabilities.

---
The landscape of VM backup solutions vendors has significantly evolved over the last few years with the emergence of cloud computing and modern apps driving innovation. Nakivo Backup & Replication is keeping up this pace with fast release cycle to bring more value to the product and offer solutions to their customers' use cases. The recent release of Nakivo Backup & Replication v10.5 is a testimony of this statement with the announcement of two major enhancements to the flagship product.

### Nakivo Backup & Replication v10.5 new features

Although the changelog isn't a long scroll down, you will find that a lot of work has gone into this release and it will certainely bring value to existing and new customers.

* **VMware Monitoring**
* **Hardened Virtual Appliance**

This functionality allows you to create immutable backups in Backup Repositories deployed as part of a virtual appliance. The immutability cannot be unset by any user or process. This provides an additional level of security for your backups.

* **Auto-Set API Permissions for Microsoft 365 Accounts**

NAKIVO Backup & Replication can now automatically check and set the required API permissions for Microsoft 365 accounts before adding them to Inventory.

* **Backup of VM Templates**

NAKIVO Backup & Replication can now back up and recover custom VM templates to and from VMware vCenter or ESXi hosts.

* **General Tab Facelift**

This update also brings a new, more intuitive user interface to the General tab in Settings.

### VMware monitoring

This new VMware monitoring feature lets you track and monitor VMware vSphere hosts and VMs metrics such as CPU, memory, and disk load/usage as well as datastore disk usage. 

_Do note that this is the first installment of this feature. A lot more metrics and capabilities will be added in the next release to make it a production tool that you can leverage to monitor your environment._

Let's have a look at the value brought by Nakivo VMware monitoring:

* **Simpler VM Sprawl Control**

VM sprawl refers to a common challenge faced by most companies where the increasing number of virtual machines in an environment because too much for the vSphere administrator to effectively manage. With VMware Monitoring, you will gain complete visibility into hosts, VMs and datastores to help you contain virtual machine sprawl.

* **Resource Management**

One of the core duties of a VI admin is to ensure that all the workloads in the environment are getting the resources they need to run. The VMware performance monitoring dashboard offers real-time resource usage which allows you to keep an eye on used and available hardware resources at any time.

* **Improved Load Distribution**

While resources management will give you a state of the art on resources usage, you also want to ensure that your workloads are distributed efficiently. You don't want a host running a 95% CPU while the other five are cruising at 30% usage. vSphere DRS can help with that but there are license restrictions and Nakivo VMware monitoring offers capabilities in that space as well.

* **Centralized VMware vSphere Infrastructure Monitoring**

The centralized dashboard in Nakivo VMware monitoring offers a hollistic view of your environment and helps focus your attention on what matters.

* **Precise Scalability Forecasting**

One of the pain points of the VI admin role lies in the capacity planning. Anticipating the future resource needs can be incredibly tricky and complicated, a reason why Cloud got so popular since it solves this problem. However, on-premise environments still need to account for future growth and this is where Nakivo VMware monitoring can help with detailed real-time and historical data on the performance of your environment to anticipate virtual or physical resources needed.

### Additional improvements in Nakivo Backup & Replication v10.5

A number of other enhancements are brought by Nakivo B&R v10.5:

* Now display full license information, including full licensing model breakdown and used/licensed workload details.
* More consistent format for alarms and notifications.
* Improved two-factor authentication for Active Directory users.
* Improved tree UI component for easier management of large item sets.
* Backup copy jobs now skip data unpack/pack if the source and target Backup Repository share the same type and compression.
* The solution more easily identifies backups with corrupted recovery points.
* Enhanced tracking of virtual machines in Microsoft Hyper-V clusters during job runs.
* Data unpack is now skipped for new backup copy jobs. A mapping run is required to apply the improvement for existing backup copy jobs.
* Support for Asustor ADM 4.0.