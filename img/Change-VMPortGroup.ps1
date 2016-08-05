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