---
layout: post
title: Boosting Primary Data Quality through Machine Learning Techniques
subtitle: Anomaly Detection in Batch Process Manufacturing Data using an Autoencoder
tags: [sensor data, time series, anomaly detection, neural networks, autoencoder, primary data, data quality rating, product carbon footprint, pcf, ocf]
comments: true
---

In this blog post, we demonstrate how to apply machine learning to detect quality issues of sensor data. Specifically, we consider a reconstruction convolutional autoencoder model as a tool to detect anomalies in timeseries data.

Historically, the objective of detecting anomalies and identifying patterns of abnormal behavior in metering data was to quickly identify when production equipment is not functioning as intended. This can help the manufacturers to prevent downtime, reduce the time and cost of maintenance and repair, and minimize the impact on the production line, thus improving the overall quality of the final product and the overall equipment efficiency. However, the focus of this blog post is accurate measuring of energy use in production processes: sensors and meters are sources of the primary data on the energy consumption of production equipment; thus, if the production equipment is experiencing anomalies or the data collection infrastructure is not functioning correctly, the data collected will not accurately reflect its actual energy consumption. This can result in inaccurate calculations of energy use and can affect the accuracy of any calculations based on this data, such as organizational carbon footprint and product carbon footprint. By detecting and flagging anomalous data points, it is possible to adjust the calculations for the corresponding time window, resulting in a more precise measurement of energy use.

## Setup

We will use synthesised data of electric current for an engine working in a batch process manufacturing line. See one of our previous posts, [Applying OPP Principles to Manufacturing Analytics Testing Data Generation](https://zhenev.github.io/2022-08-06-opp-real-world-data-generation/), for more details. Our dataset includes minutely data for the period August 06 to September 07, 2022:

<div id="myDiv_v1"></div>
<script>
  fetch('/assets/data/2022-12-17-full-viz.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v1', data);
    });
</script>

We are using the part of the data before the `CUT_POINT` for training and the rest of the data for testing to see if the sudden jump ups in the data is detected as an anomaly:

```python
CUT_POINT = '2022-08-09 18:00:00'
training_df = generated_time_series.loc[:CUT_POINT].copy()
testing_df = generated_time_series.loc[CUT_POINT:].copy()

```

Note: as we want the missing data points be also detected as anomalous, we will fill them in with the maximum of observed electric current values when feeding them into the autoencoder.

To implement the task, we introduce a custom class called `AnomalyDetector`, which includes methods for sequence generation, model building, training, and others. The `__init__` method of the class takes the training and the testing datasets and the number of data points for generating sequences as parameters. Note: our data has its inner structure and periodicity of approximately 150 timestamps (the nominal batch duration plus thetime window between batches according to our hypothetical production process specification), thus, to create sequences, we can combine `TIME_STEPS=150` contiguous data values.

```python

TIME_STEPS = 150

class AnomalyDetector:
    
    def __init__(self, training_data: pd.DataFrame, testing_data: pd.DataFrame, time_steps_number: int):
        """
        :param training_df: a pandas minutely time series dataframe with 'time' as index and 'current'
        as sensor values, used for training
        :param testing_df: a pandas minutely time series dataframe with 'time' as index and 'current'
        as sensor values, used for testing
        :param time_steps_number: sequences length
        """
        self.training_df = training_data
        self.testing_df = testing_data
        self.time_steps_number = time_steps_number
```
