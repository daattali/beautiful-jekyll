---
layout: page
title: I3E-D3
subtitle: Um mascote para nosso IEEE
cover-img: /assets/img/i3ed3/i3ed3_cover.png
---

## O que é o I3E-D3?
O I3E-D3 é o mascote do IEEE CIMATEC, um robô autônomo utilizado também como ferramenta de marketing para nosso Ramo.
Além disso, a ideia do projeto é que ele possa ser utilizado pelos voluntários da RAS para o aprendizado de robótica em uma plataforma física, implementando novas funcionalidades ao robô.

### Como surgiu?
A ideia do projeto surgiu a partir do [I3E-D2](../project-i3e_d2/), um robô bastante simples (inspirado no R2D2), construído por nós há alguns anos, e apresentado no IEEE DAY 2018. Então, ao fim de 2019, resolvemos projetar um robô mais complexo, autônomo e com mais funcionalidades.

## Desenvolvimento
### Software

<article class="project-preview-left">
    <div class="project-image">
        <a href="https://ros.org/">
        <img src="{{ 'assets/img/i3ed3/rosnoetic.jpeg' | relative_url }}" alt="ROS Noetic" class="rounded-circle"/>
        </a>
    </div>
        Todo o desenvolvimento de software do robô foi feito utilizando o framework de robótica ROS Noetic. O <a href="https://ros.org/">ROS</a> é um conjunto de bibliotecas e ferramentas de software que auxiliam na construção de aplicações robóticas, contendo diversos pacotes e algoritmos de estado-da-arte, drivers, ferramentas de visualização e desenvolvimento, e muitas outras coisas que facilitam o desenvolvimento de robôs.
</article>

#### Funcionalidades implementadas:
- **Teleoperação:** Utilizando um controle Joystick genérico, o D3 pode ser controlado remotamente e navegar pelo ambiente;
- **Localização:** Conforme o D3 se move pelo ambiente (seja por navegação autônoma ou por teleoperação), ele é capaz de se localizar em um mapa predefinido, ou mesmo se localizar enquanto mapeia o ambiente, o que é chamado de [SLAM - Simultaneous Localization And Mapping](https://pt.wikipedia.org/wiki/SLAM_(rob%C3%B3tica));
- **Mapeamento:** O D3 é capaz de mapear uma região conforme se move por ela. Isso é possível graças ao seu sensor LIDAR, que dá ao robô informações sobre o ambiente ao seu redor;
- **Navegação Autônoma:** O D3 utiliza a [Navigation Stack](http://wiki.ros.org/navigation) do ROS para navegar de forma autônoma pelo ambiente. Isso pode ser feito tanto com um mapa predefinido (mapeado por ele mesmo), desviando de possíveis novos obstáculos ou pessoas, que não estavam contidos no mapa inicial, ou até sem nenhum mapa;
- **Exploração:** A exploração consiste-se em uma navegação autônoma sem um mapa predefinido, de forma que o mapeamento é feito enquanto navega. A exploração termina quando o D3 consegue mapear o ambiente inteiro ao seu redor, salvando o mapa em um arquivo, de forma que possa ser utilizado posteriormente.

![Navigation](../assets/img/i3ed3/navigation.png)

### Eletrônica

<table class="table-borderless">
    <tbody>
    <tr>
        <td><img src="{{ 'assets/img/i3ed3/D3_Board.png' | relative_url }}" alt="D3 main board" width=400/></td>
        <td rowspan="2" width="50%" style="text-align: left">Para a eletrônica do I3E-D3, foram desenvolvidas duas Placas de Circuito Impresso (PCBs): uma placa principal chamada de <b>Main Board</b>, contendo os componentes principais da placa (microcontrolador, entrada para alimentação, conversor DC-DC, conectores para motores e pontes-H, GPS, IMU, e outros), e outra placa chamada de <b>Face Board</b>, contendo os circuitos para funcionamento das matrizes de LED do rosto do robô, que se comunica com a placa principal. 
        O microcontrolador utilizado para o projeto foi o <b>STM32F103C8T6</b>, popularmente conhecido como <b>bluepill</b>. Ele se comunica via Serial com uma <b>Raspberry Pi 3</b>, que é o controlador responsável pelo funcionamento do robô, utilizando o ROS.
        </td>
    </tr>
    <tr>
        <td><img src="{{ 'assets/img/i3ed3/D3_Face.png' | relative_url }}" alt="D3 face board" width=400/></td>
    </tr>
    </tbody>
</table>

### CAD

<article class="project-preview-right">
    <div class="project-image">
        <img src="{{ 'assets/img/i3ed3/cad.jpeg' | relative_url }}" alt="CAD" class="rounded-circle"/>
    </div>
        O CAD do projeto foi responsável pela criação de todas as peças do robô - desde os braços e cabeça até as peças internas de fixação. Para modelagem das peças e montagem do robô, foi utilizado o <a href="https://www.solidworks.com/pt-br">SolidWorks</a> e o <a href="https://www.onshape.com/en/">OnShape</a>. Após modeladas, as peças foram impressas em 3D, e a partir do modelo 3D do robô, foi possível criar o <a href="http://wiki.ros.org/urdf">URDF</a> (a descrição do robô) para simulação.
</article>


## Resultados obtidos
<iframe width="720" height="480"
src="https://www.youtube.com/embed/L5760xKJU8">
</iframe>


## Equipe de desenvolvimento
<div class="row">
  <div class=" col-xl-auto offset-xl-0 col-lg-4 offset-lg-0">
    <div class="mobile-side-scroller">
      <table class="table-borderless highlight">
        <thead>
          <tr>
            <th><a href="https://www.linkedin.com/in/felipe-mohr-a9922a15a"><center><img src="{{ 'assets/img/voluntarios/felipe_mohr.png' | relative_url}}" width="100" alt="felipe" class="img-fluid rounded-circle blur-img" /></center></a></th>
            <th></th>
            <th><center><img src="{{ 'assets/img/voluntarios/caio_oliva.png' | relative_url }}" width="100" alt="caio" class="img-fluid rounded-circle" /></center></th>
          </tr>
        </thead>
        <tbody>
          <tr class="font-weight-bolder" style="text-align: center margin-top: 0">
            <td width="50%"><center>Felipe Mohr</center></td>
            <td></td>
            <td width="50%"><center>Caio Oliva</center></td>
          </tr>
          <tr style="text-align: center" >
            <td style="vertical-align: top"><small><center>Voluntário desde 2018 <p/> Líder do projeto</center></small></td>
            <td></td>
            <td style="vertical-align: top"><small><center>Voluntário desde 2019</center></small></td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</div>
