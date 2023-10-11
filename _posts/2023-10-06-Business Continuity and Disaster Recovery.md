---
layout: post
title: Business Continuity and Disaster Recovery
date: 2023-10-06T09:58:04.234Z
nobanner: no
fb-img: null
---
In the current IT landscape where natural disasters, cyberattacks, and unforeseen crises lurk around every corner, the need for businesses to have a robust disaster recovery or business continuity plan cannot be overstated. It doesn't only happen to others, history is crippled with stories of this sort, take a look at what happened to OVH, the french cloud provider that had its main Strasbourg Datacenter go up in flames in the middle of the night. In this blog we will take a look at the differences, use cases, benefits and and why they are so important. 

## What is disaster recovery or business continuity?

In the grand scheme of things, both disaster recovery and business continuity are frameworks to protect a business against catastrophic events such as a datacenter fire, Ransomware attack, you name it. This is why it is so important to introduce them into your SDDC. However, there is a big difference between the two.

### Disaster Recovery

The objective of Disaster Recovery is to **minimize data loss**, reduce downtime, and expedite the restoration of IT systems when a catastrophic event occurs. It allows the business to resume its normal operations as quickly as possible while still experiencing some level of downtime, which is called Recovery Time Objective (RTO).

* Backup and Data Recovery: Regularly backing up critical data and applications to ensure their availability in case of a failure or disaster.
* Recovery Time Objective (RTO): Defining the acceptable downtime for specific systems and processes and creating strategies to meet those objectives.
* Failover and Redundancy: Implementing redundancy measures, such as backup servers or cloud solutions, to ensure continuity of IT operations.
* Testing and Validation: Regularly testing recovery procedures to verify that they work as intended and meet the defined recovery objectives.

### Business Continuity

The goal of Business Continuity is to **minimize downtime** of critical workloads and ensure that essential services continue to be delivered to customers, even during adverse conditions.

* Risk Assessment: Identifying potential threats and vulnerabilities that could disrupt operations, such as natural disasters, cyberattacks, or supply chain disruptions.
* Planning: Developing strategies, policies, and procedures to mitigate these risks and maintain critical functions during and after a crisis.
* Testing and Training: Regularly simulating scenarios and training employees to ensure they know how to respond effectively when disruptions occur.
* Communication: Establishing clear lines of communication and information dissemination to keep stakeholders informed during crises.

### Which one to choose?

That's the thing, you don't! It is not a case of BC vs DR as they have a different purpose. BC will ensure the most critical workloads keep running at all times while DR will restore workloads by restarting them at the recovery site. Most organizations don't actually have the budget to protect everything with Business Continuity as it is much more expensive. 

It is totally valid to have several tiers of protection such as BC, DR 2 hours, DR 8 hours, DR 1 day and so on.

## How does it work?

As mentioned previously, both framework aim at protecting workloads availability but they work differently.

### Disaster Recovery

In most virtual environments, Disaster Recovery happens through the use of replication technologies such as BDRSuite which allows you to replicate VMs from a primary site to a secondary site, ensuring that all your data and applications are available in the event of a disaster or downtime. Once the virtual machines are replicated, [BDRSuite](https://www.bdrsuite.com/) monitors the primary site for changes and automatically replicates any updates to the secondary site. This ensures that the secondary site is always up-to-date and ready for use in the event of a disaster.

One of the key metrics is the Recovery Point Objective (RPO) which dictates the frequency of replications, a.k.a. the amount of acceptable data loss. BDRSuite allows you to replicate the changes on the VM in primary site to replica VM on different site as often as every 15 mins or hourly/daily/weekly.

In the event of a disaster, you can immediately start the replica VM in the secondary site using the Failover option by following a pre-defined Disaster Recovery Plan (DRP). Of course the complexity will depend on the environments and the apps, especially regarding networking. If the secondary site has a different IP scheme, the process of Re-IP will be required to connect the VMs to the network, in which case the app running in the VM must support it.

Once the primary site is healthy again, the failback mechanism lets you move the workloads back to either the same or a different host.

### Business Continuity

As opposed to disaster recovery, business continuity means that the workloads must remain accessible during an outage. For the super top mission critical workloads, there may be needs to have high availability at the VM level with features such as vSphere Fault Tolerance but those are rather uncommon. In general, the time it take for vSphere HA to start the machine on a healthy host is acceptable for business continuity as the RTO is only a couple minute and the RPO is 0.

While it makes life much easier when it comes to surviving disasters as there is no recovery process involved, business continuity requires a more advanced infrastructure architecture such as:

* Overlayed network with the likes of NSX-T to span the layer 2 subnet across the broadcast domains to ensure workload mobility.
* Stretched storage across both sites to also workload mobility.
* Considerations regarding public ingress and egress must be taken to avoid hairpining of traffic between sites in normal operations.
* Low latency between the sites.
* Stretched cluster containing the hosts running in both sites.

## Benefits and common use cases

While the decision is sometimes driven by budget constraints or business needs, it is interesting to take a look at the pros and cons of each solutions.

**Benefits**:
  * **Disaster Recovery**
    * Multiple RTOs/RPOs to fit all workload types.
    * Fairly easy to setup and doesn't require changes to underlying architecture.
    * Efficient recovery processes with modern tools like BDRSuite.
  * **Business Continuity**
    * Low management overhead.
    * Incredibly low RTO and no RPO (vSphere HA).
    * Workload mobility facilitates maintenance tasks.
**Pitfalls**
  * **Disaster Recovery**
    * Some level of data loss after recovery.
    * Time to recover will vary according to hardware/procedures/knowledge of employees at hand...
    * Requirement to test disaster recovery plan (DRP) regularly, a time consumming task for the teams.
    * Networking is never easy.
  * **Business Continuity**
    * Expensive architecture.
    * Doesn't fit all environments.

## How MSPs can leverage BDRSuite?

Having usually multiple environments to take care of, MSPs need a way to centrally manage all aspects of their customers' SDDCs, including data protection. BDRSuite is a popular choice among MSPs as it adds many tools to their belt such as:

* Centralized Management and Multi-Tenancy Support:  Simplified operations with BDRSuite’s centralized management platform, which supports multi-tenancy. It is possible to manage multiple clients and environments from a single interface, streamlining the workflow.
* Pay-as-you-go Pricing: BDRSuite has no minimum monthly commitments, pay-as-you-go pricing model enables organizations to align costs with their business needs, providing flexibility and cost control.
* License Management Portal: The license management portal makes it easy to purchase and allocate licenses as per customer requirements to seamlessly manage licenses, ensuring efficient utilization and scalability.
* 24/7 Technical Support: An important factor is the peace of mind you get from having a support team to assist you whenever you need assistance with round-the-clock technical support. Additionally, a dedicated account manager will provide personalized guidance and support.
* Comprehensive Backup Solutions: BDRSuite supports most on-premise and cloud infrastructure as well as SaaS apps for data protection activities. 

## Wrap up

In this blog about disaster recovery and business continuity, we've learned why it is important to fortify our organizations against uncertainty. Business Continuity and Disaster Recovery are the twin pillars of preparedness.

From risk assessment to recovery planning, these practices create a framework for resilience. Real-world examples illustrate their importance as these principles are not just wise but crucial. They protect reputation, data, and customer service.

As we wrap up, check out [BDRSuite Backup and Replication](https://www.bdrsuite.com/) to take the first steps to bolster your organization's readiness.