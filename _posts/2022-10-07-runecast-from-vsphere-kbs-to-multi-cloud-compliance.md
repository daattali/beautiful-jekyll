---
layout: post
title: Runecast - From vSphere KBs to multi-cloud compliance
description: null
date: 2022-10-07T14:37:51.966Z
nobanner: "yes"
fb-img: null
---

Back at the beginning of my journey through infrastructure in IT, I came across Runecast I think from Yellow Bricks (Duncan Epping's blog). It must have been around 2015 or 2016 when I was in Scotland and back then the product was somewhat revolutionary within the VMware space as it would scan your environment and tell you what you were doing wrong in terms of best practices by comparing your configuration against official VMware KBs. I used it a bit and loved it instantly, it was amazing because it was easy to use (not like vRops), there was a free tier and you would get tons of valuable insight into your infrastructure with tips on how to fix the flaws it detected. The various jobs I had over the years sent me in a direction where I didn't get to use Runecast and didn't really follow its evolution.

Fast forward to 2022, my career shifted towards Kubernetes (with a VMware flavor) in the past year and I was lucky enough to attend KubeCon in Valencia thanks to my employer [Giant Swarm](https://www.giantswarm.io/). While I was roaming the sponsor booths and chatting with people from various companies, I was surprised to bump into Runecast and got a flashback from my time in Scotland managing a 900 VMs infrastructure. I had a very nice chat with the folks at the booth and learned about the evolution of the product and how it now works with Kubernetes. Over the years the product gained popularity but virtualization hasn't really been the cool kid on the block for a while now as you might know. In order to address customers' problematics and stay current with trends, Runecast evolved organically towards becoming a security and compliance platform spanning a great deal of infrastructure providers with AWS, Azure, Google Cloud Platform (GCP), Kubernetes, VMware, Windows and Linux. So I decided to get in touch with them and offered to talk about it on the blog as I really liked the product back then and I'd like to know more about what it's become.

In this blog I will only cover the VMware side of things and a little bit of Kubernetes but you can have a look at the website if your use cases revolve around cloud hyperscalers. I will be using the [online demo](https://demo.runecast.com/) to provide the screenshots and play around with the product.

## VMware integration

Because Runecast started off as a best practices tool for vSphere, the VMware integration is top notch and supports other products like NSX, VSAN, VMware Cloud Director and yes, even Horizon! Runecast will continuously scan your environment against known issues, security standards, the VMware HCL, official KBs and more. It also check best practices for Pure Storage, Nutanix (vSphere) and SAP HANA on vSphere. When vulnerabilities are found in the environment, the concerned VMSA/CVE will be displayed on the dashboard to get your attention.

As you would expect from such a product, you also get configuration drift management with Configuration Vault to keep your environment in check. And when something's not right, there's a pretty nifty feature that can generate a custom script to remediate the configuration, handy but also a good learning tool if you ask me. Granted, things were made simpler since vSphere 7.0 thanks to Image remediation and Skyline, but Runecast can also help by validating host hardware, BIOS, drivers and firmware against the HCL (a very cumbersome task back in the days...). 

### vSphere Upgrades

Now, that was for a quick overview, I want to dedicate a couple chapters to specific features, including this one that I found both clever, funny (for a nerd) and very useful. If you are in a company running a small datacenter with up to 50 hosts (maybe a bit more), upgrade campaigns can be fairly straightforward and not too much hassle (although there will be some). However, if you are in a large organization or a cloud provider running hundreds of vSphere hosts, the process is much more involved, lenghthy, expensive and has a lot more visibility across departments (usually top-to-bottom...). 

Runecast attempts to simplify this process of preparing for vSphere upgrades and validating that everything goes and went smoothly. It will discover in advance if there are incompatible components or combinations (driver/firmware/BIOS...), make recommendations etc...

![runecast hardware compatibility](/img/2022-10-06-07-38-12.png)

As you can see in the screenshot, I selected a cluster with hosts running vSphere 6.5 and I can simulate the hardware compatibility if it were to be upgraded to vSphere 7.0u3 in the current state. Surprisingly, only the RAID controller wouldn't be compliant on this host so it's not to bad, note that you also get a link to the HCL page of the device. This tool would be particlarly useful in large environments to quickly provide detailed info and identify where to focus your attention.

### Configuration drift

If you've ever used vSphere Host Profiles, you probably know how painful it can be to get it to work properly and keep it that way. I am yet to find a customer that is happy with it and doesn't have issues with host compliance. Runecast offers a comparable feature with Configuration Vault where you can find deviation from a baseline in your vSphere hosts. For instance, you can see below a change in the syslog destination that deviates from the baseline.

![runecast configuration drift](/img/2022-10-06-07-32-17.png)

You can have several timestamped baselines and compare it to the status of your environment at various dates as well if that makes sense.

![runecast baselines comparison](/img/2022-10-06-07-35-39.png)

### Best Practices and KB discovery

Just like in the first iterations of the product several years ago, Runecast offers recommendations based on best practices for your environment. According to how complex the environment is (NSX, VSAN...), it might not be a walk in the park to knock them all down but it gives vSphere admins something to work with and go through the checklist one by one.

The good thing about this is that, on top of getting insight into the environment, you learn in the process as each recommendation comes with details and context along with links to the original resource.

![runecast vsphere best practices](/img/2022-10-06-07-39-48.png)

In a sense, Runecast was doing what Skyline does long before it existed by scanning the environment to match with VMware KBs so you don't have to go scavenging the logs or through every single error, that way you get everything in one place with context and criticity.

### Security enforcement

Because a compliance tool wouldn't be one without a fair amount of security related capabilities, Runecast scans the environment for vulnerabilities and lets you know which CVE/VMSA are threatening your SDDC. Things like this will go a long way in sensitive environments, especially seeing the recent trends of malware targeting ESXi these last couple of years.

![runecast cve vmsa vulnerability scanning](/img/2022-10-06-07-51-35.png)

Along with vulnerability scanningm Runecast simplifies the process of achieving compliance towards specific frameworks or certifications such as ISO27001 or GDPR. I suspect this is largely based on the security configuration guide and I also suspect that most of the framework will have a majority of requirements in common with regards to VMware products but at least it gives VI admins and stakeholders piece of mind to know that everything is taken care of.

## Kubernetes

Runecast now also supports Kubernetes clusters to offer compliance capabilities and security recommendations also known as Kubernetes Security Posture Management (KSPM). The nice thing about the product here is that you get your various infrastructure components (vSphere, NSX-T, Kubernetes and so on) in the same portal with the same user experience (configuration vault, custom scripts...).

### Runecast on Kubernetes

Note that Runecast Analyzer can be deployed in a number of providers (vSphere Appliance, AWS, Azure) or in a Kubernetes cluster with a Helm chart at [https://helm.runecast.com/](https://helm.runecast.com/). Meaning you can monitor Kubernetes with Runecast but you can also run Runecast on Kubernetes... Or both obviously.

* You first add the Helm repo

`helm repo add runecast https://helm.runecast.com/charts`

* And then install the chart. The example below will install with the default values but you can configure it with a values file (details in the link above). At least to expose it via an ingress instead of proxying UI access through the kube-api.

`helm upgrade --install runecast-analyzer runecast/runecast-analyzer`

This is just to give you a 20.000 ft. overview of the process but I highly suggest you dive a little in the Helm chart doc to make sure you deploy it correctly and not with the defaults.

### Kubernetes in Runecast

I split this chapter in two to avoid confusion and make it clear that running Runecast in Kubernetes and managing a Kubernetes cluster are decoupled things. In order to monitor a K8s cluster in Runecast, you need the IP:port of the Kubernetes API endpoint and the [token](https://docs.runecast.com/connect_to_a_system_and_analyze.html) of a service account that has the right set of permissions.

![connect kubernetes in runecast](/img/2022-10-07-13-30-34.png)

### Runecast Validating Webhook

The documentation also includes a section about a [Runecast ValidatingWebhook](https://docs.runecast.com/kubernetes_integration_examples.html) that will prevent operations that could lead to running vulnerable workloads. Kubernetes webhooks (validating and mutating) are checks that run with an admission controller when specific actions are triggered (CREATE and UPDATE in this case). For instance, if someone tries to create a deployment referencing a container images known to have security breach, the admission controller will fail the action and give an error message.

In the screenshot below, you can see that nginx 1.19 includes a lot of vulnerabilities, as a result, it is deemed non compliant and will be rejected by the validatingWebhook.

![Runecast image scan](/img/runecast%20image%20scan.png)

## Wrap up

I finish this blog on my way back from VMUG France in Paris where I met, yet again, with Runecast and had a nice chat with them. All in all I really like the product and the way it's headed. My only gripe at this point is on the useability of the Webhook. Those are great but it takes a little bit to wrap your head around it so I think a bit more context and documentation around this would go a long way. I believe a bulk of the Runecast users will come from the infrastructure world and won't be as technical in Kubernetes as those setting up Kyverno for instance. So a more automated way to set it up would probably open the capability to more folks out there.

Apart from that, a very nice product that spans pretty much all areas of the SDDC which will be welcomed with open arms by those embracing the VMware portfolio and its overall craziness.

You can download the [free trial](https://portal.runecast.com/registration) or test the product in the [online demo](https://www.runecast.com/runecast-analyzer-online-demo).