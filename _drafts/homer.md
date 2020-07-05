---
layout: post
title: [HOMER]
subtitle: teste
image: /assets/img/docker-tips.png
share-img: /assets/img/docker-tips.png
tags: [devops, turotial]
categories: tutorial homer
---

Depois de algum tempo off(quase 2 anos), volto para tentar escrever alguns posts com uma frequência maior e com uma abordagem mais prática. Nesta série de artigos/post pretendo abordar a criação de uma aplicação para que possa gerenciar sua infraestrutura na [AWS] e também subir novas aplicações com maior facilidade e controle.

Bom, dividi a criação desse projeto em alguns artigos que são:

1. Iniciando um Projeto e criando sua infra.(Você esta aqui)
2. Reaproveitando código.
3. Deploy de aplicações.
4. Testes.
5. Monitoração usando GoLang.

## Requisitos básicos

Bom, antes de começar cada artigo vou fazer um check-list dos requisitos básicos para conseguir concluir com sucesso o tutorial. Bom nesta primeira etapa vamos utilizar basicamente 2 recursos que são, a [AWS](aonde criaremos nossa infra) e uma ferramenta de IaC, que para este tutorial, vou utilizar o terraform com a versão superior a 0.12.19.

Para criar a conta na [AWS] é simples, basta acessar esse [link][criando-conta-aws] e seguir os passos descritos. Com sua conta criada, você poderá usufruir de diversos recursos e "brincar" com os que existe na plataforma. Para saber os recursos free que você tem, basta acessar esse outro [link][aws-free]. Para utilizar o terraform, vamos precisar fazer a instalação dele, para realizar a instalação basta seguir os passos descritos abaixo:

```
$ wget https://releases.hashicorp.com/terraform/0.12.19/terraform_0.12.19_linux_amd64.zip
$ unzip terraform_0.12.19_linux_amd64.zip
$ mv terraform /usr/local/bin
$ terraform --version
```

> *Esses passos foram testados no MacOs & Linux(ubuntu\|Debian).

Outro recurso que precisamos é o __aws-cli__(_command line interface_), sua instalação é bem simples, basta seguir os seguintes passos:

```
$ pip install awscli --upgrade --user
$ aws --version
```

Para mais informações, basta acessas esse [link][aws-cli].


### Primeiros passos

A ideia dessa sequência de artigos surgiu com minha necessidade de aprender um pouco mais sobre algumas ferramentas e também a vontade de criar um projeto _open-source_ do zero que possa vir a ser utilizado por empresas que tem pouco domínio dessas ferramentas. Não vou entrar em detalhes sobre cada ferramenta que vou utilizar, nem tao pouco o porque estou utilizando ela e não a ferramenta x, y ou z. A ideia é mais passar conhecimento e dar algumas dicas ao decorrer dos artigos... Sem mais delongas, vamos la.

O projeto consiste na ideia de poder subir aplicações de maneira "fácil" e conseguir monitorara alguns recursos e realizar outras ações(que até esse momento não refleti sobre isso). Para isso vamos criar [VPC] com subnets publicas para nossos _load balance_ e subnets privadas onde será realizado o _deploy_ das aplicações.



1- Primeiro Apply

Bom, vamos começar a subir nossa infra, mas primeiro precisamos criar nosso usuario do terraform na aws.  O [IAM] nos permite criar e configurar com seguranças regras de acesso a aws, com isso é possivel adicionar novas regras, deletar regras antigas, ou ate mesmo revogar um token. Nâo vou entrar em detalhes de como o [IAM] funciona([esse tutorial pode le ajudar][IAM-Tutorial]), mas vamos precisar criar um usuario para o terraform e atribuir algumas permissoes para ele(vou mostrar o passo a passo a seguir).

Eu tenho o costume de segregar as policies, assim eu posso vir a usar elas no futuro, ou até mesmo remover ela com mais facilidade, para essa primeira etapa vamos criar uma policy para poder criar e deletar uma VPC.


IAM > Policy > Create Policy

<script src="https://gist.github.com/adrianocanofre/3bb9b1361a79cfb37bc798b8109b5153.js"></script>

Após ter criado nossa primeira policy, vamos criar o usuario, no momento em que voce estiver criando o usuário se atente em selecionar corretamente o tipo de acesso(Programmatic Acess), para isso vamos acessar novamente o [IAM], só que dessa vez, vou em " User > add user". Nesta parte vamos colocar o nome do usuario e escolher o typo de acesso, e adicionar algumas tags caso queira. No momento em que voce finalizar a criação, ira aparecer o *Access Key ID* e o *Secret access Key*, essas informações sâo importantes para que possamos fazer o terraform acessar a aws(Caso queira podem fazer o download delas e guardar em algum lugar).

Com o usuário criado e o *Access Key ID* e o *Secret access Key* em mâos, vamos realizar a configuração do aws cli, conforme descrito a seguir:

```
$ aws configure
AWS Access Key ID [None]: <valor_access_key>
AWS Secret Access Key [None]: <valor_secret_key>
Default region name [None]: us-east-1
Default output format [None]: json
```

Eu estou usando a região da virginia, mas você pode aplicar essas configurações em qualquer regiao.

[AWS]: https://aws.amazon.com
[aws-cli]: https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-install.html
[aws-free]: https://aws.amazon.com/pt/free/?all-free-tier.sort-by=item.additionalFields.SortRank&all-free-tier.sort-order=asc
[criando-conta-aws]: https://docs.aws.amazon.com/pt_br/rekognition/latest/dg/setting-up.html
[VPC]: https://aws.amazon.com/pt/vpc/
[IAM]: https://aws.amazon.com/pt/iam/
[IAM-Tutorial]: https://docs.aws.amazon.com/pt_br/IAM/latest/UserGuide/introduction.html
[tf-providers]: https://www.terraform.io/docs/providers/index.html
[Homer]: https://github.com/adrianocanofre/homer
