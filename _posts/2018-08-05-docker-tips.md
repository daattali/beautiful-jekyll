---
layout: post
title: Docker tips
subtitle: 5 dicas muito úteis para seu dia a dica com o docker.
date: 2018-08-05 13:00:00
image: /assets/img/docker-tips.png
share-img: /assets/img/docker-tips.png
tags: [docker, devops, dicas, ferramentas, tips, tricks]
categories: docker dicas
---

Você costumar subir muitos containers e tem dificuldade para realizar o gerenciamento deles? Ou então, está querendo aprender algumas dicas e truques para ficar mais expert em docker? Está no lugar certo, neste post irei descrever algumas dicas sobre containers, e como isso pode ajudar no seu dia a dia.

Cada vez mais o docker está se tornando algo rotineiro na vida das pessoas que transformam café em código, seja ele um dev python, java, go ou o pessoal de infra que precisa deixar o ambiente imutável, seja em desenvolvimento, stage, produção , QA ... Pensando em tudo isso, escrevo essas dicas que iram ser muito úteis para todos.

Se você caiu de paraquedas no blog, [aqui](https://adrianocanofre.github.io/tutorial/docker-basico/) eu comento alguns comandos básicos sobre docker.


## 1 - Cuide do seu storage

O repositório do  [docker hub](https://hub.docker.com/explore/) e extremamente grande, e contem inumeras imagens do seus mais diversos tipos, porem sempre é bom fazer uma limpeza, para resolver esse problema vai algumas dicas.


#### Removendo containers

Caso queira fazer uma limpa em todos os seus containers basta digitar:

 `$ docker rm $( docker ps -aq)`
 > Lembre-se esse comando apaga todos os containers

Caso queira, você pode optar por  salvar o container ao inicia lo com o  `docker run`.

`$docker run -it <img>  /bin/bash`

assim quando você sair do container ele automaticamente será removido.

#### Removendo imagens

Você pode também querer fazer uma limpa em todas suas imagens, para isso basta digitar;

`$ docker rmi $(docker images -q)`

> lembre-se que você vai apagar todas as suas imagens.

## 2 - Inspect

Não são todas as pessoas que tem uma memoria de elefante, que sabe todos os parametros passados ao iniciar o container. Para as pessoas normais que não tem uma boa memoria o docker tem um comando chamado `docker inspect` onde você pode ver o quanto de cpu e memoria tem o docker, ou foi mapeado os volumes e outras coisas bem legais, abaixo eu descrevo alguns exemplos de uso.

#### Limpando o log

`$ echo "" > $(docker inspect --format="{{.LogPath}}" <container_id>)`

#### IP

`$ docker inspect -f "{{ .NetworkSettings.IPAddress }}" <container_id>`

#### Log path

`$ docker inspect --format='{{.LogPath}}' <container_id>`

## 3 - Logs

Como visto anteriormente você pode limpar os logs quando ele ficar muito grande( ou limitar o tamanho do log). Porém caso queira ver os logs dos containers basta digitar:

`$ docker logs <container_id>`

Com esse comando, você vai conseguir ver todos os logs do container. Caso queira vocêpode acompanhar em tempo real os logs da sua aplicação, basta passar o parametro -f:

`$ docker logs <container_id> -f`

> Para sair do modo iterativo basta digitar ctrl + d.

## 4 Docker commit
Após você criar sua imagem, você pode fazer um commit dela para guardar em outro host ou até mesmo para deixar seu processo de build mais rápido, para isso basta criar a imagem e fazer um commit dela.

`$ docker commit -p <container_id> <nova_imagem>`

caso queira ainda é possivel salvar sua imagem em um .tar, para que possa usar em outro host, basta usar o parametro save.

`$ docker save -o minha_imagem.tar <container_id>`

Desta maneira você tem um backup da sua imagem, e pode usar em outros servidores.

## 5 Recursos

Um dos comandos do docker que foi e é muito útil para mim é o docker stats, com ele você acompanha em tempo real, os recursos que estão sendo usados, como  memoria, cpu, I/O de todos os containers ativos. para isso basta digitar

`$ docker stats `

> Lembrando que para sair do modo interativo, basta teclar ctrl + d.


## Dica extra

Você pode copiar arquivos para dentro do seu container facilmente, basta digitar:

`$ docker cp <arquivo> <container_id>:/path/`

Espero que esse post tenha sido útil para vocês e tenha ajudado a melhorar o seu dia a dia com o docker. Caso queira, deixe algum comentário, dúvidas ou compartilhe algum  conhecimento nos comentarios abaixo.

Abraços a todos, e por hoje é só!
