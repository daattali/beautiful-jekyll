---
layout: post
title: How to update to vSphere 7.0 Update 2
DATE: 
subtitle: ''
metadescription: The latest vSphere 7.0 Update 2 brings a wealth of new features spanning
  VSAN, vCenter and Tanzu.

---
VMware recently released vSphere 7.0 Update 2. It delivers a number of really interesting features and improvements in terms of performance and LifeCycle management. Among the main features we find :

· Nvidia backed AI & Developer Ready Infrastructure

· Enhanced security footprint

· Simplified operations with vLCM

· Performance improvements

· vSAN 7.0 Update 2

Refer to my blog for Altaro to find more detailed information about the release.

## Caveat on vSphere 7.0 Update 2 update

As of 19/03/2021, it is not possible to update to vSphere 7.0 Update 2 using either vLCM or esxcli. It has been pulled from the repo by VMware to address an issue discovered post release which would result in an error when trying to patch the host. 

> Cannot download VIB: ''. This might be because of network issues or the specified VIB does NOT exist or does NOT have a proper 'read' privilege set. Please make sure the specified VIB exists and is accessible from vCenter Server.

You can find more information on this issue in [KB83107](https://kb.vmware.com/s/article/83107?lang=en_US).

In the meantime it is still possible to update vSphere by booting the server on the vSphere 7.0 Update 2 ISO and updating it in interactive mode.

![](/img/v7u2.jpg)

VMware is currently working on it and this blog will be updated accordingly.

## How to update to vCenter 7.0 Update 2