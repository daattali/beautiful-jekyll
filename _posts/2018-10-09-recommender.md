---
layout: post
title: Recommendation Engine For Retail Marketing
subtitle: Matrix Factorization
tags: [books, test]
author: Nana Boateng
---


## Recommendation Engine For Retail Marketing



Introduction
---------------------------------

Recommender systems are among the most popular applications of data science we see all around us. They are used to predict the "rating" or "preference" that a user would give to an item. In the retail market Amazon and ebay use it to  personlize our web experience by recommending items to shoppers. Facebook uses it to recommend friends and pages to follow. Pandora uses to suggest which songs  to play and Netflix recommends movies with it. A recommender system studies customer behavior like similarites between items purchased, past purchases, demographic info, their search history or movie review  by consumers and  use that information to predict other items to those customers.
The benefits of recommender systems include improving retention,increasing sales and brand loyalty.




$
\text{Similarity }(x,y)=\frac{\displaystyle \sum\limits_{i \in I_{x,y}}(r_{x,i}-\bar{r}_{x})(r_{y,i}-\bar{r}_{y})}{\sqrt{\displaystyle \sum\limits_{i \in I_{x} }(r^{2}_{x,i}-\bar{r}_{x})^{2}} \sqrt{\displaystyle \sum\limits_{i \in I_{y} }(r^{2}_{y,i}-\bar{r}_{y}})^{2}}
$
