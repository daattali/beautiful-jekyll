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










