---
layout: post
title: Iceberg vs Ship Classifier Contest
subtitle: Hosted by Kaggle and Statoil
image: /img/iceberg/iceberg_icon.png
tags: [Classifier, Neural Networks, ConvNet, Keras, Tensorflow]
---

<p align="center">
<img src="/img/iceberg/vigilant-iceberg_explanation_graphic_2.png" width="512" />
</p>

Use data from Kaggle and Statoil to make a classifier that predicts if something is an iceberg or a ship.

**The data provided is:**
* unique identifier
* two bands of radar data
* satellite incidence angle
* is_iceberg label

**Scoring:** Lowest measured error in predictions on final evaluation set. (log loss)

_Additionally because so much of Kaggle contests revolves around impractical ensembles of models an additional self-imposed constraint of using only a single model was followed. (Which may have been too restrictive.)_

**Example:** [Beluga 2nd Place Contestant](https://www.kaggle.com/c/statoil-iceberg-classifier-challenge/discussion/48294) solution model complexity is more than 100x greater than my solution.

## Results
<p align="center">
<img src="/img/iceberg/log_scores_a.png" width="512" align="middle">
</p>

###### **_Scores above 1.0 were clipped as those scores weren't remotely competitive and skewed the distribution even further. Then Log10 transformation of scores was performed because initial distribution was [log normal.](/img/iceberg/normal_scores_a.png)_**

**Accuracy:** >=95%

**Measured error for final ranking:** 0.1491

**Placement:**  372/3,343 (top 11%)

This was my first Kaggle competition. Next time I would increase my arbitrary ensemble limitation to perhaps 3 models. This may help feature engineering add some predictive value.

I learned a lot from this project and I'm looking forward to my next challenge.

[Technical details here](https://github.com/pixelatedbrian/vigilant-iceberg/blob/master/README.md)

## Project Summary:
* Keras/Tensorflow GPU
* single convolutional neural network for classification
* utilized AWS EC2 instance for compute
* 6 week project duration
