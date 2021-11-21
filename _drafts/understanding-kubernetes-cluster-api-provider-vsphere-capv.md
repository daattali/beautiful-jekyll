---
layout: post
title: Understanding Kubernetes Cluster API Provider vSphere (CAPV)
DATE: 
subtitle: ''
metadescription: Find out about declarative Kubernetes cluster creation with Kubernetes
  Cluster API Provider vSphere (CAPV)

---
I recently got into Kubernetes Cluster API Provider vSphere (CAPV) to understand what it is, what it does and where it fits in the Kubernetes and VMware ecosystem. The answer is a lot simpler than it seems and it is already used by several companies such as VMware (Tanzu Community Edition) or Giant Swarm to only name a couple.

So, the way Kubernetes provisions resources is declaratively through YAML manifest describing the state you want them to be in. By default these manifests cover "vanilla" Kubernetes objects such as deployments, pods, replicasets, services, ingress, you name it. You can get the list by running "_kubectl api-resources_". 

Projects like [cluter-api](https://cluster-api.sigs.k8s.io/) expand the capabilities of Kubernetes by offering the possibility to interface with [many cloud providers ](https://cluster-api.sigs.k8s.io/reference/providers.html)such as AWS, Azure, Sidero, etc to provision Kubernetes workload clusters. These extra capabilities are in the form of Custom Resource Definitions (CRD) and controllers that know how to "speak" (API) to these cloud providers. In our case we are interested in the vSphere provider called Cluster API Provider vSphere or CAPV.