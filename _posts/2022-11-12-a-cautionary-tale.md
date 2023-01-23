---
layout: post
title: Comparing Distribution Differences of Generated Vectors - A cautionary tale
subtitle: Examining the impact of different methods on generated data
tags: [generated data, vectors, distributions, data visualization, statistical testing, nonparametric test, unit testing]
comments: true
---

This time, we will be implementing a function that generates vectors with a truncated normal distribution. We will be comparing two different versions of the function and examining the impact of the different methods used on the resulting distributions. 

## Unit test

Before diving into the two implementations of the function, it is important to establish a unit test to ensure that our generated vectors meet the desired criteria. In this case, we will be testing for the mean of the vector values, for the standard deviation, and the vector values being within a specified bound. It is important to note that the results of the random number generation are different each time we run the test; therefore, the test should check that the function is working correctly and that the statistical parameters of the generated samples are close to the expected values within certain tolerance. To this end, the test employes `.assertAlmostEqual()`, `.assertTrue()`, and `.all()` methods.

We will be setting the parameters of the distribution as global variables:

```python
MEAN = 0.5
STD_DEV = 0.3
SIZE = 1000
LOWER_BOUND = 0
UPPER_BOUND = 100

class TestTruncatedNormalVector(unittest.TestCase):
    def test_truncated_normal_vector(self):
	tests = [
	    {'version': 1},
	    {'version': 2}
	]
	for test in tests:
	    # Generate random values
	    random_values = truncated_normal_vector(
	    MEAN, STD_DEV, SIZE, LOWER_BOUND, UPPER_BOUND, test['version']
	    )

	    # Check that the mean of the values is close to the expected mean
	    self.assertAlmostEqual(random_values.mean(), MEAN, delta=0.1)

	    # Check that the SD of the values is close to the expected standard deviation
	    self.assertAlmostEqual(random_values.std(), STD_DEV, delta=0.1)

	    # Check that all values are within the specified bounds
	    self.assertTrue((random_values >= LOWER_BOUND).all())
	    self.assertTrue((random_values <= UPPER_BOUND).all())

if __name__ == '__main__':
	unittest.main()
```

## Verison 1

The first version of the function uses the numpy library to generate the vectors with a truncated normal distribution. It takes in the mean, standard deviation, vector length, lower and upper bounds as parameters, generates a set of values from a normal distribution and employes `.clip()` method to  limit the values of the array within the specified range.

```python
def truncated_normal_vector(
    mean: float,
    std_dev: float,
    size: int,
    lower_bound: float,
    upper_bound: float,
    version: int
) -> np.array:
    """Generates a vector of random values with a truncated normal distribution.

    Version 1: Uses random.normal function to generate random values with a normal distribution,
    and the .clip() method to truncate values outside the specified bounds.

    :param mean: the mean of the normal distribution.
    :param std_dev: the standard deviation of the normal distribution.
    :param size: the number of random values to generate.
    :param lower_bound: the lower bound of the truncation.
    :param upper_bound: the upper bound of the truncation.
	  :param version: can take values 1 or 2.
    :return: a numpy vector.
    """
    
    if version==1:
    	return np.random.normal(mean, std_dev, size).clip(lower_bound, upper_bound)
```

## Version 2

The second version of the function uses a different method to generate the vectors with a truncated normal distribution. It still takes in the same parameters as the first version, but employes [`truncnorm`](https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.truncnorm.html) function of the `scipy.stats` library.

``` python
def truncated_normal_vector_clip(
    mean: float,
    std_dev: float,
    size: int,
    lower_bound: float,
    upper_bound: float,
    version: int
) -> np.array:
    """Generates a vector of random values with a truncated normal distribution.
    
    Version 1: Uses random.normal function to generate random values with a normal
    distribution, and the .clip() method to truncate values outside the specified bounds.
	
    Version 2: Uses truncnorm function to generate random values directly from a
    truncated normal distribution.

    :param mean: the mean of the normal distribution.
    :param std_dev: the standard deviation of the normal distribution.
    :param size: the number of random values to generate.
    :param lower_bound: the lower bound of the truncation.
    :param upper_bound: the upper bound of the truncation.
	  :param version: can take values 1 or 2.
    :return: a numpy vector.
    """
    if version==1:
    	return np.random.normal(mean, std_dev, size).clip(lower_bound, upper_bound)
    if version==2:
    	return truncnorm(
	    (lower_bound - mean) / std_dev, (upper_bound - mean) / std_dev,
	    loc=mean,
	    scale=std_dev
	).rvs(size)
```

## Testing

When we run the unit test, the generated vectors meet the desired criteria for bith versions:

```
============================= test session starts =============================
collecting ... collected 1 item

trunc_norm_vector.py::TestTruncatedNormalVector::test_truncated_normal_vector PASSED  [100%]

============================== 1 passed in 0.49s ==============================

Process finished with exit code 0
```

On the surface, it may seem that the two versions of the function have produced similar results. However, a closer examination of the distributions may reveal a difference. Let's make a visual check: in order to truly understand the impact of the different methods used in the two versions of the function, it is important to make a visual check of the distributions.

## Plotting the results

We will be using the plotly library to create histograms of the generated vectors for both versions of the function.

``` python
import plotly.graph_objects as go

def truncated_normal_vector_viz(data: pd.DataFrame):
    # Plot histogram of random values using plotly
    fig = go.Figure(data=[go.Histogram(x=data, nbinsx=50)])
    fig.update_layout(
        title='Histogram of Truncated Normal Distribution',
	xaxis_title='Value',
	yaxis_title='Frequency'
    )
    fig.show()
```

The histogram of the vector generated by the first version of the function:
 
``` python
random_values_v1 = truncated_normal_vector(
    MEAN, STD_DEV, SIZE, LOWER_BOUND, UPPER_BOUND, version=1
)  # version 1 of the function
truncated_normal_vector_viz(random_values_v1)

```
<div id="myDiv_v1"></div>
<script>
  fetch('/assets/data/2022-11-12-version_1.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v1', data);
    });
</script>

The histogram of the vector generated by the second version of the function:
 
``` python
random_values_v2 = truncated_normal_vector(
    MEAN, STD_DEV, SIZE, LOWER_BOUND, UPPER_BOUND, version=2
)  # version 2 of the function
truncated_normal_vector_viz(random_values_v2)

```
<div id="myDiv_v2"></div>
<script>
  fetch('/assets/data/2022-11-12-version_2.json')
    .then(response => response.json())
    .then(data => {
      Plotly.newPlot('myDiv_v2', data);
    });
</script>

One can observe that, altough the basic statistics of the two distributions are similar and both functions pass the unit test, a visual examination reveals that there is a slight difference in the shape of the distributions. We can even test these two distributions for statistical difference.

## Statistical testing

To confirm that the difference in the distributions is statistically significant, we can use a nonparametric two-sample Kolmogorov-Smirnov test, which compares the distributions of two samples without making any assumption about the underlying distribution of the data. The test statistic is the maximum difference between the cumulative distribution function of the two samples and the p-value is the probability of observing a test statistic as extreme as the one computed from the samples, under the assumption that the two samples come from the same distribution. Thus:
1. The null hypothesis is that the two samples have the same distribution;
2. The alternative hypothesis is that the two samples come from different distrubutions;
3. The test is done using a significance level (alpha) of 0.05.

In our example, the two sample of data are generated by the two different versions of the `truncated_normal_vector` function. We will use the [`ks_2samp`](https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.ks_2samp.html) implementation of the test from  the `scipy.stats` library:


```python
from scipy.stats import ks_2samp

# Perform two-sample Kolmogorov-Smirnov test
statistic, p_value = ks_2samp(random_values_v1, random_values_v2)

# Print results
print(f'KS-statistic: {statistic:.3f}, p-value: {p_value:.3f}')

# Interpret the results
alpha = 0.05
if p_value < alpha:
    print('The two distributions are different (reject H0)')
else:
    print('The two distributions are the same (fail to reject H0)')
```

The output of the test states the following:

```
KS-statistic: 0.083, p-value: 0.002
The two distributions are different (reject H0)
```

## Conclusion

This example highlights the importance of being aware and careful about the methods chosen to generate data, as even small differences in the methods used can result in significant differences in the resulting distributions. It may be important to not only rely on basic statistics, but also make a visual check and even use statistical tests to confirm the difference in distributions. In our example, the ultimate reason for the observed deference is one peculiarity of the [`.clip()`](https://numpy.org/doc/stable/reference/generated/numpy.clip.html) method: any value in the array that is less than `lower_bound` will be set to `lower_bound`, and any value that is greater than `upper_bound` will be set to `upper_bound`.

Copyright © 2021 Zheniya Mogilevski
