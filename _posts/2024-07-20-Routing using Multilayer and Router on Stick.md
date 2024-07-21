---
layout: page
title: Documentation
subtitle: CCNA Notes
---
layout: post
title: Routing using Multilayer and Router on Stick.
# subtitle: Where am i in my career and learning..
# cover-img: assets/img/where_am_i.jpg
# thumbnail-img: /assets/img/thumb.png
# share-img: /assets/img/path.jpg
tags: [documents]
author: Baltej Giri
---
---

## LAB Configuration for inter-vlan routing using ROAS, SVI and Routed Ports

### Multi-layer Switch Configuration 
Mutlilayer Switch configuration with Switch Virtual Interface for VLAN 10 and 11.

- Switch's hostname is set to multilayer-sw1.
- Interfaces Gig1/2-3 and Gi0/2-3 are configured with access port on vlan 10 and vlan 11 respectively.
- All access port's are set with port security mode to restric and age timmer with 5 minute along with portfast.
- To prevent log messages to interpt from CLI enteries, logging synchronous is set.
- SVI's are created for VLAN 10 and 11 and assigned with ip address.
- Switch's interface Gig0/0 is set to routed port which connects to Router as a point to point link.
- Static Route is set to forward traffic destined for networks outside of Local Area Network.
- IP addresses and port status are verified at last.
- Connectivity between both VLANs is tested using ping command from a endpoint to another of each vlan.
- Configuration is saved on multilayer switch at last.
```
enable
configure terminal
no banner exec
no banner incoming
no banner login
!
hostname multilayer-sw1
ip routing
!
line con 0
logging synchronous
exit
!
interface range g1/2-3
 switchport access vlan 10
 switchport mode access
 switchport port-security violation restrict
 switchport port-security aging time 5
 spanning-tree portfast
 !
interface range g0/2-3
 switchport access vlan 11
 switchport mode access
 switchport port-security violation restrict
 switchport port-security aging time 5
 spanning-tree portfast
 !
!
interface vlan 10
ip address 192.168.10.254 255.255.255.0
no shutdown
!
exit
interface vlan 11
ip address 192.168.11.254 255.255.255.0
no shutdown
!
interface gig0/0
 description link_to_router's_g0/0
 no switchport
 ip address 200.10.50.1 255.255.255.252
 no shutdown
 !
ip route 192.168.12.0 255.255.255.0 200.10.50.2
ip route 192.168.13.0 255.255.255.0 200.10.50.2
 !
 end
 show ip interface brief
 !
 show interface status
 !
copy running-config startup-config

```
### Router Configuration
Router's Gi0/0 port is configured as a point-to-point link with Multi-layer switch and interface Gi0/1 and sub-interfaces Gi0/1.12 and Gi0/1.13 for router on stick.

```
enable
configure terminal
no banner exec
no banner incoming
no banner login
!
hostname router-1
!
line con 0
logging synchronous
exit
interface gig0/0
 description link_to_multilayer-sw1's_g0/0
 ip address 200.10.50.2 255.255.255.252
 no shutdown
 !
interface gig0/1
 description link_to_layer2-sw1's_g0/0
 no shutdown
 interface gig0/1.12
 encapsulation dot1Q 12
 ip address 192.168.12.254 255.255.255.0
 no shutdown
 interface gig0/1.13
 encapsulation dot1Q 13
 ip address 192.168.13.254 255.255.255.0
 no shutdown
!
exit
!
ip route 192.168.10.0 255.255.255.0 200.10.50.1
ip route 192.168.11.0 255.255.255.0 200.10.50.1
end
!
show ip int brief
!
show running-config
!
copy running-config startup-config
```

### Layer 2 Switch configuration
Layer 2 switch is configutred with two vlan's 12 and 13, it's gig0/0 port will be a trunk port with vlans 12,13 allowed along with native vlan 1.

```
enable
configure terminal
no banner exec
no banner incoming
no banner login
!
hostname layer-2-sw1
!
line con 0
logging synchronous
exit
!
interface gig0/3
 switchport access vlan 12
 switchport mode access
 switchport port-security violation restrict
 switchport port-security aging time 5
 spanning-tree portfast
interface gig1/3
 switchport access vlan 13
 switchport mode access
 switchport port-security violation restrict
 switchport port-security aging time 5
 spanning-tree portfast
interface gig0/0
description link_to_router-1's_g0/1
switchport trunk encapsulation dot1q
switchport mode trunk
switchport trunk allowed vlan 12
switchport trunk allowed vlan add 13
switchport trunk native vlan 1
!
end
!
show vlan brief
!
show interface trunk
!
show interface status
!

```
