Function Reset-FFBComputerAccounts {
    [CmdletBinding(SupportsShouldProcess)]
    Param (
        [ValidateScript({Test-Connection -ComputerName $_ -Quiet})]
        [string[]]$ComputerName,
        [ValidateRange(0,30)]
        [int]$Age = 20,
        [pscredential]$Credential,
        [string[]]$Domain
    )

    Begin {
        
    }
    Process {
        foreach($computer in $ComputerName){
	        foreach ($singledomain in $domain){ 
               try{
                    $passwordage = [datetime]::fromfiletime((Get-adcomputer -server $singledomain -identity $computer -properties pwdLastSet).pwdlastset)
                    Write-Verbose "Found [$computer] in the [$singledomain] Domain - Password Age $passwordage"
                    break
                }catch{
                    Write-Warning "[$Computer] was not found in [$singledomain]"
                }#try/catch 
            }
	        $pwage = ((get-date) - $passwordage).days
	        if($pwage -ge $age){
                Write-Verbose "$computer account password is $pwage days old and will be reset $passwordage"
                if ($pscmdlet.ShouldProcess("$computer", "Reset computer account password, it is $pwage Days old")) {
                    Try {
                        Invoke-Command -ComputerName $Computer -Credential $Credential -ScriptBlock {
                            Try {
                                Reset-ComputerMachinePassword
                            }Catch {
                                Write-Warning "[$env:COMPUTERNAME] Password could not be reset."
                            }
                        }
                    }Catch {
                        Write-Warning "[$computer] Could not connect to the remote machine."
                    }
                }
            }else {
                    Write-Verbose "The Account password for [$computer] is $pwage days old and will not be reset"
            }# if age
        }# foreach computer
    }
}
Function Start-PowerCLI {
    Param (
        [string[]]$Server='sr1vc011',
        [switch]$AllLinked,
        [pscredential]$Credential
    )
    $oldverbosepreference = $VerbosePreference
    $VerbosePreference = 'SilentlyContinue'
    $global:DefaultVIServer = $null
    $global:DefaultVIServers = $null
    # . "C:\Program Files (x86)\VMware\Infrastructure\vSphere PowerCLI\Scripts\Initialize-PowerCLIEnvironment.ps1" 
    Import-Module VMware.VimAutomation.Core
    $oldwarningpreference = $WarningPreference
    $WarningPreference = 'SilentlyContinue'
    if ($PSBoundParameters['Credential']){
        Connect-VIServer -Server $Server -AllLinked:$AllLinked -Credential $Credential | Out-Null
    }else {
        Connect-VIServer -Server $Server -AllLinked:$AllLinked | Out-Null
    }
    $WarningPreference = $oldwarningpreference
    $VerbosePreference = $oldverbosepreference
}
Function Remove-PowerCLI {
    $oldverbosepreference = $VerbosePreference
    $VerbosePreference = 'SilentlyContinue'
    Disconnect-VIServer * -Force -Confirm:$false -ErrorAction SilentlyContinue
    
    Remove-Module *vmware*
    $VerbosePreference = $oldverbosepreference
}
Function Get-DRInfo {
    [CmdletBinding()]
    Param (
        [ValidateScript({Test-Path $_ -PathType Leaf})]
        $DRWorksheet,
        
        [pscredential]$Credential,
        
        $ExportPath
    )
    Begin {
        $DRData = Import-Csv -Path $DRWorksheet
        $clusters = Import-Excel -FileName $clustersdoc -WorksheetName Cluster -DisplayProgress $false
        $listeners = Import-Excel -FileName $clustersdoc -WorksheetName Listener -DisplayProgress $false
        [System.Collections.ArrayList]$ServersProcessed = @()
        [System.Collections.ArrayList]$restrictedIPs = @()
        [System.Collections.ArrayList]$AllServers = @()
        ForEach ($listener in $listeners) {
            $restrictedIPs += $listener.'IP-LB'
        }
        ForEach ($cluster in $clusters){
            $restrictedIPs += $cluster.'ClusterIP-LB'
        }
        Try {
            Start-PowerCLI -Credential $Credential
        } Catch {
            $_
            return
        }
    }
    Process {
        ForEach ($App in ($DRData | where {$_.'Server Name' -ne $null -and $_.'Server Name' -ne 'N/A' -and $_.'Server Name' -ne ''} ) ) {
            $AppServers = $app.'Server Name' -split ','
            [System.Collections.ArrayList]$Servers = @()
            [System.Collections.ArrayList]$AppIPs = @()
            [System.Collections.ArrayList]$DRAppIPs = @()
            [System.Collections.ArrayList]$AppDatastores = @()
            [System.Collections.ArrayList]$AppVLANIDs = @()
                        
            foreach ($AppServer in $AppServers){
                Write-Verbose "Processing Server $AppServer of Application [$($app.'Application Name')]"
                if ($App.Physical -eq 'No' -and $App.'Recovery Method' -eq 'Replicated LUN') {
                    $VM = get-vm $appserver -Verbose:$false
                    
                    # Find the LUN's that each server is on
                    $ServerDatastores = ($VM | select @{N="Datastore";E={Get-Datastore -Id $_.DatastoreIdList -Verbose:$false | Select -ExpandProperty Name}}).datastore -join ","
                    $AppDatastores.add($ServerDatastores) | Out-Null
                    
                    # Find the VLAN for each VM
                    $VLANID = (Get-NetworkAdapter -VM $VM -Verbose:$false).NetworkName.Split("_")[1]
                    $AppVLANIDs.Add($VLANID) | Out-Null
                }
                
                # Find the IP's for each Server
                Try {
                    $IP = (Test-Connection $AppServer -Count 1 -ErrorAction Stop).IPV4Address.IPAddressToString
                    $AppIPs.Add($IP) | Out-Null
                } Catch {
                    Write-Warning "Can not connect to [$AppServer] - Please verify that the server is on the network and pingable"
                }

                # Find available Failover IP address
                if ($appserver -notin $ServersProcessed) {
                    if ( ($App.'Recovery Method' -eq 'Replicated LUN' -or $App.'Recovery Method' -eq 'Networker Restore') -and $IP -ne $null) {
                        $octets = $IP.Split('.')
                        #transpose 2nd octet
                        if ($octets[1] -ne 8){
                            $octets[1] = 17
                        }else {
                            $octects[1] = 24
                        }
                        $DrIp1 = $octets -join "."
                        if (($octets[3] -as [int]) -lt 150 ){ 
                            $octets[3] = ($octets[3] -as [int]) + 100
                        }else {
                            $octets[3] = ($octets[3] -as [int]) - 100
                        }
                        $DrIp2 = $octets -join "."

                        if ($DrIp1 -notin $restrictedIPs -and (-not (Test-Connection -ComputerName "$DrIp1" -Count 2 -Quiet -ErrorAction SilentlyContinue))) {
                            $DrIp = $DrIp1
                            [void]$restrictedIPs.add($DrIp)
                            Write-Verbose "[$($app.'Application Name')] - [$AppServer] - Failover IP Set [$DrIP]"
                        } elseif ($DrIp2 -notin $restrictedIPs -and (-not (Test-Connection -ComputerName "$DrIp2" -Count 2 -Quiet -ErrorAction SilentlyContinue))) {
                            Write-Verbose "$DRIp1 is in use!"
                            $DrIp = $DrIp2
                            [void]$restrictedIPs.add($DrIp)
                            Write-Verbose "[$($app.'Application Name')] - [$AppServer] - Failover IP Set [$DrIP]"
                        } else {
                            Write-Verbose "$DRIp2 is in use!"    
                            for ($i = 249; $i -gt 0; $i--){ 
                                $octets[3] = $i
                                $i
                                $DrIp3 = $octets -join "."
                                if ($DrIp3 -notin $restrictedIPs -and (-not (Test-Connection -ComputerName "$DrIp3" -Count 2 -Quiet))) {
                                    $DrIp = $DrIp3
                                    [void]$restrictedIPs.add($DrIp)
                                    Write-Verbose "[$($app.'Application Name')] - [$AppServer] - Failover IP Set [$DrIP]"
                                    break
                                }
                            }
                        }
                                
                        if (-not $DRip) {  
                            Write-Warning "Could not find an available IP address for [$AppServer].  Please assign one manually"
                        }
                        $DRAppIPs.Add($DrIp) | Out-Null
                    } else {
                        Write-Verbose "[$AppServer] is not replicated or is not online. No Failover IP configured."
                    }
                } else {
                    $dupserver = $AllServers | where {$_.'Server Name' -eq $AppServer} | select -First 1
                    if ($dupserver) {
                        Write-Verbose "[$AppServer] has already been processed. Set IP to [$($dupserver.'Failover IP')]"
                        $DrIp = $dupserver.'Failover IP'
                        $DRAppIPs.Add($DrIp) | Out-Null
                        Remove-Variable dupserver
                    }
                }
                $Server = [pscustomobject]@{"Server Name" = $AppServer;"Application Name" = $App.'Application Name';"Shutdown CyrusOne" = $App.'Shutdown CyrusOne';"Recovery Method" = $App.'Recovery Method';'Original IP' = $IP; 'Failover IP' = $DrIp;'Storage DevID' = $ServerDatastores;'VLAN' = $VLANID;'Physical' = $App.Physical;'Application Tier' = $App.'Application Tier';'Order' = $App.Order;'SS Owner'=$App.'SS Owner'}
                $Servers.Add($Server) | Out-Null
                $AllServers.add($server)| Out-Null
                Remove-Variable -Name VM,ServerDatastores,VLANID,DrIp -Force -ErrorAction SilentlyContinue
                [void]$ServersProcessed.add($AppServer)
            } #End foreach $appserver
            $App | Add-Member -MemberType NoteProperty -Name 'Server Details' -Value $Servers -Force
            $App.'Storage DevID' = ($AppDatastores | select -Unique ) -join ","
            $App.VLAN = ($AppVLANIDs | select -Unique) -join ","
            $App.'Original IP' = ($AppIPs | select -Unique ) -join ","
            $App.'Failover IP' = ($DRAppIPs | select -Unique ) -join ","
            Write-Output $App
        } #End ForEach $App
        

    } #End Process Block
    End {
        $restrictedIPs | export-csv "$exportpath\restrictedIPs.csv" -NoTypeInformation -Force
        Remove-powerCLI
    }
}
Function Find-DRLUNs {
    [CmdletBinding()]
    Param (
        [VMware.VimAutomation.ViCore.Impl.V1.VM.UniversalVirtualMachineImpl[]]$VM
    )
    Begin {
    }
    Process {
        foreach ($Vserver in $VM){
            $lunmapping = $Vserver | select name,@{N="Datastore";E={Get-Datastore -Id $_.DatastoreIdList | Select -ExpandProperty Name}}
            foreach ($item in $lunmapping){
                Write-Verbose "Processing $($item.Name)"
                foreach ($lun in $item.Datastore){
                    Write-Verbose "Processing $lun"
                    $obj=[pscustomobject]@{'datastore' = $lun; 'VM' = $item.Name;'isReplicated'=[bool]$null}
                    if ($lun -notlike '*RDF*' -and $lun -notlike 'RP_*'){
                        Write-Warning "$($item.Name) on $LUN is not replicated!"
                        $obj.isReplicated= $false
                    }else {
                        Write-Verbose "[$($item.Name) on [$LUN] is replicated"
                        $obj.isReplicated= $true
                    }
                Write-Output $obj
                } 
            }
        
        }
    }    
}
function lun_find_and_resignature {
    [CmdletBinding()]
    # This only needs to run on one ESXi host in the cluster
    Param (
        [string]$esxhost,
        [switch]$RunASync
    )

    $hostView = get-vmhost -name $esxhost | get-view
    $dsView = get-view $hostView.ConfigManager.DatastoreSystem
    $unBound = $dsView.QueryUnresolvedVmfsVolumes()

    foreach ($ub in $UnBound) {
        $extPaths = @()
        $Extents = $ub.Extent;
        foreach ($ex in $Extents) {
            $extPaths = $extPaths + $ex.DevicePath
        }

        $resolutionSpec = New-Object VMware.Vim.HostUnresolvedVmfsResignatureSpec
        $resolutionSpec.extentDevicePath = New-Object System.String[] (1)
        $resolutionSpec.extentDevicePath[0] = $extPaths

        $dsResig = Get-View -Id $hostView.ConfigManager.DatastoreSystem
        
        if ($PSBoundParameters['RunASync']){
            $dsResig.ResignatureUnresolvedVmfsVolume_Task($resolutionSpec)    # This one runs a background task and continues
        }else {
            $dsResig.ResignatureUnresolvedVmfsVolume($resolutionSpec)        # This one waits for the task to finish
        }
    }

}
Function Get-DatastoreMountInfo {
	[CmdletBinding()]
	Param (
		[Parameter(ValueFromPipeline=$true)]
		$Datastore
	)
	Process {
		$AllInfo = @()
		if (-not $Datastore) {
			$Datastore = Get-Datastore
		}
		Foreach ($ds in $Datastore) {  
			if ($ds.ExtensionData.info.Vmfs) {
				$hostviewDSDiskName = $ds.ExtensionData.Info.vmfs.extent[0].diskname
				if ($ds.ExtensionData.Host) {
					$attachedHosts = $ds.ExtensionData.Host
					Foreach ($VMHost in $attachedHosts) {
						$hostview = Get-View $VMHost.Key
						$hostviewDSState = $VMHost.MountInfo.Mounted
						$StorageSys = Get-View $HostView.ConfigManager.StorageSystem
						$devices = $StorageSys.StorageDeviceInfo.ScsiLun
						Foreach ($device in $devices) {
							$Info = "" | Select Datastore, VMHost, Lun, Mounted, State
							if ($device.canonicalName -eq $hostviewDSDiskName) {
								$hostviewDSAttachState = ""
								if ($device.operationalState[0] -eq "ok") {
									$hostviewDSAttachState = "Attached"							
								} elseif ($device.operationalState[0] -eq "off") {
									$hostviewDSAttachState = "Detached"							
								} else {
									$hostviewDSAttachState = $device.operationalstate[0]
								}
								$Info.Datastore = $ds.Name
								$Info.Lun = $hostviewDSDiskName
								$Info.VMHost = $hostview.Name
								$Info.Mounted = $HostViewDSState
								$Info.State = $hostviewDSAttachState
								$AllInfo += $Info
							}
						}
						
					}
				}
			}
		}
		$AllInfo
	}
}
Function Detach-Datastore {
	[CmdletBinding()]
	Param (
		[Parameter(ValueFromPipeline=$true)]
		$Datastore
	)
	Process {
		if (-not $Datastore) {
			Write-Host "No Datastore defined as input"
			Exit
		}
		Foreach ($ds in $Datastore) {
			$hostviewDSDiskName = $ds.ExtensionData.Info.vmfs.extent[0].Diskname
			if ($ds.ExtensionData.Host) {
				$attachedHosts = $ds.ExtensionData.Host
				Foreach ($VMHost in $attachedHosts) {
					$hostview = Get-View $VMHost.Key
					$StorageSys = Get-View $HostView.ConfigManager.StorageSystem
					$devices = $StorageSys.StorageDeviceInfo.ScsiLun
					Foreach ($device in $devices) {
						if ($device.canonicalName -eq $hostviewDSDiskName) {
							$LunUUID = $Device.Uuid
							Write-Host "Detaching LUN $($Device.CanonicalName) from host $($hostview.Name)..."
							$StorageSys.DetachScsiLun($LunUUID);
						}
					}
				}
			}
		}
	}
}
Function Unmount-Datastore {
	[CmdletBinding()]
	Param (
		[Parameter(ValueFromPipeline=$true)]
		$Datastore
	)
	Process {
		if (-not $Datastore) {
			Write-Host "No Datastore defined as input"
			Exit
		}
		Foreach ($ds in $Datastore) {
			$hostviewDSDiskName = $ds.ExtensionData.Info.vmfs.extent[0].Diskname
			if ($ds.ExtensionData.Host) {
				$attachedHosts = $ds.ExtensionData.Host
				Foreach ($VMHost in $attachedHosts) {
					$hostview = Get-View $VMHost.Key
					$StorageSys = Get-View $HostView.ConfigManager.StorageSystem
					Write-Host "Unmounting VMFS Datastore $($DS.Name) from host $($hostview.Name)..."
					$StorageSys.UnmountVmfsVolume($DS.ExtensionData.Info.vmfs.uuid);
				}
			}
		}
	}
}
Function Mount-Datastore {
	[CmdletBinding()]
	Param (
		[Parameter(ValueFromPipeline=$true)]
		$Datastore
	)
	Process {
		if (-not $Datastore) {
			Write-Host "No Datastore defined as input"
			Exit
		}
		Foreach ($ds in $Datastore) {
			$hostviewDSDiskName = $ds.ExtensionData.Info.vmfs.extent[0].Diskname
			if ($ds.ExtensionData.Host) {
				$attachedHosts = $ds.ExtensionData.Host
				Foreach ($VMHost in $attachedHosts) {
					$hostview = Get-View $VMHost.Key
					$StorageSys = Get-View $HostView.ConfigManager.StorageSystem
					Write-Host "Mounting VMFS Datastore $($DS.Name) on host $($hostview.Name)..."
					$StorageSys.MountVmfsVolume($DS.ExtensionData.Info.vmfs.uuid);
				}
			}
		}
	}
}
Function Attach-Datastore {
	[CmdletBinding()]
	Param (
		[Parameter(ValueFromPipeline,ParameterSetName='Datastore')]
		[VMware.VimAutomation.ViCore.Impl.V1.DatastoreManagement.VmfsDatastoreImpl]$Datastore
	)
	Process {
        Foreach ($ds in $Datastore) {
			$hostviewDSDiskName = $ds.ExtensionData.Info.vmfs.extent[0].Diskname
			if ($ds.ExtensionData.Host) {
				$attachedHosts = $ds.ExtensionData.Host
				Foreach ($VMHost in $attachedHosts) {
					$hostview = Get-View $VMHost.Key
					$StorageSys = Get-View $HostView.ConfigManager.StorageSystem
					$devices = $StorageSys.StorageDeviceInfo.ScsiLun
					Foreach ($device in $devices) {
						if ($device.canonicalName -eq $hostviewDSDiskName) {
							$LunUUID = $Device.Uuid
							Write-Host "Attaching LUN $($Device.CanonicalName) to host $($hostview.Name)..."
							$StorageSys.AttachScsiLun($LunUUID);
						}
					}
				}
			}
		}
        
	}
}
Function Remove-DetatchedDatastore {
	[CmdletBinding(SupportsShouldProcess)]
	Param (
		[Parameter(ParameterSetName='Datastore',ValueFromPipeline)]
		[VMware.VimAutomation.ViCore.Impl.V1.DatastoreManagement.VmfsDatastoreImpl]$Datastore,
        [Parameter(ParameterSetName='Host',ValueFromPipelineByPropertyName)]
        $VMHost
	)
	
    Process {
		if ($psboundparameters['VMHost']) {
			$hostcli = Get-EsxCli -VMHost $VMhost -V2
            $Detatched = $hostcli.storage.core.device.detached.list.Invoke()
            
            foreach ($lun in $Detatched){
                $arguments = $hostcli.storage.core.device.detached.remove.CreateArgs()
                $arguments.device = $lun.deviceUID
                if ($pscmdlet.ShouldProcess("$($lun.DeviceUID) on $($hostcli.VMHost.name)", "Remove LUN")) {
                    Write-Host "Removing LUN $($lun.DeviceUID) from host $($hostcli.VMHost.name)..."
                    $hostcli.storage.core.device.detached.remove.Invoke($arguments)
                }
            }
		}elseif ($psboundparameters['Datastore']) {
		    Foreach ($ds in $Datastore) {
			    $hostviewDSDiskName = $ds.ExtensionData.Info.vmfs.extent[0].Diskname

			    if ($ds.ExtensionData.Host) {
				    $attachedHosts = $ds.ExtensionData.Host
				    Foreach ($VMHost in $attachedHosts) {
                   	    $hostcli = Get-EsxCli -VMHost (get-vmhost -id $VMHost.Key ) -V2
                        $lunid = $hostcli.storage.core.device.detached.list.Invoke() | Where {$_.DeviceUID -eq $hostviewDSDiskName}
					    if ($pscmdlet.ShouldProcess("$($lunid.DeviceUID) on $($hostcli.VMHost.name)","Remove LUN")) {
                            Write-Host "Removing LUN $($lunid.DeviceUID) from host $($hostcli.VMHost.name)..."
					        $arguments = $hostcli.storage.core.device.detached.remove.CreateArgs()
                            $arguments.device = $lunid.DeviceUID
                            $hostcli.storage.core.device.detached.remove.Invoke($arguments)
                        }
				    }
			    }
		    }
        }
	}
}
Function Attach-Disk{
    param(
        [Parameter(Mandatory,ValueFromPipeline,ValueFromPipelineByPropertyName)]
        [VMware.VimAutomation.ViCore.Impl.V1.Inventory.VMHostImpl]$VMHost,
        
        [string]$CanonicalName
    )
    $storSys = Get-View $VMHost.Extensiondata.ConfigManager.StorageSystem
    $lunUuid = ($storsys.storagedeviceinfo.scsilun | ? CanonicalName -eq $CanonicalName).Uuid
    $storSys.AttachScsiLun($lunUuid)
}
Function Detach-Disk{
    param(
        [Parameter(Mandatory,
        ValueFromPipeline,
        ValueFromPipelineByPropertyName)]
        [VMware.VimAutomation.ViCore.Impl.V1.Inventory.VMHostImpl]$VMHost,

        [string]$CanonicalName
    )
    $storSys = Get-View $VMHost.Extensiondata.ConfigManager.StorageSystem
    $lunUuid = ($storsys.storagedeviceinfo.scsilun | ? CanonicalName -eq $CanonicalName).Uuid
    $storSys.DetachScsiLun($lunUuid)
}
Function Move-FFBFSMORoles {
    [CmdletBinding()]
    Param (
        [ValidateSet('DC1','DC2')]
        $Destination,
        
        [ValidateSet('PDC','RID','Infrastructure','Domain','Schema','All')]
        [string[]]$Roles,
        [ValidateSet('myDomain.local','corp.mydomain.local','ALL')]
        [string[]]$Domain = 'ALL'
    )
    
    Begin {
            switch ($Roles)
            {
                'PDC' {$DomainFSMO=0}
                'RID' {$DomainFSMO=1}
                'Infrastructure' {$DomainFSMO=2}
                'Domain' {$ForestFSMO=4}
                'Schema' {$ForestFSMO=3}
                'All' {
                    $ForestFSMO=3,4
                    $DomainFSMO=0,1,2
                }
            }
        }
    Process{
        
        if ($PSBoundParameters['Lightbound']) {
        
            $mydomaindc = Get-ADDomainController -Server DC2.mydomain.local
            $corpdc = Get-ADDomainController -Server DC2.corp.mydomain.local
        }
    
    
        if ($PSBoundParameters['CyrusOne']){
            $mydomaindc = Get-ADDomainController -Server DC1.mydomain.local
            $corpdc = Get-ADDomainController -Server DC1.corp.mydomain.local
        }
   
        $me = get-aduser "$env:USERNAME"

        Add-ADGroupMember -Identity 'Schema Admins' -Members $me -Server mydomain.local
        klist purge
        if ($Domain -eq 'All') {

            Move-ADDirectoryServerOperationMasterRole -Identity $corpdc -OperationMasterRole $DomainFSMO

            Move-ADDirectoryServerOperationMasterRole -Identity $mydomaindc -OperationMasterRole $DomainFSMO

            Move-ADDirectoryServerOperationMasterRole -Identity $mydomaindc -OperationMasterRole $ForestFSMO
        } 
        
        Remove-ADGroupMember -Identity 'Schema Admins'  -Members $me -Server mydomain.local
    }
}
function Start-Monitor {
      
      #Requires -Version 2.0            
      [CmdletBinding()]            
      Param             
      (                       
            [Parameter(Position=0,                         
                       ValueFromPipeline=$true,            
                       ValueFromPipelineByPropertyName=$true)]
            [String[]]$ComputerName = $env:COMPUTERNAME,        
            
            # Switch to Enable Email Notifications on First Down
            [Switch]$notifyonServerDown,
            
            # Switch to Enable Email Notifications on Server Online
            [Switch]$notifyonServerBackOnline,
            
            # Switch to Enable Email Notifications on MaxOutageCount
            [Switch]$notifyonMaxOutageCount,
            
            # Switch to Enable all notifications
            [Switch]$notifyAll,

            # specify the time you want email notifications resent for hosts that are down
            $EmailTimeOut = 30,
            # specify the time you want to cycle through your host lists.
            $SleepTimeOut = 5,
            # specify the maximum hosts that can be down before the script is aborted
            $MaxOutageCount = 100,
            
            # specify who gets notified 
            $tonotification = "user@domain.org", 
            # specify where the notifications come from 
            $fromnotification = "admin@domain.org", 
            # specify the SMTP server 
            $smtpserver = "relay.domain.org",
            
            # reset the lists of hosts prior to looping
            $OutageHosts = @(),
            
            #ping from a remote machine
            [Parameter(ParameterSetName='Remote')]
            $SourceMachine
                      
      )#End Param
 
 # Use end block, to ensure all computers are read in at once, even by pipeline    
 Begin {} 
 end {     
      if ($notifyAll)
      {
            $notifyonMaxOutageCount,$notifyonServerBackOnline,$notifyonServerDown =  $True,$True,$True
      }

      Write-Verbose -Message "computername: $computername"
      Write-Verbose -Message "notifyonMaxOutageCount: $notifyonMaxOutageCount"
      Write-Verbose -Message "notifyonServerBackOnline: $notifyonServerBackOnline"
      Write-Verbose -Message "notifyonServerDown: $notifyonServerDown"

      # Allow
      if ( $Input )
      {
            Write-Verbose -Message "Input: $Input"
            $ComputerName = $Input
      }
      
      # start looping here
      Do{
            ipconfig /flushdns
            $available = @()
            $notavailable = @()
            Write-Host (Get-Date)
            
            # Read the File with the Hosts every cycle, this way to can add/remove hosts
            # from the list without touching the script/scheduled task, 
            # also hash/comment (#) out any hosts that are going for maintenance or are down.
            $ComputerName | Where-Object {!($_ -match "#")} | 
            ForEach-Object {
                  if(Test-Connection -ComputerName $_ -Count 1 -ErrorAction SilentlyContinue)
                  {
                        # if the Host is available then write it to the screen
                        write-host "Available host ---> "$_ -BackgroundColor Green -ForegroundColor White
                        [String[]]$available += $_
                        
                        # if the Host was out and is now backonline, remove it from the OutageHosts list
                        if ($OutageHosts -ne $Null)
                        {
                              if ($OutageHosts.ContainsKey($_))
                              {
                                    $OutageHosts.Remove($_)
                                    $Now = Get-date
                                    if ($notifyonServerBackOnline)
                                    {
                                          $Body = "$_ is back online at $Now"
                                          Send-MailMessage -Body "$body" -to $tonotification -from $fromnotification `
                                          -Subject "Host $_ is up" -SmtpServer $smtpserver
                                    }
                                    
                              }
                        }  
                  }
                  else
                  {
                        # If the host is unavailable, give a warning to screen
                        write-host "Unavailable host ------------> "$_ -BackgroundColor Magenta -ForegroundColor White
                        if(!(Test-Connection -ComputerName $_ -Count 2 -ea silentlycontinue))
                        {
                              # If the host is still unavailable for 4 full pings, write error and send email
                              write-host "Unavailable host ------------> "$_ -BackgroundColor Magenta -ForegroundColor White
                              [Array]$notavailable += $_
                              
                              if ($OutageHosts -ne $Null)
                              {
                                    if (!$OutageHosts.ContainsKey($_))
                                    {
                                          # First time down add to the list and send email
                                          Write-Host "$_ Is not in the OutageHosts list, first time down"
                                          $OutageHosts.Add($_,(get-date))
                                          $Now = Get-date
                                          if ($notifyonServerDown)
                                          {
                                                $Body = "$_ has not responded for 5 pings at $Now"
                                                Send-MailMessage -Body "$body" -to $tonotification -from $fromnotification `
                                                -Subject "Host $_ is down" -SmtpServer $smtpserver
                                          }
                                    }
                                    else
                                    {
                                          # If the host is in the list do nothing for 1 hour and then remove from the list.
                                          Write-Host "$_ Is in the OutageHosts list"
                                          if (((Get-Date) - $OutageHosts.Item($_)).TotalMinutes -gt $EmailTimeOut)
                                          {$OutageHosts.Remove($_)}
                                    }
                              }
                              else
                              {
                                    # First time down create the list and send email
                                    Write-Host "Adding $_ to OutageHosts."
                                    $OutageHosts = @{$_=(get-date)}
                                    $Now = Get-date
                                    if ($notifyonServerDown)
                                    {
                                          $Body = "$_ has not responded for 5 pings at $Now"
                                          Send-MailMessage -Body "$body" -to $tonotification -from $fromnotification `
                                          -Subject "Host $_ is down" -SmtpServer $smtpserver
                                    }
                              } 
                        }
                  }
            }
            # Report to screen the details
            Write-Host "Available count:"$available.count
            Write-Host "Not available count:"$notavailable.count
            if ($OutageHosts)
            {
                  Write-Host "Not available hosts:"
                  $OutageHosts
            }
            Write-Host ""
            Write-Host "Sleeping $SleepTimeOut seconds"
            Start-Sleep -Seconds $SleepTimeOut
            if ($OutageHosts.Count -gt $MaxOutageCount)
            {
                  # If there are more than a certain number of host down in an hour abort the script.
                  $Exit = $True
                  $body = $OutageHosts | Out-String
                  
                  if ($notifyonMaxOutageCount)
                  {
                        Send-MailMessage -Body "$body" -to $tonotification -from $fromnotification `
                        -Subject "More than $MaxOutageCount Hosts down, monitoring aborted" -SmtpServer $smtpServer
                  }
            }
      }
      while ($Exit -ne $True)
}#End     
}#Start-Monitor
Function Set-WinVMIP {
    [CmdletBinding(SupportsShouldProcess)]
    Param 
    (
        [string]$ComputerName, 
        [PSCredential]$HostCredential,
        [PSCredential]$GuestCredential, 
        [string]$IPAddress, 
        [string]$SubnetMask = '255.255.255.0',
        [string]$Gateway,
        [string[]]$DNSServers,
        [string]$Vcenter,
        # netsh is deprecated, it requires knowing the name of the interface to function correctly, powershell is more flexible and uses WMI to find the NIC
        [ValidateSet("netsh","powershell")]
        $Method,
        $From,
        [pscredential]$FromCredential
    )
    Begin {
        $powershell = @'
            $DNSServerSearchOrder = "10.17.10.20","10.17.10.10"
            $wmiNet = Get-WmiObject win32_networkadapterconfiguration -Filter "ipenabled = 'true' AND (ServiceName like 'vmx%' OR ServiceName like 'E1%')"
            if ($wmiNet.Count -ge 2) {
                Write-Output "$env:COMPUTERNAME has multiple NIC's, choosing $wmiNet[0]"
                $wmiNet = $wmiNet[0]
            }

            $wminet.EnableStatic("#IP#", "#Subnetmask#")

            $wminet.SetGateways("#Gateway#", 1)

            $wminet.SetDNSServerSearchOrder($DNSServerSearchOrder)

            ipconfig /registerdns
'@
        if (-not ($DefaultVIServers) ) {
            $oldwarningpreference = $WarningPreference
            $WarningPreference = 'SilentlyContinue'
            Connect-VIServer $Vcenter | out-null
            $WarningPreference = $oldwarningpreference
        }
        
    }
    Process {
        switch ($method)
        {
            'netsh' {
                $script = $netsh = "c:\windows\system32\netsh.exe interface ip set address ""Local Area Connection"" static $IPAddress $SubnetMask $Gateway 0 && netsh interface ip set dns name=""Local Area Connection"" static $DNSServer1 && netsh interface ip add dns name=""Local Area Connection"" $DNSServer2 index=2 && ipconfig /registerdns"
                $type = 'bat'
            }
            'powershell' {
                $script = $powershell.Replace('#IP#',$IPAddress).Replace('#Subnetmask#',$SubnetMask).Replace('#Gateway#',$Gateway)
                $type = 'powershell'
            }
           
        }
        
        
        if ($pscmdlet.ShouldProcess($ComputerName,"Change IP address")){
            Write-Verbose "Setting IP address for $ComputerName..."
            try{
                Invoke-VMScript -VM $ComputerName -HostCredential $HostCredential -GuestCredential $GuestCredential -ScriptType $type -ScriptText $script -ErrorAction stop -Server $Vcenter -RunAsync
                # Ping until the above invoke-command takes the computer offline
                $tries = 2
                <#
                Do
                {
                    #$ping = Test-Connection -ComputerName $IPAddress -Quiet -Count 2
                    $ping = Test-Connection -ComputerName $IPAddress -Source $From -Credential $FromCredential -Count 2
                    Write-Verbose "$ComputerName $IPAddress"
                    if ($ping)
                    {
                        Write-Output "$ComputerName : IP changed successfully!"
                        Break
                    }
                    $tries --
                if ($tries -lt 1)
                    {Write-Warning 'IP address was not successfully changed, moving on'}

                }While($tries -gt 0)
                #>
            }Catch{
                Write-Error "$($_.Exception.Message) - Line Number: $($_.InvocationInfo.ScriptLineNumber)"
            }
        }
    }
}
