---
layout: post
published: true
title: How to silence VSAN health checks
---
The VSAN health checks are great in vCenter to quickly notice when something wrong is going on. However there may be some of the health checks that you don't want to come up as warning. As an example,  lots of vCenter implementations don't have access to internet by design and when it is the case the Health check "VSAN Build Recommendation Engine Health" will be in a warning state even though you don't care about it. 

![dr.evil-shh.JPG]({{site.baseurl}}/img/dr.evil-shh.JPG)

As of vCenter 6.5U1 it is currently not possible to silence a check from the web client, the only way to do it is [via the VsanHealthSetVsanClusterSilentChecks method in the API](https://code.vmware.com/apis/217/vsan#/doc/vim.cluster.VsanVcClusterHealthSystem.html#getVsanClusterSilentChecks). Note that the VSAN API was made available in **PowerCLI 6.5.1 and above** so if you are still running an older version you will have to upgrade by uninstalling PowerCLI and downloading the module, [more info here](http://www.vxav.fr/2018-03-03-Install-latest-PowerCLI-on-offline-systems/).

I used this use case as an opportunity to play a little bit with the API so I wrote a short 4 functions module. I will probably expand it as I get the need for new cmdlets.

- **Get-VsanHealthChecks** : Display VSAN health checks with their current health.
- **Get-VsanHealthGroups** : Display VSAN health groups with their current health.
- **Get-VsanHealthSilentCheck** : Display the silenced health checks.
- **Set-VsanHealthSilentCheck** : Silence or unsilence a health check.

## Silence a VSAN health Check

Download the module : [VSAN-HealthChecks.psm1](https://github.com/vxav/Scripting/blob/master/VSAN-HealthChecks.psm1)

- First you need to import the module and connect to vCenter.

`Import-Module VSAN-HealthChecks.psm1`

`Connect-VIServer -Server "srv-vcenter`

- Find the Id of the check you want to silence. Mine is in Yellow state so I filter using it.

![VSAN-Health-yellow.jpg]({{site.baseurl}}/img/VSAN-Health-yellow.jpg)

`Get-VsanHealthChecks -Cluster (get-cluster) -Health Yellow | ft`

![Get-VsanHealthChecks-1.jpg]({{site.baseurl}}/img/Get-VsanHealthChecks-1.jpg)

- Pick the one you want to silence and use the **TestId** property to silence it. The output should be the updated list of silenced checks including the one specified above (Same output as Get-VsanHealthSilentCheck).

`Set-VsanHealthSilentChecks -Cluster (get-cluster) -HealthCheckId vumconfig -CheckState Silence`

![Set-VsanHealthSilentChecks.jpg]({{site.baseurl}}/img/Set-VsanHealthSilentChecks.jpg)

- You can run the command to display Health checks with the **DontFetchFromCache** switch enabled to re-run the test. The health check should now be in state **Skipped**.

`Get-VsanHealthChecks -Cluster (Get-Cluster) -DontFetchFromCache | ft`

![Get-VsanHealthChecks-2.jpg]({{site.baseurl}}/img/Get-VsanHealthChecks-2.jpg)

![VSAN-Health-skipped.jpg]({{site.baseurl}}/img/VSAN-Health-skipped.jpg)

- If you want to have an overview of the VSAN health per groups.

`Get-VsanHealthGroups -Cluster (get-cluster) | ft`

![Get-VsanHealthGroups.jpg]({{site.baseurl}}/img/Get-VsanHealthGroups.jpg)

## List of VSAN health checks

**TestId**|**TestName**|**GroupName**
-----|-----|-----
vsancloudhealthceipexception|Customer experience improvement program (CEIP)|Cloud Health
vsancloudhealthconnectionexception|Online health connectivity|Cloud Health
upgradesoftware|Software version compatibility|Cluster
diskbalance|vSAN Disk Balance|Cluster
healtheaminstall|ESXi vSAN Health service installation|Cluster
resynclimit|Resync operations throttling|Cluster
vcauthoritative|vCenter state is authoritative|Cluster
physdiskdedupusage|Deduplication and compression usage health|Cluster
timedrift|Time is synchronized across hosts and VC|Cluster
healthversion|vSAN Health Service up-to-date|Cluster
consistentconfig|vSAN cluster configuration consistency|Cluster
mmdecominsync|Host Maintenance Mode|Cluster
clustermembership|vSphere cluster members match vSAN cluster members|Cluster
clomdliveness|vSAN CLOMD liveness|Cluster
physdiskdedupconfig|Deduplication and compression configuration consistency|Cluster
upgradelowerhosts|Disk format version|Cluster
advcfgsync|Advanced vSAN configuration in sync|Cluster
objecthealth|vSAN object health|Data
vmhealth|vSAN VM health|Data
kmsconnection|vCenter and all hosts are connected to Key Management Servers|Encryption
hostcpuaesni|CPU AES-NI is enabled on hosts|Encryption
controllerdriver|Controller driver is VMware certified|Hardware compatibility
controllerfirmware|Controller firmware is VMware certified|Hardware compatibility
hcldbuptodate|vSAN HCL DB up-to-date|Hardware compatibility
controllerreleasesupport|Controller is VMware certified for ESXi release|Hardware compatibility
controlleronhcl|SCSI controller is VMware certified|Hardware compatibility
autohclupdate|vSAN HCL DB Auto Update|Hardware compatibility
hclhostbadstate|Host issues retrieving hardware info|Hardware compatibility
controllerdiskmode|Controller disk group mode is VMware certified|Hardware compatibility
limit1hf|After 1 additional host failure|Limits
limit0hf|Current cluster situation|Limits
nodecomponentlimit|Host component limit|Limits
hostdisconnected|Hosts disconnected from VC|Network
largeping|vSAN: MTU check (ping with large packet size)|Network
multicastsuspected|Multicast assessment based on other checks|Network
smallping|vSAN: Basic (unicast) connectivity check|Network
vmotionpinglarge|vMotion: MTU check (ping with large packet size)|Network
matchingsubnet|All hosts have matching subnets|Network
clusterpartition|vSAN cluster partition|Network
multicastdeepdive|Active multicast connectivity check|Network
hostconnectivity|Hosts with connectivity issues|Network
vsanvmknic|All hosts have a vSAN vmknic configured|Network
hostlatencycheck|Network latency check|Network
vmotionpingsmall|vMotion: Basic (unicast) connectivity check|Network
multicastsettings|All hosts have matching multicast settings|Network
masterexist|Stats master election|Performance service
statsdb|Stats DB object|Performance service
perfsvcstatus|Performance service status|Performance service
verbosemode|Verbose mode|Performance service
renameddirs|Stats DB object conflicts|Performance service
hostsmissing|All hosts contributing stats|Performance service
collection|Performance data collection|Performance service
physdiskhostissues|Physical disk health retrieval issues|Physical disk
physdiskcomplimithealth|Component limit health|Physical disk
physdiskoverall|Overall disks health|Physical disk
lsomslab|Memory pools (slabs)|Physical disk
physdiskcongestion|Congestion|Physical disk
physdiskcapacity|Disk capacity|Physical disk
componentmetadata|Component metadata health|Physical disk
physdisksoftware|Software state health|Physical disk
lsomheap|Memory pools (heaps)|Physical disk
physdiskmetadata|Metadata health|Physical disk
clusterwithouttwodatafaultdomains|Unexpected number of fault domains|Stretched cluster
witnessinsidevccluster|Witness host within vCenter cluster|Stretched cluster
clusterwithmultipleunicastagents|Unicast agent configuration inconsistent|Stretched cluster
hostunicastagentunset|Unicast agent not configured|Stretched cluster
siteconnectivity|Site latency health|Stretched cluster
witnessfaultdomaininvalid|Witness host fault domain misconfigured|Stretched cluster
witnesspreferredfaultdomainnotexist|Preferred fault domain unset|Stretched cluster
witnesspreferredfaultdomaininvalid|Invalid preferred fault domain on witness host|Stretched cluster
witnesswithnodiskmapping|No disk claimed on witness host|Stretched cluster
clusterwithoutonewitnesshost|Witness host not found|Stretched cluster
hostwithinvalidunicastagent|Invalid unicast agent|Stretched cluster
hostwithnostretchedclustersupport|Unsupported host version|Stretched cluster
vumconfig|vSAN Build Recommendation Engine Health|vSAN Build Recommendation
vumrecommendation|vSAN build recommendation|vSAN Build Recommendation
iscsiservicerunningtest|Service runtime status|vSAN iSCSI target service
iscsihomeobjectstatustest|Home object|vSAN iSCSI target service
iscsiservicenetworktest|Network configuration|vSAN iSCSI target service
