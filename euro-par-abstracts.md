---
layout: page
title: Euro-Par Workshop Abstracts
subtitle: Abstracts of talks from the Euro-Par DSL workshop
---

## Gihan Mudalige

__Keynote: Evolutionary Re-Engineering of an Industrial HPC application with OP2__

The rapid evolution of High Performance Computing architectures has resulted in highly complex systems with massively parallel heterogeneous processors, deep and multiple memory hierarchies and interconnects. As a result, maintaining performance as platforms change has becomes increasingly difficult. On the one hand, open standards have been slow to catch up with supporting new hardware, and for many real applications have not provided the best performance achievable from these systems. On the other hand, proprietary solutions have only targeted narrow vendor-specific devices resulting in a proliferation of parallel programming models and technologies. In this talk I will present how we used OP2, one of the earliest DSLs developed in the UK, to re-engineer the Hydra CFD application, a production HPC application from Rolls-Royce to achieve a performance portable code-base.  The recent use of the new application, OP2-Hydra, to carry out break-through simulations reaching fidelity levels for virtual certification of aero gas-turbine engine design will be presented. I will detail the simple source-to-source and automatic code-generation techniques based on maintainable software technologies led to these achievements enabling to evolve the application without overhauling or re-writing the entire code-base. The talk will discuss how OP2 has remained agile in delivering performance portability in the face of over a decade of hardware and parallel programming innovations and discuss lessons learnt from this work.

## Maurice Jamieson

__Research paper: Performance of the Vipera framework for DSLs on micro-core architectures__

Vipera provides a compiler and runtime framework for implementing dynamic Domain-Specific Languages on micro-core architectures. The performance and code size of the generated code is critical on these architectures. In this paper we present the results of our investigations into the efficiency of Vipera in terms of code performance and size.

## Yifei He

__Research paper: FFTc: An MLIR Dialect for Developing HPC Fast Fourier Transform Libraries__

Discrete Fourier Transform (DFT) libraries are one of the most critical software components for scientific computing. Inspired by FFTW, a widely used library for DFT HPC calculations, we apply compiler technologies for the development of HPC Fourier transform libraries. In this work, we introduce FFTc, a domain-specific language, based on Multi-Level Intermediate Representation (MLIR), for expressing Fourier Transform algorithms. We present the initial design, implementation, and preliminary results of FFTc.

## Nick Brown

__Reseach paper: TensorFlow as a DSL for stencil-based computation on the Cerebras Wafer Scale Engine__

The Cerebras Wafer Scale Engine (WSE) is an accelerator that combines hundreds of thousands of AI-cores onto a single chip. Whilst this technology has been designed for machine learning workloads, the significant amount of available raw compute means that it is also a very interesting potential target for accelerating traditional HPC computational codes. Many of these algorithms are stencil-based, where update operations involve contributions from neighbouring elements, and in this paper we explore the suitability of this technology for such codes from the perspective of an early adopter of the technology, compared to CPUs and GPUs. Using TensorFlow as the interface, we explore the performance and demonstrate that, whilst there is still work to be done around exposing the programming interface to users, performance of the WSE is impressive as it out performs four V100 GPUs by two and a half times and two Intel Xeon Platinum CPUs by around 114 times in our experiments. There is significant potential therefore for this technology to play an important role in accelerating HPC codes on future exascale supercomputers.
