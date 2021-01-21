---
layout: post
title: Differential expression analysis for RNA-Seq data
subtitle: Subread pipeline
tags: [Transcriptomics]
---

To create a working environment, we strongly suggest using [conda](https://www.anaconda.com/products/individual). After installing the conda distribution, follow the next steps to create an environment and install the required software.

```bash
# Create an environment called "rnaseq"
conda create -n rnaseq -c bioconda subread
```

We will use the FASTQ files (RNA-Seq raw data) from [Gonzales *et al*. 2018](https://pubmed.ncbi.nlm.nih.gov/29584757/). To download the raw data from ENA (European Nucleotide Archive) run the next commands. The project ID is [PRJNA395984](https://www.ebi.ac.uk/ena/browser/view/PRJNA395984)

```bash
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/SRR587/003/SRR5874663/SRR5874663.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/SRR587/004/SRR5874664/SRR5874664.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/SRR587/006/SRR5874666/SRR5874666.fastq.gz
wget ftp://ftp.sra.ebi.ac.uk/vol1/fastq/SRR587/007/SRR5874667/SRR5874667.fastq.gz
```

The details of each FASTQ file is the next:

| ID           | Group        | Condition    |
| ------------ | ------------ | ------------ |
| SRR5874663   | Control      | Disomic      |
| SRR5874664   | Control      | Disomic      |
| SRR5874666   | Experimental | Trisomic     |
| SRR5874667   | Experimental | Trisomic     |

We will use the disomic samples as reference for the differential expression analysis.