FROM jekyll/jekyll

COPY --chown=jekyll:jekyll Gemfile .
COPY --chown=jekyll:jekyll Gemfile.lock .

RUN bundle install --quiet --clean

RUN chown -R jekyll:jekyll /srv/jekyll
CMD ["jekyll", "serve"]