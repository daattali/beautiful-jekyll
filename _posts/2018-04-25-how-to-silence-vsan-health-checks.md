---
layout: post
published: false
title: How to silence VSAN health checks
---
The VSAN health checks are great in vCenter to quickly notice when something wrong is going on. However there may be some of the health checks that you don't want to come up as warning. As an example,  lots of vCenter implementations don't have access to internet by design and when it is the case the Health check "VSAN Build Recommendation Engine Health" will be in a warning state even though you don't care about it. 

As of vCenter 6.5U1 it is currently not possible to silence a check from the web client, the only way to do it is [via the VsanHealthSetVsanClusterSilentChecks method in the API](https://code.vmware.com/apis/217/vsan#/doc/vim.cluster.VsanVcClusterHealthSystem.html#getVsanClusterSilentChecks). Note that the VSAN API was made available in **PowerCLI 6.5.1 and above** so if you are still running an older version you will have to upgrade by uninstalling PowerCLI and downloading the module, [more info here](http://www.vxav.fr/2018-03-03-Install-latest-PowerCLI-on-offline-systems/).

![VSAN-Health-yellow.jpg]({{site.baseurl}}/img/VSAN-Health-yellow.jpg)

I used this use case as an opportunity to play with the API so I wrote a short 4 functions module. I will probably expand it over time.

- **Get-VsanHealthChecks** : Display VSAN health checks with their current health.
- **Get-VsanHealthGroups** : Display VSAN health groups with their current health.
- **Get-VsanHealthSilentCheck** : Display the silenced health checks.
- **Set-VsanHealthSilentCheck** : Silence or unsilence a health check.

## Silence a VSAN health Check

Download the module : [VSAN-HealthChecks.psm1](https://github.com/vxav/Scripting/blob/master/VSAN-HealthChecks.psm1)

- First you need to import the module.

```
Import-Module VSAN-HealthChecks.psm1
```

- Find the Id of the check you want to silence. Mine is in Yellow state so I filter using it.

```
PS> Get-VsanHealthChecks -Cluster (get-cluster) -Health Yellow | ft

TestHealth TestId             TestName                                TestShortDescription
---------- ------             --------                                --------------------
yellow     controllerfirmware Controller firmware is VMware certified Checks if the controller firmware...
yellow     **vumconfig**          vSAN Build Recommendation Engine Health Checks that the build recommendat...
```

- Pick the one you want to silence and use the **TestId** property to silence it. The output should be the updated list of silenced checks including the one specified above (Same output as Get-VsanHealthSilentCheck).

```
PS> Set-VsanHealthSilentChecks -Cluster (get-cluster) -HealthCheckId vumconfig -CheckState Silence
True

TestId                       TestName                                       GroupId     GroupName
------                       --------                                       -------     ---------
vumconfig                    vSAN Build Recommendation Engine Health        vum         vSAN Build Recommendation
vsancloudhealthceipexception Customer experience improvement program (CEIP) cloudhealth Cloud Health
autohclupdate                vSAN HCL DB Auto Update                        hcl         Hardware compatibility

```

![VSAN-Health-skipped.jpg]({{site.baseurl}}/img/VSAN-Health-skipped.jpg)

- You can run the command to display Health checks with the **DontFetchFromCache** switch enabled to re-run the test. The health check should now be in state **Skipped**. (I removed the description to avoid killing the formatting).

```
PS> Get-VsanHealthChecks -Cluster (Get-Cluster) | select TestHealth,TestId,TestName | ft

TestHealth TestId                       TestName
---------- ------                       --------
green      hcldbuptodate                vSAN HCL DB up-to-date
skipped    autohclupdate                vSAN HCL DB Auto Update
green      controlleronhcl              SCSI controller is VMware certified
green      controllerreleasesupport     Controller is VMware certified for ESXi release
yellow     controllerdriver             Controller driver is VMware certified
yellow     controllerfirmware           Controller firmware is VMware certified
green      controllerdiskmode           Controller disk group mode is VMware certified
yellow     hclhostbadstate              Host issues retrieving hardware info
green      hostdisconnected             Hosts disconnected from VC
green      hostconnectivity             Hosts with connectivity issues
green      clusterpartition             vSAN cluster partition
green      vsanvmknic                   All hosts have a vSAN vmknic configured
green      matchingsubnet               All hosts have matching subnets
green      smallping                    vSAN: Basic (unicast) connectivity check
green      largeping                    vSAN: MTU check (ping with large packet size)
green      vmotionpingsmall             vMotion: Basic (unicast) connectivity check
green      vmotionpinglarge             vMotion: MTU check (ping with large packet size)
green      hostlatencycheck             Network latency check
green      physdiskoverall              Overall disks health
green      physdiskmetadata             Metadata health
green      physdiskcapacity             Disk capacity
green      physdisksoftware             Software state health
green      physdiskcongestion           Congestion
green      physdiskcomplimithealth      Component limit health
green      componentmetadata            Component metadata health
green      lsomheap                     Memory pools (heaps)
green      lsomslab                     Memory pools (slabs)
green      objecthealth                 vSAN object health
green      healtheaminstall             ESXi vSAN Health service installation
green      healthversion                vSAN Health Service up-to-date
green      advcfgsync                   Advanced vSAN configuration in sync
green      clomdliveness                vSAN CLOMD liveness
green      diskbalance                  vSAN Disk Balance
green      resynclimit                  Resync operations throttling
green      vcauthoritative              vCenter state is authoritative
green      consistentconfig             vSAN cluster configuration consistency
green      timedrift                    Time is synchronized across hosts and VC
green      clustermembership            vSphere cluster members match vSAN cluster members
green      upgradesoftware              Software version compatibility
green      upgradelowerhosts            Disk format version
green      limit0hf                     Current cluster situation
green      limit1hf                     After 1 additional host failure
green      nodecomponentlimit           Host component limit
green      statsdb                      Stats DB object
green      masterexist                  Stats master election
green      collection                   Performance data collection
green      hostsmissing                 All hosts contributing stats
green      renameddirs                  Stats DB object conflicts
**skipped    vumconfig                    vSAN Build Recommendation Engine Health**
green      vumrecommendation            vSAN build recommendation
skipped    vsancloudhealthceipexception Customer experience improvement program (CEIP)
```

- If you want to have an overview of the VSAN health per groups.

```
PS> Get-VsanHealthGroups -Cluster (get-cluster) | ft

GroupId       GroupName                 GroupHealth ChecksGreen ChecksYellow ChecksRed
-------       ---------                 ----------- ----------- ------------ ---------
hcl           Hardware compatibility    yellow                4            2         0
network       Network                   green                10            0         0
physicaldisks Physical disk             green                 9            0         0
data          Data                      green                 1            0         0
cluster       Cluster                   green                12            0         0
limits        Limits                    green                 3            0         0
perfsvc       Performance service       green                 5            0         0
vum           vSAN Build Recommendation green                 1            0         0
cloudhealth   Online health             skipped               0            0         0
```


