---
layout: post
title:  "Framework Development Guidelines"
date:   2023-01-22 00:05:00 AM
categories: Framework
---

These days at work I have been involved in developing a framework for application development. The main purpose of this framework is

1. Code sharing
2. Code can be easily tested
3. New Pipelines can be created quickly by new developers
4. Easy of deployment / release cycles
5. Maintaining the code should be easy
6. Each component performance like latency, success/failure rate etc can be easily tracked and alerted on.


Based on these guidelines, we came up with a design of creating a DAG (Directed Acylic Graph) which depicts all the operations possible in the pipeline. This dag can be easily created based on a given config file and multiple pipelines can be scheduled/executed by the framework.

Creating and running a DAG is used in many softwares like
- Airflow
- Microsoft MS Build
- Nuget
- ....

The core components of our framework are
1. Processors
2. Each processor has a configuration which it defines
3. A property bag/Context which is used for data sharing between the different processors
4. Services are shared between processors. Accessing the Database or logging or Perf Monitoring are exposed as services and they are registeted when the application starts. These services are shared across the components through DI.


Some of the main learnings for me while developing this framework were

- Use of Dependency Injection Container, we used Autofac because its a mature product and supports lot of features we needed like named resolution etc. The use of DI makes every thing very testable and loosely coupled.
- Creating of the Dependency graph makes the code easily composable where dependency between the processors are defined through the DependsOn Property.
- Using testing framework like MOQ makes unit testing very easy.
- Exposing Logging as a service so that we can define different loggers like ConsoleLogger, Specific Hosting component loggers.
- Using of disposable pattern to measure the Latency.
- Dynamic loading of liraries through Assembly.load , this makes library loading very easy and multiple compontents can share the same code.
- Using Least Recently Used Cache for application development
- Saving simple Graph Visualization scripts to view the DAG. Python has a very useful package like GraphViz for plotting graphs.


I will be writing individual blog entry for some of these component to make it more clear.

!Happy Learning and improving one day at a time!


