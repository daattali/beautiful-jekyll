---
title: Exhange Traded Funds Perforance
subtitle: 
output:
  html_document:
    keep_md: true
    toc_float: true
    #theme: flatly
    toc: true # table of content true
    toc_depth: 3  # upto three depths of headings (specified by #, ## and ###)
    number_sections: true  ## if you want number sections at each table header
    theme: united  # many options for theme, this one is my favorite.
    code_download: true
author: Nana Boateng
Time: '2020-05-09 20:37:36'
date: "May 09, 2020"
params:
  series: '2'
tags: ETF, Quantitative Finance, Asset Return,  
  
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
pacman::p_load(dygraphs,DT,tidyverse,janitor,ggthemes,scales,ggpubr,viridis)

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


DT::datatable(tbls_ls, class = 'cell-border stripe')
```

<!--html_preserve--><div id="htmlwidget-514989a1d4a3560f94dd" style="width:100%;height:auto;" class="datatables html-widget"></div>
<script type="application/json" data-for="htmlwidget-514989a1d4a3560f94dd">{"x":{"filter":"none","data":[["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150","151","152","153","154","155","156","157","158","159","160","161","162","163","164"],["Brand","iShares","Vanguard","SPDR","Invesco","Schwab","First Trust","VanEck","WisdomTree","ProShares","JPMorgan","PIMCO","Goldman Sachs","Fidelity","Xtrackers","FlexShares","Direxion","Global X","Alerian","Pacer","VictoryShares","LibertyShares","John Hancock","Hartford","ARK","UBS","KraneShares","ETF Managers Group","Principal","IndexIQ","Aberdeen","VelocityShares","ETRACS","ALPS","Invesco DB","Innovator","Credit Suisse","US Commodity Funds","iPath","Janus Henderson","Barclays","Vident","Legg Mason","ROBO Global","Nuveen","PGIM","REX Microsectors","Amplify","DeltaShares","Davis","O’Shares","GraniteShares","AdvisorShares","Columbia","Virtus","Cambria","Main Funds","RiverFront","American Century","Avantis","Tortoise","WBI Shares","Inspire","FormulaFolios","EMQQ","Alpha Architect","Aptus","Nationwide","Aware","InfraCap","Motley Fool","TMW Funds","Timothy","Defiance","Sprott","C-Tracks","ClearShares","ELEMENTS","AGFiQ","Overlay Shares","Perth Mint","Reality Shares","Teucrium","Highland","RPAR","HCM","Knowledge Leaders Capital","TrimTabs","Deutsche X-trackers","ArrowShares","Eve Capital","Pacific Global ETF","Core Alternative","BlueStar","Anfield","Strategy Shares","US Global","SoFi","Exponential ETFs","Quadratic","ERShares","Etho Capital","LeaderShares","Blackrock","Distillate","Opus Capital Management","Premise Capital","Cboe Vest","Metaurus","Saba","Fieldstone","Vesper","Loncar","AAM","Gadsden","MainStay","Natixis","NETL","Merlyn.AI","Renaissance","Hull","iM","Portfolio+","Day Hagan","Reaves","USCF Advisers","SP Funds","Innovation Shares","BMO","Syntax","Wahed","EntrepreneurShares","AlphaClone","Salt Financial","Belpointe","EventShares","AlphaMark","Validea","Market Vectors","Sage","Procure","Acquirers Fund","Point Bridge Capital","Change Finance","Beyond","Impact Shares","Roundhill","Hoya","Franklin","UP Fintech","Volshares","Counterpoint","QRAFT","Absolute","Affinity","Little Harbor Advisors","EquBot","Source Asset Management","Leuthold","Breakwave","Global Beta","URNM","RYZZ","Ideanomics"],["AUM ($, mm)","1,761,739.92","1,195,773.48","737,904.99","232,732.50","168,568.37","89,959.57","42,713.07","40,277.21","36,429.66","33,899.71","23,179.37","18,410.82","17,874.90","16,873.75","16,099.56","14,152.59","12,496.35","7,252.12","6,051.28","5,397.41","4,792.37","4,775.42","4,377.94","3,557.10","3,544.79","3,516.57","3,455.71","3,437.87","3,422.51","3,040.58","3,015.50","2,817.18","2,739.54","2,551.17","2,514.32","2,454.21","2,295.60","2,114.63","1,779.57","1,767.27","1,704.39","1,555.91","1,291.87","1,152.36","1,104.31","866.80","843.33","810.29","797.12","793.45","772.30","736.61","722.74","718.58","650.96","581.20","580.27","548.86","494.41","478.22","477.74","477.59","460.48","450.31","428.52","425.64","399.83","380.09","323.61","318.64","304.51","295.72","269.69","241.05","239.87","216.48","214.95","198.30","191.14","189.78","180.38","159.66","158.54","153.18","150.00","147.94","142.14","135.20","129.58","125.32","114.89","110.91","104.00","103.24","102.99","102.82","101.70","95.74","89.49","87.09","78.75","77.87","72.75","70.38","56.47","53.79","53.02","52.42","52.31","51.80","51.64","51.37","49.95","49.31","48.65","48.42","46.93","46.78","45.28","41.05","40.61","39.07","37.97","34.61","33.67","29.91","29.52","29.07","28.50","28.04","26.72","25.76","25.41","25.07","22.67","22.03","21.22","18.37","17.93","17.91","16.47","16.40","15.64","15.11","12.96","12.63","12.05","10.17","9.38","8.56","8.13","7.00","6.23","6.01","5.71","5.37","4.18","3.81","3.27","2.45","2.42","2.14","1.75"],["Net Flows ($, mm)","1,120.23","1,154.64","-710.71","250.17","165.32","69.20","-305.82","21.57","67.40","17.86","-24.21","14.96","18.51","-21.89","-6.42","17.39","14.62","0.00","15.80","-6.88","0.00","1.40","0.00","2.61","0.00","0.48","23.87","0.00","-2.78","12.11","93.67","0.00","-9.06","-20.34","-17.04","1.76","-52.85","-4.71","3.93","1.66","-0.00","-0.02","0.01","3.32","2.50","0.00","2.85","0.00","0.00","0.00","0.00","0.00","8.41","2.57","0.02","0.00","0.00","0.00","0.00","-10.37","-2.05","0.00","0.00","1.82","1.43","4.70","0.00","0.00","1.89","0.00","0.00","0.00","0.00","0.00","0.00","0.00","-0.60","1.20","5.33","0.00","0.00","0.00","-33.09","5.16","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","2.31","0.00","0.67","0.00","0.00","0.00","0.63","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","-0.00","0.00","0.00","0.00","2.60","0.00","0.00","0.00","0.00","0.00","0.00","0.00","-0.00","0.00","0.00","0.00","0.00","0.00","0.00","-0.00","0.00","0.00","0.00","0.00","0.00","0.00","-0.61","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00","0.00"],["% of AUM","0.06%","0.10%","-0.10%","0.11%","0.10%","0.08%","-0.72%","0.05%","0.19%","0.05%","-0.10%","0.08%","0.10%","-0.13%","-0.04%","0.12%","0.12%","0.00%","0.26%","-0.13%","0.00%","0.03%","0.00%","0.07%","0.00%","0.01%","0.69%","0.00%","-0.08%","0.40%","3.11%","0.00%","-0.33%","-0.80%","-0.68%","0.07%","-2.30%","-0.22%","0.22%","0.09%","-0.00%","-0.00%","0.00%","0.29%","0.23%","0.00%","0.34%","0.00%","0.00%","0.00%","0.00%","0.00%","1.16%","0.36%","0.00%","0.00%","0.00%","0.00%","0.00%","-2.17%","-0.43%","0.00%","0.00%","0.40%","0.33%","1.10%","0.00%","0.00%","0.58%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","-0.28%","0.61%","2.79%","0.00%","0.00%","0.00%","-20.87%","3.37%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","2.22%","0.00%","0.65%","0.00%","0.00%","0.00%","0.70%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","-0.00%","0.00%","0.00%","0.00%","5.06%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","-0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","-0.01%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","-2.44%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.00%","0.01%","0.00%","0.00%"]],"container":"<table class=\"cell-border stripe\">\n  <thead>\n    <tr>\n      <th> <\/th>\n      <th>brand<\/th>\n      <th>aum_mm<\/th>\n      <th>net_flows_mm<\/th>\n      <th>percent_of_aum<\/th>\n    <\/tr>\n  <\/thead>\n<\/table>","options":{"order":[],"autoWidth":false,"orderClasses":false,"columnDefs":[{"orderable":false,"targets":0}]}},"evals":[],"jsHooks":[]}</script><!--/html_preserve-->









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



DT::datatable(data.frame(head(prices)))
```

<!--html_preserve--><div id="htmlwidget-6df03b15966a564d012a" style="width:100%;height:auto;" class="datatables html-widget"></div>
<script type="application/json" data-for="htmlwidget-6df03b15966a564d012a">{"x":{"filter":"none","data":[["2010-01-04","2010-01-05","2010-01-06","2010-01-07","2010-01-08","2010-01-11"],[41.718689,41.718689,41.467049,41.494007,41.835529,41.664768],[92.105225,92.37265,92.44558,92.850777,93.16687,93.296555],[92.246048,92.490204,92.555328,92.94606,93.255348,93.385582],[null,null,null,null,null,null],[46.969406,47.149708,47.215279,47.411976,47.567688,47.633263],[51.313255,51.477928,51.543785,51.749645,51.922558,51.996662],[109.800003,109.699997,111.510002,110.82,111.370003,112.849998],[34.661869,34.913445,34.986481,34.783596,35.059521,34.986481],[7.66089,7.801696,7.817341,7.984223,7.937286,7.942502],[44.592617,45.02256,46.116112,45.891796,46.583435,46.89188],[null,null,null,null,null,null]],"container":"<table class=\"display\">\n  <thead>\n    <tr>\n      <th> <\/th>\n      <th>QQQ<\/th>\n      <th>IVV<\/th>\n      <th>SPY<\/th>\n      <th>VOO<\/th>\n      <th>VTI<\/th>\n      <th>IWB<\/th>\n      <th>GLD<\/th>\n      <th>EEM<\/th>\n      <th>XLF<\/th>\n      <th>GDX<\/th>\n      <th>ARKW<\/th>\n    <\/tr>\n  <\/thead>\n<\/table>","options":{"columnDefs":[{"className":"dt-right","targets":[1,2,3,4,5,6,7,8,9,10,11]},{"orderable":false,"targets":0}],"order":[],"autoWidth":false,"orderClasses":false}},"evals":[],"jsHooks":[]}</script><!--/html_preserve-->


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

{% include /ETF/p1.html %}



Convert daily prices to monthly prices using a call to to.monthly(prices, indexAt = “last”, OHLC = FALSE) from quantmod. The argument index = “last” tells the function whether we want to index to the first day of the month or the last day.



```r
prices_monthly <- to.monthly(prices, indexAt = "last", OHLC = FALSE)%>%tk_tbl()%>% rename(date=index) 


start_date <-first(index(prices_monthly))
end_date <- last(index(prices_monthly)) 

prices_monthly  %>% head()   %>%  gt() %>%
  tab_header(
    title = " Monthly Prices for ETF's",
    subtitle = glue::glue("{start_date} to {end_date}")
  )
```

<!--html_preserve--><style>html {
  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Helvetica Neue', 'Fira Sans', 'Droid Sans', Arial, sans-serif;
}

#kjsunapnap .gt_table {
  display: table;
  border-collapse: collapse;
  margin-left: auto;
  margin-right: auto;
  color: #333333;
  font-size: 16px;
  background-color: #FFFFFF;
  width: auto;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #A8A8A8;
  border-right-style: none;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #A8A8A8;
  border-left-style: none;
  border-left-width: 2px;
  border-left-color: #D3D3D3;
}

#kjsunapnap .gt_heading {
  background-color: #FFFFFF;
  text-align: center;
  border-bottom-color: #FFFFFF;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
}

#kjsunapnap .gt_title {
  color: #333333;
  font-size: 125%;
  font-weight: initial;
  padding-top: 4px;
  padding-bottom: 4px;
  border-bottom-color: #FFFFFF;
  border-bottom-width: 0;
}

#kjsunapnap .gt_subtitle {
  color: #333333;
  font-size: 85%;
  font-weight: initial;
  padding-top: 0;
  padding-bottom: 4px;
  border-top-color: #FFFFFF;
  border-top-width: 0;
}

#kjsunapnap .gt_bottom_border {
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
}

#kjsunapnap .gt_col_headings {
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
}

#kjsunapnap .gt_col_heading {
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: normal;
  text-transform: inherit;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
  vertical-align: bottom;
  padding-top: 5px;
  padding-bottom: 6px;
  padding-left: 5px;
  padding-right: 5px;
  overflow-x: hidden;
}

#kjsunapnap .gt_column_spanner_outer {
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: normal;
  text-transform: inherit;
  padding-top: 0;
  padding-bottom: 0;
  padding-left: 4px;
  padding-right: 4px;
}

#kjsunapnap .gt_column_spanner_outer:first-child {
  padding-left: 0;
}

#kjsunapnap .gt_column_spanner_outer:last-child {
  padding-right: 0;
}

#kjsunapnap .gt_column_spanner {
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  vertical-align: bottom;
  padding-top: 5px;
  padding-bottom: 6px;
  overflow-x: hidden;
  display: inline-block;
  width: 100%;
}

#kjsunapnap .gt_group_heading {
  padding: 8px;
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: initial;
  text-transform: inherit;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
  vertical-align: middle;
}

#kjsunapnap .gt_empty_group_heading {
  padding: 0.5px;
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: initial;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  vertical-align: middle;
}

#kjsunapnap .gt_striped {
  background-color: rgba(128, 128, 128, 0.05);
}

#kjsunapnap .gt_from_md > :first-child {
  margin-top: 0;
}

#kjsunapnap .gt_from_md > :last-child {
  margin-bottom: 0;
}

#kjsunapnap .gt_row {
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
  margin: 10px;
  border-top-style: solid;
  border-top-width: 1px;
  border-top-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
  vertical-align: middle;
  overflow-x: hidden;
}

#kjsunapnap .gt_stub {
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: initial;
  text-transform: inherit;
  border-right-style: solid;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
  padding-left: 12px;
}

#kjsunapnap .gt_summary_row {
  color: #333333;
  background-color: #FFFFFF;
  text-transform: inherit;
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
}

#kjsunapnap .gt_first_summary_row {
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
}

#kjsunapnap .gt_grand_summary_row {
  color: #333333;
  background-color: #FFFFFF;
  text-transform: inherit;
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
}

#kjsunapnap .gt_first_grand_summary_row {
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
  border-top-style: double;
  border-top-width: 6px;
  border-top-color: #D3D3D3;
}

#kjsunapnap .gt_table_body {
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
}

#kjsunapnap .gt_footnotes {
  color: #333333;
  background-color: #FFFFFF;
  border-bottom-style: none;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 2px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
}

#kjsunapnap .gt_footnote {
  margin: 0px;
  font-size: 90%;
  padding: 4px;
}

#kjsunapnap .gt_sourcenotes {
  color: #333333;
  background-color: #FFFFFF;
  border-bottom-style: none;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 2px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
}

#kjsunapnap .gt_sourcenote {
  font-size: 90%;
  padding: 4px;
}

#kjsunapnap .gt_left {
  text-align: left;
}

#kjsunapnap .gt_center {
  text-align: center;
}

#kjsunapnap .gt_right {
  text-align: right;
  font-variant-numeric: tabular-nums;
}

#kjsunapnap .gt_font_normal {
  font-weight: normal;
}

#kjsunapnap .gt_font_bold {
  font-weight: bold;
}

#kjsunapnap .gt_font_italic {
  font-style: italic;
}

#kjsunapnap .gt_super {
  font-size: 65%;
}

#kjsunapnap .gt_footnote_marks {
  font-style: italic;
  font-size: 65%;
}
</style>
<div id="kjsunapnap" style="overflow-x:auto;overflow-y:auto;width:auto;height:auto;"><table class="gt_table">
  <thead class="gt_header">
    <tr>
      <th colspan="12" class="gt_heading gt_title gt_font_normal" style> Monthly Prices for ETF's</th>
    </tr>
    <tr>
      <th colspan="12" class="gt_heading gt_subtitle gt_font_normal gt_bottom_border" style>1 to 69</th>
    </tr>
  </thead>
  <thead class="gt_col_headings">
    <tr>
      <th class="gt_col_heading gt_columns_bottom_border gt_left" rowspan="1" colspan="1">date</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">QQQ</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">IVV</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">SPY</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">VOO</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">VTI</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">IWB</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">GLD</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">EEM</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">XLF</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">GDX</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">ARKW</th>
    </tr>
  </thead>
  <tbody class="gt_table_body">
    <tr>
      <td class="gt_row gt_left">2014-09-30</td>
      <td class="gt_row gt_right">93.71915</td>
      <td class="gt_row gt_right">176.6444</td>
      <td class="gt_row gt_right">176.5203</td>
      <td class="gt_row gt_right">161.6403</td>
      <td class="gt_row gt_right">91.02445</td>
      <td class="gt_row gt_right">98.94495</td>
      <td class="gt_row gt_right">116.21</td>
      <td class="gt_row gt_right">36.63364</td>
      <td class="gt_row gt_right">12.99660</td>
      <td class="gt_row gt_right">20.55621</td>
      <td class="gt_row gt_right">16.92123</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2014-10-31</td>
      <td class="gt_row gt_right">96.19518</td>
      <td class="gt_row gt_right">180.8587</td>
      <td class="gt_row gt_right">180.6775</td>
      <td class="gt_row gt_right">165.5249</td>
      <td class="gt_row gt_right">93.52393</td>
      <td class="gt_row gt_right">101.31341</td>
      <td class="gt_row gt_right">112.66</td>
      <td class="gt_row gt_right">37.15370</td>
      <td class="gt_row gt_right">13.37242</td>
      <td class="gt_row gt_right">16.56238</td>
      <td class="gt_row gt_right">17.20904</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2014-11-28</td>
      <td class="gt_row gt_right">100.56856</td>
      <td class="gt_row gt_right">185.8393</td>
      <td class="gt_row gt_right">185.6411</td>
      <td class="gt_row gt_right">170.0898</td>
      <td class="gt_row gt_right">95.84360</td>
      <td class="gt_row gt_right">104.06014</td>
      <td class="gt_row gt_right">112.11</td>
      <td class="gt_row gt_right">36.58075</td>
      <td class="gt_row gt_right">13.68653</td>
      <td class="gt_row gt_right">17.66910</td>
      <td class="gt_row gt_right">17.52985</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2014-12-31</td>
      <td class="gt_row gt_right">98.31519</td>
      <td class="gt_row gt_right">185.2874</td>
      <td class="gt_row gt_right">185.1702</td>
      <td class="gt_row gt_right">169.5703</td>
      <td class="gt_row gt_right">95.80689</td>
      <td class="gt_row gt_right">103.75922</td>
      <td class="gt_row gt_right">113.58</td>
      <td class="gt_row gt_right">35.13086</td>
      <td class="gt_row gt_right">13.94251</td>
      <td class="gt_row gt_right">17.80461</td>
      <td class="gt_row gt_right">17.37833</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2015-01-30</td>
      <td class="gt_row gt_right">96.26794</td>
      <td class="gt_row gt_right">179.9134</td>
      <td class="gt_row gt_right">179.6837</td>
      <td class="gt_row gt_right">164.7011</td>
      <td class="gt_row gt_right">93.18576</td>
      <td class="gt_row gt_right">100.97132</td>
      <td class="gt_row gt_right">123.45</td>
      <td class="gt_row gt_right">34.88944</td>
      <td class="gt_row gt_right">12.97279</td>
      <td class="gt_row gt_right">21.59221</td>
      <td class="gt_row gt_right">17.32754</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2015-02-27</td>
      <td class="gt_row gt_right">103.21903</td>
      <td class="gt_row gt_right">190.0703</td>
      <td class="gt_row gt_right">189.7828</td>
      <td class="gt_row gt_right">173.8906</td>
      <td class="gt_row gt_right">98.53648</td>
      <td class="gt_row gt_right">106.68292</td>
      <td class="gt_row gt_right">116.16</td>
      <td class="gt_row gt_right">36.42736</td>
      <td class="gt_row gt_right">13.72827</td>
      <td class="gt_row gt_right">20.61383</td>
      <td class="gt_row gt_right">18.75810</td>
    </tr>
  </tbody>
  
  
</table></div><!--/html_preserve-->



We now have an xts object, and we have moved from daily prices to monthly prices.

Return.calculate(prices_monthly, method = “log”) to convert to returns and save as an object called assed_returns_xts. Note this will give us log returns by the method = “log” argument. We could have used method = “discrete” to get simple returns. The daily percentage  return on a stock is the difference between the previous day's price and the current day's price relative to the previous day's price. The monthly perentage return follows as the difference between the previous month and the current month's price divided by the previous months price.

$\text{Percentage Return } = \frac{\left(P_{1}-P_{0}\right)+D}{P_{0}}$
Where

$P_{0}$ Initial Asset Price
$P_{1}$ Ending Asset Price
$D$ is the dividends

The actual asset return is given as
$\text{ Return } = \left(P_{1}-P_{0}\right)+D$


```r
#asset_returns_xts <- na.omit(Return.calculate(prices_monthly, method = "discreet"))
prices_monthly <- to.monthly(prices, indexAt = "last", OHLC = FALSE)
asset_returns_quantmod <- na.omit(CalculateReturns(prices_monthly, method = "log"))
head(asset_returns_quantmod)%>%tk_tbl()%>%  gt()
```

<!--html_preserve--><style>html {
  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Helvetica Neue', 'Fira Sans', 'Droid Sans', Arial, sans-serif;
}

#glrpywjprj .gt_table {
  display: table;
  border-collapse: collapse;
  margin-left: auto;
  margin-right: auto;
  color: #333333;
  font-size: 16px;
  background-color: #FFFFFF;
  width: auto;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #A8A8A8;
  border-right-style: none;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #A8A8A8;
  border-left-style: none;
  border-left-width: 2px;
  border-left-color: #D3D3D3;
}

#glrpywjprj .gt_heading {
  background-color: #FFFFFF;
  text-align: center;
  border-bottom-color: #FFFFFF;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
}

#glrpywjprj .gt_title {
  color: #333333;
  font-size: 125%;
  font-weight: initial;
  padding-top: 4px;
  padding-bottom: 4px;
  border-bottom-color: #FFFFFF;
  border-bottom-width: 0;
}

#glrpywjprj .gt_subtitle {
  color: #333333;
  font-size: 85%;
  font-weight: initial;
  padding-top: 0;
  padding-bottom: 4px;
  border-top-color: #FFFFFF;
  border-top-width: 0;
}

#glrpywjprj .gt_bottom_border {
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
}

#glrpywjprj .gt_col_headings {
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
}

#glrpywjprj .gt_col_heading {
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: normal;
  text-transform: inherit;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
  vertical-align: bottom;
  padding-top: 5px;
  padding-bottom: 6px;
  padding-left: 5px;
  padding-right: 5px;
  overflow-x: hidden;
}

#glrpywjprj .gt_column_spanner_outer {
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: normal;
  text-transform: inherit;
  padding-top: 0;
  padding-bottom: 0;
  padding-left: 4px;
  padding-right: 4px;
}

#glrpywjprj .gt_column_spanner_outer:first-child {
  padding-left: 0;
}

#glrpywjprj .gt_column_spanner_outer:last-child {
  padding-right: 0;
}

#glrpywjprj .gt_column_spanner {
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  vertical-align: bottom;
  padding-top: 5px;
  padding-bottom: 6px;
  overflow-x: hidden;
  display: inline-block;
  width: 100%;
}

#glrpywjprj .gt_group_heading {
  padding: 8px;
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: initial;
  text-transform: inherit;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
  vertical-align: middle;
}

#glrpywjprj .gt_empty_group_heading {
  padding: 0.5px;
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: initial;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  vertical-align: middle;
}

#glrpywjprj .gt_striped {
  background-color: rgba(128, 128, 128, 0.05);
}

#glrpywjprj .gt_from_md > :first-child {
  margin-top: 0;
}

#glrpywjprj .gt_from_md > :last-child {
  margin-bottom: 0;
}

#glrpywjprj .gt_row {
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
  margin: 10px;
  border-top-style: solid;
  border-top-width: 1px;
  border-top-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
  vertical-align: middle;
  overflow-x: hidden;
}

#glrpywjprj .gt_stub {
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: initial;
  text-transform: inherit;
  border-right-style: solid;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
  padding-left: 12px;
}

#glrpywjprj .gt_summary_row {
  color: #333333;
  background-color: #FFFFFF;
  text-transform: inherit;
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
}

#glrpywjprj .gt_first_summary_row {
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
}

#glrpywjprj .gt_grand_summary_row {
  color: #333333;
  background-color: #FFFFFF;
  text-transform: inherit;
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
}

#glrpywjprj .gt_first_grand_summary_row {
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
  border-top-style: double;
  border-top-width: 6px;
  border-top-color: #D3D3D3;
}

#glrpywjprj .gt_table_body {
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
}

#glrpywjprj .gt_footnotes {
  color: #333333;
  background-color: #FFFFFF;
  border-bottom-style: none;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 2px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
}

#glrpywjprj .gt_footnote {
  margin: 0px;
  font-size: 90%;
  padding: 4px;
}

#glrpywjprj .gt_sourcenotes {
  color: #333333;
  background-color: #FFFFFF;
  border-bottom-style: none;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 2px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
}

#glrpywjprj .gt_sourcenote {
  font-size: 90%;
  padding: 4px;
}

#glrpywjprj .gt_left {
  text-align: left;
}

#glrpywjprj .gt_center {
  text-align: center;
}

#glrpywjprj .gt_right {
  text-align: right;
  font-variant-numeric: tabular-nums;
}

#glrpywjprj .gt_font_normal {
  font-weight: normal;
}

#glrpywjprj .gt_font_bold {
  font-weight: bold;
}

#glrpywjprj .gt_font_italic {
  font-style: italic;
}

#glrpywjprj .gt_super {
  font-size: 65%;
}

#glrpywjprj .gt_footnote_marks {
  font-style: italic;
  font-size: 65%;
}
</style>
<div id="glrpywjprj" style="overflow-x:auto;overflow-y:auto;width:auto;height:auto;"><table class="gt_table">
  
  <thead class="gt_col_headings">
    <tr>
      <th class="gt_col_heading gt_columns_bottom_border gt_left" rowspan="1" colspan="1">index</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">QQQ</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">IVV</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">SPY</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">VOO</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">VTI</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">IWB</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">GLD</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">EEM</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">XLF</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">GDX</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">ARKW</th>
    </tr>
  </thead>
  <tbody class="gt_table_body">
    <tr>
      <td class="gt_row gt_left">2014-10-31</td>
      <td class="gt_row gt_right">0.02607669</td>
      <td class="gt_row gt_right">0.023577611</td>
      <td class="gt_row gt_right">0.023277427</td>
      <td class="gt_row gt_right">0.023748307</td>
      <td class="gt_row gt_right">0.027089275</td>
      <td class="gt_row gt_right">0.023655167</td>
      <td class="gt_row gt_right">-0.031024422</td>
      <td class="gt_row gt_right">0.014096472</td>
      <td class="gt_row gt_right">0.028506520</td>
      <td class="gt_row gt_right">-0.216029614</td>
      <td class="gt_row gt_right">0.016865430</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2014-11-28</td>
      <td class="gt_row gt_right">0.04446046</td>
      <td class="gt_row gt_right">0.027165955</td>
      <td class="gt_row gt_right">0.027101615</td>
      <td class="gt_row gt_right">0.027204324</td>
      <td class="gt_row gt_right">0.024500294</td>
      <td class="gt_row gt_right">0.026750191</td>
      <td class="gt_row gt_right">-0.004893928</td>
      <td class="gt_row gt_right">-0.015541380</td>
      <td class="gt_row gt_right">0.023218202</td>
      <td class="gt_row gt_right">0.064683848</td>
      <td class="gt_row gt_right">0.018470776</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2014-12-31</td>
      <td class="gt_row gt_right">-0.02266116</td>
      <td class="gt_row gt_right">-0.002974243</td>
      <td class="gt_row gt_right">-0.002539849</td>
      <td class="gt_row gt_right">-0.003058407</td>
      <td class="gt_row gt_right">-0.000383041</td>
      <td class="gt_row gt_right">-0.002895892</td>
      <td class="gt_row gt_right">0.013026911</td>
      <td class="gt_row gt_right">-0.040442204</td>
      <td class="gt_row gt_right">0.018529945</td>
      <td class="gt_row gt_right">0.007640004</td>
      <td class="gt_row gt_right">-0.008681112</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2015-01-30</td>
      <td class="gt_row gt_right">-0.02104319</td>
      <td class="gt_row gt_right">-0.029432389</td>
      <td class="gt_row gt_right">-0.030077047</td>
      <td class="gt_row gt_right">-0.029135649</td>
      <td class="gt_row gt_right">-0.027739704</td>
      <td class="gt_row gt_right">-0.027236535</td>
      <td class="gt_row gt_right">0.083328739</td>
      <td class="gt_row gt_right">-0.006895657</td>
      <td class="gt_row gt_right">-0.072088211</td>
      <td class="gt_row gt_right">0.192875272</td>
      <td class="gt_row gt_right">-0.002926942</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2015-02-27</td>
      <td class="gt_row gt_right">0.06971794</td>
      <td class="gt_row gt_right">0.054918331</td>
      <td class="gt_row gt_right">0.054681883</td>
      <td class="gt_row gt_right">0.054294315</td>
      <td class="gt_row gt_right">0.055831874</td>
      <td class="gt_row gt_right">0.055024563</td>
      <td class="gt_row gt_right">-0.060867606</td>
      <td class="gt_row gt_right">0.043136074</td>
      <td class="gt_row gt_right">0.056602901</td>
      <td class="gt_row gt_right">-0.046370579</td>
      <td class="gt_row gt_right">0.079328556</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2015-03-31</td>
      <td class="gt_row gt_right">-0.02387254</td>
      <td class="gt_row gt_right">-0.016099672</td>
      <td class="gt_row gt_right">-0.015830159</td>
      <td class="gt_row gt_right">-0.015832690</td>
      <td class="gt_row gt_right">-0.011696995</td>
      <td class="gt_row gt_right">-0.013102059</td>
      <td class="gt_row gt_right">-0.021757014</td>
      <td class="gt_row gt_right">-0.015086285</td>
      <td class="gt_row gt_right">-0.006179701</td>
      <td class="gt_row gt_right">-0.154150526</td>
      <td class="gt_row gt_right">-0.006792035</td>
    </tr>
  </tbody>
  
  
</table></div><!--/html_preserve-->






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


{% include /ETF/p2.html %}



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
Prices%>%head() %>% DT::datatable()
```

<!--html_preserve--><div id="htmlwidget-47a0c08efdb97f0482a9" style="width:100%;height:auto;" class="datatables html-widget"></div>
<script type="application/json" data-for="htmlwidget-47a0c08efdb97f0482a9">{"x":{"filter":"none","data":[["1","2","3","4","5","6"],["QQQ","QQQ","QQQ","QQQ","QQQ","QQQ"],["2010-01-11","2010-01-12","2010-01-13","2010-01-14","2010-01-15","2010-01-19"],[46.610001,46.080002,45.919998,46.259998,46.470001,45.959999],[46.639999,46.139999,46.490002,46.52,46.549999,46.639999],[46.119999,45.529999,45.610001,46.220001,45.650002,45.950001],[46.360001,45.779999,46.349998,46.389999,45.849998,46.59],[104673400,90673900,100661000,75209000,126849300,84388200],[41.664768,41.143528,41.655792,41.691734,41.206409,41.871487]],"container":"<table class=\"display\">\n  <thead>\n    <tr>\n      <th> <\/th>\n      <th>symbol<\/th>\n      <th>date<\/th>\n      <th>open<\/th>\n      <th>high<\/th>\n      <th>low<\/th>\n      <th>close<\/th>\n      <th>volume<\/th>\n      <th>adjusted<\/th>\n    <\/tr>\n  <\/thead>\n<\/table>","options":{"columnDefs":[{"className":"dt-right","targets":[3,4,5,6,7,8]},{"orderable":false,"targets":0}],"order":[],"autoWidth":false,"orderClasses":false}},"evals":[],"jsHooks":[]}</script><!--/html_preserve-->





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


{% include /ETF/p3.html %}






#### Returns


```r
monthlyreturns <-Prices%>% select(symbol,date,adjusted)%>%
  group_by(symbol)%>%
  tq_transmute( 
                 mutate_fun = periodReturn, 
                 period     = "monthly", 
                 type       = "arithmetic")%>%head()



monthlyreturns%>%head() %>% gt()
```

<!--html_preserve--><style>html {
  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Helvetica Neue', 'Fira Sans', 'Droid Sans', Arial, sans-serif;
}

#ckubnmrutg .gt_table {
  display: table;
  border-collapse: collapse;
  margin-left: auto;
  margin-right: auto;
  color: #333333;
  font-size: 16px;
  background-color: #FFFFFF;
  width: auto;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #A8A8A8;
  border-right-style: none;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #A8A8A8;
  border-left-style: none;
  border-left-width: 2px;
  border-left-color: #D3D3D3;
}

#ckubnmrutg .gt_heading {
  background-color: #FFFFFF;
  text-align: center;
  border-bottom-color: #FFFFFF;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
}

#ckubnmrutg .gt_title {
  color: #333333;
  font-size: 125%;
  font-weight: initial;
  padding-top: 4px;
  padding-bottom: 4px;
  border-bottom-color: #FFFFFF;
  border-bottom-width: 0;
}

#ckubnmrutg .gt_subtitle {
  color: #333333;
  font-size: 85%;
  font-weight: initial;
  padding-top: 0;
  padding-bottom: 4px;
  border-top-color: #FFFFFF;
  border-top-width: 0;
}

#ckubnmrutg .gt_bottom_border {
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
}

#ckubnmrutg .gt_col_headings {
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
}

#ckubnmrutg .gt_col_heading {
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: normal;
  text-transform: inherit;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
  vertical-align: bottom;
  padding-top: 5px;
  padding-bottom: 6px;
  padding-left: 5px;
  padding-right: 5px;
  overflow-x: hidden;
}

#ckubnmrutg .gt_column_spanner_outer {
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: normal;
  text-transform: inherit;
  padding-top: 0;
  padding-bottom: 0;
  padding-left: 4px;
  padding-right: 4px;
}

#ckubnmrutg .gt_column_spanner_outer:first-child {
  padding-left: 0;
}

#ckubnmrutg .gt_column_spanner_outer:last-child {
  padding-right: 0;
}

#ckubnmrutg .gt_column_spanner {
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  vertical-align: bottom;
  padding-top: 5px;
  padding-bottom: 6px;
  overflow-x: hidden;
  display: inline-block;
  width: 100%;
}

#ckubnmrutg .gt_group_heading {
  padding: 8px;
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: initial;
  text-transform: inherit;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
  vertical-align: middle;
}

#ckubnmrutg .gt_empty_group_heading {
  padding: 0.5px;
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: initial;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  vertical-align: middle;
}

#ckubnmrutg .gt_striped {
  background-color: rgba(128, 128, 128, 0.05);
}

#ckubnmrutg .gt_from_md > :first-child {
  margin-top: 0;
}

#ckubnmrutg .gt_from_md > :last-child {
  margin-bottom: 0;
}

#ckubnmrutg .gt_row {
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
  margin: 10px;
  border-top-style: solid;
  border-top-width: 1px;
  border-top-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 1px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 1px;
  border-right-color: #D3D3D3;
  vertical-align: middle;
  overflow-x: hidden;
}

#ckubnmrutg .gt_stub {
  color: #333333;
  background-color: #FFFFFF;
  font-size: 100%;
  font-weight: initial;
  text-transform: inherit;
  border-right-style: solid;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
  padding-left: 12px;
}

#ckubnmrutg .gt_summary_row {
  color: #333333;
  background-color: #FFFFFF;
  text-transform: inherit;
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
}

#ckubnmrutg .gt_first_summary_row {
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
}

#ckubnmrutg .gt_grand_summary_row {
  color: #333333;
  background-color: #FFFFFF;
  text-transform: inherit;
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
}

#ckubnmrutg .gt_first_grand_summary_row {
  padding-top: 8px;
  padding-bottom: 8px;
  padding-left: 5px;
  padding-right: 5px;
  border-top-style: double;
  border-top-width: 6px;
  border-top-color: #D3D3D3;
}

#ckubnmrutg .gt_table_body {
  border-top-style: solid;
  border-top-width: 2px;
  border-top-color: #D3D3D3;
  border-bottom-style: solid;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
}

#ckubnmrutg .gt_footnotes {
  color: #333333;
  background-color: #FFFFFF;
  border-bottom-style: none;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 2px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
}

#ckubnmrutg .gt_footnote {
  margin: 0px;
  font-size: 90%;
  padding: 4px;
}

#ckubnmrutg .gt_sourcenotes {
  color: #333333;
  background-color: #FFFFFF;
  border-bottom-style: none;
  border-bottom-width: 2px;
  border-bottom-color: #D3D3D3;
  border-left-style: none;
  border-left-width: 2px;
  border-left-color: #D3D3D3;
  border-right-style: none;
  border-right-width: 2px;
  border-right-color: #D3D3D3;
}

#ckubnmrutg .gt_sourcenote {
  font-size: 90%;
  padding: 4px;
}

#ckubnmrutg .gt_left {
  text-align: left;
}

#ckubnmrutg .gt_center {
  text-align: center;
}

#ckubnmrutg .gt_right {
  text-align: right;
  font-variant-numeric: tabular-nums;
}

#ckubnmrutg .gt_font_normal {
  font-weight: normal;
}

#ckubnmrutg .gt_font_bold {
  font-weight: bold;
}

#ckubnmrutg .gt_font_italic {
  font-style: italic;
}

#ckubnmrutg .gt_super {
  font-size: 65%;
}

#ckubnmrutg .gt_footnote_marks {
  font-style: italic;
  font-size: 65%;
}
</style>
<div id="ckubnmrutg" style="overflow-x:auto;overflow-y:auto;width:auto;height:auto;"><table class="gt_table">
  
  <thead class="gt_col_headings">
    <tr>
      <th class="gt_col_heading gt_columns_bottom_border gt_left" rowspan="1" colspan="1">date</th>
      <th class="gt_col_heading gt_columns_bottom_border gt_right" rowspan="1" colspan="1">monthly.returns</th>
    </tr>
  </thead>
  <tbody class="gt_table_body">
    <tr class="gt_group_heading_row">
      <td colspan="2" class="gt_group_heading">QQQ</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2010-01-29</td>
      <td class="gt_row gt_right">-0.07700585</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2010-02-26</td>
      <td class="gt_row gt_right">0.04603873</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2010-03-31</td>
      <td class="gt_row gt_right">0.07710888</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2010-04-30</td>
      <td class="gt_row gt_right">0.02242552</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2010-05-28</td>
      <td class="gt_row gt_right">-0.07392362</td>
    </tr>
    <tr>
      <td class="gt_row gt_left">2010-06-30</td>
      <td class="gt_row gt_right">-0.05975721</td>
    </tr>
  </tbody>
  
  
</table></div><!--/html_preserve-->









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


![ ]( /img/ETF/unnamed-chunk-13-1.png1.png)

```r
   #scale_color_viridis_d() 
```










