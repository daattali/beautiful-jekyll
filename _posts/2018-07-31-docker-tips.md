---
layout: post
title: Docker tips
subtitle: 5 dicas muito uteis para seu dia a dica com o docker.
date: 2018-07-31 13:00:00
image: /img/iac_icon.png
share-img: /img/iac_icon.png
tags: docker, devops, dicas, ferramentas, tips, tricks
categories: docker dicas
---

Você costumar subir muitos containers e ter dificuldade para fazer seu gerenciamento? Ou então, está querendo aprender algumas dicas e truques para ficar mais expert em docker? Está no lugar certo, neste post irei detalhar algumas dicas sobre containers, e como isso pode ajudar no seu dia a dia.  

Cada vez mais o docker está se tornando algo rotineiro na vida das pessoas que transformam café em código, seja ele um dev python, java, go ou o pessoal de infra que precisa deixar o ambiente imutável, seja em desenvolvimento, stage, produção , QA ... Pensando em tudo isso, escrevo essas dicas que iram ser muito uteis para todos.  

Se você caiu de paraquedas no blog, [aqui](http://localhost), eu comento alguns comando basicos sobre docker.  


## 1 - Cuide do seu storage  

Se você é como eu, que ao descobri o docker ficou surpreso com a quantidade de imagens no docker hub e passou o dia digitando docker  pulll <...> e criando containers para brincar, você provavelmente está com seu hd lotado (de imagens, containers e volumes) e provavelmente não ocupe nem 10% delas. Caso queira remover elas uma por uma, você levara alguns minutos(eu demorei mais de 30 minutos para remover as 120 e poucas imagens que baixei) mas podemos fazer isso de uma maineira mais rápida e fácil.  


Caso queira ser drastico e remover todos os containers do seu hd, basta digitar;  

 `$ docker rm $( docker ps -aq)`  

Caso queira, você pode não salvar o container ao dar um `docker run` na imagem, para isso basta digitar;  

`$docker run -it <img>  /bin/bash`

assim quando vc sair do container ele automaticamente será removido.

Vocá pode tambem querer fazer uma limpa em todas suas imagens, para isso basta digitar;  

`$ docker rmi $(docker images -q)`

OBS: lembrese que você vai apagar todas as suas imagens.

## 2 - inspect

Não são todas as pessoas que tem uma memoria de elefante, que sabe todos os parametros passados ao iniciar o container. Para as pessoas normais que não tem uma boa memoria o docker tem um comando chamado docker inspect onde você pode ver o quanto de cpu e memoria tem o docker, ou foi mapeado os volumes e outras coisas bem legais, abaixo eu descrevo alguns exemplos de uso

Limpando o log
`$ echo "" > $(docker inspect --format='{{.LogPath}}' <container_id>)`

IP
`$ docker inspect -f "{{ .NetworkSettings.IPAddress }}" <container_id>`

Log path
`$ docker inspect --format='{{.LogPath}}' <container_id>`
## 3 - Logs e mais logs   

O que seria da TI sem os logs para debugar aquele parada aleatoria no servidor ou entao ver os erros da aplicações. O comando docker logs faz exatamente isso, digitando;  

`$ docker logs <container_id>`  

você vai conseguir ver todos os logs do container, mas caso queira acompanhar em tempo real você pode passar o parametro -f (para sair do modo iterativo basta digitar ctrl + d);

`$ docker logs <container_id> -f`

## 4 Docker commit
Apos você criar sua imagem, você pode fazer um commit dela para guardar em outro host ou até mesmo para deixar seu processo de build mais rápido, para isso basta criar a imagem e fazer um commit dela.

`$ docker commit -p <container_id> <nova_imagem>`

caso queira ainda é possivel salvar sua imagem em um .tar, para que possa usar em outro host, basta usar o parametro save.

`$ docker save -o minha_imagem.tar <container_id>`

desta maneira você tem um backup da sua imagem, e pode usar em outros servidores.

## 5 Recursos

Um dos comandos do docker que foi e é muito útil para mim é o docker stats, com ele você acompanha em tempo real, os recursos que estão sendo usados, como  memoria, cpu, I/O de todos os containers ativos. para isso basta digitar

`$ docker stats `

lembrando que para sair do modo interativo, basta teclar ctrl + d.



## Dica extra

Você pode copiar arquivos para dentro do seu container facilmente, basta digitar;

`$ docker cp <arquivo> <container_id>:/path/`
