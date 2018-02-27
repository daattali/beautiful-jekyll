---
layout: post
title: Iceberg vs Ship Classifier Contest
subtitle: Hosted by Kaggle and Statoil
image: /img/iceberg/iceberg_icon.png
tags: [Classifier, Neural Networks, ConvNet, Keras, Tensorflow]
---

<img src="/img/iceberg/vigilant-iceberg_explanation_graphic_2.png" width="512" style="margin:0px auto;display:block"/>

Use data from Kaggle and Statoil to make a classifier that predicts if something is an iceberg or a ship.

**The data provided is:**
unique identifier, two bands of radar data in log format, satellite incidence angle, is_iceberg label

**Scoring:** Lowest log loss on predicted values on a validation set.

_Additionally because so much of Kaggle contests revolves around impractical ensembles of models an additional self-imposed constraint of using only a single model was followed. (Which may have been too restrictive.)_

**Example:** [Beluga 2nd Place Contestant](https://www.kaggle.com/c/statoil-iceberg-classifier-challenge/discussion/48294) used a weighted average of ~100 ensembled N.N. models.

## Results
<img src="/img/iceberg/log_scores_a.png" width="512" align="middle">

###### **_Scores above 1.0 were clipped as those scores weren't remotely competitive and skewed the distribution even further. Then Log10 transformation of scores was performed because initial distribution was [log normal.](/img/iceberg/normal_scores_a.png)_**

On the final leader board I placed 372nd out of 3,343 teams, or roughly top 11%. This was my first Kaggle competition. Next time I would increase my arbitrary ensemble limitation to perhaps 3 models. This may help feature engineering add some predictive value.

I learned a lot from this project and I'm looking forward to my next challenge.

Many more details [here](https://github.com/pixelatedbrian/vigilant-iceberg/blob/master/README.md)

## Project Overview:
<img src="/img/iceberg/model_flowchart_2.png" width="512" align="middle">

* Used AWS p2.xlarge instance running Ubuntu 16.04 with Nvidia K80 GPU
  + Created custom AWS AMI image for faster deployment of spot instances
  + [AMI Details Here](https://pixelatedbrian.github.io/2018-01-12-AWS-Deep-Learning-with-GPU/)
  + Used Keras with Tensorflow CUDA/CUDNN GPU acceleration
* ~10 different convolutional networks evaluated
* 2 Transfer learning models evaluated, Inception v3 & VGG 17
  + Experimentation found that transfer learning models massively overfit
  + Hypothesize that the small 'image' size caused issues here
  + Also the shapes/textures/features for the image nets really didn't apply to the data provided
  + Finally as there were 2 channels of radar data a third channel had to be synthesized in order to pretend to be the 3rd color channel for the RGB ConvNets
* ~6 newly trained architectures evaluated [source](https://github.com/pixelatedbrian/vigilant-iceberg/blob/master/src/model_zoo_v2.py)
  + Final submission only used 2 channels of 'color'
  + Training from scratch enabled the networks to learn specific features of the radar data
  + Multiple transformations were attempted as well as blurring and noise cropping. The one with the most apparent potential was a derivative edge detection algorithm.
  + As the image transformations increased error hypothesize that a few networks trained on transformations individually with their predictions then ensembled would perform better.
  + Custom models trained tended to take about 15min per run to train on AWS p2.xlarge
* Most time and effort were spent on:
  + Evaluating different model architecture performance
  + Feature engineering/transformations
  + Hyperparameter tuning of more promising models
* Model 2 from model_zoo_v2.py ultimately had the best performance
  + Used script to perform automated randomized hyperparameter grid search
  + Predictions from model2 got a final leader board error of 0.1491
* Ideas to try next time:
  + Increase arbitrary model limit to 3 to allow slight ensembling
  + Interested in trying to augment data to be predicted then see if an ensemble of those predictions perform better than simply the normal single prediction
