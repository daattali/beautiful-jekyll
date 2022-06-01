---
layout: single
title: 숫자를 포함한 파일이름을 naturally하게 정렬하는 라이브러리 (natsort)
tags: [python library, natsort]
categories: python_lib
---

## 1.모듈 임포트
natsorted 함수만 거의 사용됨.   
```python
from natsort import natsorted
```
   
소스 : https://github.com/SethMMorton/natsort    

## 2.모둘 사용해 정렬
숫자가 포함된 폴더 이름을 정렬 시, 빌트인 정렬 함수처럼 1, 10, 2.. 이런식으로 정렬되지 않고 1,2, 10 이렇게 "naturally"하게 정렬됨.

아래는 모듈 설명 :   
When you try to sort a list of strings that contain numbers, the normal python sort algorithm sorts lexicographically, so you might not get the results that you expect:   
```
>>> a = ['2 ft 7 in', '1 ft 5 in', '10 ft 2 in', '2 ft 11 in', '7 ft 6 in']
>>> sorted(a)
['1 ft 5 in', '10 ft 2 in', '2 ft 11 in', '2 ft 7 in', '7 ft 6 in']
```
Notice that it has the order ('1', '10', '2') - this is because the list is being sorted in lexicographical order, which sorts numbers like you would letters (i.e. 'b', 'ba', 'c').       
    
natsort provides a function natsorted that helps sort lists "naturally" ("naturally" is rather ill-defined, but in general it means sorting based on meaning and not computer code point). Using natsorted is simple:     
```
>>> from natsort import natsorted
>>> a = ['2 ft 7 in', '1 ft 5 in', '10 ft 2 in', '2 ft 11 in', '7 ft 6 in']
>>> natsorted(a)
['1 ft 5 in', '2 ft 7 in', '2 ft 11 in', '7 ft 6 in', '10 ft 2 in']
```
natsorted identifies numbers anywhere in a string and sorts them naturally. Below are some other things you can do with natsort (also see the examples for a quick start guide, or the api for complete details).