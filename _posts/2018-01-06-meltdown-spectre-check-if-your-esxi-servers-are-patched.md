---
layout: post
published: true
title: Meltdown & Spectre - Check if your ESXi servers are patched
---
### [Update 20/03/2018]

VMware now recommends to apply the patch for Hypervisor-Assisted Guest Mitigation. According to them the performance impact is [less than 2%](https://kb.vmware.com/s/article/52337).

I haven't patched yet and I will wait for the feedback of early adopters. The start of the year has been so ridiculous with patches being rolled back every week because they broke more things than they fixed. So wait and see.

### [Update 15/01/2018]

A few days ago VMware release the Security Advisory [VMSA-2018-0004](https://www.vmware.com/us/security/advisories/VMSA-2018-0004.html) and [KB52085](https://kb.vmware.com/s/article/52085) regarding _Hypervisor-Assisted Guest Remediation_ that would present the new CPU features to the VMs even without having the Firmware/Bios updated.

One or 2 days later, because of sightings for a number of Intel Haswell and Broadwell processors Intel recommends VMware to not issue the patches associated with VMSA-2018-0004 and recommends customers who may have already installed them on their hosts to mask the newly presented features.  
Vmware immediately issued an update to the security advisory pointing to [KB52345](https://kb.vmware.com/s/article/52345) that explains it all.

If you have already patched your hosts with the KB52085 and your CPUs are in the list of affected models, refer to the directions in the KB. Alternatively you can have a look at [William Lam's post](https://www.virtuallyghetto.com/2018/01/automating-intel-sighting-remediation-using-powercli-ssh-not-required.html) that will help you automate it.

Note that the patching for _Hypervisor-Specific Mitigation_ (VMSA-2018-0002) is still recommended to install.

> For ESXi hosts that have not yet applied one of the following patches ESXi650-201801402-BG, ESXi600-201801402-BG, or ESXi550-201801401-BG, VMware recommends not doing so at this time. It is recommended to apply the patches listed in VMSA-2018-0002 instead.

[Note2](https://www.virtualizationhowto.com/2018/01/vmware-performance-impact-of-meltdown-and-spectre-patches/): I link this good post in which they load test different patching scenarios and discover that performances are heavily impacted when the host is patched (VMSA-2018-0004) **and** the guest OS is patched.

In short, it's ok to patch for VMSA-2018-0002, don't patch for VMSA-2018-0004, I won't get into the guest OS patching as it is a "it depend". And most importantly, when a new patch is release by Intel, Microsoft, VMware or XYZ: **WAIT !**

------------

## Meltdown & Spectre - Check if your ESXi servers are patched

There has been a lot of noise recently regarding the 2 major flaws, **Spectre** and **Meltdown**, uncovered affecting mainly Intel CPUs. The flaws are apparently very difficult to exploit which makes a leak coming from there an unlikely scenario but who knows? No one likes to have a somewhat vulnerable system so let's treat it as so.

_**Note that Meltdown does not affect ESXi**_

Spectre and Meltdown can have an impact of various degrees regarding your system/infra. Here we talk about virtualisation, to explain in a nutshell I will quote a [post by El Reg'](https://www.theregister.co.uk/2018/01/04/intel_amd_arm_cpu_vulnerability/).

> On a shared system, such as a public cloud server, it is possible, depending on the configuration, for software in a guest virtual machine to drill down into the host machine's physical memory and steal data from other customers' virtual machines.

I won't get into the details of these because 1) I don't have the knowledge 2) There are already a million good articles online, the added value here is the focus on ESXi. Though I recommend having a read at this [post by Frank Denneman quoting Graham Sutherland](http://frankdenneman.nl/2018/01/05/explainer-spectre-meltdown-graham-sutherland/), even though I have to admit that a lot of it was chinese to me...

## VMware patch

The patches were released by VMware in 2017 and only address "Spectre" (CVE-2017-5753 and CVE-2017-5715). ESXi is not affected by "Meltdown" (CVE-2017-5754).

> A third issue due to speculative execution, Rogue Data Cache Load (CVE-2017-5754), was disclosed along the other two issues. It does not affect ESXi, Workstation, and Fusion because ESXi does not run untrusted user mode code, and Workstation and Fusion rely on the protection that the underlying operating system provides.

[Source](https://blogs.vmware.com/security/2018/01/vmsa-2018-0002.html)

Here is the security bulleting by VMware in which you will find the patches IDs, the CVEs and some other useful stuff: [https://www.vmware.com/us/security/advisories/VMSA-2018-0002.html](https://www.vmware.com/us/security/advisories/VMSA-2018-0002.html)

**Patch IDs**

-**ESXi 6.5 : ESXi650-201712101-SG**

-**ESXi 6.0 : ESXi600-201711101-SG**

-**ESXi 5.5 : ESXi550-201709101-SG**

_The 5.5 patch has remediation against CVE-2017-5715 but not against CVE-2017-5753._

## Identify if your ESXi hosts are patched

The point of this quick post is to give you a quick and easy way to check if the patch is installed on your servers.

Note that you will need Powercli version 6.3R1 or higher as I make use of the "Get-ESXCLI -V2" cmdlet (earlier version don't have a v2 switch that offers a better syntaxe to deal with esxcli).

Connect to your vCenter in PowerCLI and paste the following script in your prompt. It will output a table of your hosts with their version number and if the vibs contained in the VMware patch are installed.

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

If you are more of a CLI bloke you can download the patches [there](https://my.vmware.com/group/vmware/patch) and install them on your servers. Just log on with your VMware account and search for the patch ID.
