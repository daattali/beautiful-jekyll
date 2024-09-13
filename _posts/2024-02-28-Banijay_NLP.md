---
layout: post
title: Advanced Emotion Classification System; Leveraging NLP and Machine Learning for Enhanced Video Content Analysis
subtitle: A Collaborative Project with Banijay
gh-repo: DominikSzewczyk224180/Projects-2022-2023
gh-badge: [star, fork, follow]
tags: [NLP, Machine Learning, Emotion Classification, Transformer Models]
comments: true
mathjax: false
author: Dominik Szewczyk
categories: projects
---

{: .box-success}
This project with Banijay aimed to develop an advanced emotion classification system utilizing natural language processing (NLP) and cutting-edge machine learning models to enhance video content analysis.

**Project Duration:** January 2024 - April 2024

## 📝 Project Overview

In collaboration with Banijay, we focused on creating a sophisticated emotion classification system that leverages NLP techniques and state-of-the-art machine learning models. The goal was to achieve high accuracy in detecting emotions from video content. The final model integrated transformer-based techniques to optimize emotion detection performance.

## 📊 Data Preprocessing & Feature Extraction

The project involved several key preprocessing and feature extraction steps:
- **Text Cleaning:** Regular expressions were used for text cleaning.
- **Normalization:** Tokenization and stemming techniques were applied.
- **Word Embeddings:** We employed word embeddings to represent words as vectors and incorporated these embeddings into our machine learning model.
- **TF-IDF & POS Tagging:** These techniques were utilized to further enhance feature extraction.
- **Custom Word Embedding Model:** A word embedding model based on the project corpus was created and integrated into the machine learning model.

## 🧠 Machine Learning Models

We developed several emotion classification models, including:
- **Naïve Bayes**
- **Logistic Regression**
- **Hidden Markov Model (HMM)**
- **Conditional Random Fields (CRF)**
- **Recurrent Neural Network (RNN)**
- **Long Short-Term Memory (LSTM)**

These models were evaluated for their effectiveness in classifying emotions from textual data.

## 🛠️ Project Pipeline

A comprehensive pipeline was designed to handle the following tasks:
- **Video Fragmentation:** Splitting video content into manageable fragments.
- **Text Extraction:** Extracting text from video fragments.
- **Emotion Prediction:** Applying emotion classification models to predict emotions for each video fragment.

The use of NLP models, particularly BERT, was selected based on the project's requirements and data characteristics.

## 📈 Model Performance & Error Analysis

We conducted an extensive evaluation of model performance using metrics such as:
- **Accuracy**
- **Precision**
- **Recall**
- **F1-score**

The performance of various models was analyzed to determine the best-performing model, taking into account the trade-offs between different performance metrics. The entire process, including evidence and findings, was documented in a detailed Technical Report.

## 🌐 Transformer Models & BERT

We utilized the Hugging Face platform to test and fine-tune several transformer models. BERT was successfully implemented and trained on our dataset, leading to significant improvements in emotion classification accuracy.

## 📸 Presentation Snippets

Here are some snapshots from our project presentation:

![Presentation Snapshot 1]({{ '/assets/img/banijay_presentation1.png' | relative_url }})
![Presentation Snapshot 2]({{ '/assets/img/banijay_presentation2.png' | relative_url }})
![Presentation Snapshot 3]({{ '/assets/img/banijay_presentation3.png' | relative_url }})

## 🔗 Links

- [View the Project on GitHub](https://github.com/DominikSzewczyk224180/Projects-2022-2023/tree/main/Banijay_Emotion_Classification)

## 🛠 Skills

- Transformer Models
- Performance Metrics Analysis
- Feature Engineering
- Natural Language Processing (NLP)
- Model Evaluation
- Using Hugging Face
- Large Language Models
- Advanced Text Processing