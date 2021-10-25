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

My kubeconfig file is located in %USERPROFILE%\\.kube\\config

    PS> $env:KUBECONFIG
    
    C:\Users\xavier\.kube\config

I retrieved it from my kubernetes node and changed the IP for 127.0.0.1 to the node's LAN IP.

    PS> kubectl config view
    
    apiVersion: v1
    clusters:
    - cluster:
        certificate-authority-data: DATA+OMITTED
        server: https://192.168.1.233:6443
      name: default
    contexts:
    - context:
        cluster: default
        namespace: tv-automation
        user: default
      name: default
    current-context: default
    kind: Config
    preferences: {}
    users:
    - name: default
      user:
        client-certificate-data: REDACTED
        client-key-data: REDACTED

g