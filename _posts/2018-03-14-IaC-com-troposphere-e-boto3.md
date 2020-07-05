---
layout: post
title: IaC com Troposphere e boto3
subtitle: Subindo uma infra na aws utilizando CloudFormation
date: 2018-03-14 13:00:00
image: /assets/img/iac_icon.png
share-img: /assets/img/iac_icon.png
tags: [iac, devops, infragil, ferramentas]
categories: devops iac
---

Hoje a criação de uma infra ágil é indispensável, pois assim aquela release que antes demorava 1 semana para ir pro ar, pode demorar alguns minutos. Neste post vamos subir uma simples configuração de infraestrutura na aws utilizando o troposphere, boto3 e o CloudFormation, onde toda a infraestrutura estar em código  ou IaC(Infra as code).

## Conhecendo as ferramentas

Bom, irei detalhar brevemente cada ferramenta que foi utilizada para subir os serviços, vale também lembrar que as informações de IP, e chaves de ssh são fictícias, você precisa gerar as suas.


### Troposphere
[Troposphere](https://github.com/cloudtools/troposphere) é uma ferramenta opensource, escrita em python, onde v cria um template para ser "inserido" no CloudFormation. O propio repositório do troposphere tem alguns exemplos, bem simples de como utilizar.

### Boto3

[Boto3](http://boto3.readthedocs.io/en/latest/index.html) é um SDK da aws para interagir entra seus scripts e os serviços da aws. Ele contem uma vasta documentação com inúmeros serviços que pode ser utilizados. Neste artigo iremos utilizar o componente [create_stack](http://boto3.readthedocs.io/en/latest/reference/services/cloudformation.html?highlight=create_stack#CloudFormation.Client.create_stack).


### CloudFormation
O [CloudFormation](https://aws.amazon.com/cloudformation/) é uma das inúmeras serviços da aws,com este serviço você consegue descrever todos os recursos da aws(vale salientar que o CloudFormation é free).


Mãos ao código...

Vamos criar uma infra com um Ec2 com um security group vinculado a ele, nada muito complexo, mas que já ajudara a compreender o funcionamento das ferramentas.

Vale lembrar que estou utilizando o Debian 9.

**1 - Criação do ambiente**
Sempre é bom você ter ambientes isolados para seus projetos, com isso um modulo não influencia no outro. Uma boa dia é utilizar o virtualenv, assim os projetos em python ficam isolados um dos outros.

```
$ apt-get install python-virtualenv
$ mkdir iac
$ cd iac
$ virtualenv -p python3 venv
$ source venv/bin/activate
```

Bom nesse trecho de código eu instalo o virtualenv(caso eu não tenha), após isso crio uma pasta para o projeto e depois instalo os pacotes do virtualenv.

Com o comando `$ source venv/bin/activate` eu inicializo o virtualenv e isolo meu ambiente, assim todos os pacotes que eu instalar agora, ficaram nesse ambiente. Caso queira sair, basta digitar `deactivate`.

**2 - Instalação de pacotes**

Sera necessário a instalação de alguns pacotes...

```
$ pip install awscli
$ pip install troposphere
$ pip install boto3
```

Após a instalação sera necessário adicionar as credencias da aws, digite:

```
$ aws configure
```

Lembre-se, caso você tem mais projetos na sua maquina, você podeter mais de uma configuração da aws, por exemplo nesse, precisamos de um usuário com acesso a ec2, loadbalance e autoscaling.

**3 - Criando seu primeiro Ec2**
Agora vamos criar um arquivo chamado `exemplo1.py`, onde iremos criar primeiramente um ec2, para ver como funciona as ferramentas. Neste exemplo estarei usando a região *us-east-1*. Vale lembra que cada região tem sua AMI propia, ou seja o ID de uma AMI não vale para outra região. [Aqui](https://cloud-images.ubuntu.com/locator/ec2/) você pode ver todos os IDs das amis do ubuntu. Bom, vamos la...

exemplo.py
```
from troposphere import Template
from troposphere.ec2 import Instance

def ec2():
    return Instance(
        "ec2",
        ImageId='ami-43a15f3e',
        InstanceType="t1.micro",
        KeyName='keyTeste',
        SecurityGroups=["default"]
    )

def template():
    t = Template()
    t.add_resource(ec2())
    return t


if __name__ == '__main__':

    print(template().to_json())
```

Salve e execute `$ python exemplo.py` e a saída no terminal sera algo como:

![exemplo](/assets/img/troposphere1.png)

Como podemos ver na saída do terminal o troposphere criou um template que você pode adicionar manualmente no CloudFormation, porem agora vamos editar esse aquivo e adicionar o boto3, para que ele crie essa stack no CloudFormation.


```
from troposphere import Template
from troposphere.ec2 import Instance
from boto3 import client
import botocore


def ec2():
    ...
    ...

def template():
    ...
    ...


def deploy():
    cf = client('cloudformation', region_name='us-east-1')
    try:
        cf.create_stack(StackName='Bacon', TemplateBody=template_it().to_json(),
                        Capabilities=['CAPABILITY_IAM'])
    except botocore.exceptions.ClientError as e:
        print(e)


if __name__ == '__main__':

    deploy()
```
Veja que adicionamos uma nova função, ela que se encarregara de mandar o template para o CloudFormation.Se tudo ocorreu como planejado, nesse momento está sendo criado sua stack no CloudFormation, e se tudo tiver dado errado, alguma mensagem ira aparecer no seu terminal.

Lembre-se cada CloudFormation é único, então tem que ter nomes diferentes.


**4 - Security Group**

Bom agora que já subimos nossa stack, vamos criar um security group para ela. Nesse exemplo, vamos liberar a porta 80 para todos e a 22 para o meu ip. Para verificar seu ip basta [ver aqui](https://api.ipify.org/)


```
from troposphere import Template, Ref
...

def ec2():
    return Instance(
        "ec2",
        ImageId='ami-916f59f4',
        InstanceType="t2.micro",
        KeyName='keyTeste',
        SecurityGroups=[Ref(security_group_ec2())]
    )


def security_group_ec2():

    return SecurityGroup(
        'Ec2',
        GroupName='Ec2_Bacon',
        GroupDescription="Security group for Ec2",
        SecurityGroupIngress=[
            SecurityGroupRule(
                IpProtocol='tcp',
                FromPort=22,
                ToPort=22,
                CidrIp='1.1.1.1/32',
                Description='ssh port'
            ),SecurityGroupRule(
                IpProtocol='tcp',
                FromPort=80,
                ToPort=80,
                CidrIp='0.0.0.0/0',
                Description='Porta 80'
            )
        ]
    )


def template():
    ...
    t.add_resource(security_group_ec2())
    ...

```

Bom, vamos explicar o que foi feito. Foi adicionado  o SG e feito sua referencia na criação do Ec2, foi adicionado um **KeyName** e **CidrIp** fictícios.

**5 - Bônus**
Caso queira deletar a stack no seu script, basta adicionar esse trecho do código.


```

def delete_it(suffix, REGION):
    cf = client('cloudformation', region_name='us-east-2')
    cf.delete_stack(StackName='Bacon')
```

Com essa função você consegue deletar a stack no CloudFormation.

[github do projeto](https://github.com/adrianocanofre/iac/tree/master/troposphere)
[exemplos do troposphere](https://github.com/cloudtools/troposphere/tree/master/examples)
