---
title: Processing Reddit Data to Tackle Police Brutality
subtitle: A short dive into the world of Natural Language Processing
---

## Background

This project was made in conjunction with Human Rights First, an independant advocacy and action organization. The work they do is centered around getting America to stand up to its ideals, and in doing so, they sought the help of Lambda School for their project. Their challenge to my group and I, as well as two other groups of students here at Lambda, was to see if we could make a map of continental America that showed events of police brutality, using data aggregated from Reddit and Twitter.

While most of the issues pertaining to the website and getting that to work fell to the Web Development team, the issue of sourcing and cleaning data fell to myself and my team member, Chris. The requirements of the project meant that we would be creating a FastAPI web app deployed via ElasticBeanstalk to Amazon Web Services (AWS), something that neither of us had done before, but other than that, our options for going about sourcing the data and cleaning it were entirely open to us.

### Initial Worries

At first, both Chris and I worried about using FastAPI and AWS; we'd never worked with either framework, so we worried that we'd have to spend a fair amount of time learning how it works and getting it set up. On further inspection, we realised that FastAPI beared a striking resemblance to Flask, another kind of web-app framework, but came with a built-in user interface that allowed us to test the functions of our app. As for the Amazon Web Services, we haven't gotten that far, but we expect to have an app built later this week.

## API Roadmap Breakdown

At the start of working on the project, we broke down what we thought we'd need to make in order to get our app running. This included things like finding a source of data, cleaning it, getting the app up and running, and outputting the cleaned data through an endpoint in the app. There were also times during working on the project where there was some confusion with how the data would flow from the API to the backend, and at one point, Chris and I had set up a database to hold data because there was some miscommunication as to who would be sanitizing the data for duplicates.

![picture of trello board](https://i.imgur.com/BEg4Eao.png)

###### General overview of what the Data Science team needed to do.

## The First Four Weeks

### Week One: Planning the project

Week one of working on the project consisted of planning things out. We decided on what kind of framework layout we'd be using for the project as well as how each piece of the project was going to communicate with one another. Below is a diagram of the layout we eventually came up with in terms of how the project would be laid out:

![diagram of the project](https://i.imgur.com/0U4nrK7.png)

###### Diagram of our project layout

### Week Two: Data Exploration

Week Two was where the teams split up and started working more specifically on solving the problems they had to. For Data Science, that meant getting an idea of what our data should look like. While we did get a general idea of how our data was going to leave our API based off of some websites like (846policebrutality.com)[https://incidents.846policebrutality.com/] which provided their own API to see how they formatted their data, we didn't make any progress on updating the code for our API, believing that we needed the keys to AWS to actually make any progress towards it. We did, however, make progress on exploring both the data from the 846 API, as well as pulled data from Reddit, of which we explored ways to filter and process.

![an example of the data we pulled from reddit](https://i.imgur.com/b5xe2rG.png)

###### Example data pulled from Deddit

### Week Three: API Updates 

Week Three consisted mostly of figuring out how to build the API locally in Docker, and before that, getting Docker to work, even. Once that was all sorted, however, it didn't take long to transfer the code we'd written in various notebooks to output the data from the 846 API as a proof that our API was working.

![The title card of our API](https://i.imgur.com/NLViiKy.png)

###### The app in action

### Week Four: Modelling the Data

Week Four is where a large portion of our work on actually serving the data from Reddit and Twitter got done. We updated the app to create new endpoints that served data from Reddit filtered through a model. The model itself uses Natural Language Processing to determine if the post from reddit is about police brutality or not, and only the data returned by the model as being about police brutality gets passed along.

![an example of the app in action](https://i.imgur.com/qQfRtgr.png)
