`Kubernetes` is a portable, extensible, open-source platform for managing containerized workloads and services, that facilitates both declarative configuration and automation. It has a large, rapidly growing ecosystem. Kubernetes services, support, and tools are widely available.


K8s as an abbreviation results from counting the eight letters between the "K" and the "s".


A Kubernetes cluster consists of a set of worker machines, called `nodes`, that run containerized applications. Every cluster has at least one worker node.

### Node Components
Node components run on every node, maintaining running pods and providing the Kubernetes runtime environment.

#### pods
Pods are the smallest deployable units of computing that you can create and manage in Kubernetes.

A Pod (as in a pod of whales or pea pod) is a group of one or more containers, with shared storage and network resources, and a specification for how to run the containers. A Pod's contents are always co-located and co-scheduled, and run in a shared context. A Pod models an application-specific "logical host": it contains one or more application containers which are relatively tightly coupled. 
In terms of `Docker` concepts, `a Pod` is similar to a group of Docker containers with shared namespaces and shared filesystem volumes.

Kubernetes is designed to accommodate configurations that meet all of the following criteria:

No more than `110 pods` per node

No more than `5000 nodes`

No more than `150000 total pods`

No more than `300000 total containers`

You can scale your cluster by adding or removing nodes. The way you do this depends on how your cluster is deployed.
Applications running in the same Pod share the same IP address and port space (net‐
work namespace), have the same hostname (UTS namespace)
Pods are described in a Pod manifest. The Pod manifest is just a text-file representa‐
tion of the Kubernetes API object. The Kubernetes API server accepts and processes Pod manifests before storing them
in persistent storage ( etcd ). The scheduler also uses the Kubernetes API to find Pods
that haven’t been scheduled to a node. The scheduler then places the Pods onto nodes
depending on the resources and other constraints expressed in the Pod manifests.


#### kubelet
An agent that runs on each node in the cluster. It makes sure that containers are running in a Pod.

The kubelet takes a set of PodSpecs that are provided through various mechanisms and ensures that the containers described in those PodSpecs are running and healthy. The kubelet doesn't manage containers which were not created by Kubernetes.

#### kube-proxy
kube-proxy is a network proxy that runs on each node in your cluster, implementing part of the Kubernetes Service concept.

kube-proxy maintains network rules on nodes. These network rules allow network communication to your Pods from network sessions inside or outside of your cluster.

kube-proxy uses the operating system packet filtering layer if there is one and it's available. Otherwise, kube-proxy forwards the traffic itself.

#### Container runtime
The container runtime is the software that is responsible for running containers.

Kubernetes supports several container runtimes: Docker, containerd, CRI-O, and any implementation of the Kubernetes CRI (Container Runtime Interface).

#### Addons
Addons use Kubernetes resources (DaemonSet, Deployment, etc) to implement cluster features. Because these are providing cluster-level features, namespaced resources for addons belong within the kube-system namespace.

Selected addons are described below; for an extended list of available addons, please see Addons.

#### DNS
While the other addons are not strictly required, all Kubernetes clusters should have cluster DNS, as many examples rely on it.

Cluster DNS is a DNS server, in addition to the other DNS server(s) in your environment, which serves DNS records for Kubernetes services.

Containers started by Kubernetes automatically include this DNS server in their DNS searches.

#### Web UI (Dashboard)
Dashboard is a general purpose, web-based UI for Kubernetes clusters. It allows users to manage and troubleshoot applications running in the cluster, as well as the cluster itself.

#### Container Resource Monitoring
Container Resource Monitoring records generic time-series metrics about containers in a central database, and provides a UI for browsing that data.

#### Cluster-level Logging
A cluster-level logging mechanism is responsible for saving container logs to a central log store with search/browsing interface.

#### Label

Labels are key/value pairs that can be attached to Kubernetes objects such as Pods and
ReplicaSets

#### Selector

When a Kubernetes object refers to a set of other Kubernetes objects, a label selector
is used



 #### Deploying a `kubernetes` cluster using kind

Create A cluster : `kind create cluster --name cluster-name`

Delete A cluster : `kind delete cluster --name cluster-name`

To interact with a specific cluster:  `kubectl cluster-info --context kind-cluster-name`

To View Active clusters : `kind get clusters`

list out all of the nodes : `kubectl get nodes`

list out all of the pods : `kubectl get pods`

view Kubectl version in json :  `kubectl version -o json`

Describe a node in details : `kubectl describe nodes node-name`

Delete all deployments: `kubectl delete deployments --all`

! [Udemy CourSe](https://www.youtube.com/watch?v=2CAU4xWdKVM&list=PLMPZQTftRCS8Pp4wiiUruly5ODScvAwcQ&index=3)

Deploy a container image in kubernetes from registry: `kubectl run ecommerce-api --image=raihankhanraka/ecommerce-api:v1.1`

Deploy a container image i kubernetes using YAML file: `kubectl apply -f ecommerce-api-pod.yaml`

after you make changes to the object, you can use the apply commandagain to update the object. The apply tool will only modify objects that are different from the current objects in the cluster. If the objects you are creating already exist in the cluster, it will simply exit successfully without making any changes.

##### Basic YAML configuration file

```yaml
apiVersion: v1.1
# Pod starts with capital letter
kind: Pod
metadata:
  name: ecommerce-api
spec:
  containers:
    - image: raihankhanraka/ecommerce-api:v1.1
      # container name must not use alphanumeric  characters
      name: ecommerce-api
      ports:
        - containerPort: 8080
          name: http
          protocol: TCP
```

#### Kubernetes Workload

 you don't need to manage each Pod directly. you can use workload resources that manage a set of pods. 
 
- Deployment and ReplicaSet
- StatefulSet
- DaemonSet
- Job and CronJob

#### kubernetes Deployment

A Kubernetes deployment is a resource object in Kubernetes that provides declarative updates to applications. A deployment allows you to describe an application’s life cycle, such as which images to use for the app, the number of pods there should be, and the way in which they should be updated. 

A Kubernetes object is a way to tell the Kubernetes system how you want your cluster’s workload to look. After an object has been created, the cluster works to ensure that the object exists, maintaining the desired state of your Kubernetes cluster. 

The process of manually updating containerized applications can be time consuming and tedious. Upgrading a service to the next version requires starting the new version of the pod, stopping the old version of a pod, waiting and verifying that the new version has launched successfully, and sometimes rolling it all back to a previous version in the case of failure.

Performing these steps manually can lead to human errors, and scripting properly can require a significant amount of effort, both of which can turn the release process into a bottleneck. 

A Kubernetes deployment makes this process automated and repeatable. Deployments are entirely managed by the Kubernetes backend, and the whole update process is performed on the server side without client interaction.

A deployment ensures the desired number of pods are running and available at all times. The update process is also wholly recorded, and versioned with options to pause, continue, and roll back to previous versions.

Automate deployments with pre-made, repeatable Kubernetes patterns
The Kubernetes deployment object lets you:

- Deploy a replica set or pod
- Update pods and replica sets
- Rollback to previous deployment versions
- Scale a deployment
- Pause or continue a deployment

A sample deployment:

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.14.2
        ports:
        - containerPort: 80
```
apply the YAML configuration of the deployment:

`kc apply -f nginx-deployment.yaml`

View the list of current deployments:

`kc get deployments`

Describe a deployment:

`kc describe deployment/nginx-deployment`

view the list of current replicasets:

`kc get replicaset`

view pods along with their labels:

`kc get pods --show-labels`

edit a deployment and keep record with a flag. Alternatively, update the yaml local file and then apply to configure it:
 
`kc edit deployment/nginx-deployment --record`

view the deployment in YAML:

`kubectl get deploy nginx-deployment  -o yaml`

view the rollout history:

`kc rollout history deployment/nginx-deployment`

view a specific rollout history with it's revision number:

`kc rollout history deployment/nginx-deployment --revision=2`

rollback the current rollout history:

`kc rollout undo deployment/nginx-deployment`

view current rollout status:

`kc rollout status deployment/nginx-deployment`

describe the nodes in the running control plane:

`kc describe nodes/nginx-cluster-control-plane`

view the running cluster info:

`kc cluster-info`

update an image in deployment:

`kc set image deployment/nginx-deployment nginx=nginx:1.21.1-alpine --record`


