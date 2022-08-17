### Create a column in a dataframe that contains an unique list of the items under the 'source' column


```python
import pandas as pd
df=pd.DataFrame({'state':['NY','CA','CT','NJ','NY','FL','FL','CA'],\
                 'source':['source_a','source_a','source_a','source_b','source_b','source_b',\
                 'source_d','source_c']})
df
```

To create the unique list for each of 'state' value, use 'groupby' and apply(list)


```python
df_grouped=df.groupby('state')['source'].unique().apply(list).reset_index()
df_grouped
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>state</th>
      <th>source</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>0</td>
      <td>CA</td>
      <td>[source_a, source_c]</td>
    </tr>
    <tr>
      <td>1</td>
      <td>CT</td>
      <td>[source_a]</td>
    </tr>
    <tr>
      <td>2</td>
      <td>FL</td>
      <td>[source_b, source_d]</td>
    </tr>
    <tr>
      <td>3</td>
      <td>NJ</td>
      <td>[source_b]</td>
    </tr>
    <tr>
      <td>4</td>
      <td>NY</td>
      <td>[source_a, source_b]</td>
    </tr>
  </tbody>
</table>
</div>



Merge with original dataframe


```python
result=pd.merge(df,df_grouped,on='state',how='left')
result
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>state</th>
      <th>source_x</th>
      <th>source_y</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>0</td>
      <td>NY</td>
      <td>source_a</td>
      <td>[source_a, source_b]</td>
    </tr>
    <tr>
      <td>1</td>
      <td>CA</td>
      <td>source_a</td>
      <td>[source_a, source_c]</td>
    </tr>
    <tr>
      <td>2</td>
      <td>CT</td>
      <td>source_a</td>
      <td>[source_a]</td>
    </tr>
    <tr>
      <td>3</td>
      <td>NJ</td>
      <td>source_b</td>
      <td>[source_b]</td>
    </tr>
    <tr>
      <td>4</td>
      <td>NY</td>
      <td>source_b</td>
      <td>[source_a, source_b]</td>
    </tr>
    <tr>
      <td>5</td>
      <td>FL</td>
      <td>source_b</td>
      <td>[source_b, source_d]</td>
    </tr>
    <tr>
      <td>6</td>
      <td>FL</td>
      <td>source_d</td>
      <td>[source_b, source_d]</td>
    </tr>
    <tr>
      <td>7</td>
      <td>CA</td>
      <td>source_c</td>
      <td>[source_a, source_c]</td>
    </tr>
  </tbody>
</table>
</div>



Rename 'source_x' and 'source_y' columns


```python
result.rename(columns={'source_x':'source_original','source_y':'unique_list'},inplace=True)
result
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>state</th>
      <th>source_original</th>
      <th>unique_list</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>0</td>
      <td>NY</td>
      <td>source_a</td>
      <td>[source_a, source_b]</td>
    </tr>
    <tr>
      <td>1</td>
      <td>CA</td>
      <td>source_a</td>
      <td>[source_a, source_c]</td>
    </tr>
    <tr>
      <td>2</td>
      <td>CT</td>
      <td>source_a</td>
      <td>[source_a]</td>
    </tr>
    <tr>
      <td>3</td>
      <td>NJ</td>
      <td>source_b</td>
      <td>[source_b]</td>
    </tr>
    <tr>
      <td>4</td>
      <td>NY</td>
      <td>source_b</td>
      <td>[source_a, source_b]</td>
    </tr>
    <tr>
      <td>5</td>
      <td>FL</td>
      <td>source_b</td>
      <td>[source_b, source_d]</td>
    </tr>
    <tr>
      <td>6</td>
      <td>FL</td>
      <td>source_d</td>
      <td>[source_b, source_d]</td>
    </tr>
    <tr>
      <td>7</td>
      <td>CA</td>
      <td>source_c</td>
      <td>[source_a, source_c]</td>
    </tr>
  </tbody>
</table>
</div>


