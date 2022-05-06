---
layout: post
title: pytorch(2) tensor control
subtitle: pytorch의 tensor 조작
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [pytorch, tensor]
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

  
## @ 참고
https://tutorials.pytorch.kr/beginner/basics/quickstart_tutorial.html
