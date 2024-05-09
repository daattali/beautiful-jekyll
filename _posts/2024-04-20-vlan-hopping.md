---
layout: post
title: VLAN Hopping 
subtitle: "Furious Jumping" 
comments: true
author: Ramon Franke
last_modified_at: 2024-04-17
---

## DTP: Dynamic Trunking Protokol
Als Einleitung eine Übersicht über DTP, das Cisco Dynamic Trunking Protocol. Das Protokoll ist zum automatischen Aushandeln von Trunking Ports und soll den Administratoren von Netzwerken, Arbeit abnehmen. Kurz zur Erinnerung, Trunking Ports sind Ports, über die mehrere VLANs übertragen werden. Damit zwei Switche automatisch einen Trunk Port zueinander herstellen, werden DTP-Frames über die Multicast-MAC-Adresse 01-00-0C-CC-CC-CC gesendet. Über die Frames findet dann die Verhandlungen des Port-Zustands statt. Wenn die Bedingungen stimmen, wird automatisch ein Trunk Port ausgehandelt. Dazu gleich mehr, hier zunächst ein Auszug eines DTP-Frames: 

![dtp-frame](/assets/img/vlan_hopping/DTP-Paket.png)

In dem Feld __Trunk Status__ gibt es die beiden Felder __Trunk Operating Status__ und __Trunk Administrativ Status__. Wichtig für die Aushandlung über DTP ist der Wert in dem Feld __Trunk Administrativ Status__, das andere Feld spiegelt den aktuellen Port-Zustand wieder. In der unten stehenden Tabelle sind die Kombinationen aufgeschrieben, welche zu einem Trunk Port führen würden. Zur Erklärung, wenn beide Switche mit dem Port-Mode __Dynamic Auto__ konfiguriert sind, bleiben beide Ports im Zustand __Access__. Es werden also keine VLANs getaggt bzw keine weiteren VLANs als ein vorkonfiguriertes übertragen. Befindet sich ein Port im Mode __Trunk__ und der Port des zweiten Switches im Mode __Auto__ wird automatisch ein Trunk aufgebaut. Sofern nicht anders konfiguriert (was bei der Standardkonfiguration der Fall ist) werden alle VLANS (1-4096) übertragen, sofern diese auf dem Switch konfiguriert sind.

| Administrative Status | Access | Trunk | Dynamic Auto | Dynamic Desirable |
|---------------------|--------|-------|--------------|-------------------|
| **Access**          | Access | -     | Access       | Access            |
| **Trunk**           | -      | Trunk | Trunk        | Trunk             |
| **Dynamic Auto**    | Access | Trunk | Access       | Trunk             |
| **Dynamic Desirable** | Access | Trunk | Trunk        | Trunk             |

Das Gefährliche aber ist, dass ein Angreifer somit ungewollt einen Trunk Port provozieren kann (und somit auf alle VLANs Zugriff hat) wenn die Gegenstelle nicht abgesichert wird. 
Nachfolgend habe ich das Ganze mal in CML nachgebaut, um die Einfachheit zu verdeutlichen und das Protokoll besser zu verstehen. Anschließend gebe ich meinen Rat zur Prävention.

## Der Versuch

{: .box-warning}
**Achtung!:** Ich möchte auf keinen Fall zu Straftaten verleihten. Das gezeigte Tutorial ist zum Lernen bzw Verstehen von Netzwerken gedacht und soll zugleich Bewusstsein schafen.

An dieser Stelle ist noch zu erwähnen, dass ein frisch ausgepackter Cisco Switch standardmäßig DTP verwendet. Das heißt, jeder Port im Default-Zustand ohne Konfiguration lässt einen Trunk Port zu.

### IST-Zustand
Etwas zum Versuchsaufbau, wir haben zwei L2-Switche bzw __eine Broadcast-Domäne__. Auf den Switchen gibt es jeweils das VLAN 10 und VLAN 30 in dem sich jeweils ein Client befindet. An Switch1 haben wir als unseren __Angreifer__ eine Kali-Linux-Maschine mit dem Tool "Yersinia". Den Port von Switch1 an dem das Kali-Linux hängt, bezeichne ich weiter im Artikel als Angriffsport.

![Topology](/assets/img/vlan_hopping/cml_topology.png)

Hier ist zusehen, dass die Konfig des Angriffsports fast "default" ist. Lediglich für eine bessere Nachvollziehbarkeit habe ich auf dem Port eine Description konfiguriert, die bei verschiedenen Ausgaben den Port kenntlicher macht.

Konfig des Interfaces:
~~~
Switch1#show run int gi0/1
Building configuration...

Current configuration : 77 bytes
!
interface GigabitEthernet0/1
 description Attk-Kali
 negotiation auto
end
~~~

Auf Switch1 haben wir nun folgende Ports:
~~~
Switch1#show int status

Port      Name               Status       Vlan       Duplex  Speed Type 
Gi0/0                        connected    trunk      a-full   auto RJ45
Gi0/1     Attk-Kali          connected    1          a-full   auto RJ45
Gi0/2     Client-Office      connected    10         a-full   auto RJ45
Gi0/3                        connected    1          a-full   auto RJ45
~~~

Wenn wir uns den Switchport genauer anschauen, erkennen wir, dass das DT-Protokoll (DTP) automatisch aktiv ist und auf __dynamic auto__ steht. Wir erinnern uns an die zu Beginn gezeigte Tabelle, bei der Kombination "auto-zu-desirable" entsteht automatisch ein Trunk!
~~~
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
~~~

### Zum Angriff

Gehen wir den Test nun aktiv an und schwenken zu unserem Kali-Linux. Um dem Switch DTP-Pakete zusenden, verwenden wir das Tool Yersinia. Wir können dies direkt über die CLI oder über eine GUI erledigen. In unserem Test gehen wir direkt über die CLI und wählen unser Inteface aus.

![Yersinia-Interface-Selection](/assets/img/vlan_hopping/yersinia_interface_auswahl.png)

Im nächsten Schritt wählen wir unseren Angriff aus.
Yersinia zeichnet jetzt empfangene DTP-Pakete auf. In unserem Fall können wir also bereits Pakete mit **ACCESS/AUTO** von der MAC-Adresse: **52:54:00:15:3A:FF** sehen. Die MAC-Adresse gehört zu dem Interface unseres Switches. Über Yersinia können wir jetzt einfach über das Menü sagen, dass wir auch DTP-Pakete senden wollen, um einen Trunk herzustellen.

![Yersinia-Attack-Selection](/assets/img/vlan_hopping/yersinia_attack_enabling_trunking.png)

Nach Auswahl sendet Yersinia Pakete mit dem Typ **ACCESS/Desirable**, sprich unser Port ist noch im Mode Access, Mode Trunk wäre aber erwünscht. Rufen wir uns die Tabelle zu Beginn in Erinnerung: Bei der Kombination Switch1:Auto, Switch2:Desirable einigen sich die Switche auf einen Trunk Port. Das Resultat ist, dass ein DTP-Paket des Switches zurückkommt, mit **TRUNK/AUTO**, der Port-Mode ist also zu einem Trunk gewechselt. Nach kurzer Zeit sendet auch Yersinia ein Paket mit **TRUNK/DESIRABLE**.

Zum nachvollziehen hier Links ein Bild des DTP-Frames von dem Switch, rechts ein Paket von unserem Angreifer.

Switch | Angreifer
------ | --------- 
![ping-test](/assets/img/vlan_hopping/dtp-switch.png) | ![ping-test](/assets/img/vlan_hopping/dtp-attk-marked.png)

Hier zwei Bilder von Frames nach dem ausgehandelten Trunk.

Switch | Angreifer
------ | --------- 
![ping-test](/assets/img/vlan_hopping/dtp-switch-2.png) | ![ping-test](/assets/img/vlan_hopping/attk-trunk.png)

Switch-Status nach dem Angriff:
~~~
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
~~~

### Ausnutzen des Trunks

Der eigentliche Angriff bzw die Ausnutzung des DTP-Protokolls ist damit abgehandelt. Zwischen unserem Angriffs-PC und dem Switch besteht ein Trunk Port und wir haben Zugriff auf alle VLANs innerhalb des Trunks. Zur Demonstration, was das bedeuten kann, können wir unter dem Linux zwei Subinterfaces konfigurieren, eines im VLAN10 und ein weiteres in VLAN30. Durch die TRUNK-Verbindung sollten wir beide Rechner anpingen können. 

Unsere neue Konfig von `/etc/network/interfaces`
~~~
# This file describes the network interfaces available on your system
# and how to activate them. For more information, see interfaces(5).

source /etc/network/interfaces.d/*

#The loopback network interface
auto lo
iface lo inet loopback

auto eth0.10
iface eth0.10 inet static
 address 192.168.10.100
 netmask 255.255.255.0

auto eth0.30
iface eth0.30 inet static
 address 192.168.30.100
 netmask 255.255.255.0
~~~

Nach einem Neustart des Networking-Services `sudo service networking restart` ist ein Ping über die Subinterfaces möglich.

![ping-test](/assets/img/vlan_hopping/kali_successfull_pings.png)

Eine schnelle und einfache Methode!

## Prävention
So einfach der Angriff ist, so einfach kann man sich auch davor schützen. Natürlich gilt immer der Grundsatz, alles abzuschalten was nicht gebraucht wird (das spart auch noch Strom), so also auch den Port. Mit dem Befehl `switchport nonegotiate` wird DTP auf Ports deaktiviert, was zur Standardkonfiguration der Ports gehören sollte. Zusätzlich ist es ratsam, Ports als Access Ports zu konfigurieren und in ein Dummy-VLAN zu "parken". Das liegt an der vielseitigen Verwendung des __VLAN 1__ bei Cisco Switchen. Darüber finden beispielsweise auch Aushandlungen für STP/CDP. Zuletzt kann auch das __nativ Vlan__ vorsorglich konfiguriert werden. Dies spielt zwar so lange keine Rolle, bis der Modus wieder in einen Trunk konfiguriert wird, besser ist es dennoch. Es könnte also folgende Port-Konfiguration konfiguriert werden.

~~~
vlan 999
name dummy-vlan

int gig0/0/1
switchport mode access
switchport trunk native vlan 999
switchport access vlan 999
switchport nonegotiate
shutdown
~~~

## Links
https://de.wikipedia.org/wiki/Dynamic_Trunking_Protocol  
https://jay-miah.co.uk/index.php/vlan-hopping-concept-attack-example-and-prevention/
