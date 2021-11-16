## Instalação do Jekyll no Ubuntu
- Instale as dependências:
```bash
$ sudo apt-get install ruby-full build-essential zlib1g-dev
$ echo '# Install Ruby Gems to ~/gems' >> ~/.bashrc
$ echo 'export GEM_HOME="$HOME/gems"' >> ~/.bashrc
$ echo 'export PATH="$HOME/gems/bin:$PATH"' >> ~/.bashrc
$ source ~/.bashrc
```
- Instale o Jekyll e o Bundler:
```bash
$ gem install jekyll bundler
```

Para instalação em outros Sistemas Operacionais, consulte a [página oficial do Jekyll](https://jekyllrb.com/docs/installation/#requirements).

Caso ocorram erros durante a instalação do Jekyll em outros Sistemas Operacionais, recomendo a [instalação do Ubuntu em uma Máquina Virtual](https://www.youtube.com/watch?v=wGwikwPrACA)


## Clone o repositório:
```bash 
git clone https://github.com/ieeecimatec/ieeecimatec.github.io
```
*Se preferir, pode fazer Download do arquivo .ZIP e descompactá-lo, clicando no botão ver "Code" no github e em "Download ZIP".

## Utilizando o Jekyll no VSCode (recomendado):
- Instale o [VSCode](https://code.visualstudio.com/);
- Instale a extensão ["Jekyll Run"](https://marketplace.visualstudio.com/items?itemName=Dedsec727.jekyll-run) na aba "Extensions" do VSCode;
- Dentro do repositório **ieeecimatec.github.io**, rode o comando: ```$ bundle install``` (deve ser executado apenas a primeira vez)
- Ainda em seu repositório, clique no botão **Jekyll Run** no canto inferior esquerdo do VSCode. O site será compilado e abrirá automaticamente em um servidor local, em seu browser. Caso não abra automaticamente, acesse **http://localhost:4000**

## Utilizando o Jekyll sem o VSCode:
- Dentro do repositório **ieeecimatec.github.io**, rode o comando: ```$ bundle install``` no *Command Prompt* (deve ser executado apenas a primeira vez)
- Sempre que queira pré-visualizar o site, abra o repositório no *Command Prompt* e rode:
```bash
bundle exec jekyll serve --livereload
```
- O site será compilado em um servidor local. Para visualizá-lo, acesse o seu Browser e navegue até **http://localhost:4000**

## Tutorial para alterar o site:
[Assista aqui](https://youtu.be/sLmVR54jKFU)
