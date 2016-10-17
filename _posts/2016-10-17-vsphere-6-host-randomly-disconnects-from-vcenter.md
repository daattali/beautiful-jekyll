---
layout: post
published: true
title: vSphere 6 host randomly disconnects from vCenter
---
I got a few email alerts recently from my vCenter regarding host not responding and disconnect at a random time. At first I tried to find a pattern for what could be potentially causing the issue and quickly realized that nothing funny was happening in vSphere-land.

So I had a quick peek at the logs and found a few interesting records.

```
Hostd: info hostd[FFE61B70] [Originator@6876 sub=Vimsvc.ha-eventmgr] Event 6361 : /usr/lib/vmware/vpxa/bin/vpxa crashed (1 time(s) so far) and a core file might have been created at /var/core/vpxa-worker-zdump.000. This might have caused connections to the host to be dropped.
```

```
vobd:  [UserWorldCorrelator] 11239800115513us: [esx.problem.vpxa.core.dumped] /usr/lib/vmware/vpxa/bin/vpxa crashed (1 time(s) so far) and a core file may have been created at /var/core/vpxa-worker-zdump.000. This may have caused connections to the host to be dropped.
```

```
vobd:  [UserWorldCorrelator] 11239267815288us: [vob.uw.core.dumped] /usr/lib/vmware/vpxa/bin/vpxa(34895) /var/core/vpxa-worker-zdump.000
```

So I gave a shot at google with this and found the [KB2144799](https://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=2144799) from VMware and here what comes from it:

**Cause** 

>  This issue occurs when too many performance counters are being registered on the ESXi hosts vpxa process causing the process to run out of memory.

**Resolution**

>  This is a known issue affecting ESXi 5.5 and 6.0. 
>  This issue is resolved in ESXi 5.5 Patch 08 and ESXi 6.0 Patch 03.

Up to the patch released early August 2016, the default vpxa memory allocation was set to 173MB, which could fill up and crash vpxa. Vpxa being the vCenter agent in ESXi that causes vCenter to lose connection to the host.

The issue is corrected by the patch [ESXi-6.0.0-20160804001-standard](https://kb.vmware.com/selfservice/search.do?cmd=displayKC&docType=kc&docTypeID=DT_KB_1_1&externalId=2145667) for vSphere 6.0 and [ESXi550-201608401-BG](https://kb.vmware.com/selfservice/search.do?cmd=displayKC&docType=kc&docTypeID=DT_KB_1_1&externalId=2144361) for vSphere 5.5.

I'm not sure what exactly was fixed in this patch but the memory allocated vpxa has been increased to 256MB.

I hope there was some other kind of root cause fix on top of increasing the memory which would potentially just delay the crash of VPXA. We'll see in the comming few months, I will definitely keep an eye on that.

Before patching to 20160804001:

![vpxa-crash-before.jpg]({{site.baseurl}}/img/vpxa-crash-before.jpg)

After patching to 20160804001:

![vpxa-crash-after.jpg]({{site.baseurl}}/img/vpxa-crash-after.jpg)