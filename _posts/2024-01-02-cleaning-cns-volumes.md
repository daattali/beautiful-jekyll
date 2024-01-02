---
layout: post
title: How to clean Kubernetes CNS volumes in vSphere with PowerCLI
date: 2024-01-02T11:58:04.234Z
nobanner: no
fb-img: null
---

Since I somewhat shifted from VMware Sysadmin to Solutions Architect for a Kubernetes service provider (Giant Swarm) two years ago, I haven't done much PowerCLI as I now live in a world of Yaml, Go and Bash. However, I do miss PowerShell for its object oriented nature which I find a million times easier to work with than parsing strings in Bash and stacking parameters I immediately forget about.

So when I had to clean up a whole bunch of Cloud Native Storage volumes in vSphere which were leftovers from our CAPV testing, I thought it would be fun to do it in PowerCLI. Although it is quick and simple, I did enjoy it a lot again!

The issue here is that we had over 400 CNS volumes in vSphere, most of which or no longer in use. This is due to PVCs being created in our test clusters and leftover when the cluster is deleted. We now have a cleanup operator to take care of it but those were created before.

![too many cns volumes](/img/cnsvolumes1.png)

The vSphere client being the great piece of UX it is, you can only delete volumes one at a time, so => PowerCLI to the rescue with the `<verb>-CNSVolume` suite of commands. 

Note that our use case here is pretty simple, we want to delete all the CNS volumes that are not used by the 3 Kubernetes clusters we have running. **Your use case will most likely vary so DON'T COPY THE COMMANDS BLINDLY!**

* First I store the list of volumes in a variable as it took a long time to run because of the number of volumes. That way I can work with it more efficiently.

``` powershell
$cnsvolumes=Get-CnsVolume
```

* With this PowerCLI object, you will find details about the volumes.

``` powershell
$cnsvolumes[0].Metadata.CnsEntityMetadata

EntityType          : PersistentVolume
Namespace           :
ReferredEntity      : {}
KubernetesClusterId : t-41asv95
EntityName          : pvc-7e50dd14-7fc5-480d-8824-a1cd800dcd84
Label               :

EntityType          : Pod
Namespace           : test-storage
ReferredEntity      : {test-pvc}
KubernetesClusterId : t-41asv95
EntityName          : pvc-test-pod
Label               :

EntityType          : PersistentVolumeClaim
Namespace           : test-storage
ReferredEntity      : {pvc-7e50dd14-7fc5-480d-8824-a1cd800dcd84}
KubernetesClusterId : t-41asv95
EntityName          : test-pvc
Label               :
```

* You also find information about the cluster it belongs to. This is what interests me in my case as I want to keep only the volumes that belong to clusters `gmc`, `gravel` and `gcapeverde`. 

``` powershell
$cnsvolumes[0].Metadata.ContainerCluster

ClusterFlavor KubernetesClusterId ClusterType VSphereUser
------------- ------------------- ----------- -----------
      Vanilla t-41asv95            Kubernetes vcenter-admin@vsphere.local


$cnsvolumes|select name,capacitymb,@{l="cluster";e={$_.Metadata.ContainerCluster.KubernetesClusterId}}|Sort-Object -Property cluster

Name                                     CapacityMB cluster
----                                     ---------- -------
pvc-4f1b2419-6741-4ce2-89b6-c5367841c154       5120 gcapeverde
pvc-4996541f-1aef-412a-82a3-d172f608fbfc     102400 gcapeverde
pvc-0b33d2d9-a8d6-455f-b07b-323501f041cd       1024 gcapeverde
pvc-811c6e82-7bee-483f-b748-e1a7867f01ad     102400 gcapv
pvc-727b597a-7d8b-4691-b0c6-1411d719a4cd       5120 gcapv
pvc-9ab76bcb-e3fa-4623-8a0d-19ec19026493       1024 gcapv
pvc-1afcc0e2-566d-46b5-8ce0-4c2de2568e07       5120 gipam
pvc-97acde0c-7df6-4a6c-89aa-53617a27634c     102400 gipam
pvc-ef5e3196-5bf9-4a8d-afc7-1990d77a95a7       1024 gipam
pvc-ac1fe690-a023-48e4-b40f-b782afcfd273       5120 gmc
pvc-2885202f-d5ca-42b2-a34e-42ac14065f3c       1024 gmc
pvc-a148a8b7-2df3-4d8d-ae2c-d659f03f3e8b       1024 t-06w2kog
pvc-43d13ea5-dccf-42c0-bf6a-5a64cc5edbe8       1024 t-08q1kjs
pvc-384d02e5-4b89-43ce-a26f-3a49d0a2b134       1024 t-0e8yfrr
pvc-b8c7e3d3-e636-41b7-88ec-ae794cfb9a2f       1024 t-0fle3ka
pvc-33797e4a-1ab1-4e30-bc82-de43a3370567       1024 t-0gdveu9
pvc-35dc1cd5-7b59-4c20-9b54-8e033f6715f5       1024 t-0nchhio
pvc-6bd8f714-94cd-46bd-a42f-0b0e28d608a3       1024 t-0pdj0rt
pvc-5022a2bb-15d8-4606-a8c9-884ca32761ea       1024 t-0vliv8oveojf4f17y0
pvc-e9f1b3e6-111f-41dc-95d6-bfd1592bdda9       1024 t-0yll5wy
pvc-5a53d789-1f06-48c4-850f-d485bc120436       1024 t-10x5xz2
pvc-61188498-78ed-416a-b437-34c4872a1738       1024 t-1172sl0
pvc-36814fdd-f01f-4903-8f78-1ce7ad52d68f       1024 t-132epdw
pvc-04f59599-5341-4778-b2b5-cee6cfa37e0c       1024 t-18sucb15ky8lzdc0yc
```

* To filter out the CNS volumes from the clusters to keep, I add them to a list, exclude it from the full list of CNS volumes and I pipe the output into the `Remove-CnsVolume`.

``` powershell
$excluded_clusters = "gmc","gcapeverde","gravel"

$cnsvolumes | where {$_.Metadata.ContainerCluster.KubernetesClusterId -notin $excluded_clusters} | Remove-CnsVolume

Confirm
Are you sure you want to perform this action?
Performing the operation "Remove-CnsVolume" on target "Remove CNS volumes.".
[Y] Yes  [A] Yes to All  [N] No  [L] No to All  [S] Suspend  [?] Help (default is "Y"): a
```

This will delete all the CNS volumes in the list. Again, make sure the list includes the volumes you want to delete before pressing the red button.

![cleaned up cns volumes](/img/cnsvolumes2.png)

## Wrap up

In conclusion, working with Kubernetes resources in vSphere using PowerCLI not only empowers administrators with efficient resource management but also underscores the importance of seamless integration between Kubernetes and VMware environments. By navigating the intricacies of PowerCLI commands tailored for volume management, administrators can ensure the prompt removal of unnecessary storage resources and optimizing storage utilization.

On a side note, if you are looking for options on how to **protect your vSphere and VMware Cloud Director** workloads, [Nakivo Backup & Replication](https://www.nakivo.com/) offers capabilities to back up vSphere VMs and VCD objects such as vApps, individual VMs and vApp metadata and ensure that remote workloads can be recovered in case of a data loss event.

[![nakivo backup](/img/2022-10-26-13-45-41.png)](https://www.nakivo.com)