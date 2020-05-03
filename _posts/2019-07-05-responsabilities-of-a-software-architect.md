---
layout: post
published: true
title: 'Responsabilities of a Software Architect'
subtitle: 'Highlights and notes from the book Building Microservices'
date: '2019-07-05'
image: /assets/img/building-microservices-book-cover.png
share-img: /assets/img/building-microservices-book-cover.png
tags: [books, notes]
---

## A Software Architect is like a Town Planner..

I recently finished *Building Microservices* book by Sam Newman and the first concept that I found interesting in Sam's book was the definition of what a Software Architect should do. He makes a comparison against Town Planners. He explains the idea with the game SimCity as an example, where you are the Town Planner and you are not involved in the specifics of any building, but instead in the design of how the city would be connected, how the city can take advantage of its resources and always taking into consideration what new requirements (city growth) the future could bring. That doesn't mean that a Software Architect shouldn't code or that he shouldn't interfer in the design of a specific service. On the contrary, a Software Architect **should** code, and I would try to elaborate why I believe that in another post, but the main focus of a Software Architect as a "Town Planner" should be to plan and design for the bigger picture.

## Principles and Practices

To help make the daunting work of a Software Architect "easier", it is important to define the Principles and  Desired Practices that developers must follow. In a large organization the *practices* could differ between different teams, for example, the *practices* defined for a PHP team are not necessarily the same for a Python team. Although, their principles could be the same.

An example of a *practice* in a REST/HTTP application could be having documented every endpoint of a service (Swagger?). Or that each service must be designed with Continuous Deployment in mind. As *principles*, we could be talking of things like making choices in favor of changes and quick feedback.

Now, why to do this? Well, I think that defining this is really important as it provides guidance to developers on how to address some of the challenges that arise while developing software. In fact, it makes clear what we are aiming to (as a team) and facilitates teamwork for a common goal. 

## Standards 

We have been talking about principles and desired practices, but it is also important to define standards. What kind of standards? Well, probably having some services communicating through RPC, some using a Queue and others with REST/HTTP is a recipe for long nights and high stress. So, if it's in your hands, why not define a unique way for your services to communicate with each other? It will make facilitate monitoring, developing, debugging, etc.

Once have defined what it is the standard for communication, it is also important to define a non-ambiguous way of knowing when an error occurred in a request. HTTP provides some defined standards that can help you to do it correctly. But whatever protocol you choose, make sure you have a standard way of knowing when a request was OK or not, since based in that, you probably will have a lot of different paths in your logic.

## Monitoring 

I know from first hand that monitoring in a monolith is not the same as in microservices. A key thing to keep in mind when implementing microservices is that it is essential to have a cross-service view of the system health, it is necessary to have a way of monitoring the overall picture. Without it, things can get out of hand quickly once you start having more than 3 different services with more than 2 replicas, I assure you.

It is important to have standards for monitoring as well. If you have a service that pushes logs to the cloud, another that writes to a file in its container and another that just prints to standard output, having a cross-service view of the system health will not be fun at all.

## Tip

One thing that might help to get all this right are exemplars. With a **real world** exemplar you will provide to developers an easy way to follow not only your *Practices* and *Principles*, but also your standards.
  