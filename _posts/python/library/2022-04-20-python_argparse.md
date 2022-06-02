---
layout: single
title: 커맨드라인 인자 파싱용 파이썬 라이브러리  (argparse)
tags: [python, python library, argparse]
categories: python_lib
---



## 1.모듈 임포트
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
type으로 입력되어야 하는 인자의 형식을 지정할 수 있고, dest로 실제 attribute에 저장되는 값, default로 기본값을 정할 수 있다.

name or flags 인자에서   
- 인자는 positional 인자와 optional 인자가 있으며, 인자의 이름 앞에 -가 붙어 있으면 optional, 아니면 positional 인자로서 필수로 지정해야 한다.
- 인자의 이름에는 -와 _을 쓸 수 있으나, python 기본 문법은 변수명에 -를 허용하지 않기 때문에, 인자의 이름에 -가 들어갔다면 args.인자로 접근하려면 -를 _로 바꿔 주어야 한다.

action 인자에서는 커맨드라인에서 args 입력 시, 어떤 행동을 할지 정한다.   


- **store** : 기본값으로 지정된 action이며, 설정한 인자를 단순히 저장한다.
```
>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo')
>>> parser.parse_args('--foo 1'.split())
Namespace(foo='1')
```
- **store_const** : const 인자에 의해 지정된 값을 저장한다.
```
>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', action='store_const', const=42)
>>> parser.parse_args(['--foo'])
Namespace(foo=42)
```
- store_true : 인자를 설정하면 true값을 반환한다. store_false로 false값을 지정할 수도 있다.
```commandline
>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', action='store_true')
>>> parser.add_argument('--bar', action='store_false')
>>> parser.add_argument('--baz', action='store_false')
>>> parser.parse_args('--foo --bar'.split())
Namespace(foo=True, bar=False, baz=True)

```


 3. args = parser.parse_args(args=None, namespace=None)    
 : 인자를 파싱해 객체로 저장한다. 

## 3. 참고
https://docs.python.org/ko/3/howto/argparse.html#id1
https://greeksharifa.github.io/references/2019/02/12/argparse-usage/
