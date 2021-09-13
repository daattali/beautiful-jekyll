---
layout: post
title: Interacting with containerd runtime for kubernetes
DATE: 
subtitle: ''
metadescription: Since docker deprecation in kubernetes, find out how to interact
  with the containerd runtime

---
If you work with or learn Kubernetes, you probably know the docker is now deprecated. While most people are comfortable with the docker cli, you now need to use another runtime such as containerd or CRI-O.

I am currently in the process of learning kubernetes and I went with containerd for no particular reason as I am not knowledgeable on the topic. However, I decided to write this piece to help those who are in the same boat get their bearing around containerd. I opted to show a few different things that I feel may be valuable if you are using containerd with kubernetes. I will try to update this blog with more commands when I need new ones.

#### Containerd command line: ctr

Everyone knows docker to interact with its eponymous container runtime. The default tool to interact with containerd is named "ctr". Although not as intuitive as docker, ctr is fairly user friendly and easy to use.

* **Use sudo**

If you don't use sudo, you will get a permission error because your current user doesn't have the rights on the containerd socket file (/run/containerd/containerd.sock).

    ctr: failed to dial "/run/containerd/containerd.sock": connection error: desc = "transport: error while dialing: dial unix /run/containerd/containerd.sock: connect: permission denied"

* Specify the namespace

By default, containerd will use a default namespace, however, kubernetes uses its own containerd namespace called "k8s.io". If you don't specify this namespace in your commands, your results will be empty. 

    - No namespace specified
    ------------------------
    ubuntu@c1-cp1:~$ sudo ctr containers ls
    CONTAINER    IMAGE    RUNTIME
    
    
    - k8s.io namespace
    ------------------
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
    