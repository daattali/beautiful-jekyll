---
layout: single
title: pytorch(2) tensor control
tags: [pytorch, tensor]
categories: pytorch
---

Pytorch 튜토리얼을 참고하였다.

## 텐서
Pytorch에서는 텐서를 사용해서 모델의 입력과 출력 및 매개변수들을 encoding한다.  
Numpy의 ndarray와 유사하며, Automatic differentiation ([Autograd](https://tutorials.pytorch.kr/beginner/basics/autogradqs_tutorial.html)) 에
 최적화 되어있다.
기본적으로 필요한 모듈은 다음과 같다.  
```python
import torch
import numpy as np
```
  
  
## 텐서 초기화
1. 데이터로 부터 직접 생성
```python
data = [[1,2],[3,4]]
x_data = torch.tensor(data)
```
   
2. Numpy 배열로 생성   
from_numpy를 이용한다.
```python
np_array = np.array(data)
x_np = torch.from_numpy(np_array)
```

3. 다른 텐서로 생성  
ones_like, zeros_like, rand_like 등을 사용한다.

```python
x_ones = torch.ones_like(x_data)
# 속성을 override.
x_rand = torch.rand_like(x_data, dtype=torch.float)
```
   
4. 상수값 사용
```python
shape = (2,3,)
ones_tensor = torch.ones(shape)
```
## 텐서 속성 확인.
tensor에는 shape, dytpe, device 등 다양한 attribute가 있다. dir(tensor)로 가능한 속성을 확인할 수 있다.
```python
tensor = torch.rand((3,4))
print(f"Shape : {tensor.shape}, DataType : {tensor.dtype}, Device : {tensor.device}")
```
   
   
## 텐서 연산
pytorch는 여러 텐서 연산을 지원한다. [링크](https://pytorch.org/docs/stable/torch.html)   
각 연산들은 GPU에서 실행할 수 있다. .to 메소드를 사용할 수 있다.
보틍은 nn.module 상속한 모델을 만들어서 모델에 직접 .to을 적용한다.
```python
import torch.cuda

if torch.cuda.is_available()
 tensor = tensor.to("cuda")

```
    

아래와 같이 인덱싱과 슬라이싱도 numpy처럼 사용할 수 있으며, cat, stack을 이용해 합칠 수 있다.
```python
tensor = torch.ones((4,4))
print(f"First row:{tensor[0]}, First col:{tensor[:,0], Last col:{tensor[...,-1]}")
# cat 함수 : 차원수는 그대로 하되, 특정 차원(dim)의 요소를 concat
# 아래의 결과로는 (4,12)의 shape를 가진 텐서가 나옴.
print(torch.cat([tensor, tensor, tensor], dim=1))
# stack은 dim으로 설정한 차원을 추가한다.
# 아래의 결과로는 (4,4,3). dim=1이면 (4,3,4)
print(torch.stack([tensor, tensor, tensor], dim=1))
```  
   

두 텐서간의 산술연산
```python
# matrix multiplicaton
y1 = tensor @ tensor.T
y2 = tensor.matmul(tensor.T)
out = torch.matmul(tensor,tensor.T)
# element-wise product
z1 = tensor * tensor
z2 = tensor.mul(tensor)
out = torch.mul(z1,z2)
```
  
  
single-element 연산, 텐서의 요소값이 하나로 aggregate된다.
```python
agg = tensor.sum()
# item()을 사용해 python 숫자값으로 변환가능.
agg_item = agg.item()
print(agg_item,type(agg_item))
```

## Numpy bridge
CPU상에서 텐서와 Numpy 배열은 메모리 공간을 공유하므로, 하나가 변경되면 다른 하나도 변경된다.
```python
t = torch.ones(5)
n = t.numpy()
# in-place 연산
t.add_(1)
print(f"t:{t}, n:{n}")
# 새로 할당할 경우에는 결과가 다름.
t = t.add(1)
print(f"t:{t}, n:{n}")
```

## @ 참고
https://tutorials.pytorch.kr/beginner/basics/quickstart_tutorial.html
