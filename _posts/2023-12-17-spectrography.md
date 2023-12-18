---
layout: post
title: Fourier Time Series Analysis In Python
subtitle: Data Segmentation with the STFT and DBSCAN Clustering
gh-repo: cormazz/spectrography
gh-badge: [star, fork, follow]
tags: [machine-learning, python, clustering, dbscan, spectrogram]
comments: true
author: Corrado R. Mazzarelli
---

{: .box-success}
This article explores separating parts of a signal based on the dominant frequency in that part of the signal. All the material used to create this is within the GitHub repository linked above. **I strongly encourage you to explore the [resources](#resources) linked below.** They have guided me on my data science journey and it is truly some remarkable information, all available for free. This article will be written with the assumption that you are familiar with Python, and have watched the reference videos on the discrete Fourier transform, the short-time-Fourier-transform, and clustering algorithms. 

# Summary
While working at GE, I did my best to seek out fun data science projects to sate intellectual curiosity. Two years ago, someone approached me and asked if there was a way to cluster periodic data based on its frequency. The goal was to turn a plot of data that looked like this:

{% include bp.spectrography/initial_data.html %}

and label the different sections.

{: .box-note}
**Note:** Try moving the plot around, zooming in, and clicking on legend entries. If you like these plots, look into [Plotly](https://plotly.com/python/) which allows you to save interactive plots as html files.

I did this by transforming the data into the frequency domain where high and low frequencies could easily be seen using the short-time-Fourier-transform, which essentially takes the normal Fourier transform but on a rolling window, thus trading temporal certainty for spectral certainty. That spectrogram looked like this:

{% include bp.spectrography/spectrogram.html %}

This plot shows the energy in each frequency at a given time. From here, the dominant frequencies were drawn out by simply finding the frequency with the most energy (the most yellow on the plot) at a certain time, and plotted. 

{% include bp.spectrography/dominant_frequency_plot.html %}

It would be simple to draw a line to separate out the high frequency from the low frequency data; however, that would neglect the temporal separation of the different sections of data. Thus, DBSCAN clustering was used to temporally and spectrally cluster the data.

{% include bp.spectrography/clustered_dominant_frequencies.html %}

Once the hyperparameters were tuned, the DBSCAN algorithm did an excellent job segmenting the data into different clusters. The identified clusters were then mapped onto the original data, and the final plot was created.

{% include bp.spectrography/clustered_data.html %}

In conclusion, this project demonstrated the synergy between signal processing techniques like STFT, frequency analysis, and clustering algorithms like DBSCAN. By combining these methods, I successfully transformed and clustered periodic data, providing a comprehensive and insightful representation of the underlying patterns in the original time series.

# Introduction

## Context
I'm not going to go too in depth here regarding what testing GE was doing. However, the data was from a wear test rig where different samples of material were rubbed against each other and properties such as load and displacement were recorded. This data could be used to help describe material properties to let engineers predict the life of different gas turbine components. In this case, there were low-frequency, high-amplitude sections of the data interspersed between high-frequency, low-amplitude sections. 

## Personal History and Motivation
When I first wrote the script for GE 2 years ago, I had never heard of a spectrogram and had just learned about the Fourier transform and its uses. Funnily enough, when I was trying to use the Fourier transform to determine the frequency of the signal at a certain time, I had the idea to take a "rolling Fourier transform," which is exactly what the spectrogram is. I "independently discovered" the spectrogram and made a crude interpretation of it in Python. After following some Dr. Brunton's lecture series (in the [resources](#resources)) and I learned about the spectrogram, I decided to endeavor to rewrite my script for fun, implementing my newfound tools to improve it and then give the improved version to my friend over in the Wear Laboratory. 

## Interesting Concepts

### Short-Time Fourier Transform
The Short-Time Fourier Transform is a signal processing technique used to analyze the frequency content of a signal over time. Unlike the traditional Fourier Transform, which provides information about the entire duration of a signal, STFT breaks the signal into short, overlapping time segments and performs a Fourier Transform on each segment. This allows for a more detailed examination of how the frequency components of a signal change over time, making STFT particularly useful in applications such as audio signal processing and time-frequency analysis.

### Uncertainty Principle
The Uncertainty Principle is a fundamental concept in quantum mechanics, formulated by Werner Heisenberg. It states that certain pairs of physical properties (such as position and momentum) cannot both be precisely measured simultaneously. The more accurately one property is known, the less accurately the other can be known. This principle challenges the classical notion of absolute precision in measurements and introduces a fundamental limit to the predictability of particle behavior at the quantum level.

When considering the Uncertainty Principle in the context of the Short-Time Fourier Transform (STFT), it's helpful to explore how this principle manifests as temporal and spectral uncertainty in the analysis of signals.

#### Temporal Uncertainty:
The Uncertainty Principle, as applied to the temporal domain in the context of STFT, implies that there is a fundamental limit to how precisely we can simultaneously determine the time and frequency characteristics of a signal. When using STFT, the trade-off between time and frequency resolution becomes apparent. This trade-off is a result of the windowing process inherent in STFT.

**Short Time Windows:** Using shorter time windows in the STFT improves temporal resolution by capturing rapid changes in the signal. However, this comes at the cost of frequency resolution. Short windows are less effective in accurately identifying the frequency content of signals with longer durations or those that change more slowly over time.

**Long Time Windows:** Conversely, using longer time windows enhances frequency resolution but diminishes temporal resolution. Longer windows are better suited for capturing the frequency components of slowly varying signals but might miss the nuances of rapidly changing portions.

#### Spectral Uncertainty:
The Uncertainty Principle also manifests as spectral uncertainty when performing STFT.

**Narrow Frequency Windows:** Employing narrow frequency windows in STFT improves frequency specificity, enabling the detection of signals with precise frequency components. However, this increases uncertainty in the time domain. Narrow windows might not capture the dynamics of signal changes occurring within each window.

**Wide Frequency Windows:** On the other hand, wider frequency windows enhance temporal coherence by encompassing a broader range of frequencies. Nevertheless, this approach sacrifices frequency precision, making it challenging to pinpoint the exact frequencies present in the signal.

In summary, the Uncertainty Principle introduces a fundamental constraint on the joint precision of time and frequency measurements in signal analysis. This principle influences the design choices made when configuring the parameters of the STFT, such as the choice of window size and overlap. Striking a balance between time and frequency resolutions is crucial to effectively extract meaningful information from signals while acknowledging the inherent limitations imposed by the Uncertainty Principle.

### DBSCAN Clustering
DBSCAN (Density-Based Spatial Clustering of Applications with Noise) is a clustering algorithm commonly used in machine learning and data analysis. Unlike traditional clustering algorithms that assume clusters have a specific shape, size, or density, DBSCAN identifies clusters based on the density of data points in a region. It can find clusters of arbitrary shapes and is robust to noise. DBSCAN categorizes points as core points, border points, or noise, providing a flexible and effective approach to cluster analysis.

### Polars Lazy Execution
Polars is a data manipulation library in the Rust programming language that introduces the concept of lazy execution. Lazy execution delays the actual computation until the result is explicitly needed, optimizing performance by avoiding unnecessary calculations. Polars allows users to build a sequence of transformations on large datasets without immediately computing the results. This can be advantageous when working with big data, as it enables more efficient resource utilization and can lead to faster overall processing times when the final results are requested.


# Python Libraries

## Numpy
[Numpy](https://numpy.org/) is a powerhouse in scientific Python analysis, and needs no introduction.

## Polars
Instead of using Pandas, I opted for [Polars](https://pola.rs/). Polars is essentially much faster Pandas that has a lazy API which was useful for processing the ~billion data points in the data from the lab. One downside to Polars is that it is still new and does not have the community support/integration that Pandas enjoys. 

## Scipy
[Scipy](https://scipy.org/) is another powerhouse in scientific Python analysis. Here specifically I leveraged scipy.signal.spectrogram, which automatically calculates the spectrogram for you.

## Scikit-Learn
Beloved to machine learning enthusiasts everywhere [scikit-learn](https://scikit-learn.org/stable/index.html) contains prebuilt machine learning models ready to implement. In this case, I leveraged their data scaling and DBSCAN clustering implementations. 

## Plotly
[Plotly](https://plotly.com/python/) is a widely used plotting library which enables easy interactive plots which can be saved as interactive. They are the plots you'll see embedded here.

## Plotly-Resampler
[Plotly-resampler](https://github.com/predict-idlab/plotly-resampler) is a Python library that utilizes Dash to create a dynamically updating Plotly chart that only displays a limited number of data points to ensure the plot doesn't become bloated and slow. This was very useful for the GE implementation, since there were about a billion data points to plot. A limitation of plotly-resampler is that it requires an actively running Python kernel, so the plots cannot be saved as interactive.

## Tqdm
[Tqdm](https://tqdm.github.io/) is just a progress bar library. I like to use it to let me know how long my scripts are taking. 

**Note:** An environment.yml file is included in the GitHub repository to allow you to recreate a functional Anaconda environment.

# Methodology

## Generate Data
First we have to generate some representative data. I did this using numpy to generate a few different sinusoids with the desired frequencies and amplitudes and then save that data as a .csv. The original data is the first plot shown above. If you want more data, check out `generate_example_data.py` in the repo.

## Load the Data
Now, we use Polars to load the data, using their pl.scan_csv() functionality. This lazily scans a CSV so that only the required data is read from the file when you finally instruct Polars to actually load the file. In this case, we didn't really have to lazily scan the .csv, but that is vestigial from the real data implementation. 

{% highlight javascript linenos %}
df = pl.scan_csv(files, try_parse_dates=True).collect()
{% endhighlight %}

## Plot the Original Data

### Plotly
In this case, we used vanilla Plotly to create a plot of the original data since there weren't too many data points. 

{% highlight javascript linenos %}
fig = go.Figure()
fig.add_trace(
    go.Scattergl(
        x=x,
        y=y,
        name='Vertical Displacement',
        showlegend=True
    ),
)
fig.show(renderer="browser")
{% endhighlight %}

### Plotly Resampler
If there was a lot of data generated, we would have to use 

{% highlight javascript linenos %}
fig = go.Figure()
fig.add_trace(
    go.Scattergl(
        x=x,
        y=y,
        name='Vertical Displacement',
        showlegend=True
    ),
)
fig.show(renderer="browser")
{% endhighlight %}

## Take the STFT
There are several inputs to the STFT. The most important of which are the window type, the window size, and the window overlap. I left the window type as the default value provided by scipy, but the window type and the window size were carefully selected to achieve a desired level of temporal accuracy which was specified as an input. The temporal resolution (in seconds) says how many seconds pass between each point that the STFT samples the frequency. Thus, any changes in frequency that happen faster than the temporal resolution will not be detected. It was important to maintain the temporal resolution below the rate at which the data changed from low frequency to high frequency. Per the Uncertainty Principle, the temporal resolution is a trade-off of spectral resolution, so increasing the temporal resolution would lower the spectral resolution, possibly to the point of losing the ability to distinguish between the sections of the signal.

{% highlight javascript linenos %}
# First determine the sampling frequency (fs)
# Convert to float by dividing a time delta by another TD
fs = datetime.timedelta(seconds=1) / (df[time_col].gather([1])[0] - df[time_col].gather([0])[0])

# Determine the samples per window and window overlap to get the desired temporal resolution
# https://dsp.stackexchange.com/questions/42428/understanding-overlapping-in-stft
# I did the math to determine the formula for nperseg and noverlap Assume we want 12.5% overlap (default from Scipy)
overlap_fraction = 0.125
nperseg = int(temporal_resolution * fs / (1-overlap_fraction))
noverlap = int(overlap_fraction*nperseg)

f, t, Sxx = spectrogram(y, fs, nperseg=nperseg, noverlap=noverlap, scaling="spectrum")

# Zoom the data to the range we care about (below max detection frequency)
max_detection_frequency = np.max(np.array(list(frequency_ranges.values())))
idx = f < max_detection_frequency*1.1
f, Sxx = f[idx], Sxx[idx, :]
{% endhighlight %}

# Resources

## Data-Driven Science and Engineering
[An excellent book](https://databookuw.com/) provided by Steven Brunton and Nathan Kutz, the online material included here gives a summary of all the requisite concepts to understand the analysis here. The actual PDF of the book is provided by them on their website, [here](https://databookuw.com/databook.pdf). The particularly relevant sections for this analysis are [Chapter 2: Dimensionality Reduction and Transforms](https://databookuw.com/page-2/page-21/), and [Chapter 5: Clustering and Classification](https://databookuw.com/page/page-8/).

## 3Blue1Brown
Created by mathematician Grant Sanderson, [3Blue1Brown](https://www.3blue1brown.com/) is a youtube channel that creates math visualizations and explanations to help people understand complex concepts.
**Relevant Lectures**
- [Fourier Series](https://www.youtube.com/watch?v=r6sGWTCMz2k)
- [Fourier Transform](https://www.youtube.com/watch?v=spUNpyF58BY)
- [Uncertainty Principle](https://www.youtube.com/watch?v=MBnnXbOM5S4)

## Veritasium 
Another science and math youtube channel, this time with a video on the history and implementation of the [Fast Fourier Transform](https://www.youtube.com/watch?v=nmgFG7PUHfo&t=892s)