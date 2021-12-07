---
layout: page
title: Developer zone
subtitle: Application Developers
---

The developers of HPC applications have traditionally been forced to work in serial languages, such as Fortran or C, to develop their parallel codes. By leveraging libraries such as MPI or OpenMP, these developers are thus responsible for all the tricky, low level details of parallelism which is critical for performance but for many domain programmers is uninteresting from the perspective of the science or engineering they are looking to simulate. It is therefore highly beneficial to raise the abstraction level and for HPC programmers to encode their application in a much richer manner, thus providing significant information to the compiler for it to drive the parallelism. This is especially important as we move to exascale which the larger and more heterogeneous architectures.

## Devito

We are looking to enhance the Devito DSL by building it upon our xDSL common ecosystem. This will unlock the benefits of MLIR and the LLVM toolchain to programmers. We will link to work and updates as these progress.

## PSyclone

We are looking to enable PSyclone to utilise MLIR by integrating our xDSL common ecosystem. We will link to work and updates as these progress. 

## Fortran

There is much work currently on-going in the LLVM community around the Flang Fortran frontend. We believe that it will be possible to integrate the xDSL toolkit into Flang and enable DSL style abstractions in Fortran directly. 
