---
layout: post
title: Automatically install CNI in new kubernetes cluster with Cluster API
DATE: 
subtitle: ''
metadescription: ''

---
In a [previous blog ](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/)we discovered Cluster API and how it allows you to declaratively deploy Kubernetes cluster to your favourite cloud provider, ours being vSphere obviously! While this is great, one thing that may be frustrating. It is the fact that, once the cluster is deployed, you have to retrieve the kubeconfig file for the cluster and install a CNI in order for it to go in a **Ready** state. Thankfully there is a way to automate it and this is what we will describe here.

### ClusterResourceSet

Without further ado, I'll start with a spoiler: the solution is a [**ClusterResourceSet**](https://github.com/kubernetes-sigs/cluster-api/blob/main/docs/proposals/20200220-cluster-resource-set.md). A feature of the Cluster API project that lets you automatically install a resource to a newly created cluster. The current use cases are CNI (network) and CSI (storage provider). 

In our case, we apply the Calico CNI through a ConfigMap that contains the latest manifest. The ClusterResourceSet object is applied to a cluster through a **matchLabel**. Which is similar to how you tie pods to a service for instance except here we use a **ClusterSelector** tag.