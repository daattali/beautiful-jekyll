---
layout: post
title: Visualizing & Animating Equilibrium Combustion Products vs. Equivalence Ratio 
subtitle: Using Cantera and Plotly Animations
gh-repo: cormazz/vmd-denoising
gh-badge: [star, fork, follow]
tags: [python, cantera, combustion, Georgia Tech, plotly, animation]
comments: true
author: Corrado R. Mazzarelli
---

* Do not remove this line (it will not be displayed)
{:toc}

# Summary

### Figure 1: Equilibrium Composition Mole Fraction Animation
[Standalone Figure](https://corradomazzarelli.com/assets/blog_posts/bp.equilibrium_cantera/HP_mole_fraction_animation.html)
{% include bp.equilibrium_cantera/HP_mole_fraction_animation.html %}

### Figure 2: Equilibrium Combustion 
[Standalone Figure](https://corradomazzarelli.com/assets/blog_posts/bp.equilibrium_cantera/HP.html)
{% include bp.equilibrium_cantera/HP.html %}

# Introduction

## Context
This was a homework assignment for the class AE6766 at Georgia Tech, but I wanted to hone my visualization skills using Plotly so I put a little extra effort into it. 

## Interesting Concepts

### Equilibrium Gas Composition

In the realm of thermodynamics, equilibrium gas composition refers to the distribution of chemical species in a gas mixture when the system has reached thermodynamic equilibrium. At this state, there is no net change in the concentrations of various species, and the system's properties remain constant over time. The equilibrium gas composition is determined by factors such as temperature, pressure, and the initial composition of the gas mixture.

Understanding equilibrium gas composition is crucial in various fields, including chemistry, chemical engineering, and environmental science. It helps predict the distribution of different molecules in a gas phase under specific conditions, allowing scientists and engineers to optimize processes and design systems with greater efficiency.

### Equivalence Ratio

The equivalence ratio is a parameter used in combustion engineering to describe the ratio of the actual fuel-to-oxidizer mixture to the stoichiometric fuel-to-oxidizer ratio required for complete combustion. It is a key factor in determining the efficiency and characteristics of combustion processes. The equivalence ratio influences whether a mixture is fuel-rich, stoichiometric, or fuel-lean.

An equivalence ratio equal to 1 indicates a stoichiometric mixture, where all the fuel and oxidizer react completely. Values greater than 1 signify a fuel-rich mixture, while values less than 1 indicate a fuel-lean mixture. Engineers use the equivalence ratio to optimize combustion processes, ensuring efficient energy release and minimizing the production of pollutants.

### Cantera

Cantera is an open-source software suite used for solving problems that involve chemically reacting systems. It is particularly powerful in the fields of chemical kinetics, thermodynamics, and transport processes. Cantera provides a set of tools and libraries for simulating chemical reactions, equilibrium calculations, and the behavior of reacting flows.

Engineers and researchers use Cantera to model and simulate complex chemical processes, combustion reactions, and heat transfer phenomena. The software allows users to define chemical mechanisms, simulate reactions under different conditions, and analyze the thermodynamic properties of reacting systems. Cantera plays a significant role in advancing research and development in areas such as combustion engines, environmental science, and materials science.

# Conclusion

# Python Libraries

## Cantera
"[Cantera](https://cantera.org/) is an open-source suite of tools for problems involving chemical kinetics, thermodynamics, and transport processes."

## Numpy
[Numpy](https://numpy.org/) is a powerhouse in scientific Python analysis, and needs no introduction.

## Plotly
[Plotly](https://plotly.com/python/) is a widely used plotting library which enables easy interactive plots which can be saved as interactive. They are the plots you'll see embedded here.
