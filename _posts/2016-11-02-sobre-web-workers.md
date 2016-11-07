---
layout: post
title: Sobre Web Workers
subtitle: O Javascript multihilo
---

Si estás leyendo este post posiblemente no conoces los web workers, y por tanto habrá una pregunta en tu cabeza:

*¿Javascript no era monohilo?*
En realidad JS no es monohilo o multihilo. Solo es un lenguaje que históricamente ha usado un solo hilo. Esta posibilidad o limitación se la daba el navegador, que es el entorno donde era interpretado. Por supuesto el lenguaje no puede manejar más hilos de los que le proporciona dicho entorno. Quizá era complicado manejar el DOM con varios hilos, o quizá fuera una limitación sin una base lógica. En cualquier caso esa barrera se ha roto y ahora los navegadores permiten abrir múltiples hilos. No obstante, el DOM sigue manejándose solo desde un hilo (el principal de la página)

Dicho esto, continuemos.

## ¿Qué son los web workers?
Un web worker es un archivo de javascript que se ejecuta en segundo plano sin afectar el rendimiento de la página. Es independiente de la UI y funciona en otro hilo.

## ¿Son hilos reales o "falsos" como con el setTimeout?
Son hilos reales a nivel de sistema operativo.

## ¿Son lo mismo que los service workers?
No. Son conceptos similares, pero con alcances diferentes. Los service worker están pensados para realizar procesos continuamente en segundo plano. Para ello necesitan un hilo independiente del hilo principal de la aplicación, y eso es justo lo que podemos hacer con un web worker. Por ello los service worker usan un web worker internamente. 

## ¿Cómo se usan?
Supongamos que tenemos un proceso pesado. Normalmente llamaríamos al método y esperaríamos que tardara poco. Reduciríamos complejidad, haríamos asincrono todo lo que pudiéramos, y el resto quedaría en manos del ~~destino~~ navegador.

Sin embargo, con web workers podemos hacer lo siguiente

**En nuestro js principal**
{% highlight javascript linenos %}
function startProcess () {
  /* Creamos un web worker */
  var webWorker = new Worker('worker.js')

  /* Añadimos un listener que será llamado desde el worker. En nuestro ejemplo se llamará cuando haya acabado el proceso */
  webWorker.addEventListener('message', function (oEvent) {
    console.log(oEvent.data);
  })

  /* Llamamos al web worker */
  webWorker.postMessage('Datos');
}
{% endhighlight %}

**worker.js**
{% highlight javascript linenos %}

/* Aquí llegaremos al llamar al web worker con el postMessage */
onmessage = function (oEvent) {				

  /* Imaginemos que aquí llamamos a un proceso pesado. El oEvent.data contiene los datos que hemos enviado desde el postMessage */
  heavyProcess(oEvent.data);

  /* Mandamos un mensaje al hilo principal. */
  postMessage("Proceso terminado");
}
{% endhighlight %}

Lo que hacemos en este ejemplo es sencillo. He puesto comentarios para aclarar lo que ocurre en las diferentes líneas, pero el resumen sería el siguiente. Creamos un web worker desde el hilo principal. Importante: **solo el hilo principal puede modificar el DOM.**

Posteriormente llamamos al web worker. Cuando queramos y donde queramos. El web worker ejecutará la función *onmessage*. Para acabar, llamamos al hilo principal de nuevo con el método *postMessage*.

Como harás observado, el *postMessage* es la forma que tenemos de comunicarnos entre hilos. El evento *onMessage* existente tanto en el hilo principal como en el web worker recibirá los datos que enviemos en esa llamada en ambas direcciones.

Se pueden hacer llamadas con XMLHttpRequest, con la particularidad de que el responseXML y los atributos channel serán siempre null.

[Ejemplo](https://github.com/DavidColladoGitHub/blogExamples/tree/master/web%20workers) en GitHub

## Importando scripts
Podemos importar scripts con la función global *importScripts*. Si necesitaramos usar un archivo llamado *miLibreria.js* haríamos lo siguiente:

{% highlight javascript linenos %}
importScripts('miLibreria.js'); 
}
{% endhighlight %}

Si hubiera algún problema con la carga del scripts nos saltaría un error *NETWORK_ERROR*

## Contexto
Los web workers tienen un contexto propio (DedicatedWorkerGlobalScope). De hecho, no podemos usar el *window*. Para obtener el scope actual necesitaremos usar *self*

## ¿Cuándo debería usar web workers?
Para aligerar la carga en el hilo principal, principalmente en procesos pesados. Conversiones, recursividad... hay muchos escenarios.

## Limitaciones
Como cualquier tecnología web, solo podrá usarse en aquellos casos en que el navegador lo permita. Este [enlace](http://caniuse.com/#feat=webworkers) tiene la información por navegador.

## Otros datos de interés
* Es importante apuntar que **los valores que se pasan son una copia, no datos por referencia.** 
* Los *workers* pueden crear más *subworkers* o *workers anidados*. De momento esta característica solo está disponible en Firefox
* Podemos acceder al objeto navigator desde el worker. Este objeto contiene información interesante que nos permite, por ejemplo, identificar el navegador.
* Tanto *localStorage* como *sessionStorage* son indefinidos en los web workers. Para guardar información usando dichas APIs de HTML5 podemos enviar los datos al hilo principal mediante el *postMessage* para que los gestione.


## Referencias
MDN: <https://developer.mozilla.org/es/docs/Web/Guide/Performance/Usando_web_workers>
html5rocks: <https://www.html5rocks.com/en/tutorials/workers/basics/>
