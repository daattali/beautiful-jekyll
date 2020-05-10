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





Convert daily prices to monthly prices using a call to to.monthly(prices, indexAt = “last”, OHLC = FALSE) from quantmod. The argument index = “last” tells the function whether we want to index to the first day of the month or the last day.



```r
prices_monthly <- to.monthly(prices, indexAt = "last", OHLC = FALSE)%>%tk_tbl()%>% rename(date=index) 


start_date <-first(index(prices_monthly))
end_date <- last(index(prices_monthly)) 

#prices_monthly  %>% head()   %>%  gt() %>%
#  tab_header(
#    title = " Monthly Prices for ETF's",
#    subtitle = glue::glue("{start_date} to {end_date}")
#  )




prices_monthly  %>% head()%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> date </th>
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
   <td style="text-align:center;"> 2014-09-30 </td>
   <td style="text-align:center;"> 93.71915 </td>
   <td style="text-align:center;"> 176.6444 </td>
   <td style="text-align:center;"> 176.5203 </td>
   <td style="text-align:center;"> 161.6403 </td>
   <td style="text-align:center;"> 91.02445 </td>
   <td style="text-align:center;"> 98.94495 </td>
   <td style="text-align:center;"> 116.21 </td>
   <td style="text-align:center;"> 36.63364 </td>
   <td style="text-align:center;"> 12.99660 </td>
   <td style="text-align:center;"> 20.55621 </td>
   <td style="text-align:center;"> 16.92123 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2014-10-31 </td>
   <td style="text-align:center;"> 96.19518 </td>
   <td style="text-align:center;"> 180.8587 </td>
   <td style="text-align:center;"> 180.6775 </td>
   <td style="text-align:center;"> 165.5249 </td>
   <td style="text-align:center;"> 93.52393 </td>
   <td style="text-align:center;"> 101.31341 </td>
   <td style="text-align:center;"> 112.66 </td>
   <td style="text-align:center;"> 37.15370 </td>
   <td style="text-align:center;"> 13.37242 </td>
   <td style="text-align:center;"> 16.56238 </td>
   <td style="text-align:center;"> 17.20904 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2014-11-28 </td>
   <td style="text-align:center;"> 100.56856 </td>
   <td style="text-align:center;"> 185.8393 </td>
   <td style="text-align:center;"> 185.6411 </td>
   <td style="text-align:center;"> 170.0898 </td>
   <td style="text-align:center;"> 95.84360 </td>
   <td style="text-align:center;"> 104.06014 </td>
   <td style="text-align:center;"> 112.11 </td>
   <td style="text-align:center;"> 36.58075 </td>
   <td style="text-align:center;"> 13.68653 </td>
   <td style="text-align:center;"> 17.66910 </td>
   <td style="text-align:center;"> 17.52985 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2014-12-31 </td>
   <td style="text-align:center;"> 98.31519 </td>
   <td style="text-align:center;"> 185.2874 </td>
   <td style="text-align:center;"> 185.1702 </td>
   <td style="text-align:center;"> 169.5703 </td>
   <td style="text-align:center;"> 95.80689 </td>
   <td style="text-align:center;"> 103.75922 </td>
   <td style="text-align:center;"> 113.58 </td>
   <td style="text-align:center;"> 35.13086 </td>
   <td style="text-align:center;"> 13.94251 </td>
   <td style="text-align:center;"> 17.80461 </td>
   <td style="text-align:center;"> 17.37833 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2015-01-30 </td>
   <td style="text-align:center;"> 96.26794 </td>
   <td style="text-align:center;"> 179.9134 </td>
   <td style="text-align:center;"> 179.6837 </td>
   <td style="text-align:center;"> 164.7011 </td>
   <td style="text-align:center;"> 93.18576 </td>
   <td style="text-align:center;"> 100.97132 </td>
   <td style="text-align:center;"> 123.45 </td>
   <td style="text-align:center;"> 34.88944 </td>
   <td style="text-align:center;"> 12.97279 </td>
   <td style="text-align:center;"> 21.59221 </td>
   <td style="text-align:center;"> 17.32754 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2015-02-27 </td>
   <td style="text-align:center;"> 103.21903 </td>
   <td style="text-align:center;"> 190.0703 </td>
   <td style="text-align:center;"> 189.7828 </td>
   <td style="text-align:center;"> 173.8906 </td>
   <td style="text-align:center;"> 98.53648 </td>
   <td style="text-align:center;"> 106.68292 </td>
   <td style="text-align:center;"> 116.16 </td>
   <td style="text-align:center;"> 36.42736 </td>
   <td style="text-align:center;"> 13.72827 </td>
   <td style="text-align:center;"> 20.61383 </td>
   <td style="text-align:center;"> 18.75810 </td>
  </tr>
</tbody>
</table>



We now have an xts object, and we have moved from daily prices to monthly prices.

Return.calculate(prices_monthly, method = “log”) to convert to returns and save as an object called assed_returns_xts. Note this will give us log returns by the method = “log” argument. We could have used method = “discrete” to get simple returns. The daily percentage  return on a stock is the difference between the previous day's price and the current day's price relative to the previous day's price. The monthly perentage return follows as the difference between the previous month and the current month's price divided by the previous months price.

![ ]( /img/ETF/eqn.PNG)


```r
#asset_returns_xts <- na.omit(Return.calculate(prices_monthly, method = "discreet"))
prices_monthly <- to.monthly(prices, indexAt = "last", OHLC = FALSE)
asset_returns_quantmod <- na.omit(CalculateReturns(prices_monthly, method = "log"))
head(asset_returns_quantmod)%>%tk_tbl()%>%  
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> index </th>
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
   <td style="text-align:center;"> 2014-10-31 </td>
   <td style="text-align:center;"> 0.0260767 </td>
   <td style="text-align:center;"> 0.0235776 </td>
   <td style="text-align:center;"> 0.0232774 </td>
   <td style="text-align:center;"> 0.0237483 </td>
   <td style="text-align:center;"> 0.0270893 </td>
   <td style="text-align:center;"> 0.0236552 </td>
   <td style="text-align:center;"> -0.0310244 </td>
   <td style="text-align:center;"> 0.0140965 </td>
   <td style="text-align:center;"> 0.0285065 </td>
   <td style="text-align:center;"> -0.2160296 </td>
   <td style="text-align:center;"> 0.0168654 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2014-11-28 </td>
   <td style="text-align:center;"> 0.0444605 </td>
   <td style="text-align:center;"> 0.0271660 </td>
   <td style="text-align:center;"> 0.0271016 </td>
   <td style="text-align:center;"> 0.0272043 </td>
   <td style="text-align:center;"> 0.0245003 </td>
   <td style="text-align:center;"> 0.0267502 </td>
   <td style="text-align:center;"> -0.0048939 </td>
   <td style="text-align:center;"> -0.0155414 </td>
   <td style="text-align:center;"> 0.0232182 </td>
   <td style="text-align:center;"> 0.0646838 </td>
   <td style="text-align:center;"> 0.0184708 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2014-12-31 </td>
   <td style="text-align:center;"> -0.0226612 </td>
   <td style="text-align:center;"> -0.0029742 </td>
   <td style="text-align:center;"> -0.0025398 </td>
   <td style="text-align:center;"> -0.0030584 </td>
   <td style="text-align:center;"> -0.0003830 </td>
   <td style="text-align:center;"> -0.0028959 </td>
   <td style="text-align:center;"> 0.0130269 </td>
   <td style="text-align:center;"> -0.0404422 </td>
   <td style="text-align:center;"> 0.0185299 </td>
   <td style="text-align:center;"> 0.0076400 </td>
   <td style="text-align:center;"> -0.0086811 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2015-01-30 </td>
   <td style="text-align:center;"> -0.0210432 </td>
   <td style="text-align:center;"> -0.0294324 </td>
   <td style="text-align:center;"> -0.0300770 </td>
   <td style="text-align:center;"> -0.0291356 </td>
   <td style="text-align:center;"> -0.0277397 </td>
   <td style="text-align:center;"> -0.0272365 </td>
   <td style="text-align:center;"> 0.0833287 </td>
   <td style="text-align:center;"> -0.0068957 </td>
   <td style="text-align:center;"> -0.0720882 </td>
   <td style="text-align:center;"> 0.1928753 </td>
   <td style="text-align:center;"> -0.0029269 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2015-02-27 </td>
   <td style="text-align:center;"> 0.0697179 </td>
   <td style="text-align:center;"> 0.0549183 </td>
   <td style="text-align:center;"> 0.0546819 </td>
   <td style="text-align:center;"> 0.0542943 </td>
   <td style="text-align:center;"> 0.0558319 </td>
   <td style="text-align:center;"> 0.0550246 </td>
   <td style="text-align:center;"> -0.0608676 </td>
   <td style="text-align:center;"> 0.0431361 </td>
   <td style="text-align:center;"> 0.0566029 </td>
   <td style="text-align:center;"> -0.0463706 </td>
   <td style="text-align:center;"> 0.0793286 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> 2015-03-31 </td>
   <td style="text-align:center;"> -0.0238725 </td>
   <td style="text-align:center;"> -0.0160997 </td>
   <td style="text-align:center;"> -0.0158302 </td>
   <td style="text-align:center;"> -0.0158327 </td>
   <td style="text-align:center;"> -0.0116970 </td>
   <td style="text-align:center;"> -0.0131021 </td>
   <td style="text-align:center;"> -0.0217570 </td>
   <td style="text-align:center;"> -0.0150863 </td>
   <td style="text-align:center;"> -0.0061797 </td>
   <td style="text-align:center;"> -0.1541505 </td>
   <td style="text-align:center;"> -0.0067920 </td>
  </tr>
</tbody>
</table>






```r
pacman::p_load(kable,kableExtra)

ETF_returns <- prices %>%
  tk_tbl(preserve_index = TRUE, rename_index = "date") %>%
  
  pivot_longer(-date , names_to = "symbol",values_to = "Adjusted_Prices")%>%
  
  group_by(symbol) %>%
  tq_transmute(mutate_fun = periodReturn, period = "monthly", type = "log") %>%
  
  arrange(desc(monthly.returns))
 


ETF_returns%>%head()%>%
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> symbol </th>
   <th style="text-align:center;"> date </th>
   <th style="text-align:center;"> monthly.returns </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:center;"> GDX </td>
   <td style="text-align:center;"> 2020-04-30 </td>
   <td style="text-align:center;"> 0.3365961 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> GDX </td>
   <td style="text-align:center;"> 2016-02-29 </td>
   <td style="text-align:center;"> 0.3102956 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> GDX </td>
   <td style="text-align:center;"> 2016-04-29 </td>
   <td style="text-align:center;"> 0.2573056 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> XLF </td>
   <td style="text-align:center;"> 2016-09-30 </td>
   <td style="text-align:center;"> 0.2350068 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> ARKW </td>
   <td style="text-align:center;"> 2020-04-30 </td>
   <td style="text-align:center;"> 0.2197622 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> GDX </td>
   <td style="text-align:center;"> 2016-06-30 </td>
   <td style="text-align:center;"> 0.2047288 </td>
  </tr>
</tbody>
</table>



An interactive  visualiation for the monthly returns for the ETF's selected is displayed below.


```r
library(crosstalk)

ETF_returns <-  ETF_returns %>%  ungroup(symbol)


d <- 
  SharedData$new(ETF_returns, ~symbol)
p2 <- ggplot(d, aes(date,monthly.returns,color=symbol)) +
  geom_line(aes(group = symbol))+
  
  
#scale_y_continuous(trans = log10_trans(), labels =  scales::comma)+
  
  #scale_fill_viridis_d()+
  scale_color_viridis_d(option="D") +
  
  # scale_shape_manual(values = 1:6 )  +
  
 #   theme_economist() +
  
  scale_x_date(labels = date_format("%d-%m-%Y"),date_breaks = "1 year") +
  theme(axis.text.x=element_text(angle=45, hjust=1)) +
   labs(title = "Monthly Returns Performance of Exhcange Traded Funds",
       subtitle = " 2010 - 2020",
       caption = "www.restsanalytics.com", 
       x = "Time", y = "Returns")


(gg <- ggplotly(p2, tooltip = "symbol"))
```


```r
gg=highlight(gg, "plotly_hover")
ggsave("p2.png")

#htmlwidgets::saveWidget(as_widget(gg), "p2.html")
htmlwidgets::saveWidget(gg, "p2.html", selfcontained = F, libdir = "lib")
#saveWidget(gg, file="p2.html")
gg
```


<iframe src="/img/ETF/p2.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>




```r
ETF_returns %>% mutate(Year= format(date,"%Y")) %>%  group_by(symbol,Year) %>%  
                summarize(meanreturn =mean(monthly.returns,na.rm = TRUE))%>%
  
  ggplot(aes(x=Year,y=meanreturn,fill=symbol))+
  geom_col()+
 #scale_color_viridis(discrete=TRUE,option = "A")
scale_fill_viridis(discrete=TRUE,option = "D")+
    theme(
    legend.position="top",
    legend.direction="horizontal",
    legend.title = element_blank(),
    text=element_text(size=8,  family="Comic Sans MS"),
    axis.text.x=element_text(angle=45,hjust=1,size = 9),
    axis.text.y=element_text(size = 8),
    legend.text = element_text(size=8)
)+
   labs(y="Mean Yearly Return",x="Year",title="")
```
![ ]( /img/ETF/unnamed-chunk-9-1.png)


```r
 # scale_x_date(breaks = date_breaks("1 year"),labels=date_format("%b %Y") )
```



The analysis above in which the data was downloaded with the quantmod package, can be replicated with the tidyquant package. The tidyquant package builds a wrapper around the quantmod and converts the data from xts format to tibble dataframes.

```r
end<-Sys.Date()
start<-as.Date("2010-01-10")


Prices  <- tq_get(tickers , get = "stock.prices", from = start,to=end)
#Prices%>%head() %>% DT::datatable()

Prices%>%head() %>%tk_tbl()%>%  
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> symbol </th>
   <th style="text-align:center;"> date </th>
   <th style="text-align:center;"> open </th>
   <th style="text-align:center;"> high </th>
   <th style="text-align:center;"> low </th>
   <th style="text-align:center;"> close </th>
   <th style="text-align:center;"> volume </th>
   <th style="text-align:center;"> adjusted </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-01-11 </td>
   <td style="text-align:center;"> 46.61 </td>
   <td style="text-align:center;"> 46.64 </td>
   <td style="text-align:center;"> 46.12 </td>
   <td style="text-align:center;"> 46.36 </td>
   <td style="text-align:center;"> 104673400 </td>
   <td style="text-align:center;"> 41.66477 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-01-12 </td>
   <td style="text-align:center;"> 46.08 </td>
   <td style="text-align:center;"> 46.14 </td>
   <td style="text-align:center;"> 45.53 </td>
   <td style="text-align:center;"> 45.78 </td>
   <td style="text-align:center;"> 90673900 </td>
   <td style="text-align:center;"> 41.14353 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-01-13 </td>
   <td style="text-align:center;"> 45.92 </td>
   <td style="text-align:center;"> 46.49 </td>
   <td style="text-align:center;"> 45.61 </td>
   <td style="text-align:center;"> 46.35 </td>
   <td style="text-align:center;"> 100661000 </td>
   <td style="text-align:center;"> 41.65579 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-01-14 </td>
   <td style="text-align:center;"> 46.26 </td>
   <td style="text-align:center;"> 46.52 </td>
   <td style="text-align:center;"> 46.22 </td>
   <td style="text-align:center;"> 46.39 </td>
   <td style="text-align:center;"> 75209000 </td>
   <td style="text-align:center;"> 41.69173 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-01-15 </td>
   <td style="text-align:center;"> 46.47 </td>
   <td style="text-align:center;"> 46.55 </td>
   <td style="text-align:center;"> 45.65 </td>
   <td style="text-align:center;"> 45.85 </td>
   <td style="text-align:center;"> 126849300 </td>
   <td style="text-align:center;"> 41.20641 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-01-19 </td>
   <td style="text-align:center;"> 45.96 </td>
   <td style="text-align:center;"> 46.64 </td>
   <td style="text-align:center;"> 45.95 </td>
   <td style="text-align:center;"> 46.59 </td>
   <td style="text-align:center;"> 84388200 </td>
   <td style="text-align:center;"> 41.87149 </td>
  </tr>
</tbody>
</table>





```r
library(crosstalk)
d <- SharedData$new(Prices, ~symbol)
p3 <- ggplot(d, aes(date, adjusted,color=symbol)) +
  geom_line(aes(group = symbol))+
  
  
#scale_y_continuous(trans = log10_trans(), labels =  scales::comma)+
  
  #scale_fill_viridis_d()+
  scale_color_viridis_d(option="D") +
  
  # scale_shape_manual(values = 1:6 )  +
  
 #   theme_economist() +
  
  scale_x_date(labels = date_format("%d-%m-%Y"),date_breaks = "1 year") +
  theme(axis.text.x=element_text(angle=45, hjust=1)) +
   labs(title = "Performance of Exhcange Traded Funds",
       subtitle = " 2010 - 2020",
       caption = "www.restsanalytics.com", 
       x = "Time", y = "Adjusted Prices")


(gg <- ggplotly(p3, tooltip = "symbol"))
```

```r
gg=highlight(gg, "plotly_hover")



ggsave("p3.png")


htmlwidgets::saveWidget(as_widget(gg), "p3.html")
#htmlwidgets::saveWidget(gg, "p3.html", selfcontained = F, libdir = "lib")
gg
```

<iframe src="/img/ETF/p3.html"
    sandbox="allow-same-origin allow-scripts"
    width="100%"
    height="500"
    scrolling="no"
    seamless="seamless"
    frameborder="0">
</iframe>




#### Returns


```r
monthlyreturns <-Prices%>% select(symbol,date,adjusted)%>%
  group_by(symbol)%>%
  tq_transmute( 
                 mutate_fun = periodReturn, 
                 period     = "monthly", 
                 type       = "arithmetic")%>%head()



#monthlyreturns%>%head() %>% gt()
  
monthlyreturns%>%head()  %>%tk_tbl()%>%  
  kable(escape = F, align = "c") %>%
  kable_styling(c("striped", "condensed"), full_width = F)
```

<table class="table table-striped table-condensed" style="width: auto !important; margin-left: auto; margin-right: auto;">
 <thead>
  <tr>
   <th style="text-align:center;"> symbol </th>
   <th style="text-align:center;"> date </th>
   <th style="text-align:center;"> monthly.returns </th>
  </tr>
 </thead>
<tbody>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-01-29 </td>
   <td style="text-align:center;"> -0.0770059 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-02-26 </td>
   <td style="text-align:center;"> 0.0460387 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-03-31 </td>
   <td style="text-align:center;"> 0.0771089 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-04-30 </td>
   <td style="text-align:center;"> 0.0224255 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-05-28 </td>
   <td style="text-align:center;"> -0.0739236 </td>
  </tr>
  <tr>
   <td style="text-align:center;"> QQQ </td>
   <td style="text-align:center;"> 2010-06-30 </td>
   <td style="text-align:center;"> -0.0597572 </td>
  </tr>
</tbody>
</table>









```r
ETF_returns %>%
    ggplot(aes(x = date, y = monthly.returns, group = symbol)) +
    geom_area(aes(fill = symbol), position = "stack") +
    labs(title = "Quantity Sold: Month Plot", x = "", y = "Sales",
         subtitle = "March through July tend to be most active") +
    theme(
    legend.position="top",
    legend.direction="horizontal",
    legend.title = element_blank(),
    text=element_text(size=8,  family="Comic Sans MS"),
    axis.text.x=element_text(angle=45,hjust=1,size = 9),
    axis.text.y=element_text(size = 8),
    legend.text = element_text(size=8)
)+
    scale_x_date(breaks = date_breaks("12 month"),labels=date_format("%b %Y") ) +
   # theme_tq()+
  #scale_color_viridis()
 #scale_color_continuous_tableau()
   scale_fill_viridis(discrete = T,option="B")
```

![ ]( /img/ETF/unnamed-chunk-13-1.png)



```r
   #scale_color_viridis_d() 
```










