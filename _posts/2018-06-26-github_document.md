---
layout: post
title: Rendering markdown file for github
subtitle: Finance
gh-repo: NanaAkwasiAbayieBoateng/NanaAkwasiAbayieBoateng.github.io
gh-badge: [star, fork, follow]
tags: [test]
---





Rendering markdown file for github
================
Nana Boateng
June 26, 2018


Load Required Packages
----------------------

``` r
pacman::p_load(skimr,kable,kableExtra)
```

    ## Warning: package 'kable' is not available (for R version 3.5.0)

    ## Bioconductor version 3.7 (BiocInstaller 1.30.0), ?biocLite for help

    ## Warning in p_install(package, character.only = TRUE, ...):

    ## Warning in library(package, lib.loc = lib.loc, character.only = TRUE,
    ## logical.return = TRUE, : there is no package called 'kable'

    ## Warning in pacman::p_load(skimr, kable, kableExtra): Failed to install/load:
    ## kable

``` r
# Load the caret package
library(caret)
```

    ## Loading required package: lattice

    ## Loading required package: ggplot2

``` r
# Import dataset
orange <- read.csv('https://raw.githubusercontent.com/selva86/datasets/master/orange_juice_withmissing.csv')

# Structure of the dataframe
str(orange)
```

    ## 'data.frame':    1070 obs. of  18 variables:
    ##  $ Purchase      : Factor w/ 2 levels "CH","MM": 1 1 1 2 1 1 1 1 1 1 ...
    ##  $ WeekofPurchase: int  237 239 245 227 228 230 232 234 235 238 ...
    ##  $ StoreID       : int  1 1 1 1 7 7 7 7 7 7 ...
    ##  $ PriceCH       : num  1.75 1.75 1.86 1.69 1.69 1.69 1.69 1.75 1.75 1.75 ...
    ##  $ PriceMM       : num  1.99 1.99 2.09 1.69 1.69 1.99 1.99 1.99 1.99 1.99 ...
    ##  $ DiscCH        : num  0 0 0.17 0 0 0 0 0 0 0 ...
    ##  $ DiscMM        : num  0 0.3 0 0 0 0 0.4 0.4 0.4 0.4 ...
    ##  $ SpecialCH     : int  0 0 0 0 0 0 1 1 0 0 ...
    ##  $ SpecialMM     : int  0 1 0 0 0 1 1 0 0 0 ...
    ##  $ LoyalCH       : num  0.5 0.6 0.68 0.4 0.957 ...
    ##  $ SalePriceMM   : num  1.99 1.69 2.09 1.69 1.69 1.99 1.59 1.59 1.59 1.59 ...
    ##  $ SalePriceCH   : num  1.75 1.75 1.69 1.69 1.69 1.69 1.69 1.75 1.75 1.75 ...
    ##  $ PriceDiff     : num  0.24 -0.06 0.4 0 0 0.3 -0.1 -0.16 -0.16 -0.16 ...
    ##  $ Store7        : Factor w/ 2 levels "No","Yes": 1 1 1 1 2 2 2 2 2 2 ...
    ##  $ PctDiscMM     : num  0 0.151 0 0 0 ...
    ##  $ PctDiscCH     : num  0 0 0.0914 0 0 ...
    ##  $ ListPriceDiff : num  0.24 0.24 0.23 0 0 0.3 0.3 0.24 0.24 0.24 ...
    ##  $ STORE         : int  1 1 1 1 0 0 0 0 0 0 ...

``` r
# See top 6 rows and 10 columns
head(orange[, 1:10])
```

    ##   Purchase WeekofPurchase StoreID PriceCH PriceMM DiscCH DiscMM SpecialCH
    ## 1       CH            237       1    1.75    1.99   0.00    0.0         0
    ## 2       CH            239       1    1.75    1.99   0.00    0.3         0
    ## 3       CH            245       1    1.86    2.09   0.17    0.0         0
    ## 4       MM            227       1    1.69    1.69   0.00    0.0         0
    ## 5       CH            228       7    1.69    1.69   0.00    0.0         0
    ## 6       CH            230       7    1.69    1.99   0.00    0.0         0
    ##   SpecialMM  LoyalCH
    ## 1         0 0.500000
    ## 2         1 0.600000
    ## 3         0 0.680000
    ## 4         0 0.400000
    ## 5         0 0.956535
    ## 6         1 0.965228

Add a new chunk by clicking the *Insert Chunk* button on the toolbar or by pressing *Cmd+Option+I*.

Creating a Table
----------------

``` r
library(tidyverse)
```

    ## ── Attaching packages ────────────────

    ## ✔ tibble  1.4.2     ✔ purrr   0.2.5
    ## ✔ tidyr   0.8.1     ✔ dplyr   0.7.5
    ## ✔ readr   1.1.1     ✔ stringr 1.3.1
    ## ✔ tibble  1.4.2     ✔ forcats 0.3.0

    ## ── Conflicts ─────────────────────────
    ## ✖ dplyr::filter() masks stats::filter()
    ## ✖ dplyr::lag()    masks stats::lag()
    ## ✖ purrr::lift()   masks caret::lift()

``` r
library(DT)

kableExtra::kable(orange[1:10, 1:10])
```

<table>
<thead>
<tr>
<th style="text-align:left;">
Purchase
</th>
<th style="text-align:right;">
WeekofPurchase
</th>
<th style="text-align:right;">
StoreID
</th>
<th style="text-align:right;">
PriceCH
</th>
<th style="text-align:right;">
PriceMM
</th>
<th style="text-align:right;">
DiscCH
</th>
<th style="text-align:right;">
DiscMM
</th>
<th style="text-align:right;">
SpecialCH
</th>
<th style="text-align:right;">
SpecialMM
</th>
<th style="text-align:right;">
LoyalCH
</th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align:left;">
CH
</td>
<td style="text-align:right;">
237
</td>
<td style="text-align:right;">
1
</td>
<td style="text-align:right;">
1.75
</td>
<td style="text-align:right;">
1.99
</td>
<td style="text-align:right;">
0.00
</td>
<td style="text-align:right;">
0.0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0.500000
</td>
</tr>
<tr>
<td style="text-align:left;">
CH
</td>
<td style="text-align:right;">
239
</td>
<td style="text-align:right;">
1
</td>
<td style="text-align:right;">
1.75
</td>
<td style="text-align:right;">
1.99
</td>
<td style="text-align:right;">
0.00
</td>
<td style="text-align:right;">
0.3
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
1
</td>
<td style="text-align:right;">
0.600000
</td>
</tr>
<tr>
<td style="text-align:left;">
CH
</td>
<td style="text-align:right;">
245
</td>
<td style="text-align:right;">
1
</td>
<td style="text-align:right;">
1.86
</td>
<td style="text-align:right;">
2.09
</td>
<td style="text-align:right;">
0.17
</td>
<td style="text-align:right;">
0.0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0.680000
</td>
</tr>
<tr>
<td style="text-align:left;">
MM
</td>
<td style="text-align:right;">
227
</td>
<td style="text-align:right;">
1
</td>
<td style="text-align:right;">
1.69
</td>
<td style="text-align:right;">
1.69
</td>
<td style="text-align:right;">
0.00
</td>
<td style="text-align:right;">
0.0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0.400000
</td>
</tr>
<tr>
<td style="text-align:left;">
CH
</td>
<td style="text-align:right;">
228
</td>
<td style="text-align:right;">
7
</td>
<td style="text-align:right;">
1.69
</td>
<td style="text-align:right;">
1.69
</td>
<td style="text-align:right;">
0.00
</td>
<td style="text-align:right;">
0.0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0.956535
</td>
</tr>
<tr>
<td style="text-align:left;">
CH
</td>
<td style="text-align:right;">
230
</td>
<td style="text-align:right;">
7
</td>
<td style="text-align:right;">
1.69
</td>
<td style="text-align:right;">
1.99
</td>
<td style="text-align:right;">
0.00
</td>
<td style="text-align:right;">
0.0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
1
</td>
<td style="text-align:right;">
0.965228
</td>
</tr>
<tr>
<td style="text-align:left;">
CH
</td>
<td style="text-align:right;">
232
</td>
<td style="text-align:right;">
7
</td>
<td style="text-align:right;">
1.69
</td>
<td style="text-align:right;">
1.99
</td>
<td style="text-align:right;">
0.00
</td>
<td style="text-align:right;">
0.4
</td>
<td style="text-align:right;">
1
</td>
<td style="text-align:right;">
1
</td>
<td style="text-align:right;">
0.972182
</td>
</tr>
<tr>
<td style="text-align:left;">
CH
</td>
<td style="text-align:right;">
234
</td>
<td style="text-align:right;">
7
</td>
<td style="text-align:right;">
1.75
</td>
<td style="text-align:right;">
1.99
</td>
<td style="text-align:right;">
0.00
</td>
<td style="text-align:right;">
0.4
</td>
<td style="text-align:right;">
1
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0.977746
</td>
</tr>
<tr>
<td style="text-align:left;">
CH
</td>
<td style="text-align:right;">
235
</td>
<td style="text-align:right;">
7
</td>
<td style="text-align:right;">
1.75
</td>
<td style="text-align:right;">
1.99
</td>
<td style="text-align:right;">
0.00
</td>
<td style="text-align:right;">
0.4
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0.982197
</td>
</tr>
<tr>
<td style="text-align:left;">
CH
</td>
<td style="text-align:right;">
238
</td>
<td style="text-align:right;">
7
</td>
<td style="text-align:right;">
1.75
</td>
<td style="text-align:right;">
1.99
</td>
<td style="text-align:right;">
0.00
</td>
<td style="text-align:right;">
0.4
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0
</td>
<td style="text-align:right;">
0.985757
</td>
</tr>
</tbody>
</table>
``` r
DT::datatable(orange[1:10, 1:10])
```

![ ]( /img/unnamed-chunk-3-1.png)






