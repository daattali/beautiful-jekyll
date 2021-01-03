---
layout: post
title: " Exploratory Data Analysis"
subtitle: Visualization with ggplot Extensions
#output: rmarkdown::github_document

output:
  html_document:
    keep_md: true    
    toc: true
    toc_float: TRUE
    theme: united
author: Nana Boateng
df_print: paged
Time: '2018-07-26 06:04:51'
date: "July 26, 2018"
toc_depth: 3  # upto three depths of headings (specified by #, ## and ###)
number_sections: true  ## if you want number sections at each table header
highlight: tango  # specifies the syntax highlighting style
tags:  ggplot2,visualization,Data Exploration,ggplot Extensions
---

#<body style="background: #fff;">

Introduction
---------------------------------
In this post, I would like to go through some common methods of data exploration. Data exploration is one of the introductory analysis that is performed before any model building task. Data exploration can uncover some hidden patterns and  lead to  insights into the  some phenomenom behind the data.It can inform the selection of appropriate statistical techniques,tools and models. Exploratory techniques are also important for eliminating or sharpening potential hypotheses about the causes of the observed phenomena in the data. We can also detect outliers and anomalies in the data through exploration. Exploratory analysis emphasizes graphical visualizations of the data.





Load Required Packages
---------------------------------

The pacman package provides a convenient way to load packages. It installs the package before loading if it not already installed.One of my favorite themes that I use with ggplot is the theme_pubclean. Here I set all themes with ggplot by it.


```r
#install.packages("ggpubr")


#install_github("kassambara/easyGgplot2")
#p_install_gh("kassambara/easyGgplot2")

pacman::p_load(tidyverse,janitor,DataExplorer,skimr,ggpubr,viridis,kableExtra,Amelia,easyGgplot2,VIM)


theme_set(theme_pubclean())
```




The data for this analysis Orange Juice data, is contained in the ISLR package.The ISLR package created to store the  data for the popular introductory statistical learning text,  Introduction to Statistical Learning with Applications in R (Gareth James, Daniela Witten, Trevor Hastie and Rob Tibshirani).The data contains 1070 purchases where the customer either purchased Citrus Hill or Minute Maid Orange Juice. A number of characteristics of the customer and product are recorded.The categorical response variable is Purchase  with levels CH and MM indicating whether the customer purchased Citrus Hill or Minute Maid Orange Juice. The goal of this data is to predict which of the two brands of orange juice did customers want to buy based on some seventeen features which describes the product and nature of the customers. The dataset can be  [downloaded here](https://raw.githubusercontent.com/NanaAkwasiAbayieBoateng/ExploratoryDataAnalysis/master/orangejuice.csv). It contains 1070 observations and seveenteen features plus the response variable purchase.


#### Description of Variables:

1.  WeekofPurchase: Week of purchase
2.  StoreID: Store ID
3.  PriceCH: Price charged for CH
4.  PriceMM: Price charged for MM
5.  DiscCH: Discount offered for CH
6.  DiscMM: Discount offered for MM
7.  SpecialCH: Indicator of special on CH
8.  SpecialMM: Indicator of special on MM
9.  LoyalCH: Customer brand loyalty for CH
10.  SalePriceMM: Sale price for MM
11. SalePriceCH: Sale price for CH
12.  PriceDiff: Sale price of MM less sale price of CH
13.  Store7: A factor with levels No and Yes indicating whether the sale is at Store 7
14.  PctDiscMM: Percentage discount for MM
15.  PctDiscCH: Percentage discount for CH
16.  ListPriceDiff: List price of MM less list price of CH
17. STORE: store id.


```r
# Import dataset
orangejuice<-read_csv('https://raw.githubusercontent.com/NanaAkwasiAbayieBoateng/ExploratoryDataAnalysis/master/orangejuice.csv')

write_csv(orangejuice,"orangejuice.csv")

orangejuice%>%head()%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> Purchase </th>
   <th style="text-align:center;"> WeekofPurchase </th>
   <th style="text-align:center;"> StoreID </th>
   <th style="text-align:center;"> PriceCH </th>
   <th style="text-align:center;"> PriceMM </th>
   <th style="text-align:center;"> DiscCH </th>
   <th style="text-align:center;"> DiscMM </th>
   <th style="text-align:center;"> SpecialCH </th>
   <th style="text-align:center;"> SpecialMM </th>
   <th style="text-align:center;"> LoyalCH </th>
   <th style="text-align:center;"> SalePriceMM </th>
   <th style="text-align:center;"> SalePriceCH </th>
   <th style="text-align:center;"> PriceDiff </th>
   <th style="text-align:center;"> Store7 </th>
   <th style="text-align:center;"> PctDiscMM </th>
   <th style="text-align:center;"> PctDiscCH </th>
   <th style="text-align:center;"> ListPriceDiff </th>
   <th style="text-align:center;"> STORE </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:center;"> CH </td>
   <td style="text-align:center;"> 237 </td>
   <td style="text-align:center;"> 1 </td>
   <td style="text-align:center;"> 1.75 </td>
   <td style="text-align:center;"> 1.99 </td>
   <td style="text-align:center;"> 0.00 </td>
   <td style="text-align:center;"> 0.0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0.500000 </td>
   <td style="text-align:center;"> 1.99 </td>
   <td style="text-align:center;"> 1.75 </td>
   <td style="text-align:center;"> 0.24 </td>
   <td style="text-align:center;"> No </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.24 </td>
   <td style="text-align:center;"> 1 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> CH </td>
   <td style="text-align:center;"> 239 </td>
   <td style="text-align:center;"> 1 </td>
   <td style="text-align:center;"> 1.75 </td>
   <td style="text-align:center;"> 1.99 </td>
   <td style="text-align:center;"> 0.00 </td>
   <td style="text-align:center;"> 0.3 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 1 </td>
   <td style="text-align:center;"> 0.600000 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 1.75 </td>
   <td style="text-align:center;"> -0.06 </td>
   <td style="text-align:center;"> No </td>
   <td style="text-align:center;"> 0.150754 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.24 </td>
   <td style="text-align:center;"> 1 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> CH </td>
   <td style="text-align:center;"> 245 </td>
   <td style="text-align:center;"> 1 </td>
   <td style="text-align:center;"> 1.86 </td>
   <td style="text-align:center;"> 2.09 </td>
   <td style="text-align:center;"> 0.17 </td>
   <td style="text-align:center;"> 0.0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0.680000 </td>
   <td style="text-align:center;"> 2.09 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 0.40 </td>
   <td style="text-align:center;"> No </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.091398 </td>
   <td style="text-align:center;"> 0.23 </td>
   <td style="text-align:center;"> 1 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> MM </td>
   <td style="text-align:center;"> 227 </td>
   <td style="text-align:center;"> 1 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 0.00 </td>
   <td style="text-align:center;"> 0.0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0.400000 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 0.00 </td>
   <td style="text-align:center;"> No </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.00 </td>
   <td style="text-align:center;"> 1 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> CH </td>
   <td style="text-align:center;"> 228 </td>
   <td style="text-align:center;"> 7 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 0.00 </td>
   <td style="text-align:center;"> 0.0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 0.956535 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 0.00 </td>
   <td style="text-align:center;"> Yes </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.00 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> CH </td>
   <td style="text-align:center;"> 230 </td>
   <td style="text-align:center;"> 7 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 1.99 </td>
   <td style="text-align:center;"> 0.00 </td>
   <td style="text-align:center;"> 0.0 </td>
   <td style="text-align:center;"> 0 </td>
   <td style="text-align:center;"> 1 </td>
   <td style="text-align:center;"> 0.965228 </td>
   <td style="text-align:center;"> 1.99 </td>
   <td style="text-align:center;"> 1.69 </td>
   <td style="text-align:center;"> 0.30 </td>
   <td style="text-align:center;"> Yes </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.000000 </td>
   <td style="text-align:center;"> 0.30 </td>
   <td style="text-align:center;"> 0 </td>
  </tr>
</tbody>
</table>


Univariate Analysis
---------------------------------



```r
plot_str(orangejuice)
```

There are 40 missing observations in the data set.In this exploratory analysis we would simply delete these missing values. Imputing missing values would be discussed extensively in a later post.When the number of missing values is relative to the sample size is small in a data set, a basic approach to handling missing data is to delete them.


```r
plot_missing(orangejuice)
```

![ ]( /img/ExploratoryDataAnalysis/1.png)



An alternate visualization approach is to use visna function from the extracat package.The columns represent the variables in the data and the rows the missing pattern.The blue cells represent cells of the variable  with missing values.The proportion of missing values for each variable is shown by the bars vertically beneath cells.The right show the relative frequencies of patterns.

```r
pacman::p_load(extracat)


extracat::visna(orangejuice, sort = "b", sort.method="optile", fr=100, pmax=0.05, s = 2)
```

![ ]( /img/ExploratoryDataAnalysis/2.png)



```r
library(VIM)

aggr(orangejuice , col=c('navyblue','yellow'),
                    numbers=TRUE, sortVars=TRUE,
                    labels=names(orangejuice), cex.axis=.7,
                    gap=3, ylab=c("Missing data","Pattern"))
```

![ ]( /img/ExploratoryDataAnalysis/3.png)

```
## 
##  Variables sorted by number of missings: 
##        Variable        Count
##       SpecialMM 0.0046728972
##         LoyalCH 0.0046728972
##     SalePriceMM 0.0046728972
##       PctDiscMM 0.0046728972
##         PriceMM 0.0037383178
##          DiscMM 0.0037383178
##          DiscCH 0.0018691589
##       SpecialCH 0.0018691589
##       PctDiscCH 0.0018691589
##           STORE 0.0018691589
##         StoreID 0.0009345794
##         PriceCH 0.0009345794
##     SalePriceCH 0.0009345794
##       PriceDiff 0.0009345794
##        Purchase 0.0000000000
##  WeekofPurchase 0.0000000000
##          Store7 0.0000000000
##   ListPriceDiff 0.0000000000
```




```r
library(Amelia)
missmap(orangejuice, main = "Missing values vs observed",col=c('navyblue','yellow'),y.cex=0.5)
```

![ ]( /img/ExploratoryDataAnalysis/4.png)




```r
plot_histogram(orangejuice)
```

![ ]( /img/ExploratoryDataAnalysis/5.png)




```r
plot_density(orangejuice)
```

![ ]( /img/ExploratoryDataAnalysis/6.png)



```r
plot_bar(orangejuice)
```

![ ]( /img/ExploratoryDataAnalysis/7.png)

Purchases made at store store 7 is lower than other stores whereas 
more customers  purchased Citrus Hill than Minute Maid Orange Juice




Multivariate Analysis
---------------------------------
Multivariate analysis include examining the correlation structure between variables in the dataset and also the bivariate relationship between the response variable and each predictor variable. 






```r
pacman::p_load(GGally)

na.omit(orangejuice)%>%select_if(is.double)%>%ggpairs(  title = "Continuous Variables")
```

![ ]( /img/ExploratoryDataAnalysis/8.png)




Multiple continuous  variables can be visualized by Parallel Coordinate Plots (PCP). Each vertical axis represents a column variable in the data and the observations are drawn as lines connecting its value on the corresponding vertical axes. The ggplot extension  GGally package  has the ggparcoord function which can be used for PCP plots in R. High values for Week of purchase corresponds with stores with low ID numbers. Low values for Indicator of special on MM corresponds with higher customer loyalty



```r
#p_ <- GGally::print_if_interactive

# this time, color by diamond cut
p <- ggparcoord(data = na.omit(orangejuice), columns = c(2:10), groupColumn = "Purchase", title = "Parallel Coord. Plot of Orange Juice Data",scale = "uniminmax", boxplot = FALSE, mapping = ggplot2::aes(size = 1),showPoints = TRUE,alpha = .05,)+
  #scale_fill_viridis(discrete = T)+
  
    scale_fill_manual(values=c("#B9DE28FF" , "#D1E11CFF" ))+
   ggplot2::scale_size_identity()
#p_(p)
p
```

![ ]( /img/ExploratoryDataAnalysis/9.png)


```r
na.omit(orangejuice)%>%select_if(is.double)%>%
  mutate(Above_Avg = PriceCH > mean(PriceCH)) %>%
  GGally::ggparcoord(showPoints = TRUE,
 
    alpha = .05,
    scale = "center",
    columns = 1:8,
    groupColumn = "Above_Avg"
    )
```

![ ]( /img/ExploratoryDataAnalysis/10.png)




Correlation between numeric variables can also be visualized by a heatmap. Heatmaps can identify clusters with strong correlation among variables. The correlation matrix between the variables can be visualized neatly on a heatmap. e the correlation matrix and visualize this matrix with a heatmap.  Deep points represent low correlations whereas light yellow represents strong correlations. There exist strong correlations among variable pairs such as (WeekofPurchase, Price) ,( PctDisc, SalePrice )for both CH and MM,  ( ListPriceDiff, PriceMM) etc.


```r
plot_correlation(na.omit(orangejuice),type = "continuous",theme_config = list(legend.position = "bottom", axis.text.x =
  element_text(angle = 90)))
```

![ ]( /img/ExploratoryDataAnalysis/11.png)


The corrplot function can also equivalently plot the correlatio between variables in a dataset as shown below:


```r
pacman::p_load(plotly,corrr,RColorBrewer,corrplot)



na.omit(orangejuice)%>%select_if(is.numeric)%>%cor()%>%corrplot::corrplot()
```

![ ]( /img/ExploratoryDataAnalysis/12.png)

```r
#Equivalently
#na.omit(orangejuice)%>%select_if(is.numeric)%>%cor()%>%
#  corrplot.mixed(upper = "color", tl.col = "black")
```



```r
na.omit(orangejuice)%>%
  select_if(is.numeric) %>%
  cor() %>%
  heatmap(Rowv = NA, Colv = NA, scale = "column")
```

![ ]( /img/ExploratoryDataAnalysis/13.png)


An interactive heatmap can be easily plotted courtesy the d3heatmap package. 

```r
pacman::p_load(d3heatmap)

na.omit(orangejuice)%>%
  select_if(is.numeric) %>%
  cor() %>%
d3heatmap(colors = "Blues", scale = "col",
          dendrogram = "row", k_row = 3)
```

![ ]( /img/ExploratoryDataAnalysis/heatmap.png)

```r
ggsave("/Users/nanaakwasiabayieboateng/Documents/memphisclassesbooks/DataMiningscience/ExploratoryDataAnalysis/d3heatmap.pdf")
```




```r
library(devtools)

#install_github("easyGgplot2", "kassambara")


pacman::p_load(ggalt,gridExtra,scales,kassambara,easyGgplot2)


p1<-ggplot(orangejuice, aes(x=SalePriceCH, fill=Purchase)) + geom_bkde(alpha=0.5)
p2<-ggplot(orangejuice, aes(x=SalePriceMM, fill=Purchase)) + geom_bkde(alpha=0.5)



# Multiple graphs on the same page
easyGgplot2::ggplot2.multiplot(p1,p2, cols=2)
```

![ ]( /img/ExploratoryDataAnalysis/14.png)

The sale price for both purchased Citrus Hill and  Minute Maid Orange Juice is multimodal and the Citrus Hill has a higher sale price.





The skimr and mlr packages have functions that conveniently summaeizes a dataset and present the output in a tabular form.

```r
skimmed <-skim_to_wide(orangejuice)
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
   <th style="text-align:left;"> empty </th>
   <th style="text-align:left;"> n_unique </th>
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
   <td style="text-align:left;"> character </td>
   <td style="text-align:left;"> Purchase </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 2 </td>
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
   <td style="text-align:left;"> character </td>
   <td style="text-align:left;"> Store7 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> 3 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 2 </td>
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
   <td style="text-align:left;"> integer </td>
   <td style="text-align:left;"> SpecialCH </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> 1068 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.15 </td>
   <td style="text-align:left;"> 0.35 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 1 </td>
   <td style="text-align:left;"> ▇▁▁▁▁▁▁▂ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> integer </td>
   <td style="text-align:left;"> SpecialMM </td>
   <td style="text-align:left;"> 5 </td>
   <td style="text-align:left;"> 1065 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.16 </td>
   <td style="text-align:left;"> 0.37 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 1 </td>
   <td style="text-align:left;"> ▇▁▁▁▁▁▁▂ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> integer </td>
   <td style="text-align:left;"> STORE </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> 1068 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 1.63 </td>
   <td style="text-align:left;"> 1.43 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> 3 </td>
   <td style="text-align:left;"> 4 </td>
   <td style="text-align:left;"> ▇▃▁▅▁▅▁▃ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> integer </td>
   <td style="text-align:left;"> StoreID </td>
   <td style="text-align:left;"> 1 </td>
   <td style="text-align:left;"> 1069 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 3.96 </td>
   <td style="text-align:left;"> 2.31 </td>
   <td style="text-align:left;"> 1 </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> 3 </td>
   <td style="text-align:left;"> 7 </td>
   <td style="text-align:left;"> 7 </td>
   <td style="text-align:left;"> ▃▅▅▃▁▁▁▇ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> integer </td>
   <td style="text-align:left;"> WeekofPurchase </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 254.38 </td>
   <td style="text-align:left;"> 15.56 </td>
   <td style="text-align:left;"> 227 </td>
   <td style="text-align:left;"> 240 </td>
   <td style="text-align:left;"> 257 </td>
   <td style="text-align:left;"> 268 </td>
   <td style="text-align:left;"> 278 </td>
   <td style="text-align:left;"> ▆▅▅▃▅▇▆▇ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> DiscCH </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> 1068 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.052 </td>
   <td style="text-align:left;"> 0.12 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0.5 </td>
   <td style="text-align:left;"> ▇▁▁▁▁▁▁▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> DiscMM </td>
   <td style="text-align:left;"> 4 </td>
   <td style="text-align:left;"> 1066 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.12 </td>
   <td style="text-align:left;"> 0.21 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0.23 </td>
   <td style="text-align:left;"> 0.8 </td>
   <td style="text-align:left;"> ▇▁▁▂▁▁▁▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> ListPriceDiff </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.22 </td>
   <td style="text-align:left;"> 0.11 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0.14 </td>
   <td style="text-align:left;"> 0.24 </td>
   <td style="text-align:left;"> 0.3 </td>
   <td style="text-align:left;"> 0.44 </td>
   <td style="text-align:left;"> ▂▂▂▂▇▆▁▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> LoyalCH </td>
   <td style="text-align:left;"> 5 </td>
   <td style="text-align:left;"> 1065 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.57 </td>
   <td style="text-align:left;"> 0.31 </td>
   <td style="text-align:left;"> 1.1e-05 </td>
   <td style="text-align:left;"> 0.32 </td>
   <td style="text-align:left;"> 0.6 </td>
   <td style="text-align:left;"> 0.85 </td>
   <td style="text-align:left;"> 1 </td>
   <td style="text-align:left;"> ▅▂▃▃▆▃▃▇ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> PctDiscCH </td>
   <td style="text-align:left;"> 2 </td>
   <td style="text-align:left;"> 1068 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.027 </td>
   <td style="text-align:left;"> 0.062 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0.25 </td>
   <td style="text-align:left;"> ▇▁▁▁▁▁▁▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> PctDiscMM </td>
   <td style="text-align:left;"> 5 </td>
   <td style="text-align:left;"> 1065 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.059 </td>
   <td style="text-align:left;"> 0.1 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0.11 </td>
   <td style="text-align:left;"> 0.4 </td>
   <td style="text-align:left;"> ▇▁▁▂▁▁▁▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> PriceCH </td>
   <td style="text-align:left;"> 1 </td>
   <td style="text-align:left;"> 1069 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 1.87 </td>
   <td style="text-align:left;"> 0.1 </td>
   <td style="text-align:left;"> 1.69 </td>
   <td style="text-align:left;"> 1.79 </td>
   <td style="text-align:left;"> 1.86 </td>
   <td style="text-align:left;"> 1.99 </td>
   <td style="text-align:left;"> 2.09 </td>
   <td style="text-align:left;"> ▂▅▁▇▁▁▅▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> PriceDiff </td>
   <td style="text-align:left;"> 1 </td>
   <td style="text-align:left;"> 1069 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 0.15 </td>
   <td style="text-align:left;"> 0.27 </td>
   <td style="text-align:left;"> -0.67 </td>
   <td style="text-align:left;"> 0 </td>
   <td style="text-align:left;"> 0.23 </td>
   <td style="text-align:left;"> 0.32 </td>
   <td style="text-align:left;"> 0.64 </td>
   <td style="text-align:left;"> ▁▁▂▂▃▇▃▂ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> PriceMM </td>
   <td style="text-align:left;"> 4 </td>
   <td style="text-align:left;"> 1066 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 2.09 </td>
   <td style="text-align:left;"> 0.13 </td>
   <td style="text-align:left;"> 1.69 </td>
   <td style="text-align:left;"> 1.99 </td>
   <td style="text-align:left;"> 2.09 </td>
   <td style="text-align:left;"> 2.18 </td>
   <td style="text-align:left;"> 2.29 </td>
   <td style="text-align:left;"> ▁▁▁▃▁▇▃▂ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> SalePriceCH </td>
   <td style="text-align:left;"> 1 </td>
   <td style="text-align:left;"> 1069 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 1.82 </td>
   <td style="text-align:left;"> 0.14 </td>
   <td style="text-align:left;"> 1.39 </td>
   <td style="text-align:left;"> 1.75 </td>
   <td style="text-align:left;"> 1.86 </td>
   <td style="text-align:left;"> 1.89 </td>
   <td style="text-align:left;"> 2.09 </td>
   <td style="text-align:left;"> ▁▁▁▂▆▇▅▁ </td>
  </tr>
  <tr>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:left;"> SalePriceMM </td>
   <td style="text-align:left;"> 5 </td>
   <td style="text-align:left;"> 1065 </td>
   <td style="text-align:left;"> 1070 </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> NA </td>
   <td style="text-align:left;"> 1.96 </td>
   <td style="text-align:left;"> 0.25 </td>
   <td style="text-align:left;"> 1.19 </td>
   <td style="text-align:left;"> 1.69 </td>
   <td style="text-align:left;"> 2.09 </td>
   <td style="text-align:left;"> 2.13 </td>
   <td style="text-align:left;"> 2.29 </td>
   <td style="text-align:left;"> ▁▁▃▃▁▂▇▆ </td>
  </tr>
</tbody>
</table>

```r
mlr::summarizeColumns(orangejuice)%>%
  kable() %>%
  kable_styling()
```

<table class="table" style="margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;"> name </th>
   <th style="text-align:left;"> type </th>
   <th style="text-align:right;"> na </th>
   <th style="text-align:right;"> mean </th>
   <th style="text-align:right;"> disp </th>
   <th style="text-align:right;"> median </th>
   <th style="text-align:right;"> mad </th>
   <th style="text-align:right;"> min </th>
   <th style="text-align:right;"> max </th>
   <th style="text-align:right;"> nlevs </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> Purchase </td>
   <td style="text-align:left;"> character </td>
   <td style="text-align:right;"> 0 </td>
   <td style="text-align:right;"> NA </td>
   <td style="text-align:right;"> 0.3897196 </td>
   <td style="text-align:right;"> NA </td>
   <td style="text-align:right;"> NA </td>
   <td style="text-align:right;"> 4.17e+02 </td>
   <td style="text-align:right;"> 653.000000 </td>
   <td style="text-align:right;"> 2 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> WeekofPurchase </td>
   <td style="text-align:left;"> integer </td>
   <td style="text-align:right;"> 0 </td>
   <td style="text-align:right;"> 254.3813084 </td>
   <td style="text-align:right;"> 15.5582861 </td>
   <td style="text-align:right;"> 257.00 </td>
   <td style="text-align:right;"> 20.7564000 </td>
   <td style="text-align:right;"> 2.27e+02 </td>
   <td style="text-align:right;"> 278.000000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> StoreID </td>
   <td style="text-align:left;"> integer </td>
   <td style="text-align:right;"> 1 </td>
   <td style="text-align:right;"> 3.9569691 </td>
   <td style="text-align:right;"> 2.3081886 </td>
   <td style="text-align:right;"> 3.00 </td>
   <td style="text-align:right;"> 1.4826000 </td>
   <td style="text-align:right;"> 1.00e+00 </td>
   <td style="text-align:right;"> 7.000000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> PriceCH </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 1 </td>
   <td style="text-align:right;"> 1.8674275 </td>
   <td style="text-align:right;"> 0.1020172 </td>
   <td style="text-align:right;"> 1.86 </td>
   <td style="text-align:right;"> 0.1482600 </td>
   <td style="text-align:right;"> 1.69e+00 </td>
   <td style="text-align:right;"> 2.090000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> PriceMM </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 4 </td>
   <td style="text-align:right;"> 2.0850375 </td>
   <td style="text-align:right;"> 0.1344285 </td>
   <td style="text-align:right;"> 2.09 </td>
   <td style="text-align:right;"> 0.1334340 </td>
   <td style="text-align:right;"> 1.69e+00 </td>
   <td style="text-align:right;"> 2.290000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> DiscCH </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 2 </td>
   <td style="text-align:right;"> 0.0519569 </td>
   <td style="text-align:right;"> 0.1175628 </td>
   <td style="text-align:right;"> 0.00 </td>
   <td style="text-align:right;"> 0.0000000 </td>
   <td style="text-align:right;"> 0.00e+00 </td>
   <td style="text-align:right;"> 0.500000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> DiscMM </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 4 </td>
   <td style="text-align:right;"> 0.1234146 </td>
   <td style="text-align:right;"> 0.2141255 </td>
   <td style="text-align:right;"> 0.00 </td>
   <td style="text-align:right;"> 0.0000000 </td>
   <td style="text-align:right;"> 0.00e+00 </td>
   <td style="text-align:right;"> 0.800000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> SpecialCH </td>
   <td style="text-align:left;"> integer </td>
   <td style="text-align:right;"> 2 </td>
   <td style="text-align:right;"> 0.1470037 </td>
   <td style="text-align:right;"> 0.3542755 </td>
   <td style="text-align:right;"> 0.00 </td>
   <td style="text-align:right;"> 0.0000000 </td>
   <td style="text-align:right;"> 0.00e+00 </td>
   <td style="text-align:right;"> 1.000000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> SpecialMM </td>
   <td style="text-align:left;"> integer </td>
   <td style="text-align:right;"> 5 </td>
   <td style="text-align:right;"> 0.1624413 </td>
   <td style="text-align:right;"> 0.3690285 </td>
   <td style="text-align:right;"> 0.00 </td>
   <td style="text-align:right;"> 0.0000000 </td>
   <td style="text-align:right;"> 0.00e+00 </td>
   <td style="text-align:right;"> 1.000000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> LoyalCH </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 5 </td>
   <td style="text-align:right;"> 0.5652030 </td>
   <td style="text-align:right;"> 0.3080704 </td>
   <td style="text-align:right;"> 0.60 </td>
   <td style="text-align:right;"> 0.3891084 </td>
   <td style="text-align:right;"> 1.10e-05 </td>
   <td style="text-align:right;"> 0.999947 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> SalePriceMM </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 5 </td>
   <td style="text-align:right;"> 1.9619343 </td>
   <td style="text-align:right;"> 0.2525100 </td>
   <td style="text-align:right;"> 2.09 </td>
   <td style="text-align:right;"> 0.1482600 </td>
   <td style="text-align:right;"> 1.19e+00 </td>
   <td style="text-align:right;"> 2.290000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> SalePriceCH </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 1 </td>
   <td style="text-align:right;"> 1.8155192 </td>
   <td style="text-align:right;"> 0.1434442 </td>
   <td style="text-align:right;"> 1.86 </td>
   <td style="text-align:right;"> 0.1482600 </td>
   <td style="text-align:right;"> 1.39e+00 </td>
   <td style="text-align:right;"> 2.090000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> PriceDiff </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 1 </td>
   <td style="text-align:right;"> 0.1463237 </td>
   <td style="text-align:right;"> 0.2716379 </td>
   <td style="text-align:right;"> 0.23 </td>
   <td style="text-align:right;"> 0.1482600 </td>
   <td style="text-align:right;"> -6.70e-01 </td>
   <td style="text-align:right;"> 0.640000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> Store7 </td>
   <td style="text-align:left;"> character </td>
   <td style="text-align:right;"> 0 </td>
   <td style="text-align:right;"> NA </td>
   <td style="text-align:right;"> 0.3327103 </td>
   <td style="text-align:right;"> NA </td>
   <td style="text-align:right;"> NA </td>
   <td style="text-align:right;"> 3.56e+02 </td>
   <td style="text-align:right;"> 714.000000 </td>
   <td style="text-align:right;"> 2 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> PctDiscMM </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 5 </td>
   <td style="text-align:right;"> 0.0593881 </td>
   <td style="text-align:right;"> 0.1018414 </td>
   <td style="text-align:right;"> 0.00 </td>
   <td style="text-align:right;"> 0.0000000 </td>
   <td style="text-align:right;"> 0.00e+00 </td>
   <td style="text-align:right;"> 0.402010 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> PctDiscCH </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 2 </td>
   <td style="text-align:right;"> 0.0273179 </td>
   <td style="text-align:right;"> 0.0622811 </td>
   <td style="text-align:right;"> 0.00 </td>
   <td style="text-align:right;"> 0.0000000 </td>
   <td style="text-align:right;"> 0.00e+00 </td>
   <td style="text-align:right;"> 0.252688 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> ListPriceDiff </td>
   <td style="text-align:left;"> numeric </td>
   <td style="text-align:right;"> 0 </td>
   <td style="text-align:right;"> 0.2179907 </td>
   <td style="text-align:right;"> 0.1075354 </td>
   <td style="text-align:right;"> 0.24 </td>
   <td style="text-align:right;"> 0.0889560 </td>
   <td style="text-align:right;"> 0.00e+00 </td>
   <td style="text-align:right;"> 0.440000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
  <tr>
   <td style="text-align:left;"> STORE </td>
   <td style="text-align:left;"> integer </td>
   <td style="text-align:right;"> 2 </td>
   <td style="text-align:right;"> 1.6282772 </td>
   <td style="text-align:right;"> 1.4304973 </td>
   <td style="text-align:right;"> 2.00 </td>
   <td style="text-align:right;"> 1.4826000 </td>
   <td style="text-align:right;"> 0.00e+00 </td>
   <td style="text-align:right;"> 4.000000 </td>
   <td style="text-align:right;"> 0 </td>
  </tr>
</tbody>
</table>


```r
(spec_variables <- attr(orangejuice, "spec"))
```

```
## cols(
##   Purchase = col_character(),
##   WeekofPurchase = col_integer(),
##   StoreID = col_integer(),
##   PriceCH = col_double(),
##   PriceMM = col_double(),
##   DiscCH = col_double(),
##   DiscMM = col_double(),
##   SpecialCH = col_integer(),
##   SpecialMM = col_integer(),
##   LoyalCH = col_double(),
##   SalePriceMM = col_double(),
##   SalePriceCH = col_double(),
##   PriceDiff = col_double(),
##   Store7 = col_character(),
##   PctDiscMM = col_double(),
##   PctDiscCH = col_double(),
##   ListPriceDiff = col_double(),
##   STORE = col_integer()
## )
```


```r
spec_variables<-c("LoyalCH", "SalePriceMM","SalePriceCH" ,"PctDiscMM","PctDiscCH","ListPriceDiff","Purchase","Store7")


spec_variable<-noquote(spec_variables)
 
pm<-ggpairs(orangejuice,spec_variable , title = "",mapping = aes(color = Purchase))+
  theme(legend.position = "top")

pm
```

![ ]( /img/ExploratoryDataAnalysis/15.png)


We can select one of plots above as follows:

```r
pm[1,7]
```

![ ]( /img/ExploratoryDataAnalysis/16.png)



```r
na.omit(orangejuice)%>% select_if(~!is.double(.x))%>%
  ggpairs( mapping = aes(color = Purchase) , title = "Categorical Variables")+
  theme(legend.position = "top")
```

![ ]( /img/ExploratoryDataAnalysis/17.png)

```r
#Equivalently

#na.omit(orangejuice)%>% select_if(funs(!is.double(.)))%>%
 # ggpairs(  title = "Categorical Variables")


#index=!sapply(na.omit(orangejuice), is.double)
#orange_numeric<-orangejuice[index==TRUE]
#orange_numeric%>%ggpairs(  title = "Categorical Variables")



#na.omit(orangejuice)%>%select_if(negate(is.double))%>%
#  ggpairs(  title = "Categorical Variables")
```





```r
categorical_orange=na.omit(orangejuice)%>% select_if(~!is.double(.x))
continuous_orange=na.omit(orangejuice)%>% select_if(is.double)

categorical_orange<-noquote(names(categorical_orange))
continuous_orange<-noquote(names(continuous_orange))


ggduo(
  orangejuice, rev(continuous_orange), categorical_orange,
  mapping = aes(color = Purchase),
   types = list(continuous = wrap("smooth_loess", alpha = 0.25)),
  showStrips = FALSE,
  title = "Variable Comparison By Purchase",
  xlab = "Continuous Variables",
  ylab = "Categorical",
  legend = c(5,2)
) +
  theme(legend.position = "top")
```

![ ]( /img/ExploratoryDataAnalysis/18.png)



#</body>
