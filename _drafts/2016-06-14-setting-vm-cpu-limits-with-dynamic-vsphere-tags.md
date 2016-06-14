---
layout: post
published: false
title: Setting VM CPU limits with dynamic vSphere tags
---
In the majority of VMware environments, the use of limits (especially memory limits) is strongly discouraged as it can lead to several misbehaviours such as CPU ready or memory swapping, which no one wants.  
But in some cases it can be useful to leverage them, provided it is implemented with sensibility. For example, if you host customer VMs running the same piece of software, it is likely that you want to serve them equally as they probably pay the same amount of money.  

Managing limits can sometimes be a hassle as there is no view in the client for the limits or reservations, you need to check and set on a per-vm basis.

In order to simplify the process of assigning CPU limits to the virtual machines I came up with a PowerCLI script that is called every night by a scheduled task from a "task box"