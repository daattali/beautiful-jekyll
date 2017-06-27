---
layout: post
published: false
title: Principios de Diseño para Desarrolladores
date: '2017-06-27'
subtitle: Un buen diseño evoluciona sin dolor
image: /img/design-principles.jpg
tags:
  - tips
  - conference
---
## ¿Cómo sé si tengo un buen diseño de software?

Es una pregunta sencilla pero con una respuesta no tan trivial. Por lo que me gustaría iniciar comentando lo que considero que es un **mal** diseño.

La tecnología siempre ha avanzado a una velocidad impresionante y en ningún ha mostrado señales de querer desacelerar en algún futuro, por lo que es normal que con frecuencia veamos la salida de nuevos frameworks, nuevas herramientas o metodologías que solucionan de formas innovadoras los problemas que surgen en el ámbito de la programación. Es por ello que considero que el diseño de una plataforma, software o proyecto debe ser concebida teniendo en cuenta su futuro creciemiento y evolución, sin descartar la posibilidad de tener que migrar a otras tecnologías.

Acá ya pudieramos hablar de arquitecturas orientadas a [microservicios](https://martinfowler.com/articles/microservices.html), pero no es solo la arquitectura la que nos va a garantizar un buen diseño para nuestro producto.

Duele hacer un cambio
Es peligroso hacer un cambio
Cuesta agregar modulos
Cuesta quitar modulos
Es inestable


Solucionar el problema 

Simple fails less
simple is easier to understand
simple solves only real problem we know about

Inherent complexity or accidental complexity?

Good design is the one that hides inherent complexity and eliminates the accidental complexity.

Think YAGNI (You aren't gonna need it)

Code should be cohesive. Because a peace of code should have one, and only one responsability. This way they fail less, change less and are simpler.

knock out before you mock out - blog

Reduce Coupling: Depending on a class is thigt coupling. Dependinf on an interface is loose coupling. The second one is the best approach. 

A good design has high cohesion and low coupling.

DRY - Every piece of knowledge in a system should have a single unambigups authorative representation.

pragmatic programmers book

Focus on single responsability - A class and/or a method should have only one responsability

Enter text in [Markdown](http://daringfireball.net/projects/markdown/). Use the toolbar above, or click the **?** button for formatting help.
