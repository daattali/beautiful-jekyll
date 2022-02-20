---
layout: page
title: Baby IoT
subtitle: Uma babá eletrônica
cover-img: /assets/img/babyiot/babyiot-cover.jpg
---

<!-- Baba eletrônica que ofereça conexão entre o bebê, seu quarto e um aplicativo que irá integrar e monitorar tudo. O projeto deverá inicialmente promover a conexão entre os microcontroladores e o celular e englobará conhecimentos de programação de microcontroladores, sensores e desenvolvimento de aplicativo. -->

**BabyIOT** é um projeto que visa utilizar microcontroladores para conectar um bebê e seu quarto ao telefone de um adulto responsável. O projeto é dividido em três partes que irão interagir entre si, uma parte será embarcada no bebê por meio de um bracelete, outra parte será acoplada ao berço e quarto do bebê e a terceira e última parte é o aplicativo que irá sincronizar as informações colhidas pelas outras duas partes.

![Baby IOT](../assets/img/babyiot/logo.png)

O bracelete que ficará em contato com o bebê será comandado por um **Arduino Pro Mini** e irá transmitir os dados de temperatura, batimentos cardíacos e movimentação do bebê por meio de um modulo bluetooth, totalizando cinco componentes acoplados ao Arduino em um corpo impresso em 3D.

A unidade que ficará no quarto será controlada por um **Raspberry-Pi** e terá como principal funcionalidade receber as informações via bluetooth do bracelete e transmiti-las por meio do wi-fi para o aplicativo. Além disso, o Raspberry será responsável por adicionar um certo grau de inteligência no quarto do bebê, contando com uma câmera e um microfone para transmitir som e imagem para o app e um sensor de presença para ativar todo esse ecossistema e assim economizar dados e energia. **Posteriormente poderão ser adicionados mais sensores e módulos para que essa parte do projeto tenha mais inteligência.**

Já o aplicativo, será desenvolvido para compilar todos os dados obtidos pelo bracelete e terá o monitoramento do quarto do bebê. Sensores como giroscópio, acelerômetro e de batimentos irão indicar quando o bebê está dormindo, tendo todas essas informações em uma interface com gráficos e informações uteis. Caso o bebê apresente uma movimentação muito intensa, o aplicativo também alertará ao usuário, que por meio da câmera poderá visualizar remotamente se o bebê precisa de cuidados urgentes. **Com a implementação do app, as funcionalidades se ampliam bastante, podendo surgir mais usos no decorrer do desenvolvimento do projeto ou após sua finalização, sendo uma área que pode representar mais um futuro projeto dentro do IEEE Cimatec.**

**O babyIOT** é um projeto que a princípio é voltado ao monitoramento de bebês em um ambiente controlado, mas que poderá ser ampliado para idosos, pessoas com alguma deficiência etc. sendo um projeto amplo e que pode ser implementado em casas e hospitais para acompanhamento de pacientes e ou bebês que os responsáveis não fiquem o tempo inteiro em casa.

### Equipe de Desenvolvimento
<div class="row">
  <div class=" col-xl-auto offset-xl-0 col-lg-4 offset-lg-0">
    <div class="mobile-side-scroller">
      <table class="table-borderless highlight">
        <thead>
          <tr>
            <th><center><img src="{{ 'assets/img/voluntarios/matheus_bomfim.png' | relative_url }}" width="100" alt="matheus" class="img-fluid rounded-circle" /></center></th>
            <th></th>
            <th><center><img src="{{ 'assets/img/voluntarios/danisson_jose.png' | relative_url }}" width="100" alt="danisson" class="img-fluid rounded-circle"/></center></th>
            <th></th>
            <th><center><img src="{{ 'assets/img/voluntarios/lucas_lopes.png' | relative_url }}" width="100" alt="lucas" class="img-fluid rounded-circle" /></center></th>
            <th></th>
            <th><center><img src="{{ 'assets/img/voluntarios/ludmila_nascimento.png' | relative_url }}" width="100" alt="ludmila" class="img-fluid rounded-circle"/></center></th>
          </tr>
        </thead>
        <tbody>
          <tr class="font-weight-bolder" style="text-align: center margin-top: 0">
            <td width="25%"><center>Matheus Bomfim</center></td>
            <td></td>
            <td width="25%"><center>Danisson José</center></td>
            <td></td>
            <td width="25%"><center>Lucas Lopes</center></td>
            <td></td>
            <td width="25%"><center>Ludmila Nascimento</center></td>
          </tr>
          <tr style="text-align: center" >
            <td style="vertical-align: top"><small><center>Voluntário desde 2020 <p/> Líder do projeto</center></small></td>
            <td></td>
            <td style="vertical-align: top"><small><center>Voluntário desde 2021</center></small></td>
            <td></td>
            <td style="vertical-align: top"><small><center>Voluntário desde 2021</center></small></td>
            <td></td>
            <td style="vertical-align: top"><small><center>Voluntária desde 2021</center></small></td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</div>
