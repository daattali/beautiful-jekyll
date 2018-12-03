---
title: Canceling hung tools upgrade task
layout: post
date: 2018-12-03 11:49:38 +0100
DATE: 2018-12-01 00:00:00 +0100

---
One of the steps of upgrading a vSphere deployment is to update the VMware tools to the version provided by the hosting ESXi server. Like most of you know, it is very easy to upgrade the tools from vCenter. You either click the _Update VMware Tools_ button in the _VMware Tools outdated_ warning, or you can use PowerCLI which has the benefit of offering the _-NoReboot_ switch.

Now regardless of the method you use to update, it is possible that the operation will hang for some reason. In this case, the options of the VM are greyed out, you cannot cancel the task in the UI, you cannot move the VM or mount the ISO to go manual, quite messy but easy to fix.