FROM jekyll/jekyll

WORKDIR /srv/jekyll
COPY Gemfile .

RUN gem install bundler
RUN bundle install --clean --quiet

EXPOSE 4000

# See https://github.com/daattali/beautiful-jekyll/issues/302#issuecomment-357528536
CMD [ "/usr/gem/bin/bundle", "exec", "/usr/local/bundle/bin/jekyll", "serve", "--port", "4000", "--host", "0.0.0.0" ]

STOPSIGNAL 2
