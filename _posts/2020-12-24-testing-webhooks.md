---
layout: post
published: true
title: 'Automating webhook tests'
subtitle: 'Testcontainers + Ngrok + Docker'
date: '2020-12-24'
image: /assets/img/testcontainer-logo.png
share-img: /assets/img/testcontainer-logo.png
tags: [java, test, automation, docker]
---
Has it happened to you that you are coding a test that requires you to wait for a webhook notification? It is a problem because normally the third-party service is outside your network and your machine will not hear their notification unless you provide them with your public IP, and sometimes the public IP is not a feasible option.

![HowToTestWebhooks?](/assets/img/how-to-test-webhook.png)

The automated tests that I have seen for these scenarios aren't too pretty. So maybe there is a better/prettier way to do this, but I wanted to share my approach in case anyone finds it useful.

## Why?

When your code needs to interact with a third party, you should probably take some time to read their documentation to learn how to make requests to them and how they will respond. 

Unfortunately, sometimes their documentation is out of date and when that happens your trust in their documentation disappears. Therefore, you will want to see for yourself that everything really works as expected and be prepared for any undocumented behavior that you encounter.

Besides that, I think it's useful to have tests between my code and anything outside my control to be able to know that everything works as expected.

## How?

I used [testcontainer](https://www.testcontainers.org/) to integrate into my tests the lifecycle of the Docker containers that I required. Testcontainer lets me forget about having to run `docker run` and `docker stop` before and after running any of my tests, as it integrates those commands with the start and finish of related tests.
 
I used [ngrok](https://ngrok.com/) to open a tunnel from the Internet to my container so the webhook could target the server waiting on my test. In other words, it allows me to have an URL for my public IP and makes accessible my machine from outside my private network.

And a small web service that will be listening for any request made to the Ngrok URL.

## Proposal

Putting all the pieces together this is more or less what I build to be able to automate a webhook test.

![NgrokForWebhookTesting](/assets/img/ngrok-with-testcontainers.png)

To illustrate what I did I made a dummy project that you can find [here](https://github.com/JosemyDuarte/testcontainer_webhook_poc).
