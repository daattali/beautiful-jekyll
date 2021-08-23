---
layout : post
title : robust regression
subtitle : breakdown value, influence function
date : 2021-08-23
#categories:
tags : [datascience, robust statistics]
toc_sticky : true
use_math : true
comments: true
---

 Anomaly detection by robust statistics 논문을 읽던 중 1학기 응용통계 시간에 배웠던 breakdown value와 influence fucntion에 대한 개념이 헷갈려 이와 관련된 내용을 다시 한번 정리해보았다.

아래 정리한 내용은 모두 서울대학교 통계학과 정성규 교수님의 '응용통계 1' 수업에서 기반한 것이다.



### Robust regression



#### sensitivity

How sensitive is the estimator when F varies?



민감도이기 때문에 도함수와도 연관되어 있다.

우선 influence function을 정의하기 위해서는 statistical functional 의 개념을 이해해야 한다.

statistical functional이란 함수들의 함수를 의미한다. 즉 family of distribution을 
$$
\mathbb{F} = \{F_\theta : \theta \in \Theta\}
$$
라고 정의할 때,
$$
\eta = T(F)
$$
를 statistical functional이라 한다.



이에 대한 예로

※ mean
$$
T(F) = \int x dF(x)
$$
를 생각하면 statistical functional 에 대한 이해가 좀 더 쉬울 것이다.

이때
$$
\hat{T(F)} \approx T(F)
$$
라고 가정하고 F가 변화할 때 추정량이 많이 바뀌지 않는다면 파라미터값이 robust 한 성질을 가지고 있지 않을까 생각할 수 있다.

문제는 F가 함수라는것에 있다. 만약 F가 실수라면 그 점에서의 미분값을 생각하면 변화율을 알 수 있을 것이다. 그러나 F가 함수라면 F가 바뀔 때 T(F)의 변화율은 어떻게 구할 수 있을까?



이를 위해 Cateaux differentiable이라는 개념이 등장한다.

functional T 가 F에서 Gateaux differentiable 하다는 것은 
$$
\exists \ a(X) ( a : X \rarr \mathbb{R})\ \ such \ that\ \ G \in \mathbb{F}
$$
에 대해서
$$
lim_{\epsilon \rarr 0} \frac{T(F + \epsilon(G-F)) - T(F)}{\epsilon} = lim_{\epsilon \rarr 0} \frac{T((1-\epsilon)F + \epsilon G) - T(F)}{\epsilon} = \int a(x)dG(x) = T_a(G)
$$
으로 정의된다. 

T(G)의 값을 Gateaux derivative 라고 하고 a(x)의 값을 gradient라고 하면 Gateaux derivative는 방향도함수와 같다. 

(아래 사진에서 GAteaux derivative가 방향도함수와 같은지 알 수 있습니다. 방향도함수는 gradient와 방향벡터 v 와의 내적으로 구성되는데 내적은 결국 원소들의 곱에 대한 합과 동일하기 때문에 Gateaux derivative에서 a(x)는 gradient와 동일하다.)

<그림>



이제 influential function을 정의하기 위해 필요한 마지막 notation들을 정의한다
$$
\delta_x(u) = \begin{cases} 0\ \  if \ \ u<x \\ 1 \ \ if \ \ u>x\end{cases}
$$
여기서 델타는 point mass


$$
F_{x \cdot \epsilon} = (1 - \epsilon)F + \epsilon \delta_x
$$
이를 'perturbed F at X with fraction epsilon'



###### influence function 정의

CDF F에 대해 functional T가 존재하고 이때 
$$
IF(x ; T,F) = lim_{\epsilon \rarr 0} \frac {T(F_{x \cdot \epsilon}) - T(F)}{\epsilon}
$$
을 influence function이라 정의한다. 

이때

1. fluence function은 T에 대한 measure이다

2. 만약 T가 Gateaux differentiable이면 
   $$
   \exists \ \ a(x) \ \ s.t. \ \ IF(x;T,F) = \int a(u)d\delta_x(u) = a(x)
   $$
   이므로 결국 influence function은 gradient a(x)와 동일.



3. gross error sensitivity
   $$
   r^*(T,F) = sup_x |IF(x;T,F)|
   $$

4. 만약 

$$
r^*(T,F) < \infty
$$

가 성립하면 functional T는 F에 대해 B-robutst 하다고 말한다. 

5. 3에서 언급한 gross error sensitivity 를 고려할 때 population breakdown point를 다음과 같이 정의한다

$$
\epsilon^* = inf\{\epsilon : b(\epsilon) = \infty\} \\ where \ \  b(\epsilon) =sup_x|T(F) - T(F_{x \cdot \epsilon})|
$$





#### resistency

How many gross outliers to make the estimator garbage? ( ※ gross outlier? 특정 값이 무한대로 매우 큰 값)



###### breakdown point 정의

파라미터 추정량 
$$
T_n = T_n(x_1, x_2, ... , x_n)
$$
에 대해 이 추정량에 대한 breakdown point를 

"the largest fraction of gross outliers before T_n becomes arbitarily large" 라고 정의한다. 

이 정의에 따르면 평균의 경우, 평균을 이루는 원소 중에서 단 하나의 값만이라도 매우 커진다면 통계량이 크게 변화하기 때문에 breakdown point = 0 이라고 할 수 있다. 상대적으로 median의 경우는 breakdown point 가 크고 breakdown point 가 클수록 resistance가 크다고 말할 수 있다.

<사진>

수식으로 breakdown point를 정의해보자.
$$
let \ \ R_m(T_n ; x_1,...x_n) = Max_{i_1},...,{i_m} \{Sup_{y_1},...,{y_m} |T_n(z_1,...,z_n)\}
\\
where \ \ Z_j = \begin{cases} x_j & if \ \ j \notin \{i_k\}_{k=1} ^ m \\ y_k & if \ \  j = i_k \ for \ some \ k=1,2,...,m \end{cases}
$$


즉 x 중에서 임의로 m 개를 골라서 매우 큰 y로 바꾸었을 때의 값이 R_m 이 되는 것이다.



이 때 breakdown pointf를 입실론이라 하면
$$
\epsilon_n^* = \frac{1}{n} Max\{m;R_m(T_n;x_1,...,x_n) < \infty\}
$$
 



