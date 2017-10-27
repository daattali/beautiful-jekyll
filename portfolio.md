---
layout: page
title: Portfolio - Brian Hardenstein
---

All projects:
* Python was used for all projects unless otherwise noted.
* Used models from SciKit-Learn unless otherwise noted. 
* Data manipulation was performed using Numpy/Pandas unless otherwise indicated. 
* Cross validation was utilized in all cases. Usually 70/30 split but in certain cases 60/30/10 for high iteration modeling.
* All projects utilized CRISP-DM methodology
* Sorted with most recent projects first

**Smartphone User Data Cleaning and Formatting (W.I.P)**
* **Tools Used:** Python, JSON, tarfile, gunzip, Matplotlib
* **Summary:** Taking in several TB of smart phone data from CrowdSignals.IO, modifying/fixing some values in the data, then filtering the data based on labels that exist in other files. Project consists of many relatively small JSON files (5KB to 10MB) that are stored in large (8+GB compressed) .tar.gz files. 

**Atlantic Hurricane Animated Data Visualizations**
![Hurricane Visualizations](img/hurricane_thumb.png)

* **Tools Used:** Python, overextended Matplotlib, Numpy, FFMpeg, custom FFMpeg Python wrapper
* **Summary:** As global warming heats up the oceans there is more energy that can power hurricanes. This project was inspired by a /r/dataisbeautiful post on Reddit. I first tried to recreate the original post and then improve on it. Eventually I created 4 different visualizations that were rendered using Matplotlib and my FFMpeg wrapper. More information [here](https://pixelatedbrian.github.io/2017-10-17-atlantic-hurricanes/)

**DeepTraffic Neural Network**
* **Tools used:** CNN, DNN, DeepQ, DeepLearn.js, regularization, [DeepTraffic](http://selfdrivingcars.mit.edu/deeptrafficjs/), tanh/relu activation
* **Summary:** MIT contest where a neural network has to learn how to navigate through video game-like traffic. (Think frogger) Evaluation is average speed (mph) on test sets mean of 10 runs.  Current highest 'score' is 67.4mph, 65mph is a passing grade for the MIT class. Implementing automated grid search of hyperparameters to try to improve performance more.

[Home Price Prediction: Ames, IA (work in progress)](https://github.com/Brionnic/sturdy-umbrella/blob/master/README.md)
* **Tools used:** Selenium scraping/munging, EDA, stacked ensemble, feature engineering, model experimentation, kaggle-like project, PostGreSQL
* **Summary:** Inspired by a meetup presentation implemented home price regressor using Ames, Iowa dataset. Scraped additional data from Story County Assessor website (Ames’ county) to create new features and SQL to manipulate/store data.

### Individual Case Studies:

[Indie Game Recommender (Capstone Project)](https://github.com/Brionnic/Indie-Game-Recommender/blob/master/README.md)
* **Tools used:** BeautifulSoup, Selenium, AWS EC2/S3, MongoDB, EDA, Spark/PySpark, Spark MLLib NMF ALS explicit/implicit, rating weighting system, model serialization, capstone presentation
* **Summary:** Scraped 3M web pages in 5+ rounds of iteration, wrangled data with MongoDB workflow, ultimately predicted using ~10M rows of data, switched from explicit ratings to implicit ratings (log10 playtime) which ended up improving predictions quite a bit, presented capstone project to audience > 50. Serialized model for flask website but have not yet implemented front end. 

### Case Studies During Bootcamp:

**Classify Phone Apps Based on Text Descriptions (1hr assessment)**
* **Tools used** tfidf vectorizer, NLP, Multinomial Naive Bayes Classifier
* **Summary:** For a 1hr test used sklearn's tfidfvectorizer with basic stop words to get a sparse matrix which was then fed into a MultinomialNB classifier. 92% mean accuracy (of 5 runs) [solution](https://github.com/pixelatedbrian/BKHardenstein_Portfolio/blob/master/src/final_assessment2.py) / [explanation](https://github.com/pixelatedbrian/BKHardenstein_Portfolio/blob/master/src/final_assessment2.txt)

**Event Planning Fraud Detection**
* **Tools used:** gradient boosting classifier, recall optmized, serialized model, confusion matrices, ROC, flask website, AWS EC2
* **Summary:** In two days built a web dashboard that showed events that had the highest predicted fraud as well as cost (downside) to the company to help client staff use their anti-fraud time more effectively

**Ride Sharing App Churn Prediction**
* **Tools used:** logistic regression, confusion matrices, profit curves (LTV vs CAC), ROC
* **Summary:** Prioritized optimizing recall instead of accuracy as downsides of incorrect predictions had the biggest impact

**Predict Sale Price of Used Heavy Machinery at Auction**
* **Tools Used:** linear regression, feature engineering, RMSLE
* **Summary:** First attempt at modeling and feature engineering, log transformation of the sale price had a huge impact on lowering the error rate
