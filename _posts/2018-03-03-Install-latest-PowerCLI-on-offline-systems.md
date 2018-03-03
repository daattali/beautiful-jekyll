---
layout: post
published: true
title: Install the latest PowerCLI on offline systems
---

![powercli.png]({{site.baseurl}}/img/powercli.png)

If you keep your PowerCLI up to date you may have noticed that since version 6.5.1 you can't download the installer on the VMware website anymore. This being because VMware moved the distribution of PowerCLI to Powershell Gallery using the cmdlets ```Install-Module```, ```Uninstall-Module``` and ```Save-Module```.

At the time of the writing of this article we are at version 10.0.0. VMware made a big jump in version number from 6.5.4 I think because they released compatibility for OS X (other than that a 6.5.5 would have done it justice just fine).

Anyway, the version 6.5.1 that changed the install method actually brought some cool modifications:

> Removed the MSI file for installing VMware PowerCLI. All modules are now available in the PowerShell Gallery.

> Removed the desktop icons for launching VMware PowerCLI. It is recommended that you launch PowerShell or your chosen PowerShell-enabled script editor (...) to work with VMware PowerCLI.

> Altered the VMware PowerCLI modules to enable automatic loading of modules that are loaded into a registered PowerShell modules folder. The use of Import-Module is no longer required in scripts or profiles to import the modules. All cmdlets will be automatically loaded when used in your PowerShell session.

That last one is a godsend by the way, it will speed up my profile so much since the disruptive [6.5 R1](http://www.vxav.fr/2016-11-22-import-powercli-6-5-module-and-keep-custom-prompt/)!

You can find more information in the [PowerCLI Changelog page](https://www.vmware.com/support/developer/PowerCLI/changelog.html).

### Requirements

- Powershell 3.0 minimum is needed. 

Note that if you are running 3.0 or 4.0 you need to install the PowerShellGet and PackageManagement modules (Maybe it's time to update?). more info [here](https://blogs.msdn.microsoft.com/powershell/2016/09/29/powershellget-and-packagemanagement-in-powershell-gallery-and-github/).

- Uninstall any pre-6.5 R1 PowerCLI installation.

### Install PowerCLI online

```
Install-Module VMware.PowerCLI -Scope CurrentUser -AllowClobber
```

The Hyper-V module contains commands with the same name as some of the PowerCLI ones (Get-VM, Get-VMHost, ...), the _AllowClobber_ parameter allows these duplicates to co-exist.

You can drop the _scope_ parameter if you run it as administrator. The modules will be stored in C:\Program Files\WindowsPowerShell\Modules instead of your profile and will be available to all users.

### Install PowerCLI offline

So it brings us to where this post came from. What do you do if you need PowerCLI on a machine that is not connected to internet?

Again, if an installation of PowerCLI pre-6.5 R1 exists on this computer you need to uninstall it.

- Download the module on a computer connected to internet

```
Save-Module VMware.PowerCLI -Path $env:userprofile\PowerCLI-vXXX
```

- Copy it to your computer that is isolated from internet with a USB, share or whatever works.

- Copy all the PowerCLI folders to : $env:userprofile\Documents\WindowsPowerShell\Modules

If you have permission and want it available to all users you can also place it in C:\Program Files\WindowsPowerShell\Modules

### Update PowerCLI

This section only concerns version 6.5.1 and newer.

Like VMware states in the doc, you could use the Update-Module cmdlet but it won't remove the existing version or deprecated ones. More info [there](https://vdc-download.vmware.com/vmwb-repository/dcr-public/a5963bb3-674c-4fb1-92aa-df896e3b4758/ad921b7b-3e4f-4404-b98b-b6c4aa53f152/vmware-powercli-651-user-guide.pdf).

The recommended way to update is as follow:

```Powershell
Get-Module VMware.* -ListAvailable | Uninstall-Module -Force

Install-Module VMware.PowerCLI
```

If your system is offline, just delete the PowerCLI module folders and copy the new ones instead.
