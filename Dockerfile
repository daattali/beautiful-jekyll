FROM jekyll/jekyll

COPY Gemfile .
COPY Gemfile.lock .

RUN chown -R jekyll: . && bundle install --clean

CMD ["jekyll", "serve"]
