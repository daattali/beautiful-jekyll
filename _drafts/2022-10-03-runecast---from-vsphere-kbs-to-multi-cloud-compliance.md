---
layout: post
title: Runecast - From vSphere KBs to multi-cloud compliance
description: null
date: 2022-10-03T16:37:51.966Z
nobanner: no
fb-img: null
---

Back at the beginning of my journey through infrastructure in IT, I came across Runecast I think from Yellow Bricks (Duncan Epping's blog). It must have been around 2015 or 2016 and back then the product was somewhat revolutionary within the VMware space as it would scan your environment and tell you what you were doing wrong in terms of best practices by comparing your configuration against official VMware KBs. I used it a bit and loved it instantly, it was amazing because it was easy to use (not like vRops back then), there was a free tier and you would get tons of valuable insight over your infrastructure with tips on how to fix the flaws it detected. The various jobs I had over the years sent me in a direction where I didn't get to use Runecast and didn't really follow its evolution.

My career shifted towards Kubernetes (with a VMware flavor) in the last year and I was lucky enough to attend KubeCon 2022 in Valencia with my employer [Giant Swarm](https://www.giantswarm.io/). While I was roaming the sponsor booths, talking with people from various companies, I was surprised to bump into Runecast and had a flashback from my time in Scotland managing a 900 VMs infrastructure. I had a very nice chat with the folks at the booth and learned about the evolution of the product. Over the years the product gained popularity but virtualization isn't really the cool kid on the block anymore as you might know. In order to address customers' problematics and stay current with trends, Runecast evolved organically towards becoming a security and compliance platform spanning a great deal of infrastructure providers with AWS, Azure, Google Cloud Platform (GCP), Kubernetes, VMware, Windows and Linux. So I decided to get in touch with them and offered to talk about it on the blog as I really liked the product back then and I'd like to know more about what it's become.

In this blog I will only cover the VMware side of things and touch base on Kubernetes but you can have a look at the website if your use cases revolve around cloud hyperscalers. I will be using the [online demo](https://demo.runecast.com/) to provide the screenshots here, you can try it yourself to discoer the product.

## VMware integration

Because Runecast started off as a best practices tool for vSphere, the VMware integration is top notch and supports other products like NSX, VSAN, VMware Cloud Director and yes, even Horizon! Runecast will continuously scan your environment against known issues, security standards, the VMware HCL, Best Practices and more. It also check best practices for Pure Storage, Nutanix (vSphere) and SAP HANA on vSphere. When vulnerabilities are found in the environment, the concerned VMSA/CVE will be displayed on the dashboard.

As you would expect from such a product, you also get configuration drift management with Configuration Vault to keep your environment in check. And when something's not right, there's a pretty nifty feature that can generate a custom script to remediate the configuration, handy but a good learning tool if you ask me. Granted things are simpler in vSphere 7.0 with Image remediation and Skyline, but Runecast can also help by validating host hardware, BIOS, drivers and firmware against the HCL (a very cumbersome task back in the days...).

### vSphere Upgrades

Now that was for a quick overview. I want to dedicate a couple chapters for specific features, including this one that I found both clever, funny (for a nerd) and very useful. If you are in a company running a small datacenter with up to 50 (maybe a bit more), upgrade campaigns can be fairly straightforward and not too much headache (although there will be some). However, if you are in large organization or a cloud provider running hundreds of vSphere hosts, the process is much more involved, lenghthy, expensive and has a lot more visibility across departments (usually top-to-bottom...). 

Runecast attempts to simplify this process of preparing for vSphere upgrades and validating that everything goes and went smoothly. It will discover in advance if there are incompatible components or combinations (driver/firmware/BIOS...), make recommendations etc...

As you can see in the screenshot, I selected a cluster with hosts running vSphere 6.5 and I can simulate the hardware compatibility if it were upgraded to vSphere 7.0u3. Surprisingly, only the RAID controller wouldn't be compliant so not to bad, you also get a link to the HCL page of the device. However, this tool would provide great info in large environments to quickly identify where to focus your attention.

### Configuration drift

