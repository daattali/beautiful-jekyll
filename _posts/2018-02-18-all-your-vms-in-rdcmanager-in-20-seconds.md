---
layout: post
published: true
title: All your VMs in RDCManager in 20 seconds
---
```
[ EDIT 2021/08/18 ]

RDCMan suffered security flaws up until version 2.7 and Microsoft recommended against using it. RDC Manager 2.8 has been released in July 2021 and is now safe to use. Note that it is now part of the Sysinternals suite. Do not use version older than 2.8. (Links updated)

[ Updates 2019/03/17 & 2019/11/07 ]
    - Bug fix - The RDG file must be opened at least once before running the set command to update it
    - [Set-RDCManFile] Adds new VMs and new domains to an existing file.
    - Added Function Set-RDCManFile.

[ Update 2018/08/17 ]

- Added 3389 TCP port check on VM IP(s) - Set the first one the responds as hostname and "NO-RDP-RESPONSE" if none does.

- Added TCPCheckTimeout parameter to Add-RDCManVM function to configure the time it takes for the TCP port check to time out.
```

----

I recently started a new job and just like in my previous one I wanted to have all servers consolidated in one place so I can easily RDP on them if needed. I use the free Microsoft tool **Remote Desktop Connection Manager (RDCMan)**. There are better software out there like RoyalTS in which you can configure SSH, Http, Ftp, vnc etc but for now RDCMan is good enough and there are plenty of people using it so hopefully this post can help them. There is "quite a few" servers in the environment so adding them to the console one by one manually is a major no-no given my allergy to repetitive tasks. 

The script below will create an RDG file you can use in RDCMan that will contain all the Windows VMs of the vCenter your are connected to. The VMs that are powered off or don't have VMware tools running won't be processed as PowerCLI won't be able to fetch the host name and IP (non Windows VMs are excluded for obvious reasons).

Download RDC Man here : [**Remote Desktop Connection Manager**](https://docs.microsoft.com/en-us/sysinternals/downloads/rdcman)

Download the module here: [**RDCMan.psm1**](https://github.com/vxav/Scripting/blob/master/Rdcman.psm1)

To create a file covering all your VMs:

```Powershell
Connect-VIServer -Server MyVcenter -credential (get-credentials)

Import-Module RDCMan.psm1

New-RDCManFile -RdgFilePath ".\MyRDGFile.rdg" -VM (Get-VM)
```

Wait for it to finish and double click on the rdg file to open it in RDCMan. You can then configure your credentials for each domain of your environment and add any physical servers you may want to add.

The generated file will have the following structure:

- File name (root) is the name of the vCenter.
- One server group per DNS domain (to allow for the storing of credentials).
- Server name : VM's first IPv4 (Not everyone has a rock solide cross domain DNS server!)
- Server display name : host name of the VM's host name.
- Server comments : VM name, IPs, cluster, OS, Notes, custom fields.

Like so:

![RDCMan-pic01.JPG]({{site.baseurl}}/img/RDCMan-pic01.JPG)

![RDCMan-pic2.JPG]({{site.baseurl}}/img/RDCMan-pic2.JPG)

Sometimes you forget to edit RDCMan when added a new VM or changed an IP and it quickly becomes obsolete. With this script you just run it again 2 months down the road and you'll have a file that is freshly up to date again. 

I personally created one file per vCenter and I open them all in RDCMan. It gives me a nicely organized structure.


**Note2**: If you get an error about an unsupported special character when opening the file please tell me via the contact form so I can update it. a covered a few of them but I'm sure there'll be others.
