---
layout: post
published: false
title: How to silence VSAN health checks
---
The VSAN health checks are great in vCenter to quickly notice when something wrong is going on. However there may be some of the health checks that you don't want to come up as warning. As an example,  lots of vCenter implementations don't have access to internet by design and when it is the case the Health check "VSAN Build Recommendation Engine Health" will be in a warning state even though you don't care. As of vCenter 6.5 u1 it is currently not possible to silence a check in web client, the only way to do it is [via the VsanHealthSetVsanClusterSilentChecks method in the API](https://code.vmware.com/apis/217/vsan#/doc/vim.cluster.VsanVcClusterHealthSystem.html#getVsanClusterSilentChecks). Note that the VSAN API was made available in **PowerCLI 6.5.1 and above** so if you are still running an older version you will need to upgrade by uninstalling PowerCLI and downloading the module, [more info here](http://www.vxav.fr/2018-03-03-Install-latest-PowerCLI-on-offline-systems/).

I used this use case as an opportunity to play with the API so I wrote a short 4 functions module. I will probably expand it over time.

- Get-VsanHealthChecks : Display VSAN health checks with their current health.
- Get-VsanHealthGroups : Display VSAN health groups with their current health.
- Get-VsanHealthSilentCheck : Display the silenced health checks.
- Set-VsanHealthSilentCheck : Silence or unsilence a health check.

## Silence a VSAN health Check

First you need to import the module.

- Import-Module VSAN-HealthChecks.psm1

Find the Id of the check you want to silence. Mine is in Yellow state so I filter using it.

- Get-VsanHealthChecks -Cluster (get-cluster) -Health "yellow"

Pick the one you want to silence and use the **TestId** property to silence it. The output should be the updated list of silenced checks including the one specified above.

- Set-VsanHealthSilentCheck -Cluster (get-cluster) -TestId vumconfig -CheckState Silence

You can run the command to display Health checks with the **DontFetchFromCache** switch enabled to re-run the test. The health check should now be in state **Skipped**.

- Get-VsanHealthChecks -Cluster (get-cluster) -DontFetchFromCache

