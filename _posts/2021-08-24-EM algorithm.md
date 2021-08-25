---
layout : post
title : EM algorithm
subtitle : bayesian, applied statistics
date : 2021-08-24
#categories:
tags : [datascience, bayesian, applied statistics in SNU]
toc_sticky : true
use_math : true
comments: true 
---

이 글은 서울대학교 정성규 교수님의 응용통계 강의 EM algorithm 내용을 정리한 것입니다.

### EM-algorithm

주요 개념:  optimization / missingness / parameter estimation



결측치가 존재하면 likelihood가 매우 복잡해지는데 EM 알고리즘은 이 경우에 문제를 단순화 시켜 모수 추정을 돕는다 .

##### E-step(expectation) & M-step(maximization)

※ E-step :

파라미터 값을 알고 있다면 결측치를 쉽게 채워넣을 수 있을 것이다. 파라미터값을 모른다면 현재까지의 얻어낸 파라미터 추정량을 사용해서 log-likelihood의 기댓값을 찾기 위한 함수를 만들어 낸다.(이 기댓값으로 결측치를 대신한다) (결측치가 변수인 경우 그 분포를 찾아내어 기댓값으로 결측치를 대체할 수 있다)(어찌되었든 결측치를 찾아내는 것이 핵심!!!)

나중에 내용이 나오겠지만 Q function을 찾아내서 이를 최대화 하는데 기댓값 안에 들어가는 함수가 가능도 함수이기에 모수에 대한 가능도함수 혹은 데이터들의 결합분포 두가지 측면에서 모두 사용가능하다.

※ M-stpe : 

모든 데이터를 가지고 있다면 MLE 를 구하기 쉬울 것이다. 그렇지 않은 경우 E-step에서 찾은 log-likelihood의 기댓값을 최대하하는 parameter값으로 추정한다. 



아래는 EM 알고리즘 기본 유제를 풀이한 것이다.(이는 GMM(Gaussian Mixture Model 의 학습과 관련이 있다는 것을 알게 되었다!)


<img src='{{"/assets/img/EM1-1.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>

<img src='{{"/assets/img/EM1-2.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>



###### Formal EM algorithm

※ E-step :

compute 'Q-function'

$$
\begin{align} Q(\theta | \theta^{(t)}) = E\{logL(\theta | Y_{obs},Y_{mis})|y_{obs},\theta^{(t)}\} \\ = E\{logf(Y_{obs},Y_{mis} | \theta)|y_{obs},\theta^{(t)}\}
\end{align}
$$


※ M-step : Maximize Q - function

$$
\theta^{(t+1)} = argmax_\theta Q(\theta | \theta^{(t)})
$$
 

아래 문제는 포아송 mixture 모델에 대한 EM 알고리즘 문제이다.

풀이를 하면서 잊지 말아야할 것은 E - step에서는 결측치를 기존 모수들을 가지고 업데이트 해준다는 것이다.

또한 결측치를  업데이트 할 때, 아래첨자 i 는 고려하지 않는데 이는 업데이트할 모수들이 모두 j와 관계있는 변수이기 때문이다.

<img src='{{"/assets/img/EM6-1.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>

<img src='{{"/assets/img/EM6-2.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>

<img src='{{"/assets/img/EM6-3.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>

<img src='{{"/assets/img/EM6-4.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>



###### The nature of EM

1. Ascent property

쉽게 생각해보자. EM알고리즘은 로그가능도의 값을 최대화 하는값이므로 Q - function을 계속 높이려고 할 것이다.


$$
- H(\theta | \theta^{(t)}) = log f(y_{obs};\theta) - Q(\theta | \theta^{(t)})
$$

이 값은 

$$
\theta = \theta^{(t)}
$$

일 때 최소가 된다.

<img src='{{"/assets/img/EM3.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>



ascent property을 증명하는 또 다른 수식이 있는데 여기서는 surrogate function 인 G - function 을 찾아내어 이를 최대화 하는 것이 EM 알고리즘과 같은 것임을 보이고 있다. 

<img src='{{"/assets/img/EM4.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>

<img src='{{"/assets/img/EM5.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>

2. Convergence order

$$
\epsilon^{(t)} = x^{(t)} - x^*
$$

일 때,


$$
lim_{t \rightarrow \infty} \epsilon^{(t)} = 0 \ \ \& \ \ lim_{t \rightarrow \infty} \frac {|\epsilon^{(t+1)}   |}{|\epsilon^{t}   |^\beta} = c \\ where \ \ c \neq 0 \ \  \& \ \beta>0 
$$

를 만족하는 beta 값을 order of convergence라고 한다. 

이 값이 클수록 수렴속도는 빠르나 robustness를 희생해야 한다. 뉴턴법이나 할선법(secant method)가 수렴 속도가 빠르다.



3.  the EM mapping

$$
mapping \ \ \ \Psi : \Theta \rightarrow \Theta
$$

에 대해

$$
\theta^{(t+1)} = \Psi(\theta^{(t)})
$$

을 EM mapping 이라 하자. 프사이의 값은 데이터와 문제에 의해 항상 바뀐다. 



만약 EM 알고리즘이 수렴한다고 가정하면,

$$
\hat \theta = \Psi(\hat \theta)
$$

이고 Taylor's expansion은

$$
\Psi( \hat\theta) \approx \Psi( \theta^{(t)}) + \Psi'( \theta^{(t)})(\hat \theta - \theta^{(t)})
$$

이고 알고리즘의 수렴성에 의해서 

$$
\hat \theta = \Psi( \hat\theta) \ \ \& \ \ \theta^{(t+1)} = \Psi( \theta^{(t)})
$$

$$
\frac {|\hat \theta - \theta^{(t+1)}|}{|\hat \theta - \theta^{(t)}|} \ \approx \Psi'(\theta^{(t)})
$$

이 때 t 가 무한대로 갈 때 우변의 값이 C로 수렴하고, C 값이 작을 수록 수렴 속도가 빠르다.
<img src='{{"/assets/img/EM2.jpg"| relative_url}}'  width="70%" height="70%" title="1" alt='relative'>
