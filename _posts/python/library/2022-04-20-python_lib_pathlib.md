---
layout: single
title: 파일 접근을 위한 파이썬 라이브러리 (pathlib)
tags: [python library, pathlib]
categories: python_lib
---
기존에는 폴더에 있는 파일들을 접근하려면 os 라이브러리를 사용했다. 하지만, os는 문자열로
파일 및 폴더를 접근하기 때문에 객체로 좀 더 편리하게 접근하기 위해서는 pathlib를 사용해야 한다.

## 1.모듈 임포트
아래와 같은 형식으로 공식 문서에 제시되어 있다.
```
from pathlib import Path
```
## 2. 기능
1. 서브 디렉터리 나열:
```python
p = Path('')
[x for x in p.iterdir() if x.is_dir()]
```
iterdir()는 경로가 디렉터리를 가리킬 때, 디렉터리 내용의 경로 객체를 산출한다.
2. 폴더 트리에 있는 파이썬 소스 파일 나열:
```python
list(p.glob('**/*.py'))
```
glob(patten)는 경로 객체에 대해 pattern과 일치하는 모든 파일을 산출한다.   
rglob(patten)도 쓸 수 있다. 이는 앞에 "**/"가 추가된 Path.glob()을 호출하는 것과 같다.
3. 폴더 트리 내에서 탐색:
```python
p = Path('/etc')
q = p / 'init.d' / 'reboot'
q.resolve()
```
resolve는 경로 객체의 절대경로를 구하며, 새로운 경로 객체가 반환된다.
4. 경로가 있는지, 폴더인지 조회:
```python
q.exist()
q.is_dir()
```
5 파일 이름/확장자: 
파일 이름은 name 속성을 참조한다. **주의할 점은 name 속성은 확장자까지 포함**한다는 것이다.   
만약 확장자를 포함하지 않으려면 stem 속성을 참조한다.
```python
PurePosixPath('my/library/setup.py').name
#'setup.py'
PurePosixPath('my/library/setup.py').stem
#'setup'

```

6. with_name, with_suffix를 이용한 파일 이름, 확장자 변경:  
{path obj}.with_name({new_name})로 파일 이름만 새롭게 변경 가능. 변경이 반영되려면 shutil.move 등을 이용해 파일 자체를 바꿔야 한다.  
마찬가지로 with_suffix를 사용할 수 있다.

```python
>>> p = Path('foo')
>>> p.with_name('fool')
>>> p.with_suffix('mp4')
>>> shutil.move(video, p)
```

7. path의 개별 요소에 접근:  
parts를 사용한다.
```python
>>> p = PurePath('/usr/bin/python3')
>>> p.parts
('/', 'usr', 'bin', 'python3')

>>> p = PureWindowsPath('c:/Program Files/PSF')
>>> p.parts
('c:\\', 'Program Files', 'PSF')
```  

8. joinpath()를 이용한 경로 결합
```python
Path.home().joinpath('python', 'scripts', 'test.py')
```

9. 기타 프로퍼티
parents : 경로의 조상 들에 대한 접근을 제공하는 시퀀스. parent라고 하면 바로 윗단계 부모를 의미한다. 
```python
>>> p = PureWindowsPath('c:/foo/bar/setup.py')
>>> p.parents[0]  #parent와 동일
PureWindowsPath('c:/foo/bar')
>>> p.parents[1]
PureWindowsPath('c:/foo')
>>> p.parents[2]
PureWindowsPath('c:/')

```
## @참고
https://docs.python.org/ko/3/library/pathlib.html