---
layout: post
title: VMworld 2020 announcements
DATE: 

---
This year's VMworld is like no other before due to the current situation. Everything is accessible on the virtual platform provided you registered for the event. I wasn't a big fan of the interface, I found it a bit confusing to navigate with all the timezones. However you get to see John Legend do a 30 minutes jam in his living room, what about that!

Anyway, lots of announcements were made this year, as you could expect most of them focused on the cloud.

**_Carbon Black Cloud Workload_**

![](/img/vmworld2020-carbonblack.jpg)

That was one of the big guys at the show. VMware acquired Carbon Black in August 2019 for 2.1B and managed to turn it around and integrate it in their portfolio in time for the VMworld, well it will be GA in November but still not bad. It fits into VMware's drive towards intrinsic security, meaning it should be native and built into the system. Carbon Black Cloud Workload will offer agentless protection with a management console embedded inside vCenter via a plug-in to workloads running in virtualized, private and hybrid cloud environments.

**VMware Cloud DR**

![](/img/vmworld2020-clouddr.jpg)

As someone who managed traditional SRM implementations I was really excited about this one as I found it super interesting. Site Recovery has been around and allowed you to replicate workloads to VMC on AWS. With VMware Cloud DR, you can now replicate your workload to cheap native cloud storage and recover it to VMC on AWS with just in time SDDC provisioning. Meaning you only pay for the storage during normal operations. You only pay for compute when you spin up an SDDC when you need to recover or test. You can keep a small footprint SDDC running, called Pilot Light version for the most critical workloads that can't afford to wait for the spinning up of the SDDC. This technology of replicating to native cloud storage was made possible with the acquisition of Datrium by VMware this summer. Note that the replication and failback operation only transfer deltas to optimize bandwidth utilization and TCO by extension.

**vRealize AI Cloud**

![](/img/vmworld2020-vrai.jpg)

vRealize AI made me feel like I was in Minority Report. The way this product works is quite incredible. Its purpose is to observe the trend of the environment workloads and adjust settings on the hosts to improve IOPS and latency dynamically. Say your VDI boot storm and your DB dumps require different configurations at different time for best performance, vRAI will accomodate. The resources of the environment will be monitored via data sampling, sent to a SaaS data lake to be stored, analyzed to identify potential improvement and action are set to the vSphere and VSAN tuneables. Then vRAI will analyze the performance improvements and start again in an infinite loop to achieve best performance.