---
layout: post
tags: [.net, roslyn, refactoring, analysis]
title: Adventures in the .NET Compiler Platform aka Roslyn!
author: emir_osmanoski
comments: true
---

I recently started reading up the title subject of the .NET Compiler Platform
(aka Roslyn) and all the interesting things you could do with it in terms of
code quality and coding standards analyzers and code fixers.

There is a lot of materials on Roslyn out there specifically on the official
Nicrosof Focs and I won't go into more details here besides the following couple
of points that should serve as an intrdocution for the remainder of the post:

- Roslyn is a set of API's and Services that allow us to acesss the .NET
  Compiler pipeline and have access to a lot of information about a lot of
  aspects of our projects and code while we are working on them.
- Compilers are a complex subject that's interesting to think about, but
  maybe hard to understand.
	- They live to understand and reason about what we are trying to tell the computer to do!
	- To do this they've done a bit of divide and conquer trick where they've organized themselves around several steps.
	- The first of which is 
- We have access to low level syntax trees that describe how the code is
  structured
- We also have acccess to API's and services that can tell us how the code is
  interconected, and what it actually means! 
- On top of all this there are also API's that allow us to perform major changes
  that range from code refactorings to project and solution level refactorings!
 
For a lot more information presented in a much more better way please check out
the documents
[here](https://docs.microsoft.com/en-us/dotnet/csharp/roslyn-sdk/compiler-api-model)

So, after going through the materials on the docs site and on github around
Roslyn as well as the tutorial analyzer and code fixer for refactoring unused
properties to consts I decided to tackle another (maybe too complicated)
challenge as a way to better understand exactly how these things work.

# The Example problem

What I was looking to address were intances were the the 