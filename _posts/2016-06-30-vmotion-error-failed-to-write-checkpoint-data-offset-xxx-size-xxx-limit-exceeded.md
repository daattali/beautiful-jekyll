---
layout: post
published: true
title: >-
  vMotion error - Failed to write checkpoint data (offset xxx, size xxx): Limit
  exceeded.
---
Still in the process of migrating our dev cluster I was doing a whole bunch of storage vMotions to evacuate our old storage backend to the new one. Most of the VMs went smoothly but I ran into an error on one of them that I never encountered before. The VM's hardware version is version 9.

**Problem**

During the relocation I received the usual generic alert "Cannot migrate VM". I then looked at the events and noticed in the error stack:

```
Failed to write checkpoint data (offset 25150738, size 16384): Limit exceeded.
```

After googling the error, one of the first results was this old vsphere 4.0 KB: [KB1011971](https://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=1011971).  
In the note section it states:

> Using VMotion to migrate a virtual machine with VRAM greater than 30MB to an ESX/ESXi 4.0 Update 1 host might prevent you from migrating it back to a host that does not have this fix.

> When using high resolution monitors, VMware View may change the virtual machine's VRAM to greater than 30 MB.

Even though I am running a 6.0 cluster I opened the VM's console which displayed a big 1920x1080 resolution. So I looked at the video card config of the VM that was set to the default 16MB, which is the size that was in the error "_Failed to write checkpoint data (offset 25150738, size **16384**): Limit exceeded._"  
The video memory used by the VM being 25150738 (about 24MB) it was what was blocking the vMotion to proceed.

![videomemoryvm.jpg]({{site.baseurl}}/img/videomemoryvm.jpg)

**Resolution**

There are 2 solutions to fix this issue:

- Reduce the resolution of the virtual machine under 1280 x 1024 (the one I chose in this case).
- increase the memory allocated to the virtual video card.
  
-----------
  

Here is the chronology of the events and tasks pulled from my vRealize Log Insight appliance (chronologic order is top to bottom).

```
MyVCENTER vcenter-server: Task: Relocate virtual machine
source event_type vc_event_type vc_username vc_vm_name hostname appname vmw_vc_task_type

MyVCENTER vcenter-server: Migrating MyVM from MyHOST, Datastore-SRC to MyHOST, Datastore-DEST in MyDC
source event_type vc_details vc_event_type vc_username vc_vm_name hostname appname

MyVCENTER vcenter-server: Migrating MyVM off host MyHOST in MyDC
source event_type vc_event_type vc_username vc_vm_name hostname appname

MyVCENTER vcenter-server: Error message on MyVM on MyHOST in MyDC: Failed to write checkpoint data (offset 25150738, size 16384): Limit exceeded.
source event_type vc_details vc_event_type vc_username vc_vm_name hostname appname vmw_vc_msg_vm

MyVCENTER vcenter-server: Cannot migrate MyVM from MyHOST, Datastore-SRC to MyHOST, Datastore-DEST in MyDC
source event_type vc_details vc_event_type vc_username vc_vm_name hostname appname

MyVCENTER vcenter-server: Alarm 'Migration error' on MyVM changed from Gray to Yellow
source event_type vc_event_type vc_vm_name hostname appname vmw_vc_alarm_type vmw_vc_alarm_source vmw_vc_alarm_status

MyVCENTER vcenter-server: Alarm 'Migration error' on MyVM triggered an action
source event_type vc_event_type vc_vm_name hostname appname vmw_vc_alarm_source

MyVCENTER vcenter-server: Alarm 'Migration error' on MyVM sent email to Alert@MyCompany.co.uk
source event_type vc_event_type vc_vm_name hostname appname
```
