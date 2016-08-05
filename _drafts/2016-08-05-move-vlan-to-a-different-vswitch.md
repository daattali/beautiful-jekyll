---
layout: post
published: false
title: Move VLAN to a different vSwitch
---
Recently after we had network changes to consolidate our network, I had to move a whole bunch of VMs to a port-group in a different vSwitch but in the same VLAN without losing connectivity.

In order to do that I created a port-group in the target vSwitch with a different name.

-Existing port-group "R-50" in vSwitch1
-New port-group "V-50" in vSwitch0

![change-vmportgroup.jpg]({{site.baseurl}}/img/change-vmportgroup.jpg)

I checked that the new port-group was properly configured by placing a test VM on it and pinging the gateway. Once I validated this step I proceeded to write a little script to do it en masse.

To move the VMs from a folder:

```Powershell

Get-VM -Location "VmFolder1" | Change-VMPortGroup -SrcPortgroupName "R-50" -DestPortgroupName "V-50"

```

During the change the VMs doesn't loose a single ping.

```Powershell

Function Change-VMPortGroup {

[CmdletBinding(SupportsShouldProcess = $true,ConfirmImpact = 'High')] 

param(

    [parameter(position=0,ValueFromPipeline=$True,ValueFromPipelineByPropertyname=$True)]
    [VMware.VimAutomation.ViCore.types.V1.Inventory.VirtualMachine[]]
    $VM,

    [string]
    $SrcPortgroupName,

    [string]
    $DestPortgroupName

)

Begin{

    $hosts = Get-VMHost

    $Dest = Get-virtualportgroup -name $DestPortgroupName
    IF ($Dest.count -lt $hosts.count) {Write-Warning "$DestPortgroupName not present on all the hosts"} ELSEIF (!$Dest) {break}

    $Src = Get-virtualportgroup -name $SrcPortgroupName
    IF (!$Src) {break}

}

Process{

    $VM | ForEach-Object {
        
        TRY {

            IF ($PSCmdlet.ShouldProcess($_.name,"Move from $SrcPortgroupName to $DestPortgroupName")) {

                $_ | Get-NetworkAdapter | where networkname -eq $SrcPortgroupName | Set-NetworkAdapter -NetworkName $DestPortgroupName -Confirm:$false
        
            }

        } CATCH {

            Write-Error $_.Exception -ErrorAction Stop
            
        }

    }
    
}

}

```