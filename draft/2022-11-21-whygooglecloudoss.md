---
layout: post
title: Why Google Cloud?
subtitle: "Part 3: Open Source Offerings, Innovation, Support, Contributions, Kubernetes, and Anthos Multicloud"
#cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/cloud-babble-low-resolution-logo-color-on-transparent-background (1).png
#share-img: /assets/img/path.jpg
readtime: true
share-title: "Why Google Cloud? Part 3: Open Source: Offerings, Innovation, Support, Contributions, Kubernetes, and Anthos Multicloud"
share-description: "Read how Google releases to open source innovative products, and how open source helps organisations reduce the risk of vendor lock-in and helps make multicloud a little less complex"
share-img: /assets/img/cloud-babble-low-resolution-logo-color-on-transparent-background (1).png
tags: [open source, kubernetes, GKE, Istio, Anthos, multicloud]
---

Welcome to my third blog in the series 'Why Google Cloud' where I discuss my reasons why I advocate Google Cloud. The first two blogs in the series focussed on security and sustainability. If you missed them, you can read them here:

- [Why Google Cloud? Part 1: Security](https://www.cloudbabble.co.uk/2022-11-03-whygooglecloudsecurity/)
- [Why Google Cloud? Part 2: Sustainability](https://www.cloudbabble.co.uk/2022-11-12-whygooglecloudsustainability/). 

This blog focuses on Google's support and contributions to open source, Kubernetes, and how open source can help organisations avoid vendor lock-in and make multicloud a little less complex.

Before specialising in Google Cloud, my career as an architect was more of a traditional infrastructure based role and centred around secure private clouds typically based on vSphere for large enterprises and multi-tenant platforms. I had also spent many years working with Windows Server and Microsoft products, so other than RHEL and a few database offerings, I had very little involvement with open source products!

Fast forward to my role now as a Google Cloud Architect and that has nearly rotated 360 degrees. One of the first considerations when assessing application migrations to Google Cloud I make is whether the application is benefiting from proprietary licensed software, or whether it can benefit from modernisation and migration to an open source offering to provide savings or offer opportunities for further innovation. There is a significant trend in organisations adopting more of the open source ecosystem. The Worldwide Open Source Services Industry is Expected to Reach $50 Billion by 2026 [(ResearchAndMarkets.com)](https://www.marketsandmarkets.com/Market-Reports/open-source-services-market-27852275.html).

I recently worked as a Lead Architect migrating applications for a leading global financial services organisation to GCP, and a lot of the applications had databases running on a legacy Oracle Exadata platform. Whilst not all databases could be migrated for various reasons, a significant number were designed to migrate to PostgreSQL on Google Cloud SQL for their target architecture. Those applications with databases that looked suitable would be assessed using migVisor. migVisor would generate a report for the database, detailing the complexity migrating to Cloud SQL and highlighting any challenges that may be faced for features/scripts etc. that may not be supported. Ora2PG would then be used to perform the migration... Before veering down the road of database migration too far, I best stop and get back to the purpose of this post... Why Google Cloud? 

Google's ongoing and historic support and contributions to a wide range of open source projects and its history of developing application code internally and releasing them to the open source communities for general consumption and further innovation is my second reason why I advocate Google Cloud.

## Kubernetes

Application modernisation and containerisation has benefited significantly from Google's innovation with Kubernetes born via this process. Google developed the containerisation orchestration tool which they had used for running their own container workloads for many years before releasing it as open source in 2014. Since then it has become the de facto containerisation orchestration platform with each of the hyperscalers offering their own managed services. In 2021, the CNCF Annual Survey revealed that 96% of organisations are using or evaluating Kubernetes!

![Kubernetes](/assets/img/whygcpopensource/kubernetes-horizontal-color.png "Kubernetes")

*Kubernetes Container Orchestration and Management Platform*

Kubernetes is not the only project Google has released. There are many more Google product offerings including Tensorflow as a machine learning platform, Istio as a service mesh offering helping simplify security and observability for microservices, chromium as a web browser, and Android as an operating system. In fact, Google has so many open source projects they maintain a website specifically for them: [Google Open Source](https://opensource.google/).

![Google Open Source](/assets/img/whygcpopensource/google-opensource-logomark.png "Google Open Source Logo")

*Google releases open source to share innovation*

Google Cloud offers a managed Kubernetes platform in two modes- Google Kubernetes Engine (GKE) Standard Mode, and GKE Autopilot Mode. Whilst both provide a fully managed control plane, with GKE Autopilot, Google also fully manages the Kubernetes cluster and infrastructure including node autoscaling. There is no configuration or monitoring required by yourself. Autopilot configures the cluster according to GKE best practices for cluster, workload and security configuration. With Autopilot, you only pay for the pod resources you consume, avoiding the overhead associated with system components and unused node capacity etc. However, if more flexibility is required regarding node pool configuration, the GKE Standard Mode enables you to manage the clusters underlying infrastructure, node specification, quantity etc.

![Google Kubernetes Engine](/assets/img/whygcpopensource/gke-icon.png "Google Kubernetes Engine Logo")

*Google Kubernetes Engine is Google Cloud's fully managed Kubernetes offering available in Standard or Autopilot mode*

Despite donating Kubernetes to CNCF, Google continues to innovate, regularly contributing and updating the project. Google is the number one contributor to Kubernetes project by a significant margin (generally at least twice the volume of the next top contributor!).

## Lock-In and Knative

One major concern of organisations migrating to public cloud is the risk of vendor lock-in. They are concerned how difficult it is to migrate from one cloud platform to another, if it is too complex and expensive their application may become 'locked in' to a particular platform and require significant financial, time or technical investment to move at a later date. By choosing open source offerings, organisations can remove (or lessen) concerns about vendor lock-in.... Helping to address this concern, Google created the Knative project, which has grown to have contributions from a variety of companies including IBM, RedHat, VMware and SAP, but ultimately ensures organisations can run serverless workloads anywhere they want, be that on a fully managed GKE cluster, serverless Cloud Run, Cloud run for Anthos, Kubernetes on premise, or on another hyperscaler platform or OpenShift platform. 

![Knative](/assets/img/whygcpopensource/knative.png "Knative Logo")

*Knative is an Open-Source Enterprise-level solution to build Serverless and Event Driven Applications.*

Whilst the Knative serverless components need to be installed on top of GKE clusters, for Google Cloud Run, Knative is built in. Knative is a platform agnostic solution for running serverless. With Knatives open API and runtime environment, concerns of vendor lock-in from a serverless container perspective are alleviated. 

Without Knative, developers have to undertake a steep learning curve to become experts in Kubernetes, configuring GKE cluster settings, configuring autoscaling, defining various YAML files for the deployment etc. With Knative, developers no longer need this level of expertise in Kubernetes. The Knative Serving and Eventing components work together taking care of this complexity and enabling developers to use Kubernetes in a serverless manner, focussing more on their code rather than the Kubernetes infrastructure, resources and manifest files.

Knative was accepted on CNCF earlier this year in March and is at the incubating project maturity level- both graduated and incubating projects are considered stable and used in production environments. More information on Knative is available here [Knative](https://knative.dev/docs/). 

## Serverless vs Fully Managed

Google Cloud offers a range of open source products as fully managed services, supported by Google and their partner ecosystem. This includes database offerings on Cloud SQL for MySQL, PostgreSQL, Dataflow as a managed Apache Beam offering, Dataproc as a fully managed Apache Hadoop offering, Cloud Composer as a fully managed Apache Airflow offering, MongoAtlas database offerings and many others. Some of these offerings are serverless, others are classed as fully managed services. Serverless offerings remove any control and configuration of what machines are being used to run your services- with serverless, you only need to focus on your code, Google takes care of all the configuration of clusters, HA, DR settings etc. Additionally you typically only pay for the resources you use. 

Fully Managed services provide more control- with fully managed you typically define the machines that run the services, whether the service is highly available, autoscales etc. However, the machines are fully managed- you don't need to install, configure or maintain them, this is done as part of the offering. 

## Multicloud
By opting to run your applications on open source software, organisations can more easily embrace multicloud. According to Gartner, more than 80% of organisations are using two or more public cloud providers. Whilst a multicloud strategy inevitably introduces more complexity to your public cloud architecture and governance, enterprises are opting for a multicloud strategy for a variety of reasons including:

- Avoiding vendor lock-in- developers can deploy their code on multiple clouds by consuming open source software.
- Disaster Recovery- some organisations look to use a second cloud provider for DR purposes. Equally organisations may view multicloud as providing increased resilience and availability. This is particularly true for organisations who have regulatory, or sovereignty requirements limiting the region upon which an environment can be deployed. Multicloud architectures can provide more regions within the constraints the organisation has to work within.
- Best of breed capabilities- some organisations may opt to consume select services from one public cloud provider for areas they are seen as a leader in e.g. opting for Google Cloud for Data and AI, and consuming other services with another CSP.
- Accidental multicloud- some organisations may find that different areas of the business are already consuming services from multiple public cloud providers. Others may inherit multicloud architectures following mergers and acquisitions. 

## Anthos

Whatever the reason, defining a strategy to manage and govern these multicloud environments is key. Organisations need to ensure they have a way of gaining centralised visibility and management of resources, wherever they are deployed- on GCP, on premise, at the edge or in other public clouds. Anthos aims to address this- it provides a single pane of glass view across all platforms, providing infrastructure management, container management, service management, policy enforcement and observability. Collectively this simplifies the challenges organisations face managing and maintaining containerised workloads across multicloud environments. Instead of having to define and configure each public cloud Kubernetes cluster, containers, services, policy enforcement, monitoring, logging, SLO's, troubleshooting tools and application maintenance, this can all be done once within Anthos and deployed across your Kubernetes clusters regardless of whether they are running upon GKE, on premise or in another public cloud.

![Anthos multicloud](/assets/img/whygcpopensource/anthos.png "Anthos multicloud management")

*Anthos multicloud management*

## Assured Open Source
The Solarwinds attack in 2020 highlighted the risk of supply chain attacks. With open source software, there is a risk the software may contain hidden vulnerabilities or malicious code. To help mitigate this threat, Google has a new product currently in preview called Assured Open Source Software (Assured OSS). Assured OSS provides access to open source software packages that have been curated and vetted by Google. This enables customers to deploy the same OSS Packages Google uses themselves, which have been regularly scanned, analysed and tested for vulnerabilities. The packages are built with verifiable SLSA compliance, signed by Google and are distributed from a Google secured Artifact Registry.

## Conclusion
With open source, organisations help avoid vendor lock-in, lower costs (maybe not so much with some Enterprise OSS!), benefit from faster development, innovation, and bug fixes. Google's rich history of innovation, developing, releasing OSS, contributing to OSS projects and creating an array of fully managed OSS product offerings is my third reason 'Why Google Cloud'. With innovative products like Kubernetes available as part of Google Kubernetes Engine Standard and Autopilot modes, or a Knative serverless deployment running on Cloud Run, Google Cloud is the perfect platform to run your containerised workloads. Equally, for organisations with hybrid or multicloud architectures, Google Cloud's Anthos offering simplifies the management of multiple Kubernetes clusters on premise and in public clouds.

Thanks for taking the time to read this blog. Please feel free to share, [subscribe](https://www.cloudbabble.co.uk/subscribe) to be alerted to future posts, follow me on [LinkedIn](https://linkedin.com/in/jamiethompson85), and react/comment below! 

Do reach out if you would like me to cover any particular areas of Google Cloud products, concepts or certifications in future posts.

