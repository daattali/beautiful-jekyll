---
layout: post
title: GitOps with Kubernetes, vSphere, Flux, Helm and Cluster-API
DATE: 
subtitle: ''
metadescription: ''

---
A couple weeks back I wrote a piece about the [vSphere provider of Cluster-API ](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/)for Kubernetes and I now want to expand on this and drill into using GitOps to manage Kubernetes clusters in vSphere.

In the blog mentioned above, we install cluster API in a bootstrap cluster which allows us to provision clusters in a vSphere environment. While this works and is a valid approach, tracking changes and storing manifests may prove challenging. This is where GitOps comes into play. GitOps is a term that was created by the company [WeaveWorks ](https://www.weave.works/technologies/gitops/)in 2017 which describes a way to manage your kubernetes clusters declaratively from a Git repository with version and change tracking. In their own words: 

> _GitOps works by using Git as a single source of truth for declarative infrastructure and applications._

That way, instead of manually storing and applying your yaml manifest with kubectl, you will store them in a Git repository that is monitored, and when a change is detected, the new manifest is applied in the environment. Git allows you to track who changed what, revert to a previous state, validate changing through pull requests... Now I am no software developper but it brings the benefits of git to your kubernetes infrastructure.

### Components

Because my audience is mostly VMware centric and Kubernetes might be a fairly new or obscur subjet, I will start by describing the components involved in our GitOps lab environment.

#### Bootstrap cluster

The Bootstrap cluster is a kubernetes cluster that runs the components for cluster-API and Flux. It is sort of a "meta" cluster (called management cluster) in the sense that it does not run production workloads. Instead it provisions and maitains the clusters that run production workloads. It can be a permanent cluster or a temporary one created with kind in a VM for instance (my use case).

#### FluxCD

Flux is the CD (Continuous Delivery) part of our environment. It is a collection of components, called GitOps toolkit, which offer a collection of kubernetes controllers that monitor a Git repository, install Helm releases, apply changed manifests, kustomization overlays... More details in the [official documentation](https://fluxcd.io/docs/). These components are installed in the management (bootstrap) cluster. 

#### Cluster API

Cluster API is a Kubernetes extension that lets us interact with various cloud providers (including vSphere) trop create Kubernetes clusters declaratively. More details in this [previous blog](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/).

#### vSphere environment

While GitOps applies to many use cases such as maintaining traditional Kubernetes workloads, here we want to deal with kubernetes cluster running in vSphere through cluster-API.

#### Helm

Helm is a convenient way to package applications. Instead of applying a yaml manifest straight away, a template with variable names exists and you can change the values of these variable when you create a Helm release. That way you can easily create a bunch of resources and significantly simplify the deployment and maintenance workflow.