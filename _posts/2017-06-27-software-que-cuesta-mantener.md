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

## ¿Tengo un mal diseño de software?

La tecnología siempre ha avanzado a una velocidad impresionante y en ningún momento ha mostrado señales de querer desacelerar en algún futuro, por lo que es normal que con frecuencia veamos la salida de nuevos frameworks, nuevas herramientas o metodologías que solucionan de formas innovadoras los problemas que surgen en el ámbito de la programación. Es por ello que considero que el diseño de una plataforma, software o proyecto debe ser concebida teniendo en cuenta su futuro crecimiento y evolución, sin descartar la posibilidad de tener que migrar a otras tecnologías.

Como solución a ésta capacidad de _adaptación_ que se requiere pudiéramos hablar de arquitecturas orientadas a [microservicios](https://martinfowler.com/articles/microservices.html), pero no es solo la arquitectura la que nos va a garantizar un buen diseño para nuestro producto.

Ahora, sobre la pregunta del título... Es una pregunta sencilla pero con una respuesta no tan trivial. Estas son señales de lo que considero un **mal** diseño:

- Duele hacer un cambio
- Es peligroso hacer un cambio
- Es complicado agregar funcionalidades
- Es complicado quitar funcionalidades
- Estás amarrado a cierta tecnología

Si, algunas pueden ser subjetivas. Lo que es "complicado" para un _junior_ no necesariamente lo sea para un _senior_. Pero podemos estar de acuerdo en que agregar o quitar funcionalidades no debe acarrear un alto nivel de **complejidad** (sobre este punto hablaré un poco más adelante). Finalmente, puedieramos resumir todas las señales listadas en una sola palabra: **rígidez**. Es esta característica la que practicamente nos garantiza que será _costoso_ mantener o mejorar el software en el que trabajamos. 

## Enfócate

Es importante tener claro el problema/requerimiento que se quiere resolver. Esta es uno de las aspectos que las metodologías __tradicionales__ buscaban solucionar, con todos los diagramas de flujo, de actividades, de clases... El conjunto de todos estos documentos buscan plasmar lo que se requiere del software. Pero bueno, ya saben, no son **ágiles**, característica muy importante si queremos tener la capacidad de adaptación que mencionaba antes.

En las metodologías ágiles, para comprender el problema que queremos resolver, tenemos reuniones diarias o semanales, wikis, memos... Todo en favor de la adaptabilidad y velocidad (o **agilidad**, obviamente).

Al conocer bien el problema, podemos enfocarnos en solucionarlo. El código que desarrollemos para satisfacer algún requerimiento cuenta con 2 tipos de complejidades, por así decirlo. Éstas son la  complejidad inherente y la complejidad accidental. La primera de ellas es la complejidad propia del dominio del problema, es algo natural y contra la que poco podemos hacer, más que buscar entenderla lo mejor posible. En cambio, la complejidad accidental pudiéramos decir que es _nuestra culpa_, es complejidad que agregamos al hacer el código complejo, no testeable, poco mantenible, ambiguo. Éste tipo de complejidad es común cuando no sabemos con claridad el problema que queremos solucionar.

Un buen diseño es aquel que esconde la complejidad inherente y elimina la complejidad accidental. Un código simple falla menos, es fácil de entender y facilita su mantenimiento.
