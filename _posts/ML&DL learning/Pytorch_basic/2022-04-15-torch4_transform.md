---
layout: single
title: pytorch(4) Transform
tags: [pytorch, transform]
categories: pytorch
---

Pytorch 튜토리얼을 참고하였다.
   
## Transform
모델에 입력으로 적합하도록 데이터를 변형한다. 데이터가 이미 모델 입력으로 fit하면 추가적인 처리가 필요없으므로 필요하지 않다.  
아래와 같이 datasets을 통해 데이터를 불러온 경우, feature를 처리하기 위한 **transform**과 label을 처리하기 위한 **target_transform이** 있다.
     
```python
import torch
from torchvision import datasets
from torchvision.transforms import ToTensor, Lambda

ds = datasets.FashionMNIST(
    root="data",
    train=True,
    download=True,
    transform=ToTensor(),
    target_transform=Lambda(lambda y: torch.zeros(10, dtype=torch.float).scatter_(0, torch.tensor(y), value=1))
)
```
## TOTensor()
ToTensor는 PIL Image나 Numpy ndarray 등 Tensor가 아닌 객체를 FloatTensor로 변환하고 값을 [0,1] 범위로 normalization한다.

## @ 참고
https://tutorials.pytorch.kr/beginner/basics/transforms_tutorial.html
