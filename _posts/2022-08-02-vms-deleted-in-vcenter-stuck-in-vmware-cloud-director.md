---
layout: post
title: VMs deleted in vCenter stuck in VMware Cloud Director
description: You may be stuck with stale record in VCD if you deleted VMs from vCenter that are managed by Cloud Director. Find out how to clean these up.
date: 2022-08-02T09:51:10.376Z
nobanner: no
fb-img: null
---

While playing a bit roughly in my homelab, I deleted a couple VMs from vCenter that were originally created and managed by VMware Cloud Director because I didn't have time to start NSX-T, ALB, VCD... The problem is that after doing this, the VMs were still in VMware Cloud Director and the vAPP was stuck in powered on state. I couldn't power it off so I couldn't remove the VMs either.

![power off vAPP impossible](/img/2022-08-02-11-55-09.png)

``` text
The entity xav is in an invalid state for operation powerof. - com.vmware.ssdc.library.exceptions.MultipleLMException: One or more exceptions have occurred - Multiple Exceptions follow: [java.util.concurrent......
```

After trying a few things it turns out that the only way to clean this up is to remove the records from the postgres database in VMware Cloud Director.

_**I shall point out that I only used this workaround in a simple lab environment and is in no way supported by VMware so run tests and use this at your own risks.**_

* Connect to VCD using ssh

* Enter the postgresql database

``` bash
su postgres
psql
```

* you can list the databases to double check, you are looking for `vcloud`.

```
postgres-# \l
                             List of databases
   Name    |  Owner   | Encoding | Collate | Ctype |   Access privileges
-----------+----------+----------+---------+-------+-----------------------
 postgres  | postgres | UTF8     | C       | C     |
 repmgr    | repmgr   | UTF8     | C       | C     |
 template0 | postgres | UTF8     | C       | C     | =c/postgres          +
           |          |          |         |       | postgres=CTc/postgres
 template1 | postgres | UTF8     | C       | C     | =c/postgres          +
           |          |          |         |       | postgres=CTc/postgres
 vcloud    | vcloud   | UTF8     | C       | C     |
(5 rows)

```

* Connect the `vcloud` database

``` text
\c vcloud
You are now connected to database "vcloud" as user "postgres".
```

* You can list the tables to see how it's structured or if you're looking for something else than our current use case.

``` text
\dt;
                      List of relations
 Schema |               Name                | Type  | Owner
--------+-----------------------------------+-------+--------
 public | acl                               | table | vcloud
 public | acl_defined_entity                | table | vcloud
 public | acl_defined_entity_definition     | table | vcloud
 public | acl_general                       | table | vcloud
```

* Grab the name of the VM you want to remove in its settings in VCD or its name in vSphere.

![vsphere vm name in vmware cloud director](/img/2022-08-02-12-02-08.png)

* If you try to delete the VM now in psql, you will get an error sayint it is id is still referenced in another table as a key.

``` text
delete from vm where name like 'xav-md0-5fb4ff79fb-kbtp2-GIKU';
ERROR:  update or delete on table "vm" violates foreign key constraint "virtualserverdeployedvirtualse" on table "deployed_vm"
DETAIL:  Key (id)=(dc7f1f04-402e-4d59-bb91-a76a03d3cbf0) is still referenced from table "deployed_vm".
```

* List the table that was mentioned and you should find the ID somewhere in there.

``` text
select * from deployed_vm;
             instance_id              |                vm_id                 |      date_deployed
--------------------------------------+--------------------------------------+-------------------------
 49c74a63-5375-4645-a3dd-abecf9cc4acd | 31564d96-98c7-4504-a7a0-2cbe836fa1a1 | 2022-06-17 15:58:08.228
 34bd332a-36af-4691-8e95-db6f67dde178 | dc7f1f04-402e-4d59-bb91-a76a03d3cbf0 | 2022-06-17 16:01:52.237
(2 rows)
```

* Delete the record from the table.

``` text
delete from deployed_vm where vm_id = dc7f1f04-402e-4d59-bb91-a76a03d3cbf0;
DELETE 1
```

* You should now be able to remove the VM and not get an error.

``` text
delete from vm where name like 'xav-md0-5fb4ff79fb-kbtp2-GIKU';
DELETE 1
```

* The VM will be in `Unknown` state in VMware Cloud Director and you can delete it from there.

![vm unknown cloud director](/img/2022-08-02-12-05-49.png)

* After you remove all the VMs from the vAPP, you should be able to switch it off and delete it.

![power off vapp vcd](/img/2022-08-02-12-06-26.png)

![delete vapp vcd](/img/2022-08-02-12-06-40.png)