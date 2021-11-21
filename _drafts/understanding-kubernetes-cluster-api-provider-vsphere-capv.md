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

### What is Cluster API Provider vSphere (CAPV)

Projects like [cluter-api](https://cluster-api.sigs.k8s.io/) expand the capabilities of Kubernetes by offering the possibility to interface with [many cloud providers ](https://cluster-api.sigs.k8s.io/reference/providers.html)such as AWS, Azure, Sidero, etc to provision Kubernetes workload clusters. These extra capabilities are in the form of Custom Resource Definitions (CRD) and controllers that know how to "speak" (API) to these cloud providers to deploy the nodes as VMs and then create a cluster with kubeadm. The cluster-api resources are installed in what is referred to as a _kubernetes management cluster_ that remains and is used to provision Kubernetes clusters on a cloud provider.

In our case we are interested in the vSphere provider called Cluster API Provider vSphere or CAPV. For instance, you can see pretty much the same steps when getting started with Tanzu Community Edition, except it is made a lot simpler through UI and automation. In this post we are doing essentially the same steps but manually, that way we can see what's going on behind the scenes.

The steps are as follows to get started with cluster-api:

1. **Install Kind on a bootstrap VM**: We will use a debian VM to run a temporary cluster with Kind and delete it at the end. 
2. **Create a bootstrap cluster with Kind**: You could turn an existing kubernetes cluster in a management cluster but the more common process is to use a temporary kind cluster to provision a kubernetes cluster on your cloud provider and then move the cluster-api components to it, rendering the temporary cluster obsolete.
3. **Download clusterctl and prepare the temporary cluster with it**: clusterctl is the command line tool for cluster-api. The cluster has to be prepared with a configuration file containing the details about the vSphere environment. That way the cluster knows how to speak with the vSphere infrastructure.
4. **Provision the kubernetes cluster to the cloud provider**: A YAML manifest has to be generated with clusterctl containing the details of the kubernetes cluster to deploy and then apply it.
5. **Move the cluster-api components to the kubernetes cluster**: We then need to connect to the cluster i SSH, run step 3 against it and then move the components from the bootstrap cluster using clusterctl.
6. **Decommission the bootstrap cluster**: The last step is to delete the bootstrap kind cluster if you have no more use for it.