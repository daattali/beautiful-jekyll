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

#### Flagship features

The two main features driving NAKIVO Backup & Replication v10.5 are the following:

* **VMware Monitoring**
* **Hardened Virtual Appliance**

More details on these later.

#### Other new features

* **Auto-Set API Permissions for Microsoft 365 Accounts**

NAKIVO Backup & Replication automatically checks and sets the required API permissions for Microsoft 365 accounts before adding them to the Inventory.

* **Backup of VM Templates**

NAKIVO B&R can back up and recover custom VM templates to and from vCenter Server or vSphere hosts.

* **General Tab Facelift**

This update also brings a new, more intuitive user interface to the General tab settings.

![](/img/nakivo105-6.png)

### Nakivo Virtual appliance update to v10.5

If you already run a NAKIVO Backup & Replication virtual appliance you can obviously update your existing server. The documentation explains how to update manualy. 

1. First download the updater package [here](https://www.nakivo.com/resources/download/update/).

![](/img/nakivo105-2.png)

Before updating your virtual appliance (VA), check that no jobs or repository maintenance tasks are running and create a snapshot of the VA in case of a failure.

1. Connect to the Nakivo appliance with WinSCP and copy the Updated file to /opt/nakivo.updates

![](/img/nakivo105-3.png)

1. In vCenter, open a virtual console on the Nakivo appliance and go to **Manage NAKIVO services** > **Software update** > Select the **Updater file** > Scroll down to the bottom and **type Y to start the update**.

![](/img/nakivo105-4.png)

The appliance should now be running the latest version. You can check in **Settings > General > Software Update**.

![](/img/nakivo105-5.png)

### VMware infrastructure monitoring

This new [VMware monitoring feature ](https://helpcenter.nakivo.com/User-Guide/Content/Getting-Started/Monitoring/Managing-The-Monitored-Items.htm)lets you track and monitor VMware vSphere hosts and VMs metrics such as CPU, memory, and disk load/usage as well as datastore disk usage. VMware Monitoring is available as part of the NAKIVO Backup & Replication [Free Trial](https://www.nakivo.com/resources/download/trial-download/) and the [Free Edition](https://www.nakivo.com/resources/download/free-edition/).

_Do note that this is the first installment of this feature. A lot more metrics and capabilities will be added in the next release to make it a production tool that you can leverage to monitor your environment._

Let's have a look at the value brought by Nakivo VMware monitoring:

* **Simpler VM Sprawl Control**

VM sprawl refers to a common challenge faced by most companies where the increasing number of virtual machines in an environment because too much for the vSphere administrator to effectively manage. With VMware Monitoring, you will gain complete visibility into hosts, VMs and datastores to help you contain virtual machine sprawl.

* **Resource Management**

One of the core duties of a VI admin is to ensure that all the workloads in the environment are getting the resources they need to run. The VMware performance monitoring dashboard offers real-time resource usage which allows you to keep an eye on used and available hardware resources at any time.

* **Improved Load Distribution**

While resources management will give you a state of the art on resources usage, you also want to ensure that your workloads are distributed efficiently. You don't want a host running a 95% CPU while the other five are cruising at 30% usage. vSphere DRS can help with that but there are license restrictions and Nakivo VMware monitoring offers capabilities in that space as well.

* **Centralized VMware vSphere Infrastructure Monitoring**

The centralized dashboard in Nakivo VMware monitoring offers a hollistic view of your environment and helps focus your attention on what matters. You can monitor up to 1,000 VMs, 100 hosts, and 200 datastores from a single dashboard.

* **Capacity Planning and trends analyzis**

One of the pain points of the VI admin role lies in the capacity planning. Anticipating the future resource needs can be incredibly tricky and complicated, a reason why Cloud got so popular since it solves this problem. However, on-premise environments still need to account for future growth and this is where Nakivo VMware monitoring can help with detailed real-time and historical data on the performance of your environment to anticipate virtual or physical resources needed.

### Improved anti-ransomware resilience

Ransomware have been a rising threat for IT professionals over the last few years with ever more sophisticated attacks. I already covered the topic lately with [vSphere environments in the Ransomware landscape](https://www.vxav.fr/2021-09-29-vsphere-environments-in-the-ransomware-landscape/) and [How NAKIVO Backup & Replication can help you with Ransomware](https://www.vxav.fr/2021-11-15-how-nakivo-backup-replication-can-help-you-with-ransomware/).

While the crux of a ransomware attack is to encrypt the victim's data, attackers are also targeting backup solutions since this is essentially the only way to recover from a Ransomware attack and avoid paying the ransom. In order to prevent the encryption of backups, Software vendors include repository immutability, meaning the data cannot be altered in any way.

![](/img/nakivo105-1.png)

Nakivo Backup and Replication v10.5 is working hard on improving security of [virtual appliance](https://www.nakivo.com/resources/download/free-edition/download/) deployments with the **Hardened Virtual Appliance** which allows you to create immutable backups in Backup Repositories. The immutability cannot be unset by any user or process. This provides an additional level of security for your backups.

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

### Wrap up

With Nakivo Backup & Replication v10.5, the company focuses on aspects of the SDDC that concern all customers with VMware monitoring and imporved Anti-Ransomware resilience.