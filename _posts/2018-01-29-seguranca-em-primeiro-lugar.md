---
layout: post
title: Segurança em primeiro lugar
subtitle: tenha cuidado com tudo
date: 2018-01-29 23:10:00
image: /assets/img/anonymous-hacker.jpg
share-img: /assets/img/anonymous-hacker.jpg
tags: [seguranca, dicas]
categories: geral
---

Em grade parte das empresas, a área de segurança é pouco valor, ou muitas vezes nem se preocupam com a realização de um simples backup(Lembram dos ransomware que bloqueavam o sistema e pediam resgate), ou com uma boa segurança na suas senhas(Não vale guarda as senhas no google drive, como o Palácio do Planalto) entre outros casos "bizarros" que já vimos.

![Logs](/assets/img/seguranca.jpg)

Assim como testes são algo básico na sua aplicação, uma simples politica de segurança(PSI), pode fazer uma grande diferença no futuro da sua empresa, como evitar aquela dor de cabeça, pois o estagiario que foi demitido, tinha a senha do root de todos os serviços, e deixou um *script* de presente para você.

#### PSI
Tenha um politica de segurança, nem que seja minima... revise a mesma com uma certa frequência, modifique ela com o tempo, pois neste mundo ágil e de grandes mudanças, tudo se modifica com uma grande rapidez.

Tenha um "guia" básico, com informações importantes, sobre o quais são os ativos sensíveis na sua empresa. Podemos começar esse PSI com dicas/normas básicas como:

+ **Politicas de backup**
  Sim, tenha um politica de backup, seja loca ou na nuvem, não confie segamente no q lé foi vendido, pois catástrofes podem acontecer.
+ **Senhas seguras**
  Não é por que sua senha tem 16 caracteres que ela é segura, pois segundo [McAffe](https://securingtomorrow.mcafee.com/consumer/family-safety/world-password-day/) 90% das senhas são inseguros. Não utilizem frases, nome de cachorros, datas nem outra informação que seja possível obter através de uma engenharia social. Utilize caracteres especiais(\*!@#$%...). Utilize 2FA para uma maior segurança, e não esqueça de trocar sua senha periodicamente.
+ **ativos importantes**
  Saiba quais são seus ativos importantes, tenha em mente o que é sensível, ou no bom portugues, o que não pode ser visto por terceiros.
+ **Acessos a Internet**
  Muitas empresas vivem da internet(facebook, Instagram, Linkedin), e também não tem como viver isolado dela, mas o que temos que cuidar nesta parte é o que é postado, o que aquele print pode mostrar para as outras pessoas. Será que uma simples foto de final de tarde na empresa, não aparecera dados de clientes num quadro branco, ou uma senha pendurada num *post it*?


#### Monitore tudo
Mantenha logs de tudo que ocorre no sistema(Melhor errar pra mais do que pra menos), pois somente assim vai conseguir ver o que ocorre no seu serviço, tanto na aplicação quanto no seu servidor.

![Logs](/assets/img/logs.jpg)

Existem enumeras ferramentas que podem fazer o monitoramento do seus logs, como o [ELK](https://www.elastic.co/elk-stack), [GrayLog](https://www.graylog.org/), [Spluk](https://www.splunk.com/), [LogZilla](http://www.logzilla.net/) entre outros. O ponto é que independentemente da ferramenta que for utilizada no seu ambiente, use e abuse do serviço, crie dashboards especifícos para cada serviço.


#### PCN
Para finalizar, tenha um PCN(Plano de Continuidade de Negocio) com  bem definido, pois ele pode salvar uma boa noite de sono. Tenha em mente que falhas vão acontecer e devemos estar preparados para agir da maneira mais rápida e segura possível.
