---
layout: post
published: false
title: Pagefile and overcommitted lab
---
I recently ran into a very annoying issue in my virtual lab where vCenter would timeout all the time, the hosts were in a "not responding" state although all the pings were fine everywhere.

I tried a few different things when I thought, hang on, my lab is the most overcommited in the known universe so maybe my vCenter's (which runs in a nested ESXi) is in the pagefile. (Picture the task manager memory performance tab with 16GB installed in the computer and 27GB committed oh yes).

By default the pagefile file isn't flushed across reboots so I looked online how to do that and I ended up in a Microsoft forum that sent me [there](https://support.microsoft.com/en-us/help/314834/how-to-clear-the-windows-paging-file-at-shutdown).

> 1. Start Registry Editor (Regedt32.exe).
> 2. Change the data value of the **ClearPageFileAtShutdown** value in the following registry key to a value of 1:  
>        **HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management**  
>  If the value does not exist, add the following value:  
>        Value Name: ClearPageFileAtShutdown  
>        Value Type: REG_DWORD  
>        Value: 1  

>This change does not take effect until you restart the computer.