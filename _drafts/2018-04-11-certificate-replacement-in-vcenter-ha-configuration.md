---
layout: post
published: false
title: Certificate replacement in vCenter HA configuration
---
Recently I had to change the default certificates of a newly installed vCenter. Nothing unusal with that, if not for the fact that I didn't think about vCenter HA that I configured before getting the certs. If only I had read [that little piece of advice](https://docs.vmware.com/en/VMware-vSphere/6.5/com.vmware.vsphere.avail.doc/GUID-CDC20BD4-E0CE-45D9-B73B-9AA795DA5FDD.html) from VMware...

> If you want to use custom certificates, you have to remove the vCenter HA configuration, delete the Passive and Witness nodes, provision the Active node with the custom certificate, and reconfigure the cluster.

Anyway, I didn't read so I replaced the certificates with the PSC web gui and SSH'd to my VCSA to restart the services (more info [here](https://docs.vmware.com/en/VMware-vSphere/6.5/com.vmware.psc.doc/GUID-15A4FD99-37E2-41E5-8A35-247B8FDB019D.html)).

When I tried to start the services after stopping them I got the following output:

```
root@srv-vcenter [ ~ ]# service-control --start vmafdd
Perform start operation. vmon_profile=None, svc_names=['vmafdd'], include_coreossvcs=False, Include_leafossvcs=False
2018-04-11T10:00:19.720Z	Running command: ['/usr/bin/systemctl
```

