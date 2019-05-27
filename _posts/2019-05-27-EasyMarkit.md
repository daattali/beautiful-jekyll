---
layout: post
title: Winning the EasyMarkit AI Hackathon
category: blog
---

On April 6, 2019, EasyMarkit hosted their first Hackathon in Vancouver where teams were asked to offer an AI solution to improve patient communication. My team Sigma (Bailey Lei, Alex Pak, Betty Zhou) was awarded first place based on the accuracy of our model in predicting communication response from patients.

##### About EasyMarkit AI Hackathon

EasyMarkit is a company that focuses on developing automated patient communication software specializing in dentistry. The company aimed to use the hackathon to challenge participants to come up with AI solutions to better predict communication from patients. The event was hosted at EasyMarkit’s office in downtown Vancouver. Owen Ingraham, CTO at EasyMarkit, and his team did a fantastic job of hosting the event and our team was extremely impressed by the culture at EasyMarkit.

##### Coming up with the winning solution:

While I cannot disclose the detail about the data set, I do want to share the story of how our team came up with the winning solution.

The main criteria for this hackathon was on classification accuracy, and to make it more challenging, only one submission was allowed per team. This was really well thought out by EasyMarkit as it forced teams to make a robust model that generalized well with unseen data. One of the nice things about this competition was working with real data, but real data can be pretty messy and requires tons of data cleaning. We decided on using Python and Jupyter notebook for this hackathon but could have easily used R as well. Prior to the hackathon, I already set-up a Jupyter notebook running on Google Cloud that allowed us to run multiple Jupyter notebook instances on the data set simultaneously. We spent about an hour doing EDA and background research related to the data set. The data set was relatively small, but there were over 15 features. There was time series in the data and extracting features from the time series improved our model significantly.

We trained the model with all default features initially, then removed irrelevant and nonsensical features, such as clinic ID and patient ID. You might be wondering why did we not remove these features prior to training. Well, we believed that we should still test the model on all features and see how it performs. Often, data might be mislabeled or some form of data leakage might occur. Surprisingly, our model actually showed that clinic ID was a significant contributor to the model. However, after performing more EDA and retaining the model, we decided to drop it as it did not make sense to incorporate it into the model. We did cross-validation and initially did a few models that ranged from logistic regression to random forest, but ultimately decided a tree based learning algorithm - Light Gradient Boosting Machine (LightGBM). The accuracy from LightGBM was about the same as XGBoost, but its training time was a lot faster. We tried to perform random grid search during hyperparameter tuning, but it took too long, and given the time constraint, tuning it manually was a better idea. We ended up selecting the parameter that gave us the lowest approximation error as opposed to the highest train or test accuracy. This was quite a difficult decision for our team since we were only allowed one submission. However, using what we learned in machine learning in MDS, the choice was pretty clear: use the model with the lowest approximation error for better generalization. When the results were announced, the reported test accuracy was within 0.1% of what our model predicted with the validation set.

Overall, our team learned a lot from the hackathon and winning it was a pretty awesome experience. It was great to witness our team’s ability to perform under pressure. Under pressure, we acknowledged the importance of taking breaks to maintain effective performance.
