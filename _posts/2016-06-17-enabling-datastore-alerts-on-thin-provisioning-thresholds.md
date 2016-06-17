---
layout: post
published: false
title: Enabling datastore alerts on thin provisioning thresholds
meta description: >-
  How to add vCenter alerts on datastore storage overcommitment with thin
  provisioned virtual machines.
---
Something every sensible VMware administrator is concerned about is the over commitment of the datastores. Since the dawn of times in virtualization it is possible to thin provision the disks of the virtual machines by not allocating the blocks to it, hence over commit the actual physical storage by provisioning X+Y GB even if the storage has only X GB to offer.

![thick-thin.jpg]({{site.baseurl}}/img/thick-thin.jpg)

If the storage is well monitored and the storage activity of your VMs is predictable (i.e. no surprises with tempdb filling up) it is sensible to have a bit of overcommitment environment.

However, if you get to the point where one of your overcommited datastore runs out of storage you might get into trouble.  
- The thick provisionned VMs will keep running as the space has been "reserved" on the datastore so it is already ready for usage by the VM which is good.
- The thin provisionned VMs asking for extra storage will be **paused** (imagine the db of a web stack).

See this very good post by Cormac Hogan for more details: [Thin Provisioning – What's The Scoop?](http://blogs.vmware.com/vsphere/2012/03/thin-provisioning-whats-the-scoop.html)


### Add an alarm for datastore overcommitment

This alert isn't set by default and is "hidden" in the datastore usage alert.

To set it, select your vCenter on the "Manage" tab then "Alarm definitions" and select "Datastore usage on disk"

![datastore-usage-on-disk.jpg]({{site.baseurl}}/img/datastore-usage-on-disk.jpg)

And click "Edit" to modify the alarm.

Then add a trigger, and select "Datastore Disk Provisioned".

![datastore-usage-on-disk-provisionned.jpg]({{site.baseurl}}/img/datastore-usage-on-disk-provisionned.jpg)

The default thresholds are Warning = Datastore 100% Provisioned and Critical = Datastore 200% Provisioned.  
But because I am a little bit paranoid and I don't use thin disks a lot I set a lower value to be warned when 130% is reached.

You can then configure the action according to your alerting process (email, snmp and so on). You could also set the critical alert to repeat every X minutes, I like it to be annoying so we take the time to deal with it.

That's all, you will now get alerts on overcommitment threshold.

### PowerCLI script to find out the overallocated datastores

Now you probably want to know which one of your datastores are overprovisioned. There are plenty of good and free tools that will do the job like [RVTools](http://www.robware.net/) which is a must have! But it is more interesting to do some PowerCLI to get there yourself.

I wrote the function **Get-Datastore2** below to give a clear output of the state of the datastore without having to dig into the objects.

![get-datastore2.jpg]({{site.baseurl}}/img/get-datastore2.jpg)

If you want to get only the over provisioned datastore:

```Powershell
get-datastore | Get-Datastore2 | Where-Object {$_.ProvisionedGB -gt $_.CapacityGB}
```

[Get-Datastore2](https://github.com/vxav/Scripting/blob/master/Get-Datastore2.ps1)

```Powershell
Function Get-Datastore2 {

param(
    [parameter(position=0,ValueFromPipeline=$True,ValueFromPipelineByPropertyname=$True)]
    [VMware.VimAutomation.ViCore.Types.V1.DatastoreManagement.VmfsDatastore[]]
    $Datastore
)

Process{

    $Datastore | ForEach-Object {

        [pscustomobject]@{
            Name          = $_.name
            CapacityGB    = [Math]::Round(($_.extensiondata.summary.capacity   / 1GB),2)
            FreeSpaceGB   = [Math]::Round(($_.extensiondata.summary.FreeSpace  / 1GB),2)
            UsedSpaceGB   = [Math]::Round((($_.extensiondata.summary.capacity  / 1GB) - ($_.extensiondata.summary.FreeSpace / 1GB)),2)
            ProvisionedGB = [Math]::Round((($_.extensiondata.summary.capacity  / 1GB) - ($_.extensiondata.summary.FreeSpace / 1GB) + ($_.extensiondata.summary.Uncommitted / 1GB)),2)
            NbRunningVMs  = ($_ | Get-VM | where powerstate -eq Poweredon).count
        }

    }

}

}
```

### PowerCLI script to find out the thin provisioned disks in your vSphere environment.

If you realise that your datastores are overallocated and you want to change that pattern you probably want to know what virtual machine has thin provisioned disks.

I put a really simple one liner into a function in my powershell modules just so I don't need to remember and write the command.

![get-thinharddisk.jpg]({{site.baseurl}}/img/get-thinharddisk.jpg)

[Get-ThinHardDisk](https://github.com/vxav/Scripting/blob/master/Get-ThinHardDisk.ps1)

```Powershell
Function Get-ThinHardDisk {

param(
    [parameter(position=0,ValueFromPipeline=$True,ValueFromPipelineByPropertyname=$True)]
    [ValidateNotNullOrEmpty()]
    [VMware.VimAutomation.ViCore.types.V1.Inventory.VirtualMachine[]]
    $VM = (get-VM)
)

Process{

    $VM | ForEach-Object {

        (Get-HardDisk -VM ($_) | where StorageFormat -eq Thin) | select Parent,Name,CapacityGB,StorageFormat

    }

}

}
```
