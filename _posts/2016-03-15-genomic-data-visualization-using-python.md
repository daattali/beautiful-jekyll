---
layout: post
title: Genomic Data Visualization in Python
subtitle: From deep sequencing to insights
category: visualization
tags: [python, matplotlib, seaborn, sequencing, genomics]
published: false
---


**Table Of Content**
<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Targeted Sequencing Analytics Suite](#targeted-sequencing-analytics-suite)
		- [How to use it ?](#how-to-use-it-)
		- [What are the plots generated ?](#what-are-the-plots-generated-)
		- [Example Output](#example-output)
		- [Dependencies](#dependencies)
		- [Contribution guidelines](#contribution-guidelines)
		- [Who do I talk to?](#who-do-i-talk-to)

<!-- /TOC -->

# Targeted Sequencing Analytics Suite

[![Code Issues](http://www.quantifiedcode.com/api/v1/project/3c5051c46b7f4fb09b5498318e29e1ff/badge.svg)](http://www.quantifiedcode.com/app/project/3c5051c46b7f4fb09b5498318e29e1ff)


This is a list of functions we can use to generate different kind of plots on deep sequencing data.

Data is usually a list of bam files, and intervals. Additionnally I am reading a specific tsv file output from a deep sequencing pipeline

### How to use it ?

Please follow these instructions to get this tool work properly

```
git clone <this repo url>.git
cd DeepSeqPlots
python tsa.py \
	--path_to_bams <Path where your (**sorted and indexed**) bam files are> \
	--targets <regions in bed format> \
	--variant_status_path <Path where the variant status tsv files are >
	--bam_extension ".example.realigned.blahblah.sorted.flagstat.indexed.blablablabla.bam"

```

You should have 6 plots in the directory

### What are the plots generated ?

**Coverage histogram in amplicon region :**

This is a distribution of coverage inside the amplicon regions. The function parses region by region and get the coverage of all the samples provided, then render a histogram with X axis being the coverage

**Cumulative coverage saturation plot :**

This is the same as before, instead we render a cumulative histogram, it can be useful, you can see how bad the NSG sample renders for example

**Mapping qualities in amplicon regions :**

This is a stacked histogram that renders the mapping qualitites inside the amplicon regions, we can see that NSG is again failing and that we have a mapping qualities around 42 in this example in particular

**Targeted regions coverage:**

This is the so called CDF function of coverage per sample inside the target regions

**Coverage heatmap inside amplicon regions:**

This plot is another view of coverage inside amplicon region, it places all the samples side by side and render all the row as a heatmap, I did 2 examples here, one with a crazy sample like the NSG one and one without

**Allelic frequencies heatmap**

This is a plot showing the allele frequencies change across positions and samples, I tried to cluster the positions per frequencies values but I dont get 'clusterable' positions, so I sorted the positions values across all samples  

**Zygosity Matrix**

Dual clustering on positions and sample names grouping positions per zygosity (heterozygote, homozygote wildtype, homozygote mutant)


### Example Output

**allele frequencies clustering (positions vs samples)**

![allele frequencies](https://bytebucket.org/radaniba/targeted-sequencing-analytics-suite/raw/c66ec81fde737c7c5159611390cd892a9307bf3f/example_output/allele_frequencies.png?token=a91e78b2141bfdc8a531dd01647de9f89b30fab8)

**coverage across positions violin plot**

![coverage](https://bytebucket.org/radaniba/targeted-sequencing-analytics-suite/raw/c66ec81fde737c7c5159611390cd892a9307bf3f/example_output/coverage_across_positions_violin.png?token=eca1c3c58643d998a2ed42f0091481e9f8bdbade)

**target capture CDF**

![capture](https://bytebucket.org/radaniba/targeted-sequencing-analytics-suite/raw/c66ec81fde737c7c5159611390cd892a9307bf3f/example_output/target_capture_cdf.png?token=326eb8883929ba10db87f4a69f5b6197c72642bb)

**Zygosity matrix**

![zygosity](https://bytebucket.org/radaniba/targeted-sequencing-analytics-suite/raw/c66ec81fde737c7c5159611390cd892a9307bf3f/example_output/zygosity_matrix.png?token=7e7564911de748ccf976476469bfd3d806a0a4d4)

**Coverage heatmap across amplicon regions**

![coverage in amplicon](https://bytebucket.org/radaniba/targeted-sequencing-analytics-suite/raw/e407a493eca27b8b8351cb8e422a7352d524f5a6/example_output/coverage_heatmap_per_amplicon.png?token=ef2eef0f330040f7fe15e094ac37db51009aee44)


**In target vs Out of targets**

![in_out](https://bytebucket.org/radaniba/targeted-sequencing-analytics-suite/raw/c66ec81fde737c7c5159611390cd892a9307bf3f/example_output/in_out_of_target.png?token=7e3b9f61b5ea40fd115502c540a3972a2f0d80c2)

**Mapped Unmapped Reads**

![mapped unmapped](https://bytebucket.org/radaniba/targeted-sequencing-analytics-suite/raw/c66ec81fde737c7c5159611390cd892a9307bf3f/example_output/mapped_reads.png?token=523e92eccb47afde3fd5b35a6e7aed374e5362d7)

**Mapping Qualities**

![mapping quality](https://bytebucket.org/radaniba/targeted-sequencing-analytics-suite/raw/c66ec81fde737c7c5159611390cd892a9307bf3f/example_output/mapping_quality.png?token=1ddbdd03613efea77b83f505e272b4ea6117d86c)


### Dependencies

* bedtools2
* samtools
* matplotlib
* pandas
* numpy
* seaborn

### Contribution guidelines

* Writing tests
* Code review

### Who do I talk to?

* Repo owner at aradwen@gmail.com
