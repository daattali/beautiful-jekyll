---
layout: page
title: Projects
subtitle: Let's see what I've done ! 
---

*I'll talk about projects (even some small code bits) I've done in past or currently working on, which I think are pretty cool. If I feel like I need to talk a lot about a project, I'll make a blog post about it as well*

Let's begin

## Machine Learning (incl. NLP) 

***Recursion Cellular Image Classification***  
This is what I've just started working on. This is actually a Kaggle competetion <a href = "https://www.kaggle.com/c/recursion-cellular-image-classification" target = "_blank"> here </a>. The challenge here is to disentangle experimental noise from real biological signals. I'll update this, once I have results.

***Predicting NASDAQ Composite movements using News*** <a href="https://github.com/anti-mony/NASDAQ-Movement-Prediction" target="_blank"><i class="fab fa-github"></i></a>  
I did this project very recently from July-August 2019, where I tried to predict how the NASDAQ Composite index moves based on the news that comes in daily, here is a <a href= "http://localhost:4000/2019-09-06-PredictNasdaqwithNews/" target="_blank">blog</a> for this.  
***TLDR**: I used RNNs to summarize text and used that to predict +ve/-ve movements of the index, I gathered data from sources online; cleaned and pre-processed it using NLTK and used PyTorch for deep learning.*

***Just Miscelaneous Models***  
I've implemented various models such as *Decision Tree Classifier*, *k-nearest neighbors*, *k-means (unspervised)*, *AdaBoost*, *SVM* and *Seq2Seq* (for translation). These don't classify as projects because the time spent on them was one-two weeks as course work. But yet, these are powerful machine learning models and need to be mentioned. Right now, I'm looking into the <a href= "https://arxiv.org/abs/1706.03762" target="_blank">Transformer</a> and derived models.

***Air Quality Analysis*** <a href= "https://github.com/anti-mony/DataMiningLabs" target="_blank"><i class="fab fa-github">&nbsp;</i></a>  
This was the project where I was first dipped my toes into the field of data. I was more focused on the visualizations in this one than other aspects. We got data from the EPA about the air and we tried to see how has it changed across years. We did visualizations such as choropleths, tree-maps and the good old bar charts using Plotly for R and put them in a Shiny Dashboard.

## Web development

***Shrink-Pdf*** <a href= "https://github.com/anti-mony/Shrink-Pdf" target="_blank"><i class="fab fa-github">&nbsp;</i></a>  
I did this one just out of curiosity and a little bit of need. I was getting suspicious about online pdf converts storing my documents so I made one of my own. I found a linux script based on GhostScript by [Alfred Klomp](http://www.alfredklomp.com/programming/shrinkpdf/). Also another big reason for doing this was to use Flask tp write an API, which I had never done before and also to try Bulma, a CSS framework which I had just heard about. I know I could've just used the script offline I know, but then I never would have tried Flask or Bulma. 


***Golang Web API*** <a href= "https://github.com/anti-mony/Topos-Intern-Challenge" target="_blank"><i class="fab fa-github">&nbsp;</i></a>  
This fun is a funny one, back in end of March in 2019 when I was looking for internships, so I sgned up for this challenge from TOPOS, they wanted me to write a web api in Golang (GET, POST, DELETE). So over the weekend, I learned Golang and made web API which also had an ETL (Extract, transform, load) component in it, I was pulling data from the city of NewYork and transforming it so as to store it into a MongoDB instance. I learned quite a lot from this, also it gave me a head start in Golang which I was supposed to learn in my Parallel Programming course. 

***E-Commerce Website*** <a href= "https://github.com/anti-mony/The-Baking-Room---E-Commerce-Website" target="_blank"><i class="fab fa-github">&nbsp;</i></a>  
This was a course project in my undergrad, this project took way longer than expected. I did this to learn the MEAN stack, but then because the complexity was increasing too much (for the time we had) we left out Angular(which I learnt later). I did this with 4 other classmates, I was primarily working on the backend which included setting up the routing, data models, ajax requests, cookie management and more. It was a good experience overall, I had a good supportive team and we were able to work well together. 

## Miscellaneous  

***Internet Radio*** <a href= "https://github.com/anti-mony/Computer-Networks" target="_blank"><i class="fab fa-github">&nbsp;</i></a>  
A command line based Internet radio server and a client to connect. The server could serve upto 4 concurrent channels, you would have to provide the streams as a file. And the client could connect to any of those channels, play and pause the music using command line. This was all done in C, which was the hard part. Forking processes, managing them and making the network work without choppy audio was a challenge. This is one of the projects that I'm really proud of, just because of the amount of effort that went into it and the result that I could achieve.
