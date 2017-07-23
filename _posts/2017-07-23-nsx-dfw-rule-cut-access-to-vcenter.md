---
layout: post
published: true
title: NSX DFW rule - lost access to vCenter
---
I was playing with NSX recently and testing the distributed firewall (DFW) that allows for east-west firewalling, aka micro-segmentation.

All was going well when I disconnected my brain for a second and added a rule "deny all all" (Yes I know...). Following that moment facepalm I obviously lost access to the vCenter so I could not remove my rule. I basically cut the tree branch I was sitting on.

![facepalm.jpg]({{site.baseurl}}/img/facepalm.jpg)

**Best practice is to have your vCenter server included in the exclusion list!**

Obviously I didn't. VMware actually has a KB for that issue, 2017 so I must not be the first one: [2079620](https://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=2079620)

The only easy fix at the moment is to delete the configuration of the ditributed firewall via the [REST API](https://pubs.vmware.com/NSX-6/topic/com.vmware.ICbase/PDF/nsx_604_api.pdf "vSphere REST API doc (pdf)") to regain access to the vCenter. I find this fix a little bit clumsy coming from VMware. I am only running a lab so I don't really care but I can only imagine the furious sweating if someone pushed that rule in prod... In such case you don't really want to go digging in the doc and get a REST client running and fiddle with the self-signed certificate settings. Actually I'm glad I did that mistake here!

**Feature request to VMware: Implement a roll back mecanism or a warning message please.**

So here's what we're going to do:

1. Reset firewall configuration via REST API.
2. Include vCenter server in the exclusion list.
3. Restore last firewall configuration.

## 1: Reset firewall configuration via REST API

You can easily do it with Curl, Chrome or Firefox but I wrote a few lines in powershell to simplify the process even more for those who ended up on this page. It will be as long as a copy/paste.

- Just Copy and paste the following into Powershell. It will prompt for the IP and credentials of **NSX Manager**.

```Powershell
$NSXmgrIP = Read-Host "Enter IP or FQDN of NSX Manager"

$creds = Get-Credential -Message "NSX Manager credentials"

$bytes = [System.Text.Encoding]::UTF8.GetBytes("$($Creds.UserName):$($Creds.GetNetworkCredential().password)")

$Base64 = [System.Convert]::ToBase64String($bytes)

$header = @{Authorization= "Basic $Base64"}

$uri = "https://$NSXmgrIP/api/4.0/firewall/globalroot-0/config"

Write-warning "Delete firewall configuration? (y/n)"

$confirm = read-host " "

if ($confirm -eq "y") {
    Invoke-RestMethod -Method Delete -Uri $uri -Headers $header
    write-warning "Log in vCenter > Add vCenter to the exclusion list > restore the latest firewall configuration backup > Publish"
}
```

The output should be blank and you should have access to vCenter again.

## 2: Include vCenter server in the exclusion list.

- Log in vCenter and browse to "NSX Manager" configuration in the "Exclusion list" tab.

- Click on the green "+" sign and add your vCenter VM. From now on it will be ignored by the firewall.

![nsx-load-config0.jpg]({{site.baseurl}}/img/nsx-load-config0.jpg)

## 3: Restore last firewall configuration.

- Browse to the firewall section of NSX
- The firewall rules list will be back to the default one - no worries
- Click on the "Load saved configuration" button above the list

![nsx-load-config.jpg]({{site.baseurl}}/img/nsx-load-config.jpg)

- Select the latest config (the one containing your genius rule) and click "Load"

![nsx-load-config2.jpg]({{site.baseurl}}/img/nsx-load-config2.jpg)

- A warning message is displayed "_This will replace the current configuration. All the unsaved changes made on current configuration will be lost. Yes to continue_". Click "Yes". The configuration is then loaded but not published.

![nsx-load-config3.jpg]({{site.baseurl}}/img/nsx-load-config3.jpg)

- Publish the changes.

![nsx-load-config4.jpg]({{site.baseurl}}/img/nsx-load-config4.jpg)

All your rules are now back and vCenter won't be impacted anymore.

Conclusion, don't be like me and double check every single rule before publishing. Especially in prod !!
