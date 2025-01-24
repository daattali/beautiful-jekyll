---
layout: post
title: Umgebungsmonitoring mit dem Science+
subtitle: Zeit zum Lüften
comments: true
author: Ramon Franke
last_modified_at: 2024-06-14
---

## Die Idee

Nachdem wir das Oxocard nun kennengelernt haben, möchte ich mit den Funktionen etwas experimentieren, dafür habe ich ein kleines Projekt gestartet.

Die Oxocard hat viele Sensoren, vor allem die Überwachung der Raumluft war für mich von Interesse. Mich hat schon länger interessiert, wie sich die Luftqualität im Büro verändert und wann es vlt angebracht wäre, zu lüften. 
Meine Idee war also, entsprechende Parameter wie Temperatur, CO2 oder Luftfeuchtigkeit mittels Graphen darzustellen. Einfach zur Beobachtung, wie sich das am Tag verhält.  

Zunächst dachte ich an Dockercontainern und Graphana um die Daten darzustellen. Durch Zufall bin ich aber auf Ada/IO gestoßen. Ein Service, der von Adafruit angeboten wird und genau für solche Zwecke gedacht ist. Vereinfacht ist AdaIO eine Datenbank, welche über eine API angesteuert werden kann. Zusätzlich gibt es direkt die Möglichkeit, Dashboards zu erstellen und nach Belieben zu gestalten.  

Diesen Service kann man glücklicherweise gratis nutzen. Es gibt zwar eine Pro-Variante, diese ist aber erst relevant, sollte eine höhere Datenrate oder mehr Feeds benötigt werden.
![feeds](/assets/img/oxocard/account_overview.png)
Der Plan steht also, ein AdaIO einzurichten und die Daten der Oxocard über CURL-Post an die API zu senden.

## Das Program

Das Programmieren geht hier recht schnell von der Hand. Ich möchte auch nicht den Code erklären, ich bin ohnehin kein begnadeter Programmierer. Deshalb habe ich mich auch dazu entschlossen, erstmal das Rad nicht neu zu erfinden und mich für die Anzeige des Displays an bereits bestehenden Community-Projekten zu bedienen. 

Ich habe mir also den Code von einem Projekt "Alle Sensoren" von Dietmar Klimmek kopiert und an meine Bedürfnisse angepasst.Dann habe ich noch eine weitere Funktion hinzugefügt, welche die gewünschten Daten wie Luftfeuchtigkeit, CO2, IAQ etc über ein CURL-Request sendet. Dabei musste ich aber ein paar Einschränkungen durch die Programmiersprache NanoPy hinnehmen aber auch dies lies sich lösen. Zusätzlich war es für mich nicht ganz einfach, die eingebaute Post-Request Funktion zu verstehen. Die Dokumentation war zu dieser Funktion etwas dürftig. 

Nach etwas Trial-and-Error war aber auch das geschafft.

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

Den vollständigen Code zum Nachmachen findest du hier: [Nanopy-Envmonitoring](https://github.com/gtxmen/nanopy-adaio-envmonitoring/tree/main)

## AdaIO

Zunächst wollte ich eine Schritt-für-Schritt-Erklärung schreiben. Adafruit hat aber super tolle Dokumentationen, auf die ich weiter unten verweise. Darüber hinaus ist auch die Nutzeroberfläche intuitiv, sodass mir eine Anleitung als nichtig erschien. 

Hier aber ein Überblick zu AdaIO und was aus meinen Daten geworden ist:
Wie kurz eingeleitet, ist AdaIO ein Service von Adafruit. Um die Datenbanken zu füllen, kann man die API verwenden. Dafür braucht man wie üblich einen API-Key, der sich unter den Einstellungen generieren lässt. AdaIO arbeitet mit "Feeds", das sind im Wesentlichen Sammlungen von Datenpunkten. Ich kann zum Beispiel die CO2-Messwerte meines Sensors an den Feed "co2" senden. Unter dem Feed habe ich dann eine Liste mit den gesendeten CO2-Werten. Mit diesen Feeds lässt sich dann super weiter arbeiten.  

Hier ein Beispiel:
![feeds](/assets/img/oxocard/feeds.png)
AdaIO bringt direkt die eigene Funktion mit, die Feeds grafisch darzustellen. Das heißt, ihr könnt direkt Dashboards mit Graphen, Reglern oder Diagrammen erstellen.
![dashboard](/assets/img/oxocard/dashboard.png) 

## Fazit

Unterm Strich ist die Oxocard in der Kombination mit AdaIO eine einfache und tolle Möglichkeit, um einen schnellen Einstieg, um Daten visuell darzustellen. Hier sehe ich gerade für Anfänger große Vorteile. Da sich diese nicht erst mit Tools wie Telegraph,InfluxDB und Graphana (TIG-Stack) herumschlagen müssen.

Die Einfachheit von AdaIO bietet so ein schnelles Erfolgserlebnis und sorgt für Motivation.

## Links

[Oxocard](https://oxocard.ch/)  
[Adrafruit-Blog](https://io.adafruit.com/blog/)  
[Getting Started with Adafruit](https://learn.adafruit.com/welcome-to-adafruit-io/getting-started-with-adafruit-io)  
[Adafruit-IO-API](https://io.adafruit.com/api/docs/#adafruit-io-http-api)