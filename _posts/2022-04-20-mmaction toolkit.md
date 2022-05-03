---
layout: post
title: mmaction Toolkit
subtitle: 
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [mmaction]
---
기존에는 폴더에 있는 파일들을 접근하려면 os 라이브러리를 사용했다. 하지만, os는 문자열로
파일 및 폴더를 접근하기 때문에 객체로 좀 더 편리하게 접근하기 위해서는 pathlib를 사용해야 한다.

## 1.모듈 설치
아래와 같은 형식으로 공식 문서에 제시되어 있다.
```
from pathlib import Path
```

## appendix 
### NTURGB-D 데이터 형식
SsssCcccPpppRrrrAaaa (e.g., S001C002P003R002A013)   
: sss is the setup number, ccc is the camera ID, ppp is the performer (subject) ID, rrr is the replication number (1 or 2), and aaa is the action class label.

#### skeleton demo
```python
python demo/demo_skeleton.py ${VIDEO_FILE} ${OUT_FILENAME} \
    [--config ${SKELETON_BASED_ACTION_RECOGNITION_CONFIG_FILE}] \
    [--checkpoint ${SKELETON_BASED_ACTION_RECOGNITION_CHECKPOINT}] \
    [--det-config ${HUMAN_DETECTION_CONFIG_FILE}] \
    [--det-checkpoint ${HUMAN_DETECTION_CHECKPOINT}] \
    [--det-score-thr ${HUMAN_DETECTION_SCORE_THRESHOLD}] \
    [--pose-config ${HUMAN_POSE_ESTIMATION_CONFIG_FILE}] \
    [--pose-checkpoint ${HUMAN_POSE_ESTIMATION_CHECKPOINT}] \
    [--label-map ${LABEL_MAP}] \
    [--device ${DEVICE}] \
    [--short-side] ${SHORT_SIDE}

```


## @ 참고
1. demo 링크
- https://github.com/open-mmlab/mmaction2  : github 메인 페이지
- https://github.com/open-mmlab/mmaction2/blob/master/docs/getting_started.md : 사용방법
- https://github.com/open-mmlab/mmaction2/tree/master/demo : 데모방법
- https://github.com/open-mmlab/mmaction2/blob/master/demo/demo.ipynb : 데모방법(notebook)