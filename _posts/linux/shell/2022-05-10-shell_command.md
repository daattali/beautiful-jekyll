---
layout: single
title: Shell 기초 및 명령어
tags: [shell, cat, export]
categories: linux
---
셸은 커널에 명령을 전달하기 위한 사용자 인터페이스 역할을 한다. 셸 명령어는 실제로 커널에 실행할 내용을 의미한다.
# 셸
## 리눅스에서 셸의 위치
HW - Kernel - **Shell** - 사용자 or 응용프로그램   
  
## 사용가능한 Shell 보기
cat /etc/shells  
  
## 현재 사용중인 Shell 보기
echo $SHELL

bash Shell은 실행 후 /etc/profile과 /etc/bashrc를 참조함.

## 명령어 위치 확인
nvcc 명령어를 확인할 수 있다.
```commandline
which nvcc  
```

## 명령어 경로 추가
```commandline
export PATH=$PATH:/bin:/usr/local 
```

## 환경 변수 확인
export 명령어로 바로 확인 가능.
```commandline
export
```

## 명령어 실행 순서*
- 각 파일의 맨 아랫 부분에 실행 코드를 추가할 때 기준이다.
1. /etc/profile.d/ 에 있는 모든 sh 파일 (가령, /etc/profile.d/test.sh)
2. /etc/profile : 전역적인 파일로 **모든 사용자가 로그인 시 실행**
3. /etc/bashrc : 전역적인 파일로 logic 과정 없이 **bash shell이 실행하는 경우에만 실행.**
4. ~/.bashrc : 지역적인 파일로 특정 사용자가 bash shell을 실행할 때 실행됨.
5. ~/.bash_profile : 전역적인 파일로 특정 사용자가 shell을 실행할 때 실행됨.
6. (.bash_profile 이 없으면 .profile을 실행. .bash_profile 이 1순위이고, 우선순위에 따라 1개만 실행된다.)

## Login shell 과 Non-Login shell
/etc/profile와 ~/.bash_profile는 로그인이 필요하지 않은 경우에 실행된다.  
반면에 /etc/bashrc, ~/.bashrc는 로그인이 필요한 상황에서 쓰인다.  

## Jupyter의 shell :Ipython
주피터는 ipython을 shell로 사용하기 때문에 bashrc가 붙은 파일에 있는 명령어가 실행되지 않음에 주의한다.  
profile에 있는 명령어는 사용이 가능하다.

## @ 참고
chrome-extension://hmigninkgibhdckiaphhmbgcghochdjc/pdfjs/web/viewer.html?file=https%3A%2F%2Fcs.kangwon.ac.kr%2F~leeck%2FIR%2Fbash.pdf
[환경변수](https://blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=koromoon&logNo=220793570727)
[zetawiki](https://zetawiki.com/wiki/Bash_%EC%89%98%EC%8A%A4%ED%81%AC%EB%A6%BD%ED%8A%B8_%EC%83%81%EB%8C%80%EA%B2%BD%EB%A1%9C_%EC%96%BB%EA%B8%B0)   
[Shell script tutorial](https://www.shellscript.sh/quickref.html)   
[colon을 이용한 참조](https://tldp.org/LDP/abs/html/parameter-substitution.html#EXPREPL1)   
[명령어 실행 순서](https://zetawiki.com/wiki/Profile_bashrc_bash_profile_%EC%8B%A4%ED%96%89_%EC%88%9C%EC%84%9C)  