---
layout: post
title: VMware vCenter Converter is gone, here's an alternative
DATE: 
subtitle: ''
metadescription: Find out how Nakivo can replace VMware vCenter Converter after removing
  it from downloads
image: ''

---
vCenter Converter has been a trusty sidekick for many IT administrators over the years, helping them achieve the virtualization of tricky physical workloads. While it is always recommended to deploy a new clean virtual machine, it isn't always possible due to licensing or compatibility constraints with legacy software for instance.

As you may have read recently, [VMware removed vCenter Converter ](https://blogs.vmware.com/vsphere/2022/02/vcenter-converter-unavailable-for-download.html)from the available downloads. This was a precautionary measure to prevent users from downloading a product that hasn't been updated since 2019 and in turn, open the door to all kinds of vulnerabilities. If you still need a P2V tool and don't want to use a deprecated product like vCenter Converter, [Nakivo ](https://www.nakivo.com/physical-to-virtual-recovery/)can help you there!

### Nakivo P2V: Physical-to-Virtual Recovery

As you probably know [Nakivo ](https://www.vxav.fr/2021-12-09-nakivo-v10.5-brings-vmware-monitoring-and-anti-ransomware-resilience/)distributes and Backup and Replication software that supports physical, virtual and cloud workloads with a plethora of bells and whistles such as monitoring and ransomware protection to cover as many data protection scenarios as possible. 

![Nakivo P2V can as an alternative to VMware vCenter Converter](/img/nakivop2v1.png)

One of these bells (or whistles) is the "P2V: Physical-to-Virtual Recovery" capability. You guessed it, this feature offers several physical to virtual options and is superior to vCenter Converter in a way. 

* **Restore from backups** Windows, Linux physical servers and workstations to VMware VMs.
* **Instant P2V** lets you run physical workloads in your vSphere environment without any downtime. Imagine that, you can test updates before applying them to your production physical environment in a "Sandbox" virtual environment.
* Traditional Full **P2V migrations** to convert physical machines to VMware VMs. By leveraging the backup infrastructure, you can plan and scale your migrations from physical to virtual much like you would in a regular VM migration scenario across datacenters for instance.

The great thing is that you can boot directly from backups where compression and deduplication are enabled to save storage space. Any changes you make to a booted VMware VM will not alter in any way the source physical machine backup. Note that Free ESXi is not supported for physical to virtual recovery.

The steps to perform a Nakivo P2V are very simple:

1. **Add** the physical machine to the inventory. 
2. **Run** a physical machine backup job
3. **Recover** the backup to a VMware VM either via the **Dashboard** or the **Repositories** page. 

Much like VMware vCenter Converter, when recovering a physical machine to a VM, you get to configure its hardware specifications, keep or renew the mac address, use thin disks...

![P2V with Nakivo backup and replication](/img/nakivop2v2.png)

### Conclusion

What I like about Nakivo P2V: Physical-to-Virtual Recovery is that it transparently integrates into your backup solution and you can use it in a number of ways that best suit your needs. You can think of it like a migration tool that completely abstract the platform a workload is or will be running on.

You can [check out Nakivo Backup and Replication for free ](https://www.nakivo.com/resources/download/trial-download/)and deploy it to pretty much whatever you want (Windows, Linux, OVA, AWS, a NAS...).