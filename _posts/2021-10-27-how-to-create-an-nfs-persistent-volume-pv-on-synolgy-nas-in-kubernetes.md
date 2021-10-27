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

![Kubernetes persistent volume on synology nas](/img/synopv1-1.png)

Take note of the Mount path as you'll need it for the persistentVolume.

### persistentVolume manifest

Now that the share exist, let's create the manifest for the persistentVolume. I always get confused with the capacity field. From what I understand it has no impact and is an organisational thing. The NAS itself is 1TB so I set the pv to 800Gi using the wet finger technique, if you have recommendations regarding this I'm all ears, please add it in the comments.

Note that accessModes doesn't need to be ReadWriteMany since I only have one node but who knows if I decide to add one at some point, at least I won't have to figure out what's not working then.

In the nfs section, type in the mount path we highlighted in yellow earlier.

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

The output should be:

    kubectl apply -f pv.yaml
    
    persistentvolume/nas-video-pv created

You can then see it with _kubectl get pv_ with _STATUS = Available_.

![](/img/synopv2.png)

### persistentVolumeClaim manifest

Now that the persistentVolume is created, we need a persistentVolumeClaim to connect it to our pods. Remember that persistentVolumeClaims are namespaced while persistentVolumes are not namespaced.

As you can see I tied the persistentVolumeClaim to the persistentVolume using the label selector _type: "nas-video"_.

    apiVersion: v1
    kind: PersistentVolumeClaim
    metadata:
      name: nas-video-pvc
    spec:
      storageClassName: ""
      selector:
        matchLabels:
          type: "nas-video"
      accessModes:
        - ReadWriteMany
      resources:
        requests:
          storage: 800Gi

The output should be:

    kubectl apply -f pvc.yaml
    
    persistentvolumeclaim/nas-video-pvc created

You can then see it with _kubectl get pv/pvc_ with _STATUS = Bound_.

![](/img/synopv3.png)

### Pod/deployment volume manifest

The last thing left to do is to create a pod and connect the pvc to it. This is not the actual manifest nor image that I use in my context but I went for something simpler for the sake of this blog.

This output should be:

    kubectl apply -f depl.yaml
    
    deployment.apps/test-htpc created

You can then see the pod running:

    kubectl get pod
    
    NAME                         READY   STATUS    RESTARTS   AGE
    test-htpc-6b7f57565d-54jkw   1/1     Running   0          8s

You can also open a shell inside the pod to see if the volume is here and available (autocompletion is your friend here):

    kubectl exec -it test-htpc-6b7f57565d-54jkw -- ls /video

And there you have it. Now you can manage your persistentVolumes on synology and persistentVolumeClaims from kubernetes. If you delete them, the data won't be impacted. You can connect it to several pods when need for added flexibility... It's generally beneficial to work that way. You can even see them in [Octant ](https://www.vxav.fr/2021-10-25-octant-vmware-open-source-ui-dashboard-for-kubernetes/)if you're interested in a Dashboard UI for Kubernetes.

### Conclusion

Thanks for following this blog. I am writing more content on Kubernetes these days but I won't leave vSphere on the side of the road just yet, especially with how things are going with Tanzu. Creating a Persistent Volume on Synology is a great way to get started with Kubernetes and get a grasp of what you can do with it in terms of storage persistency.