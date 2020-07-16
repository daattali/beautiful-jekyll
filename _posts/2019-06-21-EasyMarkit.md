---
layout: post
title: Winning the EasyMarkit AI Hackathon
subtitle: by Bailey Lei
category: blog
---

On April 6, 2019, [EasyMarkit](https://www.easymarkit.com/) hosted their first Hackathon in Vancouver where teams were asked to offer an AI solution to improve patient communication. My team ([Bailey Lei](https://www.linkedin.com/in/baileylei), [Alex Pak](https://www.linkedin.com/in/pakalexh), [Betty Zhou](https://www.linkedin.com/in/bettybhzhou)) was awarded first place based on the accuracy of our model in predicting communication response from patients.

##### About the EasyMarkit AI Hackathon

EasyMarkit is a Vancouver-based company that focuses on developing automated patient communication software specializing in dentistry. The hackathon challenged participants to predict whether or not patients will respond to communications like appointment reminders. The event was hosted at EasyMarkit's office in downtown Vancouver, and ran from 9am to 5pm. Owen Ingraham, CTO at EasyMarkit, and his team did a fantastic job of hosting the event and our team was extremely impressed by the culture at EasyMarkit.

##### Our solution

Submissions were evaluated on classification accuracy when applied to an unseen test data set. One of the nice things about this competition was working with real data, but real data can be pretty messy and requires tons of data cleaning. We decided on using Python and Jupyter notebook for this hackathon but could have easily used R as well. Prior to the hackathon, we set-up a Jupyter notebook running on Google Cloud that allowed us to run multiple Jupyter notebook instances on the data set simultaneously. We spent about an hour doing EDA and background research related to the data set. The data contained some time series variables, and extracting features from the time series improved our model significantly.

We trained the model with all default features initially, then removed irrelevant and nonsensical features, such as patient ID. Other variables, like clinic ID, were tricky to handle. In this competition, we had access to the test set features that we would use for our final predictions. While clinic ID was a significant contributor to the model in training/validation, we noticed that the test data came from a different set of clinics, and so we decided to remove it from our model. 

We evaluated several models such as logistic regression and random forest, but ultimately settled on Light Gradient Boosting Machine (LightGBM). The accuracy from LightGBM was about the same as XGBoost, but its training time was a lot faster. We tried to perform random grid search during hyperparameter tuning, but it took too long, and given the time constraint, tuning it manually worked better. We ended up selecting the hyperparameters that gave us the lowest approximation error (gap between train and validation) as opposed to the lowest validation error. This was quite a difficult decision for our team since we were only allowed one submission. However, the model with the lowest validation error had a very high approximation error, which felt too risky, so we went with a model with a slightly higher validation error and much lower approximation error. When the results were announced, the reported test accuracy was within 0.1% of what our model predicted with the validation set.

Overall, our team learned a lot from the hackathon and winning it was a pretty awesome experience. It was great to witness our team's ability to perform under pressure. One strategy we employed under time pressure was taking regular breaks to improve overall performance.


--------

[Bailey Lei](https://www.linkedin.com/in/baileylei) is a current student in the 2018-2019 MDS cohort.
