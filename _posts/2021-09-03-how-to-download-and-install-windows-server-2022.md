---
layout: post
title: How to download and install Windows Server 2022
DATE: 
subtitle: ''
metadescription: Find out about how to download and install Windows Server 2022 and
  create a Windows Server 2022 VMware template.

---
In a world where security is increasingly important along with the adoption of hybrid cloud options, Microsoft recently released Windows server 2022 which builds on these industry requirements to offer a mature and secure platform. In this blog, we will discuss how to download and install Windows Server 2022 in VMware. We will also touch base on how to create a Windows Server 2022 template.

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

* Once downloaded, I had issues with the content library and my remote access so I uploaded the Windows Server 2022 ISO to my datastore. You can also simply connect it in the virtual console for the sake of creating a template.

![Windows server 2022 iso in datastore](/img/ws2022-3.png "Upload the iso to datastore")

## Install Windows Server 2022 in VMware

Now the installation procedure will vary according to your environment and your needs. You can automate the process with various automation tools or install it on a bare metal server by making a bootable USB stick, you name it. In our case, we install Windows server 2022 in VMware vSphere 7 in a VM using the ISO to turn it into a template.

### 1) Create the virtual machine in vSphere

* **Create a new virtual machine** in the vSphere client.

![create windows server 2022 server VM](/img/ws2022-4.png "create new vm")

* I will be skipping a few panes here. I select my "TEMPLATES" **folder** as this is where this machine will live once it is converted to a windows server 2022 template.

![Virtual machine folder](/img/ws2022-5.png "vm folder")

* Select the correct **compatibility** for your VM and the latest **guest OS version**. Windows Server 2022 may not be available in the choices if you aren't running vSphere 7 Update 2, in which case you can use the next latest version such as Windows Server 2019.

![guest os type windows server 2022](/img/ws2022-6.png "os type")

* In the hardware section, we configure the **system hard disk** with 64GB which is a nice one-size-fits-all and set it to **Thin Provision**.

![](/img/ws2022-7.png)

* Still in the hardware pane, I set the network **adapter type to VMXNET 3** and connect the Windows Server 2022 **ISO file**. 

![](/img/ws2022-8.png)

* You can then finish the wizard, power on the VM and open the virtual console to install the OS from the windows server 2022 ISO.

### 2) Install Windows Server 2022

The way to install Windows Server 2022 is similar to previous releases but we will show it here for the sake of demonstrating the complete process.

* Like any Windows install, boot on the ISO and select your **languages**, click **Next** and click **Install** on the next pane.

![](/img/ws2022-9.png)

* Select the **edition** of the OS that fits your needs. In this case we selected Windows Server 2022 Standar Evaluation with Desktop Experience.

![](/img/ws2022-11.png)

* Click on **Custom: Install Microsoft**...

![](/img/ws2022-12.png)

* Click **New** to partition the 64GB disk and install Windows Server 2022 on it. Then Click **Next** and wait for the installation process to complete.

![](/img/ws2022-13.png)

* When the Windows server 2022 install finishes, type a **password** for the local admin account and move on.

![](/img/ws2022-14.png)

### 3) Prepare the Windows Server 2022 template

#### Install VMware Tools

the first thing to do after installing a virtual machine, especially when building a template, is to install the VMware Tools. 

* Mount the ISO on the virtual machine with **Actions or right click on the VM > Guest OS > Install VMware Tools**

![](/img/ws2022-15.png)

* Then run the installer in the virtual console and restart the virtual machine.

![](/img/ws2022-16.png)

* The vSphere Client should now display the VMware Tools running.

![windows server 2022 vmware tools](/img/ws2022-18.png)

Install Windows Update

Search and install the latest Windows Updates. Run the wizard again until there are no more updates available.

![](/img/ws2022-19.png)

#### Tweak Windows Server (optional)

You can tweak a few OS properties when building a template. These are not mandatory and they might very well be overriden downstream by AD domain GPOs but I like to set them straight away.

* **Enable ICMPv4 (ping)**

Go to the Windows Defender Firewall rules configuration in the inbound rules section > Sort by protocol and scroll to ICMPv4 > **Enable both ICMPv4 Echo Requests**.

![](/img/ws2022-20.png)

**Disable open server manager at startup**

The first thing I do on a new Windows Server is to disable the automatic opening of the server manager.Disable open server manager at startupDisable open server manager at startup

![](/img/ws2022-21.png)

* **Check the time zone**

In Server Manager, make sure that the time zone configured corresponds to where you are located.  
![](/img/ws2022-22.png)

* **Set performance options to best performance**

In Server manager, click on the server to open system properties > **Advanced** > **Performance** > **Settings** > Check **Adjust for best performance.**

![](/img/ws2022-23-1.png)

* **Install any software that must be in the template**

These will obviously depend on what you need in your environment. Here is a few suggestions you may want to have a look at:

* **BGInfo**: get quick information on the system on the wallpaper.
* **Various agents**: Save time by installing agents in the template such as Horizon agent, monitoring, backup, anti-virus...
* **7-zip**: The famous compression software, small enough to justify having it in the template if at all needed.
* **Notepad++**: You will be happy to have it when you need to review log files.

### 4) Create Windows Server 2022 template

Now that the install Windows Server 2022 in finished and the OS has been prepared, we can proceed with converting it to template. You don't need to sysprep if you plan on using customization specs to deploy new Windows Server 2022 virtual machines.

* **Shut down** the Windows Server virtual machine.
* **Convert the virtual machine to template**.

![](/img/ws2022-24.png)

* As a last step I suggest that you add some meta **notes** to the template. Especially if you work in a team with other admins. You can also use the content library which facilitates the versioning process.

![](/img/ws2022-25.png)

## Wrap up

There you have it on how to download and install Windows Server 2022 in VMware. No doubt your mileage will vary according to your environment but this should give you a good baseline. 

Once you have a solid base image, you can start creating customization specification to customize new Windows Server 2020 install at deployment. 