---
layout: post
title: Oxocard Science+
subtitle: Neues Spielzeug 
comments: true
author: Ramon Franke
last_modified_at: 2024-06-14
---

## Die Idee
Nach dem Einleitenden Artikel zur Oxocard möchte ich jetzt aber etwas damit basteln bzw ein kleines Projekt zeigen. Vlt kann jemand davon lernen.  
Die Oxocard hat viele Sensoren, vorallem was die beobachtung der Raumluft angeht. Da mich schon länger interessiert hat wie sich meine Luft im Büro verändert und wann es vlt angebracht ist zu lüften. War also die Idee das ganze mit Graphen darzustellen. Einfach zur Beobachtung wie sich das am Tag verhält.  
Mein Gedanke lag dabei erst auf Dockercontainern und Graphana um die Daten darzustellen. Durch Zufall bin ich aber auf Ada/IO gestoßen. Ein Service der von Adafruit angeboten wird und genau für solche Zwecke gedacht ist. Vereinfacht ist AdaIO eine Datenbank welche über eine API angesteuert werden kann. Zusätzlich gibt es direkt die Möglichkeit Dashboards zu erstellen und nach belieben zu gestallten.  
Diesen Service kann man glücklicherweise gratis Nutzen. Es gibt zwar eine Pro Variante, diese ist aber erst Relevant sollte eine höhrere Datenrate oder mehr Feeds benötigt werden.
Der Plan steht also, ein AdaIo einrichten und die Daten der Oxocard über CURL-Post an die API senden.

## Das Program
Das Programmieren geht hier recht schnell von der Hand. Ich möchte auch nicht den Code erklären, ich bin ohnehin kein begnadeter Programmierer. Deshalb habe ich mich auch dazu entschlossen erstmal das Rad nicht neu zu erfinden und mich für die Anzeige auf dem Display an bereits bestehenden Community Projekten zu bedienen. Ich habe mir also den Code von einem Projekt (Projekt Name einfügen) kopiert und an meine bedürfnisse angepasst.
Dan habe ich noch eine Funktion geschrieben welche die gewünschten Daten wie Luftfeuchtigkeit, CO2, IAQ etc über ein CURL-Request sendet.  
Dabei musste ich aber einpaar Einschränkungen durch die Programmiersprache NanoPy hinnehmen, das ließ sich aber alles Lösen. Nicht ganz einfach war es zusätzlich die eingebaute Post-Request Funktion zu verstehen. Nach etwas Try and Error war aber auch das geschafft. 

## AdaIo
Wie kurz eingeleitet ist AdaIo ein Service von Adafruit. Um die Datenbanken zu füllen kann man die API verwenden. Dafür braucht man wie üblich einen API-Key der sich unter den Einstellungen generieren lässt. AdaIO arbeitet mit "Feeds", das sind im wesentlichen Sammlungen von Datenpunkten. Ich kann zum Beispiel die Raumdemperatur meines Sensors an den feed "temperatur" senden. Unter dem feed habe ich dann eine Liste mit den gesendeten Temperaturwerten. Mit den Feeds lässt sich dann super weiter arbeiten.

https://io.adafruit.com/blog/
https://learn.adafruit.com/welcome-to-adafruit-io/getting-started-with-adafruit-io
https://io.adafruit.com/api/docs/#adafruit-io-http-api

## Links
https://oxocard.ch/