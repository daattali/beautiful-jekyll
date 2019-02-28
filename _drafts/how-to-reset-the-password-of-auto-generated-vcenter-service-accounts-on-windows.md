---
layout: post
title: How to reset the password of auto-generated vCenter service accounts on Windows
DATE: ''
date: 2019-02-28 09:04:43 +0100

---
I stumbled upon this [VMTN post](https://communities.vmware.com/thread/550780) while troubleshooting an issue on a vCenter. Even though it didn't solve my problem, I found it interesting and learned something. So I though I would share it here with a bit of background info.

The Windows based vCenter installation creates one service account per service which purpose is to _place services into their own silo_. You can find more info about them in [KB2124709](https://kb.vmware.com/s/article/2124709). These are [**virtual accounts**](https://social.technet.microsoft.com/wiki/contents/articles/391.managed-service-accounts-msas-versus-virtual-accounts-in-windows-server-2008-r2.aspx). 

> Starting from vCenter Server 6.0 for Windows, virtual accounts replace the Local Service Account used in vCenter Server 5.x to run the vCenter Server services. This article contains information on the impact it will have on your environment.

In some cases where aggressive GPO are in place, it can happen that the password of local accounts expire, making them unable to be used, causing vCenter services to fail to start. 99% of the time you don't have to fiddle with these accounts as they are managed by vCenter... and you shouldn't. But desperate times call for desperate measures. 

Such measure is to renew the password of these auto-generated accounts (I know how that sounds...). Once it's done, we need to tell the application (vCenter) the new password and we use **vmon** to do so. The **vmware-vmon** service is a centralized platform-independent service that manages the lifecycle of Platform Services Controller and vCenter Server, it exposes APIs and CLIs to third-party applications.

**Notes of caution**: 

* This procedure is not supported by VMware (as far as I could tell) and is to be performed if the vCenter is experiencing problems. 
* Take a snapshot of your vCenter prior to this or take at least a backup if it is a physical box. There is no guarantee the this will fix your problem, you are doing it at your own expense.

**Procedure**

1. Open an elevated command prompt
2. **Stop the vCenter services** _"C:\\Program Files\\VMware\\vCenter Server\\bin\\service-control" --stop --all_
3. Open the **Computer Management** console and go to **Local Users and Groups** > **Users**.
4. **Reset the password** of each account that has **SVCUSER** in the description. Write the passwords in a notepad if they are different.
5. Browse to _"C:\\Program Files\\VMware\\vCenter Server\\vmon\\"_.
6. Run _".\\vmon.exe –p <service account name>"_ and type the associated password when prompted. Repeat for all service accounts
7. **Start the vCenter services** _"C:\\Program Files\\VMware\\vCenter Server\\bin\\service-control" --start--all_