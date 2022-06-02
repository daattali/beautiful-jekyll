---
layout: single
title: PyTorch Distributed(2) DP
tags: [pyTorch, pytorch distributed, DDP]
categories: pytorch
permalink: categories/pytorch/pytorch_distribute2
work: 1
---

# Introduction
DP는 one process & multi-gpu로 실행할 수 있는 데이터 병렬 처리를 모듈 수준에서 구현하는 패러다임을 말한다.   
이 패러다임에 해당하는 모듈인 torch.nn.DataParallel은 일종의 컨테이너인데, 입력 데이터는 mini-batch로 학습시킬 때 1 batch를 GPU마다 동일하게 분할하여 학습한다.  
아래 파이토치 설명에 따르면 입력데이터 이외에 모델 등은 GPU별로 동일하게 복사된다.   
> This container parallelizes the application of the given module by splitting the input across the specified devices by chunking in the batch dimension (other objects will be copied once per device).   

따라서 batch size는 gpu개수보다 크거나 같아야 한다.   

# DP 모듈을 이용한 학습 과정
![img.png](img.png)
아래는 forward 과정이며, backward 비슷한 방식으로 진행된다.
### 1. Scatter mini-batch inputs to GPUs
mini-batch 데이터를 GPU별로 분할한다. 차원 변환을 통해 0번째 dim은 gpu dim이 된다.  
tuple, list 또는 dict type 등은 shallow copy된다. 
### 2. Replicate model on GPUs
moodel이 각 GPU별로 복제된다.
### 3. Parallel forward passes
력데이터를 모델에 순전파시켜 GPU별 output을 얻는다.
### 4. Gather outputs on GPU-1
output을 모두 합쳐 1 batch에 대한 output이 최종적으로 얻어진다.

# Discussion
실제로는 GIL로 인한 성능 문제로 DDP를 많이 사용하게 되며, 자세한 내용은 아래 Reference들을 참고한다. 
   
# Reference 
[공식문서](https://pytorch.org/docs/stable/generated/torch.nn.DataParallel.html)  
[참고 블로그 - 사용방법](https://hongl.tistory.com/291)  
[참고 블로그(Medium)](https://medium.com/huggingface/training-larger-batches-practical-tips-on-1-gpu-multi-gpu-distributed-setups-ec88c3e51255)



