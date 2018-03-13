---
layout: post
title: IaC com Troposphere e boto3
subtitle: Subindo uma infra na aws utilizando CloudFormation
date: 2018-01-01 21:00:00
image: /img/big-bang.jpg
share-img: /img/big-bang.jpg
tags: iac, devops, infragil, ferramentas
categories: iac
---

Hoje a criação de uma infra ágil é indispensável, pois assim aquela release que antes demorava 1 semana para ir pro ar, pode demorar alguns minutos. Neste post vamos subir uma simples configuração de infraestrutura na aws utilizando o troposphere, boto3 e o cloduformation, onde toda a infraestrutura estar em código  ou IaC(Infra as code).  

## Conhechendo as ferramentas

### Troposphere  
[Troposphere](https://github.com/cloudtools/troposphere) é uma ferramenta opensource, escrita em python, onde v cria um template para ser "inserido" no clodformation. O propio repositorio do troposphere tem alguns exemplos, bem simples de como utilizar.

### Boto3  

[Boto3](http://boto3.readthedocs.io/en/latest/index.html) é um SDK da aws para interagir entra seus scripts e os serviços da aws. Ele possue uma vassta documentação com inumeros serviçs que pode ser utilizados. Neste artigo iremos utilizar o componente [create_stack](http://boto3.readthedocs.io/en/latest/reference/services/cloudformation.html?highlight=create_stack#CloudFormation.Client.create_stack).


### CloudFormation  
O [CloudFormation](https://aws.amazon.com/cloudformation/) é uma das inumeras serviços da aws,com este serviço você consegue descrever todos os recursos da aws(vale salientar que o clodformation é free).


Mãos ao código...

Vamos criar uma infra com um Ec2+ELB+autoscaling, nada muito complexo, mas que ja ajudara a compreender o funcionamento das ferramentas.

Vale lembrar que estou utilizando o Debian 9

1 - Criação do ambiente
Sempre é bom você ter ambientes isolados para seus projetos, com isso um modulo não ingluencia no outro. Uma boa dia é utilizar o virtualenv, assim os projetos em python ficam isolados um dos outros.

```
$ apt-get install python-virtualenv
mkdir iac
cd iac
virtualenv -p python3 venv
source venv/bin/activate
```

Bom nesse trecho de codigo eu instalo o virtualenv(caso eu não tenha), após isso crio uma pasta para o projeto e depois instalo os pacotesz do virtualenv.

com o comando `$ source venv/bin/activate` eu inicializo o virtualenv e isolo meu ambiente, assim todos os pacotes que eu instalar agora, ficaram nesse ambiente. Caso queira sair, basta digitar `deactivate`.

2 - Instalação de pacotes

Sera necessario a instalação de alguns pacotes...

```
$ pip install awscli  
$ pip install troposphere   
$ pip install boto3
```

Após a instalação sera necessario adicionar as credencias da aws, digite:

```
aws configure

```
lembrese, caso vc tem mais projetos na sua maquina, voce podeter mais de uma configuração da aws, por exemplo nesse, precisamos de um usuario com acesso a ec2, loadbalance e autoscaling.



exemplo
