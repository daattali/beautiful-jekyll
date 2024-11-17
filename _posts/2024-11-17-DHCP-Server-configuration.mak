---
layout: post
title: DHCP Server Configuration
subtitle: A topic from CCNA.
#cover-img: /assets/img/trubleshooting.jpg
#thumbnail-img: /assets/img/thumb.png
#share-img: /assets/img/path.jpg
tags: [blogs]
author: Baltej Giri
---

DHCP SERVER LAB
-----------------
Configuring DHCP on router and switch while using vlans can be tricky but it is a common practive if an enterprise choose to use the DHCP server funtion either on cisco router or Cisco's layer 3 swithes.

The following instructions are required to configure the DHCP Server Lab on a Cisco Router, this lab include the setup of; ip address exclude list on each vlan and setting switch as the default gateway for each vlan but dns server as router. At last we need to verify the connectivity from PC 1 to PC 2.

There are some additional protocols setup. A routing configuration is required on both switch and router to route traffic between different netoworks. Switch needs DHCP request forwarding setup, a DHCP request messages are send by PC's, there messages are a broadcast messages by default layer 3 switches does not forward boradcast messages to routers thus we need to confiure DHCP forwarding on switch.

The following bullet points are the overall point of view of how this lab should be configured.
1. Exclude first 10 IP addresses in each subnet from pool, Pool names = vlan10 and vlan20
2. Networks: 10.1.10.0/24 (vlan10) and 10.1.20.0/24 (vlan20)
3. Default Gateway: Switch1
4. DNS Server: Router1
5. Make sure PCs can ping each other and the loopback of Router1

The detailed ip address and vlans information is in the logical diagram of this lab.

## Configuration
### Router1

- IP address configuration on both interfaces <code>gig0/0/0</code> and <code>loopback 0</code>.
	<pre>
	interface gig0/0/0
	 ip address 10.1.1.254 255.255.255.0
	 no shutdown
	!
	interface loopback0
	 ip address 1.1.1.1 255.255.255.255
	 no shutdown
	!
	</pre>
- Configuring ip addresses exclude list for both subnets, subnet 10.1.10.0/24 and 10.1.20.0/24
	ip dhcp excluded-address 10.1.10.1 10.1.10.10
	ip dhcp excluded-address 10.1.20.1 10.1.20.10
- Creating ip dhcp pool name, pool names: "vlan10" and "vlan20" and assigning network address, default router and dns server addresses.
	<pre>
	ip dhcp pool vlan10
	 network 10.1.10.0 255.255.255.0
	 default-router 10.1.10.1
	 dns-server 10.1.1.254
	!
	ip dhcp pool vlan20
	 network 10.1.20.0 255.255.255.0
	 default-router 10.1.20.1
	 dns-server 10.1.1.254
	</pre>

- Creating a static route on router 1 using i'ts loopback ip address as network to point all incoming traffic from network 10.1.10.0/24.
	<pre>
	ip route 10.1.10.0 255.255.255.0 10.1.1.1
	</pre>

- Enable CDP on switch to view the neighbor device and it's connected ports.
	<pre>
	cdp run
	</pre>

### Switch 1

- Creating vlans on switch and assigning interfaces gig1/0/2-3 to respective vlans; vlan10 and vlan20
	<pre>
	vlan 10
	name vlan10
	!
	vlan 20
	name vlan20
	!
	interface gig1/0/2
	switchport mode access
	switchport access vlan 10
	!
	interface gig1/0/3
	switchport mode access
	switchport access vlan 20
	!
	</pre>
- Creating switch virtual interface and assigning default gateway on switch 1.
	<pre>
		sw-1(config)interface vlan 1
		ip address 10.1.1.1 255.255.255.0
		no shutdown
	</pre>
- Enable CDP on switch if it is not enabled already. CDP is used to view the neighbor device and it's connected ports.
	<pre>
	w-1(config)cdp run
	</pre>
- Enable routing on layer 3 switch so it can route packets between different networks.	
	<pre>
		sw-1(config)ip routing
	</pre>
- Next, switch needs to have a static route configured for network 1.1.1.1/32 as we're currently unable to ping to the router's loopback address 1.1.1.1/32.
	<pre>
		sw-1#ping 1.1.1.1

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 1.1.1.1, timeout is 2 seconds:
		.....
		Success rate is 0 percent (0/5)
	</pre>
- Configuring static route for network 1.1.1.1/32 on switch.
	<pre>
		sw-1(config)#ip route 1.1.1.1 255.255.255.255 10.1.1.254
		!
		sw-1#ping 1.1.1.1

		Type escape sequence to abort.
		Sending 5, 100-byte ICMP Echos to 1.1.1.1, timeout is 2 seconds:
		!!!!!
		Success rate is 100 percent (5/5), round-trip min/avg/max = 0/0/3 ms
	</pre>
- Switch will need to have DHCP request forwarding setup, In this diagram, PC's will send a boradcast message with DHCP request. By default, layer 3 switch does not forward broadcast messages to the router as it can casue network issues thus switch needs to configured with DHCP request forwarding.
	<pre>
		sw-1(config)#interface vlan 10
		sw-1(config-if)#ip helper-address 10.1.1.254
		sw-1(config-if)#exit
		sw-1(config)#interface vlan 20
		sw-1(config-if)#ip helper-address 10.1.1.254
		sw-1(config-if)#exit
	</pre>

This compeltes the configuration on router and switch. The PC1 and PC2 needs to have network interface card (NIC) configured to use the ip address from DHCP instead Static. If the lap is done in simulator or emulators then you may need to configure these settings otherwise the actual computers does have DHCP enabled on their NICs.

Next section shows the verification of routing, cdp neighbors, ip addresses verification, and ping connectivity on router, switch and pc's.

## Verification

### Router
- We can see both switch and router are learing static routes.

	<pre>
		rtr-1#show ip route static 
		 10.0.0.0/8 is variably subnetted, 4 subnets, 2 masks
	S       10.1.10.0/24 [1/0] via 10.1.1.1
	S       10.1.20.0/24 [1/0] via 10.1.1.1
	</pre>
- CDP neighbor command shows us, sw-1 is connected to rtr-1's local interface gig0/0/0 and it shows switch's (sw-1) port id is gig1/0/1
	<pre>
		rtr-1#show cdp neighbors 
		Capability Codes: R - Router, T - Trans Bridge, B - Source Route Bridge
                  S - Switch, H - Host, I - IGMP, r - Repeater, P - Phone
		Device ID    Local Intrfce   Holdtme    Capability   Platform    Port ID
		sw-1         Gig 0/0/0        148                    3650        Gig 1/0/1
	</pre>
- We can see router (rtr-1) received DHCP messages to assign an IP address for pc-1.

	<pre>
		rtr-1#debug ip packet
		Packet debugging is on
		rtr-1#
		rtr-1#
		IP: tableid=0, s=10.1.10.1 (GigabitEthernet0/0/0), d=10.1.1.254 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.10.1 (GigabitEthernet0/0/0), d=10.1.1.254 (GigabitEthernet0/0/0), len 77, rcvd 3

		IP: tableid=0, s=10.1.1.254 (local), d=10.1.10.11 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.1.254 (local), d=10.1.10.11 (GigabitEthernet0/0/0), len 128, sending

		rtr-1#
		IP: tableid=0, s=10.1.1.254 (local), d=10.1.10.11 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.1.254 (local), d=10.1.10.11 (GigabitEthernet0/0/0), len 128, sending

		rtr-1#
		IP: tableid=0, s=10.1.1.254 (GigabitEthernet0/0/0), d=10.1.10.1 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.1.254 (local), d=10.1.10.1 (GigabitEthernet0/0/0), len 66, sending

		IP: tableid=0, s=10.1.10.1 (GigabitEthernet0/0/0), d=10.1.1.254 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.10.1 (GigabitEthernet0/0/0), d=10.1.1.254 (GigabitEthernet0/0/0), len 77, rcvd 3

		IP: tableid=0, s=10.1.1.254 (GigabitEthernet0/0/0), d=10.1.10.1 (GigabitEthernet0/0/0), routed via RIB

		IP: s=10.1.1.254 (local), d=10.1.10.1 (GigabitEthernet0/0/0), len 66, sending

		rtr-1#un all
		All possible debugging has been turned off
	</pre>
- Now we can verify ip addresses on both pc-1 and pc-2 as well as a ping test from one pc to another.
PC 1
	<pre>
		C:\>ipconfig
		FastEthernet0 Connection:(default port)
		Connection-specific DNS Suffix..: 
		Link-local IPv6 Address.........: FE80::201:C9FF:FEE3:8437
		IPv6 Address....................: ::
		IPv4 Address....................: 10.1.10.11
		Subnet Mask.....................: 255.255.255.0
		Default Gateway.................: ::
						 10.1.10.1
	</pre>
PC 2
	<pre>
		C:\>ipconfig

		FastEthernet0 Connection:(default port)

		Connection-specific DNS Suffix..: 
		Link-local IPv6 Address.........: FE80::200:CFF:FE59:952A
		IPv6 Address....................: ::
		IPv4 Address....................: 10.1.20.11
		Subnet Mask.....................: 255.255.255.0
		Default Gateway.................: ::
										10.1.20.1
	</pre>

Ping test from PC 1 to PC 2 and PC 2 to PC1.
	<pre>
		C:\>ping 10.1.20.11

		Pinging 10.1.20.11 with 32 bytes of data:

		Reply from 10.1.20.11: bytes=32 time<1ms TTL=127
		Reply from 10.1.20.11: bytes=32 time<1ms TTL=127
		Reply from 10.1.20.11: bytes=32 time<1ms TTL=127
		Reply from 10.1.20.11: bytes=32 time<1ms TTL=127

		Ping statistics for 10.1.20.11:
		Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),
		Approximate round trip times in milli-seconds:
		Minimum = 0ms, Maximum = 0ms, Average = 0ms
	</pre>
PC 2
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
- Switch (sw-1) has static route 1.1.1.1 learnt by 10.1.1.254.
	<pre>
		sw-1#show ip route static 
		 1.0.0.0/32 is subnetted, 1 subnets
		S       1.1.1.1 [1/0] via 10.1.1.254	
	</pre>
