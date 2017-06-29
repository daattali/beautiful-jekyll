---
layout: post
published: false
title: Software que cuesta mantener
date: '2017-06-27'
subtitle: Un buen diseño evoluciona sin dolor
image: /img/design-principles.jpg
tags:
  - tips
  - conference
---
¿Puede doler mantener software? Pues si, puede doler mentalmente (desgaste intelectual, estrés), físicamente (horas sin dormir) y económicamente (si es un producto o tienes desarrolladores contratados). Y ¿por qué puede resultar doloroso? Por múltiples razones, pero me atrevo a decir que la principal razón **técnica** es por un _mal diseño_.

## ¿Cómo sé si tengo un buen diseño de software?

La tecnología siempre ha avanzado a una velocidad impresionante y en ningún momento ha mostrado señales de querer desacelerar en algún futuro, por lo que es normal que con frecuencia veamos la salida de nuevos frameworks, nuevas herramientas o metodologías que solucionan de formas innovadoras los problemas que surgen en el ámbito de la programación. Es por ello que considero que el diseño de una plataforma, software o proyecto debe ser concebida teniendo en cuenta su futuro crecimiento y evolución, sin descartar la posibilidad de tener que migrar a otras tecnologías.

Como solución a ésta capacidad de _adaptación_ que se requiere pudiéramos hablar de arquitecturas orientadas a [microservicios](https://martinfowler.com/articles/microservices.html), pero no es solo la arquitectura la que nos va a garantizar un buen diseño para nuestro producto.

Ahora, sobre la pregunta del título... Es una pregunta sencilla pero con una respuesta no tan trivial. Por lo que me gustaría iniciar comentando lo que considero son señales de un **mal** diseño:

- Duele hacer un cambio
- Es peligroso hacer un cambio
- Es complicado agregar funcionalidades
- Es complicado quitar funcionalidades
- Estás amarrado a cierta tecnología

Si, algunas pueden ser subjetivas. Lo que es "complicado" para un _junior_ no necesariamente lo sea para un _senior_. Pero podemos estar de acuerdo en que agregar o quitar funcionalidades no debe acarrear un alto nivel de **complejidad**. Sobre la complejidad hablaré un poco más adelante igualmente.

## Enfócate

Es importante tener claro el problema/requerimiento que se quiere resolver. Esta es una de las cosas que las metodologías __tradicionales__ buscaban solucionar, con todos los diagramas de flujo, de actividades, de clases... El conjunto de todos estos documentos buscaban plasmar lo que se requería del software. Pero bueno, ya saben, no son **ágiles**, característica muy importante si queremos tener la capacidad de adaptación que mencionaba antes.


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
