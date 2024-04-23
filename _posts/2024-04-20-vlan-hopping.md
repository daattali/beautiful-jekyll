---
layout: post
title: VLAN Hopping 
subtitle: "Wildes rumgehopse" 
comments: true
author: Ramon Franke
last_modified_at: 2024-04-17
---

## DTP: Dynamic Trunking Protokol
Als Einleitung eine Übersicht über DTP, das Cisco Dynamic Trunking Protocol. Das Protokol ist zum automatischen Aushandeln von Trunking Ports. Trunking Ports sind Ports über die mehrere VLANS übertragen werden.
Für diese Aushandlung senden Cisco Switche DTP-Frames an die Multicast-MAC-Adresse 01-00-0C-CC-CC-CC. Über die Frames finden dann die Verhanldungen des Port zustands statt. Zum einen wird der Port automatisch zu einem Trunking Port mit entsprechenden Protokoll (802.1q). Ein Frame sieht wie folgt aus: 

//Bild von einem Frame 

Um das Feld Status zuverstehen ist die Vorkenntnis wichtig das noch weitere Switchport Modes gibt. Das Feld gibt dann an in welchem Switchport Mode sich der Port befindet. Die Switche entscheiden dann anhand des empfangenen Frames für welchen Port Sie sich entscheiden. Ein Port wird zum Trunk wenn folgende Kombinationen aufeinander treffen:

// Tabelle mit allen Möglichkeiten Zuständen
// Noch überprüfen
 
| Switch1 | Switch2  | Zustand | Bemerkung |
| :------ |:-------- |:------- |:--------- |
| on | on | Trunk | DTP-Pakete werden von beiden Switches gesendet |
| on | off | Kein Trunk | DTP-Pakete werden nur von SW2 gesendet |
| on | auto | Trunk | DTP-Pakete werden von beiden SW gesendet | 
| on | desirable | Trunk | DTP-Pakete werden von beiden Switchen gesendet | 
| auto | auto | Kein Trunk | DTP-Pakete werden von beiden Switchen gesendet |
| auto | desirable | Trunk | DTP-Pakete werden von beiden Switchen gesendet |  

//Noch eine Tabelle in der steht welche Zustand (on,off, desirable) bei welche Switchport Konfig zutrifft.

## IST-Zustand


Konfig des Interfaces:
---
Switch1#show run int gi0/1
Building configuration...

Current configuration : 77 bytes
!
interface GigabitEthernet0/1
 description Attk-Kali
 negotiation auto
end
---

.Show int status:
---
Switch1#show int status

Port      Name               Status       Vlan       Duplex  Speed Type 
Gi0/0                        connected    trunk      a-full   auto RJ45
Gi0/1     Attk-Kali          connected    1          a-full   auto RJ45
Gi0/2     Client-Office      connected    10         a-full   auto RJ45
Gi0/3                        connected    1          a-full   auto RJ45
---

.Show int switchport
---
Switch1#show int gi0/1 switchport 
Name: Gi0/1
Switchport: Enabled
Administrative Mode: dynamic auto
Operational Mode: static access
Administrative Trunking Encapsulation: negotiate
Operational Trunking Encapsulation: native
Negotiation of Trunking: On
Access Mode VLAN: 1 (default)
Trunking Native Mode VLAN: 1 (default)
Administrative Native VLAN tagging: enabled
Voice VLAN: none
Administrative private-vlan host-association: none 
Administrative private-vlan mapping: none 
Administrative private-vlan trunk native VLAN: none
Administrative private-vlan trunk Native VLAN tagging: enabled
Administrative private-vlan trunk encapsulation: dot1q
Administrative private-vlan trunk normal VLANs: none
Administrative private-vlan trunk associations: none
Administrative private-vlan trunk mappings: none
Operational private-vlan: none
Trunking VLANs Enabled: ALL
Pruning VLANs Enabled: 2-1001
Capture Mode Disabled
Capture VLANs Allowed: ALL

Protected: false
Appliance trust: none
---


Ausgabe nach dem Angriff:
----
Switch1#show int status

Port      Name               Status       Vlan       Duplex  Speed Type 
Gi0/0                        connected    trunk      a-full   auto RJ45
Gi0/1     Attk-Kali          connected    trunk      a-full   auto RJ45
Gi0/2     Client-Office      connected    10         a-full   auto RJ45
Gi0/3                        connected    1          a-full   auto RJ45
Switch1#show int gi0/1 switchport 
Name: Gi0/1
Switchport: Enabled
Administrative Mode: dynamic auto
Operational Mode: trunk
Administrative Trunking Encapsulation: negotiate
Operational Trunking Encapsulation: dot1q
Negotiation of Trunking: On
Access Mode VLAN: 1 (default)
Trunking Native Mode VLAN: 1 (default)
Administrative Native VLAN tagging: enabled
Voice VLAN: none
Administrative private-vlan host-association: none 
Administrative private-vlan mapping: none 
Administrative private-vlan trunk native VLAN: none
Administrative private-vlan trunk Native VLAN tagging: enabled
Administrative private-vlan trunk encapsulation: dot1q
Administrative private-vlan trunk normal VLANs: none
Administrative private-vlan trunk associations: none
Administrative private-vlan trunk mappings: none
Operational private-vlan: none
Trunking VLANs Enabled: ALL
Pruning VLANs Enabled: 2-1001
Capture Mode Disabled
Capture VLANs Allowed: ALL

Protected: false
Appliance trust: none
----

---


![DAD](/assets/img/ipv6/ipv6_dad_keinedopplung.jpg)


## Links
https://de.wikipedia.org/wiki/Dynamic_Trunking_Protocol
https://jay-miah.co.uk/index.php/vlan-hopping-concept-attack-example-and-prevention/
