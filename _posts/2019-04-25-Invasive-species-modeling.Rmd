---
title: "Invasive species modelling"
subtitle: PhD Research
layout: post
---

My PhD work involves modelling invasive species dynamics in NZ forests. There is more detail for my supervisors and colleagues.

### ALL MATERIAL IS DRAFT ONLY

<- PRIVATE ->

Population dynamics of interacting invasive species in New Zealand forests

<- PRIVATE ->

This folder has the working documents for my PhD publications. I would normally keep these files on dropbox or something similar. During this PhD I have been creating a reproducible workflow for my scientific career using version control. I am now in the process of slowly transferring projects version control using GIT and GIThub. Once I publish results and copyright is released I will publish the final documents on the Open Science Framework (OSF) or other scientific repo/server.

## Thesis Overview

The overarching aim of this PhD is to examine the role of predation, competition and resource flow in regulating invasive mammal populations in NZ forests. This research can then be used support other forecasting models to estimate the likely effects of species removals on the objectives set by the government of New Zealand under “Predator Free New Zealand 2050 (PFNZ2050).

To do this I will construct ecological models that describe the population dynamics of interacting invasive species in New Zealand forests. I will use the understanding derived from these models to predict the effects of management manipulations and reduce the likelihood of unanticipated outcomes. Aligning this ecological research with good research practise that insures the results are reproducible and replicable by allowing open access to statistical code and analysis.

## Key points this thesis will cover

In this thesis I will use observed data to build ecosystem models that allow researchers to directly quantify the interactions among invasive species (Peng 2015).

1. To build a research synthesis database of the theoretical relationships proposed in over 100 years of conservation research in NZ and the experimental work supporting these models. We need a uniform set of models and notation to develop from (e.g. Holland et al. 2015; Ruscoe et al. 2005; Choquenot & Ruscoe 2000; Ruscoe et al. 2004; King et al. 2003).

2. Use a combined theoretical modelling and experimental approach to clarify the outcomes of invasive species control in three large-scale ecological datasets (Chapters 2,3,4). I build and test previous research that has attempted to characterize these interactions between invasive species, resources and native species in New Zealand Forests (Choquenot & Ruscoe 2000 + +).

3. Advances in ecological modelling tools have opened up opportunities to assess and parameterize theoretical models from observational data (King 2012). Along with this comes the correct partitioning of observation and process error. We use statistical software such as JAGS (Plummer 2010), WinBUGS (Suess & Trumbo 2010) and STAN (STAN development Team 2015) to develop the understanding of how these sources of error may effect the goals and targets of conservation managers and researchers alike.

## Thesis introduction

Overall PhD summary **Have started first draft in GIThub**

## Introduction 1.1

Invasive species database *A database (DB) for invasive species in New Zealand (NZ)*

Creating a database of research to understand the current knowledge of observation and/or population level demographics of New Zealand invasive species.

**NOTE:** This is already part of a standard literature review and if this does not get any further than that it is a bonus.

## Introduction 1.2

Dealing with Reproducibility *Why and how to make a reproducible workflow for invasive species research in New Zealand*

This chapter creates a workflow that allows the ability to access and use the invasive species database in a reproducible way.... Etc etc

Importance of reproducibility between community groups etc

We also conduct a meta-analysis to shows that even though the time it takes to reproduce a workflow comes back THIS>...

- Citation records (Google scholar and elsivear)
- Collaborations (international vs domestic)
- Outreach (twitter/fb).

Packages used:

- Revtools
- Scholar
- Python?

## Data Chapter 1

**Status:** [1st draft with Richard](https://www.dropbox.com/s/m5hte0n2vyl1dt2/Davidson_2019_BeechForest_19022019.docx?dl=0)

### NZ beech forests

*Merky forests. What can we expect from stoat control in NZ forests? - Food vs. Predation.*

**Abstract:** This publication clarifies the discrepancy between; two modelling papers that suggest mesopredator release of rodents is possible in New Zealand forest systems and; several field studies that have presented limited but conflicting support for increases in mouse abundance following predator control. We used an experimental design to test the differences between the two "frames of though" and found that there is no evidence to suggest mice will become more abundant after predator removal ([*additional resources can be found here*](https://davan690.github.io/)).

## Data Chapter 2

*A more complex set of interreacting invasive species.*

**Status:** [Analysis underway](https://www.dropbox.com/s/fm57ns1jndmkmq1/Davidson_2019_mpd_manuscript.docx?dl=0)

### NZ mixed forests

**Background:** This chapter will extend on the modelling explored for the beech forest system (Chapter Two). Previous research has shown that complex interactions between native and exotic species exist in NZ mixed forest systems (Ruscoe et al. 2011; Ruscoe et al. 2012). This chapter parametrises a model to account for these different interactions in an extension of the beech forest model in the previous chapter to account for different food resources and other invasive species dynamics.

**Objectives:** This chapter has the overall objective to model additional interactions and species in a New Zealand forest system. Beech forests have a limited number of species producing food for invasive mammals. When the ecosystem has more resources with different availability to the mesopredators the system is expected to have different outcomes (Choquenot & Ruscoe 2000). For example, mice populations are thought to persist in podocarp/hardwood forests at higher densities than adjoining beech forest (Choquenot & Ruscoe 2000).

To meet the objective for this chapter, the model will extend on the proposed forest model in the previous chapter to account for different food resources and other invasive species dynamics. The multi-species dataset (MPD) will allow for the modelling of native bird species and investigate more complex interactions in a different forest type.

AIMS:

1. Estimate observation models for rodents, possums, seed production and invertebrates.

2. Link these using a process model of links between species. In this process we will test multiple possible processes driving these dynamics including predator and competition release between native and invasive species.

3. Simulation studies will investigate possible errors associated with different data collection methods.

Research on the same dataset has investigated differences in the abundance indices for invasive species (Ruscoe et al. 2011). The response of invertebrates to different invasive species control was also investigated (Ruscoe et al. 2012). I will extend on these analyses to build an overall model incorporating the additional invasive species  My GIT account is a work in  [progress](https://github.com/davan690/).

## Data Chapter 3

*A more complex set of interreacting invasive species and reduced data quality*

**Status:** [Planning stage]()

## Apllication chapter

The effects of incorrectly modelling observation and process error for PFNZ2050

## Dicussion chapter

Overall conclusion

## Key Resources

Here is an [example](https://github.com/davan690/PestManagement/blob/master/README.md) individual based pest modelling This is a `repo` from a recent publication on dynamic pest management from Dean Anderson and others.