---
layout: post
title: What's new in Vembu BDR Suite v5.1
DATE: 
subtitle: ''
metadescription: Learn about the new features and improvements released with Vembu
  BDR Suite v5.1.
image: ''

---
The world of data protection has been in motion for the past several years with the rise of cloud services and SaaS in general. Vembu BDRSuite carved a place for the company among the leading backup software vendors with a robust virtual machine backup and recovery solution. While the core components are still being improved to answer production problematics, BDRSuite brought extensive cloud integration features in the latest versions to maintain the products place on the podium.

Following a change to a more rapid product releases cycle, Vembu announced the release of BDRSuite v5.1 Only four months after the release of [BDRSuite v5.0](https://www.vxav.fr/2021-10-11-vembu-bdr-suite-v5.0-ga-release/). BDRSuite v5.1 brings, among other things, the long awaited Object Storage Backup Repository and Backup Copy capabilities. Let's dig into it and find out what's new in Vembu BDR Suite v5.1.

#### Object Storage Backup Repository

As you know most backup solution often rely on local storage or some flavour of shared storage such as NFS, SMB, iSCSI and other protocols to present a volume or a share to the backup proxy. But how cool would it be to map cheap cloud storage as your destination to ensure flexibility and resilience? BDRSuite v5.1 now brings capabilities to use object storages such as AWS S3 & S3 compatible storage solutions as a storage destination for the backup data. A great use would be to use it to enforce the 3-2-1 rule with an offsite copy stored on a different medium.

#### Backup Copy

Like mentioned before, the 3-2-1 rule states that you should have 3 copies of your data, on 2 different mediums and 1 offsite copy. The Backup Copy feature in BDRSuite v5.1 will now allow you to create a copy of your primary backup data and store it in a different backup repository. Note that you can leverage Object Storage backup repos.

#### BDR Cluster Deployment

Many aspects of the datacenter often raise the question of wether to scale-up or scale-out. While scaling up may produce the same outcome, it induces some downtime while resizing the server and isn't particularly flexible. This is why BDRSuite v5.1 introduces BDR Cluster Deployment, a feature that lets you easily scale out your BDRSuite Backup Server by adding instances. You can then make them work together for load balancing and high availability 