---
layout: post
title: Octant - VMware open-source UI dashboard for Kubernetes
DATE: 
subtitle: ''
metadescription: Quickly install a comprehensive kubernetes UI dashboard with Octant,
  a VMware open-source project

---
Octant is an open source project to provide a powerful dashboard for Kubernetes. It was originally developped by Heptio and fell under the Tanzu umbrella when VMware acquired the company back in late 2018.

If you use Kubernetes, be it for learner or in production you are no stranger to kubectl (and you shouldn't). However, sometimes it would be useful to get a visual view of what's going on and be able to run a few actions from there as well. 

  
There is a number of existing projects for Kubernetes Dashboards suchs as Web UI (Dashboard) which is probably the most popular. However, it runs in Kubernetes so it uses some resources. Because I run a mini-pc with k3s with limited resources (core-i3 with 4 HT vCPU and 8GB of ram), I want to reduce the overhead as much as possible to save the capacity for actual workloads. This is where Octant shines, it is a simple app you run on you workstation and it will connect to whatever kubernetes cluster is defined in your kubeconfig file.