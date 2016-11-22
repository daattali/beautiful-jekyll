---
layout: post
published: false
title: PowerCLI 6.5 broke my Powershell custom prompt!
---
_This blog post applies only if you have a customized Powershell prompt.  
Function Prompt { ... } in Microsoft.PowerShell_profile.ps1_

---------

My Powershell profile has a few different things including:
- A function to add the VMware core snapin and connect quickly to a vCenter.
- A function to customize the prompt with separator and display of the connected vCenter.

![cvc-tf-vcenter.png]({{site.baseurl}}/img/cvc-tf-vcenter.png)

These are very usefull to have as I spend quite a lot of time on PowerShell to make things quicker and clearer.

## Good bye VMware snapin

When I upgraded to [PowerCLI 6.5 R1](http://blogs.vmware.com/PowerCLI/2016/11/new-release-powercli-6-5-r1.html) I noticed that the connection to vCenter failed with the error ```The Windows PowerShell snap-in 'VMware.VimAutomation.Core' is not installed on this computer.```.

![no-snapin.png]({{site.baseurl}}/img/no-snapin.png)

After investigation it appears that the snapins can't be used anymore for PowerCLI. Now we have to use the modules (which is the proper way to do). 

- **NO :** ```Add-PSSnapin VMware.VimAutomation.Core```
- **YES:** ```Import-Module VMware.VimAutomation.Core```

## Hello cheeky module

However I ran into a problem when I imported the module. My prompt was reset/modified by it, which is really annoying.

![Import-prompt-go.png]({{site.baseurl}}/img/Import-prompt-go.png)

The problem with that module is that the custom prompt is loaded at the start of PowerShell, so if you Import the module after customizing the prompt (which is in the profile), it overrides it as seen in the previous screenshot.

A fix is to Import the module in your PowerShell profile before the prompt, even when you don't plan on connecting to a vCenter.

- **Before**: Start Powershell > customize Prompt > "Connect-vCenter" func > Add pssnapin > Connect vCenter
- **After** : Start Powershell > Import module > customize Prompt > "Connect-vCenter" func > Connect vCenter

The start time of powershell is a little bit slower due to it but the advantage is that you keep your custom profile and the module is ready to use should you need it. I actually timed the start of powershell with and without the module imported and the difference is under a second. I can live with it.

![Powershell-time-start.png]({{site.baseurl}}/img/Powershell-time-start.png)

## Conclusion

Import the VMware modules before customizing the prompt in your Powershell profile.

_Example for %UserProfile%\Documents\WindowsPowerShell\Microsoft.PowerShellprofile.ps1_

![MyCustomPrompt.png]({{site.baseurl}}/img/MyCustomPrompt.png)

```Powershell

# Function to import powercli and connect to vsphere server

Import-Module VMware.VimAutomation.Core

function Connect-vCenter {

    param(
        [parameter(position=0)][String]$Server = "MyDefault-vCenter",
        [Parameter(Position=1)][PSCredential]$Credential = "MyDomain\MyDefaultUser",
        [parameter()][String]$Protocol = "https"
    )
    
    $params = @{
        Server = $Server
        Protocol = $Protocol
    }

    if ($Credential) {$params.Add('Credential',$Credential)}

    Connect-VIServer @params 3>&1 | Out-Null
  
  }
  
Function Prompt {

    Write-Host ""

    IF ($global:DefaultVIServer) {
        Write-Host "[$($global:DefaultVIServer.name)]" -NoNewline -ForegroundColor green
    }

    Write-Host "$((Get-location).Path) $('-' * $Width)" -ForegroundColor red

    "My Custom Prompt:) "
   
}

```
