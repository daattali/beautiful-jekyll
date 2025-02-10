---
title: " Pothole Detection With Machine Learning"
subtitle: Visualization with ggplot Extensions
#output: rmarkdown::github_document

output:
  html_document:
    keep_md: true    
    toc: true
    toc_float: false
    theme: united
author: Nana Boateng
df_print: paged
Time: '2018-08-21 12:04:45'
date: "August 21, 2018"
toc_depth: 3  # upto three depths of headings (specified by #, ## and ###)
number_sections: true  ## if you want number sections at each table header
highlight: tango  # specifies the syntax highlighting style
tags:  Machine Learning,visualization,Data Exploration,caret,recipes
---







Introduction
---------------------------------
Our goal is to predict the depth and size of a pothole based on features collecting by vehicle running over potholes such as vehicle speed,acceleration ,direction ect. The number of distinct  labels Label_Combined B1,..B5  represents various  increasing size and depth of potholes.


Load Required Packages
---------------------------------

The pacman package provides a convenient way to load packages. It installs the package before loading if it not already installed.One of my favorite themes that I use with ggplot is the theme_pubclean. Here I set all themes with ggplot by it.


```r
rm(list=ls())

#set.seed(4)
set.seed(7)


pacman::p_load(tidyverse,janitor,DataExplorer,skimr,ggpubr,viridis,kableExtra,caret,lightgbm,recipes,rsample,yardstick,pROC,xgboost,doParallel,mlr,readxl,stringr,parallel,VIM,GGally,DALEX,MLmetrics)


#Load  variable importance plot
source("Varplot.R")

source("EvaluationMetrics.R")


theme_set(theme_pubclean())
```



Equivalently the rio package provides a unified approach to importing a variety of file formats into R. The date variable is not in a standard date format so we convert to a standard format thus separating year, month and day by '-'. We can take a look at the  first few rows of the data afterwards. The str_c function from the stringr package works similarly to the paste function


```r
potholedata<- rio::import("/POTHOLEDETECTION/pothole.xlsx",sheet="Sheet6")

potholedata<-potholedata%>%mutate_if(is.character,as_factor)%>%rename(Label_Combined=Feature,Label=Feature2)
  
  


Date=paste(substr(20180709, 1, 4),substr(20180709, 5, 6),substr(20180709, 7, 8),sep = "-")

#Equivalently
Date<-str_c(substr(20180709, 1, 4),"-",substr(20180709, 5, 6),"-",substr(20180709, 7, 8))

extracdate<-function(x){
d<-str_c(str_sub(x, 1, 4),str_sub(x, 5, 6),str_sub(x, 7, 8),sep = "-")  
 return(d) 
}



potholedata$Date<-as.Date(as_vector(purrr::map(potholedata$Date,extracdate)) )    


#sapply(potholedata$Date, extracdate)

 
potholedata%>%head()%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> Label_Combined </th>
   <th style="text-align:center;"> Label </th>
   <th style="text-align:center;"> Peak.Duration </th>
   <th style="text-align:center;"> Vehicle.Speed..mph. </th>
   <th style="text-align:center;"> Peak.Z.Accel </th>
   <th style="text-align:center;"> Peak.Lat.Accel </th>
   <th style="text-align:center;"> Peak.Long.Accel </th>
   <th style="text-align:center;"> Front.Slip </th>
   <th style="text-align:center;"> Right.Slip </th>
   <th style="text-align:center;"> Left.Slip </th>
   <th style="text-align:center;"> Direction </th>
   <th style="text-align:center;"> MLT1.Feature </th>
   <th style="text-align:center;"> MLT2.Feature </th>
   <th style="text-align:center;"> File </th>
   <th style="text-align:center;"> Date </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:center;"> B1 </td>
   <td style="text-align:center;"> P1 </td>
   <td style="text-align:center;"> 0.544 </td>
   <td style="text-align:center;"> 11.93148 </td>
   <td style="text-align:center;"> 1.327386 </td>
   <td style="text-align:center;"> 1.1773803 </td>
   <td style="text-align:center;"> 0.4910319 </td>
   <td style="text-align:center;"> 0.4385430 </td>
   <td style="text-align:center;"> 0.1112423 </td>
   <td style="text-align:center;"> 0.3469242 </td>
   <td style="text-align:center;"> Left3 </td>
   <td style="text-align:center;"> Type1 </td>
   <td style="text-align:center;"> N/A </td>
   <td style="text-align:center;"> Cal_EL1000Avg_1014 </td>
   <td style="text-align:center;"> 2018-07-09 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B1 </td>
   <td style="text-align:center;"> P1 </td>
   <td style="text-align:center;"> 0.534 </td>
   <td style="text-align:center;"> 12.45331 </td>
   <td style="text-align:center;"> 1.335112 </td>
   <td style="text-align:center;"> 1.1289830 </td>
   <td style="text-align:center;"> 0.8495341 </td>
   <td style="text-align:center;"> 0.5327276 </td>
   <td style="text-align:center;"> 0.1025403 </td>
   <td style="text-align:center;"> 0.4539765 </td>
   <td style="text-align:center;"> Left1 </td>
   <td style="text-align:center;"> Type1 </td>
   <td style="text-align:center;"> N/A </td>
   <td style="text-align:center;"> Cal_EL1000Avg_1014 </td>
   <td style="text-align:center;"> 2018-07-09 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B1 </td>
   <td style="text-align:center;"> P1 </td>
   <td style="text-align:center;"> 0.470 </td>
   <td style="text-align:center;"> 14.43407 </td>
   <td style="text-align:center;"> 1.383979 </td>
   <td style="text-align:center;"> 1.4389222 </td>
   <td style="text-align:center;"> 1.2037202 </td>
   <td style="text-align:center;"> 0.7060992 </td>
   <td style="text-align:center;"> 0.1216020 </td>
   <td style="text-align:center;"> 0.6253896 </td>
   <td style="text-align:center;"> Left1 </td>
   <td style="text-align:center;"> Type1 </td>
   <td style="text-align:center;"> N/A </td>
   <td style="text-align:center;"> Cal_EL1000Avg_1014 </td>
   <td style="text-align:center;"> 2018-07-09 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B1 </td>
   <td style="text-align:center;"> P1 </td>
   <td style="text-align:center;"> 0.464 </td>
   <td style="text-align:center;"> 14.97096 </td>
   <td style="text-align:center;"> 1.317055 </td>
   <td style="text-align:center;"> 1.0312775 </td>
   <td style="text-align:center;"> 0.9508938 </td>
   <td style="text-align:center;"> 0.7458671 </td>
   <td style="text-align:center;"> 0.1410580 </td>
   <td style="text-align:center;"> 0.7275356 </td>
   <td style="text-align:center;"> Left1 </td>
   <td style="text-align:center;"> Type1 </td>
   <td style="text-align:center;"> N/A </td>
   <td style="text-align:center;"> Cal_EL1000Avg_1519 </td>
   <td style="text-align:center;"> 2018-07-09 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B1 </td>
   <td style="text-align:center;"> P1 </td>
   <td style="text-align:center;"> 0.416 </td>
   <td style="text-align:center;"> 16.11388 </td>
   <td style="text-align:center;"> 1.325739 </td>
   <td style="text-align:center;"> 1.1956568 </td>
   <td style="text-align:center;"> 1.1412229 </td>
   <td style="text-align:center;"> 0.5629772 </td>
   <td style="text-align:center;"> 0.1215295 </td>
   <td style="text-align:center;"> 0.3926258 </td>
   <td style="text-align:center;"> Left3 </td>
   <td style="text-align:center;"> Type1 </td>
   <td style="text-align:center;"> N/A </td>
   <td style="text-align:center;"> Cal_EL1000Avg_1519 </td>
   <td style="text-align:center;"> 2018-07-09 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B1 </td>
   <td style="text-align:center;"> P1 </td>
   <td style="text-align:center;"> 0.184 </td>
   <td style="text-align:center;"> 24.47751 </td>
   <td style="text-align:center;"> 1.639389 </td>
   <td style="text-align:center;"> 0.4963087 </td>
   <td style="text-align:center;"> 0.1579519 </td>
   <td style="text-align:center;"> 0.3131939 </td>
   <td style="text-align:center;"> 0.1071209 </td>
   <td style="text-align:center;"> 0.4625270 </td>
   <td style="text-align:center;"> Left3 </td>
   <td style="text-align:center;"> Hump </td>
   <td style="text-align:center;"> Crest </td>
   <td style="text-align:center;"> Cal_EL1000Avg_2024 </td>
   <td style="text-align:center;"> 2018-07-09 </td>
  </tr>
</tbody>
</table>





Exploratory Data Analysis
---------------------------------

We can take a pictorial look at the variables in the dataset courtesy the plot_str from the DataExplorer package.Alternatively the glimpse function in tidyverse can also be used to inspect the variables.


```r
plot_str(potholedata)

glimpse(potholedata)
```

```
## Observations: 280
## Variables: 15
## $ Label_Combined      <fct> B1, B1, B1, B1, B1, B1, B1, B1, B1, B1, B1...
## $ Label               <fct> P1, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1...
## $ Peak.Duration       <dbl> 0.544, 0.534, 0.470, 0.464, 0.416, 0.184, ...
## $ Vehicle.Speed..mph. <dbl> 11.93148, 12.45331, 14.43408, 14.97096, 16...
## $ Peak.Z.Accel        <dbl> 1.327386, 1.335112, 1.383979, 1.317055, 1....
## $ Peak.Lat.Accel      <dbl> 1.1773803, 1.1289830, 1.4389222, 1.0312775...
## $ Peak.Long.Accel     <dbl> 0.4910319, 0.8495341, 1.2037202, 0.9508938...
## $ Front.Slip          <dbl> 0.4385430, 0.5327276, 0.7060992, 0.7458671...
## $ Right.Slip          <dbl> 0.11124231, 0.10254033, 0.12160195, 0.1410...
## $ Left.Slip           <dbl> 0.3469242, 0.4539765, 0.6253896, 0.7275356...
## $ Direction           <fct> Left3, Left1, Left1, Left1, Left3, Left3, ...
## $ MLT1.Feature        <fct> Type1, Type1, Type1, Type1, Type1, Hump, T...
## $ MLT2.Feature        <fct> N/A, N/A, N/A, N/A, N/A, Crest, N/A, N/A, ...
## $ File                <fct> Cal_EL1000Avg_1014, Cal_EL1000Avg_1014, Ca...
## $ Date                <date> 2018-07-09, 2018-07-09, 2018-07-09, 2018-...
```


The labels distribution is not severely imbalanced to create concern in evaluation of the models which shall be built later.


```r
table(potholedata$Label)
```

```
## 
## P1 P2 P3 P4 P5 P6 P7 P8 P9 
## 33 57 55 32 33 22 22 13 13
```

```r
#check classes distribution
prop.table(table(potholedata$Label))*100
```

```
## 
##        P1        P2        P3        P4        P5        P6        P7 
## 11.785714 20.357143 19.642857 11.428571 11.785714  7.857143  7.857143 
##        P8        P9 
##  4.642857  4.642857
```


There are no missing observations in the data. Handling missing data in machine learning is very important. Several  ways of dealing with missing values include mean and median imputation for continous and catergorical variables respectively. Several supervised learning algorthms such as random forest are also commonly used to impute missing values. Missing value imputation is a topic that would be looked at in depth later on.


```r
aggr(potholedata , col=c('navyblue','yellow'),
                    numbers=TRUE, sortVars=TRUE,
                    labels=names(potholedata), cex.axis=.7,
                    gap=3, ylab=c("Missing data","Pattern"))
```

![ ]( /img/pothole/1.png)

```
## 
##  Variables sorted by number of missings: 
##             Variable Count
##       Label_Combined     0
##                Label     0
##        Peak.Duration     0
##  Vehicle.Speed..mph.     0
##         Peak.Z.Accel     0
##       Peak.Lat.Accel     0
##      Peak.Long.Accel     0
##           Front.Slip     0
##           Right.Slip     0
##            Left.Slip     0
##            Direction     0
##         MLT1.Feature     0
##         MLT2.Feature     0
##                 File     0
##                 Date     0
```

```r
plot_missing(potholedata)
```

![ ]( /img/pothole/2.png)

There exist significant correlation between some of the variables. This is not suprising because some of the features were engineered from others already present.

```r
plot_correlation(potholedata,type = "continuous",theme_config = list(legend.position = "bottom", axis.text.x =
  element_text(angle = 90)))
```

![ ]( /img/pothole/3.png)




```r
potholedata%>%select(Label_Combined ,Peak.Duration, Vehicle.Speed..mph., Peak.Z.Accel,Peak.Lat.Accel, Peak.Long.Accel,Front.Slip, Right.Slip, Left.Slip, Direction)%>%ggpairs(title = "")+
  theme(legend.position = "top")
```

![ ]( /img/pothole/4.png)







```r
pn<-potholedata%>%select(Label_Combined ,Peak.Duration, Vehicle.Speed..mph., Peak.Z.Accel,Peak.Lat.Accel, Peak.Long.Accel,Front.Slip, Right.Slip, Left.Slip, Direction)%>%ggpairs(title = "",mapping = aes(color = Label_Combined ))+
  theme(legend.position = "top")

pn
```

![ ]( /img/pothole/5.png)


We can select the elements in the matrix plot with their indices.

```r
pn[1,1]
```

![ ]( /img/pothole/6.png)

```r
pn[1,2]
```

![ ]( /img/pothole/7.png)

```r
pn[1,3]
```

![ ]( /img/pothole/8.png)

```r
pn[1,4]
```

![ ]( /img/pothole/9.png)

```r
pn[1,5]
```

![ ]( /img/pothole/10.png)

```r
pn[1,6]
```

![ ]( /img/pothole/11.png)

```r
pn[1,7]
```

![ ]( /img/pothole/12.png)

```r
pn[1,8]
```

![ ]( /img/pothole/13.png)

```r
pn[1,9]
```

![ ]( /img/pothole/14.png)

```r
pn[1,10]
```

![ ]( /img/pothole/15.png)



```r
pn[3,2]
```

![ ]( /img/pothole/16.png)

```r
pn[6,5]
```

![ ]( /img/pothole/17.png)

```r
pn[5,3]
```

![ ]( /img/pothole/18.png)


```r
pn[6,4]
```

![ ]( /img/pothole/19.png)

```r
pn[6,5]
```

![ ]( /img/pothole/20.png)

```r
pn[6,3]
```

![ ]( /img/pothole/21.png)

The summary  statistics for each variable in the data

```r
skimmed <-skim_to_wide(potholedata)
skimmed%>%
  kable() %>%
  kable_styling()
```

<table class="table" style="margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;"> type </th>
   <th style="text-align:left;"> variable </th>
   <th style="text-align:left;"> missing </th>
   <th style="text-align:left;"> complete </th>
   <th style="text-align:left;"> n </th>
   <th style="text-align:left;"> min </th>
   <th style="text-align:left;"> max </th>
   <th style="text-align:left;"> median </th>
   <th style="text-align:left;"> n_unique </th>
   <th style="text-align:left;"> top_counts </th>
   <th style="text-align:left;"> ordered </th>
   <th style="text-align:left;"> mean </th>
   <th style="text-align:left;"> sd </th>
   <th style="text-align:left;"> p0 </th>
   <th style="text-align:left;"> p25 </th>
   <th style="text-align:left;"> p50 </th>
   <th style="text-align:left;"> p75 </th>
   <th style="text-align:left;"> p100 </th>
   <th style="text-align:left;"> hist </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Date </td>
   <td style="text-align:left;"> Date </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 2018-07-09 </td>
   <td style="text-align:left;"> 2018-07-16 </td>
   <td style="text-align:left;"> 2018-07-09 </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> factor </td>
   <td style="text-align:left;"> Direction </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 3 </td>
   <td style="text-align:left;"> Lef: 211, Lef: 54, Lef: 15, NA: 0 </td>
   <td style="text-align:left;"> FALSE </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> factor </td>
   <td style="text-align:left;"> File </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 12 </td>
   <td style="text-align:left;"> Cal: 44, Cal: 43, Cal: 37, Cal: 32 </td>
   <td style="text-align:left;"> FALSE </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> factor </td>
   <td style="text-align:left;"> Label </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 9 </td>
   <td style="text-align:left;"> P2: 57, P3: 55, P1: 33, P5: 33 </td>
   <td style="text-align:left;"> FALSE </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> factor </td>
   <td style="text-align:left;"> Label_Combined </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 5 </td>
   <td style="text-align:left;"> B3: 87, B4: 77, B2: 57, B1: 33 </td>
   <td style="text-align:left;"> FALSE </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> factor </td>
   <td style="text-align:left;"> MLT1.Feature </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 3 </td>
   <td style="text-align:left;"> Typ: 166, Typ: 113, Hum: 1, NA: 0 </td>
   <td style="text-align:left;"> FALSE </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> factor </td>
   <td style="text-align:left;"> MLT2.Feature </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> N/A: 279, Cre: 1, NA: 0 </td>
   <td style="text-align:left;"> FALSE </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> Front.Slip </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 1.76 </td>
   <td style="text-align:left;"> 0.84 </td>
   <td style="text-align:left;"> 0.31 </td>
   <td style="text-align:left;"> 1.02 </td>
   <td style="text-align:left;"> 1.62 </td>
   <td style="text-align:left;"> 2.34 </td>
   <td style="text-align:left;"> 3.95 </td>
   <td style="text-align:left;"> ▅▇▇▅▇▂▂▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> Left.Slip </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 2.12 </td>
   <td style="text-align:left;"> 1.08 </td>
   <td style="text-align:left;"> 0.35 </td>
   <td style="text-align:left;"> 1.24 </td>
   <td style="text-align:left;"> 2.08 </td>
   <td style="text-align:left;"> 2.85 </td>
   <td style="text-align:left;"> 4.93 </td>
   <td style="text-align:left;"> ▅▇▆▇▆▃▁▂ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> Peak.Duration </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.68 </td>
   <td style="text-align:left;"> 0.51 </td>
   <td style="text-align:left;"> 0.1 </td>
   <td style="text-align:left;"> 0.32 </td>
   <td style="text-align:left;"> 0.5 </td>
   <td style="text-align:left;"> 0.92 </td>
   <td style="text-align:left;"> 2.6 </td>
   <td style="text-align:left;"> ▇▇▂▂▂▁▁▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> Peak.Lat.Accel </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 2.88 </td>
   <td style="text-align:left;"> 1.41 </td>
   <td style="text-align:left;"> 0.22 </td>
   <td style="text-align:left;"> 1.74 </td>
   <td style="text-align:left;"> 2.66 </td>
   <td style="text-align:left;"> 3.77 </td>
   <td style="text-align:left;"> 6.22 </td>
   <td style="text-align:left;"> ▂▇▇▇▆▃▃▂ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> Peak.Long.Accel </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 2.46 </td>
   <td style="text-align:left;"> 1.17 </td>
   <td style="text-align:left;"> 0.16 </td>
   <td style="text-align:left;"> 1.5 </td>
   <td style="text-align:left;"> 2.33 </td>
   <td style="text-align:left;"> 3.46 </td>
   <td style="text-align:left;"> 5.32 </td>
   <td style="text-align:left;"> ▂▇▇▇▆▆▃▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> Peak.Z.Accel </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 3.42 </td>
   <td style="text-align:left;"> 1.29 </td>
   <td style="text-align:left;"> 1.32 </td>
   <td style="text-align:left;"> 2.44 </td>
   <td style="text-align:left;"> 3.12 </td>
   <td style="text-align:left;"> 4.25 </td>
   <td style="text-align:left;"> 7.09 </td>
   <td style="text-align:left;"> ▅▇▇▅▃▃▂▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> Right.Slip </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.34 </td>
   <td style="text-align:left;"> 0.18 </td>
   <td style="text-align:left;"> 0.071 </td>
   <td style="text-align:left;"> 0.19 </td>
   <td style="text-align:left;"> 0.33 </td>
   <td style="text-align:left;"> 0.46 </td>
   <td style="text-align:left;"> 0.86 </td>
   <td style="text-align:left;"> ▇▇▆▇▅▃▁▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> Vehicle.Speed..mph. </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> 280 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 25.36 </td>
   <td style="text-align:left;"> 15.58 </td>
   <td style="text-align:left;"> 3.64 </td>
   <td style="text-align:left;"> 12.45 </td>
   <td style="text-align:left;"> 22.55 </td>
   <td style="text-align:left;"> 36.22 </td>
   <td style="text-align:left;"> 61.73 </td>
   <td style="text-align:left;"> ▇▇▇▅▃▂▃▂ </td>
  </tr>
</tbody>
</table>

```r
#skimr::skim(potholedata)

  mlr::summarizeColumns(potholedata)%>%  
  
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> name </th>
   <th style="text-align:center;"> type </th>
   <th style="text-align:center;"> na </th>
   <th style="text-align:center;"> mean </th>
   <th style="text-align:center;"> disp </th>
   <th style="text-align:center;"> median </th>
   <th style="text-align:center;"> mad </th>
   <th style="text-align:center;"> min </th>
   <th style="text-align:center;"> max </th>
   <th style="text-align:center;"> nlevs </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:center;"> Label_Combined </td>
   <td style="text-align:center;"> factor </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 0.6892857 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 26.0000000 </td>
   <td style="text-align:center;"> 87.0000000 </td>
   <td style="text-align:center;"> 5 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Label </td>
   <td style="text-align:center;"> factor </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 0.7964286 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 13.0000000 </td>
   <td style="text-align:center;"> 57.0000000 </td>
   <td style="text-align:center;"> 9 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Peak.Duration </td>
   <td style="text-align:center;"> numeric </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0.6762429 </td>
   <td style="text-align:center;"> 0.5070269 </td>
   <td style="text-align:center;"> 0.4985000 </td>
   <td style="text-align:center;"> 0.3484110 </td>
   <td style="text-align:center;"> 0.1040000 </td>
   <td style="text-align:center;"> 2.6050000 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Vehicle.Speed..mph. </td>
   <td style="text-align:center;"> numeric </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 25.3645046 </td>
   <td style="text-align:center;"> 15.5784650 </td>
   <td style="text-align:center;"> 22.5494956 </td>
   <td style="text-align:center;"> 16.2697198 </td>
   <td style="text-align:center;"> 3.6364981 </td>
   <td style="text-align:center;"> 61.7288470 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Peak.Z.Accel </td>
   <td style="text-align:center;"> numeric </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 3.4220157 </td>
   <td style="text-align:center;"> 1.2917025 </td>
   <td style="text-align:center;"> 3.1230914 </td>
   <td style="text-align:center;"> 1.2859451 </td>
   <td style="text-align:center;"> 1.3170555 </td>
   <td style="text-align:center;"> 7.0852490 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Peak.Lat.Accel </td>
   <td style="text-align:center;"> numeric </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 2.8756696 </td>
   <td style="text-align:center;"> 1.4096700 </td>
   <td style="text-align:center;"> 2.6602507 </td>
   <td style="text-align:center;"> 1.4832631 </td>
   <td style="text-align:center;"> 0.2202256 </td>
   <td style="text-align:center;"> 6.2201228 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Peak.Long.Accel </td>
   <td style="text-align:center;"> numeric </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 2.4605413 </td>
   <td style="text-align:center;"> 1.1737102 </td>
   <td style="text-align:center;"> 2.3336269 </td>
   <td style="text-align:center;"> 1.3882734 </td>
   <td style="text-align:center;"> 0.1579519 </td>
   <td style="text-align:center;"> 5.3205001 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Front.Slip </td>
   <td style="text-align:center;"> numeric </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 1.7559611 </td>
   <td style="text-align:center;"> 0.8388320 </td>
   <td style="text-align:center;"> 1.6233722 </td>
   <td style="text-align:center;"> 0.9514858 </td>
   <td style="text-align:center;"> 0.3131939 </td>
   <td style="text-align:center;"> 3.9547484 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Right.Slip </td>
   <td style="text-align:center;"> numeric </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0.3431604 </td>
   <td style="text-align:center;"> 0.1764695 </td>
   <td style="text-align:center;"> 0.3345577 </td>
   <td style="text-align:center;"> 0.2042645 </td>
   <td style="text-align:center;"> 0.0711265 </td>
   <td style="text-align:center;"> 0.8599148 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Left.Slip </td>
   <td style="text-align:center;"> numeric </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 2.1245021 </td>
   <td style="text-align:center;"> 1.0781293 </td>
   <td style="text-align:center;"> 2.0771931 </td>
   <td style="text-align:center;"> 1.1810550 </td>
   <td style="text-align:center;"> 0.3469242 </td>
   <td style="text-align:center;"> 4.9332445 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Direction </td>
   <td style="text-align:center;"> factor </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 0.2464286 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 15.0000000 </td>
   <td style="text-align:center;"> 211.0000000 </td>
   <td style="text-align:center;"> 3 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> MLT1.Feature </td>
   <td style="text-align:center;"> factor </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 0.4071429 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 166.0000000 </td>
   <td style="text-align:center;"> 3 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> MLT2.Feature </td>
   <td style="text-align:center;"> factor </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 0.0035714 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 279.0000000 </td>
   <td style="text-align:center;"> 2 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> File </td>
   <td style="text-align:center;"> factor </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 0.8428571 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 4.0000000 </td>
   <td style="text-align:center;"> 44.0000000 </td>
   <td style="text-align:center;"> 12 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Date </td>
   <td style="text-align:center;"> Date </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 4.0000000 </td>
   <td style="text-align:center;"> 276.0000000 </td>
   <td style="text-align:center;"> 2 </td>
  </tr>
</tbody>
</table>










Model Building
---------------------------------

The rsample package can be used to split the data into training and test set.


```r
library(rsample)

pothole_data<-potholedata%>%dplyr::select(-Date,-Label,-File,-Date,-MLT2.Feature)

data_split <- initial_split(pothole_data, strata = "Label_Combined", prop = 0.8)

pothole_train <- training(data_split)
pothole_test  <- testing(data_split)
```




The recipes package makes prepocessing step in machine learning very convenient. Most preprocessing steps involves one single line of code. The first step is to apply the Yeo-Johnson Power transformation. It is similar to the popular Box-Cox Transformation but includes transformation family of  variables that include negative values. We do this transformation  to stabilize variance and make the data more normal distribution-like. Next is to center and standardize all numeric variables in  the data to a mean of zero and a unit variance. With step-other function we lump  factor levels that occur in <= 10% of data as "other".step-dummy createsone-hot encoding or  dummy variables for all nominal predictor factor variables except the response One-hot encoding.



```r
pothole_recipe2 <- recipe(Label_Combined ~ ., data = pothole_train ) %>%
  #Transform numeric skewed predictors
  step_YeoJohnson(all_numeric()) %>%
  # standardize the data 
  step_center(all_numeric(), -all_outcomes()) %>%
  #scale the data
  step_scale(all_numeric(), -all_outcomes()) %>%
  #step_kpca a specification of a recipe step that will convert numeric data into one or more principal components using a kernel basis expansion.
  #step_kpca(all_numeric(), num=6)%>%
  #step_log(Label, base = 10)
   # Lump factor levels that occur in <= 10% of data as "other"
  step_other(Direction, MLT1.Feature, threshold = 0.1) %>%
  # Create dummy variables for all nominal predictor factor variables except the response
  step_dummy(all_nominal(), -all_outcomes())%>%
  prep(data = pothole_train,retain = TRUE )

# split data into training and test set
test_tbl2  <- bake(pothole_recipe2, newdata = pothole_test)
train_tbl2 <- bake(pothole_recipe2, newdata = pothole_train) 
glimpse(train_tbl2)
```

```
## Observations: 226
## Variables: 13
## $ Label_Combined      <fct> B1, B1, B1, B1, B1, B1, B1, B1, B1, B1, B1...
## $ Peak.Duration       <dbl> 0.006525519, -0.207802332, -0.226370118, -...
## $ Vehicle.Speed..mph. <dbl> -0.8249478, -0.5814521, -0.5330513, -0.433...
## $ Peak.Z.Accel        <dbl> -2.1870155, -2.0950290, -2.2040901, -2.189...
## $ Peak.Lat.Accel      <dbl> -1.3096776, -1.0552851, -1.4598802, -1.291...
## $ Peak.Long.Accel     <dbl> -1.85372136, -1.04917684, -1.31762792, -1....
## $ Front.Slip          <dbl> -2.0399125, -1.4628490, -1.3852557, -1.758...
## $ Right.Slip          <dbl> -1.5197233, -1.4290844, -1.2639294, -1.429...
## $ Left.Slip           <dbl> -2.18627766, -1.68674759, -1.52218284, -2....
## $ Direction_Left4     <dbl> 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ...
## $ Direction_other     <dbl> 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, ...
## $ MLT1.Feature_Type2  <dbl> 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ...
## $ MLT1.Feature_other  <dbl> 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, ...
```





Multinomial Logistic Regression
----------------------------------------------------------

The first model we consider is the multinomial logistic regression. Multinomial logistic regression is used to model nominal outcome variables, in which the log odds of the outcomes are modeled as a linear combination of the predictor variables.


```r
library(ggrepel)
# Fit the multinomial logistic model
model_multlog  <- nnet::multinom(Label_Combined ~., data = train_tbl2)
```

```
## # weights:  70 (52 variable)
## initial  value 363.732968 
## iter  10 value 186.989385
## iter  20 value 93.855296
## iter  30 value 35.866528
## iter  40 value 32.017762
## iter  50 value 30.831075
## iter  60 value 29.827671
## iter  70 value 29.455249
## iter  80 value 29.228431
## iter  90 value 28.858957
## iter 100 value 28.619521
## final  value 28.619521 
## stopped after 100 iterations
```

```r
#summary(model_multlog )
```


```r
tidy(model_multlog)%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> y.level </th>
   <th style="text-align:center;"> term </th>
   <th style="text-align:center;"> estimate </th>
   <th style="text-align:center;"> std.error </th>
   <th style="text-align:center;"> statistic </th>
   <th style="text-align:center;"> p.value </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> (Intercept) </td>
   <td style="text-align:center;"> 1.006932e+43 </td>
   <td style="text-align:center;"> 123.808721 </td>
   <td style="text-align:center;"> 7.997665e-01 </td>
   <td style="text-align:center;"> 0.4238461 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Peak.Duration </td>
   <td style="text-align:center;"> 6.468647e+18 </td>
   <td style="text-align:center;"> 72.453981 </td>
   <td style="text-align:center;"> 5.978070e-01 </td>
   <td style="text-align:center;"> 0.5499687 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Vehicle.Speed..mph. </td>
   <td style="text-align:center;"> 1.104725e+07 </td>
   <td style="text-align:center;"> 32.174210 </td>
   <td style="text-align:center;"> 5.040587e-01 </td>
   <td style="text-align:center;"> 0.6142201 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Peak.Z.Accel </td>
   <td style="text-align:center;"> 5.335858e+07 </td>
   <td style="text-align:center;"> 164.997240 </td>
   <td style="text-align:center;"> 1.078354e-01 </td>
   <td style="text-align:center;"> 0.9141263 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Peak.Lat.Accel </td>
   <td style="text-align:center;"> 1.119356e+02 </td>
   <td style="text-align:center;"> 53.964076 </td>
   <td style="text-align:center;"> 8.742710e-02 </td>
   <td style="text-align:center;"> 0.9303320 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Peak.Long.Accel </td>
   <td style="text-align:center;"> 1.311299e+00 </td>
   <td style="text-align:center;"> 20.762958 </td>
   <td style="text-align:center;"> 1.305300e-02 </td>
   <td style="text-align:center;"> 0.9895855 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Front.Slip </td>
   <td style="text-align:center;"> 3.094576e+10 </td>
   <td style="text-align:center;"> 134.148466 </td>
   <td style="text-align:center;"> 1.800654e-01 </td>
   <td style="text-align:center;"> 0.8571012 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Right.Slip </td>
   <td style="text-align:center;"> 4.387685e+14 </td>
   <td style="text-align:center;"> 107.542443 </td>
   <td style="text-align:center;"> 3.135041e-01 </td>
   <td style="text-align:center;"> 0.7538977 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Left.Slip </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 147.569783 </td>
   <td style="text-align:center;"> -1.478489e-01 </td>
   <td style="text-align:center;"> 0.8824620 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Direction_Left4 </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> -1.970507e+09 </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> Direction_other </td>
   <td style="text-align:center;"> 5.796511e-01 </td>
   <td style="text-align:center;"> 152.479942 </td>
   <td style="text-align:center;"> -3.576400e-03 </td>
   <td style="text-align:center;"> 0.9971465 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> MLT1.Feature_Type2 </td>
   <td style="text-align:center;"> 6.878763e+05 </td>
   <td style="text-align:center;"> 7.952293 </td>
   <td style="text-align:center;"> 1.690250e+00 </td>
   <td style="text-align:center;"> 0.0909801 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B2 </td>
   <td style="text-align:center;"> MLT1.Feature_other </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> -7.021216e+09 </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> (Intercept) </td>
   <td style="text-align:center;"> 4.040040e+51 </td>
   <td style="text-align:center;"> 123.983569 </td>
   <td style="text-align:center;"> 9.584181e-01 </td>
   <td style="text-align:center;"> 0.3378520 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Peak.Duration </td>
   <td style="text-align:center;"> 1.743407e+18 </td>
   <td style="text-align:center;"> 72.251109 </td>
   <td style="text-align:center;"> 5.813388e-01 </td>
   <td style="text-align:center;"> 0.5610121 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Vehicle.Speed..mph. </td>
   <td style="text-align:center;"> 1.023150e-02 </td>
   <td style="text-align:center;"> 32.485612 </td>
   <td style="text-align:center;"> -1.410558e-01 </td>
   <td style="text-align:center;"> 0.8878259 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Peak.Z.Accel </td>
   <td style="text-align:center;"> 1.497944e+21 </td>
   <td style="text-align:center;"> 165.843708 </td>
   <td style="text-align:center;"> 2.940020e-01 </td>
   <td style="text-align:center;"> 0.7687564 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Peak.Lat.Accel </td>
   <td style="text-align:center;"> 2.493845e+03 </td>
   <td style="text-align:center;"> 54.157950 </td>
   <td style="text-align:center;"> 1.444217e-01 </td>
   <td style="text-align:center;"> 0.8851675 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Peak.Long.Accel </td>
   <td style="text-align:center;"> 3.748920e-01 </td>
   <td style="text-align:center;"> 20.817928 </td>
   <td style="text-align:center;"> -4.712850e-02 </td>
   <td style="text-align:center;"> 0.9624108 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Front.Slip </td>
   <td style="text-align:center;"> 1.146640e+09 </td>
   <td style="text-align:center;"> 134.198452 </td>
   <td style="text-align:center;"> 1.554422e-01 </td>
   <td style="text-align:center;"> 0.8764727 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Right.Slip </td>
   <td style="text-align:center;"> 6.288793e+15 </td>
   <td style="text-align:center;"> 107.505841 </td>
   <td style="text-align:center;"> 3.383774e-01 </td>
   <td style="text-align:center;"> 0.7350788 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Left.Slip </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 147.712431 </td>
   <td style="text-align:center;"> -1.929784e-01 </td>
   <td style="text-align:center;"> 0.8469758 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Direction_Left4 </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 15.058656 </td>
   <td style="text-align:center;"> -3.318957e+00 </td>
   <td style="text-align:center;"> 0.0009035 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> Direction_other </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> -6.555174e+10 </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> MLT1.Feature_Type2 </td>
   <td style="text-align:center;"> 3.297745e+07 </td>
   <td style="text-align:center;"> 6.873321 </td>
   <td style="text-align:center;"> 2.518627e+00 </td>
   <td style="text-align:center;"> 0.0117813 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B3 </td>
   <td style="text-align:center;"> MLT1.Feature_other </td>
   <td style="text-align:center;"> 6.279000e-04 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> -8.836191e+10 </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> (Intercept) </td>
   <td style="text-align:center;"> 2.363141e+49 </td>
   <td style="text-align:center;"> 124.004944 </td>
   <td style="text-align:center;"> 9.167914e-01 </td>
   <td style="text-align:center;"> 0.3592520 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Peak.Duration </td>
   <td style="text-align:center;"> 4.233409e+16 </td>
   <td style="text-align:center;"> 72.255228 </td>
   <td style="text-align:center;"> 5.298491e-01 </td>
   <td style="text-align:center;"> 0.5962165 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Vehicle.Speed..mph. </td>
   <td style="text-align:center;"> 8.000000e-07 </td>
   <td style="text-align:center;"> 32.559928 </td>
   <td style="text-align:center;"> -4.321252e-01 </td>
   <td style="text-align:center;"> 0.6656504 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Peak.Z.Accel </td>
   <td style="text-align:center;"> 1.716274e+24 </td>
   <td style="text-align:center;"> 165.857570 </td>
   <td style="text-align:center;"> 3.364465e-01 </td>
   <td style="text-align:center;"> 0.7365342 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Peak.Lat.Accel </td>
   <td style="text-align:center;"> 1.288872e+04 </td>
   <td style="text-align:center;"> 54.178156 </td>
   <td style="text-align:center;"> 1.746849e-01 </td>
   <td style="text-align:center;"> 0.8613272 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Peak.Long.Accel </td>
   <td style="text-align:center;"> 1.273826e-01 </td>
   <td style="text-align:center;"> 20.849234 </td>
   <td style="text-align:center;"> -9.883150e-02 </td>
   <td style="text-align:center;"> 0.9212721 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Front.Slip </td>
   <td style="text-align:center;"> 3.612412e+11 </td>
   <td style="text-align:center;"> 134.234403 </td>
   <td style="text-align:center;"> 1.982563e-01 </td>
   <td style="text-align:center;"> 0.8428446 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Right.Slip </td>
   <td style="text-align:center;"> 3.315180e+18 </td>
   <td style="text-align:center;"> 107.530926 </td>
   <td style="text-align:center;"> 3.965840e-01 </td>
   <td style="text-align:center;"> 0.6916743 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Left.Slip </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 147.782400 </td>
   <td style="text-align:center;"> -2.586204e-01 </td>
   <td style="text-align:center;"> 0.7959281 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Direction_Left4 </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 14.977781 </td>
   <td style="text-align:center;"> -3.823875e+00 </td>
   <td style="text-align:center;"> 0.0001314 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> Direction_other </td>
   <td style="text-align:center;"> 3.188615e+11 </td>
   <td style="text-align:center;"> 441.523491 </td>
   <td style="text-align:center;"> 5.999230e-02 </td>
   <td style="text-align:center;"> 0.9521617 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> MLT1.Feature_Type2 </td>
   <td style="text-align:center;"> 2.136756e+08 </td>
   <td style="text-align:center;"> 6.871591 </td>
   <td style="text-align:center;"> 2.791198e+00 </td>
   <td style="text-align:center;"> 0.0052513 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B4 </td>
   <td style="text-align:center;"> MLT1.Feature_other </td>
   <td style="text-align:center;"> 1.104226e+02 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 1.040894e+13 </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> (Intercept) </td>
   <td style="text-align:center;"> 4.434352e+15 </td>
   <td style="text-align:center;"> 147.413209 </td>
   <td style="text-align:center;"> 2.444025e-01 </td>
   <td style="text-align:center;"> 0.8069191 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Peak.Duration </td>
   <td style="text-align:center;"> 2.046723e+27 </td>
   <td style="text-align:center;"> 75.591690 </td>
   <td style="text-align:center;"> 8.319173e-01 </td>
   <td style="text-align:center;"> 0.4054556 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Vehicle.Speed..mph. </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 56.546553 </td>
   <td style="text-align:center;"> -7.853381e-01 </td>
   <td style="text-align:center;"> 0.4322553 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Peak.Z.Accel </td>
   <td style="text-align:center;"> 4.554239e+48 </td>
   <td style="text-align:center;"> 176.256593 </td>
   <td style="text-align:center;"> 6.356650e-01 </td>
   <td style="text-align:center;"> 0.5249948 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Peak.Lat.Accel </td>
   <td style="text-align:center;"> 6.726265e+02 </td>
   <td style="text-align:center;"> 62.987158 </td>
   <td style="text-align:center;"> 1.033733e-01 </td>
   <td style="text-align:center;"> 0.9176667 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Peak.Long.Accel </td>
   <td style="text-align:center;"> 2.950000e-04 </td>
   <td style="text-align:center;"> 26.937573 </td>
   <td style="text-align:center;"> -3.017524e-01 </td>
   <td style="text-align:center;"> 0.7628408 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Front.Slip </td>
   <td style="text-align:center;"> 5.853313e+04 </td>
   <td style="text-align:center;"> 145.595906 </td>
   <td style="text-align:center;"> 7.539600e-02 </td>
   <td style="text-align:center;"> 0.9398996 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Right.Slip </td>
   <td style="text-align:center;"> 3.327703e+21 </td>
   <td style="text-align:center;"> 108.832751 </td>
   <td style="text-align:center;"> 4.553461e-01 </td>
   <td style="text-align:center;"> 0.6488603 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Left.Slip </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 162.114774 </td>
   <td style="text-align:center;"> -1.253797e-01 </td>
   <td style="text-align:center;"> 0.9002230 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Direction_Left4 </td>
   <td style="text-align:center;"> 0.000000e+00 </td>
   <td style="text-align:center;"> 29.915098 </td>
   <td style="text-align:center;"> -2.621409e+00 </td>
   <td style="text-align:center;"> 0.0087567 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> Direction_other </td>
   <td style="text-align:center;"> 5.659578e+34 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 4.724513e+54 </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> MLT1.Feature_Type2 </td>
   <td style="text-align:center;"> 5.638244e-01 </td>
   <td style="text-align:center;"> 20.036849 </td>
   <td style="text-align:center;"> -2.859790e-02 </td>
   <td style="text-align:center;"> 0.9771853 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> B5 </td>
   <td style="text-align:center;"> MLT1.Feature_other </td>
   <td style="text-align:center;"> 8.524256e+02 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 4.544929e+88 </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
</tbody>
</table>





```r
z<-summary(model_multlog)$coefficients/summary(model_multlog)$standard.errors
# 2-tailed z test
 ((1 - pnorm(abs(z), 0, 1)) * 2) %>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> (Intercept) </th>
   <th style="text-align:center;"> Peak.Duration </th>
   <th style="text-align:center;"> Vehicle.Speed..mph. </th>
   <th style="text-align:center;"> Peak.Z.Accel </th>
   <th style="text-align:center;"> Peak.Lat.Accel </th>
   <th style="text-align:center;"> Peak.Long.Accel </th>
   <th style="text-align:center;"> Front.Slip </th>
   <th style="text-align:center;"> Right.Slip </th>
   <th style="text-align:center;"> Left.Slip </th>
   <th style="text-align:center;"> Direction_Left4 </th>
   <th style="text-align:center;"> Direction_other </th>
   <th style="text-align:center;"> MLT1.Feature_Type2 </th>
   <th style="text-align:center;"> MLT1.Feature_other </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> B2 </td>
   <td style="text-align:center;"> 0.4238461 </td>
   <td style="text-align:center;"> 0.5499687 </td>
   <td style="text-align:center;"> 0.6142201 </td>
   <td style="text-align:center;"> 0.9141263 </td>
   <td style="text-align:center;"> 0.9303320 </td>
   <td style="text-align:center;"> 0.9895855 </td>
   <td style="text-align:center;"> 0.8571012 </td>
   <td style="text-align:center;"> 0.7538977 </td>
   <td style="text-align:center;"> 0.8824620 </td>
   <td style="text-align:center;"> 0.0000000 </td>
   <td style="text-align:center;"> 0.9971465 </td>
   <td style="text-align:center;"> 0.0909801 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> B3 </td>
   <td style="text-align:center;"> 0.3378520 </td>
   <td style="text-align:center;"> 0.5610121 </td>
   <td style="text-align:center;"> 0.8878259 </td>
   <td style="text-align:center;"> 0.7687564 </td>
   <td style="text-align:center;"> 0.8851675 </td>
   <td style="text-align:center;"> 0.9624108 </td>
   <td style="text-align:center;"> 0.8764727 </td>
   <td style="text-align:center;"> 0.7350788 </td>
   <td style="text-align:center;"> 0.8469758 </td>
   <td style="text-align:center;"> 0.0009035 </td>
   <td style="text-align:center;"> 0.0000000 </td>
   <td style="text-align:center;"> 0.0117813 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> B4 </td>
   <td style="text-align:center;"> 0.3592520 </td>
   <td style="text-align:center;"> 0.5962165 </td>
   <td style="text-align:center;"> 0.6656504 </td>
   <td style="text-align:center;"> 0.7365342 </td>
   <td style="text-align:center;"> 0.8613272 </td>
   <td style="text-align:center;"> 0.9212721 </td>
   <td style="text-align:center;"> 0.8428446 </td>
   <td style="text-align:center;"> 0.6916743 </td>
   <td style="text-align:center;"> 0.7959281 </td>
   <td style="text-align:center;"> 0.0001314 </td>
   <td style="text-align:center;"> 0.9521617 </td>
   <td style="text-align:center;"> 0.0052513 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> B5 </td>
   <td style="text-align:center;"> 0.8069191 </td>
   <td style="text-align:center;"> 0.4054556 </td>
   <td style="text-align:center;"> 0.4322553 </td>
   <td style="text-align:center;"> 0.5249948 </td>
   <td style="text-align:center;"> 0.9176667 </td>
   <td style="text-align:center;"> 0.7628408 </td>
   <td style="text-align:center;"> 0.9398996 </td>
   <td style="text-align:center;"> 0.6488603 </td>
   <td style="text-align:center;"> 0.9002230 </td>
   <td style="text-align:center;"> 0.0087567 </td>
   <td style="text-align:center;"> 0.0000000 </td>
   <td style="text-align:center;"> 0.9771853 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
</tbody>
</table>




```r
glance(model_multlog) %>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> edf </th>
   <th style="text-align:center;"> deviance </th>
   <th style="text-align:center;"> AIC </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:center;"> 52 </td>
   <td style="text-align:center;"> 57.23904 </td>
   <td style="text-align:center;"> 161.239 </td>
  </tr>
</tbody>
</table>





```r
# Make predictions
pred3 = predict(model_multlog , newdata = test_tbl2, type="class")

data1=data.frame(test_tbl2["Label_Combined"],predicted=pred3)

#check accuracy
yardstick::metrics(data1,truth = Label_Combined, estimate = predicted) 
```

```
## # A tibble: 1 x 1
##   accuracy
##      <dbl>
## 1    0.926
```

```r
# Make predictions
predicted.classes <- model_multlog  %>% predict(test_tbl2)
head(predicted.classes)
```

```
## [1] B1 B1 B2 B1 B1 B3
## Levels: B1 B2 B3 B4 B5
```

```r
#Equivalently Model accuracy

mean(predicted.classes == test_tbl2$Label_Combined)
```

```
## [1] 0.9259259
```




```r
#plot variable importance
feature=factor(rownames(varImp(model_multlog ,scale=T)))
Importance=varImp(model_multlog ,scale=T)$Overall





Varplot(feature,Importance)
```

![ ]( /img/pothole/22.png)

```r
ggsave("/POTHOLEDETECTION/variable.png") 
```



```r
#confusion matrix
table(predicted.classes,test_tbl2$Label_Combined)
```

```
##                  
## predicted.classes B1 B2 B3 B4 B5
##                B1  4  0  0  0  0
##                B2  1 14  0  0  0
##                B3  0  1 15  0  0
##                B4  0  0  2 14  0
##                B5  0  0  0  0  3
```

Multi-class  Evaluation Metrics
----------------------------------------------------------

#### Macro-Averaging

The overall classification accuracy is defined as the fraction of instances that are correctly classified.  In order to assess the performance of a classification,these metrics are calculated from the model predictions. In cases where the class labels are not uniformly distributed or imbalance class labels, using  the accuracy metric alone may be misleading as one could predict the dominant class most of the time and still achieve a relatively high overall accuracy but very low precision or recall for other classes.

**Specificity or TNR (True Negative Rate):** Number of items correctly identified as negative out of total negatives- TN/(TN+FP)

**Recall or Sensitivity or TPR (True Positive Rate):** Number of items correctly identified as positive out of total true positives- TP/(TP+FN)
**Precision:** Number of items correctly identified as positive out of total items identified as positive- TP/(TP+FP)

	**F1 Score:** It is a harmonic mean of precision and recall given by- 
$F1 = \frac{2*Precision*Recall}{(Precision + Recall)} $

**Accuracy:** Percentage of total items classified correctly- (TP+TN)/(N+P)


#### Macro-averaged Metrics
The per-class metrics can be averaged over all the classes resulting in macro-averaged precision, recall and F-1.




```r
model_multlog_pred<-predict(model_multlog , newdata = test_tbl2, type="probs")

#pred <- predict(model_multlog, newdata = test_tbl2, probability = TRUE)

#MLmetrics::MultiLogLoss(y_true = test_tbl2$Label_Combined, y_pred = attr(model_multlog_pred, "probabilities"))
```

#### Overall Classification Accuracy


```r
l=caret::confusionMatrix(predicted.classes,test_tbl2$Label_Combined)

overall_classification_accuracy<-sum(diag(l$table))/sum(l$table)

l$overall%>%data.frame()%>%
  rename(`Macro Measure`=".")%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Macro Measure </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Accuracy </td>
   <td style="text-align:center;"> 0.9259259 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Kappa </td>
   <td style="text-align:center;"> 0.9002770 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyLower </td>
   <td style="text-align:center;"> 0.8210666 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyUpper </td>
   <td style="text-align:center;"> 0.9794490 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyNull </td>
   <td style="text-align:center;"> 0.3148148 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyPValue </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> McnemarPValue </td>
   <td style="text-align:center;"> NaN </td>
  </tr>
</tbody>
</table>

#### Per-class Precision, Recall, and F-1


```r
l$byClass%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Sensitivity </th>
   <th style="text-align:center;"> Specificity </th>
   <th style="text-align:center;"> Pos Pred Value </th>
   <th style="text-align:center;"> Neg Pred Value </th>
   <th style="text-align:center;"> Precision </th>
   <th style="text-align:center;"> Recall </th>
   <th style="text-align:center;"> F1 </th>
   <th style="text-align:center;"> Prevalence </th>
   <th style="text-align:center;"> Detection Rate </th>
   <th style="text-align:center;"> Detection Prevalence </th>
   <th style="text-align:center;"> Balanced Accuracy </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Class: B1 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 1.000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.9800000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.8888889 </td>
   <td style="text-align:center;"> 0.0925926 </td>
   <td style="text-align:center;"> 0.0740741 </td>
   <td style="text-align:center;"> 0.0740741 </td>
   <td style="text-align:center;"> 0.9000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B2 </td>
   <td style="text-align:center;"> 0.9333333 </td>
   <td style="text-align:center;"> 0.974359 </td>
   <td style="text-align:center;"> 0.9333333 </td>
   <td style="text-align:center;"> 0.9743590 </td>
   <td style="text-align:center;"> 0.9333333 </td>
   <td style="text-align:center;"> 0.9333333 </td>
   <td style="text-align:center;"> 0.9333333 </td>
   <td style="text-align:center;"> 0.2777778 </td>
   <td style="text-align:center;"> 0.2592593 </td>
   <td style="text-align:center;"> 0.2777778 </td>
   <td style="text-align:center;"> 0.9538462 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B3 </td>
   <td style="text-align:center;"> 0.8823529 </td>
   <td style="text-align:center;"> 0.972973 </td>
   <td style="text-align:center;"> 0.9375000 </td>
   <td style="text-align:center;"> 0.9473684 </td>
   <td style="text-align:center;"> 0.9375000 </td>
   <td style="text-align:center;"> 0.8823529 </td>
   <td style="text-align:center;"> 0.9090909 </td>
   <td style="text-align:center;"> 0.3148148 </td>
   <td style="text-align:center;"> 0.2777778 </td>
   <td style="text-align:center;"> 0.2962963 </td>
   <td style="text-align:center;"> 0.9276630 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B4 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.950000 </td>
   <td style="text-align:center;"> 0.8750000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.8750000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.9333333 </td>
   <td style="text-align:center;"> 0.2592593 </td>
   <td style="text-align:center;"> 0.2592593 </td>
   <td style="text-align:center;"> 0.2962963 </td>
   <td style="text-align:center;"> 0.9750000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B5 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 1.0000000 </td>
  </tr>
</tbody>
</table>

#### Macro-averaged Metrics


```r
macro_meaure=l$byClass%>%apply(.,2,mean)%>%
  data.frame()%>%
  rename(`Macro Measure`=".")

macro_meaure%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Macro Measure </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Sensitivity </td>
   <td style="text-align:center;"> 0.9231373 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Specificity </td>
   <td style="text-align:center;"> 0.9794664 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Pos Pred Value </td>
   <td style="text-align:center;"> 0.9491667 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Neg Pred Value </td>
   <td style="text-align:center;"> 0.9803455 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Precision </td>
   <td style="text-align:center;"> 0.9491667 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Recall </td>
   <td style="text-align:center;"> 0.9231373 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> F1 </td>
   <td style="text-align:center;"> 0.9329293 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Prevalence </td>
   <td style="text-align:center;"> 0.2000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Detection Rate </td>
   <td style="text-align:center;"> 0.1851852 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Detection Prevalence </td>
   <td style="text-align:center;"> 0.2000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Balanced Accuracy </td>
   <td style="text-align:center;"> 0.9513018 </td>
  </tr>
</tbody>
</table>


The confusion matrix is given as:


```r
l$table%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> B1 </th>
   <th style="text-align:center;"> B2 </th>
   <th style="text-align:center;"> B3 </th>
   <th style="text-align:center;"> B4 </th>
   <th style="text-align:center;"> B5 </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> B1 </td>
   <td style="text-align:center;"> 4 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> B2 </td>
   <td style="text-align:center;"> 1 </td>
   <td style="text-align:center;"> 14 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> B3 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 1 </td>
   <td style="text-align:center;"> 15 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> B4 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 2 </td>
   <td style="text-align:center;"> 14 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> B5 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 3 </td>
  </tr>
</tbody>
</table>

The function below can be used to find the multi-class logloss. Logloss is among the numerous evaluation metric for multi-class classfication models.


```r
pred_probs1<-predict(model_multlog , newdata = test_tbl2, type="probs")

#truth: integer vector with truth labels, values range from 0 to n - 1 classes
 # prob_matrix: predicted probs: column 1 => label 0, column 2 => label 1 and so on
  Multiclasslogloss = function(truth, pred_prob_matrix, eps = 1e-15){

     if(is.double(truth)=="FALSE"){
      
     truth=as.numeric(truth)-1 
      
    }
    
    
    if(max(truth) >= ncol(pred_prob_matrix) || min(truth) < 0){
      stop(cat('True labels should range from 0 to', ncol(pred_prob_matrix) - 1, '\n'))
    }
    
   
    
    
    

   pred_prob_matrix[pred_prob_matrix > 1 - eps] = 1 - eps
   pred_prob_matrix[pred_prob_matrix< eps] = eps
   pred_prob_matrix = t(apply(pred_prob_matrix, 1, function(r)r/sum(r)))
   truth_matrix = matrix(0, nrow = nrow(pred_prob_matrix), ncol = ncol(pred_prob_matrix))
   truth_matrix[matrix(c(1:nrow(pred_prob_matrix), truth + 1), ncol = 2)] = 1
   -sum(truth_matrix * log(pred_prob_matrix))/nrow(pred_prob_matrix)
  }
  

  
Multiclasslogloss(test_tbl2$Label_Combined, pred_probs1)
```

```
## [1] 0.3282304
```


#### Micro-averaged Metrics
The micro-averaged precision, recall, and F-1 can also be computed from the matrix above. Compared to unweighted macro-averaging, micro-averaging favors classes with a larger number of instances. Because the sum of the one-vs-all matrices is a symmetric matrix, the micro-averaged precision, recall, and F-1 wil be the same.



```r
 n = sum(l$table) # number of instances
 nc = nrow(l$table) # number of classes
 diag = diag(l$table) # number of correctly classified instances per class 
 rowsums = apply(l$table, 1, sum) # number of instances per class
 colsums = apply(l$table, 2, sum) # number of predictions per class
 p = rowsums / n # distribution of instances over the actual classes
 q = colsums / n # distribution of instances over the predicted classes
 
precision = diag / colsums 
recall = diag / rowsums 
f1 = 2 * precision * recall / (precision + recall) 
data.frame(precision, recall, f1)
```

```
##    precision    recall        f1
## B1 0.8000000 1.0000000 0.8888889
## B2 0.9333333 0.9333333 0.9333333
## B3 0.8823529 0.9375000 0.9090909
## B4 1.0000000 0.8750000 0.9333333
## B5 1.0000000 1.0000000 1.0000000
```

#### One-vs-all

For micro-averaging metrics , we can examine  the performance of the classifier one class at a time. This results in 5 binary classification task such that the class considered is the positive class and all others constitute the negative class.




```r
pacman::p_load(furrr)



### faster version using furrr package
oneVsAll =furrr::future_map(1 : nc,
                      function(i){
                        m = c(l$table[i,i],
                              rowsums[i] - l$table[i,i],
                              colsums[i] - l$table[i,i],
                              n-rowsums[i] - colsums[i] + l$table[i,i]);
                        return(matrix(m, nrow = 2, byrow = T))})







#sum matrices element wise
#s=rowSums(c, dims = 2)



#equivalenlty
#apply(c, c(1,2), sum)




## A general-purpose adder:
#this function adds the elements of the matrix
#in the list elementwise
add <- function(x) Reduce("+", x)
sum_all<-add(oneVsAll)
```




#### Average Accuracy
Similar to the overall accuracy, the average accuracy is defined as the fraction of correctly classified instances in the sum of one-vs-all matrices matrix.



```r
Average_Accuracy <- sum(diag(sum_all)) / sum(sum_all)

Average_Accuracy
```

```
## [1] 0.9703704
```

#### Micro-averaged Metrics
The micro-averaged precision, recall, and F-1 can also be computed from the matrix above. Compared to unweighted macro-averaging, micro-averaging favors classes with a larger number of instances. Because the sum of the one-vs-all matrices is a symmetric matrix, the micro-averaged precision, recall, and F-1 wil be the same.


```r
Micro_Accuracy<-(diag(sum_all) / apply(sum_all,1, sum))[1];
Micro_Accuracy
```

```
## [1] 0.9259259
```











Weighted k-Nearest Neighbor Classifier
----------------------------------------------------------

The Weighted k-Nearest Neighbor method expands k-nearest neighbor in several directions.It is used for both classification,ordinal classfication and regression. It uses kernel functions to weight the neighbors according to their distances. 


```r
fitControl <- trainControl(method="repeatedcv",
 #For repeated k-fold cross-validation only: the number of complete sets of folds to compute                          
                     repeats = 10,
                     savePredictions = "final",
                     classProbs=TRUE,
          #Either the number of folds or number of resampling iterations
                     number = 10,
                     summaryFunction=multiClassSummary,
                     allowParallel=TRUE) 
```



```r
knn_grid <- expand.grid(
  kmax = 1:9,
  distance = 1:3,
  kernel = c("rectangular", "triangular", "gaussian")
  )



knnFit <- caret::train(Label_Combined ~ ., 
                       data = train_tbl2, 
                       method = "kknn",
                       trControl = fitControl,
                       tuneGrid = knn_grid,
                       summaryFunction=multiClassSummary,
                        ## Specify which metric to optimize
                        metric = "Accuracy")

#Output of kNN fit
knnFit
```

```
## k-Nearest Neighbors 
## 
## 226 samples
##  12 predictor
##   5 classes: 'B1', 'B2', 'B3', 'B4', 'B5' 
## 
## No pre-processing
## Resampling: Cross-Validated (10 fold, repeated 10 times) 
## Summary of sample sizes: 204, 205, 203, 204, 204, 202, ... 
## Resampling results across tuning parameters:
## 
##   kmax  distance  kernel       logLoss   AUC        prAUC       Accuracy 
##   1     1         rectangular  4.548771  0.9162104  0.06699458  0.8682996
##   1     1         triangular   4.548771  0.9162104  0.06699458  0.8682996
##   1     1         gaussian     4.548771  0.9162104  0.06699458  0.8682996
##   1     2         rectangular  5.815951  0.8920005  0.08356107  0.8316110
##   1     2         triangular   5.815951  0.8920005  0.08356107  0.8316110
##   1     2         gaussian     5.815951  0.8920005  0.08356107  0.8316110
##   1     3         rectangular  6.352123  0.8835768  0.08867452  0.8160872
##   1     3         triangular   6.352123  0.8835768  0.08867452  0.8160872
##   1     3         gaussian     6.352123  0.8835768  0.08867452  0.8160872
##   2     1         rectangular  4.548771  0.9162104  0.06699458  0.8682996



##   Kappa      Mean_F1    Mean_Sensitivity  Mean_Specificity
##   0.8277033  0.8707264  0.8669524         0.9654684       
##   0.8277033  0.8707264  0.8669524         0.9654684       
##   0.8277033  0.8707264  0.8669524         0.9654684       
##   0.7792944  0.8375603  0.8288476         0.9551534       
##   0.7792944  0.8375603  0.8288476         0.9551534       
##   0.7792944  0.8375603  0.8288476         0.9551534       
##   0.7592663  0.8232414  0.8160048         0.9511489       
##   0.7592663  0.8232414  0.8160048         0.9511489       
##   0.7592663  0.8232414  0.8160048         0.9511489       
##   0.8277033  0.8707264  0.8669524         0.9654684       
   
      
       
##   Mean_Pos_Pred_Value  Mean_Neg_Pred_Value  Mean_Precision  Mean_Recall
##   0.8911250            0.9669165            0.8911250       0.8669524  
##   0.8911250            0.9669165            0.8911250       0.8669524  
##   0.8911250            0.9669165            0.8911250       0.8669524  
##   0.8664536            0.9575990            0.8664536       0.8288476  
##   0.8664536            0.9575990            0.8664536       0.8288476  
##   0.8664536            0.9575990            0.8664536       0.8288476  
##   0.8534597            0.9538081            0.8534597       0.8160048  
##   0.8534597            0.9538081            0.8534597       0.8160048  
##   0.8534597            0.9538081            0.8534597       0.8160048  
##   0.8911250            0.9669165            0.8911250       0.8669524  


##   Mean_Detection_Rate  Mean_Balanced_Accuracy
##   0.1736599            0.9162104             
##   0.1736599            0.9162104             
##   0.1736599            0.9162104             
##   0.1663222            0.8920005             
##   0.1663222            0.8920005             
##   0.1663222            0.8920005             
##   0.1632174            0.8835768             
##   0.1632174            0.8835768             
##   0.1632174            0.8835768             
##   0.1736599            0.9162104             
             

## Accuracy was used to select the optimal model using the largest value.
## The final values used for the model were kmax = 3, distance = 1 and
##  kernel = triangular.
```

```r
getTrainPerf(knnFit)
```

```
##   TrainlogLoss  TrainAUC TrainprAUC TrainAccuracy TrainKappa TrainMean_F1
## 1     2.647393 0.9457703  0.2740201     0.8757911  0.8374018    0.8769454
##   TrainMean_Sensitivity TrainMean_Specificity TrainMean_Pos_Pred_Value
## 1             0.8727143             0.9674464                    0.897
##   TrainMean_Neg_Pred_Value TrainMean_Precision TrainMean_Recall
## 1                0.9689589               0.897        0.8727143
##   TrainMean_Detection_Rate TrainMean_Balanced_Accuracy method
## 1                0.1751582                   0.9200803   kknn
```

```r
ggplot(knnFit)
```

![ ]( /img/pothole/23.png)


```r
saveRDS(knnFit , "/POTHOLEDETECTION/knnFit.rds")
knnFit <- readRDS("/POTHOLEDETECTION/knnFit.rds")
```





```r
kknnpred1 = predict(knnFit, newdata = test_tbl2, type="prob")
kknnpred = predict(knnFit, newdata = test_tbl2, type="raw")


library(yardstick)

# Compute the summary statistics
d2=data.frame(test_tbl2["Label_Combined"],predicted=kknnpred)
yardstick::metrics(d2,truth = Label_Combined, estimate = predicted) 
```

```
## # A tibble: 1 x 1
##   accuracy
##      <dbl>
## 1    0.833
```

```r
yardstick::conf_mat(d2,truth = Label_Combined, estimate = predicted)
```

```
##           Truth
## Prediction B1 B2 B3 B4 B5
##         B1  5  2  0  0  0
##         B2  0 10  1  0  0
##         B3  0  3 15  1  0
##         B4  0  0  1 12  0
##         B5  0  0  0  1  3
```

```r
l=caret::confusionMatrix(kknnpred,test_tbl2$Label_Combined)



l$overall%>%data.frame()%>%
  rename(`Macro Measure`=".")%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Macro Measure </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Accuracy </td>
   <td style="text-align:center;"> 0.8333333 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Kappa </td>
   <td style="text-align:center;"> 0.7789905 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyLower </td>
   <td style="text-align:center;"> 0.7070588 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyUpper </td>
   <td style="text-align:center;"> 0.9208456 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyNull </td>
   <td style="text-align:center;"> 0.3148148 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyPValue </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> McnemarPValue </td>
   <td style="text-align:center;"> NaN </td>
  </tr>
</tbody>
</table>

```r
l$byClass%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Sensitivity </th>
   <th style="text-align:center;"> Specificity </th>
   <th style="text-align:center;"> Pos Pred Value </th>
   <th style="text-align:center;"> Neg Pred Value </th>
   <th style="text-align:center;"> Precision </th>
   <th style="text-align:center;"> Recall </th>
   <th style="text-align:center;"> F1 </th>
   <th style="text-align:center;"> Prevalence </th>
   <th style="text-align:center;"> Detection Rate </th>
   <th style="text-align:center;"> Detection Prevalence </th>
   <th style="text-align:center;"> Balanced Accuracy </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Class: B1 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.9591837 </td>
   <td style="text-align:center;"> 0.7142857 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.7142857 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.8333333 </td>
   <td style="text-align:center;"> 0.0925926 </td>
   <td style="text-align:center;"> 0.0925926 </td>
   <td style="text-align:center;"> 0.1296296 </td>
   <td style="text-align:center;"> 0.9795918 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B2 </td>
   <td style="text-align:center;"> 0.6666667 </td>
   <td style="text-align:center;"> 0.9743590 </td>
   <td style="text-align:center;"> 0.9090909 </td>
   <td style="text-align:center;"> 0.8837209 </td>
   <td style="text-align:center;"> 0.9090909 </td>
   <td style="text-align:center;"> 0.6666667 </td>
   <td style="text-align:center;"> 0.7692308 </td>
   <td style="text-align:center;"> 0.2777778 </td>
   <td style="text-align:center;"> 0.1851852 </td>
   <td style="text-align:center;"> 0.2037037 </td>
   <td style="text-align:center;"> 0.8205128 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B3 </td>
   <td style="text-align:center;"> 0.8823529 </td>
   <td style="text-align:center;"> 0.8918919 </td>
   <td style="text-align:center;"> 0.7894737 </td>
   <td style="text-align:center;"> 0.9428571 </td>
   <td style="text-align:center;"> 0.7894737 </td>
   <td style="text-align:center;"> 0.8823529 </td>
   <td style="text-align:center;"> 0.8333333 </td>
   <td style="text-align:center;"> 0.3148148 </td>
   <td style="text-align:center;"> 0.2777778 </td>
   <td style="text-align:center;"> 0.3518519 </td>
   <td style="text-align:center;"> 0.8871224 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B4 </td>
   <td style="text-align:center;"> 0.8571429 </td>
   <td style="text-align:center;"> 0.9750000 </td>
   <td style="text-align:center;"> 0.9230769 </td>
   <td style="text-align:center;"> 0.9512195 </td>
   <td style="text-align:center;"> 0.9230769 </td>
   <td style="text-align:center;"> 0.8571429 </td>
   <td style="text-align:center;"> 0.8888889 </td>
   <td style="text-align:center;"> 0.2592593 </td>
   <td style="text-align:center;"> 0.2222222 </td>
   <td style="text-align:center;"> 0.2407407 </td>
   <td style="text-align:center;"> 0.9160714 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B5 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.9803922 </td>
   <td style="text-align:center;"> 0.7500000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.7500000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.8571429 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 0.0740741 </td>
   <td style="text-align:center;"> 0.9901961 </td>
  </tr>
</tbody>
</table>

```r
macro_meaure=l$byClass%>%apply(.,2,mean)%>%
  data.frame()%>%
  rename(`Macro Measure`=".")

macro_meaure%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Macro Measure </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Sensitivity </td>
   <td style="text-align:center;"> 0.8812325 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Specificity </td>
   <td style="text-align:center;"> 0.9561653 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Pos Pred Value </td>
   <td style="text-align:center;"> 0.8171854 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Neg Pred Value </td>
   <td style="text-align:center;"> 0.9555595 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Precision </td>
   <td style="text-align:center;"> 0.8171854 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Recall </td>
   <td style="text-align:center;"> 0.8812325 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> F1 </td>
   <td style="text-align:center;"> 0.8363858 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Prevalence </td>
   <td style="text-align:center;"> 0.2000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Detection Rate </td>
   <td style="text-align:center;"> 0.1666667 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Detection Prevalence </td>
   <td style="text-align:center;"> 0.2000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Balanced Accuracy </td>
   <td style="text-align:center;"> 0.9186989 </td>
  </tr>
</tbody>
</table>

```r
 Multiclasslogloss(test_tbl2$Label_Combined, kknnpred1)
```

```
## [1] 2.122451
```




Multinomial Logistic Regression with H20
----------------------------------------------------------
 The h2o.glm function can be used to fit multinomial logistic regression and a host of other  generalized linear regression models including poisson, ordinal ,ridge and LASSO.


```r
library(h2o)
h2o.init()
```

```
##  Connection successful!
## 
## R is connected to the H2O cluster: 
##     H2O cluster uptime:         1 days 13 hours 
##     H2O cluster timezone:       America/Detroit 
##     H2O data parsing timezone:  UTC 
##     H2O cluster version:        3.20.0.2 
##     H2O cluster version age:    2 months and 5 days  
##     H2O cluster name:           H2O_started_from_R_nanaakwasiabayieboateng_par282 
##     H2O cluster total nodes:    1 
##     H2O cluster total memory:   1.54 GB 
##     H2O cluster total cores:    8 
##     H2O cluster allowed cores:  8 
##     H2O cluster healthy:        TRUE 
##     H2O Connection ip:          localhost 
##     H2O Connection port:        54321 
##     H2O Connection proxy:       NA 
##     H2O Internal Security:      FALSE 
##     H2O API Extensions:         XGBoost, Algos, AutoML, Core V3, Core V4 
##     R Version:                  R version 3.5.0 (2018-04-23)
```

```r
pf=as.h2o(train_tbl2)
```

```
## 
  |                                                                       
  |                                                                 |   0%
  |                                                                       
  |=================================================================| 100%
```

```r
pftest=as.h2o(test_tbl2)
```

```
## 
  |                                                                       
  |                                                                 |   0%
  |                                                                       
  |=================================================================| 100%
```

```r
# Run GLM 
myX = setdiff(colnames(train_tbl2), "Label_Combined")

h2o_mult<-h2o.glm(y = "Label_Combined", x = myX, training_frame = pf, family = "multinomial",
nfolds = 0, alpha = 0, lambda_search = FALSE)
```

```
## 
  |                                                                       
  |                                                                 |   0%
  |                                                                       
  |=================================================================| 100%
```




```r
h2o.performance(h2o_mult)
```

```
## H2OMultinomialMetrics: glm
## ** Reported on training data. **
## 
## Training Set Metrics: 
## =====================
## 
## Extract training frame with `h2o.getFrame("train_tbl2")`
## MSE: (Extract with `h2o.mse`) 0.05720497
## RMSE: (Extract with `h2o.rmse`) 0.2391756
## Logloss: (Extract with `h2o.logloss`) 0.2008426
## Mean Per-Class Error: 0.06190476
## Null Deviance: (Extract with `h2o.nulldeviance`) 688.4571
## Residual Deviance: (Extract with `h2o.residual_deviance`) 90.78083
## R^2: (Extract with `h2o.r2`) 0.9580881
## AIC: (Extract with `h2o.aic`) NaN
## Confusion Matrix: Extract with `h2o.confusionMatrix(<model>,train = TRUE)`)
## =========================================================================
## Confusion Matrix: Row labels: Actual class; Column labels: Predicted class
##        B1 B2 B3 B4 B5  Error       Rate
## B1     28  0  0  0  0 0.0000 =   0 / 28
## B2      1 39  2  0  0 0.0714 =   3 / 42
## B3      0  3 60  7  0 0.1429 =  10 / 70
## B4      0  0  6 57  0 0.0952 =   6 / 63
## B5      0  0  0  0 23 0.0000 =   0 / 23
## Totals 29 42 68 64 23 0.0841 = 19 / 226
## 
## Hit Ratio Table: Extract with `h2o.hit_ratio_table(<model>,train = TRUE)`
## =======================================================================
## Top-5 Hit Ratios: 
##   k hit_ratio
## 1 1  0.915929
## 2 2  1.000000
## 3 3  1.000000
## 4 4  1.000000
## 5 5  1.000000
```

```r
pftest=as.h2o(test_tbl2)
```

```
## 
  |                                                                       
  |                                                                 |   0%
  |                                                                       
  |=================================================================| 100%
```

```r
predh20mult=h2o.predict(h2o_mult,pftest)
```

```
## 
  |                                                                       
  |                                                                 |   0%
  |                                                                       
  |=================================================================| 100%
```

```r
predict_model.H2OMultinomialModel <- function(x, newdata, type, ...) {
    
  
# Function performs prediction and returns dataframe with Response
  
# x is h2o model
# newdata is data frame
# type is only setup for data frame

    pred <- h2o.predict(x, as.h2o(newdata))

    # return classification probabilities only
    return(as.data.frame(pred[,-1]))

}

h2ologisticpred=predict_model.H2OMultinomialModel(h2o_mult,pftest)
```

```
## 
  |                                                                       
  |                                                                 |   0%
  |                                                                       
  |=================================================================| 100%
```

```r
h2o_multdata<-data.frame(h2o.varimp(h2o_mult))



Varplot(feature=h2o_multdata$names,Importance=h2o_multdata$coefficients)
```

![ ]( /img/pothole/24.png)


```r
ggsave("/POTHOLEDETECTION/h2o_multcombined.png") 
```


#### Metric Evaluation


```r
# predicted probabilities for each class
head(h2ologisticpred)
```

```
##           B1           B2           B3           B4           B5
## 1 0.97217723 2.776202e-02 6.074508e-05 4.476462e-09 5.842084e-21
## 2 0.99993751 6.248919e-05 1.404794e-13 3.751218e-19 2.523806e-33
## 3 0.15851847 8.404513e-01 1.030224e-03 2.189931e-09 5.605275e-23
## 4 0.98302422 1.697135e-02 4.427456e-06 4.436548e-14 7.376240e-28
## 5 0.98546664 1.453336e-02 1.128159e-09 2.050341e-15 4.547862e-28
## 6 0.02611215 4.125397e-01 5.542656e-01 7.082515e-03 2.472140e-10
```

```r
#select the indices of the column on rows  of the class with the highest predicted probability as the class label prediction


x=apply(h2ologisticpred, 1, which.max)

prob=apply(h2ologisticpred,1,max)


## Equivalent  way to convert numeric values to factor variables with dplyr
# recode works better, it preserves levels in the factors
y=recode_factor(x, `1` = "B1", `2` = "B2", `3` = "B3",`4` = "B4", `5` = "B5")



probdataframe<-data.frame(x=x,prob=prob,predclass=y)

#accuracy

mean(test_tbl2$Label_Combined==probdataframe$predclass)
```

```
## [1] 0.8703704
```

```r
l=caret::confusionMatrix(probdataframe$predclass,test_tbl2$Label_Combined)



l$overall%>%data.frame()%>%
  rename(`Macro Measure`=".")%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Macro Measure </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Accuracy </td>
   <td style="text-align:center;"> 0.8703704 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Kappa </td>
   <td style="text-align:center;"> 0.8269231 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyLower </td>
   <td style="text-align:center;"> 0.7509878 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyUpper </td>
   <td style="text-align:center;"> 0.9462570 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyNull </td>
   <td style="text-align:center;"> 0.3148148 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyPValue </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> McnemarPValue </td>
   <td style="text-align:center;"> NaN </td>
  </tr>
</tbody>
</table>

```r
l$byClass%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Sensitivity </th>
   <th style="text-align:center;"> Specificity </th>
   <th style="text-align:center;"> Pos Pred Value </th>
   <th style="text-align:center;"> Neg Pred Value </th>
   <th style="text-align:center;"> Precision </th>
   <th style="text-align:center;"> Recall </th>
   <th style="text-align:center;"> F1 </th>
   <th style="text-align:center;"> Prevalence </th>
   <th style="text-align:center;"> Detection Rate </th>
   <th style="text-align:center;"> Detection Prevalence </th>
   <th style="text-align:center;"> Balanced Accuracy </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Class: B1 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.9591837 </td>
   <td style="text-align:center;"> 0.6666667 </td>
   <td style="text-align:center;"> 0.9791667 </td>
   <td style="text-align:center;"> 0.6666667 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.7272727 </td>
   <td style="text-align:center;"> 0.0925926 </td>
   <td style="text-align:center;"> 0.0740741 </td>
   <td style="text-align:center;"> 0.1111111 </td>
   <td style="text-align:center;"> 0.8795918 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B2 </td>
   <td style="text-align:center;"> 0.7333333 </td>
   <td style="text-align:center;"> 0.9743590 </td>
   <td style="text-align:center;"> 0.9166667 </td>
   <td style="text-align:center;"> 0.9047619 </td>
   <td style="text-align:center;"> 0.9166667 </td>
   <td style="text-align:center;"> 0.7333333 </td>
   <td style="text-align:center;"> 0.8148148 </td>
   <td style="text-align:center;"> 0.2777778 </td>
   <td style="text-align:center;"> 0.2037037 </td>
   <td style="text-align:center;"> 0.2222222 </td>
   <td style="text-align:center;"> 0.8538462 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B3 </td>
   <td style="text-align:center;"> 0.8823529 </td>
   <td style="text-align:center;"> 0.9459459 </td>
   <td style="text-align:center;"> 0.8823529 </td>
   <td style="text-align:center;"> 0.9459459 </td>
   <td style="text-align:center;"> 0.8823529 </td>
   <td style="text-align:center;"> 0.8823529 </td>
   <td style="text-align:center;"> 0.8823529 </td>
   <td style="text-align:center;"> 0.3148148 </td>
   <td style="text-align:center;"> 0.2777778 </td>
   <td style="text-align:center;"> 0.3148148 </td>
   <td style="text-align:center;"> 0.9141494 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B4 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.9500000 </td>
   <td style="text-align:center;"> 0.8750000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.8750000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.9333333 </td>
   <td style="text-align:center;"> 0.2592593 </td>
   <td style="text-align:center;"> 0.2592593 </td>
   <td style="text-align:center;"> 0.2962963 </td>
   <td style="text-align:center;"> 0.9750000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B5 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 1.0000000 </td>
  </tr>
</tbody>
</table>

```r
macro_meaure=l$byClass%>%apply(.,2,mean)%>%
  data.frame()%>%
  rename(`Macro Measure`=".")

macro_meaure%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Macro Measure </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Sensitivity </td>
   <td style="text-align:center;"> 0.8831373 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Specificity </td>
   <td style="text-align:center;"> 0.9658977 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Pos Pred Value </td>
   <td style="text-align:center;"> 0.8681373 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Neg Pred Value </td>
   <td style="text-align:center;"> 0.9659749 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Precision </td>
   <td style="text-align:center;"> 0.8681373 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Recall </td>
   <td style="text-align:center;"> 0.8831373 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> F1 </td>
   <td style="text-align:center;"> 0.8715548 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Prevalence </td>
   <td style="text-align:center;"> 0.2000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Detection Rate </td>
   <td style="text-align:center;"> 0.1740741 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Detection Prevalence </td>
   <td style="text-align:center;"> 0.2000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Balanced Accuracy </td>
   <td style="text-align:center;"> 0.9245175 </td>
  </tr>
</tbody>
</table>

```r
Multiclasslogloss(test_tbl2$Label_Combined, as.matrix(predh20mult[,-1]))
```

```
## [1] 0.2677523
```



Extreme Gradient Boosting Machines
----------------------------------------------------------
Gradient boosting is a  popular   machine learning lagorithm for regression and classification problems. It produces a prediction model in the form of an ensemble of weak prediction models using a baselearner such as  decision tree. It builds the model in a stage-wise fashion similar to other boosting methods, and then generalizes them by allowing optimization of an arbitrary differentiable loss function.
The XGBoost implementation of Gradient Boosting  uses a more regularized model formalization to control over-fitting. This  gives it  a better performance and  reduces overfitting.


```r
xgbmGrid <-  expand.grid(max_depth = c(1, 5, 8,10),
                         nrounds=300,
                        colsample_bytree = c(0.3,0.4,0.5,0.6,0.8,1), 
                        eta = seq.int(from=0.01, to=0.3, length.out=5),
                        min_child_weight = 1:3,
                        subsample=1,
                        
                        #rate_drop=0.1, 
                        #skip_drop=0.1
                        gamma=0.001
                        )

xgbm <-caret::train(Label_Combined ~ ., data = train_tbl2, 
                 method = "xgbTree", 
                 trControl = fitControl, 
                 verbose = FALSE, 
                 ## Now specify the exact models 
                 ## to evaluate:
                  #summaryFunction=multiClassSummary,
                 tuneGrid = xgbmGrid)



saveRDS(xgbm , "/POTHOLEDETECTION/xgbm.rds")
xgbm <- readRDS("/POTHOLEDETECTION/xgbm.rds")



getTrainPerf(xgbm)
```

```
##   TrainlogLoss  TrainAUC TrainprAUC TrainAccuracy TrainKappa TrainMean_F1
## 1    0.3601013 0.9821397  0.6814514      0.868236  0.8277019    0.8726167
##   TrainMean_Sensitivity TrainMean_Specificity TrainMean_Pos_Pred_Value
## 1             0.8734095             0.9649483                0.8925939
##   TrainMean_Neg_Pred_Value TrainMean_Precision TrainMean_Recall
## 1                0.9663713           0.8925939        0.8734095
##   TrainMean_Detection_Rate TrainMean_Balanced_Accuracy  method
## 1                0.1736472                   0.9191789 xgbTree
```

```r
ggplot(xgbm)
```

![ ]( /img/pothole/26.png)

```r
xgbm$bestTune
```

```
##     nrounds max_depth    eta gamma colsample_bytree min_child_weight
## 122     300         8 0.0825 0.001              0.8                2
##     subsample
## 122         1
```

```r
xgbm_pred = predict(xgbm, newdata = test_tbl2, type="raw")
xgbm_pred1 = predict(xgbm, newdata = test_tbl2, type="prob")


xgbmd=data.frame(test_tbl2["Label_Combined"],predicted=xgbm_pred)
yardstick::metrics(xgbmd,truth = Label_Combined, estimate = predicted) 
```

```
## # A tibble: 1 x 1
##   accuracy
##      <dbl>
## 1    0.907
```

```r
l=caret::confusionMatrix(xgbm_pred,test_tbl2$Label_Combined)



l$overall%>%data.frame()%>%
  rename(`Macro Measure`=".")%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Macro Measure </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Accuracy </td>
   <td style="text-align:center;"> 0.9074074 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Kappa </td>
   <td style="text-align:center;"> 0.8756333 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyLower </td>
   <td style="text-align:center;"> 0.7969985 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyUpper </td>
   <td style="text-align:center;"> 0.9692472 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyNull </td>
   <td style="text-align:center;"> 0.3148148 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> AccuracyPValue </td>
   <td style="text-align:center;"> 0.0000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> McnemarPValue </td>
   <td style="text-align:center;"> NaN </td>
  </tr>
</tbody>
</table>

```r
l$byClass%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Sensitivity </th>
   <th style="text-align:center;"> Specificity </th>
   <th style="text-align:center;"> Pos Pred Value </th>
   <th style="text-align:center;"> Neg Pred Value </th>
   <th style="text-align:center;"> Precision </th>
   <th style="text-align:center;"> Recall </th>
   <th style="text-align:center;"> F1 </th>
   <th style="text-align:center;"> Prevalence </th>
   <th style="text-align:center;"> Detection Rate </th>
   <th style="text-align:center;"> Detection Prevalence </th>
   <th style="text-align:center;"> Balanced Accuracy </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Class: B1 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.9795918 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.9795918 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.0925926 </td>
   <td style="text-align:center;"> 0.0740741 </td>
   <td style="text-align:center;"> 0.0925926 </td>
   <td style="text-align:center;"> 0.8897959 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B2 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.9743590 </td>
   <td style="text-align:center;"> 0.9230769 </td>
   <td style="text-align:center;"> 0.9268293 </td>
   <td style="text-align:center;"> 0.9230769 </td>
   <td style="text-align:center;"> 0.8000000 </td>
   <td style="text-align:center;"> 0.8571429 </td>
   <td style="text-align:center;"> 0.2777778 </td>
   <td style="text-align:center;"> 0.2222222 </td>
   <td style="text-align:center;"> 0.2407407 </td>
   <td style="text-align:center;"> 0.8871795 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B3 </td>
   <td style="text-align:center;"> 0.9411765 </td>
   <td style="text-align:center;"> 0.9459459 </td>
   <td style="text-align:center;"> 0.8888889 </td>
   <td style="text-align:center;"> 0.9722222 </td>
   <td style="text-align:center;"> 0.8888889 </td>
   <td style="text-align:center;"> 0.9411765 </td>
   <td style="text-align:center;"> 0.9142857 </td>
   <td style="text-align:center;"> 0.3148148 </td>
   <td style="text-align:center;"> 0.2962963 </td>
   <td style="text-align:center;"> 0.3333333 </td>
   <td style="text-align:center;"> 0.9435612 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B4 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.9750000 </td>
   <td style="text-align:center;"> 0.9333333 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.9333333 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.9655172 </td>
   <td style="text-align:center;"> 0.2592593 </td>
   <td style="text-align:center;"> 0.2592593 </td>
   <td style="text-align:center;"> 0.2777778 </td>
   <td style="text-align:center;"> 0.9875000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Class: B5 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 1.0000000 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 0.0555556 </td>
   <td style="text-align:center;"> 1.0000000 </td>
  </tr>
</tbody>
</table>

```r
macro_meaure=l$byClass%>%apply(.,2,mean)%>%
  data.frame()%>%
  rename(`Macro Measure`=".")

macro_meaure%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> Macro Measure </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Sensitivity </td>
   <td style="text-align:center;"> 0.9082353 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Specificity </td>
   <td style="text-align:center;"> 0.9749794 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Pos Pred Value </td>
   <td style="text-align:center;"> 0.9090598 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Neg Pred Value </td>
   <td style="text-align:center;"> 0.9757287 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Precision </td>
   <td style="text-align:center;"> 0.9090598 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Recall </td>
   <td style="text-align:center;"> 0.9082353 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> F1 </td>
   <td style="text-align:center;"> 0.9073892 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Prevalence </td>
   <td style="text-align:center;"> 0.2000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Detection Rate </td>
   <td style="text-align:center;"> 0.1814815 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Detection Prevalence </td>
   <td style="text-align:center;"> 0.2000000 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Balanced Accuracy </td>
   <td style="text-align:center;"> 0.9416073 </td>
  </tr>
</tbody>
</table>

```r
 Multiclasslogloss(test_tbl2$Label_Combined, xgbm_pred1)
```

```
## [1] 0.263521
```



Conclusion
----------------------------------------------------------

The multinomial logistic regression has superior performance over the machine learning algorithms evaluated in this project. It's evaluation metrics including accuracy, F-1 score, sensitivity, specificity and precision is higher than for the other models considered.
