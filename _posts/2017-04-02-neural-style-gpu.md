---
layout: post
title: Neural Style on AWS GPU Instance!
image: /img/hello_world.jpeg
comments: true
tags: [aws, jupyter-notebook, cnn]
mathjax: true
---

This is my example of running a jupyter notebook on an AWS GPU instance. This allows us to greatly speed up all the computations while having all the convenience of working with a notebook on your browser.

1. Go to the [Amazon EC2 Console](https://console.aws.amazon.com/ec2/v2/) and launch an instance.

   * **Choose AMI:** Select a *Deep Learning Ubuntu AMI* from the AWS Marketplace.
   
   * **Choose Instance Type:** Select a GPU compute *p2.xlarge* Instance.
      
   * **Configure Security Group:** Create a custom TCP rule to allow port 8888. This should only be allowed for your public IP. 
   
   * **Add Storage:** (Optional) Increase size to 20 GiB
   
2. Connect to your E2 instance
3. Set up SSL certificates and Jupyter

to be continued ...