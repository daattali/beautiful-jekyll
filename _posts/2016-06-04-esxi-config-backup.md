---
layout: post
title: Config backup of your ESXi hosts with powerCLI
published: true
subtitle: Backup script with files rotation
meta description: >-
  Backup the configuration of all your ESXi hosts using PowerCLI with files
  rotation on destination storage.
---
For my first article I wanted to start with something basic that every company should do on a regular basis, I am talking about the configuration of the ESXi hosts. It can seem like a no brainer but it is not implemented everywhere. Having a backup of your host's configurations will let you restore it in minutes instead of reconfiguring everything from scratch manually.  
Although you probably won't need it if you leverage the host profile feature as vCenter will serve the configuration in this case.

There are multiple very good tools that can do the same thing but I am kind of a purist and I don't really like multiplying the softwares in the datacenter when I can avoid it. And lucky me PowerCLI is here!

In my case I wanted to automate the backup of my hosts so I wrote a quick script that will do the job for me through a scheduled task. I have set it to run once a month as we don't change the configuration so often.  
I am going to go through the script bit by bit but you can find the .ps1 file here:

[Backup-ESXiConfigs.ps1](https://github.com/vxav/Scripting/blob/master/Backup-ESXiConfigs.ps1).

## Backup process
At the backup location each host will have a folder with its name containing x backups of its configs named after the date when they were taken.  
The scheduled task can run the script either from a batch file that would allow you to redirect all the output to a log file (the solution I use) or include logging in the PS1 script and call it as a parameter to powershell.exe right into the task.
The script backs up all the hosts connected to the vCenter in a foreach loop. So if you want to reduce the scope of the backup you will need to add a filter in the script as I haven't made it a parameter.  


### Connect to the vCenter server that you specify in the parameters of the function.
The scheduled task must run under an account that has rw permissions on the target file share and global permissions in vCenter as well. It is best practice to make it a service account for obvious security reasons.

``` Powershell
Add-PSSnapin VMware.VimAutomation.Core -ErrorAction Stop  
Connect-VIServer -Server $Server  
```

### Rotate the previous backup files according to the rotation value set in the parameters.
From now on the commands specified are run within a ```Try/catch``` block to capture the error messages and in a loop hitting all the hosts.
In this block, the backup location is configured and the last backup file is removed from the folder.

``` Powershell
$ESXiBak = "$BackupLocation\$($_.name)"
IF (-not(Test-path $ESXiBak)) {MKDIR $ESXiBak}
WHILE (((Get-ChildItem $ESXiBak).count) -gt $FileRotation) {Get-ChildItem $ESXiBak | Sort-Object lastwritetime | select -First 1 | Remove-Item -Force -Confirm:$false}
```

### Backup the configuration of the current host to the destination and rename the file.
The backup is taken with Get-VMHostFirmware and the file is renamed with the current date and the name of the host "2016-06-04_MyESXiHost.tgz  

``` Powershell
Get-VMHostFirmware -VMHost $_.name -BackupConfiguration -DestinationPath $ESXiBak
Get-ChildItem $ESXiBak | Sort-Object lastwritetime | select -Last 1 | Rename-Item -NewName "$(get-date -Format yyyy-MM-dd)_$($_.name).tgz"
```

### Backup files
The backup files have a .tgz extension and contain a tree of files resulting in the etc/ folder containing your host's configuration.  
MyBackup.tgz/MyBackup.tar/state-tgz/state.tar/local.tgz/local.tar/etc/

## Restore process
To restore the config to a host after its basic configuration (management IP, password, ...) you just need to place your host into maintenance mode and run the following command after which a restart will be triggered:  

```PowerShell
Set-VMHostFirmware -VMHost (get-VMHost MyHost) -Restore -Force -SourcePath
```


And remember to always document your work where you and your colleagues can find it. It's always better to have a corporate document with procedures created for YOUR environment than googling around in panic mode.
