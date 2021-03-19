---
layout: post
title: How to update to vSphere 7.0 Update 2
DATE: 
subtitle: ''
metadescription: The latest vSphere 7.0 Update 2 brings a wealth of new features spanning
  VSAN, vCenter and Tanzu.

---
VMware recently released vSphere 7.0 Update 2. It delivers a number of really interesting features and improvements in terms of performance and LifeCycle management. Among the main features we find :

· Nvidia backed AI & Developer Ready Infrastructure

· Enhanced security footprint

· Simplified operations with vLCM

· Performance improvements

· vSAN 7.0 Update 2

Refer to my blog for Altaro to find more detailed information about the release.

## Before upgrading

The usual prerequisites and recommendations still apply:

* Make sure your hardware and firmware are supported for vSphere 7.0 Update 2 in the VMware HCL. Even if it's not you can still upgrade vCenter though.
* Make sure any third party products connecting to the environment is compatible with vCenter 7.0 Update 2.

## WAIT: vSphere 7.0 Update 2 update

As of 19/03/2021, it is not possible to update to vSphere 7.0 Update 2 using either vLCM or esxcli. It has been pulled from the repo by VMware to address an issue discovered post release which would result in an error when trying to patch the host.

> Cannot download VIB: ''. This might be because of network issues or the specified VIB does NOT exist or does NOT have a proper 'read' privilege set. Please make sure the specified VIB exists and is accessible from vCenter Server.

You can find more information on this issue in [KB83107](https://kb.vmware.com/s/article/83107?lang=en_US).

In the meantime it is still possible to update vSphere by booting the server on the vSphere 7.0 Update 2 ISO and updating it in interactive mode.

![](/img/v7u2.jpg)

VMware is currently working on a patch and recommends to **NOT** upgrade to 7.0 U2 until this patch is available. This blog will be updated accordingly.

## How to update to vCenter 7.0 Update 2

While vSphere 7.0u2 is recovering from its hangover, vCenter 7.0 Update 2 is doing fine thank you very much. You can go ahead and patch vCenter.

Before starting the update process, it is highly recommended to make sure you can revert to the current version in case the update goes sideways. You can obviously take a backup of the VCSA in the VAMI or shut down the VM and take a snapshot.

* If vCenter does not have internet access you need to download the patch on the [VMware Patch Download Center](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwiL8ur1u7zvAhVL9IUKHRE4DckQFjAAegQIARAD&url=https%3A%2F%2Fmy.vmware.com%2Fgroup%2Fvmware%2Fpatch&usg=AOvVaw0rrH8ShNTJpCNFMMRton3o). Select **VC** with the latest version and click **Download**. On a side note, when you to update a product, make sure you get the "Patch-FP" iso.

![](/img/v7u2-1.png)

* First connect to the VAMI and browse to the Update 