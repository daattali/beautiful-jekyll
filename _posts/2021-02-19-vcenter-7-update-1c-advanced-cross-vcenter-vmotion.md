---
layout: post
title: 'vCenter 7 update 1c: Advanced Cross vCenter vMotion (XVM)'
DATE: 

---
Migrating virtual machines across vCenter instances has been a thing for several years now but it wasn't a straightforward process at first. After a while the Cross vCenter Workload Migration Utility fling was released in order to simplify the process and remove the need for enhanced linked mode.

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

The task will appear like any relocating task on the source system but you will see an "_Initiate vMotion receive operation_" task on the destination vCenter.

![](/img/xvm11.png)

I ran a ping to the VM during the migration and I only got a longer response time during the switchover but that doesn't mean you are 100% sure not to lose pings (just a word of caution for mission critical workloads).

![](/img/xvm12-1.png)

### Importing a virtual machine

Advanced Cross vCenter vMotion also brings the possibility to import virtual machines from a distant vCenter. This can be useful of the remote instance runs a version lower than vCenter 7 update 1c and doesn't have XVM in the vSphere client for example.

* To initiate an **Import VMs** task, right click on a compute resource and select the option.

**![](/img/xvm10.png)**

* Select the remote vCenter like shown previously and then select the virtual machine(s) you wish to import.

![](/img/xvm13.png)

The next steps are similar to the ones described in the Migrate chapter.

### Conclusion

There has been many occurences of features that started out as Flings which eventually made it into the core product because it was so popular. vCenter Server 7.0 update 1c is another example of what the community can bring to the table and it goes on to show how VMware listens to them.

Advanced Cross vCenter vMotion (XVM) will allow many companies to perform safe and efficient migrations whether they are on-premise or in hybrid scenarios. Is this a feature that you see yourself or your company using in the near future? Talk about your use case in the comment section !