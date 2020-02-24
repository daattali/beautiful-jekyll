---
layout: post
title: How to use the SRM PowerCLI module
DATE: 

---
The famous Site Recovery Manager allows vSphere administrators to orchestrate disaster recovery scenarios. In a number of cases it can be useful to have the ability to automate some actions against SRM and avoid repetitive work like protecting VMs that have been storage vmotioned in Array based replication environment.

The PowerCLI module will help you automate such tasks but its usage is a bit tricky. As opposed to your usual vSphere modules, the SRM only includes the _Connect_ and _Disconnect_ cmdlets. The rest needs to be done "manually" using the PowerCLI API. It can be a little bit confusing at start if you are not used to working with APIs. I wrote a blog for Altaro on this topic that will help you get started:

[https://www.altaro.com/vmware/site-recovery-manager-powercli/](https://www.altaro.com/vmware/site-recovery-manager-powercli/ "https://www.altaro.com/vmware/site-recovery-manager-powercli/")