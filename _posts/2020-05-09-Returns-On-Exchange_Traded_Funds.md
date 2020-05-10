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



