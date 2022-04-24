---
layout: post
title: What is VMware Cloud Director CSE 3.1.3
metadescription: Find out about VMware Cloud Director CSE 3.1.3 new features
date: null
fb-img: /img/2022-04-20-17-44-16.png
draft: true
---

Up until now I never wrote about VMware Cloud Director because I'd never used it before. More recently I got involved in it as I was checking out the Cluster API VMware Cloud Director provider (CAPVCD) and got interested in the topic. I learned about CSE (Container Service Extension) and how it helps cloud providers propose a Kubernetes-as-a-Service offering to their tenants. Kubernetes is a complexe ecosystem that takes a lot of effort to wrap your head around, let alone run in production. For that reason, VMware put a lot of effort into developping CSE and currently CAPVCD. CSE is mostly used to run TKG (Tanzu Kubernetes Grid) clusters but it can accomodate vanilla Kubernetes clusters as well.

## What is Container Service Extension (CSE)?

First and foremost, let's define what CSE is for those that haven't heard of it! It is a plug-in for VMware Cloud Director that extends it to let you manage Kubernetes clusters. CSE helps VCD tenants provision Kubernetes clusters using a familiar consumption interface that has been around for a long time for virtual machines management. CSE lets you manage VMware Tanzu for vSphere, Vanilla kubernetes clusters and Tanzu Kubernetes Grid Integrated a.k.a. TKGI (Tanzu integrated with NSX-T). The [CSE doc](https://vmware.github.io/container-service-extension/cse3_1/INTRO.html) includes everything that I won't cover here since it is only an overview.

CSE works in a client-server model. The "server" runs as an extension of the VCD Rest API and the client component is a plugin to the command line tool vcd-cli. the CLI plugin knows how to talk to the VCD API using the extra endpoints exposed by the server component. This simplifies the process for user to create Kubernetes clusters in VCD.

![VCD CSE kubernetes cluster creation](/img/2022-04-23-11-25-35.png)

VMware Cloud Director CSE is of course popular among service providers that are looking to offer their customers an integrated way of deploying and managing Kubernetes clusters.

There are a few good articles out there talking about CSE such as [vBlog.nl](https://www.vblog.nl/install-cse-3-1-1-with-cloud-director-10-3-1/).

## Container Service Extension 3.1.3
