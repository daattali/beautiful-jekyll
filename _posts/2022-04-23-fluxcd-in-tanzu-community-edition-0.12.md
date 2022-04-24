---
layout: post
title: FluxCD in Tanzu Community Edition v0.12
description: Installing FluxCD in Tanzu Community Edition with the apps manager to manage Kubernetes resources in a GitOps fashion.
date: 2022-04-23T14:15:41.114Z
fb-img: /img/2022-04-23-preview.png
---

With Tanzu Community Edition v0.11, the contributors brought FluxCD in the app manager that comes with TCE (kapp). Mind you it was only the Flux Source controller which is the one that keeps track of the changes made in a Git repository and pulls the resources. Deployed by itself it isn't much use as there is nothing in the cluster to bring the resources defined in the git repo into the cluster. Sure you can install flux yourself in a jiffy but the point here is to use the TCEapp catalog. In version 0.12 (rc1 as I write these lines), the kustomize controller was added into the mix, making the whole thing a lot more interesting. [I recently wrote about GitOps](https://www.vxav.fr/2022-03-22-getting-started-with-gitops-in-argocd/) when I moved my home automation stuff to a private GitHub repo that is reconciled by ArgoCD. The most obvious difference is that FluxCD doesn't have a nice UI like ArgoCD so it is not as intuitive and visually appealing as ArgoCD but it is efficient and has other strong points. You can find the differences between the two products in this [blog](https://thenewstack.io/gitops-on-kubernetes-deciding-between-argo-cd-and-flux/).

If a lot of these terms like GitOps or FluxCD make no sense to you, you can always refer to the [documentation](https://fluxcd.io/docs/concepts/) where you will find a lot of information about how the different components work and interact between each other.

In this blog, we are going to deploy a Tanzu Community Edition unmanaged cluster, install FluxCD using the app manager and configure a Git repository to watch. Note that this is not production ready as I am using an unmanaged cluster. Also there is no Helm or notification controller (yet).

![Tanzu community edition with FluxCD](/img/2022-04-23-16-39-48.png)

## Install Tanzu CLI v0.12

You can install the Tanzu CLI manually or using Homebrew. I have Brew installed but this time I downloaded the [v0.12rc1 release](https://github.com/vmware-tanzu/community-edition/releases) from the release page using wget, unpacked it and then installed it on my linux machine with `./install.sh`.

I am using WSL and Docker for Windows which works quite well. However there is a condition where managed clusters have issues with docker on Windows so I stuck with unmanaged clusters for this blog as I don't have access to my vSphere lab just now. However it doesn't make a difference for the purpose of this writing.

## Deploy a Tanzu Unamanaged Cluster

Let's start by deploying an unmanaged cluster. This step is super easy as the whole bootstrapping process is automated by the Tanzu CLI. A TCE unmanaged cluster is simply a single node cluster running in Kind with the Tanzu bits installed on top of it, so no cluster API provider involved here. The prerequisite is of course that you have the Tanzu CLI installed and Docker running.

* Deploy an unmanaged cluster, I named mine "vxav-unmanaged". You can also use `um` as an alias of `unmanaged-cluster`. The process may take several minutes to complete, especially if it is the first time and it has to pull the images from the internet.

`tanzu unmanaged-cluster create vxav-unmanaged`

![deploy tanzu community edition unmanaged cluster](/img/2022-04-24-10-02-12.png)

Your kube context should switch automatically to the newly created cluster. You can then run commands against it like listing the nodes.

`kubectl get node`

![get TCE um nodes](/img/2022-04-24-10-05-11.png)

The list of pods running across all namespaces should look something like this.

`kubectl get pods -A`

![list TCE um pods](/img/2022-04-24-10-06-13.png)

At this point you have a Tanzu Community Edition unmanaged cluster running, how easy was that?

## Install FluxCD on Tanzu Community Edition

Now let's start using the Tanzu App manager to install Flux in TCE.

* Start by listing the available packages. In our case, the Flux controllers are the ones we're interested in, highlighted in yellow (I hope it is readable).

`tanzu package available list`

![Tanzu community edition flux packages](/img/2022-04-24-10-08-55.png)

* I nstall the FluxCD Source Controller.

The role of the FluxCD source controller is to watch a repository (Git, Helm or S3 bucket) and pull the resources (artifacts) locally for controllers to consume (among other things).

`tanzu package install flux-source-controller --package-name fluxcd-source-controller.community.tanzu.vmware.com --version 0.21.2`

![Install FluxCD source controller in Tanzu Community edition](/img/2022-04-24-10-11-15.png)

* Next install the FluxCD Kustomize Controller.

The role of the FluxCD Kustomize controller is to reconcile the cluster state from multiple sources provided by the Source controller (among other things).

`tanzu package install flux-kustom ize-controller --package-name kustomize-controller.fluxcd.community.tanzu.vmware.com --version 0.21.1`

![Install FluxCD kustomize controller in Tanzu Community edition](/img/2022-04-24-10-15-17.png)

You will find that a namespace has been automatically created for each controller. However, note that the FluxCD operations we'll do later will happen in the `flux-system` namespace.

``` go
k get ns
NAME                        STATUS   AGE
default                     Active   16h
flux-system                 Active   2m33s **
kube-node-lease             Active   16h
kube-public                 Active   16h
kube-system                 Active   16h
kustomize-system            Active   55s   **
local-path-storage          Active   16h
tanzu-package-repo-global   Active   16h
tkg-system                  Active   16h

```

You can also look at the custom resource definitions (CRDs) that have been added to the cluster. Those are what extend the Kubernetes API to understand what FluxCD works with, for instance, a source such as a Git repository.

`kubectl get crd -A | grep flux`

![FluxCD CRDs](/img/2022-04-24-10-19-34.png)

## Configure FluxCD on TCE

Anyway, now that FluxCD is installed in our cluster, it is time to configure it. We first need a location to store our manifests so I created a dummy public GitHub repository at [https://github.com/vxav/test-gitops](https://github.com/vxav/test-gitops). Next, in our cluster we will create a source that points to this repository and a kustomization that specifies where to look for manifests.

### Create a FluxCD Git repository source

* Create a manifest to create the FluxCD GitRepository source. I named mine `/tmp/gitrepo.yaml`

Make sure that you are pointing to the right branch. I set it to main but you may want to use another one. Also the public documentation is still referencing master which is being replaced by main. Note that you can add more advanced settings to your [sources](https://fluxcd.io/docs/components/source/gitrepositories/) but we'll stick to the basics here.

``` go
apiVersion: source.toolkit.fluxcd.io/v1beta1
kind: GitRepository
metadata:
  name: vxav-test-gitops
  namespace: flux-system
spec:
  interval: 1m
  url: https://github.com/vxav/test-gitops
  ref:
    branch: main
```

Pretty straightforward as you can see. Note that you will want to install it in the `flux-system` namespace as this is where the FluxCD controllers look (by default anyway). I changed the interval to 1 minute, specified the URL of my repo and the main branch.

* Apply the manifest in the cluster to create the custom resource that will be consumed by the FluxCD source controller.

``` go
kubectl apply -f /tmp/gitrepo.yaml

gitrepository.source.toolkit.fluxcd.io/vxav-test-gitops created
```

You can list your FluxCD sources by looking for the CRs (Customer Resources).

`kubectl get gitrepositories.source.toolkit.fluxcd.io  -n flux-system`

![FluxCD source CR in Tanzu](/img/2022-04-24-10-32-25.png)

### Create a FluxCD Kustomization

Here, the kustomization will tell the FluxCD Kustomize controller where to look for manifests to apply. For the sake of this demonstration I will set it to the root of the repository but this isn't what you would do in production. If you want an idea of a solid GitOps structure, you can refer to this public [GitOps template repository](https://github.com/giantswarm/gitops-template) provided by Giant Swarm to manage Cluster API clusters in a GitOps fashion. This would be even more relevant for Tanzu Community Edition managed clusters.

* Create a FluxCD kustomization manifest. I named mine `/tmp/kustomization.yaml`

```
/tmp/kustomization.yaml
apiVersion: kustomize.toolkit.fluxcd.io/v1beta2
kind: Kustomization
metadata:
  name: stuff
  namespace: flux-system
spec:
  interval: 1m0s
  path: .
  prune: true
  sourceRef:
    kind: GitRepository
    name: vxav-test-gitops
```

I gave it a silly name and put it in the `flux-system` namespace. Path is an important setting as it is where it will be looking for resources to reconcile. in SourceRef I specify the FluxCD source that I created earlier.

* Apply the manifest to create the customer resource that will be consumed by the FluxCD Kustomize controller.

``` go
k apply -f /tmp/kustomization.yaml
kustomization.kustomize.toolkit.fluxcd.io/stuff created
```

Again, you can look at the CR that was created.

`k get kustomizations.kustomize.toolkit.fluxcd.io  -n flux-system`

![kustomize CR in fluxCD TCE](/img/2022-04-24-10-43-40.png)

### Reconcile resources stored in GitHub with FluxCD

Out very basic GitOps structure is now ready and all that's left to do is to add resources in our GitHub repository for FluxCD to reconcile. Reconciliation refers to the actions to make the cluster state match the desired state.

If the flux command line tool is not installed in your machine, refer to the [Flux documentation](https://fluxcd.io/docs/installation/) to install it.

* Add a manifest to your GitHub repository. I used the common and boring example of an Nginx deployment but what we deploy doesn't matter. Pay attention to the commit ID.

![example deployment fluxcd](/img/2022-04-24-10-48-14.png)

* List the flux kustomizations done by the kustomize controller.

`flux get kustomizations`

![flux kustomization](/img/2022-04-24-10-51-01.png)

As you can see the kustomize controller picked up the commit ID.

* List the pods in the cluster.

`k get pod`

![example deployment fluxcd](/img/2022-04-24-10-52-16.png)

The nginx pods defined in our deployment should automagically appear as the manifest was retrieved by the source controller and applied by the kustomize controller.

Now you can play about with it, for instance I will change the number of replicas in the Git repo from 3 to 1 and push the change.

![flux git repo](/img/2022-04-24-10-53-53.png)

The kustomization should be picked up as before.

![flux kustomization](/img/2022-04-24-10-54-20.png)

The deployment will be scaled down and we should end up with a single pod in our deployment.

![flux reconciliation](/img/2022-04-24-10-54-55.png)

And that's it, we now have a Tanzu Community Edition cluster which resources are managed in a basic GitOps fashion by FluxCD.

## Wrap up

We discovered how to use the Tanzu app catalog to install FluxCD and manage or Tanzu Community Edition cluster in a GitOps fashion. While setting this up for a basic use case like this one is easy, it is that, a basic use case. Production environments will need to consider important factors such as secret encryption (FluxCD works well with Sealed Secrets and SOPS), private repositories, monitoring, lifecycling...

Note that I referred to the FluxCD resources with CRDs a lot but you can also use the `flux` command line to manage Flux. You can display sources, kustomizations, logs, you name it it's all there.

It is pretty cool to see the direction Tanzu Community Edition is taking and I hope the rest of the FluxCD components will be added to the list in future releases.
