---
layout: single
title: pytorch(1) basic process
tags: [pytorch]
categories: pytorch
---

요약하면 다음과 같다.   
1. 학습을 위한 필요 모듈 임포트
2. 데이터 전처리 (이미 전처리된 torchvision.datasets 등을 이용할 수 있음)
3. 데이터 로더 생성 (DataLoader로 datasets을 batch 단위의 iterable 객체로 만듦.)
4. 모델 정의 (nn.module 등)
5. 최적화 함수 정의 (optimizers, loss functions 등)
6. 학습 함수 정의 (epoch마다 호출, dataloader로 batch 단위의 data load 후 loss 계산 후 역전파해 weight 최적화)
7. 테스트 함수 정의 (학습된 모델 사용, test dataloader 사용)
8. 학습 및 테스트
   
  
## 데이터 작업


파이토치에는 데이터 작업을 위한 기본 요소로 torch.utils.data.DataLoader와 torch.utils.data.Dataset이 있다.
- Dataset은 샘플과 정답을 저장하고, DataLoader는 Dataset을 순회 가능한 객체(iterable)로 감싼다.
- TorchVision은 도메인 특화 라이브러리를 데이터셋과 함께 제공하고 있다.
```python
import torch
from torch import nn
from torch.utils.data import DataLoader
from torchvision import datasets
from torchvision.transforms import ToTensor

torch.__version__
print(torch.cuda.device_count())
```
    
## 데이터 준비

데이터를 준비한다. 여기서는 torchvision 모듈을 이용해 FashionMNIST를 불러온다
```python
# Download training data from open datasets.
training_data = datasets.FashionMNIST(
    root="data",
    train=True,
    download=True,
    transform=ToTensor(),
)

# Download test data from open datasets.
test_data = datasets.FashionMNIST(
    root="data",
    train=False,
    download=True,
    transform=ToTensor(),
)
``` 

## 데이터 로딩

- 데이터로더를 이용해 dataset을 iterable 객체로 감싸고, 학습 시 데이터를 batch 단위로 불러올 수 있도록 한다.
- 데이터로더를 통해 자동화된 배치, 샘플링, 섞기, 및 다중 프로세스로 데이터 불러오기를 지원한다.
- 데이터로더는 객체에 대한 input과 label을 묶음(batch)로 반환한다.


```python
batch_size = 64

# Create data loaders.
train_dataloader = DataLoader(training_data, batch_size=batch_size)
test_dataloader = DataLoader(test_data, batch_size=batch_size)

for X, y in test_dataloader:
    print(f"Shape of X [N, C, H, W]: {X.shape}")
    print(f"Shape of y: {y.shape} {y.dtype}")
    break
```


  
## 모델 정의


PyTorch에서 신경망 모델은 nn.Module을 상속받은 클래스를 생성해 정의한다.
- __init__ 함수에서 신경망의 계층(layer)들을 정의하고 forward 함수에서 신경망에 데이터를 어떻게 전달할지 지정한다.
- GPU로 신경망을 이동시켜 연산을 가속할 수 있다. device라는 변수를 만들고, cuda를 사용가능한 경우, "cuda"를 아닌 경우 "cpu"를 변수로 넣는다.

```python
# Get cpu or gpu device for training.
device = "cuda" if torch.cuda.is_available() else "cpu"
print(f"Using {device} device")

# Define model
class NeuralNetwork(nn.Module):
    def __init__(self):
        super(NeuralNetwork, self).__init__()
        self.flatten = nn.Flatten()
        self.linear_relu_stack = nn.Sequential(
            nn.Linear(28*28, 512),
            nn.ReLU(),
            nn.Linear(512, 512),
            nn.ReLU(),
            nn.Linear(512, 10)
        )

    def forward(self, x):
        x = self.flatten(x)
        logits = self.linear_relu_stack(x)
        return logits

model = NeuralNetwork().to(device)
print(model)
```
  
## 최적화 함수


모델 학습을 위해 loss function과 optimizer가 필요하다.
```python
loss_fn = nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(model.parameters(), lr=1e-3)
```
  
## train 함수

각 epoch마다 실행할 train 함수를 만든다. batch로 제공되는 학습 데이터 셋에 대한
예측을 수행하고, 예측 오류를 역전파해 weight를 최적화한다.
```python
def train(dataloader, model, loss_fn, optimizer):
    size = len(dataloader.dataset)
    for batch, (X, y) in enumerate(dataloader):
        X, y = X.to(device), y.to(device)

        # 예측 오류 계산
        pred = model(X)
        loss = loss_fn(pred, y)

        # 역전파
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if batch % 100 == 0:
            loss, current = loss.item(), batch * len(X)
            print(f"loss: {loss:>7f}  [{current:>5d}/{size:>5d}]")
```
  
## test 함수

모델 성능 확인을 위해 테스트 셋을 사용한다.
```python
def test(dataloader, model, loss_fn):
    size = len(dataloader.dataset)
    num_batches = len(dataloader)
    model.eval()
    test_loss, correct = 0, 0
    with torch.no_grad():
        for X, y in dataloader:
            X, y = X.to(device), y.to(device)
            pred = model(X)
            test_loss += loss_fn(pred, y).item()
            correct += (pred.argmax(1) == y).type(torch.float).sum().item()
    test_loss /= num_batches
    correct /= size
    print(f"Test Error: \n Accuracy: {(100*correct):>0.1f}%, Avg loss: {test_loss:>8f} \n")
```
  
## 학습

epoch을 여러번 거쳐서 학습이 되도록 한다.
```python
epochs = 5
for t in range(epochs):
    print(f"epoch {t+1}\n---------------")
    train(train_dataloader, model, loss_fn, optimizer)
    test(test_dataloader, model, loss_fn)
print("Done!")
```
  
## @ 참고

https://tutorials.pytorch.kr/beginner/basics/quickstart_tutorial.html
