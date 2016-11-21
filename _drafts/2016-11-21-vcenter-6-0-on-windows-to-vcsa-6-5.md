---
layout: post
published: false
title: vCenter 6.0 on Windows to VCSA 6.5
---
As everyone knows now VMware released the [version 6.5](https://blogs.vmware.com/vsphere/2016/10/introducing-vsphere-6-5.html) of vSphere/vCenter along with a version of the vRealize suite. This new version comes with loads of awesome new feature that I won't detail as there are already millions of posts about it, but one feature that I wanted to expand on is the vCenter migration tool.

This tool allows you to migrate from a vCenter server installed on a windows box to a vCenter Server Appliance (VCSA) seemlessly and automatically, taking off the pain of doing it manually.

This tool used to be a fling developped by the community and got taken over by VMware because it was so good. However it had quite a long list of prerequisites and was applicable only to a few use case scenarios. With the support brought by VMware, this tool is now even better and integrated in the vCenter server Appliance image.

When the tool was still a Fling it supported only migrations from VCS5.5 to VCSA6.0. It is probably because the release is so fresh but I couldn't find anything stating the compatibility for a migration from 6.0 to 6.5 so I tried and it worked fine.