---
layout: post
title: Docker run avançado
subtitle: muito alem de um simples docker run...[Parte 1]
date: 2018-02-26 22:00:00
image: /assets/img/docker_logo_2.png
share-img: /assets/img/docker_logo_2.png
tags: [tutorial, docker, dicas]
categories: tutorial docker
---

Existe algumas opções que você pode utilizar ao iniciar um container, e com essas opções você pode melhorar o gerenciamento do seus container. Este artigo vai ser dividido em 2 partes, para que possa ser melhor aproveitado.

Segue alguns opções bem uteis para ser usados na criação de containers.

**-p**
Esta opção é usada para adicionar uma porta de entrada e a porta que ira rodas dentro do *docker*, ex:

`$ docker run -p 80:3000 imagem`

Neste exemplo você pode acessar o *docker* externamente pela porta 80, mas dentro do container ele usara a porta 80.

**-\-restart**
Politicas de *restart* do container. Por padrão apos um container morrer, ele não é iniciado automaticamente, ex:

`$ docker run -d --restart=always debian`
* Desta maneira o *docker* sempre vai tentar dar um *restart* no container.

`$ docker run -d --restart=on-failure arch`

* Nesta opção o container ira reiniciar se a saída for um erro com código de saida diferente de 0.

**-\-name**
Quando você não passa o -\-name o propio *docker* adiciona um nome aleatoriamente para o seu container.

**-\-hostname**
Nesta opção você pode definir o hostname do container.

**-e**
Podemos  passar na criação do container alguma variável de ambiente, assim dentro do containers você pode utilizar a variável normalmente, ex:

`$ docker run -d -e CERVEJA='Vamos beber uma cerveja...' ubuntu`

Desta maneira você poderá usar  a variável CERVEJA dentro do seu container.

**-env-file**
Esta opção tem a mesma logica do -e, porem você passar um arquivo com varias variaveis.


**-\-rm**
Por padrão após você matar um container ele persistira no seu server, porem com essa opção ele sera removido automaticamente.


**-\-v**
Tudo que é executado e/ou salvo em um container é perdido apos você sair dele, porem com a opção -v, você pode mapear um volume externo, para salvar os dados do container, assim, ele não sera perdido após um restart. Ex:

`$ docker run -d -v /home/admin/bkp:/data/db  mongo`


### Network
O *docker* contem algumas opções de network, como:

**-\-mac-address**

Adiciona um  MAC address para o container.

`$ docker run -d --mac-address="12:72:ac:54:65:44" ubuntu`

O mac address passado no cli é setado no *docker*, você pode usar o *docker inspect* para verificar as informações de network.

**-\-dns**
adiciona um dns server.

**-\-ip**
Adiciona um ip expecifico ao container.


Neste artigo, falei sobre algumas opções que você pode usar no seu *docker* e algumas configurações básicas de rede. No próximo artigo, tratarei sobre recursos do container e mais alguns outros argumentos que podem vir a serem uteis.
