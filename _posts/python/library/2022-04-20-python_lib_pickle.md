---
layout: single
title: 객체를 저장하는 라이브러리 (pickle)
tags: [python library, pickle]
categories: python_lib
---

파이썬에 있는 모든 객체는 pickle로 저장이 가능하다. pickle은 바이너리 파일로 저장이 된다.

## 1.모듈 임포트
내장 라이브러리라 import만 하면 된다.
```
import pickle
```
## 2. 기능
예시데이터 : test_dict = {'name': "test", 'pw': "1234"}

# 데이터 로드
with open('filename.pkl', 'rb') as f:
	data = pickle.load(f)

# 데이터 저장
with open('filename.pkl', 'wb') as f:
	pickle.dump(test_dict, f, protocol=pickle.HIGHEST_PROTOCOL)

```
## @참고
https://docs.python.org/3/library/pickle.html
https://seing.tistory.com/95


