---
layout: page
permalink: /Shape_analysis/
title: Shape analysis
show-avatar: True
---

Below are displayed movies of the shape analysis tools used in our [paper](https://hal.archives-ouvertes.fr/hal-03362573) presented at the PIPPI workshop 2021.

### Shape analysis pipeline for fetal brain MRI

This shape analysis pipeline is specifically tailored to the challenges fetal MRI. Using diffeomorphic image registration, fetuses are compared to an age-machted template brain. Age differences between fetuses are smooth out. Using PCA, a mean and variance analysis is performed on the subjects deformations to extract the modes of deformation that best characterize the anatomical variability of the dataset.

<img src="/assets/img/shape_analysis_pipeline.gif" alt="drawing" width="700"/>

### Geodesic trajectory of a healthy template brain from 26 to 38 gestational weeks

This is the continuous trajectory of healthy brain growth used as reference.

[Source of the healthy template brains used to compute the trajectory.] (http://crl.med.harvard.edu/research/fetal_brain_atlas/) 


<img src="/assets/img/gif_regression_geodesique.gif" alt="drawing" width="500"/>

____

### An example of deformation mode obtained on a dataset of fetuses with Corpus Callosum Agenesis

Second mode of deformation obtained by PCA on the initial vector fiels, between σ = 0 and σ = 4. This movie shows the deformation of an average healthy anatomy at 31 weeks of gestation towards the anatomy characterizing Corpus Callosum Agenesis. 

<img src="/assets/img/ezgif.com-gif-maker(2).gif" alt="drawing" width="190"/><img src="/assets/img/ezgif.com-gif-maker(3).gif" alt="drawing" width="190"/><img src="/assets/img/ezgif.com-gif-maker(1).gif" alt="drawing" width="175"/>

<img src="/assets/img/cor2.gif" alt="drawing" width="210"/><img src="/assets/img/sag2.gif" alt="drawing" width="210"/><img src="/assets/img/ax2.gif" alt="drawing" width="200"/>


