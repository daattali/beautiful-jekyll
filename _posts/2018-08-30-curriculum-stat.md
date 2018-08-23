---
layout: post
title: Our curriculum, Part 1
subtitle: Statistics stream
---

Main difficulty is distilling statistical concepts down to a year’s worth of study, to fit amongst other important data science streams like machine learning. We did this by considering the most fundamental concepts, and spinning it in a way that allows them to dig deeper when they need to.
Here is how we arranged concepts into a statistics stream.

Our foundation:

* 551: “probability-first” philosophy. Not only how to calculate probabilities and distributional quantities like the mean and median, but what does iid data look like coming from this distribution? We put special emphasis on conditional distributions, and using that for prediction. This exposes learners to the concept of irreducible error: the inability to make a perfect prediction, even when we know the true data generating process.
* 552: This course addresses how to deduce aspects of the data generating process from data, and how certain we can be. The focus for this course is univariate. Here is where we introduce the notion of parametric assumptions, such as Gaussian, and their usefulness in interpretation, the bias-variance tradeoff, and especially their use in describing uncertainty. At the heart of this course is the frequentist paradigm, emulated through simulation and bootstrap as a data-approximation to simulation. We also introduce the notion of hypothesis testing here, too.
* 561: The focus is still inference on a response variable, but this time, conditional on observing some predictors. This is different from our machine learning branch that stems away here and focusses on how to best fit a curve through data: this Regression I course focuses on *how* predictors influence the response, with a special focus on linear regression.

We have four more “specialty” courses that stem from this foundation:

* 562: This course focusses on special cases of regression — and why taking these special cases into consideration is important. Examples include GLM’s, survival analysis, missing data, and others.
* 553: This course introduces the Bayesian paradigm of statistical analysis, returning to considerations from 552 and 561.
* 554: This course focusses on using statistical tools in the context of experiments.
* 574: This course focusses on the non-iid case: why it’s important to consider serial and spatial dependence, and some key ways of dealing with it.
