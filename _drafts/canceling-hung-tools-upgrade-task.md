---
title: Canceling hung tools upgrade task
layout: post
date: 2018-12-03 11:49:38 +0100
DATE: 2018-12-01 00:00:00 +0100

---
One of the steps of upgrading a vSphere deployment is to update the VMware tools to the version provided by the hosting ESXi server. Like most of you know, it is very easy to upgrade the tools from vCenter. You either click the _Update VMware Tools_ button in the _VMware Tools outdated_ warning, or you can use PowerCLI which has the benefit of offering the _-NoReboot_ switch.

Now regardless of the method you use to update, it is possible that the operation will hang for some reason. In this case, the options of the VM are greyed out, you cannot cancel the task in the UI, you cannot move the VM or mount the ISO to go manual. If you wait long enough the task will eventually time out and get canceled but there is no point waiting. Quite messy but easy to fix.

To fix it we need to connect to the host running the VM via SSH, find its ID and use it to cancel the task.

* Find the ID of the troublesome VM (case sentitive)

    vim-cmd vmsvc/getallvms | grep my-vm-01

The output will be similar to this including the VM ID, **10** in the example below.

    [root@my-esxi-01:~] vim-cmd vmsvc/getallvms | grep my-vm-01
    10     my-vm-01   [my-datastore-01] my-vm-01/my-vm-01.vmx    windows7Server64Guest   vmx-10

* Cancel the task using the VM ID

    vim-cmd vmsvc/tools.cancelinstall 10

Once you've done that the task is canceled in vCenter and you can get back to fixing the tools install. 