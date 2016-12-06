---
layout: post
title: "Quantitative Trading with R by H. Georgakopoulos"
subtitle: Chapter 1
share_img: https://github.com/fderyckel/fderyckel.github.io/blob/master/img/The_R_Trader_Ch01_files/figure-markdown_github/unnamed-chunk-22-1.png
tags: [Book_Review, quantmod, ggplot2, dplyr]
---

This post is a personal summary & interpretation of the first chapter of the *Quantitative Trading with R* book by H. Georgakopoulos.  
Although we have been using R for a shortwhile we still found quite a few good nuggets of learning in this chapter.  

Each chapter finish with a nice hand-out exercise.  Instead of recopying what the author did, we adapted it to something closer to our current interest.  


A **vector** is a one-dimensional array.

``` r
a <- c(1, 2, 3, 4)
a
```

    ## [1] 1 2 3 4

A vector can also contain other vectors

``` r
b <- c(a, 5, 6, 7, 8)
b
```

    ## [1] 1 2 3 4 5 6 7 8

``` r
b[2]
```

    ## [1] 2

**Vectorisation:** instead of performing operations on one element at a time, vectorization allows us to perform the same operation on all the elements at the same time. Vectorization allows to avoid looping through all the elements of the vector. Rather, the operation of interest is performed on all the elements at once.

``` r
b
```

    ## [1] 1 2 3 4 5 6 7 8

``` r
2*b
```

    ## [1]  2  4  6  8 10 12 14 16

``` r
b^2
```

    ## [1]  1  4  9 16 25 36 49 64

A **matrix** can be thought of as a two-dimensional vector. Matrices also hold data of a similar type.

``` r
my_matrix <- matrix(1:6, nrow = 2, ncol = 3)
my_matrix
```

    ##      [,1] [,2] [,3]
    ## [1,]    1    3    5
    ## [2,]    2    4    6

The matrix function expect the data to be arranged in columnar format. If we want the data in row format, we add the argument *byrow=TRUE*

``` r
my_matrix <- matrix(1:6, nrow = 2, ncol = 3, byrow=TRUE)
my_matrix
```

    ##      [,1] [,2] [,3]
    ## [1,]    1    2    3
    ## [2,]    4    5    6

To give names to the rows and columns of a matrix, we use the *dimnames(x)* function.

``` r
dimnames(my_matrix) <- list(c("one", "hello"), c("Col1", "Col2", "Col3"))
my_matrix
```

    ##       Col1 Col2 Col3
    ## one      1    2    3
    ## hello    4    5    6

A **data frame** is like a matrix which the elements do not need to be form the same type, it is like a spreadsheet on its own.

``` r
df <- data.frame(price = c(2, 4, 8.9),
                 symbol = c("XOM", "CVX", "HAL"),
                 action = c("buy", "sell", "accumulate"))
df
```

    ##   price symbol     action
    ## 1   2.0    XOM        buy
    ## 2   4.0    CVX       sell
    ## 3   8.9    HAL accumulate

``` r
str(df)
```

    ## 'data.frame':    3 obs. of  3 variables:
    ##  $ price : num  2 4 8.9
    ##  $ symbol: Factor w/ 3 levels "CVX","HAL","XOM": 3 1 2
    ##  $ action: Factor w/ 3 levels "accumulate","buy",..: 2 3 1

``` r
df <- data.frame(price = c(2, 4, 8.9),
                 symbol = c("XOM", "CVX", "HAL"),
                 action = c("buy", "sell", "accumulate"),
                 stringsAsFactors = FALSE)
df
```

    ##   price symbol     action
    ## 1   2.0    XOM        buy
    ## 2   4.0    CVX       sell
    ## 3   8.9    HAL accumulate

``` r
str(df)
```

    ## 'data.frame':    3 obs. of  3 variables:
    ##  $ price : num  2 4 8.9
    ##  $ symbol: chr  "XOM" "CVX" "HAL"
    ##  $ action: chr  "buy" "sell" "accumulate"

A **list** is like a data frame but it can contain elements of different types & dimensions

``` r
my_list <- list(a = c(1, 2, 3, 4, 5, 6, 7),
                b = matrix(1:20, nrow = 4, ncol = 5),
                c = data.frame(price = c(12.53, 9.76, 7.09, 56.3),
                               symbols = c("XOM", "CVX", "HAL", "IBM")))
my_list
```

    ## $a
    ## [1] 1 2 3 4 5 6 7
    ## 
    ## $b
    ##      [,1] [,2] [,3] [,4] [,5]
    ## [1,]    1    5    9   13   17
    ## [2,]    2    6   10   14   18
    ## [3,]    3    7   11   15   19
    ## [4,]    4    8   12   16   20
    ## 
    ## $c
    ##   price symbols
    ## 1 12.53     XOM
    ## 2  9.76     CVX
    ## 3  7.09     HAL
    ## 4 56.30     IBM

``` r
str(my_list)
```

    ## List of 3
    ##  $ a: num [1:7] 1 2 3 4 5 6 7
    ##  $ b: int [1:4, 1:5] 1 2 3 4 5 6 7 8 9 10 ...
    ##  $ c:'data.frame':   4 obs. of  2 variables:
    ##   ..$ price  : num [1:4] 12.53 9.76 7.09 56.3
    ##   ..$ symbols: Factor w/ 4 levels "CVX","HAL","IBM",..: 4 1 2 3

``` r
my_list[1]
```

    ## $a
    ## [1] 1 2 3 4 5 6 7

``` r
my_list[[1]]
```

    ## [1] 1 2 3 4 5 6 7

``` r
my_list[c(1,3)]
```

    ## $a
    ## [1] 1 2 3 4 5 6 7
    ## 
    ## $c
    ##   price symbols
    ## 1 12.53     XOM
    ## 2  9.76     CVX
    ## 3  7.09     HAL
    ## 4 56.30     IBM

A **enviroment** is a special data structure in *R* that we use for performance reason.

``` r
env <- new.env()
env[["first"]] <- 5
env$second <- 7
env
```

    ## <environment: 0x7fd392a81908>

``` r
ls(env)
```

    ## [1] "first"  "second"

If we want to get the values associate with the name, we use the *get* function

``` r
get("first", envir = env)
```

    ## [1] 5

**Function** are used when chunck of instructions have to be repeated quite often.
Here we will use functions to download price data, see their correlation then plot it.

First we ensure that all the symbols follow the structure: only 2 to 4 upper case letter (no digits or other symbols)

``` r
filter_symbols <- function(symbols){
  #name: filter_symbols
  #purpose: Convert all symbols to upper case and disregard all those that have more than 4 letters and those that contains anything else than the 26 letters
  #input: symbols = a vector of stock tickers
  #output: filtered_symbols = filtered symbols
  
  #convert symbols to upper case
  symbols <- toupper(symbols)
  
  #ensure the symbols follow the given rules (2 to 4 letters, no other symbols)
  valid <- regexpr("^[A-Z]{2,4}$", symbols)
  
  #return only the valid symbols
  return(sort(symbols[valid == 1]))
  
}

filter_symbols(c("MOT", "cvx", "123", "Gog2", "XLe"))
```

    ## [1] "CVX" "MOT" "XLE"

Correlation matrix, heatmap and discussion on correlated return.
----------------------------------------------------------------

First let's load the downloaded data.
Althoug, *Georgakopoulos* use the log on the return for a simple day, we'll use a 5 day moving average to try to reduce the noise. [Andreas Clenow](http://www.followingthetrend.com/2012/08/how-to-build-correlation-matrices/) wrote an interesting article on why to use return instead of price and also the need to normalize the data with the log of the return.

``` r
library(readr)
usdzmw <- read_csv("USDZMW.csv")
```

``` r
tail(usdzmw)
```

    ## # A tibble: 6 × 2
    ##         Date    Rate
    ##       <date>   <dbl>
    ## 1 2015-07-26 7.48670
    ## 2 2015-07-25 7.51963
    ## 3 2015-07-24 7.51963
    ## 4 2015-07-23 7.57500
    ## 5 2015-07-22 7.54404
    ## 6 2015-07-21 7.58001

``` r
str(usdzmw)
```

    ## Classes 'tbl_df', 'tbl' and 'data.frame':    365 obs. of  2 variables:
    ##  $ Date: Date, format: "2016-07-19" "2016-07-18" ...
    ##  $ Rate: num  9.8 10 10.2 10.2 10.1 ...
    ##  - attr(*, "spec")=List of 2
    ##   ..$ cols   :List of 2
    ##   .. ..$ Date:List of 1
    ##   .. .. ..$ format: chr ""
    ##   .. .. ..- attr(*, "class")= chr  "collector_date" "collector"
    ##   .. ..$ Rate: list()
    ##   .. .. ..- attr(*, "class")= chr  "collector_double" "collector"
    ##   ..$ default: list()
    ##   .. ..- attr(*, "class")= chr  "collector_guess" "collector"
    ##   ..- attr(*, "class")= chr "col_spec"

Let's have a quick look at the exchange rate over the last year.

``` r
library(quantmod)
rate <- xts(usdzmw[,2], order.by = usdzmw$Date, index.class = "POSICct")
tail(rate)
```

    ##                Rate
    ## 2016-07-14 10.18840
    ## 2016-07-15 10.09180
    ## 2016-07-16 10.17700
    ## 2016-07-17 10.17700
    ## 2016-07-18 10.01150
    ## 2016-07-19  9.80458

``` r
lineChart(rate, name = "USD-ZMW", TA="addRSI()")
```

![](/img/The_R_Trader_Ch01_files/figure-markdown_github/unnamed-chunk-14-1.png) The Kwacha has been extremely volatile over the last year, going [from one of the worst currency](http://www.bloomberg.com/news/articles/2015-09-25/barclays-sees-zambia-acting-to-stem-world-s-worst-currency-fall) in the world [to one of its best](http://www.bloomberg.com/news/articles/2016-04-14/zambia-s-world-beating-kwacha-shows-copper-can-outshine-gold). Go figure!

Zambia's economy is quite dependent on the price of copper and being a landlocked country, many of its imports are from South-Africa.
So let's get some data related to Copper and South-Africa.
We choose to get

-   [COPX](http://www.globalxfunds.com/funds/copx/) - an ETF that tracks the price of companies that are heavy into mining copper. (from Yahoo Finance)

-   [CU\_LME](http://www.lme.com/metals/non-ferrous/copper/) - the price of copper on the London Metal Exchange. (from Quandl)

-   [DBB](https://www.invesco.com/portal/site/us/financial-professional/etfs/product-detail?productId=DBB) - an ETF that tracks the price of industrial metal. (fron Yahoo Finance)

-   ZARZMW - the exchange rate between the SA Rand and the Kwacha (from Aonda)

-   USDZAR - the exchange rate between the USD and the SA Rand (from Aonda)

We load the data from our .csv file

``` r
copx <- read_csv(file = "COPX.csv")
```

``` r
dbb <- read_csv(file = "DBB.csv")
```

``` r
usdzmw <- read_csv(file = "USDZMW.csv")
```

``` r
usdzar <- read_csv(file = "USDZAR.csv")
```

``` r
zarzmw <- read_csv(file = "ZARZMW.csv")
```

``` r
cu_lme <- read_csv(file = "LME-PR_CU.csv")
```

``` r
dbb <- dbb[,c(1,5)]
copx <- copx[,c(1, 5)]
cu_lme <- cu_lme[,1:2]

colnames(dbb) <- c("Date", "DBB")
colnames(copx) <- c("Date", "COPX")
colnames(usdzar) <- c("Date", "USDZAR")
colnames(usdzmw) <- c("Date", "USDZMW")
colnames(zarzmw) <- c("Date", "ZARZMW")
colnames(cu_lme) <- c("Date", "CU_LME")
```

Now using the *dplyr* library, we can join all these data together into one data frame.

``` r
library(dplyr)
data <- usdzmw
data <- left_join(data, dbb, by = "Date")
data <- left_join(data, copx, by = "Date")
data <- left_join(data, usdzar, by = "Date")
data <- left_join(data, zarzmw, by = "Date")
data <- left_join(data, cu_lme, by = "Date")

#as some data, include weekend and some other doesn't, one should only keep the raws with the full data set
data <- na.omit(data)
head(data)
```

    ## # A tibble: 6 × 7
    ##         Date   USDZMW   DBB  COPX  USDZAR   ZARZMW CU_LME
    ##       <date>    <dbl> <dbl> <dbl>   <dbl>    <dbl>  <dbl>
    ## 1 2016-07-19  9.80458 13.79 16.57 14.3065 0.687800 4936.0
    ## 2 2016-07-18 10.01150 13.73 17.04 14.3169 0.703032 4838.0
    ## 3 2016-07-15 10.09180 13.73 17.12 14.3016 0.707889 4945.0
    ## 4 2016-07-14 10.18840 13.76 17.27 14.3400 0.713023 4911.0
    ## 5 2016-07-13 10.45760 13.69 17.14 14.3845 0.729379 4918.0
    ## 6 2016-07-12 10.36550 13.68 16.98 14.3598 0.723620 4810.5

``` r
cormat <- round(cor(data[,2:7], method = "pearson"), 2)
cormat
```

    ##        USDZMW   DBB  COPX USDZAR ZARZMW CU_LME
    ## USDZMW   1.00 -0.49  0.00   0.41   0.73  -0.21
    ## DBB     -0.49  1.00 -0.04  -0.60  -0.29   0.68
    ## COPX     0.00 -0.04  1.00   0.59  -0.29  -0.57
    ## USDZAR   0.41 -0.60  0.59   1.00  -0.17  -0.80
    ## ZARZMW   0.73 -0.29 -0.29  -0.17   1.00   0.12
    ## CU_LME  -0.21  0.68 -0.57  -0.80   0.12   1.00

Instead of using the data per se, it will be more useful to use the percentage of change from *t-1* to *t*. Idea taken from [here](http://stackoverflow.com/questions/31352685/how-can-i-calculate-the-percentage-change-within-a-group-for-multiple-columns-in).

``` r
require(dplyr)
pct <- function(x) {log(x/lag(x, n=5))}
data2 <- data %>% mutate_each(funs(pct), c(USDZMW, DBB, COPX, USDZAR, ZARZMW, CU_LME))
head(data2)
```

    ## # A tibble: 6 × 7
    ##         Date     USDZMW         DBB       COPX      USDZAR     ZARZMW
    ##       <date>      <dbl>       <dbl>      <dbl>       <dbl>      <dbl>
    ## 1 2016-07-19         NA          NA         NA          NA         NA
    ## 2 2016-07-18         NA          NA         NA          NA         NA
    ## 3 2016-07-15         NA          NA         NA          NA         NA
    ## 4 2016-07-14         NA          NA         NA          NA         NA
    ## 5 2016-07-13         NA          NA         NA          NA         NA
    ## 6 2016-07-12 0.05563336 -0.00800878 0.02444235 0.003718657 0.05076829
    ## # ... with 1 more variables: CU_LME <dbl>

We can now execute on the correlation matrix.

``` r
cormat <- round(cor(data2[,2:7], method = "pearson", use = "complete.obs"), 2)
cormat
```

    ##        USDZMW   DBB  COPX USDZAR ZARZMW CU_LME
    ## USDZMW   1.00 -0.06 -0.24   0.27   0.53   0.05
    ## DBB     -0.06  1.00  0.16  -0.43   0.14   0.77
    ## COPX    -0.24  0.16  1.00  -0.36   0.04   0.10
    ## USDZAR   0.27 -0.43 -0.36   1.00  -0.21  -0.35
    ## ZARZMW   0.53  0.14  0.04  -0.21   1.00   0.18
    ## CU_LME   0.05  0.77  0.10  -0.35   0.18   1.00

Now on the graphing part. To help us we have use this nice [tutorial](http://www.sthda.com/english/wiki/ggplot2-quick-correlation-matrix-heatmap-r-software-and-data-visualization). The first step is to only consider half of the matrix (let's say bottom half) then melt it using *rshape2* (as *tidyr* can not work with matrix) in order to be processed by *ggplot2*.

``` r
library(reshape2)
get_lower_trig <- function(cormat){
  cormat[upper.tri(cormat)] <- NA
  return(cormat)
}
lower_trig <- get_lower_trig(cormat)
lower_trig <- melt(lower_trig, na.rm=TRUE)
tail(lower_trig)
```

    ##      Var1   Var2 value
    ## 22 USDZAR USDZAR  1.00
    ## 23 ZARZMW USDZAR -0.21
    ## 24 CU_LME USDZAR -0.35
    ## 29 ZARZMW ZARZMW  1.00
    ## 30 CU_LME ZARZMW  0.18
    ## 36 CU_LME CU_LME  1.00

Let's see the result

``` r
library(ggplot2)
ggplot(data = lower_trig, aes(x = Var1, y = Var2, fill = value)) + 
  geom_tile(color = "white") + 
  scale_fill_gradient2(low = "blue", mid = "white", high = "red", midpoint = 0,
                       limit = c(-1, 1)) + 
  theme_minimal() + 
  theme(axis.text.x = element_text(angle = 45, vjust = 1, size = 12, hjust = 1)) + 
  coord_fixed()
```

![](/img/The_R_Trader_Ch01_files/figure-markdown_github/unnamed-chunk-21-1.png)

Using hierarichal clustering, we could make the graph more insightful.

``` r
require(reshape2)
require(ggplot2)

reorder_cormat <- function(cormat){
 dd <- as.dist((1-cormat) / 2)
 hc <- hclust(dd)
 cormat <- cormat[hc$order, hc$order]
}

cormat <- reorder_cormat(cormat)
lower_trig <- get_lower_trig(cormat)
lower_trig <- melt(lower_trig, na.rm = TRUE)

#redo the whole graph
ggplot(lower_trig, aes(x = Var1, y = Var2, fill = value)) + 
  geom_tile(color = "white") + 
  scale_fill_gradient2(low = "blue", mid = "white", high = "red",
                       midpoint = 0, limit = c(-1,1)) + 
  theme_minimal() + 
  theme(axis.text.x = element_text(angle = 45, vjust = 1, size = 12, hjust = 1), 
        legend.justification = c(1, 0),
        legend.position = c(0.6, 0.7),
        legend.direction = "horizontal") + 
  coord_fixed() + 
  geom_text(aes(Var1, Var2, label = value), color = "black", size = 4) +
  guides(fill = guide_colorbar(barwidth = 7, barheight = 1,
                               title.position = "top", title.hjust = 0.5))
```

![](/img/The_R_Trader_Ch01_files/figure-markdown_github/unnamed-chunk-22-1.png) If we keep in mind the [Anscombe's quartet](https://en.wikipedia.org/wiki/Anscombe%27s_quartet), we know that our *r* value alone might be misleading and do not give the whole picture.
There is another library we could use here to give us more insights in the distribution. *Performance Analytics* is a library we will use more and more as it is an essential tool to use in conjunction with *quantstrat* for back testing.

``` r
library(PerformanceAnalytics)
chart.Correlation(data2[,2:7], histogram = TRUE, pch = 19)
```

![](/img/The_R_Trader_Ch01_files/figure-markdown_github/unnamed-chunk-23-1.png)


We would really appreciate any feedback you have and / or any useful addition.  
