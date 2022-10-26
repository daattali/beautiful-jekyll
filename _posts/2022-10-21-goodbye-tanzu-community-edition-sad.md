---
layout: post
title: "Goodbye Tanzu Community Edition :sad:"
description: null
date: 2022-10-21T17:41:55.021Z
nobanner: "yes"
fb-img: /img/2022-10-21-20-30-28.png
---
You may have missed the news as it was somewhat under the radar but it was an expected outcome for those that were involved in the community, Tanzu Community Edition has been ~~murdered~~ retired.

![tce is dead](/img/2022-10-21-20-32-15.png)

I don't consider myself as such since I don't do much with Tanzu in general as I work mostly with Vanilla Kubernetes and VMware based cluster API providers ([CAPVCD](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjNyYjn7_H6AhUK3hoKHY9lAo4QFnoECBIQAQ&url=https%3A%2F%2Fwww.vxav.fr%2F2022-05-15-cluster-api-with-vmware-cloud-director-10.3-(capvcd)%2C-nsx-t-and-alb%2F&usg=AOvVaw0QxwJEFFRFZA5uLoSyXTEt) and [CAPV](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwidosHs7_H6AhVCJBoKHT9nC7EQFnoECBgQAQ&url=https%3A%2F%2Fwww.vxav.fr%2F2021-11-21-understanding-kubernetes-cluster-api-provider-vsphere-capv%2F&usg=AOvVaw3PAL7MEWT14JE4l4_iiSNj)). However, I am quite active in Slack and I follow a bunch of VMware, Kubernetes and Cluster API channels, which are all part of Tanzu Community Edition.

Tanzu Community Edition is (was) VMware's open source implementation of Tanzu which relied on cluster API to provision Kubernetes clusters on various infrastructure providers like AWS, Azure, vSphere or even locally in Docker. With a simple one-liner you could spin up a cluster with control plane and worker nodes. The whole process was automated, create a Kind cluster, install cluster API and the relevant provider, provision the cluster, pivot the CAPI/CAPx resources to the cluster, and install the "Tanzu Flavor" to it, which would give you a package manager with Carvel, OIDC authentication and a whole bunch of stuff.

Everyone I know in the space agreed that Tanzu Community Edition was awesome and that the maintainers were doing a fine job at rolling out new features and building an active community behind it.

The Tanzu Community Edition wasn't a massive team within VMware as far as I know but its members (some of them coming from Pivotal) were a clever bunch that are active contributors in the Open Source ecosystem. Doubts started to form in my mind back when VMware announced that Broadcom was likely to acquire the company in May 2022. Everyone in the VMware space (and beyond) were very much surprised by this move as the company doesn't have a great track record regarding its acquirees.

Following this announcement, a number of resignations started to be made public within VMware. Now, people leave companies all the time and I don't want to come across as a gossip as I have no interest in this. What I saw as red flags were the resignation of important people such as Joe Beda (Heptio founder). After this point in time, we noticed significantly less activity in the Tanzu Community Edition Slack channel, no new releases and questions left unanswered. The latest TCE version being `0.12.1` which they scrambled to get out of the door the day before Kubecon 2022 in Valencia (Spain).

![TCE latest version](/img/2022-10-21-20-01-33.png)

Later on John Mc Bride who was one of the main contributors to the project (very nice guy that I met at Kubecon) announced his resignation along with several other key contributors to Tanzu Community Edition. John actually gave a great talk about [the risk of single maintainer dependencies](https://kccnceu2022.sched.com/event/ytlk/the-risks-of-single-maintainer-dependencies-john-mcbride-vmware) at Kubecon which sounds very topical here even though the talk was focused on other Open Source projects.

![John mc bride goes to aws](/img/2022-10-21-19-59-02.png)

Fast forward to late October, I open Slack to start my workday by browsing the various channels I'm in and find out that out... Oops.

![TCE is archived](/img/2022-10-21-20-09-01.png)

Surely that's not how things go nowadays right? There has to be a little bit of communication and some way to maintain a product? Not really, the [Tanzu Community Edition page](https://tanzucommunityedition.io/) has been updated to let us know that the product was just shoved into the dumpster and replaced with `Tanzu Kubernetes Grid for free in non-commercial environments up to 100 cores`. What a weird morning that was. Why put so much effort to have a team of brilliant minds work on an open source product to eventually light it on fire.

https://github.com/vmware-tanzu/community-edition/commit/f16cad8a602eb0c2cbc7233b39eb2a494c5d8a3e

> Acting on insights gained through community engagement over the past year, VMware has decided to offer a free download of VMware Tanzu Kubernetes Grid in place of VMware Tanzu Community Edition software and to retire the Tanzu Community Edition open source project.
> 
> This project is no longer being updated or maintained and code related to the project will be removed by the end of this calendar year (Dec 2022). Users can download Tanzu Kubernetes Grid here.

![VMware retiring TCE](/img/2022-10-21-20-13-31.png)

Although I am sad about the news and to see it handled the way it was, the silver lining is that we get free TKG for 100 cores which should be more than enough to play with. I guess it ties somewhat with vSphere 8's announcement of TKG 2.0 which aims at collapsing TKG offerings into a unique one.

I will keep wearing my Tanzu Community Edition t-shirt though !

---

If you are looking for options on how to **protect your vSphere and VMware Cloud Director** workloads, [Nakivo Backup & Replication](https://www.nakivo.com/) offers capabilities to back up vSphere VMs and VCD objects such as vApps, individual VMs and vApp metadata and ensure that remote workloads can be recovered in case of a data loss event. Not a lot of vendors out there support VCD so kuddos to that!

[![nakivo backup](/img/2022-10-26-13-45-41.png)](https://www.nakivo.com)
