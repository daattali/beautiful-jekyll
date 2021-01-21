---
layout: post
title: Circular diagrams with circlize
subtitle: A beautiful way to show paired relationships
thumbnail-img: /assets/img/2020-02-26-circular-diagrams/circlize.png
tags: [R Programming, Plots]
---

Circular layouts are useful and elegant plots to show relations between elements. Specifically, we will make a chord diagram to visualize relationships between target genes and miRNAs. To achieve our goal, we will use the [circlize](https://jokergoo.github.io/circlize_book/book/) package for R.

First, we will install the required packages. If you have tidyverse already installed, you actually have the readr package.

``` r
install.packages("readr")
install.packages("circlize")
```

``` r
library(readr)
library(circlize)
```

Download the example interaction dataset to work with

``` r
read_csv(url("https://raw.githubusercontent.com/FairerBadge66/neurito-bioinformatics/gh-pages/assets/input_data/miRNA-target-interactions.tsv"))
```