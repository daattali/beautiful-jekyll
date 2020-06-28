---
layout: post
published: true
title: 'AWS Lambda: Quarkus vs Plain Java'
subtitle: 'Benchmark expirement'
date: '2020-06-28'
image: /assets/img/quarkus_logo.png
share-img: /assets/img/quarkus_logo.png
tags: [serverless, code, aws, benchmark]
---

## TL;DR

In my current job I've been using [AWS Lambda](https://aws.amazon.com/es/lambda/) with plain Java 8, and to be honest, the first time this didn't sound too good for me. I mean, don't get me wrong, I'm mainly a Java Developer, but from previous experiences, I know how slow a Spring Boot app can be to start and the fact that serverless functions have what it's known as ["Cold Start"](https://en.wikipedia.org/wiki/Cold_start_(computing)) didn't make too much sense for me.

However, they didn't have too many problems with cold starts because first, they don't use SpringBoot and second for those services that it is unaffordable a cold start there is something called "Warm Up" which previously it was just a CRON that would make a call to your Lambda to keep it alive and avoid cold starts, but now AWS has released a new feature called ["Provisioned Capacity"](https://aws.amazon.com/blogs/compute/new-for-aws-lambda-predictable-start-up-times-with-provisioned-concurrency/) which will initialize the requested number of execution environments so they can be ready to respond to invocations.

On the other hand, not so long ago I saw a demonstration given by a RedHat employee of their new project [Quarkus] (https://quarkus.io/). It showed how incredibly fast it was to start a Java app and how well it works with Kubernetes, as Quarkus was meant to make Java more cloud-friendly.

Just a few days ago, my brain decided to relate AWS Lambda with plain Java (as in my current job) and Quarkus, and I was wondering what the results would be in terms of cold start, memory, and speed for the following requests. So this is my experiment, probably not the most scientifically accurate, but I hope it gives you an idea of ​​the performance of these technologies with AWS Lambda.

## Experiment 

I developed two simple projects: one with Java 8 with the default DynamoDB client and the other with Quarkus and the Quarkus DynamoDB client. Both projects will simply print the received request, query an existing DynamoDB item, and return it. At the end of the post, you will find the repositories if you want to play around with them (note that the code is not beautiful, it was developed just for the sake of this experiment). And these are my findings:

### Plain Java 8

![Java8LambdaCloudwatch](/assets/img/java-lambda-cloudwatch.png)

### Quarkus Java 11

![Java8LambdaCloudwatch](/assets/img/quarkus-lambda-cloudwatch.png)

So, in terms of cold start, we can appreciate that for the first request Plain Java 8 took almost **24800ms** to finish while Quarkus did it in less than half with **9000ms**.

The following requests with the function "hot" took Plain Java 8 an average of 484.78ms. While for Quarkus it took an average of 503.55 ms. Since these numbers are only for 3 requests and the numbers are very close to each other, I would dare to say that they would probably converge to the same number with a larger sample. Anyway, we can accept that after the cold start, the following requests seem to last more or less the same in Plain Java 8 or Quarkus.

In terms of memory, it's fair to note that Quarkus (172mb) required more memory than Plain Java 8 (137mb). But keep in mind that Quarkus provides us with a dependency injection feature (among other things) that our other option doesn't provide.

Yeah, I know, probably I should try making 1K requests and take the average or probably my code is not fair with one of the subjects under test, I'm completely open to suggestions, but what I can guarantee is that I did this 3 times (destroying all the infrastructure and creating it again) and the results were similar.

Another point to take into consideration is the size of the package uploaded to AWS. We can appreciate that in this case, Quarkus is heavier than Plain Java 8.

![PackageSizeOfLambdaFunctions](/assets/img/aws-lambdas-details.png)

I know there is a feature in Quarkus that allows us to produce a native app, which could have a faster cold start, but so far I have not been able to get it to work with AWS Lambda. When I make it work I will publish my findings.