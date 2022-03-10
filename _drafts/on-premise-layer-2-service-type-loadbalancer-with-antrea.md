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

There are a few options out there to get Load Balancer capabilities such as metalLB but I liked the idea of having it included in the CNI with Antrea since v1.5.0. Antrea can allocate external IPs to load balancer service types from a pool that you set yourself. When a service is created, the "virtual IP" is allocated to one of the nodes with a "nodeSelector" and the traffic is routed ky kube-proxy (or antrea proxy) to the service endpoints.

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