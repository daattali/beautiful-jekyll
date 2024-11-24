---
layout: post
title: Cisco Router as a DHCP Server
subtitle: A topic from CCNA.
#cover-img: /assets/img/Router_as_a_DHCP_Server_Diagram.png
#thumbnail-img: /assets/img/thumb.png
#share-img: /assets/img/path.jpg
tags: [blogs]
author: Baltej Giri
full-width: true
---

##### Preface
Hello fellow learners, I am writing this blog to document my understanding on DHCP server. DHCP servers can be setup in multiple ways, in this blog I am covering the details on how to setup DHCP server on a Cisco router. This blog has four parts, the first part is about an introduction. In the second part, I have designed a logical diagram of the network. The third part, the configuration on all network devices used in this lab. The last part is about verification, verification of configuration is important as it makes sure we're getting the anticipated results. 

# Introduction
## Cisco Router as a DHCP Server

A Cisco router or a Cisco switch can be used as a DHCP server. An enterprise can decide to configure DHCP server on a Cisco router or switch depending their infrastructure design. In this blog, a simple yet complex network design is used to demonstrate the concept of DHCP server on Cisco router. This network design consists of a router, multi-layer switch and two PCs. The complexity of this design is in the configuration of DHCP server using Cisco router concept.

This lab has more than just getting a DHCP server service configured on router. For example, router will have a routing protocol setup, switch will have VLANs, routing and DHCP forwarding service.

A routing protocol is required on both switch and router to route traffic between different networks. Switch needs DHCP forwarding enabled on each VLAN because PCs sends out DHCP Discover message when it starts up, and DHCP server responses with a DHCP Offer message. The client then selects a server and broadcasts a DHCP Request message. This process uses a broadcast message. A layer 3 switch does not forward broadcast packets that are designated to other devices.

There are some other protocols and features enabled in this lab i.e. cdp neighbor to view the neighbor device and interface from each other. One of my favorite feature i like to enable on all network devices is ```logging synchronous```. This feature keeps the input line of text in control otherwise network devices logs displaying on CLI can ghost your place in the line.

In the end I have sectioned the part of documentation to show the verification of working lab. Verification is important as it make us sure network device is doing what we have told it to do. Additionally, verification commands are also used to troubleshoot the issues. 

### Resources

- Packet Tracer
- Cisco ISR4321 Router
- Cisco 3650 Multi-layer Switch
- Two PCs
- Github pages to host this blog-post.
- Notepad++
- Markdown (.md) file format to write this blog-post

### IP Addresses
The table below shows the IP addresses used on router's and switch's interfaces.

<pre>
| Device | IP Address    | Interface           |
|--------|---------------|---------------------|
| Router | 10.1.1.254/24 | Interface gig0/0/0  |
| Router | 1.1.1.1/32    | Interface loopback0 |
| Switch | 10.1.10.1/24  | Interface vlan 10   |
| Switch | 10.1.20.1/24  | Interface vlan 20   |
| Switch | 10.1.1.1/24   | Interface vlan 1    |
</pre>

A routing configuration is required on both switch and router to route traffic between different networks. Switch needs DHCP request forwarding setup, a DHCP request messages are send by PC's, there messages are a broadcast messages by default layer 3 switches does not forward broadcast messages to routers thus we need to configure DHCP forwarding on switch.

The following bullet points are the overall point of view of how this lab should be configured.

1. Exclude first 10 IP addresses in each subnet from pool, Pool names = vlan10 and vlan20
2. Networks: 10.1.10.0/24 (vlan10) and 10.1.20.0/24 (vlan20)
3. Default Gateway: Switch1
4. DNS Server: Router1
5. Make sure PCs can ping each other and the loopback of Router1

The detailed ip address and vlans information is in the logical diagram of this lab.

# Design
The design is created using Microsoft Visio. The design is simple yet complex, it carries both layer 2 and layer 3 technologies of OSI model. Switch's virtual interface 1 is used as a default gateway which creates a need of IP DHCP helper and routing between different networks.
![Router_as_a_DHCP_Server_Diagram](https://baltejgiri.github.io/assets/img/Router_as_a_DHCP_Server_Diagram.png)

# Configuration
### Router

- IP address configuration on both interfaces ```gig0/0/0``` and ```loopback 0```.
	<pre>
		Router(config)#interface gig0/0/0
		Router(config-if)#ip address 10.1.1.254 255.255.255.0
		Router(config-if)#no shutdown
		Router(config-if)#exit
		Router(config)#interface loopback0
		Router(config-if)#ip address 1.1.1.1 255.255.255.255
		Router(config-if)#no shutdown
		Router(config-if)#end
	</pre>
- Configuring ip addresses exclude list for both subnets, subnet ```10.1.10.0/24``` and ```10.1.20.0/24```
	Router(config)#ip dhcp excluded-address 10.1.10.1 10.1.10.10
	Router(config)#ip dhcp excluded-address 10.1.20.1 10.1.20.10
- Creating ip dhcp pool name, pool names: vlan10 and vlan20 and assigning network address, default router and dns server addresses.
	<pre>
		Router(config)#ip dhcp pool vlan10
		Router(dhcp-config)#network 10.1.10.0 255.255.255.0
		Router(dhcp-config)#default-router 10.1.10.1
		Router(dhcp-config)#dns-server 10.1.1.254
		Router(dhcp-config)#exit
		Router(config)#ip dhcp pool vlan20
		Router(dhcp-config)#network 10.1.20.0 255.255.255.0
		Router(dhcp-config)#default-router 10.1.20.1
		Router(dhcp-config)#dns-server 10.1.1.254
	</pre>

- Creating a static route on router  using it's loopback ip address as network to point all incoming traffic from network 10.1.10.0/24.
	<pre>
		Router(config)#ip route 10.1.10.0 255.255.255.0 10.1.1.1
	</pre>

- Enable CDP on router to view the neighbor device and it's connected ports.
	<pre>
		Router(config)#cdp run
	</pre>

### Switch

- Creating vlans on switch and assigning ```interfaces gig1/0/2-3``` to respective vlans; vlan10 and vlan20
	<pre>
		Switch(config)#vlan 10
		Switch(config-vlan)#name vlan10
		Switch(config-vlan)#
		Switch(config-vlan)#vlan 20
		Switch(config-vlan)#name vlan20
		Switch(config-vlan)#exit
		Switch(config)#interface gig1/0/2
		Switch(config-if)#switchport mode access
		Switch(config-if)#switchport access vlan 10
		Switch(config-if)#interface gig1/0/3
		Switch(config-if)#switchport mode access
		Switch(config-if)#switchport access vlan 20
		Switch(config-if)#exit
	</pre>
- Creating switch virtual interface and assigning default gateway on switch.
	<pre>
		Switch(config)#interface vlan 1
		Switch(config-if)#ip address 10.1.1.1 255.255.255.0
		Switch(config-if)#no shutdown
		Switch(config-if)#exit
	</pre>
- Enable CDP on switch if it is not enabled already. CDP is used to view the neighbor device and it's connected ports.
	<pre>
		Switch(config)cdp run
	</pre>
- Enable routing on layer 3 switch so it can route packets between different networks.	
	<pre>
		Switch(config)ip routing
	</pre>
- Next, switch needs to have a static route configured for network ```1.1.1.1/32``` as we're currently unable to ping to the router's loopback address ```1.1.1.1/32```.
	<pre>
		Switch#ping 1.1.1.1

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 1.1.1.1, timeout is 2 seconds:
		.....
		Success rate is 0 percent (0/5)
	</pre>
- Configuring static route for network 1.1.1.1/32 on switch.
	<pre>
		Switch(config)#ip route 1.1.1.1 255.255.255.255 10.1.1.254
		!
		Switch#ping 1.1.1.1

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 1.1.1.1, timeout is 2 seconds:
		!!!!!
		Success rate is 100 percent (5/5), round-trip min/avg/max = 0/0/3 ms
	</pre>
- Switch will need to have DHCP request forwarding setup, In this diagram, PC's will send a broadcast message with DHCP request. By default, layer 3 switch does not forward broadcast messages to the router as it can casue network issues thus switch needs to configured with DHCP request forwarding.
	<pre>
		Switch(config)#interface vlan 10
		Switch(config-if)#ip helper-address 10.1.1.254
		Switch(config-if)#exit
		Switch(config)#interface vlan 20
		Switch(config-if)#ip helper-address 10.1.1.254
		Switch(config-if)#exit
	</pre>

This completes the configuration on router and switch. The PC1 and PC2 needs to have network interface card (NIC) configured to use the ip address from DHCP instead Static. If the lap is done in simulator or emulators then you may need to configure these settings otherwise the actual computers does have DHCP enabled on their NICs.

Next section shows the verification of routing, cdp neighbors, ip addresses verification, and ping connectivity on router, switch and pc's.

# Verification
The verification of working configuration and protocol can be tested on a router, switch or PCs.
### Router
- We can see both switch and router are learning static routes.
	<pre>
			Router#show ip route static 
			 10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
		S       10.1.10.0/24 [1/0] via 10.1.1.1
		S       10.1.20.0/24 [1/0] via 10.1.1.1
	</pre>
- CDP neighbor command shows us, sw-1 is connected to rtr-1's local interface gig0/0/0 and it shows switch's (sw-1) port id is gig1/0/1
	<pre>
		Router#show cdp neighbors 
		Capability Codes: R - Router, T - Trans Bridge, B - Source Route Bridge
                  S - Switch, H - Host, I - IGMP, r - Repeater, P - Phone
		Device ID    Local Intrfce   Holdtme    Capability   Platform    Port ID
		Switch         Gig 0/0/0        148                    3650        Gig 1/0/1
	</pre>
- We can see router (rtr-1) received DHCP messages to assign an IP address for pc-1.
	<pre>
		Router#debug ip packet
		Packet debugging is on
		!
		IP: tableid=0, s=10.1.10.1 (GigabitEthernet0/0/0), d=10.1.1.254 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.10.1 (GigabitEthernet0/0/0), d=10.1.1.254 (GigabitEthernet0/0/0), len 77, rcvd 3

		IP: tableid=0, s=10.1.1.254 (local), d=10.1.10.11 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.1.254 (local), d=10.1.10.11 (GigabitEthernet0/0/0), len 128, sending

		Router#
		IP: tableid=0, s=10.1.1.254 (local), d=10.1.10.11 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.1.254 (local), d=10.1.10.11 (GigabitEthernet0/0/0), len 128, sending

		Router#
		IP: tableid=0, s=10.1.1.254 (GigabitEthernet0/0/0), d=10.1.10.1 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.1.254 (local), d=10.1.10.1 (GigabitEthernet0/0/0), len 66, sending

		IP: tableid=0, s=10.1.10.1 (GigabitEthernet0/0/0), d=10.1.1.254 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.10.1 (GigabitEthernet0/0/0), d=10.1.1.254 (GigabitEthernet0/0/0), len 77, rcvd 3

		IP: tableid=0, s=10.1.1.254 (GigabitEthernet0/0/0), d=10.1.10.1 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.1.254 (local), d=10.1.10.1 (GigabitEthernet0/0/0), len 66, sending

		Router#un all
		All possible debugging has been turned off
	</pre>
- DHCP Binding can be seen from DHCP enabled router, it lists all ip addresses assigned to devices via DHCP.
	<pre>
		Router#ping 10.1.10.11

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 10.1.10.11, timeout is 2 seconds:
		!!!!!
		Success rate is 100 percent (5/5), round-trip min/avg/max = 0/0/0 ms

		Router#
		Router#ping 10.1.20.11

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 10.1.20.11, timeout is 2 seconds:
		!!!!!
		Success rate is 100 percent (5/5), round-trip min/avg/max = 0/0/0 ms

		Router#show ip dhcp binding 
		IP address       Client-ID/              Lease expiration        Type
						Hardware address
		10.1.10.11       0001.C9E3.8437           --                     Automatic
		10.1.20.11       0000.0C59.952A           --                     Automatic
	</pre>

- DHCP pool can also be seen from DHCP enabled router.
	<pre>
		Router#show ip dhcp pool 

		Pool vlan10 :
		Utilization mark (high/low)    : 100 / 0
		Subnet size (first/next)       : 0 / 0 
		Total addresses                : 254
		Leased addresses               : 1
		Excluded addresses             : 2
		Pending event                  : none

		1 subnet is currently in the pool
		Current index        IP address range                    Leased/Excluded/Total
		10.1.10.1            10.1.10.1        - 10.1.10.254       1    / 2     / 254

		Pool vlan20 :
		Utilization mark (high/low)    : 100 / 0
		Subnet size (first/next)       : 0 / 0 
		Total addresses                : 254
		Leased addresses               : 1
		Excluded addresses             : 2
		Pending event                  : none

		1 subnet is currently in the pool
		Current index        IP address range                    Leased/Excluded/Total
		10.1.20.1            10.1.20.1        - 10.1.20.254       1    / 2     / 254
	</pre>
- Now we can verify ip addresses on both PC 1 and PC 2 as well as a ping test from one pc to another.
	- PC 1 received IPv4 address of 10.1.10.11 with subnet mask 255.255.255.0 and default gateway address 10.1.10.1 from the DHCP server, from router (rtr-1) in this case.
		<pre>
			C:\>ipconfig
			FastEthernet0 Connection:(default port)
			Connection-specific DNS Suffix..: 
			Link-local IPv6 Address.........: FE80::201:C9FF:FEE3:8437
			IPv6 Address....................: ::
			IPv4 Address....................: 10.1.10.11
			Subnet Mask.....................: 255.255.255.0
			Default Gateway.................: ::10.1.10.1
		</pre>
	- PC 2 received IPv4 address of 10.1.20.11 with subnet mask 255.255.255.0 and default gateway address 10.1.20.1 from the DHCP server from router (rtr-1) similar to PC1.
		<pre>
			C:\>ipconfig
			FastEthernet0 Connection:(default port)
			Connection-specific DNS Suffix..: 
			Link-local IPv6 Address.........: FE80::200:CFF:FE59:952A
			IPv6 Address....................: ::
			IPv4 Address....................: 10.1.20.11
			Subnet Mask.....................: 255.255.255.0
			Default Gateway.................: ::10.1.20.1
		</pre>
	- Ping test from PC 1 to PC 2 and PC 2 to PC1.
	- PC 1 can ping to PC 2 successfully.
		<pre>
			C:\>ping 10.1.20.11			
			Reply from 10.1.20.11: bytes=32 time<1ms TTL=127
			Reply from 10.1.20.11: bytes=32 time<1ms TTL=127
			Reply from 10.1.20.11: bytes=32 time<1ms TTL=127
			Reply from 10.1.20.11: bytes=32 time<1ms TTL=127
				
			Ping statistics for 10.1.20.11:
			Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),
			Approximate round trip times in milli-seconds:
			Minimum = 0ms, Maximum = 0ms, Average = 0ms
		</pre>
	- PC2 can also ping to PC 2, these ping tests proves out that the routing is working between both networks.
		<pre>
			C:\>ping 10.1.10.11
			Pinging 10.1.10.11 with 32 bytes of data:
			Reply from 10.1.10.11: bytes=32 time<1ms TTL=127
			Reply from 10.1.10.11: bytes=32 time<1ms TTL=127
			Reply from 10.1.10.11: bytes=32 time<1ms TTL=127
			Reply from 10.1.10.11: bytes=32 time<1ms TTL=127
			Ping statistics for 10.1.10.11:
	
		    	Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),
			Approximate round trip times in milli-seconds:
		    	Minimum = 0ms, Maximum = 0ms, Average = 0ms
		</pre>
### Switch
- Switch has static route 1.1.1.1 learnt by 10.1.1.254.
	<pre>
		Switch#show ip route static 
		 1.0.0.0/32 is subnetted, 1 subnets
		S       1.1.1.1 [1/0] via 10.1.1.254
	</pre>
- Switch is learning Device ID of Router on it's local interface gigabit 1/0/1, and displaying router's port ID is gigabit 0/0/0.
	<pre>
		Switch#show cdp neighbors 
		Capability Codes: R - Router, T - Trans Bridge, B - Source Route Bridge
					S - Switch, H - Host, I - IGMP, r - Repeater, P - Phone
		Device ID    Local Intrfce   Holdtme    Capability   Platform    Port ID
		Router       Gig 1/0/1        139            R       ISR4300     Gig 0/0/0
	</pre>
- Vlan configuration and 
	<pre>
		Switch#show vlan brief 

		VLAN Name                             Status    Ports
		---- -------------------------------- --------- -------------------------------
		1    default                          active    Gig1/0/1, Gig1/0/4, Gig1/0/5, Gig1/0/6
														Gig1/0/7, Gig1/0/8, Gig1/0/9, Gig1/0/10
														Gig1/0/11, Gig1/0/12, Gig1/0/13, Gig1/0/14
														Gig1/0/15, Gig1/0/16, Gig1/0/17, Gig1/0/18
														Gig1/0/19, Gig1/0/20, Gig1/0/21, Gig1/0/22
														Gig1/0/23, Gig1/0/24, Gig1/1/1, Gig1/1/2
														Gig1/1/3, Gig1/1/4
		10   vlan10                           active    Gig1/0/2
		20   vlan20                           active    Gig1/0/3
		1002 fddi-default                     active    
		1003 token-ring-default               active    
		1004 fddinet-default                  active    
		1005 trnet-default                    active
	</pre>

	<pre>
		Switch#show ip interface br
		Interface              IP-Address      OK? Method Status                Protocol 
		GigabitEthernet1/0/1   unassigned      YES unset  up                    up 
		GigabitEthernet1/0/2   unassigned      YES unset  up                    up 
		GigabitEthernet1/0/3   unassigned      YES unset  up                    up 
		GigabitEthernet1/0/4   unassigned      YES unset  down                  down 
		GigabitEthernet1/0/5   unassigned      YES unset  down                  down 
		GigabitEthernet1/0/6   unassigned      YES unset  down                  down 
		GigabitEthernet1/0/7   unassigned      YES unset  down                  down 
		GigabitEthernet1/0/8   unassigned      YES unset  down                  down 
		GigabitEthernet1/0/9   unassigned      YES unset  down                  down 
		GigabitEthernet1/0/10  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/11  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/12  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/13  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/14  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/15  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/16  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/17  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/18  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/19  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/20  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/21  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/22  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/23  unassigned      YES unset  down                  down 
		GigabitEthernet1/0/24  unassigned      YES unset  down                  down 
		GigabitEthernet1/1/1   unassigned      YES unset  down                  down 
		GigabitEthernet1/1/2   unassigned      YES unset  down                  down 
		GigabitEthernet1/1/3   unassigned      YES unset  down                  down 
		GigabitEthernet1/1/4   unassigned      YES unset  down                  down 
		Vlan1                  10.1.1.1        YES manual up                    up 
		Vlan10                 10.1.10.1       YES manual up                    up 
		Vlan20                 10.1.20.1       YES manual up                    up
	</pre>
- Connectivity to all networks
	<pre>
		Switch#ping 1.1.1.1

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 1.1.1.1, timeout is 2 seconds:
		!!!!!
		Success rate is 100 percent (5/5), round-trip min/avg/max = 0/0/0 ms

		Switch#ping 10.1.1.254

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 10.1.1.254, timeout is 2 seconds:
		!!!!!
		Success rate is 100 percent (5/5), round-trip min/avg/max = 0/0/0 ms

		Switch#ping 10.1.10.11

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 10.1.10.11, timeout is 2 seconds:
		.!!!!
		Success rate is 80 percent (4/5), round-trip min/avg/max = 0/0/0 ms

		Switch#ping 10.1.20.11

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 10.1.20.11, timeout is 2 seconds:
		.!!!!
		Success rate is 80 percent (4/5), round-trip min/avg/max = 0/4/18 ms
	</pre>
This ends the lab on DHCP configuration on a Cisco Router. Thank you for checking out this blog. 
