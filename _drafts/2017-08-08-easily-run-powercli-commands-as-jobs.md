---
layout: post
published: false
title: Easily run PowerCLI commands as jobs
---
## Overview

Running PowerCLI jobs is not as straightforward as it is with regular Powershell commands. If you try to run  a command that requires to be connected to a vCenter you will receive an error saying that the command is not recognized.

Start a job to get datastores.  
![job-ds-fail-1.jpg]({{site.baseurl}}/img/job-ds-fail-1.jpg)

Wait for the job to finish and place the result into the $ds variable.  
![job-ds-fail-2.jpg]({{site.baseurl}}/img/job-ds-fail-2.jpg)

This error occurs because the job create creates a new session which is not connected to vCenter and doesn't even have the PowerCLI module loaded. 

In order to run PowerCLI commands in parallel you need to import the module and connect to vCenter for every job. One easy way to connect to vCenter when you already have a session is to re-use the **SessionSecret** property of the **$DefaultVIServer** variable created when you logged in vCenter.

```Powershell
PS> $global:DefaultVIServer | Select *


IsConnected   : True
Id            : /VIServer=**********\xavier@*******:443/
ServiceUri    : https://*******/sdk
SessionSecret : "4e4c6c1a00349b3c9ef28b0a031b5a3ce4a1d790"    <<=====
Name          : **********
Port          : 443
SessionId     : "4e4c6c1a00349b3c9ef28b0a031b5a3ce4a1d790"
User          : **********\xavier
Uid           : /VIServer=**********\xavier@**********:443/
Version       : 6.0
Build         : 3634793
ProductLine   : vpx
InstanceUuid  : fe7a8d6c-65a7-4d02-9ed2-7f51b1128042
RefCount      : 1
ExtensionData : VMware.Vim.ServiceInstance
Client        : VMware.VimAutomation.ViCore.Impl.V1.VimClient
```

## Start-PowerCLIJob

