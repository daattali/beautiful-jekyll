---
layout: post
title: Interacting with containerd runtime for kubernetes
DATE: 
subtitle: ''
metadescription: Since docker deprecation in kubernetes, find out how to interact
  with the containerd runtime

---
If you work with or learn Kubernetes, you probably know the [docker is being deprecated](https://kubernetes.io/blog/2020/12/02/dont-panic-kubernetes-and-docker/). While most people are comfortable with the docker cli, you now need to use another runtime such as containerd or CRI-O.

![containerd ctr kubernetes](/img/ctr.png "containerd ctr kubernetes")

I am currently in the process of learning kubernetes and I went with containerd for no particular reason as I am not knowledgeable on the topic. However, I decided to write this piece to help those who are in the same boat get their bearing around containerd. 

I will try to update this blog with more commands when I need new ones.

## Kubernetes and container runtimes

Although you probably know what a container runtime is if you are reading this, I want to quickly touch base on the term to avoid the confusion that usually come with Docker and Kubernetes.

Disclaimer, you most likely (hopefully) won't need these often as Kubernetes takes care of it for you. Still I find it interesting to fiddle with it and opted to show a few different things that I feel may be valuable if you are using containerd with kubernetes. 

## Containerd command line: ctr

Everyone knows docker to interact with its eponymous container runtime. The default tool to interact with containerd is named "ctr". Although not as intuitive as docker, ctr is fairly user friendly and easy to use.

* **Use sudo**

If you don't use sudo, you will get a permission error because your current user doesn't have the rights on the containerd socket file (/run/containerd/containerd.sock).

    ctr: failed to dial "/run/containerd/containerd.sock": connection error: desc = "transport: error while dialing: dial unix /run/containerd/containerd.sock: connect: permission denied"

* **Specify the namespace**

By default, containerd will use a default namespace, however, kubernetes uses its own containerd namespace called "k8s.io". If you don't specify this namespace in your commands, your results will be empty. 

    - No namespace specified
    ------------------------
    ubuntu@c1-cp1:~$ sudo ctr containers ls
    CONTAINER    IMAGE    RUNTIME
    
    
    - k8s.io namespace specified
    ----------------------------
    ubuntu@c1-cp1:~$ sudo ctr -n k8s.io container ls
    CONTAINER    IMAGE                              RUNTIME
    132...a8a    k8s.gcr.io/etcd:3.5.0-0            io.containerd.runc.v2
    144...7b3    k8s.gcr.io/coredns/coredns:v1.8.4  io.containerd.runc.v2
    ...
    
    
    - List namespaces
    -----------------
    ubuntu@c1-cp1:~$ sudo ctr namespaces ls
    NAME   LABELS
    k8s.io
    

#### Containerd help

Just type the property you want information about to get help on it, just like with esxcli for instance. You can also add -h to your commands.

![containerd ctr help](/img/containerdhelp-1.png "containerd ctr help")

#### List containers

To list the running containers, use the following command. You will find the Container ID which is useful when you need to kill one, the image and the runtime (which is containerd obviously). 

    ubuntu@c1-cp1:~$ sudo ctr -n k8s.io container ls
    CONTAINER    IMAGE                              RUNTIME
    132...a8a    k8s.gcr.io/etcd:3.5.0-0            io.containerd.runc.v2
    144...7b3    k8s.gcr.io/coredns/coredns:v1.8.4  io.containerd.runc.v2
    088...da4    k8s.gcr.io/pause:3.5               io.containerd.runc.v2
    0b3...00b    k8s.gcr.io/pause:3.5               io.containerd.runc.v2
    ...
    
    ubuntu@c1-cp1:~$ sudo ctr -n k8s.io container ls | grep etcd
    132...a8a    k8s.gcr.io/etcd:3.5.0-0            io.containerd.runc.v2
    76f...cb6    k8s.gcr.io/etcd:3.5.0-0            io.containerd.runc.v2
    
    Note that you can also find the container ID with "kubectl describe".
    ubuntu@c1-cp1:~$ k describe pods -n kube-system -l component=etcd |grep ID
        Container ID:  containerd://132...a8a
        Image ID:      k8s.gcr.io/etcd@sha256:9ce...b6d

**_What are "k8s.gcr.io/pause:" containers_**? From what I could gather online, "pause" is an infrastructure container that sets up the network namespace for the pod before provisioning the actual containers. [Source](https://groups.google.com/g/kubernetes-users/c/jVjv0QK4b_o "k8s.gcr.io/pause")

#### Kill a container

Because you never know when you will need the big guns, you can kill a container using ctr directly. Note that kubelet will restart it if it is configured to do so. First you need to find the container ID, then use "task" to kill it.

This can be useful when you need to restore etcd, in which case the process must be stopped manually.

    I am killing the etcd container
    -------------------------------
    ubuntu@c1-cp1:~$ sudo ctr -n k8s.io task kill 132...a8a

![kill containerd container](/img/etcdkill.png "kill containerd container")

#### Print containerd version

You can find the current latest containerd version on their [official page](https://github.com/containerd/containerd/releases "containerd latest version"). To find your version, use the "version" parameter.

    ubuntu@c1-cp1:~$ sudo ctr -n k8s.io version
    Client:
      Version:  1.5.2-0ubuntu1~20.04.2
      Revision:
      Go version: go1.13.8
    
    Server:
      Version:  1.5.2-0ubuntu1~20.04.2
      Revision:
      UUID: 4976b576-650b-470c-9e9d-f92b6c8c7fc4

#### List container images

To display the list of pulled images, use the image property. I had to shrink the screenshot to make it a bit more readable for you.

    ubuntu@c1-cp1:~$ sudo ctr -n k8s.io image ls

![list containerd images](/img/ctrimagels.png "list containerd images")

## Wrap up

Kubernetes has been the fastest growing container orchestrator and is without a doubt the future of where infrastructure is going. OpenShift, Tanzu and all their competitors are the living proof of that as well as the ever growing demand for DevOps/SRE engineers.

While virtualisation isn't going anywhere anytime soon, VI admins can no longer ignore the container technologies which are now a must have to our tool belts.