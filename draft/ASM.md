---
layout: post
title: Anthos Service Mesh Overview
subtitle: 
description: "tbd"
#cover-img: /assets/img/path.jpg
thumbnail-img: 
The #share-img: /assets/img/path.jpg
readtime: true
share-title: 
share-description: 
share-img: 
tags: [Anthos, kubernetes, containers, istio, service mesh, app modernisation]
---

# Some L1 Title
Monolithic applications with multiple functions have no issues communicating internally, but when these applications are modernised and migrate to a mircoservices architecture, these functions now need to communicate with each other over a network. 

<diagram showing monolithic app functions vs microservice functions communicating>

With traditional enterprise networks being secured at the perimeter and providing lateral movement within network segments, organisations need to start treating the network as  an untrusted network and ensure all traffic between functions are authenticated, authorised and securely encrypted. 

<diagram showing traditional network perimeter firewall and free lateral movement>

Building authentication and encryption into each function is a complex and time consuming process. Similarly developers need to consider APM and telemetry for each function, again consuming developer time that could be spent adding business value and improving application business logic. This is where Anthos Service Mesh (ASM) helps. 

<ASM logo>

The service mesh acts as a layer of infrastructure above the application, managing the network functions and security. It decouples these from the application, running the network functions in a second container within the same pod, as a sidecar envoy proxy (deployed using a sidecar pattern). This enables the application function to communicate with the proxy container as if it was on the same machine. The application has no awareness of this, and becomes truly portable.

<diagram showing proxy side car and traffic flows>

Anthos Service Mesh addresses network security, observability and advanced traffic management requirements. Not only does it manage this within a single Kubernetes cluster, the service mesh can run across multiple Kubernetes clusters on the same cloud, across multiple public clouds and even extending to on premise clusters. It enables secure and reliable communication between workloads that may be running on islands of clusters potentially spread around the world.

<Diagram showing ASM across multiple clusters>

## Network Security
Anthos Service Mesh can enforce services to authenticate each other using SSL certificates via mutual TLS (mTLS). With mTLS both the initiating service, and the receiving server authenticate each other, verifying the services are who they claim to be against a certificate issued from a trusted CA. 

mTLS also ensures data in transit is encrypted between services.

Where TLS authentication between a client and server validates the server is who the client thinks it is, mTLS ensures the server authenticates the client and they also are who they claim to be. By default, ASM issues certificates self signed by the mesh CA service that runs on the control plane. In a later blog, i’ll cover configuring ASM with Google Cloud Certifcate Authority Service for those scenarios when Mesh CA alone isn’t adequate.

mTLS helps mitigate the risk of replay or impersonation attacks of your services from stolen credentials as attackers need access to the services private key in order to impersonate them.

ASM also enables you to restrict access to sensitive services from authorised clients  regardless of the network location or the client and application level credentials e.g. limiting access to a particular GKE namespace, or an authorised service identity. For environments outside of Anthos, IP based access  policies can be defined to grant access.

Anthos Service mesh records the identify of the mTLS client and it’s IP address in logs, enabling you to trace what clients have accessed what resources when, even if the resource was ephemeral.


<Diagram of mTLS)

## Observability
Anthos Service Mesh provides proactive and reactive observability of services within the mesh. By default, these are integrated with Google Cloud, enabling a centralised single pane of glass dashboard of all Kubernetes clusters within the Google Cloud Console. There are several preconfigured service dashboards in the Google Cloud console so you don't have to manually set up dashboards and charts to observe service behaviour, troubleshoot or optmise your applications.

<insert dashboard console view>

The side car proxy intercepts all inbound and outbound HTTP traffic flows and reports them to ASM providing observability into the health and performance of your workloads. With this feature, developers no longer need to instrument their code to collect telemetry data. The telemetry data is automatically loaded into the ASM telemetry pages via the Google Cloud Logging and Monitoring API’s.

Out of the box ASM provides 3 of Google’s 4 golden signals for monitoring as per Google’s SRE practice. These include:

Latency: The time it takes to service a request e.g. ms response time of a web page.
Traffic: A measure of how much demand is being placed on your service e.g. requests per second for a service.
Errors: The rate of requests that fail e.g. HTTP response 5xx errors.

The 4th golden signal is saturation which needs to be manually defined based upon the workload and business requirements.

From these metrics, ASM enables you to define SLO’s which can be used to proactively alert support teams before a service impacting issue arises.

The console displays all services within the mesh in a services topology graph, records traffic flows that have occurred and provides high level statistics to assess health and performance and drill down into problem areas, simplifying troubleshooting for operations teams. This view shows relationships between services within the mesh, and highlights any flows that are not configured with mutual TLS encryption. Having a visual representation of know traffic flows also simplifies the impact of future planned maintenance, making it easier to understand the impact an update to a particular service may have on others.

<insert diagram showing service traffic flows and encryption).

## Advanced Traffic Management
 ASM pcontrols the flow of traffic in and out of the service mesh, and between services within the mesh. In addition to this, it provide various traffic management functions including:

Configuring load balancing of traffic between services.
Creating and managing canary or blue/green deployments.
Creating staged rollouts with percentage based traffic splits.
Defining circuit breakers, timeouts, retry settings and fault injections.
Redirecting traffic based on routing rules matching HTTP field attributes.
# Anthos Service Mesh Offerings

ASM is available as part of a suite of products under the Anthos platform or individually as a single product offering for teams only requiring the service mesh functionality. ASM is a fully managed service mesh based on the open source Istio project. 

# How It Works
ASM has two main components: the data plane and the control plane. The data plane refers to the envoy proxy sidecar containers that run alongside the application workloads. It is at the data plane that all traffic flows for the workloads are encrypted and authenticated with mutual TLS via the envoy proxies. The proxies also collect and report telemetry for mesh traffic.

The control plane is responsible for managing and configuring the proxies so they are able to route traffic accordingly. The control plane consists of three components.

Traffic director: Google Cloyds fully managed traffic control plane, which is responsible for keeping the proxies up to date with all the service mesh endpoints and directing service mesh ingress and egress traffic.

Managed CA: this is the certificate authority responsible for issuing SSL certificates to all the distributed proxies for the purpose of authentication and encryption .

Google Cloud Operations: The ingestion point for telemetry, providing monitoring, tracing and logging data for each of the proxies. This tooling also powers the ASM observability dashboards.


Istio architecture from https://istio.io/latest/docs/ops/deployment/architecture/

ASM has two deployment options- the first is an in cluster control plane. With this control plane, you install a Google supported distribution of Istio but you are responsible for managing version upgrades, security patches etc.

The second option is a fully managed control plane. With this control plane, you get a fully managed Istio deployment managed and maintained by Google. 

## Envoy Proxy
Alongside each application function’s container within the mesh, runs the envoy proxy as a sidecar container. This can be deployed automatically to all workloads within a configured namespace. 

All traffic into the service and out of the service routes via the proxy. The proxy manages the traffic flows, as defined and configured and deployed by the control plane.

## Mutual TLS




### Some L3 Title
Random points to consider

Anthos Service Mesh lets you adopt a defense-in-depth posture that is consistent with Zero Trust security principles. It lets you achieve this posture through declarative policies and without modifying any application code.



