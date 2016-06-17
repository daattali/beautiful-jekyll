---
layout: post
published: false
title: Enabling datastore alerts on thin provisioning thresholds
---
Something every sensible VMware administrator is concerned about is the over commitment of the datastores. Since the dawn of times in virtualization it is possible to thin provision the disks of the virtual machines by not allocating the blocks to it, hence over commit the actual physical storage by provisioning X+Y GB even if the storage has only X GB to offer.

If the storage is well monitored and the storage activity of your VMs is predictable (i.e. no surprises with tempdb filling up) it is fine to have a bit of overcommitment environment.

![thick-thin.jpg]({{site.baseurl}}/img/thick-thin.jpg)

However, if you get to the point where one of your overcommited datastore runs out of storage you might get into trouble.  
- The thick provisionned VMs will keep running as the space has been "reserved" on the datastore so it is already ready for usage by the VM.
- The thin provisionned VMs asking for extra storage will be paused (imagine the db of a web stack).

See this very good post by Cormac Hogan for more details: [Thin Provisioning – What's The Scoop?](http://blogs.vmware.com/vsphere/2012/03/thin-provisioning-whats-the-scoop.html)

### Add an alarm for disk provisionned

This alert isn't set by default and is "hidden" in the datastore usage alert.

To set it, select your vCenter on the "Manage" tab then "Alarm definitions" and select "Datastore usage on disk"

![datastore-usage-on-disk.jpg]({{site.baseurl}}/img/datastore-usage-on-disk.jpg)

And click "Edit" to modify the alarm.

Then add a trigger, and select "Datastore Disk Provisioned".

img

The default thresholds are Warning = Datastore 100% Provisioned and Critical = Datastore 200% Provisioned.  
But because I am a little bit paranoid and I don't use thin disks a lot I set a lower value to be warned when 130% is reached.

You can then configure the action according to your alerting process (email, snmp and so on).