---
layout: post
title: VMworld 2020 announcements
DATE: 2020-10-01
subtitle: Discover the major announcements of VMworld 2020

---
This year's VMworld is like no other before due to the current situation. Everything is accessible on the virtual platform provided you registered for the event. I wasn't a big fan of the interface, I found it a bit confusing to navigate with all the timezones. However you get to see John Legend do a 30 minutes jam in his living room, what about that!

Anyway, lots of announcements were made this year, as you could expect most of them focused on the cloud. You can find a summary [there](https://www.vmware.com/company/news/updates/2020/vmworld-2020-news-announcement-summary.html).

**_Carbon Black Cloud Workload_**

![](/img/vmworld2020-carbonblack.jpg)

That was one of the big guys at the show. VMware acquired Carbon Black in August 2019 for 2.1B and managed to turn it around and integrate it in their portfolio in time for the VMworld, well it will be GA in November but still not bad. It fits into VMware's drive towards intrinsic security, meaning it should be native and built into the system. Carbon Black Cloud Workload will offer agentless protection with a management console embedded inside vCenter via a plug-in to workloads running in virtualized, private and hybrid cloud environments.

**_VMware Cloud DR_**

![](/img/vmworld2020-clouddr.jpg)

As someone who managed traditional SRM implementations I was really excited about this one as I found it super interesting. Site Recovery has been around and allowed you to replicate workloads to VMC on AWS. With VMware Cloud DR, you can now replicate your workload to cheap native cloud storage backed by Amazon S3 and recover it to VMC on AWS with just in time SDDC provisioning. Meaning you only pay for the storage during normal operations. You only pay for compute when you spin up an SDDC when you need to recover or test. You can keep a small footprint SDDC running, called Pilot Light version for the most critical workloads that can't afford to wait for the spinning up of the SDDC. This technology of replicating to native cloud storage was made possible with the acquisition of Datrium by VMware this summer. Note that the replication and failback operation only transfer deltas to optimize bandwidth utilization and TCO by extension.

**_vRealize AI Cloud_**

![](/img/vmworld2020-vrai.jpg)

vRealize AI made me feel like I was in Minority Report. The way this product works is quite incredible. Its purpose is to observe the trend of the environment workloads and adjust settings on the hosts to improve IOPS and latency dynamically. Say your VDI boot storm and your DB dumps require different configurations at different time for best performance, vRAI will accomodate. The resources of the environment will be monitored via data sampling, sent to a SaaS data lake to be stored, analyzed to identify potential improvement and action are set to the vSphere and VSAN tuneables. Then vRAI will analyze the performance improvements and start again in an infinite loop to achieve best performance. The solution will eventually have a very wide scope but it will start with VSAN self-tuning at first. vRAI Cloud will be available in every vRealize Cloud Universal subscription with vRealize Operations Cloud.

**_VMware NSX Advanced Threat Prevention_**

![](/img/vmworld2020-nsxatp.jpg)

Another acquisition that was melted in the VMware roadmap with Lastline's network traffic analysis (NTA), fueled with AI, that was integrated into VMware NSX Service-defined Firewall. This distributed and scale-out firewall protects east-west traffic across multi-cloud environments and uses unsupervised and supervised machine learning to identify threats and reduces false positives by up to 90%. This other science fiction tech can apply virtual patches at every workload in the environment. NSX advanced threat detection will sense all east-west traffic and after a few days will offer visibility on all the device types seen throughout the network, their OS and all the services and applications communicating. Machine learning is then applied to all this gathered data to detect potential malicious activity.

**_Tanzu Support For VMware Cloud On AWS_**

![](/img/vmworld2020-tanzu.png)

Application modernization is at the forefront of this year's VMworld. Tanzu is VMware's brand name for their modern apps portfolio. It started with mission control which allows to centralize the management of Kubernetes clusters regardless of where they run and evolved into a beast made of several companies acquisitions. It is integrated into vSphere and interacts with NSX (it gets confusing). Tanzu is now generally available for VMware on AWS and still in preview state on Oracle Cloud VMware Solution as well as Google Cloud VMware Engine.

**_vRealize Cloud Universal_**

![](/img/vmworld2020-vrcu.jpg)

VMware vRealize Cloud Universal accelerates cloud adoption by combining SaaS and on-premises capabilities for automation, operations, and log analytics into one license. It gives the possibility to deploy cloud management on premises or SaaS and provides the freedom to move between the two as needed. vRealize Cloud Universal includes vRealize Cloud Federated Catalog, Cloud Federated Analytic, AI Cloud, Cloud Subscription Manager, Cloud Log Insight, Operations Cloud, Automation Cloud as well as PLUS Proactive Support with VMware Skyline. The subscription comes in 3 editions illustrated above.

**_Project Monterey_**

![](/img/vmworld2020-monterey.png)

A pretty big deal in the hardware space is project Monterey, a rearchitecture of VCF from the hardware up to support modern applications. A new concept of SmartNIC is introduced to deliver maximum performance, zero-trust security, and simplified operations. SmartNICs are also supposed to extend support to bare metal OSes and applications across on-premise and cloud. VMware is working partnerships with vendors to offer a broad set of SmartNIC to customers. A SmartNIC is a NIC with a general-purpose CPU, out-of-band management, and virtualized device functionality to relieve the core CPU of the server.

**_New versions (NSX-T 3.1 and vRNI 6.0)_**

VMware release version 3.1 of NSX-T offering new API-driven advanced routing and multicast capabilities, along with automated deployment of workflows through Terraform Provider. It will also support larger-scale global deployments and disaster recovery use cases.

vRealize Network Insight 6.0 brings Network Assurance and Verification capabilities to determine whether the network is meeting its intended goals. It uses formal verification for better network planning and path troubleshooting. It will aslo add new VMware SD-WAN visibility capabilities with path tunnel visibility and round-trip time latency in a richer dashboard. Some improvements are also brought to the cloud integration and operations enhancements.

**VMware footprint in every major public cloud**

![](/img/vmworld2020-azurjpg.png)

Since Azure VMware Solution is generally available, there is now a production VMware footprint in every major public cloud (AWS, Azure, Google Cloud, IBM Cloud, Oracle Cloud). Customers will be able to leverage Azure Hybrid Benefit, integration with Microsoft Office 365 and other native Azure services, as well as Azure console integration. 

Other enhancements have been added to VMC on AWS such as:

* **VMware Transit Connect:** Provides any-to-any connectivity between on-premises, VMC on AWS SDDCs and AWS VPCs using AWS Transit Gateway and AWS Direct Connect Gateway.
* **Enhanced automation and operations:** Expanded vRealize Operations, Cloud Automation, Orchestrator, Log Insight and Network Insight support.
* **Enhanced HCX capabilities:** Replication Assisted vMotion, local routing for migrated VMs and migration grouping.