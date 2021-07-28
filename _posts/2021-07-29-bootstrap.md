---
layout : post
title : Boostrap
subtitle : data mining - bagging
date : 2021-07-28
#categories:
tags : [datascience, datamining, machinelearning]
toc_sticky : True
comments: true
---

bagging은 boostrap을 기반으로 한 앙상블 방법 중 하나 입니다. 다음 글에서는 bagging과 boosting에 대한 비교 글을 적을 예정인데 그에 앞서, bagging에서 빠질 수 없는 boostrap 에 대해 다시 한번 정리하고자 합니다.



#### 1. 경험분포함수



Sample
$$
\{X_1, X_2, ..., X_n\}\
$$
에 대해  모집단 분포함수 F의 추정치로 경험분포함수 
$$
\hat{F}_n(x) = \frac{1}{n} \sum I(X_i \leq x)
$$
를 고려하자.



일반적으로 경험분포함수는 다음과 같은 성질을 가진다
$$
n\hat{F}_n(x) =  \sum I(X_i \leq x) \ \ \sim B(n, F(x))
$$

$$
1. \ \ unbiased : E(\hat{F}_n(x)) = F(x) \\\\ 2. \ \ variance : \frac{1}{n}F(x)(1-F(x))
$$



#### 2. bootstrap 알고리즘

경험분포함수를 통해 볼 때, 모평균 F(x)는 표본평균으로 점추정 된다. 또한 중심극한정리를 통해 구간 추정 또한 가능하다. 그러나 소표본인 경우는 이와 다르다. Boostrap은 통계량에 대한 분포를 모르는 상황에서 이에 대한 구간추정을 만들어 낸다. 이는 처음에 가지고 있는 표본이 정규분포를 따르지 않아도 된다라는 데서 큰 이점을 갖는다.

##### step 1

반복 횟수를 k 라고 하면 표본에서 **등확률 복원추출**을 통해 새로운 표본 set을 만들어 낸다
$$
\{X_1, X_2, ..., X_n\}\ \longrightarrow X^{*(k)} = \{x_1^*,x_2^*,...,x_n^* \}\
$$

##### step 2

theta 에 대한 통계량 theta hat을 bootstrap 표본을 통해 추정한다. 즉
$$
\hat\theta  = \theta(X_1,X_2, ... , X_n) 
$$
을 추정하기 위해


$$
\hat\theta^{*(1)},\hat\theta^{*(2)},...,\hat\theta^{*(K)}
$$


에 대한 경험분포를 이용하는 것이다. 



즉, 표본을 활용해 모수를 추정하는 추정량을 구하고, 이 추정량에 대해 신뢰구간을 구하는 것처럼, 소표본의 경우에 등확률 복원추출을 통해 추정량에 대한 표준오차를 다시 추정해서 신뢰구간을 구할 수 있다는 것이다. 



추정량의 표준오차에 대한 Boostrap 추정
$$
\hat {se}(\hat\theta) = \sqrt{ \frac{1}{n-1} \sum^K (\hat\theta^{*(k)} - \bar{\hat\theta^*})    }
$$
추정량의 bias 에 대한 Boostrap 추정
$$
\hat{bias}(\hat\theta) = \bar{\hat\theta^*} - \hat\theta
$$


추정량에 대한 구간추정
$$
\hat\theta에 \ 대해 \ \hat\theta^{*(1)},\hat\theta^{*(2)},...,\hat\theta^{*(K)} \ 의\ \ \alpha / 2 \ 와 \ \  1-\ \alpha / 2 \ 분위수
$$

* 회귀계수에 대한 구간추정 또한 마찬가지이다.



#### 3. Bootstrap 알고리즘 실험 with R



R에서 boot 패키지 안의 aircondit 데이터는 기계의 고장간의 시간을 나타낸다.  이때 고장간의 시간이 모수가 lambda인 지수분포를 따른다고 할 때 이에 대한 최대가능도 추정값은
$$
\frac{1}{\bar{X}}
$$
이다. 이 때 MLE의 bias와 standard error 에 대한 boostrap 추정값을 구해보자



~~~R
set.seed(2020)
library(boot)
data("aircondit")
x=aircondit
rate = function(x, i){return(1/mean(as.matrix(x[i,])))}
boot(x, statistic = rate, R=2000)


#ORDINARY NONPARAMETRIC BOOTSTRAP


# Call:
# boot(data = x, statistic = rate, R = 2000)


# Bootstrap Statistics :
#      original      bias    std. error
# t1* 0.00925212 0.001210366 0.004185513

~~~





** 이 글은 서울시립대학교 통계학과 박창이 교수님의 통계 계산 과목의 강의자료를 참고했습니다.



 

