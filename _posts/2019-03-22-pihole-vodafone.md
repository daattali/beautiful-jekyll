---
layout: post
title: Usar o Pi-hole como servidor DNS com o Smart router da Vodafone
---

Os router actualmente fornecidos pela Vodafone, Smart Router 2.0, não permitem configurar manualmente os servidores DNS anunciados por DHCP. Caso forçemos a alteração dos servidores DNS a BOX IPTV deixa de funcionar.

Este guia tem como finalidade instalar e configurar o PiHole de forma a poder ser usado como servidor DNS e DHCP pelos equipamentos ligados ao Smart Router 2.0.

Este guia tem como objectivo a instalação e configuração do PiHole no raspberry Pi 3B+. Apesar deste guia usar o raspberry PI 3B+ como referência é válido para qualquer modelo, desde que usem o Raspbian.

Os objectivos para o final deste guia  são:

1. Instalar o Raspbian no Raspberry
2. Instalar o PIHole
3. Activar o servidor DHCP no Raspberry e desligar o DHCP do do router Vodafone


## Material necessário.

Para este guia irei usar um Raspberry PI 3B+. Apesar de ter usado este modelo, este guia é valido para qualquer Raspberry a correr Raspbian, incluido o Raspberry PI 1 B com 512MB de ram  e um cpu de 700MHz.

Não vamos ter ambiente gráfico no raspbian por isso terão de ter um cliente ssh instalado na vossa máquina. Para o pessoal do Linux ou MacOs não é neicessário fazer nada, para o Windows podem usar o Putty https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html.


## Instalação Raspbian

O primeiro passo é obter a imagem mais recente do raspbian. Podem fazer download do site oficial: https://www.raspberrypi.org/downloads/raspbian/
A versão que vamos suar é a Raspbian Stretch Lite, sem ambiente gráfico.

O próximo passo é copiar a imagem para o SDCard, para isto recomendo o etcher https://www.balena.io/etcher/. Ou podem usar o dd.


Após a imagem ter sido copiada com sucesso é necessário activar o ssh. Monta o cartão SD novamente (tira e volta a colocar ou “mount”). Na raiz cria um ficheiro vazio chamado “ssh”.
