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

