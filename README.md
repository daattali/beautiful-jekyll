Local development:
Build image:
 docker build -t blog .
Run docker: 
 docker run -d -p 4000:4000 --name blog -v "$PWD":/srv/jekyll blog

