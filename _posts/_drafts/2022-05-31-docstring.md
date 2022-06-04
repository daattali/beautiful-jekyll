---
layout: single
title: 문서화
tags: [docstring, google_style]
categories: python_clean
---

## 구글 스타일
```python
"""구글 스타일 문서화 문자열.

구글 스타일
===========

제목을 정할 때는 기존과 같습니다. `==`로 제목을 `--`로 소제목을
표현합니다. `참고해야 할 하이퍼링크`_ 가 있다면 아래 에 url 정의를
할 수 있습니다.

.. _참고해야 할 하이퍼링크:
    https://soma0sd.tistory.com/

Attributes:
    module_variable_1(int): 모듈 수준의 변수가 있는 경우 모듈의
      문서화 문자열에 `Attributes:` 섹션을 만들어서 표현합니다.

Example:
    예시를 기록합니다.

Todo:
    * 앞으로 할 것의 목록
    * `Todo`는 모듈이나 패키지, 함수, 클래스 등에 자유롭게
        사용할 수 있습니다.
    * 사용자 입장에서 서술하는 것이 좋습니다.
"""

def function(arg1: int, arg2: str) -> bool:
    """함수의 문서화 문자열.

    Args:
        arg1 (int): 사실 함수에 이미 매개변수 형태가 있다면
            굳이 괄호로 표시해 줄 필요는 없습니다.
        arg2: 들여쓰기와 콜론(`:`)이 매개변수와 설명을
            구분합니다.

    Returns:
        bool: 이 경우에도 형태가 소스코드에 이미 있다면
            굳이 반복해서 쓸 필요는 없습니다.

    Raises:
        AttributeError: 예외 설명이 필요한 경우.

    Yields:
        출력값이 무언가를 나열하는 경우.

    Note:
        함께 알아두어야 할 사항이 있는 경우.

    `Args`나 `Returns` 등 각 섹션 사이에는 빈 줄이 하나 필요합니다.
    """
    return True

```


## @ 참고
python docstring : https://wikidocs.net/16050  
document format : https://soma0sd.tistory.com/130