---
layout: post
title: How to use PostgreSQL database for Horizon 8 (2103) events
DATE: 
subtitle: ''
metadescription: Learn here how to set up a PostgreSQL database to store the events
  with Horizon 8 (2103).

---
VMware released Horizon 8 (2103) on the 23rd of March 2021. While previous versions only allowed Microsoft SQL Server and Oracle for the events database, this latest version introduces support for PostgreSQL.

The benefits of using Postgres is that it is free, lightweight and very easy to configure. We are going to describe in a few steps how to install Postgres and configure the events database to use it.

## Install and configure PostgreSQL

Although it is not embedded in the installer like vCenter's vPostgres database, you will find that getting started with PostgreSQL is a lot easier than even Microsoft SQL Express.

In this blog I am installing the database directly on the Connection Server as it is a lab with a single instance. Make sure to install it on a third part server if you run multiple Connection Servers.

* First, check for database compatibility in the new [VMware interoperability matrix](https://interopmatrix.vmware.com/#/Database?productId=569&extProdIds=326&extProdIds=333&extProdIds=345&isHideEmpty=true&isHideGenSupported=true&isHideTechSupported=true&). As you can see Postgres is only compatible with Horizon 2103.

![](/img/hzn2103-1.png)

* Once you know which version you want to install, head over to [www.postgresql.org ](https://www.postgresql.org/download/)and download it. In this example we are installing the Windows version.

![](/img/hzn2103-2.png)

* 