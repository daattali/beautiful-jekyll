---
layout: post
title: Hot add memory to a kubernetes node VM
date: 2023-06-15T15:00:20.305Z
---

Recently I had to increase the memory in a bunch of Kubernetes nodes running on VMware and I wanted to avoid switching off the nodes as it means draining them first which sometimes take quite a bit of time and can get the customer slightly nervous. So I ended up doing it online thanks to memory hot add being enabled on the VMs.

Note that this if you use Cluster API you will not need to go through these steps as you would typically change the nodes' "flavour" which will trigger the capi controllers to roll the nodes with new ones fitting that flavour.

In this example I am working with Kubernetes nodes that were provisioned (somewhat) manually, meaning there isn't a controller that can take care of increasing the RAM or changing VM sizing policy for me.

* First we need to make sure that `Memory hot add` is enabled on the VM.

![memory hot add kubernetes vmware](/img/increasememk8s1.png)

* Then edit the virtual machines settings and increase the memory to whatever values you need.

![memory hot add kubernetes vmware](/img/increasememk8s2.png)

At this point the VM is equipped with the new amount but it isn't detected in the guest.

* There is an easy way to enable the new "virtual DIMMs" in the OS. After connecting the node (ssh), you can check if there is memory that isn't used by the OS, check for memory states set to `offline`.

```
cat /sys/devices/system/memory/*/state | grep offline
```

* Then, replace `offline` by `online` and it will cause the memory to be detected. Thanks to this [little internet nugget](https://blog.yucas.net/2020/01/22/hot-add-cpu-and-memory-to-ubuntu-guest-in-vmware/) by the way.

```bash
for RAM in $(grep line /sys/devices/system/memory/*/state)
do
        echo "Found ram: ${RAM} ..."
        if [[ "${RAM}" == *":offline" ]]; then
                echo "Bringing online"
                echo $RAM | sed "s/:offline$//"|sed "s/^/echo online > /"|source /dev/stdin
        else
                echo "Already online"
        fi
done
```

* At this point the memory is recognized in the guest. All that's left to do is to restart the kubelet service.

```
sudo systemctl restart kubelet
```

The Kubernetes node should now report the correct amount in `kubectl describe node`.

```
Capacity:
  cpu:                34
  ephemeral-storage:  484204528Ki
  hugepages-1Gi:      0
  hugepages-2Mi:      0
  memory:             165416684Ki
```

On a side note, if you are looking for options on how to **protect your vSphere and VMware Cloud Director** workloads, [Nakivo Backup & Replication](https://www.nakivo.com/) offers capabilities to back up vSphere VMs and VCD objects such as vApps, individual VMs and vApp metadata and ensure that remote workloads can be recovered in case of a data loss event.

[![nakivo backup](/img/2022-10-26-13-45-41.png)](https://www.nakivo.com)