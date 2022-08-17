### Assign an id that is unique to each element in a group

```python
import pandas as pd
```


```python
dataset=pd.DataFrame({'A': [1, 1, 1,2,2,2,1,3,2,3,3]})
print(dataset)
```

        A
    0   1
    1   1
    2   1
    3   2
    4   2
    5   2
    6   1
    7   3
    8   2
    9   3
    10  3
    


```python
dataset['id']=dataset.groupby('A').cumcount()
print(dataset)
```

        A  id
    0   1   0
    1   1   1
    2   1   2
    3   2   0
    4   2   1
    5   2   2
    6   1   3
    7   3   0
    8   2   3
    9   3   1
    10  3   2
    

Note that the values contained in column 'A' do not need to be sorted prior to applying this function.
