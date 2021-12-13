---
layout: home
title:  DescribeByQuote
subtitle: Detect profile of the speaker with their quotations based on deep learning
---

<style>
table {
margin: auto;
}
</style>


## Introduction

Quotations, the repetition of well-known statement parts, have preserved and inherited wisdoms and perspectives 
that significantly changed the world. And we not only focus on the power of the words, but also the people who speaked 
them. There are lots of famous quotations that we can instantly identify the speakers. However, we can find a large 
number of quotations whose speakers are unidentifiable. We may never know their names, but is that possible to find 
other more details about their profiles? 

![Mr_unknown](https://github.com/WeiSHI7/weishi7.github.io/blob/master/assets/img/unknown_speaking.png)

Our project, **DescribeByQuote**, aims to detect the profiles of the speakers from the quotations based on deep learning
methods. While performing analysis of Quotebank data we found out that around **34%** of quotations don't have assigned 
speakers to it (e.g., 1.8 million out of 5.2 million in file quotes-2020.json). Our goal is to answer the following question: if we cannot determine the exact author of a quotation, what other information can we get from it? We would like to achieve this by training the deep learning models that can help to classify with different features.

In that work, first we would need to generate labels for our quotations, which requires extra information. Therefore, we extracted those additional information about known authors of the quotations by parsing their information from **Wikipedia**. Through filtering and parsing, we successfully extracted six important features of the speakers as the labels for the data, including ```Gender, Occupation, Nationality, Ethic group, Date of birth, and Religion```. 

| Feature Name | Class Number| 
| :----- | :----- |
| Gender | 2 |
| Occupation | 10 |
| Nationality | 5 |
| Ethic Group | 10 |
| Date of Birth | 8 |
| Religion | 10 |

<!-- | Feature Name | :----- | Gender | occupation | nationality | ethic group | date of birth | religion |
| Class Number| :----- | 2 | 10 | 5 | 10 | 8 | 10 | -->

With the data and labels, we trained several models and verified the functionalities, then predicted the features of the 
quotatations that are not assigned speakers in Quotebank. Also, we did some analysis on the outcomes and explored the 
relationships between different features, as well as tried to understand the mechanism of the prediction.

## Methods 

### Data Preparation

### Data analysis

### Deep Learning Metrics

## Experiment

### Set Up

### Results and Analytics