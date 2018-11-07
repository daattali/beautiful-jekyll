---
layout: post
title: PopSim Workshop
subtitle: New advances in simulation will allow marine biologists to simulate very large population sizes
---

Last Saturday I attended the PopSim Workshop at Cold Spring Harbor. The workshop was organized in an effort to address the lack of 
benchmark simulations in population genetics and genomics for evaluating methods. A “benchmark” set is a set of simulations that everyone 
uses to evaluate and compare their methods to each other. Benchmark datasets for image recognition, like ![MNIST](https://en.wikipedia.org/wiki/MNIST_database), 
have been crucial in moving the field of machine learning forward.

We discussed how simulations have bias in the way that they are designed by different people, depending on which aspects of 
evolution the designer thinks about the most. Many people discussed how simulations could help us resolve issues and sources of bias in 
the analysis of genomic data, including:
* SNP callling and polarization
* Gene conversion
* Polyploidy
* Pop structure
* Background selection
* Hitchhiking
* Phasing
* mutation rate variation  and multi-nucleotide mutations
* demographic history and population size history
* recombination rate evolution
* sweep finding
* introgression

We also discussed different ways of approaching testing methods as a community and developing benchmarks:
* hold a DREAM challenge. Teams are presented with a population genomic dataset (simulated with known truth) submit their 
estimates of important parameters in the data (such as demographic history, selection, recombination, etc). 
* start a repository with a common metadata format for simulations, where people can deposit their code and results
* first develop a basic set of benchmark simulations, starting with simple, tractable problems 

Over the course of only one day, little consensus was reached on how the group would proceed, and more discussion will be necessary to 
determine the next steps. **However, one clear consensus that emerged was how simulated data should be stored.**

Jerome Kelleher presented the [recent method he and others have devised to track and store genealogies from simulations](https://www.biorxiv.org/content/early/2018/06/07/248500). 
Their method is called “tree sequence recording” and now allows the simulation of entire genomes on thousands to millions of individuals 
in orders (yes, orders) of magnitude less time and hard disk space. The method is already been implemented in [popular simulation 
programs](https://www.biorxiv.org/content/early/2018/11/06/407783). Now Jerome is working on tools to estimate population genomic 
parameters directly from tree sequence data (“tskit” is coming), and on ways to estimate tree sequence from real data. Overall, 
I left with the impression that this is a very exciting development in population genomics right now.

Given this new ability to simulate populations that would be representative of marine species, this is an excellent time for 
RCN-ECS to be thinking critically about how evolutionary processes may play out uniquely in marine systems: 

**What kind of “benchmarks” do YOU think we need for understanding the strengths and weaknesses of methods for population genetic 
inference?** 

Feel free to email your thoughts to evolvingseas@gmail.com. If we get enough responses, I will write another post.

### Biography
Katie Lotterhos is an Assistant Professor in the Department of Marine and Environmental Sciences at Northeastern University. 
