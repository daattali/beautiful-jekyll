---
layout: post
title: 'vCenter 7 update 1c: Advanced Cross vCenter vMotion (XVM)'
DATE: 

---
Migrating virtual machines across vCenter instances has been a thing for several years now but it wasn't a straightforward process at first. After a while the "Cross vCenter Workload Migration Utility" fling was released in order to simplify the process and remove the need for enhanced linked mode.

![](https://core.vmware.com/sites/default/files/overview.PNG)

In the latest vCenter 7.0 update 1c, the "Advanced Cross vCenter vMotion" (also called XVM) feature was embedded natively into the vSphere client. 

* Does not depend on vCenter Enhanced Linked Mode or Hybrid Linked Mode 
* Works for both on-premise and cloud environments and across SSO domains.
* Compatible with vCenter 6.x or later.
* Possibility to "_Migrate_" (send) or "_Import_" (receive) virtual machines.

In our demonstrations below we are running vCenter 7.0u1c on the initiating instance and vCenter 7u1a on the distant one.

### Migrating a virtual machine