---
layout: post
title: AWS Introduction
subtitle: This is a simple introduction on AWS - most common services what you can connect with without prior experience in cloud services 
gh-repo: daattali/beautiful-jekyll
gh-badge: [star, fork, follow]
tags: [test]
comments: true
---

AWS - in the current world of software development does not require any introduction! I am going to introduce some of the common services of AWS. In this episode, we won’t dive deep into any of them. Instead it will be a quick overview for better understanding.

Let’s start a journey of making a simple application. We have some products to offer. We want to sell them online. We will build a website to present those products to probable customers and take orders from those customers. 

Now what do we need?
- A website
- Website needs a domain name so customers can find our website easily.
- We need a computer to run the server
- File storage to keep the server codebase, products will have some image.
- We need database to keep the customer and order information
- We need to secure the server computer from hackers
- etc

Let’s have a look at what AWS offers for our needs.

## Computer to run the server
We can simply say computing machine. AWS offers 

### Elastic Cloud Compute (EC2)
With EC2, AWS gives you a virtual machine/computer to setup and run any code. It offers granular control for managing your infrastructure with the *choice of processors, storage, and networking*. EC2 virtual machines are called EC2 instances.

### App Runner
Fully managed service that makes it easy for developers to quickly deploy containerized web applications and APIs, at scale and with no prior infrastructure experience required.

### Lambda (Serverless)
AWS Lambda enables you to run your function/code in response to events. So you don’t need to think about the OS or virtual machine configuration to run your code. You simply write your function and set up to call the function on predefined events e.g. http request etc.

So we have a number of choices to run/host our server. While app runner is a ready cooked service, it is costly. We can pick EC2 instances with adequate CPU and memory.


## File storage

### Elastic Block Storage (EBS)
You can think of it as the C-drive of your computer.
EBS is usable with one compute (EC2) machine.

### Elastic File Storage (EFS)
Your hard disk to store files.
Similar to EBS. But you can attach your EFS instance to any compute machine.

### Simple Storage Solution (S3)
S3 is an object storage. That means you can put any object in this storage.

### FSx
If you need any specific type of file system, FSx comes handy. FSx supports most of the popular file systems out there.

While there are several types of storage solution, all of them have their own purpose. 
- We will use EBS with our EC2 instance.
- We will use S3 to store the product images and other images or static assets for our website.

## Database
AWS has a good number of options for databases

- Relational
  - Arora
  - RDS
  - Redshift
- Key-Value
  - Dynamodb
- In-memory
  - Redis
  - ElasticCache
- Document
  - DocumentDB (MongoDB)
- Wide-column
  - Keyspaces
- Graph
  - Naptune
- Time series
  - Timestream
- Ledger
  - Ledger Database Service (QLDB)

Let’s find **what we might need to store in databases**. We need to store
- Products information
- Customer information
- Order information
	
To store these information,
- we can pick Arora, RDS (postgres, mysql) or DocumentDB.

- Also we may want to cache some parts to make the website faster. If the website has a feed that shows the top offers, we can generate the top offer list once in a while and cache the generated list then serve it from that cache to the customers. It will save the website from generating the list every time someone visits the top offers. For caching we use in-memory database e.g. Redis or ElasticCache.

- We want our customers to search for the products easily and fast. We may want to use awesome ElasticSearch. For that, AWS has Amazon Elasticsearch.

## Domain
When we have the EC2 instance, AWS gives us an IP address to access that instance. It is better to use some beautiful domain name instead of the IP address for the customers. To manage the domain AWS has Amazon Route 53.


## *With these we can start running our website. So what’s next?*

You are right.
As our business is growing, the number of customers, number of page visits to our website is increasing. As a result, sometimes our EC2 instance is not able to cope up.
- We need more power to our server machine. We can use more powerful EC2 instances. Problem solved!
- Our business is growing more and we are already using the most powerful EC2 instance. Now what can we do? Till now we scaled up our server in one way which is known as vertical scaling.
- We will use multiple instances which allows us to add as many machines we need. This is known as horizontal scaling. When we start using multiple instances instead of one, we need a manager who will direct different requests to different machines efficiently. This is called load balancing. AWS has the Elastic load balancer (ELB). With ELB you can attach your EC2 instances and select the algorithm for how the incoming requests will be distributed among those instances.

That’s enough for today. There are lots of other services. Some more services are required to run the websites but we discussed most of the significant ones.

Hopefully this overview will help you to understand better how a website runs in the AWS infrastructure.

Next we will have a look on **how we can secure our website**.

After that I will try to take you dive deep on *containerization-docker-kubernetes, cloudformation and other IaaC* services etc.

That's enough marketing of AWS for today! ha ha!!

What are you expecting from this series? Do you have suggestions or comments on any point? Let me know in the comment.
