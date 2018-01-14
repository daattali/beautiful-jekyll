FROM jekyll/jekyll

WORKDIR /srv/jekyll
COPY Gemfile .

RUN gem install bundler
RUN bundle install --clean --quiet

EXPOSE 4000

CMD [ "/usr/gem/bin/bundle", "exec", "/usr/local/bundle/bin/jekyll", "serve", "--port", "4000", "--host", "0.0.0.0" ]

STOPSIGNAL 2
