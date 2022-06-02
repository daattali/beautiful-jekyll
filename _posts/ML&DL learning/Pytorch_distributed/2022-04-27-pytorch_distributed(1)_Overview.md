---
layout: single
title: PyTorch Distributed(1) Overview
tags: [pyTorch, pytorch distributed, parallelism]
categories: pytorch
permalink: categories/pytorch/pytorch_distribute1
work: 1
---
# Introduction
파이토치를 이용한 병렬 및 분산 학습 전반 (튜토리얼)에 대해 정리하였다.

# Overview
distributed 패키지는 아래 3가지 카테고리로 구성된다.
### Distributed Data-Parallel Training(DDP):   
 하나의 프로그램으로 여러 다른 데이터 셋을 돌린다는 패러다임으로, 모델이 모든 프로세스에 복제된 뒤, 각 프로세스는 다른 입력데이터 셋을 가지게 된다.   
gradients의 계산과 계산값은 프로세서간 communications을 통해 공유되고 모델 학습을 가속화한다.   

### RPC-Based Distributed Training(RPC):   
 RPC는 remote procedure call의 약자로 별도의 원격 제어를 위한 코딩 없이 다른 주소 공간에서 함수나 프로시저를 실행할 수 있게 하는 프로세서간
통신 기술이다. 즉 RPC는 함수가 로컬에 위치하든 원격 위치에 위치하든 동일한 코드를 이용할 수 있다.   
RPC-Based Distributed Training 기법은 DDP 개념을 머신의 경계없이 분산된 자원으로 학습할 수 있는 패러다임을 말한다.   

### Collective Communication(c10d):   
 c10d 라이브러리는 하나의 그룹 내에서 프로세스간 텐서 통신을 지원한다.
collective communication APIs(e.g. all_reduce and all_gather)와 P2P communicationsAPIs(e.g. send and isend)를 제공한다.   
   DDP와 RPC(ProcessGroup Backend)들이 c10d에 빌트인되어있는데, 전자는 collective communications, 후자는 P2P communication에 사용된다.  
 개발자는 DDP와 RPC APIs가 워낙 다양한 분산 학습 시나리오에 맞게 설계되었기 때문에, 이런 raw communication API를 자주 사용하지는 않겠지만, 통신구조를 low하게 수정하고 싶을 때 사용될 수 있다.  
 일례로 distributed parameter averaging이 있다. DDP를 이용해 gradients를 통신하는 것 대신, 역전파 이후 모든 모델의 파라미터에 대한 평균값을 계산할 때 쓰일 수 있다.   
 이 방법을 통해 텐서 통신에 대한 finer-grain control이 가능하다.   
 대신 DDP에 의한 성능 최적화를 포기해야 하는 단점이 있다. 

# Data Parallel Training
## 개발 환경에 따른 distributed 모듈 사용 방법
### single machine with one GPU : Normal
데이터와 모델이 한 개의 GPU로 충분하고, 학습속도가 중요하지 않은 경우. 여분의 GPU가 없는 개인 PC에서 돌릴 때 사용하는 방법이다.
 
### single machine with multi GPU : DataParallel
적은 코드의 수정만으로 여러 개의 GPU를 사용해 학습을 가속화시킬 경우, 그러나 후술할 GIL문제로 DDP를 사용하지, DP를 사용하는 경우는 많지 않다.
   
### single machine with multi GPU : DistributedDataParallel
DataParallel을 쓸 때 보다는 좀 더 코드를 손봐서 학습속도를 더 개선하고 싶은 경우. 그렇다고 해도 코드가 많이 추가되지는 않는다.   
아래 내용을 참고했을 때, GIL 문제로 DataParallel을 사용하기보다 DistributedDataParallel을 사용하는 것이 좋다.
[링크](https://pytorch.org/tutorials/intermediate/ddp_tutorial.html)
![img_3.png](../Pytorch_basic/img_3.png)

### multi machine : DistributedDataParalled and launching script
여러 개의 머신을 사용할 경우 사용되는 패러다임. single machine과 다르게 launcing script를 사용한다고 하는데, 아래 내용을 참고한다.
[참고](https://github.com/pytorch/examples/blob/main/distributed/ddp/README.md)
   
### 컴퓨팅 자원이 수시로 변경되는 상황 : torch.distributed.elastic
컴퓨팅 자원이 실시간으로 추가되거나 제거되야 하면, out-of-memory 등 여러 학습 오류를 발생시킬 수 있는데, 이런 문제들을 해결하기 위해 fine-grained하게 
통신 방법을 설정해줄 필요가 있다. 이럴 때 사용되는 것이 elastic이라고 한다. 

## 관련된 주요 패키지
### torch.nn.DataParallel (DP)
DataParallel package는 single process multi-thread 병렬화 방식으로 단 한줄의 소스 코드만 추가하면 multi-GPU를 사용하게 해준다.  
따라서 사용하기 매우 편한 장점이 있지만, GIL로 인해 쓰레드간 GIL 경합, 복제 모델의 반복 당 생성, 산란 입력 및 수집 출력으로 인한 추가적인 오버헤드가 발생해 성능이 좀 떨어진다고 한다.
   
### torch.nn.DistributedDataParallel (DDP)
DDP는 multi-process parallelism을 사용하며 GIL 문제로 인한 문제를 줄여 single machine에서도 학습 속도를 개선한다.
  
DDP와 관련된 글이다.
- [DDP NOTES](https://pytorch.org/docs/stable/notes/ddp.html) : DDP 패키지를 사용한 간단한 구현 예시를 보여준다. DDP를 처음접할 때 보면 좋은 문서.
- [Getting Started with Distributed Data Parallel](https://tutorials.pytorch.kr/intermediate/ddp_tutorial.html) : DDP를 사용한 학습에서 공통적으로 나타나는 문제
(unbalanced workload, checkpointing and multi-device model)들을 설명한다. 

### torch.distributed.elastic
분산학습 환경에서 failure recovery가 필요할 때 쓰이는 패키지. DDP를 쓸 때 out-of-memory(OOM) error가 발생할 수 있지만, 이를 복구하는 것은 DDP가 할 수 없다. (예상처럼 try-expect문 구조를 사용하지 못한다고 한다.)
이는 DDP 연산이 모든 프로세스에 대해 동기화되어야 하기 때문인데, 아래 자세한 내용이 나와있다.
![img_1.png](img_1.png)

# RPC-Based Distributed Training
단순히 data parallelism으로 처리할 수 없으며 원격 컴퓨팅 자원이 사용되어야 하는 training paradigm들, 예를 들면 parameter server paradigm, distributed pipeline parallelism, reinforcement learning applications with multiple observers or agents
와 같은 좀 일반화된 분산 학습 상황에서 RPC가 사용될 수 있다.

## 관련된 주요 패키지
### torch.distributed.rpc
4가지 주요 구성 요소가 있다.
- RPC는 remote 호출할 함수를 remote worker 에서 돌아갈 수 있도록 지원한다.
- RRef는 remote 객체의 생애주기를 조절한다. [RRef notes](https://pytorch.org/docs/stable/rpc/rref.html#remote-reference-protocol)
- Distributed Autograd는 기존 autograd 엔진에서 로컬 머신 바운더리보다 더 확장된 분산 autograd를 지원한다. [Distributed autograd design](https://pytorch.org/docs/stable/rpc/distributed_autograd.html#distributed-autograd-design)
- Distributed Optimizer는 이 distributed autograd engine로 계산된 gradient로 개별 worker들의 파라미터를 업데이트한다.

# Discussion
- multi-machine에서 DDP 개념이 적용되려면, 결국 remote procedure call이 필요한 것이 아닌가 생각되는데 관련된 라이브러리를 사용해보면서 감을 익혀야 할 것 같다.

# Appendix
- 개발된지 좀 된 오픈 소스에서 torch.distributed.launch를 쓰는 경우가 있는데, deprecated되었으므로 torchrun를 사용하여야 한다. [관련내용](https://pytorch.org/docs/stable/elastic/run.html)


# Reference 
[overview 공식](https://tutorials.pytorch.kr/beginner/dist_overview.html)    
[torch tutorial](https://tutorials.pytorch.kr/intermediate/dist_tuto.html)

  