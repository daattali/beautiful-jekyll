---
layout: post
title: Docker básico
subtitle: uma baleia que está mudando o modo como fizemos deploy...
date: 2018-02-19 21:00:00
image: /assets/img/docker_logo.jpg
share-img: /assets/img/docker_logo.jpg
tags: [tutorial, docker, dicas]
categories: tutorial
---

Qual dev nunca proferiu as sabias palavras *"ahh, mas na minha maquina funciona."*, pois o docker veio para tentar diminuir isso. Meu objetivo não é falar sobre o baixo nível do docker, ou suas historias(vc pode ler aqui), mas sim mostrar como o docker funciona, e como ele é fod* para todos.


# O que é docker?
Bom, docker é uma ferramenta *open source* que facilita(e muito) o deploy de aplicações, onde tudo que voceêaltera nos containers se "perde", apos matar o mesmo. Caso queira se aprofundar, tem um tutorial bem interessante no site da [redHat](https://www.redhat.com/pt-br/topics/containers/what-is-docker).

![dockerxVms](/assets/img/docker_vm_container.png)  
# Primeiros Passos

O docker trabalha com conteiners, que é uma especie de virtualização do SO, onde nele você faz as alterações, teste entre outras coisas, e nada é alterado no seu SO.

## instalação
Abra o terminal do seu linux(estou usando o debian), e digite os seguintes comando.

```
$ curl -fsSL get.docker.com | sh
```

Após feita a instalação verifique a versão do docker.

![Docker](/assets/img/docker_version.png)

Bom, até aqui tudo facilzinho, vc instalou o docker e verificou sua versão, pois agora vamos rodas um "Hello-world"(sim, no docker tambem tem um hello world). Digite ai no seu console:
```
$ docker run hello-world
```

Se tudo ocorreu como planejado, ira aparecer uma mensagem de boas vindas do docker. Explicando um pouco o comando digitado, o run executa um novo container com base na imagem passada(no nosso caso foi o hello-world). Veja o como pode ser usado o docker run:

```
$ docker run [PARAMETROS] IMAGE [CMD] [ARG]
```
* parametros: aqui você pode colocar opções como nome, porta, volume, ip, hostname, entre outras do container([veja mais aqui](https://docs.docker.com/engine/reference/commandline/run/#options)).
Aqui vai alguns exemplos básicos de como usar:
```
$ sudo docker run -it ubuntu
```
Após voce dar um enter, a imagem do ubuntu existente no [docker hub](https://hub.docker.com/_/ubuntu/) sera baixa para seu computador, as opções -i, faz com q seja usado o modo interativo(mantem o modo STDIN aberto) e o -t

* cmd: aqui vcs podem colocar alguns comandos para ser executado no docker, como por exemplo:
```
$ sudo docker run -it debian bash
```
sera executado o bash do debian em modo interativo.

# Algumas dicas

O docker tem inumeros comandos, e pretendo no proximo post fazer um mais avançado sobre o "docker run", mas aqui segue algumas outras dicas que podem ser bem uteis.

`` $ docker ps  ``
  Listas todos os containes em execução.

`` $ docker images ``
  Mostra todas as imagens que voce tem no seu computados.

` $ docker ps -a`
  Lista os containes.

`$ dpcker rmi <imagemId>`
  Remove a imagem

`$ docker rm <containerId>`
  Remove o container


  Espero que tenha ajudado a torna a vida de todos mais fácil.
