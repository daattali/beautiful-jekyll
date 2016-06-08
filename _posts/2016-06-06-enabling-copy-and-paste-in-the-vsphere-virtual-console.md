---
layout: post
published: false
title: Enabling copy and paste in the vsphere virtual console
---
It is not always that I need to use the virtual console on a virtual machine as most of them have remote desktop or PowerShell remoting enabled, but every so and often we need to use the console and what is more annoying than not being able to copy and paste from your desktop to the VM.  
You will most likely need it in multiple cases like after deploying a VM from template or creating one from scratch, if if doesn't have network connectivity, if the OS is bricked, ...

Copy and paste can be enabled at the VM or at the host level depending on your needs. Personnaly I chose to do it on a per-VM basis as I quite rarely use the console for the benefit of RDP or PowerShell remoting.

### Per virtual machine

In order to enable copy and/or paste there are two lines to add in the configuration of the virtual machine. These two lines are to be added in the advanced configuration.  
To enable in the vSphere web client the VM needs to be powered off otherwise the "edit
