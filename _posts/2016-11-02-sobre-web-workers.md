---
layout: post
title: Sobre Web Workers
subtitle: O Javascript multihilo
---

Si estás leyendo este post posiblemente no conoces los web workers, y por tanto habrá una pregunta en tu cabeza:

*¿Javascript no era monohilo?*
En realidad JS no es monohilo o multihilo. Solo es un lenguaje que históricamente ha usado un solo hilo. Esta posibilidad o limitación se la daba el navegador, que es el entorno donde era interpretado. Por supuesto el lenguaje no puede manejar más hilos de los que le proporciona dicho entorno. Quizá era complicado manejar el DOM con varios hilos, o quizá fuera una limitación sin una base lógica. En cualquier caso esa barrera se ha roto y ahora los navegadores permiten abrir múltiples hilos. No obstante, el DOM sigue manejándose solo desde un hilo (el principal de la página)

Dicho esto, continuemos.

**Con texto en negrita**

## ¿Qué son los web workers?
Un web worker es un archivo de javascript que se ejecuta en segundo plano sin afectar el rendimiento de la página. Es independiente de la UI y funciona en otro hilo.

## ¿Son hilos reales o "falsos" como con el setTimeout?
Son hilos reales

## ¿Son lo mismo que los service workers?
No. Son conceptos similares, pero con alcances diferentes. Los service worker están pensados para realizar procesos continuamente en segundo plano. Para ello necesitan un hilo independiente del hilo principal de la aplicación, y eso es justo lo que podemos hacer con un web worker. Por ello los service worker usan un web worker internamente. 

## ¿Cómo se usan?

## Cuándo deben usarse

## Limitaciones

## Otros datos de interés
