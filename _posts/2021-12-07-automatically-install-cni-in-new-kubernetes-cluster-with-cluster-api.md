---
layout: post
title: Automatically install CNI in new kubernetes cluster with Cluster API
DATE: 
subtitle: ''
metadescription: Find out how to easily automate the CNI install in new kubernetes
  clusters with Cluster API.
image: "/img/cni-clusterresourceset-2.png"

---
In a [previous blog ](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/)we discovered Cluster API and how it allows you to declaratively deploy Kubernetes clusters to your favourite cloud provider, ours being vSphere obviously! If you have no idea what Cluster API and CAPV are, I suggest you put this reading on pause and start with the blog aformentioned.

While this is great, one thing that may be frustrating is the fact that, once the cluster is deployed, you have to retrieve the kubeconfig file for the cluster and install a CNI in order for it to go in a **Ready** state. 

Thankfully there is a way to automate it and this is what we will describe here. Spoiler alert, the solution to this is called a [**ClusterResourceSet**](https://github.com/kubernetes-sigs/cluster-api/blob/main/docs/proposals/20200220-cluster-resource-set.md). Note that this blog is also valid for other Cluster API providers.

![Automatically install a CNI in your kubernetes clusters deployed with Cluster API](/img/cni-clusterresourceset-2.png)

### 1 - CNI ConfigMap

I'm not really going to get into what a configmap is, except to say it is a kubernetes resource that includes configuration settings to pass to another resource. In this case, the ConfigMap will contain the content of the Calico yaml manifest.

Note that the name of the configMap must match the name of the one specified in the clusterResourceSet. All the actions below are to perform in the bootstrap (management) cluster.

* **First download the latest calico yaml manifest.**

Note that it doesn't have to be Calico, it can be some other CNI if required.

    curl -L https://docs.projectcalico.org/manifests/calico.yaml -o calico.yaml

* **Create a configMap from the Calico manifest file.**

If you wish to create a cluster in a specific namespace, you want to place the configMap in this same namespace.

    kubectl create configmap calico-configmap --from-file=calico.yaml -o yaml --dry-run=client > calico-configmap.yaml

* **Apply the Calico configMap.**

Again, this is to be applied in the bootstrap/management cluster.

    kubectl apply -f calico-configmap.yaml

### 2 - ClusterResourceSet

The [**ClusterResourceSet**](https://github.com/kubernetes-sigs/cluster-api/blob/main/docs/proposals/20200220-cluster-resource-set.md) is a feature of the Cluster API project that lets you automatically install a resource to a newly created cluster. The current use cases are mostly for CNI (network) and CSI (storage provider).

In our case, we apply the Calico CNI through a ConfigMap that contains the latest manifest. The ClusterResourceSet object is applied to a cluster through a **matchLabel**. Which is similar to how you tie pods to a service for instance except here we use a **ClusterSelector** tag.

the ConfigMap named calico-configmap is applied to all clusters with the label "cni: calico". Again, you need to pay attention to namespaces and want to keep all these resources together.

* **Create a clusterResourceSet yaml manifest with this content (adjusted to your needs). You can name it calico-clusterResourceSet.yaml for instance.**

You may want to double check the apiVersion with "kubectl api-resources" as these things change quite frequently.

    ---
    apiVersion: addons.cluster.x-k8s.io/v1alpha3
    kind: ClusterResourceSet
    metadata:
      name: calico
    spec:
      clusterSelector:
        matchLabels:
          cni: calico 
      resources:
      - kind: ConfigMap
        name: calico-configmap

* Apply the clusterResourceSet in your environment.

  kubectl apply -f calico-clusterResourceSet.yaml

### 3 - Cluster

The next steps are very much the same as what we saw in the [previous blog](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/) about CAPV. Except we need to add the "cni : calico" label to our cluster manifest once it is generated with `clusterctl generate cluster`.

You can either do it imperatively once the cluster is created:

    kubectl label cluster cluster-50 cni=calico

Or you can add the label tag in the cluster's manifest:

    apiVersion: cluster.x-k8s.io/v1beta1
    kind: Cluster
    metadata:
      name: cluster-50
      labels:
        cni: calico

Now every time you provision a new cluster, all you have to do in order to install Calico on it is to apply the "cni:calico" label to it.

### Wrap up

Kubernetes is a rising technology which more and more organizations are getting their hands on. Many of them don't really want to fiddle with the nitty gritty of clusters, nodes and such. They want to focus on what matters to them, the applications running in these clusters. This is why other companies leverage projects like Cluster API to offer managed kubernetes environment and take this burden off the customer's hands.

If you want to go a bit further, note that you can also normalize the labelling of your clusters with a kustomization file referrencing all the clusters and a [commonLabel tag](). And if you want to have one configmap and clusterResourceSet per cluster, you can add these to a Kustomization overlay per cluster and specify a namespace for them to avoid name/id duplicates.

Now this can be improved even more for more flexibility by using Helm charts and a GitOps approach with FluxCD but this will be the topic of a further blog post.