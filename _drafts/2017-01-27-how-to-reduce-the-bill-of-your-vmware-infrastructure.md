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

Let's have a look at the evolution in the core count of the biggest CPUs over the years: