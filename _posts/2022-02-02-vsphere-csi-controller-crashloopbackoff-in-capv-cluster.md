---
layout: post
title: vSphere CSI controller CrashLoopBackoff in CAPV cluster
DATE: 
subtitle: ''
metadescription: Here we fix the vSphere CSI controller CrashLoopBackoff in kubernetes
  cluster created with CAPV
image: ''

---
As a bit of background, I recently wrote about the [Cluster API vSphere provider ](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/)and how to deploy a Kubernetes cluster to a vSphere environment, otherwise this blog won’t make much sense. I also experimented with the use of a [clusterResourceSet ](https://www.vxav.fr/2021-12-07-automatically-install-cni-in-new-kubernetes-cluster-with-cluster-api/)to automatically install the Calico CNI inside the workload cluster but this isn’t related to the issue at hand.

> _At the time of this writing,_ [_this issue is being worked on_](https://github.com/kubernetes-sigs/cluster-api-provider-vsphere/pull/1220) _by the CAPV folks and should be resolved in a future release where it will leverage the vCenter certificate thumbprint._

Anyways, in the [blog ](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/)about CAPV, I show you how to deploy a kubernetes cluster to vSphere which works quite well. In short, what I didn’t show is that one of the [vSphere CSI ](https://github.com/kubernetes-sigs/vsphere-csi-driver)controller pod’s containers wouldn’t reach the ready state because it didn’t trust the vCenter certificate thumbprint, even though it is in the cluster definition manifest (that you originally set in _clusterctl.yaml_).

In order to fix this issue, I was helped by a colleague who is highly knowledgeable in Kubernetes and it was a great learning experience so I thought I’d go through the steps here as I enjoyed the process.

**First, here is the pod not initializing, as you can see, 1 container out of 5 is not running.**

    kubectl get pod -n kube-system

![](/img/vcsicrashloopbackoff1.png)

**Use describe to get more information and we find that it’s the container named “_vsphere-csi-controller_” which is the problem.**

    kubectl describe pod vsphere-csi-controller-76c9d858d4-mhqss -n kube-system

![](/img/vcsicrashloopbackoff2.png)

**Display the logs of said container** (you must specify the container if there are more than one in a pod) **and we find that the vCenter** (192.168.1.102) **certificate is not trusted.** Even though its thumbprint is in the cluster yaml manifest.

    kubectl logs vsphere-csi-controller-76c9d858d4-mhqss -n kube-system -c vsphere-csi-controller

![](/img/vcsicrashloopbackoff3.png)

**After a bit of digging we found, in the** [**vSphere Cloud provider’s config specs**](https://cloud-provider-vsphere.sigs.k8s.io/cloud_config)**, a line to bypass the error linked to certificates signed by unknown authorities.**

![](/img/vcsicrashloopbackoff4.png)

**If we go back to the describe command, we find that the CSI controller configuration is done in _/etc/cloud/csi-vsphere.conf_ which is mounted through a volume named _vsphere-config-volume_, which contains the _csi-vsphere-config secret_. So the answer must be in this secret.**

![](/img/vcsicrashloopbackoff5.png)

**Now if we look in the cluster definition manifest, we find this secret which looks an aweful lot like the cloud config specs. So we can add _insecure-flag = “1”_ under either global or VirtualCenter.**

    insecure-flag = "1"

![](/img/vcsicrashloopbackoff6.png)

Then you just have to redeploy the cluster and the pod should initialize correctly.

![](/img/vcsicrashloopbackoff7.png)

Alternatively if you want to fix a running cluster, you can also edit the **_csi-vsphere-config_** secret in the **_kube-system_** namespace (you’ll have to decode and encode with base64) and then delete the **_csi-controller_** pod to get it recreated with the updated secret.

You can then start using the vSphere CSI driver to provision Cloud Native Storage in your environment but that will be the topic of another blog.

![](/img/vcsicrashloopbackoff8.png)