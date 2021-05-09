---
title: Ansible 2.5 and network_cli
layout: post
tags: [ansible, automation]
readtime: true
before-content: old-post-warn.html
---
Red Hat recently released version 2.5 of Ansible Core, and with it comes a significant change to the connection method for Network devices, by way of the `network_cli` connection type. Up until now, Ansible playbooks used for managing Network devices utilised the connection type `local`, which required the creation of a _provider_. The provider is essentially a collection of authentication information that’s referenced in every task. Providers are unique to network modules, and create a framework to pass credentials to the managed device.

For example, a simple playbook to gather facts from a network device and output to the terminal, **prior to version 2.5**:

```yaml
---
- hosts: routers
  connection: local

  vars:
    cli:
      username: cisco
      password: cisco
      authorize: yes
      auth_pass: cisco

  tasks:

  - name: Gather facts
    ios_facts:
      provider: ""
    register: result

  - debug: var=result 
```

The provider must be included in each task, and this process differs from typical Ansible playbooks used to manage Linux hosts. With the new `network_cli` connection method, the playbook is streamlined by referencing global parameters. The `network_cli` connection method _does_ require that you define what type of network operating system is being managed, in order to load the appropriate module, which is defined using the `ansible_network_os` parameter, or passed through the command-lne. We can also extract some of the authentication parameters, such as the SSH username password, to our command-line run of `ansible-playbook`.

A refactor of the same playbook with the `network_cli` connection method would look something like this:

```yaml
---
- hosts: routers
  connection: network_cli
  become: yes
  become_method: enable

  tasks:

  - name: Gather facts
    ios_facts:
    register: result

  - debug: var=result
```

Which would run using the following:

```
$ ansible-playbook -u cisco -k -e ansible_network_os=ios playbook.yml
```

But this playbook can be further refactored by including the connection type, `become`, `become_method`, and `ansible_network_os` as variables in the inventory file. These variables can be applied globally, through the `[all:vars]`, or to a subset of devices by using the child variables.

A sample inventory file, `hosts.ini` would look something like this:

```ini
[all:vars]
ansible_connection=network_cli

[routers]
CSR1000v_1 ansible_host=172.16.201.132

[routers:vars]
ansible_network_os=ios
ansible_become=yes
ansible_become_method=enable
```

Therefore, leaving the playbook itself to be condensed to only a few lines:

```yaml
---
- hosts: routers

  tasks:

  - name: Gather facts
    ios_facts:
    register: result

  - debug: var=result
```

Which can be run with the following:

```
$ ansible-playbook -u cisco -k playbook.yml
```

As you can see, the `network_cli` connection type in Ansible 2.5 allows you to optimise your playbooks when managing network devices.

The playbooks accompanying this blog post are available on [GitHub](https://github.com/MrThePlague/network_cli_demo).