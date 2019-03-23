---
layout: post
title: Usar o PiHole como servidor DNS com o Smart router da Vodafone
categories: [raspberry]
tags: [raspberry, pihole, vodafone]
---

O router actualmente fornecido pela Vodafone, Smart Router 2.0, não permite configurar manualmente os servidores DNS anunciados por DHCP. Ao tentar alterar os servidores DNS recebemos um aviso a informar que a BOX IPTV vai deixar de funcionar.
Este guia resolve esse problema criando um servidor DNS e DHCP local usando um Raspberry Pi.

Além de alterar os servidores DNS este guia tem também como objectivo instalar e configurar o PiHole de forma a poder ser usado como servidor DNS e DHCP pelos equipamentos ligados ao Smart Router 2.0. Apesar deste guia usar o raspberry PI 3B+ como referência é válido para qualquer modelo, desde que usem o Raspbian.

O [PiHole](https://pi-hole.net/) é uma aplicação open source que tem como objectivo bloquear anúncios e mecanismos de tracking na internet. Para cumprir este objectivo actua como um servidor DNS dentro da nossa rede.
Após instalado e configurado vai ser responsável por resolver os nomes dos domínios em endereços IP, caso estes domínios pertençam a uma lista negra de domínios usados para publicidade ou tracking serão barrados.


Neste guia vamos implementar as seguintes funcionalidades:

1. Usar o PiHole como um DNS sinkhole para barrar todo o tráfego publicitário e de tracking
2. Usar o raspberry como servidor DHCP
3. Manter o funcionamento da box IPTV da Vodafone


## Pré Requisitos

Apesar deste guia tentar ser o mais simples possível, é necessário ter um conhecimento dos básicos de Linux. Criar/editar ficheiros no terminal (ex usando nano ou vi) deve ser suficiente.

Sendo que a instalação vai ser feita remotamente no raspberry será necessário aceder ao raspberry por ssh.

## Material necessário.

![pihole vodafone router 2](/assets/posts/pihole-vodafone/vodafone_router_raspberry.jpg)

Para este guia irei usar um Raspberry PI 1B. Apesar de ter usado este modelo, este guia é válido para qualquer Raspberry a correr Raspbian. Sendo que este Raspberry já é o modelo mais antigo, com um processador de 700MHz e 512MB de ram, é esperado que esta solução corra também nas novos modelos.

Não vamos ter ambiente gráfico no raspbian por isso terão de ter um cliente ssh instalado na vossa máquina. Caso usem Linux ou MacOs não é necessário fazer nada, para o Windows podem usar o [Putty](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).

O router Vodafone é usado é o Smart Router 2.0 (Huawei HG8247W). Não testei para o 1.0 mas os passos devem ser semelhantes.


## Instalação Raspbian

O primeiro passo é obter a imagem mais recente do raspbian. Podem fazer download do site [oficial](https://www.raspberrypi.org/downloads/raspbian/). A versão que vamos usar é a Raspbian Stretch Lite, sem ambiente gráfico.

O próximo passo é copiar a imagem para o SDCard, para isto recomendo o [etcher](https://www.balena.io/etcher/). Ou podem usar o [dd](https://ss64.com/bash/dd.html).

![etcher raspbian](/assets/posts/pihole-vodafone/etcher.png)

Como não temos ambiente gráfico vamos fazer a instalação remotamente por ssh. Para activar o ssh é necessário criar um ficheiro "ssh" na raiz do cartão.
Para isto basta montar o cartão SD novamente (tira e volta a colocar ou “mount”), e na raiz criar um ficheiro vazio chamado “ssh”.

    echo "" > /Volumes/{nome_cartao}/ssh
    # Normalmente o cartão está em /Volumes/boot

O cartão sd está pronto, podem fazer unmount e coloca-lo no raspberry.


## Instalar o PiHole

Os passos seguintes são efectuados no raspberry, para isto é necessário ligar-nos ao raspberry por ssh.
Para efectuar a ligação é necessário saber o ip. A maneira mais fácil é aceder à interface de gestão do router da Vodafone e obter o IP que foi atribuído por DHCP.

* Aceder a http://192.168.1.1/index.asp
* Usar as credenciais vodafone:PPyjj246
* Clicar em "Dispositivos com fios"

O Ip do raspberry irá aparecer na lista de dispositivos conectados.

![vodafone router gestao](/assets/posts/pihole-vodafone/router_vodafone.png)

Neste caso o IP atribuído ao raspberry foi o 192.168.1.84. Vamos então efectuar a ligação ssh:

    ssh pi@192.168.1.84

Vai ser pedida a password, a password incial é "raspberry".
Após estarmos ligados vamos alterar a password para algo mais seguro. Para isso corram o seguinte comando:

    passwd

Primeiro introduzam a password antiga "raspberry" e depois a nova password duas vezes.

E por ultimo um update ao sistema:

    sudo apt-get update && sudo apt-get upgrade

O output dos comandos anteriores será semelhante ao seguinte:
![first ssh](/assets/posts/pihole-vodafone/first_ssh.png)

## Instalar o PiHole

    curl -sSL https://install.pi-hole.net > pihole.sh
    chmod +x pihole.sh
    sudo ./pihole.sh

Estes comandos vão iniciar o processo de instalação. O tempo de instalação varia consoante o modelo do raspberry que estão a usar, na versão 1B demora alguns minutos.
Durante a instalação será necessário responder às seguintes questões:

**Passo 1** - Escolha dos servidores DNS upstream.
Estes são os servidores DNS que o PiHole vai usar para resolver as domínios que não estejam em nenhuma lista negra. Recomendo usarem o Google ou OpenDns.
![pihole escolha servidor dns](/assets/posts/pihole-vodafone/pihole_install_1.png)

**Passo 2** - Escolha das listas negras de domínios.
Estas são as listas que vão ser usadas para validar se um determinado dominio deve ser barrado por conter publicidade ou mecanismos de tracking. Podem usar as selecionadas por omissão.
![pihole escolha listas negras](/assets/posts/pihole-vodafone/pihole_install_2.png)

**Passo 3** - Escolha dos protocolos de rede.
Usar os valores por omissão(IPv4 + IPv6).
![pihole escolha protocolos de rede](/assets/posts/pihole-vodafone/pihole_install_3.png)

**Passo 4** - Confirmar endereços IP.
Confirmar o endereço IP do raspberry e do gateway(router Vodafone).
![pihole confirmar ip](/assets/posts/pihole-vodafone/pihole_install_4.png)

**Passo 5** - Activar interface de gestão.
Usar o valor por omissão(On). A interface de gestão vai permitir gerir o PiHole mais facilmente através de uma página web.
![pihole activar interface de gestão](/assets/posts/pihole-vodafone/pihole_install_5.png)


**Passo 6** - Instalar servidor web.
Usar o valor por omissão(On).
![pihole instalar web server](/assets/posts/pihole-vodafone/pihole_install_6.png)


**Passo 7** - Activar log de queries.
Usar o valor por omissão(On). Irá permitir gerar estatisticas sobre os domínios pedidos.
![pihole activar log queries](/assets/posts/pihole-vodafone/pihole_install_7.png)


**Passo 8** - Modo de privacidade.
Usar o valor por omissão(Show everything). Irá permitir gerar estatisticas sobre os domínios pedidos.
![pihole Modo de privacidade](/assets/posts/pihole-vodafone/pihole_install_8.png)


**Passo 9** - Fim. **Importante!!**
Devem guardar a password mostrada no terminal, esta irá ser usada para aceder à interface de gestão.
![pihole passo final instalacao](/assets/posts/pihole-vodafone/pihole_install_last.png)


## Configurar o PiHole

Umas das primeiras coisas que devemos fazer é alterar o endereço IP do raspberry para um IP fixo. Vamos definir o endereço IP para 192.168.1.10. Este alinhamento será util mais tarde quando estivermos a configurar o servidor DHCP.

Para isto vamos editar o ficheiro /etc/dhcpcd.conf usando o editor de texto nano: ```sudo nano /etc/dhcpcd.conf```

Navegar até ao fim do ficheiro e editar o endereço IP de 192.168.1.84/24 para 192.168.1.10/24. A última parte do ficheiro deverá ficar assim:

    interface eth0
        static ip_address=192.168.1.10/24
        static routers=192.168.1.1
        static domain_name_servers=127.0.0.1

Para gravar o ficheiro "ctrl+x" e responder "y".

De seguida reiniciar o raspberry ```sudo reboot```
Depois de alguns segundos o raspberry deverá estar disponivel novamente, devemo-nos ligar novamente por ssh.
**Atenção** Como alteramos o endereço IP o comando ssh deverá ser ```ssh pi@192.168.1.10```


## Activar servidor DHCP do PIHole

**Nota:** Após iniciar os próximos passos a ligação à internet poderá apresentar problemas até à conclusão do guia.

Neste passo vamos activar o servidor DHCP do PiHole. O servidor DHCP é responsável por atribuir IPs aos dispositivos que se ligam à rede e informar esses mesmos dispositivos sobre qual é o servidor DNS que devem usar. Neste caso o servidor DNS que vai ser anunciado é o próprio PiHole.

Antes de activar o servidor DHCP do router do PiHole é necessário desactivar o que está à escuta no router da Vodafone.
Para isso vamos aceder à página de gestão do router da Vodafone http://192.168.1.1

![vodafone desligar dhcp](/assets/posts/pihole-vodafone/vodafone_disable_dhcp.png)

Nesta página devem desligar a opção "Ativar servidor DHCP primário". Caso apareça um popup a avisar sobre potenciais problemas devem ignorar e desactivar o DHCP.


Agora que o servidor DHCP do Router está desligado podemos activar o do PiHole. Para isso vamos então aceder à interface de gestão do PiHole http://192.168.1.10/admin/. Devem clicar em "login" e usar a password obtida no **passo 9**.

![pihole manager](/assets/posts/pihole-vodafone/pihole_enable_dhcp.png)

Devem navegar até ao separador "Settings" e depois "DHCP". Activem a opção "DHCP server enabled" e preencham o range DHCP entre "192.168.1.50" e "192.168.1.251".


## Configurar IP e DNS para a Box IPTV

Este é o passo mais importante deste guia. Caso não o efectuem vão perder as funcionalidades interactivas da Box (rewind, videoclube, guia tv etc...)

O truque é atribuir um IP fixo à box e anunciar como servidor DNS o router da Vodafone. Ou seja, quando a Box enviar um pedido DHCP para a rede o PiHole irá responder com um IP e anunciar como servidor DNS o 192.168.1.1 (o router Vodafone). A box vai ser o único dispositivo na rede a usar os servidores DNS da Vodafone, todos os outros equipamentos irão usar o PiHole e os servidores upstream configurados (Google DNS no caso deste guia).

Para este passo é necessário saber o mac address da box. Podem encontrar o mac adress no autocolante colado por baixo da box.

![pihole box mac address](/assets/posts/pihole-vodafone/box_mac.jpg)

O MAC address é o conjunto de letras no campo "MAC:". Deve separar cada conjunto de 2 letras por ":", por exemplo, caso o MAC address na etiqueta seja AABBCCDDEEFF deve converter para aa:bb:cc:dd:ee:ff.

Depois de obter o MAC address vamos criar o seguinte ficheiro ```nano /etc/dnsmasq.d/02-vodafone.conf``` e adicionar o seguinte conteúdo:

    dhcp-host=aa:bb:cc:dd:ee:ff,set:vodafone
    dhcp-option=tag:vodafone,option:dns-server,192.168.1.1

*Substituir aa:bb:cc:dd:ee:ff pelo mac address da box*
Guardem o ficheiro "ctrl+x" e "y"

E agora o basta configurar o servidor DHCP do PiHole para atribuir sempre o mesmo IP à Box:

![pihole box static ip](/assets/posts/pihole-vodafone/pihole_box_static_ip.png)


E agora devem reiniciar o raspberry ```sudo reboot```


## Validação

Após estes passos todos a instalação está concluída. Para finalizar devem desligar e voltar a ligar a box e validar que está tudo a funcionar normalmente.

Pode ser também necessário voltar a ligar os dispositivos wifi à rede, para isso basta desligar e voltar a ligar as redes wifi no dispositivo.
Após estes se ligarem à rede podem ver o IP que foi atribuído ao dispositivo na página de configuração do DHCP do PiHole http://192.168.1.10/admin/settings.php?tab=piholedhcp


Aproveitem para explorar as estatísticas na homepage da interface de gestão do PiHole. Ao fim de alguns minutos podem começar a ver a quantidade de domínios que foram bloqueados.

Um exemplo da minha instalação do PiHole:
![pihole dns bloqueados](/assets/posts/pihole-vodafone/pihole_sample_blocked.png)

De todos os pedidos DNS efectuados 16.7% foram bloqueados por serem destinados a publicidade ou mecanismos de tracking.

Neste momento o PiHole apenas tem as listas default. É possível adicionar mais listas negras de domínios. Podem incluir desde publicidade, malware, pornografia etc.... Num próximo post irei explicar como podem configurar estas listas extra.
