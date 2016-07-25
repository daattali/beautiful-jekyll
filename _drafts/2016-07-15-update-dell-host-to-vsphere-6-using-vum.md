---
layout: post
published: false
title: Update Dell host to vSphere 6 using VUM
---
In this post I will go through the steps involved in the process of updating a Dell server running ESXi 5.5 to the latest version of vSphere. I mention Dell because I am going to use a customized Dell ISO to get the latest certified drivers and patches.

Why do I use a Dell customized ISO?

- Ease of drivers and specific packages management.
- Simplify and shorten the execution of support tickets.
- Dell server, Dell software, it makes sense to me.

In order to have an idea of the difference I downloaded the latest ISO build "3620759" from the VMware website to have the stock ISO and from the Dell website to have their customized one and compared it with PowerShell.

<= are the objects only present in the reference (ESXiStock)
=> are the objects only present in the difference (ESXIDell)

![vibs-difference.jpg]({{site.baseurl}}/img/vibs-difference.jpg)

The 2 main things we can note from this comparison are:
- More recent vib versions in the Dell build.
- More vibs in the Dell build, most likely drivers for hardware used in their servers.

I was actually surprised to see that the Dell build embedded more recent drivers but I guess VMware relies on the manufacturers to provide their ISOs with versions certified for their Support, which would make perfect sense.

## Download the right iso image

First of all we need to download the latest version of the Dell customized vSphere 6.0 image. The Dell support website is a little bit weird as I couldn't find my way through to the vSphere downloads but google got me there: [www.dell.com/support/home/us/en/04/Drivers/DriversDetails?driverId=2RNCX](www.dell.com/support/home/us/en/04/Drivers/DriversDetails?driverId=2RNCX)

As of today the latest Dell ISO is the 6.0U2, A02.

![update6-0.0.jpg]({{site.baseurl}}/img/update6-0.0.jpg)

Scroll down to verify that it is the latest version and go to the most recent one if there is one. Even though it's not really necessary (as long as your server is in the [hcl](http://www.vmware.com/resources/compatibility/search.php)) I check that my model is listed under the compatible systems. Blade M630 in my case.

![update6-0.jpg]({{site.baseurl}}/img/update6-0.jpg)

That done, find the iso image in the "available formats" section and click "download file".

----------------

## Create the host upgrade baseline

Log in vCenter and go to the configuration of Update manager in "Manage" > "ESXi Images".  
Once the import is finished validate by clicking OK.

![update6-1.jpg]({{site.baseurl}}/img/update6-1.jpg)

Click "Import Esxi Image...", browse to the ISO image you just downloaded and click "Import".

![update6-2.jpg]({{site.baseurl}}/img/update6-2.jpg)

Go to the "Host baseline" tab and create a baseline by click the green plus.

Check "Host Upgrade" to make it a major upgrade and not a patching.

Enter a name and description that your colleagues can easily understand and click next.

![create-baseline.jpg]({{site.baseurl}}/img/create-baseline.jpg)

Choose the ESXi image that you just uploaded and complete the wizard.

## Attach the baseline and remediate the host

Now attach the baseline to the cluster by right clicking on it, in the contextual menu go to "Update manager" > "Attache baseline" > Check the baseline you just created and click OK.

All the hosts in your cluster now have the baseline attached and can be scanned and remediated.

_Note that you can attach the baseline on a per host basis if you don't want it on all the hosts in this cluster. Keep in mind however that, if you upgrade a VM's virtual hardware to a version N+1 you won't be able to migrate it to a host that supports up to version N._

| ESX/ESXi | vHardware |
------------------------
| 6.x      | 11        |
| 5.5      | 10        |
| 5.1      | 10        |
| 5.0      | 8         |
| 4.x      | 7         |
| 3.x      | 4         |
| 2.x      | 3         |

Scan your cluster for updates by right right-clicking on it > Update Manager > Scan for Updates and wait for the scan to finish. You'll see that your cluster is non compliant to your attached baselines.

![Non-Compliant-vum.jpg]({{site.baseurl}}/img/Non-Compliant-vum.jpg)

Then put the host you want to upgrade in maintenance mode.  
Note that you might need to disable admission control if for example you have a 2 nodes cluster with a tolerance of one host loss.

Once it is done right click on it > Update Manager > Remediate

Select the baseline we created earlier containing the last ESXi ISO.

![remediate1.jpg]({{site.baseurl}}/img/remediate1.jpg)

If you triggered the remediation while positionned on a host you'll only see this one, otherwise chose the host you want to upgrade.

![remediate2.jpg]({{site.baseurl}}/img/remediate2.jpg)

Then I chose not to ignore the warnings about unsupported hardware devices but this one is up to you.

Give the task a name and run this action now.

Leave the default Maintenance mode options as it is already correctly configured.

![remediate3.jpg]({{site.baseurl}}/img/remediate3.jpg)

For the remediation options I leave the default options as well but it will depend on the available resources in your cluster and the level of "risk" you are willing to take.

I am usually very cautious when it comes to upgrades, even after having them tested in pre-prod before because you never know what can happen. That is why I don't allow the remediation of multiple hosts in parallel (Or at least not the first one).

I don't check the box to disable HA as I know I have enoug resources in my cluster to place a host in maintenance mode without violating my admission control's policy. but if you already put th host in maintenance mode prior to do the remediation it is very likely that you don't need to check it.

![remediate4.jpg]({{site.baseurl}}/img/remediate4.jpg)

Click Next, review the settings and double check it's the right host and the right build ;).  
And click Finish.

vCenter will then proceed to upgrade the host which will trigger a restart. The operation takes a little while so this step is all about patience.

Once the operation finishes you can take your host out of maintenance mode and check the ESXi version, as you can see it is now 6.0.0, 3620759 on my lab.

![version6.0.jpg]({{site.baseurl}}/img/version6.0.jpg)