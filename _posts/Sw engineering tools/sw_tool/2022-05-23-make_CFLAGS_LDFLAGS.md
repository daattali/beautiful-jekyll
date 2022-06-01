---
layout: single
title: make FLAG 옵션
tags: [make]
categories: sw_tool
---

FLAG(옵션)에 대해 정의

##CFLAGS 
일반적인 컴파일 옵션들을 선언해 줌.  
```commandline
CFLAGS+= -DCUDNN -I/usr/local/cuda-11.1/include
```
-I : include할 head 파일들의 path를 지정함.

## LDFLAGS 
ld 링커 library에 관한 설정을 선언해 주는 부분
```commandline
LDFLAGS+= -L/usr/local/cuda-11.1/lib64 -lcudnn
```
-L  라이브러리가 있는 PATH 설정
이런 식으로 사용할 library PATH나 library를 명시적으로 해줌.   

## @ 참고
https://wh00300.tistory.com/201
http://doc.kldp.org/KoreanDoc/html/GNU-Make/GNU-Make-4.html
