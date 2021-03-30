---
layout: post
title: "Using Ansible 2.9 Resource Modules"
tags: [automation, ansible]
readtime: true
before-content: old-post-warn.html
---

Red Hat recently updated Ansible to version 2.9, and with it comes [a number of exciting new features](https://www.ansible.com/blog/network-features-coming-soon-in-ansible-engine-2.9) for enthusiasts of network automation. One such update is an enhancement to the way that Ansible retrieves and normalises facts for network devices, and allows you to idempotently pass those values back to the device.

Since network automation with Ansible first began to take take shape, the typical fact gathering process used with other types of automation has lacked maturity. Once facts were gathered, there was no consistent way of being able use leverage them across platforms without translation and modification. Platform-specific `<nios>_facts` modules were required for each operating system, and once the facts were gathered it wasn't straightforward to _do_ anything with them. The return data of a particular fact wasn't necessarily the same data or in the same format required to _put_ the configuration to the device. Ansible 2.9 begins to solve that by enhancing the way that facts are gathered by normalising the return into a standardised structured data model of key-value pairs for a given subset of configuration details.

## Disorganised Data

Gathering network device details can be done with a simple playbook, such as the following: 

```yaml
- name: Gather facts from IOS devices
  hosts: all

  tasks:

    - name: Gather facts for IOS devices
      ios_facts:
        gather_subset:
          - '!config'
      register: output

    - name: Output facts to file
      copy: content="{{ output | to_nice_yaml }}" dest="{{ansible_net_hostname}}_facts.yaml"
```

This playbook will write the gathered facts to a file, formatted as YAML.

Here is an example of a subset of interface facts pulled by the `ios_facts` module in Ansible <2.9:

```yaml
ansible_net_interfaces:
        GigabitEthernet0/0:
            bandwidth: 1000000
            description: OOB Management
            duplex: Full
            ipv4:
            -   address: 10.4.10.205
                subnet: '24'
            lineprotocol: up
            macaddress: 5e00.0000.0000
            mediatype: RJ45
            mtu: 1500
            operstatus: up
            type: iGbE
        GigabitEthernet0/1:
            bandwidth: 1000000
            description: "Interface description"
            duplex: Full
            ipv4:
            -   address: 10.0.0.5
                subnet: '30'
            lineprotocol: up
            macaddress: fa16.3e22.0c07
            mediatype: RJ45
            mtu: 1500
            operstatus: up
            type: iGbE
```

The retrieved facts include a large amount of interface configuration details, such as interface state, duplex settings, MAC address, etc. Notice, in the gathered facts, the interface configuration is expressed as a dictionary, with the IPv4 configuration expressed as a list within, also defining separate `address` and `subnet` values. However, if you would like to set the layer 3 interface addressing of this specific interface, the `ios_l3_interface` module expects a different set of inputs, in a different format to what is retrieved by the facts module, e.g.:

```yaml
- name: This task would set the layer3 interface IPv4 address
  ios_l3_interface:
    name: GigabitEthernet0/1
    ipv4: 10.0.0.5/30
```

When the values are set with the `ios_l3_interface` module, it expects an individual _key:value_ pair defining the interface name, and an IPv4 address in the CIDR format. Because these inputs and outputs aren't normalised, it becomes very challenging to establish an off-box source of truth for your device configuration. Furthermore, if you'd like to set the other values such as the MTU or operational state, a different network module is required, which suffers from the same non-standard data model.

Additionally, if you'd like to set more than one interface configuration using the same task, a loop is required to iterate over either or list or dictionary of interfaces and values, e.g.:

```yaml
vars:
  interfaces:
    GigabitEthernet0/0:
      ipv4: 10.4.10.205/24
    GigabitEthernet0/1:
      ipv4: 10.0.0.5/30

tasks:
  - name: Configure multiple interfaces
    ios_l3_interface:
      name: "{{ item.key }}"
      ipv4: "{{ item.value.ipv4 }}"
    with_dict: "{{ interfaces }}"
```

## Moving Forward

Starting in Ansible 2.9, a wide array of network modules are being re-written and/or replaced with modules that follow a more standardised data model. Furthermore, any new network modules will be required to include the corresponding `facts` processing within the `<nios>_facts` module! This means we'll have a consistent way of being able to retrieve and set configuration data to a network device. Let's take another look at the previous example of gathering and setting the layer3 interface configuration of a Cisco router.

Ansible 2.9 added an additional parameter to the `ios_facts` module, `gather_network_resources`, which accepts a number of different subsets, such as `l3_interfaces`. The above playbook can be edited to gather the network resources by adding this parameter:

```yaml
- name: Gather facts from IOS devices
  hosts: all

  tasks:

    - name: Gather facts for IOS devices
      ios_facts:
        gather_subset:
          - '!config'
        gather_network_resources:
          - 'l3_interfaces'
      register: output

    - name: Output facts to file
      copy: content="{{ output | to_nice_yaml }}" dest="{{ansible_net_hostname}}_facts.yaml"
```

Now, we have an additional group of facts within our output YAML file called `ansible_network_resources`, and within this section is a list called `l3_interfaces` outlining all of the layer3-specific interface configurations:

```yaml
ansible_network_resources:
        l3_interfaces:
        -   ipv4:
            -   address: 10.4.10.205 255.255.255.0
            name: GigabitEthernet0/0
        -   ipv4:
            -   address: 10.0.0.5 255.255.255.252
            name: GigabitEthernet0/1
```

Augmenting this change is a brand new layer3 interface configuration module, `ios_l3_interfaces`. If we look at an example of the way the interface configurations are set within this new module, you can start to see the alignment:

```yaml
- name: Perform the same configuration layer3 interface configuration
  ios_l3_interfaces:
    config:
      - ipv4:
        - address: 10.0.0.5 255.255.255.252
        name: GigabitEthernet0/1
```

As you can see, the input configuration data, and the output facts are now in the same format! This opens up significant possibilities as it pertains to establishing an off-device source of truth, i.e.: defining your device's configuration in a standardised data model made up of _key:value_ pairs.

An additional benefit of the new network modules is the ability to take a list as an input, meaning you can pass the configuration of multiple interfaces within the same task, e.g.:

```yaml
vars:
    l3_interfaces:
      - ipv4:
        - address: 10.4.10.205 255.255.255.0
        name: GigabitEthernet0/0
      - ipv4:
        - address: 10.0.0.5 255.255.255.252
        name: GigabitEthernet0/1

tasks:
  - name: Replaces device configuration of listed interfaces with provided configuration
    ios_l3_interfaces:
      config: "{{ l3_interfaces }}"
```

All that's required to configure multiple interfaces is to pass the correctly the correctly formatted list, which could be stored in a variable file such as the device's corresponding `host_vars` file.

## Conclusion

Ansible 2.9 significantly matures the ability for network automators to leverage the tool at scale, by beginning to develop a standardised data model for the retrieval, storage, and execution of network configuration.

New network modules are being written to align with this strategy, so at this time only a few subsets of configuration parameters are available, such as the Cisco IOS modules below; however, more will be debuted in upcoming releases:

```yaml
ios_interfaces
ios_l2_interfaces
ios_l3_interfaces
ios_lacp
ios_lacp_interfaces
ios_lag_interfaces
ios_lldp_global
ios_lldp_interfaces
ios_vlans
```

A final note is that my experiences with these modules in their current state has been mixed, so far. While this new strategy offers significant promise, the new network modules are still very young, and therefore a little _rough around the edges_, so your mileage may vary with Ansible _2.9.0_.