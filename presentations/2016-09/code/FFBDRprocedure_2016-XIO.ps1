ipmo \\rsc.first.int\DFS_OC\users\jryan\scripts\3rdParty\Modules\MTSXtremIO 
ipmo \\rsc.first.int\DFS_OC\users\jryan\scripts\3rdParty\Modules\Posh-RecoverPoint 

Connect-RPAppliance -Name recoverpoint-dc -Credentials (Get-Credential -Credential admin) -ignorecert -Verbose 

<# !!!Testing!!!
$rpsnap = Get-RPImage -CGName vr1esx -ClusterName Lightbound -CGCopyName Lightbound-copy1 | select -Last 1
$rpsnap | Enable-RPImageAccess -Newest -WhatIf
Get-RPGroupUID | Get-RPGroupLink | where {$_.localLink -eq $false} | %{$_ | Get-RPGroupCopy} | %{$_ | Get-RPImage | select -Last 1 } | Enable-RPImageAccess -WhatIf
#>

                                                                                                                                                                                                                                  
New-PasswordFile -Path 'V:\' -Filename XIOpwfile.txt                                                                                                           
#Get-PasswordFromFile -FullPath V:\XIOpwfile.txt                                                                                                                                                                                                                                                                             
Disable-CertificateValidation -Verbose                                                                                                                          
Set-XIOAPIConnectionInfo -Username 'hq\jryana' -PasswordFile V:\XIOpwfile.txt -Hostname er2xio01.hq.first.int -Verbose                                          
$xiovolumes = Get-XIOVolume                                                                                                                                     
$xiovolumes | where {$_.Name -like '*copy1'} | select name  
