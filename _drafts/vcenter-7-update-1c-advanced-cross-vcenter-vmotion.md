---
layout: post
title: 'vCenter 7 update 1c: Advanced Cross vCenter vMotion'
DATE: 

---
Migrating virtual machines across vCenter instances has been a thing for several years now but it wasn't a straightforward process at first. After a while the "Cross vCenter Workload Migration Utility" fling was released in order to simplify the process and remove the need for enhanced linked mode.

In the latest vCenter 7.0 update 1c, the "Advanced Cross vCenter vMotion" feature was added to the vSphere client which is directly integrated into the VMs' "migrate" action. Note that it does not depend on vCenter Enhanced Linked Mode or Hybrid Linked Mode and works for both on-premise and cloud environments.