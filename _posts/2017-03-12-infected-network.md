---
layout: post
published: true
title: Infected Network
date: 2017/03/12
---

>One hundred computers are connected in a 10x10 network grid, as below. At the start exactly nine of them are infected with a virus. The virus spreads like this: if any computer is directly connected to at least 2 infected neighbours, it will also become infected.
>
>Will the virus infect all 100 computers? 

<!--more-->

([The Guardian](https://www.theguardian.com/science/2017/mar/13/can-you-solve-it-pi-day-puzzles-that-will-leave-you-pie-eyed))

## Solution:

Think of the 10x10 grid as situated within a larger grid with immune nodes surrounding it on all sides. And call the "fringe" of a state of infection the number of edges connecting any infected node to an uninfected one.  When a new node gets infected by two infected neighbors, the fringe gets reduced by the two edges connecting it to those neighbors, and increased by at most the two other edges from that new node. So the fringe of a state of infection can never increase with any new infection.  An initial infection state for nine infected nodes in a 10x10 grid can have a fringe of no more than 4 edges per node times 9 nodes, or 36. And the fringe of a fully infected 10x10 grid is 40. Therefore, no nine infected nodes can infect the entirety of a 10x10 grid.

<br>
