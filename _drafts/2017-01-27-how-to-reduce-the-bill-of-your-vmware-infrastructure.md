---
layout: post
published: false
title: How to reduce the bill of your VMware infrastructure
---
Since the start of virtualisation as we know it, two CPU sockets configurations were the obvious choice since it allowed to increase density and put more VMs in a single server, saving in the meantime money on the other components such as RAID controllers, network cads/HBAs, chassis, disks, you name it.

This is all great until you choke on the price of licenses... Like many other software companies, VMware licenses most of its products on a per-socket basis. Not cores!

![Sockets.jpg]({{site.baseurl}}/img/Sockets.jpg)

So a servers with 2 CPUs of 8 cores each would require 2 vSphere licenses. If you are using vRops you will need 2 vRops licenses. If you use VSAN you will need 2 VSAN and so on. As you can imagine the number at the bottom of the bill quickly skyrockets, but you can control it a little.

So how do you save money then? Easy:
- Instead of two 8 cores CPUs, why not using a single socket 16 cores CPUs?

With the evolution of processors, every year the manufacturers such as Intel and AMD increase the density of cores per CPU. In the 4th generation of E5-2600 (v4), the biggest CPU includes 22 cores!

Let's have a look at the evolution of the core count on the biggest CPUs in the E5-2600 family over the years:

| Year | CPU Model | Core count |
|------|-----------|------------|
| 2012 | E5-2690   | 8          |
| 2013 | E5-2697 v2| 12         |
| 2014 | E5-2699 v3| 18         |
| 2016 | E5-2699 v4| 22         |

source: [https://ark.intel.com/](https://ark.intel.com/)

_M. Picky will say:_

>But the clock speed reduces as well !

True, the denser the CPU, the slower the cores.

_Why does in not bother me?_

>Because that's what most of virtualised environments need: More cores to improve the concurrency without doubling the sockets.

So let's include the **Money factor** and have a look at it to prove that it could save you good money to switch to single socket servers!

### Parameters of the study

We will see here 2 scenarios:
- **Scenario A : Small infrastructure**, 3 hosts running vSphere Standard only.
- **Scenario B : Advanced Infrastructure**, 8 Hosts running vSphere with Operations Manager Enterprise Plus and VSAN advanced.

In each scenario we will detail 2 configurations:
- **Single socket** servers equipped with E5-2698 v4 (20 cores each)
- **Dual socket** servers equipped with E5-2640 v4 (10 cores each so 20 cores per server)

I picked these models deliberatly to have a fair point of comparison: the total number of cores in the cluster.

The price of the processors come from the Intel ARK website and the price of the VMware licenses from the Dell configurator website. Whether the prices are perfectly accurate doesn't really matter as the point is to show a difference in relation to each scenario. vCenter is not included because the price will always be the same (vCenter Standard pricing).

For these configs I set a fixed base price for the servers (no license, no CPU) of 3000$ and 5000$ respectively. Again this is not relevant as it will be a constant, so let's dig in.

## Scenario A

SMB company running a 3 hosts cluster on vSphere Standard. 

![Scenario-A.jpg]({{site.baseurl}}/img/Scenario-A.jpg)

- Single socket, E5-2698 v4 - **Cluster price: $22,788**
- Dual socket, E5-2640 v4 - **Cluster price: $22,854**

Here we can see that the dual-socket servers are almost at the same price as the single socket one.

To get a more accurate idea, let's check the price per GHz.

_Single socket, E5-2698 v4_

1 Socket x 20 cores x 2.20GHz x 3 hosts = 132 GHz

$22,788 / 132 GHz = $172.63/GHz

_Dual socket, E5-2640 v4_

2 Sockets x 10 cores x 2.4 GHz x 3 hosts = 144 GHz

$22,854 / 144 GHz = $158.70/GHz

Eventhough the price of purchase is greater for the dual socket server, it proves to actually be cheaper for the resources you get. Yes the number of cores matters a lot in virtualisation, but for a $66 difference I'd rather have an extra 12 GHz.

In the meantime on a dual socket server, you have to possibility to use all the memory and PCI slots, which is not true on a single socket server.

**Outcome Scenario A: Dual socket suits small environments better.**

## Scenario B

Middle sized company running an 8 hosts cluster on vSphere Entperprise Plus, monitor it with vRops and stretch the storage with VSAN advanced edition.

![Scenario-B.jpg]({{site.baseurl}}/img/Scenario-B.jpg)

- Single socket, E5-2698 v4 - **Cluster price: $156,208**
- Dual socket, E5-2640 v4 - **Cluster price: $235,824**

In this scenario for the _same number of cores (not GHz)_ the cluster is **$79,616 more expensive with 2 socket** servers. Quite a difference right?

I think these figures are self explanatory, but let's follow the same reasoning as scenario B and get a price per GHz.

_Single socket, E5-2698 v4_

1 Socket x 20 cores x 2.20GHz x 8 hosts = 352 GHz

$156,208 / 352 GHz = $443.77/GHz

_Dual socket, E5-2640 v4_

2 Sockets x 10 cores x 2.4 GHz x 8 hosts = 384 GHz

$235,824 / 384 GHz = $614.12/GHz

Again, $170.35 difference for every single GHz in the cluster (Think that the same applies to memory GB, local storage ...).

I bet the same M. Picky will say:

>But there are 32 GHz more on the dual socket servers.

True, however this time let's make no compromise and make the point even more obvious!

What if I added a host to the (single CPU) cluster to give M. Picky his 32 GHz?

![Scenario-B-9.jpg]({{site.baseurl}}/img/Scenario-B-9.jpg)

- 9 x Single socket, E5-2698 v4 - **Cluster price: $175,734**

1 Socket x 20 cores x 2.20GHz x 9 hosts = 396 GHz

So what is to note here :
- Still $60,090 cheaper than the 8 hosts single socket cluster ! (That could provide training to your whole team)
- 12 more GHz to reduce the impact of the hypervisor overhead
- 20 more physical cores to decrease the vCPU to physical core ratio
- 1 more host to improve redundancy and reduce failure domains
- Room for growth.

Should we stop here? Maybe. Will we? Boy no!

Let's try to match the $235,824 of the dual socket cluster with single sockets servers.

And here it is:

![Scenario-B-12.jpg]({{site.baseurl}}/img/Scenario-B-12.jpg)

- 12 x Single socket, E5-2698 v4 - **Cluster price: $234,312**

So to summarize, what do you get for $235,824? Imagine these have 192 GB of memory and 3TB of raw local storage each

| Dual Socket | Single Socket |
|-------------|---------------|
| 160 cores   | 240 cores     |
| 384 GHz     | 528 GHz       |
| 1,536GB RAM | 2304GB RAM    | 
| 28TB RAW    | 36TB raw      |
| 8 hosts     | 12 hosts      |
| $235,824    | $234,312      |

**Outcome Scenario B: Single socket servers are much more cost efficient as you leverage more VMware (socket base licensed) products.**

## Conclusion

If like M. Picky you have always worked with dual socket servers and thought that single sockets are for peasants, consider looking into it from this day forward. With the constant evolution of processors by the manufacturers, it makes now more and more sense to go for a single processor with lot's of cores instead of dual smaller CPUs, especially in environments running lot's of small/medium size VMs. 

You might realise that you'll save a lot of money or maybe it won't change a lot. Again it will depend on your environment.

If you have planned to start small, because of budget restrictions for example, and expand later on with solutions like VSAN, VROPS or NSX, I highly recommend to take the full picture into account when doing your sizing. Because when the time comes to write the second check you will be happy to have single socket servers.

If you are thinking "Why not have half as many servers but each with two processors of 22 cores and full of RAM?". Well, technically you can but I wouldn't recommend it.

Yes you will maybe save a few $ grands on the price of the chassis, raid controllers, motherboard ... But what if you lose a host? Where HA would need to restart 30 VMs on a 22 cores host, will have to restart 60 VMs on a 44 cores one, twice as much sweat during the failover process! You are basically reducing your failure domain and that's something you (as a sane admin) want to avoid. I won't get into the Scale-out versus Scale-up debate as this is not the point but it's definitely something to take into account and avoid getting carried away on crazy configurations.