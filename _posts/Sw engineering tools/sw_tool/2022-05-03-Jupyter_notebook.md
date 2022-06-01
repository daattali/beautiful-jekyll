---
layout: single
title: jupyter notebook 환경변수
tags: [jupyter notebook, environment variable]
categories: sw_tool
---

커맨드 창에서 실행한 명령어들이 주피터에서는 실행이 안되는 경우가 있다.  

jupyter notebook github issue 사항에 있는 아래 답변을 참고한다.

.bashrc affects bash, and then environment variables are inherited by anything you run from bash. So it won't affect something launched from a GUI shortcut, because that hasn't gone through bash. On a Linux system, you can set environment variables in .profile, which is run at login, so it should affect everything.

## 주피터 환경 확인
```commandline
%env

{'PATH': '/home/sglee/anaconda3/envs/yolo_v4/bin:/home/sglee/anaconda3/condabin:/usr/local/cuda-11.1/bin:/home/sglee/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin',
```

## 주피터 모듈 autoreload
외부에서 import한 모듈 수정 사항이 발생해도, reload하지 않으면 반영이 되지 않음.
```commandline
%load_ext autoreload
%autoreload 2
from mycode import my_func
```


## @참고
[관련 중요 질문](https://github.com/jupyter/notebook/issues/3704)
- https://docs.conda.io/projects/conda/en/latest/commands/create.html : 공식문서