---
layout: post
title:  "Docker Command Catalog"
date:   2020-10-18 5:45:00 PM
categories: Docker
---

[Docker run details]: https://loneshark99.github.io/images/docker_run_details.png
[Remove docker image]: https://loneshark99.github.io/images/docker_images.png
[Docker logs]: https://loneshark99.github.io/images/docker_logs.png
[Docker exec]: https://loneshark99.github.io/images/docker_exec.png
[Docker run]: https://loneshark99.github.io/images/docker_run.png
[Docker volume]: https://loneshark99.github.io/images/docker_volume.png

Delete a Docker Image :: docker image rm {imageid}
![alt text][Remove docker image]

Inspect docker logs ::  docker logs {containerId or name}
![alt text][Docker logs]

Docker exec runs a command inside the docker container.

docker exec -it {containerId/name} sh
![alt text][Docker exec]

Link a container to one another, makes it possible for one container to talk to another container. In this example we are creating
a second container with redis client to access the redis server. This is done through --link and giving the name of the container.

-i interactive
-t terminal 

![alt text][Docker run]

docker run is used to create a container.
docker exec is used to interact with a running container.

External to a container we can create volumes. Volumes are used to read and write data which persists.

![alt text][Docker volume]


![alt text][Docker run details]