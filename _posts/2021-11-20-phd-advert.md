---
layout: post
title: PhD opportunity
subtitle: Come to Edinburgh and work with us researching DSLs and compilers
thumbnail-img: /assets/img/phd_advert.png
tags: [PhD]
---

We are advertising for a fully funded (with nationality restrictions) PhD position at the University of Edinburgh with the student based at EPCC and in collaboration with the School of Informatics.

## About the project

Writing efficient parallel code for current generation supercomputers is difficult and in the domain of the (relatively) few experts. However this situation is set to become even more challenging as the trend for heterogeneity (i.e. use of accelerators) and scale increase significantly with next generation exascale machines. Put simply, sequential languages that we have relied upon for so long to write our parallel codes do not provide the necessary abstractions when it comes to writing parallel codes. As a community we have gotten around this by making it the job of the programmer to determine all aspects of parallelism for their code and provide their own parallel abstractions (e.g. by explicitly designing at the code level for geometric decomposition, or divide-and-conquer, or pipeline parallelism), but determining this low level and tricky detail is time consuming, requiring significant expertise, as well as not being scalable to future much larger and more complex supercomputers.

There is however another way, and that is of the use of Domain Specific Languages (DSLs). These are languages which, out of the box, provide specific abstractions to the programmer which they can then use as a basis for writing their code. The idea being that by encouraging the programmer to work within the confines of specific rules governed by the abstractions and restrictions of a specific domain, then there is a significant amount of information upon which the compiler can act to determine details that traditionally required the programmer to specify manually. In-fact the word language is a bit of a misnomer here, instead the key is abstractions as many of these technologies are embedded within existing languages such as Python.

DSLs have demonstrated their potential to play an important role in programming future exascale simulation codes, however there is a big problem! The issue is around the underlying compilation stack, where DSLs are often siloed and tend to share very little, if any, underlying infrastructure. This means that it can be costly to develop new DSLs, the underlying technology stack can be brittle, and there can be a lack of third party tools such as debuggers and profilers. But there is also a potential solution and that is of Multi Level Intermediate Representation (MLIR) which is a framework for IR that enables one to effectively lower source code to the general representation required by the LLVM compiler through a series of pre-built abstractions. There are very many existing MLIR dialects, with it being possible to write new ones too, thus enabling many different languages, abstractions, and domains to more readily integrate with the existing and mature LLVM tooling without losing information in the translation process.

## Who you would be working with

## For more details
