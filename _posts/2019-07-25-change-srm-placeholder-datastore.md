---
layout: post
title: Change SRM placeholder datastore
DATE: 

---
For every virtual machine in a protection group, Site Recovery Manager creates a placeholder virtual machine at the recovery site. You must identify a datastore on the recovery site in which Site Recovery Manager can store the placeholder virtual machines. It only reserves a place for protected virtual machines in the inventory on the recovery site.

We are describing how to change the datastore used for placeholders. We assume you already have the new datastore ready.

1-Log in vCenter, head over to the SRM plugin  in Sites > Manage > Placeholder datastores and click the add datastore icon.

![](/img/phds1.png)

2-Pick the datastore and click OK.

![](/img/phds2.png)

3-Then select the currently used placeholder datastore and remove it.

![](/img/phds3.png)

4-Accept the warning.

![](/img/phds4.png)

5-Head over to the protection group associated with that placeholder datastore and remove the protection of all the VMs.

![](/img/phds5.png)

6-The VMs will go in a "Not Configured" state. Click the "Configure All" button and accept the warning.

![](/img/phds7.png)

At this point I sometimes had weird issues where the VMs would display an error and I couldn't protect it. I had to fiddle with it to get it to work (host rescan seemed to be it but not sure...).

![](/img/phds6.png)

7-Then the VMs should appear as protected. You can also check that the placeholder VMs disappeared from the old datastore and appear in the new one.

![](/img/phds9.png)