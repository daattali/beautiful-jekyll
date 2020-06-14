---
layout: post
title: Motivating Beam Search
subtitle: Problems with the decoder on an nmt system
cover-img: /assets/img/path.jpg
tags: [nmt, nlp]
---
## Training Auto-regressive model
Feeding the correct output and learning to decode from it.

## Greedy Decoding

## Exhaustive Search Decoding
V^t possible partial translation. Far too expensive.

## Beam Search
Keep track of K most probable partial translations(aka hypothesis). Score of a hypothesis is just its log probability

A Hypothesis $$y_{1}, \ldots, y_{t}$$ has a score which is its log probability:

$$
\operatorname{score}\left(y_{1}, \ldots, y_{t}\right)=\log P_{\mathrm{LM}}\left(y_{1}, \ldots, y_{t} | x\right)=\sum_{i=1}^{t} \log P_{\mathrm{LM}}\left(y_{i} | y_{1}, \ldots, y_{i-1}, x\right)
$$

* Scores are all negative and higher score is better
* We search for high scoring hypothesis, tracking top k on each step
* Not guarranteed to find the optimal solution, but it is much more efficient
