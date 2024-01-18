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

* Do not remove this line (it will not be displayed)
{:toc}

# Summary
Something I noticed in the Combustion organization at GE is that we had terabytes of time series data, but we only actually used steady state sections of that data. Seeing this, I endeavored to create a Python tool which would comb through the existing data GE had and locate additional steady state points that we could use to increase our confidence in characterizing our combustor performance. We already paid for the data, why not get our money's worth?