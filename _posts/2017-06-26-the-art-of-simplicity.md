---
layout: post
title: ''
subtitle: The Art of Simplicity
bigimg: /img/the-art-of-simplicity.jpg
published: true
date: '2017-06-26'
---
En la empresa en la que trabajo actualmente ([RocketROI](https://www.rocketroi.com/es/)) como premio a una especie de competencia interna, me han regalado una entrada a la [Java Barcelona Conference](http://www.jbcnconf.com/2017/). Esta conferencia tuvo una duración de 3 días, siendo los primeros 2 días exclusivos para las [charlas](http://www.jbcnconf.com/2017/talks.html) y el último día dedicado a los [workshops](http://www.jbcnconf.com/2017/workshops.html). Debido a que todas las charlas se ejecutaban de forma simultanea, era necesario elegir con antelación "el camino" que querías seguir. A continuación, quiero contarles _brevemente_ lo que aprendí de la primera de ellas, _The Art of Simplicity_.

## The Art of Simplicity

Speaker: [Venkat Subramaniam](https://twitter.com/venkat_s) 

Venkat comenzó esta charla explicándonos **que NO es la simplicidad**. Además de ofrecernos variadas recomendaciones, de esas que muchos sabemos pero igualmente pocos aplicamos. Recomendaciones como: usar nombres de variables que tengan sentido, documentar nuestro código, evitar la mutabilidad, entre otras. 

**Imperative Code < Declarative Code.** El código es menos complejo y mantenible si en lugar de especificar _qué hacer_ y _cómo hacerlo_, solo tenemos que definir _qué hacer_. 

**Simple code it is not clever.** El código debe ser claro, entendible. El buscar una solución "ingeniosa" dificulta el desarrollo para otro programador, ya que primero deberá entender lo que está hecho. Además, el código _ingenioso_ suele ser más propenso a bugs que el código _simple_.

**Simple code it is not necessarily familiar.** La forma en la que explica este punto me parece genial aunque debatible. Muestra en la presentación un par de letras chinas y pregunta si alguien sabe que significan, nadie responde. Son las letras en chino para "Simple", y nos demuestra que el hecho de que no estemos familiarizados con el idioma no quiere decir que no sea simple. El punto a destacar acá es que en muchas ocasiones hay formas más simples de solucionar ciertos problemas, pero al no ser _familiares_ para nosotros, pensamos que es complejo. El hecho es que una vez entendemos el código, que aunque no nos sea familiar en un principio, sí que es simple y nos facilita su futuro mantenimiento o mejora. 

**Simple code it is not overengineer.** Venkat nos comenta que es una mala practica desarrollar pensando en solucionar la "madre de los problemas" cuando podemos solucionar _simplemente_ el problema que tenemos. Nos cuenta una anécdota en la que habla en persona con un desarrollador que buscaba solucionar la "madre de los problemas" y quería convencerlo de que era una buena idea. Entonces Venkat le pide que lo disculpe un minuto y se retira para llamar al mismo desarrollador con el que hablaba a su teléfono móvil y éste le pregunta "¿Porque me llamas? Si estamos a pasos de distancia." y Venkat le responde "Aunque estemos cerca, si quisiéramos estar lejos, pudiéramos seguir hablando.". Demostrando que no hay que _buscarle la quinta pata al gato_, cuando queremos solucionar un problema que de por sí es simple. 

**Simple code it is not terse.** Existe una diferencia entre código conciso y código breve o corto. El código breve, en la búsqueda de ser corto puede dar espacio a bugs o comportamientos no esperados, además de ser difícil de comprender. En cambio, el código conciso hace lo que debe hacer sin _boilerplate_ y buscando mantener la simplicidad, lo que facilita su comprensión. Para finalizar, les comento de una de las frases que dijo que me gustó mucho: "Existen 2 formas de hacer software, la primera es hacerlo tan simple que sea obvio que no tiene deficiencias. La segunda es hacerlo tan complejo que no sea obvio que tiene deficiencias."
