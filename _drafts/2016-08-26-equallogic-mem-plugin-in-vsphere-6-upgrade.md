---
layout: post
published: false
title: Equallogic MEM plugin in vSphere 6 upgrade
---
If you have a Dell Equallogic SAN it is more than likely that you are using the EQL extention for ESXi called MEM or "Multipath Extension Module" from Dell.  
MEM is a Path Selection Plugin that uses the PSA architecture of the vmkernel to manage more effectively the IO paths in an "Equallogic aware" fashion, rather than a simple round robin or fixed path. It adds an extra PSP called "DELL_PSP_EQL_ROUTED", which is the best optimized to use in an EQL environment.

