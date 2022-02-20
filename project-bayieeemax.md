---
layout: page
#title: 
#subtitle: Um robô para auxiliar em triagens
cover-img: /assets/img//bayieeemax/baymaxx.png
---
# O BayIEEEmax

## Apresentação
O projeto consiste na construção de um robô autônomo capaz de auxiliar os agentes de saúde no processo de triagem por meio da medição de parâmetros do estado de saúde do paciente, tais como pressão sanguínea, oxigenação e temperatura e registrá-los nas respectivas fichas dos pacientes. O robô exibirá perguntas numa tela LCD e também as emitirá pela via sonora através de um alto-falante e receberá as respostas do paciente por meio de comandos de voz.

Durante a execução do projeto será construído um modelo em um software de modelagem 3D para o corpo do robô para posterior impressão 3D. Além disso, será desenvolvida uma placa de circuito impresso responsável por interligar os sensores, atuadores e controlador, bem como retificar a tensão de entrada a fim de disponibilizá-la para o carregamento das baterias. Por fim, a lógica de funcionamento do robô será implementada por meio do *framework* ROS (*Robot Operating System*).

A realização do projeto só foi possível graças ao financiamento de **$2.000 dólares** recebido através de um edital do [RAS Chapter Initiative Grant](https://www.ieee-ras.org/chapters/support-for-chapters) da [**RAS**](https://www.ieee-ras.org/). Para mais detalhes acesse esse [post](https://ieeecimatec.github.io/bayieeemax-financiamento/).

<a href="https://ieeecimatec.github.io/bayieeemax-financiamento/"><img src="/assets/img/bayieeemax/baymax_premio.png" alt="BayIEEEmax Financiamento"></a>

## Desenvolvimento

### Simulação

<p style="text-align: center;"> <img src="/assets/img/bayieeemax/baymax_ros.jpg" alt="ROS" width="150"/> </p>

O ROS é um *framework* que possui uma série de ferramentas úteis para o desenvolvimento de robôs. Por exemplo, ele é capaz de simplificar para o usuário o processo de comunicação dos diferentes componentes de um robô, tais como os motores, sensores, baterias e o *software* através de um sistema baseado em tópicos e mensagens. 

O ROS foi adotado como ferramenta neste projeto para a realização das simulação e implementação da lógica do robô por ser um projeto *open-source*, que possui diversos pacotes já desenvolvidos, suporta de forma nativa as lingugens de programação C++ e Python e também por poder ser carregado diretamente em sistemas embarcados, tal como a Raspberry Pi 4, o controlador que funcionará como o "cérebro" do robô.

Uma grande vantagem da simulação é que podem ser construídos ambientes virtuais complexos semelhantes aos hospitais reais, que seriam de difícil acesso para todos os testes necessários ao longo do projeto. Além disso, falhas podem ser identificadas  e melhorias implementadas sem a necessidade de estar com o robô em mãos ou da construção de um campo de trainamento.

Atualmente estamos desenvolvendo a teleoperação, que será usada para fins de testes no robô após a sua montagem, a navegação autônoma e a integração com os sensores que serão usados durante a triagem.

<img width="30" src="{{ 'assets/img/github-logo.png' | relative_url }}" alt="logo github"/> **Repositório:** [ieeecimatec/bayieeemax](https://github.com/ieeecimatec/bayieeemax)

### Eletrônica

<p style="text-align: center;"> <img src="/assets/img/bayieeemax/baymax_kicad.png" alt="KICAD" width="200"/> </p>

KiCad é um *programa computacional* de *código aberto* para projeto eletrônico assistido por computador, com o objetivo de facilitar a concepção de layouts e suas conversões para placas de *circuito impresso*.

O KiCad foi utilizado neste projeto como instrumento para a confecção do circuito impresso (PCB), o qual foi construído por meio da montagem do circuito propriamente dito, colocando componentes essenciais para o funcionamento do robô, e por ser Open Source, permite a utilização de modelos 3Ds e footprints, criados por sua empresa ou usuários desse Software.

A utilização do KiCad permite ao usuário desenvolver um circuito prévio, construindo uma placa que será feita para o funcionamento desejado, com os componentes desejados, evitando gastos com risco de mal posicionamento ou falta de espaço entre componentes. Ademais, as possíveis falhas de conexões do circuito são identificadas durante a construção do mesmo, em que o próprio software te alerta sobre os erros de ligações encontrados.

Hodiernamente, está sendo desenvolvido a placa *Main board*, possuindo em seu circuito um MicroControlador chamado STM32F103C8T6, que irá se conectar com a *Placa Mãe*, cujo componente principal é a Raspberry PI 4 Model B, o qual irá monitorar esse Microcontrolador. Dessa maneira, permite o funcionamento dos motores, sensores, GPs e reconhecimento de voz que serão utilizados na triagem médica dos pacientes.

A imagem abaixo apresenta estágio atual da *Main board*, com o modele tridimensional dos componentes utilizados e que serão interligados por meio da placa de circuito impresso.

<p style="text-align: center;"> <img src="/assets/img/bayieeemax/baymax_componentes.jpeg" alt="compoentes eletrônicos"/> </p>

<img width="30" src="{{ 'assets/img/github-logo.png' | relative_url }}" alt="logo github"/> **Repositório:** [ieeecimatec/Baiyeeemax_eletronics](https://github.com/ieeecimatec/Baiyeeemax_eletronics)

### Equipe de desenvolvimento
#### Software
<div class="row">
  <div class=" col-xl-auto offset-xl-0 col-lg-4 offset-lg-0">
    <div class="mobile-side-scroller">
      <table class="table-borderless highlight">
        <thead>
          <tr>
            <th><center><img src="{{ 'assets/img/voluntarios/gabriel_calmon.png' | relative_url }}" width="100" alt="gabriel" class="img-fluid rounded-circle" /></center></th>
            <th></th>
            <th><center><img src="{{ 'assets/img/voluntarios/victor_guerra.jpeg' | relative_url }}" width="100" alt="victor" class="img-fluid rounded-circle"/></center></th>
            <th></th>
            <th><center><img src="{{ 'assets/img/voluntarios/felipe_mohr.png' | relative_url }}" width="100" alt="felipe" class="img-fluid rounded-circle" /></center></th>
          </tr>
        </thead>
        <tbody>
          <tr class="font-weight-bolder" style="text-align: center margin-top: 0">
            <td width="25%"><center>Gabriel Calmon</center></td>
            <td></td>
            <td width="25%"><center>Victor Guerra</center></td>
            <td></td>
            <td width="25%"><center>Felipe Mohr</center></td>
          </tr>
          <tr style="text-align: center" >
            <td style="vertical-align: top"><small><center>Voluntário desde 2020 <p/> Líder do projeto</center></small></td>
            <td></td>
            <td style="vertical-align: top"><small><center>Voluntário desde 2021</center></small></td>
            <td></td>
            <td style="vertical-align: top"><small><center>Voluntário desde 2018</center></small></td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</div>

#### Eletro-eletrônica
<div class="row">
  <div class=" col-xl-auto offset-xl-0 col-lg-4 offset-lg-0">
    <div class="mobile-side-scroller">
      <table class="table-borderless highlight">
        <thead>
          <tr>
            <th><center><img src="{{ 'assets/img/voluntarios/ruan_utah.png' | relative_url }}" width="100" alt="ruan" class="img-fluid rounded-circle" /></center></th>
            <th></th>
            <th><center><img src="{{ 'assets/img/voluntarios/julia_nascimento.png' | relative_url }}" width="100" alt="julia" class="img-fluid rounded-circle"/></center></th>
          </tr>
        </thead>
        <tbody>
          <tr class="font-weight-bolder" style="text-align: center margin-top: 0">
            <td width="50%"><center>Ruan Utah</center></td>
            <td></td>
            <td width="50%"><center>Julia Nascimento</center></td>
          </tr>
          <tr style="text-align: center" >
            <td style="vertical-align: top"><small><center>Voluntário desde 2020</center></small></td>
            <td></td>
            <td style="vertical-align: top"><small><center>Voluntária desde 2021</center></small></td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</div>

#### CAD
<div class="row">
  <div class=" col-xl-auto offset-xl-0 col-lg-4 offset-lg-0">
    <div class="mobile-side-scroller">
      <table class="table-borderless highlight">
        <thead>
          <tr>
            <th><center><img src="{{ 'assets/img/voluntarios/caio_oliva.png' | relative_url }}" width="100" alt="caio" class="img-fluid rounded-circle" /></center></th>
            <th></th>
            <th><center><img src="{{ 'assets/img/voluntarios/yan_valdez.png' | relative_url }}" width="100" alt="yan" class="img-fluid rounded-circle"/></center></th>
          </tr>
        </thead>
        <tbody>
          <tr class="font-weight-bolder" style="text-align: center margin-top: 0">
            <td width="50%"><center>Caio Oliva</center></td>
            <td></td>
            <td width="50%"><center>Yan Valdez</center></td>
          </tr>
          <tr style="text-align: center" >
            <td style="vertical-align: top"><small><center>Voluntário desde 2019</center></small></td>
            <td></td>
            <td style="vertical-align: top"><small><center>Voluntário desde 2021</center></small></td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</div>
