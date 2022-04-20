---
layout: post
title: paper-review-template
subtitle: pape-review
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [paper-review]
---
# Paper Title
Using an EfficientNet-LSTM for the recognition of single Cow’s motion
behaviours in a complicated environment

## Keyword
Behaviour recognition, Livestock, EffecientNet, BiFPN, LSTM

## Summary   
### why did you choice this?
가축 행동 인식을 위한 딥러닝 모델 서치 및 제안서 작업.


### what did authors try to accomplish?
behaviour recogn 문제에서, 소를 기준으로 기존 LSTM 기반 모델보다 더 나은 예측 성능(Accuracy)을 얻기 위한 모델 구조 변경.   

 
### what were the key elements of the approach?
1. cow's video frames에서 spatial feature를 효과적으로 뽑기 위해 Efficient Net을 사용하였다.   
2. EfficientNet의 3~5 layers에 대해 효과적으로 characteristic feature를 fusion함.   
3. 2까지에서 추출된 behavior information은 BiLSTM으로 보내지고, 이후 subnet인 attension layers를 거쳐 time-series에 대해 축적된 information을 바탕으로
빠르고 정확하게 행동 인식을 한다.   

### what can you use yourself? 
- 현재 고려하고 있는 제안서 작업에는 keypoint를 model input으로 사용할 것인데, 논문에서 제안한 모델 뒷단의 LSTM+Attension parts를 응용해 새로운 모델을 제안할 수 있을 것 같다.   


### what other references do you want to follow?
- 주어진 key points에 대해 behavior recogn을 한 논문들을 더 찾아봐야 겠다.  
- 이 논문은 single cow에 대해서만 결과를 냈으며, 만약 video에 다른 객체가 추가된다면
- 유사 도메인에서 attension 모듈을 사용한 예시를 확인할 필요가 있다.

## methods
### data description (input, output)
1009x 90sec(average)의 video clips으로 구성되며, fps는 25임.


output은 haviour classes, [feeding, lying, standing, walking, drinking]임.


### model or algorithm
![Crepe](https://s3-media3.fl.yelpcdn.com/bphoto/cQ1Yoa75m2yUFFbY2xwuqw/348s.jpg)


### result (with eval-indicators)




## New knowledge



## After review



