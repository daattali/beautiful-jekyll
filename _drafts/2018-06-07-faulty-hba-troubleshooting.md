---
layout: post
published: false
title: Faulty HBA troubleshooting
---
After moving an ESXi host to another rack, I encountered a really strange behaviour. The hosts are connected to an EMC FC SAN. 

When we powered the host back on, some datastores were missing but not all of them. When I did a rescan they would appear and then some disappeared, then reappeared and went away again, really odd. I looked at the LUNs attached to the host and they were all here on both HBAs. At first we suspected a faulty connection like an FC connector not secured or a broken fiber but after reviewing it everything was fine.

After looking into the **vmkernel.log** of the host I found a lot of these events:

_2018-06-07T08:02:43.154Z cpu44:32881)WARNING: NMP: nmpDeviceRequestFastDeviceProbe:237: NMP device "naa.60000970000298700131533030363941" state in doubt; requested fast path state update...
2018-06-07T08:02:43.154Z cpu44:32881)ScsiDeviceIO: 2369: Cmd(0x412e80405cc0) 0x28, CmdSN 0xbf from world 34443 to dev "naa.60000970000XXXXXXXXXXXXXX0363941" failed **H:0x7 D:0x0 P:0x0** Possible sense data: 0x0 0x0 0x0.
2018-06-07T08:02:43.404Z cpu44:32881)ScsiDeviceIO: 2369: Cmd(0x412e8043ca40) 0x28, CmdSN 0xc1 from world 34443 to dev "naa.60000970000298700131533030363941" failed **H:0x7 D:0x0 P:0x0** Possible sense data: 0x0 0x0 0x0.
2018-06-07T08:02:43.418Z cpu44:32881)NMP: nmpThrottleLogForDevice:2458: Cmd 0x28 (0x412e845e0400, 34443) to dev "naa.60000970000298700131533030363941" on path "vmhba4:C0:T2:L13" Failed: **H:0x7 D:0x0 P:0x0** Possible sense data: 0x0 0x0 0x0. Act:EVAL
2018-06-07T08:02:43.418Z cpu44:32881)ScsiDeviceIO: 2369: Cmd(0x412e845e0400) 0x28, CmdSN 0xc3 from world 34443 to dev "naa.60000970000298700131533030363941" failed **H:0x7 D:0x0 P:0x0** Possible sense data: 0x0 0x0 0x0.
2018-06-07T08:02:43.494Z cpu44:32881)NMP: nmpThrottleLogForDevice:2458: Cmd 0x28 (0x412e842d9840, 34443) to dev "naa.60000970000298700131533030353641" on path "vmhba4:C0:T2:L4" Failed: **H:0x7 D:0x0 P:0x0** Possible sense data: 0x0 0x0 0x0. Act:EVAL
2018-06-07T08:02:43.494Z cpu44:32881)WARNING: NMP: nmpDeviceRequestFastDeviceProbe:237: NMP device "naa.60000970000298700131533030353641" state in doubt; requested fast path state update...
2018-06-07T08:02:43.886Z cpu44:32881)lpfc: lpfc_scsi_cmd_iocb_cmpl:2057: 0:(0):3271: FCP cmd x28 failed <4/99> sid xe20a00, did x7002ef, oxid xffff Local Reason x1d Returning Host Error_

As you can see there are a lot of these **H:0x7 D:0x0 P:0x0** scsi sense codes which I never envountered in the past.

Now if you are not familiar with SCSI sense code, it is a collection of codes used by SCSI targets and initiators to communicate. These codes follow an industry standard maintained by the [T10](http://www.t10.org/lists/1spc-lst.htm) Committee. You can learn more about it in [KB289902](https://kb.vmware.com/s/article/289902).

To find out what it means I used the very good tool on [virten.net](https://www.virten.net/vmware/esxi-scsi-sense-code-decoder/?host=7&device=&plugin=&sensekey=&asc=&ascq=&opcode=) that tells you what a sense code means.

![sense-code-hx7.jpg]({{site.baseurl}}/img/sense-code-hx7.jpg)

> This status is returned when a device has been reset due to a Storage Initiator Error. This typically occurs due to an outdated HBA firmware or possibly (though rarely) as the result of a bad HBA.

Hmm, strange, I could see all the LUNs on both HBAs.

The 2 HBAs are called vmhba3 and vmhba4 in ESXi. I searched through the vmkernel.log for vmhba3 then vmhba4. I noticed that the error mentionned above only appeared on vmhba4.

