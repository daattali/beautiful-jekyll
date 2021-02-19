---
layout: post
title: 'vCenter 7 update 1c: Advanced Cross vCenter vMotion (XVM)'
DATE: 

---
Migrating virtual machines across vCenter instances has been a thing for several years now but it wasn't a straightforward process at first. After a while the "Cross vCenter Workload Migration Utility" fling was released in order to simplify the process and remove the need for enhanced linked mode.

### Advanced Cross vCenter vMotion (XVM)

It is not often that a minor update is exciting but this time it certainly is! In the latest vCenter 7.0 update 1c (7.0.1.00300) iteration, "_Advanced Cross vCenter vMotion_" (also called XVM) was finally embedded natively into the vSphere client. This feature simplifies a number of scenarios ranging from basic workload mobility to bulk migrations to a public cloud.

* Does not depend on vCenter Enhanced Linked Mode or Hybrid Linked Mode
* Works for both on-premise and cloud environments.
* Works across different SSO domains.
* Compatible with vCenter 6.x or later.
* Possibility to "_Migrate_" (send) or "_Import_" (receive) virtual machines.

![](/img/xvm000.PNG)

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

* Select a **Compute resource** at the destination. In my example I only have a single host in the datacenter for testing.

![](/img/xvm5.png)

* Then select a **datastore**. Note that just like any storage vMotion you can change the disk format should you want to (thin, thick..).

![](/img/xvm6.png)

* Select a **VM Folder** where you want the VM in the inventory.

![](/img/xvm7.png)

* And finally you can choose a **portgroup** to connect your VM. You obviously need to ensure beforehand that the distant network is configured properly (same gateway, routing...).

![](/img/xvm8.png)

* Review the migration summary details and click **Finish** to trigger the move. 

![](/img/xvm9.png)

The migration will appear in the tasks like any other vMotion as opposed to how it was with the Fling.

### Importing a virtual machine