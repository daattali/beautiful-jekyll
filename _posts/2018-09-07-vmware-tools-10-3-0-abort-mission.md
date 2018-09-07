---
layout: post
published: true
title: VMware Tools 10.3.0 - Abort mission!
---
VMware rolled out the latest version of the VMware Tools in version 10.3.0 but recalled them quickly afterwards due to an issue with the VMXNET3 network driver for Windows. In some cases the symptoms can be a Purple Diagnostic Screen (PSOD) or guest network connectivity loss. Not fun...

Virtual machines can be affected if the following 3 conditions are met:
- vSphere ESXi 6.5 hosts
- VM Hardware Version 13
- Windows 8/Windows Server 2012 or higher guest OS

You can run this PowerCLI one-liner to check your environment and see if you are concerned:

```Powershell
Get-VM | where {$_.guest.toolsversion -eq "10.3.0" -and $_.version -eq v13 -and $_.guest.osfullname -match "Windows server 2012|Windows server 2016|Windows 8|Windows 10"}
```

If there is no output it means you are fine. However if VMs are displayed you need to take actions:
- Download VMware tools 10.2.5 : [here](https://my.vmware.com/web/vmware/details?downloadGroup=VMTOOLS1025&productId=614)
- Uninstall the VMware tools on the affected VMs
- Install VMware tools 10.2.5

