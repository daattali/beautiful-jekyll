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

## Desenvolvimento

### Simulação

<p style="text-align: center;"> <img src="/assets/img/bayieeemax/baymax_ros.jpg" alt="logo ieee cimatec" width="150"/> </p>

O ROS é um *framework* que possui uma série de ferramentas úteis para o desenvolvimento de robôs. Por exemplo, ele é capaz de simplificar para o usuário o processo de comunicação dos diferentes componentes de um robô, tais como os motores, sensores, baterias e o *software* através de um sistema baseado em tópicos e mensagens. 

O ROS foi adotado como ferramenta neste projeto para a realização das simulação e implementação da lógica do robô por ser um projeto *open-source*, que possui diversos pacotes já desenvolvidos, suporta de forma nativa as lingugens de programação C++ e Python e também por poder ser carregado diretamente em sistemas embarcados, tal como a Raspberry Pi 3, o controlador que funcionará como o "cérebro" do robô.

Uma grande vantagem da simulação é que podem ser construídos ambientes virtuais complexos semelhantes aos hospitais reais, que seriam de difícil acesso para todos os testes necessários ao longo do projeto. Além disso, falhas podem ser identificadas  e melhorias implementadas sem a necessidade de estar com o robô em mãos ou da construção de um campo de trainamento.

Atualmente estamos desenvolvendo a teleoperação, que será usada para fins de testes no robô após a sua montagem, a navegação autônoma e a integração com os sensores que serão usados durante a triagem.

### Eletrônica

### CAD

<p style="text-align: center;"> <img src="/assets/img/bayieeemax/baymax_onshape.png" alt="logo ieee cimatec" width="200"/> </p>


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
