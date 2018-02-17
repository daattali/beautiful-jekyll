FROM jekyll/jekyll

WORKDIR /srv/jekyll
COPY Gemfile .
COPY Gemfile.lock .

RUN gem install bundler
RUN bundle install --quiet --clean

EXPOSE 4000

ENTRYPOINT ["jekyll", "serve"]
