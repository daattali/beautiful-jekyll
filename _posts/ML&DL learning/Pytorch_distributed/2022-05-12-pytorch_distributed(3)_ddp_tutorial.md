---
layout: single
title: PyTorch Distributed(3) DDP
tags: [pyTorch, distributed data parallel processing, DDP]
permalink: categories/pytorch/pytorch_distribute3
categories: pytorch
---

# Introduction
DDP는 여러 machine(node)에서 실행할 수 있는 데이터 병렬 처리를 모듈 수준에서 구현한다.  
multi-process를 생성하고, process당 단일 DDP 인스턴스를 생성한다.   
DDP는 torch.distributed의 collective communication을 사용해 gradient를 동기화한다.   
   
단, 모델이 여러 대의 기기에 존재해야 하거나, 데이터 병렬화 패러다임에 맞지 않는 경우에는 RPC API를 참고한다. 
# 기본 개념
machine은 분산학습에서 node로 지칭한다.    
노드의 개수를 *N*, GPU의 개수를 *G*라고 하면, GPU의 총 개수는 world size *W*라고 하며,
각 node별로 돌아가는 process(DDP에서는 GPU와 동일) 개수는 *local world size L*로 나타낸다.   
**Rank**는 DDP에서 가동되는 process id로 global rank, local rank로 나뉜다.   
global rank는 전체 node에 가동되는 process id이며, local rank는 각 node 별 process id이다.

# 기본 사용법
## 작업 그룹 설정
```python
import os
import sys
import tempfile
import torch
import torch.distributed as dist
import torch.nn as nn
import torch.optim as optim
import torch.multiprocessing as mp

from torch.nn.parallel import DistributedDataParallel as DDP

# 윈도우 플랫폼에서 torch.distributed 패키지는
# Gloo backend, FileStore 및 TcpStore 만을 지원합니다.
# FileStore의 경우, init_process_group 에서
# init_method 매개변수를 로컬 파일로 설정합니다.
# 다음 예시:
# init_method="file:///f:/libtmp/some_file"
# dist.init_process_group(
#    "gloo",
#    rank=rank,
#    init_method=init_method,
#    world_size=world_size)
# TcpStore의 경우 리눅스와 동일한 방식입니다.

def setup(rank, world_size):
    os.environ['MASTER_ADDR'] = 'localhost'
    os.environ['MASTER_PORT'] = '12355'

    # 작업 그룹 초기화
    dist.init_process_group("gloo", rank=rank, world_size=world_size)

def cleanup():
    dist.destroy_process_group()
```
## DDP 모델 구성과 학습
이제 DDP로 감싼 Toy 모듈을 생성하고 더미 입력 데이터를 사용한다.      
DDP는 0순위 작업부터 DDP 생성자의 다른 모든 작업들에 모델의 상태를 전달한다.
```python
class ToyModel(nn.Module):
    def __init__(self):
        super(ToyModel, self).__init__()
        self.net1 = nn.Linear(10, 10)
        self.relu = nn.ReLU()
        self.net2 = nn.Linear(10, 5)

    def forward(self, x):
        return self.net2(self.relu(self.net1(x)))


def demo_basic(rank, world_size):
    print(f"Running basic DDP example on rank {rank}.")
    setup(rank, world_size)

    # 모델을 생성하고 순위 아이디가 있는 GPU로 전달
    model = ToyModel().to(rank)
    ddp_model = DDP(model, device_ids=[rank])

    loss_fn = nn.MSELoss()
    optimizer = optim.SGD(ddp_model.parameters(), lr=0.001)

    optimizer.zero_grad()
    outputs = ddp_model(torch.randn(20, 10))
    labels = torch.randn(20, 5).to(rank)
    loss_fn(outputs, labels).backward()
    optimizer.step()

    cleanup()


def run_demo(demo_fn, world_size):
    mp.spawn(demo_fn,
             args=(world_size,),
             nprocs=world_size,
             join=True)

```
    
 DDP는 하위 수준의 분산 커뮤니케이션 사항을 포함하여 로컬 모델과 크게 다르지 않게 사용가능하다.
gradient synchronization communications은 역전파 전달(backward pass)간 수행되어 역전파 계산과 겹쳐서 수행된다.

## 체크포인트 저장 및 읽기
DDP는 사용할 때 최적의 방법은 모델을 한 작업에만 저장하고 그 모델을 모든 작업에서 읽어오는 것이다.  
이 방법을 사용할 경우 저장이 완료되기 전에 읽어오는 작업이 시작되지 않도록 해야 하며, 모듈을 읽어올 때 다른 기기에서도 접근하지 않도록 적절한 map_location 인자를 제공해야 한다.
map_location값이 없을 경우, torch.load는 먼저 모듈을 CPU에서 읽어온 다음 각 매개변수가 저장된 위치로 복사하여 동일한 장치를 사용하는 동일 기기에서 모든 작업을 실행한다.
```python
def demo_checkpoint(rank, world_size):
    print(f"Running DDP checkpoint example on rank {rank}.")
    setup(rank, world_size)

    model = ToyModel().to(rank)
    ddp_model = DDP(model, device_ids=[rank])

    loss_fn = nn.MSELoss()
    optimizer = optim.SGD(ddp_model.parameters(), lr=0.001)

    CHECKPOINT_PATH = tempfile.gettempdir() + "/model.checkpoint"
    if rank == 0:
        # 모든 작업은 같은 매개변수로부터 시작된다고 생각해야 합니다.
        # 무작위의 매개변수와 변화도는 역전파 전달로 동기화됩니다.
        # 그럼으로, 하나의 작업은 모델을 저장하기에 충분합니다.
        torch.save(ddp_model.state_dict(), CHECKPOINT_PATH)

    # 작업 0이 저장한 후 작업 1이 모델을 읽어오도록 barrier()를 사용합니다.
    dist.barrier()
    # configure map_location properly
    map_location = {'cuda:%d' % 0: 'cuda:%d' % rank}
    ddp_model.load_state_dict(
        torch.load(CHECKPOINT_PATH, map_location=map_location))

    optimizer.zero_grad()
    outputs = ddp_model(torch.randn(20, 10))
    labels = torch.randn(20, 5).to(rank)
    loss_fn = nn.MSELoss()
    loss_fn(outputs, labels).backward()
    optimizer.step()

    # 파일삭제를 보호하기 위해 아래에 dist.barrier()를 사용할 필요는 없습니다.
    # DDP의 역전파 전달 과정에 있는 AllReduce 옵스(ops)가 동기화 기능을 수행했기 때문에

    if rank == 0:
        os.remove(CHECKPOINT_PATH)

    cleanup()
```

## 모델 병렬 처리를 활용한 DDP
모델 하나를 여러 노드에 분산시켜 학습이 가능하다. 
```python
class ToyMpModel(nn.Module):
    def __init__(self, dev0, dev1):
        super(ToyMpModel, self).__init__()
        self.dev0 = dev0
        self.dev1 = dev1
        self.net1 = torch.nn.Linear(10, 10).to(dev0)
        self.relu = torch.nn.ReLU()
        self.net2 = torch.nn.Linear(10, 5).to(dev1)

    def forward(self, x):
        x = x.to(self.dev0)
        x = self.relu(self.net1(x))
        x = x.to(self.dev1)
        return self.net2(x)
```
이는 다중 GPU 모델에서도 동일하게 사용될 수 있다. 대신 device_ids와 output_device를 설정하지 않아야 한다.
입력 및 출력 데이터는 어플리케이션 또는 모델 forward()에 의해 적절하게 장치에 배치된다.
```python
def demo_model_parallel(rank, world_size):
    print(f"Running DDP with model parallel example on rank {rank}.")
    setup(rank, world_size)

    # 작업을 위한 mp_model 및 장치 설정
    dev0 = (rank * 2) % world_size
    dev1 = (rank * 2 + 1) % world_size
    mp_model = ToyMpModel(dev0, dev1)
    ddp_mp_model = DDP(mp_model)

    loss_fn = nn.MSELoss()
    optimizer = optim.SGD(ddp_mp_model.parameters(), lr=0.001)

    optimizer.zero_grad()
    # 출력값은 dev1에 저장
    outputs = ddp_mp_model(torch.randn(20, 10))
    labels = torch.randn(20, 5).to(dev1)
    loss_fn(outputs, labels).backward()
    optimizer.step()

    cleanup()


if __name__ == "__main__":
    n_gpus = torch.cuda.device_count()
    assert n_gpus >= 2, f"Requires at least 2 GPUs to run, but got {n_gpus}"
    world_size = n_gpus
    run_demo(demo_basic, world_size)
    run_demo(demo_checkpoint, world_size)
    run_demo(demo_model_parallel, world_size)
```

# 분산 동기화 지점(distribute synchronization point)
DDP에서 생성자, 순전파 및 역전파의 전달 호출 지점이 분산 처리 동기화가 되는 지점이다.   
이때, 서로 다른 작업이라도 거의 동시에 동기화 지점에 진입해야 한다. 그렇지 않을 경우 대기시간 초과로 에러가 발생할 수 있는데, 이를 위해
작업간의 작업량을 적절히 분배하고, 시간 초과를 방지하기 위해 init_process_group 호출 시 충분한 timeout 값을 전달해야 한다.

# Discussion
- 대부분의 내용을 튜토리얼 문서에서 있는대로 서술했으나 직접 모듈을 사용해보면서 자세한 서술이 필요할 것 같다.

# Reference 
[공식문서](https://tutorials.pytorch.kr/intermediate/ddp_tutorial.html)
[pytorch로 분산 어플리케이션 개발하기](https://tutorials.pytorch.kr/intermediate/dist_tuto.html)
[DDP 동작 원리](https://hongl.tistory.com/292?category=927704)




