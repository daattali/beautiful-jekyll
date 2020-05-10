---
layout: post
title:  Returns on Exchange Traded Funds
subtitle:  performance of some popular ETF's
gh-repo: NanaAkwasiAbayieBoateng/NanaAkwasiAbayieBoateng.github.io
gh-badge: [star, fork, follow]
tags: [ETF, Quantitative Finance, Asset Return,quantmod]
---




#### Exchange Traded Funds

A collection of securities  for example stocks which usually tracks an underlying index  is known as an    Exchange - Traded Fund(ETF). ETF's share some similarity with mutual funds although they are listed on exchanges and their share is traded like stocks throughout the day. ETF's can be made up of various strategies and invest in diverse number of industry sectors.

The most popular index tracked by most ETF's is the S&P 500. For example the SPDR S&P 500 ETF (SPY) tracks the S&P 500. ETFs can include different types of investments, including stocks, commodities, bonds, or a mixture of investment types. ETF's  is traded on financial markets as a security with a price at which it can be bought and sold. Most ETF's are set up as Open-end funds meaning  there is no cap on the number of investors allowed in on the product.



#### Types of ETFs


There are various types of ETFs available to investors that can be used for income generation, speculation, price increases, and to hedge or partly offset risk in an investor's portfolio. Below are several examples of the types of ETFs.

- Bond ETFs may include government bonds, corporate bonds, and state and local government bonds called municipal bonds.
- Industry ETFs track a particular industry such as technology, banking, or the oil and gas sector.
- Commodity ETFs invest in commodities including crude oil or gold.
- Currency ETFs invest in foreign currencies such as the Euro or the British pound.
- Inverse ETFs attempt to earn gains from stock declines by shorting stocks. Shorting is selling a stock, expecting a decline in value, and repurchasing it at a lower price. Many inverse ETFs are Exchange Traded Notes (ETNs) and not true ETFs. An ETN is a bond but trades like a stock and is backed by an issuer like a bank.

#### How to Buy and Sell ETFs
ETF's are traded through licensed online and traditional broker  dealers. Most of the poular ETF brokers like Vanguard  also have robo-advisors which is a computer algorithm that attempts to mimic a human trader. Some ETF's go a step further by offering commision free products. Examples of  such brokers can easily be found online.


The following libraries required is loaded loaded here.


```r
library(ggplot2)
library(plotly)
library(rvest)
library(pbapply)
library(TTR)
library(dygraphs)
library(lubridate)
library(tidyquant)
library(timetk)
library(htmlwidgets)
library(kableExtra)
pacman::p_load(kable,dygraphs,DT,tidyverse,janitor,ggthemes,scales,ggpubr,viridis)

theme_set(theme_pubclean())
```









The table below shows some popular U.S. ETF brands and issuers. 


```r
library(rvest)
library(XML)
library(gt)
library(tidyverse)
library(glue)



webpage <- read_html("https://www.etf.com/sections/etf-league-tables/etf-league-table-2020-02-10")

tbls <- html_nodes(webpage, "table")

print(head(tbls))
```

```
## {xml_nodeset (2)}
## [1] <table border="0" cellpadding="2" cellspacing="0" class="IUtable" style=" ...
## [2] <table border="0" cellpadding="2" cellspacing="0" class="IUtable" style=" ...
```

```r
tbls_ls <- webpage %>%
        html_nodes("table") %>%
        .[[1]] %>%
        html_table(fill = TRUE)



colnames(tbls_ls)  <-  c("Brand","AUM ($, mm)","Net Flows ($, mm)","% of AUM")

tbls_ls  <- tbls_ls %>% janitor::clean_names()


#DT::datatable(tbls_ls, class = 'cell-border stripe')

tbls_ls %>%head()%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> brand </th>
   <th style="text-align:center;"> aum_mm </th>
   <th style="text-align:center;"> net_flows_mm </th>
   <th style="text-align:center;"> percent_of_aum </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:center;"> Brand </td>
   <td style="text-align:center;"> AUM ($, mm) </td>
   <td style="text-align:center;"> Net Flows ($, mm) </td>
   <td style="text-align:center;"> % of AUM </td>
  </tr>
  <tr>
   <td style="text-align:center;"> iShares </td>
   <td style="text-align:center;"> 1,761,739.92 </td>
   <td style="text-align:center;"> 1,120.23 </td>
   <td style="text-align:center;"> 0.06% </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Vanguard </td>
   <td style="text-align:center;"> 1,195,773.48 </td>
   <td style="text-align:center;"> 1,154.64 </td>
   <td style="text-align:center;"> 0.10% </td>
  </tr>
  <tr>
   <td style="text-align:center;"> SPDR </td>
   <td style="text-align:center;"> 737,904.99 </td>
   <td style="text-align:center;"> -710.71 </td>
   <td style="text-align:center;"> -0.10% </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Invesco </td>
   <td style="text-align:center;"> 232,732.50 </td>
   <td style="text-align:center;"> 250.17 </td>
   <td style="text-align:center;"> 0.11% </td>
  </tr>
  <tr>
   <td style="text-align:center;"> Schwab </td>
   <td style="text-align:center;"> 168,568.37 </td>
   <td style="text-align:center;"> 165.32 </td>
   <td style="text-align:center;"> 0.10% </td>
  </tr>
</tbody>
</table>



We can download the following ETF's some of which are actively managed and others which are passively managed from the yahoo API using the quantmod API.


```r
#library("RSelenium")

tickers= c("QQQ","IVV","SPY","VOO","VTI","IWB","GLD","EEM","XLF",
           "GDX","ARKW")

actively_managed =c("ARKW")

passively_managed <-  c("AGZ","IHI","IEUS","FCOM","VGT.IV","
VUG.IV")

vanguard <- c("MGK.IV","MGC.IV","VGT.IV","
VUG.IV","VONG.IV")

# The symbols vector holds our tickers. 
symbols <- c("SPY","EFA", "IJS", "EEM","AGG")

# The prices object will hold our raw price data 
prices <- 
  quantmod::getSymbols(tickers, src = 'yahoo', from = "2010-01-01", 
             auto.assign = TRUE, warnings = FALSE) %>% 
 furrr::future_map(~Ad(get(.))) %>%   
  reduce(merge) %>%   #reduce() combines from the left, reduce_right() combines from the right
  `colnames<-`(tickers)



#DT::datatable(data.frame(head(prices)))

data.frame(head(prices)) %>%head()%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:left;">   </th>
   <th style="text-align:center;"> QQQ </th>
   <th style="text-align:center;"> IVV </th>
   <th style="text-align:center;"> SPY </th>
   <th style="text-align:center;"> VOO </th>
   <th style="text-align:center;"> VTI </th>
   <th style="text-align:center;"> IWB </th>
   <th style="text-align:center;"> GLD </th>
   <th style="text-align:center;"> EEM </th>
   <th style="text-align:center;"> XLF </th>
   <th style="text-align:center;"> GDX </th>
   <th style="text-align:center;"> ARKW </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:left;"> 2010-01-04 </td>
   <td style="text-align:center;"> 41.71869 </td>
   <td style="text-align:center;"> 92.10523 </td>
   <td style="text-align:center;"> 92.24605 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 46.96941 </td>
   <td style="text-align:center;"> 51.31325 </td>
   <td style="text-align:center;"> 109.80 </td>
   <td style="text-align:center;"> 34.66187 </td>
   <td style="text-align:center;"> 7.660890 </td>
   <td style="text-align:center;"> 44.59262 </td>
   <td style="text-align:center;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> 2010-01-05 </td>
   <td style="text-align:center;"> 41.71869 </td>
   <td style="text-align:center;"> 92.37265 </td>
   <td style="text-align:center;"> 92.49020 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 47.14971 </td>
   <td style="text-align:center;"> 51.47793 </td>
   <td style="text-align:center;"> 109.70 </td>
   <td style="text-align:center;"> 34.91345 </td>
   <td style="text-align:center;"> 7.801696 </td>
   <td style="text-align:center;"> 45.02256 </td>
   <td style="text-align:center;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> 2010-01-06 </td>
   <td style="text-align:center;"> 41.46705 </td>
   <td style="text-align:center;"> 92.44558 </td>
   <td style="text-align:center;"> 92.55533 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 47.21528 </td>
   <td style="text-align:center;"> 51.54378 </td>
   <td style="text-align:center;"> 111.51 </td>
   <td style="text-align:center;"> 34.98648 </td>
   <td style="text-align:center;"> 7.817341 </td>
   <td style="text-align:center;"> 46.11611 </td>
   <td style="text-align:center;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> 2010-01-07 </td>
   <td style="text-align:center;"> 41.49401 </td>
   <td style="text-align:center;"> 92.85078 </td>
   <td style="text-align:center;"> 92.94606 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 47.41198 </td>
   <td style="text-align:center;"> 51.74965 </td>
   <td style="text-align:center;"> 110.82 </td>
   <td style="text-align:center;"> 34.78360 </td>
   <td style="text-align:center;"> 7.984223 </td>
   <td style="text-align:center;"> 45.89180 </td>
   <td style="text-align:center;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> 2010-01-08 </td>
   <td style="text-align:center;"> 41.83553 </td>
   <td style="text-align:center;"> 93.16687 </td>
   <td style="text-align:center;"> 93.25535 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 47.56769 </td>
   <td style="text-align:center;"> 51.92256 </td>
   <td style="text-align:center;"> 111.37 </td>
   <td style="text-align:center;"> 35.05952 </td>
   <td style="text-align:center;"> 7.937286 </td>
   <td style="text-align:center;"> 46.58344 </td>
   <td style="text-align:center;"> NA </td>
  </tr>
  <tr>
   <td style="text-align:left;"> 2010-01-11 </td>
   <td style="text-align:center;"> 41.66477 </td>
   <td style="text-align:center;"> 93.29655 </td>
   <td style="text-align:center;"> 93.38558 </td>
   <td style="text-align:center;"> NA </td>
   <td style="text-align:center;"> 47.63326 </td>
   <td style="text-align:center;"> 51.99666 </td>
   <td style="text-align:center;"> 112.85 </td>
   <td style="text-align:center;"> 34.98648 </td>
   <td style="text-align:center;"> 7.942502 </td>
   <td style="text-align:center;"> 46.89188 </td>
   <td style="text-align:center;"> NA </td>
  </tr>
</tbody>
</table>


The prices of these ETF's can be visualized with dygraph package, it allows a user to set a date window which lets you expand and narrow the windows to focus on detail visualization within the range of interest.


```r
dateWindow <- c("2015-01-01", "2020-02-20")

p1= dygraph(prices, main = "Value", group = "stock",
        xlab = "Time",ylab = "Adjusted Prices") %>%
  dyRebase(value = 100) %>%
  dyRangeSelector(dateWindow = dateWindow)


htmlwidgets::saveWidget(as_widget(p1), "p1.html")

p1
```



<iframe src="/img/ETF/p1.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>
