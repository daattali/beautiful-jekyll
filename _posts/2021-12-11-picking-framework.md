---
layout: post
title:  "Deciding on the Language/Framework for your new Project"
---
This advice does not hold if you are embarking on a personal project to learn a new technology. This is advice for selecting a language/framework for a project that is being developed within a company/team.

Recently in the Data Infrastructure team at GoCardless we have started to build a new micro-service to give other teams at GoCardless access to an internal domain-specific data store. Often, at the start of a project we always have discussions in which language/framework we should implement it in.
As engineers, we always have a tendency to explore new and different things however, when building something within an ecosystem of other services that is probably one of the worst decisions you can take.

In the past these discussions were always informal and we came to a decision fairly quickly, this time around, I decided to think about a selection criteria which I'm sharing in this post. I decided the following five criteria should define which language should be selected:

### 1. Aim for long-term maintainability

You should select a language/framework which will make it easy for your team and your future selves to maintain the code base. If your team has a large code base in Python, writing a new service in Haskel might not be a great idea since if you need to come back to it six months later to fix a bug as it will take longer to context-switch back to the unfamiliar code base.

### 2. Ensure Consistency

If the service you are building is related to another set of services or components that are currently running in production, then consistency should be prioritised to ensure the same language and framework is used across the board. This reduces cognitive load for engineers. For instance, if you have a set of data ingestion services build on the SpringBoot framework, you should for consistency's sake use that framework for a new component in that space.

### 3. Prioritise Developer productivity & Team experience

At Data Infrastructure in Gocardless, we have developed services that use Go, Java (mainly SpringBoot) and Python. Due to the depth of experience in these frameworks and the fact that we have learnt best pratices in these framworks we can develop high quality components quickly. If we introduced another language to the mix we might be learning something new, however, since most of our code base is in the languages mentioned it might take us more time.
