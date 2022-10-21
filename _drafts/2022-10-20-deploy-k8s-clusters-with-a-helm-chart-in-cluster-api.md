---
layout: post
title: Deploy K8s clusters with a Helm chart in Cluster API
description: null
date: 2022-10-20T18:14:18.932Z
nobanner: no
fb-img: null
---
While trying to think of something cool to write about, I'm came up another Cluster API topic that I'm having a lot of fun with at work. If you are not familiar with Cluster API, you may want to check some of my blogs on the topics [here](https://www.vxav.fr/2022-05-15-cluster-api-with-vmware-cloud-director-10.3-(capvcd),-nsx-t-and-alb/), [here](https://www.vxav.fr/2021-12-07-automatically-install-cni-in-new-kubernetes-cluster-with-cluster-api/) or [here](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/). In a nutshell, Cluster API lets you provision infrastructure necessary to run a Kubernetes cluster on your favourite infrastructure provider (vSphere, VCD, AWS, Azure, OpenStack...) by defining them with Custom Resources (CRs) and bootstrap the nodes subesquently.

My readership being coming mostly from the infra VMware world, I feel like I should talk a little bit about Helm and what it is. helm is a highly popular package manager for Kubernetes that simplifies the management of resources by bundling them into apps that are available in public or private repositories. When working with it, we mostly deal with Helm charts. A chart being a collection of Yaml files that can be easily parameterized thanks to a values file. And this is what we are about to do here, specifically take the manifests that constitute a Kubernetes cluster in Cluster API and adjust them with configurable variables.

To demonstrate this, I will be using CAPVCD (Cluster API for VMware Cloud Director) but you can use whatever provider you like (there's one for Docker). My previous [here](https://www.vxav.fr/2022-05-15-cluster-api-with-vmware-cloud-director-10.3-(capvcd),-nsx-t-and-alb/) on the topic is a bit outdate as it uses an old version of CAPVCD but you can also use [Giant Swarm's Helm chart](https://github.com/giantswarm/cluster-api-provider-cloud-director-app) to quickly install a newer version.

As a side note, if you are looking for options on how to protect your VMware Cloud Director workloads, [Nakivo Backup & Replication](https://www.nakivo.com/vmware-cloud-director-backup/) offers capabilities to back up VCD objects such as vApps, individual VMs and vApp metadata and ensure that remote workloads can be recovered in case of a data loss event. Not a lot of vendors out there support VCD so kuddos to that.

## Foreword

Before starting, I'd like to expose a few caveats to make some things clearer:

* I use a local clone of a Github repo for the test, a real environment would store the Helm chart in an accessible repository.
* I only create the base cluster with CAPI. The next bare minimum would be to install a CNI and the CPI (which you could do with [Cluster Resource Sets](https://www.vxav.fr/2021-12-07-automatically-install-cni-in-new-kubernetes-cluster-with-cluster-api/))
* I am building my chart based off the current main branch of the project, meaning I use a custom built image. If you use a more mature provider like CAPV for instance, you can just initialize CAPV with `clusterctl init` without any concern.
* For CAPVCD I am using the sample manifest as a base to work with but most providers support `clusterctl generate` to generate a cluster template. I also think the sample manifest is more straightforward for our example.

## Retrieving the cluster manifests and identifying variables

To make building the chart a bit simpler, you can use the [template](https://github.com/vmware/cluster-api-provider-cloud-director/blob/22af653e351f3e788774fa6000658710b3415706/templates/cluster-template-v1.21.8.yaml) used by `clusterctl generate` as all relevant properties are already parameterized. Make sure to take it from the same commit as the one you built the controller from if that's what you did. For instance, I built my CAPVCD controller from commit _22af653_, so I browse the files from that commit to make sure the manifests and the CRDs are compatible with the controller.

This manifest contains a bunch of things that describe the cluster to deploy. I won't describe them here but you can refer to the [CAPI doc](https://cluster-api.sigs.k8s.io/user/concepts.html) for more details about them.

Note that the secret holding the credentials for VCD is in there but we will remove it from the chart as we will require for it to already exist in the namespace which is more secure.

## Building the cluster chart

* Start by creating the chart with `helm create <name of chart>` and it will create the 

``` bash
❯ helm create capvcd-cluster
Creating capvcd-cluster
```