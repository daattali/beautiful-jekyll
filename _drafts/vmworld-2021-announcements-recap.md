---
layout: post
title: VMworld 2021 announcements recap
DATE: 
subtitle: ''
metadescription: Keep reading to find out about the best VMworld 2021 announcements
  and learn about the future of virtualization.

---
VMworld 2021 took place on 5/6/7 of October 2021 during which VMware officials unveiled a number of new offerings, products, features etc... As always it was a great show with lots of value and you could really tell where VMware is taking the world of IT infrastructure.

VMworld 2021 was the first event since Raghu Raghuram started as VMware's CEO this year. 

![VMworld 2021 was the first VMworld since Raghu Raghuram took office as VMware CEO](/img/vmworld2021-1.png "VMware’s CEO Raghu Raghuram speaking at VMworld 2021")

We can tell that VMware understood that cloud adoption isn't easy for all organizations as they keep simplifying the process to get there. They also understood that on-premise isn't going anywhere so they are bringing the cloud to vSphere with the likes of Project Arctic. VMware Tanzu was the other golden child of this year's VMworld 2021 announcements with many sessions on the topic and some exciting announcements.

Without further ado, let's dig in!

## VMware Cloud

### VMware Cross-Cloud services

This VMworld 2021 announcement was among the main ones as it aims at simplifying the adoption of multi-cloud for VMware customers. The goal is to be able to pick and choose from five services among several cloud providers in a flexbiel and "free" way.

![VMworld 2021 announcements included vmware cross-cloud services](/img/vmworld2021-2.png)

These five services include:

* App platform: Building apps.
* Cloud infrastructure: Operating apps.
* Cloud management: Managing (cost and performance) across multi-cloud.
* Security and networking.
* Anywhere workspace and edge-native apps.

### VMware Sovereign Cloud

Sovereign cloud refers to data legislation and how one can ensure it is secure for a government entity to store sensitive data in it. Such customers may include country governments, European Union, United Kingdom... Monaco recently announced their own [Monegasque sovereign cloud](https://extendedmonaco.com/en/project/monaco-cloud-the-monegasque-sovereign-cloud-set-for-launch-in-2021/).

VMware Sovereign cloud will be a label that cloud providers can acquire in partnership with VMware via a checklist of best practices to become "VMware Cloud Verified".

### VMware Cloud on AWS Outpost

It is now possible to get the VMware Cloud on AWS offering as AWS Outpost to get the workload closer to home in an on-premise or co-located SDDC for instance. AWS ships the rack, configures it, VMware double checks everything and off you go to leverage it like you would any other VMC on AWS service (Because yes, it is a **service**).

![](/img/vmworld2021-3.png)

### Enhancements to DRaaS

DRaaS was announced during VMworld 2020 to showcase a more cost-effective approach to cloud oriented DR. VMworld 2021 announced also included enhancements to DRaaS with:

* **30-minutes RPO**: A tighter RPO ensure less data loss in case of recovery and this granularity will also serve in cases of ransomware attacks recovery.
* **Accelerated Ransomware recovery with File-level recovery**: You can restore files from various snapshots at different point in time into a restore point at another time to shorten the time to recover a virtual machine after a ransomware attack.
* **Integrated and simple data protection for VMware Cloud on AWS**: VMC on AWS will now be able to leverage data protection in a unified DR, ransomware, and foundational backup-restore solution.

## VMware Tanzu

### VMware Tanzu Community Edition

I loved this VMworld 2021 announcement because Tanzu is cool and open-source software is cool. VMware unveiled [Tanzu Community Edition](https://tanzucommunityedition.io/), an open-source, free and full-featured Tanzu edition. Ideal for users and testers to get a good feel of the solution since the original vSphere with Tanzu requires quite a lot of resources and isn't as straightforward to deploy.

You can deploy VMware Tanzu Community Edition in vSphere, EC2, Azure or even locally in Docker! Lots of packages can be plugged in such as Grafana, Prometheus, Harbor, Velero...

### Cloud Tanzu services

Because many organizations don't necessarily have the resources, times or in-house skills to operate a complete Kubernetes infrastructure, VMware now offers VMware Tanzu as a multi-cloud service.

* **Managed Tanzu Kubernetes Grid (TKG)**: The underlying infrastructure for Kubernetes is managed by VMware, while VI admins can leverage the vCenter they know and love to provision workload clusters deliver role-based access and capacity to the developer teams.
* **Tanzu Mission Control Essentials**: With TMC Essentials you get the management plane for K8S as a managed cloud service in which you can plug whatever cluster you feel like throwing at it.
* **Tanzu Mission Control Starter**: Tanzu Mission Control Starter will be the free tier for TMC with a set of core Kubernetes management features.

### Other Tanzu mentions

Tanzu was mentioned in other areas such as [Tanzu Service Mesh Enterprise](https://tanzu.vmware.com/service-mesh), VMware Tanzu Standard for VMware Cloud Universal, New TKG features, New capabilities for [Tanzu Application Platform.]()

## vSphere 7 Update 3

As it is often the case, a new version of vSphere is released around the time of VMworld and is the topic of a session or two. This VMworld 2021 was no exception with a session around [vSphere 7 Update 3 release notes](https://docs.vmware.com/en/VMware-vSphere/7.0/rn/vsphere-esxi-703-release-notes.html) and [vSAN 7 Update 3 release notes](https://docs.vmware.com/en/VMware-vSphere/7.0/rn/vmware-vsan-703-release-notes.html). 

Sphere 7 Update 3 addresses the burning topic of the SD cards being dodgy in vSphere 7. SD cards and USB sticks are no longer supported by VMware, which is a bold move and I'm sure many customers won't be too pleased about that.

However, those customers will be consoled by the fact that VMware keeps building on their beloved hypervisor instead of bulldozing their way into the cloud like Microsoft is doing by deprecated free on-permise Hyper-V in Windows Server 2022... Lots of cool stuff in this release such as:

* vCenter Server plug-in for NSX
* Simplified deployment process of VMware vSphere with Tanzu (Yes please)
* Improved maintenance operations regaring vCLS cluster VMs
* Improvements to lifecycle management
* vCenter RDU (Reduced Downtime Upgrade), bring cloud tech to on-prem
* Future Linux distributions will have VMware Tools preinstalled (What??)
* I/O Trip Analyzer for vSAN 7 Update 3