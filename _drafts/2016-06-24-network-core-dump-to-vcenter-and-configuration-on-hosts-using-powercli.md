---
layout: post
published: false
title: Network core dump to vCenter and configuration on hosts using PowerCLI
---
In the event of a PSOD (Purple Screen Of Death) ESXi will try to save a core dump of the vmkernel and a screenshot of the console screen, which can be crucial for diagnosing the root cause of the failure.

There are two types of locations that can be configured as a target for the core dump files:  
-**Disk dump collection**: The host stores the files on a partition on disk dedicated to that.
-**Network dump collection**: The host sends the data to the Network Dump Collector service over the network, which will most likely be the vCenter. 

_I will only talk about the network way in this article as this is the one that I'm interested in._

##vCenter configuration

First of all the vCenter must be configured to accept the files through the Network Dump Collector Service.

**Netdump-setup.xml**

The configuration is done in an xml file located at the following path (edit according to your VMware installation folder):

```Powershell
C:\ProgramData\VMware\vCenterServer\data\netdump\netdump-setup.xml
```

The interesting tags to configure will allow you to tune a few settings of the network core dump service.

Directory where the logs of the service are stored, I use a log folder on a data disk.  
```Powershell
<defaultLogPath></defaultLogPath>
```

Directory where the actual core dump files are stored, I use a data folder on a data disk.
```Powershell
<defaultDataPath></defaultDataPath>
```

Amount of disk space in GB that can be used for it, I set 4 (which is too much) because I have plenty of space.  
```Powershell
<maxSize></maxSize>
```

You can configure the UDP port to use that you will need to adjust according to your network/server configuration. This setting, along with MaxSize can be configured in the webclient in Services>ESXi Dump Collector.

Now save the file and close it.

**NetDump service**

