---
layout: post
title: Change vmnic order on vSphere host
DATE: 

---
Changing the vmnic order is an unusual thing to do and you may rightfully wonder why one would want to do that. Heterogeneous enironments are fully supported but most vSphere administrators aim at having homogeneous hosts with the exact same config in their clusters to simplify operations and avoid human errors.

Uplinks lables are no exceptions. vSphere gives them labels at the first boot that you then use to configure the vSwtiches (vmnic0, 1, 2...). However, if you make changes to the physical configuration and reorder the vSwitches you may need to change the labels to make them match the other hosts.