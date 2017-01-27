---
layout: post
published: false
title: How to reduce the bill of your VMware infrastructure
---
Since the start of virtualisation as we know it, two CPU sockets configurations were the most popular on the market since it allowed to increase density and put more VMs in a single server. Saving in the meantime money on the other components such as RAID controllers, network cads/HBAs, chassis, disks, you name it.

This is all great until you choke on the price of licenses. Like many other software companies, VMware licenses most of its products on a per-socket basis.

So a servers with 2 CPUs of 8 cores each would require 2 vSphere licenses. If you are using vRops you will need 2 vRops licenses. If you use VSAN you will need 2 VSAN and so on. As you can imagine the number at the bottom of the bill quickly skyrockets.

So how do you save money then? Easy:
- Instead of two 8 cores CPUs, why not using a single socket 16 cores CPUs?

With the evolution of processors, every year the manufacturers such as Intel and AMD increase the density of cores per CPU. In the 4th generation of E5-2600 (v4), the biggest CPU includes 22 cores!

Let's have a look at the evolution in the core count of the biggest CPUs in the E5-2600 family over the years:

| Year | CPU Model | Core count |
|------|-----------|------------|
| 2012 | E5-2690   | 8          |
| 2013 | E5-2697 v2| 12         |
| 2014 | E5-2699 v3| 18         |
| 2016 | E5-2699 v4| 22         |

source: [https://ark.intel.com/](https://ark.intel.com/)

_Some will say: But the clock speed reduces as well !_

True, the denser the CPU, the slower are the cores.

Why? Because that's what most of virtualised environments need: More cores to increase the concurrency without doubling the count of sockets.

Let's include the "Money factor" and have a look to prove that it will save you good money!

### Parameters of the study

We will see here 2 scenarios:
- **Scenario A : Small infrastructure**, 3 hosts running vSphere Standard only.
- **Scenario B : Advanced Infrastructure**, 8 Hosts running vSphere with Operations Manager Enterprise Plus and VSAN advanced.

In each scenario we will detail 2 configurations:
- **Single socket** servers equipped with E5-2698 v4 (20 cores each)
- **Dual socket** servers equipped with E5-2640 v4 (10 cores)

I picked these models deliberatly to have a fair point of comparison: the total number of cores in the cluster.

The price of the processors come from the Intel ARK website and the price of the VMware licenses from the Dell configurator website. Whether the prices are perfectly accurate doesn't really matter as the point to make is to show a difference in relation to each other server.

For these configs I set a fixed base price for the servers (no license, no CPU) to 3000$ and 5000$ respectively. Again this is not relevant as it will be a constant, so let's dig in.

### Scenario A

SMB company with a 3 hosts infrastructure running vSphere Standard. 

