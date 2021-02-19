---
layout: post
title: 'vCenter 7 update 1c: Advanced Cross vCenter vMotion (XVM)'
DATE: 

---
Migrating virtual machines across vCenter instances has been a thing for several years now but it wasn't a straightforward process at first. After a while the "Cross vCenter Workload Migration Utility" fling was released in order to simplify the process and remove the need for enhanced linked mode.

### Advanced Cross vCenter vMotion (XVM)

In the latest vCenter 7.0 update 1c (7.0.1.00300), the "Advanced Cross vCenter vMotion" (also called XVM) feature was embedded natively into the vSphere client. 

* Does not depend on vCenter Enhanced Linked Mode or Hybrid Linked Mode
* Works for both on-premise and cloud environments.
* Works across different SSO domains.
* Compatible with vCenter 6.x or later.
* Possibility to "_Migrate_" (send) or "_Import_" (receive) virtual machines.

In our demonstrations below we are running vCenter 7.0u1c on the initiating instance and vCenter 7u1a on the distant one.

### Migrating a virtual machine

* Initiating a cross-vCenter vMotion is as easy as it gets. Right click on the VM you want to relocate and select **Migrate**.

![](/img/xvm0-1.png)

* Select the new **Cross vCenter Server export** migration type. Note that if you don't see this option you need to update to vCenter 7 update 1c (7.0.1.00300).

![](/img/xvm1.png)

* Then you need to specify the target vCenter. Start by selecting **New vCenter** and type in the connection details (IP/FQDN, user, password). You can then save this information to have it ready for later use. Then click on **Login** to validate the information.

![](/img/xvm2.png)

* You may be prompted with the distant vCenter's certificate which you need to accept.

![](/img/xvm3.png)

* If the connection is successful you will be able to click **Next**.

![](/img/xvm4.png)

* 

![](/img/xvm5.png)

![](/img/xvm6.png)

![](/img/xvm7.png)

![](/img/xvm8.png)

![](/img/xvm9.png)

### Importing a virtual machine