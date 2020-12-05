---
layout: post
title: How To Choose Pre-trained Models
subtitle: Guide on How to Begin Choosing Pretrained Models for Solving a Problem
gh-repo: ghosh-r/ghosh-r.github.io
gh-badge: [star, follow]
tags: [deep-learning, neural-networks, transfer-learning]
comments: true
cover-img: /assets/img/nn-sheet.jpg
---

There isn't exactly a cheat sheet if you are looking for that. You can do it through these steps-

#### Read Respective Papers

It is not as hard as it sounds. Because all those models are discussed in detail in some papers. For example, this is the ResNet Paper- [Deep Residual Learning for Image Recognition](https://arxiv.org/abs/1512.03385). You can learn about ResNet there. And, it is very likely that your framework's documentation has explicit links to papers where the concerned model was discussed. This one is the link to PyTorch's page-

##### [TORCHVISION.MODELS](https://pytorch.org/docs/stable/torchvision/models.html)

#### Study Benchmarks

You should study benchmarks. Benchmarks are a great way to achieve better results and to see whether an architecture fits your needs. For example, the last time I used MobileNet, I remember it being just about 17 MB in size with pre-trained weights and works great for narrow use cases such as recognizing sign-language. So, you can deploy the model to mobile devices, Raspberry Pi- you name it! On the other hand, you would want to use ResNet-50 for achieving state-of-the-art results.

* You can rely on standard benchmarks such as [DAWNBench- An End-to-End Deep Learning Benchmark and Competition](https://dawn.cs.stanford.edu/benchmark/), powered by Stanford, and,
* benchmarks by researchers- [cnn-benchmarks](https://github.com/jcjohnson/cnn-benchmarks#cnn-benchmarks)-- this one is by Justin Johnson, who is now at UofM, and used to teach Stanford's reputed CNN course.

#### Study Others' Works

1. Look at projects created by others, see what they used, and if they have had put blog posts accompanying the projects- read those and look for justification for using a certain framework over another. Or just look at their code and their results.
2. Look at open and old Kaggle competitions' submissions- look at what architecture they are using, and read about the justification, if any.

#### Prototype a Lot

Whether it's a school project or personal, whether it is Kaggle competitions, prototype a lot with the same data- use different architectures, different variants, and so on. And judge for yourself which is the best. Ultimately, using models for a certain task is a skill that you master through practice. You have to do experiments, make prototypes with different pre-trained models to get a feel for them.
