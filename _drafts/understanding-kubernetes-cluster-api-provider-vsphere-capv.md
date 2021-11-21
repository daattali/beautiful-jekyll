---
layout: post
title: Understanding Kubernetes Cluster API Provider vSphere (CAPV)
DATE: 
subtitle: ''
metadescription: Find out about declarative Kubernetes cluster creation with Kubernetes
  Cluster API Provider vSphere (CAPV)

---
I recently got into Kubernetes Cluster API Provider vSphere (CAPV) to understand what it is, what it does and where it fits in the Kubernetes and VMware ecosystem. The answer is a lot simpler than it seems and it is already used by several companies such as VMware (Tanzu Kubernetes Grid) or Giant Swarm to only name a couple. If you're wondering, the three "kubernetes turtles" is the Cluster-API logo.

![](/img/capv-banner.png)

So, the way Kubernetes provisions resources is declaratively through YAML manifest describing the state you want them to be in. By default these manifests cover "vanilla" Kubernetes objects such as deployments, pods, replicasets, services, ingress, you name it. You can get the list by running "_kubectl api-resources_". 

### What is Cluster API Provider vSphere (CAPV)

Projects like [cluter-api](https://cluster-api.sigs.k8s.io/) expand the capabilities of Kubernetes by offering the possibility to interface with [many cloud providers ](https://cluster-api.sigs.k8s.io/reference/providers.html)such as AWS, Azure, Sidero, etc to provision Kubernetes workload clusters. These extra capabilities are in the form of Custom Resource Definitions (CRD) and controllers that know how to "speak" (API) to these cloud providers to deploy the nodes as VMs and then create a cluster with kubeadm. The cluster-api resources are installed in what is referred to as a _kubernetes management cluster_ that remains and is used to provision Kubernetes clusters on a cloud provider.

In our case we are interested in the vSphere provider called Cluster API Provider vSphere or CAPV. For instance, you can see pretty much the same steps when getting started with Tanzu Community Edition, except it is made a lot simpler through UI and automation. In this post we are doing essentially the same steps but manually, that way we can see what's going on behind the scenes.

![How to install Cluster API Provider vSphere (CAPV)](/img/capv-diagram_1.png)

The steps are as follows to get started with cluster-api:

1. **Install Kind on a bootstrap VM**: We will use a debian VM to run a temporary cluster with Kind and delete it at the end. 
2. **Create a bootstrap cluster with Kind**: You could turn an existing kubernetes cluster in a management cluster but the more common process is to use a temporary kind cluster to provision a kubernetes cluster on your cloud provider and then move the cluster-api components to it, rendering the temporary cluster obsolete.
3. **Download clusterctl and initialize the temporary cluster with it**: clusterctl is the command line tool for cluster-api. The cluster has to be prepared with a configuration file containing the details about the vSphere environment. That way the cluster knows how to speak with the vSphere infrastructure.
4. **Provision the kubernetes cluster to the cloud provider**: A YAML manifest has to be generated with clusterctl containing the details of the kubernetes cluster to deploy and then apply it.
5. **Move the cluster-api components to the kubernetes cluster**: We then need to connect to the cluster i SSH, run step 3 against it and then move the components from the bootstrap cluster using clusterctl.
6. **Decommission the bootstrap cluster**: The last step is to delete the bootstrap kind cluster if you have no more use for it.

### Getting started with Cluster API Provider vSphere (CAPV)

Let's dig into it and see how we can get a Kubernetes cluster-API management cluster in vSphere in 6 steps. While this is more complicated than Tanzu Community Edition that offer a shiny web UI, it is still made easy for thanks to the efforts of the team behind the cluster-API project and kubeadm.

#### Prerequisites

There are a few things I want to touch on before starting with Cluster-API. The bootstrap machine used in this how-to is an Ubuntu Server VM.

* **Download and deploy a Kubernetes OVA**: This will be the template Cluster-API will use to deploy kubernetes nodes on vSphere. I used the [OVAs provided by VMware](https://customerconnect.vmware.com/downloads/get-download?downloadGroup=TCE-090) for Tanzu Community Edition where you can choose between ubuntu and photon. I downloaded ubuntu-2004-kube-v1.21.2+vmware.1-tkg.1-7832907791984498322.ova at the time of this writing. You then need to deploy the OVA to your vSphere environment and turn it into a template.
* **Have a bootstrap machine**: Ensure you have a machine with [Docker ](https://docs.docker.com/engine/install/)and [kubectl ](https://kubernetes.io/docs/tasks/tools/)installed to make it more convenient. You can use a Linux VM for instance if you don't want to mess with your workstation. 

#### Step 1 - Install Kind on a bootstrap VM

In our how-to, we are using an Ubuntu VM, however, you can find the procedure for MacOS and Windows in the official [Kind documentation](https://kind.sigs.k8s.io/docs/user/quick-start/#interacting-with-your-cluster).

    curl -Lo ./kind https://kind.sigs.k8s.io/dl/v0.11.1/kind-linux-amd64
    chmod +x ./kind
    mv ./kind /usr/bin/kind

#### Step 2 - Create a bootstrap cluster with Kind

Creating a bootstrap kind cluster is as easy as it gets. Just run this one liner, it will create the "nested" kubernetes cluster and create the Kubeconfig file on your machine so you can connect to it directly.

    kind create cluster

The output should look like so:

![](/img/capv-1.png)

At this point you should already be able to query your kind cluster with kubectl.

![](/img/capv-2.png)

#### Step 3 - Download clusterctl and initialize the temporary cluster with it

Clusterctl is the Cluster-API command line utility that will let you initialize a management cluster. We need to download the utility, move it in our PATH and initialize (prepare) the cluster.

* First let's download the utility, make it executable and move it to our PATH. This example uses clusterctl version 1.0.1 but check for the latest [clusterctl release here](https://github.com/kubernetes-sigs/cluster-api/releases).

    curl -L https://github.com/kubernetes-sigs/cluster-api/releases/download/v1.0.1/clusterctl-linux-amd64 -o clusterctl
    chmod +x ./clusterctl
    sudo mv ./clusterctl /usr/local/bin/clusterctl

* Then create the YAML clusterctl configuration file.

    mkdir ~/.cluster-api
    nano ~/.cluster-api/clusterctl.yaml

* Specify the settings of your vSphere environment following this format:

These are case sensitive so pay attention to it. You will obviously have to adapt this file to your environment. Note that it is better to do it with a file since the password won't be in your bash history and you can remove it once done. These fields are specific to vSphere obviously and clusterctl will know about that in the next step when we specify the provider.

    ## -- Controller settings -- ##
    VSPHERE_USERNAME: "xavier-adm@lab.priv"
    VSPHERE_PASSWORD: "Uh uh"
    
    ## -- Required workload cluster default settings -- ##
    VSPHERE_SERVER: "192.168.1.102"
    VSPHERE_DATACENTER: "LAB01-DC"
    VSPHERE_DATASTORE: "LAB01-VSAN"
    VSPHERE_NETWORK: "management"
    VSPHERE_RESOURCE_POOL: "*/Resources" 
    VSPHERE_FOLDER: "CAPV" 
    VSPHERE_TEMPLATE: "ubuntu-2004-kube-v1.21.2+vmware.1"
    CONTROL_PLANE_ENDPOINT_IP: "192.168.1.140" 
    VSPHERE_TLS_THUMBPRINT: "D5:...:0E"
    EXP_CLUSTER_RESOURCE_SET: "true" 
    VSPHERE_SSH_AUTHORIZED_KEY: "ssh-rsa AAAAB3N...+G/Xpnc>
    VSPHERE_STORAGE_POLICY: "" 

* Then we want to initialize our kind kubernetes cluster as a management cluster with clusterctl. Note that vSphere is the provider here, you would change it to aws, azure, alibabacloud or whatever else should you deploy to some other cloud provider.

    clusterctl init --infrastructure vsphere

The output should look something like this. As you can see clusterctl does the heavy lifting for us here.

    root@ubuntu:~# clusterctl init --infrastructure vsphere
    Fetching providers
    Installing cert-manager Version="v1.5.3"
    Waiting for cert-manager to be available...
    Installing Provider="cluster-api" Version="v1.0.1" TargetNamespace="capi-system"
    Installing Provider="bootstrap-kubeadm" Version="v1.0.1" TargetNamespace="capi-kubeadm-bootstrap-system"
    Installing Provider="control-plane-kubeadm" Version="v1.0.1" TargetNamespace="capi-kubeadm-control-plane-system"
    I1119 14:53:44.492746    6548 request.go:665] Waited for 1.043003371s due to client-side throttling, not priority and fairness, request: GET:https://127.0.0.1:46309/apis/clusterctl.cluster.x-k8s.io/v1alpha3?timeout=30s
    Installing Provider="infrastructure-vsphere" Version="v1.0.1" TargetNamespace="capv-system"
    
    Your management cluster has been initialized successfully!
    
    You can now create your first workload cluster by running the following:
    
      clusterctl generate cluster [name] --kubernetes-version [version] | kubectl apply -f -
    

#### Step 4 - Provision the kubernetes cluster to the cloud provider

At this point we have a bootstrap management cluster. What we want to do next is to provision a workload cluster to our vSphere environment (which will later on be our management cluster).

* First we need to generate a YAML manifest to describe the workload cluster to deploy. This step does not deploy anything, we are using clusterctl to create a YAML file.

Adjust the fields as necessary. In this example I am deploying a cluster named _capv-management_ with 1 control plane node and 1 worker node, in Kubernetes version 1.21.1 since it is the version of the OVA I deployed and I redirect the output to _cluster.yaml_.

    clusterctl generate cluster capv-management \
        --infrastructure vsphere \
        --kubernetes-version v1.21.1 \
        --control-plane-machine-count 1 \
        --worker-machine-count 1 > cluster.yaml

fd