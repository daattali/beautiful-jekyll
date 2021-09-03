---
layout: post
title: How to download and install Windows Server 2022
DATE: 
subtitle: ''
metadescription: Find out about Windows Server 2022 download and install in this blog.
  Learn about some some of the Windows Server 2022 new features.

---
In a world where security is increasingly important along with the adoption of hybrid cloud options, Microsoft recently released Windows server 2022 which builds on these industry requirements to offer a mature and secure platform. In this blog, we will discuss how to download and install Windows Server 2022 in VMware. We will also touch base on the Windows Server 2022 new features. 

## Windows Server 2022 hardware requirements

The hardware requirements haven't changed much from earlier versions. These are the minimum requirements. The amount of resources you need in your server will obviously depend on the purpose it will serve.

**Memory**

* 512 MB for core,  2 GB for Server with Desktop Experience
* ECC DIMMs for bare metal hosts

Note that you need at least 800MB of RAM during the installation process in a VM

**CPU**

* 1.4 GHz 64-bit processor (2 cores recommended)
* Compatible with x64 instruction set
* Supports NX and DEP, CMPXCHG16b, LAHF/SAHF, and PrefetchW
* Supports EPT or NPT

**Storage**

* 32GB for the OS as an absolute minimum (28GB for Core install)
* Add more space if you have significant memory size for the paging, hibernation, and dump files.

**Network**

* 1 Gbps network adapter, compliant with PCI Express architecture specification

## Download Windows Server 2022

There are a few ways you can get the Windows Server 2022 free download but the easiest and most flexible is probably to get the ISO in the Microsoft Evaluation Center and install it in a virtual machine. The Windows Server 2022 ISO gives you access to a 180 days free trial period. Note that the ISO is a bit chunky with about 5.2GB in size.

* Head over to the **Microsoft Evaluation Center** > Expand **Windows Server 2022** > Expand **Get started for free** > Check **Download the ISO** and click **Continue**.

[Windows Server 2022 ISO download](https://www.microsoft.com/en-us/evalcenter/evaluate-windows-server-2022)

Notice the different options that also let you easily try Windows Server 2022 in Azure.

![Windows Server 2022 dowload](/img/ws2022-1.png "Windows server 2022 evaluation center")

* Next you have to fill the form to access the Download link. Note that there is no email verification so you can get creative there. After that, just select the language and download Windows server 2022 ISO.

![Windows server 2022 iso download](/img/ws2022-2.png "Windows server language download")

* Once downloaded, I uploaded the Windows Server 2022 ISO to my local content library You can also store it on a datastore or simply connect it in the virtual console.

## Install Windows Server 2022 in VMware

Now the installation procedure will vary according to your environment and your needs. You can decide to create a Windows server 2022 VMware template to quickly deploy VMs from it, install it on a bare metal server by making a bootable USB stick, you name it. In our case, we install Windows server 2022 in VMware vSphere 7.

### Create Windows Server 2022 VM