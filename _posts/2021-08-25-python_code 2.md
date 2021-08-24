---
  layout : post
title : [python] dataframe , Numpy array
subtitle : 
date : 2021-08-25
#categories:
tags : [datascience, python]
toc_sticky : true
use_math : true
comments: true
---



### DataFrame 와 Numpy array 헷갈리는 점

~~~python
import pandas as pd
import numpy as np

N = np.random.randn(3, 3) # 행과 열이 3개  => 인덱스는 0, 1, 2
D = pd.DataFrame(N)
print('D is \n ', D)
print('N is \n' ,N)
print("      ")
print('D [0:2] 슬라이싱 \n', D.iloc[0:2]) # dataframe은 iloc을 , numpy array는 그냥
print('N [0:2] 슬라이싱 \n', N[0:2]) #dataframe 이든 numpy 배열이든 index로 slicing 할 때는 첫번째는 시작점, 두번째는 slicing 개수 이다. 
print("   ")
print('첫번째 행 인덱스 \n', D.iloc[0])
print("   ")
print('첫번째 행 인덱스 \n', N[0])
print("     ")
print('D shape \n',D.shape)#인덱스가 0,1,2 일 뿐 shape는 3 x 3
print('N shape \n',N.shape) 


"""
D is 
            0         1         2
0 -1.823920  1.167075 -0.039669
1  0.885826  0.189862  0.798064
2 -0.101932  0.743357 -1.509573
N is 
 [[-1.82391985  1.16707517 -0.0396687 ]
 [ 0.8858258   0.18986165  0.7980638 ]
 [-0.10193204  0.74335654 -1.50957268]]
      
D [0:2] 슬라이싱 
           0         1         2
0 -1.823920  1.167075 -0.039669
1  0.885826  0.189862  0.798064
N [0:2] 슬라이싱 
 [[-1.82391985  1.16707517 -0.0396687 ]
 [ 0.8858258   0.18986165  0.7980638 ]]
   
첫번째 행 인덱스 
 0   -1.823920
1    1.167075
2   -0.039669
Name: 0, dtype: float64
   
첫번째 행 인덱스 
 [-1.82391985  1.16707517 -0.0396687 ]
     
D shape 
 (3, 3)
N shape 
 (3, 3)
"""
~~~



