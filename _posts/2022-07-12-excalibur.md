---
layout: post
title: xDSL at the ExCALIBUR workshop
subtitle: The xDSL project presented at the ExCALIBUR workshop
thumbnail-img: /assets/img/excalibur_workshop.jpg
tags: [project, technical]
---

This week saw the two day ExCALIBUR workshop held at the Met Office where representatives from across the programme met and discussed project-level updates as well as opportunities for collaboration and interaction during the research. There were some very interesting projects presented, and clearly the programme is doing a fantastic job pushing UK science towards exascale and beyond.

<img src="/assets/img/excalibur_workshop.jpg" align="left">

As part of this workshop xDSL PI, Tobias Grosser, gave an update about the xDSL project itself and, considering that xDSL has been running for almost a year, this was also an ideal opportunity to take stock of where we are as a project, to reflect on early successes, and refine the strategy going forwards into the next two years. Tobias described the underlying [xDSL](https://github.com/xdslproject/xdsl) framework that has been developed in the past 12 months, before highlighting work that has been undertaken to build on this for both the existing [PSyclone](https://github.com/xdslproject/PSyclone) and [Devito](https://github.com/xdslproject/devito) DSLs. 

The compilers of both these existing DSLs have been enhanced to run on-top of the xDSL stack, with bespoke dialects and transformations provided which are expressed via the IRDL MLIR-DSL. Exploitation of distributed memory parallelism and GPUs is also possible with xDSL, for instance the PSyclone xDSL work already having been demonstrated to run on 32768 cores of ARCHER2 and V100 GPUs. Moving forwards, the integration with xDSL provides numerous opportunities, including the ability to leverage the LLVM ecosystem more widely and easily build upon work being done elsewhere by the community.
