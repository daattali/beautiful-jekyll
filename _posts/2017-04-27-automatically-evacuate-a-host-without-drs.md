---
layout: post
published: true
title: Automatically evacuate a host without DRS
date: '2017-04-27'
---
Like many other places I believe, our non-prod hosts run on vSphere Standard instead of Enterprise Plus for its lower price. The price is great, but what isn't is that DRS isn't available. Which means every time a host needs to be put in maintenance mode you have to do it the old school way: _manually vmotion all the VMs running on it_.

My non-prod cluster has 9 hosts and 300 VMs. Although an option, the manual vMotion way is incredibly boring and time consuming.

In this post I am going to share a Powershell script that I quickly put together to automate the process of safely evacuating a host from the VMs running on it. 

This script will safely migrate the VMs of a host one by one to other hosts by taking into consideration:

- Projected maximum CPU usage after migration (default 75%).
- Projected maximum Memory usage after migration (default 75%).
- Projected maximum vCPU per physical cores after migration (default 9).
- Possibility to exclude hosts from the possible destinations.
- Possibility to exclude VMs from the migratees.
- Interactive mode with possibility to change the selected destination host (default) or skip a VM.
- Fully automated mode.
- Possibility to use whatif.

If the resources requirements can't be fulfilled, a warning is displayed and the VM is skipped.

The execution is pretty slow so I it's something that can be improved. I don't really mind as I fire it up and then I go do something else while it's doing my job. 

We could imagine adding a command to place the host in maintenance mode at the end of the script, but for now I don't mind a right click.

## Usage examples

####Evacuate a host automatically with the default values (see above).

All the live VMs on ESXi-1 will be migrated to other hosts as long as they don't go over 75% CPU/MEM usage and a 9:1 vCPU ratio.

```powershell
Evacuate-VMHost -VMHost (Get-vmhost ESXi-1) -fullyautomated
```

####Evacuate a host interactively with the defined values.

For every VM a choice will be given to the user including the projected capacity after the migration for every available host with a recommended one.

The user has 2 choices:

- Press enter and follow the script's recommendation (the host with a *)
- Select another destination host
- Skip the VM and leave it where it is

```powershell
Evacuate-VMHost -VMHost (Get-vmhost ESXi-1) -VMHostMaxCPUUsagePercent 80 -VMHostMaxMEMUsagePercent 85 -VMHostMaxVCpuPerCore 10
```

![evacuate-vmhost1.jpg]({{site.baseurl}}/img/evacuate-vmhost1.jpg)

## Parameters

- **VMHost**: Host to evacuate
- **VMHostMaxCPUUsagePercent**: CPU usage (%) limit that the destination hosts shouldn't reach
- **VMHostMaxMEMUsagePercent**: Memory usage (%) limit that the destination hosts shouldn't reach
- **VMHostMaxVCpuPerCore**: vCPU:core ration that the destination hosts shouldn't reach
- **ExcludedVMHost**: Hosts to exclude from the possible destinations
- **ExcludedVM**: Virtual machines that won't be migrated
- **fullyAutomated**: No choice given to the user, the VMs are migrated automatically one by one
- **Whatif**: Simulate the migration but doesn't do it

## Script code

Also available [on github](https://github.com/vxav/Scripting/blob/master/Evacuate-VMHost.ps1).

```powershell
Function Evacuate-VMHost {

param (
    [Parameter(Mandatory=$true,Position=0,ValueFromPipeline=$True,ValueFromPipelineByPropertyname=$True)]
    [VMware.VimAutomation.ViCore.Types.V1.Inventory.VMHost]
    $VMHost,

    [ValidateRange(1,100)]
    [int]
    $VMHostMaxCPUUsagePercent = 75,

    [ValidateRange(1,100)]
    [int]
    $VMHostMaxMEMUsagePercent = 75,

    [int]
    $VMHostMaxVCpuPerCore = 9,

    [VMware.VimAutomation.ViCore.Types.V1.Inventory.VMHost[]]
    $ExcludedVMHost,

    [VMware.VimAutomation.ViCore.types.V1.Inventory.VirtualMachine[]]
    $ExcludedVM,

    [switch]
    $fullyAutomated,

    [switch]
    $Whatif
)

Try {

    IF ($VMHost.connectionstate -eq "connected") {

    $VM = $VMHost | Get-VM | where {$_ -notin $ExcludedVM}

        $VM | where powerstate -eq poweredon | ForEach-Object {
        
            $CurVM = $_

            $PossibleHost = Get-VMHost `
                | Where name -ne $VMHost.name `
                | where {$_ -notin $ExcludedVMHost} `
                | where connectionstate -eq "connected" `
                | where {(Compare-Object $CurVM.ExtensionData.network.value $_.ExtensionData.network.value).sideindicator -notcontains "<="}

            $i = 0
            $choice = "a"

            $selectedVMHost = $PossibleHost | ForEach-Object {
            
                $i++

                $HostVM = $_ | get-vm | where powerstate -eq poweredon

                [pscustomobject]@{
                    id = $i
                    name = $_.name
                    "ProjectedCpuUsage" = [math]::round(($_.CpuUsageMhz + $CurVM.ExtensionData.Runtime.MaxCpuUsage) / $_.CpuTotalMhz * 100,1)
                    "ProjectedMemUsage" = [math]::round(($_.MemoryUsageMB + $CurVM.memoryMB) / $_.MemoryTotalMB * 100,1)
                    "ProjectedVCPUperCORE" =[math]::round(($HostVM | Measure-Object -Property numcpu -Sum).sum / $_.NumCpu,1)
                    "Projected#LiveVM" = $HostVM.count + 1
                }

            } | where {$_.ProjectedCpuUsage -lt $VMHostMaxCPUUsagePercent -and $_.ProjectedMemUsage -lt $VMHostMaxMEMUsagePercent -and $_.ProjectedVCPUperCORE -lt $VMHostMaxVCpuPerCore}

            IF ($selectedVMHost) {

                $BestVMHost = $selectedVMHost | where id -eq ($selectedVMHost | select id,@{l="sum";e={$_.ProjectedCpuUsage + $_.ProjectedMemUsage}} | Sort-Object sum | select -First 1).id

                ($selectedVMHost | where id -eq $BestVMHost.id).id = "*"

                IF (!$fullyAutomated) {

                    Clear-Host

                    $_ | select name,powerstate,numcpu,memorygb
                
                    $selectedVMHost | Sort-Object id | ft -au

                    Write-Host "Select host manually by its ID"
                    Write-Host "Press enter to follow the recommendation ( * )"
                    Write-Host "Enter N to skip this VM"

                    While ($choice -notin @("","n") -and $choice -notin (1..$i)) { $choice = Read-Host " " }

                    IF (!$Choice) {$selectedVMHost = $BestVMHost}
                        ELSEIF ($choice -eq "n") {Write-Warning "$($CurVM.name) skipped"}
                            ELSE {$selectedVMHost = $selectedVMHost | where id -eq $Choice}

                } ELSE {
                    $selectedVMHost = $BestVMHost
                }

                IF ($choice -ne "n") {

                    Write-Host "$($CurVM.name) moving to $($selectedVMHost.name)" -ForegroundColor green

                    $params = @{VM = $_ ; Destination = get-vmhost $selectedVMHost.name}

                    IF ($Whatif) {$params.Add('whatif', $true)}

                    Move-VM @params | Out-Null

                }

            } ELSE {Write-Warning "There is no host capable of fulfilling the destination resource requirements"}

        }

    } ELSE {Write-warning "$($VMHost.name) is in a $($VMHost.connectionstate) state"}

} CATCH {
    Write-Error $_.Exception -ErrorAction stop
}
```
