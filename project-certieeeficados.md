---
layout: page
title: CertIEEEficados
subtitle: Preenchimento automático de certificados
cover-img: /assets/img/certieeeficados/certifieeecados-cover.png
---

## O que é o projeto?

O projeto CertIEEEficados tem o objetivo de facilitar o trabalho de Ramos e Capítulos IEEE, que sempre organizam Eventos, Cursos e Workshops. Após a organização e realização dessas atividades, é muito comum que seja emitido um certificado de participação para os participantes, podendo por exemplo ser utilizado como horas complementares na Faculdade. Porém, isso é algo muito trabalhoso e demorado de ser feito manualmente.

Assim, surgiu a ideia de desenvolver um Gerador de Certificados Automático, que poderá preencher inúmeros certificados de diferentes atividades rapidamente, eliminando o esforço que os organizadores do evento teriam para preencher cada um de forma manual, economizando consideravelmente seu tempo e poupando energias.

Para desenvolver o programa, foi utilizada a linguagem Python, com auxílio de algumas bibliotecas, de forma que fosse criada uma interface gráfica para facilitar seu uso a qualquer usuário que tenha necessidade.


## Como faço para utilizar o programa?

O programa funciona tanto para Windows quanto para Linux. Tudo que precisa ser feito para rodar o programa é baixar o repositório no [<img width="20" src="{{ 'assets/img/github-logo.png' | relative_url }}" alt="logo github"/> Github](https://github.com/rascimatec/CertIEEEficados) e executar o arquivo **preencher_certificados**, dentro da pasta *exe.linux-x86_64-3.8* (para sistema Linux) ou *exe.win-amd64-3.9* (para sistema Windows). Não é necessário possuir o python ou qualquer biblioteca instalada, já que o programa foi compilado de forma que possa ser executado apenas rodando esse arquivo.

* Obs: Caso prefira, pode pular direto para o fim da página, que possui um video tutorial que exemplifica a utilização do programa.

Para que o programa funcione, são necessárias algumas coisas. A primeira delas é um arquivo de fonte .ttf, que será utilizada para escrever o nome (podem ser encontradas, por exemplo, [nesse site](https://www.dafont.com/pt/ttf.d592); caso não queira utilizar uma fonte padronizada, será utilizada uma genérica). Obrigatoriamente, você deve ter duas pastas: uma contendo os templates dos certificados (arquivos em .png) e outra contendo arquivos .csv que possuam uma coluna com o nome das pessoas que receberão certificado (esses arquivos podem ser exportados de algum software de planilhas, como o Excel ou Google Planilhas). Além disso, o nome dos arquivos do template e do .csv de uma mesma atividade devem ser o mesmo, pois o programa irá relacionar, de acordo com o nome dos arquivos, o template do certificado com o seu arquivo .csv.

<center><img width="420" src="{{ 'assets/img/certieeeficados/certificate-of-participation.jpeg' | relative_url }}" alt="interface"/>
<br>Exemplo de modelo de certificado</center>


Para que o Programa seja genérico, adaptando-se a diversos modelos diferentes de certificados, existem alguns parâmetros que devemos preencher.

Primeiro, devemos inserir os caminhos das pastas que contém os arquivos .csv (**Pasta de Dados (.CSV)**), os modelos de certificado .png (**Pasta de Modelos**) e o caminho que se deseja salvar os certificados (**Pasta de Certificados**), e também o arquivo da fonte (.ttf) que será utilizada (**Fonte**).

<center><img width="720" src="{{ 'assets/img/certieeeficados/certieeeficados-interface.jpeg' | relative_url }}" alt="interface"/></center>

Devemos inserir também o nome da coluna que possui os nomes a serem preenchidos, nos arquivos .csv (**Coluna de Nomes**). Depois disso, podemos clicar em **Update** para ter uma pré-visualização em tempo real dos certificados que serão gerados.

<center><img width="720" src="{{ 'assets/img/certieeeficados/previsualizacao-certificado.jpeg' | relative_url }}" alt="interface"/></center>


Caso insira um caminho inválido em algum dos campos, aparecerá um aviso de erro na tela, e a visualização em tempo real será interrompida. Ao corrijir os caminhos, pressione novamente o botão de **Update**, e a pré-visualização voltará a funcionar em tempo real.

<center><img width="360" src="{{ 'assets/img/certieeeficados/interface-erro.jpeg' | relative_url }}" alt="interface"/></center>

A partir daqui, podemos regular a altura em que o nome da pessoa será preenchido (para nomes que ocupam uma e duas linhas), o comprimento em caracteres que o nome poderá ocupar em uma linha, o tamanho da fonte, o espaçamento entre as linhas (caso o nome ocupe duas linhas), e a cor da fonte, em RGB (valores decimais entre 0 e 255).

Existem também alguns botões que nos permitem visualizar os demais certificados:
- **< / > :** Navega entre os certificados preenchidos daquela mesma atividade
- **<< / >> :** Visualiza certificados de outros eventos

Finalmente, pressione o botão **OK**, para gerar os certificados. Eles serão salvos em formato PDF na pasta que indicamos, em uma subpasta criada para cada uma das atividades. Cada certificado será salvo com o nome da pessoa a quem o certificado pertence.

Aqui está um vídeo que explica todo o processo para se utilizar o programa:

<center><iframe allow="fullscreen;" width="640" height="360" src="https://www.youtube.com/embed/oeE6aI9ZMKo"></iframe></center>

Por fim, criamos também um programa em python que envia os certificados gerados para o email dos participantes (**enviar_certificados.py**), relacionando os certificados preenchidos com os emails de cada um, contidos dentro dos mesmos arquivos .csv utilizados. Porém, esse programa está incompleto e ainda não possui uma interface gráfica, sendo necessário modificar alguns trechos do código fonte para que funcione bem.

## Posso utilizar esse programa à vontade?
É claro! **Esse programa é livre para todos** que queiram utilizá-lo! Você pode inclusive **propor melhorias**, fazendo um Pull Request [em nosso repositório](https://github.com/rascimatec/CertIEEEficados).

Caso utilize nosso programa, apenas deixe um comentário aqui embaixo, nos dizendo o que achou, e como foi sua experiência &#128513;!
<br>
Isso é importante para que tenhamos uma noção do alcance que o nosso projeto está tendo, e se está sendo realmente útil &#128540;.

### Equipe de desenvolvimento
<div class="row">
  <div class=" col-xl-auto offset-xl-0 col-lg-4 offset-lg-0">
    <div class="mobile-side-scroller">
      <table class="table-borderless highlight">
        <thead>
          <tr>
            <th><a href="https://www.linkedin.com/in/felipe-mohr-a9922a15a"><center><img src="{{ 'assets/img/voluntarios/felipe_mohr.png' | relative_url}}" width="100" alt="felipe" class="img-fluid rounded-circle blur-img" /></center></a></th>
          </tr>
        </thead>
        <tbody>
          <tr class="font-weight-bolder" style="text-align: center margin-top: 0">
            <td width="100%"><center>Felipe Mohr</center></td>
          </tr>
          <tr style="text-align: center" >
            <td style="vertical-align: top"><small><center>Voluntário desde 2018 <p/> Líder do projeto</center></small></td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</div>
