---
layout: post
title: On-premise Layer-2 Service type LoadBalancer with Antrea
DATE: 
subtitle: ''
metadescription: Find out how to easily get Service types load balancer with Antrea
image: ''

---
While kubernetes clusters running with cloud providers benefit from external load balancers which can be easily interacted with through the CPI, on-premise installations don't get that by default. Sure if you have an external load balancer you can always install the kubernetes operator if there is one but it is not such a straightforward operation. For instance, if you take clusters deployed to vSphere through [CAPV ](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/)of TCE, your LoadBalancer service resources will remain in pending state out of the box.

    ❯ k get svc whoami-lb
    NAME        TYPE           CLUSTER-IP      EXTERNAL-IP   PORT(S)          AGE
    whoami-lb   LoadBalancer   10.102.27.166   <pending>     8080:30001/TCP   17s

There are a few options out there to get Load Balancer capabilities such as metalLB but I liked the idea of having it included in the CNI with Antrea since v1.5.0. [Antrea ](https://antrea.io/)is a CNI project maintained by VMware and backed by a really cool and helpful community. In fact they have a weekly podcast on Youtube called [Antrea Live](https://www.youtube.com/watch?v=4JcCltW8K48&list=PLuzde2hYeDBfHDD0zMbmG4QoVaSbkJChZ). You can also find the _#Antrea_ Slack channel in the Kubernetes Slack.

![](/img/antrealb0.png)

Anyways, Antrea can allocate external IPs to load balancer service types from a pool that you set yourself. When a service is created, the "virtual IP" is allocated to one of the nodes with a "nodeSelector" and the traffic is routed ky kube-proxy (or antrea proxy) to the service endpoints.

Note that the range of external IPs you allocate to it will need to be reserved so they can't be distributed by DHCP in order to avoid duplicates. The documentation about all this is in the [Antrea repo ](https://github.com/antrea-io/antrea/blob/main/docs/service-loadbalancer.md)and you will find everything that is missing in my blog there.

### Install Antrea v1.5.0

Let's take things one by one and start with the installation of Antrea. You can check out my blog on [CAPV ](https://www.vxav.fr/2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv/)(cluster api provier vSphere) if you want to provision a kubernetes cluster to vSphere. You can also use Tanzu Community Edition which already comes with Antrea by default I believe.

Anyway, if you deploy your cluster with CAPV like in my other blog, by default the nodes will be in "NotReady" state until you install a CNI.

![](/img/antrealb1.png)

Let's then install the Antrea CNI by applying the default manifest from upstream.

    kubectl apply -f https://github.com/antrea-io/antrea/releases/download/v1.5.0/antrea.yml

This will deploy CRDs, service accounts, and other antrea components into the cluster which should then be in Ready state.

![](/img/antrealb2.png)

### Configure Antrea Load Balancer

Now we need to enable the ServiceExternalIP features of Antrea. To do that we will edit the Antrea configmap that holds (you guessed it) the configuration of Antrea. It is named "_antrea-config-xxx_" and is in the "_kube-system_" namespace.

    k edit cm antrea-config-2k82d6f6t4 -n kube-system

Now you want to find the "_ServiceExternalIP"_ records, uncomment them and set them to true:

    data:
      antrea-agent.conf: |
        featureGates:
          ServiceExternalIP: true
      antrea-controller.conf: |
        featureGates:
          ServiceExternalIP: true

You won't need to do this if you deploy everything correctly from the get go but if you change values on the fly like we just did, you'll need to destroy the antrea pod so they can pick up the new values (that's what I had to do at least), I believe it's only true for the agent pods but you might as well go crazy.

    kubectl delete pod -l app=antrea -n kube-system

Next prepare a manifest to deploy an _ExternalIPPool_, I named mine _antrea-externalIPpool.yaml_. This is an Antrea CRD that the loadbalancer service can pick from to assign. In my example I only allowed 3 IP addresses from my node network. _Don't forget the " " if your label isn't a string (mine is a boolean), otherwise the Antrea Controller will log errors and it won't work._

Note that I manually applied the _antrea-lb=true_ to all my worker nodes beforehand which is what will make them participate.

    apiVersion: crd.antrea.io/v1alpha2
    kind: ExternalIPPool
    metadata:
      name: service-external-ip-pool
    spec:
      ipRanges:
      - start: 10.10.222.240
        end: 10.10.222.242
      - cidr: 10.10.222.0/24
      nodeSelector:
        matchLabels:
          antrea-lb: "true"

Now apply the manifest:

    k apply -f antrea-externalIPpool.yaml

### Create load balancer service types

We can now start with load balancer service types. In order for them to work with Antrea however, you need to apply the _service.antrea.io/external-ip-pool: "service-external-ip-pool"_ annotation to them.

Let's first create a small deployment with an image that displays information about the pod.

    k create deployment whoami --image=containous/whoami --replicas=3

![](/img/antrealb3-1.png)

Then expose the deployment with a service type load balancer.

    kubectl expose deployment whoami --port=8080 --target-port=80 --name=whoami-lb --type=LoadBalancer

You will find that it is still in _Pending_ state because we haven't set the annotation yet.

    NAME         TYPE           CLUSTER-IP     EXTERNAL-IP   PORT(S)          AGE
    whoami-lb    LoadBalancer   10.96.43.248   <pending>     8080:31882/TCP   6m16s

Let's do that by editing the service with "_kubectl edit svc whoami-lb_" and add the _service.antrea.io/external-ip-pool: "whoami-lb"_ annotation in the metadata section.

    apiVersion: v1
    kind: Service
    metadata:
      name: whoami-lb
      annotations:
        service.antrea.io/external-ip-pool: "whoami-lb"
     ...

The service should now get an IP address like so:

    NAME        TYPE           CLUSTER-IP     EXTERNAL-IP     PORT(S)          AGE
    whoami-lb   LoadBalancer   10.97.177.72   10.10.222.240   8080:30402/TCP   23m

Now you can try to curl the external IP address several times to witness the load balancing between the pods. As you can see below I get a **response from all three pods**. Note that this is not round robin so I had to run it a bunch of times to get a different response three times in a row.

![](/img/antrealb4.png)

### Wrap up

I very much enjoyed playing with the load balancer capability of Antrea as I think it is great to have an alternative to external load balancers, especially in lab environments or for learning purpose if you want to get up and running quickly.

I should point out that we did a bunch of stuff imperatively and edited configs on the fly which is not best practice in an actual environment. To do correctly you want to get all your manifests in order prior to deploying them.

If you are going to play with this, you might be interested in my blog about [ClusterResourceSets with Calico](https://www.vxav.fr/2021-12-07-automatically-install-cni-in-new-kubernetes-cluster-with-cluster-api/). Those are CRDs that let you install a resource in a cluster from the management cluster using a configMap. You can also check out my [capi repo](https://github.com/vxav/capi/tree/main/charts/capi-vsphere/templates) (which should be renamed capv) where I have a Helm chart for CAPV to install workload clusters with Antrea in a clusterResourceSet. Although the load balancing stuff isn't set up and I make quite a few changes in there so this might become obsolete as I tinker with it.