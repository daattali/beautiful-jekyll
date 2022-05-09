---
layout: post
title: python library : pathlib
subtitle: 파일 접근을 위한 내장 라이브러리
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [python library, pathlib]
---
기존에는 폴더에 있는 파일들을 접근하려면 os 라이브러리를 사용했다. 하지만, os는 문자열로
파일 및 폴더를 접근하기 때문에 객체로 좀 더 편리하게 접근하기 위해서는 pathlib를 사용해야 한다.

## 1.모듈 설치
아래와 같은 형식으로 공식 문서에 제시되어 있다.
```
from pathlib import Path
```
## 2. 기능
1. 서브 디렉터리 나열:
```commandline
p = Path('')
[x for x in p.iterdir() if x.is_dir()]
```
iterdir()는 경로가 디렉터리를 가리킬 때, 디렉터리 내용의 경로 객체를 산출한다.
2. 폴더 트리에 있는 파이썬 소스 파일 나열:
```commandline
list(p.glob('**/*.py'))
```
glob(patten)는 경로 객체에 대해 pattern과 일치하는 모든 파일을 산출한다.
3. 폴더 트리 내에서 탐색:
```commandline
p = Path('/etc')
q = p / 'init.d' / 'reboot'
q.resolve()
```
resolve는 경로 객체의 절대경로를 구하며, 새로운 경로 객체가 반환된다.
4. 경로가 있는지, 폴더인지 조회:
```commandline
q.exist()
q.is_dir()
```

## @참고
https://docs.python.org/ko/3/library/pathlib.html