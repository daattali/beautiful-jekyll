---
layout: post
published: false
title: Missing host storage data in hardware tab from LSI SMI-S CIM provider
---
If you monitor your hosts using CIM you may encounter an issue where no data is gathered and the storage view of the hardware tab is blank in the ESXi web client. In such case you see the following warning message:

> The Small Footprint CIM Broker Daemon (SFCBD) is running, but no data has been reported. You may need to install a CIM provider for your storage adapter.

![wbem1.jpg]({{site.baseurl}}/img/wbem1.jpg)

After seeing this message I opened an SSH session on the host that had the issue and a similar one that was working as expected. I then ran the following command to display list of providers:

```powershell
esxcli system wbem provider list
```

![wbem2.jpg]({{site.baseurl}}/img/wbem2.jpg)

As you can see the lsiprovider is not in the list of the host on the left. Meaning it is not presenting information from the storage controller to the wbem API.

If we look at the vibs installed on these hosts now, we see below that the lsiprovider vib is missing.

```powershell
esxcli software vib list | grep lsi
```

So what we need to do now is to download the CIM provider vib and install it on the host. My host is equipped with LSI cards so your mileage may vary here. However if you are using it, follow these instructions:

1. Navigate to the [Avago (LSI) Documents & Downloads site](https://www.broadcom.com/support/download-search).
2. Select _RAID controllers_ for Product Family and _Management Software and Tools_ for Asset Type and click _Search_.
3. Expand the view and find the version that works for you, then click on its name to download it.
4. 

