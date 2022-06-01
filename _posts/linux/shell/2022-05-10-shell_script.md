---
layout: single
title: Shell Script 문법
tags: [sh, shell script]
categories: linux
---

셸 스크립트는 쉘에게 명령할 일련의 스크립트를 적은 sh 확장자 파일을 의미한다.

## #!/bin/bash
 보통의 sh파일 맨 윗줄에 선언되는데, #!는 SheBang 이라는 기호로, 
 **스크립트를 실행할 인터프리터의 절대경로**를 지정하는 역할을 한다.    
만약 스크립트가 여러 다른 환경에서 사용될 수 있다면, #!/usr/bin/env를 사용한다.    

## 매개변수
스크립트 이름 다음에 공백 문자로 구분된 인자를 매개변수라고 부른다. 문자열 안에 표
- $0 : 실행한 셸 스크립트 파일명
- $$ : 셸의 PID
- $# : 전달받은 인자 개수
- $1, $2, ... : 위치 매개변수
- $* or $@ : 모든 매개변수
 
## 특수참조
- ${VAR=aaa} : VAR가 사용되지 않으면 VAR에 aaa를 대입하고 VAR를 반환한다. 기본값을 설정한다고 볼 수 있다. 
- ${VAR:-aaa} : VAR가 사용되지 않거나 NULL인 경우 aaa를 반환한다. 단, VAR값은 업데이트되지 않는다.
  
## 경로얻기
- $(dirname $0) : 상대경로를 얻음
```commandline
root@test:/tmp# tree aa
aa
├── bb
└── test.sh

1 directory, 1 file

root@test:/tmp# cat aa/test.sh
script_dir=$(dirname $0)
echo $script_dir


root@test:/tmp# sh aa/test.sh 
aa
root@test:/tmp# bash aa/test.sh 
aa


root@test:/tmp# cd aa/bb
root@test:/tmp/aa/bb# sh ../test.sh 
..
root@test:/tmp/aa/bb# bash ../test.sh 
..


root@test:/tmp/aa/bb# sh /tmp/aa/test.sh 
/tmp/aa
root@test:/tmp/aa/bb# bash /tmp/aa/test.sh 
/tmp/aa

```
사용 예시
```commandline
#!/usr/bin/env bash
# Copyright (c) OpenMMLab. All rights reserved.

NNODES=${NNODES:-1}
NODE_RANK=${NODE_RANK:-0}
MASTER_ADDR=${MASTER_ADDR:-"127.0.0.1"}
GPUS=$1
PORT=${PORT:-29500}

PYTHONPATH="$(dirname $0)/..":$PYTHONPATH \
python -m torch.distributed.launch --nnodes=$NNODES --node_rank=$NODE_RANK --master_addr=$MASTER_ADDR \
    --nproc_per_node=$GPUS --master_port=$PORT $(dirname "$0")/cus_ntu_pose_extraction.py --launcher pytorch ${@:3}
# Any arguments from the third one are captured by ${@:3}

```

## @ 참고
chrome-extension://hmigninkgibhdckiaphhmbgcghochdjc/pdfjs/web/viewer.html?file=https%3A%2F%2Fcs.kangwon.ac.kr%2F~leeck%2FIR%2Fbash.pdf

[zetawiki](https://zetawiki.com/wiki/Bash_%EC%89%98%EC%8A%A4%ED%81%AC%EB%A6%BD%ED%8A%B8_%EC%83%81%EB%8C%80%EA%B2%BD%EB%A1%9C_%EC%96%BB%EA%B8%B0)   
[Shell script tutorial](https://www.shellscript.sh/quickref.html)   
[colon을 이용한 참조](https://tldp.org/LDP/abs/html/parameter-substitution.html#EXPREPL1)   