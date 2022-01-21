---
layout: page
permalink: /Shape_analysis/
title: Shape analysis
show-avatar: True
---
Below are displayed movies of the shape analysis tools described in our [paper](https://hal.archives-ouvertes.fr/hal-03362573) presented at the PIPPI workshop 2021.

### Shape analysis pipeline for fetal brain MRI

This shape analysis pipeline is specifically tailored to the specificities of fetal MRI. Using diffeomorphic image registration, fetuses are compared to an age-machted template brain. Age differences between fetuses are corrected. Using PCA, a mean and variance analysis is performed on the subjects deformations to extract the modes of deformation that best characterize the anatomical variability of the dataset.

<img src="/assets/img/output-onlinegiftools(23).gif" alt="drawing" width="800"/>

____

<details>
  <summary><font size="4" color="#FF0000">Click here to display the reference trajectory of healthy brain growth during gestation</font></summary>
  
This is the geodesic trajectory of healthy brain growth (from 27 to 38 gestational weeks) used as reference to compute a distance from normality. Corresponds to the red curve.

 <a href="http://crl.med.harvard.edu/research/fetal_brain_atlas/"> <font size="1"> Source of the healthy template brains used to compute the trajectory </font>  </a>

<img src="/assets/img/geodesic_regression.gif" alt="drawing" width="400"/>

</details>


<details>
  <summary><font size="4" color="#00008B">Click here to display an example of parallel transport along the reference trajectory</font></summary>
  
Registration computes the distance between the healthy template at age 34 weeks and a subject's brain at age 34 weeks (green arrow). Parallel transport (blue arrows) transports the computed deformation to any time point along the red curve. Combined with geodesic shooting, we apply the reference growth dynamic to the subject's brain from 27 to 38 gestational weeks. The movie below illustrates how this brain, only observed at 34 weeks, would evolve between during gestation (under the hypothesis that his growth rate is comparable to that of the healthy template).

<img src="/assets/img/parallel_transport3.gif" alt="drawing" width="400"/>

</details>

____

### An example of deformation mode obtained on a dataset of fetuses with Corpus Callosum Agenesis

Second mode of deformation obtained by PCA on the initial vector fiels, between σ = 0 and σ = 4. This movie shows the deformation of an average healthy anatomy at 31 weeks of gestation towards the anatomy characterizing Corpus Callosum Agenesis. 

<img src="/assets/img/output-onlinegiftools(18).gif" alt="drawing" width="160"/>&nbsp; &nbsp; &nbsp; &nbsp; <img src="/assets/img/output-onlinegiftools(19).gif" alt="drawing" width="160"/>&nbsp;&nbsp;  &nbsp; &nbsp; <img src="/assets/img/output-onlinegiftools(17).gif" alt="drawing" width="145"/>

<img src="/assets/img/cor2.gif" alt="drawing" width="190"/><img src="/assets/img/sag2.gif" alt="drawing" width="190"/><img src="/assets/img/ax2.gif" alt="drawing" width="190"/>


