---
layout: post
title: [behaviour recongition] livestock 행동 인식
subtitle: EfficientNet-biLSTM+attention 사용한 paper 리뷰
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
가축 행동 인식을 위한 딥러닝 모델 서치.



### what did authors try to accomplish?
가축(소)의 behaviour classes, [feeding, lying, standing, walking, drinking]를 예측 시, 기존 C3D, LSTM 기반 모델보다 더 나은 예측 성능(Accuracy)을
위해 모델 구조 변경.   

 
### what were the key elements of the approach?
1. cow's video frames에서 spatial feature를 효과적으로 뽑기 위해 Efficient Net을 사용하였다.   
2. EfficientNet의 3~5 layers에 대해 효과적으로 characteristic feature를 fusion함.   
3. 2까지에서 추출된 behavior information은 BiLSTM으로 보내지고, 이후 subnet인 attension layers를 거쳐 time-series에 대해 축적된 information을 바탕으로
빠르고 정확하게 행동 인식을 한다.   

### what can you use yourself?     </br>
- 현재 고려하고 있는 제안서 작업에는 keypoint를 model input으로 사용할 것인데, 논문에서 제안한 모델 뒷단의 LSTM+Attension parts를 응용해 새로운 모델을 제안할 수 있을 것 같다.   


### what other references do you want to follow?
- 주어진 key points에 대해 behavior recogn을 한 논문들을 더 찾아봐야 겠다.  
- 이 논문은 single cow에 대해서만 결과를 냈으며, 만약 video에 다른 객체가 추가된다면
- 유사 도메인에서 attension 모듈을 사용한 예시를 확인할 필요가 있다.



## methods
### data description (input, output)
1009x 90sec(average)의 video clips으로 구성되며, fps는 25임.
![image](https://user-images.githubusercontent.com/33012030/163295371-0ec238b1-b292-4992-b7ce-93bbc360b630.png)
input은 16 frame의 video clips이며 1 frame은 512 x 512의 RGB 영상. </br>
(undivided behaviour video test의 경우 60 frame에 30 frame을 step으로 줌)
output은 haviour classes, [feeding, lying, standing, walking, drinking]에 대한 softmax 출력값(확률)이 나옴.


### model or algorithm
**EfficientNet-LSTM network framework digram**     
EfficientNet Block의 P1/2, P2/4, P3/8 에서 2,4,8은 Scale factor를 의미한다.  
![image](https://user-images.githubusercontent.com/33012030/163295415-717e8ee2-9b01-4393-ae33-9f8e39862055.png)
     
BiFPN에 대해 부가적인 설명을 하자면, FPN(Feature Pyramid Network)에서 Downsampling(PANet에도 적용)과 Jump connection이 적용되었다.
![image](https://user-images.githubusercontent.com/33012030/163301093-f158020b-f085-4f09-9c3f-be6647984a6e.png)


**EfficientNet-LSTM layers 별 특징**     
각 layer별 output feature dimension (w,h,c)이 제시되어 있다. Fc의 d는 FC layer 은닉층 노드 개수다. 
![image](https://user-images.githubusercontent.com/33012030/163295426-2242cda5-6d89-4a18-a123-ece43e6bc5a0.png)



**Fusion Layer**     
이 논문의 contribution이라고 할 수 있는 fusion layer이다. BiFPN의 output인 5 scale feature maps이 fusion block으로 입력된다.     
7 layer (4x4x64)는 w방향으로 x4 upsampling, .. 3 layer (64x64x64)는 x1/4 downsampling된 후 concat되어 16x80x64의 fusion feature가 완성된다.     
![image](https://user-images.githubusercontent.com/33012030/163310305-00208133-42aa-411e-a087-2bf9e706ad63.png)



**Subnet으로 활용된 Attention-BiLSTM 구조**</br>
NLPDPTJ 일반적으로 사용되는 Attention-biLSTM 구조. 이미 BiFPN에서 정제된 feature가 나오는데 왜 embedding 층이 나오있는지 모르겠다.. 예시 이미지인가?
![image](https://user-images.githubusercontent.com/33012030/163295476-481ef742-12e8-4a9b-abb5-32af673b2420.png)


**undivided videos 분석 시 방법**</br>
긴 영상의 경우 60frame씩 30 step frame을 input으로 넣어 연속으로 behaviour 예측. </br>
![image](https://user-images.githubusercontent.com/33012030/163326154-2bb114c2-ab7d-4482-8355-bb2a117c61b0.png)


### result (with eval-indicators)
정확도는 97.87%로 높게 나온 편.</br>
![image](https://user-images.githubusercontent.com/33012030/163311622-6c9b4f5f-fb82-4ff7-be86-afc7f6ab964b.png) </br>
그리고 아래와 같이 다른 backbone보다 더 적은 파라미터와 계산량을 가진다.
![image](https://user-images.githubusercontent.com/33012030/163311651-94ee634c-237c-4ab1-b1dc-0be599d21161.png)


## New knowledge
- EffecientNet 구조와 이를 활용한 BiFPN, Fusion Layer 사용 예. 
- Bi-LSTM + Attention으로 temporal feature를 추출하는 방법.


## After review



