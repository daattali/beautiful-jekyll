---
layout: post
title: ESXi not booting - CRC error on decompression
DATE: 
subtitle: ''
metadescription: The CRC error on decompression message is due to a bad USB key used
  a boot device.
image: ''

---
I recently encountered an issue in my homelab where the bare-metal ESXi server wouldn't start. All my labs run on one physical server (Dell R430) which has vSphere 7u2 installed on a USB key. A cheap one from the supermarket obviously (because I like it this way!).

Anyway, ESXi would get stuck during boot with the following error:

    CRC error during decompression. Received CRC (0x54a6b1ec)...
    gzip_extract failed for /basemisc.tgz (size 0): CRC error
    Error 28 (CRC error) while loading module: /basemisc.tgz
    Compressed MD5: ...
    Fatal error: 28 (CRC error)

![](/img/crcerror.png)

In case it wasn't clear, it's a CRC error. At this point I suspected something was up with the USB since it was plugged inside the chassis which runs pretty hot. A restart wouldn't fixed it of course, neither changing USB port.

So I tried to reinstall vSphere 7u2 on the USB and was greeted with another error during the installation. At this point I was pretty sure the USB was shot. 

![](/img/crcerror1.png)

I tried to reinstall vSphere 7u2 on another USB key (yes, a cheap one from the supermarket, so what?!) and everything went smoothly. All I had to do after that point was to register my VMs from the datastore, boot the vCenter, connect the host and Bob's your uncle.

Bottom line, cheap USBs aren't great for running enterprise grade hypervisors, which was the whole ordeal of 2021 by the way... A way to mitigate this is to reduce the number of IOs to the device by [moving the ESX-OSData to another device ](https://core.vmware.com/resource/esxi-system-storage-when-upgrading#1)or at least move the scratch partition to a datastore.

In the end, low endurance devices will no longer be supported by VMware so you shouldn't really use them anymore but most of us running labs at home don't really care that much about official support.