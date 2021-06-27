---
layout: post
title: Homer!!! Iniciando nosso projeto
subtitle: Vamos criar um projeto do zero que abrange algumas ferramentas e trabalhos do dia a dia.
date: 2021-06-27 15:00:00
last-updated: 2021-06-27 15:00:00
image: /assets/img/infinity_homer.jpg
share-img: /assets/img/infinity_homer.jpg
tags: [devops, turotial, homer, terraform, aws]
categories: tutorial homer
---

Logo que comecei meus primeiros passos com *terraform*, achei muito interessante
a ideia de poder criar recursos escrevendo algumas linhas de códigos, porem na
época a grande maioria dos tutorias explicava somente algumas partes de como usar,
e até então, não tinha achado algum tutorial mostrando a criação de algum projeto,
modulo, ou *pipiline* com o *terraform*, foi então que surgiu a ideia de escrever
essa sequencia de 6 *posts* mostrando a criação de uma aplicação, e como podemos
usar no nosso dia a dia.

Um outro ponto que me motivou a iniciar essa sequencia de artigos, era que queria
aprender algumas novas ferramentas e criar algum projeto de ponta a ponta que
ajudasse quem está começando a se familiarizar com *terraform*, *ci/cd*, *aws*,
*docker*, etc.

Esse primeiro *post* vai ser dedicado mais a configuração do nossa maquina e falar
algumas coisas básicas que acho muito importante sobre como funciona e como vamos
criar nosso projeto. Dividi a criação desse projeto em 6 partes que são:

1. The Big Bang
2. O Projeto Parte 1.
3. O Projeto Parte 2.
4. Boas práticas
5. Deploy de aplicações.
6. Automatizando o processo


### Requisitos básicos

Bom, antes de começar cada artigo vou fazer um *checklist* dos requisitos básicos
para conseguir concluir com sucesso o tutorial. Nesta primeira etapa vamos utilizar
basicamente 3 recursos, que são:

- Conta na aws
- aws-cli
- Terraform

**Conta na AWS**

Para criar a conta na [AWS] é simples, basta acessar esse [link][criando-conta-aws]
e seguir os passos descritos. Com sua conta criada, você poderá utilizar seus diversos
recursos e "brincar" com os que existe na plataforma(Cuidado com deus gastos).
Para saber os recursos *free* que você tem, basta acessar esse outro [link][aws-free].

**aws-cli**


Outro recurso que precisamos é o **aws-cli**(*command line interface*), sua instalação
é bem simples, basta seguir os seguintes passos:

```shell
$ pip install awscli --upgrade --user
$ aws --version
```

Para mais informações, basta acessas esse [link][aws-cli].

**Terraform**

O ultimo recurso que precisamos é o [Terraform], que basicamente é uma ferramenta
*open-source* que vai nos ajudar a provisionar e versionar nossa infraestrutura.
Sua instalação é bem simples, e só vamos precisar seguir os passos descritos abaixo:

```
$ wget https://releases.hashicorp.com/terraform/1.0.0/terraform_1.0.0_linux_amd64.zip
$ unzip terraform_1.0.0_linux_amd64.zip
$ mv terraform /usr/local/bin
$ terraform version
```

> *Esses passos foram testados no MacOs & Linux(ubuntu\|Debian).

## The Big Bang

Agora com nossos pré-requisitos feitos, vamos fazer uma validação para verificar
se está tudo funcionando como esperávamos. A primeira coisa que vamos precisar
fazer são criar o usuário que vamos utilizar no nosso projeto(Não recomendado
utilizar o usuário *root*). Para criar um usuário basta para nosso projeto, basta
seguir esse [tutorial][aws-iam-user], nas ultimas etapas você precisara adicionar
alguma *policies*, para que possamos ter permissão de criar nossa infraestrutura.
Você tem algumas opções para esse passo, como adicionar uma *policy* de *PowerUserAccess*
que le dara permissão para criar tudo na **aws**(grandes poderes, grandes responsabilidades).
Outro passo é ir adicionando as policies existentes na *aws* conforme for precisando,
assim você consegue segregar e dar permissão para o usuário criado, usar somente
o que for liberado. Caso queira saber mais como o [IAM] funciona [esse tutorial pode lê ajudar][IAM-Tutorial].

Um terceiro modo(e é o que eu mais uso) é criar uma *policy* nova e ir adicionando
as permissões que você precisa, assim você consegue segregar bastante as permissões
que o usuário vai precisar. Abaixo segue **JSON** com todas as permissões que
vamos precisar para provisionar nossa infraestrutura.

<script src="https://gist.github.com/adrianocanofre/1f113838303b1018fcd209b2baac805f.js"></script>

> Essa *policy* contem as regras que vamos precisar para esse post, caso queira,
> você pode ir adicionando mais permissões assim que forem sendo necessitadas.

Após ter criado nosso usuário e ter atachado alguma *policy* e terminado o tutorial
de criação de usuário, vamos fazer o download das credencias e configurar nosso *cli*
para que possamos usar junto com o *terraform*. Para isso, basta ter em mãos os
valores do *Access Key ID* e o *Secret access Key* e realizar a configuração do
[AWS] *cli*, conforme descrito a seguir:

```shell
$ aws configure
AWS Access Key ID [None]: <valor_access_key>
AWS Secret Access Key [None]: <valor_secret_key>
Default region name [None]: us-east-1
Default output format [None]: json
```

> Eu estou usando a região da Virgínia, mas você pode aplicar essas configurações em qualquer região.



### First commit

Bom, se tudo foi instalado e configurado corretamente(espero que não tenha esquecido
nada), vamos realizar nosso primeiro *deploy*( básico, mas honesto).

Antes de definir nosso escopo, de como vamos criar todo nosso código, vamos fazer
pequeno teste e criar um ec2 na *aws*, e para isso vamos criar uma pasta e um arquivo
chamado *main.tf* e abrir com seu editor preferido para adicionar nosso código.


```shell
$ mkdir homer
$ touch homer/maint.tf
$ cd homer
$ vi maint.tf
```

Com o arquivo aberto, vamos adicionar esse trecho de código:

```terraform
provider "aws" {
  region                  = "us-east-1"
  shared_credentials_file = "$HOME/.aws/credentials"
}

data "aws_ami" "ubuntu" {
  most_recent = true

  filter {
    name   = "name"
    values = ["ubuntu/images/hvm-ssd/ubuntu-focal-20.04-amd64-server-*"]
  }

  filter {
    name   = "virtualization-type"
    values = ["hvm"]
  }

  owners = ["099720109477"] # Canonical
}

resource "aws_instance" "first_commit" {
  ami           = data.aws_ami.ubuntu.id
  instance_type = "t3.micro"
  key_name      = "homer"
  tags = {
    Name = "teste-homer"
  }
}
```

O primeiro bloco de notas, faz referencia a qual *provider* do *terraform* vamos
utilizar, nesse caso a aws e passo algumas informações como a região que vou
quer criar e também meu arquivo de credenciais, caso queira passar outras informações,
nesse [link][AWS-Provider] você consegue ver mais detalhado o que é possível usar.

No segundo bloco utilizo um recurso chamado *Data Source*(nos próximos capítulos
vou detalhar mais sobre isso), nele passo algumas informações, como qual tipo de
**ami** vou utilizar, seu **owner**. Esse trecho nos ajuda a deixar nosso código
mais dinâmico, e podemos usar ele em outras regiões.

No ultimo bloco escrevemos a parte em que cria propriamente o nosso Ec2 na aws,
nela passo informações como a **ami** que vou utilizar, tipo de **instance_type**,
e a **key_name** que vou vincular a minha ec2(nesse caso é uma key já existente
na aws), e por ultimo passo um **name** para ela.

Feito toda essa configuração, e com o arquivo devidamente salvo, vamos inicializar o
processo de criação utilizando o terraform. Esse processo é dividido em 3 etapas, que
são, **Init**, **Plan** e **Apply**.

*Init*

Nesse passo o terraform faz a inicialização de seu **backend** e **provider**,
para inicializar ele, digite:

```shell
$ terraform init
```

Ele pode levar alguns segundos, mas depois de inicializado, seu output será algo como:

```shell
Terraform has been successfully initialized!
```

Nesse passo o **terraform** foi inicializado com sucesso e podemos dar continuidade
no nosso artigo.

**Plan**

Agora é a hora da verdade, nesse momento vamos verificar se escrevemos tudo de maneira
correta, e passamos todas as informações que o **terraform** precisa, para isso basta
digitar o seguinte comando:

```shell
$ terraform plan
```

Se tudo ocorreu conforma o planejado, seu output deve ser algo como:

```shell
Plan: 1 to add, 0 to change, 0 to destroy.
```

No output tem mais informações como block device, network, ebs, etc. Nesse momento
não vamos entrar em detalhes sobre isso, mas como não estamos passando nenhuma
informação extra, a instância ira ser criada com os recursos padrão da aws.

**Apply**

Agora que realizamos nosso **plan** com sucesso e conseguimos verificar tudo que vai
ser adicionad0, vamos executar e criar nosso recurso na aws, para isso, execute
o seguinte comando:

```shell
$ terraform apply
```

Nesse comando, vamos precisar digitar "yes"  quando for pedido, para confirmar que
queremos criar nosso ec2. Ele demorara menos de 1 minuto para executar o **apply**,
e seu output será algo como:

```shell
aws_instance.first_commit: Creating...
aws_instance.first_commit: Still creating... [10s elapsed]
aws_instance.first_commit: Creation complete after 19s [id=i-02afd14d353f7b912]

Apply complete! Resources: 1 added, 0 changed, 0 destroyed.
```

Para verificar o ec2 sendo inicializado, basta verificar no console da [aws][aws-console].

**Destroy**

Agora voce precisa destruir seus recursos criados, para não ficar nada nos nossos
*providers* que não estamos utilizando, para isso, basta digitar:

```shell
$ terraform destroy
```

Esse comando irar destruir com tudo que foi criado e está salvo no seu *.tfstate*,
seu output será algo como:

```
aws_instance.first_commit: Destroying... [id=i-06f567a96370f0aac]
aws_instance.first_commit: Still destroying... [id=i-06f567a96370f0aac, 10s elapsed]
aws_instance.first_commit: Still destroying... [id=i-06f567a96370f0aac, 20s elapsed]
aws_instance.first_commit: Still destroying... [id=i-06f567a96370f0aac, 30s elapsed]
aws_instance.first_commit: Destruction complete after 34s

Destroy complete! Resources: 1 destroyed.
```

## Houston, We have a problem!!!

Antes de começar a falar do escopo do nosso projeto e como vamos trabalhar nele,
vale a pena falar um pouco sobre como o *terraform* trabalha e alguns problemas que
possamos ter no futuro e como evitar alguns(sempre vai ter uma nova forma de fazer).

**tfsate**

Toda vez que você executar os comando *plan*, *apply* e *destroy* o *terraform* precisa verificar
o seu *tfstate*, que basicamente serve para guardar informações do estado da sua
infraestrutura, e por isso acaba se tornando um arquivo que requer um pouco mais de
cuidado, visto que ele guarda todo a informação do estado atual dos nossos recursos.

Nesse momento nosso *tfstate* está local(na nossa maquina), o que é um pouco inseguro,
visto que só você será o detentor dessa informação e com isso ninguém do seu time
vai conseguir subir novas *features*, outro ponto e também é um local onde posso vir
a perder ele(rm -rf *). Para contornar esse problema temos o [terraform beckend][tf-beckend]
onde você configurar onde vai guardar eles, assim você consegue visionar com uma
maior facilidade e os demais membros da equipe, vão conseguir usar o *.tfstate*.

Um exemplo básico de *beckend*, seria:

```terraform
terraform {
  backend "s3" {
    bucket = "homer"
    key    = "terraform/project/homer/terraform.tfstate"
    region = "us-east-1"
  }
}
```

Nesse caso, toda ver que for dar um plan, vou fazer uma consulta no meu tfstate e
verificar o que tem de diferente, e após fazer o apply, vou atualizar meu tfstate
com as novas informações.

**provider**

O terraform possui muitos [providers][providers] que voce pode utilizar no seu projeto, e os
mesmo são atualizados frequentemente, com isso sempre é bom manter eles com a versâo
que é compataivel, como no exemplo a seguir:

```
terraform {
  required_providers {
    cloudflare = {
      source = "cloudflare/cloudflare"
      version = "2.22.0"
    }
  }
}
```

Caso não tenha o *provider* para o que você precisa, poderemos criar o nosso
propio *provider*.

## Primeiro Escopo

Para finalizar essa primeira parte, vamos falar um pouco sobre como vai ser o escopo
do nosso projeto, e como vamos trabalhar para que ele saia do papel.

> Como comentei, a ideia dessa sequencia de artigos é criar um projeto que ajude
> desde dev que não sabe nada de terraform, até aquele que já provisionou sua
> infraestrutura, e é por isso que essa primeira parte foi um pouco mais básica.


Nesse primeiro momento, a ideia desse projeto é criar uma código que possamos utilizar
para subir nossos recursos tanto na aws, quanto em outro *provider* que possamos vir a utilizar.

Nossos projeto utilizara recursos independentes, ou compartilhados, como *RDS*,
*S3*, *Cache*, *SQS*, *SNS*, etc.

A ideia no geral é que quando um dev faça um *commit* no repositório do seu projeto
**XPTO**( vou usar o github) o mesmo possua uma pipeline que possibilite a atualização
automática dessa nova versão no nosso projeto, outra ideia é que possamos subir
nossa infra utilizando uma pipeline padrão, sem precisar rodar nada local.

No próximo capitulo, vamos escreve bem mais código e adentrar nesse fantástico
mundo do *terraform*, e começar definitivamente a criar nosso projeto.


Até mais!!

[providers]: https://registry.terraform.io/browse/providers
[AWS]: https://aws.amazon.com
[aws-console]: https://aws.amazon.com/pt/console/
[aws-cli]: https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-install.html
[aws-iam-user]: https://docs.aws.amazon.com/pt_br/IAM/latest/UserGuide/id_users_create.html
[aws-free]: https://aws.amazon.com/pt/free/?all-free-tier.sort-by=item.additionalFields.SortRank&all-free-tier.sort-order=asc
[criando-conta-aws]: https://docs.aws.amazon.com/pt_br/rekognition/latest/dg/setting-up.html
[VPC]: https://aws.amazon.com/pt/vpc/
[IAM]: https://aws.amazon.com/pt/iam/
[IAM-Tutorial]: https://docs.aws.amazon.com/pt_br/IAM/latest/UserGuide/introduction.html
[tf-providers]: https://www.terraform.io/docs/providers/index.html
[Terraform]: https://www.terraform.io
[Homer]: https://github.com/adrianocanofre/homer
[AWS-Provider]: https://registry.terraform.io/providers/hashicorp/aws/latest/docs/resources/instance
[tf-beckend]: https://www.terraform.io/docs/language/settings/backends/index.html
