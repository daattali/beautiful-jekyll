---
layout: post
title: ANSI color handling characters with Tanzu CLI on Windows
DATE: 
subtitle: ''
metadescription: Get your Tanzu CLI to display colors instead of ANSI characters in
  Windows.

---
If you installed the Tanzu CLI (to try VMware Tanzu Community Edition or TCE for instance), you probably encountered odd characters such as ←\[1m or ←\[0m in your powershell or cmd sessions when using it. I thought I'd write a quick blog on that since I'm pretty sure I'll need it in a few months time and I'll have forgotten about it by then.

![](/img/2021-10-14_10h10_11.png)

These are ANSI coloring characters. Windows 10 supports ANSI terminal control through a function called SetConsoleMode but has the associated flag disabled by default. Disclaimer: I'm not a Windows deep dive expert, I got this from [superuser](https://superuser.com/questions/413073/windows-console-with-ansi-colors-handling).

#### Fix: Change default with a registry key

The fix is as easy as adding a registry key to set the default behaviour of the SetConsoleMode function. 

    [HKEY_CURRENT_USER\Console]
    "VirtualTerminalLevel"=dword:00000001

Open Registry editor and create the key if it doesn't already exist.

![](/img/2021-10-14_10h14_42.png)

You don't to restart your machine, just launch as new powershell window for instance and you should now get colors instead of ANSI coloring characters.

> ![](/img/2021-10-14_10h14_23.png)