---
layout: post
title: What's new in vSphere 8 Update 1
date: 2023-03-14T14:57:20.305Z
nobanner: "yes"
---

In 2022, VMware rolled out vSphere 8 which brought a number of new features, one of the big ones being vSAN ESA. A few months later, we are already graced with the Update 1 version which we will look at today. Note that this version was only announced and hasn't reach IA (initial availability) yet. Look up the new release cycle that came with vSphere 8 if you never heard about IA.

This new version comes with the usual truckload of nice diagram and marketing wordage such as `delivers enhanced value`. Here are the main changes in vSphere 8 Update 1.

### VMware vSphere Configuration Profiles

This feature was announced in vSphere 8 and aims to somewhat be a less clunky replacement of host profile. It was announced but not released which will be the case in this version. It aims to provide Desired Configuration capabilities at the cluster level for your vSphere hosts. It will monitor configuration drift and issue notifications for the administrator to act on and remediate.

![VMware vSphere Configuration Profiles](/img/2023-03-14-18-41-09.png)

### Integration of VMware Skyline Health Diagnostics with vCenter

Skyline Health Diagnostics is a self-service diagnostic platform to provide admins with insights in their environment with issues diagnosis, failure resolution in an automatic fashion. VI admins can use it to troubleshoot issues before contacting support (Broadcom will like it). In vSphere 8 Update 1, Skyline Health Diagnostics is integrated with vCenter.

### Heterogenous vGPU Profiles on the same GPU

Well, the title is pretty self-explanatory on this one. Different vGPUs on a physical GPU can be assigned to different types of worloads such as VDI, compute, graphics... 

![Heterogenous vGPU Profiles on the same GPU](/img/2023-03-14-18-46-53.png)

### vSphere Green Metrics

Another one that was announced in vSphere 8, Green Metrics works for hosts and VMs to track energy consumption and establish the efficiency of the infrastructure. These metrics include:

•	Host energy consumption not used by VMs (overhead)
•	Host is idle consumption
•	Host's consumption used by VMs
•	VM-level power consumption (vSphere 8 Update 1)

### NVIDIA NVSwitch

This was a TIL moment (Today I learned) as I'd never heard of NVSwitches before, which I still need to [read more about](https://www.nvidia.com/fr-fr/data-center/nvlink/). In a nutshell, NVIDIA NVSwitch is a high-performance networking fabric designed for interconnecting multiple GPUs and servers in a data center environment. vSphere 8 Update 1 brings support for NVSwitch for high performance and connects up to 8 GPUs to the same VM.

### Okta Federated Identity Management for vCenter​

I was quite chuffed to see this one as vCenter was somewhat lacking in the identity federation department. vSphere 8 Update 1 adds support for 3rd party identity providers to Okta for both vCenter and NSX Manager.

### Other changes

* Support for Fault Tolerance of VMs Employing vTPM
* ESXi Quick Boot Support on Servers with TPM 2.0 Chips
* Full vSphere Client support is available to manage Standalone Hosts with vSphere Lifecycle Manager
* Supervisor Services with vSphere Distributed Switch
* VM Service Bring Your Own Image
* VM DirectPath I/O Hot-Plug for NVMe
* Multi VC deployment for VASA Provider without Self-Signed Certificate
* Enhanced XCOPY to optimize data copy between Datastores across different storage arrays
* NFSv3 vmkPortBinding
* Increase WSFC clusters per ESXi host from 3 to 16 (should we though?)

## Wrap up

In conclusion, vSphere 8 Update 1 brings several exciting features and improvements that can greatly benefit organizations of all sizes. From enhanced security and performance capabilities to improved scalability and flexibility, the new version offers a range of functionalities that can help businesses streamline their operations and improve their overall efficiency.

On a side note, if you are looking for options on how to **protect your vSphere and VMware Cloud Director** workloads, [Nakivo Backup & Replication](https://www.nakivo.com/) offers capabilities to back up vSphere VMs and VCD objects such as vApps, individual VMs and vApp metadata and ensure that remote workloads can be recovered in case of a data loss event.

[![nakivo backup](/img/2022-10-26-13-45-41.png)](https://www.nakivo.com)