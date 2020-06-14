---
layout: post
title: Evolving landscape of Machine Translation
subtitle: High level overview of the primary techniques for machine translation over time
tags: [nlp, nmt]
---

Neural Machine translation directly calculates
... a given wire happens to be carrying "$$\lvert 0\rangle$$."
By that we mean that it's carrying the linear combination


Conditional language modelling is currently the most popular machine translation technique. It involves calculating the probability for each term in the sequence conditioned on the input sentence and previous outputs.

$$
P(y | x)=P\left(y_{1} | x\right) P\left(y_{2} | y_{1}, x\right) P\left(y_{3} | y_{1}, y_{2}, x\right) \ldots P\left(y_{T} | y_{1}, \ldots, y_{T-1}, x\right)
$$
