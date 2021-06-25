---
layout: page
title: APEREA - JetBot 2
subtitle: Robô autônomo diferencial
---

<center>
<img src="{{ 'assets/img/aperea/jetbot.png' | relative_url }}" text-align=center alt="nvidiaJetbot" />
</center>

## INTRODUÇÃO

A junção da mobilidade com ferramentas de visão computacional e inteligência artificial proporcionam aos robôs móveis uma grande variedade de aplicações e autonomia. As aplicações incluem navegação, localização e identificação de objetos, por exemplo.

O Projeto Aperea Jetbot II almeja utilizar alguns dos benefícios gerados do elo entre robótica móvel, visão computacional e I.A. Para isso será utilizada a placa Nvidia Jetson Nano em conjunto com elementos sensoriais para coletar dados do meio externo.

Conforme ilustrado na Figura abaixo, o robô deverá ser capaz de buscar e reconhecer uma tag no ambiente. A tag indicará a localização de uma bola na cor laranja. E, a partir desta informação, o robô deverá encontrar esta bola.

<center>
<img src="{{ 'assets/img/aperea/jetbotmission.png' | relative_url }}" text-align=center alt="missao" />
</center>

O projeto teve inicio em 07/05/2021, possui uma duração estimada de 58 dias e tem sua conclusão prevista para 30/07/2021. A execução deste projeto irá propor, aos seus respectivos desenvolvedores, conhecimentos direcionados a robótica móvel, além de experiências voltadas ao gerenciamento de projetos. Ambos ganhos são importantes na formação de pesquisadores e desenvolvedores com alvo em sistemas robóticos.

<br>

## Detalhamento
O Aperea, para cumprir a sua missão, precisa realizar deslocamentos para navegar no ambiente.Conforme ilustrado abaixo, o movimento do robô será proporcionado pelas atuações dos motores TT. A implementação também será focada para atribuir uma dinâmica de um robô móvel diferencial.
Durante a navegação, o robô deve encontrar obstáculos que podem dificultar a execução da missão. Para tratar os eventuais obstáculos serão implementados sensores que ajudarão na tarefa de evita-lós.

<center>
<img src="{{ 'assets/img/aperea/esquema.png' | relative_url }}" text-align=center alt="ga" />
</center>

O sensor ultrassônico, implementado na parte frontal do robô, proverá informação da existência de obstáculos que podem estar a frente do robô.
Um Lidar 2d, juntamente com uma câmera de profundidade Mynteye serão utilizados para tornar este sistema robótico capaz de realizar a técnica SLAM, que irá permitir a construção do mapa e localização de forma simultânea.
Afim de identificar a TAG e a esfera colorida, a câmera V2 Raspberry Pi será utilizada para captar os dados visuais do ambiente. Os dados visuais serão processados com uso da biblioteca de visão computacional OpenCV.

O processamento dos dados que serão coletados pelos sensores e câmeras será realizado pela placa Nvidia Jetson Nano. A placa conterá o sistema operacional Ubuntu 20.04, que permitirá a instalação da plataforma ROS, Robot Operation System. Também será desenvolvido um sistema de gerenciamento de energia para monitorar a carga do sistema. A tabela abaixo apresenta mais informações com relação aos principais componentes que compõem o sistema do Aperea.

<center> Principais Componentes</center>

|Componente| Modelo|Fabricante| Aplicação|
|:-:|:-:|:-:|:-:|
| <center><img src="{{ 'assets/img/aperea/jetson_nano.png' | relative_url }}" width="100" alt="camerav2" >|Jetson Nano|NVIDIA| Unidade de processamento
| <center><img src="{{ 'assets/img/aperea/cameraV2.png' | relative_url }}" width="100" alt="camerav2" >|Câmera Module V2 |RaspberryPi| Detectar a TAG e a esfera
| <center><img src="{{ 'assets/img/aperea/mynteye.png' | relative_url }}" width="100" alt="mynteye">|Câmera Stereo S1030 |Mynt eye| Detectar obstáculos, localização e mapeamento
| <center><img src="{{ 'assets/img/aperea/sensorultr.png' | relative_url }}" width="100" alt="sensorultr"> |Sensor Ultrassônico HC-SR04|HC-SR04|Detectar obstáculos|
| <center><img src="{{ 'assets/img/aperea/lidar.png' | relative_url }}" width="100" alt="lidar"> |Lidar LDS-01|Robotis| Mapeamento e localização
| <center><img src="{{ 'assets/img/aperea/motordc.png' | relative_url }}" width="100" alt="lidar"> |Motor DC 3-6v|Rob| Deslocamento


<br/>

<center>
<h3 class="post-title">Equipe de desenvolvimento</h3><br/>
</center>
<div class="row">

<div class=" col-xl-auto offset-xl-0 col-lg-4 offset-lg-0">
<table class="table-borderless highlight">
<thead>
<tr>
<th><center><img src="{{ 'assets/img/marco.jpg' | relative_url }}" width="100" alt="juliana" class="img-fluid rounded-circle" /></center></th>
<th></th>
<th><center><img src="{{ 'assets/img/marco.jpg' | relative_url }}" width="100" alt="matheusanselmo" class="img-fluid rounded-circle"/></center></th>
<th></th>
<th><center><img src="{{ 'assets/img/marco.jpg' | relative_url }}" width="100" alt="marco" class="img-fluid rounded-circle"/></center></th>
</tr>
</thead>
<tbody>
<tr class="font-weight-bolder" style="text-align: center margin-top: 0">
<td width="33.33%">Juliana Santana</td>
<td></td>
<td width="33.33%">Matheus Anselmo</td>
<td></td>
<td width="33.33%">Marco Reis</td>
</tr>
<tr style="text-align: center" >
<td style="vertical-align: top"><small>Pesquisadora Jr. do projeto <br>Engenheira Eletricista.</small></td>
<td></td>
<td style="vertical-align: top"><small>Pesquisador Jr. do projeto <br>Engenheiro de Controle e Automação.</small></td>
<td></td>
<td style="vertical-align: top"><small>Orientador do projeto <br>Mestre em Engenharia de Produção e Eng. Eletricista.</small></td>
</tr>
</tbody>
</table>
</div>
</div>

<br>

### Resumo do Projeto
1. Categoria: 
2. Prazo: 03 meses
3. Data de início: <font color="#fbb117">07/maio/2021</font>
4. Data de término: <font color="#fbb117">30/julho/2021</font>
5. Repositório URL: 
6. Sponsor: <a href="http://www.senaicimatec.com.br/en/"><font color="#fbb117">Senai CIMATEC</font></a>
7. Recursos materiais: US$
8. Apresentação URL:
9. Report URL: 
10. Artigos relacionados: 

<br>

# Referência
1. Jetbot. **JETBOT**. Acesso em: 4 de Junho de 2021 [https://jetbot.org/master].
