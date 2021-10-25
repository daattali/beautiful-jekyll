---
layout: post
title: Octant - VMware open-source UI dashboard for Kubernetes
DATE: 
subtitle: ''
metadescription: Quickly install a comprehensive kubernetes UI dashboard with Octant,
  a VMware open-source project

---
Octant is an open source project to provide a powerful dashboard for Kubernetes. It was originally developped by Heptio and fell under the Tanzu umbrella when VMware acquired the company back in late 2018.

![](/img/octant0.png)

If you use Kubernetes, be it for learner or in production you are no stranger to kubectl (and you shouldn't). However, sometimes it would be useful to get a visual view of what's going on and be able to run a few actions from there as well. 

There is a number of existing projects for Kubernetes Dashboards suchs as Web UI (Dashboard) which is probably the most popular. However, it runs in Kubernetes so it uses some resources. Because I run a mini-pc with k3s with limited resources (core-i3 with 4 HT vCPU and 8GB of ram), I want to reduce the overhead as much as possible to save the capacity for actual workloads. 

This is where Octant shines, it is a simple app you run on you workstation that will connect to whatever kubernetes cluster is defined in your kubeconfig file. Meaning it uses the resources of your workstation instead of those of the cluster.

And because it uses the kubeconfig file you don't need to worry about authentication or user accounts since your users most likely already have their own kubeconfig file with their own permissions on the kubernetes resources so that's taken care of.

![](/img/octant1.png)

Before cracking on with Octant, make sure you can interact with you kubernetes cluster with kubectl on your workstation. 

    PS> kubectl get node
    
    NAME      STATUS   ROLES                  AGE     VERSION
    mini-01   Ready    control-plane,master   5d16h   v1.21.5+k3s2

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

### Download Octant

First we need to download Octant. It is available on Linux, Windows and MacOS, both on 64bit as well as ARM and ARM64. I will download the Windows build in my case.

* Head over to [https://octant.dev/](https://octant.dev/ "https://octant.dev/") and click **Download Octant** to be redirected to the latest version.

![](/img/octant2.png)

* Here you get the choice to use the **portable version** (zip file) that will run a local web server on port 7777 or the **installer** that will open the dashboard in the app itself.

![](/img/octant3.png)

* Whichever you choose you may need to bypass the windows warning about unknown signature. Then it is just a case of running the .exe file and it will open the dashboard. Again, your kubeconfig must be valid and your cluster running.

### Octant dashboard UI

You should end up on this dashboard in which you can visualize your environment. 

![VMware Octant kubernetes UI dashboard](/img/octant6.png)

#### Top right corner

A few things you can do quickly from the top right corner include:

* Switch between **contexts** (if your kubeconfig file includes more than one).

![](/img/octant4.png)

* Switch between **namespaces**. In my case, it defaults to the "tv-automation" namespace since it is how my kubeconfig file is configured.

![](/img/octant5.png)

* Apply YAML by typing it in or by feeding a file to it.

![](/img/octant7.png)

#### Navigation pane

The Octant navigation pane on the left lets you display several types of resources:

* **Applications**: displays your pods and deployments by name with their resource usage.

![](/img/octant8-1.png)

If you click on it you will get details about the resource and interdependencies. In the screenshot below you can see the related service, ingress, persistentVolumeClaim, replicaSet and deployment. You can also then click on the resource on the right ahand side to quickly get access to it.

![](/img/octant9.png)

**Namespace Overview**: In this pane you will find all the namespaced resources (aka. _kubectl api-resources --namespaced=true_).

![](/img/octant10.png)

You can then browse through your namespaced resources and roam through relationships just like you would in the vSphere client to access the datastore related to a cluster for instance. 

The great thing is that you can perform a few actions such as changing deployment's replicas number. In the example below I changed the replicas number from 3 to 1.

![](/img/octant11.png)

In the YAML tab you can even display the manifest file ( -o yaml) and update it on the fly.

![](/img/octant12.png)

* **Cluster Overview**: In this section you will find the non-namespaced resources (aka. _kubectl api-resources --namespaced=false_). For instance, you can see you few persistentVolumes I have in the cluster.

![](/img/octant13.png)

* **Plugins**: I haven't tested the plugin section as I am not there yet. You can find more details about it in the [documentation]().