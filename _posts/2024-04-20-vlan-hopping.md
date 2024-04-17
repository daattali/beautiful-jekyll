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
### 1. Interface Identifier:

~~~
Physische Adresse . . . . . . . . : 7C-10-C9-41-1E-90
gebildete EUI-64 Adresse . . . . .: 7E10:C9FF:FE41:1E90
~~~

![DAD](/assets/img/ipv6/ipv6_dad_keinedopplung.jpg)


## Links
https://de.wikipedia.org/wiki/Dynamic_Trunking_Protocol

## Table Styling in Markdown

<style>
    .heatMap {
        width: 70%;
        text-align: center;
    }
    .heatMap th {
        background: grey;
        word-wrap: break-word;
        text-align: center;
    }
    .heatMap tr:nth-child(1) { background: red; }
    .heatMap tr:nth-child(2) { background: orange; }
    .heatMap tr:nth-child(3) { background: green; }
</style>

<div class="heatMap">

| Everything | in this table | is Centered | and the table will only take up 70% of the screen width | 
| -- | -- | -- | -- |
| This | is | a | Red Row |
| This | is | an | Orange Row |
| This | is | a | Green Row |

</div>

Another text
