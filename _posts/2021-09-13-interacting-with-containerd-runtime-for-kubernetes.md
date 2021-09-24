---
layout: post
title: Interacting with containerd runtime for kubernetes
DATE: 
subtitle: ''
metadescription: Since docker deprecation in kubernetes, find out how to interact
  with the containerd runtime

---
**EDIT on terminology**: In this blog I talk a lot about Container Runtime. In this context I should really be talking about Container Manager to be more accurate with the proper terminology. Refer to this very good [Twitter thread by Ivan Velichko  ](https://twitter.com/iximiuz/status/1423984739514454033)for more details.

If you work with or learn Kubernetes, you probably know that [docker is being deprecated](https://kubernetes.io/blog/2020/12/02/dont-panic-kubernetes-and-docker/). While most people are comfortable with the docker cli, you now need to use another runtime such as [containerd ](https://github.com/containerd/containerd)or CRI-O.

![containerd ctr kubernetes](/img/ctr.png "containerd ctr kubernetes")

I am currently in the process of learning kubernetes and I went with containerd for no particular reason as I am not knowledgeable on the topic. However, I decided to write this piece to help those who are in the same boat get their bearing around containerd.

I will try to update this blog with more commands when I need new ones.

## Use cases

Now, why do we care about interacting with the container runtime when Kubernetes is taking care of it for us you may think?

I will be updating this section as I figure out more use cases for it:

* **Etcd restore**: When restoring etcd from a snapshot, you need to stop the container directly if etcd was set up as a static pod as the output of kubectl is nothing but a [mirror pod](https://kubernetes.io/docs/tasks/configure-pod-container/static-pod/#behavior-of-static-pods), for instance if you created your cluster with kubeadm.
* **API server down**: If the API component is down for any number of reasons and kubectl isn't available, you may still want to interact with containers.
* **Exec in a container as a different user**: kubectl doesn't allow to run a command in a container as a different user (--user), which could be useful for troubleshooting purpose with root for instance. In which case, you need to use the CRI to do it. (Thanks to [u/lordkoba](https://www.reddit.com/r/kubernetes/comments/ppcg0s/what_are_your_use_cases_for_interacting_directly/hd3c9si?utm_source=share&utm_medium=web2x&context=3) for the tip)

Please, propose other use cases in the comments and I will add them here!

## Kubernetes and container runtimes

Although you probably know what a container runtime is if you are reading this, I want to quickly touch base on the term to avoid the confusion that usually comes with Docker and Kubernetes.

![containerd container runtime](/img/cri.png "containerd container runtime")

* **_Kubernetes_** is a container orchestration solution. It interact, among other things, with container runtimes which must be [CRI ](https://kubernetes.io/blog/2016/12/container-runtime-interface-cri-in-kubernetes/)compliant. _In kubernetes you interact with pods (which contain one or more containers)_.
* **_Container runtimes_** execute containers and manages container images on a node. You get to choose one when setting up your kubernetes nodes. _Interacts with containers (not pods)._
* **_Docker and containerd_** are both container runtimes.
* **_Containers_** are processes running on the nodes.

Do note that this is an incredibly overly simplified explanation but the point of this blog isn't to deep dive in the terminology.

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

    - I am killing the etcd container
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

#### Execute a command in a container as a different user

You know you can use kubectl exec -it mycont -- /bin/sh to open a shell in a pod container for instance? Well you can do the same thing with ctr. However, like Docker, ctr allows you to specify a different user which you cannot do with kubectl. Read below this code block to get a pod to test the permissions.

    - Find the container ID with "ctr -n k8s.io c ls" on the worker node
    - or "k describe pod | grep ID" on the control plane
    --------------------------------------------------------------------
    ubuntu@c1-cp1:~$ k describe pod security-context-demo | grep ID
    Annotations:  cni.projectcalico.org/containerID: e51...835
        Container ID:  containerd://a48...964
        
     - Find the PID of the process on the worker node (here PID=341884)
     ------------------------------------------------------------------
     ubuntu@c1-node2:~$ sudo ctr -n k8s.io task ls | grep a48...964
    a48...964    341884    RUNNING
    
    - Execute a command with "... task --exec-id <PID> <ContID> <CMD>"
    ------------------------------------------------------------------
    ubuntu@c1-node2:~$ sudo ctr -n k8s.io task exec --exec-id 341884 a48...964 /bin/sh
    
    - Display the user and try to create a file at the root: Failed
    ---------------------------------------------------------------
    whoami
    whoami: unknown uid 1000
    touch /test
    touch: /test: Permission denied
    exit
    
    - Now add --user root before the PID and try again: OK
    ------------------------------------------------------
    ubuntu@c1-node2:~$ sudo ctr -n k8s.io task exec --exec-id 341884 --user root a48...964 /bin/sh
    
    whoami
    root
    touch /test
    ls /test
    /test

You can test the permissions by provisioning the following [pod](https://kubernetes.io/docs/tasks/configure-pod-container/security-context/). Note that you need to change "allowPrivilegeEscalation: false" to "true" or you won't be able to execute as root.

    kubectl apply -f https://k8s.io/examples/pods/security/security-context.yaml

## Wrap up

Kubernetes has been the fastest growing container orchestrator and is without a doubt the future of where infrastructure is going. OpenShift, Tanzu and all their competitors are the living proof of that as well as the ever growing demand for DevOps/SRE engineers.

While virtualisation isn't going anywhere anytime soon, VI admins can no longer ignore the container technologies which are now a must have to our tool belts.