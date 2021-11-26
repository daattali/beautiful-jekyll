---
layout: post
title: What is the Retreat Mode for vSphere clusters
DATE: 
subtitle: ''
metadescription: The VMware Retreat Mode lets you put your clustering capabilities
  on hold for maintenance duties.

---
In vSphere, the DRS cluster duty have historically been tied to vCenter server, making it unavaiable if it went to go offline. In order to rectify that, vSphere 7u1 introduced vSphere Cluster Service VMs, a cluster of small virtual appliance holding the clustering duties to take them out of vCenter's hands and improve availability, which brought Retreat Mode along with it.

vSphere Cluster Services (vCLS) is enabled by default and runs in all vSphere clusters, even 1 and 2 nodes clusters. It uses "agents" virtual appliance to maintain the health of cluster services that created automatically along with anti-affinity DRS rules. I must point out that this is not something you go about turning off for fun in a production environment like you would with DRS, VMware give the following warning about it:

> **_Note:_** _Retreat Mode should be used with extra caution and should be used only for the purposes mentioned in this document._ 

If you try to power off these VMs, you will get a warning and they will be automatically powered back on anyway as the vCLS monitoring service runs every 30 seconds.

![](/img/retreatmode1.png)

Now what is VMware Retreat Mode? Retreat Mode lets you disable the vSphere Clustering Service to automatically remove the agent VMs. In a number of cases, vCenter will automatically place a cluster in retreat mode. 

![](/img/retreatmode6.png)

There are not a lot of use cases for it since you can relocate the VMs to other hosts and datastores. You can also somewhat configure the datastore placement of these VMs in vCenter 7 Update 3.

However, you may still need to evict these VMs manually for a span of time, in which case, Retreat Mode is what you are after. There is no "Retreat Mode" button in the UI, it happens through an advanced setting at the vCenter level targeting a specific cluster.

* First we need to find the cluster domain ID of the cluster we want to put in retreat mode. Select the cluster in the vSphere client and look for the "domain-cXXX" section in the url of your browser.

![](/img/retreatmode2.png)

* Then select the vCenter > Configure > Settings > Advanced Settings > Add a new setting like so

    | Name                                       | Value  |
    | ------------------------------------------ | ------ |
    | config.vcls.clusters.domain-c16011.enabled | True   |

![](/img/retreatmode3.png)

* Within 1 minute, all the vCLS VMs in the cluster are cleaned up, the Cluster Services health will be set to Degraded and DRS will stop working. You will find the following warning.

![](/img/retreatmode4.png)

* If you look at the events you notice the vCLS VMs being powered off and deleted.

![](/img/retreatmode5.png)

You can obviously revert and re-enable the Cluster Services by changing the setting to True. You cannot remove a vCenter Setting.