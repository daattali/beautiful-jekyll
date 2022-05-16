---
layout: post
title: PyTorch Distributed(3) DDP
subtitle: pyTorch를 이용한 분산 데이터 병렬 처리(DDP)
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [pyTorch, distributed data parallel processing, DDP]
---
DDP는 여러 machine(node)에서 실행할 수 있는 데이터 병렬 처리를 모듈 수준에서 구현한다.  
multi-process를 생성하고, process당 단일 DDP 인스턴스를 생성한다.   
DDP는 torch.distributed의 collective communication을 사용해 gradient를 동기화한다.   
### 기본 개념
machine은 분산학습에서 node로 지칭한다.    
노드의 개수를 *N*, GPU의 개수를 *G*라고 하면, GPU의 총 개수는 world size *W*라고 하며,
각 node별로 돌아가는 process(DDP에서는 GPU와 동일) 개수는 *local world size L*로 나타낸다.   
**Rank**는 DDP에서 가동되는 process id로 global rank, local rank로 나뉜다.   
global rank는 전체 node에 가동되는 process id이며, local rank는 각 node 별 process id이다.


### 기타


### @ 참고
[공식문서](https://tutorials.pytorch.kr/intermediate/ddp_tutorial.html)    
[DDP 동작 원리](https://hongl.tistory.com/292?category=927704)