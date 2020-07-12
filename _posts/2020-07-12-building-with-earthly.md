---
layout: post
published: true
title: 'Earthly + Quarkus Funqy'
subtitle: 'Simplifying building automation'
date: '2020-07-12'
image: /assets/img/earthly-logo.png
share-img: /assets/img/earthly-logo.png
tags: [cloud, serverless, quarkus, earthly]
---

There is a new building automation tool in the neighborhood named [Earthly](https://www.earthly.dev/). Its intention is to simplify CI pipelines. Nothing like an image to explain it better:

![EarthlyIntegrationDiagram](/assets/img/earthly-integration-diagram.png)

I would describe it as a [docker multistage build](https://docs.docker.com/develop/develop-images/multistage-build/) with batteries. It actually has a Docker-like syntax. 

These are some features right from their [repo](https://github.com/earthly/earthly):

🐳 **Build anything via containers** - build container images or standalone artifacts (eg binaries, packages, arbitrary files)

🛠 **Programming language agnostic** - allows use of language-specific build tooling

♻️ **Reproducible builds** - does not depend on user's local installation. Runs the same locally, as in CI

⛓ **Parallelism that just works** - builds in parallel without special considerations the user has to make

🏠 **Mono-repo friendly** - ability to split the build definitions across a vast directory hierarchy

🏘 **Multi-repo friendly** - ability to import builds or artifacts from other repositories

### Building something with Earthly

Some days ago while taking a look at [Quarkus](https://quarkus.io/) I found [Funqy](https://quarkus.io/guides/funqy-amazon-lambda), part of Quarkus’s serverless strategy that aims to provide a portable Java API to write functions deployable to various FaaS environments like AWS Lambda, Azure Functions, Knative, and Knative Events (Cloud Events). So I decided to see how easy would it be to build a simple "Hello World" with **Funqy** and **Earthly**.

I'm not going to focus on the Funqy part since I simply followed their [guide](https://quarkus.io/guides/funqy). I wanted to know how complicated it would be to define a `build.earth` file that allowed me to test and build a native quarkus application. This was the result:

```dockerfile
FROM quay.io/quarkus/centos-quarkus-maven:20.1.0-java11

WORKDIR /java-example

deps:
    COPY pom.xml ./
    RUN mvn -B de.qaware.maven:go-offline-maven-plugin:1.2.5:resolve-dependencies
    SAVE IMAGE

build:
    FROM +deps
    COPY src src
    RUN mvn -Pnative clean package
    SAVE ARTIFACT target/ /target AS LOCAL target
```

With that file, I am creating a reproducible build that will create a `target` folder with my artifacts.

As said before, it is very similar to Dockerfile syntax. Apart from just a few new intuitive commands, if you know Docker you will get comfortable with Earthly really fast.

#### Describing build.earth
 
**base**
 
This section initializes the build environment, it is like a base for all other steps, it applies to all "targets".

(1) Base Docker image

(2) Setting working directory

```
(1) FROM quay.io/quarkus/centos-quarkus-maven:20.1.0-java11
(2) WORKDIR /java-example
```

**deps**

This section gathers all my project's dependencies.

(3) Target's name

(4) Copy the `pom.xml` to allow earthly to create a layer/cache of the dependencies of my application.

(5) Runs `maven` and download all my application dependencies.

(6) Saves this container as an image. This allows the following steps/targets to use all the hard work done by these commands.

```
(3) deps:
    (4) COPY pom.xml ./
    (5) RUN mvn -B de.qaware.maven:go-offline-maven-plugin:1.2.5:resolve-dependencies
    (6) SAVE IMAGE
``` 

**build**

This section actually builds my artifact.

(7) Target's name

(8) Defines that this target is built from `deps` target. There is a dependency.

(9) Copy all my source code into the container.

(10) Maven command to execute all my tests and build my artifact.

(11) Saves output into my machine on a `target` folder.

```
(7) build:
    (8) FROM +deps
    (9) COPY src src
    (10) RUN mvn -Pnative clean package
    (11) SAVE ARTIFACT target/ /target AS LOCAL target
```
 
 Of course, this is a toy example. You can have earthly files way more complicated (even multi-repo projects). It was also really easy to integrate it into Github Actions. This is the repo for anyone who might want to take a deeper look [Earthly Repository](https://github.com/JosemyDuarte/earthly-quarkus-poc).
