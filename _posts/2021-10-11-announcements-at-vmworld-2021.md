---
layout: post
title: Announcements at VMworld 2021
DATE: 2021-10-10 00:00:00 +0200
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

### Project Arctic and Cascade

Those two projects work hand in hand to address the needs of Operations teams and DevOps teams. **Project Arctic** will look after Ops teams by making vSphere "Cloud aware" by bringing connectivity directly to it to, again, compromise with beloved on-premise infrastructures and simplify the transition to hybrid cloud.

**Project Cascade** focuses on DevOps folks by a proposing a unified Kubernetes interface for both on-demand infrastructure and containers across multi-clouds. It will leverage Tanzu VM service that lets "kubernetes" interact with VMs.

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

## VMware EDGE

### VMware Edge Compute Stack

Although it is not nearly as mentioned as cloud or container techs, Edge computing is going to be one of the next big things in IT. For all those use cases where you need your compute capacity as close to the endpoint as possible (at the Edge).

Because refactoring apps to run at the edge is complicated, time consuming and expensive, VMware is simplified the road to Edge computing with VMware Edge Compute Stack, a stack that extends your SDDC or Cloud infrastructure to the edge with HCI, SDN, Tanzu and vSphere. That way you keep delevoping your apps like you're used to and just push them to the Edge.

![](/img/vmworld2021-4.png)

The offering will be licensed in three tiers:

* **Edge Compute Standard**: vSphere Enterprise Plus, Tanzu Standard
* **Edge Compute Advanced**: vSphere Enterprise Plus, Tanzu Standard, vSAN Standard
* **Edge Compute Enterprise**: vSphere Enterprise Plus, Tanzu Standard, vSAN Standard, SD-WAN by VeloCloud

### Project Santa Cruz

Among the project in the VMworld 2021 announcements was Project Santa Cruz, a purpose built box that will easily connect an Edge site to the SDDC or Cloud mothership where centralized management is. I find there's vibe in between apple products and desktop computers from the early 2000.

![Project Santa Cruz VMworld 2021 box](/img/vmworld2021-5.png)

Note that Project Santa Cruz also includes "Bring-your-own-host" with a cluster API provider that can support existing infrastructure such as Hyper-V or specific kernel-tuned environments.

## VMware Infrastructure

### vSphere 7 Update 3

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

### Project Capitola

Now this project is REALLY cool as it will essentially let you virtualize and pool memory in several tiers such as DRAM, PMEM, NVMe and other future technologies that don't yet exist. This will make for a more cost-effective solution for those memory hungry workloads. This is somewhat like vSAN for memory and it will be managed by vSphere in the backend.

![](/img/vmworld2021-6.png)

## Other projects

A bunch of projects were announced that we didn't mentioned earlier. Here they are if you're interested to see what VMware is currently working on:

* **Project Radium**: AI oriented project to expand the compatibility of BitFusion to a wider range of hardware such as AMD, Graphcore, Intel, Nvidia and other vendors and make it dynamically attachable.
* **Project Cryptographic agility**: Offer crypto agility through increased control over configurations and the ability to switch between standard and libraries.
* **Project Ensemble**: streamlines multi-cloud operations through app-centric views of multi-clouds.
* **Project IDEM**: Multi-cloud task automation platform with auto-discover of cloud APIs.

## Conclusion

Another big year ahead with all these VMworld 2021 announcements. Unless it wasn't already clear enough, it is obvious that VMware is directing the company toward a more service and subscription oriented model. Recurring streams of income make a lot more sense than upfront investments and in-house management of the assets.

App modernization is still in its early days in the VMware space with Tanzu but it is coming and it is coming fast. Teams are skilling up on the technology and customer interest will only grow in the coming months bringing lots of interesting use cases and scenarios.