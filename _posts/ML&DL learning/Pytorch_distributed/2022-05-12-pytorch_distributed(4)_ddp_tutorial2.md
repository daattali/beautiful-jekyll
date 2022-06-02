---
layout: single
title: PyTorch Distributed(4) DDP 패키지 적용
tags: [pyTorch, distributed data parallel processing, DDP]
permalink: categories/pytorch/pytorch_distribute4
categories: pytorch
---

# Introduction
[이전 포스팅](/categories/pytorch/pytorch_distribute3)


# Setup
```python
"""run.py:"""
#!/usr/bin/env python
import os
import torch
import torch.distributed as dist
import torch.multiprocessing as mp

def run(rank, size):
    """ Distributed function to be implemented later. """
    pass

def init_process(rank, size, fn, backend='gloo'):
    """ Initialize the distributed environment. """
    os.environ['MASTER_ADDR'] = '127.0.0.1'
    os.environ['MASTER_PORT'] = '29500'
    dist.init_process_group(backend, rank=rank, world_size=size)
    fn(rank, size)


if __name__ == "__main__":
    size = 2
    processes = []
    for rank in range(size):
        p = Process(target=init_process, args=(rank, size, run))
        p.start()
        processes.append(p)

    for p in processes:
        p.join()
```
# Discussion

# Reference 
[공식문서](https://tutorials.pytorch.kr/intermediate/ddp_tutorial.html))




