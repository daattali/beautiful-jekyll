---
layout: post
published: true
title: Move VLAN to a different vSwitch
---
Recently after we had a network change aimed to consolidate our uplinks, I had to move a whole bunch of VMs to a port-group in a different vSwitch but in the same VLAN without losing connectivity.

It is a very easy process and not a single ping is lost (maybe one).

- Create a port-group in the target vSwitch with a different name (Can be easily scripted if you have lots of hosts).

_Existing port-group "R-50" in vSwitch1  
New port-group "V-50" in vSwitch0_

![change-vmportgroup.jpg]({{site.baseurl}}/img/change-vmportgroup.jpg)

- Check that the new port-group is properly configured by placing a test VM in it and by pinging the gateway.

- Once validated, this little script will help to do it en masse. If the previous test failed it is down to your network admin to troubleshoot. Probably these new VLANs not enabled on the trunk port.

To move the VMs located in the "VmFolder1" folder:

```Powershell

Get-VM -Location "VmFolder1" | Change-VMPortGroup -SrcPortgroupName "R-50" -DestPortgroupName "V-50"

```

During the change the VMs doesn't loose a ping.

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
