---
layout: post
title: Interacting with containerd runtime for kubernetes
DATE: 
subtitle: ''
metadescription: Since docker deprecation in kubernetes, find out how to interact
  with the containerd runtime

---
If you work with or learn Kubernetes, you probably know the docker is now deprecated. While most people are comfortable with the docker cli, you now need to use another runtime such as containerd or CRI-O.

I am currently in the process of learning kubernetes and I went with containerd for no particular reason as I am not knowledgeable on the topic. However, I decided to write this piece to help those who are in the same boat get their bearing around containerd. I opted to show a few different things that I feel may be valuable if you are using containerd with kubernetes. I will try to update this blog with more commands when I need new ones.

#### Containerd command line: ctr

Everyone knows docker to interact with its eponymous container runtime. The default tool to interact with containerd is named "ctr". Although not as intuitive as docker, ctr is fairly user friendly and easy to use.