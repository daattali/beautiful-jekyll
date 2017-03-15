---
layout: page
title: A beginner's experience of learning R 
---
Throughout my undergraduate psychology degree, I had exclusively used SPSS (to the point where I thought it was the only way to do data-analysis), and it was only during my Master’s degree that I came across R as a data-analysis language and environment. I did not know anyone else who used R, and I did not see anything online for what it is like to learn how to use it. Therefore, I thought it might to be useful to share my experience of learning R for anyone else who wants to learn but does not know where to start.

I’ll start by providing a bit of my background and what drew me to using R, and then outline the beginning of my experience. I’ll end with some tips that might be useful for anyone else in a similar position, and an annotated list of resources that have been indispensable to me.

## My background

I am currently a psychology PhD student and my research is exclusively quantitative. Research methods and statistics were my favourite modules throughout my undergraduate psychology degree, and I have a decent understanding of data-analysis. However, my whole education was built on using SPSS. There is nothing specifically wrong with it but I think it creates bad habits through the ease in which you can just click through menus, and there are certain things that it is not suited for. For example, the plots that it produces are notoriously ugly, and there is no platform to perform some more advanced analyses. What I am trying to get at here is that when I started to learn R I had a good education in data-analysis, but the main barrier was my lack of experience in programming. 

## A false start

My first engagement with R was through Roger Peng’s book R Programming for Data Science. I had seen R mentioned from place to place but I had never used it myself (or knew anyone else who used it at my university). I thought the book would be a good place to start, but I found it overwhelming for someone who had no prior experience in programming or using R. It is a great book for learning more about R as a programming language, but I did not have any context to work with and it all became very confusing. It was like trying to learn a foreign language by learning the underlying grammar before you know any vocabulary. I quickly become lost and gave up trying.

## …Another go

A month or two later, an introduction to R workshop was held at my university and being guided through the environment in a structured format allowed me to see how it all fitted together. I was able to see how you entered data, I was able to learn some of the coding basics, and I was able to see how a t-test was performed. This was much more tangible, and I started to see how key components of the R language were structured.

## Steady progress

The main learning curve for getting to grips with the R language was overcome by following online tutorials. The first couple of months I used R exclusively for creating plots of some old data for a conference poster. I would look at tutorials on websites such as R-bloggers (see resources below) to copy their code and adapt it to use my own data. Trial and error has been one of the best strategies for me (see tips below). I would start with an online example, try to adapt it to fit my own data, and be bombarded with error messages stating something is wrong.


## Current progress

It has taken around eight months (from December 2015) to reach my current level of understanding. There have been many times when I have become frustrated at not being able to work out what I have done wrong, but the key to learning R is persistence (see tips). Whenever I have made significant progress, it has been because I have sat in front of my laptop for a few hours and worked on a specific task. A large amount of trial and error is involved (especially when the programming language is unfamiliar), and you need to look past all the error messages. Unless you are comfortable with programming, there is a steep initial learning curve, but it becomes progressively easier with time and experience.

I’ve gone through this process for eight months now and I’m finally seeing some rewarding progress. Looking back, I have a few tips and resources that I wish I was aware of. Hopefully if you are reading this and are either new to using R or want to begin to use it, you will find them useful and avoid some of the head-scratching that I have done.

## Tips for progressing with R  

1. Persistence

My main tip for learning R (especially if you have limited programming experience) is persistence. You will receive more error messages than you receive actual output, but try not to be put off by it, and try to stick at it until you work out what the problem is. You might need to take a break and look at it with a fresh pair of eyes, but make sure you do not give up until you have produced what you set out to do. Most of these experiences are useful for the future, as problems that have taken a large amount of time to overcome become easier to spot in future.

2. Have a clear goal in mind

When I first started using R, my aim was to just learn R. This is quite vague, and unless you’re enrolled on a course or following a guide, it is difficult to know exactly where to start and how to progress. I started to see more progress when I had a clear goal, which in my case was making some plots for a conference poster. I knew what I wanted to produce as an output, so it was just a matter of learning what R code was necessary to produce it.

3. Use online tutorials

The chances are that each analysis you are trying to perform, or each plot you are aiming to create has been done before. One of my favourite aspects of R is the community of users who help others through online tutorials and blog posts. All of my initial successes in using R were from adapting the code of others who had created tutorials. When you are unfamiliar with the programming language, it is helpful to copy something you know that works and change it from there. Use other people’s experience wisely and take advantage of it.

4. Use package help documents

R thrives through the input of its users, and many create specific packages for specific problems. Their functions can contain a lot of arguments and unless you repeatedly use a package it is difficult to remember each one. For each package there is usually a help document that outlines each of the functions within the package, and explains what each argument within those functions does. I often have the help package open when I writing the code so I can keep referring back to the manual.

## Useful resources

### Books

Discovering statistics using R – Andy Field, Jeremy Miles, and Zoe Field

This book is aimed towards psychology, but it is one of the best introductory books on statistics and programming in R. It includes both statistical theory and downloadable R code and tutorials to follow. I would hugely recommend this as a starting point, particularly if you are a psychology student.

R Programming for Data Science – Roger D. Peng

With over 90,000 readers on Leanpub, this is a hugely successful book that outlines the fundamentals of R programming. I would not recommend it as a starting point, but it is indispensable when you want to brush up on the programming language.

ggplot2 – Hadley Wickham

This is my favourite package for creating plots. As well as having some of the most helpful documentation to help you with coding, there is an accompanying book for if you want to read more about the underlying theory of ggplot2. As I spent a lot of time using R for creating plots, this book was useful in showing the full capabilities of the package.

Learning statistics with R – Daniel Navarro

As well as the advantage of it being free (although I do encourage you to buy a copy), this is one of my favourite guides to using R. Similar to Discovering statistics using R, the book is organised by starting with the underlying statistical principles and then providing tutorials. The examples utilise the data sets incorporated into R and the accompanying package to the book, so it is easy to follow along without additional downloads.

### Blogs

R-Bloggers

This is a kind of blog of blogs (a meta-blog if you will). R-bloggers is a collection of tutorials creating by other R users on a range of topics including simulation, analysis, and creating plots. This website has been crucial for me, so if you want to learn how to do something with R, I would suggest having a look here first.

Stack Overflow

This is a general programming Q&A that is not specific to R. However, there are a lot of questions on here that have been answered about R problems. Although I have never done it myself, if you are totally stuck and need some assistance, you can post a question and hope someone can provide you with an answer. These posts typically appear when I Google a problem, so it can be an incredibly useful source of information.

Quick-R

This is a website full of tutorials on how to perform analyses and create plots in R. Most of the sections are very straight forward so it would be an advantage to be familiar with the underlying concepts beforehand. Robert Kabacoff, the creator of the website, also has a book called R in Action.

Cookbook for R

This is another website with tutorials and examples on how to perform analyses. It is particular useful for ggplot2 as it covers a range of common features such as how to rename axes and using facets. Similar to Quick-R, there is also an accompanying book called R Graphics Cookbook which extends many of the website features.

### Other

ggplot2 cheat sheet  – R Studio

R studio is a user interface that is used in conjunction with R. I’ve never used R without the addition of R studio as it makes everything a little easier. On top of this, they create cheat sheets to help with navigating certain elements. They have one for R Markdown, and they have a particular good one for ggplot2. If you need a quick guide without trawling through the documentation, this is a good place to start.

Have I missed anything that you have found useful when learning R? Feel free to contact me through email, Twitter, or the comments and I will add it to the list.
