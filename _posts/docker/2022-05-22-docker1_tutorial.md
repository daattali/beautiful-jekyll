---
layout: archive
title: docker(1) tutorial
subtitle: docker 사용법 기초
tags: docker
categories: docker
---
도커는 컨테이너 기반의 가상화 오픈플랫폼이다. 리눅스용으로 만들어졌지만, 윈도우에서도 사용이 가능은 하다.     
컨테이너는 도커 플랫폼에서 구성할 수 있는 독립적인 환경으로, 구동하려는 어플리케이션에 필요한 것들을 모두 포함한다.  

## 시작하기
포스팅에서 아래 내용들을 배우게 된다.
- Build and run an image as a container
- Share images using Docker Hub
- Deploy Docker applications using multiple containers with a database
- Running applications using Docker Compose


```commandline
docker run -d -p 80:80 docker/getting-started
```
- -d - detach mode (background mode)로 컨테이너를 동작
- p 80:80 - port 매핑, host의 80번 포트를 컨테이너의 80번 포트로 매핑.
  (-d 와 -p는 -dp로 줄여쓸 수 있다.)
- docker/getting-started - 사용할 도커 이미지


## @ 참고
도커 공식 문서 get start : https://docs.docker.com/get-started/  
도커란 무엇인가 : https://velog.io/@ckstn0777/%EB%8F%84%EC%BB%A4%EB%9E%80-%EB%AC%B4%EC%97%87%EC%9D%B8%EA%B0%80
도커 입문 (컨테이너 기초부터 서버 배포까지) : https://www.44bits.io/ko/post/easy-deploy-with-docker  
윈도우에서 도커 설치시 WSL2 installation is incomplete 문제 : https://blog.nachal.com/1691