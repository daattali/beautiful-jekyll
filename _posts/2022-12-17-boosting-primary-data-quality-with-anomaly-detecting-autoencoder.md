---
layout: post
title: Boosting Primary Data Quality through Machine Learning Techniques
subtitle: Anomaly Detection in Batch Process Manufacturing Data using an Autoencoder
tags: [sensor data, time series, anomaly detection, neural networks, autoencoder, primary data, data quality rating, product carbon footprint, pcf, ocf]
comments: true
---

In this blog post, we demonstrate how to apply machine learning to detect quality issues of sensor data. Specifically, we consider a reconstruction convolutional [autoencoder](https://www.tensorflow.org/tutorials/generative/autoencoder) model as a tool to detect anomalies in timeseries data.

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

To implement the task, we introduce a custom class called `AnomalyDetector`, which includes methods for sequence generation<sup>1</sup>, model building, training, and others. The `__init__` method of the class takes the training and the testing datasets and the number of data points for generating sequences as parameters. Note: our data has its inner structure and periodicity of approximately 150 timestamps (the nominal batch duration plus thetime window between batches according to our hypothetical production process specification), thus, to create sequences, we can combine `TIME_STEPS=150` contiguous data values.

```python

TIME_STEPS = 150

class AnomalyDetector:
    
    def __init__(
        self,
        training_data: pd.DataFrame,
        testing_data: pd.DataFrame,
        time_steps_number: int
    ):
        """
        :param training_df: a pandas minutely time series dataframe with 'time' as index
        and 'current' as sensor values, used for training
        :param testing_df: a pandas minutely time series dataframe with 'time' as index
        and 'current' as sensor values, used for testing
        :param time_steps_number: sequences length
        """
        self.training_df = training_data
        self.testing_df = testing_data
        self.time_steps_number = time_steps_number
```

## Data preparation

To prepare the data for sequence generation, we first are extracting the data values from the time series and then normalizing them. We are using training mean and standard deviation to normalize the testing timeseries. Then we are constructing training and testing sequences.

```python
    def normalize_data(self):
        self.training_mean = self.training_df.mean()
        self.training_std = self.training_df.std()
        self.normalized_training_df = (
            self.training_df - self.training_mean
        ) / self.training_std
        self.normalized_testing_df = (
            self.testing_df - self.training_mean
        ) / self.training_std
        print(f"Number of training samples: {len(self.normalized_training_df)}")
        print(f"Number of testing samples: {len(self.normalized_testing_df)}")
    
    def __generate_sequences(self, values: np.array):
        # Generated training sequences for use in the model.
        output = []
        for i in range(len(values) - self.time_steps_number + 1):
            output.append(values[i : (i + self.time_steps_number)])
        return np.stack(output)
        
    def generate_training_sequences(self):      
        self.training_sequences = self.__generate_sequences(
            self.normalized_training_df.values
        )
        print(f"Training input shape: {self.training_sequences.shape}")
        
    def generate_testing_sequences(self):
        self.testing_sequences = self.__generate_sequences(
            self.normalized_testing_df.values
        )
        print(f"Testing input shape: {self.testing_sequences.shape}")
```

## Building the model

### Convolutional reconstruction autoencoder

To detect anomalies in batch process manufacturing data, we will employ a convolutional reconstruction autoencoder model for sequenced data. It is a type of neural network that analyzes the sequential structure of the input data and learns to encode and decode sequential data by extracting and reconstructing relevant features from the input sequence. During training, the model minimizes the difference between the input and output sequences, and the resulting reconstructed sequences for the testing data can be compared to the original ones to detect anomalies. There have been several studies and publications that have demonstrated the effectiveness of using autoencoders for anomaly detection in various process manufacturing related domains:

- The use of convolutional autoencoders for anomaly detection in industrial machinery, using vibration sensor data, was explored in "Convolutional Autoencoders for Predictive Maintenance and Anomaly Detection in Industrial Machinery" by K. Kim et al. (2017).
- The application of autoencoders for detecting anomalies in temperature and pressure readings in chemical batch reactors was discussed in "Anomaly Detection in Chemical Batch Processes Using Autoencoder Neural Networks" by S. Khemchandani and J. P. Maree (2018).
- The performance of different models, including an autoencoder, while considering activated sludge process in wastewater treatment plants and the Bayer process in alumina production plants, was studied in "Anomaly detection in complex industrial processes using deep learning" by Zhang, X. et al. (2021).

### Architecture

The convolutional architecture is thought to be particularly suited to data, where local features and relationships between adjacent data points are important. The classical architecture of a convolutional reconstruction autoencoder model consists of an encoder and a decoder, where the encoder consists of one or more convolutional layers followed by one or more pooling layers, which reduce the spatial dimensions of the input, and the decoder consists of one or more transposed convolutional layers followed by one or more upsampling layers, which reconstruct the original input from the low-dimensional representation created by the encoder. The "bottleneck" layer is typically a fully connected or dense layer that connects the encoder and decoder. The goal is to learn a compressed representation of the input data in the bottleneck layer, which can be used for anomaly detection or other downstream tasks. We are limiting our architecture to the basic one implemented in the `create_model` method below:

- After the `Input` layer, the model includes two 1D convolutional layers and two `Conv1DTranspose` layers, with one Droput layer between them;
- The use of Dropout layers helps to prevent overfitting of the model to the training data;
- Finally, the output layer is a `Conv1DTranspose` layer with the filter parameter value of one to produce final one-dimensionsl output.

The model is taking two parameters, `sequence_length` and `num_features`. In our case, `sequence_length` equals `TIME_STEPS` and `num_features` takes the value of one (the electric current values); both parameters are stored in the `shape` instance of the sequence tensor.

```python
    def create_model(self):
        # define the model
        model = Sequential()
        # add layers to model
        model.add(Input(shape=(
            self.training_sequences.shape[1], self.training_sequences.shape[2]
        )))
        model.add(Conv1D(filters=30, kernel_size=7, padding="same", activation="relu"))
        model.add(Dropout(rate=0.2))
        model.add(Conv1D(filters=15, kernel_size=7, padding="same", activation="relu"))
        model.add(Conv1DTranspose(
            filters=15, kernel_size=7, padding="same", activation="relu"
        ))
        model.add(Dropout(rate=0.2))
        model.add(Conv1DTranspose(
            filters=30, kernel_size=7, padding="same", activation="relu"
        ))
        model.add(Conv1DTranspose(filters=1, kernel_size=7, padding="same"))
        # add compiler
        optimizer = Adam(learning_rate=0.001)
        model.compile(optimizer=optimizer, loss='mse')
        self.model = model
        print(self.model.summary())
```
Using `padding="same"` parameter in the convolutional layers ensures that the output feature maps have the same length as the input time series by padding zeros to the edges of the input sequence if necessary. This is important for preserving the temporal structure of the data and allowing the model to learn meaningful patterns across the entire sequence. Without padding, the convolutional layers would reduce the length of the sequence, which could result in loss of information and reduced model performance.

Using the rectified linear unit (ReLU) activation function, which besides preventing the vanishing gradient problem during training, helps to ensure that output values are always non-negative (since we are working with non-negative values).

We are leveraging the MSE loss function for our time series autoencoder as a straightforward choice, more computationally efficient for gradient-based optimization methods, like `Adam`, and putting a higher weight on larger errors.

## Training the model

When training the model, we are using batches of 128 samples in 30 epochs and set aside 10% of the data for validation. Then we are plotting the resulting training and validation loss to see how the training went.

```python
    def train_model(self, epochs=30, batch_size=128, validation_split=0.1):
        # fit model
        history = self.model.fit(
            self.training_sequences,
            self.training_sequences,
            epochs=epochs,
            batch_size=batch_size,
            validation_split=validation_split,
        )
        self.history = history
        # plot losses
        plt.plot(self.history.history["loss"], label="Training Loss")
        plt.plot(self.history.history["val_loss"], label="Validation Loss")
        plt.legend()
        plt.show()
```

## Anomaly detection

We are detecting anomalies by determining how well our model can reconstruct the input data. To this end we:

- Get reconstruction error threshold;
- Compare recontruction;
- Run the model on the testing data;
- Label anomalies;
- Find anomalous data points in the original testing data.

### Get reconstruction error threshold

1. Find `MAE` loss on training samples (at this step, we want to treat all errors equally).
2. Find max `MAE` loss value. This is the worst our model has performed trying to reconstruct a sample. We will make this value the threshold for anomaly detection.
3. If the reconstruction loss for a sample is greater than the stated value then we can infer that the model is seeing a pattern that is not familiar to it. We will label this sample as an anomaly.

```python
    def get_reconstruction_error_threshold(self):
        # calculate predictions
        self.train_predictions = self.model.predict(self.training_sequences)
        # calculte MAE loss
        self.train_mae_loss = np.mean(
            np.abs(self.train_predictions - self.training_sequences), axis=1
        )
        # get reconstruction loss threshold
        self.threshold = np.max(self.train_mae_loss)
        # plot the distribution of the train MAE losses
        plt.hist(self.train_mae_loss, bins=50)
        plt.xlabel("Train MAE loss")
        plt.ylabel("No of samples")
        plt.show()
        # print out the threshold
        print(f"Reconstruction error threshold: {self.threshold}")
```

### Compare recontruction

To grasp a visual impression of how the things worked out, we add a method to plot one of the sequences of our training dataset and the reconstructed sequence.

```python
    def plot_one_reconstructed_training_sequence(self, sequence_num: int):
        """Checks out visualy how reconstruction worked"""
        plt.plot(self.training_sequences[sequence_num], label="Training sample")
        plt.plot(self.train_predictions[sequence_num], label="Predicted sample")
        plt.legend()
        plt.show()
```

### Run the model on the testing data

Then we add a method for reconstructing the testing sequences.

```python
    def get_reconstructed_testing_sequences(self):
        # calculate predictions
        self.testing_predictions = self.model.predict(self.testing_sequences)
        # calculate MAE loss
        self.test_mae_loss = np.mean(
            np.abs(self.testing_predictions - self.testing_sequences), axis=1
        )
        # plot the distribution of the test MAE losses
        plt.hist(self.test_mae_loss, bins=50)
        plt.xlabel("Test MAE loss")
        plt.ylabel("No of samples")
        plt.show()
```

### Label anomalies

Anomalies are defined as testing samples with testing MAE loss above the reconstruction error threshold.

```python
    def mark_anomalous_samples(self):
        # Detect all the samples which are anomalies.
        self.anomalies = self.test_mae_loss > self.threshold
        print(f"Number of anomaly samples: {np.sum(self.anomalies)}")
        print(f"Indices of anomaly samples: {np.where(self.anomalies)[0]}")
```

### Find anomalous data points in the original testing data

To determined the anomalous data points, we check each data point on being presented in anomalous sequences: data point `i` is an anomaly if samples `[(i - timesteps + 1) to (i)]` are anomalies.

```python
    def mark_anomalous_data_points(self):
        anomalous_data_indices = []
        for data_idx in range(
          self.time_steps_number - 1,
          len(self.normalized_testing_df) - self.time_steps_number + 1
        ):
            if np.all(self.anomalies[data_idx - 149 : data_idx]):
                anomalous_data_indices.append(data_idx)
        self.anomalous_data_indices = anomalous_data_indices
```

### Plot anomalies

We are adding two methods, to plot one of the testing reconstructed sequences and to overlay the anomalies on the original test data plot.

```python
    def plot_one_reconstructed_testing_sequence(self, sequence_num: int):
        """Checks out visualy how reconstruction worked"""
        plt.plot(self.testing_sequences[sequence_num], label="Testing sample")
        plt.plot(self.testing_predictions[sequence_num], label="Predicted sample")
        plt.legend()
        plt.show()

    def visualize_anomalies(self, start_index: int, end_index: int):
        df_subset = self.testing_df.iloc[self.anomalous_data_indices]
        fig, ax = plt.subplots(figsize=(28,4))
        self.testing_df[start_index:end_index].plot(legend=False, ax=ax)
        start_ts = self.testing_df.iloc[start_index].name
        end_ts = self.testing_df.iloc[end_index].name
        df_subset[start_ts:end_ts].plot(
            legend=False, ax=ax, color="r", marker='o', linestyle='None'
        )
        plt.show()
```

### Construct labeled testing dataset

Finally, after fetching the anamalous data point indices, we are adding labels to the testing dataset.

```python
    def construct_labeled_testing_time_series(self):
        df = self.testing_df.copy()
        df.reset_index(inplace=True)
        df['anomaly'] = False
        df.loc[self.anomalous_data_indices, 'anomaly'] = True
        self.testing_df_labeled = df.set_index('time')
```

## Running the model

To demonstrate how the anomaly detector works, we are explicitely running each method of the class. As it has been already mentioned, we want the missing data points to be detected as anomalous as well; to this end, we are filling them in with the maximum of the current values.

```python
ad = AnomalyDetector(
    training_df,
    testing_df.fillna(testing_df['current'].apply('max')),
    TIME_STEPS
)
ad.normalize_data()
ad.generate_training_sequences()
ad.generate_testing_sequences()
ad.create_model()
ad.train_model()
ad.get_reconstruction_error_threshold()
ad.get_reconstructed_testing_sequences()
ad.mark_anomalous_samples()
ad.mark_anomalous_data_points()
ad.construct_labeled_testing_time_series()

Number of training samples: 5311
Number of testing samples: 41409
Training input shape: (5162, 150, 1)
Testing input shape: (41260, 150, 1)
Model: "sequential_21"
_________________________________________________________________
 Layer (type)                Output Shape              Param #   
=================================================================
 conv1d_44 (Conv1D)          (None, 150, 30)           240       
                                                                 
 dropout_43 (Dropout)        (None, 150, 30)           0         
                                                                 
 conv1d_45 (Conv1D)          (None, 150, 15)           3165      
                                                                 
 conv1d_transpose_64 (Conv1D  (None, 150, 15)          1590      
 Transpose)                                                      
                                                                 
 dropout_44 (Dropout)        (None, 150, 15)           0         
                                                                 
 conv1d_transpose_65 (Conv1D  (None, 150, 30)          3180      
 Transpose)                                                      
                                                                 
 conv1d_transpose_66 (Conv1D  (None, 150, 1)           211       
 Transpose)                                                      
                                                                 
=================================================================
Total params: 8,386
Trainable params: 8,386
Non-trainable params: 0
_________________________________________________________________
None
Epoch 1/30
37/37 [==============================] - 3s 59ms/step
- loss: 0.2756 - val_loss: 0.0570
Epoch 2/30
37/37 [==============================] - 2s 49ms/step
- loss: 0.0548 - val_loss: 0.0286
Epoch 3/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0339 - val_loss: 0.0173
Epoch 4/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0233 - val_loss: 0.0171
Epoch 5/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0176 - val_loss: 0.0144
Epoch 6/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0142 - val_loss: 0.0139
Epoch 7/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0120 - val_loss: 0.0163
Epoch 8/30
37/37 [==============================] - 2s 49ms/step
- loss: 0.0104 - val_loss: 0.0161
Epoch 9/30
37/37 [==============================] - 2s 49ms/step
- loss: 0.0091 - val_loss: 0.0138
Epoch 10/30
37/37 [==============================] - 2s 52ms/step
- loss: 0.0083 - val_loss: 0.0142
Epoch 11/30
37/37 [==============================] - 2s 51ms/step
- loss: 0.0076 - val_loss: 0.0148
Epoch 12/30
37/37 [==============================] - 2s 49ms/step
- loss: 0.0069 - val_loss: 0.0147
Epoch 13/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0063 - val_loss: 0.0133
Epoch 14/30
37/37 [==============================] - 2s 50ms/step
- loss: 0.0059 - val_loss: 0.0102
Epoch 15/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0054 - val_loss: 0.0093
Epoch 16/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0050 - val_loss: 0.0061
Epoch 17/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0046 - val_loss: 0.0060
Epoch 18/30
37/37 [==============================] - 2s 53ms/step
- loss: 0.0043 - val_loss: 0.0055
Epoch 19/30
37/37 [==============================] - 2s 53ms/step
- loss: 0.0041 - val_loss: 0.0055
Epoch 20/30
37/37 [==============================] - 2s 49ms/step
- loss: 0.0038 - val_loss: 0.0039
Epoch 21/30
37/37 [==============================] - 2s 52ms/step
- loss: 0.0035 - val_loss: 0.0034
Epoch 22/30
37/37 [==============================] - 2s 52ms/step
- loss: 0.0033 - val_loss: 0.0027
Epoch 23/30
37/37 [==============================] - 2s 46ms/step
- loss: 0.0031 - val_loss: 0.0025
Epoch 24/30
37/37 [==============================] - 2s 47ms/step
- loss: 0.0029 - val_loss: 0.0018
Epoch 25/30
37/37 [==============================] - 2s 47ms/step
- loss: 0.0027 - val_loss: 0.0019
Epoch 26/30
37/37 [==============================] - 2s 46ms/step
- loss: 0.0026 - val_loss: 0.0016
Epoch 27/30
37/37 [==============================] - 2s 50ms/step
- loss: 0.0025 - val_loss: 0.0014
Epoch 28/30
37/37 [==============================] - 2s 52ms/step
- loss: 0.0024 - val_loss: 0.0012
Epoch 29/30
37/37 [==============================] - 2s 48ms/step
- loss: 0.0022 - val_loss: 0.0011
Epoch 30/30
37/37 [==============================] - 2s 49ms/step
- loss: 0.0021 - val_loss: 9.7198e-04
```
![losses](/assets/data/2022-12-17-losses.png)

![train_mae](/assets/data/2022-12-17-train-mae.png)
```python
Reconstruction error threshold: 0.03448834298971466
```
![test_mae](/assets/data/2022-12-17-test-mae.png)
```python
Number of anomaly samples: 2853
Indices of anomaly samples: [   44    45    46 ... 39556 39557 39558]
```

<sup>1</sup> In what follows, we apply a sequence-based model. It learns to encode and decode sequential data by extracting and reconstructing relevant features from the input sequences, which are constructed from a given timeseries. The sequence generation is performed using a sliding window approach. The initial timeseries is divided into overlapping windows of a specified length, and each window is treated as a sequence of data points. The length of the window, defined by the `TIME_STEPS` parameter, determines the length of the sequence (150 data points in our case), and the amount of overlap between adjacent windows can also be specified (we use one data point). By sliding the window along the time axis of the data, multiple sequences are generated from a single time series. These sequences are then fed into the convolutional reconstruction autoencoder model for training and the following for anomaly detection.

Copyright © 2022 Zheniya Mogilevski

