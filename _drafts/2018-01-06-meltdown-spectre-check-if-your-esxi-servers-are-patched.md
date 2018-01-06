---
layout: post
published: false
title: Meltdown & Spectre - Check if your ESXi servers are patched
---
There has been a lot of noise recently regarding the 2 major flaws, **Spectre** and Meltdown, uncovered affecting mainly Intel CPUs. The flaws are apparently very difficult to exploit which makes a leak coming from there an unlikely scenario but who knows? No one likes to have a somewhat vulnerable system so let's treat it as so.

Spectre and Meltdown can have an impact to various degrees regarding your system/infra. Here we talk about virtualisation, to explain in a nutshell I will quote a [post by El Reg'](https://www.theregister.co.uk/2018/01/04/intel_amd_arm_cpu_vulnerability/).

> On a shared system, such as a public cloud server, it is possible, depending on the configuration, for software in a guest virtual machine to drill down into the host machine's physical memory and steal data from other customers' virtual machines.

I won't get into the details of these because 1) I don't have the knowledge to 2) There are already a million good articles about it online. I recommend having a read at this [post by Frank Denneman quoting Graham Sutherland](http://frankdenneman.nl/2018/01/05/explainer-spectre-meltdown-graham-sutherland/), I have to admit that a lot of it is chinese to me.

## VMware patch

The patches only address CVE-2017-5753 and CVE-2017-5715 which correspond to "Spectre". Meltdown (CVE-2017-5754) does not affect ESXi.

> A third issue due to speculative execution, Rogue Data Cache Load (CVE-2017-5754), was disclosed along the other two issues. It does not affect ESXi, Workstation, and Fusion because ESXi does not run untrusted user mode code, and Workstation and Fusion rely on the protection that the underlying operating system provides.

[Source](https://blogs.vmware.com/security/2018/01/vmsa-2018-0002.html)

Here is the security bulleting by VMware in which you will find the patches IDs, the CVEs and some other useful stuff: [https://www.vmware.com/us/security/advisories/VMSA-2018-0002.html](https://www.vmware.com/us/security/advisories/VMSA-2018-0002.html)

-**ESXi 6.5 : ESXi650-201712101-SG**
-**ESXi 6.0 : ESXi600-201711101-SG**
-**ESXi 5.5 : ESXi550-201709101-SG**

The 5.5 patch has remediation against CVE-2017-5715 but not against CVE-2017-5753.

## Identify if your ESXi hosts are patched

The point of this short post is to give you a quick and easy way to check if the patch is installed on your servers.

Note that you will need Powercli version 6.3R1 or higher as I make use of the "Get-ESXCLI -V2" cmdlet (earlier version don't have a v2 switch that offers a better syntaxe to deal with esxcli).

Connect to your vCenter in PowerCLI and paste the following script in your prompt. It will output a table of your hosts with their version number and if the vibs included in the VMware patches are installed.

```Powershell
foreach ($VMHost in (Get-VMHost |where powerstate -eq "PoweredOn")) {

    $esxcliv2 = Get-EsxCli -VMHost $VMHost -V2

    if ($VMHost.version -eq "6.5.0") {
    
        foreach ($patch in "VMware_bootbank_esx-base_6.5.0-1.33.7273056","VMware_bootbank_esx-tboot_6.5.0-1.33.7273056","VMware_bootbank_vsan_6.5.0-1.33.6852403","VMware_bootbank_vsanhealth_6.5.0-1.33.6852404") {

            if ($esxcliv2.software.vib.list.Invoke() | where ID -eq $patch) {[pscustomobject]@{Host=$vmhost.name;version=$VMHost.version;patch=$patch;status="Installed"}}
            else {[pscustomobject]@{Host=$vmhost.name;patch=$patch;status="Not Installed"}}

        }

    } elseif ($VMHost.version -eq "6.0.0") {

        foreach ($patch in "VMware_bootbank_esx-base_6.0.0-3.76.6856897","VMware_bootbank_vsan_6.0.0-3.76.6769077","VMware_bootbank_vsanhealth_6.0.0-3000000.3.0.3.76.6769078") {

            if ($esxcliv2.software.vib.list.Invoke() | where ID -eq $patch) {[pscustomobject]@{Host=$vmhost.name;version=$VMHost.version;patch=$patch;status="Installed"}}
            else {[pscustomobject]@{Host=$vmhost.name;patch=$patch;status="Not Installed"}}

        }

    } elseif ($VMHost.version -eq "5.5.0") {

        foreach ($patch in "VMware_bootbank_esx-base_5.5.0-3.103.6480267") {

            if ($esxcliv2.software.vib.list.Invoke() | where ID -eq $patch) {
                [pscustomobject]@{Host=$vmhost.name;version=$VMHost.version;patch=$patch;status="Installed"}
                Write-Warning "Doesn't include remediation for CVE-2017-5753"}
            else {[pscustomobject]@{Host=$vmhost.name;patch=$patch;status="Not Installed"}}

        }
        

    } else {Write-Warning "No patch released for ESXi version $($VMHost.version) as of 2018/01/06"}

}
```

The result looks like the following for a patched ESXi 5.5.

![spectre-5.5.jpg]({{site.baseurl}}/img/spectre-5.5.jpg)

for a patched ESXi 6.5.

![spectre-6.5.jpg]({{site.baseurl}}/img/spectre-6.5.jpg)

If you don't have the patches it will simply display "Not Installed" instead.

## What to do now?

Well, it's time to log back in vSphere Update Manager and patch your systems with the patches mentionned earlier.

If you are more of a CLI guys you can download the patches [there](https://my.vmware.com/group/vmware/patch). Log in and search for the patch ID.