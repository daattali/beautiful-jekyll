---
layout: post
title: Where do MSPs go to protect their workloads?
description: Learn about how Nakivo helps MSP protect their most critical workloads
date: 2022-04-25T17:00:55.694Z
fb-img: null
nobanner: "yes"
---

The last few years have been ruthless in terms of cybersecurity attacks, in particular ransomware becoming more and more widespread across the board. While any company can be the target of such attacks, MSP are often a prime choice for bad actors. The fact that multiple small and medium sized companies rely on them to handle the bulk of their IT operations makes attacking an MSP an "x birds one stone" type of thing. If we get past the dark cloud of ransomware hovering over us, MSPs also need solid backup solutions in order to offer their customers reliable data protection.

NAKIVO Backup & Replication provides a wide array of features to deliver efficient and profitable backup-as-a-service offerings. Nakivo B&R provides a data protection platform to protect any clients’ workloads ranging from virtual, physical, cloud and SaaS environments. The ransomware recovery features are among the most critical ones but MSPs also enjoy the simple administration of multi-tenant environments as well as the per-workload pricing model.

## True and resilient Multi-Tenancy

MSPs being MSPs, multi-tenancy is the bread and butter of the company and connecting to each and every client manually doesn't sound like fun. To make things more streamlined, you can offer backup as a service (BaaS) to up to 1000 clients with a single NAKIVO Backup & Replication deployment. The web interface is pretty simple to use and includes everything MSPs need to take care of each client in a fast and proactive fashion. Tenants can also monitor their backup and data activites themselves with the self service portal which can be customized to match the client's company's look and feel. And yes, tenants are of course isolated from each other. With multi-tenancy you can offer your clients Backup-as-a-Service, Replication-as-a-Service, and Disaster-Recovery-as-a-Service, for VMware, Hyper-V and AWS EC2 environments.

![nakivo self-service portal](/img/2022-05-30-19-21-09.png)

## Ransomware protection

While there is nothing like risk 0, MSPs are responsible for their clients' data so they need to make sure they put everything in place to mitigate the risk of [Ransomware](https://www.vxav.fr/2021-11-15-how-nakivo-backup-replication-can-help-you-with-ransomware/) attacks as much as possible. Nakivo B&R tackled this through a number of measures and best practices such as:

* Immutable backups when stored on Amazon S3 or in a local Linux-based repository which protects them from encryption or deletion with the hardened appliance.
* Create air-gapped backups by sending backup copies to tape.
* Apply the 3-2-1-1 backup rule (3 copies on 2 different storage media, 1 copy stored offsite and 1 copy stored in air-gapped or immutable form).
* With 2FA enabled, users need a code provided by the Google Authenticator mobile app or by email to access the solution and backups.

## VMware Cloud Director integration

One of the things I didn't expect from Nakivo was the integration with VCD. I recently got into VMware Cloud Director and built a lab with NSX-T, NSX ALB and vSAN to evaluate [CAPVCD](https://www.vxav.fr/2022-05-15-cluster-api-with-vmware-cloud-director-10.3-(capvcd),-nsx-t-and-alb/). Many MSPs use VMware Cloud Director to provide resources to their tenants in an automated fashion with quotas along with all the bells and whistles. Nakivo B&R can now integrate with VMware Cloud Director to backup vApps, individual VMs and vApp metadata to local storage, NAS and the cloud (Amazon S3...). Objects can then be restored directly to the Cloud Director hierarchy.

![vmware cloud director nakivo](/img/2022-05-30-19-35-15.png)

## One Solution to rule them all

MSPs manage environments and provide resources, clients and environments can be wildly different from one another and the backup solution has to be fit for any of these use cases. Because NAKIVO Backup & Replication is an all-in-one backup solution, MSPs can use it to protect workload of all shape or form such as virtual, cloud, physical and SaaS workloads in vSphere, VMware Cloud Director, Hyper-V, Nutanix AHV, Amazon EC2, Linux, Windows servers, workstations, Oracle Database, Microsoft 365, the list goes on. Being able to backup any of these to any type of storage repository (NAS, Windows, Linux...) from one single place offers MSPs the ease of use the need for they daily operations.

## Secure Connection to Remote Environments

The main duty of MSPs is to manage their customers' environments, and you need remote access to said environment in order to do that. Security being on the forefront of the IT landscape in the last few years (arguably ever), ensuring a secure remote connection to the client's environment is paramount to maintain a good level of service and trust between the parties. 

Nakivo B&R lets you establish secure connections to the remote IT infrastructures of the clients over one port without requiring bulky VPN connections with each tenant. This is made possible through a Proxy Transporter, a Transporter deployed at a remote environment with the Direct Connect feature enabled which communicates with the transporter and the director that are deployed on the master site.

![nakivo direct connect feature](/img/2022-05-30-19-48-28.png)

## Flexible pricing for MSP

Pricing being core to MSPs, Nakivo Backup & Replication decided to decline their offering into three editions to give MSPs as much financial flexibility as possible. However, note that they all include 24/7 Support for MSPs and clients:

* MSP Pro
* MSP Enterprise
* MSP Enterprise Plus

The subscriptions are charged per workload/month with a minimum of 10 workloads. As always, the annual subscription will set you back less than the monthly one.
