---
layout: post
title: PyTorch Distributed Overview
subtitle: pyTorch를 이용한 병렬 및 분산 학습 튜토리얼
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [python library, xml]
---
파이토치를 이용한 병렬 및 분산 학습 전반에 대해 정리하였다.

## 1. 개념
distributed 패키지는 아래 3가지 카테고리로 구성된다.
#### Distributed Data-Parallel Training(DDP):   
 하나의 프로그램으로 여러 다른 데이터 셋을 돌린다는 패러다임으로, 모델이 모든 프로세스에 복제된 뒤, 각 프로세스는 다른 입력데이터 셋을 가지게 된다.   
gradients의 계산과 계산값은 프로세서간 communications을 통해 공유되고 모델 학습을 가속화한다.   

#### RPC-Based Distributed Training(RPC):   
 RPC는 remote procedure call의 약자로 별도의 원격 제어를 위한 코딩 없이 다른 주소 공간에서 함수나 프로시저를 실행할 수 있게 하는 프로세서간
통신 기술이다. 즉 RPC는 함수가 로컬에 위치하든 원격 위치에 위치하든 동일한 코드를 이용할 수 있다.   
RPC-Based Distributed Training 기법은 DDP 개념을 머신의 경계없이 분산된 자원으로 학습할 수 있는 패러다임을 말한다.   

#### Collective Communication(c10d):   
 c10d 라이브러리는 하나의 그룹 내에서 프로세스간 텐서 통신을 지원한다.
collective communication APIs(e.g. all_reduce and all_gather)와 P2P communicationsAPIs(e.g. send and isend)를 제공한다. 
DDP와 RPC(ProcessGroup Backend)들이 c10d에 빌트인되어있는데, 전자는 collective communications, 후자는 P2P communication에 사용된다. 
 개발자는 DDP와 RPC APIs가 워낙 다양한 분산 학습 시나리오에 맞게 설계되었기 때문에, 이런 raw communication API를 자주 사용하지는 않겠지만, 통신구조를 low하게 수정하고 싶을 때 사용될 수 있다.
일례로 distributed parameter averaging이 있다. DDP를 이용해 gradients를 통신하는 것 대신, 역전파 이후 모든 모델의 파라미터에 대한 평균값을 계산할 때 쓰일 수 있다.
 이 방법은 계산으로 인한 . 대신 DDP에 의한 성능 최적화를 포기해야 하는 단점이 있다. 

 torch.distributed.launch 가 deprecated 되서 torchrun 사용해야 함.
https://pytorch.org/docs/stable/elastic/run.html




### @ 참고
1. torch tutorial  
https://tutorials.pytorch.kr/intermediate/dist_tuto.html

2. 한글 설명자료
https://hongl.tistory.com/291
https://medium.com/daangn/pytorch-multi-gpu-%ED%95%99%EC%8A%B5-%EC%A0%9C%EB%8C%80%EB%A1%9C-%ED%95%98%EA%B8%B0-27270617936b

4. RPC
https://ko.wikipedia.org/wiki/%EC%9B%90%EA%B2%A9_%ED%94%84%EB%A1%9C%EC%8B%9C%EC%A0%80_%ED%98%B8%EC%B6%9C