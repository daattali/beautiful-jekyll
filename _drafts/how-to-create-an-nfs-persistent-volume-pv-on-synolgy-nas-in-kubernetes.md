---
layout: post
title: How to create an NFS persistent volume (PV) on Synolgy NAS in Kubernetes
DATE: 
subtitle: ''
metadescription: Learn how to create an NFS persistent volume on Synology NAS in Kubernetes
  in a few easy steps.

---
I have been learning about Kubernetes over the past couple of months and I thought I would move some of home multimedia workloads to kubernetes as a use case. It is necessary to go through the basics and courses but I find that I learn much faster and better with actual use cases. Although it isn't production grade stuff (_unless HTPC stuff is part of your job in which case you're awesome!_), I try to follow best practices and the way it would be done in the real world, even if it's overkill in my environment.

I used to run a few HTPC services in Docker on my old Raspberry Pi 2 which I repurposed into a Wireguard VPN server with DDNS client. I run a single Kubernetes node with K3S on Ubuntu Server that is hosted on a second hand [Gygabite mini PC ](https://www.gigabyte.com/fr/Mini-PcBarebone/GB-BSi3-6100-rev-10#ov)equipped with a core-i3 and 8GB of RAM. 

Anyway, part of this whole ordeal included to map NFS shares to containers. In the past on the RPi I did it quick and dirty by mounting the shares on the host OS in fstab and then mapping the mount point to the container. In Kubernetes I decided to do it properly with use persistent volumes (PV) and persistent volume claims (pvc).

### Synology NFS share

First we need our NFS share. This part is fairly generic, there is nothing to it really. Just create your folder and add it to the shared folders, again, I try to follow best practices by only allowing what's needed.

I allowed the whole subnet here because I access this share from multiple locations and it's just easier (already contradicting myself aren't I?). However, it is best to only allow the IPs that will access it if possible.

![](/img/synopv1-1.png)

Take note of the Mount path as you'll need it for the persistentVolume.

### persistentVolume manifest

Now that the share exist, let's create the manifest for the persistentVolume. I always get confused with the capacity field. From what I understand it has no impact and is an organisational thing. The NAS itself is 1TB so I set the pv to 800Gi using the wet finger technique, if you have recommendations regarding this I'm all ears, please add it in the comments.

Note that accessModes doesn't need to be ReadWriteMany since I only have one node but who knows if I decide to add one at some point, at least I won't have to figure out what's not working then.

    apiVersion: v1
    kind: PersistentVolume
    metadata:
      name: nas-video-pv
      labels:
        type: nas-video
    spec:
      storageClassName: ""
      capacity:
        storage: 800Gi
      accessModes:
        - ReadWriteMany
      nfs:
        server: 192.168.1.230
        path: "/volume1/video"