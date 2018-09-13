---
layout: post
published: false
title: VMware Tools 10.3.2 - and AppDefense
---
Just a few days ago [I wrote about VMware Tools 10.3.0](http://www.vxav.fr/2018-09-07-vmware-tools-10-3-0-abort-mission/) that were recalled due to an issue with the VMXNET3 network driver for Windows. 

It didn't take long for VMware to get back on their feet and release the version 10.3.2 and make 10.3.0 deprecated. Can be downloaded [here](https://my.vmware.com/web/vmware/details?downloadGroup=VMTOOLS1032&productId=742).

![10.3.0-deprecated.jpg]({{site.baseurl}}/img/10.3.0-deprecated.jpg)

Note that this version (just like the gammy 10.3.0) requires Microsoft Visual C++ 2017 Redistributable version 14.0 so if your company cannot meet this requirement for any reason you should stick to 10.2.x.

> VMware Tools 10.3.2 depends on and ships Microsoft Visual C++ 2017 Redistributable version 14.0. While preparing the system for VMware Tools 10.3.0 installation, Microsoft Visual C++ 2017 Redistributable is installed on the system as a prerequisite. Installing or upgrading to VMware Tools 10.3.2 is not supported for Windows versions that do not meet the prerequisites and customers should continue to use VMware Tools 10.2.x or older until they can patch or update Windows OS to meet the prerequisites for VMware Tools 10.3.0.

This release is compatible with Windows Vista and later, Red Hat Enterprise Linux (RHEL) 5 and later, SUSE Linux Enterprise Server (SLES) 11 and later, Ubuntu 10.04 and later, other distributions with glibc versions 2.5 and later, Mac OS X versions 10.11 and later, and Solaris.

Among the short list of new things are bug fixes and performance improvement in the OpenGL driver, the ability to update the PVSCSI driver during a Windows update on Windows Server 2016, some other "core" changes. Though the most visible of all is the integration of AppDefense in the VMware Tools.

### AppDefense

Here's an extract of the [Tool's documentation](https://docs.vmware.com/en/VMware-Tools/10.3.0/vmware-tools-user-guide.pdf) about AppDefense.

> VMware Tools installation includes the VMware AppDefense, a security management, and monitoring
solution. This data center security solution is based on application control, detection, and response.
AppDefense agent can be installed on the guest virtual machine using the VMware Tools installer. Virtual
machines with VMware Tools installed are monitored and managed whenever they are started up on an
ESXi host that has the solution installed. However, VMware Tools cannot install the AppDefense
component automatically. The component must be installed manually. 

It is only supported on ESXi 6.5 for the following OSes:
- Windows 2008 R2
- Windows 2012
- Windows 2012 R2
- Windows 2016

![10.3.0-appdefense.jpg]({{site.baseurl}}/img/10.3.0-appdefense.jpg)

In case you are wondering what AppDefense, it is a security service aimed at protecting applications running in virtualized environments. It embeds threat detection and response into the virtualization layer on which applications and data live following a 3 tiers model: **Capture > Detect > Respond**.

> From inside the vSphere hypervisor, AppDefense has an authoritative understanding of how data center endpoints are meant to behave and is the first to know when changes are made. When a threat is detected, AppDefense can trigger vSphere and VMware NSX® to orchestrate the correct response to the threat, without the need for manual intervention. It can Block process communication, Snapshot an endpoint for forensic analysis, Suspend an endpoint, Shut down an endpoint. The first thing that most malware variants do when they reach an endpoint is disable antivirus and other agent-based endpoint security solutions. The hypervisor provides a protected location from which AppDefense can operate, ensuring that even if an endpoint is compromised AppDefense itself is protected.

Basically AppDefense monitors applications against their intended state for what they are supposed to do using machine learning. If a change in behaviour of an application happen, AppDefense will pick it up and raise an alarm or responds automatically to it.

[here's](https://blogs.vmware.com/networkvirtualization/2017/09/ensuring-good-appdefense.html/) some more info about it on VMware blogs.
