---
layout: post
title: " Working with Python in R"
subtitle: python + Rstudio
#output: rmarkdown::github_document

output:
  html_document:
    keep_md: true    
    toc: true
    toc_float: TRUE
    theme: united
author: Nana Boateng
df_print: paged
Time: '2018-07-22 14:41:09'
date: "July 22, 2018"
toc_depth: 3  # upto three depths of headings (specified by #, ## and ###)
number_sections: true  ## if you want number sections at each table header
highlight: tango  # specifies the syntax highlighting style
tags:  python,reticulate,rstudio
---


Introduction
---------------------------------
Python and R are the most popular machine learning languages. Jupiter notebooks are the most popular platform for python users to write up and run code. Rmarkdown can also be used for this same purpose. The choice of which of these two largely depends on your goals, interest  and background.Those with a background in statistics overwhemly prefer to work in R wheareas those with computer science background prefer python. Which is better? R or Python is often asked.  Neither one is beter than the other. A third alternative I believe is using both together. The availability of libraries that allows you to work interchangeably between the two languages has made data science officialy agnostic. Examples of these packages include  rPython, PythonInR, reticulate , rJython, SnakeCharmR and XRPython.  




#### Load the required packages.


```r
pacman::p_load(skimr,kableExtra,tidyverse,reticulate,scales,viridis)
```



The  Python Engine
---------------------------------------------------

This is a  new Python language engine for R Markdown. It  supports bi-directional communication between R and Python (R chunks can access Python objects and vice-versa).


```python
import csv
import datetime
import re
import codecs
import requests
import pandas as pd
import random as r
# Importing Dataset
data = pd.read_excel("EmployeeAttrition.xlsx")
# Print Text
print( "working with python" +"in R is much fun")
#generate a random number
```

```
## working with pythonin R is much fun
```

```python
import random as r
print(r.random())
```

```
## 0.3069455789523037
```

```python
print(data[['Age','Attrition','BusinessTravel','DailyRate','Department']].head(3))
```

```
##    Age Attrition     BusinessTravel  DailyRate              Department
## 0   41       Yes      Travel_Rarely       1102                   Sales
## 1   49        No  Travel_Frequently        279  Research & Development
## 2   37       Yes      Travel_Rarely       1373  Research & Development
```




```python
# summary statistics from the data
print(data.describe())
#get the current working directory
```

```
##                Age    DailyRate  DistanceFromHome    Education  EmployeeCount  \
## count  1470.000000  1470.000000       1470.000000  1470.000000         1470.0   
## mean     36.923810   802.485714          9.192517     2.912925            1.0   
## std       9.135373   403.509100          8.106864     1.024165            0.0   
## min      18.000000   102.000000          1.000000     1.000000            1.0   
## 25%      30.000000   465.000000          2.000000     2.000000            1.0   
## 50%      36.000000   802.000000          7.000000     3.000000            1.0   
## 75%      43.000000  1157.000000         14.000000     4.000000            1.0   
## max      60.000000  1499.000000         29.000000     5.000000            1.0   
## 
##        EmployeeNumber  EnvironmentSatisfaction   HourlyRate  JobInvolvement  \
## count     1470.000000              1470.000000  1470.000000     1470.000000   
## mean      1024.865306                 2.721769    65.891156        2.729932   
## std        602.024335                 1.093082    20.329428        0.711561   
## min          1.000000                 1.000000    30.000000        1.000000   
## 25%        491.250000                 2.000000    48.000000        2.000000   
## 50%       1020.500000                 3.000000    66.000000        3.000000   
## 75%       1555.750000                 4.000000    83.750000        3.000000   
## max       2068.000000                 4.000000   100.000000        4.000000   
## 
##           JobLevel          ...           RelationshipSatisfaction  \
## count  1470.000000          ...                        1470.000000   
## mean      2.063946          ...                           2.712245   
## std       1.106940          ...                           1.081209   
## min       1.000000          ...                           1.000000   
## 25%       1.000000          ...                           2.000000   
## 50%       2.000000          ...                           3.000000   
## 75%       3.000000          ...                           4.000000   
## max       5.000000          ...                           4.000000   
## 
##        StandardHours  StockOptionLevel  TotalWorkingYears  \
## count         1470.0       1470.000000        1470.000000   
## mean            80.0          0.793878          11.279592   
## std              0.0          0.852077           7.780782   
## min             80.0          0.000000           0.000000   
## 25%             80.0          0.000000           6.000000   
## 50%             80.0          1.000000          10.000000   
## 75%             80.0          1.000000          15.000000   
## max             80.0          3.000000          40.000000   
## 
##        TrainingTimesLastYear  WorkLifeBalance  YearsAtCompany  \
## count            1470.000000      1470.000000     1470.000000   
## mean                2.799320         2.761224        7.008163   
## std                 1.289271         0.706476        6.126525   
## min                 0.000000         1.000000        0.000000   
## 25%                 2.000000         2.000000        3.000000   
## 50%                 3.000000         3.000000        5.000000   
## 75%                 3.000000         3.000000        9.000000   
## max                 6.000000         4.000000       40.000000   
## 
##        YearsInCurrentRole  YearsSinceLastPromotion  YearsWithCurrManager  
## count         1470.000000              1470.000000           1470.000000  
## mean             4.229252                 2.187755              4.123129  
## std              3.623137                 3.222430              3.568136  
## min              0.000000                 0.000000              0.000000  
## 25%              2.000000                 0.000000              2.000000  
## 50%              3.000000                 1.000000              3.000000  
## 75%              7.000000                 3.000000              7.000000  
## max             18.000000                15.000000             17.000000  
## 
## [8 rows x 26 columns]
```

```python
import os
cwd = os.getcwd()
print(cwd)
```

```
## /Users/nanaakwasiabayieboateng/Documents/memphisclassesbooks/DataMiningscience
```

```python
print("Path at terminal when executing this file")
```

```
## Path at terminal when executing this file
```

```python
print(os.getcwd() + "\n")
```

```
## /Users/nanaakwasiabayieboateng/Documents/memphisclassesbooks/DataMiningscience
```






```python
#matplotlib inline
#Import datavis libraries
import matplotlib.pyplot as plt
# Hide warnings if there are any
import warnings
warnings.filterwarnings('ignore')
import pandas_datareader.data as web
import numpy as np
import seaborn as sns; sns.set() 
from datetime import datetime
from dateutil.parser import parse
import pandas as pd
# 
start = datetime(2015, 1, 1)
end = datetime(2018, 3, 1)
#download Apple stock data
df = web.DataReader(['AAPL'], 'morningstar', start, end)
df=pd.DataFrame(df)
print(df.dtypes)
## select the Date and Symbol index and add as a main column
```

```
## Close     float64
## High      float64
## Low       float64
## Open      float64
## Volume      int64
## dtype: object
```

```python
df["Date"]=df.index.get_level_values('Date')
df["Symbol"]=df.index.get_level_values('Symbol')
df.tail(3)
#drop columns
df2=df.drop(columns=['Date','Symbol'])
#Convert  index  to  column
df2=df2.reset_index()
#drop index
#df.drop(index='Date')
#We can use the drop parameter to avoid the old index being added as a column:
df3=df
df3.reset_index(drop=True)
print(df3.head(4))
```

```
##                     Close    High     Low    Open    Volume       Date Symbol
## Symbol Date                                                                  
## AAPL   2015-01-01  110.38  110.38  110.38  110.38         0 2015-01-01   AAPL
##        2015-01-02  109.33  111.44  107.35  111.39  53204626 2015-01-02   AAPL
##        2015-01-05  106.25  108.65  105.41  108.29  64285490 2015-01-05   AAPL
##        2015-01-06  106.26  107.43  104.63  106.54  65797116 2015-01-06   AAPL
```

```python
df4 = pd.DataFrame([('bird',    389.0),
                    ('bird',     24.0),
                   ('mammal',   80.5),
                    ('mammal', np.nan)],
                  index=['falcon', 'parrot', 'lion', 'monkey'],
                  columns=('class', 'max_speed'))
df4.head()
#drop an index column
print(df4.reset_index(drop=True))
#df3.reset_index(level=['Date'])
#df3.MultiIndex.drop(labels, level=None, errors='raise')
```

```
##     class  max_speed
## 0    bird      389.0
## 1    bird       24.0
## 2  mammal       80.5
## 3  mammal        NaN
```

```python
df5=df2.drop(columns=['Symbol','Volume'])
#Set the index to become the 
df5=df5.set_index(['Date'])
fig, ax = plt.subplots(1, 1,figsize=(20,10))
plt.subplots(1, 0)
params = {'legend.fontsize': 'x-large',
          'figure.figsize': (15, 8),
         'axes.labelsize': 'x-large',
         'axes.titlesize':'x-large',
         'xtick.labelsize':'x-large',
         'ytick.labelsize':'x-large'}
plt.rcParams.update(params)
plt.title('Stock Prices ', fontsize=20)
plt.ylabel('Price', fontsize=20)
plt.xlabel('Date', fontsize=20)
df5.plot(lw=2,grid = True)
fig.savefig('Apple.jpg')
plt.grid(True)
plt.legend(loc='lower right')
plt.show()
```

<div class="figure">
<img src="RPYTHON_files/figure-html/unnamed-chunk-4-1.png" alt="Fig. 30" width="100%" />
<p class="caption">Fig. 30</p>
</div>

We can also plot transfer the data from the Python environment and plot with ggplot as follows:

```r
#install.packages("viridis")
library(viridis)


df6=py$df3%>%mutate(Date=as.Date(Date))
ggplot(df6)+geom_line(aes(x=Date,y=Close,color="Close"))+geom_line(aes(x=Date,y=High,color="High"))+geom_line(aes(x=Date,y=Low,color="Low"))+geom_line(aes(x=Date,y=Open,color="Open"))+
scale_color_viridis(discrete=TRUE,option = "A")+
  #scale_fill_viridis(discrete = T,option = "C")+
      theme(
    legend.position="top",
    legend.direction="horizontal",
    legend.title = element_blank(),
    text=element_text(size=8,  family="Comic Sans MS"),
    axis.text.x=element_text(angle=45,hjust=1,size = 9),
    axis.text.y=element_text(size = 8),
    legend.text = element_text(size=8)
)+

  
  labs(y="Value",x="Date",title="")+
  
  # scale_x_date(date_labels = "%b %d")
 #scale_x_date(labels = date_format("%m-%y"))

 scale_x_date(breaks = date_breaks("4 month"),labels=date_format("%b %Y") ) 
```

<div class="figure">
<img src="RPYTHON_files/figure-html/unnamed-chunk-5-1.png" alt="Fig. 30" width="100%" />
<p class="caption">Fig. 30</p>
</div>

```r
df6%>% select(Date,High,Close,Low,Open,Symbol)%>%
gather(Name,Value,-Date,-Symbol)%>%mutate(Name=as.factor(Name))%>%
  
  ggplot(aes(x=Date,y=Value,color=Name))+geom_line()+
  
scale_color_viridis(discrete=TRUE,option = "D")+
  #scale_fill_viridis(discrete = T,option = "C")+
   theme(
   
    
    legend.title = element_blank(),
    text=element_text(size=8,  family="Comic Sans MS"),
    axis.text.x=element_text(angle=45,hjust=1,size = 9),
    axis.text.y=element_text(size = 8),
    legend.text = element_text(size=8)
)+
   scale_x_date(breaks = date_breaks("4 month"),labels=date_format("%b %Y") ) 
```

<div class="figure">
<img src="RPYTHON_files/figure-html/unnamed-chunk-5-2.png" alt="Fig. 30" width="100%" />
<p class="caption">Fig. 30</p>
</div>

```r
  # scale_fill_manual(values=c("#B9DE28FF" , "#D1E11CFF" , "#E8E419FF"))
```



The reticulate Package
---------------------------------

Another alternative to working with in R is via the reticulate package. The reticulate package has made it possible for several popular python libraries such as  tensorflow and keras available in R. It provides a set of tools for  interoperability between R and Python. It's functionality include sourcing python scripts,using Python interactively within an R session and importing modules.





```r
library(reticulate)
os <- import("os")

#get current working directory
os$getcwd()
```

```
## [1] "/Users/nanaakwasiabayieboateng/Documents/memphisclassesbooks/DataMiningscience"
```

```r
#list files current directory
os$listdir(".")
```

```
##   [1] " Central Limit Theorem.pdf"                                                                              
##   [2] " climate changing and where with R.pdf"                                                                  
##   [3] " data.table Package | R-bloggers.pdf"                                                                    
##   [4] " Factor PrincipalComponentAnalysis.pdf"                                                                  
##   [5] " Gradient Descent 2.pdf"                                                                                 
##   [6] " tables in rmarkdown.pdf"                                                                                
##   [7] " Tidyr | RStudio Blog.pdf"                                                                               
##   [8] ".DS_Store"                                                                                               
##   [9] ".gitignore"                                                                                              
##  [10] ".httr-oauth"                                                                                             
##  [11] ".Rapp.history"                                                                                           
##  [12] ".RData"                                                                                                  
##  [13] ".RDataTmp"                                                                                               
##  [14] ".RDataTmp1"                                                                                              
##  [15] ".Rhistory"                                                                                               
##  [16] ".Rproj.user"                                                                                             
##  [17] "7TypesofRegressionTechniques .pdf"                                                                       
##  [18] "advanced-r.pdf"                                                                                          
##  [19] "Amazon Web Services (AWS).pdf"                                                                           
##  [20] "AmazonRelationalDatabaseServicePythonandR.pdf"                                                           
##  [21] "AmericanUrologicalAssociation.docx"                                                                      
##  [22] "Anomalydetection"                                                                                        
##  [23] "Anomalydetection.R"                                                                                      
##  [24] "Apple.jpg"                                                                                               
##  [25] "applyfamily.R"                                                                                           
##  [26] "Approximating poisson distribution with normal distribution.pdf"                                         
##  [27] "Assurant"                                                                                                
##  [28] "AUA.nb.html"                                                                                             
##  [29] "AUA.R"                                                                                                   
##  [30] "AUA.Rmd"                                                                                                 
##  [31] "AUANotebook.nb.html"                                                                                     
##  [32] "AUAReport.docx"                                                                                          
##  [33] "Bankloan.nb.html"                                                                                        
##  [34] "Bankloanxgboost.html"                                                                                    
##  [35] "Bankloanxgboost.nb.html"                                                                                 
##  [36] "Bankloanxgboost.Rmd"                                                                                     
##  [37] "Benchmarking"                                                                                            
##  [38] "Best Machine Learning Packages in R? | R-bloggers.pdf"                                                   
##  [39] "Big Data Analyses with R Presentation.pdf"                                                               
##  [40] "Big-Data-Analytics-with-R-and-Hadoop.pdf"                                                                
##  [41] "big-data-wp.pdf"                                                                                         
##  [42] "Bigquery.Rmd"                                                                                            
##  [43] "blogdown (1).pdf"                                                                                        
##  [44] "blogdown _ Alison Presmanes Hill.pdf"                                                                    
##  [45] "blogdown.pdf"                                                                                            
##  [46] "BloombergAPI.R"                                                                                          
##  [47] "BostonRegressionHousingdata.pdf"                                                                         
##  [48] "Broom.pdf"                                                                                               
##  [49] "Broom.R"                                                                                                 
##  [50] "C2FO_Interview_Basics.txt"                                                                               
##  [51] "C2FO_Interview_Basics_Negative.ipynb"                                                                    
##  [52] "Capitalone"                                                                                              
##  [53] "Car Fuel Efficiency and Transmission Type.pdf"                                                           
##  [54] "Caret"                                                                                                   
##  [55] "caret_6.0-73.tar.gz"                                                                                     
##  [56] "caretEnsemble.pdf"                                                                                       
##  [57] "CaretEnsemble2.pdf"                                                                                      
##  [58] "causaimpact.pdf"                                                                                         
##  [59] "CensusBureauData"                                                                                        
##  [60] "Central Limit Theorem.pdf"                                                                               
##  [61] "Cheatsheet_ Scikit-Learn & Caret Package for Python & R respectively.pdf"                                
##  [62] "Cheatsheets"                                                                                             
##  [63] "climate changing and where with R.pdf"                                                                   
##  [64] "Clustering"                                                                                              
##  [65] "Composite analysis to capture non-linear relationships.pdf"                                              
##  [66] "Correlation map of climate variables.pdf"                                                                
##  [67] "Cranpkginfo.nb.html"                                                                                     
##  [68] "Cranpkginfo.Rmd"                                                                                         
##  [69] "Customer segmentation"                                                                                   
##  [70] "Data Mining with R-Kumar.pdf"                                                                            
##  [71] "Data Mining With Rattle and R_ The Art of Excavating Data for Knowledge Discovery - Graham Williams.pdf" 
##  [72] "data+table+cheat+sheet.pdf"                                                                              
##  [73] "Data.Gov"                                                                                                
##  [74] "Data.nb.html"                                                                                            
##  [75] "Data.R"                                                                                                  
##  [76] "Data.Rmd"                                                                                                
##  [77] "data.table"                                                                                              
##  [78] "data.table Package | R-bloggers.pdf"                                                                     
##  [79] "data.table+cheat+sheet.pdf"                                                                              
##  [80] "Data_Mining_and_Business_Analytics_with_R__Johannes_Ledolter.pdf"                                        
##  [81] "data_output.pdf"                                                                                         
##  [82] "Databaseconnection.nb.html"                                                                              
##  [83] "Databaseconnection.Rmd"                                                                                  
##  [84] "datamining.R"                                                                                            
##  [85] "DataMiningWithR.pdf"                                                                                     
##  [86] "datascience.R"                                                                                           
##  [87] "DataScienceBook1_1.pdf"                                                                                  
##  [88] "DataSciencerprogramming.pdf"                                                                             
##  [89] "Datashader is a big deal | R-bloggers.pdf"                                                               
##  [90] "DateTime- lubridate.pdf"                                                                                 
##  [91] "Deeplearning"                                                                                            
##  [92] "diabetes.csv"                                                                                            
##  [93] "diabetes.R"                                                                                              
##  [94] "diabetes1.R"                                                                                             
##  [95] "DifferentialGeometryDGLARS.pdf"                                                                          
##  [96] "DiffGoemleastAngleRegression.R"                                                                          
##  [97] "Document Clustering.pdf"                                                                                 
##  [98] "Downloading data from the web using R.webarchive"                                                        
##  [99] "dplyr"                                                                                                   
## [100] "dplyr 0.5 .pdf"                                                                                          
## [101] "dplyr.html"                                                                                              
## [102] "dplyr.nb.html"                                                                                           
## [103] "dplyr.pdf"                                                                                               
## [104] "dplyr3.html"                                                                                             
## [105] "dplyr3.nb.html"                                                                                          
## [106] "dplyrtutorial.pdf"                                                                                       
## [107] "DT: An R interface to the DataTables library.pdf"                                                        
## [108] "Economic-crises-and-womens-work.pdf"                                                                     
## [109] "Elementsstatisticallearning.pdf"                                                                         
## [110] "employeeattrition"                                                                                       
## [111] "employeeAttrition.py"                                                                                    
## [112] "EmployeeAttrition.xlsx"                                                                                  
## [113] "EmployeeAttritionPrediction.Rmd at master · Microsoft:acceleratoRs.pdf"                                  
## [114] "Ensemble Machine Learning Techniques for Human Activity Recognition.pdf"                                 
## [115] "EnsembleLearning.pdf"                                                                                    
## [116] "EssentialsofMachine Learning Algorithms (with Python and R Codes).pdf"                                   
## [117] "example01.png"                                                                                           
## [118] "example02.png"                                                                                           
## [119] "example03.png"                                                                                           
## [120] "example04.png"                                                                                           
## [121] "example05.png"                                                                                           
## [122] "example06.png"                                                                                           
## [123] "example07.png"                                                                                           
## [124] "example08.png"                                                                                           
## [125] "example09.png"                                                                                           
## [126] "example10.png"                                                                                           
## [127] "example11.png"                                                                                           
## [128] "example_1.gif"                                                                                           
## [129] "examples"                                                                                                
## [130] "Exploratory Analysis of Fine Particulate Matter.pdf"                                                     
## [131] "ExploratoryDataAnalysis"                                                                                 
## [132] "ExploratoryDataAnalysis.Rmd"                                                                             
## [133] "FCA"                                                                                                     
## [134] "fca.jpg"                                                                                                 
## [135] "feather_0.3.1.tar.gz"                                                                                    
## [136] "Featureselection"                                                                                        
## [137] "figure"                                                                                                  
## [138] "Finance"                                                                                                 
## [139] "Financial"                                                                                               
## [140] "Flexdashboard"                                                                                           
## [141] "flights.py"                                                                                              
## [142] "foo.png"                                                                                                 
## [143] "Forexxgboost.nb.html"                                                                                    
## [144] "Forexxgboost.Rmd"                                                                                        
## [145] "Gapminder World Map with R & ggplot2 | R-bloggers.pdf"                                                   
## [146] "gapminder.pdf"                                                                                           
## [147] "GapminderGoogleVis and R.pdf"                                                                            
## [148] "gbm_2.1.1.tar.gz"                                                                                        
## [149] "generatedataemailproject.R"                                                                              
## [150] "GentleIntroRandomForestsEnsemblesandPerformance Metrics in a Commercial System -.pdf"                    
## [151] "gganimate"                                                                                               
## [152] "ggeffects.pdf"                                                                                           
## [153] "ggfortify : Extension to ggplot2 to handle some popular packages - R software and data visualization.pdf"
## [154] "ggfortify.html"                                                                                          
## [155] "ggfortify.Rmd"                                                                                           
## [156] "ggplot2_2.2.0.tar.gz"                                                                                    
## [157] "ggplot_barplot.html"                                                                                     
## [158] "ggplottutorial.R"                                                                                        
## [159] "Git with RStudio.pdf"                                                                                    
## [160] "GitHubMastering Markdown · .pdf"                                                                         
## [161] "githuntutorial.pdf"                                                                                      
## [162] "gitRStudioandGitHub _ R-bloggers.pdf"                                                                    
## [163] "Google Trends Analytics using Shiny.pdf"                                                                 
## [164] "googlesheets Basic Usage.pdf"                                                                            
## [165] "googlesheets.pdf"                                                                                        
## [166] "googletrends.nb.html"                                                                                    
## [167] "googletrends.Rmd"                                                                                        
## [168] "googleVis examples.pdf"                                                                                  
## [169] "googleVis.pdf"                                                                                           
## [170] "googlevisworldbank.pdf"                                                                                  
## [171] "GPU"                                                                                                     
## [172] "Gradient descent and normal equation in Linear Regression.pdf"                                           
## [173] "Gradient Descent.pdf"                                                                                    
## [174] "gradient descent3.pdf"                                                                                   
## [175] "gradient_boosting.pdf"                                                                                   
## [176] "gradientdescent"                                                                                         
## [177] "Gradientdescent1.pdf"                                                                                    
## [178] "gretaintro.pdf"                                                                                          
## [179] "H20"                                                                                                     
## [180] "HealthcareAnalyticR.pdf"                                                                                 
## [181] "Highcharter.nb.html"                                                                                     
## [182] "Highcharter.R"                                                                                           
## [183] "Highcharter.Rmd"                                                                                         
## [184] "Hmisc.pdf"                                                                                               
## [185] "HR Analytics_ Using Machine Learning to Predict Employee Turnover.pdf"                                   
## [186] "htmlwidgets.nb.html"                                                                                     
## [187] "htmlwidgets.Rmd"                                                                                         
## [188] "http___www_personality-project_org_r_r_commands_html.pdf"                                                
## [189] "Image"                                                                                                   
## [190] "imbalancedata"                                                                                           
## [191] "ImportingDataR – Part Two | R-bloggers.pdf"                                                              
## [192] "installed_previously.csv"                                                                                
## [193] "Installing and loading many R packages at once.pdf"                                                      
## [194] "interactiveHeatmap.nb.html"                                                                              
## [195] "interactiveHeatmap.R"                                                                                    
## [196] "interactiveHeatmap.Rmd"                                                                                  
## [197] "InteractivePlots.html"                                                                                   
## [198] "interactiveplots.pdf"                                                                                    
## [199] "InteractivePlots.Rmd"                                                                                    
## [200] "Interpretability"                                                                                        
## [201] "Interview2.docx"                                                                                         
## [202] "intro-to-r-for-data-mining.pdf"                                                                          
## [203] "Introstatisticallearning.pdf"                                                                            
## [204] "ISL_conceptual_solutions.pdf"                                                                            
## [205] "ISLR.R"                                                                                                  
## [206] "ISLR_1.0.tar.gz"                                                                                         
## [207] "ISLRAllcodes.R"                                                                                          
## [208] "Kaggle"                                                                                                  
## [209] "kaggle.R"                                                                                                
## [210] "Leaflet, Plotly and Shiny- Weather Forecasts In The Northeast.pdf"                                       
## [211] "LedolterDataMiningWileyComputerProgramsApril2013.pdf"                                                    
## [212] "LiblineaR_1.94-2.tar.gz"                                                                                 
## [213] "limepackage.nb.html"                                                                                     
## [214] "limepackage.Rmd"                                                                                         
## [215] "listfiles.nb.html"                                                                                       
## [216] "listfiles.R"                                                                                             
## [217] "listfiles.Rmd"                                                                                           
## [218] "listfiles2.Rmd"                                                                                          
## [219] "lubridate.nb.html"                                                                                       
## [220] "lubridate.Rmd"                                                                                           
## [221] "Machine Learning and Random Forest_NZ_041615.pptx"                                                       
## [222] "Machine Learning for Drug Adverse Event Discovery.pdf"                                                   
## [223] "machine learning using R.pdf"                                                                            
## [224] "Machine Learning with R - Second Edition.pdf"                                                            
## [225] "Machine_Learning_in_Action.pdf"                                                                          
## [226] "MakingMaps.pdf"                                                                                          
## [227] "Maps"                                                                                                    
## [228] "MatlabLogistic Regression.pdf"                                                                           
## [229] "MatlabSupport Vector Machines (SVMs).pdf"                                                                
## [230] "matrixplot.pdf"                                                                                          
## [231] "matrixplot1.pdf"                                                                                         
## [232] "Medicare_Provider_Charge_Inpatient_DRGALL_FY2014.csv"                                                    
## [233] "Metabolon.docx"                                                                                          
## [234] "Metaboloninsert elements in a vector.pdf"                                                                
## [235] "Microsoft R Client.pdf"                                                                                  
## [236] "Missingdata"                                                                                             
## [237] "mljar-api-R.nb.html"                                                                                     
## [238] "mljar-api-R.Rmd"                                                                                         
## [239] "MLR"                                                                                                     
## [240] "modelevaluation.pdf"                                                                                     
## [241] "MongoDB with R and Python.pdf"                                                                           
## [242] "Most Harmful Storms and Weather Events In The United States.pdf"                                         
## [243] "MRIdatavisuakization.pdf"                                                                                
## [244] "mtcars.feather"                                                                                          
## [245] "Multi-Task-Learning"                                                                                     
## [246] "MushroomRandom Forest Classification s | R-bloggers.pdf"                                                 
## [247] "nested ifelse | R-bloggers.pdf"                                                                          
## [248] "neuralnetwork RR-bloggers.pdf"                                                                           
## [249] "NiceOutputR.pdf"                                                                                         
## [250] "Notebookbasics.nb.html"                                                                                  
## [251] "Notebookbasics.Rmd"                                                                                      
## [252] "oecd.gif"                                                                                                
## [253] "onlinereaddata.R"                                                                                        
## [254] "op searches associated with each nation.pdf"                                                             
## [255] "Operations%20Analytics%20Analyst%20Position%20-%202nd%20Round.csv"                                       
## [256] "orangejuice.csv"                                                                                         
## [257] "out.html"                                                                                                
## [258] "out.txt"                                                                                                 
## [259] "output.gif"                                                                                              
## [260] "Package “SentimentAnalysis” released on CRAN _ R-bloggers.pdf"                                           
## [261] "PackageDevelopment Pictorial.pdf"                                                                        
## [262] "Packages.nb.html"                                                                                        
## [263] "Packages.Rmd"                                                                                            
## [264] "PDF Mining with R using Shiny.pdf"                                                                       
## [265] "Performing SQL selects on R data frames.pdf"                                                             
## [266] "Plumber"                                                                                                 
## [267] "plumber.nb.html"                                                                                         
## [268] "Predicting Earnings from census data.pdf"                                                                
## [269] "prediction - movieratings.pdf"                                                                           
## [270] "principal component analysis"                                                                            
## [271] "printingtables.R"                                                                                        
## [272] "purrr.nb.html"                                                                                           
## [273] "purrr.pdf"                                                                                               
## [274] "purrr.Rmd"                                                                                               
## [275] "purrr_0.2.2.tar.gz"                                                                                      
## [276] "Purrrtutorial.pdf"                                                                                       
## [277] "Python"                                                                                                  
## [278] "pythonr_files"                                                                                           
## [279] "q1.csv"                                                                                                  
## [280] "Quote.nb.html"                                                                                           
## [281] "Quote.Rmd"                                                                                               
## [282] "r - Download a file from HTTPS using download.file() - Stack Overflow.pdf"                               
## [283] "R for Data Science.pdf"                                                                                  
## [284] "randomForest_4.6-12.tar.gz"                                                                              
## [285] "randonforest.pdf"                                                                                        
## [286] "raster.nb.html"                                                                                          
## [287] "raster.Rmd"                                                                                              
## [288] "rblogger.docx"                                                                                           
## [289] "Rcheatsheet"                                                                                             
## [290] "rdatabase"                                                                                               
## [291] "RDataMining-book.pdf"                                                                                    
## [292] "RDataMining-introduction-slides.pdf"                                                                     
## [293] "RDataMining-reference-card.pdf"                                                                          
## [294] "RDataMining-slides-association-rules.pdf"                                                                
## [295] "RDataMining-slides-clustering.pdf"                                                                       
## [296] "RDataMining-slides-data-exploration-visualization.pdf"                                                   
## [297] "RDataMining-slides-introduction-data-import-export.pdf"                                                  
## [298] "RDataMining-slides-regression-classification.pdf"                                                        
## [299] "RDataMining-slides-text-mining.pdf"                                                                      
## [300] "RDataMining-slides-time-series-analysis.pdf"                                                             
## [301] "Rdatamining.pdf"                                                                                         
## [302] "read_multiplefiles.R"                                                                                    
## [303] "reading:writing biggish data, revisited - the stupidest thing....pdf"                                    
## [304] "Readonline.nb.html"                                                                                      
## [305] "Readonline.Rmd"                                                                                          
## [306] "Regression"                                                                                              
## [307] "ReinforcementLearning_new.pdf"                                                                           
## [308] "repl_python.png"                                                                                         
## [309] "Replyr _ R-bloggers.pdf"                                                                                 
## [310] "Replyr%20_%20R-bloggers.pdf"                                                                             
## [311] "Reproducible Research with R.pdf"                                                                        
## [312] "reshape2.pdf"                                                                                            
## [313] "RevoScaleR package for Microsoft R | R-bloggers.pdf"                                                     
## [314] "rfexplainer.nb.html"                                                                                     
## [315] "rfexplainer.Rmd"                                                                                         
## [316] "rmarkdown"                                                                                               
## [317] "rmarkdown.pdf"                                                                                           
## [318] "rmarkdown.R"                                                                                             
## [319] "rmarkdown1.html"                                                                                         
## [320] "rmarkdown1.R"                                                                                            
## [321] "rmarkdownunnamed-chunk-4-1.png"                                                                          
## [322] "rpackage_instructions.pdf"                                                                               
## [323] "RPostgres.pdf"                                                                                           
## [324] "rprogramming.pdf"                                                                                        
## [325] "RPubs - Introduction to Statistical Learning - Chap2 Solutions.htm"                                      
## [326] "RPubs - Introduction to Statistical Learning - Chap2 Solutions.pdf"                                      
## [327] "RPubs - Introduction to Statistical Learning - Chap2 Solutions_files"                                    
## [328] "RPubs AnalyzingRealEstateDatawithR.pdf"                                                                  
## [329] "RPubs.htm"                                                                                               
## [330] "RPubs_files"                                                                                             
## [331] "RPYTHON.html"                                                                                            
## [332] "RPYTHON.md"                                                                                              
## [333] "RPYTHON.Rmd"                                                                                             
## [334] "RPYTHON_files"                                                                                           
## [335] "rsample.nb.html"                                                                                         
## [336] "rsample.Rmd"                                                                                             
## [337] "rsconnect"                                                                                               
## [338] "sampled20170509182124.csv"                                                                               
## [339] "sampled20170509182134.csv"                                                                               
## [340] "sampled20170509182144.csv"                                                                               
## [341] "sampled20170509182154.csv"                                                                               
## [342] "sampled20170509182204.csv"                                                                               
## [343] "sampled20170509182214.csv"                                                                               
## [344] "SavingFiles"                                                                                             
## [345] "Sberbank Russian Housing Market"                                                                         
## [346] "Scales.R"                                                                                                
## [347] "scales_0.4.1.tar.gz"                                                                                     
## [348] "ScalesPackage.nb.html"                                                                                   
## [349] "ScalesPackage.Rmd"                                                                                       
## [350] "Sentiment Analysis of Donald Trump's views on Muslims using R and Tableau.webarchive"                    
## [351] "serveremailproject.R"                                                                                    
## [352] "Shiny"                                                                                                   
## [353] "SoftwareTesting.pdf"                                                                                     
## [354] "solutionmanual.pdf"                                                                                      
## [355] "Solutions & Notes for ISL Hastie-Tibshirani | Introduction to Statistical Learning with Applications.pdf"
## [356] "southerncompany"                                                                                         
## [357] "SP500.RData"                                                                                             
## [358] "Spark"                                                                                                   
## [359] "Spatial Analysis With R.pdf"                                                                             
## [360] "Spatial distribution of FDA's drug adverse events report.pdf"                                            
## [361] "sqldf.pdf"                                                                                               
## [362] "stan.pdf"                                                                                                
## [363] "statisticallearningLASSO.pdf"                                                                            
## [364] "streamingdata.Rmd"                                                                                       
## [365] "stringr.nb.html"                                                                                         
## [366] "Subsampling"                                                                                             
## [367] "Supervised Machine Learning with R and Python.pdf"                                                       
## [368] "t-SNE.Rmd"                                                                                               
## [369] "tabimage.png"                                                                                            
## [370] "tables in rmarkdown.pdf"                                                                                 
## [371] "tables-concordance.tex"                                                                                  
## [372] "tables.html"                                                                                             
## [373] "tables.log"                                                                                              
## [374] "tables.pdf"                                                                                              
## [375] "tables.Rmd"                                                                                              
## [376] "tables.Rnw"                                                                                              
## [377] "tables.synctex.gz"                                                                                       
## [378] "tables.tex"                                                                                              
## [379] "tables2.html"                                                                                            
## [380] "tables2.Rmd"                                                                                             
## [381] "TaxiData"                                                                                                
## [382] "Text"                                                                                                    
## [383] "TibshiraniBigDataTalk.pdf"                                                                               
## [384] "Tidy evaluation, most common actions – That's so Random.pdf"                                             
## [385] "tidyeval-user.pdf"                                                                                       
## [386] "TidyEvaluation.Rmd"                                                                                      
## [387] "Tidyr | RStudio Blog.pdf"                                                                                
## [388] "tidyverse 1.0.0 | RStudio Blog.pdf"                                                                      
## [389] "Timingcode.nb.html"                                                                                      
## [390] "tree"                                                                                                    
## [391] "tree_1.0-37.tar.gz"                                                                                      
## [392] "TreeBasedModeling (R & Python).pdf"                                                                      
## [393] "trig.jpg"                                                                                                
## [394] "Twoggplots.R"                                                                                            
## [395] "uemailproject.R"                                                                                         
## [396] "UIC.xls"                                                                                                 
## [397] "UICProject"                                                                                              
## [398] "UnitedAirlines"                                                                                          
## [399] "unsupervisedlearning.pdf"                                                                                
## [400] "Untitled.html"                                                                                           
## [401] "Untitled.R"                                                                                              
## [402] "Untitled.Rhtml"                                                                                          
## [403] "Untitled.Rmd"                                                                                            
## [404] "Untitled_files"                                                                                          
## [405] "updateR.R"                                                                                               
## [406] "UpdateR.Rmd"                                                                                             
## [407] "US Hospitals Ranking Shiny App.pdf"                                                                      
## [408] "Variable Importance PlotR-bloggers.pdf"                                                                  
## [409] "visNetwork.nb.html"                                                                                      
## [410] "visNetwork.R"                                                                                            
## [411] "visNetwork.Rmd"                                                                                          
## [412] "Visualizing election predictions using ggplot2.pdf"                                                      
## [413] "Visualizing murder rates in the US.pdf"                                                                  
## [414] "Visualizing outcomes of drug related adverse events.pdf"                                                 
## [415] "Visualizing world cities using R.pdf"                                                                    
## [416] "Visualizing%20Streaming%20Data%20with%20Shiny.docx"                                                      
## [417] "visualizingshiny.R"                                                                                      
## [418] "visualR.pdf"                                                                                             
## [419] "Webscrapping"                                                                                            
## [420] "Working with databases in R.pdf"                                                                         
## [421] "Working with Dates and Times in R using Power Consumption Data.pdf"                                      
## [422] "World's Biggest Companies.pdf"                                                                           
## [423] "xgb.DMatrix.data"                                                                                        
## [424] "xgboost copy.R"                                                                                          
## [425] "xgboost copy.txt"                                                                                        
## [426] "xgboost-150831021017-lva1-app6891.pdf"                                                                   
## [427] "xgboost.model"                                                                                           
## [428] "xgboost.nb.html"                                                                                         
## [429] "xgboost.R"                                                                                               
## [430] "xgboost.Rmd"                                                                                             
## [431] "xgboost1.pdf"                                                                                            
## [432] "xgboostexplainer.txt"                                                                                    
## [433] "xgboostvidiya.pdf"                                                                                       
## [434] "xgModel"                                                                                                 
## [435] "xts.pdf"                                                                                                 
## [436] "Your_forest_explained.html"                                                                              
## [437] "youtube.pdf"                                                                                             
## [438] "youtube.R"                                                                                               
## [439] "Zhao_R_and_data_mining.pdf"                                                                              
## [440] "Zillow.nb.html"                                                                                          
## [441] "Zillow.Rmd"                                                                                              
## [442] "Zumel_Mount_Practical_Data_Science_with_R_2014.pdf"
```

#### Python in R Markdown


```python
from IPython import get_ipython
#get_ipython().magic('reset -sf')
import matplotlib.pyplot as plt
#%matplotlib inline 
import numpy as np
fig, ax = plt.subplots(1, 1,figsize=(20,10))
plt.subplots(1, 0)
t=np.arange(-5,5,0.01)
s1=1+np.sin(0.5*np.pi*t)
s2=1+np.cos(0.5*np.pi*t)
plt.plot(t,s1, label="sine", linestyle='--')
plt.plot(t,s2, label="cosine",    lw=2)
plt.grid(True)
plt.title('Sine and Cosine Functions ', fontsize=20)
plt.ylabel('y-axis', fontsize=20)
plt.xlabel('x-axis', fontsize=20)
plt.grid(True)
# Place a legend above this subplot, expanding itself to
# fully use the given bounding box.
#plt.legend(bbox_to_anchor=(0, 1.02, 1., .102), loc=3,
#          ncol=1, mode="expand", borderaxespad=0.)
# Place a legend to the right of this smaller subplot.
plt.legend(bbox_to_anchor=(-0.1, 1.11), loc=2, borderaxespad=0.5)
#plt.legend(loc='lower right')
plt.savefig('trig.jpg')
plt.show()
#print(s)
```

<div class="figure">
<img src="RPYTHON_files/figure-html/unnamed-chunk-7-1.png" alt="Fig. 30" width="100%" />
<p class="caption">Fig. 30</p>
</div>





```python
import pandas
employeedata = pandas.read_csv("https://raw.githubusercontent.com/NanaAkwasiAbayieBoateng/Datasets/master/EmployeeAttrition.csv")
employeedata = employeedata[employeedata['BusinessTravel'] == "Travel_Frequently"]
employeedata = employeedata[['Age', 'Attrition', 'BusinessTravel','DailyRate','Department']]
employeedata = employeedata.dropna()
```



```r
library(ggplot2)
ggplot(py$employeedata, aes(Age,fill=Attrition)) + geom_histogram(bins = 30)
```

<div class="figure">
<img src="RPYTHON_files/figure-html/unnamed-chunk-9-1.png" alt="Fig. 30" width="100%" />
<p class="caption">Fig. 30</p>
</div>



#### Sourcing Python scripts

A Python script can be sourced using source_python() function. For example, if you had the following Python script employeeAttrition.py:



```r
source_python("/Users/nanaakwasiabayieboateng/Documents/memphisclassesbooks/DataMiningscience/employeeAttrition.py")


employeedata <- read_employee("https://raw.githubusercontent.com/NanaAkwasiAbayieBoateng/Datasets/master/EmployeeAttrition.csv")

library(ggplot2)
ggplot(py$employeedata, aes(Age,fill=Attrition)) + geom_histogram(bins = 30)
```

<div class="figure">
<img src="RPYTHON_files/figure-html/unnamed-chunk-10-1.png" alt="Fig. 30" width="100%" />
<p class="caption">Fig. 30</p>
</div>


#### Python REPL
The repl_python() function allows switching between Python and R a breeze.First a call is made to repl_python() function , which provides a Python REPL embedded within your R session.Objects created within the Python REPL can be accessed from R using the py object exported from reticulate. The Python and R code can together be run in the R console like the example below.



```r
# repl_python()
# 
# import pandas
# 
# 
# employeedata = pandas.read_csv("https://raw.githubusercontent.com/NanaAkwasiAbayieBoateng/Datasets/master/EmployeeAttrition.csv")
# employeedata = employeedata[employeedata['BusinessTravel'] == "Travel_Frequently"]
# employeedata = employeedata[['Age', 'Attrition', 'BusinessTravel','DailyRate','Department']]
# employeedata = employeedata.dropna()
# exit
# 
# library(ggplot2)
# ggplot(py$employeedata, aes(Age,fill=Attrition)) + geom_histogram(bins = 30)
```




<div class="figure">
<img src="/Users/nanaakwasiabayieboateng/Downloads/repl_python.png" alt="Employee Age" width="100%" />
<p class="caption">Employee Age</p>
</div>
