---
layout: post
published: false
title: Easily run PowerCLI commands as jobs
---
## Overview

Running commands as jobs is pretty mainstream in Powershell. A simple "Start-Job" or "Invoke-Command -AsJob" will do the trick. However, when PowerCLI is involved it is not as straightforward. If you try to run  a command that requires to be connected to a vCenter you will probably receive an error saying that the command is not recognized.

Start a job to get datastores.  
![job-ds-fail-1.jpg]({{site.baseurl}}/img/job-ds-fail-1.jpg)

Wait for the job to finish and place the result into the $ds variable.  
![job-ds-fail-2.jpg]({{site.baseurl}}/img/job-ds-fail-2.jpg)

This error occurs because the job initiates a new Powershell session which doesn't have the PowerCLI module loaded and of course is not connected to any vCenter. 

The trick to run PowerCLI commands in parallel is to import the module and connect to vCenter for every job.  One easy way to connect to vCenter when you already have a session is to re-use the **SessionSecret** property of the **$DefaultVIServer** variable created when you logged in vCenter. It is very easy to do but if you have to do it often or you don't want to repeat the same 4 lines every time in your script to keep it lean and clean, your OCD self will be upset, which is where the "Start-PowerCLIJob" function becomes useful.

## Start-PowerCLIJob

This function is very simple, all it does is:

- Import the PowerCLI module (by default only VMware.VimAutomation.Core but it's parameterised)
- Disable the PowerCLI deprecation warning (if not your job will hang)
- Connect to vCenter using the existing $DefaultVIServer variable including the IP/FQDN and the session secret
- Prepend all this to your ScriptBlock

Example:

Imagine you have a PowerShell module that allows you to deploy VMs from a CSV file to make the example more convenient. What we do here is create a job for every VM deployment and wait for the jobs to finish. you can then do receive-job etc... 

```Powershell
PS> Import-CSV "MyDeployment.CSV" | foreach-object {Start-PowerCLIJob -DefaultVIServer $DefaultVIServer -JobName "Job Deploy VM $($_.VMName)" -ScriptBlock {Import-Module Deploy-vm.psm1; $using:_ | Deploy-VM}}

Id     Name            PSJobTypeName   State         HasMoreData     Location             Command
--     ----            -------------   -----         -----------     --------             -------
21     Deploy VM VM-1  BackgroundJob   Running       True            localhost            ...
23     Deploy VM VM-2  BackgroundJob   Running       True            localhost            ...
25     Deploy VM VM-3  BackgroundJob   Running       True            localhost            ...
27     Deploy VM VM-4  BackgroundJob   Running       True            localhost            ...
29     Deploy VM VM-5  BackgroundJob   Running       True            localhost            ...

PS> Get-Job "Deploy VM*" | Wait-Job
```

## Caveats

One thing to note though that is also true for "regular" PowerShell jobs is that when you receive the job, the objects returned are deserialized. Meaning they don't have any method, it is only a basic data container. You won't be able to browse through the object's properties or use it as an active object.

Example with Get-VM:

**Regular PowerCLI**

Pay attention to the type: _VMware.VimAutomation.ViCore.Impl.V1.VM.UniversalVirtualMachineImpl_

And the Definition of all the properties and methods.

```Powershell
PS> $VM = get-vm tf-utl-vone

PS> $VM | get-member


   TypeName: VMware.VimAutomation.ViCore.Impl.V1.VM.UniversalVirtualMachineImpl

Name                    MemberType Definition
----                    ---------- ----------
ConvertToVersion        Method     T VersionedObjectInterop.ConvertToVersion[T]()
Equals                  Method     bool Equals(System.Object obj)
GetConnectionParameters Method     VMware.VimAutomation.ViCore.Interop.V1.VM.RemoteConsoleVMParams RemoteConsoleVMInterop.GetConnectionParameters()
GetHashCode             Method     int GetHashCode()
GetType                 Method     type GetType()
IsConvertableTo         Method     bool VersionedObjectInterop.IsConvertableTo(type type)
LockUpdates             Method     void ExtensionData.LockUpdates()
ObtainExportLease       Method     VMware.Vim.ManagedObjectReference ObtainExportLease.ObtainExportLease()
ToString                Method     string ToString()
UnlockUpdates           Method     void ExtensionData.UnlockUpdates()
Client                  Property   VMware.VimAutomation.ViCore.Interop.V1.VIAutomation Client {get;}
CoresPerSocket          Property   int CoresPerSocket {get;}
CustomFields            Property   System.Collections.Generic.IDictionary[string,string] CustomFields {get;}
DatastoreIdList         Property   string[] DatastoreIdList {get;}
DrsAutomationLevel      Property   System.Nullable[VMware.VimAutomation.ViCore.Types.V1.Cluster.DrsAutomationLevel] DrsAutomationLevel {get;}
ExtensionData           Property   System.Object ExtensionData {get;}
Folder                  Property   VMware.VimAutomation.ViCore.Types.V1.Inventory.Folder Folder {get;}
FolderId                Property   string FolderId {get;}
Guest                   Property   VMware.VimAutomation.ViCore.Types.V1.VM.Guest.VMGuest Guest {get;}
GuestId                 Property   string GuestId {get;}
HAIsolationResponse     Property   System.Nullable[VMware.VimAutomation.ViCore.Types.V1.Cluster.HAIsolationResponse] HAIsolationResponse {get;}
HARestartPriority       Property   System.Nullable[VMware.VimAutomation.ViCore.Types.V1.Cluster.HARestartPriority] HARestartPriority {get;}
Id                      Property   string Id {get;}
MemoryGB                Property   decimal MemoryGB {get;}
MemoryMB                Property   decimal MemoryMB {get;}
Name                    Property   string Name {get;}
Notes                   Property   string Notes {get;}
NumCpu                  Property   int NumCpu {get;}
PersistentId            Property   string PersistentId {get;}
PowerState              Property   VMware.VimAutomation.ViCore.Types.V1.Inventory.PowerState PowerState {get;}
ProvisionedSpaceGB      Property   decimal ProvisionedSpaceGB {get;}
ResourcePool            Property   VMware.VimAutomation.ViCore.Types.V1.Inventory.ResourcePool ResourcePool {get;}
ResourcePoolId          Property   string ResourcePoolId {get;}
Uid                     Property   string Uid {get;}
UsedSpaceGB             Property   decimal UsedSpaceGB {get;}
VApp                    Property   VMware.VimAutomation.ViCore.Types.V1.Inventory.VApp VApp {get;}
Version                 Property   VMware.VimAutomation.ViCore.Types.V1.VM.VMVersion Version {get;}
VMHost                  Property   VMware.VimAutomation.ViCore.Types.V1.Inventory.VMHost VMHost {get;}
VMHostId                Property   string VMHostId {get;}
VMResourceConfiguration Property   VMware.VimAutomation.ViCore.Types.V1.VM.VMResourceConfiguration VMResourceConfiguration {get;}
VMSwapfilePolicy        Property   System.Nullable[VMware.VimAutomation.ViCore.Types.V1.VMSwapfilePolicy] VMSwapfilePolicy {get;}
```

**Powershell job**

The type has changed: _Deserialized.VMware.VimAutomation.ViCore.Impl.V1.VM.UniversalVirtualMachineImpl_

All the methods previously available are gone and the properties are now either Integers or Strings.

```Powershell
PS> Start-PowerCLIJob -DefaultVIServer $global:DefaultVIServer -JobName GetVM -ScriptBlock {Get-VM tf-utl-vone}

PS> $VMJob = get-job getvm | wait-job | receive-job

PS> $VMJob | get-member


   TypeName: Deserialized.VMware.VimAutomation.ViCore.Impl.V1.VM.UniversalVirtualMachineImpl

Name                    MemberType   Definition
----                    ----------   ----------
GetType                 Method       type GetType()
ToString                Method       string ToString(), string ToString(string format, System.IFormatProvider formatProvider), string IFormattable.ToString(string format, System.IFormatProvider formatProvider)
PSComputerName          NoteProperty string PSComputerName=localhost
PSShowComputerName      NoteProperty bool PSShowComputerName=False
RunspaceId              NoteProperty guid RunspaceId=2c3c6f16-65ff-4884-b0aa-5f677b43a48c
Client                  Property     System.String {get;set;}
CoresPerSocket          Property     System.Int32 {get;set;}
CustomFields            Property     Deserialized.VMware.VimAutomation.ViCore.Impl.V1.Util.ReadOnlyDictionary`2[[System.String, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089],[...
DatastoreIdList         Property     Deserialized.System.String[] {get;set;}
DrsAutomationLevel      Property     System.String {get;set;}
ExtensionData           Property     System.String {get;set;}
Folder                  Property     System.String {get;set;}
FolderId                Property     System.String {get;set;}
Guest                   Property     System.String {get;set;}
GuestId                 Property     System.String {get;set;}
HAIsolationResponse     Property     System.String {get;set;}
HARestartPriority       Property     System.String {get;set;}
Id                      Property     System.String {get;set;}
MemoryGB                Property     System.Decimal {get;set;}
MemoryMB                Property     System.Decimal {get;set;}
Name                    Property     System.String {get;set;}
Notes                   Property     System.String {get;set;}
NumCpu                  Property     System.Int32 {get;set;}
PersistentId            Property     System.String {get;set;}
PowerState              Property     System.String {get;set;}
ProvisionedSpaceGB      Property     System.Decimal {get;set;}
ResourcePool            Property     System.String {get;set;}
ResourcePoolId          Property     System.String {get;set;}
Uid                     Property     System.String {get;set;}
UsedSpaceGB             Property     System.Decimal {get;set;}
VApp                    Property      {get;set;}
Version                 Property     System.String {get;set;}
VMHost                  Property     System.String {get;set;}
VMHostId                Property     System.String {get;set;}
VMResourceConfiguration Property     System.String {get;set;}
VMSwapfilePolicy        Property     System.String {get;set;}
```

## Conclusion

The fact that the objects received from a job are deserialized is certainly annoying but it is just the way jobs work, you just need to be aware of that and treat the output of a job as a "print screen" and not as an object that you can do something with. Jobs are only here to parallelize stuff that would take too much time if they were put one after the other. 

In some cases you will probably notice that running your payload in jobs takes longer than sequentially, especially with PowerCLI as it needs to import the module and reconnect to vCenter every time. I measured a 4 second penalty on "PowerCLI jobs". It might seem like a lot, and it is for a 2 seconds job, but if every single job takes 5 or 10 minutes to complete and you have 5 of them to run... You do the math.

