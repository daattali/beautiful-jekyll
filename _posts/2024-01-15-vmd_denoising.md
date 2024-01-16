---
layout: post
title: Denoising Time Series Data with Variational Mode Decomposition In Python
subtitle: A Precursor to Steady State Detection
gh-repo: cormazz/vmd-denoising
gh-badge: [star, fork, follow]
tags: [python, vmd, denoising, time-series,]
comments: true
author: Corrado R. Mazzarelli
---

{: .box-success}
This article explores separating parts of a signal based on the dominant frequency in that part of the signal. All the material used to create this is within the GitHub repository linked above. **I strongly encourage you to explore the [resources](#resources) linked below.** They have guided me on my engineering journey and it is truly some remarkable information, all available for free. This article will be written with the assumption that you are familiar with Python, and have watched the reference videos on the discrete Fourier transform, the fast Fourier transform, the Uncertainty Principle, and clustering algorithms. 

* Do not remove this line (it will not be displayed)
{:toc}

# Summary
Something I noticed in the Combustion organization at GE is that we had terabytes of time series data, but we only actually used steady state sections of that data. Seeing this, I endeavored to create a Python tool which would comb through the existing data GE had and locate additional steady state points that we could use to increase our confidence in characterizing our combustor performance. We already paid for the data, why not get our money's worth?

After researching methods for steady state detection, I stumbled across variational mode decomposition (VMD) as a method for preprocessing real-world, noisy data, before proceeding with the steady state detection. 

In sum, the paper [(Chen et al.)](#the-steady-state-detection-paper) describes a technique for using Bayesian optimization to choose the optimal hyperparameters for VMD such that the denoised signal captured a large amount of the variation of the original noisy signal, while having less Gaussian noise. I explored the optimization understand the effects of the hyperparameters and the ultimate results. 

I created two traces of representative data: Pressure and Temperature, using a script which allows me to draw the trace in MS Paint, then load it into Python, give it a time x-axis, and optionally add noise and outliers. For instance, below is the raw pressure trace as a PNG image. 

{% include bp.vmd_denoising/paint_drawing_pressure_trace.png %}

Here are the plots of the generated signals. 

{% include bp.vmd_denoising/generated_data.html %}

{: .box-note}
**Note:** Try moving the plot around, zooming in, and clicking on legend entries. If you like these plots, look into [Plotly](https://plotly.com/python/) which allows you to save interactive plots as html files.

From this point, the two primary hyperparameters of VMD, &alpha and k, were varied. &alpha is the bandwidth penalty, and k is the number of modes. Increasing &alpha makes it so that each mode covers a smaller frequency band, and increasing k decomposes the original signal into more modes (see below for more details). 


# Introduction

## Context


## Personal History and Motivation


## Interesting Concepts


# Python Libraries

## Numpy
[Numpy](https://numpy.org/) is a powerhouse in scientific Python analysis, and needs no introduction.

## Plotly
[Plotly](https://plotly.com/python/) is a widely used plotting library which enables easy interactive plots which can be saved as interactive. They are the plots you'll see embedded here.

## Plotly-Resampler
[Plotly-resampler](https://github.com/predict-idlab/plotly-resampler) is a Python library that utilizes Dash to create a dynamically updating Plotly chart that only displays a limited number of data points to ensure the plot doesn't become bloated and slow. This was very useful for the GE implementation, since there were about a billion data points to plot. A limitation of plotly-resampler is that it requires an active Python kernel, so the plots cannot be saved as interactive.

## Tqdm
[Tqdm](https://tqdm.github.io/) is just a progress bar library. I like to use it to let me know how long my scripts are taking. 

{: .box-note}
**Note:** An environment.yml file is included in the GitHub repository to allow you to recreate a functional Anaconda environment.

# Code Implementation

## Generate Data

## Define Inputs


## Load the Data

## Plot the Original Data

### Plotly


# Conclusion


# References

## The Steady State Detection Paper
This is the paper I was reading to learn about steady state detection where I found this method for first denoising the data. 
[Shuo Chen, Cong Yu, Yukun Zhu, Wei Fan, Haiquan Yu, Tihua Zhang, (2024). NOx formation model for utility boilers using robust two-step steady-state detection and multimodal residual convolutional auto-encoder, Journal of the Taiwan Institute of Chemical Engineers, Volume 155, 105252, ISSN 1876-1070, https://doi.org/10.1016/j.jtice.2023.105252.](https://www.sciencedirect.com/science/article/pii/S1876107023005795)

## The Original VMD Paper
This is the paper that originally proposed and explained VMD. 
[Zosso, Dominique & Dragomiretskiy, Konstantin. (2013). Variational Mode Decomposition. IEEE Transactions on Signal Processing. 62. 10.1109/TSP.2013.2288675.](https://ww3.math.ucla.edu/camreport/cam13-22.pdf)

