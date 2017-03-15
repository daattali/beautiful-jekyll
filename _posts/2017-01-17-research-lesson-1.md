---
layout: post
title: "Research lessons learnt the hard way: #Maintaining organised data files"
date: 2017-01-17
---
This is the first post in a (hopefully not long) series of research lessons learned from making mistakes. Most of the lessons have been in various aspects of programming as none of my supervisors or fellow postgraduates have any interest in R or Python, so I have had to learn through books and online resources. Combined with the fact I do not have any history in computer science, I’ve learnt a lot through trial and error, and learning from the mistakes I have made. Keeping with the philosophy of this blog, my aim here is to share my experiences in research for the benefit of other people.

## LESSON LEARNT #1: MAINTAINING ORGANISED DATA FILES

The first mistake I have made is not keeping an organised version of my data. One of my studies involved a response time task that was split into three blocks. The program that I used to create the experiment produced a separate data file for each block. The first step before I could analyse any data was to create a master version of the data that contained all three blocks. During this process, I copied and pasted all the responses into one spreadsheet and labelled it as the master file for each participant… or so I thought.

Recently, I went to perform a different type of analysis on the data that required it to be changed from long format to wide format before any data screening. However, it turns out I had only maintained an organised version of the master files for approximately half of the participants. This is either the result of not saving the master versions after I had analysed the trial data, or they are hidden in a separate folder that I cannot find. Either way, this is not good organisation and I clearly did not have future me in mind. I only have myself to blame, so what would be a better method of organisation to save time in future?

## A BETTER ORGANISATION METHOD

The approach I have taken for most of the study is to maintain a folder that contains the participant’s data in several versions that can be used for different purposes:

1. Raw data
This is the file that is produced directly from that whatever program you are using. For example, I used PsychoPy for my experiment which produces a .csv file (helpful if you use R). In my most recent study, I organised the task into three blocks which produced a separate .csv file for each. The first version of data in my participant folder are these three files. These are the raw files that are fresh from the participant. Nothing is done to them, and they are preserved as the original files.

2. Readable data
The next step is to have a file that you can analyse straight away in the spreadsheet, or read into R. These are the master files that I mentioned above. As I had three separate files, I wanted all the trials to be included in one spreadsheet, ready to be analysed. Although this is still the raw data, it is something that you can analyse straight away with no messing around. Note: depending how you receive your data, you might find that this is the raw data that is fresh from the participant listed in step 1.

3. Processed data
The next step is to perform any data screening requirements that are relevant to your study. For example, in my study only correct responses were retained, and then responses within certain boundaries (I previously wrote about how you can write an R script to automate this process). This produces a file that can be analysed for mean responses or whatever your dependent variable is. The important thing in this step is that you have a data file that is ready to go. If you need to come back to it for whatever reason, you can immediately rerun your analysis script.


This process leaves you with three (or two depending on the format that you receive the data) versions of the data that can be used immediately for different purposes. For example, for my main analysis, if I wanted to check I had recorded the mean values correctly, I could immediately go back to the file produced in step 3 and reanalyse it. However, if I had a different purpose like the motivation for this blog post, I would need the file produced in step 2. Organising your data to contain different versions with future you in mind saves you a lot of time and headaches. This issue could have been even more problematic if it was years instead of months down the line. I would have to spend even longer familiarising myself with the variable names and trying to remember what I was doing.

## Take home message
When you are analysing your data, have future you in mind. Keep an organised folder for each participant’s data in different versions that allows you to quickly go back and access it without having to process it again.
