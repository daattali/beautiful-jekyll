---
layout: post
title: Applying OPP Principles to Manufacturing Analytics Testing Data Generation
subtitle: From Separate Methods to a Unified Class
tags: [generated data, sensor data, time series, software development, oop]
comments: true
---

In this blog post, we will explore how to move away from procedure-based code and increase code usability by following object-oriented programming principles. To this end, we will refactor the code from one of our previous blog posts, namely [Generating Realistic Testing Data for Manufacturing Analytics Software](https://zhenev.github.io/2022-07-16-real-life-sensor-data-modeling/). By streamlining our code and incorporating OPP techniques, we aim to make the data generation process mentioned there more efficient, scalable, and easy to maintain for future development. Let's dive into the details and see how we can achieve this goal.


Our class will be called `FlowSensorDataGenerator`. Its goal is to generate realistic minute-wise demo data for a sensor such as electrical current sensors or flow meters in a batch manufacturing process. The data generation will consist of three steps:
1. Initializing a class object by providing basic parameters such as the lower and upper limits of the flow/current, the average duration of batches, the average time window between batches, and the start time of the time series.
2. Defining a mapping of parameters for four data generating patterns: regular, with omissions, with malfunctions, and zero time series.
3. Generating a combined time series.

The class will have several methods that generate different chunks of the overall time series, including:

- An internal method, `__generate_partial_data`, for generating regular data, data with omissions, or with malfunctions, based on a given number of batches and a pre-defined rate of irregularity occurrence, irregularity type, and its average length.
- An internal method, `__generate_zero_data`, for generating a zero time series to simulate the chunks of data when the equipment is off.
- The main method, `generate_data`, which takes a pre-defined mapping to combine different chunks of data from these four types mentioned above.
- A static internal method, `__generate_truncated_normal_vector`, which is used to add variability to the main process paramaters, such as batch duration.

The `current_time` variable is defined as part of the `__init__` method and is modified by each of the methods to combine the chunks of data into the final time series. The generated time series will be stored in the `generated_time_series` variable. We will add a visualization function as a class method as well.

Let's take a look at the implementation:

```python
class FlowSensorDataGenerator:
    """A class which generates batch-level minute-wise demo data for a sensor of a flow
    type, e.g. electrical current sensor or flow meter.
    
    The class takes in basic parameters: the lower and the upper limits of the flow / 
    current, average duration of batches and average time window between the batches,
    as well as time series start time."""
    
    def __init__(
        self,
        lower_bound: float,
        upper_bound: float,
        mean_duration: int,
        mean_window_size: int,
        start_time: datetime
    ):
        """
        :param mean_duration: average duration of each batch in minutes
        :param mean_duration: average time period between batches
        :param lower_bound: lower threshold value for the current data
        :param upper_bound: range for the current data values
        :param start_time: start of the time series
        """
        self.lower_bound = lower_bound
        self.upper_bound = upper_bound
        self.mean_duration = mean_duration
        self.mean_window_size = mean_window_size
        self.start_time = start_time
        
        self.current_time = start_time
        
    
    def __generate_partial_data(
        self,
        num_batches: int,
        irregularity_rate: float = 0,
        mean_irregularity_length: int = 0,
        irregularity_type: str = None,
    ) -> pd.DataFrame:
        """Generates data for a given number of batches, with pre-defined rate of
        irregularity occurrence, its type and average length.

        :param num_batches: number of batches to generate data for
        :param irregularity_rate: rate of irregularity occurrence (between 0 and 1)
        :param mean_irregularity_length: average time period of irregularity, in minutes
        :param irregularity_type: one of the two types, 'omission' or 'malfunction'

        :return: a time series dataframe, where values represent the current value
        """
        current_data = []
        if irregularity_type:
            irregularity_rate /= mean_irregularity_length
        i = 0
        j = 0
        while i < num_batches:
            duration = int(
                self.mean_duration*self.__generate_truncated_normal_vector(
                    1, 0.1, 1, 0, 2
                )[0]
            )
            window_size = int(
                self.mean_window_size*self.__generate_truncated_normal_vector(
                    1, 0.1, 1, 0, 3
                )[0]
            )
            while j < duration:
                if random.random() > irregularity_rate:
                    current_data.append((
                        self.current_time, random.uniform(
                            self.lower_bound, self.upper_bound
                        )
                    ))
                    self.current_time += timedelta(minutes=1)
                    j += 1
                else:
                    irregularity_length = int(
                        mean_irregularity_length*self.__generate_truncated_normal_vector(
                            1, 0.4, 1, 0, 2
                        )[0]
                    )
                    for m in range(irregularity_length):
                        irreg_coef = self.__generate_truncated_normal_vector(
                            1, 0.9, 1, 0, 100
                        )[0]
                        if irregularity_type == 'malfunction':
                            value = random.uniform(
                                self.lower_bound, self.upper_bound
                            )*irreg_coef
                        elif irregularity_type == 'omission':
                            value = np.NaN
                        current_data.append((
                            self.current_time + timedelta(minutes=m), value
                        ))  
                    self.current_time += timedelta(minutes=irregularity_length)
                    j += irregularity_length
            if j < duration + window_size:
                for m in range(duration + window_size - j):
                    current_data.append((self.current_time + timedelta(minutes=m), 0))
                self.current_time += timedelta(minutes=duration + window_size - j)
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
    
    def __generate_zero_data(self, period_length: int = 0) -> pd.DataFrame:
        """Generates zero time series of a pre-defined length"""
        current_data = []
        j = 0
        while j < period_length:
            current_data.append((self.current_time, 0))
            self.current_time += timedelta(minutes=1)
            j += 1
        current_data = pd.DataFrame(current_data)
        current_data = current_data.rename(
            columns = {0: 'time', 1: 'current'}
        ).set_index('time')
        return current_data
    
    def generate_data(self, pattern: dict) -> pd.DataFrame:
        """Generates a fully functional time series based on the pre-defined pattern"""
        df = pd.DataFrame()
        df = pd.concat([df, self.__generate_partial_data(*pattern['regular'])])
        df = pd.concat([df, self.__generate_partial_data(*pattern['omission'])])
        df = pd.concat([df, self.__generate_partial_data(*pattern['regular'])])
        df = pd.concat([df, self.__generate_partial_data(*pattern['malfunction'])])
        df = pd.concat([df, self.__generate_zero_data(pattern['off'])])
        
        self.generated_time_series = df.copy()
        
    def visualize_data(self):
        # Create a trace for the current data
        df = self.generated_time_series.reset_index()
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

    @staticmethod
    def __generate_truncated_normal_vector(
        mean: float,
        std_dev: float,
        size: int,
        lower_bound: float,
        upper_bound: float
    ) -> np.array:
        """Generates a vector of random values with a truncated normal distribution.

        Uses scipy.stats.truncnorm function to fit values into the specified bounds.

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

Now, we can chose and apply a pattern to generate a fully functional time series; we will generate regular batches, as well as the batches with omissions, in chunks of 30; to simulate equipment malfunctioning we will generate a short sequence of batches, e.g. of three, then we can add a chunk of zeroes to imitate equipment going off:

```python
pattern = {
    'regular': (30, 0, 0),
    'omission': (30, 0.1, 200, 'omission'),
    'malfunction': (3, 0.3, 20, 'malfunction'),
    'off': (600)
}
```
Note, that in the `generate_data` function, we utilize the `regular` patern twice, before and after generating the `omission` chunk.

As mentioned before, to initialize our data generator, we need to define the lower and the uppre limit of the values, average batch duration, average time window between batches, and the start time:

```python
dg = FlowSensorDataGenerator(
    10, 11, 120, 30,
    datetime.strptime(datetime.now().isoformat(timespec='minutes'), '%Y-%m-%dT%H:%M')
)
```
Let's generate the data and visualize it<sup>1</sup>:

```python
dg.generate_data(pattern)
dg.visualize_data()
```

<div id="myDiv_v1"></div>
<script>
  fetch('/assets/data/2022-08-06-full-viz.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v1', data);
    });
</script>

 
## Conclusion

The class introduced in this blog post, provides a convenient and flexible way to generate realistic demo data for the development of manufacturing analytics software for batch production. The generated time series simulate the complexities and irregularities of real-world data and can be fed into machine learning models and statistical analysis. The implementation of OOP principles, such as encapsulating methods into the class, makes the code more readable and reusable, while the class objects can be tailored to suit the specific needs of different manufacturing processes.

<sup>1</sup> The generated time series from this case study can be found [here](/assets/data/2022-08-06-generated-data.csv).

Copyright © 2022 Zheniya Mogilevski
