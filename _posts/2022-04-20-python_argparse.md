---
layout: post
title: python library : argparse
subtitle: 커맨드라인 인자 파싱을 위한 파이썬 표준 라이브러리
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [python library, argparse]
---



## 1.모듈 설치
```
import argparse
```
## 2. 사용
아래는 사용 예시.
```
import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('integers', metavar='N', type=int, nargs='+',
                    help='an integer for the accumulator')
parser.add_argument('--sum', dest='accumulate', action='store_const',
                    const=sum, default=max,
                    help='sum the integers (default: find the max)')

args = parser.parse_args()
print(args.accumulate(args.integers))
```
argparse는 깃허브에서 ML/DL 모델을 테스트할 때 하이퍼파라미터를 설정하기 위해 자주 사용된다.   
기본적으로 3가지 코드가 필요하다.     
1. parser = argparseArgumentParser(prog=None, usage=None, description=None, epilog=None, parents=[], formatter_class=argparse.HelpFormatter, prefix_chars='-', fromfile_prefix_chars=None, argument_default=None, conflict_handler='error', add_help=True, allow_abbrev=True, exit_on_error=True)     
: 새로운 ArgmentParser 객체를 만든다.
필수는 아니지만 description에 기재된 내용은 parser가 있는 파이썬 파일에 -h 옵션으로 실행 시 나오는 도움말에서 표시된다.
기타 다른 옵션들은 표준 문서 참고.   


2. parser.add_argument(name or flags...[, action][, nargs][, const][, default][, type][, choices][, required][, help][, metavar][, dest])   
: 인자를 추가한다. name or flags에는 인자의 이름 또는 string list가 포함 되는데, foo 또는 -f, --foo 이런 식.  
type으로 입력되어야 하는 인자의 형식을 지정할 수 있고, default로 기본값을 정할 수 있다.


3. args = parser.parse_args(args=None, namespace=None)    
 : 인자를 파싱해 객체로 저장한다. 

## 3. 참고
https://docs.python.org/ko/3/howto/argparse.html#id1
https://greeksharifa.github.io/references/2019/02/12/argparse-usage/
