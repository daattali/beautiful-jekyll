---
layout: page
title: Developer zone
subtitle: Application Developers
---

The developers of HPC applications have traditionally been forced to work in serial languages, such as Fortran or C, to develop their parallel codes. By leveraging libraries such as MPI or OpenMP, these developers are thus responsible for all the tricky, low level details of parallelism which is critical for performance but for many domain programmers is uninteresting from the perspective of the science or engineering they are looking to simulate. It is therefore highly beneficial to raise the abstraction level and for HPC programmers to encode their application in a much richer manner, thus providing significant information to the compiler for it to drive the parallelism. This is especially important as we move to exascale which the larger and more heterogeneous architectures.

## Devito

We are enhancing the Devito DSL by porting it on top of the xDSL common ecosystem. Devito is a Python based DSL enabling programmers to design highly optimised finite difference kernels for use in inversion methods. This popular tool is especially common for seismology workloads, however can be applied to very many different applications. The Devito xDSL fork can be found [here](https://github.com/xdslproject/devito)

https://github.com/xdslproject/devito

## PSyclone

We are looking to enable PSyclone to utilise MLIR by integrating our xDSL common ecosystem. We will link to work and updates as these progress. 

## Fortran

There is much work currently on-going in the LLVM community around the Flang Fortran frontend. We believe that it will be possible to integrate the xDSL toolkit into Flang and enable DSL style abstractions in Fortran directly. 
