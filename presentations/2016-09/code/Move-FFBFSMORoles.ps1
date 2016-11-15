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


   

    

    
    

    

       

    