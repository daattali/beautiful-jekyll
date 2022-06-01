---
layout: single
title: mmaction tutorial
tags: [mmaction]
categories: open-mmlab
---
## 1.모듈 설치

## appendix 
### NTURGB-D 데이터 형식
SsssCcccPpppRrrrAaaa (e.g., S001C002P003R002A013)   
: sss is the setup number, ccc is the camera ID, ppp is the performer (subject) ID, rrr is the replication number (1 or 2), and aaa is the action class label.

#### skeleton demo
```python
python demo/demo_skeleton.py ${VIDEO_FILE} ${OUT_FILENAME} \
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
- https://github.com/open-mmlab/mmaction2/blob/master/demo/demo.ipynb : 데모방법(notebook