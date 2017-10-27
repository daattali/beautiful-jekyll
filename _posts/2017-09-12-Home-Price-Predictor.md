---
layout: post
title: Housing Price Regressor
subtitle: Ames, IA Data Set
gh-repo: https://github.com/pixelatedbrian/sturdy-umbrella
gh-badge: [star, fork, follow]
tags: [regression, housing, price prediction, Galvanize]
---

While attending Galvanize's immersive data science program we covered many different types of regressors. There wasn't really enough time to delve into the details though. This project was inspired by a meetup at Zillow where the presenter, a Senior Data Scientist at Zillow, did a presentation on the Ames, IA home price dataset. This dataset is similar to the seminal Boston home price data set but the Ames information is much more recent and comprehensive.

Currently the RMSLE of my model is ~0.1203 on the verification data set. There is a ongoing Kaggle competition using this data set and currently that leaderboard #1 position is at 0.10567. My model is getting close. I haven't yet run my model on the Kaggle dataset but it appears that they have filtered the sample some, as there are less rows than in my unmodified dataset.

I've kept a [log](https://github.com/pixelatedbrian/sturdy-umbrella/blob/master/src/scores.txt) of the feature additions, model changes, etc. Interestingly the error rate seems to have minimized just below 0.14 on the whole dataset. (multiple kfold train/test splits are done on each iteration, with the evaluation on the final test set occuring once every 10 revisions or so, to try to avoid overfitting the final evaluation set.)

I think currently some of the models that are being fit are overfitting because of the number of features currently being used. Currently there are ~300 features although a lot of those are dummified categorical features. (boolean flags)

This is currently a work in progress.
