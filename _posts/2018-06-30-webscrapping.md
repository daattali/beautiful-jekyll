
#### Webscrapping FCA reviews

We can start by  requesting the content of the first web page: https://www.glassdoor.com/Reviews/FCA-Fiat-Chrysler-Automobiles-Reviews-E149.htm.  As follows.

Import the get() function from the requests module.
Assign the address of the web page to a variable named url.
Request the server the content of the web page by using get(), and store the server’s response in the variable response.
Print a small part of response's content by accessing its .text attribute (response is now a Response object).


```python
from requests import get
import numpy as np
import pandas as pd
from datetime import datetime
from dateutil.parser import parse
import re
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
%matplotlib inline

#url = 'https://www.glassdoor.com/Reviews/FCA-Fiat-Chrysler-Automobiles-Reviews-E149.htm'

#url="https://www.glassdoor.com/Reviews/FCA-Fiat-Chrysler-Automobiles-Auburn-Hills-Reviews-EI_IE149.0,29_IL.30,42_IC1134622.htm"


url="https://www.indeed.com/cmp/Fiat-Chrysler-Automobiles/reviews"

response = get(url)
print(response.text[:500])



from bs4 import BeautifulSoup

html_soup = BeautifulSoup(response.text, 'html.parser')
type(html_soup)


date_containers = html_soup.find_all('span', attrs={'class':'cmp-review-date-created'})
date_containers

text_containers = html_soup.find_all('span', attrs={'class':'cmp-review-text'})


text_containers[1].text


title_containers = html_soup.find_all('div', attrs={'class':'cmp-review-title'})

title_containers[1].text


location_containers = html_soup.find_all('span', attrs={'class':'cmp-reviewer-job-location'})

location_containers[1].text


job_containers = html_soup.find_all('span', attrs={'class':'cmp-reviewer'})



jobstatus_containers = html_soup.find_all('span', attrs={'class':'cmp-reviewer-job-title'})

jobstatus_containers[1].text[-21:-5]

job_containers[1].text

```

    <!doctype html><html>
    <head>
      <title>Working at Fiat Chrysler Automobiles: 1,793 Reviews | Indeed.com</title>
      <meta http-equiv="content-type" content="text/html;charset=UTF-8"/><meta name="description" content="1,793 reviews from Fiat Chrysler Automobiles employees about Fiat Chrysler Automobiles culture, salaries, benefits, work-life balance, management, job security, and more."/><meta name="viewport" content="width = device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no"/><li





    'Assembly Line Worker'




```python
date_containers[1].text
```




    'June 6, 2018'




```python
len(date_containers)
```




    21




```python
range(len(text_containers))
```




    range(0, 21)




```python

date_container=[]
text_container=[]
title_container=[]
location_container=[]
job_container=[]
jobstatus_container=[]


for i in range(len(text_containers)):  
   
    date_container.append(date_containers[i].text)
    text_container.append(text_containers[i].text)
    title_container.append(title_containers[i].text)
    location_container.append(location_containers[i].text)
    job_container.append(job_containers[i].text)
    jobstatus_container.append(jobstatus_containers[i].text[-21:-5])
```


```python
z=[len(date_container),len(text_container),len(title_container),len(location_container),
  len(job_container),len(jobstatus_container)]

df = pd.DataFrame({ 'Date' : date_container,
                       'Title' : title_container,
                        'Location' : location_container,
                        ' Job' :  job_container,
                        'Jobstatus' : jobstatus_container,
                       'Text' : text_container})

#Remove all parenthesis from Jobstatus column
df['Jobstatus']=df['Jobstatus'].str.replace("(","") 

df.info()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 21 entries, 0 to 20
    Data columns (total 6 columns):
     Job         21 non-null object
    Date         21 non-null object
    Jobstatus    21 non-null object
    Location     21 non-null object
    Text         21 non-null object
    Title        21 non-null object
    dtypes: object(6)
    memory usage: 1.1+ KB



```python
#Adding the following lines to a new script will clear all variables each time you rerun the script:

#from IPython import get_ipython
#get_ipython().magic('reset -sf')

#len(pd.unique(u))
# Find the length of uique elements in a list
#len(set(w))
```

Create alist to store all website urls


```python

url="https://www.indeed.com/cmp/Fiat-Chrysler-Automobiles/reviews"
v='https://www.indeed.com/cmp/Fiat-Chrysler-Automobiles/reviews?start='

w=[]
for i in np.arange(20,1780,20):
    w.append(v+str(i))

url=[url]    

url.append(w)

url.extend(w)

```


```python
url="https://www.indeed.com/cmp/Fiat-Chrysler-Automobiles/reviews"

def merge(l1, l2):
    yield from l1
    yield from l2

list(merge(url, w))
len(list(merge(url, set(w))))

len(set(url))
```




    26



#### Function to extract information from the first page


```python
def webscrap (url):
    from requests import get
    import numpy as np
    import pandas as pd
    from bs4 import BeautifulSoup
     
  
    response = get(url)

    html_soup = BeautifulSoup(response.text, 'html.parser')

    date_containers = html_soup.find_all('span', attrs={'class':'cmp-review-date-created'})

    text_containers = html_soup.find_all('span', attrs={'class':'cmp-review-text'})


    title_containers = html_soup.find_all('div', attrs={'class':'cmp-review-title'})

    location_containers = html_soup.find_all('span', attrs={'class':'cmp-reviewer-job-location'})


    job_containers = html_soup.find_all('span', attrs={'class':'cmp-reviewer'})

    jobstatus_containers = html_soup.find_all('span', attrs={'class':'cmp-reviewer-job-title'})

   

    z=[len(date_containers),len(text_containers),len(title_containers),len(location_containers),
         len(job_containers),len(jobstatus_containers)]

       #min(z)
    z2=np.amin(z)
        
        
        
    date_container=[]
    text_container=[]
    title_container=[]
    location_container=[]
    job_container=[]
    jobstatus_container=[]


    for i in range(z2):  
   
            date_container.append(date_containers[i].text)
            text_container.append(text_containers[i].text)
            title_container.append(title_containers[i].text)
            location_container.append(location_containers[i].text)
            job_container.append(job_containers[i].text)
            jobstatus_container.append(jobstatus_containers[i].text[-21:-5])
    
      
        
        # store extracted information in a dataframe
    df = pd.DataFrame({ 'Date' : date_container,
                       'Title' : title_container,
                        'Location' : location_container,
                        ' Job' :  job_container,
                        'Jobstatus' : jobstatus_container,
                       'Text' : text_container})

       #Remove all parenthesis from Jobstatus column
    df['Jobstatus']=df['Jobstatus'].str.replace("(","") 
    
    
     # change the type of Date from object to  datetime column for plotting
    df['Date'] = pd.to_datetime(df['Date'])



    
    return df;
```


#### Repeat function over all webpages



```python
url="https://www.indeed.com/cmp/Fiat-Chrysler-Automobiles/reviews"

webscrap (url ).head(4)

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
      <th>Job</th>
      <th>Date</th>
      <th>Jobstatus</th>
      <th>Location</th>
      <th>Text</th>
      <th>Title</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Vehicle Maintenance Auditor (Contracted)</td>
      <td>2016-10-12</td>
      <td>Current Employee</td>
      <td>Auburn Hills, MI 48326</td>
      <td>Top of line techs for FCA automobiles hard to ...</td>
      <td>Productive good managment</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Assembly Line Worker</td>
      <td>2018-06-06</td>
      <td>Current Employee</td>
      <td>Belvidere, IL</td>
      <td>Management is moving forward in positive direc...</td>
      <td>Management</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Assembly Line Worker</td>
      <td>2018-06-05</td>
      <td>Former Employee</td>
      <td>Belvidere, IL</td>
      <td>It was a fast pace environment.  It was easy t...</td>
      <td>It was a fast pace environment.</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Facilitator Twinsburg Stamping Plant</td>
      <td>2018-06-05</td>
      <td>Former Employee</td>
      <td>Twinsburg, OH</td>
      <td>If you can find a plant that isn't in danger o...</td>
      <td>Big 3 benefits</td>
    </tr>
  </tbody>
</table>
</div>



#### Repeat function over all webpages


```python

pages_2last=list(map(webscrap,w))



```

#### Concatenate all pages extracted into one data frame


```python
page_1=webscrap(url)

#pd.concat([pages_2last,page_1])
AllData=pd.Series.append(page_1,pages_2last)

AllData=pd.DataFrame(AllData)
AllData.head()
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
      <th>Job</th>
      <th>Date</th>
      <th>Jobstatus</th>
      <th>Location</th>
      <th>Text</th>
      <th>Title</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>Vehicle Maintenance Auditor (Contracted)</td>
      <td>2016-10-12</td>
      <td>Current Employee</td>
      <td>Auburn Hills, MI 48326</td>
      <td>Top of line techs for FCA automobiles hard to ...</td>
      <td>Productive good managment</td>
    </tr>
    <tr>
      <th>1</th>
      <td>Assembly Line Worker</td>
      <td>2018-06-06</td>
      <td>Current Employee</td>
      <td>Belvidere, IL</td>
      <td>Management is moving forward in positive direc...</td>
      <td>Management</td>
    </tr>
    <tr>
      <th>2</th>
      <td>Assembly Line Worker</td>
      <td>2018-06-05</td>
      <td>Former Employee</td>
      <td>Belvidere, IL</td>
      <td>It was a fast pace environment.  It was easy t...</td>
      <td>It was a fast pace environment.</td>
    </tr>
    <tr>
      <th>3</th>
      <td>Facilitator Twinsburg Stamping Plant</td>
      <td>2018-06-05</td>
      <td>Former Employee</td>
      <td>Twinsburg, OH</td>
      <td>If you can find a plant that isn't in danger o...</td>
      <td>Big 3 benefits</td>
    </tr>
    <tr>
      <th>4</th>
      <td>Warehouse Associate</td>
      <td>2018-06-05</td>
      <td>Former Employee</td>
      <td>Tappan, NY</td>
      <td>Chrystler was a great place to work for the ti...</td>
      <td>Productive work place</td>
    </tr>
  </tbody>
</table>
</div>



#### Write The File to excel


```python

# Create a Pandas dataframe from the data.
df = AllData

# Create a Pandas Excel writer using XlsxWriter as the engine.
writer = pd.ExcelWriter('/Users/nanaakwasiabayieboateng/PythonNLTK/AllData.xlsx', engine='xlsxwriter')

# Convert the dataframe to an XlsxWriter Excel object.
df.to_excel(writer, sheet_name='Sheet1')

# Close the Pandas Excel writer and output the Excel file.
writer.save()
```

#### Write to a csv File


```python
# Create a Pandas dataframe from the data.

pd.DataFrame.to_csv(AllData,'/Users/nanaakwasiabayieboateng/PythonNLTK/AllData.csv')
```

#### Natural Language Processing


```python
import spacy
nlp = spacy.load("en_core_web_sm")
AllData=pd.read_csv('/Users/nanaakwasiabayieboateng/PythonNLTK/AllData.csv')
```

Convert text to string and tokenize the strings into words.


```python
myvariable = AllData["Text"]
mystring = str(myvariable)  
doc=nlp(mystring)

##alternatively try repr:

#mystring = repr(myvariable) # '4'
```


```python
doc.text.split()[0:10]
```




    ['0', 'Top', 'of', 'line', 'techs', 'for', 'FCA', 'automobiles', 'hard', 'to']




```python
len(doc.text.split())

```




    598




```python
type(AllData)
```




    pandas.core.frame.DataFrame




```python
AllData.dtypes
```




    Unnamed: 0     int64
     Job          object
    Date          object
    Jobstatus     object
    Location      object
    Text          object
    Title         object
    dtype: object




```python
AllData.shape
```




    (1869, 7)



#### Part-of-speech tagging, lemmatization

Tokenize,lemmatize,part of speech tag and check of the word is a stop word


```python
import spacy

nlp = spacy.load('en_core_web_sm')
doc = nlp( mystring)

for token in doc:
    print(token.text, token.lemma_, token.pos_, token.tag_, token.dep_,
          token.shape_, token.is_alpha, token.is_stop)
```

    0 0 PUNCT NFP ROOT d False False
                  SPACE _SP       False False
    Top top NOUN NN ROOT Xxx True False
    of of ADP IN prep xx True True
    line line NOUN NN compound xxxx True False
    techs tech NOUN NNS pobj xxxx True False
    for for ADP IN prep xxx True True
    FCA fca PROPN NNP compound XXX True False
    automobiles automobile NOUN NNS pobj xxxx True False
    hard hard ADJ JJ advmod xxxx True False
    to to PART TO prep xx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1 1 NUM CD nummod d False False
                  SPACE _SP       False False
    Pros pros PROPN NNPS ROOT Xxxx True False
    : : PUNCT : punct : False False
    Benefits benefit NOUN NNS appos Xxxxx True False
    , , PUNCT , punct , False False
    flexible flexible ADJ JJ amod xxxx True False
    overtime overtime NOUN NN appos xxxx True False
    , , PUNCT , punct , False False
    career career NOUN NN compound xxxx True False
    advan advan NOUN NNS appos xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    2 2 NUM CD meta d False False
                  SPACE _SP       False False
    I -PRON- PRON PRP nsubj X True False
    was be VERB VBD aux xxx True True
    working work VERB VBG ROOT xxxx True False
    as as ADP IN prep xx True True
    supplier supplier NOUN NN amod xxxx True False
    quality quality NOUN NN compound xxxx True False
    engineer engineer NOUN NN pobj xxxx True False
    . . PUNCT . punct . False False
    Th th NOUN NN ROOT Xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    3 3 NUM CD nummod d False False
                  SPACE _SP       False False
    Learnt learnt PROPN NNP amod Xxxxx True False
    things thing NOUN NNS appos xxxx True False
    about about ADP IN prep xxxx True True
    Body body NOUN NN pobj Xxxx True False
    in in ADP IN prep xx True True
    White white PROPN NNP pobj Xxxxx True False
    . . PUNCT . punct . False False
    Was be VERB VBD ROOT Xxx True False
    not not ADV RB neg xxx True True
    alw alw ADJ JJ nsubj xxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    4 4 NUM CD nummod d False False
                  SPACE _SP       False False
    Just just ADV RB advmod Xxxx True False
    a a DET DT det x True True
    workplace workplace NOUN NN attr xxxx True False
    that that ADJ WDT nsubj xxxx True True
    only only ADV RB advmod xxxx True True
    cares care VERB VBZ relcl xxxx True False
    about about ADP IN prep xxxx True True
    buildin buildin NOUN NN pobj xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    5 5 NUM CD nummod d False False
                  SPACE _SP       False False
    Great great ADJ JJ amod Xxxxx True False
    place place NOUN NN ROOT xxxx True False
    to to PART TO aux xx True True
    be be VERB VB relcl xx True True
    if if ADP IN mark xx True True
    you -PRON- PRON PRP nsubj xxx True True
    can can VERB MD aux xxx True True
    handle handle VERB VB ccomp xxxx True False
    a a DET DT det x True True
    fast fast ADJ JJ amod xxxx True False
    pac pac NOUN NN dobj xxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    6 6 NUM CD nummod d False False
                  SPACE _SP       False False
    learnt learn VERB VBD ROOT xxxx True False
    a a DET DT det x True True
    lot lot NOUN NN npadvmod xxx True False
    of of ADP IN prep xx True True
    automotive automotive ADJ JJ amod xxxx True False
    system system NOUN NN pobj xxxx True False
    , , PUNCT , punct , False False
    but but CCONJ CC cc xxx True True
    sometim sometim NOUN NN conj xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    7 7 NUM CD nummod d False False
                  SPACE _SP       False False
    Typical typical ADJ JJ amod Xxxxx True False
    factory factory NOUN NN compound xxxx True False
    work work NOUN NN appos xxxx True False
    . . PUNCT . punct . False False
    It -PRON- PRON PRP nsubj Xx True False
    is be VERB VBZ ROOT xx True True
    a a DET DT det x True True
    no no DET DT det xx True True
    brainer brainer NOUN NN compound xxxx True False
    job job NOUN NN compound xxx True False
    b b NOUN NN attr x True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    8 8 NUM CD nummod d False False
                  SPACE _SP       False False
    Poor poor PROPN NNP compound Xxxx True False
    ManagementExtreme managementextreme PROPN NNP compound XxxxxXxxxx True False
    animosity animosity NOUN NN appos xxxx True False
    between between ADP IN prep xxxx True True
    Compa compa PROPN NNP pobj Xxxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    9 9 NUM CD nummod d False False
                  SPACE _SP       False False
    FCA fca PROPN NNP nsubj XXX True False
    is be VERB VBZ ROOT xx True True
    such such ADJ PDT predet xxxx True True
    a a DET DT det x True True
    large large ADJ JJ amod xxxx True False
    diverse diverse ADJ JJ amod xxxx True False
    organization organization NOUN NN attr xxxx True False
    that that ADJ WDT nsubj xxxx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    10 10 NUM CD nummod dd False False
                SPACE _SP       False False
    Hours hour NOUN NNS nsubj Xxxxx True False
    are be VERB VBP relcl xxx True True
    long long ADJ JJ acomp xxxx True False
    , , PUNCT , punct , False False
    pay pay VERB VB nsubj xxx True False
    is be VERB VBZ conj xx True True
    good good ADJ JJ acomp xxxx True False
    , , PUNCT , punct , False False
    most most ADJ JJS amod xxxx True True
    supervisors supervisor NOUN NNS nsubj xxxx True False
    a a DET DT det x True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    11 11 NUM CD npadvmod dd False False
                SPACE _SP       False False
    If if ADP IN mark Xx True False
    you -PRON- PRON PRP nsubj xxx True True
    like like VERB VBP ROOT xxxx True False
    to to PART TO aux xx True True
    work work VERB VB xcomp xxxx True False
    7 7 NUM CD nummod d False False
    seven seven NUM CD nummod xxxx True False
    days day NOUN NNS npadvmod xxxx True False
    a a DET DT det x True True
    week week NOUN NN npadvmod xxxx True False
    and and CCONJ CC cc xxx True True
    ha ha INTJ UH intj xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    12 12 NUM CD nummod dd False False
                SPACE _SP       False False
    First first ADJ JJ amod Xxxxx True False
    day day NOUN NN nsubj xxx True False
    sold sell VERB VBD conj xxxx True False
    my -PRON- ADJ PRP$ poss xx True True
    first first ADJ JJ amod xxxx True True
    car car NOUN NN dobj xxx True False
    and and CCONJ CC cc xxx True True
    never never ADV RB neg xxxx True True
    got get VERB VBD auxpass xxx True False
    paid pay VERB VBN conj xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    13 13 NUM CD nummod dd False False
                SPACE _SP       False False
    Great great ADJ JJ amod Xxxxx True False
    place place NOUN NN ROOT xxxx True False
    to to PART TO aux xx True True
    work work VERB VB relcl xxxx True False
    if if ADP IN mark xx True True
    you -PRON- PRON PRP nsubj xxx True True
    want want VERB VBP advcl xxxx True False
    to to PART TO aux xx True True
    be be VERB VB xcomp xx True True
    complete complete ADJ JJ acomp xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    14 14 NUM CD nummod dd False False
                SPACE _SP       False False
    Worked work VERB VBD ROOT Xxxxx True False
    in in ADP IN prep xx True True
    sales sale NOUN NNS pobj xxxx True False
    for for ADP IN prep xxx True True
    about about ADV RB advmod xxxx True True
    6 6 NUM CD nummod d False False
    years year NOUN NNS pobj xxxx True False
    although although ADP IN mark xxxx True True
    mos mo NOUN NNS nmod xxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    15 15 NUM CD nummod dd False False
                SPACE _SP       False False
    Productive productive PROPN NNP amod Xxxxx True False
    and and CCONJ CC cc xxx True True
    great great ADJ JJ conj xxxx True False
    group group NOUN NN nsubj xxxx True False
    of of ADP IN prep xx True True
    people people NOUN NNS pobj xxxx True False
    to to PART TO aux xx True True
    work work VERB VB advcl xxxx True False
    w w DET DT advmod x True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    16 16 NUM CD nummod dd False False
                SPACE _SP       False False
    none none NOUN NN nsubj xxxx True True
    , , PUNCT , punct , False False
    good good ADJ JJ amod xxxx True False
    manager manager NOUN NN nmod xxxx True False
    good good ADJ JJ amod xxxx True False
    people people NOUN NNS appos xxxx True False
    bad bad ADJ JJ amod xxx True False
    hours hour NOUN NNS npadvmod xxxx True False
    do do VERB VBP ROOT xx True True
    nt not ADV RB advmod xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    17 17 NUM CD ROOT dd False False
                SPACE _SP       False False
    I -PRON- PRON PRP nsubj X True False
    really really ADV RB advmod xxxx True True
    enjoyed enjoy VERB VBD ROOT xxxx True False
    working work VERB VBG xcomp xxxx True False
    at at ADP IN prep xx True True
    Chrysler chrysler PROPN NNP pobj Xxxxx True False
    . . PUNCT . punct . False False
    The the DET DT det Xxx True False
    only only ADJ JJ amod xxxx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    18 18 NUM CD nummod dd False False
                SPACE _SP       False False
    Data data PROPN NNP compound Xxxx True False
    entry entry NOUN NN nsubj xxxx True False
    got get VERB VBD ROOT xxx True False
    to to PART TO aux xx True True
    make make VERB VB xcomp xxxx True True
    out out PART RP prt xxx True True
    going go VERB VBG ccomp xxxx True False
    calls call NOUN NNS dobj xxxx True False
    and and CCONJ CC cc xxx True True
    wor wor NOUN NN conj xxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    19 19 NUM CD nummod dd False False
                SPACE _SP       False False
    Competitive competitive ADJ JJ nsubj Xxxxx True False
    , , PUNCT , punct , False False
    stressful stressful ADJ JJ amod xxxx True False
    at at ADP IN prep xx True True
    times time NOUN NNS pobj xxxx True False
    , , PUNCT , punct , False False
    managers manager NOUN NNS nsubj xxxx True False
    are be VERB VBP ROOT xxx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    20 20 NUM CD nummod dd False False
                SPACE _SP       False False
    FCA fca PROPN NNP nsubj XXX True False
    is be VERB VBZ ROOT xx True True
    a a DET DT det x True True
    highly highly ADV RB advmod xxxx True False
    technical technical ADJ JJ amod xxxx True False
    place place NOUN NN attr xxxx True False
    to to PART TO aux xx True True
    work work VERB VB relcl xxxx True False
    and and CCONJ CC cc xxx True True
    ut ut VERB VB conj xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    21 21 NUM CD nummod dd False False
                SPACE _SP       False False
    Top top NOUN NN nsubj Xxx True False
    of of ADP IN prep xx True True
    line line NOUN NN compound xxxx True False
    techs tech NOUN NNS pobj xxxx True False
    for for ADP IN prep xxx True True
    FCA fca PROPN NNP compound XXX True False
    automobiles automobile NOUN NNS pobj xxxx True False
    hard hard ADJ JJ advmod xxxx True False
    to to PART TO ROOT xx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    22 22 NUM CD ROOT dd False False
                SPACE _SP       False False
    I -PRON- PRON PRP nsubj X True False
    like like VERB VBP ROOT xxxx True False
    the the DET DT det xxx True True
    fact fact NOUN NN dobj xxxx True False
    that that ADP IN det xxxx True True
    FCA fca PROPN NNP nsubj XXX True False
    sponsored sponsor VERB VBN amod xxxx True False
    sand sand NOUN NN compound xxxx True False
    volley volley ADJ JJ acl xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    23 23 NUM CD punct dd False False
                SPACE _SP       False False
    This this DET DT det Xxxx True False
    organization organization NOUN NN nsubj xxxx True False
    has have VERB VBZ ROOT xxx True True
    a a DET DT det x True True
    culture culture NOUN NN dobj xxxx True False
    that that ADJ WDT nsubj xxxx True True
    is be VERB VBZ relcl xx True True
    only only ADV RB advmod xxxx True True
    w w DET DT attr x True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    24 24 NUM CD meta dd False False
                SPACE _SP       False False
    At at ADP IN ROOT Xx True False
    FCA fca PROPN NNP pobj XXX True False
    I -PRON- PRON PRP nsubj X True False
    and and CCONJ CC cc xxx True True
    many many ADJ JJ amod xxxx True True
    others other NOUN NNS conj xxxx True True
    had have VERB VBD ROOT xxx True True
    a a DET DT det x True True
    relaxed relaxed ADJ JJ amod xxxx True False
    work work NOUN NN dobj xxxx True False
    sc sc ADP IN ROOT xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    25 25 NUM CD punct dd False False
                SPACE _SP       False False
    A a DET DT det X True False
    fantastic fantastic ADJ JJ amod xxxx True False
    place place NOUN NN ROOT xxxx True False
    to to PART TO aux xx True True
    work work VERB VB relcl xxxx True False
    . . PUNCT . punct . False False
    Great great ADJ JJ amod Xxxxx True False
    managers manager NOUN NNS ROOT xxxx True False
    and and CCONJ CC cc xxx True True
    p p NOUN NN quantmod x True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    26 26 NUM CD conj dd False False
                SPACE _SP       False False
    The the DET DT det Xxx True False
    company company NOUN NN nsubj xxxx True False
    is be VERB VBZ ROOT xx True True
    great great ADJ JJ acomp xxxx True False
    to to PART TO aux xx True True
    work work VERB VB xcomp xxxx True False
    for for ADP IN prep xxx True True
    . . PUNCT . punct . False False
        SPACE     False False
    The the DET DT det Xxx True False
    people people NOUN NNS ROOT xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    27 27 NUM CD nummod dd False False
                SPACE _SP       False False
    Office office PROPN NNP compound Xxxxx True False
    politics politic NOUN NNS nsubj xxxx True False
    are be VERB VBP ccomp xxx True True
    rife rife ADJ JJ acomp xxxx True False
    , , PUNCT , punct , False False
    fragile fragile ADJ JJ amod xxxx True False
    ego ego NOUN NN poss xxx True False
    's 's PART POS case 'x False False
    abound abound NOUN NN ROOT xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    28 28 NUM CD nummod dd False False
                SPACE _SP       False False
    HR hr NOUN NN nsubj XX True False
    is be VERB VBZ ccomp xx True True
    there there ADV RB advmod xxxx True True
    for for ADP IN prep xxx True True
    upper upper ADJ JJ amod xxxx True False
    management management NOUN NN pobj xxxx True False
    onlyThere onlythere ADV RB punct xxxxXxxxx True False
    is be VERB VBZ ROOT xx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    29 29 NUM CD ROOT dd False False
                SPACE _SP       False False
    The the DET DT det Xxx True False
    workforce workforce NOUN NN nsubj xxxx True False
    is be VERB VBZ ROOT xx True True
    fairly fairly ADV RB advmod xxxx True False
    average average ADJ JJ acomp xxxx True False
    and and CCONJ CC cc xxx True True
    most most ADV RBS advmod xxxx True True
    depen depen VERB VB conj xxxx True False
    ... ... PUNCT NFP punct ... False False
    
                                   
                                   SPACE _SP  
         False False
    ... ... PUNCT NFP punct ... False False
                           
                            
     SPACE _SP      
     False False
    1829 1829 NUM CD nummod dddd False False
            SPACE _SP      False False
    Chrysler chrysler PROPN NNP nsubj Xxxxx True False
    is be VERB VBZ ROOT xx True True
    a a DET DT det x True True
    great great ADJ JJ amod xxxx True False
    company company NOUN NN attr xxxx True False
    . . PUNCT . punct . False False
    We -PRON- PRON PRP nsubj Xx True False
    are be VERB VBP aux xxx True True
    working work VERB VBG ROOT xxxx True False
    to to ADP IN prep xx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1830 1830 NUM CD ROOT dddd False False
            SPACE _SP      False False
    I -PRON- PRON PRP nsubj X True False
    enjoyed enjoy VERB VBD ROOT xxxx True False
    the the DET DT det xxx True True
    people people NOUN NNS dobj xxxx True False
    and and CCONJ CC cc xxx True True
    jobs job NOUN NNS conj xxxx True False
    at at ADP IN prep xx True True
    Chrysler chrysler PROPN NNP pobj Xxxxx True False
    . . PUNCT . punct . False False
    We -PRON- PRON PRP ROOT Xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1831 1831 NUM CD ROOT dddd False False
            SPACE _SP      False False
    While while ADP IN mark Xxxxx True False
    the the DET DT det xxx True True
    work work NOUN NN nsubj xxxx True False
    can can VERB MD aux xxx True True
    become become VERB VB ROOT xxxx True True
    routine routine ADJ JJ acomp xxxx True False
    and and CCONJ CC cc xxx True True
    monotono monotono NOUN NNS conj xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1832 1832 NUM CD conj dddd False False
            SPACE _SP      False False
    Competitive competitive ADJ JJ amod Xxxxx True False
    work work NOUN NN nsubj xxxx True False
    envioronment envioronment ADJ JJ ROOT xxxx True False
    lots lot NOUN NNS dobj xxxx True False
    of of ADP IN prep xx True True
    vultures vulture NOUN NNS pobj xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1833 1833 NUM CD ROOT dddd False False
            SPACE _SP      False False
    I -PRON- PRON PRP nsubj X True False
    assembled assemble VERB VBD ROOT xxxx True False
    various various ADJ JJ amod xxxx True True
    engine engine NOUN NN compound xxxx True False
    parts part NOUN NNS dobj xxxx True False
    for for ADP IN prep xxx True True
    the the DET DT det xxx True True
    Chrys chrys PROPN NNP pobj Xxxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1834 1834 NUM CD nsubj dddd False False
            SPACE _SP      False False
    was be VERB VBD ccomp xxx True True
    a a DET DT det x True True
    super super ADV RB advmod xxxx True False
    great great ADJ JJ amod xxxx True False
    job job NOUN NN attr xxx True False
    , , PUNCT , punct , False False
    plant plant NOUN NN nsubj xxxx True False
    closed close VERB VBN ROOT xxxx True False
    , , PUNCT , punct , False False
    had have VERB VBD dep xxx True True
    great great ADJ JJ oprd xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1835 1835 NUM CD nummod dddd False False
            SPACE _SP      False False
    great great ADJ JJ amod xxxx True False
    place place NOUN NN ROOT xxxx True False
    to to PART TO aux xx True True
    work work VERB VB relcl xxxx True False
    if if ADP IN mark xx True True
    you -PRON- PRON PRP nsubj xxx True True
    can can VERB MD aux xxx True True
    handle handle VERB VB advcl xxxx True False
    the the DET DT det xxx True True
    very very ADV RB dobj xxxx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1836 1836 NUM CD nummod dddd False False
            SPACE _SP      False False
    Chrysler chrysler PROPN NNP nsubj Xxxxx True False
    is be VERB VBZ ROOT xx True True
    a a DET DT det x True True
    great great ADJ JJ amod xxxx True False
    corporation corporation NOUN NN attr xxxx True False
    to to PART TO aux xx True True
    work work VERB VB relcl xxxx True False
    for for ADP IN prep xxx True True
    , , PUNCT , punct , False False
    e e PUNCT LS intj x True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1837 1837 NUM CD nummod dddd False False
            SPACE _SP      False False
    Very very ADV RB advmod Xxxx True False
    poor poor ADJ JJ amod xxxx True False
    raises raise NOUN NNS ROOT xxxx True False
    and and CCONJ CC cc xxx True True
    salaries salary NOUN NNS conj xxxx True False
    . . PUNCT . punct . False False
    Great great ADJ JJ amod Xxxxx True False
    aerospace aerospace NOUN NN ROOT xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1838 1838 NUM CD ROOT dddd False False
            SPACE _SP      False False
    My -PRON- ADJ PRP$ poss Xx True False
    role role NOUN NN nsubj xxxx True False
    is be VERB VBZ ROOT xx True True
    plant plant NOUN NN compound xxxx True False
    - - PUNCT HYPH punct - False False
    side side NOUN NN attr xxxx True True
    in in ADP IN prep xx True True
    Human human PROPN NNP compound Xxxxx True False
    Resources resources PROPN NNPS pobj Xxxxx True False
    and and CCONJ CC cc xxx True True
    I -PRON- PRON PRP conj X True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1839 1839 NUM CD ROOT dddd False False
            SPACE _SP      False False
    Good good ADJ JJ amod Xxxx True False
    benefits benefit NOUN NNS ROOT xxxx True False
    and and CCONJ CC cc xxx True True
    pay pay VERB VB conj xxx True False
    , , PUNCT , punct , False False
    but but CCONJ CC cc xxx True True
    is be VERB VBZ conj xx True True
    it -PRON- PRON PRP nsubj xx True True
    worth worth ADJ JJ acomp xxxx True False
    taking take VERB VBG xcomp xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1840 1840 NUM CD ROOT dddd False False
            SPACE _SP      False False
    During during ADP IN ROOT Xxxxx True False
    the the DET DT det xxx True True
    time time NOUN NN pobj xxxx True False
    of of ADP IN prep xx True True
    my -PRON- ADJ PRP$ poss xx True True
    hiring hiring NOUN NN pobj xxxx True False
    at at ADP IN prep xx True True
    Chrysler chrysler PROPN NNP pobj Xxxxx True False
    , , PUNCT , punct , False False
    they -PRON- PRON PRP intj xxxx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1841 1841 NUM CD ROOT dddd False False
            SPACE _SP      False False
    The the DET DT det Xxx True False
    company company NOUN NN nsubj xxxx True False
    has have VERB VBZ aux xxx True True
    been be VERB VBN aux xxxx True True
    going go VERB VBG ROOT xxxx True False
    thru thru ADP IN prep xxxx True True
    changes change NOUN NNS pobj xxxx True False
    and and CCONJ CC cc xxx True True
    is be VERB VBZ conj xx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1842 1842 NUM CD nummod dddd False False
            SPACE _SP      False False
    Chrysler chrysler PROPN NNP compound Xxxxx True False
    LLC llc PROPN NNP nsubj XXX True False
    went go VERB VBD ROOT xxxx True False
    thru thru ADP IN prep xxxx True True
    a a DET DT det x True True
    lot lot NOUN NN pobj xxx True False
    of of ADP IN prep xx True True
    changes change NOUN NNS pobj xxxx True False
    from from ADP IN prep xxxx True True
    2 2 NUM CD pobj d False False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1843 1843 NUM CD ROOT dddd False False
            SPACE _SP      False False
    There there ADV EX expl Xxxxx True False
    is be VERB VBZ ROOT xx True True
    a a DET DT det x True True
    vast vast ADJ JJ amod xxxx True False
    amount amount NOUN NN attr xxxx True True
    of of ADP IN prep xx True True
    areas area NOUN NNS pobj xxxx True False
    to to PART TO aux xx True True
    work work VERB VB relcl xxxx True False
    at at ADP IN prep xx True True
    . . PUNCT . punct . False False
    Fr fr NOUN NN ROOT Xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1844 1844 NUM CD ROOT dddd False False
            SPACE _SP      False False
    Great great ADJ JJ ROOT Xxxxx True False
    to to PART TO aux xx True True
    see see VERB VB advcl xxx True True
    how how ADV WRB advmod xxx True True
    they -PRON- PRON PRP nsubj xxxx True True
    are be VERB VBP aux xxx True True
    coming come VERB VBG ccomp xxxx True False
    back back ADV RB advmod xxxx True True
    . . PUNCT . punct . False False
    Buildin buildin PROPN NNP ROOT Xxxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1845 1845 NUM CD nummod dddd False False
            SPACE _SP      False False
    Contracted contract VERB VBN dep Xxxxx True False
    thru thru ADP IN prep xxxx True True
    Caravan caravan PROPN NNP compound Xxxxx True False
    Knight knight PROPN NNP pobj Xxxxx True False
    , , PUNCT , punct , False False
    Supervised supervised PROPN NNP ROOT Xxxxx True False
    all all DET DT advmod xxx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1846 1846 NUM CD ROOT dddd False False
            SPACE _SP      False False
    I -PRON- PRON PRP nsubj X True False
    worked work VERB VBD ROOT xxxx True False
    there there ADV RB advmod xxxx True True
    for for ADP IN prep xxx True True
    almost almost ADV RB advmod xxxx True True
    12 12 NUM CD nummod dd False False
    years year NOUN NNS pobj xxxx True False
    and and CCONJ CC cc xxx True True
    it -PRON- PRON PRP nsubj xx True True
    eem eem VERB VBP conj xxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1847 1847 NUM CD ROOT dddd False False
            SPACE _SP      False False
    As as ADP IN prep Xx True False
    a a DET DT det x True True
    contract contract NOUN NN compound xxxx True False
    employee employee NOUN NN pobj xxxx True False
    , , PUNCT , punct , False False
    there there ADV EX expl xxxx True True
    is be VERB VBZ ROOT xx True True
    a a DET DT det x True True
    bit bit NOUN NN attr xxx True False
    of of ADP IN prep xx True True
    a a DET DT det x True True
    " " PUNCT `` punct " False False
    u u NOUN NN meta x True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1848 1848 NUM CD nummod dddd False False
            SPACE _SP      False False
    Top top NOUN NN pobj Xxx True False
    of of ADP IN prep xx True True
    line line NOUN NN compound xxxx True False
    techs tech NOUN NNS pobj xxxx True False
    for for ADP IN prep xxx True True
    FCA fca PROPN NNP compound XXX True False
    automobiles automobile NOUN NNS pobj xxxx True False
    hard hard ADJ JJ advmod xxxx True False
    to to PART TO prep xx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1849 1849 NUM CD ROOT dddd False False
            SPACE _SP      False False
    Great great ADJ JJ amod Xxxxx True False
    place place NOUN NN ROOT xxxx True False
    to to PART TO aux xx True True
    work work VERB VB relcl xxxx True False
    . . PUNCT . punct . False False
    Work work NOUN NN nsubj Xxxx True False
    is be VERB VBZ ROOT xx True True
    challenging challenging ADJ JJ acomp xxxx True False
    but but CCONJ CC cc xxx True True
    u u PUNCT LS conj x True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1850 1850 NUM CD nummod dddd False False
            SPACE _SP      False False
    Very very ADV RB advmod Xxxx True False
    dedicated dedicated ADJ JJ amod xxxx True False
    employee employee NOUN NN npadvmod xxxx True False
    . . PUNCT . punct . False False
    But but CCONJ CC cc Xxx True False
    the the DET DT det xxx True True
    top top ADJ JJ amod xxx True True
    management management NOUN NN ROOT xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1851 1851 NUM CD ROOT dddd False False
            SPACE _SP      False False
    I -PRON- PRON PRP nsubj X True False
    grow grow VERB VBP ROOT xxxx True False
    up up PART RP prt xx True True
    working work VERB VBG advcl xxxx True False
    at at ADP IN prep xx True True
    Chrysler chrysler PROPN NNP pobj Xxxxx True False
    ! ! PUNCT . punct ! False False
    I -PRON- PRON PRP nsubj X True False
    learned learn VERB VBD ROOT xxxx True False
    so so ADP IN advmod xx True True
    mu mu NOUN NNS intj xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1852 1852 NUM CD nummod dddd False False
            SPACE _SP      False False
    Chrysler chrysler PROPN NNP nsubj Xxxxx True False
    is be VERB VBZ ROOT xx True True
    a a DET DT det x True True
    great great ADJ JJ amod xxxx True False
    place place NOUN NN attr xxxx True False
    to to PART TO aux xx True True
    work work VERB VB relcl xxxx True False
    and and CCONJ CC cc xxx True True
    has have VERB VBZ conj xxx True True
    grea grea NOUN NN dobj xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1853 1853 NUM CD ROOT dddd False False
            SPACE _SP      False False
    as as ADP IN mark xx True True
    Chrysler chrysler PROPN NNP nsubj Xxxxx True False
    changed change VERB VBD advcl xxxx True False
    names name NOUN NNS dobj xxxx True False
    through through ADP IN prep xxxx True True
    mergers merger NOUN NNS pobj xxxx True False
    I -PRON- PRON PRP nsubj X True False
    fo fo ADP IN relcl xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1854 1854 NUM CD ROOT dddd False False
            SPACE _SP      False False
    A a DET DT det X True False
    job job NOUN NN ROOT xxx True False
    for for ADP IN prep xxx True True
    life life NOUN NN pobj xxxx True False
    very very ADV RB advmod xxxx True True
    good good ADJ JJ amod xxxx True False
    enviroment enviroment NOUN NN appos xxxx True False
    to to PART TO aux xx True True
    put put VERB VB relcl xxx True True
    out out PART RP prt xxx True True
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1855 1855 NUM CD ROOT dddd False False
            SPACE _SP      False False
    I -PRON- PRON PRP nsubj X True False
    loved love VERB VBD ROOT xxxx True False
    going go VERB VBG xcomp xxxx True False
    to to PART TO aux xx True True
    work work VERB VB xcomp xxxx True False
    at at ADP IN prep xx True True
    6:45 6:45 NUM CD nummod d:dd False False
    a.m. a.m. NOUN NN pobj x.x. False False
    and and CCONJ CC cc xxx True True
    getting get VERB VBG conj xxxx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1856 1856 NUM CD nummod dddd False False
            SPACE _SP      False False
    great great ADJ JJ amod xxxx True False
    benefits benefit NOUN NNS dobj xxxx True False
    , , PUNCT , punct , False False
    off off ADV RB advmod xxx True True
    for for ADP IN prep xxx True True
    holidays holiday NOUN NNS pobj xxxx True False
    , , PUNCT , punct , False False
    excellent excellent ADJ JJ amod xxxx True False
    pay pay NOUN NN dobj xxx True False
    , , PUNCT , punct , False False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1857 1857 NUM CD ROOT dddd False False
            SPACE _SP      False False
    Unfortunately unfortunately ADV RB advmod Xxxxx True False
    they -PRON- PRON PRP nsubj xxxx True True
    closed close VERB VBD ROOT xxxx True False
    the the DET DT det xxx True True
    plant plant NOUN NN dobj xxxx True False
    where where ADV WRB advcl xxxx True True
    I -PRON- PRON PRP nsubj X True False
    wo wo VERB MD aux xx True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    1858 1858 NUM CD npadvmod dddd False False
            SPACE _SP      False False
    I -PRON- PRON PRP nsubj X True False
    enjoyed enjoy VERB VBD ROOT xxxx True False
    every every DET DT det xxxx True True
    moment moment NOUN NN dobj xxxx True False
    of of ADP IN prep xx True True
    the the DET DT det xxx True True
    Job job PROPN NNP pobj Xxx True False
    i i PRON PRP nsubj x True True
    was be VERB VBD ROOT xxx True True
    once once ADV RB advmod xxxx True True
    e e PUNCT LS intj x True False
    ... ... PUNCT : punct ... False False
    
     
     SPACE   
     False False
    Name name NOUN NN ROOT Xxxx True False
    : : PUNCT : punct : False False
    Text text PROPN NNP nsubj Xxxx True False
    , , PUNCT , punct , False False
    Length length PROPN NNP npadvmod Xxxxx True False
    : : PUNCT : punct : False False
    1859 1859 NUM CD appos dddd False False
    , , PUNCT , punct , False False
    dtype dtype VERB VB appos xxxx True False
    : : PUNCT : punct : False False
    object object NOUN NN ROOT xxxx True False


#### Words  Tokenization with Spacy


```python
tokenlist=[]
for token in doc:
    tokenlist.append(token)
    
len(tokenlist)  


```




    'object'



#### Sentence Tokenization with Spacy


```python
sentences = list(doc.sents)
sentences[:5]
```




    [0       ,
     Top of line techs for FCA automobiles hard to ...,
     1       Management is moving forward in positive direc...,
     2       ,
     It was a fast pace environment.  ]



#### Word Tokenization with nltk


```python
from nltk.tokenize import RegexpTokenizer

tokenizer = RegexpTokenizer(r'\w+')
tokenizer.tokenize(mystring)[:5]
```




    ['0', 'Top', 'of', 'line', 'techs']



#### Sentence Tokenization with nltk


```python
from nltk.tokenize import sent_tokenize, word_tokenize

sentences2=sent_tokenize(mystring)
print(sentences2[:2])



```

    ['0       Top of line techs for FCA automobiles hard to ...\n1       Management is moving forward in positive direc...\n2       It was a fast pace environment.', "It was easy t...\n3       If you can find a plant that isn't in danger o...\n4       Chrystler was a great place to work for the ti...\n5       Great place to work."]


#### Remove Unwanted Characters from the Senences

* Matches any non-digit character; this is equivalent to the class [^0-9].
* Matches any alphanumeric character; this is equivalent to the class [a-zA-Z0-9_].
* Matches any non-alphanumeric character; this is equivalent to the class [^a-zA-Z0-9_].
* Matches any whitespace character; this is equivalent to the class [ \t\n\r\f\v].
* Matches any non-whitespace character; this is equivalent to the class [^ \t\n\r\f\v].


```python

import re

my_new_string = re.sub('[^ a-zA-Z]', '', sentences2[0])
print(my_new_string)
```

           Top of line techs for FCA automobiles hard to        Management is moving forward in positive direc       It was a fast pace environment


#### Check for Named Entities


```python

#for ent in doc.ents:
#    print(ent.text, ent.start_char, ent.end_char, ent.label_)
    
    
    
entlist=[]
ent_startlist=[]
ent_endlist=[]
ent_labellist=[]
for ent in doc.ents:
    entlist.append(ent.text)
    ent_startlist.append(ent.start_char)
    ent_endlist.append(ent.end_char)
    ent_labellist.append(ent.label_)
    
       # store extracted information in a dataframe
    Named_entity = pd.DataFrame({ 'Entity' : entlist,
                       'ent.start_char' : ent_startlist,
                        'ent.end_char' : ent_endlist,
                        ' ent.label_' :  ent_labellist
                       }) 
    
Named_entity.head()  
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
      <th>ent.label_</th>
      <th>Entity</th>
      <th>ent.end_char</th>
      <th>ent.start_char</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>CARDINAL</td>
      <td>0</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>ORG</td>
      <td>FCA</td>
      <td>33</td>
      <td>30</td>
    </tr>
    <tr>
      <th>2</th>
      <td>GPE</td>
      <td>\n</td>
      <td>58</td>
      <td>57</td>
    </tr>
    <tr>
      <th>3</th>
      <td>GPE</td>
      <td>\n</td>
      <td>116</td>
      <td>115</td>
    </tr>
    <tr>
      <th>4</th>
      <td>GPE</td>
      <td>\n</td>
      <td>174</td>
      <td>173</td>
    </tr>
  </tbody>
</table>
</div>



#### Remove Stop Words nltk


```python
# Import nltk
import nltk

# Get English stopwords and print some of them
sw = nltk.corpus.stopwords.words('english')
```


```python
# split into words
from nltk.tokenize import word_tokenize
tokens = word_tokenize(mystring)

# convert to lower case
tokens = [w.lower() for w in tokens]

# remove punctuation from each word
import string
table = str.maketrans('', '', string.punctuation)
stripped = [w.translate(table) for w in tokens]


# remove remaining tokens that are not alphabetic
words = [word for word in stripped if word.isalpha()]


# filter out stop words
from nltk.corpus import stopwords
stop_words = set(stopwords.words('english'))
words = [w for w in words if not w in stop_words]
print(words[:10])



# split into words
from nltk.tokenize import word_tokenize
tokens = word_tokenize(mystring)

# stemming of words
from nltk.stem.porter import PorterStemmer
porter = PorterStemmer()
stemmed = [porter.stem(word) for word in tokens]
print(stemmed[:10])
```

    ['top', 'line', 'techs', 'fca', 'automobiles', 'hard', 'pros', 'benefits', 'flexible', 'overtime']
    ['0', 'top', 'of', 'line', 'tech', 'for', 'fca', 'automobil', 'hard', 'to']


#### Remove Stop Words with Spacy


```python
import spacy
nlp = spacy.load('en_core_web_sm')
# filter out stop words
from nltk.corpus import stopwords
stop_words = set(stopwords.words('english'))

words = [w for w in tokenlist if not w in stop_words]
print(words[:10])
```

    [0,       , Top, of, line, techs, for, FCA, automobiles, hard]



#### Add Self Defined Stop Words


```python
from spacy.lang.en.stop_words import STOP_WORDS

#print(STOP_WORDS) # <- set of Spacy's default stop words

STOP_WORDS.add("add word")

for word in STOP_WORDS:
    lexeme = nlp.vocab[word]
    lexeme.is_stop = True
```


```python
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords
 
data = mystring 
stopWords = set(stopwords.words('english'))
words = word_tokenize(data)
wordsFiltered = []
 
for w in words:
    if w not in stopWords:
        wordsFiltered.append(w)
 
    #print(wordsFiltered)
   
```

#### Remove all non alphabetic characters 


```python
# remove all tokens that are not alphabetic
#The method isalnum() checks whether the string consists of alphanumeric characters.
cleanword = [word for word in wordsFiltered if word.isalpha()]
cleanword[:10]
```




    ['Top',
     'line',
     'techs',
     'FCA',
     'automobiles',
     'hard',
     'Pros',
     'Benefits',
     'flexible',
     'overtime']



#### Stemming Words


```python
from nltk.stem import PorterStemmer
from nltk.tokenize import sent_tokenize, word_tokenize
 
cleanwords = []
ps = PorterStemmer()
 
for word in cleanword:
    #print(ps.stem(word))
    cleanwords.append(ps.stem(word))
    
```


```python
cleanwords[:10]
```




    ['top',
     'line',
     'tech',
     'fca',
     'automobil',
     'hard',
     'pro',
     'benefit',
     'flexibl',
     'overtim']



#### Visualize Words with The Highest Frequency


```python
#Import datavis libraries
import matplotlib.pyplot as plt
import seaborn as sns

# Figures inline and set visualization style
%matplotlib inline
sns.set()
#fig, ax = plt.subplots(1, 1,figsize=(10,7))
plt.figure(figsize=(15,8))
plt.plot( linewidth=2.0)
plt.title('Most Common Words in Review ', fontsize=20)
plt.ylabel('Counts', fontsize=20)
plt.xlabel('Words', fontsize=20)
# Create freq dist and plot
freqdist1 = nltk.FreqDist(cleanwords)
freqdist1.plot(40)


plt.show()
```


![png](output_60_0.png)



```python
from collections import Counter
c = Counter(cleanwords)
c.most_common(10)
```




    [('work', 22),
     ('I', 14),
     ('great', 14),
     ('chrysler', 9),
     ('fca', 7),
     ('place', 7),
     ('job', 5),
     ('good', 5),
     ('manag', 5),
     ('the', 5)]




```python
#pd.DataFrame(c)
#df = pd.DataFrame(np.array(my_list).reshape(3,3), columns = list("abc"))
dfcommon = pd.DataFrame.from_dict(c, orient='index').reset_index()
dfcommon.columns = ['Word', 'Frequency']
dfcommon=dfcommon.sort_values(by='Frequency',ascending=[False])
dfcommon.head()
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
      <th>Word</th>
      <th>Frequency</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>13</th>
      <td>work</td>
      <td>22</td>
    </tr>
    <tr>
      <th>12</th>
      <td>I</td>
      <td>14</td>
    </tr>
    <tr>
      <th>28</th>
      <td>great</td>
      <td>14</td>
    </tr>
    <tr>
      <th>83</th>
      <td>chrysler</td>
      <td>9</td>
    </tr>
    <tr>
      <th>3</th>
      <td>fca</td>
      <td>7</td>
    </tr>
  </tbody>
</table>
</div>




```python
boxdata=dfcommon.iloc[0:20,:]
plt.figure(figsize=(15,8))
ax = sns.boxplot(x="Word", y='Frequency', data=boxdata)
plt.show()
```

    /Users/nanaakwasiabayieboateng/anaconda3/lib/python3.6/site-packages/seaborn/categorical.py:462: FutureWarning: remove_na is deprecated and is a private function. Do not use.
      box_data = remove_na(group_data)



![png](output_63_1.png)



```python
plt.figure(figsize=(20,8))
sns.set_style('ticks')
#fig, ax = plt.subplots()
# the size of A4 paper
#fig.set_size_inches(11.7, 8.27)
ax = sns.barplot(x="Word", y="Frequency", data=boxdata)
plt.show()
```

    /Users/nanaakwasiabayieboateng/anaconda3/lib/python3.6/site-packages/seaborn/categorical.py:1460: FutureWarning: remove_na is deprecated and is a private function. Do not use.
      stat_data = remove_na(group_data)



![png](output_64_1.png)



```python
params = {'legend.fontsize': 'x-large',
          'figure.figsize': (15, 8),
         'axes.labelsize': 'x-large',
         'axes.titlesize':'x-large',
         'xtick.labelsize':'x-large',
         'ytick.labelsize':'x-large'}
plt.rcParams.update(params)
plt.title('Most Common Words in Review ', fontsize=20)
plt.ylabel('Counts', fontsize=20)
plt.xlabel('Words', fontsize=20)
freqdist1 = nltk.FreqDist(cleanwords)
freqdist1.plot(40)
fig.savefig('fca.jpg')
plt.show()
```


![png](output_65_0.png)



```python
def ExtractAlphanumericc(InputString):
    import re
    #string = "man"
    pattern = re.compile('\W')
    string = re.sub(pattern, '', InputString)
    return string;
#print(string) 


    ExtractAlphanumericc(mytring)
```


```python
def ExtractAlphanumeric(InputString):
    from string import ascii_letters, digits
    return "".join([ch for ch in InputString if ch in (ascii_letters + digits)])



#list(map( ExtractAlphanumeric,mystring))
```


```python
def ExtractAlphanumericc(InputString):
    import re
    #string = "man"
    pattern = re.compile('\W')
    string = re.sub(pattern, '', InputString)
    return string;
```


```python
 #ExtractAlphanumericc(mystring)
 
 #list(map( ExtractAlphanumericc,mystring))   
```


```python
  #Remove all parenthesis from Jobstatus column
    #df['Jobstatus']=df['Jobstatus'].str.replace("(","")
import re
text = re.sub('[^A-Za-z]', ' ', str(words)) # Assuming it is a string
text
# remove all tokens that are not alphabetic
cleanwords = [word for word in words if word.isalpha()]
cleanwords[:10]
```




    ['Top',
     'of',
     'line',
     'techs',
     'for',
     'FCA',
     'automobiles',
     'hard',
     'to',
     'Pros']



#### Text Cleaning and Processing


```python
    #Convert to lower case
    mystring = mystring.lower()
    
    #Convert www.* or https?://* to URL
    mystring = re.sub('((www\.[^\s]+)|(https?://[^\s]+))','URL',mystring)
    
    #Convert @username to AT_USER
    mystring = re.sub('@[^\s]+','AT_USER',mystring)
    
    #Remove additional white spaces
    mystring = re.sub('[\s]+', ' ', mystring)
    
    #Replace #word with word
    mystring = re.sub(r'#([^\s]+)', r'\1', mystring)
    #replace ...
    mystring =re.sub('[...]', '', mystring)
    #trim
    mystring = mystring.strip('\'"')
    mystring[:100]
```




    '0 top of line techs for fca automobiles hard to  1 pros:benefits, flexible overtime, career advan 2 '



#### Sentiment Analysis with VADER Library


```python
from vaderSentiment.vaderSentiment import SentimentIntensityAnalyzer

analyser = SentimentIntensityAnalyzer()
```


```python
import re

#remove ...\n characters
def removespecial (w):
    my_new_string = re.sub('[...]', '', w)
    #my_new_string = re.sub('[..\]', '', w)
    return my_new_string;

sentences3=list(map(removespecial,sentences2))
sentences3[0]
```




    '0       Top of line techs for FCA automobiles hard to \n1       Pros:Benefits, flexible overtime, career advan\n2       I was working as supplier quality engineer'




```python
import re
my = re.sub('[...]', '', sentences2[0])
print(my)
```

    0       Top of line techs for FCA automobiles hard to 
    1       Pros:Benefits, flexible overtime, career advan
    2       I was working as supplier quality engineer


#### Text Polarity with VADER library

Define function to print sentiment scores


```python
def print_sentiment_scores(sentence):
    snt = analyser.polarity_scores(sentence)
    #print("{:-<40} {}".format(sentence, str(snt)))
    print("{:-<65} {}".format(sentence, str(snt)))
```


```python
print_sentiment_scores(sentences2[0])
```

    0       Top of line techs for FCA automobiles hard to ...
    1       Management is moving forward in positive direc...
    2       It was a fast pace environment. {'neg': 0.054, 'neu': 0.736, 'pos': 0.209, 'compound': 0.6124}



The compound score is computed by summing the valence scores of each word in the lexicon, adjusted according to the rules, and then normalized to be between -1 (most extreme negative) and +1 (most extreme positive). This is the most useful metric if you want a single unidimensional measure of sentiment for a given sentence. Calling it a 'normalized, weighted composite score' is accurate.

It is also useful for researchers who would like to set standardized thresholds for classifying sentences as either positive, neutral, or negative. Typical threshold values (used in the literature cited on this page) are:

* positive sentiment: compound score >= 0.05
* neutral sentiment: (compound score > -0.05) and (compound score < 0.05)
* negative sentiment: compound score <= -0.05
The pos, neu, and neg scores are ratios for proportions of text that fall in each category (so these should all add up to be 1... or close to it with float operation). These are the most useful metrics if you want multidimensional measures of sentiment for a given sentence.


```python
analyzer.polarity_scores(sentences2[0])
```




    {'compound': 0.6124, 'neg': 0.054, 'neu': 0.736, 'pos': 0.209}




```python
analyzer.polarity_scores(sentences2[0])["compound"]
```




    0.6124




```python
from nltk.classify import NaiveBayesClassifier
from nltk.corpus import subjectivity
from nltk.sentiment import SentimentAnalyzer
from nltk.sentiment.util import *

sid = SentimentIntensityAnalyzer()
sid.polarity_scores(sentences2[0])


def nltkpolarity (w):
    sid = SentimentIntensityAnalyzer()
    compound=sid.polarity_scores(w)["compound"]

    return compound;


nltkpolarity(sentences2[0])


dnltk=list(map(nltkpolarity , AllData["Text"]))
dnltk[-1]
```




    0.5574



#### Group Reviews into Positive, Neutral and Negative


```python
Reviewclass=[]

for i in dnltk:
    
        if i >= 0.05:
            Reviewclass.append("Positive")

        elif -0.05 < i < 0.05:
            Reviewclass.append("Neutral")
    
        else:
            Reviewclass.append("Negative")
            
Reviewclass[:5]      
```




    ['Negative', 'Positive', 'Positive', 'Negative', 'Negative']




```python
dnltk[:5]
```




    [-0.4215, 0.8481, 0.8755, -0.1531, -0.1531]




```python
Reviewclass=np.zeros(1869)

for i in range(len(dnltk)):
    
    if dnltk[i] >= 0.05:
            Reviewclass[i]=1
    elif -0.05 < dnltk[i] < 0.05:
            Reviewclass[i]=0
    else:
            Reviewclass[i]=-1
            
Reviewclass[:5]
```




    array([-1.,  1.,  1., -1., -1.])




```python
#Reviewclass[Reviewclass=="Negative"]
AllData["Reviewclass"]=Reviewclass

AllData.head(4)
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
      <th>Unnamed: 0</th>
      <th>Unnamed: 0.1</th>
      <th>Unnamed: 0.1.1</th>
      <th>Job</th>
      <th>Date</th>
      <th>Jobstatus</th>
      <th>Location</th>
      <th>Text</th>
      <th>Title</th>
      <th>polarity</th>
      <th>subjectivity</th>
      <th>Reviewclass</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>1868</td>
      <td>1868</td>
      <td>20</td>
      <td>Janitorial Facilities Supervisor</td>
      <td>2012-01-30</td>
      <td>Former Employee</td>
      <td>Warren Truck Assembly Plant, Newark Assembly P...</td>
      <td>Contracted thru Caravan Knight, Supervised all...</td>
      <td>Contract Employee</td>
      <td>1.500000e-01</td>
      <td>0.466667</td>
      <td>Negative</td>
    </tr>
    <tr>
      <th>1</th>
      <td>1867</td>
      <td>1867</td>
      <td>19</td>
      <td>Materials Manager</td>
      <td>2012-02-02</td>
      <td>Former Employee</td>
      <td>Multiple with 2 international assignments</td>
      <td>Great to see how they are coming back. Buildin...</td>
      <td>Solid company</td>
      <td>2.700000e-01</td>
      <td>0.350000</td>
      <td>Positive</td>
    </tr>
    <tr>
      <th>2</th>
      <td>1866</td>
      <td>1866</td>
      <td>18</td>
      <td>Product Development Specialist</td>
      <td>2012-02-09</td>
      <td>Former Employee</td>
      <td>Auburn Hills, MI</td>
      <td>There is a vast amount of areas to work at. Fr...</td>
      <td>I loved going to work every day. Corporate cul...</td>
      <td>3.750000e-01</td>
      <td>0.750000</td>
      <td>Positive</td>
    </tr>
    <tr>
      <th>3</th>
      <td>1865</td>
      <td>1865</td>
      <td>17</td>
      <td>Project Manager and Business Analyst</td>
      <td>2012-02-24</td>
      <td>Former Employee</td>
      <td>Auburn Hills, MI</td>
      <td>Chrysler LLC went thru a lot of changes from 2...</td>
      <td>Great people to work with. I worked in several...</td>
      <td>5.551115e-17</td>
      <td>0.633333</td>
      <td>Negative</td>
    </tr>
  </tbody>
</table>
</div>




```python
range(len(dnltk))
```




    range(0, 1869)



#### Text Polarity and Subjectivity with Textblob


```python
from textblob import TextBlob
myvariable = AllData["Text"]
mystring = str(myvariable)  


AllData.info()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 1869 entries, 0 to 1868
    Data columns (total 11 columns):
    Unnamed: 0        1869 non-null int64
    Unnamed: 0.1      1869 non-null int64
    Unnamed: 0.1.1    1869 non-null int64
     Job              1869 non-null object
    Date              1869 non-null object
    Jobstatus         1869 non-null object
    Location          1869 non-null object
    Text              1869 non-null object
    Title             1864 non-null object
    polarity          1869 non-null float64
    subjectivity      1869 non-null float64
    dtypes: float64(2), int64(3), object(6)
    memory usage: 160.7+ KB



```python
AllData.dtypes
```




    Unnamed: 0       int64
    Unnamed: 0.1     int64
     Job            object
    Date            object
    Jobstatus       object
    Location        object
    Text            object
    Title           object
    dtype: object




```python


def textpolarity (w):
    zen = TextBlob(w)
    polarity=zen.sentiment.polarity
    subjectivity=zen.sentiment.subjectivity
    return polarity ,subjectivity;



d=list(map(textpolarity , AllData["Text"]))
len(d)
d[:5]

textpolarity(sentences2[0])
```




    ([0.15890151515151513], [0.546780303030303])




```python
df2 = pd.DataFrame(np.array(d).reshape(len(d),2), columns =['polarity','subjectivity'])


#df2.info()
AllData["polarity"]=df2["polarity"]

AllData["subjectivity"]=df2["subjectivity"]

# sort the date column
AllData=AllData.sort_values(by=['Date'], ascending=[ True])



# Create a Pandas dataframe from the data.

pd.DataFrame.to_csv(AllData,'/Users/nanaakwasiabayieboateng/PythonNLTK/AllData.csv')


AllData.head(2)
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
      <th>Unnamed: 0</th>
      <th>Unnamed: 0.1</th>
      <th>Unnamed: 0.1.1</th>
      <th>Job</th>
      <th>Date</th>
      <th>Jobstatus</th>
      <th>Location</th>
      <th>Text</th>
      <th>Title</th>
      <th>polarity</th>
      <th>subjectivity</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>1868</td>
      <td>1868</td>
      <td>20</td>
      <td>Janitorial Facilities Supervisor</td>
      <td>2012-01-30</td>
      <td>Former Employee</td>
      <td>Warren Truck Assembly Plant, Newark Assembly P...</td>
      <td>Contracted thru Caravan Knight, Supervised all...</td>
      <td>Contract Employee</td>
      <td>0.15</td>
      <td>0.466667</td>
    </tr>
    <tr>
      <th>1</th>
      <td>1867</td>
      <td>1867</td>
      <td>19</td>
      <td>Materials Manager</td>
      <td>2012-02-02</td>
      <td>Former Employee</td>
      <td>Multiple with 2 international assignments</td>
      <td>Great to see how they are coming back. Buildin...</td>
      <td>Solid company</td>
      <td>0.27</td>
      <td>0.350000</td>
    </tr>
  </tbody>
</table>
</div>




```python
# visualisation of anomaly throughout time (viz 1)
fig, ax = plt.subplots(1, 1,figsize=(20,10))
colors = {0:"#440154FF", 1:"#482878FF", 2:"#3E4A89FF", 3:"#31688EFF", 4:"#26828EFF", 5:"#1F9E89FF", 6:"#CFE11CFF", 7:"#482878FF", 8:"#482878FF", 9:"#B4DE2CFF", 10:"#FDE725FF", 11: "#9FDA3AFF", 12:"#71CF57FF", 13:"#4AC16DFF", 14: 'darkgrey'}



ax.scatter(AllData["Date"], AllData["polarity"], color="#71CF57FF", label='Polarity')
ax.scatter(AllData["Date"],AllData["subjectivity"], color="#31688EFF", label= 'Subjectivity')
plt.title('Polarity and Subjectivity ', fontsize=20)
plt.ylabel('Value', fontsize=20)
plt.xlabel('Date', fontsize=20)
plt.legend(fontsize=20,loc='lower right')
plt.show()

```


![png](output_96_0.png)



```python
# visualisation of anomaly throughout time (viz 1)
fig, ax = plt.subplots(1, 1,figsize=(20,10))
colors = {0:"#440154FF", 1:"#482878FF", 2:"#3E4A89FF", 3:"#31688EFF", 4:"#26828EFF", 5:"#1F9E89FF", 6:"#CFE11CFF", 7:"#482878FF", 8:"#482878FF", 9:"#B4DE2CFF", 10:"#FDE725FF", 11: "#9FDA3AFF", 12:"#71CF57FF", 13:"#4AC16DFF", 14: 'darkgrey'}

#AllData=AllData[:1000]

params = {'legend.fontsize': 'x-large',
          'figure.figsize': (15, 8),
         'axes.labelsize': 'x-large',
         'axes.titlesize':'x-large',
         'xtick.labelsize':'x-large',
         'ytick.labelsize':'x-large'}
plt.rcParams.update(params)

x=AllData["Date"]

ax.plot(x, AllData["polarity"], color="#71CF57FF", label='Polarity')
ax.plot(x,AllData["subjectivity"], color="#31688EFF", label= 'Subjectivity')
#set ticks every week
#ax.xaxis.set_major_locator(mdates.WeekdayLocator())
#set major ticks format
#ax.xaxis.set_major_formatter(mdates.DateFormatter('%b %d %y'))
plt.title('Polarity and Subjectivity ', fontsize=20)
plt.ylabel('Value', fontsize=20)
plt.xlabel('Date', fontsize=20)
#plt.xtick.labelsize(fontsize=20)
plt.legend(fontsize=20,loc='lower right')
plt.show()
```


![png](output_97_0.png)



```python
params = {'legend.fontsize': 'x-large',
          'figure.figsize': (15, 8),
         'axes.labelsize': 'x-large',
         'axes.titlesize':'x-large',
         'xtick.labelsize':'x-large',
         'ytick.labelsize':'x-large'}
plt.rcParams.update(params)
plt.title('Polarity and Subjectivity ', fontsize=20)
plt.ylabel('Values', fontsize=20)
plt.xlabel('Date', fontsize=20)
plt.plot(AllData['Date'], AllData['polarity'], 'k', AllData['Date'], AllData['subjectivity'],
         'r--',lw=2)
#fig.savefig('fca.jpg')
plt.grid(True)
plt.legend(loc='lower right')
plt.show()
```


![png](output_98_0.png)



```python
AllData.shape
```




    (10, 10)




```python
import cufflinks as cf #cufflinks binds pandas to plotly for easy plotting
from plotly.offline import init_notebook_mode, iplot
# initialize notebook mode
init_notebook_mode(connected=True)
#type below in terminal before starting jupiter
# this stops an error message about limit of data that 
# can be read into notebooks
#jupyter notebook --NotebookApp.iopub_data_rate_limit=10000000000
# set to offline
cf.go_offline()


#themes: solar,white,pearl,space,polar,henanigans


#reset the Date column to index
AllData2=AllData.set_index(['Date'])
AllData2

AllData2[['polarity', 'subjectivity']].iplot(kind='scatter', up_color='#482878FF', down_color='#1F9E89FF', theme='white', 
                                           title='Polarity and Subjectivity', xTitle='Time',yTitle='Values')


```


<script>requirejs.config({paths: { 'plotly': ['https://cdn.plot.ly/plotly-latest.min']},});if(!window.Plotly) {{require(['plotly'],function(plotly) {window.Plotly=plotly;});}}</script>


    IOPub data rate exceeded.
    The notebook server will temporarily stop sending output
    to the client in order to avoid crashing it.
    To change this limit, set the config variable
    `--NotebookApp.iopub_data_rate_limit`.



<div id="de41be24-5657-4708-9868-a54a331d32c8" style="height: 525px; width: 100%;" class="plotly-graph-div"></div><script type="text/javascript">require(["plotly"], function(Plotly) { window.PLOTLYENV=window.PLOTLYENV || {};window.PLOTLYENV.BASE_URL="https://plot.ly";Plotly.newPlot("de41be24-5657-4708-9868-a54a331d32c8", [{"type": "scatter", "x": ["2012-01-30", "2012-02-02", "2012-02-09", "2012-02-24", "2012-02-24", "2012-02-28", "2012-02-29", "2012-03-01", "2012-03-06", "2012-03-06", "2012-03-07", "2012-03-10", "2012-03-16", "2012-03-17", "2012-03-21", "2012-03-23", "2012-03-23", "2012-03-26", "2012-03-26", "2012-03-27", "2012-03-27", "2012-03-27", "2012-03-28", "2012-03-30", "2012-04-02", "2012-04-10", "2012-04-11", "2012-04-12", "2012-04-17", "2012-04-25", "2012-04-25", "2012-04-27", "2012-04-27", "2012-04-30", "2012-04-30", "2012-05-01", "2012-05-03", "2012-05-04", "2012-05-06", "2012-05-08", "2012-05-08", "2012-05-08", "2012-05-09", "2012-05-09", "2012-05-09", "2012-05-10", "2012-05-15", "2012-05-22", "2012-05-22", "2012-05-23", "2012-05-24", "2012-06-04", "2012-06-06", "2012-06-10", "2012-06-13", "2012-06-19", "2012-06-21", "2012-06-22", "2012-06-25", "2012-06-26", "2012-06-28", "2012-07-01", "2012-07-01", "2012-07-02", "2012-07-06", "2012-07-09", "2012-07-11", "2012-07-12", "2012-07-12", "2012-07-14", "2012-07-15", "2012-07-17", "2012-07-17", "2012-07-18", "2012-07-22", "2012-07-24", "2012-07-24", "2012-07-25", "2012-07-27", "2012-07-27", "2012-08-02", "2012-08-02", "2012-08-02", "2012-08-03", "2012-08-06", "2012-08-07", "2012-08-10", "2012-08-13", "2012-08-14", "2012-08-16", "2012-08-17", "2012-08-19", "2012-08-20", "2012-08-21", "2012-08-21", "2012-08-22", "2012-08-24", "2012-08-27", "2012-09-04", "2012-09-05", "2012-09-10", "2012-09-11", "2012-09-15", "2012-09-17", "2012-09-17", "2012-09-17", "2012-09-18", "2012-09-20", "2012-09-23", "2012-09-26", "2012-09-26", "2012-09-27", "2012-09-28", "2012-10-01", "2012-10-02", "2012-10-03", "2012-10-03", "2012-10-08", "2012-10-09", "2012-10-09", "2012-10-13", "2012-10-13", "2012-10-14", "2012-10-14", "2012-10-15", "2012-10-17", "2012-10-17", "2012-10-20", "2012-10-21", "2012-10-22", "2012-10-23", "2012-10-23", "2012-10-28", "2012-10-29", "2012-10-29", "2012-10-30", "2012-10-30", "2012-10-30", "2012-10-30", "2012-10-31", "2012-11-07", "2012-11-07", "2012-11-08", "2012-11-08", "2012-11-10", "2012-11-13", "2012-11-14", "2012-11-16", "2012-11-16", "2012-11-18", "2012-11-24", "2012-11-26", "2012-11-29", "2012-12-03", "2012-12-03", "2012-12-06", "2012-12-08", "2012-12-11", "2012-12-12", "2012-12-12", "2012-12-16", "2012-12-17", "2012-12-21", "2012-12-26", "2012-12-30", "2012-12-30", "2013-01-04", "2013-01-05", "2013-01-07", "2013-01-08", "2013-01-15", "2013-01-15", "2013-01-16", "2013-01-17", "2013-01-17", "2013-01-18", "2013-01-20", "2013-01-22", "2013-01-22", "2013-01-25", "2013-01-27", "2013-01-27", "2013-01-27", "2013-01-29", "2013-01-30", "2013-02-01", "2013-02-01", "2013-02-01", "2013-02-03", "2013-02-04", "2013-02-05", "2013-02-05", "2013-02-06", "2013-02-06", "2013-02-06", "2013-02-07", "2013-02-12", "2013-02-12", "2013-02-15", "2013-02-15", "2013-02-15", "2013-02-21", "2013-02-22", "2013-02-23", "2013-02-25", "2013-02-25", "2013-02-26", "2013-02-27", "2013-02-28", "2013-03-02", "2013-03-02", "2013-03-04", "2013-03-04", "2013-03-05", "2013-03-05", "2013-03-06", "2013-03-10", "2013-03-11", "2013-03-11", "2013-03-14", "2013-03-19", "2013-03-19", "2013-03-20", "2013-03-20", "2013-03-25", "2013-03-25", "2013-03-25", "2013-03-27", "2013-03-27", "2013-03-29", "2013-04-02", "2013-04-02", "2013-04-05", "2013-04-05", "2013-04-05", "2013-04-09", "2013-04-09", "2013-04-10", "2013-04-11", "2013-04-11", "2013-04-12", "2013-04-12", "2013-04-13", "2013-04-14", "2013-04-17", "2013-04-18", "2013-04-18", "2013-04-21", "2013-04-22", "2013-04-23", "2013-04-23", "2013-04-23", "2013-04-24", "2013-04-25", "2013-04-26", "2013-04-29", "2013-04-29", "2013-04-29", "2013-04-30", "2013-05-01", "2013-05-09", "2013-05-09", "2013-05-09", "2013-05-09", "2013-05-13", "2013-05-16", "2013-05-19", "2013-05-22", "2013-05-28", "2013-05-29", "2013-05-29", "2013-06-01", "2013-06-03", "2013-06-04", "2013-06-04", "2013-06-07", "2013-06-08", "2013-06-08", "2013-06-10", "2013-06-11", "2013-06-15", "2013-06-17", "2013-06-18", "2013-06-22", "2013-06-23", "2013-06-24", "2013-06-25", "2013-06-26", "2013-06-26", "2013-06-26", "2013-06-28", "2013-06-29", "2013-07-01", "2013-07-05", "2013-07-06", "2013-07-08", "2013-07-08", "2013-07-10", "2013-07-12", "2013-07-12", "2013-07-14", "2013-07-15", "2013-07-15", "2013-07-16", "2013-07-17", "2013-07-17", "2013-07-18", "2013-07-19", "2013-07-19", "2013-07-22", "2013-07-23", "2013-07-24", "2013-07-25", "2013-07-27", "2013-07-28", "2013-07-29", "2013-07-29", "2013-07-30", "2013-08-03", "2013-08-03", "2013-08-06", "2013-08-06", "2013-08-07", "2013-08-07", "2013-08-08", "2013-08-09", "2013-08-10", "2013-08-13", "2013-08-15", "2013-08-16", "2013-08-16", "2013-08-16", "2013-08-20", "2013-08-20", "2013-08-21", "2013-08-26", "2013-08-27", "2013-08-27", "2013-08-28", "2013-08-28", "2013-08-29", "2013-08-30", "2013-08-30", "2013-09-01", "2013-09-02", "2013-09-02", "2013-09-03", "2013-09-03", "2013-09-03", "2013-09-03", "2013-09-06", "2013-09-06", "2013-09-06", "2013-09-07", "2013-09-09", "2013-09-09", "2013-09-10", "2013-09-10", "2013-09-11", "2013-09-11", "2013-09-13", "2013-09-14", "2013-09-18", "2013-09-18", "2013-09-19", "2013-09-20", "2013-09-23", "2013-09-23", "2013-09-24", "2013-09-27", "2013-09-28", "2013-10-01", "2013-10-01", "2013-10-02", "2013-10-03", "2013-10-06", "2013-10-08", "2013-10-08", "2013-10-10", "2013-10-13", "2013-10-14", "2013-10-14", "2013-10-14", "2013-10-16", "2013-10-16", "2013-10-17", "2013-10-22", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-24", "2013-10-27", "2013-10-28", "2013-10-29", "2013-10-31", "2013-10-31", "2013-11-03", "2013-11-04", "2013-11-04", "2013-11-05", "2013-11-06", "2013-11-07", "2013-11-07", "2013-11-08", "2013-11-14", "2013-11-14", "2013-11-15", "2013-11-17", "2013-11-17", "2013-11-18", "2013-11-20", "2013-11-22", "2013-11-22", "2013-12-01", "2013-12-02", "2013-12-03", "2013-12-04", "2013-12-04", "2013-12-04", "2013-12-09", "2013-12-10", "2013-12-10", "2013-12-10", "2013-12-11", "2013-12-16", "2013-12-16", "2013-12-17", "2013-12-18", "2013-12-21", "2013-12-21", "2013-12-23", "2013-12-23", "2013-12-26", "2013-12-27", "2013-12-31", "2014-01-05", "2014-01-05", "2014-01-05", "2014-01-08", "2014-01-09", "2014-01-10", "2014-01-12", "2014-01-14", "2014-01-16", "2014-01-17", "2014-01-20", "2014-01-20", "2014-01-20", "2014-01-21", "2014-01-21", "2014-01-23", "2014-01-25", "2014-01-27", "2014-01-28", "2014-01-28", "2014-01-29", "2014-01-29", "2014-01-31", "2014-01-31", "2014-02-02", "2014-02-03", "2014-02-04", "2014-02-05", "2014-02-05", "2014-02-06", "2014-02-06", "2014-02-12", "2014-02-13", "2014-02-15", "2014-02-17", "2014-02-18", "2014-02-19", "2014-02-21", "2014-02-25", "2014-02-25", "2014-02-25", "2014-02-27", "2014-02-27", "2014-02-28", "2014-03-02", "2014-03-03", "2014-03-05", "2014-03-05", "2014-03-09", "2014-03-12", "2014-03-12", "2014-03-16", "2014-03-19", "2014-03-19", "2014-03-22", "2014-03-23", "2014-03-26", "2014-03-27", "2014-03-28", "2014-03-29", "2014-03-31", "2014-03-31", "2014-03-31", "2014-04-01", "2014-04-02", "2014-04-03", "2014-04-06", "2014-04-07", "2014-04-08", "2014-04-09", "2014-04-10", "2014-04-15", "2014-04-16", "2014-04-16", "2014-04-16", "2014-04-17", "2014-04-18", "2014-04-24", "2014-04-24", "2014-05-02", "2014-05-05", "2014-05-05", "2014-05-07", "2014-05-07", "2014-05-09", "2014-05-09", "2014-05-10", "2014-05-14", "2014-05-15", "2014-05-15", "2014-05-16", "2014-05-16", "2014-05-20", "2014-05-21", "2014-05-21", "2014-05-23", "2014-05-23", "2014-05-24", "2014-05-27", "2014-05-27", "2014-05-27", "2014-05-29", "2014-06-02", "2014-06-03", "2014-06-04", "2014-06-05", "2014-06-06", "2014-06-06", "2014-06-09", "2014-06-14", "2014-06-16", "2014-06-17", "2014-06-19", "2014-06-19", "2014-06-20", "2014-06-20", "2014-06-20", "2014-06-22", "2014-06-23", "2014-06-23", "2014-06-23", "2014-06-24", "2014-06-24", "2014-06-25", "2014-06-28", "2014-06-29", "2014-06-30", "2014-07-01", "2014-07-02", "2014-07-07", "2014-07-08", "2014-07-11", "2014-07-11", "2014-07-12", "2014-07-13", "2014-07-14", "2014-07-16", "2014-07-16", "2014-07-17", "2014-07-20", "2014-07-21", "2014-07-22", "2014-07-22", "2014-07-23", "2014-07-23", "2014-07-23", "2014-07-25", "2014-07-25", "2014-07-25", "2014-07-27", "2014-07-28", "2014-07-30", "2014-07-31", "2014-08-04", "2014-08-05", "2014-08-05", "2014-08-09", "2014-08-11", "2014-08-12", "2014-08-13", "2014-08-14", "2014-08-14", "2014-08-15", "2014-08-17", "2014-08-18", "2014-08-18", "2014-08-18", "2014-08-23", "2014-08-26", "2014-08-26", "2014-08-27", "2014-08-29", "2014-08-30", "2014-08-30", "2014-08-31", "2014-09-02", "2014-09-03", "2014-09-03", "2014-09-04", "2014-09-05", "2014-09-06", "2014-09-07", "2014-09-08", "2014-09-09", "2014-09-11", "2014-09-12", "2014-09-12", "2014-09-12", "2014-09-12", "2014-09-15", "2014-09-16", "2014-09-16", "2014-09-17", "2014-09-18", "2014-09-19", "2014-09-19", "2014-09-19", "2014-09-21", "2014-09-22", "2014-09-22", "2014-09-23", "2014-09-27", "2014-09-27", "2014-09-29", "2014-09-30", "2014-10-01", "2014-10-02", "2014-10-04", "2014-10-04", "2014-10-06", "2014-10-07", "2014-10-07", "2014-10-08", "2014-10-12", "2014-10-12", "2014-10-13", "2014-10-14", "2014-10-15", "2014-10-16", "2014-10-18", "2014-10-19", "2014-10-20", "2014-10-20", "2014-10-21", "2014-10-21", "2014-10-22", "2014-10-22", "2014-10-23", "2014-10-23", "2014-10-25", "2014-10-27", "2014-10-27", "2014-10-29", "2014-10-30", "2014-10-30", "2014-10-31", "2014-11-03", "2014-11-04", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-19", "2014-11-20", "2014-11-21", "2014-11-22", "2014-11-24", "2014-11-24", "2014-11-24", "2014-11-26", "2014-11-30", "2014-12-01", "2014-12-01", "2014-12-02", "2014-12-03", "2014-12-04", "2014-12-04", "2014-12-05", "2014-12-06", "2014-12-08", "2014-12-08", "2014-12-11", "2014-12-16", "2014-12-17", "2014-12-19", "2014-12-23", "2014-12-26", "2014-12-26", "2014-12-26", "2014-12-27", "2014-12-27", "2014-12-27", "2014-12-29", "2014-12-29", "2014-12-30", "2015-01-01", "2015-01-01", "2015-01-01", "2015-01-02", "2015-01-05", "2015-01-05", "2015-01-05", "2015-01-06", "2015-01-06", "2015-01-07", "2015-01-07", "2015-01-09", "2015-01-10", "2015-01-10", "2015-01-10", "2015-01-11", "2015-01-11", "2015-01-12", "2015-01-12", "2015-01-13", "2015-01-14", "2015-01-15", "2015-01-18", "2015-01-18", "2015-01-19", "2015-01-19", "2015-01-19", "2015-01-19", "2015-01-21", "2015-01-21", "2015-01-23", "2015-01-25", "2015-01-28", "2015-01-28", "2015-01-29", "2015-02-01", "2015-02-02", "2015-02-04", "2015-02-05", "2015-02-05", "2015-02-06", "2015-02-07", "2015-02-09", "2015-02-10", "2015-02-12", "2015-02-13", "2015-02-14", "2015-02-15", "2015-02-17", "2015-02-19", "2015-02-20", "2015-02-23", "2015-02-23", "2015-02-23", "2015-02-24", "2015-02-24", "2015-02-24", "2015-02-26", "2015-02-26", "2015-02-26", "2015-02-26", "2015-02-27", "2015-02-28", "2015-02-28", "2015-02-28", "2015-03-01", "2015-03-03", "2015-03-03", "2015-03-04", "2015-03-04", "2015-03-08", "2015-03-09", "2015-03-10", "2015-03-10", "2015-03-11", "2015-03-11", "2015-03-11", "2015-03-11", "2015-03-13", "2015-03-16", "2015-03-16", "2015-03-17", "2015-03-18", "2015-03-29", "2015-03-31", "2015-03-31", "2015-04-01", "2015-04-05", "2015-04-06", "2015-04-06", "2015-04-07", "2015-04-07", "2015-04-07", "2015-04-08", "2015-04-08", "2015-04-09", "2015-04-09", "2015-04-10", "2015-04-12", "2015-04-12", "2015-04-14", "2015-04-16", "2015-04-17", "2015-04-21", "2015-04-22", "2015-04-23", "2015-04-23", "2015-04-24", "2015-04-25", "2015-04-30", "2015-05-01", "2015-05-01", "2015-05-07", "2015-05-07", "2015-05-10", "2015-05-11", "2015-05-13", "2015-05-13", "2015-05-14", "2015-05-15", "2015-05-18", "2015-05-21", "2015-05-21", "2015-05-21", "2015-05-22", "2015-05-22", "2015-05-25", "2015-05-28", "2015-05-29", "2015-05-29", "2015-05-30", "2015-06-02", "2015-06-04", "2015-06-04", "2015-06-05", "2015-06-06", "2015-06-08", "2015-06-08", "2015-06-08", "2015-06-10", "2015-06-15", "2015-06-16", "2015-06-17", "2015-06-17", "2015-06-20", "2015-06-24", "2015-06-26", "2015-06-26", "2015-06-27", "2015-06-27", "2015-06-30", "2015-07-03", "2015-07-03", "2015-07-06", "2015-07-07", "2015-07-08", "2015-07-08", "2015-07-13", "2015-07-14", "2015-07-14", "2015-07-14", "2015-07-15", "2015-07-16", "2015-07-16", "2015-07-17", "2015-07-21", "2015-07-21", "2015-07-22", "2015-07-23", "2015-07-23", "2015-07-24", "2015-07-27", "2015-07-28", "2015-07-29", "2015-07-29", "2015-07-29", "2015-07-30", "2015-07-31", "2015-08-02", "2015-08-02", "2015-08-02", "2015-08-02", "2015-08-03", "2015-08-05", "2015-08-06", "2015-08-06", "2015-08-09", "2015-08-09", "2015-08-10", "2015-08-11", "2015-08-12", "2015-08-12", "2015-08-15", "2015-08-18", "2015-08-18", "2015-08-19", "2015-08-20", "2015-08-21", "2015-08-21", "2015-08-24", "2015-08-25", "2015-08-27", "2015-08-27", "2015-09-02", "2015-09-03", "2015-09-03", "2015-09-06", "2015-09-08", "2015-09-09", "2015-09-10", "2015-09-10", "2015-09-11", "2015-09-14", "2015-09-14", "2015-09-15", "2015-09-15", "2015-09-16", "2015-09-17", "2015-09-19", "2015-09-21", "2015-09-21", "2015-09-22", "2015-09-23", "2015-09-24", "2015-09-28", "2015-09-29", "2015-09-30", "2015-09-30", "2015-09-30", "2015-10-02", "2015-10-05", "2015-10-05", "2015-10-05", "2015-10-05", "2015-10-06", "2015-10-08", "2015-10-10", "2015-10-10", "2015-10-12", "2015-10-12", "2015-10-12", "2015-10-13", "2015-10-13", "2015-10-14", "2015-10-14", "2015-10-15", "2015-10-16", "2015-10-18", "2015-10-18", "2015-10-19", "2015-10-19", "2015-10-19", "2015-10-21", "2015-10-21", "2015-10-21", "2015-10-22", "2015-10-22", "2015-10-23", "2015-10-24", "2015-10-26", "2015-10-26", "2015-10-29", "2015-10-29", "2015-10-29", "2015-11-02", "2015-11-03", "2015-11-04", "2015-11-04", "2015-11-06", "2015-11-09", "2015-11-10", "2015-11-10", "2015-11-11", "2015-11-18", "2015-11-18", "2015-11-19", "2015-11-20", "2015-11-24", "2015-11-26", "2015-12-01", "2015-12-02", "2015-12-05", "2015-12-08", "2015-12-10", "2015-12-14", "2015-12-24", "2015-12-31", "2016-01-06", "2016-01-08", "2016-01-08", "2016-01-11", "2016-01-16", "2016-01-18", "2016-01-19", "2016-01-20", "2016-01-22", "2016-01-25", "2016-01-26", "2016-01-28", "2016-01-29", "2016-02-01", "2016-02-01", "2016-02-02", "2016-02-03", "2016-02-05", "2016-02-05", "2016-02-06", "2016-02-09", "2016-02-11", "2016-02-12", "2016-02-13", "2016-02-22", "2016-02-24", "2016-02-24", "2016-02-25", "2016-02-26", "2016-03-03", "2016-03-04", "2016-03-05", "2016-03-06", "2016-03-08", "2016-03-09", "2016-03-11", "2016-03-14", "2016-03-14", "2016-03-15", "2016-03-18", "2016-03-22", "2016-03-23", "2016-03-24", "2016-03-27", "2016-03-28", "2016-04-05", "2016-04-06", "2016-04-08", "2016-04-10", "2016-04-12", "2016-04-14", "2016-04-14", "2016-04-14", "2016-04-17", "2016-04-20", "2016-04-21", "2016-04-21", "2016-04-23", "2016-04-24", "2016-05-01", "2016-05-01", "2016-05-02", "2016-05-04", "2016-05-04", "2016-05-07", "2016-05-09", "2016-05-10", "2016-05-10", "2016-05-15", "2016-05-16", "2016-05-18", "2016-05-19", "2016-05-20", "2016-05-21", "2016-05-21", "2016-05-27", "2016-06-02", "2016-06-02", "2016-06-04", "2016-06-04", "2016-06-06", "2016-06-08", "2016-06-11", "2016-06-13", "2016-06-15", "2016-06-24", "2016-06-27", "2016-06-28", "2016-06-29", "2016-07-01", "2016-07-01", "2016-07-03", "2016-07-03", "2016-07-06", "2016-07-07", "2016-07-07", "2016-07-09", "2016-07-11", "2016-07-12", "2016-07-13", "2016-07-14", "2016-07-15", "2016-07-16", "2016-07-19", "2016-07-24", "2016-07-29", "2016-07-30", "2016-07-31", "2016-08-02", "2016-08-04", "2016-08-08", "2016-08-09", "2016-08-09", "2016-08-11", "2016-08-12", "2016-08-14", "2016-08-15", "2016-08-16", "2016-08-16", "2016-08-19", "2016-08-19", "2016-08-23", "2016-08-23", "2016-08-28", "2016-08-31", "2016-09-01", "2016-09-03", "2016-09-03", "2016-09-04", "2016-09-05", "2016-09-07", "2016-09-09", "2016-09-09", "2016-09-13", "2016-09-15", "2016-09-18", "2016-09-21", "2016-09-26", "2016-09-27", "2016-09-27", "2016-09-28", "2016-09-30", "2016-10-03", "2016-10-03", "2016-10-03", "2016-10-04", "2016-10-04", "2016-10-04", "2016-10-06", "2016-10-07", "2016-10-07", "2016-10-07", "2016-10-11", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-13", "2016-10-14", "2016-10-17", "2016-10-19", "2016-10-19", "2016-10-21", "2016-10-21", "2016-10-21", "2016-10-23", "2016-10-23", "2016-10-23", "2016-10-24", "2016-10-24", "2016-10-25", "2016-10-26", "2016-10-30", "2016-10-30", "2016-10-30", "2016-10-31", "2016-10-31", "2016-11-02", "2016-11-02", "2016-11-03", "2016-11-09", "2016-11-09", "2016-11-10", "2016-11-13", "2016-11-14", "2016-11-15", "2016-11-19", "2016-11-23", "2016-11-25", "2016-11-27", "2016-11-28", "2016-11-30", "2016-12-01", "2016-12-04", "2016-12-07", "2016-12-07", "2016-12-11", "2016-12-11", "2016-12-12", "2016-12-14", "2016-12-14", "2016-12-14", "2016-12-15", "2016-12-15", "2016-12-16", "2016-12-19", "2016-12-21", "2016-12-21", "2016-12-24", "2016-12-27", "2016-12-28", "2016-12-31", "2017-01-02", "2017-01-02", "2017-01-02", "2017-01-02", "2017-01-03", "2017-01-04", "2017-01-04", "2017-01-04", "2017-01-06", "2017-01-08", "2017-01-09", "2017-01-09", "2017-01-10", "2017-01-10", "2017-01-10", "2017-01-10", "2017-01-11", "2017-01-16", "2017-01-18", "2017-01-19", "2017-01-21", "2017-01-22", "2017-01-22", "2017-01-23", "2017-01-23", "2017-01-23", "2017-01-25", "2017-01-26", "2017-01-27", "2017-01-27", "2017-01-27", "2017-01-28", "2017-01-29", "2017-01-30", "2017-01-31", "2017-01-31", "2017-02-02", "2017-02-05", "2017-02-05", "2017-02-07", "2017-02-08", "2017-02-09", "2017-02-09", "2017-02-10", "2017-02-11", "2017-02-11", "2017-02-13", "2017-02-13", "2017-02-16", "2017-02-17", "2017-02-21", "2017-02-22", "2017-02-23", "2017-02-24", "2017-02-25", "2017-02-27", "2017-02-28", "2017-02-28", "2017-02-28", "2017-03-01", "2017-03-01", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-03", "2017-03-05", "2017-03-06", "2017-03-06", "2017-03-07", "2017-03-07", "2017-03-10", "2017-03-10", "2017-03-12", "2017-03-12", "2017-03-15", "2017-03-16", "2017-03-16", "2017-03-18", "2017-03-18", "2017-03-19", "2017-03-19", "2017-03-20", "2017-03-21", "2017-03-21", "2017-03-22", "2017-03-23", "2017-03-24", "2017-03-24", "2017-03-26", "2017-03-26", "2017-03-26", "2017-03-26", "2017-03-27", "2017-03-28", "2017-03-29", "2017-03-30", "2017-03-30", "2017-03-31", "2017-04-01", "2017-04-01", "2017-04-02", "2017-04-03", "2017-04-04", "2017-04-05", "2017-04-05", "2017-04-05", "2017-04-06", "2017-04-07", "2017-04-08", "2017-04-09", "2017-04-10", "2017-04-11", "2017-04-12", "2017-04-12", "2017-04-13", "2017-04-15", "2017-04-17", "2017-04-17", "2017-04-18", "2017-04-18", "2017-04-19", "2017-04-20", "2017-04-20", "2017-04-21", "2017-04-24", "2017-04-25", "2017-04-25", "2017-04-27", "2017-04-28", "2017-04-28", "2017-04-29", "2017-04-29", "2017-04-30", "2017-05-02", "2017-05-02", "2017-05-02", "2017-05-05", "2017-05-06", "2017-05-06", "2017-05-07", "2017-05-07", "2017-05-07", "2017-05-08", "2017-05-08", "2017-05-09", "2017-05-09", "2017-05-09", "2017-05-09", "2017-05-10", "2017-05-11", "2017-05-11", "2017-05-11", "2017-05-13", "2017-05-15", "2017-05-15", "2017-05-15", "2017-05-16", "2017-05-16", "2017-05-16", "2017-05-16", "2017-05-18", "2017-05-19", "2017-05-20", "2017-05-21", "2017-05-21", "2017-05-21", "2017-05-22", "2017-05-22", "2017-05-22", "2017-05-23", "2017-05-24", "2017-05-24", "2017-05-29", "2017-05-31", "2017-05-31", "2017-06-01", "2017-06-01", "2017-06-02", "2017-06-03", "2017-06-05", "2017-06-06", "2017-06-07", "2017-06-07", "2017-06-07", "2017-06-07", "2017-06-08", "2017-06-08", "2017-06-10", "2017-06-11", "2017-06-11", "2017-06-13", "2017-06-13", "2017-06-13", "2017-06-15", "2017-06-15", "2017-06-15", "2017-06-16", "2017-06-16", "2017-06-18", "2017-06-20", "2017-06-20", "2017-06-21", "2017-06-22", "2017-06-22", "2017-06-24", "2017-06-27", "2017-06-28", "2017-06-28", "2017-06-30", "2017-07-05", "2017-07-05", "2017-07-07", "2017-07-08", "2017-07-10", "2017-07-10", "2017-07-11", "2017-07-11", "2017-07-12", "2017-07-13", "2017-07-14", "2017-07-15", "2017-07-17", "2017-07-17", "2017-07-17", "2017-07-17", "2017-07-18", "2017-07-18", "2017-07-18", "2017-07-19", "2017-07-19", "2017-07-20", "2017-07-20", "2017-07-20", "2017-07-22", "2017-07-23", "2017-07-24", "2017-07-24", "2017-07-25", "2017-07-25", "2017-07-27", "2017-07-27", "2017-07-28", "2017-07-30", "2017-07-31", "2017-07-31", "2017-08-01", "2017-08-01", "2017-08-04", "2017-08-05", "2017-08-06", "2017-08-06", "2017-08-07", "2017-08-07", "2017-08-09", "2017-08-09", "2017-08-09", "2017-08-10", "2017-08-14", "2017-08-14", "2017-08-15", "2017-08-15", "2017-08-16", "2017-08-17", "2017-08-17", "2017-08-17", "2017-08-19", "2017-08-21", "2017-08-21", "2017-08-21", "2017-08-22", "2017-08-22", "2017-08-24", "2017-08-24", "2017-08-25", "2017-08-27", "2017-08-28", "2017-08-28", "2017-08-29", "2017-08-31", "2017-08-31", "2017-09-01", "2017-09-03", "2017-09-04", "2017-09-05", "2017-09-05", "2017-09-06", "2017-09-06", "2017-09-06", "2017-09-07", "2017-09-07", "2017-09-07", "2017-09-08", "2017-09-09", "2017-09-11", "2017-09-11", "2017-09-11", "2017-09-12", "2017-09-13", "2017-09-13", "2017-09-16", "2017-09-18", "2017-09-18", "2017-09-20", "2017-09-21", "2017-09-21", "2017-09-21", "2017-09-22", "2017-09-22", "2017-09-24", "2017-09-26", "2017-09-26", "2017-09-27", "2017-09-28", "2017-09-28", "2017-09-29", "2017-09-29", "2017-09-30", "2017-10-02", "2017-10-03", "2017-10-03", "2017-10-03", "2017-10-04", "2017-10-05", "2017-10-06", "2017-10-07", "2017-10-07", "2017-10-09", "2017-10-09", "2017-10-10", "2017-10-11", "2017-10-12", "2017-10-12", "2017-10-13", "2017-10-13", "2017-10-17", "2017-10-17", "2017-10-18", "2017-10-19", "2017-10-20", "2017-10-21", "2017-10-24", "2017-10-24", "2017-10-27", "2017-10-27", "2017-10-28", "2017-10-29", "2017-10-30", "2017-10-31", "2017-10-31", "2017-10-31", "2017-11-01", "2017-11-01", "2017-11-03", "2017-11-04", "2017-11-06", "2017-11-06", "2017-11-07", "2017-11-07", "2017-11-07", "2017-11-08", "2017-11-10", "2017-11-12", "2017-11-13", "2017-11-14", "2017-11-14", "2017-11-14", "2017-11-15", "2017-11-16", "2017-11-17", "2017-11-19", "2017-11-19", "2017-11-20", "2017-11-20", "2017-11-24", "2017-11-25", "2017-11-26", "2017-11-26", "2017-11-27", "2017-11-27", "2017-11-27", "2017-12-01", "2017-12-01", "2017-12-03", "2017-12-04", "2017-12-04", "2017-12-05", "2017-12-05", "2017-12-06", "2017-12-08", "2017-12-10", "2017-12-12", "2017-12-12", "2017-12-13", "2017-12-15", "2017-12-17", "2017-12-19", "2017-12-20", "2017-12-20", "2017-12-20", "2017-12-21", "2017-12-26", "2017-12-29", "2017-12-29", "2018-01-02", "2018-01-02", "2018-01-03", "2018-01-03", "2018-01-04", "2018-01-04", "2018-01-06", "2018-01-06", "2018-01-06", "2018-01-07", "2018-01-08", "2018-01-09", "2018-01-10", "2018-01-10", "2018-01-10", "2018-01-11", "2018-01-11", "2018-01-12", "2018-01-14", "2018-01-15", "2018-01-15", "2018-01-15", "2018-01-15", "2018-01-16", "2018-01-18", "2018-01-19", "2018-01-19", "2018-01-19", "2018-01-20", "2018-01-22", "2018-01-22", "2018-01-23", "2018-01-23", "2018-01-24", "2018-01-24", "2018-01-24", "2018-01-27", "2018-01-28", "2018-01-30", "2018-01-30", "2018-01-30", "2018-01-31", "2018-01-31", "2018-01-31", "2018-02-01", "2018-02-02", "2018-02-03", "2018-02-03", "2018-02-04", "2018-02-04", "2018-02-05", "2018-02-06", "2018-02-06", "2018-02-06", "2018-02-08", "2018-02-09", "2018-02-10", "2018-02-11", "2018-02-12", "2018-02-13", "2018-02-15", "2018-02-16", "2018-02-16", "2018-02-16", "2018-02-18", "2018-02-20", "2018-02-23", "2018-02-24", "2018-02-27", "2018-02-27", "2018-03-02", "2018-03-02", "2018-03-04", "2018-03-06", "2018-03-06", "2018-03-07", "2018-03-08", "2018-03-08", "2018-03-08", "2018-03-08", "2018-03-10", "2018-03-11", "2018-03-11", "2018-03-14", "2018-03-14", "2018-03-15", "2018-03-18", "2018-03-19", "2018-03-19", "2018-03-19", "2018-03-20", "2018-03-20", "2018-03-20", "2018-03-20", "2018-03-21", "2018-03-22", "2018-03-26", "2018-03-26", "2018-03-26", "2018-03-27", "2018-03-27", "2018-03-27", "2018-03-28", "2018-03-28", "2018-03-30", "2018-03-31", "2018-04-01", "2018-04-03", "2018-04-03", "2018-04-04", "2018-04-04", "2018-04-05", "2018-04-05", "2018-04-07", "2018-04-09", "2018-04-09", "2018-04-11", "2018-04-12", "2018-04-12", "2018-04-13", "2018-04-14", "2018-04-15", "2018-04-16", "2018-04-17", "2018-04-17", "2018-04-18", "2018-04-23", "2018-04-24", "2018-04-26", "2018-04-27", "2018-04-27", "2018-04-30", "2018-05-01", "2018-05-02", "2018-05-02", "2018-05-03", "2018-05-05", "2018-05-05", "2018-05-07", "2018-05-07", "2018-05-07", "2018-05-08", "2018-05-08", "2018-05-08", "2018-05-08", "2018-05-09", "2018-05-11", "2018-05-11", "2018-05-12", "2018-05-15", "2018-05-16", "2018-05-16", "2018-05-18", "2018-05-19", "2018-05-19", "2018-05-22", "2018-05-23", "2018-05-27", "2018-05-27", "2018-05-31", "2018-05-31", "2018-06-02", "2018-06-04", "2018-06-05", "2018-06-05", "2018-06-05", "2018-06-06"], "y": [0.15, 0.27, 0.375, 5.551115123125783e-17, 5.551115123125783e-17, 0.31174242424242427, 0.5, 0.1, 0.31, 0.010000000000000009, 0.04999999999999999, 0.6055555555555555, 0.0, -0.05, 0.55, 0.125, 0.8, 0.10119047619047619, 0.095, 0.37878787878787873, 0.45714285714285713, 0.3333333333333333, 0.125, -0.3201388888888889, 0.38106060606060604, 0.4916666666666667, 0.5, 0.5549999999999999, 0.16845238095238096, 0.003409090909090907, 0.15277777777777776, 0.315, 0.27864145658263306, 0.18194444444444446, -0.14583333333333331, 0.337396694214876, 0.8, 0.0, 0.25, 0.20416666666666666, -0.06666666666666667, 0.75, 0.5166666666666666, 0.6775, 0.0537037037037037, 0.050000000000000044, 0.017424242424242425, 0.3588383838383838, 0.4366666666666666, -0.14444444444444443, 0.16282828282828282, 0.10625000000000001, 0.25, 0.0, 0.2974747474747475, -0.10527777777777776, 0.2366161616161616, 0.12874999999999998, 0.15, 0.23500000000000001, 0.0, 0.18166666666666664, 0.32222222222222224, 0.12416666666666665, 0.175, 0.30666666666666664, 1.0, 0.5736666666666667, 0.0, 0.3333333333333333, 0.3197916666666666, 1.0, 0.09000000000000001, 0.16785714285714287, -0.18100000000000002, 0.8333333333333333, 0.317, 0.0, 0.41893939393939394, 0.0, 0.8, -0.05000000000000002, 0.4083333333333333, -0.08333333333333337, 0.3666666666666667, 0.0, 0.3666666666666667, 0.85, 0.43999999999999995, 0.26944444444444443, -0.031111111111111117, 0.25416666666666665, 0.35, 0.16545454545454544, 0.36875, 0.3953030303030303, 0.5787878787878787, 0.3666666666666667, 0.3666666666666667, 0.18250000000000002, 0.18888888888888888, 0.0, 0.34102564102564104, 0.8, 0.2, -0.06979166666666668, -0.1, -0.1101010101010101, 0.4033333333333333, 0.3903061224489796, 0.07261904761904761, 0.12, 0.6033333333333333, 0.5, 0.07708333333333331, 0.21388888888888888, 0.0, 0.2705654761904762, 0.25166666666666665, 0.6375, 0.1716111111111111, 0.31471861471861473, 0.3, -0.025, 0.1875, 0.1575, -0.125, 0.4666666666666666, 0.0, 0.1716666666666667, 0.2, -0.009595959595959616, -0.2916666666666667, 0.7, 0.05, 0.6166666666666667, 0.20833333333333334, -0.6, 0.10666666666666666, 0.2333333333333333, -0.010476190476190481, 0.8, 0.21200000000000002, 0.2333333333333333, 0.0, 0.3, 0.13636363636363635, 0.325, 0.049999999999999996, 0.3, 0.4, 0.6555555555555556, 0.5, 0.0, 0.037500000000000006, 0.525, 0.26780303030303027, 0.3638888888888889, 0.2, 0.43333333333333335, 0.2833333333333333, 0.45999999999999996, 0.32499999999999996, 0.17159090909090913, 0.0, 0.35000000000000003, 0.5, 0.7, 0.04545454545454549, 0.2, -0.18583333333333335, 0.255050505050505, 0.07500000000000002, 0.19004820936639116, 0.0, 0.5333333333333333, 0.33749999999999997, 0.4583333333333333, 0.0, 0.36020408163265305, 0.8, 0.22857142857142856, 0.20416666666666664, 0.7, -0.09013605442176871, 0.5, 0.1048611111111111, 0.5, 0.4, 0.25333333333333335, 0.5469576719576719, 0.40277777777777773, 0.3277777777777778, 0.013333333333333374, 0.06666666666666667, 0.14583333333333331, 0.8, 0.3499999999999999, 0.5, 0.0, 0.65, 0.19999999999999998, 0.6333333333333333, 0.3, 0.3229166666666667, 0.39444444444444443, 0.04545454545454545, 0.11574074074074074, 0.07546296296296297, -0.15555555555555559, 0.5, 0.3236111111111111, 0.4840909090909091, 0.46825396825396826, 0.8, 0.17916666666666667, 0.5481481481481482, 0.7, 0.12956349206349208, -0.4316666666666667, 0.8, 0.25, 0.18333333333333335, 0.26249999999999996, 0.7, -0.1, 0.65625, -1.0, 0.65, 0.24, 0.09256198347107437, 0.04999999999999997, 0.18636363636363634, 0.5125, 0.19166666666666668, 0.8, 0.2, 0.1, -0.1, 0.16818181818181818, 0.4633184523809524, 0.1582908163265306, 0.4518518518518519, 0.3875, 0.10937500000000001, 0.1125, 0.5, -0.17708333333333334, 0.3, 0.06233766233766231, 0.35, 0.22664141414141412, 0.79, 0.8, 0.7, 0.0, 0.49000000000000005, 0.35416666666666663, 0.3431818181818182, 0.1625, 0.003541666666666665, 0.1333333333333333, 0.5027777777777778, 0.2333333333333333, 0.25, 0.32666666666666666, 0.0, 0.33434343434343433, -0.2666666666666666, 0.2, 0.75, -0.02013888888888889, 0.2, 0.5799999999999998, 0.6666666666666666, -0.11093750000000001, 0.55, 0.08472222222222221, 0.1430871212121212, 0.31025, 0.2857142857142857, 0.15089285714285716, 0.255, 0.0, 0.5333333333333333, 0.1449107142857143, 0.13576278659611996, -0.08333333333333333, 0.2555555555555556, 0.4, 0.13979591836734695, 0.0, 0.0, 0.74375, 0.7, 0.17285714285714288, 0.0, 0.004166666666666652, 0.27999999999999997, 0.19660493827160494, 0.35, 0.04545454545454545, -0.09722222222222221, -0.075, 0.33592592592592596, -0.030555555555555548, 0.8, 0.3333333333333333, 0.0, 0.6000000000000001, 0.225, 0.2285714285714286, 0.3033333333333333, 0.59375, 0.4512962962962963, 0.15, 0.25, -0.13888888888888887, 0.44375, -0.030555555555555555, -0.1125, 1.0, 0.65, 0.00833333333333334, 0.15277777777777776, 0.06818181818181818, 0.21363636363636362, 0.7, 0.5, 0.5875, -0.20729166666666668, 0.0, -0.1875, 0.5, 0.10169285714285714, 0.0, 0.0, 0.12321428571428572, 0.19791666666666666, 0.17999999999999997, 0.25, 0.18088888888888885, 0.4583333333333333, -0.025, -0.0625, 0.5083333333333333, 0.39395833333333335, 0.0, 0.037500000000000006, 0.29222222222222227, 0.16666666666666666, 0.40727272727272723, 0.45666666666666667, 0.21555555555555553, 0.7, 0.26666666666666666, 0.10303030303030303, 0.13999999999999999, 0.1125, 0.07520833333333334, 0.4375, 0.14444444444444446, 0.33999999999999997, 0.36166666666666664, 0.5, 0.18333333333333335, -0.2, 0.5083333333333333, -0.025, 0.10555555555555556, 0.3181818181818182, -0.019166666666666686, 0.13482142857142856, -0.08333333333333333, 0.3, 0.3, 0.55, -0.39999999999999997, 0.12, 0.26670033670033677, 0.16, 0.26666666666666666, 0.0, 0.5555555555555555, 0.6366666666666666, 0.27526455026455027, 0.21640625, 0.5, 0.2, 0.4875, 0.7, 0.2916666666666667, 0.0, 0.0, 0.36666666666666664, 0.5388888888888889, 0.09047619047619047, 0.1, 0.4138888888888889, 0.5, 0.15909090909090906, 0.19999999999999998, 0.38, 0.2375, -0.03787878787878788, 0.8666666666666667, 0.19166666666666665, 0.3, 0.8, 0.23852813852813853, 0.4333333333333333, 0.24901960784313726, 0.422, 0.13636363636363635, 0.06519607843137254, 0.6999999999999998, 0.0, 0.4, 0.5666666666666668, 0.25, 0.37878787878787873, 0.40737179487179487, 0.29375, 0.525, 0.22083333333333333, 0.0, 0.3654545454545454, 0.35, 0.6428571428571427, 5.551115123125783e-17, 0.2161904761904762, 0.15, 0.5666666666666667, 0.43333333333333335, -0.1875, 0.16818181818181818, 0.23833333333333334, 0.35000000000000003, 0.19140102321920505, 0.23645833333333335, 0.6333333333333333, 0.2375, 0.5566666666666666, 0.0, 0.0, 0.22829861111111108, 0.31777777777777777, 0.5361111111111111, 0.07738095238095238, 0.12525510204081633, 0.32083333333333336, 0.27380952380952384, -0.06666666666666665, 0.3, 0.31666666666666665, 0.20238095238095236, 0.2916666666666667, 0.11233333333333335, 0.14666666666666667, 0.5, 0.37878787878787873, 0.35000000000000003, 0.45, 0.5, 0.51, 0.5681818181818181, 0.125, 0.3740740740740741, 0.3333333333333333, 5.551115123125783e-17, 0.2448979591836735, 0.611111111111111, -0.3125, 0.375, 0.125, 0.225, 0.5, 0.024999999999999994, 0.595, 0.3666666666666667, 0.461111111111111, 0.0, 0.43939393939393945, 0.8666666666666667, 0.49999999999999994, 0.0, 0.3, 0.4169642857142857, 0.2875, 0.2375, 0.7, 0.7666666666666666, 0.1528138528138528, 0.21818181818181817, 0.65, 0.7, 0.3764285714285714, 0.36240740740740734, 0.5, -0.20833333333333331, 0.3, 0.19999999999999998, 0.3771885521885522, 0.5, 0.0, 0.425, 0.062441249226963515, 0.24861111111111112, 0.15328282828282827, 0.22738095238095238, 0.8, -0.25, 0.11111111111111112, 0.05911111111111111, -0.15386904761904766, 0.0, 0.45999999999999996, 0.22499999999999998, 0.7, 0.7, 1.0, 0.16666666666666666, 0.20138888888888892, 0.43333333333333335, 0.24000000000000005, 0.31999999999999995, 0.30694444444444446, 0.32575757575757575, 0.22916666666666669, 0.20000000000000004, 0.3068181818181818, 0.6166666666666667, -0.16666666666666666, 0.25, 1.0, 0.23388888888888887, 0.44999999999999996, 0.25000000000000006, 0.1638888888888889, 0.4548611111111111, 0.1782312925170068, -0.16666666666666666, 0.15142857142857144, 0.0, 0.4666666666666666, 0.525, 0.7333333333333334, 0.35, -0.08680555555555557, -0.05, 0.10634920634920633, 0.31, -0.3499999999999999, 0.18, 0.5, 0.31666666666666665, 0.18958333333333333, 0.6, 0.5571428571428572, 0.07366666666666669, 0.10784313725490195, 0.21666666666666667, 0.75, 0.4, 0.2, 0.4666666666666667, 0.7, 0.0, 0.009848484848484844, 0.0, 0.5, 0.13636363636363635, 0.2, 0.4, 0.15, 0.5666666666666667, 0.28555555555555556, -0.07434573002754821, 0.65, 0.08750000000000001, 0.65, 0.75, 0.10727272727272727, 0.0, -0.15125, 1.0, 0.475, -0.18981060606060607, 0.3666666666666667, 0.58, 0.0, 0.012373737373737391, 0.475, 0.3, 0.11250000000000002, 0.24333333333333332, 0.05, 0.6187499999999999, 0.25, 0.0, 0.11630036630036632, 0.2782828282828283, 0.40625, -0.14499999999999996, 0.26, 0.36944444444444446, 0.5437500000000001, 0.3, 0.425, 0.4166666666666667, 0.27777777777777773, -0.125, 0.14994047619047618, 0.10625000000000004, 0.375, 0.0, 0.1, 0.6333333333333333, 0.2928571428571428, 0.22428571428571428, 0.0, 0.575, 0.45606060606060606, 0.0, 0.5, 0.35, 0.8, 0.49000000000000005, 0.5933333333333334, 0.5, 0.87, 0.38125, 0.044444444444444446, 0.15285714285714286, 0.0, 0.0, 0.5333333333333333, 0.17500000000000002, 0.4125, -0.8666666666666667, 0.5875, 0.5125000000000001, 1.0, 0.8620000000000001, -0.2916666666666667, 0.283994708994709, 0.29805194805194807, 0.2770833333333333, 0.8, 0.20333333333333334, 0.32916666666666666, 0.34, 0.44772727272727275, 0.35000000000000003, -0.3, 0.7, 0.375, 0.1875, -0.5499999999999999, 0.6499999999999999, 0.13333333333333333, 0.45, 0.513888888888889, 0.575, 0.35, 0.0, 0.2, 0.0, 0.75, 0.1744155844155844, 0.4440476190476191, 0.10833333333333334, 0.13333333333333333, 0.5, 0.24598214285714284, 0.21111111111111114, 0.75, 0.21111111111111114, 0.21111111111111114, 0.44375, 0.03641456582633052, 0.6, 0.2333333333333333, 0.0, 0.44800000000000006, 0.625, 0.2, 0.19708333333333333, 0.1, 0.13166666666666668, 0.41818181818181815, 0.3297619047619048, 0.16818181818181818, 0.11142857142857146, 0.34067460317460313, 0.21705808080808087, 0.5333333333333333, 0.0, 0.3405952380952381, 0.27703168044077137, 0.9, 0.6154761904761905, 0.5, 0.25, 0.6875, 0.32625000000000004, 0.19583333333333333, 0.5778409090909091, 0.8, 0.0, 0.5, 0.19791666666666669, 0.26805194805194804, 0.20000000000000004, 0.15833333333333333, 0.506, 0.48125000000000007, 0.5625, -0.15833333333333333, 0.175, 0.34005602240896354, 0.059166666666666666, 0.7000000000000001, 0.4916666666666667, 0.0, 0.0, 0.3125, 0.13272727272727272, 0.7, 0.43333333333333335, 0.3, 0.3666666666666667, 0.37878787878787873, 0.65, 0.38125, 0.40937500000000004, 0.20833333333333334, 0.85, -0.1572916666666667, 0.13888888888888887, 0.15833333333333333, 0.6599999999999999, 0.7083333333333333, 0.8, 0.75, 0.4750000000000001, 0.22857142857142856, 0.26233766233766237, 0.0, 0.3, 0.01848659003831418, 0.24747474747474754, 0.1492212036329683, 0.39999999999999997, 0.2, 0.2308333333333333, 0.27499999999999997, 0.1285714285714286, -0.01517857142857143, 0.35250000000000004, 0.65, 0.09642857142857142, 0.15740740740740738, 1.0, 0.2816666666666666, 0.19999999999999998, 0.6, 0.4828571428571428, 0.5777777777777778, 0.16666666666666666, 0.45, 0.0, 0.18333333333333335, 0.2674918831168831, 0.19682539682539682, 0.31666666666666665, 0.0, 0.13657407407407407, 0.21496212121212122, 0.16833333333333333, 0.12569444444444441, 0.06212121212121211, 0.1409090909090909, 0.17407407407407408, 0.675, -0.03593750000000001, 0.03333333333333334, 0.3013888888888889, 0.5, 0.05925925925925926, 0.22727272727272727, 0.15166666666666667, 0.7, 0.5875, -0.25, 0.10972222222222221, 0.6, 0.41565656565656567, 0.4484848484848485, 0.11481481481481481, -0.007575757575757579, -0.16666666666666666, 0.26104166666666667, 0.4333333333333333, 0.325, 0.09000000000000002, 0.1634920634920635, 0.05875000000000001, 0.0975, 0.2520833333333333, 0.275, 0.04166666666666667, 0.1, 0.6666666666666666, 0.36428571428571427, -0.16666666666666666, 0.0, 0.7000000000000001, -0.051851851851851864, 0.06666666666666667, 0.25062500000000004, 0.7866666666666667, 0.275, 0.40914285714285714, 0.3495555555555555, 0.0, 0.10000000000000002, 0.016666666666666646, 0.21481481481481485, 0.7, 0.3125, 0.38, 0.20030864197530865, -0.1625, 0.3, 0.18787878787878787, 0.28500000000000003, 0.4681818181818182, 0.2, 0.08194444444444447, 0.08194444444444447, 0.0, 0.41000000000000003, 0.20500000000000002, 0.2333333333333333, 0.584375, 0.15833333333333335, 0.4440476190476191, 0.3840909090909091, 0.16999999999999998, 0.8833333333333333, 0.7, 0.125, 0.20216450216450216, 0.34814814814814815, 0.26392045454545454, 0.04749999999999996, -0.05357142857142857, 0.19333333333333336, 0.35, 0.12865190365190365, -0.07395833333333335, 0.2833333333333334, 0.6833333333333332, 0.09999999999999999, -0.04716666666666667, 0.340625, 0.5, 1.0, 0.375, 0.2, 0.2858225108225108, 0.26196969696969696, -0.019999999999999997, 0.08148148148148147, 0.39, -0.23095238095238096, 0.17576388888888891, 0.4107954545454546, 0.2619047619047619, 0.24954545454545451, 0.3541666666666667, 0.23333333333333334, 0.625, 0.3666666666666667, 0.5, 0.5, 0.2855555555555556, 0.125, 0.252, 0.025852272727272724, 0.4778138528138528, 0.4166666666666667, -0.036111111111111115, 0.4000000000000001, 0.15555555555555556, 0.4166666666666667, 0.275, 0.14285714285714285, -0.07083333333333335, 0.11547619047619047, 0.10904356060606062, 0.41, -0.0625, 0.15666666666666668, 0.4800000000000001, -0.06666666666666667, 0.16666666666666666, 0.7, 0.2351851851851852, 0.575, -0.1, 0.1, -0.02, 0.45128205128205134, 0.35357142857142854, 0.25, 0.75, 0.6888888888888888, 0.8, 0.09999999999999999, 0.6166666666666667, 0.0, -0.5633333333333334, 0.48500000000000004, 0.65, 0.33799999999999997, 0.09214285714285715, 0.054166666666666675, 0.625, 0.2, 0.01818181818181821, 0.6, 0.05, 0.4333333333333333, 0.0, 0.04583333333333333, 0.5771428571428572, 0.1861111111111111, 0.78, 0.06944444444444443, 0.25, 0.7533333333333333, 0.2222222222222222, 0.575, 0.18738344988344988, 0.3583333333333334, 0.33999999999999997, 0.378, 0.39999999999999997, 0.21666666666666667, 0.31416666666666665, -0.041666666666666664, 0.1, 0.07857142857142857, -0.058493589743589744, 0.65, 0.22000000000000003, 0.25, 0.0, 0.42727272727272725, 0.3361111111111111, 0.2977272727272727, 0.5, 0.6590909090909091, 0.03142857142857147, 0.14444444444444446, 0.38, -0.375, 0.0, -1.0, 0.3333333333333333, 0.11111111111111112, 0.0, 0.37625, 0.6174999999999999, 0.19166666666666665, 0.2, -0.13333333333333333, 0.4, 0.7, 0.14938271604938272, 0.4139204545454545, 0.28354978354978355, 0.635, 0.5, 0.5900000000000001, 0.35589225589225587, 0.37878787878787873, 0.0, -0.133, -0.4, 0.4872727272727272, 0.3125, 0.3233766233766234, 0.5125000000000001, 0.4666666666666666, 0.5285714285714286, 0.10714285714285714, 0.6666666666666666, 0.4454545454545455, 0.09999999999999999, 0.25, 0.2415246212121212, 0.4083333333333334, 0.20416666666666664, 0.22900000000000004, 0.31212121212121213, 0.22916666666666666, -0.06746031746031746, 0.2, 0.325, 0.3, 0.525, 0.52, 0.0, 0.6666666666666666, 0.18, 0.48166666666666663, 0.4666666666666666, 0.10833333333333334, 0.18704545454545454, 0.21041666666666667, 0.15999999999999998, 0.6000000000000001, 0.39999999999999997, 0.8019999999999999, 0.38927272727272727, 0.17867965367965366, 0.18958333333333333, 0.2726190476190476, 0.3333333333333333, -0.26666666666666666, 0.17604166666666668, 0.5666666666666667, 0.7, 0.3475555555555555, 0.1278409090909091, 0.25, -0.03333333333333334, 0.2777777777777778, -0.0036616161616161644, 0.45, -0.008249158249158256, 0.10000000000000002, 0.7, 0.3125, 0.0, 0.1361111111111111, 0.4000000000000001, 0.4666666666666666, 0.48031250000000003, -0.006249999999999999, 0.5071428571428571, 0.20192307692307693, -0.2418518518518518, 0.505, 0.56875, 0.5197619047619048, 0.11904761904761907, 0.5068181818181818, 0.6444444444444445, 0.3666666666666667, 0.3773809523809524, -0.49583333333333335, 0.4431818181818182, 0.46567460317460313, 0.05833333333333337, -0.09999999999999998, 0.22083333333333333, 0.5, 0.7, 0.21464285714285714, 0.2625, 0.20833333333333334, 0.42424242424242414, -0.09375, 0.0920995670995671, 0.55, 0.41999999999999993, 0.01558080808080808, 0.2961904761904762, 0.21666666666666667, 0.25497835497835497, 0.445, 0.2995535714285714, 0.0625, 0.0, 0.06214285714285715, 0.7, 0.3, 0.8000000000000002, -0.021428571428571415, 0.68, -0.04972222222222223, -0.051767676767676775, 0.0, 0.0, 0.7166666666666667, 0.08541666666666665, 0.09126984126984126, 0.22777777777777775, -0.24166666666666667, 0.5, 0.37222222222222223, 0.26964285714285713, 0.03333333333333333, 0.4928571428571428, 0.0991025641025641, 0.14444444444444446, 0.37500000000000006, 0.5275, 0.1, 0.10166666666666666, 0.26666666666666666, 0.04375, 0.3523809523809524, 0.0, 0.8, -0.3333333333333333, 0.44000000000000006, 0.5333333333333333, 0.33285714285714285, -0.09722222222222222, 0.528888888888889, 0.2638095238095238, 0.26666666666666666, 0.2916666666666667, 0.0625, 0.3499999999999999, 0.21041666666666667, 0.45, 0.35, 0.45999999999999996, 0.4604166666666667, 0.0, 0.10277777777777779, 0.45, 0.30277777777777776, 0.046001221001221, 0.03194444444444444, -0.08194444444444442, 0.1375, 0.18404761904761904, 0.45, -0.00909090909090907, 0.3666666666666667, 0.42666666666666675, 0.37, 0.27399999999999997, -0.25555555555555554, -0.08333333333333333, 0.4625, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.3829166666666667, 0.34375, 0.20502645502645503, -0.171875, -0.09999999999999998, 0.32499999999999996, 0.0, 0.012499999999999983, 0.0175, 0.4093333333333334, 0.036111111111111115, 0.16666666666666666, 0.39749999999999996, 0.32, 0.42857142857142866, 0.22, 0.825, -0.12380952380952381, 0.3861111111111111, 0.2811111111111111, 0.3, 0.5316666666666667, 0.41250000000000003, 0.9, 0.04416666666666667, 0.44375000000000003, 0.2, 0.29, 0.1, 0.15142045454545455, 0.26805555555555555, 0.16, 0.5336666666666667, 0.16699999999999998, 0.46630952380952373, 0.5833333333333334, 0.0, 0.05352564102564103, 0.0, 0.3375, 0.16181703397612493, 0.7250000000000001, 0.0062500000000000056, 0.22184343434343434, -0.0429421768707483, -0.15, 0.16, 0.85, 0.5, 0.37777777777777777, 0.4, 0.0, 0.5166666666666667, 0.35, 0.16999999999999998, 0.2270833333333333, 0.38125, 0.19333333333333333, 0.19787878787878788, 0.16642857142857143, 0.25, 0.11481481481481481, 0.5416666666666666, 0.55, 0.19179063360881543, 0.0, 0.19583333333333333, 0.32321428571428573, -0.21562499999999996, 0.292, -0.2916666666666667, 0.15, 0.4428571428571429, 0.2696428571428572, 0.22095238095238098, 0.75, 0.36944444444444446, 0.35, 0.0, 0.08981481481481482, 0.45555555555555555, 0.38888888888888884, -0.16666666666666666, 0.44333333333333336, 0.3139880952380953, 0.24208333333333332, 0.13125, 0.1888571428571429, 0.45, 0.4666666666666666, 0.1, 0.7033333333333333, 0.04545454545454545, 0.7, 0.42625, 0.15555555555555559, -0.1, 0.13166666666666665, 0.09166666666666663, 0.2446428571428571, 0.16666666666666666, 0.6214285714285713, 0.35, 0.4976190476190476, -0.18888888888888888, 0.05833333333333331, 0.471, 0.17341269841269843, 0.31, 0.15104166666666666, -0.041666666666666664, 0.35357142857142854, 0.275, 0.65, 0.32, 0.2, 0.35555555555555557, 0.53625, 0.36904761904761907, 0.12987012987012989, 0.14, 0.1983333333333333, 0.275, -0.08833333333333333, 0.5, 0.18166666666666664, -0.16666666666666666, 0.18414502164502167, 0.475, 0.1977777777777778, 0.21833333333333335, 0.37878787878787873, 0.4, 0.06666666666666667, 0.25, 0.18459207459207458, 0.3, 0.16666666666666666, 0.2777777777777778, 0.05666666666666666, 0.5, 0.2, -0.09722222222222222, 0.14382716049382716, 0.47124999999999995, 0.06666666666666665, 0.5, -0.041666666666666664, 0.29999999999999993, 0.00208333333333334, -0.56875, 0.5485714285714286, 0.38333333333333336, 0.21270833333333333, 0.2416666666666667, 0.8333333333333334, 0.39999999999999997, -0.12333333333333334, 0.5349999999999999, 0.4, 0.82, 0.45681818181818185, 0.33333333333333337, 0.24708333333333332, 0.36515151515151517, 0.15833333333333333, 0.6318181818181817, 0.06666666666666667, 0.05833333333333335, 0.15, -0.195, 0.021666666666666657, 0.5, 0.45, 0.8, 0.04722222222222223, 0.253125, 0.30000000000000004, 0.32, 0.403125, 0.06296296296296297, 0.4, 0.03125, 0.7000000000000001, 0.6, 0.6799999999999999, 0.0, 0.1583333333333333, 0.3333333333333333, 0.25416666666666665, 0.3375, 0.29047619047619044, 0.37666666666666665, 0.375, 0.5927083333333334, 0.7, 0.06221590909090907, 0.1361111111111111, 0.6, 0.35, 0.3387878787878788, 0.22749999999999998, 0.1875, -0.009523809523809521, 0.3976190476190477, 0.36, 0.3557144522144522, 0.5875, 0.35714285714285715, -0.025, 0.06888888888888889, 0.4523809523809524, 0.12000000000000002, 0.258228354978355, 0.3, 0.25, 0.0, 0.30178571428571427, 0.04567099567099566, -0.16666666666666666, 0.47500000000000003, 0.4941666666666667, 0.09999999999999999, 0.43333333333333335, 0.041666666666666664, 0.4457575757575757, 0.5044444444444445, 0.1688888888888889, 0.15166666666666667, 0.075, 0.625, 0.06578282828282829, 0.4041666666666667, 0.41818181818181815, 0.38608058608058615, 0.39, 0.10833333333333334, 0.35, 0.5499999999999999, 0.04285714285714287, 0.25, 0.0, 0.12878787878787878, 0.36999999999999994, 0.6333333333333333, 0.08124999999999999, 0.29666666666666663, 0.25, -0.5728395061728396, 0.23095238095238096, 0.2571428571428572, 0.42424242424242425, 0.16666666666666666, 0.34259259259259256, 0.2520833333333333, 0.6, 0.0, 0.32, 0.3590909090909091, 0.19545454545454544, -0.07861952861952863, 0.42000000000000004, 0.2111111111111111, 0.5700000000000001, 0.8, 0.19393939393939394, 0.3888888888888889, -0.2638888888888889, 0.0, 0.25, 0.0, 0.3, 0.10416666666666666, 0.0, 0.27037037037037037, 0.15138888888888888, 0.18680555555555556, 0.21666666666666667, -0.3319444444444445, 0.4, 0.18666666666666668, -0.1575, -0.08333333333333333, 0.06428571428571428, 0.55, 0.0, 0.19166666666666665, 0.2111111111111111, 0.15433333333333335, 0.0, 0.7166666666666668, 0.5833333333333334, 0.11704545454545454, 0.5900000000000001, 0.42541666666666667, 0.13999999999999999, 0.3666666666666667, -0.1, 0.0, -1.0, 0.24621212121212116, 0.5666666666666668, 0.20727272727272728, 0.35000000000000003, 0.10494791666666667, 0.3333333333333333, 0.0, 0.004166666666666665, 0.3125, 0.2708333333333333, 0.13541666666666666, -0.06666666666666667, 0.5839285714285714, 0.08571428571428572, 0.22395833333333331, 0.32, 0.16785714285714287, 0.33999999999999997, 0.06666666666666667, -0.1078125, 0.35, 0.42000000000000004, 0.1805427288760622, 0.6555555555555556, 0.10714285714285712, 0.10000000000000002, 0.47380952380952385, 0.4083333333333334, 0.4, 0.29999999999999993, 0.17083333333333334, -0.14999999999999997, 0.15833333333333335, 0.25, 0.41904761904761906, 0.26785714285714285, 0.33809523809523806, 0.14, -0.0875, -0.2722222222222222, 0.6666666666666666, 0.25, 0.35, 0.3775198412698413, 0.14583333333333334, -0.03787878787878787, 0.15333333333333335, 0.24047619047619048, 0.275, 0.7333333333333334, 0.16666666666666666, 0.0, 0.3, 0.48750000000000004, 0.425, 0.030000000000000006, 0.012738095238095225, 0.13656299840510366, 0.15333333333333335, -0.10621279761904763, 0.4014814814814815, 0.2977777777777778, 0.03333333333333333, 0.075, 0.54, 0.5202380952380952, 0.39, 0.85, 0.33809523809523806, 0.5874999999999999, 0.4642857142857143, 0.14166666666666666, -0.028246753246753253, 0.08, 0.20833333333333334, 0.325, 0.235375, 0.23010204081632654, -0.11249999999999998, 0.32142857142857145, 0.3, 0.6166666666666667, 0.27444444444444444, 0.21555555555555558, 0.15833333333333335, -0.13261904761904764, 0.1472222222222222, -0.09629629629629628, 0.625, 0.175, 0.08125, 0.425, -0.004999999999999999, 0.3208333333333333, 0.5, 0.007272727272727275, -0.016666666666666666, 0.4428571428571429, -0.185, 0.392, -0.03261904761904761, 0.3242424242424242, 0.12476190476190475, -0.14, 0.04083333333333333, 0.12510822510822514, 0.5, 0.0, 0.5027777777777778, -0.15555555555555559, 0.09583333333333333, 0.1716666666666667, 0.352, 0.1333333333333333, 0.15000000000000002, 0.18666666666666668, 0.17777777777777778, 0.20000000000000004, 0.16249999999999998, 0.55, 0.2739393939393939, -0.056666666666666664, 0.475, 0.055714285714285716, 0.4405594405594406, 0.19814814814814816, 0.30563492063492065, 0.31079545454545454, 0.6095238095238095, -0.032703081232493, -0.5583333333333333, 0.6000000000000001, 0.26666666666666666, -0.03181818181818183, 0.65, 0.39666666666666667, 0.26458333333333334, 0.27166666666666667, -0.16666666666666666, 0.5666666666666668, 0.5333333333333333, -0.0375, -0.23750000000000004, 0.07619047619047618, 0.195, 0.16666666666666666, -0.08333333333333333, 0.01388888888888893, 0.3409090909090909, 0.36666666666666664, 0.3515625, 0.0, 0.2384615384615385, 0.6, 0.43500000000000005, 0.48809523809523814, 0.3, 0.036111111111111115, 0.07083333333333332, 0.75, 0.3833333333333333, 0.34687500000000004, 0.24015151515151517, 0.26607142857142857, 0.205, 0.33999999999999997, 0.5666666666666667, 0.04892857142857143, 0.10976190476190473, 0.23578431372549016, 0.2375, 0.23000000000000004, 0.0, -0.2, 0.08106060606060606, -0.0638888888888889, 0.06628787878787878, -0.1, 0.545, -0.24166666666666664, 0.21714285714285717, 0.14166666666666664, 0.09638888888888887, 0.78, 0.00416666666666668, 0.8000000000000002, -0.2, -0.5666666666666665, 0.25, 0.20416666666666664, -0.14583333333333331, 0.21333333333333332, -0.012499999999999997, 0.0, 0.18833333333333332, 0.4590909090909091, 0.16071428571428573, 0.26666666666666666, 0.575, 0.2696969696969697, -0.35, 0.20909090909090908, -0.049999999999999996, 0.0, 0.625, 0.07411616161616161, 0.018560606060606055, 0.36666666666666664, -0.26833333333333337, 0.0, 0.425, 0.04545454545454545, -0.36428571428571427, -0.15833333333333333, 0.4544155844155844, 0.29333333333333333, -0.4597222222222222, 0.04999999999999999, 0.025000000000000005, 0.13824675324675323, 0.13636363636363635, 0.3857142857142857, 0.7, 0.5333333333333333, 0.18, 0.25, 0.2771717171717172, 0.315, 0.11666666666666668, 0.39999999999999997, 0.54375, -0.3499999999999999, 0.16555555555555557, 0.0, 0.08989898989898988, 0.8, -0.06818181818181818, -0.04791666666666666, 0.2333333333333333, 0.0, 0.13333333333333333, -0.1, 0.4666666666666666, 0.5, 0.4333333333333333, 0.762, 0.1593039772727273, 0.15000000000000002, -0.5, 0.6333333333333333, 0.09037698412698413, 0.7249999999999999, 0.55, 0.13999999999999999, -0.1, 0.0, 0.6916666666666668, 0.04421487603305786, 0.34123737373737373, 0.2287878787878788, -0.05, -0.21900000000000003, 0.008333333333333331, 0.036, 0.6, 0.2333333333333333, 0.5909090909090908, 0.2, -0.044126984126984126, 0.3, 0.07208333333333333, 0.02666666666666667, 0.3180952380952382, 0.34, 0.22499999999999998, 0.6333333333333334, 0.2, 0.2375, 0.15699999999999997, 0.5, 0.09722222222222222, 0.6468750000000001, 0.355, 0.33409090909090905, -0.041666666666666664, 0.0, 0.12000000000000002, 0.165, 0.5333333333333333, 0.16904761904761903, 0.2416666666666666, 0.4375, 0.21428571428571427, 0.1625, 0.06125, 0.12142857142857143, -0.024642857142857143, 0.1333333333333333, -0.3666666666666667, -0.05333333333333333, 0.38, 0.41875, 0.16666666666666666, 0.2772727272727272, -0.08541666666666665, 0.4333333333333333, 0.15000000000000002, 0.041666666666666664, 0.2837662337662338, -0.38999999999999996, 0.2657142857142857, 0.0, 0.25, 0.8, 0.2225, 0.0625, 0.2857142857142857, 0.07500000000000001, 0.36875, 0.39888888888888885, 0.40744949494949495, 0.3833333333333333, 0.8000000000000002, 0.2488282828282828, 0.7, 0.05833333333333332, 0.18181818181818182], "name": "polarity", "text": "", "line": {"color": "rgba(255, 153, 51, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}, {"type": "scatter", "x": ["2012-01-30", "2012-02-02", "2012-02-09", "2012-02-24", "2012-02-24", "2012-02-28", "2012-02-29", "2012-03-01", "2012-03-06", "2012-03-06", "2012-03-07", "2012-03-10", "2012-03-16", "2012-03-17", "2012-03-21", "2012-03-23", "2012-03-23", "2012-03-26", "2012-03-26", "2012-03-27", "2012-03-27", "2012-03-27", "2012-03-28", "2012-03-30", "2012-04-02", "2012-04-10", "2012-04-11", "2012-04-12", "2012-04-17", "2012-04-25", "2012-04-25", "2012-04-27", "2012-04-27", "2012-04-30", "2012-04-30", "2012-05-01", "2012-05-03", "2012-05-04", "2012-05-06", "2012-05-08", "2012-05-08", "2012-05-08", "2012-05-09", "2012-05-09", "2012-05-09", "2012-05-10", "2012-05-15", "2012-05-22", "2012-05-22", "2012-05-23", "2012-05-24", "2012-06-04", "2012-06-06", "2012-06-10", "2012-06-13", "2012-06-19", "2012-06-21", "2012-06-22", "2012-06-25", "2012-06-26", "2012-06-28", "2012-07-01", "2012-07-01", "2012-07-02", "2012-07-06", "2012-07-09", "2012-07-11", "2012-07-12", "2012-07-12", "2012-07-14", "2012-07-15", "2012-07-17", "2012-07-17", "2012-07-18", "2012-07-22", "2012-07-24", "2012-07-24", "2012-07-25", "2012-07-27", "2012-07-27", "2012-08-02", "2012-08-02", "2012-08-02", "2012-08-03", "2012-08-06", "2012-08-07", "2012-08-10", "2012-08-13", "2012-08-14", "2012-08-16", "2012-08-17", "2012-08-19", "2012-08-20", "2012-08-21", "2012-08-21", "2012-08-22", "2012-08-24", "2012-08-27", "2012-09-04", "2012-09-05", "2012-09-10", "2012-09-11", "2012-09-15", "2012-09-17", "2012-09-17", "2012-09-17", "2012-09-18", "2012-09-20", "2012-09-23", "2012-09-26", "2012-09-26", "2012-09-27", "2012-09-28", "2012-10-01", "2012-10-02", "2012-10-03", "2012-10-03", "2012-10-08", "2012-10-09", "2012-10-09", "2012-10-13", "2012-10-13", "2012-10-14", "2012-10-14", "2012-10-15", "2012-10-17", "2012-10-17", "2012-10-20", "2012-10-21", "2012-10-22", "2012-10-23", "2012-10-23", "2012-10-28", "2012-10-29", "2012-10-29", "2012-10-30", "2012-10-30", "2012-10-30", "2012-10-30", "2012-10-31", "2012-11-07", "2012-11-07", "2012-11-08", "2012-11-08", "2012-11-10", "2012-11-13", "2012-11-14", "2012-11-16", "2012-11-16", "2012-11-18", "2012-11-24", "2012-11-26", "2012-11-29", "2012-12-03", "2012-12-03", "2012-12-06", "2012-12-08", "2012-12-11", "2012-12-12", "2012-12-12", "2012-12-16", "2012-12-17", "2012-12-21", "2012-12-26", "2012-12-30", "2012-12-30", "2013-01-04", "2013-01-05", "2013-01-07", "2013-01-08", "2013-01-15", "2013-01-15", "2013-01-16", "2013-01-17", "2013-01-17", "2013-01-18", "2013-01-20", "2013-01-22", "2013-01-22", "2013-01-25", "2013-01-27", "2013-01-27", "2013-01-27", "2013-01-29", "2013-01-30", "2013-02-01", "2013-02-01", "2013-02-01", "2013-02-03", "2013-02-04", "2013-02-05", "2013-02-05", "2013-02-06", "2013-02-06", "2013-02-06", "2013-02-07", "2013-02-12", "2013-02-12", "2013-02-15", "2013-02-15", "2013-02-15", "2013-02-21", "2013-02-22", "2013-02-23", "2013-02-25", "2013-02-25", "2013-02-26", "2013-02-27", "2013-02-28", "2013-03-02", "2013-03-02", "2013-03-04", "2013-03-04", "2013-03-05", "2013-03-05", "2013-03-06", "2013-03-10", "2013-03-11", "2013-03-11", "2013-03-14", "2013-03-19", "2013-03-19", "2013-03-20", "2013-03-20", "2013-03-25", "2013-03-25", "2013-03-25", "2013-03-27", "2013-03-27", "2013-03-29", "2013-04-02", "2013-04-02", "2013-04-05", "2013-04-05", "2013-04-05", "2013-04-09", "2013-04-09", "2013-04-10", "2013-04-11", "2013-04-11", "2013-04-12", "2013-04-12", "2013-04-13", "2013-04-14", "2013-04-17", "2013-04-18", "2013-04-18", "2013-04-21", "2013-04-22", "2013-04-23", "2013-04-23", "2013-04-23", "2013-04-24", "2013-04-25", "2013-04-26", "2013-04-29", "2013-04-29", "2013-04-29", "2013-04-30", "2013-05-01", "2013-05-09", "2013-05-09", "2013-05-09", "2013-05-09", "2013-05-13", "2013-05-16", "2013-05-19", "2013-05-22", "2013-05-28", "2013-05-29", "2013-05-29", "2013-06-01", "2013-06-03", "2013-06-04", "2013-06-04", "2013-06-07", "2013-06-08", "2013-06-08", "2013-06-10", "2013-06-11", "2013-06-15", "2013-06-17", "2013-06-18", "2013-06-22", "2013-06-23", "2013-06-24", "2013-06-25", "2013-06-26", "2013-06-26", "2013-06-26", "2013-06-28", "2013-06-29", "2013-07-01", "2013-07-05", "2013-07-06", "2013-07-08", "2013-07-08", "2013-07-10", "2013-07-12", "2013-07-12", "2013-07-14", "2013-07-15", "2013-07-15", "2013-07-16", "2013-07-17", "2013-07-17", "2013-07-18", "2013-07-19", "2013-07-19", "2013-07-22", "2013-07-23", "2013-07-24", "2013-07-25", "2013-07-27", "2013-07-28", "2013-07-29", "2013-07-29", "2013-07-30", "2013-08-03", "2013-08-03", "2013-08-06", "2013-08-06", "2013-08-07", "2013-08-07", "2013-08-08", "2013-08-09", "2013-08-10", "2013-08-13", "2013-08-15", "2013-08-16", "2013-08-16", "2013-08-16", "2013-08-20", "2013-08-20", "2013-08-21", "2013-08-26", "2013-08-27", "2013-08-27", "2013-08-28", "2013-08-28", "2013-08-29", "2013-08-30", "2013-08-30", "2013-09-01", "2013-09-02", "2013-09-02", "2013-09-03", "2013-09-03", "2013-09-03", "2013-09-03", "2013-09-06", "2013-09-06", "2013-09-06", "2013-09-07", "2013-09-09", "2013-09-09", "2013-09-10", "2013-09-10", "2013-09-11", "2013-09-11", "2013-09-13", "2013-09-14", "2013-09-18", "2013-09-18", "2013-09-19", "2013-09-20", "2013-09-23", "2013-09-23", "2013-09-24", "2013-09-27", "2013-09-28", "2013-10-01", "2013-10-01", "2013-10-02", "2013-10-03", "2013-10-06", "2013-10-08", "2013-10-08", "2013-10-10", "2013-10-13", "2013-10-14", "2013-10-14", "2013-10-14", "2013-10-16", "2013-10-16", "2013-10-17", "2013-10-22", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-24", "2013-10-27", "2013-10-28", "2013-10-29", "2013-10-31", "2013-10-31", "2013-11-03", "2013-11-04", "2013-11-04", "2013-11-05", "2013-11-06", "2013-11-07", "2013-11-07", "2013-11-08", "2013-11-14", "2013-11-14", "2013-11-15", "2013-11-17", "2013-11-17", "2013-11-18", "2013-11-20", "2013-11-22", "2013-11-22", "2013-12-01", "2013-12-02", "2013-12-03", "2013-12-04", "2013-12-04", "2013-12-04", "2013-12-09", "2013-12-10", "2013-12-10", "2013-12-10", "2013-12-11", "2013-12-16", "2013-12-16", "2013-12-17", "2013-12-18", "2013-12-21", "2013-12-21", "2013-12-23", "2013-12-23", "2013-12-26", "2013-12-27", "2013-12-31", "2014-01-05", "2014-01-05", "2014-01-05", "2014-01-08", "2014-01-09", "2014-01-10", "2014-01-12", "2014-01-14", "2014-01-16", "2014-01-17", "2014-01-20", "2014-01-20", "2014-01-20", "2014-01-21", "2014-01-21", "2014-01-23", "2014-01-25", "2014-01-27", "2014-01-28", "2014-01-28", "2014-01-29", "2014-01-29", "2014-01-31", "2014-01-31", "2014-02-02", "2014-02-03", "2014-02-04", "2014-02-05", "2014-02-05", "2014-02-06", "2014-02-06", "2014-02-12", "2014-02-13", "2014-02-15", "2014-02-17", "2014-02-18", "2014-02-19", "2014-02-21", "2014-02-25", "2014-02-25", "2014-02-25", "2014-02-27", "2014-02-27", "2014-02-28", "2014-03-02", "2014-03-03", "2014-03-05", "2014-03-05", "2014-03-09", "2014-03-12", "2014-03-12", "2014-03-16", "2014-03-19", "2014-03-19", "2014-03-22", "2014-03-23", "2014-03-26", "2014-03-27", "2014-03-28", "2014-03-29", "2014-03-31", "2014-03-31", "2014-03-31", "2014-04-01", "2014-04-02", "2014-04-03", "2014-04-06", "2014-04-07", "2014-04-08", "2014-04-09", "2014-04-10", "2014-04-15", "2014-04-16", "2014-04-16", "2014-04-16", "2014-04-17", "2014-04-18", "2014-04-24", "2014-04-24", "2014-05-02", "2014-05-05", "2014-05-05", "2014-05-07", "2014-05-07", "2014-05-09", "2014-05-09", "2014-05-10", "2014-05-14", "2014-05-15", "2014-05-15", "2014-05-16", "2014-05-16", "2014-05-20", "2014-05-21", "2014-05-21", "2014-05-23", "2014-05-23", "2014-05-24", "2014-05-27", "2014-05-27", "2014-05-27", "2014-05-29", "2014-06-02", "2014-06-03", "2014-06-04", "2014-06-05", "2014-06-06", "2014-06-06", "2014-06-09", "2014-06-14", "2014-06-16", "2014-06-17", "2014-06-19", "2014-06-19", "2014-06-20", "2014-06-20", "2014-06-20", "2014-06-22", "2014-06-23", "2014-06-23", "2014-06-23", "2014-06-24", "2014-06-24", "2014-06-25", "2014-06-28", "2014-06-29", "2014-06-30", "2014-07-01", "2014-07-02", "2014-07-07", "2014-07-08", "2014-07-11", "2014-07-11", "2014-07-12", "2014-07-13", "2014-07-14", "2014-07-16", "2014-07-16", "2014-07-17", "2014-07-20", "2014-07-21", "2014-07-22", "2014-07-22", "2014-07-23", "2014-07-23", "2014-07-23", "2014-07-25", "2014-07-25", "2014-07-25", "2014-07-27", "2014-07-28", "2014-07-30", "2014-07-31", "2014-08-04", "2014-08-05", "2014-08-05", "2014-08-09", "2014-08-11", "2014-08-12", "2014-08-13", "2014-08-14", "2014-08-14", "2014-08-15", "2014-08-17", "2014-08-18", "2014-08-18", "2014-08-18", "2014-08-23", "2014-08-26", "2014-08-26", "2014-08-27", "2014-08-29", "2014-08-30", "2014-08-30", "2014-08-31", "2014-09-02", "2014-09-03", "2014-09-03", "2014-09-04", "2014-09-05", "2014-09-06", "2014-09-07", "2014-09-08", "2014-09-09", "2014-09-11", "2014-09-12", "2014-09-12", "2014-09-12", "2014-09-12", "2014-09-15", "2014-09-16", "2014-09-16", "2014-09-17", "2014-09-18", "2014-09-19", "2014-09-19", "2014-09-19", "2014-09-21", "2014-09-22", "2014-09-22", "2014-09-23", "2014-09-27", "2014-09-27", "2014-09-29", "2014-09-30", "2014-10-01", "2014-10-02", "2014-10-04", "2014-10-04", "2014-10-06", "2014-10-07", "2014-10-07", "2014-10-08", "2014-10-12", "2014-10-12", "2014-10-13", "2014-10-14", "2014-10-15", "2014-10-16", "2014-10-18", "2014-10-19", "2014-10-20", "2014-10-20", "2014-10-21", "2014-10-21", "2014-10-22", "2014-10-22", "2014-10-23", "2014-10-23", "2014-10-25", "2014-10-27", "2014-10-27", "2014-10-29", "2014-10-30", "2014-10-30", "2014-10-31", "2014-11-03", "2014-11-04", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-19", "2014-11-20", "2014-11-21", "2014-11-22", "2014-11-24", "2014-11-24", "2014-11-24", "2014-11-26", "2014-11-30", "2014-12-01", "2014-12-01", "2014-12-02", "2014-12-03", "2014-12-04", "2014-12-04", "2014-12-05", "2014-12-06", "2014-12-08", "2014-12-08", "2014-12-11", "2014-12-16", "2014-12-17", "2014-12-19", "2014-12-23", "2014-12-26", "2014-12-26", "2014-12-26", "2014-12-27", "2014-12-27", "2014-12-27", "2014-12-29", "2014-12-29", "2014-12-30", "2015-01-01", "2015-01-01", "2015-01-01", "2015-01-02", "2015-01-05", "2015-01-05", "2015-01-05", "2015-01-06", "2015-01-06", "2015-01-07", "2015-01-07", "2015-01-09", "2015-01-10", "2015-01-10", "2015-01-10", "2015-01-11", "2015-01-11", "2015-01-12", "2015-01-12", "2015-01-13", "2015-01-14", "2015-01-15", "2015-01-18", "2015-01-18", "2015-01-19", "2015-01-19", "2015-01-19", "2015-01-19", "2015-01-21", "2015-01-21", "2015-01-23", "2015-01-25", "2015-01-28", "2015-01-28", "2015-01-29", "2015-02-01", "2015-02-02", "2015-02-04", "2015-02-05", "2015-02-05", "2015-02-06", "2015-02-07", "2015-02-09", "2015-02-10", "2015-02-12", "2015-02-13", "2015-02-14", "2015-02-15", "2015-02-17", "2015-02-19", "2015-02-20", "2015-02-23", "2015-02-23", "2015-02-23", "2015-02-24", "2015-02-24", "2015-02-24", "2015-02-26", "2015-02-26", "2015-02-26", "2015-02-26", "2015-02-27", "2015-02-28", "2015-02-28", "2015-02-28", "2015-03-01", "2015-03-03", "2015-03-03", "2015-03-04", "2015-03-04", "2015-03-08", "2015-03-09", "2015-03-10", "2015-03-10", "2015-03-11", "2015-03-11", "2015-03-11", "2015-03-11", "2015-03-13", "2015-03-16", "2015-03-16", "2015-03-17", "2015-03-18", "2015-03-29", "2015-03-31", "2015-03-31", "2015-04-01", "2015-04-05", "2015-04-06", "2015-04-06", "2015-04-07", "2015-04-07", "2015-04-07", "2015-04-08", "2015-04-08", "2015-04-09", "2015-04-09", "2015-04-10", "2015-04-12", "2015-04-12", "2015-04-14", "2015-04-16", "2015-04-17", "2015-04-21", "2015-04-22", "2015-04-23", "2015-04-23", "2015-04-24", "2015-04-25", "2015-04-30", "2015-05-01", "2015-05-01", "2015-05-07", "2015-05-07", "2015-05-10", "2015-05-11", "2015-05-13", "2015-05-13", "2015-05-14", "2015-05-15", "2015-05-18", "2015-05-21", "2015-05-21", "2015-05-21", "2015-05-22", "2015-05-22", "2015-05-25", "2015-05-28", "2015-05-29", "2015-05-29", "2015-05-30", "2015-06-02", "2015-06-04", "2015-06-04", "2015-06-05", "2015-06-06", "2015-06-08", "2015-06-08", "2015-06-08", "2015-06-10", "2015-06-15", "2015-06-16", "2015-06-17", "2015-06-17", "2015-06-20", "2015-06-24", "2015-06-26", "2015-06-26", "2015-06-27", "2015-06-27", "2015-06-30", "2015-07-03", "2015-07-03", "2015-07-06", "2015-07-07", "2015-07-08", "2015-07-08", "2015-07-13", "2015-07-14", "2015-07-14", "2015-07-14", "2015-07-15", "2015-07-16", "2015-07-16", "2015-07-17", "2015-07-21", "2015-07-21", "2015-07-22", "2015-07-23", "2015-07-23", "2015-07-24", "2015-07-27", "2015-07-28", "2015-07-29", "2015-07-29", "2015-07-29", "2015-07-30", "2015-07-31", "2015-08-02", "2015-08-02", "2015-08-02", "2015-08-02", "2015-08-03", "2015-08-05", "2015-08-06", "2015-08-06", "2015-08-09", "2015-08-09", "2015-08-10", "2015-08-11", "2015-08-12", "2015-08-12", "2015-08-15", "2015-08-18", "2015-08-18", "2015-08-19", "2015-08-20", "2015-08-21", "2015-08-21", "2015-08-24", "2015-08-25", "2015-08-27", "2015-08-27", "2015-09-02", "2015-09-03", "2015-09-03", "2015-09-06", "2015-09-08", "2015-09-09", "2015-09-10", "2015-09-10", "2015-09-11", "2015-09-14", "2015-09-14", "2015-09-15", "2015-09-15", "2015-09-16", "2015-09-17", "2015-09-19", "2015-09-21", "2015-09-21", "2015-09-22", "2015-09-23", "2015-09-24", "2015-09-28", "2015-09-29", "2015-09-30", "2015-09-30", "2015-09-30", "2015-10-02", "2015-10-05", "2015-10-05", "2015-10-05", "2015-10-05", "2015-10-06", "2015-10-08", "2015-10-10", "2015-10-10", "2015-10-12", "2015-10-12", "2015-10-12", "2015-10-13", "2015-10-13", "2015-10-14", "2015-10-14", "2015-10-15", "2015-10-16", "2015-10-18", "2015-10-18", "2015-10-19", "2015-10-19", "2015-10-19", "2015-10-21", "2015-10-21", "2015-10-21", "2015-10-22", "2015-10-22", "2015-10-23", "2015-10-24", "2015-10-26", "2015-10-26", "2015-10-29", "2015-10-29", "2015-10-29", "2015-11-02", "2015-11-03", "2015-11-04", "2015-11-04", "2015-11-06", "2015-11-09", "2015-11-10", "2015-11-10", "2015-11-11", "2015-11-18", "2015-11-18", "2015-11-19", "2015-11-20", "2015-11-24", "2015-11-26", "2015-12-01", "2015-12-02", "2015-12-05", "2015-12-08", "2015-12-10", "2015-12-14", "2015-12-24", "2015-12-31", "2016-01-06", "2016-01-08", "2016-01-08", "2016-01-11", "2016-01-16", "2016-01-18", "2016-01-19", "2016-01-20", "2016-01-22", "2016-01-25", "2016-01-26", "2016-01-28", "2016-01-29", "2016-02-01", "2016-02-01", "2016-02-02", "2016-02-03", "2016-02-05", "2016-02-05", "2016-02-06", "2016-02-09", "2016-02-11", "2016-02-12", "2016-02-13", "2016-02-22", "2016-02-24", "2016-02-24", "2016-02-25", "2016-02-26", "2016-03-03", "2016-03-04", "2016-03-05", "2016-03-06", "2016-03-08", "2016-03-09", "2016-03-11", "2016-03-14", "2016-03-14", "2016-03-15", "2016-03-18", "2016-03-22", "2016-03-23", "2016-03-24", "2016-03-27", "2016-03-28", "2016-04-05", "2016-04-06", "2016-04-08", "2016-04-10", "2016-04-12", "2016-04-14", "2016-04-14", "2016-04-14", "2016-04-17", "2016-04-20", "2016-04-21", "2016-04-21", "2016-04-23", "2016-04-24", "2016-05-01", "2016-05-01", "2016-05-02", "2016-05-04", "2016-05-04", "2016-05-07", "2016-05-09", "2016-05-10", "2016-05-10", "2016-05-15", "2016-05-16", "2016-05-18", "2016-05-19", "2016-05-20", "2016-05-21", "2016-05-21", "2016-05-27", "2016-06-02", "2016-06-02", "2016-06-04", "2016-06-04", "2016-06-06", "2016-06-08", "2016-06-11", "2016-06-13", "2016-06-15", "2016-06-24", "2016-06-27", "2016-06-28", "2016-06-29", "2016-07-01", "2016-07-01", "2016-07-03", "2016-07-03", "2016-07-06", "2016-07-07", "2016-07-07", "2016-07-09", "2016-07-11", "2016-07-12", "2016-07-13", "2016-07-14", "2016-07-15", "2016-07-16", "2016-07-19", "2016-07-24", "2016-07-29", "2016-07-30", "2016-07-31", "2016-08-02", "2016-08-04", "2016-08-08", "2016-08-09", "2016-08-09", "2016-08-11", "2016-08-12", "2016-08-14", "2016-08-15", "2016-08-16", "2016-08-16", "2016-08-19", "2016-08-19", "2016-08-23", "2016-08-23", "2016-08-28", "2016-08-31", "2016-09-01", "2016-09-03", "2016-09-03", "2016-09-04", "2016-09-05", "2016-09-07", "2016-09-09", "2016-09-09", "2016-09-13", "2016-09-15", "2016-09-18", "2016-09-21", "2016-09-26", "2016-09-27", "2016-09-27", "2016-09-28", "2016-09-30", "2016-10-03", "2016-10-03", "2016-10-03", "2016-10-04", "2016-10-04", "2016-10-04", "2016-10-06", "2016-10-07", "2016-10-07", "2016-10-07", "2016-10-11", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-13", "2016-10-14", "2016-10-17", "2016-10-19", "2016-10-19", "2016-10-21", "2016-10-21", "2016-10-21", "2016-10-23", "2016-10-23", "2016-10-23", "2016-10-24", "2016-10-24", "2016-10-25", "2016-10-26", "2016-10-30", "2016-10-30", "2016-10-30", "2016-10-31", "2016-10-31", "2016-11-02", "2016-11-02", "2016-11-03", "2016-11-09", "2016-11-09", "2016-11-10", "2016-11-13", "2016-11-14", "2016-11-15", "2016-11-19", "2016-11-23", "2016-11-25", "2016-11-27", "2016-11-28", "2016-11-30", "2016-12-01", "2016-12-04", "2016-12-07", "2016-12-07", "2016-12-11", "2016-12-11", "2016-12-12", "2016-12-14", "2016-12-14", "2016-12-14", "2016-12-15", "2016-12-15", "2016-12-16", "2016-12-19", "2016-12-21", "2016-12-21", "2016-12-24", "2016-12-27", "2016-12-28", "2016-12-31", "2017-01-02", "2017-01-02", "2017-01-02", "2017-01-02", "2017-01-03", "2017-01-04", "2017-01-04", "2017-01-04", "2017-01-06", "2017-01-08", "2017-01-09", "2017-01-09", "2017-01-10", "2017-01-10", "2017-01-10", "2017-01-10", "2017-01-11", "2017-01-16", "2017-01-18", "2017-01-19", "2017-01-21", "2017-01-22", "2017-01-22", "2017-01-23", "2017-01-23", "2017-01-23", "2017-01-25", "2017-01-26", "2017-01-27", "2017-01-27", "2017-01-27", "2017-01-28", "2017-01-29", "2017-01-30", "2017-01-31", "2017-01-31", "2017-02-02", "2017-02-05", "2017-02-05", "2017-02-07", "2017-02-08", "2017-02-09", "2017-02-09", "2017-02-10", "2017-02-11", "2017-02-11", "2017-02-13", "2017-02-13", "2017-02-16", "2017-02-17", "2017-02-21", "2017-02-22", "2017-02-23", "2017-02-24", "2017-02-25", "2017-02-27", "2017-02-28", "2017-02-28", "2017-02-28", "2017-03-01", "2017-03-01", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-03", "2017-03-05", "2017-03-06", "2017-03-06", "2017-03-07", "2017-03-07", "2017-03-10", "2017-03-10", "2017-03-12", "2017-03-12", "2017-03-15", "2017-03-16", "2017-03-16", "2017-03-18", "2017-03-18", "2017-03-19", "2017-03-19", "2017-03-20", "2017-03-21", "2017-03-21", "2017-03-22", "2017-03-23", "2017-03-24", "2017-03-24", "2017-03-26", "2017-03-26", "2017-03-26", "2017-03-26", "2017-03-27", "2017-03-28", "2017-03-29", "2017-03-30", "2017-03-30", "2017-03-31", "2017-04-01", "2017-04-01", "2017-04-02", "2017-04-03", "2017-04-04", "2017-04-05", "2017-04-05", "2017-04-05", "2017-04-06", "2017-04-07", "2017-04-08", "2017-04-09", "2017-04-10", "2017-04-11", "2017-04-12", "2017-04-12", "2017-04-13", "2017-04-15", "2017-04-17", "2017-04-17", "2017-04-18", "2017-04-18", "2017-04-19", "2017-04-20", "2017-04-20", "2017-04-21", "2017-04-24", "2017-04-25", "2017-04-25", "2017-04-27", "2017-04-28", "2017-04-28", "2017-04-29", "2017-04-29", "2017-04-30", "2017-05-02", "2017-05-02", "2017-05-02", "2017-05-05", "2017-05-06", "2017-05-06", "2017-05-07", "2017-05-07", "2017-05-07", "2017-05-08", "2017-05-08", "2017-05-09", "2017-05-09", "2017-05-09", "2017-05-09", "2017-05-10", "2017-05-11", "2017-05-11", "2017-05-11", "2017-05-13", "2017-05-15", "2017-05-15", "2017-05-15", "2017-05-16", "2017-05-16", "2017-05-16", "2017-05-16", "2017-05-18", "2017-05-19", "2017-05-20", "2017-05-21", "2017-05-21", "2017-05-21", "2017-05-22", "2017-05-22", "2017-05-22", "2017-05-23", "2017-05-24", "2017-05-24", "2017-05-29", "2017-05-31", "2017-05-31", "2017-06-01", "2017-06-01", "2017-06-02", "2017-06-03", "2017-06-05", "2017-06-06", "2017-06-07", "2017-06-07", "2017-06-07", "2017-06-07", "2017-06-08", "2017-06-08", "2017-06-10", "2017-06-11", "2017-06-11", "2017-06-13", "2017-06-13", "2017-06-13", "2017-06-15", "2017-06-15", "2017-06-15", "2017-06-16", "2017-06-16", "2017-06-18", "2017-06-20", "2017-06-20", "2017-06-21", "2017-06-22", "2017-06-22", "2017-06-24", "2017-06-27", "2017-06-28", "2017-06-28", "2017-06-30", "2017-07-05", "2017-07-05", "2017-07-07", "2017-07-08", "2017-07-10", "2017-07-10", "2017-07-11", "2017-07-11", "2017-07-12", "2017-07-13", "2017-07-14", "2017-07-15", "2017-07-17", "2017-07-17", "2017-07-17", "2017-07-17", "2017-07-18", "2017-07-18", "2017-07-18", "2017-07-19", "2017-07-19", "2017-07-20", "2017-07-20", "2017-07-20", "2017-07-22", "2017-07-23", "2017-07-24", "2017-07-24", "2017-07-25", "2017-07-25", "2017-07-27", "2017-07-27", "2017-07-28", "2017-07-30", "2017-07-31", "2017-07-31", "2017-08-01", "2017-08-01", "2017-08-04", "2017-08-05", "2017-08-06", "2017-08-06", "2017-08-07", "2017-08-07", "2017-08-09", "2017-08-09", "2017-08-09", "2017-08-10", "2017-08-14", "2017-08-14", "2017-08-15", "2017-08-15", "2017-08-16", "2017-08-17", "2017-08-17", "2017-08-17", "2017-08-19", "2017-08-21", "2017-08-21", "2017-08-21", "2017-08-22", "2017-08-22", "2017-08-24", "2017-08-24", "2017-08-25", "2017-08-27", "2017-08-28", "2017-08-28", "2017-08-29", "2017-08-31", "2017-08-31", "2017-09-01", "2017-09-03", "2017-09-04", "2017-09-05", "2017-09-05", "2017-09-06", "2017-09-06", "2017-09-06", "2017-09-07", "2017-09-07", "2017-09-07", "2017-09-08", "2017-09-09", "2017-09-11", "2017-09-11", "2017-09-11", "2017-09-12", "2017-09-13", "2017-09-13", "2017-09-16", "2017-09-18", "2017-09-18", "2017-09-20", "2017-09-21", "2017-09-21", "2017-09-21", "2017-09-22", "2017-09-22", "2017-09-24", "2017-09-26", "2017-09-26", "2017-09-27", "2017-09-28", "2017-09-28", "2017-09-29", "2017-09-29", "2017-09-30", "2017-10-02", "2017-10-03", "2017-10-03", "2017-10-03", "2017-10-04", "2017-10-05", "2017-10-06", "2017-10-07", "2017-10-07", "2017-10-09", "2017-10-09", "2017-10-10", "2017-10-11", "2017-10-12", "2017-10-12", "2017-10-13", "2017-10-13", "2017-10-17", "2017-10-17", "2017-10-18", "2017-10-19", "2017-10-20", "2017-10-21", "2017-10-24", "2017-10-24", "2017-10-27", "2017-10-27", "2017-10-28", "2017-10-29", "2017-10-30", "2017-10-31", "2017-10-31", "2017-10-31", "2017-11-01", "2017-11-01", "2017-11-03", "2017-11-04", "2017-11-06", "2017-11-06", "2017-11-07", "2017-11-07", "2017-11-07", "2017-11-08", "2017-11-10", "2017-11-12", "2017-11-13", "2017-11-14", "2017-11-14", "2017-11-14", "2017-11-15", "2017-11-16", "2017-11-17", "2017-11-19", "2017-11-19", "2017-11-20", "2017-11-20", "2017-11-24", "2017-11-25", "2017-11-26", "2017-11-26", "2017-11-27", "2017-11-27", "2017-11-27", "2017-12-01", "2017-12-01", "2017-12-03", "2017-12-04", "2017-12-04", "2017-12-05", "2017-12-05", "2017-12-06", "2017-12-08", "2017-12-10", "2017-12-12", "2017-12-12", "2017-12-13", "2017-12-15", "2017-12-17", "2017-12-19", "2017-12-20", "2017-12-20", "2017-12-20", "2017-12-21", "2017-12-26", "2017-12-29", "2017-12-29", "2018-01-02", "2018-01-02", "2018-01-03", "2018-01-03", "2018-01-04", "2018-01-04", "2018-01-06", "2018-01-06", "2018-01-06", "2018-01-07", "2018-01-08", "2018-01-09", "2018-01-10", "2018-01-10", "2018-01-10", "2018-01-11", "2018-01-11", "2018-01-12", "2018-01-14", "2018-01-15", "2018-01-15", "2018-01-15", "2018-01-15", "2018-01-16", "2018-01-18", "2018-01-19", "2018-01-19", "2018-01-19", "2018-01-20", "2018-01-22", "2018-01-22", "2018-01-23", "2018-01-23", "2018-01-24", "2018-01-24", "2018-01-24", "2018-01-27", "2018-01-28", "2018-01-30", "2018-01-30", "2018-01-30", "2018-01-31", "2018-01-31", "2018-01-31", "2018-02-01", "2018-02-02", "2018-02-03", "2018-02-03", "2018-02-04", "2018-02-04", "2018-02-05", "2018-02-06", "2018-02-06", "2018-02-06", "2018-02-08", "2018-02-09", "2018-02-10", "2018-02-11", "2018-02-12", "2018-02-13", "2018-02-15", "2018-02-16", "2018-02-16", "2018-02-16", "2018-02-18", "2018-02-20", "2018-02-23", "2018-02-24", "2018-02-27", "2018-02-27", "2018-03-02", "2018-03-02", "2018-03-04", "2018-03-06", "2018-03-06", "2018-03-07", "2018-03-08", "2018-03-08", "2018-03-08", "2018-03-08", "2018-03-10", "2018-03-11", "2018-03-11", "2018-03-14", "2018-03-14", "2018-03-15", "2018-03-18", "2018-03-19", "2018-03-19", "2018-03-19", "2018-03-20", "2018-03-20", "2018-03-20", "2018-03-20", "2018-03-21", "2018-03-22", "2018-03-26", "2018-03-26", "2018-03-26", "2018-03-27", "2018-03-27", "2018-03-27", "2018-03-28", "2018-03-28", "2018-03-30", "2018-03-31", "2018-04-01", "2018-04-03", "2018-04-03", "2018-04-04", "2018-04-04", "2018-04-05", "2018-04-05", "2018-04-07", "2018-04-09", "2018-04-09", "2018-04-11", "2018-04-12", "2018-04-12", "2018-04-13", "2018-04-14", "2018-04-15", "2018-04-16", "2018-04-17", "2018-04-17", "2018-04-18", "2018-04-23", "2018-04-24", "2018-04-26", "2018-04-27", "2018-04-27", "2018-04-30", "2018-05-01", "2018-05-02", "2018-05-02", "2018-05-03", "2018-05-05", "2018-05-05", "2018-05-07", "2018-05-07", "2018-05-07", "2018-05-08", "2018-05-08", "2018-05-08", "2018-05-08", "2018-05-09", "2018-05-11", "2018-05-11", "2018-05-12", "2018-05-15", "2018-05-16", "2018-05-16", "2018-05-18", "2018-05-19", "2018-05-19", "2018-05-22", "2018-05-23", "2018-05-27", "2018-05-27", "2018-05-31", "2018-05-31", "2018-06-02", "2018-06-04", "2018-06-05", "2018-06-05", "2018-06-05", "2018-06-06"], "y": [0.4666666666666666, 0.35, 0.75, 0.6333333333333333, 0.6333333333333333, 0.5405303030303029, 0.42500000000000004, 0.15000000000000002, 0.33499999999999996, 0.6433333333333334, 0.7625000000000001, 0.6694444444444444, 0.5, 0.15, 0.475, 0.35833333333333334, 0.75, 0.36309523809523814, 0.355, 0.6848484848484849, 0.5857142857142857, 0.5666666666666667, 0.425, 0.47847222222222224, 0.5840909090909091, 0.75, 0.5125, 0.54, 0.45357142857142857, 0.4387445887445887, 0.4597222222222222, 0.415, 0.5592203548085901, 0.3875992063492064, 0.4375, 0.5617768595041323, 0.75, 0.4, 0.36666666666666664, 0.375, 0.18333333333333335, 0.675, 0.8666666666666667, 0.7200000000000001, 0.46296296296296297, 0.5416666666666666, 0.2553030303030303, 0.6202020202020203, 0.56, 0.38095238095238093, 0.4686868686868687, 0.5583333333333333, 1.0, 0.0, 0.5301406926406925, 0.538611111111111, 0.40492424242424246, 0.55625, 0.7, 0.4192857142857143, 0.06666666666666667, 0.5483333333333333, 0.9, 0.7408333333333333, 0.7, 0.5166666666666666, 1.0, 0.9123333333333334, 0.5, 0.43333333333333335, 0.6104166666666667, 1.0, 0.31500000000000006, 0.4011904761904762, 0.403, 1.0, 0.5246666666666666, 0.0, 0.6381313131313132, 0.0, 0.75, 0.35, 0.5333333333333333, 0.6333333333333334, 0.6875, 0.39999999999999997, 0.7000000000000001, 0.8, 0.54, 0.6805555555555555, 0.49777777777777776, 0.6458333333333333, 0.30000000000000004, 0.5315151515151515, 0.48125, 0.7493939393939393, 0.6515151515151515, 0.75, 0.4666666666666666, 0.595, 0.4333333333333333, 0.0, 0.6384615384615384, 0.75, 0.3, 0.4927083333333333, 0.0, 0.5181818181818182, 0.4433333333333333, 0.4969387755102041, 0.5750000000000001, 0.54, 0.56, 0.7, 0.32708333333333334, 0.625, 0.0, 0.5845238095238094, 0.46749999999999997, 0.725, 0.5178333333333333, 0.5000000000000001, 0.55, 0.3375, 0.8125, 0.4491666666666666, 0.375, 0.46666666666666673, 0.0, 0.4683333333333334, 0.3, 0.3717171717171717, 0.5416666666666666, 0.6000000000000001, 0.1375, 0.7689814814814814, 0.6124999999999999, 0.9, 0.51, 0.5499999999999999, 0.600952380952381, 0.75, 0.556, 0.24666666666666667, 0.0, 0.66, 0.45454545454545453, 0.5571428571428572, 0.31666666666666665, 0.4833333333333334, 0.5, 0.75, 0.6625, 0.0, 0.37187499999999996, 0.5625, 0.4629545454545454, 0.6580246913580248, 0.41000000000000003, 0.5833333333333334, 0.6833333333333333, 0.62, 0.5, 0.459469696969697, 0.0, 0.5944444444444444, 0.625, 0.9, 0.5737373737373738, 0.3, 0.7108333333333333, 0.35656565656565653, 0.4020833333333333, 0.3045798898071625, 0.6, 0.6000000000000001, 0.6, 0.8333333333333334, 0.0, 0.7193877551020408, 0.75, 0.7071428571428571, 0.5708333333333333, 0.6000000000000001, 0.46530612244897956, 0.60625, 0.44097222222222227, 0.6, 0.375, 0.45333333333333337, 0.66494708994709, 0.6305555555555555, 0.5888888888888889, 0.5766666666666665, 0.43333333333333335, 0.5041666666666667, 0.75, 0.5, 0.7875, 0.0, 0.625, 0.6433333333333333, 0.8666666666666667, 0.45, 0.5208333333333333, 0.8416666666666667, 0.48484848484848486, 0.48981481481481487, 0.40925925925925927, 0.2888888888888889, 0.6, 0.4666666666666666, 0.6261363636363636, 0.5622574955908289, 0.75, 0.44285714285714284, 0.44629629629629636, 0.8, 0.3698412698412698, 0.6722222222222222, 0.75, 1.0, 0.5750000000000001, 0.32500000000000007, 0.4, 0.5599999999999999, 0.65, 1.0, 0.8, 0.2553846153846154, 0.5755853994490359, 0.5666666666666668, 0.5, 0.5, 0.3066666666666667, 0.75, 0.3, 0.55, 0.6, 0.42727272727272725, 0.5721726190476191, 0.4341156462585034, 0.638888888888889, 0.4166666666666667, 0.40833333333333327, 0.17083333333333334, 0.6, 0.3645833333333333, 0.55, 0.5077922077922079, 0.8, 0.5274621212121212, 0.875, 0.75, 0.6000000000000001, 0.0, 0.5225000000000001, 0.4208333333333333, 0.5007575757575758, 0.5458333333333333, 0.7364583333333332, 0.6666666666666666, 0.7638888888888888, 0.5333333333333333, 0.54, 0.61, 0.5625, 0.5931818181818181, 0.6666666666666666, 0.3, 0.675, 0.5493055555555556, 0.3, 0.65, 0.9166666666666666, 0.3875, 0.475, 0.5111111111111111, 0.5245265151515152, 0.5105, 0.5357142857142857, 0.48095238095238096, 0.595, 0.0, 0.6375, 0.43443452380952385, 0.4161552028218695, 0.45, 0.4444444444444444, 0.7, 0.38387755102040816, 0.0, 0.1, 0.6125, 0.4, 0.3857142857142858, 0.0, 0.37083333333333335, 0.7700000000000001, 0.47500000000000003, 0.55, 0.38484848484848483, 0.4916666666666667, 0.5083333333333333, 0.3888888888888889, 0.425, 0.75, 0.5, 0.5, 0.625, 0.44125000000000003, 0.4178571428571428, 0.34333333333333343, 0.65, 0.7444444444444445, 0.6499999999999999, 0.4, 0.4666666666666666, 0.6, 0.3263888888888889, 0.2375, 0.3, 0.675, 0.35833333333333334, 0.4902777777777778, 0.4772727272727273, 0.42272727272727273, 0.6000000000000001, 0.6, 0.625, 0.4708333333333333, 0.0, 0.55, 0.5, 0.3871047619047619, 0.0, 0.3, 0.7379761904761905, 0.5166666666666667, 0.6042857142857142, 0.46071428571428574, 0.6057777777777777, 0.5, 0.05, 0.6729166666666667, 0.6166666666666667, 0.56, 0.0, 0.5083333333333333, 0.5597222222222222, 0.7962962962962963, 0.6009090909090908, 0.85, 0.4261111111111111, 0.6000000000000001, 0.4666666666666666, 0.4, 0.4366666666666667, 0.75, 0.4027083333333333, 0.74375, 0.5277777777777778, 0.5055555555555555, 0.5725, 0.7, 0.5462962962962963, 0.5, 0.6333333333333333, 0.33499999999999996, 0.49444444444444446, 0.5397727272727273, 0.4208333333333333, 0.3904761904761905, 0.41666666666666663, 0.35000000000000003, 0.35000000000000003, 0.65, 0.4888888888888889, 0.4583333333333333, 0.578198653198653, 0.64, 0.25, 0.0, 0.7388888888888889, 0.7266666666666667, 0.5141534391534391, 0.6169270833333333, 1.0, 0.35, 0.44999999999999996, 0.9, 0.3333333333333333, 0.6, 0.0, 0.5333333333333333, 0.7430555555555557, 0.6571428571428571, 0.25, 0.5833333333333334, 0.7, 0.5636363636363637, 0.3, 0.6000000000000001, 0.4875, 0.4181818181818182, 0.8333333333333334, 0.39166666666666666, 0.3666666666666667, 0.75, 0.45064935064935063, 0.46666666666666673, 0.6014705882352942, 0.74, 0.45454545454545453, 0.5841596638655462, 0.7000000000000001, 0.0, 0.6, 0.5666666666666667, 0.75, 0.48484848484848486, 0.5724358974358975, 0.5520833333333334, 0.5333333333333333, 0.6541666666666667, 0.3333333333333333, 0.6115151515151516, 0.35000000000000003, 0.6928571428571428, 0.6333333333333333, 0.4076190476190476, 0.5375, 0.625, 0.6000000000000001, 0.3125, 0.5272727272727272, 0.4425, 0.6166666666666666, 0.4975993703266429, 0.34375, 0.725, 0.5438888888888889, 0.6741666666666667, 0.125, 0.0, 0.5937499999999999, 0.8333333333333334, 0.6611111111111111, 0.34880952380952385, 0.42074829931972785, 0.6708333333333334, 0.5714285714285714, 0.625, 0.8, 0.39999999999999997, 0.47806122448979593, 0.4361111111111111, 0.48655555555555546, 0.34, 0.6, 0.8181818181818182, 0.48125, 0.65, 0.8888888888888888, 0.5650000000000001, 0.7272727272727273, 0.5499999999999999, 0.5222222222222221, 0.46666666666666673, 0.6333333333333333, 0.4362244897959184, 0.6444444444444445, 0.6875, 0.4982142857142857, 0.4749999999999999, 0.3666666666666667, 0.675, 0.25, 0.5800000000000001, 0.5900000000000001, 0.5555555555555556, 0.0, 0.6757575757575758, 0.8333333333333334, 0.7125, 0.0, 0.13333333333333333, 0.6294642857142857, 0.48750000000000004, 0.4, 0.6000000000000001, 0.7999999999999999, 0.48398268398268396, 0.32727272727272727, 0.625, 0.6000000000000001, 0.7435714285714285, 0.5446296296296297, 0.5, 0.5, 0.35000000000000003, 0.4476190476190476, 0.532912457912458, 0.8333333333333334, 0.0, 0.625, 0.39904607297464434, 0.6138888888888888, 0.49242424242424243, 0.478968253968254, 0.75, 1.0, 0.38095238095238093, 0.38533333333333336, 0.5696428571428572, 0.0, 0.63, 0.22500000000000003, 0.6000000000000001, 0.6000000000000001, 1.0, 0.5708333333333334, 0.4666666666666666, 0.4666666666666666, 0.8, 0.45999999999999996, 0.5819444444444445, 0.5318181818181819, 0.5891666666666666, 0.55, 0.2863636363636364, 0.7916666666666667, 0.5, 0.25, 1.0, 0.49499999999999994, 0.45000000000000007, 0.6694444444444444, 0.4055555555555556, 0.5722222222222222, 0.3959183673469388, 0.5, 0.57, 0.03333333333333333, 0.46666666666666673, 0.65, 0.8333333333333334, 0.475, 0.4076388888888889, 0.7, 0.4057936507936509, 0.41, 0.3333333333333333, 0.7177777777777777, 0.7, 0.8666666666666667, 0.37916666666666665, 0.3, 0.7392857142857142, 0.41633333333333333, 0.30196078431372547, 0.4277777777777778, 0.6583333333333333, 0.5, 0.4, 0.6666666666666667, 0.6000000000000001, 0.0, 0.4526515151515151, 0.0, 0.525, 0.45454545454545453, 0.4, 0.6, 0.5, 0.625, 0.3033333333333333, 0.3787265764538492, 0.725, 0.3375, 0.6875, 0.75, 0.27090909090909093, 0.0, 0.5249999999999999, 0.3, 0.5, 0.5437878787878788, 0.7000000000000001, 0.41999999999999993, 0.7000000000000001, 0.6260101010101009, 0.8, 0.8, 0.66875, 0.6366666666666666, 0.35, 0.7125, 0.4, 0.0, 0.2908424908424908, 0.4646464646464647, 0.71875, 0.5683333333333334, 0.42000000000000004, 0.6, 0.775, 0.6125, 0.41250000000000003, 0.4, 0.43333333333333335, 0.375, 0.5098809523809524, 0.7, 0.75, 0.0, 0.2125, 0.6166666666666667, 0.6057142857142856, 0.41217687074829923, 0.5, 0.525, 0.5257575757575758, 0.0, 0.6900000000000001, 0.42500000000000004, 0.75, 0.56, 0.6, 0.5833333333333334, 0.7933333333333334, 0.740625, 0.4444444444444444, 0.4909523809523809, 0.0, 0.0, 0.6, 0.6375, 0.7875, 0.9333333333333332, 0.825, 0.6625, 0.3, 0.806, 0.5416666666666666, 0.5570105820105821, 0.4863636363636364, 0.6326388888888889, 0.75, 0.4425, 0.5499999999999999, 0.61, 0.5896464646464646, 0.375, 0.5125, 0.6000000000000001, 0.55, 0.725, 0.7083333333333333, 0.7500000000000001, 0.6166666666666667, 0.45, 0.65, 0.625, 0.775, 0.0, 0.2, 0.0, 0.75, 0.4380519480519481, 0.5619047619047618, 0.5708333333333333, 0.3833333333333333, 0.7000000000000001, 0.48124999999999996, 0.34722222222222215, 0.675, 0.34722222222222215, 0.34722222222222215, 0.8125, 0.49474789915966383, 0.6428571428571429, 0.6555555555555556, 0.0, 0.5740000000000001, 0.625, 0.3, 0.4533333333333333, 0.3125, 0.5183333333333333, 0.5272727272727273, 0.6178571428571429, 0.37727272727272726, 0.5855952380952381, 0.5712301587301588, 0.5630176767676768, 0.68, 0.0, 0.4122619047619048, 0.5006395120031484, 0.75, 0.6345238095238095, 0.7958333333333334, 0.475, 0.75, 0.51, 0.37916666666666665, 0.7698863636363636, 0.75, 0.3, 0.15, 0.5541666666666667, 0.5077922077922078, 0.5, 0.3583333333333334, 0.501, 0.5625000000000001, 0.6875, 0.4666666666666667, 0.525, 0.5488095238095237, 0.45999999999999996, 0.825, 0.6333333333333333, 0.8, 0.0, 0.46249999999999997, 0.412979797979798, 0.7, 0.45555555555555555, 0.3583333333333334, 0.7000000000000001, 0.48484848484848486, 0.75, 0.4666666666666667, 0.578125, 0.55, 0.8, 0.45729166666666665, 0.4231481481481481, 0.5916666666666667, 0.64, 1.0, 0.75, 0.7625, 0.6305555555555556, 0.32142857142857145, 0.3935064935064934, 0.55, 0.36, 0.4239463601532567, 0.5753787878787878, 0.36354935913759445, 0.46666666666666673, 0.55, 0.31999999999999995, 0.3666666666666667, 0.41428571428571426, 0.3258928571428571, 0.6012500000000001, 0.625, 0.44642857142857145, 0.675925925925926, 1.0, 0.5883333333333333, 0.5, 0.6000000000000001, 0.6085714285714287, 0.5583333333333332, 0.26666666666666666, 0.5416666666666666, 0.75, 0.7111111111111111, 0.423336038961039, 0.49126984126984125, 0.5666666666666667, 0.125, 0.5564814814814815, 0.5130681818181818, 0.3416666666666667, 0.43402777777777773, 0.3348484848484849, 0.483982683982684, 0.47314814814814815, 0.7250000000000001, 0.3125, 0.42037037037037034, 0.5341666666666667, 0.42500000000000004, 0.5333333333333333, 0.5454545454545454, 0.6683333333333333, 0.6000000000000001, 0.625, 0.625, 0.46408730158730155, 0.5750000000000001, 0.5853535353535354, 0.7030303030303031, 0.5962962962962963, 0.26515151515151514, 0.5, 0.3820833333333333, 0.5666666666666668, 0.625, 0.37, 0.5055555555555555, 0.3745833333333333, 0.5425, 0.5701388888888889, 0.725, 0.4616666666666666, 0.15, 0.5666666666666667, 0.5214285714285715, 0.5, 0.2333333333333333, 0.7333333333333334, 0.262962962962963, 0.6375000000000001, 0.54125, 0.8766666666666666, 0.7, 0.6151428571428571, 0.5442777777777777, 0.65, 0.27499999999999997, 0.5833333333333334, 0.5388888888888889, 0.6000000000000001, 0.5125, 0.7577777777777778, 0.6487654320987654, 0.4375, 0.3666666666666667, 0.5772727272727273, 0.5783333333333334, 0.6022727272727273, 0.55, 0.6319444444444444, 0.6319444444444444, 0.6666666666666666, 0.65, 0.39499999999999996, 0.20000000000000004, 0.675, 0.5916666666666667, 0.5619047619047618, 0.6136363636363636, 0.62, 1.0, 0.6000000000000001, 0.125, 0.5110544217687074, 0.32962962962962966, 0.6068181818181819, 0.44, 0.6773809523809524, 0.47333333333333333, 0.44999999999999996, 0.5027000777000776, 0.7095238095238094, 0.5, 0.75, 0.3125, 0.3317333333333333, 0.490625, 0.625, 1.0, 0.5416666666666666, 0.4208333333333334, 0.6352813852813853, 0.562121212121212, 0.77, 0.22962962962962963, 0.64, 0.6630952380952381, 0.5241666666666667, 0.4630681818181818, 0.5142857142857143, 0.4336931818181818, 0.5270833333333332, 0.55, 0.8125, 0.7000000000000001, 0.7, 0.5625, 0.4794444444444445, 0.18541666666666667, 0.356, 0.5174603174603174, 0.6911255411255411, 0.525, 0.5152777777777778, 0.45, 0.5703703703703703, 0.5708333333333333, 0.33749999999999997, 0.6592857142857144, 0.3958333333333333, 0.40595238095238095, 0.4471590909090909, 0.5200000000000001, 0.1875, 0.44499999999999995, 0.65, 0.32222222222222224, 0.5, 0.6000000000000001, 0.5388888888888889, 0.8125, 0.4, 0.4, 0.21333333333333332, 0.5628205128205128, 0.48035714285714287, 0.35, 0.75, 0.8333333333333334, 0.75, 0.5097222222222223, 0.75, 0.1, 0.665, 0.615, 0.725, 0.392, 0.48142857142857143, 0.42749999999999994, 0.6125, 0.1, 0.4643939393939394, 0.7444444444444445, 0.47500000000000003, 0.3666666666666667, 0.20833333333333334, 0.375, 0.6321428571428571, 0.4861111111111111, 1.0, 0.5472222222222222, 0.4, 0.7933333333333333, 0.5222222222222223, 0.6847222222222222, 0.5920482295482297, 0.525, 0.5599999999999999, 0.581, 0.3333333333333333, 0.7000000000000001, 0.3458333333333333, 0.5333333333333333, 0.45, 0.2857142857142857, 0.3815705128205128, 0.625, 0.34, 0.4625, 0.0, 0.7109090909090909, 0.6666666666666666, 0.5007575757575758, 0.6, 0.7886363636363636, 0.4404761904761904, 0.3888888888888889, 0.7100000000000001, 0.75, 0.75, 1.0, 0.6666666666666666, 0.5888888888888889, 0.75, 0.640625, 0.7675000000000001, 0.4916666666666667, 0.45416666666666666, 0.6666666666666666, 0.1, 0.6000000000000001, 0.42860873694207036, 0.5909090909090909, 0.5943722943722943, 0.6716666666666667, 0.7, 0.8, 0.5992704826038159, 0.4181818181818182, 0.0, 0.776, 0.6, 0.5609090909090909, 0.3125, 0.5418367346938775, 0.525, 0.6999999999999998, 0.5181318681318682, 0.21428571428571427, 0.7833333333333333, 0.8181818181818182, 0.26666666666666666, 0.45, 0.5943181818181817, 0.4916666666666667, 0.5708333333333333, 0.5157207977207977, 0.5348484848484848, 0.6979166666666666, 0.5603174603174603, 0.55, 0.51875, 0.6699999999999999, 0.625, 0.9099999999999999, 0.25, 0.43333333333333335, 0.42, 0.6183333333333333, 0.5333333333333333, 0.4916666666666667, 0.47056818181818183, 0.43124999999999997, 0.3, 0.625, 0.5928571428571429, 0.756, 0.4909090909090909, 0.4019480519480519, 0.44791666666666663, 0.6488095238095238, 0.5333333333333333, 0.7000000000000001, 0.296875, 0.7166666666666668, 0.6000000000000001, 0.5957777777777779, 0.4823863636363636, 0.25, 0.6208333333333332, 0.5666666666666668, 0.34520202020202023, 0.625, 0.4437109187109187, 0.3, 0.6000000000000001, 0.5666666666666667, 0.5333333333333333, 0.5472222222222223, 0.5833333333333334, 0.5416666666666666, 0.6499999999999999, 0.65, 0.5892857142857143, 0.5596153846153846, 0.4485185185185185, 0.705, 0.42500000000000004, 0.6535714285714286, 0.5238095238095238, 0.5988636363636364, 0.5777777777777778, 0.6666666666666666, 0.6246031746031745, 0.6708333333333333, 0.5647727272727273, 0.6309523809523809, 0.5444444444444444, 0.7, 0.4416666666666667, 1.0, 0.74, 0.4714285714285715, 0.5708333333333333, 0.4625, 0.403030303030303, 0.3, 0.49350649350649345, 0.55, 0.54, 0.5212878787878789, 0.4776190476190476, 0.5333333333333333, 0.3991341991341992, 0.38, 0.44226190476190474, 0.41875, 0.0, 0.7173809523809523, 0.8, 0.4666666666666666, 0.75, 0.6119047619047618, 0.7166666666666667, 0.4413888888888889, 0.38888888888888884, 0.0, 0.0, 0.6416666666666666, 0.24062500000000003, 0.519047619047619, 0.5611111111111111, 0.42500000000000004, 1.0, 0.5916666666666667, 0.375, 0.4666666666666666, 0.5678571428571428, 0.6116666666666666, 0.3555555555555556, 0.5125, 0.6200000000000001, 0.2, 0.5483333333333333, 0.8000000000000002, 0.50625, 0.44523809523809516, 0.038461538461538464, 0.75, 0.3666666666666667, 0.53, 0.6166666666666666, 0.4842857142857144, 0.34722222222222215, 0.6311111111111111, 0.6271428571428571, 0.55, 0.725, 0.5875, 0.38333333333333336, 0.43124999999999997, 0.5666666666666667, 0.55, 0.47000000000000003, 0.6166666666666667, 0.0, 0.4777777777777778, 0.4, 0.6111111111111112, 0.4464896214896215, 0.31805555555555554, 0.5958333333333333, 0.5875, 0.49023809523809525, 0.59375, 0.5178654678654678, 0.44999999999999996, 0.37, 0.6, 0.666, 0.5055555555555555, 0.25, 0.625, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5081249999999999, 0.475, 0.5576719576719577, 0.42500000000000004, 0.875, 0.5875, 0.0, 0.48750000000000004, 0.45749999999999996, 0.7166666666666666, 0.48055555555555557, 0.6666666666666666, 0.5625, 0.5133333333333333, 0.6952380952380953, 0.48, 0.825, 0.3273809523809524, 0.5597222222222222, 0.7825, 0.75, 0.85, 0.75, 0.875, 0.47750000000000004, 0.60625, 0.2, 0.6099999999999999, 0.2, 0.6536931818181818, 0.5819444444444445, 0.38499999999999995, 0.7226666666666667, 0.616, 0.6728571428571429, 0.6333333333333334, 0.3333333333333333, 0.5089743589743589, 0.19999999999999998, 0.525, 0.46106519742883373, 0.6375000000000001, 0.4, 0.5404040404040403, 0.47346938775510206, 0.65, 0.43000000000000005, 0.8, 0.4625, 0.5444444444444445, 0.5375, 0.0625, 0.6333333333333333, 0.55, 0.7, 0.4604166666666667, 0.5062500000000001, 0.5933333333333334, 0.6043181818181819, 0.5610317460317461, 0.45625000000000004, 0.32962962962962966, 0.5888888888888889, 0.7625, 0.4433677685950413, 1.0, 0.725, 0.5535714285714285, 0.5194444444444445, 0.616, 0.5416666666666666, 0.55, 0.7178571428571429, 0.4577380952380952, 0.5052380952380953, 0.7416666666666667, 0.6694444444444444, 0.6, 0.5, 0.4768518518518518, 0.5666666666666668, 0.4222222222222222, 0.6166666666666667, 0.8500000000000001, 0.5535714285714286, 0.5304166666666668, 0.44375, 0.5756190476190477, 0.6277777777777778, 0.5166666666666666, 0.35, 0.6933333333333334, 0.15151515151515152, 0.6000000000000001, 0.585, 0.5055555555555555, 0.6, 0.5433333333333333, 0.4583333333333333, 0.5419642857142857, 0.4962962962962963, 0.6642857142857144, 0.36250000000000004, 0.6321428571428572, 0.4083333333333334, 0.4166666666666667, 0.76, 0.5198412698412699, 0.4666666666666667, 0.5208333333333334, 0.5583333333333333, 0.4714285714285715, 0.575, 0.625, 0.6733333333333333, 0.825, 0.5555555555555555, 0.6449999999999999, 0.6075396825396825, 0.5162337662337663, 0.43600000000000005, 0.77, 0.48750000000000004, 0.4333333333333333, 0.5, 0.41500000000000004, 0.5, 0.4158008658008658, 0.5499999999999999, 0.4577777777777778, 0.515, 0.6515151515151515, 0.32, 0.6, 0.75, 0.4988111888111888, 0.4888888888888889, 0.5416666666666666, 0.7638888888888888, 0.5183333333333333, 0.5, 0.2, 0.38055555555555554, 0.5459876543209877, 0.645, 0.7666666666666666, 0.5, 0.18055555555555555, 0.7333333333333334, 0.3354166666666667, 0.84375, 0.6085714285714287, 0.48333333333333334, 0.4352083333333333, 0.48500000000000004, 0.85, 0.65, 0.36666666666666664, 0.66, 0.6125, 0.63, 0.5113636363636364, 0.5, 0.5625, 0.5071969696969697, 0.325, 0.6363636363636364, 0.6, 0.6, 0.31666666666666665, 0.675, 0.6283333333333333, 0.9444444444444444, 0.6375, 0.75, 0.5166666666666667, 0.5625, 0.5, 0.32999999999999996, 0.5625, 0.4129629629629629, 0.475, 0.41666666666666663, 0.7083333333333334, 0.8333333333333334, 0.65, 0.0, 0.5202380952380953, 0.4666666666666666, 0.6458333333333333, 0.775, 0.6531746031746033, 0.7083333333333334, 0.6124999999999999, 0.7208333333333333, 0.6000000000000001, 0.43863636363636366, 0.38055555555555554, 1.0, 0.52, 0.48484848484848486, 0.83, 0.5763888888888888, 0.7178571428571429, 0.6041005291005291, 0.58, 0.5773275058275058, 0.625, 0.3428571428571429, 0.45, 0.45777777777777773, 0.5119047619047619, 0.5, 0.5691183261183261, 0.6, 0.3125, 0.25, 0.5773809523809524, 0.2899350649350649, 0.5, 0.425, 0.6400000000000001, 0.275, 0.4166666666666667, 0.26944444444444443, 0.6803030303030303, 0.6166666666666667, 0.32777777777777783, 0.5549999999999999, 0.4, 0.43750000000000006, 0.3910353535353535, 0.6875, 0.5272727272727273, 0.5360805860805861, 0.44666666666666666, 0.43333333333333335, 0.8, 0.7296296296296297, 0.8035714285714286, 0.5, 0.0, 0.35151515151515156, 0.5700000000000001, 0.7666666666666666, 0.60625, 0.45333333333333337, 0.4944444444444444, 0.8265432098765433, 0.7095238095238096, 0.7178571428571429, 0.5125541125541125, 0.7833333333333332, 0.4129629629629629, 0.6076388888888888, 0.65, 1.0, 0.6399999999999999, 0.5136363636363637, 0.4515151515151515, 0.5255892255892256, 0.53, 0.4682539682539683, 0.67, 0.75, 0.41090909090909095, 0.4972222222222223, 0.8472222222222222, 0.0, 0.325, 0.125, 0.6035714285714286, 0.5708333333333333, 0.5, 0.7111111111111112, 0.7069444444444445, 0.4152777777777778, 0.55, 0.7902777777777779, 0.375, 0.41333333333333333, 0.365, 0.42523809523809525, 0.21785714285714286, 0.725, 0.1, 0.325, 0.48333333333333334, 0.6483333333333333, 0.0, 0.7833333333333333, 0.5833333333333334, 0.32765151515151514, 0.645, 0.6291666666666667, 0.2633333333333333, 0.7000000000000001, 0.4, 0.0, 1.0, 0.4859848484848485, 0.5333333333333333, 0.4409090909090909, 0.3444444444444444, 0.5083333333333333, 0.4666666666666666, 0.0, 0.3208333333333333, 0.45, 0.5666666666666667, 0.5666666666666667, 0.3333333333333333, 0.5214285714285715, 0.5999999999999999, 0.5260416666666667, 0.43, 0.5626984126984127, 0.4600000000000001, 0.3833333333333333, 0.3875, 0.35, 0.525, 0.6220097803431137, 0.75, 0.5642857142857143, 0.75, 0.680952380952381, 0.6444444444444445, 0.6, 0.44000000000000006, 0.3666666666666667, 0.5700000000000001, 0.5916666666666666, 0.6, 0.49523809523809526, 0.5095238095238096, 0.7238095238095239, 0.45999999999999996, 0.3875, 0.5833333333333334, 0.8266666666666665, 0.3, 0.35000000000000003, 0.65, 0.2541666666666667, 0.4181818181818182, 0.4711111111111111, 0.5428571428571428, 0.555, 0.65, 0.4416666666666667, 0.0, 0.46666666666666673, 0.81875, 0.5471153846153847, 0.5603846153846155, 0.4765476190476191, 0.4743620414673046, 0.6516666666666667, 0.540922619047619, 0.44172839506172834, 0.63, 0.2333333333333333, 0.5285714285714286, 0.7225, 0.6571428571428571, 0.6, 0.45000000000000007, 0.39285714285714285, 0.6875, 0.6, 0.6583333333333333, 0.3743506493506494, 0.48, 0.5416666666666666, 0.575, 0.49399999999999994, 0.41057823129251697, 0.4166666666666667, 0.4166666666666667, 0.17500000000000002, 0.7916666666666667, 0.4563888888888889, 0.3427777777777778, 0.5773809523809523, 0.5819047619047619, 0.6472222222222223, 0.6277777777777778, 0.725, 0.39030612244897966, 0.46875, 0.6625000000000001, 0.29000000000000004, 0.6291666666666667, 0.55, 0.5709090909090909, 0.35555555555555557, 0.6107142857142858, 0.6227777777777778, 0.462, 0.5773809523809523, 0.503030303030303, 0.4561904761904761, 0.27999999999999997, 0.5066666666666667, 0.5262536075036075, 0.5, 0.4, 0.7638888888888888, 0.2888888888888889, 0.5791666666666667, 0.5983333333333334, 0.6130000000000001, 0.4166666666666667, 0.6916666666666665, 0.42000000000000004, 0.4666666666666666, 0.39999999999999997, 0.5986111111111111, 0.625, 0.615909090909091, 0.5593333333333332, 0.55, 0.5328571428571428, 0.6111888111888113, 0.37407407407407406, 0.6574603174603174, 0.3474431818181818, 0.6952380952380953, 0.39726890756302524, 0.8166666666666667, 0.9, 0.39999999999999997, 0.5272727272727272, 0.625, 0.6166666666666667, 0.5729166666666666, 0.49444444444444446, 0.5, 0.5666666666666667, 0.5256410256410257, 0.6666666666666666, 0.49374999999999997, 0.42142857142857143, 0.39749999999999996, 0.1923076923076923, 0.21666666666666665, 0.54375, 0.4982683982683983, 0.3666666666666667, 0.55, 0.0, 0.49487179487179483, 0.6000000000000001, 0.5216666666666667, 0.5607142857142858, 0.6333333333333333, 0.5166666666666667, 0.44583333333333336, 0.675, 0.55, 0.6520833333333333, 0.7113636363636363, 0.5321428571428571, 0.6100000000000001, 0.325, 0.5966666666666667, 0.5992857142857143, 0.40095238095238095, 0.5058823529411764, 0.5541666666666666, 0.67, 0.4, 0.5447619047619048, 0.4068181818181818, 0.5472222222222222, 0.27651515151515155, 0.6, 0.5666666666666667, 0.496875, 0.7114285714285715, 0.5083333333333334, 0.4927777777777777, 1.0, 0.8083333333333333, 0.75, 0.0, 0.5972222222222222, 0.5033333333333333, 0.5708333333333333, 0.39166666666666666, 0.41666666666666663, 0.3625, 0.0, 0.5850000000000001, 0.6386363636363637, 0.49673382173382163, 0.6866666666666668, 0.6708333333333333, 0.6333333333333332, 0.4, 0.7636363636363637, 0.3666666666666667, 0.3, 0.5, 0.48270202020202024, 0.5215909090909091, 0.65, 0.5616666666666666, 0.0, 0.35000000000000003, 0.35984848484848486, 0.7238095238095238, 0.575, 0.6080519480519481, 0.5166666666666666, 0.7680555555555556, 0.5375, 0.31666666666666665, 0.44831945831945835, 0.45454545454545453, 0.5809523809523809, 0.74, 0.9333333333333332, 0.58, 0.5, 0.4602020202020202, 0.515, 0.6156060606060607, 0.3833333333333333, 0.69375, 0.75, 0.4377777777777777, 0.0, 0.35151515151515156, 0.75, 0.45454545454545453, 0.255952380952381, 0.5333333333333333, 0.0, 0.39999999999999997, 0.6, 0.43333333333333335, 0.61, 0.6333333333333333, 0.776, 0.43726325757575757, 0.25000000000000006, 0.5625, 0.75, 0.39623015873015877, 0.7125, 0.475, 0.38, 0.66, 0.0, 0.48055555555555557, 0.5322314049586777, 0.5164646464646464, 0.46818181818181825, 0.29500000000000004, 0.752, 0.3333333333333333, 0.516, 0.9, 0.4000000000000001, 0.4649350649350649, 0.5333333333333333, 0.30388888888888893, 0.7000000000000001, 0.41125, 0.3525, 0.6014285714285714, 0.65, 0.47500000000000003, 0.7333333333333334, 0.44999999999999996, 0.44999999999999996, 0.43100000000000005, 0.5, 0.30833333333333335, 0.6625, 0.675, 0.6386363636363637, 0.2833333333333333, 0.0, 0.4800000000000001, 0.345, 0.65, 0.5761904761904761, 0.7000000000000001, 0.5625, 0.6392857142857143, 0.5208333333333334, 0.5104166666666666, 0.3339285714285714, 0.41571428571428576, 0.4166666666666667, 0.8, 0.34, 0.5800000000000001, 0.61875, 0.43333333333333335, 0.510909090909091, 0.56875, 0.7333333333333333, 0.590625, 0.30833333333333335, 0.6792207792207793, 0.4083333333333333, 0.4092857142857143, 1.0, 0.5041666666666667, 0.5625, 0.52, 1.0, 0.6714285714285715, 0.45, 0.56875, 0.7051851851851852, 0.7424242424242425, 0.5083333333333333, 0.75, 0.4893535353535353, 0.75625, 0.5333333333333333, 0.4470779220779221], "name": "subjectivity", "text": "", "line": {"color": "rgba(55, 128, 191, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}], {"legend": {"bgcolor": "#FFFFFF", "font": {"color": "#4D5663"}}, "paper_bgcolor": "#FFFFFF", "plot_bgcolor": "#FFFFFF", "yaxis1": {"tickfont": {"color": "#4D5663"}, "gridcolor": "#E1E5ED", "titlefont": {"color": "#4D5663"}, "zerolinecolor": "#E1E5ED", "showgrid": true, "title": "Values"}, "xaxis1": {"tickfont": {"color": "#4D5663"}, "gridcolor": "#E1E5ED", "titlefont": {"color": "#4D5663"}, "zerolinecolor": "#E1E5ED", "showgrid": true, "title": "Time"}, "titlefont": {"color": "#4D5663"}, "title": "Polarity and Subjectivity"}, {"showLink": true, "linkText": "Export to plot.ly"})});</script>



```python
AllData2[['polarity', 'subjectivity']].iplot(kind='scatter', 
                                           title='Polarity and Subjectivity', xTitle='Time',yTitle='Values')



```


<div id="437fb15f-3410-4dd2-96e4-30090861c179" style="height: 525px; width: 100%;" class="plotly-graph-div"></div><script type="text/javascript">require(["plotly"], function(Plotly) { window.PLOTLYENV=window.PLOTLYENV || {};window.PLOTLYENV.BASE_URL="https://plot.ly";Plotly.newPlot("437fb15f-3410-4dd2-96e4-30090861c179", [{"type": "scatter", "x": ["2012-01-30", "2012-02-02", "2012-02-09", "2012-02-24", "2012-02-24", "2012-02-28", "2012-02-29", "2012-03-01", "2012-03-06", "2012-03-06", "2012-03-07", "2012-03-10", "2012-03-16", "2012-03-17", "2012-03-21", "2012-03-23", "2012-03-23", "2012-03-26", "2012-03-26", "2012-03-27", "2012-03-27", "2012-03-27", "2012-03-28", "2012-03-30", "2012-04-02", "2012-04-10", "2012-04-11", "2012-04-12", "2012-04-17", "2012-04-25", "2012-04-25", "2012-04-27", "2012-04-27", "2012-04-30", "2012-04-30", "2012-05-01", "2012-05-03", "2012-05-04", "2012-05-06", "2012-05-08", "2012-05-08", "2012-05-08", "2012-05-09", "2012-05-09", "2012-05-09", "2012-05-10", "2012-05-15", "2012-05-22", "2012-05-22", "2012-05-23", "2012-05-24", "2012-06-04", "2012-06-06", "2012-06-10", "2012-06-13", "2012-06-19", "2012-06-21", "2012-06-22", "2012-06-25", "2012-06-26", "2012-06-28", "2012-07-01", "2012-07-01", "2012-07-02", "2012-07-06", "2012-07-09", "2012-07-11", "2012-07-12", "2012-07-12", "2012-07-14", "2012-07-15", "2012-07-17", "2012-07-17", "2012-07-18", "2012-07-22", "2012-07-24", "2012-07-24", "2012-07-25", "2012-07-27", "2012-07-27", "2012-08-02", "2012-08-02", "2012-08-02", "2012-08-03", "2012-08-06", "2012-08-07", "2012-08-10", "2012-08-13", "2012-08-14", "2012-08-16", "2012-08-17", "2012-08-19", "2012-08-20", "2012-08-21", "2012-08-21", "2012-08-22", "2012-08-24", "2012-08-27", "2012-09-04", "2012-09-05", "2012-09-10", "2012-09-11", "2012-09-15", "2012-09-17", "2012-09-17", "2012-09-17", "2012-09-18", "2012-09-20", "2012-09-23", "2012-09-26", "2012-09-26", "2012-09-27", "2012-09-28", "2012-10-01", "2012-10-02", "2012-10-03", "2012-10-03", "2012-10-08", "2012-10-09", "2012-10-09", "2012-10-13", "2012-10-13", "2012-10-14", "2012-10-14", "2012-10-15", "2012-10-17", "2012-10-17", "2012-10-20", "2012-10-21", "2012-10-22", "2012-10-23", "2012-10-23", "2012-10-28", "2012-10-29", "2012-10-29", "2012-10-30", "2012-10-30", "2012-10-30", "2012-10-30", "2012-10-31", "2012-11-07", "2012-11-07", "2012-11-08", "2012-11-08", "2012-11-10", "2012-11-13", "2012-11-14", "2012-11-16", "2012-11-16", "2012-11-18", "2012-11-24", "2012-11-26", "2012-11-29", "2012-12-03", "2012-12-03", "2012-12-06", "2012-12-08", "2012-12-11", "2012-12-12", "2012-12-12", "2012-12-16", "2012-12-17", "2012-12-21", "2012-12-26", "2012-12-30", "2012-12-30", "2013-01-04", "2013-01-05", "2013-01-07", "2013-01-08", "2013-01-15", "2013-01-15", "2013-01-16", "2013-01-17", "2013-01-17", "2013-01-18", "2013-01-20", "2013-01-22", "2013-01-22", "2013-01-25", "2013-01-27", "2013-01-27", "2013-01-27", "2013-01-29", "2013-01-30", "2013-02-01", "2013-02-01", "2013-02-01", "2013-02-03", "2013-02-04", "2013-02-05", "2013-02-05", "2013-02-06", "2013-02-06", "2013-02-06", "2013-02-07", "2013-02-12", "2013-02-12", "2013-02-15", "2013-02-15", "2013-02-15", "2013-02-21", "2013-02-22", "2013-02-23", "2013-02-25", "2013-02-25", "2013-02-26", "2013-02-27", "2013-02-28", "2013-03-02", "2013-03-02", "2013-03-04", "2013-03-04", "2013-03-05", "2013-03-05", "2013-03-06", "2013-03-10", "2013-03-11", "2013-03-11", "2013-03-14", "2013-03-19", "2013-03-19", "2013-03-20", "2013-03-20", "2013-03-25", "2013-03-25", "2013-03-25", "2013-03-27", "2013-03-27", "2013-03-29", "2013-04-02", "2013-04-02", "2013-04-05", "2013-04-05", "2013-04-05", "2013-04-09", "2013-04-09", "2013-04-10", "2013-04-11", "2013-04-11", "2013-04-12", "2013-04-12", "2013-04-13", "2013-04-14", "2013-04-17", "2013-04-18", "2013-04-18", "2013-04-21", "2013-04-22", "2013-04-23", "2013-04-23", "2013-04-23", "2013-04-24", "2013-04-25", "2013-04-26", "2013-04-29", "2013-04-29", "2013-04-29", "2013-04-30", "2013-05-01", "2013-05-09", "2013-05-09", "2013-05-09", "2013-05-09", "2013-05-13", "2013-05-16", "2013-05-19", "2013-05-22", "2013-05-28", "2013-05-29", "2013-05-29", "2013-06-01", "2013-06-03", "2013-06-04", "2013-06-04", "2013-06-07", "2013-06-08", "2013-06-08", "2013-06-10", "2013-06-11", "2013-06-15", "2013-06-17", "2013-06-18", "2013-06-22", "2013-06-23", "2013-06-24", "2013-06-25", "2013-06-26", "2013-06-26", "2013-06-26", "2013-06-28", "2013-06-29", "2013-07-01", "2013-07-05", "2013-07-06", "2013-07-08", "2013-07-08", "2013-07-10", "2013-07-12", "2013-07-12", "2013-07-14", "2013-07-15", "2013-07-15", "2013-07-16", "2013-07-17", "2013-07-17", "2013-07-18", "2013-07-19", "2013-07-19", "2013-07-22", "2013-07-23", "2013-07-24", "2013-07-25", "2013-07-27", "2013-07-28", "2013-07-29", "2013-07-29", "2013-07-30", "2013-08-03", "2013-08-03", "2013-08-06", "2013-08-06", "2013-08-07", "2013-08-07", "2013-08-08", "2013-08-09", "2013-08-10", "2013-08-13", "2013-08-15", "2013-08-16", "2013-08-16", "2013-08-16", "2013-08-20", "2013-08-20", "2013-08-21", "2013-08-26", "2013-08-27", "2013-08-27", "2013-08-28", "2013-08-28", "2013-08-29", "2013-08-30", "2013-08-30", "2013-09-01", "2013-09-02", "2013-09-02", "2013-09-03", "2013-09-03", "2013-09-03", "2013-09-03", "2013-09-06", "2013-09-06", "2013-09-06", "2013-09-07", "2013-09-09", "2013-09-09", "2013-09-10", "2013-09-10", "2013-09-11", "2013-09-11", "2013-09-13", "2013-09-14", "2013-09-18", "2013-09-18", "2013-09-19", "2013-09-20", "2013-09-23", "2013-09-23", "2013-09-24", "2013-09-27", "2013-09-28", "2013-10-01", "2013-10-01", "2013-10-02", "2013-10-03", "2013-10-06", "2013-10-08", "2013-10-08", "2013-10-10", "2013-10-13", "2013-10-14", "2013-10-14", "2013-10-14", "2013-10-16", "2013-10-16", "2013-10-17", "2013-10-22", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-24", "2013-10-27", "2013-10-28", "2013-10-29", "2013-10-31", "2013-10-31", "2013-11-03", "2013-11-04", "2013-11-04", "2013-11-05", "2013-11-06", "2013-11-07", "2013-11-07", "2013-11-08", "2013-11-14", "2013-11-14", "2013-11-15", "2013-11-17", "2013-11-17", "2013-11-18", "2013-11-20", "2013-11-22", "2013-11-22", "2013-12-01", "2013-12-02", "2013-12-03", "2013-12-04", "2013-12-04", "2013-12-04", "2013-12-09", "2013-12-10", "2013-12-10", "2013-12-10", "2013-12-11", "2013-12-16", "2013-12-16", "2013-12-17", "2013-12-18", "2013-12-21", "2013-12-21", "2013-12-23", "2013-12-23", "2013-12-26", "2013-12-27", "2013-12-31", "2014-01-05", "2014-01-05", "2014-01-05", "2014-01-08", "2014-01-09", "2014-01-10", "2014-01-12", "2014-01-14", "2014-01-16", "2014-01-17", "2014-01-20", "2014-01-20", "2014-01-20", "2014-01-21", "2014-01-21", "2014-01-23", "2014-01-25", "2014-01-27", "2014-01-28", "2014-01-28", "2014-01-29", "2014-01-29", "2014-01-31", "2014-01-31", "2014-02-02", "2014-02-03", "2014-02-04", "2014-02-05", "2014-02-05", "2014-02-06", "2014-02-06", "2014-02-12", "2014-02-13", "2014-02-15", "2014-02-17", "2014-02-18", "2014-02-19", "2014-02-21", "2014-02-25", "2014-02-25", "2014-02-25", "2014-02-27", "2014-02-27", "2014-02-28", "2014-03-02", "2014-03-03", "2014-03-05", "2014-03-05", "2014-03-09", "2014-03-12", "2014-03-12", "2014-03-16", "2014-03-19", "2014-03-19", "2014-03-22", "2014-03-23", "2014-03-26", "2014-03-27", "2014-03-28", "2014-03-29", "2014-03-31", "2014-03-31", "2014-03-31", "2014-04-01", "2014-04-02", "2014-04-03", "2014-04-06", "2014-04-07", "2014-04-08", "2014-04-09", "2014-04-10", "2014-04-15", "2014-04-16", "2014-04-16", "2014-04-16", "2014-04-17", "2014-04-18", "2014-04-24", "2014-04-24", "2014-05-02", "2014-05-05", "2014-05-05", "2014-05-07", "2014-05-07", "2014-05-09", "2014-05-09", "2014-05-10", "2014-05-14", "2014-05-15", "2014-05-15", "2014-05-16", "2014-05-16", "2014-05-20", "2014-05-21", "2014-05-21", "2014-05-23", "2014-05-23", "2014-05-24", "2014-05-27", "2014-05-27", "2014-05-27", "2014-05-29", "2014-06-02", "2014-06-03", "2014-06-04", "2014-06-05", "2014-06-06", "2014-06-06", "2014-06-09", "2014-06-14", "2014-06-16", "2014-06-17", "2014-06-19", "2014-06-19", "2014-06-20", "2014-06-20", "2014-06-20", "2014-06-22", "2014-06-23", "2014-06-23", "2014-06-23", "2014-06-24", "2014-06-24", "2014-06-25", "2014-06-28", "2014-06-29", "2014-06-30", "2014-07-01", "2014-07-02", "2014-07-07", "2014-07-08", "2014-07-11", "2014-07-11", "2014-07-12", "2014-07-13", "2014-07-14", "2014-07-16", "2014-07-16", "2014-07-17", "2014-07-20", "2014-07-21", "2014-07-22", "2014-07-22", "2014-07-23", "2014-07-23", "2014-07-23", "2014-07-25", "2014-07-25", "2014-07-25", "2014-07-27", "2014-07-28", "2014-07-30", "2014-07-31", "2014-08-04", "2014-08-05", "2014-08-05", "2014-08-09", "2014-08-11", "2014-08-12", "2014-08-13", "2014-08-14", "2014-08-14", "2014-08-15", "2014-08-17", "2014-08-18", "2014-08-18", "2014-08-18", "2014-08-23", "2014-08-26", "2014-08-26", "2014-08-27", "2014-08-29", "2014-08-30", "2014-08-30", "2014-08-31", "2014-09-02", "2014-09-03", "2014-09-03", "2014-09-04", "2014-09-05", "2014-09-06", "2014-09-07", "2014-09-08", "2014-09-09", "2014-09-11", "2014-09-12", "2014-09-12", "2014-09-12", "2014-09-12", "2014-09-15", "2014-09-16", "2014-09-16", "2014-09-17", "2014-09-18", "2014-09-19", "2014-09-19", "2014-09-19", "2014-09-21", "2014-09-22", "2014-09-22", "2014-09-23", "2014-09-27", "2014-09-27", "2014-09-29", "2014-09-30", "2014-10-01", "2014-10-02", "2014-10-04", "2014-10-04", "2014-10-06", "2014-10-07", "2014-10-07", "2014-10-08", "2014-10-12", "2014-10-12", "2014-10-13", "2014-10-14", "2014-10-15", "2014-10-16", "2014-10-18", "2014-10-19", "2014-10-20", "2014-10-20", "2014-10-21", "2014-10-21", "2014-10-22", "2014-10-22", "2014-10-23", "2014-10-23", "2014-10-25", "2014-10-27", "2014-10-27", "2014-10-29", "2014-10-30", "2014-10-30", "2014-10-31", "2014-11-03", "2014-11-04", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-19", "2014-11-20", "2014-11-21", "2014-11-22", "2014-11-24", "2014-11-24", "2014-11-24", "2014-11-26", "2014-11-30", "2014-12-01", "2014-12-01", "2014-12-02", "2014-12-03", "2014-12-04", "2014-12-04", "2014-12-05", "2014-12-06", "2014-12-08", "2014-12-08", "2014-12-11", "2014-12-16", "2014-12-17", "2014-12-19", "2014-12-23", "2014-12-26", "2014-12-26", "2014-12-26", "2014-12-27", "2014-12-27", "2014-12-27", "2014-12-29", "2014-12-29", "2014-12-30", "2015-01-01", "2015-01-01", "2015-01-01", "2015-01-02", "2015-01-05", "2015-01-05", "2015-01-05", "2015-01-06", "2015-01-06", "2015-01-07", "2015-01-07", "2015-01-09", "2015-01-10", "2015-01-10", "2015-01-10", "2015-01-11", "2015-01-11", "2015-01-12", "2015-01-12", "2015-01-13", "2015-01-14", "2015-01-15", "2015-01-18", "2015-01-18", "2015-01-19", "2015-01-19", "2015-01-19", "2015-01-19", "2015-01-21", "2015-01-21", "2015-01-23", "2015-01-25", "2015-01-28", "2015-01-28", "2015-01-29", "2015-02-01", "2015-02-02", "2015-02-04", "2015-02-05", "2015-02-05", "2015-02-06", "2015-02-07", "2015-02-09", "2015-02-10", "2015-02-12", "2015-02-13", "2015-02-14", "2015-02-15", "2015-02-17", "2015-02-19", "2015-02-20", "2015-02-23", "2015-02-23", "2015-02-23", "2015-02-24", "2015-02-24", "2015-02-24", "2015-02-26", "2015-02-26", "2015-02-26", "2015-02-26", "2015-02-27", "2015-02-28", "2015-02-28", "2015-02-28", "2015-03-01", "2015-03-03", "2015-03-03", "2015-03-04", "2015-03-04", "2015-03-08", "2015-03-09", "2015-03-10", "2015-03-10", "2015-03-11", "2015-03-11", "2015-03-11", "2015-03-11", "2015-03-13", "2015-03-16", "2015-03-16", "2015-03-17", "2015-03-18", "2015-03-29", "2015-03-31", "2015-03-31", "2015-04-01", "2015-04-05", "2015-04-06", "2015-04-06", "2015-04-07", "2015-04-07", "2015-04-07", "2015-04-08", "2015-04-08", "2015-04-09", "2015-04-09", "2015-04-10", "2015-04-12", "2015-04-12", "2015-04-14", "2015-04-16", "2015-04-17", "2015-04-21", "2015-04-22", "2015-04-23", "2015-04-23", "2015-04-24", "2015-04-25", "2015-04-30", "2015-05-01", "2015-05-01", "2015-05-07", "2015-05-07", "2015-05-10", "2015-05-11", "2015-05-13", "2015-05-13", "2015-05-14", "2015-05-15", "2015-05-18", "2015-05-21", "2015-05-21", "2015-05-21", "2015-05-22", "2015-05-22", "2015-05-25", "2015-05-28", "2015-05-29", "2015-05-29", "2015-05-30", "2015-06-02", "2015-06-04", "2015-06-04", "2015-06-05", "2015-06-06", "2015-06-08", "2015-06-08", "2015-06-08", "2015-06-10", "2015-06-15", "2015-06-16", "2015-06-17", "2015-06-17", "2015-06-20", "2015-06-24", "2015-06-26", "2015-06-26", "2015-06-27", "2015-06-27", "2015-06-30", "2015-07-03", "2015-07-03", "2015-07-06", "2015-07-07", "2015-07-08", "2015-07-08", "2015-07-13", "2015-07-14", "2015-07-14", "2015-07-14", "2015-07-15", "2015-07-16", "2015-07-16", "2015-07-17", "2015-07-21", "2015-07-21", "2015-07-22", "2015-07-23", "2015-07-23", "2015-07-24", "2015-07-27", "2015-07-28", "2015-07-29", "2015-07-29", "2015-07-29", "2015-07-30", "2015-07-31", "2015-08-02", "2015-08-02", "2015-08-02", "2015-08-02", "2015-08-03", "2015-08-05", "2015-08-06", "2015-08-06", "2015-08-09", "2015-08-09", "2015-08-10", "2015-08-11", "2015-08-12", "2015-08-12", "2015-08-15", "2015-08-18", "2015-08-18", "2015-08-19", "2015-08-20", "2015-08-21", "2015-08-21", "2015-08-24", "2015-08-25", "2015-08-27", "2015-08-27", "2015-09-02", "2015-09-03", "2015-09-03", "2015-09-06", "2015-09-08", "2015-09-09", "2015-09-10", "2015-09-10", "2015-09-11", "2015-09-14", "2015-09-14", "2015-09-15", "2015-09-15", "2015-09-16", "2015-09-17", "2015-09-19", "2015-09-21", "2015-09-21", "2015-09-22", "2015-09-23", "2015-09-24", "2015-09-28", "2015-09-29", "2015-09-30", "2015-09-30", "2015-09-30", "2015-10-02", "2015-10-05", "2015-10-05", "2015-10-05", "2015-10-05", "2015-10-06", "2015-10-08", "2015-10-10", "2015-10-10", "2015-10-12", "2015-10-12", "2015-10-12", "2015-10-13", "2015-10-13", "2015-10-14", "2015-10-14", "2015-10-15", "2015-10-16", "2015-10-18", "2015-10-18", "2015-10-19", "2015-10-19", "2015-10-19", "2015-10-21", "2015-10-21", "2015-10-21", "2015-10-22", "2015-10-22", "2015-10-23", "2015-10-24", "2015-10-26", "2015-10-26", "2015-10-29", "2015-10-29", "2015-10-29", "2015-11-02", "2015-11-03", "2015-11-04", "2015-11-04", "2015-11-06", "2015-11-09", "2015-11-10", "2015-11-10", "2015-11-11", "2015-11-18", "2015-11-18", "2015-11-19", "2015-11-20", "2015-11-24", "2015-11-26", "2015-12-01", "2015-12-02", "2015-12-05", "2015-12-08", "2015-12-10", "2015-12-14", "2015-12-24", "2015-12-31", "2016-01-06", "2016-01-08", "2016-01-08", "2016-01-11", "2016-01-16", "2016-01-18", "2016-01-19", "2016-01-20", "2016-01-22", "2016-01-25", "2016-01-26", "2016-01-28", "2016-01-29", "2016-02-01", "2016-02-01", "2016-02-02", "2016-02-03", "2016-02-05", "2016-02-05", "2016-02-06", "2016-02-09", "2016-02-11", "2016-02-12", "2016-02-13", "2016-02-22", "2016-02-24", "2016-02-24", "2016-02-25", "2016-02-26", "2016-03-03", "2016-03-04", "2016-03-05", "2016-03-06", "2016-03-08", "2016-03-09", "2016-03-11", "2016-03-14", "2016-03-14", "2016-03-15", "2016-03-18", "2016-03-22", "2016-03-23", "2016-03-24", "2016-03-27", "2016-03-28", "2016-04-05", "2016-04-06", "2016-04-08", "2016-04-10", "2016-04-12", "2016-04-14", "2016-04-14", "2016-04-14", "2016-04-17", "2016-04-20", "2016-04-21", "2016-04-21", "2016-04-23", "2016-04-24", "2016-05-01", "2016-05-01", "2016-05-02", "2016-05-04", "2016-05-04", "2016-05-07", "2016-05-09", "2016-05-10", "2016-05-10", "2016-05-15", "2016-05-16", "2016-05-18", "2016-05-19", "2016-05-20", "2016-05-21", "2016-05-21", "2016-05-27", "2016-06-02", "2016-06-02", "2016-06-04", "2016-06-04", "2016-06-06", "2016-06-08", "2016-06-11", "2016-06-13", "2016-06-15", "2016-06-24", "2016-06-27", "2016-06-28", "2016-06-29", "2016-07-01", "2016-07-01", "2016-07-03", "2016-07-03", "2016-07-06", "2016-07-07", "2016-07-07", "2016-07-09", "2016-07-11", "2016-07-12", "2016-07-13", "2016-07-14", "2016-07-15", "2016-07-16", "2016-07-19", "2016-07-24", "2016-07-29", "2016-07-30", "2016-07-31", "2016-08-02", "2016-08-04", "2016-08-08", "2016-08-09", "2016-08-09", "2016-08-11", "2016-08-12", "2016-08-14", "2016-08-15", "2016-08-16", "2016-08-16", "2016-08-19", "2016-08-19", "2016-08-23", "2016-08-23", "2016-08-28", "2016-08-31", "2016-09-01", "2016-09-03", "2016-09-03", "2016-09-04", "2016-09-05", "2016-09-07", "2016-09-09", "2016-09-09", "2016-09-13", "2016-09-15", "2016-09-18", "2016-09-21", "2016-09-26", "2016-09-27", "2016-09-27", "2016-09-28", "2016-09-30", "2016-10-03", "2016-10-03", "2016-10-03", "2016-10-04", "2016-10-04", "2016-10-04", "2016-10-06", "2016-10-07", "2016-10-07", "2016-10-07", "2016-10-11", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-13", "2016-10-14", "2016-10-17", "2016-10-19", "2016-10-19", "2016-10-21", "2016-10-21", "2016-10-21", "2016-10-23", "2016-10-23", "2016-10-23", "2016-10-24", "2016-10-24", "2016-10-25", "2016-10-26", "2016-10-30", "2016-10-30", "2016-10-30", "2016-10-31", "2016-10-31", "2016-11-02", "2016-11-02", "2016-11-03", "2016-11-09", "2016-11-09", "2016-11-10", "2016-11-13", "2016-11-14", "2016-11-15", "2016-11-19", "2016-11-23", "2016-11-25", "2016-11-27", "2016-11-28", "2016-11-30", "2016-12-01", "2016-12-04", "2016-12-07", "2016-12-07", "2016-12-11", "2016-12-11", "2016-12-12", "2016-12-14", "2016-12-14", "2016-12-14", "2016-12-15", "2016-12-15", "2016-12-16", "2016-12-19", "2016-12-21", "2016-12-21", "2016-12-24", "2016-12-27", "2016-12-28", "2016-12-31", "2017-01-02", "2017-01-02", "2017-01-02", "2017-01-02", "2017-01-03", "2017-01-04", "2017-01-04", "2017-01-04", "2017-01-06", "2017-01-08", "2017-01-09", "2017-01-09", "2017-01-10", "2017-01-10", "2017-01-10", "2017-01-10", "2017-01-11", "2017-01-16", "2017-01-18", "2017-01-19", "2017-01-21", "2017-01-22", "2017-01-22", "2017-01-23", "2017-01-23", "2017-01-23", "2017-01-25", "2017-01-26", "2017-01-27", "2017-01-27", "2017-01-27", "2017-01-28", "2017-01-29", "2017-01-30", "2017-01-31", "2017-01-31", "2017-02-02", "2017-02-05", "2017-02-05", "2017-02-07", "2017-02-08", "2017-02-09", "2017-02-09", "2017-02-10", "2017-02-11", "2017-02-11", "2017-02-13", "2017-02-13", "2017-02-16", "2017-02-17", "2017-02-21", "2017-02-22", "2017-02-23", "2017-02-24", "2017-02-25", "2017-02-27", "2017-02-28", "2017-02-28", "2017-02-28", "2017-03-01", "2017-03-01", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-03", "2017-03-05", "2017-03-06", "2017-03-06", "2017-03-07", "2017-03-07", "2017-03-10", "2017-03-10", "2017-03-12", "2017-03-12", "2017-03-15", "2017-03-16", "2017-03-16", "2017-03-18", "2017-03-18", "2017-03-19", "2017-03-19", "2017-03-20", "2017-03-21", "2017-03-21", "2017-03-22", "2017-03-23", "2017-03-24", "2017-03-24", "2017-03-26", "2017-03-26", "2017-03-26", "2017-03-26", "2017-03-27", "2017-03-28", "2017-03-29", "2017-03-30", "2017-03-30", "2017-03-31", "2017-04-01", "2017-04-01", "2017-04-02", "2017-04-03", "2017-04-04", "2017-04-05", "2017-04-05", "2017-04-05", "2017-04-06", "2017-04-07", "2017-04-08", "2017-04-09", "2017-04-10", "2017-04-11", "2017-04-12", "2017-04-12", "2017-04-13", "2017-04-15", "2017-04-17", "2017-04-17", "2017-04-18", "2017-04-18", "2017-04-19", "2017-04-20", "2017-04-20", "2017-04-21", "2017-04-24", "2017-04-25", "2017-04-25", "2017-04-27", "2017-04-28", "2017-04-28", "2017-04-29", "2017-04-29", "2017-04-30", "2017-05-02", "2017-05-02", "2017-05-02", "2017-05-05", "2017-05-06", "2017-05-06", "2017-05-07", "2017-05-07", "2017-05-07", "2017-05-08", "2017-05-08", "2017-05-09", "2017-05-09", "2017-05-09", "2017-05-09", "2017-05-10", "2017-05-11", "2017-05-11", "2017-05-11", "2017-05-13", "2017-05-15", "2017-05-15", "2017-05-15", "2017-05-16", "2017-05-16", "2017-05-16", "2017-05-16", "2017-05-18", "2017-05-19", "2017-05-20", "2017-05-21", "2017-05-21", "2017-05-21", "2017-05-22", "2017-05-22", "2017-05-22", "2017-05-23", "2017-05-24", "2017-05-24", "2017-05-29", "2017-05-31", "2017-05-31", "2017-06-01", "2017-06-01", "2017-06-02", "2017-06-03", "2017-06-05", "2017-06-06", "2017-06-07", "2017-06-07", "2017-06-07", "2017-06-07", "2017-06-08", "2017-06-08", "2017-06-10", "2017-06-11", "2017-06-11", "2017-06-13", "2017-06-13", "2017-06-13", "2017-06-15", "2017-06-15", "2017-06-15", "2017-06-16", "2017-06-16", "2017-06-18", "2017-06-20", "2017-06-20", "2017-06-21", "2017-06-22", "2017-06-22", "2017-06-24", "2017-06-27", "2017-06-28", "2017-06-28", "2017-06-30", "2017-07-05", "2017-07-05", "2017-07-07", "2017-07-08", "2017-07-10", "2017-07-10", "2017-07-11", "2017-07-11", "2017-07-12", "2017-07-13", "2017-07-14", "2017-07-15", "2017-07-17", "2017-07-17", "2017-07-17", "2017-07-17", "2017-07-18", "2017-07-18", "2017-07-18", "2017-07-19", "2017-07-19", "2017-07-20", "2017-07-20", "2017-07-20", "2017-07-22", "2017-07-23", "2017-07-24", "2017-07-24", "2017-07-25", "2017-07-25", "2017-07-27", "2017-07-27", "2017-07-28", "2017-07-30", "2017-07-31", "2017-07-31", "2017-08-01", "2017-08-01", "2017-08-04", "2017-08-05", "2017-08-06", "2017-08-06", "2017-08-07", "2017-08-07", "2017-08-09", "2017-08-09", "2017-08-09", "2017-08-10", "2017-08-14", "2017-08-14", "2017-08-15", "2017-08-15", "2017-08-16", "2017-08-17", "2017-08-17", "2017-08-17", "2017-08-19", "2017-08-21", "2017-08-21", "2017-08-21", "2017-08-22", "2017-08-22", "2017-08-24", "2017-08-24", "2017-08-25", "2017-08-27", "2017-08-28", "2017-08-28", "2017-08-29", "2017-08-31", "2017-08-31", "2017-09-01", "2017-09-03", "2017-09-04", "2017-09-05", "2017-09-05", "2017-09-06", "2017-09-06", "2017-09-06", "2017-09-07", "2017-09-07", "2017-09-07", "2017-09-08", "2017-09-09", "2017-09-11", "2017-09-11", "2017-09-11", "2017-09-12", "2017-09-13", "2017-09-13", "2017-09-16", "2017-09-18", "2017-09-18", "2017-09-20", "2017-09-21", "2017-09-21", "2017-09-21", "2017-09-22", "2017-09-22", "2017-09-24", "2017-09-26", "2017-09-26", "2017-09-27", "2017-09-28", "2017-09-28", "2017-09-29", "2017-09-29", "2017-09-30", "2017-10-02", "2017-10-03", "2017-10-03", "2017-10-03", "2017-10-04", "2017-10-05", "2017-10-06", "2017-10-07", "2017-10-07", "2017-10-09", "2017-10-09", "2017-10-10", "2017-10-11", "2017-10-12", "2017-10-12", "2017-10-13", "2017-10-13", "2017-10-17", "2017-10-17", "2017-10-18", "2017-10-19", "2017-10-20", "2017-10-21", "2017-10-24", "2017-10-24", "2017-10-27", "2017-10-27", "2017-10-28", "2017-10-29", "2017-10-30", "2017-10-31", "2017-10-31", "2017-10-31", "2017-11-01", "2017-11-01", "2017-11-03", "2017-11-04", "2017-11-06", "2017-11-06", "2017-11-07", "2017-11-07", "2017-11-07", "2017-11-08", "2017-11-10", "2017-11-12", "2017-11-13", "2017-11-14", "2017-11-14", "2017-11-14", "2017-11-15", "2017-11-16", "2017-11-17", "2017-11-19", "2017-11-19", "2017-11-20", "2017-11-20", "2017-11-24", "2017-11-25", "2017-11-26", "2017-11-26", "2017-11-27", "2017-11-27", "2017-11-27", "2017-12-01", "2017-12-01", "2017-12-03", "2017-12-04", "2017-12-04", "2017-12-05", "2017-12-05", "2017-12-06", "2017-12-08", "2017-12-10", "2017-12-12", "2017-12-12", "2017-12-13", "2017-12-15", "2017-12-17", "2017-12-19", "2017-12-20", "2017-12-20", "2017-12-20", "2017-12-21", "2017-12-26", "2017-12-29", "2017-12-29", "2018-01-02", "2018-01-02", "2018-01-03", "2018-01-03", "2018-01-04", "2018-01-04", "2018-01-06", "2018-01-06", "2018-01-06", "2018-01-07", "2018-01-08", "2018-01-09", "2018-01-10", "2018-01-10", "2018-01-10", "2018-01-11", "2018-01-11", "2018-01-12", "2018-01-14", "2018-01-15", "2018-01-15", "2018-01-15", "2018-01-15", "2018-01-16", "2018-01-18", "2018-01-19", "2018-01-19", "2018-01-19", "2018-01-20", "2018-01-22", "2018-01-22", "2018-01-23", "2018-01-23", "2018-01-24", "2018-01-24", "2018-01-24", "2018-01-27", "2018-01-28", "2018-01-30", "2018-01-30", "2018-01-30", "2018-01-31", "2018-01-31", "2018-01-31", "2018-02-01", "2018-02-02", "2018-02-03", "2018-02-03", "2018-02-04", "2018-02-04", "2018-02-05", "2018-02-06", "2018-02-06", "2018-02-06", "2018-02-08", "2018-02-09", "2018-02-10", "2018-02-11", "2018-02-12", "2018-02-13", "2018-02-15", "2018-02-16", "2018-02-16", "2018-02-16", "2018-02-18", "2018-02-20", "2018-02-23", "2018-02-24", "2018-02-27", "2018-02-27", "2018-03-02", "2018-03-02", "2018-03-04", "2018-03-06", "2018-03-06", "2018-03-07", "2018-03-08", "2018-03-08", "2018-03-08", "2018-03-08", "2018-03-10", "2018-03-11", "2018-03-11", "2018-03-14", "2018-03-14", "2018-03-15", "2018-03-18", "2018-03-19", "2018-03-19", "2018-03-19", "2018-03-20", "2018-03-20", "2018-03-20", "2018-03-20", "2018-03-21", "2018-03-22", "2018-03-26", "2018-03-26", "2018-03-26", "2018-03-27", "2018-03-27", "2018-03-27", "2018-03-28", "2018-03-28", "2018-03-30", "2018-03-31", "2018-04-01", "2018-04-03", "2018-04-03", "2018-04-04", "2018-04-04", "2018-04-05", "2018-04-05", "2018-04-07", "2018-04-09", "2018-04-09", "2018-04-11", "2018-04-12", "2018-04-12", "2018-04-13", "2018-04-14", "2018-04-15", "2018-04-16", "2018-04-17", "2018-04-17", "2018-04-18", "2018-04-23", "2018-04-24", "2018-04-26", "2018-04-27", "2018-04-27", "2018-04-30", "2018-05-01", "2018-05-02", "2018-05-02", "2018-05-03", "2018-05-05", "2018-05-05", "2018-05-07", "2018-05-07", "2018-05-07", "2018-05-08", "2018-05-08", "2018-05-08", "2018-05-08", "2018-05-09", "2018-05-11", "2018-05-11", "2018-05-12", "2018-05-15", "2018-05-16", "2018-05-16", "2018-05-18", "2018-05-19", "2018-05-19", "2018-05-22", "2018-05-23", "2018-05-27", "2018-05-27", "2018-05-31", "2018-05-31", "2018-06-02", "2018-06-04", "2018-06-05", "2018-06-05", "2018-06-05", "2018-06-06"], "y": [0.15, 0.27, 0.375, 5.551115123125783e-17, 5.551115123125783e-17, 0.31174242424242427, 0.5, 0.1, 0.31, 0.010000000000000009, 0.04999999999999999, 0.6055555555555555, 0.0, -0.05, 0.55, 0.125, 0.8, 0.10119047619047619, 0.095, 0.37878787878787873, 0.45714285714285713, 0.3333333333333333, 0.125, -0.3201388888888889, 0.38106060606060604, 0.4916666666666667, 0.5, 0.5549999999999999, 0.16845238095238096, 0.003409090909090907, 0.15277777777777776, 0.315, 0.27864145658263306, 0.18194444444444446, -0.14583333333333331, 0.337396694214876, 0.8, 0.0, 0.25, 0.20416666666666666, -0.06666666666666667, 0.75, 0.5166666666666666, 0.6775, 0.0537037037037037, 0.050000000000000044, 0.017424242424242425, 0.3588383838383838, 0.4366666666666666, -0.14444444444444443, 0.16282828282828282, 0.10625000000000001, 0.25, 0.0, 0.2974747474747475, -0.10527777777777776, 0.2366161616161616, 0.12874999999999998, 0.15, 0.23500000000000001, 0.0, 0.18166666666666664, 0.32222222222222224, 0.12416666666666665, 0.175, 0.30666666666666664, 1.0, 0.5736666666666667, 0.0, 0.3333333333333333, 0.3197916666666666, 1.0, 0.09000000000000001, 0.16785714285714287, -0.18100000000000002, 0.8333333333333333, 0.317, 0.0, 0.41893939393939394, 0.0, 0.8, -0.05000000000000002, 0.4083333333333333, -0.08333333333333337, 0.3666666666666667, 0.0, 0.3666666666666667, 0.85, 0.43999999999999995, 0.26944444444444443, -0.031111111111111117, 0.25416666666666665, 0.35, 0.16545454545454544, 0.36875, 0.3953030303030303, 0.5787878787878787, 0.3666666666666667, 0.3666666666666667, 0.18250000000000002, 0.18888888888888888, 0.0, 0.34102564102564104, 0.8, 0.2, -0.06979166666666668, -0.1, -0.1101010101010101, 0.4033333333333333, 0.3903061224489796, 0.07261904761904761, 0.12, 0.6033333333333333, 0.5, 0.07708333333333331, 0.21388888888888888, 0.0, 0.2705654761904762, 0.25166666666666665, 0.6375, 0.1716111111111111, 0.31471861471861473, 0.3, -0.025, 0.1875, 0.1575, -0.125, 0.4666666666666666, 0.0, 0.1716666666666667, 0.2, -0.009595959595959616, -0.2916666666666667, 0.7, 0.05, 0.6166666666666667, 0.20833333333333334, -0.6, 0.10666666666666666, 0.2333333333333333, -0.010476190476190481, 0.8, 0.21200000000000002, 0.2333333333333333, 0.0, 0.3, 0.13636363636363635, 0.325, 0.049999999999999996, 0.3, 0.4, 0.6555555555555556, 0.5, 0.0, 0.037500000000000006, 0.525, 0.26780303030303027, 0.3638888888888889, 0.2, 0.43333333333333335, 0.2833333333333333, 0.45999999999999996, 0.32499999999999996, 0.17159090909090913, 0.0, 0.35000000000000003, 0.5, 0.7, 0.04545454545454549, 0.2, -0.18583333333333335, 0.255050505050505, 0.07500000000000002, 0.19004820936639116, 0.0, 0.5333333333333333, 0.33749999999999997, 0.4583333333333333, 0.0, 0.36020408163265305, 0.8, 0.22857142857142856, 0.20416666666666664, 0.7, -0.09013605442176871, 0.5, 0.1048611111111111, 0.5, 0.4, 0.25333333333333335, 0.5469576719576719, 0.40277777777777773, 0.3277777777777778, 0.013333333333333374, 0.06666666666666667, 0.14583333333333331, 0.8, 0.3499999999999999, 0.5, 0.0, 0.65, 0.19999999999999998, 0.6333333333333333, 0.3, 0.3229166666666667, 0.39444444444444443, 0.04545454545454545, 0.11574074074074074, 0.07546296296296297, -0.15555555555555559, 0.5, 0.3236111111111111, 0.4840909090909091, 0.46825396825396826, 0.8, 0.17916666666666667, 0.5481481481481482, 0.7, 0.12956349206349208, -0.4316666666666667, 0.8, 0.25, 0.18333333333333335, 0.26249999999999996, 0.7, -0.1, 0.65625, -1.0, 0.65, 0.24, 0.09256198347107437, 0.04999999999999997, 0.18636363636363634, 0.5125, 0.19166666666666668, 0.8, 0.2, 0.1, -0.1, 0.16818181818181818, 0.4633184523809524, 0.1582908163265306, 0.4518518518518519, 0.3875, 0.10937500000000001, 0.1125, 0.5, -0.17708333333333334, 0.3, 0.06233766233766231, 0.35, 0.22664141414141412, 0.79, 0.8, 0.7, 0.0, 0.49000000000000005, 0.35416666666666663, 0.3431818181818182, 0.1625, 0.003541666666666665, 0.1333333333333333, 0.5027777777777778, 0.2333333333333333, 0.25, 0.32666666666666666, 0.0, 0.33434343434343433, -0.2666666666666666, 0.2, 0.75, -0.02013888888888889, 0.2, 0.5799999999999998, 0.6666666666666666, -0.11093750000000001, 0.55, 0.08472222222222221, 0.1430871212121212, 0.31025, 0.2857142857142857, 0.15089285714285716, 0.255, 0.0, 0.5333333333333333, 0.1449107142857143, 0.13576278659611996, -0.08333333333333333, 0.2555555555555556, 0.4, 0.13979591836734695, 0.0, 0.0, 0.74375, 0.7, 0.17285714285714288, 0.0, 0.004166666666666652, 0.27999999999999997, 0.19660493827160494, 0.35, 0.04545454545454545, -0.09722222222222221, -0.075, 0.33592592592592596, -0.030555555555555548, 0.8, 0.3333333333333333, 0.0, 0.6000000000000001, 0.225, 0.2285714285714286, 0.3033333333333333, 0.59375, 0.4512962962962963, 0.15, 0.25, -0.13888888888888887, 0.44375, -0.030555555555555555, -0.1125, 1.0, 0.65, 0.00833333333333334, 0.15277777777777776, 0.06818181818181818, 0.21363636363636362, 0.7, 0.5, 0.5875, -0.20729166666666668, 0.0, -0.1875, 0.5, 0.10169285714285714, 0.0, 0.0, 0.12321428571428572, 0.19791666666666666, 0.17999999999999997, 0.25, 0.18088888888888885, 0.4583333333333333, -0.025, -0.0625, 0.5083333333333333, 0.39395833333333335, 0.0, 0.037500000000000006, 0.29222222222222227, 0.16666666666666666, 0.40727272727272723, 0.45666666666666667, 0.21555555555555553, 0.7, 0.26666666666666666, 0.10303030303030303, 0.13999999999999999, 0.1125, 0.07520833333333334, 0.4375, 0.14444444444444446, 0.33999999999999997, 0.36166666666666664, 0.5, 0.18333333333333335, -0.2, 0.5083333333333333, -0.025, 0.10555555555555556, 0.3181818181818182, -0.019166666666666686, 0.13482142857142856, -0.08333333333333333, 0.3, 0.3, 0.55, -0.39999999999999997, 0.12, 0.26670033670033677, 0.16, 0.26666666666666666, 0.0, 0.5555555555555555, 0.6366666666666666, 0.27526455026455027, 0.21640625, 0.5, 0.2, 0.4875, 0.7, 0.2916666666666667, 0.0, 0.0, 0.36666666666666664, 0.5388888888888889, 0.09047619047619047, 0.1, 0.4138888888888889, 0.5, 0.15909090909090906, 0.19999999999999998, 0.38, 0.2375, -0.03787878787878788, 0.8666666666666667, 0.19166666666666665, 0.3, 0.8, 0.23852813852813853, 0.4333333333333333, 0.24901960784313726, 0.422, 0.13636363636363635, 0.06519607843137254, 0.6999999999999998, 0.0, 0.4, 0.5666666666666668, 0.25, 0.37878787878787873, 0.40737179487179487, 0.29375, 0.525, 0.22083333333333333, 0.0, 0.3654545454545454, 0.35, 0.6428571428571427, 5.551115123125783e-17, 0.2161904761904762, 0.15, 0.5666666666666667, 0.43333333333333335, -0.1875, 0.16818181818181818, 0.23833333333333334, 0.35000000000000003, 0.19140102321920505, 0.23645833333333335, 0.6333333333333333, 0.2375, 0.5566666666666666, 0.0, 0.0, 0.22829861111111108, 0.31777777777777777, 0.5361111111111111, 0.07738095238095238, 0.12525510204081633, 0.32083333333333336, 0.27380952380952384, -0.06666666666666665, 0.3, 0.31666666666666665, 0.20238095238095236, 0.2916666666666667, 0.11233333333333335, 0.14666666666666667, 0.5, 0.37878787878787873, 0.35000000000000003, 0.45, 0.5, 0.51, 0.5681818181818181, 0.125, 0.3740740740740741, 0.3333333333333333, 5.551115123125783e-17, 0.2448979591836735, 0.611111111111111, -0.3125, 0.375, 0.125, 0.225, 0.5, 0.024999999999999994, 0.595, 0.3666666666666667, 0.461111111111111, 0.0, 0.43939393939393945, 0.8666666666666667, 0.49999999999999994, 0.0, 0.3, 0.4169642857142857, 0.2875, 0.2375, 0.7, 0.7666666666666666, 0.1528138528138528, 0.21818181818181817, 0.65, 0.7, 0.3764285714285714, 0.36240740740740734, 0.5, -0.20833333333333331, 0.3, 0.19999999999999998, 0.3771885521885522, 0.5, 0.0, 0.425, 0.062441249226963515, 0.24861111111111112, 0.15328282828282827, 0.22738095238095238, 0.8, -0.25, 0.11111111111111112, 0.05911111111111111, -0.15386904761904766, 0.0, 0.45999999999999996, 0.22499999999999998, 0.7, 0.7, 1.0, 0.16666666666666666, 0.20138888888888892, 0.43333333333333335, 0.24000000000000005, 0.31999999999999995, 0.30694444444444446, 0.32575757575757575, 0.22916666666666669, 0.20000000000000004, 0.3068181818181818, 0.6166666666666667, -0.16666666666666666, 0.25, 1.0, 0.23388888888888887, 0.44999999999999996, 0.25000000000000006, 0.1638888888888889, 0.4548611111111111, 0.1782312925170068, -0.16666666666666666, 0.15142857142857144, 0.0, 0.4666666666666666, 0.525, 0.7333333333333334, 0.35, -0.08680555555555557, -0.05, 0.10634920634920633, 0.31, -0.3499999999999999, 0.18, 0.5, 0.31666666666666665, 0.18958333333333333, 0.6, 0.5571428571428572, 0.07366666666666669, 0.10784313725490195, 0.21666666666666667, 0.75, 0.4, 0.2, 0.4666666666666667, 0.7, 0.0, 0.009848484848484844, 0.0, 0.5, 0.13636363636363635, 0.2, 0.4, 0.15, 0.5666666666666667, 0.28555555555555556, -0.07434573002754821, 0.65, 0.08750000000000001, 0.65, 0.75, 0.10727272727272727, 0.0, -0.15125, 1.0, 0.475, -0.18981060606060607, 0.3666666666666667, 0.58, 0.0, 0.012373737373737391, 0.475, 0.3, 0.11250000000000002, 0.24333333333333332, 0.05, 0.6187499999999999, 0.25, 0.0, 0.11630036630036632, 0.2782828282828283, 0.40625, -0.14499999999999996, 0.26, 0.36944444444444446, 0.5437500000000001, 0.3, 0.425, 0.4166666666666667, 0.27777777777777773, -0.125, 0.14994047619047618, 0.10625000000000004, 0.375, 0.0, 0.1, 0.6333333333333333, 0.2928571428571428, 0.22428571428571428, 0.0, 0.575, 0.45606060606060606, 0.0, 0.5, 0.35, 0.8, 0.49000000000000005, 0.5933333333333334, 0.5, 0.87, 0.38125, 0.044444444444444446, 0.15285714285714286, 0.0, 0.0, 0.5333333333333333, 0.17500000000000002, 0.4125, -0.8666666666666667, 0.5875, 0.5125000000000001, 1.0, 0.8620000000000001, -0.2916666666666667, 0.283994708994709, 0.29805194805194807, 0.2770833333333333, 0.8, 0.20333333333333334, 0.32916666666666666, 0.34, 0.44772727272727275, 0.35000000000000003, -0.3, 0.7, 0.375, 0.1875, -0.5499999999999999, 0.6499999999999999, 0.13333333333333333, 0.45, 0.513888888888889, 0.575, 0.35, 0.0, 0.2, 0.0, 0.75, 0.1744155844155844, 0.4440476190476191, 0.10833333333333334, 0.13333333333333333, 0.5, 0.24598214285714284, 0.21111111111111114, 0.75, 0.21111111111111114, 0.21111111111111114, 0.44375, 0.03641456582633052, 0.6, 0.2333333333333333, 0.0, 0.44800000000000006, 0.625, 0.2, 0.19708333333333333, 0.1, 0.13166666666666668, 0.41818181818181815, 0.3297619047619048, 0.16818181818181818, 0.11142857142857146, 0.34067460317460313, 0.21705808080808087, 0.5333333333333333, 0.0, 0.3405952380952381, 0.27703168044077137, 0.9, 0.6154761904761905, 0.5, 0.25, 0.6875, 0.32625000000000004, 0.19583333333333333, 0.5778409090909091, 0.8, 0.0, 0.5, 0.19791666666666669, 0.26805194805194804, 0.20000000000000004, 0.15833333333333333, 0.506, 0.48125000000000007, 0.5625, -0.15833333333333333, 0.175, 0.34005602240896354, 0.059166666666666666, 0.7000000000000001, 0.4916666666666667, 0.0, 0.0, 0.3125, 0.13272727272727272, 0.7, 0.43333333333333335, 0.3, 0.3666666666666667, 0.37878787878787873, 0.65, 0.38125, 0.40937500000000004, 0.20833333333333334, 0.85, -0.1572916666666667, 0.13888888888888887, 0.15833333333333333, 0.6599999999999999, 0.7083333333333333, 0.8, 0.75, 0.4750000000000001, 0.22857142857142856, 0.26233766233766237, 0.0, 0.3, 0.01848659003831418, 0.24747474747474754, 0.1492212036329683, 0.39999999999999997, 0.2, 0.2308333333333333, 0.27499999999999997, 0.1285714285714286, -0.01517857142857143, 0.35250000000000004, 0.65, 0.09642857142857142, 0.15740740740740738, 1.0, 0.2816666666666666, 0.19999999999999998, 0.6, 0.4828571428571428, 0.5777777777777778, 0.16666666666666666, 0.45, 0.0, 0.18333333333333335, 0.2674918831168831, 0.19682539682539682, 0.31666666666666665, 0.0, 0.13657407407407407, 0.21496212121212122, 0.16833333333333333, 0.12569444444444441, 0.06212121212121211, 0.1409090909090909, 0.17407407407407408, 0.675, -0.03593750000000001, 0.03333333333333334, 0.3013888888888889, 0.5, 0.05925925925925926, 0.22727272727272727, 0.15166666666666667, 0.7, 0.5875, -0.25, 0.10972222222222221, 0.6, 0.41565656565656567, 0.4484848484848485, 0.11481481481481481, -0.007575757575757579, -0.16666666666666666, 0.26104166666666667, 0.4333333333333333, 0.325, 0.09000000000000002, 0.1634920634920635, 0.05875000000000001, 0.0975, 0.2520833333333333, 0.275, 0.04166666666666667, 0.1, 0.6666666666666666, 0.36428571428571427, -0.16666666666666666, 0.0, 0.7000000000000001, -0.051851851851851864, 0.06666666666666667, 0.25062500000000004, 0.7866666666666667, 0.275, 0.40914285714285714, 0.3495555555555555, 0.0, 0.10000000000000002, 0.016666666666666646, 0.21481481481481485, 0.7, 0.3125, 0.38, 0.20030864197530865, -0.1625, 0.3, 0.18787878787878787, 0.28500000000000003, 0.4681818181818182, 0.2, 0.08194444444444447, 0.08194444444444447, 0.0, 0.41000000000000003, 0.20500000000000002, 0.2333333333333333, 0.584375, 0.15833333333333335, 0.4440476190476191, 0.3840909090909091, 0.16999999999999998, 0.8833333333333333, 0.7, 0.125, 0.20216450216450216, 0.34814814814814815, 0.26392045454545454, 0.04749999999999996, -0.05357142857142857, 0.19333333333333336, 0.35, 0.12865190365190365, -0.07395833333333335, 0.2833333333333334, 0.6833333333333332, 0.09999999999999999, -0.04716666666666667, 0.340625, 0.5, 1.0, 0.375, 0.2, 0.2858225108225108, 0.26196969696969696, -0.019999999999999997, 0.08148148148148147, 0.39, -0.23095238095238096, 0.17576388888888891, 0.4107954545454546, 0.2619047619047619, 0.24954545454545451, 0.3541666666666667, 0.23333333333333334, 0.625, 0.3666666666666667, 0.5, 0.5, 0.2855555555555556, 0.125, 0.252, 0.025852272727272724, 0.4778138528138528, 0.4166666666666667, -0.036111111111111115, 0.4000000000000001, 0.15555555555555556, 0.4166666666666667, 0.275, 0.14285714285714285, -0.07083333333333335, 0.11547619047619047, 0.10904356060606062, 0.41, -0.0625, 0.15666666666666668, 0.4800000000000001, -0.06666666666666667, 0.16666666666666666, 0.7, 0.2351851851851852, 0.575, -0.1, 0.1, -0.02, 0.45128205128205134, 0.35357142857142854, 0.25, 0.75, 0.6888888888888888, 0.8, 0.09999999999999999, 0.6166666666666667, 0.0, -0.5633333333333334, 0.48500000000000004, 0.65, 0.33799999999999997, 0.09214285714285715, 0.054166666666666675, 0.625, 0.2, 0.01818181818181821, 0.6, 0.05, 0.4333333333333333, 0.0, 0.04583333333333333, 0.5771428571428572, 0.1861111111111111, 0.78, 0.06944444444444443, 0.25, 0.7533333333333333, 0.2222222222222222, 0.575, 0.18738344988344988, 0.3583333333333334, 0.33999999999999997, 0.378, 0.39999999999999997, 0.21666666666666667, 0.31416666666666665, -0.041666666666666664, 0.1, 0.07857142857142857, -0.058493589743589744, 0.65, 0.22000000000000003, 0.25, 0.0, 0.42727272727272725, 0.3361111111111111, 0.2977272727272727, 0.5, 0.6590909090909091, 0.03142857142857147, 0.14444444444444446, 0.38, -0.375, 0.0, -1.0, 0.3333333333333333, 0.11111111111111112, 0.0, 0.37625, 0.6174999999999999, 0.19166666666666665, 0.2, -0.13333333333333333, 0.4, 0.7, 0.14938271604938272, 0.4139204545454545, 0.28354978354978355, 0.635, 0.5, 0.5900000000000001, 0.35589225589225587, 0.37878787878787873, 0.0, -0.133, -0.4, 0.4872727272727272, 0.3125, 0.3233766233766234, 0.5125000000000001, 0.4666666666666666, 0.5285714285714286, 0.10714285714285714, 0.6666666666666666, 0.4454545454545455, 0.09999999999999999, 0.25, 0.2415246212121212, 0.4083333333333334, 0.20416666666666664, 0.22900000000000004, 0.31212121212121213, 0.22916666666666666, -0.06746031746031746, 0.2, 0.325, 0.3, 0.525, 0.52, 0.0, 0.6666666666666666, 0.18, 0.48166666666666663, 0.4666666666666666, 0.10833333333333334, 0.18704545454545454, 0.21041666666666667, 0.15999999999999998, 0.6000000000000001, 0.39999999999999997, 0.8019999999999999, 0.38927272727272727, 0.17867965367965366, 0.18958333333333333, 0.2726190476190476, 0.3333333333333333, -0.26666666666666666, 0.17604166666666668, 0.5666666666666667, 0.7, 0.3475555555555555, 0.1278409090909091, 0.25, -0.03333333333333334, 0.2777777777777778, -0.0036616161616161644, 0.45, -0.008249158249158256, 0.10000000000000002, 0.7, 0.3125, 0.0, 0.1361111111111111, 0.4000000000000001, 0.4666666666666666, 0.48031250000000003, -0.006249999999999999, 0.5071428571428571, 0.20192307692307693, -0.2418518518518518, 0.505, 0.56875, 0.5197619047619048, 0.11904761904761907, 0.5068181818181818, 0.6444444444444445, 0.3666666666666667, 0.3773809523809524, -0.49583333333333335, 0.4431818181818182, 0.46567460317460313, 0.05833333333333337, -0.09999999999999998, 0.22083333333333333, 0.5, 0.7, 0.21464285714285714, 0.2625, 0.20833333333333334, 0.42424242424242414, -0.09375, 0.0920995670995671, 0.55, 0.41999999999999993, 0.01558080808080808, 0.2961904761904762, 0.21666666666666667, 0.25497835497835497, 0.445, 0.2995535714285714, 0.0625, 0.0, 0.06214285714285715, 0.7, 0.3, 0.8000000000000002, -0.021428571428571415, 0.68, -0.04972222222222223, -0.051767676767676775, 0.0, 0.0, 0.7166666666666667, 0.08541666666666665, 0.09126984126984126, 0.22777777777777775, -0.24166666666666667, 0.5, 0.37222222222222223, 0.26964285714285713, 0.03333333333333333, 0.4928571428571428, 0.0991025641025641, 0.14444444444444446, 0.37500000000000006, 0.5275, 0.1, 0.10166666666666666, 0.26666666666666666, 0.04375, 0.3523809523809524, 0.0, 0.8, -0.3333333333333333, 0.44000000000000006, 0.5333333333333333, 0.33285714285714285, -0.09722222222222222, 0.528888888888889, 0.2638095238095238, 0.26666666666666666, 0.2916666666666667, 0.0625, 0.3499999999999999, 0.21041666666666667, 0.45, 0.35, 0.45999999999999996, 0.4604166666666667, 0.0, 0.10277777777777779, 0.45, 0.30277777777777776, 0.046001221001221, 0.03194444444444444, -0.08194444444444442, 0.1375, 0.18404761904761904, 0.45, -0.00909090909090907, 0.3666666666666667, 0.42666666666666675, 0.37, 0.27399999999999997, -0.25555555555555554, -0.08333333333333333, 0.4625, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.027777777777777773, 0.3829166666666667, 0.34375, 0.20502645502645503, -0.171875, -0.09999999999999998, 0.32499999999999996, 0.0, 0.012499999999999983, 0.0175, 0.4093333333333334, 0.036111111111111115, 0.16666666666666666, 0.39749999999999996, 0.32, 0.42857142857142866, 0.22, 0.825, -0.12380952380952381, 0.3861111111111111, 0.2811111111111111, 0.3, 0.5316666666666667, 0.41250000000000003, 0.9, 0.04416666666666667, 0.44375000000000003, 0.2, 0.29, 0.1, 0.15142045454545455, 0.26805555555555555, 0.16, 0.5336666666666667, 0.16699999999999998, 0.46630952380952373, 0.5833333333333334, 0.0, 0.05352564102564103, 0.0, 0.3375, 0.16181703397612493, 0.7250000000000001, 0.0062500000000000056, 0.22184343434343434, -0.0429421768707483, -0.15, 0.16, 0.85, 0.5, 0.37777777777777777, 0.4, 0.0, 0.5166666666666667, 0.35, 0.16999999999999998, 0.2270833333333333, 0.38125, 0.19333333333333333, 0.19787878787878788, 0.16642857142857143, 0.25, 0.11481481481481481, 0.5416666666666666, 0.55, 0.19179063360881543, 0.0, 0.19583333333333333, 0.32321428571428573, -0.21562499999999996, 0.292, -0.2916666666666667, 0.15, 0.4428571428571429, 0.2696428571428572, 0.22095238095238098, 0.75, 0.36944444444444446, 0.35, 0.0, 0.08981481481481482, 0.45555555555555555, 0.38888888888888884, -0.16666666666666666, 0.44333333333333336, 0.3139880952380953, 0.24208333333333332, 0.13125, 0.1888571428571429, 0.45, 0.4666666666666666, 0.1, 0.7033333333333333, 0.04545454545454545, 0.7, 0.42625, 0.15555555555555559, -0.1, 0.13166666666666665, 0.09166666666666663, 0.2446428571428571, 0.16666666666666666, 0.6214285714285713, 0.35, 0.4976190476190476, -0.18888888888888888, 0.05833333333333331, 0.471, 0.17341269841269843, 0.31, 0.15104166666666666, -0.041666666666666664, 0.35357142857142854, 0.275, 0.65, 0.32, 0.2, 0.35555555555555557, 0.53625, 0.36904761904761907, 0.12987012987012989, 0.14, 0.1983333333333333, 0.275, -0.08833333333333333, 0.5, 0.18166666666666664, -0.16666666666666666, 0.18414502164502167, 0.475, 0.1977777777777778, 0.21833333333333335, 0.37878787878787873, 0.4, 0.06666666666666667, 0.25, 0.18459207459207458, 0.3, 0.16666666666666666, 0.2777777777777778, 0.05666666666666666, 0.5, 0.2, -0.09722222222222222, 0.14382716049382716, 0.47124999999999995, 0.06666666666666665, 0.5, -0.041666666666666664, 0.29999999999999993, 0.00208333333333334, -0.56875, 0.5485714285714286, 0.38333333333333336, 0.21270833333333333, 0.2416666666666667, 0.8333333333333334, 0.39999999999999997, -0.12333333333333334, 0.5349999999999999, 0.4, 0.82, 0.45681818181818185, 0.33333333333333337, 0.24708333333333332, 0.36515151515151517, 0.15833333333333333, 0.6318181818181817, 0.06666666666666667, 0.05833333333333335, 0.15, -0.195, 0.021666666666666657, 0.5, 0.45, 0.8, 0.04722222222222223, 0.253125, 0.30000000000000004, 0.32, 0.403125, 0.06296296296296297, 0.4, 0.03125, 0.7000000000000001, 0.6, 0.6799999999999999, 0.0, 0.1583333333333333, 0.3333333333333333, 0.25416666666666665, 0.3375, 0.29047619047619044, 0.37666666666666665, 0.375, 0.5927083333333334, 0.7, 0.06221590909090907, 0.1361111111111111, 0.6, 0.35, 0.3387878787878788, 0.22749999999999998, 0.1875, -0.009523809523809521, 0.3976190476190477, 0.36, 0.3557144522144522, 0.5875, 0.35714285714285715, -0.025, 0.06888888888888889, 0.4523809523809524, 0.12000000000000002, 0.258228354978355, 0.3, 0.25, 0.0, 0.30178571428571427, 0.04567099567099566, -0.16666666666666666, 0.47500000000000003, 0.4941666666666667, 0.09999999999999999, 0.43333333333333335, 0.041666666666666664, 0.4457575757575757, 0.5044444444444445, 0.1688888888888889, 0.15166666666666667, 0.075, 0.625, 0.06578282828282829, 0.4041666666666667, 0.41818181818181815, 0.38608058608058615, 0.39, 0.10833333333333334, 0.35, 0.5499999999999999, 0.04285714285714287, 0.25, 0.0, 0.12878787878787878, 0.36999999999999994, 0.6333333333333333, 0.08124999999999999, 0.29666666666666663, 0.25, -0.5728395061728396, 0.23095238095238096, 0.2571428571428572, 0.42424242424242425, 0.16666666666666666, 0.34259259259259256, 0.2520833333333333, 0.6, 0.0, 0.32, 0.3590909090909091, 0.19545454545454544, -0.07861952861952863, 0.42000000000000004, 0.2111111111111111, 0.5700000000000001, 0.8, 0.19393939393939394, 0.3888888888888889, -0.2638888888888889, 0.0, 0.25, 0.0, 0.3, 0.10416666666666666, 0.0, 0.27037037037037037, 0.15138888888888888, 0.18680555555555556, 0.21666666666666667, -0.3319444444444445, 0.4, 0.18666666666666668, -0.1575, -0.08333333333333333, 0.06428571428571428, 0.55, 0.0, 0.19166666666666665, 0.2111111111111111, 0.15433333333333335, 0.0, 0.7166666666666668, 0.5833333333333334, 0.11704545454545454, 0.5900000000000001, 0.42541666666666667, 0.13999999999999999, 0.3666666666666667, -0.1, 0.0, -1.0, 0.24621212121212116, 0.5666666666666668, 0.20727272727272728, 0.35000000000000003, 0.10494791666666667, 0.3333333333333333, 0.0, 0.004166666666666665, 0.3125, 0.2708333333333333, 0.13541666666666666, -0.06666666666666667, 0.5839285714285714, 0.08571428571428572, 0.22395833333333331, 0.32, 0.16785714285714287, 0.33999999999999997, 0.06666666666666667, -0.1078125, 0.35, 0.42000000000000004, 0.1805427288760622, 0.6555555555555556, 0.10714285714285712, 0.10000000000000002, 0.47380952380952385, 0.4083333333333334, 0.4, 0.29999999999999993, 0.17083333333333334, -0.14999999999999997, 0.15833333333333335, 0.25, 0.41904761904761906, 0.26785714285714285, 0.33809523809523806, 0.14, -0.0875, -0.2722222222222222, 0.6666666666666666, 0.25, 0.35, 0.3775198412698413, 0.14583333333333334, -0.03787878787878787, 0.15333333333333335, 0.24047619047619048, 0.275, 0.7333333333333334, 0.16666666666666666, 0.0, 0.3, 0.48750000000000004, 0.425, 0.030000000000000006, 0.012738095238095225, 0.13656299840510366, 0.15333333333333335, -0.10621279761904763, 0.4014814814814815, 0.2977777777777778, 0.03333333333333333, 0.075, 0.54, 0.5202380952380952, 0.39, 0.85, 0.33809523809523806, 0.5874999999999999, 0.4642857142857143, 0.14166666666666666, -0.028246753246753253, 0.08, 0.20833333333333334, 0.325, 0.235375, 0.23010204081632654, -0.11249999999999998, 0.32142857142857145, 0.3, 0.6166666666666667, 0.27444444444444444, 0.21555555555555558, 0.15833333333333335, -0.13261904761904764, 0.1472222222222222, -0.09629629629629628, 0.625, 0.175, 0.08125, 0.425, -0.004999999999999999, 0.3208333333333333, 0.5, 0.007272727272727275, -0.016666666666666666, 0.4428571428571429, -0.185, 0.392, -0.03261904761904761, 0.3242424242424242, 0.12476190476190475, -0.14, 0.04083333333333333, 0.12510822510822514, 0.5, 0.0, 0.5027777777777778, -0.15555555555555559, 0.09583333333333333, 0.1716666666666667, 0.352, 0.1333333333333333, 0.15000000000000002, 0.18666666666666668, 0.17777777777777778, 0.20000000000000004, 0.16249999999999998, 0.55, 0.2739393939393939, -0.056666666666666664, 0.475, 0.055714285714285716, 0.4405594405594406, 0.19814814814814816, 0.30563492063492065, 0.31079545454545454, 0.6095238095238095, -0.032703081232493, -0.5583333333333333, 0.6000000000000001, 0.26666666666666666, -0.03181818181818183, 0.65, 0.39666666666666667, 0.26458333333333334, 0.27166666666666667, -0.16666666666666666, 0.5666666666666668, 0.5333333333333333, -0.0375, -0.23750000000000004, 0.07619047619047618, 0.195, 0.16666666666666666, -0.08333333333333333, 0.01388888888888893, 0.3409090909090909, 0.36666666666666664, 0.3515625, 0.0, 0.2384615384615385, 0.6, 0.43500000000000005, 0.48809523809523814, 0.3, 0.036111111111111115, 0.07083333333333332, 0.75, 0.3833333333333333, 0.34687500000000004, 0.24015151515151517, 0.26607142857142857, 0.205, 0.33999999999999997, 0.5666666666666667, 0.04892857142857143, 0.10976190476190473, 0.23578431372549016, 0.2375, 0.23000000000000004, 0.0, -0.2, 0.08106060606060606, -0.0638888888888889, 0.06628787878787878, -0.1, 0.545, -0.24166666666666664, 0.21714285714285717, 0.14166666666666664, 0.09638888888888887, 0.78, 0.00416666666666668, 0.8000000000000002, -0.2, -0.5666666666666665, 0.25, 0.20416666666666664, -0.14583333333333331, 0.21333333333333332, -0.012499999999999997, 0.0, 0.18833333333333332, 0.4590909090909091, 0.16071428571428573, 0.26666666666666666, 0.575, 0.2696969696969697, -0.35, 0.20909090909090908, -0.049999999999999996, 0.0, 0.625, 0.07411616161616161, 0.018560606060606055, 0.36666666666666664, -0.26833333333333337, 0.0, 0.425, 0.04545454545454545, -0.36428571428571427, -0.15833333333333333, 0.4544155844155844, 0.29333333333333333, -0.4597222222222222, 0.04999999999999999, 0.025000000000000005, 0.13824675324675323, 0.13636363636363635, 0.3857142857142857, 0.7, 0.5333333333333333, 0.18, 0.25, 0.2771717171717172, 0.315, 0.11666666666666668, 0.39999999999999997, 0.54375, -0.3499999999999999, 0.16555555555555557, 0.0, 0.08989898989898988, 0.8, -0.06818181818181818, -0.04791666666666666, 0.2333333333333333, 0.0, 0.13333333333333333, -0.1, 0.4666666666666666, 0.5, 0.4333333333333333, 0.762, 0.1593039772727273, 0.15000000000000002, -0.5, 0.6333333333333333, 0.09037698412698413, 0.7249999999999999, 0.55, 0.13999999999999999, -0.1, 0.0, 0.6916666666666668, 0.04421487603305786, 0.34123737373737373, 0.2287878787878788, -0.05, -0.21900000000000003, 0.008333333333333331, 0.036, 0.6, 0.2333333333333333, 0.5909090909090908, 0.2, -0.044126984126984126, 0.3, 0.07208333333333333, 0.02666666666666667, 0.3180952380952382, 0.34, 0.22499999999999998, 0.6333333333333334, 0.2, 0.2375, 0.15699999999999997, 0.5, 0.09722222222222222, 0.6468750000000001, 0.355, 0.33409090909090905, -0.041666666666666664, 0.0, 0.12000000000000002, 0.165, 0.5333333333333333, 0.16904761904761903, 0.2416666666666666, 0.4375, 0.21428571428571427, 0.1625, 0.06125, 0.12142857142857143, -0.024642857142857143, 0.1333333333333333, -0.3666666666666667, -0.05333333333333333, 0.38, 0.41875, 0.16666666666666666, 0.2772727272727272, -0.08541666666666665, 0.4333333333333333, 0.15000000000000002, 0.041666666666666664, 0.2837662337662338, -0.38999999999999996, 0.2657142857142857, 0.0, 0.25, 0.8, 0.2225, 0.0625, 0.2857142857142857, 0.07500000000000001, 0.36875, 0.39888888888888885, 0.40744949494949495, 0.3833333333333333, 0.8000000000000002, 0.2488282828282828, 0.7, 0.05833333333333332, 0.18181818181818182], "name": "polarity", "text": "", "line": {"color": "rgba(226, 74, 51, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}, {"type": "scatter", "x": ["2012-01-30", "2012-02-02", "2012-02-09", "2012-02-24", "2012-02-24", "2012-02-28", "2012-02-29", "2012-03-01", "2012-03-06", "2012-03-06", "2012-03-07", "2012-03-10", "2012-03-16", "2012-03-17", "2012-03-21", "2012-03-23", "2012-03-23", "2012-03-26", "2012-03-26", "2012-03-27", "2012-03-27", "2012-03-27", "2012-03-28", "2012-03-30", "2012-04-02", "2012-04-10", "2012-04-11", "2012-04-12", "2012-04-17", "2012-04-25", "2012-04-25", "2012-04-27", "2012-04-27", "2012-04-30", "2012-04-30", "2012-05-01", "2012-05-03", "2012-05-04", "2012-05-06", "2012-05-08", "2012-05-08", "2012-05-08", "2012-05-09", "2012-05-09", "2012-05-09", "2012-05-10", "2012-05-15", "2012-05-22", "2012-05-22", "2012-05-23", "2012-05-24", "2012-06-04", "2012-06-06", "2012-06-10", "2012-06-13", "2012-06-19", "2012-06-21", "2012-06-22", "2012-06-25", "2012-06-26", "2012-06-28", "2012-07-01", "2012-07-01", "2012-07-02", "2012-07-06", "2012-07-09", "2012-07-11", "2012-07-12", "2012-07-12", "2012-07-14", "2012-07-15", "2012-07-17", "2012-07-17", "2012-07-18", "2012-07-22", "2012-07-24", "2012-07-24", "2012-07-25", "2012-07-27", "2012-07-27", "2012-08-02", "2012-08-02", "2012-08-02", "2012-08-03", "2012-08-06", "2012-08-07", "2012-08-10", "2012-08-13", "2012-08-14", "2012-08-16", "2012-08-17", "2012-08-19", "2012-08-20", "2012-08-21", "2012-08-21", "2012-08-22", "2012-08-24", "2012-08-27", "2012-09-04", "2012-09-05", "2012-09-10", "2012-09-11", "2012-09-15", "2012-09-17", "2012-09-17", "2012-09-17", "2012-09-18", "2012-09-20", "2012-09-23", "2012-09-26", "2012-09-26", "2012-09-27", "2012-09-28", "2012-10-01", "2012-10-02", "2012-10-03", "2012-10-03", "2012-10-08", "2012-10-09", "2012-10-09", "2012-10-13", "2012-10-13", "2012-10-14", "2012-10-14", "2012-10-15", "2012-10-17", "2012-10-17", "2012-10-20", "2012-10-21", "2012-10-22", "2012-10-23", "2012-10-23", "2012-10-28", "2012-10-29", "2012-10-29", "2012-10-30", "2012-10-30", "2012-10-30", "2012-10-30", "2012-10-31", "2012-11-07", "2012-11-07", "2012-11-08", "2012-11-08", "2012-11-10", "2012-11-13", "2012-11-14", "2012-11-16", "2012-11-16", "2012-11-18", "2012-11-24", "2012-11-26", "2012-11-29", "2012-12-03", "2012-12-03", "2012-12-06", "2012-12-08", "2012-12-11", "2012-12-12", "2012-12-12", "2012-12-16", "2012-12-17", "2012-12-21", "2012-12-26", "2012-12-30", "2012-12-30", "2013-01-04", "2013-01-05", "2013-01-07", "2013-01-08", "2013-01-15", "2013-01-15", "2013-01-16", "2013-01-17", "2013-01-17", "2013-01-18", "2013-01-20", "2013-01-22", "2013-01-22", "2013-01-25", "2013-01-27", "2013-01-27", "2013-01-27", "2013-01-29", "2013-01-30", "2013-02-01", "2013-02-01", "2013-02-01", "2013-02-03", "2013-02-04", "2013-02-05", "2013-02-05", "2013-02-06", "2013-02-06", "2013-02-06", "2013-02-07", "2013-02-12", "2013-02-12", "2013-02-15", "2013-02-15", "2013-02-15", "2013-02-21", "2013-02-22", "2013-02-23", "2013-02-25", "2013-02-25", "2013-02-26", "2013-02-27", "2013-02-28", "2013-03-02", "2013-03-02", "2013-03-04", "2013-03-04", "2013-03-05", "2013-03-05", "2013-03-06", "2013-03-10", "2013-03-11", "2013-03-11", "2013-03-14", "2013-03-19", "2013-03-19", "2013-03-20", "2013-03-20", "2013-03-25", "2013-03-25", "2013-03-25", "2013-03-27", "2013-03-27", "2013-03-29", "2013-04-02", "2013-04-02", "2013-04-05", "2013-04-05", "2013-04-05", "2013-04-09", "2013-04-09", "2013-04-10", "2013-04-11", "2013-04-11", "2013-04-12", "2013-04-12", "2013-04-13", "2013-04-14", "2013-04-17", "2013-04-18", "2013-04-18", "2013-04-21", "2013-04-22", "2013-04-23", "2013-04-23", "2013-04-23", "2013-04-24", "2013-04-25", "2013-04-26", "2013-04-29", "2013-04-29", "2013-04-29", "2013-04-30", "2013-05-01", "2013-05-09", "2013-05-09", "2013-05-09", "2013-05-09", "2013-05-13", "2013-05-16", "2013-05-19", "2013-05-22", "2013-05-28", "2013-05-29", "2013-05-29", "2013-06-01", "2013-06-03", "2013-06-04", "2013-06-04", "2013-06-07", "2013-06-08", "2013-06-08", "2013-06-10", "2013-06-11", "2013-06-15", "2013-06-17", "2013-06-18", "2013-06-22", "2013-06-23", "2013-06-24", "2013-06-25", "2013-06-26", "2013-06-26", "2013-06-26", "2013-06-28", "2013-06-29", "2013-07-01", "2013-07-05", "2013-07-06", "2013-07-08", "2013-07-08", "2013-07-10", "2013-07-12", "2013-07-12", "2013-07-14", "2013-07-15", "2013-07-15", "2013-07-16", "2013-07-17", "2013-07-17", "2013-07-18", "2013-07-19", "2013-07-19", "2013-07-22", "2013-07-23", "2013-07-24", "2013-07-25", "2013-07-27", "2013-07-28", "2013-07-29", "2013-07-29", "2013-07-30", "2013-08-03", "2013-08-03", "2013-08-06", "2013-08-06", "2013-08-07", "2013-08-07", "2013-08-08", "2013-08-09", "2013-08-10", "2013-08-13", "2013-08-15", "2013-08-16", "2013-08-16", "2013-08-16", "2013-08-20", "2013-08-20", "2013-08-21", "2013-08-26", "2013-08-27", "2013-08-27", "2013-08-28", "2013-08-28", "2013-08-29", "2013-08-30", "2013-08-30", "2013-09-01", "2013-09-02", "2013-09-02", "2013-09-03", "2013-09-03", "2013-09-03", "2013-09-03", "2013-09-06", "2013-09-06", "2013-09-06", "2013-09-07", "2013-09-09", "2013-09-09", "2013-09-10", "2013-09-10", "2013-09-11", "2013-09-11", "2013-09-13", "2013-09-14", "2013-09-18", "2013-09-18", "2013-09-19", "2013-09-20", "2013-09-23", "2013-09-23", "2013-09-24", "2013-09-27", "2013-09-28", "2013-10-01", "2013-10-01", "2013-10-02", "2013-10-03", "2013-10-06", "2013-10-08", "2013-10-08", "2013-10-10", "2013-10-13", "2013-10-14", "2013-10-14", "2013-10-14", "2013-10-16", "2013-10-16", "2013-10-17", "2013-10-22", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-23", "2013-10-24", "2013-10-27", "2013-10-28", "2013-10-29", "2013-10-31", "2013-10-31", "2013-11-03", "2013-11-04", "2013-11-04", "2013-11-05", "2013-11-06", "2013-11-07", "2013-11-07", "2013-11-08", "2013-11-14", "2013-11-14", "2013-11-15", "2013-11-17", "2013-11-17", "2013-11-18", "2013-11-20", "2013-11-22", "2013-11-22", "2013-12-01", "2013-12-02", "2013-12-03", "2013-12-04", "2013-12-04", "2013-12-04", "2013-12-09", "2013-12-10", "2013-12-10", "2013-12-10", "2013-12-11", "2013-12-16", "2013-12-16", "2013-12-17", "2013-12-18", "2013-12-21", "2013-12-21", "2013-12-23", "2013-12-23", "2013-12-26", "2013-12-27", "2013-12-31", "2014-01-05", "2014-01-05", "2014-01-05", "2014-01-08", "2014-01-09", "2014-01-10", "2014-01-12", "2014-01-14", "2014-01-16", "2014-01-17", "2014-01-20", "2014-01-20", "2014-01-20", "2014-01-21", "2014-01-21", "2014-01-23", "2014-01-25", "2014-01-27", "2014-01-28", "2014-01-28", "2014-01-29", "2014-01-29", "2014-01-31", "2014-01-31", "2014-02-02", "2014-02-03", "2014-02-04", "2014-02-05", "2014-02-05", "2014-02-06", "2014-02-06", "2014-02-12", "2014-02-13", "2014-02-15", "2014-02-17", "2014-02-18", "2014-02-19", "2014-02-21", "2014-02-25", "2014-02-25", "2014-02-25", "2014-02-27", "2014-02-27", "2014-02-28", "2014-03-02", "2014-03-03", "2014-03-05", "2014-03-05", "2014-03-09", "2014-03-12", "2014-03-12", "2014-03-16", "2014-03-19", "2014-03-19", "2014-03-22", "2014-03-23", "2014-03-26", "2014-03-27", "2014-03-28", "2014-03-29", "2014-03-31", "2014-03-31", "2014-03-31", "2014-04-01", "2014-04-02", "2014-04-03", "2014-04-06", "2014-04-07", "2014-04-08", "2014-04-09", "2014-04-10", "2014-04-15", "2014-04-16", "2014-04-16", "2014-04-16", "2014-04-17", "2014-04-18", "2014-04-24", "2014-04-24", "2014-05-02", "2014-05-05", "2014-05-05", "2014-05-07", "2014-05-07", "2014-05-09", "2014-05-09", "2014-05-10", "2014-05-14", "2014-05-15", "2014-05-15", "2014-05-16", "2014-05-16", "2014-05-20", "2014-05-21", "2014-05-21", "2014-05-23", "2014-05-23", "2014-05-24", "2014-05-27", "2014-05-27", "2014-05-27", "2014-05-29", "2014-06-02", "2014-06-03", "2014-06-04", "2014-06-05", "2014-06-06", "2014-06-06", "2014-06-09", "2014-06-14", "2014-06-16", "2014-06-17", "2014-06-19", "2014-06-19", "2014-06-20", "2014-06-20", "2014-06-20", "2014-06-22", "2014-06-23", "2014-06-23", "2014-06-23", "2014-06-24", "2014-06-24", "2014-06-25", "2014-06-28", "2014-06-29", "2014-06-30", "2014-07-01", "2014-07-02", "2014-07-07", "2014-07-08", "2014-07-11", "2014-07-11", "2014-07-12", "2014-07-13", "2014-07-14", "2014-07-16", "2014-07-16", "2014-07-17", "2014-07-20", "2014-07-21", "2014-07-22", "2014-07-22", "2014-07-23", "2014-07-23", "2014-07-23", "2014-07-25", "2014-07-25", "2014-07-25", "2014-07-27", "2014-07-28", "2014-07-30", "2014-07-31", "2014-08-04", "2014-08-05", "2014-08-05", "2014-08-09", "2014-08-11", "2014-08-12", "2014-08-13", "2014-08-14", "2014-08-14", "2014-08-15", "2014-08-17", "2014-08-18", "2014-08-18", "2014-08-18", "2014-08-23", "2014-08-26", "2014-08-26", "2014-08-27", "2014-08-29", "2014-08-30", "2014-08-30", "2014-08-31", "2014-09-02", "2014-09-03", "2014-09-03", "2014-09-04", "2014-09-05", "2014-09-06", "2014-09-07", "2014-09-08", "2014-09-09", "2014-09-11", "2014-09-12", "2014-09-12", "2014-09-12", "2014-09-12", "2014-09-15", "2014-09-16", "2014-09-16", "2014-09-17", "2014-09-18", "2014-09-19", "2014-09-19", "2014-09-19", "2014-09-21", "2014-09-22", "2014-09-22", "2014-09-23", "2014-09-27", "2014-09-27", "2014-09-29", "2014-09-30", "2014-10-01", "2014-10-02", "2014-10-04", "2014-10-04", "2014-10-06", "2014-10-07", "2014-10-07", "2014-10-08", "2014-10-12", "2014-10-12", "2014-10-13", "2014-10-14", "2014-10-15", "2014-10-16", "2014-10-18", "2014-10-19", "2014-10-20", "2014-10-20", "2014-10-21", "2014-10-21", "2014-10-22", "2014-10-22", "2014-10-23", "2014-10-23", "2014-10-25", "2014-10-27", "2014-10-27", "2014-10-29", "2014-10-30", "2014-10-30", "2014-10-31", "2014-11-03", "2014-11-04", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-07", "2014-11-19", "2014-11-20", "2014-11-21", "2014-11-22", "2014-11-24", "2014-11-24", "2014-11-24", "2014-11-26", "2014-11-30", "2014-12-01", "2014-12-01", "2014-12-02", "2014-12-03", "2014-12-04", "2014-12-04", "2014-12-05", "2014-12-06", "2014-12-08", "2014-12-08", "2014-12-11", "2014-12-16", "2014-12-17", "2014-12-19", "2014-12-23", "2014-12-26", "2014-12-26", "2014-12-26", "2014-12-27", "2014-12-27", "2014-12-27", "2014-12-29", "2014-12-29", "2014-12-30", "2015-01-01", "2015-01-01", "2015-01-01", "2015-01-02", "2015-01-05", "2015-01-05", "2015-01-05", "2015-01-06", "2015-01-06", "2015-01-07", "2015-01-07", "2015-01-09", "2015-01-10", "2015-01-10", "2015-01-10", "2015-01-11", "2015-01-11", "2015-01-12", "2015-01-12", "2015-01-13", "2015-01-14", "2015-01-15", "2015-01-18", "2015-01-18", "2015-01-19", "2015-01-19", "2015-01-19", "2015-01-19", "2015-01-21", "2015-01-21", "2015-01-23", "2015-01-25", "2015-01-28", "2015-01-28", "2015-01-29", "2015-02-01", "2015-02-02", "2015-02-04", "2015-02-05", "2015-02-05", "2015-02-06", "2015-02-07", "2015-02-09", "2015-02-10", "2015-02-12", "2015-02-13", "2015-02-14", "2015-02-15", "2015-02-17", "2015-02-19", "2015-02-20", "2015-02-23", "2015-02-23", "2015-02-23", "2015-02-24", "2015-02-24", "2015-02-24", "2015-02-26", "2015-02-26", "2015-02-26", "2015-02-26", "2015-02-27", "2015-02-28", "2015-02-28", "2015-02-28", "2015-03-01", "2015-03-03", "2015-03-03", "2015-03-04", "2015-03-04", "2015-03-08", "2015-03-09", "2015-03-10", "2015-03-10", "2015-03-11", "2015-03-11", "2015-03-11", "2015-03-11", "2015-03-13", "2015-03-16", "2015-03-16", "2015-03-17", "2015-03-18", "2015-03-29", "2015-03-31", "2015-03-31", "2015-04-01", "2015-04-05", "2015-04-06", "2015-04-06", "2015-04-07", "2015-04-07", "2015-04-07", "2015-04-08", "2015-04-08", "2015-04-09", "2015-04-09", "2015-04-10", "2015-04-12", "2015-04-12", "2015-04-14", "2015-04-16", "2015-04-17", "2015-04-21", "2015-04-22", "2015-04-23", "2015-04-23", "2015-04-24", "2015-04-25", "2015-04-30", "2015-05-01", "2015-05-01", "2015-05-07", "2015-05-07", "2015-05-10", "2015-05-11", "2015-05-13", "2015-05-13", "2015-05-14", "2015-05-15", "2015-05-18", "2015-05-21", "2015-05-21", "2015-05-21", "2015-05-22", "2015-05-22", "2015-05-25", "2015-05-28", "2015-05-29", "2015-05-29", "2015-05-30", "2015-06-02", "2015-06-04", "2015-06-04", "2015-06-05", "2015-06-06", "2015-06-08", "2015-06-08", "2015-06-08", "2015-06-10", "2015-06-15", "2015-06-16", "2015-06-17", "2015-06-17", "2015-06-20", "2015-06-24", "2015-06-26", "2015-06-26", "2015-06-27", "2015-06-27", "2015-06-30", "2015-07-03", "2015-07-03", "2015-07-06", "2015-07-07", "2015-07-08", "2015-07-08", "2015-07-13", "2015-07-14", "2015-07-14", "2015-07-14", "2015-07-15", "2015-07-16", "2015-07-16", "2015-07-17", "2015-07-21", "2015-07-21", "2015-07-22", "2015-07-23", "2015-07-23", "2015-07-24", "2015-07-27", "2015-07-28", "2015-07-29", "2015-07-29", "2015-07-29", "2015-07-30", "2015-07-31", "2015-08-02", "2015-08-02", "2015-08-02", "2015-08-02", "2015-08-03", "2015-08-05", "2015-08-06", "2015-08-06", "2015-08-09", "2015-08-09", "2015-08-10", "2015-08-11", "2015-08-12", "2015-08-12", "2015-08-15", "2015-08-18", "2015-08-18", "2015-08-19", "2015-08-20", "2015-08-21", "2015-08-21", "2015-08-24", "2015-08-25", "2015-08-27", "2015-08-27", "2015-09-02", "2015-09-03", "2015-09-03", "2015-09-06", "2015-09-08", "2015-09-09", "2015-09-10", "2015-09-10", "2015-09-11", "2015-09-14", "2015-09-14", "2015-09-15", "2015-09-15", "2015-09-16", "2015-09-17", "2015-09-19", "2015-09-21", "2015-09-21", "2015-09-22", "2015-09-23", "2015-09-24", "2015-09-28", "2015-09-29", "2015-09-30", "2015-09-30", "2015-09-30", "2015-10-02", "2015-10-05", "2015-10-05", "2015-10-05", "2015-10-05", "2015-10-06", "2015-10-08", "2015-10-10", "2015-10-10", "2015-10-12", "2015-10-12", "2015-10-12", "2015-10-13", "2015-10-13", "2015-10-14", "2015-10-14", "2015-10-15", "2015-10-16", "2015-10-18", "2015-10-18", "2015-10-19", "2015-10-19", "2015-10-19", "2015-10-21", "2015-10-21", "2015-10-21", "2015-10-22", "2015-10-22", "2015-10-23", "2015-10-24", "2015-10-26", "2015-10-26", "2015-10-29", "2015-10-29", "2015-10-29", "2015-11-02", "2015-11-03", "2015-11-04", "2015-11-04", "2015-11-06", "2015-11-09", "2015-11-10", "2015-11-10", "2015-11-11", "2015-11-18", "2015-11-18", "2015-11-19", "2015-11-20", "2015-11-24", "2015-11-26", "2015-12-01", "2015-12-02", "2015-12-05", "2015-12-08", "2015-12-10", "2015-12-14", "2015-12-24", "2015-12-31", "2016-01-06", "2016-01-08", "2016-01-08", "2016-01-11", "2016-01-16", "2016-01-18", "2016-01-19", "2016-01-20", "2016-01-22", "2016-01-25", "2016-01-26", "2016-01-28", "2016-01-29", "2016-02-01", "2016-02-01", "2016-02-02", "2016-02-03", "2016-02-05", "2016-02-05", "2016-02-06", "2016-02-09", "2016-02-11", "2016-02-12", "2016-02-13", "2016-02-22", "2016-02-24", "2016-02-24", "2016-02-25", "2016-02-26", "2016-03-03", "2016-03-04", "2016-03-05", "2016-03-06", "2016-03-08", "2016-03-09", "2016-03-11", "2016-03-14", "2016-03-14", "2016-03-15", "2016-03-18", "2016-03-22", "2016-03-23", "2016-03-24", "2016-03-27", "2016-03-28", "2016-04-05", "2016-04-06", "2016-04-08", "2016-04-10", "2016-04-12", "2016-04-14", "2016-04-14", "2016-04-14", "2016-04-17", "2016-04-20", "2016-04-21", "2016-04-21", "2016-04-23", "2016-04-24", "2016-05-01", "2016-05-01", "2016-05-02", "2016-05-04", "2016-05-04", "2016-05-07", "2016-05-09", "2016-05-10", "2016-05-10", "2016-05-15", "2016-05-16", "2016-05-18", "2016-05-19", "2016-05-20", "2016-05-21", "2016-05-21", "2016-05-27", "2016-06-02", "2016-06-02", "2016-06-04", "2016-06-04", "2016-06-06", "2016-06-08", "2016-06-11", "2016-06-13", "2016-06-15", "2016-06-24", "2016-06-27", "2016-06-28", "2016-06-29", "2016-07-01", "2016-07-01", "2016-07-03", "2016-07-03", "2016-07-06", "2016-07-07", "2016-07-07", "2016-07-09", "2016-07-11", "2016-07-12", "2016-07-13", "2016-07-14", "2016-07-15", "2016-07-16", "2016-07-19", "2016-07-24", "2016-07-29", "2016-07-30", "2016-07-31", "2016-08-02", "2016-08-04", "2016-08-08", "2016-08-09", "2016-08-09", "2016-08-11", "2016-08-12", "2016-08-14", "2016-08-15", "2016-08-16", "2016-08-16", "2016-08-19", "2016-08-19", "2016-08-23", "2016-08-23", "2016-08-28", "2016-08-31", "2016-09-01", "2016-09-03", "2016-09-03", "2016-09-04", "2016-09-05", "2016-09-07", "2016-09-09", "2016-09-09", "2016-09-13", "2016-09-15", "2016-09-18", "2016-09-21", "2016-09-26", "2016-09-27", "2016-09-27", "2016-09-28", "2016-09-30", "2016-10-03", "2016-10-03", "2016-10-03", "2016-10-04", "2016-10-04", "2016-10-04", "2016-10-06", "2016-10-07", "2016-10-07", "2016-10-07", "2016-10-11", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-12", "2016-10-13", "2016-10-14", "2016-10-17", "2016-10-19", "2016-10-19", "2016-10-21", "2016-10-21", "2016-10-21", "2016-10-23", "2016-10-23", "2016-10-23", "2016-10-24", "2016-10-24", "2016-10-25", "2016-10-26", "2016-10-30", "2016-10-30", "2016-10-30", "2016-10-31", "2016-10-31", "2016-11-02", "2016-11-02", "2016-11-03", "2016-11-09", "2016-11-09", "2016-11-10", "2016-11-13", "2016-11-14", "2016-11-15", "2016-11-19", "2016-11-23", "2016-11-25", "2016-11-27", "2016-11-28", "2016-11-30", "2016-12-01", "2016-12-04", "2016-12-07", "2016-12-07", "2016-12-11", "2016-12-11", "2016-12-12", "2016-12-14", "2016-12-14", "2016-12-14", "2016-12-15", "2016-12-15", "2016-12-16", "2016-12-19", "2016-12-21", "2016-12-21", "2016-12-24", "2016-12-27", "2016-12-28", "2016-12-31", "2017-01-02", "2017-01-02", "2017-01-02", "2017-01-02", "2017-01-03", "2017-01-04", "2017-01-04", "2017-01-04", "2017-01-06", "2017-01-08", "2017-01-09", "2017-01-09", "2017-01-10", "2017-01-10", "2017-01-10", "2017-01-10", "2017-01-11", "2017-01-16", "2017-01-18", "2017-01-19", "2017-01-21", "2017-01-22", "2017-01-22", "2017-01-23", "2017-01-23", "2017-01-23", "2017-01-25", "2017-01-26", "2017-01-27", "2017-01-27", "2017-01-27", "2017-01-28", "2017-01-29", "2017-01-30", "2017-01-31", "2017-01-31", "2017-02-02", "2017-02-05", "2017-02-05", "2017-02-07", "2017-02-08", "2017-02-09", "2017-02-09", "2017-02-10", "2017-02-11", "2017-02-11", "2017-02-13", "2017-02-13", "2017-02-16", "2017-02-17", "2017-02-21", "2017-02-22", "2017-02-23", "2017-02-24", "2017-02-25", "2017-02-27", "2017-02-28", "2017-02-28", "2017-02-28", "2017-03-01", "2017-03-01", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-02", "2017-03-03", "2017-03-05", "2017-03-06", "2017-03-06", "2017-03-07", "2017-03-07", "2017-03-10", "2017-03-10", "2017-03-12", "2017-03-12", "2017-03-15", "2017-03-16", "2017-03-16", "2017-03-18", "2017-03-18", "2017-03-19", "2017-03-19", "2017-03-20", "2017-03-21", "2017-03-21", "2017-03-22", "2017-03-23", "2017-03-24", "2017-03-24", "2017-03-26", "2017-03-26", "2017-03-26", "2017-03-26", "2017-03-27", "2017-03-28", "2017-03-29", "2017-03-30", "2017-03-30", "2017-03-31", "2017-04-01", "2017-04-01", "2017-04-02", "2017-04-03", "2017-04-04", "2017-04-05", "2017-04-05", "2017-04-05", "2017-04-06", "2017-04-07", "2017-04-08", "2017-04-09", "2017-04-10", "2017-04-11", "2017-04-12", "2017-04-12", "2017-04-13", "2017-04-15", "2017-04-17", "2017-04-17", "2017-04-18", "2017-04-18", "2017-04-19", "2017-04-20", "2017-04-20", "2017-04-21", "2017-04-24", "2017-04-25", "2017-04-25", "2017-04-27", "2017-04-28", "2017-04-28", "2017-04-29", "2017-04-29", "2017-04-30", "2017-05-02", "2017-05-02", "2017-05-02", "2017-05-05", "2017-05-06", "2017-05-06", "2017-05-07", "2017-05-07", "2017-05-07", "2017-05-08", "2017-05-08", "2017-05-09", "2017-05-09", "2017-05-09", "2017-05-09", "2017-05-10", "2017-05-11", "2017-05-11", "2017-05-11", "2017-05-13", "2017-05-15", "2017-05-15", "2017-05-15", "2017-05-16", "2017-05-16", "2017-05-16", "2017-05-16", "2017-05-18", "2017-05-19", "2017-05-20", "2017-05-21", "2017-05-21", "2017-05-21", "2017-05-22", "2017-05-22", "2017-05-22", "2017-05-23", "2017-05-24", "2017-05-24", "2017-05-29", "2017-05-31", "2017-05-31", "2017-06-01", "2017-06-01", "2017-06-02", "2017-06-03", "2017-06-05", "2017-06-06", "2017-06-07", "2017-06-07", "2017-06-07", "2017-06-07", "2017-06-08", "2017-06-08", "2017-06-10", "2017-06-11", "2017-06-11", "2017-06-13", "2017-06-13", "2017-06-13", "2017-06-15", "2017-06-15", "2017-06-15", "2017-06-16", "2017-06-16", "2017-06-18", "2017-06-20", "2017-06-20", "2017-06-21", "2017-06-22", "2017-06-22", "2017-06-24", "2017-06-27", "2017-06-28", "2017-06-28", "2017-06-30", "2017-07-05", "2017-07-05", "2017-07-07", "2017-07-08", "2017-07-10", "2017-07-10", "2017-07-11", "2017-07-11", "2017-07-12", "2017-07-13", "2017-07-14", "2017-07-15", "2017-07-17", "2017-07-17", "2017-07-17", "2017-07-17", "2017-07-18", "2017-07-18", "2017-07-18", "2017-07-19", "2017-07-19", "2017-07-20", "2017-07-20", "2017-07-20", "2017-07-22", "2017-07-23", "2017-07-24", "2017-07-24", "2017-07-25", "2017-07-25", "2017-07-27", "2017-07-27", "2017-07-28", "2017-07-30", "2017-07-31", "2017-07-31", "2017-08-01", "2017-08-01", "2017-08-04", "2017-08-05", "2017-08-06", "2017-08-06", "2017-08-07", "2017-08-07", "2017-08-09", "2017-08-09", "2017-08-09", "2017-08-10", "2017-08-14", "2017-08-14", "2017-08-15", "2017-08-15", "2017-08-16", "2017-08-17", "2017-08-17", "2017-08-17", "2017-08-19", "2017-08-21", "2017-08-21", "2017-08-21", "2017-08-22", "2017-08-22", "2017-08-24", "2017-08-24", "2017-08-25", "2017-08-27", "2017-08-28", "2017-08-28", "2017-08-29", "2017-08-31", "2017-08-31", "2017-09-01", "2017-09-03", "2017-09-04", "2017-09-05", "2017-09-05", "2017-09-06", "2017-09-06", "2017-09-06", "2017-09-07", "2017-09-07", "2017-09-07", "2017-09-08", "2017-09-09", "2017-09-11", "2017-09-11", "2017-09-11", "2017-09-12", "2017-09-13", "2017-09-13", "2017-09-16", "2017-09-18", "2017-09-18", "2017-09-20", "2017-09-21", "2017-09-21", "2017-09-21", "2017-09-22", "2017-09-22", "2017-09-24", "2017-09-26", "2017-09-26", "2017-09-27", "2017-09-28", "2017-09-28", "2017-09-29", "2017-09-29", "2017-09-30", "2017-10-02", "2017-10-03", "2017-10-03", "2017-10-03", "2017-10-04", "2017-10-05", "2017-10-06", "2017-10-07", "2017-10-07", "2017-10-09", "2017-10-09", "2017-10-10", "2017-10-11", "2017-10-12", "2017-10-12", "2017-10-13", "2017-10-13", "2017-10-17", "2017-10-17", "2017-10-18", "2017-10-19", "2017-10-20", "2017-10-21", "2017-10-24", "2017-10-24", "2017-10-27", "2017-10-27", "2017-10-28", "2017-10-29", "2017-10-30", "2017-10-31", "2017-10-31", "2017-10-31", "2017-11-01", "2017-11-01", "2017-11-03", "2017-11-04", "2017-11-06", "2017-11-06", "2017-11-07", "2017-11-07", "2017-11-07", "2017-11-08", "2017-11-10", "2017-11-12", "2017-11-13", "2017-11-14", "2017-11-14", "2017-11-14", "2017-11-15", "2017-11-16", "2017-11-17", "2017-11-19", "2017-11-19", "2017-11-20", "2017-11-20", "2017-11-24", "2017-11-25", "2017-11-26", "2017-11-26", "2017-11-27", "2017-11-27", "2017-11-27", "2017-12-01", "2017-12-01", "2017-12-03", "2017-12-04", "2017-12-04", "2017-12-05", "2017-12-05", "2017-12-06", "2017-12-08", "2017-12-10", "2017-12-12", "2017-12-12", "2017-12-13", "2017-12-15", "2017-12-17", "2017-12-19", "2017-12-20", "2017-12-20", "2017-12-20", "2017-12-21", "2017-12-26", "2017-12-29", "2017-12-29", "2018-01-02", "2018-01-02", "2018-01-03", "2018-01-03", "2018-01-04", "2018-01-04", "2018-01-06", "2018-01-06", "2018-01-06", "2018-01-07", "2018-01-08", "2018-01-09", "2018-01-10", "2018-01-10", "2018-01-10", "2018-01-11", "2018-01-11", "2018-01-12", "2018-01-14", "2018-01-15", "2018-01-15", "2018-01-15", "2018-01-15", "2018-01-16", "2018-01-18", "2018-01-19", "2018-01-19", "2018-01-19", "2018-01-20", "2018-01-22", "2018-01-22", "2018-01-23", "2018-01-23", "2018-01-24", "2018-01-24", "2018-01-24", "2018-01-27", "2018-01-28", "2018-01-30", "2018-01-30", "2018-01-30", "2018-01-31", "2018-01-31", "2018-01-31", "2018-02-01", "2018-02-02", "2018-02-03", "2018-02-03", "2018-02-04", "2018-02-04", "2018-02-05", "2018-02-06", "2018-02-06", "2018-02-06", "2018-02-08", "2018-02-09", "2018-02-10", "2018-02-11", "2018-02-12", "2018-02-13", "2018-02-15", "2018-02-16", "2018-02-16", "2018-02-16", "2018-02-18", "2018-02-20", "2018-02-23", "2018-02-24", "2018-02-27", "2018-02-27", "2018-03-02", "2018-03-02", "2018-03-04", "2018-03-06", "2018-03-06", "2018-03-07", "2018-03-08", "2018-03-08", "2018-03-08", "2018-03-08", "2018-03-10", "2018-03-11", "2018-03-11", "2018-03-14", "2018-03-14", "2018-03-15", "2018-03-18", "2018-03-19", "2018-03-19", "2018-03-19", "2018-03-20", "2018-03-20", "2018-03-20", "2018-03-20", "2018-03-21", "2018-03-22", "2018-03-26", "2018-03-26", "2018-03-26", "2018-03-27", "2018-03-27", "2018-03-27", "2018-03-28", "2018-03-28", "2018-03-30", "2018-03-31", "2018-04-01", "2018-04-03", "2018-04-03", "2018-04-04", "2018-04-04", "2018-04-05", "2018-04-05", "2018-04-07", "2018-04-09", "2018-04-09", "2018-04-11", "2018-04-12", "2018-04-12", "2018-04-13", "2018-04-14", "2018-04-15", "2018-04-16", "2018-04-17", "2018-04-17", "2018-04-18", "2018-04-23", "2018-04-24", "2018-04-26", "2018-04-27", "2018-04-27", "2018-04-30", "2018-05-01", "2018-05-02", "2018-05-02", "2018-05-03", "2018-05-05", "2018-05-05", "2018-05-07", "2018-05-07", "2018-05-07", "2018-05-08", "2018-05-08", "2018-05-08", "2018-05-08", "2018-05-09", "2018-05-11", "2018-05-11", "2018-05-12", "2018-05-15", "2018-05-16", "2018-05-16", "2018-05-18", "2018-05-19", "2018-05-19", "2018-05-22", "2018-05-23", "2018-05-27", "2018-05-27", "2018-05-31", "2018-05-31", "2018-06-02", "2018-06-04", "2018-06-05", "2018-06-05", "2018-06-05", "2018-06-06"], "y": [0.4666666666666666, 0.35, 0.75, 0.6333333333333333, 0.6333333333333333, 0.5405303030303029, 0.42500000000000004, 0.15000000000000002, 0.33499999999999996, 0.6433333333333334, 0.7625000000000001, 0.6694444444444444, 0.5, 0.15, 0.475, 0.35833333333333334, 0.75, 0.36309523809523814, 0.355, 0.6848484848484849, 0.5857142857142857, 0.5666666666666667, 0.425, 0.47847222222222224, 0.5840909090909091, 0.75, 0.5125, 0.54, 0.45357142857142857, 0.4387445887445887, 0.4597222222222222, 0.415, 0.5592203548085901, 0.3875992063492064, 0.4375, 0.5617768595041323, 0.75, 0.4, 0.36666666666666664, 0.375, 0.18333333333333335, 0.675, 0.8666666666666667, 0.7200000000000001, 0.46296296296296297, 0.5416666666666666, 0.2553030303030303, 0.6202020202020203, 0.56, 0.38095238095238093, 0.4686868686868687, 0.5583333333333333, 1.0, 0.0, 0.5301406926406925, 0.538611111111111, 0.40492424242424246, 0.55625, 0.7, 0.4192857142857143, 0.06666666666666667, 0.5483333333333333, 0.9, 0.7408333333333333, 0.7, 0.5166666666666666, 1.0, 0.9123333333333334, 0.5, 0.43333333333333335, 0.6104166666666667, 1.0, 0.31500000000000006, 0.4011904761904762, 0.403, 1.0, 0.5246666666666666, 0.0, 0.6381313131313132, 0.0, 0.75, 0.35, 0.5333333333333333, 0.6333333333333334, 0.6875, 0.39999999999999997, 0.7000000000000001, 0.8, 0.54, 0.6805555555555555, 0.49777777777777776, 0.6458333333333333, 0.30000000000000004, 0.5315151515151515, 0.48125, 0.7493939393939393, 0.6515151515151515, 0.75, 0.4666666666666666, 0.595, 0.4333333333333333, 0.0, 0.6384615384615384, 0.75, 0.3, 0.4927083333333333, 0.0, 0.5181818181818182, 0.4433333333333333, 0.4969387755102041, 0.5750000000000001, 0.54, 0.56, 0.7, 0.32708333333333334, 0.625, 0.0, 0.5845238095238094, 0.46749999999999997, 0.725, 0.5178333333333333, 0.5000000000000001, 0.55, 0.3375, 0.8125, 0.4491666666666666, 0.375, 0.46666666666666673, 0.0, 0.4683333333333334, 0.3, 0.3717171717171717, 0.5416666666666666, 0.6000000000000001, 0.1375, 0.7689814814814814, 0.6124999999999999, 0.9, 0.51, 0.5499999999999999, 0.600952380952381, 0.75, 0.556, 0.24666666666666667, 0.0, 0.66, 0.45454545454545453, 0.5571428571428572, 0.31666666666666665, 0.4833333333333334, 0.5, 0.75, 0.6625, 0.0, 0.37187499999999996, 0.5625, 0.4629545454545454, 0.6580246913580248, 0.41000000000000003, 0.5833333333333334, 0.6833333333333333, 0.62, 0.5, 0.459469696969697, 0.0, 0.5944444444444444, 0.625, 0.9, 0.5737373737373738, 0.3, 0.7108333333333333, 0.35656565656565653, 0.4020833333333333, 0.3045798898071625, 0.6, 0.6000000000000001, 0.6, 0.8333333333333334, 0.0, 0.7193877551020408, 0.75, 0.7071428571428571, 0.5708333333333333, 0.6000000000000001, 0.46530612244897956, 0.60625, 0.44097222222222227, 0.6, 0.375, 0.45333333333333337, 0.66494708994709, 0.6305555555555555, 0.5888888888888889, 0.5766666666666665, 0.43333333333333335, 0.5041666666666667, 0.75, 0.5, 0.7875, 0.0, 0.625, 0.6433333333333333, 0.8666666666666667, 0.45, 0.5208333333333333, 0.8416666666666667, 0.48484848484848486, 0.48981481481481487, 0.40925925925925927, 0.2888888888888889, 0.6, 0.4666666666666666, 0.6261363636363636, 0.5622574955908289, 0.75, 0.44285714285714284, 0.44629629629629636, 0.8, 0.3698412698412698, 0.6722222222222222, 0.75, 1.0, 0.5750000000000001, 0.32500000000000007, 0.4, 0.5599999999999999, 0.65, 1.0, 0.8, 0.2553846153846154, 0.5755853994490359, 0.5666666666666668, 0.5, 0.5, 0.3066666666666667, 0.75, 0.3, 0.55, 0.6, 0.42727272727272725, 0.5721726190476191, 0.4341156462585034, 0.638888888888889, 0.4166666666666667, 0.40833333333333327, 0.17083333333333334, 0.6, 0.3645833333333333, 0.55, 0.5077922077922079, 0.8, 0.5274621212121212, 0.875, 0.75, 0.6000000000000001, 0.0, 0.5225000000000001, 0.4208333333333333, 0.5007575757575758, 0.5458333333333333, 0.7364583333333332, 0.6666666666666666, 0.7638888888888888, 0.5333333333333333, 0.54, 0.61, 0.5625, 0.5931818181818181, 0.6666666666666666, 0.3, 0.675, 0.5493055555555556, 0.3, 0.65, 0.9166666666666666, 0.3875, 0.475, 0.5111111111111111, 0.5245265151515152, 0.5105, 0.5357142857142857, 0.48095238095238096, 0.595, 0.0, 0.6375, 0.43443452380952385, 0.4161552028218695, 0.45, 0.4444444444444444, 0.7, 0.38387755102040816, 0.0, 0.1, 0.6125, 0.4, 0.3857142857142858, 0.0, 0.37083333333333335, 0.7700000000000001, 0.47500000000000003, 0.55, 0.38484848484848483, 0.4916666666666667, 0.5083333333333333, 0.3888888888888889, 0.425, 0.75, 0.5, 0.5, 0.625, 0.44125000000000003, 0.4178571428571428, 0.34333333333333343, 0.65, 0.7444444444444445, 0.6499999999999999, 0.4, 0.4666666666666666, 0.6, 0.3263888888888889, 0.2375, 0.3, 0.675, 0.35833333333333334, 0.4902777777777778, 0.4772727272727273, 0.42272727272727273, 0.6000000000000001, 0.6, 0.625, 0.4708333333333333, 0.0, 0.55, 0.5, 0.3871047619047619, 0.0, 0.3, 0.7379761904761905, 0.5166666666666667, 0.6042857142857142, 0.46071428571428574, 0.6057777777777777, 0.5, 0.05, 0.6729166666666667, 0.6166666666666667, 0.56, 0.0, 0.5083333333333333, 0.5597222222222222, 0.7962962962962963, 0.6009090909090908, 0.85, 0.4261111111111111, 0.6000000000000001, 0.4666666666666666, 0.4, 0.4366666666666667, 0.75, 0.4027083333333333, 0.74375, 0.5277777777777778, 0.5055555555555555, 0.5725, 0.7, 0.5462962962962963, 0.5, 0.6333333333333333, 0.33499999999999996, 0.49444444444444446, 0.5397727272727273, 0.4208333333333333, 0.3904761904761905, 0.41666666666666663, 0.35000000000000003, 0.35000000000000003, 0.65, 0.4888888888888889, 0.4583333333333333, 0.578198653198653, 0.64, 0.25, 0.0, 0.7388888888888889, 0.7266666666666667, 0.5141534391534391, 0.6169270833333333, 1.0, 0.35, 0.44999999999999996, 0.9, 0.3333333333333333, 0.6, 0.0, 0.5333333333333333, 0.7430555555555557, 0.6571428571428571, 0.25, 0.5833333333333334, 0.7, 0.5636363636363637, 0.3, 0.6000000000000001, 0.4875, 0.4181818181818182, 0.8333333333333334, 0.39166666666666666, 0.3666666666666667, 0.75, 0.45064935064935063, 0.46666666666666673, 0.6014705882352942, 0.74, 0.45454545454545453, 0.5841596638655462, 0.7000000000000001, 0.0, 0.6, 0.5666666666666667, 0.75, 0.48484848484848486, 0.5724358974358975, 0.5520833333333334, 0.5333333333333333, 0.6541666666666667, 0.3333333333333333, 0.6115151515151516, 0.35000000000000003, 0.6928571428571428, 0.6333333333333333, 0.4076190476190476, 0.5375, 0.625, 0.6000000000000001, 0.3125, 0.5272727272727272, 0.4425, 0.6166666666666666, 0.4975993703266429, 0.34375, 0.725, 0.5438888888888889, 0.6741666666666667, 0.125, 0.0, 0.5937499999999999, 0.8333333333333334, 0.6611111111111111, 0.34880952380952385, 0.42074829931972785, 0.6708333333333334, 0.5714285714285714, 0.625, 0.8, 0.39999999999999997, 0.47806122448979593, 0.4361111111111111, 0.48655555555555546, 0.34, 0.6, 0.8181818181818182, 0.48125, 0.65, 0.8888888888888888, 0.5650000000000001, 0.7272727272727273, 0.5499999999999999, 0.5222222222222221, 0.46666666666666673, 0.6333333333333333, 0.4362244897959184, 0.6444444444444445, 0.6875, 0.4982142857142857, 0.4749999999999999, 0.3666666666666667, 0.675, 0.25, 0.5800000000000001, 0.5900000000000001, 0.5555555555555556, 0.0, 0.6757575757575758, 0.8333333333333334, 0.7125, 0.0, 0.13333333333333333, 0.6294642857142857, 0.48750000000000004, 0.4, 0.6000000000000001, 0.7999999999999999, 0.48398268398268396, 0.32727272727272727, 0.625, 0.6000000000000001, 0.7435714285714285, 0.5446296296296297, 0.5, 0.5, 0.35000000000000003, 0.4476190476190476, 0.532912457912458, 0.8333333333333334, 0.0, 0.625, 0.39904607297464434, 0.6138888888888888, 0.49242424242424243, 0.478968253968254, 0.75, 1.0, 0.38095238095238093, 0.38533333333333336, 0.5696428571428572, 0.0, 0.63, 0.22500000000000003, 0.6000000000000001, 0.6000000000000001, 1.0, 0.5708333333333334, 0.4666666666666666, 0.4666666666666666, 0.8, 0.45999999999999996, 0.5819444444444445, 0.5318181818181819, 0.5891666666666666, 0.55, 0.2863636363636364, 0.7916666666666667, 0.5, 0.25, 1.0, 0.49499999999999994, 0.45000000000000007, 0.6694444444444444, 0.4055555555555556, 0.5722222222222222, 0.3959183673469388, 0.5, 0.57, 0.03333333333333333, 0.46666666666666673, 0.65, 0.8333333333333334, 0.475, 0.4076388888888889, 0.7, 0.4057936507936509, 0.41, 0.3333333333333333, 0.7177777777777777, 0.7, 0.8666666666666667, 0.37916666666666665, 0.3, 0.7392857142857142, 0.41633333333333333, 0.30196078431372547, 0.4277777777777778, 0.6583333333333333, 0.5, 0.4, 0.6666666666666667, 0.6000000000000001, 0.0, 0.4526515151515151, 0.0, 0.525, 0.45454545454545453, 0.4, 0.6, 0.5, 0.625, 0.3033333333333333, 0.3787265764538492, 0.725, 0.3375, 0.6875, 0.75, 0.27090909090909093, 0.0, 0.5249999999999999, 0.3, 0.5, 0.5437878787878788, 0.7000000000000001, 0.41999999999999993, 0.7000000000000001, 0.6260101010101009, 0.8, 0.8, 0.66875, 0.6366666666666666, 0.35, 0.7125, 0.4, 0.0, 0.2908424908424908, 0.4646464646464647, 0.71875, 0.5683333333333334, 0.42000000000000004, 0.6, 0.775, 0.6125, 0.41250000000000003, 0.4, 0.43333333333333335, 0.375, 0.5098809523809524, 0.7, 0.75, 0.0, 0.2125, 0.6166666666666667, 0.6057142857142856, 0.41217687074829923, 0.5, 0.525, 0.5257575757575758, 0.0, 0.6900000000000001, 0.42500000000000004, 0.75, 0.56, 0.6, 0.5833333333333334, 0.7933333333333334, 0.740625, 0.4444444444444444, 0.4909523809523809, 0.0, 0.0, 0.6, 0.6375, 0.7875, 0.9333333333333332, 0.825, 0.6625, 0.3, 0.806, 0.5416666666666666, 0.5570105820105821, 0.4863636363636364, 0.6326388888888889, 0.75, 0.4425, 0.5499999999999999, 0.61, 0.5896464646464646, 0.375, 0.5125, 0.6000000000000001, 0.55, 0.725, 0.7083333333333333, 0.7500000000000001, 0.6166666666666667, 0.45, 0.65, 0.625, 0.775, 0.0, 0.2, 0.0, 0.75, 0.4380519480519481, 0.5619047619047618, 0.5708333333333333, 0.3833333333333333, 0.7000000000000001, 0.48124999999999996, 0.34722222222222215, 0.675, 0.34722222222222215, 0.34722222222222215, 0.8125, 0.49474789915966383, 0.6428571428571429, 0.6555555555555556, 0.0, 0.5740000000000001, 0.625, 0.3, 0.4533333333333333, 0.3125, 0.5183333333333333, 0.5272727272727273, 0.6178571428571429, 0.37727272727272726, 0.5855952380952381, 0.5712301587301588, 0.5630176767676768, 0.68, 0.0, 0.4122619047619048, 0.5006395120031484, 0.75, 0.6345238095238095, 0.7958333333333334, 0.475, 0.75, 0.51, 0.37916666666666665, 0.7698863636363636, 0.75, 0.3, 0.15, 0.5541666666666667, 0.5077922077922078, 0.5, 0.3583333333333334, 0.501, 0.5625000000000001, 0.6875, 0.4666666666666667, 0.525, 0.5488095238095237, 0.45999999999999996, 0.825, 0.6333333333333333, 0.8, 0.0, 0.46249999999999997, 0.412979797979798, 0.7, 0.45555555555555555, 0.3583333333333334, 0.7000000000000001, 0.48484848484848486, 0.75, 0.4666666666666667, 0.578125, 0.55, 0.8, 0.45729166666666665, 0.4231481481481481, 0.5916666666666667, 0.64, 1.0, 0.75, 0.7625, 0.6305555555555556, 0.32142857142857145, 0.3935064935064934, 0.55, 0.36, 0.4239463601532567, 0.5753787878787878, 0.36354935913759445, 0.46666666666666673, 0.55, 0.31999999999999995, 0.3666666666666667, 0.41428571428571426, 0.3258928571428571, 0.6012500000000001, 0.625, 0.44642857142857145, 0.675925925925926, 1.0, 0.5883333333333333, 0.5, 0.6000000000000001, 0.6085714285714287, 0.5583333333333332, 0.26666666666666666, 0.5416666666666666, 0.75, 0.7111111111111111, 0.423336038961039, 0.49126984126984125, 0.5666666666666667, 0.125, 0.5564814814814815, 0.5130681818181818, 0.3416666666666667, 0.43402777777777773, 0.3348484848484849, 0.483982683982684, 0.47314814814814815, 0.7250000000000001, 0.3125, 0.42037037037037034, 0.5341666666666667, 0.42500000000000004, 0.5333333333333333, 0.5454545454545454, 0.6683333333333333, 0.6000000000000001, 0.625, 0.625, 0.46408730158730155, 0.5750000000000001, 0.5853535353535354, 0.7030303030303031, 0.5962962962962963, 0.26515151515151514, 0.5, 0.3820833333333333, 0.5666666666666668, 0.625, 0.37, 0.5055555555555555, 0.3745833333333333, 0.5425, 0.5701388888888889, 0.725, 0.4616666666666666, 0.15, 0.5666666666666667, 0.5214285714285715, 0.5, 0.2333333333333333, 0.7333333333333334, 0.262962962962963, 0.6375000000000001, 0.54125, 0.8766666666666666, 0.7, 0.6151428571428571, 0.5442777777777777, 0.65, 0.27499999999999997, 0.5833333333333334, 0.5388888888888889, 0.6000000000000001, 0.5125, 0.7577777777777778, 0.6487654320987654, 0.4375, 0.3666666666666667, 0.5772727272727273, 0.5783333333333334, 0.6022727272727273, 0.55, 0.6319444444444444, 0.6319444444444444, 0.6666666666666666, 0.65, 0.39499999999999996, 0.20000000000000004, 0.675, 0.5916666666666667, 0.5619047619047618, 0.6136363636363636, 0.62, 1.0, 0.6000000000000001, 0.125, 0.5110544217687074, 0.32962962962962966, 0.6068181818181819, 0.44, 0.6773809523809524, 0.47333333333333333, 0.44999999999999996, 0.5027000777000776, 0.7095238095238094, 0.5, 0.75, 0.3125, 0.3317333333333333, 0.490625, 0.625, 1.0, 0.5416666666666666, 0.4208333333333334, 0.6352813852813853, 0.562121212121212, 0.77, 0.22962962962962963, 0.64, 0.6630952380952381, 0.5241666666666667, 0.4630681818181818, 0.5142857142857143, 0.4336931818181818, 0.5270833333333332, 0.55, 0.8125, 0.7000000000000001, 0.7, 0.5625, 0.4794444444444445, 0.18541666666666667, 0.356, 0.5174603174603174, 0.6911255411255411, 0.525, 0.5152777777777778, 0.45, 0.5703703703703703, 0.5708333333333333, 0.33749999999999997, 0.6592857142857144, 0.3958333333333333, 0.40595238095238095, 0.4471590909090909, 0.5200000000000001, 0.1875, 0.44499999999999995, 0.65, 0.32222222222222224, 0.5, 0.6000000000000001, 0.5388888888888889, 0.8125, 0.4, 0.4, 0.21333333333333332, 0.5628205128205128, 0.48035714285714287, 0.35, 0.75, 0.8333333333333334, 0.75, 0.5097222222222223, 0.75, 0.1, 0.665, 0.615, 0.725, 0.392, 0.48142857142857143, 0.42749999999999994, 0.6125, 0.1, 0.4643939393939394, 0.7444444444444445, 0.47500000000000003, 0.3666666666666667, 0.20833333333333334, 0.375, 0.6321428571428571, 0.4861111111111111, 1.0, 0.5472222222222222, 0.4, 0.7933333333333333, 0.5222222222222223, 0.6847222222222222, 0.5920482295482297, 0.525, 0.5599999999999999, 0.581, 0.3333333333333333, 0.7000000000000001, 0.3458333333333333, 0.5333333333333333, 0.45, 0.2857142857142857, 0.3815705128205128, 0.625, 0.34, 0.4625, 0.0, 0.7109090909090909, 0.6666666666666666, 0.5007575757575758, 0.6, 0.7886363636363636, 0.4404761904761904, 0.3888888888888889, 0.7100000000000001, 0.75, 0.75, 1.0, 0.6666666666666666, 0.5888888888888889, 0.75, 0.640625, 0.7675000000000001, 0.4916666666666667, 0.45416666666666666, 0.6666666666666666, 0.1, 0.6000000000000001, 0.42860873694207036, 0.5909090909090909, 0.5943722943722943, 0.6716666666666667, 0.7, 0.8, 0.5992704826038159, 0.4181818181818182, 0.0, 0.776, 0.6, 0.5609090909090909, 0.3125, 0.5418367346938775, 0.525, 0.6999999999999998, 0.5181318681318682, 0.21428571428571427, 0.7833333333333333, 0.8181818181818182, 0.26666666666666666, 0.45, 0.5943181818181817, 0.4916666666666667, 0.5708333333333333, 0.5157207977207977, 0.5348484848484848, 0.6979166666666666, 0.5603174603174603, 0.55, 0.51875, 0.6699999999999999, 0.625, 0.9099999999999999, 0.25, 0.43333333333333335, 0.42, 0.6183333333333333, 0.5333333333333333, 0.4916666666666667, 0.47056818181818183, 0.43124999999999997, 0.3, 0.625, 0.5928571428571429, 0.756, 0.4909090909090909, 0.4019480519480519, 0.44791666666666663, 0.6488095238095238, 0.5333333333333333, 0.7000000000000001, 0.296875, 0.7166666666666668, 0.6000000000000001, 0.5957777777777779, 0.4823863636363636, 0.25, 0.6208333333333332, 0.5666666666666668, 0.34520202020202023, 0.625, 0.4437109187109187, 0.3, 0.6000000000000001, 0.5666666666666667, 0.5333333333333333, 0.5472222222222223, 0.5833333333333334, 0.5416666666666666, 0.6499999999999999, 0.65, 0.5892857142857143, 0.5596153846153846, 0.4485185185185185, 0.705, 0.42500000000000004, 0.6535714285714286, 0.5238095238095238, 0.5988636363636364, 0.5777777777777778, 0.6666666666666666, 0.6246031746031745, 0.6708333333333333, 0.5647727272727273, 0.6309523809523809, 0.5444444444444444, 0.7, 0.4416666666666667, 1.0, 0.74, 0.4714285714285715, 0.5708333333333333, 0.4625, 0.403030303030303, 0.3, 0.49350649350649345, 0.55, 0.54, 0.5212878787878789, 0.4776190476190476, 0.5333333333333333, 0.3991341991341992, 0.38, 0.44226190476190474, 0.41875, 0.0, 0.7173809523809523, 0.8, 0.4666666666666666, 0.75, 0.6119047619047618, 0.7166666666666667, 0.4413888888888889, 0.38888888888888884, 0.0, 0.0, 0.6416666666666666, 0.24062500000000003, 0.519047619047619, 0.5611111111111111, 0.42500000000000004, 1.0, 0.5916666666666667, 0.375, 0.4666666666666666, 0.5678571428571428, 0.6116666666666666, 0.3555555555555556, 0.5125, 0.6200000000000001, 0.2, 0.5483333333333333, 0.8000000000000002, 0.50625, 0.44523809523809516, 0.038461538461538464, 0.75, 0.3666666666666667, 0.53, 0.6166666666666666, 0.4842857142857144, 0.34722222222222215, 0.6311111111111111, 0.6271428571428571, 0.55, 0.725, 0.5875, 0.38333333333333336, 0.43124999999999997, 0.5666666666666667, 0.55, 0.47000000000000003, 0.6166666666666667, 0.0, 0.4777777777777778, 0.4, 0.6111111111111112, 0.4464896214896215, 0.31805555555555554, 0.5958333333333333, 0.5875, 0.49023809523809525, 0.59375, 0.5178654678654678, 0.44999999999999996, 0.37, 0.6, 0.666, 0.5055555555555555, 0.25, 0.625, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5972222222222222, 0.5081249999999999, 0.475, 0.5576719576719577, 0.42500000000000004, 0.875, 0.5875, 0.0, 0.48750000000000004, 0.45749999999999996, 0.7166666666666666, 0.48055555555555557, 0.6666666666666666, 0.5625, 0.5133333333333333, 0.6952380952380953, 0.48, 0.825, 0.3273809523809524, 0.5597222222222222, 0.7825, 0.75, 0.85, 0.75, 0.875, 0.47750000000000004, 0.60625, 0.2, 0.6099999999999999, 0.2, 0.6536931818181818, 0.5819444444444445, 0.38499999999999995, 0.7226666666666667, 0.616, 0.6728571428571429, 0.6333333333333334, 0.3333333333333333, 0.5089743589743589, 0.19999999999999998, 0.525, 0.46106519742883373, 0.6375000000000001, 0.4, 0.5404040404040403, 0.47346938775510206, 0.65, 0.43000000000000005, 0.8, 0.4625, 0.5444444444444445, 0.5375, 0.0625, 0.6333333333333333, 0.55, 0.7, 0.4604166666666667, 0.5062500000000001, 0.5933333333333334, 0.6043181818181819, 0.5610317460317461, 0.45625000000000004, 0.32962962962962966, 0.5888888888888889, 0.7625, 0.4433677685950413, 1.0, 0.725, 0.5535714285714285, 0.5194444444444445, 0.616, 0.5416666666666666, 0.55, 0.7178571428571429, 0.4577380952380952, 0.5052380952380953, 0.7416666666666667, 0.6694444444444444, 0.6, 0.5, 0.4768518518518518, 0.5666666666666668, 0.4222222222222222, 0.6166666666666667, 0.8500000000000001, 0.5535714285714286, 0.5304166666666668, 0.44375, 0.5756190476190477, 0.6277777777777778, 0.5166666666666666, 0.35, 0.6933333333333334, 0.15151515151515152, 0.6000000000000001, 0.585, 0.5055555555555555, 0.6, 0.5433333333333333, 0.4583333333333333, 0.5419642857142857, 0.4962962962962963, 0.6642857142857144, 0.36250000000000004, 0.6321428571428572, 0.4083333333333334, 0.4166666666666667, 0.76, 0.5198412698412699, 0.4666666666666667, 0.5208333333333334, 0.5583333333333333, 0.4714285714285715, 0.575, 0.625, 0.6733333333333333, 0.825, 0.5555555555555555, 0.6449999999999999, 0.6075396825396825, 0.5162337662337663, 0.43600000000000005, 0.77, 0.48750000000000004, 0.4333333333333333, 0.5, 0.41500000000000004, 0.5, 0.4158008658008658, 0.5499999999999999, 0.4577777777777778, 0.515, 0.6515151515151515, 0.32, 0.6, 0.75, 0.4988111888111888, 0.4888888888888889, 0.5416666666666666, 0.7638888888888888, 0.5183333333333333, 0.5, 0.2, 0.38055555555555554, 0.5459876543209877, 0.645, 0.7666666666666666, 0.5, 0.18055555555555555, 0.7333333333333334, 0.3354166666666667, 0.84375, 0.6085714285714287, 0.48333333333333334, 0.4352083333333333, 0.48500000000000004, 0.85, 0.65, 0.36666666666666664, 0.66, 0.6125, 0.63, 0.5113636363636364, 0.5, 0.5625, 0.5071969696969697, 0.325, 0.6363636363636364, 0.6, 0.6, 0.31666666666666665, 0.675, 0.6283333333333333, 0.9444444444444444, 0.6375, 0.75, 0.5166666666666667, 0.5625, 0.5, 0.32999999999999996, 0.5625, 0.4129629629629629, 0.475, 0.41666666666666663, 0.7083333333333334, 0.8333333333333334, 0.65, 0.0, 0.5202380952380953, 0.4666666666666666, 0.6458333333333333, 0.775, 0.6531746031746033, 0.7083333333333334, 0.6124999999999999, 0.7208333333333333, 0.6000000000000001, 0.43863636363636366, 0.38055555555555554, 1.0, 0.52, 0.48484848484848486, 0.83, 0.5763888888888888, 0.7178571428571429, 0.6041005291005291, 0.58, 0.5773275058275058, 0.625, 0.3428571428571429, 0.45, 0.45777777777777773, 0.5119047619047619, 0.5, 0.5691183261183261, 0.6, 0.3125, 0.25, 0.5773809523809524, 0.2899350649350649, 0.5, 0.425, 0.6400000000000001, 0.275, 0.4166666666666667, 0.26944444444444443, 0.6803030303030303, 0.6166666666666667, 0.32777777777777783, 0.5549999999999999, 0.4, 0.43750000000000006, 0.3910353535353535, 0.6875, 0.5272727272727273, 0.5360805860805861, 0.44666666666666666, 0.43333333333333335, 0.8, 0.7296296296296297, 0.8035714285714286, 0.5, 0.0, 0.35151515151515156, 0.5700000000000001, 0.7666666666666666, 0.60625, 0.45333333333333337, 0.4944444444444444, 0.8265432098765433, 0.7095238095238096, 0.7178571428571429, 0.5125541125541125, 0.7833333333333332, 0.4129629629629629, 0.6076388888888888, 0.65, 1.0, 0.6399999999999999, 0.5136363636363637, 0.4515151515151515, 0.5255892255892256, 0.53, 0.4682539682539683, 0.67, 0.75, 0.41090909090909095, 0.4972222222222223, 0.8472222222222222, 0.0, 0.325, 0.125, 0.6035714285714286, 0.5708333333333333, 0.5, 0.7111111111111112, 0.7069444444444445, 0.4152777777777778, 0.55, 0.7902777777777779, 0.375, 0.41333333333333333, 0.365, 0.42523809523809525, 0.21785714285714286, 0.725, 0.1, 0.325, 0.48333333333333334, 0.6483333333333333, 0.0, 0.7833333333333333, 0.5833333333333334, 0.32765151515151514, 0.645, 0.6291666666666667, 0.2633333333333333, 0.7000000000000001, 0.4, 0.0, 1.0, 0.4859848484848485, 0.5333333333333333, 0.4409090909090909, 0.3444444444444444, 0.5083333333333333, 0.4666666666666666, 0.0, 0.3208333333333333, 0.45, 0.5666666666666667, 0.5666666666666667, 0.3333333333333333, 0.5214285714285715, 0.5999999999999999, 0.5260416666666667, 0.43, 0.5626984126984127, 0.4600000000000001, 0.3833333333333333, 0.3875, 0.35, 0.525, 0.6220097803431137, 0.75, 0.5642857142857143, 0.75, 0.680952380952381, 0.6444444444444445, 0.6, 0.44000000000000006, 0.3666666666666667, 0.5700000000000001, 0.5916666666666666, 0.6, 0.49523809523809526, 0.5095238095238096, 0.7238095238095239, 0.45999999999999996, 0.3875, 0.5833333333333334, 0.8266666666666665, 0.3, 0.35000000000000003, 0.65, 0.2541666666666667, 0.4181818181818182, 0.4711111111111111, 0.5428571428571428, 0.555, 0.65, 0.4416666666666667, 0.0, 0.46666666666666673, 0.81875, 0.5471153846153847, 0.5603846153846155, 0.4765476190476191, 0.4743620414673046, 0.6516666666666667, 0.540922619047619, 0.44172839506172834, 0.63, 0.2333333333333333, 0.5285714285714286, 0.7225, 0.6571428571428571, 0.6, 0.45000000000000007, 0.39285714285714285, 0.6875, 0.6, 0.6583333333333333, 0.3743506493506494, 0.48, 0.5416666666666666, 0.575, 0.49399999999999994, 0.41057823129251697, 0.4166666666666667, 0.4166666666666667, 0.17500000000000002, 0.7916666666666667, 0.4563888888888889, 0.3427777777777778, 0.5773809523809523, 0.5819047619047619, 0.6472222222222223, 0.6277777777777778, 0.725, 0.39030612244897966, 0.46875, 0.6625000000000001, 0.29000000000000004, 0.6291666666666667, 0.55, 0.5709090909090909, 0.35555555555555557, 0.6107142857142858, 0.6227777777777778, 0.462, 0.5773809523809523, 0.503030303030303, 0.4561904761904761, 0.27999999999999997, 0.5066666666666667, 0.5262536075036075, 0.5, 0.4, 0.7638888888888888, 0.2888888888888889, 0.5791666666666667, 0.5983333333333334, 0.6130000000000001, 0.4166666666666667, 0.6916666666666665, 0.42000000000000004, 0.4666666666666666, 0.39999999999999997, 0.5986111111111111, 0.625, 0.615909090909091, 0.5593333333333332, 0.55, 0.5328571428571428, 0.6111888111888113, 0.37407407407407406, 0.6574603174603174, 0.3474431818181818, 0.6952380952380953, 0.39726890756302524, 0.8166666666666667, 0.9, 0.39999999999999997, 0.5272727272727272, 0.625, 0.6166666666666667, 0.5729166666666666, 0.49444444444444446, 0.5, 0.5666666666666667, 0.5256410256410257, 0.6666666666666666, 0.49374999999999997, 0.42142857142857143, 0.39749999999999996, 0.1923076923076923, 0.21666666666666665, 0.54375, 0.4982683982683983, 0.3666666666666667, 0.55, 0.0, 0.49487179487179483, 0.6000000000000001, 0.5216666666666667, 0.5607142857142858, 0.6333333333333333, 0.5166666666666667, 0.44583333333333336, 0.675, 0.55, 0.6520833333333333, 0.7113636363636363, 0.5321428571428571, 0.6100000000000001, 0.325, 0.5966666666666667, 0.5992857142857143, 0.40095238095238095, 0.5058823529411764, 0.5541666666666666, 0.67, 0.4, 0.5447619047619048, 0.4068181818181818, 0.5472222222222222, 0.27651515151515155, 0.6, 0.5666666666666667, 0.496875, 0.7114285714285715, 0.5083333333333334, 0.4927777777777777, 1.0, 0.8083333333333333, 0.75, 0.0, 0.5972222222222222, 0.5033333333333333, 0.5708333333333333, 0.39166666666666666, 0.41666666666666663, 0.3625, 0.0, 0.5850000000000001, 0.6386363636363637, 0.49673382173382163, 0.6866666666666668, 0.6708333333333333, 0.6333333333333332, 0.4, 0.7636363636363637, 0.3666666666666667, 0.3, 0.5, 0.48270202020202024, 0.5215909090909091, 0.65, 0.5616666666666666, 0.0, 0.35000000000000003, 0.35984848484848486, 0.7238095238095238, 0.575, 0.6080519480519481, 0.5166666666666666, 0.7680555555555556, 0.5375, 0.31666666666666665, 0.44831945831945835, 0.45454545454545453, 0.5809523809523809, 0.74, 0.9333333333333332, 0.58, 0.5, 0.4602020202020202, 0.515, 0.6156060606060607, 0.3833333333333333, 0.69375, 0.75, 0.4377777777777777, 0.0, 0.35151515151515156, 0.75, 0.45454545454545453, 0.255952380952381, 0.5333333333333333, 0.0, 0.39999999999999997, 0.6, 0.43333333333333335, 0.61, 0.6333333333333333, 0.776, 0.43726325757575757, 0.25000000000000006, 0.5625, 0.75, 0.39623015873015877, 0.7125, 0.475, 0.38, 0.66, 0.0, 0.48055555555555557, 0.5322314049586777, 0.5164646464646464, 0.46818181818181825, 0.29500000000000004, 0.752, 0.3333333333333333, 0.516, 0.9, 0.4000000000000001, 0.4649350649350649, 0.5333333333333333, 0.30388888888888893, 0.7000000000000001, 0.41125, 0.3525, 0.6014285714285714, 0.65, 0.47500000000000003, 0.7333333333333334, 0.44999999999999996, 0.44999999999999996, 0.43100000000000005, 0.5, 0.30833333333333335, 0.6625, 0.675, 0.6386363636363637, 0.2833333333333333, 0.0, 0.4800000000000001, 0.345, 0.65, 0.5761904761904761, 0.7000000000000001, 0.5625, 0.6392857142857143, 0.5208333333333334, 0.5104166666666666, 0.3339285714285714, 0.41571428571428576, 0.4166666666666667, 0.8, 0.34, 0.5800000000000001, 0.61875, 0.43333333333333335, 0.510909090909091, 0.56875, 0.7333333333333333, 0.590625, 0.30833333333333335, 0.6792207792207793, 0.4083333333333333, 0.4092857142857143, 1.0, 0.5041666666666667, 0.5625, 0.52, 1.0, 0.6714285714285715, 0.45, 0.56875, 0.7051851851851852, 0.7424242424242425, 0.5083333333333333, 0.75, 0.4893535353535353, 0.75625, 0.5333333333333333, 0.4470779220779221], "name": "subjectivity", "text": "", "line": {"color": "rgba(62, 111, 176, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}], {"legend": {"bgcolor": "#FFFFFF", "font": {"color": "#666666"}}, "paper_bgcolor": "#FFFFFF", "plot_bgcolor": "#E5E5E5", "yaxis1": {"tickfont": {"color": "#666666"}, "gridcolor": "#F6F6F6", "titlefont": {"color": "#666666"}, "zerolinecolor": "#F6F6F6", "showgrid": true, "title": "Values"}, "xaxis1": {"tickfont": {"color": "#666666"}, "gridcolor": "#F6F6F6", "titlefont": {"color": "#666666"}, "zerolinecolor": "#F6F6F6", "showgrid": true, "title": "Time"}, "titlefont": {"color": "#151516"}, "title": "Polarity and Subjectivity"}, {"showLink": true, "linkText": "Export to plot.ly"})});</script>


* average sentiment over day of the week
* average sentiment over weekend vs weekday
* average sentiment over year 
* average sentiment over quarter of year
* topic modeling
* word cloud
* network analysis of words/Network Graph Visualization
* radar chart
* LSTM Model,naive bayes,svm


```python
series = AllData['Reviewclass'].value_counts()
series.iplot(kind='barh', xTitle='Frequency', title='Review Class')
```


<div id="b962983a-d122-4399-85f7-c9eef7eecce6" style="height: 525px; width: 100%;" class="plotly-graph-div"></div><script type="text/javascript">require(["plotly"], function(Plotly) { window.PLOTLYENV=window.PLOTLYENV || {};window.PLOTLYENV.BASE_URL="https://plot.ly";Plotly.newPlot("b962983a-d122-4399-85f7-c9eef7eecce6", [{"type": "bar", "x": [1499, 249, 121], "y": ["Positive", "Negative", "Neutral"], "name": "Reviewclass", "text": "", "marker": {"color": "rgba(226, 74, 51, 0.6)", "line": {"color": "rgba(226, 74, 51, 1.0)", "width": 1}}, "orientation": "h"}], {"legend": {"bgcolor": "#FFFFFF", "font": {"color": "#666666"}}, "paper_bgcolor": "#FFFFFF", "plot_bgcolor": "#E5E5E5", "yaxis1": {"tickfont": {"color": "#666666"}, "gridcolor": "#F6F6F6", "titlefont": {"color": "#666666"}, "zerolinecolor": "#F6F6F6", "showgrid": true, "title": ""}, "xaxis1": {"tickfont": {"color": "#666666"}, "gridcolor": "#F6F6F6", "titlefont": {"color": "#666666"}, "zerolinecolor": "#F6F6F6", "showgrid": true, "title": "Frequency"}, "titlefont": {"color": "#151516"}, "title": "Review Class"}, {"showLink": true, "linkText": "Export to plot.ly"})});</script>



```python

# change the type of timestamp column for plotting
AllData['Date'] = pd.to_datetime(AllData['Date'])


# the day of the week (Monday=0, Sunday=6) and if it's a week end day or week day.
AllData['DayOfTheWeek'] = AllData['Date'].dt.dayofweek
AllData['Year'] = AllData['Date'].dt.year
AllData['Month'] = AllData['Date'].dt.month
AllData['Week'] = AllData['Date'].dt.week
AllData['Quarter'] = AllData['Date'].dt.quarter
```


```python
AllData.info()
```

    <class 'pandas.core.frame.DataFrame'>
    Int64Index: 1869 entries, 0 to 1868
    Data columns (total 18 columns):
    Unnamed: 0        1869 non-null int64
    Unnamed: 0.1      1869 non-null int64
    Unnamed: 0.1.1    1869 non-null int64
     Job              1869 non-null object
    Date              1869 non-null datetime64[ns]
    Jobstatus         1869 non-null object
    Location          1869 non-null object
    Text              1869 non-null object
    Title             1864 non-null object
    polarity          1869 non-null float64
    subjectivity      1869 non-null float64
    Reviewclass       1869 non-null object
    weekday           1869 non-null int64
    DayOfTheWeek      1869 non-null int64
    Year              1869 non-null int64
    Month             1869 non-null int64
    Week              1869 non-null int64
    Quarter           1869 non-null int64
    dtypes: datetime64[ns](1), float64(2), int64(9), object(6)
    memory usage: 357.4+ KB



```python

AllData4=AllData.groupby('Year').mean()[['polarity','subjectivity']]


AllData4[['polarity', 'subjectivity']].iplot(kind='scatter', up_color='#482878FF', down_color='#1F9E89FF', theme='solar', 
                                           title='Average Polarity and Subjectivity', xTitle='Year',yTitle='Values')



```


<div id="1cae9031-a508-4f54-bab3-83da76b73be9" style="height: 525px; width: 100%;" class="plotly-graph-div"></div><script type="text/javascript">require(["plotly"], function(Plotly) { window.PLOTLYENV=window.PLOTLYENV || {};window.PLOTLYENV.BASE_URL="https://plot.ly";Plotly.newPlot("1cae9031-a508-4f54-bab3-83da76b73be9", [{"type": "scatter", "x": [2012, 2013, 2014, 2015, 2016, 2017, 2018], "y": [0.24791070030996074, 0.26746007586489073, 0.30304844256139324, 0.2740352002160356, 0.19226555657062588, 0.2415427079913481, 0.197237165018471], "name": "polarity", "text": "", "line": {"color": "rgba(255, 153, 51, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}, {"type": "scatter", "x": [2012, 2013, 2014, 2015, 2016, 2017, 2018], "y": [0.5110204875624771, 0.5192362871137246, 0.5190461938313675, 0.5344381926488777, 0.5484579951142239, 0.5291685690033022, 0.5230259915505343], "name": "subjectivity", "text": "", "line": {"color": "rgba(55, 128, 191, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}], {"legend": {"bgcolor": "#151516", "font": {"color": "#D9D9D9"}}, "paper_bgcolor": "#151516", "plot_bgcolor": "#151516", "yaxis1": {"tickfont": {"color": "#C2C2C2"}, "gridcolor": "#434343", "titlefont": {"color": "#D9D9D9"}, "zerolinecolor": "#666570", "showgrid": true, "title": "Values"}, "xaxis1": {"tickfont": {"color": "#C2C2C2"}, "gridcolor": "#434343", "titlefont": {"color": "#D9D9D9"}, "zerolinecolor": "#666570", "showgrid": true, "title": "Time"}, "titlefont": {"color": "#D9D9D9"}, "title": "Average Polarity and Subjectivity"}, {"showLink": true, "linkText": "Export to plot.ly"})});</script>



```python

AllData5=AllData.groupby('DayOfTheWeek').mean()[['polarity','subjectivity']]


AllData5[['polarity', 'subjectivity']].iplot(kind='scatter', up_color='#482878FF', down_color='#1F9E89FF', theme='pearl', 
                                           title='Average Polarity and Subjectivity', xTitle='Day of The Week',yTitle='Values')



```


<div id="cb2b8427-abe2-44d2-b622-2e405030ff55" style="height: 525px; width: 100%;" class="plotly-graph-div"></div><script type="text/javascript">require(["plotly"], function(Plotly) { window.PLOTLYENV=window.PLOTLYENV || {};window.PLOTLYENV.BASE_URL="https://plot.ly";Plotly.newPlot("cb2b8427-abe2-44d2-b622-2e405030ff55", [{"type": "scatter", "x": [0, 1, 2, 3, 4, 5, 6], "y": [0.27307863827041395, 0.24609090091578983, 0.22741821437877763, 0.24902699446840965, 0.2442750303783234, 0.2751514661455137, 0.2363192704395123], "name": "polarity", "text": "", "line": {"color": "rgba(255, 153, 51, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}, {"type": "scatter", "x": [0, 1, 2, 3, 4, 5, 6], "y": [0.5221389378643486, 0.5277936955915633, 0.5523462700376438, 0.5287748815263777, 0.5180664939187783, 0.5277707402513951, 0.4944814936937063], "name": "subjectivity", "text": "", "line": {"color": "rgba(55, 128, 191, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}], {"legend": {"bgcolor": "#F5F6F9", "font": {"color": "#4D5663"}}, "paper_bgcolor": "#F5F6F9", "plot_bgcolor": "#F5F6F9", "yaxis1": {"tickfont": {"color": "#4D5663"}, "gridcolor": "#E1E5ED", "titlefont": {"color": "#4D5663"}, "zerolinecolor": "#E1E5ED", "showgrid": true, "title": "Values"}, "xaxis1": {"tickfont": {"color": "#4D5663"}, "gridcolor": "#E1E5ED", "titlefont": {"color": "#4D5663"}, "zerolinecolor": "#E1E5ED", "showgrid": true, "title": "Day of The Week"}, "titlefont": {"color": "#4D5663"}, "title": "Average Polarity and Subjectivity"}, {"showLink": true, "linkText": "Export to plot.ly"})});</script>



```python
AllData6=AllData.groupby('Month').mean()



AllData6[['polarity', 'subjectivity']].iplot(kind='scatter', theme='space', 
                                           title='Average Polarity and Subjectivity', xTitle='Month ',yTitle='Values')




```


<div id="bc37d0ac-e91d-4ade-8e8f-545af27f70dc" style="height: 525px; width: 100%;" class="plotly-graph-div"></div><script type="text/javascript">require(["plotly"], function(Plotly) { window.PLOTLYENV=window.PLOTLYENV || {};window.PLOTLYENV.BASE_URL="https://plot.ly";Plotly.newPlot("bc37d0ac-e91d-4ade-8e8f-545af27f70dc", [{"type": "scatter", "x": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], "y": [0.2508746536554806, 0.2776849691004806, 0.2474132806012403, 0.2729863364616377, 0.26358182604345004, 0.25452853465416575, 0.24980268808200076, 0.24618060197551106, 0.26238266878922895, 0.16359280689475958, 0.28371221063657714, 0.29719709185688375], "name": "polarity", "text": "", "line": {"color": "rgba(255, 153, 51, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}, {"type": "scatter", "x": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12], "y": [0.5478300041801365, 0.5335193978986498, 0.5196562074293444, 0.5219135242967393, 0.5565621243953159, 0.5234053736990842, 0.4989857201880224, 0.5071131585181466, 0.5129876532447216, 0.5478884953683996, 0.5397166631326362, 0.5017631516502287], "name": "subjectivity", "text": "", "line": {"color": "rgba(55, 128, 191, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}], {"legend": {"bgcolor": "#1A1A1C", "font": {"color": "#D9D9D9"}}, "paper_bgcolor": "#1A1A1C", "plot_bgcolor": "#1A1A1C", "yaxis1": {"tickfont": {"color": "#C2C2C2"}, "gridcolor": "#434343", "titlefont": {"color": "#D9D9D9"}, "zerolinecolor": "#666570", "showgrid": true, "title": "Values"}, "xaxis1": {"tickfont": {"color": "#C2C2C2"}, "gridcolor": "#434343", "titlefont": {"color": "#D9D9D9"}, "zerolinecolor": "#666570", "showgrid": true, "title": "Month "}, "titlefont": {"color": "#D9D9D9"}, "title": "Average Polarity and Subjectivity"}, {"showLink": true, "linkText": "Export to plot.ly"})});</script>



```python
AllData7=AllData.groupby('Week').mean()



AllData7[['polarity', 'subjectivity']].iplot(kind='scatter', theme='henanigans', 
                                           title='Average Polarity and Subjectivity', xTitle='Week ',yTitle='Values')





```


<div id="e3ae5996-6bff-4b25-8967-7c7bb66201e1" style="height: 525px; width: 100%;" class="plotly-graph-div"></div><script type="text/javascript">require(["plotly"], function(Plotly) { window.PLOTLYENV=window.PLOTLYENV || {};window.PLOTLYENV.BASE_URL="https://plot.ly";Plotly.newPlot("e3ae5996-6bff-4b25-8967-7c7bb66201e1", [{"type": "scatter", "x": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53], "y": [0.3022227238359889, 0.1978687750489221, 0.24605327294531848, 0.26601997264700195, 0.2794308630522916, 0.20621088174840715, 0.31515096887239746, 0.3024676887926888, 0.252289044545989, 0.26769460227272723, 0.24379865210207957, 0.275818276373832, 0.24093004344140703, 0.28988279011006285, 0.25509641720431986, 0.24244704265268785, 0.3025440453959361, 0.27817275444613104, 0.2604655570001314, 0.2507067120122676, 0.2712705498866213, 0.2615590479479369, 0.27036022211915073, 0.324952948800171, 0.16601849624997772, 0.25702152460670585, 0.23680316321105802, 0.25577185100564725, 0.20713679331057383, 0.28776601512965155, 0.2386591502983548, 0.22725525342712843, 0.2518628403061273, 0.26056163940997273, 0.23405688755688756, 0.29877869389382544, 0.23015955635273813, 0.2908919144144381, 0.21402320026203953, 0.2813351162560983, 0.09774270251970306, 0.19958242672486862, 0.20589533422701037, 0.23922123015873017, 0.29308921946537686, 0.3077656709387479, 0.2400938844775743, 0.3046099206349206, 0.22467398518718174, 0.2756724104961804, 0.3996611589468733, 0.30192623514052086, 0.6666666666666666], "name": "polarity", "text": "", "line": {"color": "rgba(255, 153, 51, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}, {"type": "scatter", "x": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53], "y": [0.5245422190634237, 0.5426204321204321, 0.5613158467476649, 0.5701538665609283, 0.4982126125197555, 0.5412234968785005, 0.5189159570588143, 0.5872041654641655, 0.5282411048313828, 0.4793222427649512, 0.5213869458647684, 0.5316034377145488, 0.5387608697634921, 0.53069954104045, 0.5253541016987067, 0.5075451463112755, 0.5407875918043985, 0.548889913982122, 0.5717932121070418, 0.5381537330981776, 0.5382916537827251, 0.5352604579919396, 0.5256798483703248, 0.5915812824007269, 0.519654341347463, 0.5070040103731066, 0.459506432748538, 0.4939992985409653, 0.5065389023803658, 0.4877532711506994, 0.4885897612488522, 0.5262367161195286, 0.4762602150507243, 0.5436881240981241, 0.5054168794168794, 0.5332443165995798, 0.4701460183034858, 0.5097803182959739, 0.5130249314177885, 0.5109897300450872, 0.5835970315451742, 0.4830753839184071, 0.5591958208300537, 0.5646038176072898, 0.5105506595599186, 0.5304324941440326, 0.5416748233116326, 0.5692275793650794, 0.46011837761340263, 0.5003078396917892, 0.5461354386354386, 0.5137075688861403, 0.7833333333333333], "name": "subjectivity", "text": "", "line": {"color": "rgba(55, 128, 191, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}], {"legend": {"bgcolor": "#242424", "font": {"color": "#F4F4F4"}}, "paper_bgcolor": "#242424", "plot_bgcolor": "#242424", "yaxis1": {"tickfont": {"color": "#A4A4A4"}, "gridcolor": "#343434", "titlefont": {"color": "#A4A4A4"}, "zerolinecolor": "#444444", "showgrid": true, "title": "Values"}, "xaxis1": {"tickfont": {"color": "#A4A4A4"}, "gridcolor": "#343434", "titlefont": {"color": "#A4A4A4"}, "zerolinecolor": "#444444", "showgrid": true, "title": "Week "}, "titlefont": {"color": "#F4F4F4"}, "title": "Average Polarity and Subjectivity"}, {"showLink": true, "linkText": "Export to plot.ly"})});</script>



```python
AllData7=AllData.groupby('Quarter').mean()



AllData7[['polarity', 'subjectivity']].iplot(kind='scatter', theme='white', 
                                           title='Average Polarity and Subjectivity', xTitle='Quarter ',yTitle='Values')




```


<div id="a2020174-1555-422c-bd02-2be2566a1f7b" style="height: 525px; width: 100%;" class="plotly-graph-div"></div><script type="text/javascript">require(["plotly"], function(Plotly) { window.PLOTLYENV=window.PLOTLYENV || {};window.PLOTLYENV.BASE_URL="https://plot.ly";Plotly.newPlot("a2020174-1555-422c-bd02-2be2566a1f7b", [{"type": "scatter", "x": [1, 2, 3, 4], "y": [0.2576279342850913, 0.2642345839839939, 0.25295090420049243, 0.21968509348466894], "name": "polarity", "text": "", "line": {"color": "rgba(255, 153, 51, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}, {"type": "scatter", "x": [1, 2, 3, 4], "y": [0.5337055018129211, 0.5348329490460062, 0.506343738046399, 0.5357412519614678], "name": "subjectivity", "text": "", "line": {"color": "rgba(55, 128, 191, 1.0)", "width": 1.3, "dash": "solid"}, "mode": "lines"}], {"legend": {"bgcolor": "#FFFFFF", "font": {"color": "#4D5663"}}, "paper_bgcolor": "#FFFFFF", "plot_bgcolor": "#FFFFFF", "yaxis1": {"tickfont": {"color": "#4D5663"}, "gridcolor": "#E1E5ED", "titlefont": {"color": "#4D5663"}, "zerolinecolor": "#E1E5ED", "showgrid": true, "title": "Values"}, "xaxis1": {"tickfont": {"color": "#4D5663"}, "gridcolor": "#E1E5ED", "titlefont": {"color": "#4D5663"}, "zerolinecolor": "#E1E5ED", "showgrid": true, "title": "Quarter "}, "titlefont": {"color": "#4D5663"}, "title": "Average Polarity and Subjectivity"}, {"showLink": true, "linkText": "Export to plot.ly"})});</script>


#### Sentiment Analysis through LSTMs

Sentiment Analysis: the process of computationally identifying and categorizing opinions expressed in a piece of text, especially in order to determine whether the writer's attitude towards a particular topic, product, etc. is positive, negative, or neutral.


```python
x = []
y = []
for value in lines:
    temp = value.split('\t')
    x.append(temp[0])
    temp[1].replace('\n','')
    y.append(int(temp[1]))
    
    
    
    
from keras.preprocessing.text import Tokenizer

tokenizer = Tokenizer(num_words=2500,split=' ')
tokenizer.fit_on_texts(x)




## CODE
tokenizer = Tokenizer()
texts = ["The sun is shining in June!","September is grey.","Life is beautiful in August.","I like it","This and other things?"]
tokenizer.fit_on_texts(texts)
print(tokenizer.word_index)
tokenizer.texts_to_sequences(["June is beautiful and I like it!"])


from keras.preprocessing.sequence import pad_sequences

X = tokenizer.texts_to_sequences(x)
X = pad_sequences(X)



import numpy as np 
from sklearn.model_selection import train_test_split

Y = []
for val in y:
    if(val == 0):
        Y.append([1,0])
    else:
        Y.append([0,1])
Y = np.array(Y)

x_train, x_test, y_train, y_test = train_test_split(X,Y,train_size=0.8)



import keras 
from keras.layers import Embedding, LSTM, Dense
from keras.models import Sequential

model = Sequential()
model.add(Embedding(2500,128,input_length=X.shape[1],dropout=0.2))
model.add(LSTM(300, dropout_U=0.2,dropout_W=0.2))
model.add(Dense(2,activation='softmax'))

model.compile(loss=keras.losses.categorical_crossentropy,optimizer='adam',metrics=['accuracy'])

model.fit(x_train,y_train,epochs=10,verbose=2,batch_size=32)

print(model.evaluate(x_test,y_test)[1])
```

#### Generating Word Cloud


```python
import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
from sklearn.model_selection import train_test_split # function for splitting data to train and test sets

import nltk
from nltk.corpus import stopwords
from nltk.classify import SklearnClassifier

from wordcloud import WordCloud,STOPWORDS
import matplotlib.pyplot as plt
%matplotlib inline


from subprocess import check_output
from os import path
from wordcloud import WordCloud

d = path.dirname("/Users/nanaakwasiabayieboateng/PythonNLTK")




# Read the whole text.
text = str(AllData['Text'])

stopwords = set(STOPWORDS)
stopwords.add("Chrysler")

color = ['black','white'];

#background_color="white", max_words=2000, mask=text,
#               stopwords=stopwords, contour_width=3, contour_color='steelblue'
    
    
wordcloud = WordCloud(stopwords=stopwords, max_words=2000,
                      #contour_color='steelblue',
                      #contour_width=3,
                      background_color=color[1],
                      width=2500,
                      height=2000,max_font_size=400
                     ).generate(text)
plt.figure(1,figsize=(13, 13))
plt.imshow(wordcloud, interpolation='bilinear')
plt.axis('off')
plt.show()
    
#print("Positive words")
#wordcloud_draw(train_pos,'white')
#print("Negative words")
#wordcloud_draw(train_neg)
```


![png](output_115_0.png)


#### Topic Modelling  Latent Dirichlet Allocation (LDA)

We use NLTK’s Wordnet to find the meanings of words, synonyms, antonyms, and more. In addition, we use WordNetLemmatizer to get the root word.


```python
import nltk
nltk.download('wordnet')
from nltk.corpus import wordnet as wn
def get_lemma(word):
    lemma = wn.morphy(word)
    if lemma is None:
        return word
    else:
        return lemma
    
from nltk.stem.wordnet import WordNetLemmatizer
def get_lemma2(word):
    return WordNetLemmatizer().lemmatize(word)
```

    [nltk_data] Downloading package wordnet to
    [nltk_data]     /Users/nanaakwasiabayieboateng/nltk_data...
    [nltk_data]   Package wordnet is already up-to-date!

