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

Do consider that if you are moving from a SQL server or Oracle DB, you will lose all past events. Unless you manage to migrate all the records to Postgres but I can't help you with that :).

## Installation and configuration of PostgreSQL

Although it is not embedded in the installer like vCenter's vPostgres database, you will find that getting started with PostgreSQL is a lot easier than even Microsoft SQL Express.

In this blog I am installing the database directly on the Connection Server as it is a lab with a single instance. Make sure to install it on a third part server if you run multiple Connection Servers.

### Postgres Installation

* First, check for database compatibility in the new [VMware interoperability matrix](https://interopmatrix.vmware.com/#/Database?productId=569&extProdIds=326&extProdIds=333&extProdIds=345&isHideEmpty=true&isHideGenSupported=true&isHideTechSupported=true&). As you can see Postgres is only compatible with Horizon 2103.

![](/img/hzn2103-1.png)

* Once you know which version you want to install, head over to [www.postgresql.org ](https://www.postgresql.org/download/)and download it. In this example we are installing the Windows version. I chose version 12.x for no particular reason.

![](/img/hzn2103-2.png)

* You can then go ahead and launch the Postgres installer on the database server and click **Next**.

![](/img/hzn2103-3.png)

* Set an **installation directory** or leave it as default.

![](/img/hzn2103-4.png)

* You can leave the next window as default with all the components as it doesn't take up much space.

![](/img/hzn2103-5.png)

* Set a different **Data directory** if you don't want to leave it in the installation folder. I left it as default for the purpose of this demonstration.

![](/img/hzn2103-6.png)

* In the next pane you need to set a **password** for the **postgres user** that we will use later on to connect Horizon to it.

![](/img/hzn2103-7.png)

* You can set a TCP port or leave the **default 5432** if it doesn't suit you for some reason. Just make sure that the Connection Servers have TCP access to the database server on said port.

![](/img/hzn2103-8.png)

* Leave the **Default Locale** and click **Next**.

![](/img/hzn2103-9.png)

* Last but not least, click **Finish**...

![](/img/hzn2103-10.png)

### Postgres Configuration

The configuration of PostgreSQL is straightforward as you can see.

* Browse to the Postgres **Data folder**, by default in "_C:\\Program Files\\PostgreSQL\\XX\\data_" and edit "**pg_hba.conf**" which si the file that controls Client authentication.

![](/img/hzn2103-11.png)

* Find the "**IPV 4 local connections**" sections and add your **Horizon Connection Servers** below.

Note that you can either enter the IPs one by one with a /32 netmask or specify a range like "_192.168.1.0/24_". Try and keep it as close to the Connection Servers' IP addresses as possible for security's sake.

![](/img/hzn2103-12.png)

* Then restart the **postgres service**. If the service doesn't start it means you made a mistake in pg_hba.conf such as forgotten mask (yes I did it, so what?).

![](/img/hzn2103-13.png)

## Configuration in the Horizon console

Now that the database is ready, we can log on the Horizon console and make the change. Let me remind you that all past events will be lost unless you somehow manage to migrate the records from the previous database to Postgres.

* Head over to **Settings** > **Event Configuration** > **Event Database** and click **Edit**.

![](/img/hzn2103-14.png)

* Change the **Database Type** to **PostgreSQL**, set the **port** if you changed it, type **postgres** in the **Database Name** and **User Name** fields, type the **password** you entered during the installation and choose a **prefix** for the table, "_hz__" is as good as any. Then click **OK**.

![](/img/hzn2103-15.png)

* If everything is configured correctly you should now find the Database Configuration pane updated.

![](/img/hzn2103-16.png)