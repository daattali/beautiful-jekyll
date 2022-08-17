Convert trial balance report from a legacy system to excel


#Import libraries

```python
import pandas as pd
import numpy as np
```
```python
#Copy and paste contents from the legacy system in the form of a text file into an excel sheet
#Insert a "header" line at the top of the file and name it "description" (At this point all contents of the TB 
#raw file should be contained in a single column of an excel document (column "A") called "description" )

#Read the excel file from its saved location and save to a variable (dataframe)
tb=pd.read_excel('insert file_path/directory')
```
```python
#The following lines of code transform the Macola file into separate columns and drops all unnecessary lines
tb[['Account_num','Account_desc']]=tb['description'].str.extract('(\d{7}\-\d{2}\-\d{6})\s+(.*)')
tb['Account_num']=tb['Account_num'].ffill()
tb['Account_desc']=tb['Account_desc'].ffill()
tb['Account_total']=tb['description'].str.extract('Account Total:(.*)')
tb_=tb['Account_total'].dropna()
tb_=pd.merge(tb_,tb)
tb_1=tb_['Account_total'].str.split('\s+', expand=True).iloc[:,1:]
tb_1.columns=['Beg_bal','Total_cr','Total_db','Net_ch','Ending_bal']
tb_=tb_.join(tb_1)
tb_=tb_.drop(['Account_total','description'],axis=1)
tb_=tb_.drop_duplicates()
```
```python
#Convert balances ending with 'CR' to negative values and sum each column to ensure balances are correct
mask = tb_['Beg_bal'].str.endswith('CR')
tb_.loc[mask, 'Beg_bal'] = '-' + tb_.loc[mask, 'Beg_bal'].str[:-2]
tb_['Beg_bal']=tb_['Beg_bal'].str.replace(',','')
tb_['Beg_bal']=tb_['Beg_bal'].astype(float)
sum=tb_['Beg_bal'].sum()      

mask = tb_['Total_cr'].str.endswith('CR')
tb_.loc[mask, 'Total_cr'] = '-' + tb_.loc[mask, 'Total_cr'].str[:-2]
tb_['Total_cr']=tb_['Total_cr'].str.replace(',','')
tb_['Total_cr']=tb_['Total_cr'].astype(float)
sum=tb_['Total_cr'].sum()      

mask = tb_['Total_db'].str.endswith('CR')
tb_.loc[mask, 'Total_db'] = '-' + tb_.loc[mask, 'Total_db'].str[:-2]
tb_['Total_db']=tb_['Total_db'].str.replace(',','')
tb_['Total_db']=tb_['Total_db'].astype(float)
sum=tb_['Total_db'].sum()    

mask = tb_['Net_ch'].str.endswith('CR')
tb_.loc[mask, 'Net_ch'] = '-' + tb_.loc[mask, 'Net_ch'].str[:-2]
tb_['Net_ch']=tb_['Net_ch'].str.replace(',','')
tb_['Net_ch']=tb_['Net_ch'].astype(float)
sum=tb_['Net_ch'].sum()   

mask = tb_['Ending_bal'].str.endswith('CR')
tb_.loc[mask, 'Ending_bal'] = '-' + tb_.loc[mask, 'Ending_bal'].str[:-2]
tb_['Ending_bal']=tb_['Ending_bal'].str.replace(',','')
tb_['Ending_bal']=tb_['Ending_bal'].astype(float)
sum=tb_['Ending_bal'].sum()   
```
```python
#Save resulting file back to a directory
```
```python
tb_.to_excel('insert file path/directory')
```
