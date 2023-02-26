---
layout: post
title:  "One of the use cases of docker"
date:   2021-12-31 19:01:00 PM
categories: Docker
---

Docker is a great tool for deployment and sharing software. I use github pages for my blog and I find it pretty useful since it doesnt come in my way of writing. Authoring the markdown files is all that is needed for pushing a new blog entry. 

Earlier when I used github pages which is run using [Jekyll static site generator](https://jekyllrb.com/), I needed to install  Jekyll and its dependencies like Ruby gems etc. This always gave me one or the other issue when trying to build the blog locally. However, I found [jekyll-docker image](https://github.com/envygeeks/jekyll-docker) which wraps Jekyll and other ruby gems in an image.

All I need to do now, is expose by blog repository through docker volumes for building and running my site.

Steps I take now :


* Clean up any containers if not needed. Using the command substitution we can delete all the containers. This is a nice use of bash command substitution to get all the container Id.

```
    docker rm $(docker ps -aq)
```

* Add a new blog entry and build the site.

```
    export JEKYLL_VERSION=3.8 
    docker run --rm -v="$PWD:/srv/jekyll" -it jekyll/jekyll:$JEKYLL_VERSION jekyll build
```


* Run the site locally

```
    docker run --rm --volume="$PWD:/srv/jekyll" --publish [::1]:4000:4000 jekyll/jekyll jekyll serve
```

* Push the branch to github using [gh CLI](https://cli.github.com/manual/) Tool.

```
    gh pr create
```
