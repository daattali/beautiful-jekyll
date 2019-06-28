---
layout: post
title: Get Lun information in PowerCLI
DATE: 

---
I recently needed to check the path selection policy on a large number of Luns on a large number of hosts. The idea of doing it in the web client was worse than the 35 degrees outside so I decided to script it.

I started with the Get-ScsiLun cmdlet but it was slow as hell to run so I dug into extensiondata of the host object and came up with the script below. It runs a lot faster, you just specify one or several VMHost object(s) as parameter. It also supports the pipeline.

    PS> Get-VMHost | Get-LunInformation

![](/img/Get-LunInformation-1.jpg)

    Function Get-LunInformation {
    
    param(
        [Parameter(Mandatory=$true,Position=0,ValueFromPipeline=$True,ValueFromPipelineByPropertyname=$True)]
        [VMware.VimAutomation.ViCore.Types.V1.Inventory.VMHost[]]
        $VMHost
    )
    
    Process{
    
    foreach ($VH in $VMHost) {
    
        foreach ($LUNMP in $VH.ExtensionData.config.StorageDevice.MultipathInfo.lun) {
    
            $LUN = $VH.ExtensionData.config.StorageDevice.ScsiLun | where uuid -eq $LUNMP.Id
    
            $PathNotActive = $LUNMP.path | where state -ne "Active" | Measure-Object | select -ExpandProperty count
    
            $LUNID = $LUNMP.Path.name | ForEach-Object {$_.split("L") | select -last 1} | select -Unique
    
            [pscustomobject]@{
                Host = $VH.name
                NAA = $LUN.canonicalname
                OperationalState = $LUN.OperationalState
                CapacityGB = [math]::round($LUN.capacity.BlockSize * $LUN.capacity.Block / 1GB,1)
                MultipathingPolicy = $LUNMP.Policy.policy
                SATP = $LUNMP.StorageArrayTypePolicy.Policy
                Description = "$($LUN.Vendor) $($Lun.Model)"
                NonActivePaths = $PathNotActive
                Type = $LUN.DeviceType
                Local = $LUN.LocalDisk
                LunID = [int]$LUNID
            }
    
        }
    
    } # Foreach VMHost
    
    } # Process
    
    }