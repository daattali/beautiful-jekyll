FROM jekyll/jekyll

COPY --chown=jekyll:jekyll Gemfile .
COPY --chown=jekyll:jekyll Gemfile.lock .

RUN bundle install --quiet 

RUN chown -R jekyll:jekyll /srv/jekyll
CMD ["jekyll", "serve"]
# CMD ["jekyll", "serve", "--livereload", "--livereload_port", "25003", "--incremental"]
# CMD ["jekyll", "serve", "--livereload", "--livereload_port", "25003", "--incremental", "--trace", "--verbose"]
