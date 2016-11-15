---
layout: post
title: Midiendo tiempos en Javascript
---

Uno de los puntos a tener en cuenta en cualquier aplicación es el rendimiento. Por ello hay herramientas muy completas dedicadas específicamente a ésta tarea, como las que nos ofrece Google Chrome. Sin embargo lleva tiempo aprender a utilizarlas correctamente, y no todos los casos requieren un análisis exhaustivo.  Para dichas situaciones existen formas rápidas para medir tiempos, como las que vamos a ver a continuación.

## Mostrando tiempos en consola
Si lo único que necesitas es ver una medición rápida en consola, éste es el sistema más rápido. Solo tendrás que poner

```javascript
console.time("Etiqueta")
```

Al inicio del código a medir, y:

```javascript
console.timeEnd("Etiqueta")
```

Al final. Cuando se ejecute esta parte se mostrará el tiempo transcurrido desde el *console.time()*. La etiqueta es un identificador para la medición. Gracias a eso podemos hacer tantas mediciones a la vez como queramos, cambiando la etiqueta en cada una.

## Almacenando el valor en una variable
El método anterior es rápido y cómodo, pero tiene un problema. No se puede almacenar el resultado. Si quieres, por ejemplo, sacarlo a un log, necesitarás usar otro sistema.

```javascript
var inicio = Date.now();
...
...
var fin= Date.now();
var tiempo = (fin-inicio) + "ms";
```

El método clásico. No es el más fiable, pero funciona.

## Cuando la exactitud cuenta

Vamos con el último caso. Necesito guardarlo en una variable y además necesito un alto grado de exactitud.

```javascript
var inicio = window.performance.webkitNow();
...
var fin = window.performance.webkitNow();
var tiempo = (fin - inicio) + "ms"; 
```

