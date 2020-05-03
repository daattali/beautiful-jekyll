---
layout: post
published: true
title: 'TDD Estilo Londres'
subtitle: Test Driven Design
date: '2018-12-09'
image: /assets/img/london-logo.png
share-img: /assets/img/doubleloop.png
tags: [programming, tdd, java]
---

Hace ya algunos años se habla mucho de TDD; principalmente sobre como puede mejorar tu confianza en el código y a la vez de cierta forma documentar lo que se espera de él, facilitando la incorporación de otros desarrolladores y de nuevos features. Algunos lo llaman Test Driven Development, pero a mi me parece más apropiada la palabra *Design*, ya que su implementación influye de forma significativa en la estructura del diseño del sistema.

Cuando se habla de TDD se espera que escribas la mínima cantidad de código necesaria para hacer pasar los tests, y por lo general, se espera que inicies con la tarea más simple que tengas. Seguir este flujo resulta en lo que se conoce como un desarrollo *bottom-up* o *inside-out*, que implica iniciar desarrollando las unidades más pequeñas/simples, anticipando aquellas que se crea serán requeridas por el sistema, y luego desarrollar las unidades "compuestas", es decir, aquellas que usan estas unidades más pequeñas/simples. 

Un ejemplo del estilo antes descrito podría significar iniciar con el modelo (entity o POJO) y una función particular de ordenamiento, antes de desarrollar el controlador que haría uso de ambos.

<p align="center">
  <img src="/assets/img/classic_tdd.png" alt="Classic TDD flow"/>
</p>

Este estilo, en algunas ocasiones requiere cierto esfuerzo para encajar las pequeñas unidades en aquellas compuestas. La necesidad de hacer heavy refactors suele ser normal, debido a que al concentrarte en desarrollar la unidad pequeña no contemplas como será utilizado por las capas superiores. Aun así, no suele ser doloroso, porque cuentas con los test unitarios que te garantizan que tu refactor no rompe con la funcionalidad que tenías.

Este estilo de TDD, conocido como *Chicago/Detroit School*, era el único que conocía antes de leer [Growing Object-Oriented Software, Guided by Tests](https://www.amazon.com/Growing-Object-Oriented-Software-Guided-Tests/dp/0321503627), en el cual introducen la idea de un nuevo flow.

![London TDD flow](/assets/img/doubleloop.png)

Este estilo, también conocido como *London School*, conlleva un desarrollo *outside-in* o *top-botoom*. En este caso, y siguiendo el ejemplo anterior, primero se desarrollaría el controlador y luego el modelo y el algoritmo de ordenamiento. Ambos estilos tienen sus pros y sus contras (como todo en nuestro campo). 

Algunos comentan que **el estilo Chicago se enfoca en resultados, mientras que el estilo Londres se enfoca en comportamientos**. Esto debido a las consecuencias de iniciar desarrollando las bases o las capas más externas del sistema, respectivamente. En el primer caso, el desarrollo se inicia con pruebas que validen que los pequeños módulos retornen efectivamente los resultados esperados, avanzando luego con los módulos compuestos y repitiendo nuevamente el procedimiento. En el segundo caso, el desarrollo inicia descubriendo aquellas clases que deben colaborar para lograr el camino al resultado deseado. Esto genera clases generalmente con alta cohesión.

Para probar este approach decidí practicar el típico [kata del banco](https://github.com/JosemyDuarte/bank-kata/blob/master/README.md). Les dejo el enlace al [repo](https://github.com/JosemyDuarte/bank-kata) y podrán ver el historial de commits para observar como fue el avance. Personalmente, me sentí más comodo que con el estilo clásico (Chicago), aunque he de decir que sin el debido cuidado hubiera dejado sin probar la clase ```Clock``` o ```Console```, ya que sin haberlas implementado (y debido al mock) ya todos mis test estaban en verde, incluido el **acceptance test**. Por lo que no está demás mantener TODOs con todo aquello que queda pendiente por implementar, y evitar llevarse una sorpresa en producción. 
