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
![feeds](/assets/img/oxocard/account_overview.png)
Der Plan steht also, ein AdaIO einrichten und die Daten der Oxocard über CURL-Post an die API senden.

## Das Program
Das Programmieren geht hier recht schnell von der Hand. Ich möchte auch nicht den Code erklären, ich bin ohnehin kein begnadeter Programmierer. Deshalb habe ich mich auch dazu entschlossen erstmal das Rad nicht neu zu erfinden und mich für die Anzeige auf dem Display an bereits bestehenden Community Projekten zu bedienen. Ich habe mir also den Code von einem Projekt "Alle Sensoren" von Dietmar Klimmek kopiert und an meine bedürfnisse angepasst.
Dan habe ich noch eine Funktion geschrieben welche die gewünschten Daten wie Luftfeuchtigkeit, CO2, IAQ etc über ein CURL-Request sendet.  
Dabei musste ich aber einpaar Einschränkungen durch die Programmiersprache NanoPy hinnehmen, das ließ sich aber alles Lösen. Nicht ganz einfach war es zusätzlich die eingebaute Post-Request Funktion zu verstehen. Nach etwas Try and Error war aber auch das geschafft.

~~~python
def updateAdaIO(feed: byte[120], value):
    addRequestHeader("X-AIO-Key", KEY)
    addRequestHeader("Content-Type", "application/json")
    body = "{\"value\":" + value + "}"
    url = "https://io.adafruit.com/api/v2/"+ USERNAME + "/feeds/" + feed + "/data"

    print("sending POST request for " + feed + "...")
    if (postRequest(url, body)):
        print("sending POST successfull" + readRequestJSON("data"))
    else:
        print("error while sending POST" + readRequestJSON("data"))
~~~

Den vollständigen Code zum nachmachen findest du hier: https://github.com/gtxmen/nanopy-adaio-envmonitoring/tree/main

## AdaIO
Zunächste wollte ich eine Schritt für Schritt erklärung schreiben. Adafruit hat aber super Tolle Dokumentationen auf die ich weiter unten verweise. Darüberhinaus ist auch die Nutzeroberfläche inuitiv, das mir eine Anleitung als Nichtich erschien. Hier aber ein Überblick zu AdaIO und was aus meinen Daten geworden ist:
Wie kurz eingeleitet ist AdaIO ein Service von Adafruit. Um die Datenbanken zu füllen kann man die API verwenden. Dafür braucht man wie üblich einen API-Key der sich unter den Einstellungen generieren lässt. AdaIO arbeitet mit "Feeds", das sind im wesentlichen Sammlungen von Datenpunkten. Ich kann zum Beispiel die CO2-Messwerte meines Sensors an den feed "co2" senden. Unter dem feed habe ich dann eine Liste mit den gesendeten CO2-Werten. Mit den Feeds lässt sich dann super weiter arbeiten.  
Hier ein Beispiel:
![feeds](/assets/img/oxocard/feeds.png)
AdaIO bringt direkt die eigene Funktion mit, die Feeds Grafisch darzustellen. Das heißt ihr könnt direkt Dashboards mit Graphen, Reglern oder Diagrammen erstellen.
![dashboard](/assets/img/oxocard/dashboard.png) 



https://io.adafruit.com/blog/
https://learn.adafruit.com/welcome-to-adafruit-io/getting-started-with-adafruit-io
https://io.adafruit.com/api/docs/#adafruit-io-http-api

## Links
https://oxocard.ch/