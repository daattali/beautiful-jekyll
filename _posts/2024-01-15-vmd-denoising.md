---
layout: post
title: Denoising Time Series Data with Variational Mode Decomposition In Python
subtitle: A Precursor to Steady State Detection
gh-repo: cormazz/vmd-denoising
gh-badge: [star, fork, follow]
tags: [python, vmd, denoising, time-series]
comments: true
author: Corrado R. Mazzarelli
---

# This is a Work-In-Progress -- Last Updated 1/20/24

* Do not remove this line (it will not be displayed)
{:toc}

# Summary

I created two traces of representative data: _pressure_ and _temperature_, using a script which allows me to draw the trace in MS Paint, then load it into Python, give it a time x-axis, and optionally add noise and outliers. For instance, below is the raw _pressure_ trace as a PNG image. You might have to zoom in to see it; the trace is one pixel thick. 

![Pressure Trace](https://corradomazzarelli.com/assets/blog_posts/bp.vmd_denoising/paint_drawing_pressure_trace.png){: .mx-auto.d-block :}

Here are the plots of the generated signals. Notice how the _pressure_ trace in the plot matches the image above.

### Figure 1: Experimental Data Plot
[Standalone Figure](https://corradomazzarelli.com/assets/blog_posts/bp.vmd_denoising/generated_data.html)
{% include bp.vmd_denoising/generated_data.html %}

{: .box-note}
**Note:** Try moving the plot around, zooming in, and clicking on legend entries. If you like these plots, look into [Plotly](https://plotly.com/python/) which allows you to save interactive plots as .html files. You can also click on the _Standalone Figure_ link to get a larger version of the figure. 

From this point, α and _k_, the two primary hyperparameters of VMD,  were varied. α is the bandwidth penalty, and _k_ is the number of modes. Increasing α makes it so that each mode covers a smaller frequency band, and increasing _k_ decomposes the original signal into more modes (see below for more details). 

The original paper used VMD to decompose the signal into _k_ modes, and then added together a subset of those modes that captured the majority of the variance of the original signal to create a reconstructed signal. An example of this signal reconstruction is shown in [Figure 2](#figure-2-example-of-decomposed-and-reconstructed-signal) below.

### Figure 2: Example of Decomposed and Reconstructed Signal
[Standalone Figure](https://corradomazzarelli.com/assets/blog_posts/bp.vmd_denoising/noisy_pressure.alpha_4000.k_5.individual_scatter.html)
{% include bp.vmd_denoising/noisy_pressure.alpha_4000.k_5.individual_scatter.html %}

Notice how the first mode captures the majority of the low frequency trend in the data (does not change very fast/sporadically), whereas the additional modes capture higher frequency, lower magnitude variations in the data.

The reconstructed signal was then compared to the original signal using the following equation for the signal to noise ratio (SNR).

$$
\text{SNR} = 10 \log_{10} \left( \frac{\sum_{i=1}^{N_f} f^2}{\sum_{i=1}^{N_f} (f - f_{\text{rec}})^2} \right)
$$

Note that this SNR metric penalizes any difference from the original signal. Thus, when the paper uses this SNR metric as the objective function when optimizing the VMD hyperparameters, the optimization will converge to the hyperparameters which result in a reconstructed signal that is most similar to the original, noisy signal, possibly capturing the noise in the reconstruction. 

In the case of the paper, the true noiseless signal was unknown. However, for this study, the true signal was available. Thus, the following heatmaps of SNR vs. varying VMD hyperparameters were created. 

### Figure 3: Noisy Pressure SNR Heatmap
![Noisy Pressure 'Signal to Noise Ratio' Heatmap](https://corradomazzarelli.com/assets/blog_posts/bp.vmd_denoising/noisy_pressure.snr_heatmap.png){: .mx-auto.d-block :}

On the left, the reconstructed signal was compared to the original noisy signal (as performed in the paper), and on the right the reconstructed signal was compared to the original clean signal to see the true denoising potential of the methodology. As expected, the estimated SNR was maximized at a value of 28.41 with low α and _k_ parameters, (100 and 2 respectively), which corresponds to limited change from the noisy signal. This is seen in the left side of [Figure 3](#figure-3-noisy-pressure-snr-heatmap) where the yellow appears in the top left of the heatmap. The SNR of the reconstructed signal compared to the true noiseless signal is maximized at a value of 43.95 with α of 10,000 and _k_ of 8.  Thus, the methodology utilized in [the paper](#the-steady-state-detection-paper) is overly conservative in noise removal.

The following plot shows the comparison between [the paper's](#the-steady-state-detection-paper) optimal reconstructed signal and the true optimal reconstructed signal. 


# Introduction

## Context
Something I noticed in the Combustion organization at GE is that we had terabytes of time series data, but we only actually used steady state sections of that data that were manually identified on the day of the test. Seeing this, I endeavored to create a Python tool which would comb through the existing data GE had and locate additional steady state points that we could use to increase our confidence in characterizing our combustor performance. We already paid for the data; why not get our money's worth?

After researching methods for steady state detection, I stumbled across variational mode decomposition (VMD) as a method for preprocessing real-world, noisy data, before proceeding with the steady state detection. 

In sum, the paper [(Chen et al.)](#the-steady-state-detection-paper) describes a technique for using Bayesian optimization to choose the optimal hyperparameters for VMD such that the denoised signal captures a large amount of the variation of the original noisy signal, while having less Gaussian noise. I explored the optimization to understand the effects of the hyperparameters and the ultimate results. 

## Interesting Concepts

### Variational Mode Decomposition

Variational Mode Decomposition (VMD) is a powerful signal processing technique that aims to decompose a complex signal into a sum of simpler oscillatory modes. Unlike traditional methods such as Fourier analysis, VMD does not rely on predefined basis functions. Instead, it formulates the decomposition as an optimization problem, seeking modes that are both sparse and well-localized in the time-frequency domain. This approach makes VMD particularly effective for extracting hidden patterns and structures in signals with non-stationary and nonlinear characteristics.

### Signal to Noise Ratio

The Signal-to-Noise Ratio (SNR) is a fundamental concept in signal processing and communication engineering. It quantifies the ratio of the power of a signal to the power of background noise. In other words, SNR provides a measure of how much the desired signal stands out from the surrounding noise. A higher SNR indicates a clearer and more reliable signal, making it easier to distinguish and interpret. SNR is a crucial metric in various applications, including telecommunications, audio processing, and image analysis, where the fidelity of the signal is of paramount importance.

### Bayesian Optimization

Bayesian Optimization is an optimization technique commonly used for optimizing complex and computationally expensive functions. Unlike traditional optimization methods, Bayesian Optimization leverages probabilistic models to estimate the objective function and its uncertainty. By iteratively selecting the most promising points to evaluate, based on the current model, it efficiently navigates the search space to find the optimum with minimal function evaluations. Bayesian Optimization is particularly valuable in scenarios where each function evaluation is costly, such as in hyperparameter tuning for machine learning algorithms or optimizing parameters in scientific experiments.



# Methodology & Results

# Conclusion

# Python Libraries

## VMDpy
[vmdpy](https://pypi.org/project/vmdpy/) is a library containing an implementation of VMD based off of the original paper by [Dragomiretskiy & Zosso](#the-original-vmd-paper).

## Numpy
[Numpy](https://numpy.org/) is a powerhouse in scientific Python analysis, and needs no introduction.

## Plotly
[Plotly](https://plotly.com/python/) is a widely used plotting library which enables easy interactive plots which can be saved as interactive. They are the plots you'll see embedded here.

## Tqdm
[Tqdm](https://tqdm.github.io/) is just a progress bar library. I like to use it to let me know how long my scripts are taking. 

{: .box-note}
**Note:** An environment.yml file is included in the GitHub repository to allow you to recreate a functional Anaconda environment.

# References

## The Steady State Detection Paper
This is the paper I was reading to learn about steady state detection where I found this method for first denoising the data. 
[Shuo Chen, Cong Yu, Yukun Zhu, Wei Fan, Haiquan Yu, Tihua Zhang, (2024). NOx formation model for utility boilers using robust two-step steady-state detection and multimodal residual convolutional auto-encoder, Journal of the Taiwan Institute of Chemical Engineers, Volume 155, 105252, ISSN 1876-1070, https://doi.org/10.1016/j.jtice.2023.105252.](https://www.sciencedirect.com/science/article/pii/S1876107023005795)

[Another Link](https://www.researchgate.net/publication/376134958_NOx_formation_model_for_utility_boilers_using_robust_two-step_steady-state_detection_and_multimodal_residual_convolutional_auto-encoder)

## The Original VMD Paper
This is the paper that originally proposed and explained VMD. 
[Zosso, Dominique & Dragomiretskiy, Konstantin. (2013). Variational Mode Decomposition. IEEE Transactions on Signal Processing. 62. 10.1109/TSP.2013.2288675.](https://ww3.math.ucla.edu/camreport/cam13-22.pdf)

