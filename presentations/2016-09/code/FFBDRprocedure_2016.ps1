### This Script is not meant to be run in its entirety.  This is a collection of snippets that are ran when appropriate to do tasks related to the DR Test
return
#region #-------------Initialization--------------#

#Turn ProdData to $true to switch to the PROD DR TEST
$ProdData=$false
$Repo = 'local'
$ResetComputerAccounts = $false
$MoveFSMO = $false
    
switch ($Repo)  {
    'Jay'     {$RepoLocation = '\\rsc.first.int\DFS\users\jryan\scripts\gitrepo\'}
    'Shared'  {$RepoLocation = '\\rsc.first.int\DFS\data\Pictoria\it\System Services\Powershell Repository'}
    'Local'   {$RepoLocation = 'C:\git\Systems_Services_Git'}
}

if ($ProdData){
    Set-Variable loc -Value '\\rsc.first.int\DFS\data\Pictoria\it\System Services\DR2016\PROD\' -Confirm:$true
}else {
    Set-Variable loc -Value 'C:\personal\psug\CincyPowerShell.github.io\presentations\2016-09\code\TEST'
}

Set-Location c:\
Remove-PSDrive -Name PowershellRepo,DR -ErrorAction SilentlyContinue
New-PSDrive -Name PowershellRepo -Root $repolocation -PSProvider FileSystem
New-PSDrive -Name DR -Root $loc -PSProvider FileSystem
Set-Location DR:\
$psise.CurrentPowerShellTab.DisplayName = 'DR Script'
. PowershellRepo:\FFBCmdlets\Wait-VMPowerState.ps1
. PowershellRepo:\WIP\set-winvmIP.ps1
. PowershellRepo:\FFBScripts\Start-Monitor.ps1
. PowershellRepo:\WIP\DRModule.ps1
. PowershellRepo:\WIP\DNS\FFBDNS.ps1
Import-Module PowershellRepo:\FFBModules\FFBSystemsServices
#Import-Module V:\scripts\3rdParty\Modules\PoshRSJob

$XMLData = 'DR:\drdata.xml'
$SSBASWorksheet = 'DR:\DRlist.csv'
$SSBASWorksheetcompleted = 'DR:\DRdata.csv'
$SSBASWorksheetServers = 'DR:\drservers.csv'
$DRLUNS = 'DR:\drluns.csv'
$DNSdata = 'DR:\drdns.csv'
$VLANS = 'DR:\drvlans.csv'
$clustersdoc = '\\rsc.first.int\DFS_OC\Data\Pictoria\IT\System Services\ClusterIPs.xlsx'
$2012R2Server = 'sr1it100'
$LBVCenter = 'SR2VC011'
$DCVCenter = 'SR1VC011'
$VMFolder = 'DR Servers'

if(!(Get-ADUser -Filter 'memberOf -RecursiveMatch "CN=Organization Management,OU=Microsoft Exchange Security Groups,DC=first,DC=int"' -SearchBase (get-aduser $env:username).DistinguishedName)) {
    $vc = Get-Credential -Message "Please input your Admin Credentials for Vcenter access"
}

#endregion Initialization

#region #-------------Pre-Reqs----------------#
Start-PowerCLI -Credential $vc
#Import list of servers from the Planning worksheet, this will output an object - This is used to get the IP address, VLAN, and LUN's of the servers in the worksheet.  You can use the output to put this info back into the spreadsheet manually
[System.Collections.ArrayList]$DRInfo = @()
$DRInfo = Get-DRInfo -DRWorksheet $SSBASWorksheet -ExportPath $loc -Verbose

#exporting a XML for import to another machine to run some DR activites on multiple machines.  Exporting to CSV to combine data back into the SS BAS DR Worksheet.
$DRinfo | Export-Clixml $XMLData -Force
$DRInfo | Export-Csv $SSBASWorksheetcompleted -NoTypeInformation -Force
$DRInfo.'Server Details' | Export-Csv $SSBASWorksheetServers -NoTypeInformation -Force

$drinfodetails = $drinfo.'server details'

$VMServers = $drinfodetails | Sort-Object -property 'Server Name' -Unique | Sort-Object -Property @{e={$_.order -as [int]}},@{e={$_.'Application Tier' -as [int]}} | where {$_."Server Name" -ne 'N/A' -and $_.Physical -eq 'No'}
$ReplicatedVMs = $VMServers | Where {$_.'Recovery Method' -eq 'Replicated LUN'}
$ShutdownServers = $drinfodetails | where {$_.'Shutdown CyrusOne' -eq 'YES'}


#reset computer account passwords that are 20 days old or more

if ($ResetComputerAccounts){
    Reset-FFBComputerAccounts -ComputerName $($ReplicatedVMs.'server name') -Age 20 -Domain hq -Credential $vc -Verbose
}

#Move FSMO Roles

if ($MoveFSMOroles){
  Move-FFBFSMORoles -Destination DC2 -Roles All -Domain ALL -Verbose
}

#region #---------------DNSexports-----------------

[scriptblock]$Scriptblock = {
    ipconfig /flushdns | out-null

    $DNS = ($using:drinfo.'DNS' | where {$_ -ne ""}).split(",")

    $records = $DNS | foreach {
        Try {
            Resolve-DnsName -Name $_ -erroraction stop
        }Catch {
            Write-Warning "Could not find a record for [$_]"
            [pscustomobject]@{'Name'=$_}    
        }
     }   

     foreach ($record in $records){
        if ($record.type -eq 'CNAME'){
            [pscustomobject]@{'Type'=$record.type;'Value'=$record.namehost;'Name'=$record.Name;'TTL'=$record.TTL}
        }elseif ($record.type -eq 'A'){
            [pscustomobject]@{'Type'=$record.type;'Value'=$record.IPAddress;'Name'=$record.Name;'TTL'=$record.TTL}
        }
    }


    #$dnsrecords | Export-Csv $Using:DNSdata -NoTypeInformation -Force
}

$dnsrecords = Invoke-Command -ComputerName $2012R2Server -Credential $vc -ScriptBlock $Scriptblock

$dnsrecords | select Type,Value,Name,TTL | Export-Csv $DNSdata -NoTypeInformation -Force

#endregion dns exports

#region #--------------LUNs to move------------

$VMObjsReplicated = Get-VM -Name $ReplicatedVMs.'server name' -Server $DCVCenter
$Luns = Find-DRLUNs -VM $VMObjsReplicated
#exports the LUNs required for DR to CSV
$Luns | sort -Unique -Property datastore | export-csv $DRLUNS -NoTypeInformation -Force
$VMstoMigrate = $Luns | sort -Unique -Property VM | where {$_.isreplicated -eq $false}

#endregion LUNS

#region #----------VLANs to create---------------
Remove-PowerCLI
Start-PowerCLI -Server $LBVCenter -Credential $vc

$domain,$username = ($vc.UserName -split ("\\"))
$domain = "ucs-$domain.first.int"
$ucsCredential = Get-Credential -UserName "$domain\$username" -Message 'Enter the password for your UCS AD credential, do not modify the Username!'
$VLANIds = @($drinfo.'server details' | Sort-Object -Unique -Property VLAN | Select-Object -ExpandProperty VLAN)

#connect to UCS and Vmware
Import-Module VMware.VimAutomation.Vds
Connect-Ucs -Name "UCS1" -Credential $ucsCredential -Verbose | Out-Null

#Get VLAN's in DR Vcenter
$VPGs = Get-VDSwitch -name 1000v | Get-VDPortgroup -Name "N1KV*" | select name
$VPGIDs = foreach ($Vpg in $VPGs ){
    Write-Output "$($vpg.name.split("_")[1])"
    }

#Get VLANs in DR UCS 
$UCSOffsiteVLANS = Get-UcsVnicTemplate -Name VR2ESX-PROD4-A | Get-UcsVnicInterface
$UCSCTXVLANS = Get-UcsVnicTemplate -Name VR2CTX-PROD4-A | Get-UcsVnicInterface
$UCSVLANS = $UCSOffsiteVLANS + $UCSCTXVLANS
$UCSVLANS = $UCSVLANS | foreach {get-ucsvlan -Name $_.Name} | Select-Object -ExpandProperty id

$DRVLANS = foreach ($DRVLAN in $VLANIds) {
    $obj=[pscustomobject]@{'DRVLANID'=$DRVLAN;'VCenter'=$null;'UCS'=$null}
    $isMissingVM = Compare-Object -ReferenceObject $DRVLAN -DifferenceObject $VPGIDs | where {$_.sideIndicator -eq '<='}
    $isMissingUCS = Compare-Object -ReferenceObject $DRVLAN -DifferenceObject $UCSVLANS | where {$_.sideIndicator -eq '<='}
    if ($isMissingVM){
        $obj.VCenter = $false
        Write-Warning "Missing VLAN $DRVLAN from the Lightbound Vcenter"
    }else {
        $obj.VCenter = $true
    }
    if ($isMissingUCS){
        $obj.UCS = $false
        Write-Warning "Missing VLAN $DRVLAN from the Lightbound UCS"
    }else {
        $obj.ucs = $true    
    }
    Write-Output $obj

}
 
$DRVLANS | Export-Csv $VLANS -NoTypeInformation -Force

Remove-Module VMware.VimAutomation.Vds
Disconnect-Ucs
Remove-PowerCLI

#endregion vlans to create
#endregion Pre-Reqs

#region #-------------Pre-Failover----------------#

#Record Transcript of all DR actions
Start-Transcript -Path $loc\$env:username -Append

#Importing Data / Setting variables
[System.Collections.ArrayList]$DRInfo = @()
[System.Collections.ArrayList]$WindowsServers = @()
[System.Collections.ArrayList]$VMServers = @()
$DRinfo = Import-Clixml $XMLData

$drinfo | ogv
$drinfo.'server details' | ogv

# You can use this to scope DRinfo to just the servers you want
## $DRinfo = $DRinfo | out-gridview -passThru

### If you need multiple people running this, we can seperate $DRInfo by Tier, and by User
##
$drinfodetails = $drinfo.'server details'

$vmserversEng1 = $drinfodetails | where {$_.'SS Owner' -eq 'Damon' -or $_.'SS Owner' -eq 'Jay'} 
$vmserversEng2 = $drinfodetails | where {$_.'SS Owner' -eq 'Dustin' -or $_.'SS Owner' -eq 'Andrew'} 

#Pick which Roll you are (Don't run if only 1 user is running)
#$drinfodetails = $vmserversEng1 # Eng 1
#$drinfodetails = $vmserversEng2 # Eng 2
$drinfodetails = $drinfodetails | ogv -PassThru


#$windowsservers = $drinfodetails | where {($_.'server name' -like "S*")}
$VMServers = $drinfodetails | Sort-Object -property 'Server Name' -Unique | Sort-Object -Property @{e={$_.order -as [int]}},@{e={$_.'Application Tier' -as [int]}} | where {$_."Server Name" -ne 'N/A' -and $_.Physical -eq 'No'}
$ReplicatedVMs = $VMServers | Where {$_.'Recovery Method' -eq 'Replicated LUN'}
$ShutdownServers = $drinfodetails | where {$_.'Shutdown CyrusOne' -eq 'YES'}
#$dnsrecords = import-csv $DNSdata
#Start-PowerCLI -Credential $vc -Server $DCVCenter
$VMObjs = Get-VM -Name $VMServers.'server name'
$VMObjsShutdown = Get-VM -Name $ShutdownServers.'Server Name'
$VMObjsReplicated = Get-VM -Name $ReplicatedVMs.'Server Name'

#endregion Pre-Failover

#region #-------------Failover--------------------#

#region ------------Shutdown VMs--------------------

#### Wait for LUN snap
#### Disabled Linked Mode on Vcenters####

#Disable NIC for Exchange server and SQL clusters - This simulates a failures
$SQLClusters = 'CSQL1','CSQL2'
$CAS = 'CAS1'
$MBX = 'MBX1'
$Failclusters = $true
if($Failclusters -eq $true) {
    get-vm $CAS | Shutdown-VMGuest
    get-vm $MBX -Server $DCVCenter | get-networkadapter | Set-NetworkAdapter -Connected:$false
    get-vm -Name $SQLClusters | Get-NetworkAdapter | Set-NetworkAdapter -Connected:$false

}
 
#Shutdown servers

Shutdown-VMGuest $VMObjsShutdown -Confirm:$false

## start-monitor servers in new window
$psISE.PowerShellTabs.Add()
#Start-Sleep 3
$pingtab = $psise.PowerShellTabs | select -last 1
$pingtab.DisplayName = 'Ping Servers'
Do {Start-Sleep 1} Until ($pingtab.CanInvoke -eq $true)
$pingtab.Invoke({
    . DRModule.ps1
    $drinfo = import-clixml 'drdata.xml'
    $pinglist = ($drinfo.'server details' | where {$_.'Recovery Method' -eq 'Replicated LUN'}).'server name'
    Start-Monitor -ComputerName $pinglist
    }
)

#Monitor the Start-Monitor, wait for all servers to go offline.  Manually shut down VM's if necessary.

Remove-PowerCLI
#endregion Shutdown VMs

#Wait for DR Declaration

#Mount DR Volumes - RecoverPoint (Test a Recovery)

#region -----------Scan and Mount Volumes----------------

$Datacenter = "DC2"
$DatastorePrefix = "snap*"
$Datastores = $drinfo.'storage DevID' -split "," | where {$_ -ne ''}
$Datastores = $Datastores | foreach {
    "$DatastorePrefix$_"
}

Start-PowerCLI -Server $LBVCenter -Credential $vc

$ESXHosts = VMware.VimAutomation.Core\Get-Cluster 'OffSite Cluster' -Server $LBVCenter | Get-VMHost
#$AppVirtHosts = VMware.VimAutomation.Core\Get-Cluster 'appvirtoffsite' | get-vmhost

##### #Wait for storage to confirm all DR LUN's are Mapped
## Rescan $esxhost
#Get-VMHostStorage -VMHost $appvirthost[0] -RescanAllHba -RescanVmfs -Refresh
Get-VMHostStorage -VMHost $ESXHosts[0] -RescanAllHba -RescanVmfs -Refresh

#Mount and resig all DR LUNs

###Warning - this takes a long time and should not be run Async with more than 3-5 LUNs to Resig!
lun_find_and_resignature -esxhost $($ESXHosts[0].Name)

<# This may need to be ran if the LUN's have been previously attached and do not show up as a new datastore.
$newtab.Invoke(
    {
        $scsiluns = Get-ScsiLun -VmHost $ESXHosts
            $detatched = $scsiluns | select CanonicalName,Multipathpolicy,@{N='Operational State';E={$_.ExtensionData.Operationalstate}} | Where {$_.'Operational State' -eq 'off'}
            if ($detatched){
                foreach ($ESXHost in $ESXHosts) {
                    foreach ($disk in $detatched) {
                        Attach-Disk -CanonicalName $disk.canonicalName -VMHost $ESXHost
                    }
                }
            }
            get-datastore -Name snap* | where {$_.State -eq 'Unavailable'} | Mount-Datastore -Verbose
    }
)
#>

#endregion Scan and Mount Volumes

#region ----------Shutdown Test servers to make room for DR----------

$shutdownTESTservers = get-content $loc\shutdowntest.txt

Shutdown-VMGuest $shutdownTESTservers -Confirm:$false

#check for powered on VMs.
get-vm $shutdownTESTservers | where {$_.PowerState -eq 'PoweredOn'}

# Stop-VM

#endregion

#region -----------Add Folder and Register VMs-------------
### Need to create VM folder not datahost folder if doesn't exist

if (-not (get-datacenter $Datacenter | Get-Folder -Name $VMFolder) ) {

    New-Folder -Name $VMFolder -Location (get-datacenter $Datacenter | get-folder -name vm) -Server $LBVCenter
}
$oldVerbosePreference = $VerbosePreference
$VerbosePreference = 'Continue'
$datastores = Get-Datastore $Datastores 
foreach($Datastore in $Datastores) {
   # Set up Search for .VMX Files in Datastore
   $ds = $Datastore | Get-View -Verbose:$false
   $SearchSpec = New-Object VMware.Vim.HostDatastoreBrowserSearchSpec
   $SearchSpec.matchpattern = "*.vmx"
   $dsBrowser = Get-View $ds.browser
   $DatastorePath = "[" + $ds.Summary.Name + "]"
 
   # Find all .VMX file paths in Datastore, filtering out ones with .snapshot (Useful for NetApp NFS)
   $SearchResult = $dsBrowser.SearchDatastoreSubFolders($DatastorePath, $SearchSpec) | where {$_.FolderPath -notmatch ".snapshot" -and $_.File -ne $null } | %{$_.FolderPath + ($_.File | select Path).Path}
    if ($SearchResult){
        Write-Verbose "Found the following VMX Files!"
        Write-Verbose "$SearchResult"
    } Else {
        Write-Verbose "[$($Datastore.name)] - No Search results!"
    }
  
   #Register all .vmx Files as VMs on the datastore
   foreach($VMXFile in $SearchResult) {
      Write-Verbose "Registering VM - $VMXFile"
      New-VM -VMFilePath $VMXFile -VMHost ($ESXHosts | get-random -Count 1) -Location $VMFolder -RunAsync
   }
}
$VerbosePreference = $oldVerbosePreference

#enable DRS
get-cluster -Name 'Offsite Cluster' | set-cluster -DrsAutomationLevel FullyAutomated


# Check list of replicated VM's against the VM's that are were registered
   $Recovered =  (get-vm -Location (get-datacenter $Datacenter | Get-Folder -Name $VMFolder) ).Name
   Compare-Object -ReferenceObject $($ReplicatedVMs.'Server Name') -DifferenceObject $Recovered -IncludeEqual -OutVariable recoveredcompare
   $recoveredcompare | where {$_.SideIndicator -eq '<='}

#endregion Add Folder and Register VMs

#region -----------Set Network Adapter, Reattach missing disks ---------

$VMObjs = Get-VM -Name $VMServers.'server name'
$VMObjsShutdown = Get-VM -Name $ShutdownServers.'Server Name'
$VMObjsReplicated = Get-VM -Name $ReplicatedVMs.'Server Name'
# $ctx = $vmservers | where {$_.'server name' -like 'SR1CTX*'}
# $ctxDRvms = Get-VM -Name $ctx.'server name' -Server $LBVCenter

$oldverbose = $VerbosePreference
$VerbosePreference = 'Continue' 
foreach ($vmServer in $ReplicatedVMs){
    $VMNetworkName = "N1KV_$($vmserver.VLAN)"
    $vm = get-vm $vmserver.'Server Name'
    $vmnic = get-networkadapter -VM $vm
    if ($vmnic.NetworkName -ne $VMNetworkName) {
        Set-NetworkAdapter -Portgroup $VMNetworkName -NetworkAdapter $vmnic  -Confirm:$false
    } Else {
        Write-Verbose "[$($vmserver.'Server Name')] The Network Adapter has already been set"
    }
    
    #If VM had more than 1 disk, it is missing, this section finds the disks and attaches them to the VM before attempting power up.
    $HDCount = ($vm | get-harddisk).count
    $missingdisks = $vm | get-harddisk | where {$_.CapacityKB -eq 0}
    if ($missingdisks) {
        foreach ($missingdisk in $missingdisks) {
            $matchpattern = ($missingdisk.Filename.Split("/"))[-1]
            Write-Warning "[$($vmserver.'Server Name')] is missing a disk [$matchpattern]"
            foreach ($disk in $vmserver.'Storage DevID' -split ","){
                $ds = get-datastore -Name "$DatastorePrefix$disk" | Get-View
                $SearchSpec = New-Object VMware.Vim.HostDatastoreBrowserSearchSpec
                $SearchSpec.matchpattern = $matchpattern
                $dsBrowser = Get-View $ds.browser
                $DatastorePath = "[" + $ds.Summary.Name + "]"
                $SearchResult = $dsBrowser.SearchDatastoreSubFolders($DatastorePath, $SearchSpec) | where {$_.FolderPath -notmatch ".snapshot" -and $_.File -ne $null } | foreach {$_.FolderPath + ($_.File | select Path).Path}
                if ($searchResult){
                    Write-Output "Found Disk! $SearchResult"
                    Write-Verbose "Removing Old Disk..."
                    $missingdisk | Remove-HardDisk -Confirm:$false
                    Write-Verbose "Adding New Disk...[$searchResult]"
                    New-HardDisk -VM $vm -DiskPath $SearchResult
                    Remove-Variable SearchResult
                }
            }
        }
    }Else {
        Write-Verbose "[$($vmserver.'Server Name')] No missing Disks found, moving on..."
    }
}
$VerbosePreference = $oldverbose

#endregion Set Network Adapter, reattach missing disks

#region -----------Power On VMs--------

Start-VM -VM $VMObjsReplicated -RunAsync -ErrorVariable starterror

get-task -Status Running

## Wait for servers to have the question to answer

$VMObjsReplicated | Get-VMQuestion | Set-VMQuestion -Option button.uuid.copiedTheVM -Confirm:$false 

###Wait until all VM's are powered up to continue to the next step

#endregion Power ON VMs

#region Reconfigure IP's

#This is necessary for connecting to disconnected machines.
$gc = Get-Credential -Message "Local admin rights to the VMs"
$hc = Get-Credential -Message "Please input esxi root credentials for Invoke-vmscript" #vmware ESX Host credential

$DNS = "10.17.10.20","10.17.10.10"
$Subnetmask = "255.255.255.0"
foreach ($vmserver in $ReplicatedVMs){
    $servername = $vmserver.'server name'
    if ((get-vm -name $servername).PowerState -eq 'PoweredOn'){
        ## promting may be needed in a real DR if you need to use the local admin credentials
        #$gc = Get-Credential -Message "$servername admin rights to the VMs"
        $newIP = $vmserver.'Failover IP'
        $octets = $newIP -split '\.' ## Splits the IP into octets
        $octets[3] = '250' ### converts the last octect to the Router Gateway address
        $gateway = $octets -join '.'  ### Joins the octects back together making the complete gateway
        Set-WinVMIP -ComputerName $servername -HostCredential $hc -GuestCredential $gc -IPAddress $newIP -SubnetMask $Subnetmask -Gateway $gateway -DNSServers $DNS -Vcenter $LBVCenter -Method powershell -From 'sr2dc020' -FromCredential $vc -Verbose
    }else {Write-Host "$servername is not powered On....Moving on"}
}

Remove-PowerCLI

#endregion Reconfigure IPs

#region TESTING ----- Change DNS records (Import list of DNS changes)
<#

$DNSServer ='sr2dc020'
$dnschanges = $dnsrecords | where {$_.Type -eq 'A'}
foreach ($change in $DNSChanges){
    if ( -not (Test-Connection $change.name -Count 2 -Quiet) ) {
        
        Remove-DNSRecord -DNSServer $DNSServer -credential $vc -RecordType $change.Type -RecordName $change.Name -Verbose
        $dnsarray = $change.name.split(".")
        $count = $dnsarray.count -1
        $hostname = $dnsarray[0]
        $fzone = $dnsarray[1..$count] -join "."
        New-DnsRecord -DNSserver $DNSServer -credential $vc -arec -fzone $fzone -computer $hostname -address $change.'Failover Value'
    }
}

#endregion
#>
#endregion

#endregion

#region #-------------Failback--------------------#

Start-PowerCLI -Credential $vc -Server $LBVCenter

#Revert DNS entries - future CODE!

#Shut down VM's at LIghtbound / Unregister VM's

Shutdown-VMGuest $ShutdownServers.'server name' -Confirm:$false

###Restart the ping scripts, ensure that all servers are powered down.

# This is removes the servers 
remove-vm $ReplicatedVMs.'server name' -Confirm:$false


Remove-PowerCLI

#Power on VM's at Cincy
Start-PowerCLI -Credential $vc -Server $DCVCenter

#Start AD / DHCP

if ($ProdData -eq $true){
    start-vm DC1,DC2,DC3,DHCP1 -RunAsync
    
    start-vm $CAS
    get-vm $MBX -Server $DCVCenter | get-networkadapter | Set-NetworkAdapter -Connected:$true

    get-vm $SQLClusters | Get-NetworkAdapter | Set-NetworkAdapter -Connected:$true
}

####Enable Linked mode - VC

#enable DRS
get-cluster -Name 'Production' | Set-Cluster -DrsAutomationLevel FullyAutomated

#Startup servers

Start-VM -VM $ShutdownServers.'server name' -RunAsync

## start-monitor in new window

#Ping VMs
#Run Start-Monitor function against the list of servers to monitor

#Run DRS recommendation Jobs to ensure that the cluster is balanced upon DC coming back on line.
Get-DrsRecommendation | Apply-DrsRecommendation -RunAsync

#set DRS back to Normal
get-cluster -Name 'Production' | Set-Cluster -DrsAutomationLevel PartiallyAutomated


Remove-PowerCLI
#Back to lightbound to clean up
Start-PowerCLI -Server $LBVCenter -Credential $vc

#enable DRS
get-cluster -Name 'Offsite Cluster' | Set-Cluster -DrsAutomationLevel PartiallyAutomated -Confirm:$false

#Unmount and Detach Datastores
get-datastore snap* | Unmount-Datastore -Verbose
get-datastore snap* | Detach-Datastore -Verbose

### XtremIO Unmap 

### Recoverpoint Finish Test Copy

get-datastore snap* | Remove-DetatchedDatastore -Verbose

if ($MoveFSMOroles){
    Move-FFBFSMORoles -Destination DC1 -Roles All -Domain ALL
}

#endregion