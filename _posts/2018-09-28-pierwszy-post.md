---
layout: post
title: Docker - Optymalizacja obrazu
image: /img/docker-post-1.png
tags: [docker, kontenery, linux, how-to, optymalizacja, czyszczenie]
---

To jest pierwszy artykuł z seri o Dokerze. Objaśnie w nim jak powinien być zbudowany dobrze zoptymalizowany kontener pod wzgędem objętości.
Stosując kilka trików opisanych poniżej można zyskać cenną przestrzeń na dysku, skrócić czas pobierania obrazu. Co pozwala np przyśpieszyc proces upgradu środowiska.


## Zainstalowałeś to posprzątaj

Najważniejszą rzeczą jest sprzątanie po instalacji oprogramowania w kontenerze.
Dla przykładu posłużymy się obrazem którego używam do pisania artykułów na tym bloga.



{% highlight Dockerfile linenos %}
FROM ruby:2.4

MAINTAINER Łukasz Żułnowski "lzulnowski@gmail.com"

RUN apt-get update && apt-get install -y -q \
  build-essential \
  wget \
  curl

RUN gem install jekyll bundler

RUN mkdir -p /app

WORKDIR /app

EXPOSE 4000

CMD bundle install && bundle exec jekyll serve -H 0.0.0.0
{% endhighlight %}

Po zbudowaniu obraz wygląda następują:

{% highlight bash linenos %}
docker build . -t blog
docker images blog
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
blog                latest              d21d207746fe        40 seconds ago      729MB
{% endhighlight %}

Dodajmy czyszczenie obrazu po instalacji pakietów za pomocą apt-get oraz zbudujmy obraz jeszcze raz.

{% highlight bash linenos %}
RUN apt-get update && apt-get install -y -q \
  build-essential \
  wget \
  vim \
  curl \
  && rm -rf /var/lib/apt/lists/*
{% endhighlight %}

Po zbudowaniu obraz wygląda następująco:

{% highlight bash linenos %}
docker images blog
REPOSITORY          TAG                 IMAGE ID            CREATED              SIZE
blog                latest              030a09e675d7        About a minute ago   835MB
{% endhighlight %}

Jak widać udało nam się zaoszczędzić trochę miejsca. Niby nic, ale w przypadku gdy doinstalujemy dużo zalezności potrafi to być gigantyczna przestrzeń.

{: .box-error}
**Ważne:** Czyszczenie powinno być zawsze wykonane w tej warstwie którą chcemy czyścić. Dodanie nowej warstwy tylko zwiększy obraz.

## Instalujmy tylko to co jest nam potrzebne.

Kolejnym sposobem z użyciem apt jest instalowanie tylko paczek, które naprawde są nam potrzebne. Do naszego polecenia dodamy przełącznik dzięki któremu nie zainstalują się paczki zalerzności opcjonalne których najczęściej nie potrzebujemy. Jeśli jest inaczej warto je wpisać do Dockerfile.

{% highlight bash linenos %}
RUN apt-get update && apt-get install --no-install-recommends -y -q \
  build-essential \
  wget \
  curl \
  && rm -rf /var/lib/apt/lists/*
{% endhighlight %}

A tak wygląda obraz po tym zabiegu:
{% highlight bash linenos %}
docker images blog
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
blog                latest              d632fd938793        4 seconds ago       834MB
{% endhighlight %}

Na tej operacji aż tak dużo nie uzyskaliśmy. Przy innych pakietach może być to bardziej korzystne. Tą metodę można znaleść w wielu oficjalnych obrazach np: [elasticsearch](https://github.com/docker-library/elasticsearch/blob/5b2bf54e2c17a8e2e1b062ea0d071eae600bfec2/2.2/Dockerfile#L23)


## Obsługa zdalnych skryptów czy paczek

W przypadku gdy musimy użyć skryptu umieszczonego na przykład na [GitHub](http://github.com) nie powinniśmy go zostawiać w obrazie jeśli nie używamy go podczas pracy kontenera. To samo się tyczy paczek zip/tar itp.

Jak obsłużyć takie przypadki. Można to zrobić na 2 sposoby.

1. Bespośrednie wykonanie skryptu bez zapisywania

{% highlight bash linenos %}
RUN curl -sL https://deb.nodesource.com/setup_8.x |bash -
{% endhighlight %}

2. Zapisanie i usunięcie w ramach jednej warstwy
{% highlight bash linenos %}
RUN curl -sL https://deb.nodesource.com/setup_8.x \
  && bash ./setup_8.x \
  && rm -rf ./setup_8.x
{% endhighlight %}


## Używanie odpowiednich obrazów

DockerHub jest pełny gotowych obrazów, lepszy i gorszych. Warto poświęcić wiecej czasu na znalezienie odpowiedniego obrazu dla siebie albo stworzyć go od podstaw. W trakcie tego artykułu zobaczyłem że nie potrzebnie używam tak dużego obrazu. Jest dostępny oficjalny obraz ruby który zawiera wszystko co jest mi potrzebne do pracy. Zobaczmy jak to będzie wyglądać:


{% highlight bash linenos %}
FROM ruby:2.4-slim

MAINTAINER Łukasz Żułnowski "lzulnowski@gmail.com"

RUN apt-get update && apt-get install -y -q \
  build-essential \
  wget \
  curl

RUN gem install jekyll bundler

RUN mkdir -p /app
WORKDIR /app

EXPOSE 4000

CMD bundle install && bundle exec jekyll serve -H 0.0.0.0
{% endhighlight %}
Jak widac zmieniony został tylko obraz którego użyliśmy jako bazy

{% highlight bash linenos %}
docker images blog
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
blog                latest              3143d1c2fa63        19 seconds ago      461MB
{% endhighlight %}

No i to jest optymalizacja, obraz zmniejszony został o więcej niż połowę.

Przy tworzeniu Dockerfile'a trzeba brać pod uwagę całkiem inne aspekty niż podczas tradycyjnego stawiania środowiksa.
Te kilka trików pozwoli na tworzenie lekkich obrazów a w dodatku mamy wszystko pod kontrolą. 
