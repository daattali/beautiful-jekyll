FROM mangar/jekyll:1.0

MAINTAINER Marcio Mangar "marcio.mangar@gmail.com"

RUN gem install jekyll -v 3.1.6
RUN gem install bundler

RUN gem install execjs
RUN gem install therubyracer
RUN gem install github-pages
RUN gem install jekyll-paginate
RUN gem install jekyll-seo-tag
RUN gem install jekyll-gist
RUN gem install json -v 1.8.3

RUN gem install minitest -v 5.9.0
RUN gem install colorator -v 0.1
RUN gem install ffi -v 1.9.10
RUN gem install kramdown -v 1.10.0
RUN gem install rouge -v 1.10.1
RUN gem install pkg-config -v 1.1.7
RUN gem install terminal-table -v 1.6.0
RUN gem install ethon -v 0.9.0
RUN gem install nokogiri -v 1.6.8
RUN gem install activesupport -v 4.2.6
RUN gem install html-pipeline -v 2.4.1
RUN gem install jekyll-watch -v 1.4.0
RUN gem install github-pages-health-check -v 1.1.0
RUN gem install jekyll-github-metadata -v 2.0.0
RUN gem install jekyll-mentions -v 1.1.2
RUN gem install jekyll-redirect-from -v 0.10.0
RUN gem install jemoji -v 0.6.2
RUN gem install github-pages -v 82



RUN mkdir -p /app
ADD ./ /app

WORKDIR /app

EXPOSE 4000

CMD bundle exec jekyll serve
