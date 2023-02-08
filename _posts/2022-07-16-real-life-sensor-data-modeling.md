---
layout: post
title: Generating Realistic Testing Data for Manufacturing Analytics Software
subtitle: Modeling Real-Life Data Imperfections
tags: [generated data, sensor data, time series, unit testing, tdd, data visualization]
comments: true
---

In the development of a software that includes data tools for providing analytics on batches in chemical manufacturing, the use of realistic testing data is critical to ensure accurate and reliable results. In this blog, we will exemplify how such testing data can be generated, starting with a basic example of "ideal batches" and then incorporating some deviations such as data outages, variability in process step implementation, and equipment malfunctioning. By using the resulting close-to-real data testing time series, one can ensure that even early versions of the software are able to handle real-world scenarios.

## Unit test

Before diving into the two implementations of the any data generating function, we will establish a unit test to ensure that the generated data meets the desired criteria. Our basic scenario will include generating electrical current data; we want to be able to choose the number of batches to generate data for, the approximate duration of each batch in minutes, the approximate time of transition between batches ("window size"), a `lower_bound`, which is the lower value for the current data, and the `upper_bound`, which defines the upper limit for the current data. Thus, in terms of a unit test, we would like to check if the function outputs the expected number of batches, with the correct duration, window size, and current values. It is important to note that if the test should check statistical parameters of randomly generated samples, it should employ `.assertAlmostEqual()`, `.assertTrue()`, and `.all()` methods.


The next test class verifies the basic functionality of the future `generate_current_data` function, i.e. that: the number of batches returned is as expected, the duration of each batch is as expected, and the window size and current parameters affect the generated data as expected. The setup of the parameters is done in the `setUp` method which is automatically called before each test.

```python

class TestGenerateCurrentData(unittest.TestCase):
    
    def setUp(self):
        self.num_batches = 10
        self.duration = 100
        self.window_size = 20
        self.lower_bound = 10
        self.upper_bound = 11
        self.tested_data = generate_current_data(
            self.num_batches,
            self.duration,
            self.window_size,
            self.lower_bound,
            self.upper_bound
        )

    def test_shape(self):
        self.assertEqual(
            len(self.tested_data),
            (self.num_batches*(self.duration + self.window_size))
        )

    def test_value_range(self):
        self.assertTrue(
            np.all(self.tested_data >= 0) and np.all(self.tested_data <= self.upper_bound)
        )
    
    def test_generate_current_data_batch_stats(self):
        batch_num, batch_avg_dur, avg_window = self.__slice_into_batches(self.tested_data)
        self.assertEqual(batch_num, self.num_batches)
        self.assertAlmostEqual(batch_avg_dur, self.duration, delta = 10)
        self.assertAlmostEqual(avg_window, self.window_size, delta = 10)
    
    @staticmethod
    def __slice_into_batches(df: pd.DataFrame):
        # Add a column indicating if the current is non-zero
        df['current_on'] = df['current'].apply(lambda x: False if x == 0 else True)
        # Add a column indicating if the current is zero
        df['current_off'] = df['current'].apply(lambda x: True if x == 0 else False)
        # Add a column indicating if the current state changed from the previous row
        df['state_changed'] = df['current_on'].ne(df['current_on'].shift())
        df['state_changed_to_on'] = np.where(
            df['current']* df['state_changed'], True, False
        )
        # Add a column indicating the batch number
        df['batch_number'] = df['state_changed_to_on'].cumsum()
        # number of batches
        batch_count = df['batch_number'].max()
        # average duration
        mean_duration = pd.pivot_table(
            df, index='batch_number', values='current_on', aggfunc='sum'
        ).mean()[0]
        # average window size between batches
        mean_window = pd.pivot_table(
            df, index='batch_number', values='current_off', aggfunc='sum'
        ).mean()[0]
        return batch_count, mean_duration, mean_window

if __name__ == '__main__':
    unittest.main()

```

## Ideal Batch Model

The first version of our current data generating function will represent an "ideal" case. The function is starting by initializing an empty list called `current_data`. It then is setting the start time to the **current time**. For each batch, the function is generatimg duration minutes of current data with values randomly between `lower_bound` and `upper_bound` using the `random.uniform` function. Then it is generating `window_size` minutes of current data with values equal to `0`. The start time is being updated after each iteration of the outer loop. Finally, the function is building and returning a pandas dataframe for which the current data is stored in the 'current' column and the time stamp is set to be the index.

```python

def generate_current_data(
        num_batches: int,
        duration: int,
        window_size: int,
        lower_bound: float,
        upper_bound: float
    ) -> pd.DataFrame:
    """Generate electricity current data for a given number of batches.

    :param num_batches: number of batches to generate data for
    :param duration: duration of each batch in minutes
    :param window_size: time period between batches
    :param lower_bound: lower threshold value for the current data
    :param upper_bound: range for the current data values

    :return: a time series dataframe, where values represent the current value
    """
    current_data = []
    start_time = datetime.strptime(
        datetime.now().isoformat(timespec='minutes'), '%Y-%m-%dT%H:%M'
    )
    for i in range(num_batches):
        for j in range(duration):
            current_data.append((
                start_time + timedelta(minutes=j),
                random.uniform(lower_bound, upper_bound)
            ))
        for j in range(window_size):
            current_data.append((start_time + timedelta(minutes=duration + j), 0))
        start_time = start_time + timedelta(minutes=duration + window_size)
    current_data = pd.DataFrame(current_data)
    current_data = current_data.rename(columns={0: 'time', 1: 'current'}).set_index('time')
    return current_data

```

Below is a function to visualize a timeseries dataframe using the `plotly` library:

```python
def visualize_current_data(df: pd.DataFrame):
    # Create a trace for the current data
    trace = go.Scatter(
        x=df.time,
        y=df.current,
        mode='lines',
        name='Current'
    )

    # Create a layout for the plot
    layout = go.Layout(
        title='Current Data',
        xaxis=dict(title='Time'),
        yaxis=dict(title='Current (A)')
    )

    # Create a Figure object
    fig = go.Figure(data=[trace], layout=layout)

    # Show the plot
    fig.show()
```

When we run the unit test, the generated dataframe meets the desired criteria:
```
============================= test session starts =============================
collecting ... collected 3 item

current.py::TestGenerateCurrentData::test_generate_current_data_batch_stats PASSED  [100%]
current.py::TestGenerateCurrentData::test_shape PASSED  [100%]
current.py::TestGenerateCurrentData::test_value_range PASSED  [100%]

============================== 1 passed in 0.039s ==============================

Process finished with exit code 0
```

Let's generate a time series with the `generate_current_data` function and plot it:

```python
# Generate current data
current_data = generate_current_data(
    num_batches=5,
    duration=30,
    window_size=5,
    lower_bound=10,
    upper_bound=11
).reset_index()
# Visualize
visualize_current_data(current_data)
```

<div id="myDiv_v1"></div>
<script>
  fetch('/assets/data/2022-07-16-basic.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v1', data);
    });
</script>

In this example, we are using the `generate_current_data` function to generate current data with `5` batches, each with a duration of `30` minutes, a window size of `5` minutes, and values between `10` and `11`. With more batches it can look as follows:

```python
visualize_current_data(generate_current_data(25, 120, 20, 10, 11))
```

<div id="myDiv_v2"></div>
<script>
  fetch('/assets/data/2022-07-16-basic-more-batches.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v2', data);
    });
</script>

## Introducing Data Omissions

Now, we need to take into acount that multiple reasons can lead to missing values appearing in the raw data. Let's take a look on how data omissions can be introduced into the `generate_current_data` function result:

```python
def generate_current_data(
        num_batches: int,
        duration: int,
        window_size: int,
        lower_bound: float,
        upper_bound: float,
        irregularity_rate: float
    ) -> pd.DataFrame:
    """Generate electricity current data for a given number of batches.

    :param num_batches: number of batches to generate data for
    :param duration: duration of each batch in minutes
    :param window_size: time period between batches
    :param lower_bound: lower threshold value for the current data
    :param upper_bound: range for the current data values
    :param irregularity_rate: rate of data omissions (between 0 and 1)

    :return: a time series dataframe, where values represent the current value
    """
    current_data = []
    start_time = datetime.strptime(
        datetime.now().isoformat(timespec='minutes'), '%Y-%m-%dT%H:%M'
    )
    for i in range(num_batches):
        for j in range(duration):
            if random.random() > irregularity_rate:
                current_data.append((
                    start_time + timedelta(minutes=j),
                    random.uniform(lower_bound, upper_bound)
                ))
            else:
                current_data.append((start_time + timedelta(minutes=j), None))
        for j in range(window_size):
            current_data.append((start_time + timedelta(minutes=duration + j), 0))
        start_time = start_time + timedelta(minutes=duration + window_size)
    current_data = pd.DataFrame(current_data)
    current_data = current_data.rename(
        columns = {0: 'time', 1: 'current'}
    ).set_index('time')
    return current_data
```

In this example, we added a parameter called `irregularity_rate` to the `generate_current_data` function and a check before appending each data point to the `current_data` list. This check works as follows: using the `random.random()` function which returns a random float between 0 and 1, we generate a random number; if this number is greater than the `irregularity_rate` passed to the function, we append the current data point to the `current_data` list; otherwise we are appending `None` to the list instead, indicating an omitted data point. The `irregularity_rate` parameter takes value between 0 and 1, which allows controlling the rate of data omissions in the generated data. To illustrate this version of the `generate_current_data` function, we passed a value of 0.3 to this parameter:

<div id="myDiv_v3"></div>
<script>
  fetch('/assets/data/2022-07-16-random-omissions.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v3', data);
    });
</script>


However, actually, the data omissions rarely take place randomly; thus, we should account for omissions of sequences of data points instead (or in addition to) of random data point omissions:

```python
def generate_current_data(
        num_batches: int,
        duration: int,
        window_size: int,
        lower_bound: float,
        upper_bound: float,
        irregularity_rate: float,
        irregularity_length: int
    ) -> pd.DataFrame:
    """Generate electricity current data for a given number of batches.

    :param num_batches: number of batches to generate data for
    :param duration: duration of each batch in minutes
    :param window_size: time period between batches
    :param lower_bound: lower threshold value for the current data
    :param upper_bound: range for the current data values
    :param irregularity_rate: rate of data omissions (between 0 and 1)
    :param irregularity_length: the length of the time period to omit data for in minutes

    :return: a time series dataframe, where values represent the current value
    """
    current_data = []
    irregularity_rate /= irregularity_length
    current_time = datetime.strptime(
        datetime.now().isoformat(timespec='minutes'), '%Y-%m-%dT%H:%M'
    )
    i = 0
    j = 0
    while i < num_batches:
        while j < duration:
            if random.random() > irregularity_rate:
                current_data.append((
                    current_time, random.uniform(lower_bound, upper_bound)
                ))
                current_time += timedelta(minutes=1)
                j += 1
            else:
                for m in range(irregularity_length):
                    current_data.append((current_time + timedelta(minutes=m), np.NaN))
                current_time += timedelta(minutes=irregularity_length)
                j += irregularity_length
        if j < duration + window_size:
            for m in range(duration + window_size - j):
                current_data.append((current_time + timedelta(minutes=m), 0))
            current_time += timedelta(minutes=duration + window_size - j)
            j = 0
            i = i + 1
        else:
            i = i + 1 + j//(duration + window_size)
            j = j - (duration + window_size) * j // (duration + window_size)
    current_data = pd.DataFrame(current_data)
    current_data = current_data.rename(
        columns = {0: 'time', 1: 'current'}
    ).set_index('time')
    return current_data

```

In this example, in addition to the `irregularity_rate` parameter, we are using a parameter called `irregularity_length` in the `generate_current_data` function. We are still checking the former before appending each data point to the `current_data` list; however, whenever the generated random number is lower than the `irregularity_rate` passed to the function, we are appending `irregularity_length` number of missing data points to the list instead, thus, leaving out a chunk of data. We then have to check whether the current batch is already over and account for the number of batches possibly skipped, to appropriately restart the regular data generation. To handel the grown complexity of the condition check and uncertain loop length, we swith to `while` loops. The `irregularity_rate` parameter still takes value between 0 and 1; it is normalized by the length of the period to be omitted at the very start of the function. To illustrate this version of the `generate_current_data` function, we passed a value of 0.1 to this parameter and the value of 200 to the `irregularity_length` parameter:

<div id="myDiv_v4"></div>
<script>
  fetch('/assets/data/2022-07-16-consecutive-omissions.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v4', data);
    });
</script>

## Variability in Process Step Duration

Now that we have seen how to generate test data for ideal batch sequences and incorporate omissions in it, it is important to acknowledge that it is hard to consider the chemical manufacturing process as a perfectly timed operation. There can be deviations in the timing of each process step, which can impact the overall accuracy of batch data analysis. To accurately reflect real-world conditions in our testing data, it is necessary to incorporate these delays into our generated test time series. To this end, we will first generate a random number from a truncated normal distribution to add variability to the `duration` parameter value:

```python

def generate_truncated_normal_vector(
    mean: float,
    std_dev: float,
    size: int,
    lower_bound: float,
    upper_bound: float
) -> np.array:
    """Generates a vector of random values with a truncated normal distribution.

    Uses scipy.stats.truncnorm function to truncate values outside the specified bounds.

    :param mean: the mean of the normal distribution.
    :param std_dev: the standard deviation of the normal distribution.
    :param size: the number of random values to generate.
    :param lower_bound: the lower bound of the truncation.
    :param upper_bound: the upper bound of the truncation.
    :return: a numpy vector.
    
    """
    return truncnorm(
        (lower_bound - mean) / std_dev,
        (upper_bound - mean) / std_dev,
        loc=mean,
        scale=std_dev
    ).rvs(size)
```

To adjust the `duration` parameter value, we can generate a 1-dimensional array from a distribution with the following parameter values:
- `mean=1`,
- `std_ved=0.2`,
- `lower_bound=0`,
- `upper_bound=2`.

```python
generate_truncated_normal_vector(1, 0.2, 1, 0, 2)[0]
```

The updated version of the `generate_current_data` function will look as follows:

```python
def generate_current_data(
        num_batches: int,
        mean_duration: int,
        window_size: int,
        lower_bound: float,
        upper_bound: float,
        irregularity_rate: float,
        irregularity_length: int
    ) -> pd.DataFrame:
    """Generate electricity current data for a given number of batches.

    :param num_batches: number of batches to generate data for
    :param mean_duration: average duration of batches in minutes
    :param window_size: time period between batches
    :param lower_bound: lower threshold value for the current data
    :param upper_bound: range for the current data values
    :param irregularity_rate: rate of data omissions (between 0 and 1)
    :param irregularity_length: the length of the time period to omit data for, in minutes

    :return: a time series dataframe, where values represent the current value
    """
    current_data = []
    irregularity_rate /= irregularity_length
    current_time = datetime.strptime(
        datetime.now().isoformat(timespec='minutes'), '%Y-%m-%dT%H:%M'
    )
    i = 0
    j = 0
    while i < num_batches:
        duration = int(mean_duration*generate_truncated_normal_vector(1, 0.2, 1, 0, 2)[0])
        while j < duration:
            if random.random() > irregularity_rate:
                current_data.append((
                    current_time, random.uniform(lower_bound, upper_bound)
                ))
                current_time += timedelta(minutes=1)
                j += 1
            else:
                for m in range(irregularity_length):
                    current_data.append((current_time + timedelta(minutes=m), np.NaN))
                current_time += timedelta(minutes=irregularity_length)
                j += irregularity_length
        if j < duration + window_size:
            for m in range(duration + window_size - j):
                current_data.append((current_time + timedelta(minutes=m), 0))
            current_time += timedelta(minutes=duration + window_size - j)
            j = 0
            i = i + 1
        else:
            i = i + 1 + j//(duration + window_size)
            j = j - (duration + window_size) * j // (duration + window_size)
    current_data = pd.DataFrame(current_data)
    current_data = current_data.rename(
        columns = {0: 'time', 1: 'current'}
    ).set_index('time')
    return current_data

```

We have refactored the `duration` parameter into `mean_duration` to correctly reflect its role of the batch average duration. Let's illustrate the difference in the generated time series:

<div id="myDiv_v5"></div>
<script>
  fetch('/assets/data/2022-07-16-consecutive-omissions-irreg.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v5', data);
    });
</script>

## Equipment Failures

When it comes to equipment failures, the sensor signal should either go off (in which case we are dealing with missing data again) or experience some major irregularities. We can use the same `generate_truncated_normal_vector` function to model signal irregularities of this kind, with more "extreme" values, e.g.:

```python
generate_truncated_normal_vector(1, 0.9, 1, 0, 100)[0]
```

We will apply the resulted random number as a multiplier, while generating regular current values instead of the missing values in the last version of the `generate_current_data` function:

```python
def generate_current_data(
        num_batches: int,
        mean_duration: int,
        window_size: int,
        lower_bound: float,
        upper_bound: float,
        irregularity_rate: float,
        irregularity_length: int
    ) -> pd.DataFrame:
    """Generate electricity current data for a given number of batches.

    :param num_batches: number of batches to generate data for
    :param duration: duration of each batch in minutes
    :param window_size: time period between batches
    :param lower_bound: lower threshold value for the current data
    :param upper_bound: range for the current data values
    :param irregularity_rate: rate of irregularity occurrence (between 0 and 1)
    :param irregularity_length: time period of irregularity, in minutes

    :return: a time series dataframe, where values represent the current value
    """
    current_data = []
    irregularity_rate /= irregularity_length
    current_time = datetime.strptime(
        datetime.now().isoformat(timespec='minutes'), '%Y-%m-%dT%H:%M'
    )
    i = 0
    j = 0
    while i < num_batches:
        duration = int(mean_duration*generate_truncated_normal_vector(1, 0.2, 1, 0, 2)[0])
        while j < duration:
            if random.random() > irregularity_rate:
                current_data.append((
                    current_time, random.uniform(lower_bound, upper_bound)
                ))
                current_time += timedelta(minutes=1)
                j += 1
            else:
                for m in range(irregularity_length):
                    irreg_coef = generate_truncated_normal_vector(1, 0.9, 1, 0, 100)[0]
                    current_data.append((
                        current_time + timedelta(minutes=m),
                        random.uniform(lower_bound, upper_bound)*irreg_coef
                    ))
                current_time += timedelta(minutes=irregularity_length)
                j += irregularity_length
        if j < duration + window_size:
            for m in range(duration + window_size - j):
                current_data.append((current_time + timedelta(minutes=m), 0))
            current_time += timedelta(minutes=duration + window_size - j)
            j = 0
            i = i + 1
        else:
            i = i + 1 + j//(duration + window_size)
            j = j - (duration + window_size) * j // (duration + window_size)
    current_data = pd.DataFrame(current_data)
    current_data = current_data.rename(
        columns = {0: 'time', 1: 'current'}
    ).set_index('time')
    return current_data
```

Now, the `irregularity_rate` parameter controls the frequency with which the data exhibit equipment malfunctioning behaviour. By using different combination of the parameters we can change the resulting irregularity pattern:

<div id="myDiv_v6"></div>
<script>
  fetch('/assets/data/2022-07-16-consecutive-omissions-irreg-fail.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v6', data);
    });
</script>
 
## Conclusion

In this blog post, we examined the three most common irregularities in real-world sensor data for chemical manufacturing batches. These include variations in batch duration, missing chunks of data, and equipment malfunctions. The actual time series can be a combination of these irregularities, including varying batch durations and the presence or absence of missing data and equipment malfunctions in different proportions.

As far as the data quality is concerned, variability should be introduced to the time window between the batches and to the length of irregularity periods. One additional feature to consider can be simulating load patterns within batches. This can help to replicate real-world scenarios where there may be varying levels of equipment utilization during specific process steps.

To further improve the code, we can:
- merge the three versions of the `generate_current_data` function into a single method;
- build a dedicated class and add additional methods as needed (the `generate_truncated_normal_vector` function should be one of them);
- improve test coverage to cover all the irregularity cases discussed above.

Copyright © 2022 Zheniya Mogilevski
