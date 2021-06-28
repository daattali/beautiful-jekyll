# Kubernetes cluster arch
types of nodes
- master
- workers

Control plane - controls the cluster.
- runs on master node
- Kubernetes API server
- Scheduler - assigns a worker node to each component of your application
- Controller manager - cluster level functions
- etcd - distirbuted data store for cluster config

worker nodes
- container runtime
- kubelet - talks to the API server and manages containers on its node
- kubernetes service proxy / kube-proxy - load balances network traffic between app components

You have three worker nodes, which are VMs running Docker and the Kubelet, and you have a master node that controls the whole system. Honestly, we don’t know if a single master node is hosting all the individual components of the Kubernetes Control Plane or if they’re split across multiple nodes. It doesn’t really matter, because you’re only interacting with the API server, which is accessible at a single endpoint.

# logical arch

A pod is a group of one or more tightly related containers that will always run together on the same worker node and in the same Linux namespace(s).

pod can contain as many containers as you want
replication controller - creates maintains pods
service - pods can die anytime, when pod changes its ip also changes so need a service with a static ip

when there is more than one pod, service acts like a load balancer

## why pods
Containers are designed to run only a single process per container (unless the process itself spawns child processes). 
If you run multiple unrelated processes in a single container, it is your responsibility to keep all those processes running, manage their logs, and so on, can face issues with crashes and logging.

you can run closely related processes together but isolated in different containers in a single pod.

 Because all containers of a pod run under the same Network and UTS namespaces (we’re talking about Linux namespaces here), they all share the same hostname and network interfaces. Similarly, all containers of a pod run under the same IPC namespace and can communicate through IPC. In the latest Kubernetes and Docker versions, they can also share the same PID namespace, but that feature isn’t enabled by default.
 
 processes running in containers of the same pod need to take care not to bind to the same port
 
  All the containers in a pod also have the same loopback network interface, so a container can communicate with other containers in the same pod through localhost.
  
  All pods in a Kubernetes cluster reside in a single flat, shared, network-address space
  
  why to split multi tier applications into different pods?
  - to make use of the CPU/mem capabilities of the different machines
  - individual scaling

when to use multiple containers in single pod
- when app consists of one main process and one or more complementary processes (sidecars)

 A container shouldn’t run multiple processes. A pod shouldn’t contain multiple containers if they don’t need to run on the same machine.
 
 parts of a pod definition:
 - metadata - name, namespace, labels
 - spec - actual description of the pod's containers, volumes
 - status - pod condition, description and status of each container, internal IP

Container logs are automatically rotated daily and every time the log file reaches 10MB in size

When you want to talk to a specific pod without going through a service, Kubernetes allows you to configure port forwarding to the pod

 Organizing pods and all other Kubernetes objects is done through labels.
 
 A label is an arbitrary key-value pair you attach to a resource, which is then utilized when selecting resources using label selectors (resources are filtered based on whether they include the label specified in the selector). A resource can have more than one label, as long as the keys of those labels are unique within that resource.
 
 A canary release is when you deploy a new version of an application next to the stable version, and only let a small fraction of users hit the new version to see how it behaves before rolling it out to all users. This prevents bad releases from being exposed to too many users.
 
 label selectors
 
 the whole idea of Kubernetes is hiding the actual infrastructure from the apps that run on it. But if you want to have a say in where a pod should be scheduled, instead of specifying an exact node, you should describe the node requirements and then let Kubernetes select a node that matches those requirements. This can be done through node labels and node label selectors.
 
 setting the nodeSelector to a specific node by the hostname label may lead to the pod being unschedulable if the node is offline
 
 Annotations are also commonly used when introducing new features to Kubernetes. Usually, alpha and beta versions of new features don’t introduce any new fields to API objects. Annotations are used instead of fields, and then once the required API changes have become clear and been agreed upon by the Kubernetes developers, new fields are introduced and the related annotations deprecated.
 
 Linux namespaces which are used to isolate processes from each other. Kubernetes namespaces provide a scope for objects names.
 
 
 when different users deploy pods across different namespaces, those pods are isolated from each other and can’t communicate, but that’s not necessarily the case. Whether namespaces provide network isolation depends on which networking solution is deployed with Kubernetes. When the solution doesn’t provide inter-namespace network isolation, there is nothing preventing a pod from sending traffic, such as HTTP requests, to the other pod.
 
 # replication and other controllers: deploying managed pods
 