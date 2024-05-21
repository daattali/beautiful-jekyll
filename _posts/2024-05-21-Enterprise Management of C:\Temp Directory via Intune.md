---
layout: post
title:  "Enterprise Management of C: Temp Directory via Intune"
date:   2024-05-21
Author: Jonathan Proctor
categories: PowerShell, Intune, End User Computing
---

# Enterprise Management of C:\Temp Directory via Intune

This article provides a detailed explanation of a PowerShell script designed for enterprise management of the `C:\Temp` directory via Intune. The script performs the following tasks:

1. **Creates a new directory** named `Temp` in the `C:\` drive.
2. **Grants full control** to the 'Users' group for the `C:\Temp` directory.
3. **Sets up a scheduled task** that deletes the contents of the `C:\Temp` directory at startup.

## Script Details

### Creating a New Directory

The script begins by creating a new directory named `Temp` in the `C:\` drive using the `New-Item` cmdlet:

~~~
New-Item -Path "c:\" -Name "Temp" -ItemType "directory" -force
~~~
###  Granting Full Control to ‘Users’
Next, the script grants full control to the ‘Users’ group for the C:\Temp directory. It does this by getting the Access Control List (ACL) for the directory, creating a new access rule, adding the access rule to the ACL, and then applying the updated ACL to the directory:

~~~
$acl = Get-Acl "C:\Temp"
$permission = "Users","FullControl","Allow"
$accessRule = New-Object System.Security.AccessControl.FileSystemAccessRule $permission
$acl.SetAccessRule($accessRule)
$acl | Set-Acl "C:\Temp"
~~~
###  Setting Up a Scheduled Task
Finally, the script sets up a scheduled task that deletes the contents of the C:\Temp directory at startup. It does this by defining an action, a trigger, and a principal for the task, and then registering the task:

~~~
$Action = New-ScheduledTaskAction -Execute "PowerShell.exe" -Argument "Get-ChildItem -Path 'C:\Temp' -Recurse | Remove-Item -Force -Recurse"
$Trigger = New-ScheduledTaskTrigger -AtStartup
$Principal = New-ScheduledTaskPrincipal -UserId "NT AUTHORITY\SYSTEM" -LogonType ServiceAccount -RunLevel Highest
Register-ScheduledTask -TaskName "DeleteTempOnStartup" -Action $Action -Trigger $Trigger -Principal $Principal -Description "Deletes all files in C:\Temp at startup" -Force
~~~
### Conclusion
This PowerShell script provides a solution for managing the C:\Temp directory in an enterprise environment using Intune. It automates the process of creating the directory, setting permissions, and cleaning up the directory at startup. As always, it’s important to test the script in a controlled environment before deploying it widely.














