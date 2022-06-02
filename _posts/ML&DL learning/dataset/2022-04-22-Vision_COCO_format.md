---
layout: single
title: Microsoft's Common Objects in Context dataset(COCO)
tags: [vision, dataset, COCO]
categories: dataset
---

annotations(bounding boxes, object classes, etc)과 image metadata(height, width)를 
JSON 형식으로 정의하였다.   

폴더 구조는 아래와 같다.
```commandline
<dataset_dir>/
    data/
        <filename0>.<ext>
        <filename1>.<ext>
        ...
    labels.json
```
   
   
가장 간단한 데이터 구조는 아래와 같다.
```commandline
'images': [
    {
        'file_name': '000000001268.jpg',
        'height': 480,
        'width': 640,
        'id': 1268
    },
    ...
],
'annotations': [
    {
        'segmentation': [[426.36,
            ...
            424.34,
            223.3]],
        'keypoints': [0,0,0,
            0,0,0,
            ...
            466,300,1],
        'num_keypoints': 10,
        'area': 3894.5826,
        'iscrowd': 0,
        'image_id': 1268,
        'bbox': [402.34, 205.02, 65.26, 88.45],
        'category_id': 1,
        'id': 215218
    },
    ...
],
'categories': [
    {'id': 1, 'name': 'person'},
 ]

```
기본적으로 3개의 키가 필수적으로 들어간다.
images: 이미지들에 대한 정보를 포함한다.
annotations: 개별 이미지에 대응하는 인스턴스 어노테이션 정보를 포함한다.
categories: classification 시 unique IDs에 대한 정보를 포함한다.


## 3.출처
https://towardsdatascience.com/how-to-work-with-object-detection-datasets-in-coco-format-9bf4fb5848a4