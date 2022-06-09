---
layout: post
title: Energy Consumption Analysis
subtitle: Exploratory Data Analysis - EDA
gh-repo: leopqrz/leopqrz.github.io
gh-badge: [star, fork, follow]
tags: [EDA, Exploratory Data Analysis, Energy, Weather]
comments: false
---

---

<center> <h1> <span style='color:#292D78'> Energy Consumption Analysis </span> </h1> </center>

<center> <h3> <span style='color:#DF7F00'> Exploratory Data Analysis - EDA </span> </h3> </center>

---

In this [Jupyter Notebook](https://jupyter.org/install) we will analyze the [energy consumption of different sources](https://www.kaggle.com/datasets/nicholasjhana/energy-consumption-generation-prices-and-weather) from Spain.

# Energy Consumption Analysis

Using a [dataset](https://www.kaggle.com/datasets/nicholasjhana/energy-consumption-generation-prices-and-weather) of energy consumption in Spain, we will use statistic techniques to extract insightful information with data manipulation and visualization.

## Context

In a [paper released early 2019](https://arxiv.org/abs/1906.05433), forecasting in energy markets is identified as one of the highest leverage contribution areas of Machine/Deep Learning toward transitioning to a renewable based electrical infrastructure.

## Content

This dataset contains 4 years of electrical consumption, generation, pricing, and weather data for Spain. Consumption and generation data was retrieved from ENTSOE, a public portal for Transmission Service Operator (TSO) data. Settlement prices were obtained from the Spanish TSO Red Electric España. Weather data was purchased as part of a personal project from the Open Weather API for the 5 largest cities in Spain and made public here.

## Acknowledgements

This data is publicly available via ENTSOE and REE and may be found in the links above.

## The Data

This is a dataset containing two files, `energy_dataset.csv` and the `weather_features.csv`.

### Energy Dataset

The energy dataset contains 29 columns:

* ``time``: datetime index localized to CET
* ``generation biomass``: generated biomass energy in MW
* ``generation fossil brown coal/lignite``: generated coal energy in MW
* ``generation fossil coal-derived gas``: generated coal-derived gas energy in MW
* ``generation fossil gas``: generated natural gas energy in MW
* ``generation fossil hard coal``: generated hard coal energy in MW
* ``generation fossil oil``: generated conventional oil energy in MW
* ``generation fossil oil shale``: generated unconventional oil energy in MW
* ``generation fossil peat``: generated peat energy in MW
* ``generation geothermal``: generated geothermal energy in MW
* ``generation hydro pumped storage aggregated``: generated hydro pumped storage aggregated energy in MW
* ``generation hydro pumped storage consumption``: generated hydro pumped storage consumption energy in MW
* ``generation hydro run-of-river and poundage``: generated hydro run-of-river and poundage energy in MW
* ``generation hydro water reservoir``: generated hydro water reservoir energy in MW
* ``generation marine``: generated marine (wave) energy in MW
* ``generation nuclear``: generated nuclear energy in MW
* ``generation other``: other non-renewable sources of energy in MW
* ``generation other renewable``: other renewable sources of energy in MW
* ``generation solar``: generated solar energy in MW
* ``generation waste``: generated waste energy in MW
* ``generation wind offshore``: generated wind (offshore) energy in MW
* ``generation wind onshore``: generated wind (onshore) energy in MW
* ``forecast solar day ahead``: forecasted solar energy generation
* ``forecast wind offshore eday ahead``: forecasted offshore wind generation
* ``forecast wind onshore day ahead``: forecasted onshore wind generation
* ``total load forecast``: forecasted electrical demand
* ``total load actual``: actual electrical demand
* ``price day ahead``: forecasted price EUR/MWh
* ``price actual``: price in EUR/MWh

### Weather Features

The weather datset contains 17 columns:

* ``dt_iso``: datetime index localized to CET
* ``city_name``: name of city
* ``temp``: temperature in k (Kelvin)
* ``temp_min``: minimum in k
* ``temp_max``: maximum in k
* ``pressure``: pressure in hPa
* ``humidity``: humidity in %
* ``wind_speed``: wind speed in m/s
* ``wind_deg``: wind direction
* ``rain_1h``: rain in last hour in mm
* ``rain_3h``: rain last 3 hours in mm
* ``snow_3h``: show last 3 hours in mm
* ``clouds_all``: cloud cover in %
* ``weather_id``: Code used to describe weather
* ``weather_main``: Short description of current weather
* ``weather_description``: Long description of current weather
* ``weather_icon``: Weather icon code for website

# Data Analysis

We will simplify the data for the analysis, by combining columns and grouping by year and month.

## Loading the data


```python
# To supress warnings and deprecated messages
import warnings

warnings.filterwarnings("ignore")

# Core
import numpy as np
import pandas as pd

# Visualization
import seaborn as sns
import matplotlib.pyplot as plt

%matplotlib inline
```


```python
energy = pd.read_csv("energy_dataset.csv")
energy
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>generation biomass</th>
      <th>generation fossil brown coal/lignite</th>
      <th>generation fossil coal-derived gas</th>
      <th>generation fossil gas</th>
      <th>generation fossil hard coal</th>
      <th>generation fossil oil</th>
      <th>generation fossil oil shale</th>
      <th>generation fossil peat</th>
      <th>generation geothermal</th>
      <th>...</th>
      <th>generation waste</th>
      <th>generation wind offshore</th>
      <th>generation wind onshore</th>
      <th>forecast solar day ahead</th>
      <th>forecast wind offshore eday ahead</th>
      <th>forecast wind onshore day ahead</th>
      <th>total load forecast</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2015-01-01 00:00:00+01:00</td>
      <td>447.0</td>
      <td>329.0</td>
      <td>0.0</td>
      <td>4844.0</td>
      <td>4821.0</td>
      <td>162.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>196.0</td>
      <td>0.0</td>
      <td>6378.0</td>
      <td>17.0</td>
      <td>NaN</td>
      <td>6436.0</td>
      <td>26118.0</td>
      <td>25385.0</td>
      <td>50.10</td>
      <td>65.41</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 01:00:00+01:00</td>
      <td>449.0</td>
      <td>328.0</td>
      <td>0.0</td>
      <td>5196.0</td>
      <td>4755.0</td>
      <td>158.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>195.0</td>
      <td>0.0</td>
      <td>5890.0</td>
      <td>16.0</td>
      <td>NaN</td>
      <td>5856.0</td>
      <td>24934.0</td>
      <td>24382.0</td>
      <td>48.10</td>
      <td>64.92</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 02:00:00+01:00</td>
      <td>448.0</td>
      <td>323.0</td>
      <td>0.0</td>
      <td>4857.0</td>
      <td>4581.0</td>
      <td>157.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>196.0</td>
      <td>0.0</td>
      <td>5461.0</td>
      <td>8.0</td>
      <td>NaN</td>
      <td>5454.0</td>
      <td>23515.0</td>
      <td>22734.0</td>
      <td>47.33</td>
      <td>64.48</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 03:00:00+01:00</td>
      <td>438.0</td>
      <td>254.0</td>
      <td>0.0</td>
      <td>4314.0</td>
      <td>4131.0</td>
      <td>160.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>191.0</td>
      <td>0.0</td>
      <td>5238.0</td>
      <td>2.0</td>
      <td>NaN</td>
      <td>5151.0</td>
      <td>22642.0</td>
      <td>21286.0</td>
      <td>42.27</td>
      <td>59.32</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 04:00:00+01:00</td>
      <td>428.0</td>
      <td>187.0</td>
      <td>0.0</td>
      <td>4130.0</td>
      <td>3840.0</td>
      <td>156.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>189.0</td>
      <td>0.0</td>
      <td>4935.0</td>
      <td>9.0</td>
      <td>NaN</td>
      <td>4861.0</td>
      <td>21785.0</td>
      <td>20264.0</td>
      <td>38.41</td>
      <td>56.04</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>35059</th>
      <td>2018-12-31 19:00:00+01:00</td>
      <td>297.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>7634.0</td>
      <td>2628.0</td>
      <td>178.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>277.0</td>
      <td>0.0</td>
      <td>3113.0</td>
      <td>96.0</td>
      <td>NaN</td>
      <td>3253.0</td>
      <td>30619.0</td>
      <td>30653.0</td>
      <td>68.85</td>
      <td>77.02</td>
    </tr>
    <tr>
      <th>35060</th>
      <td>2018-12-31 20:00:00+01:00</td>
      <td>296.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>7241.0</td>
      <td>2566.0</td>
      <td>174.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>280.0</td>
      <td>0.0</td>
      <td>3288.0</td>
      <td>51.0</td>
      <td>NaN</td>
      <td>3353.0</td>
      <td>29932.0</td>
      <td>29735.0</td>
      <td>68.40</td>
      <td>76.16</td>
    </tr>
    <tr>
      <th>35061</th>
      <td>2018-12-31 21:00:00+01:00</td>
      <td>292.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>7025.0</td>
      <td>2422.0</td>
      <td>168.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>286.0</td>
      <td>0.0</td>
      <td>3503.0</td>
      <td>36.0</td>
      <td>NaN</td>
      <td>3404.0</td>
      <td>27903.0</td>
      <td>28071.0</td>
      <td>66.88</td>
      <td>74.30</td>
    </tr>
    <tr>
      <th>35062</th>
      <td>2018-12-31 22:00:00+01:00</td>
      <td>293.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>6562.0</td>
      <td>2293.0</td>
      <td>163.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>287.0</td>
      <td>0.0</td>
      <td>3586.0</td>
      <td>29.0</td>
      <td>NaN</td>
      <td>3273.0</td>
      <td>25450.0</td>
      <td>25801.0</td>
      <td>63.93</td>
      <td>69.89</td>
    </tr>
    <tr>
      <th>35063</th>
      <td>2018-12-31 23:00:00+01:00</td>
      <td>290.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>6926.0</td>
      <td>2166.0</td>
      <td>163.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>287.0</td>
      <td>0.0</td>
      <td>3651.0</td>
      <td>26.0</td>
      <td>NaN</td>
      <td>3117.0</td>
      <td>24424.0</td>
      <td>24455.0</td>
      <td>64.27</td>
      <td>69.88</td>
    </tr>
  </tbody>
</table>
<p>35064 rows × 29 columns</p>
</div>




```python
weather = pd.read_csv("weather_features.csv")
weather
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>dt_iso</th>
      <th>city_name</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
      <th>weather_id</th>
      <th>weather_main</th>
      <th>weather_description</th>
      <th>weather_icon</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2015-01-01 00:00:00+01:00</td>
      <td>Valencia</td>
      <td>270.475</td>
      <td>270.475</td>
      <td>270.475</td>
      <td>1001</td>
      <td>77</td>
      <td>1</td>
      <td>62</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 01:00:00+01:00</td>
      <td>Valencia</td>
      <td>270.475</td>
      <td>270.475</td>
      <td>270.475</td>
      <td>1001</td>
      <td>77</td>
      <td>1</td>
      <td>62</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 02:00:00+01:00</td>
      <td>Valencia</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>1002</td>
      <td>78</td>
      <td>0</td>
      <td>23</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 03:00:00+01:00</td>
      <td>Valencia</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>1002</td>
      <td>78</td>
      <td>0</td>
      <td>23</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 04:00:00+01:00</td>
      <td>Valencia</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>1002</td>
      <td>78</td>
      <td>0</td>
      <td>23</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>178391</th>
      <td>2018-12-31 19:00:00+01:00</td>
      <td>Seville</td>
      <td>287.760</td>
      <td>287.150</td>
      <td>288.150</td>
      <td>1028</td>
      <td>54</td>
      <td>3</td>
      <td>30</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>178392</th>
      <td>2018-12-31 20:00:00+01:00</td>
      <td>Seville</td>
      <td>285.760</td>
      <td>285.150</td>
      <td>286.150</td>
      <td>1029</td>
      <td>62</td>
      <td>3</td>
      <td>30</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>178393</th>
      <td>2018-12-31 21:00:00+01:00</td>
      <td>Seville</td>
      <td>285.150</td>
      <td>285.150</td>
      <td>285.150</td>
      <td>1028</td>
      <td>58</td>
      <td>4</td>
      <td>50</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>178394</th>
      <td>2018-12-31 22:00:00+01:00</td>
      <td>Seville</td>
      <td>284.150</td>
      <td>284.150</td>
      <td>284.150</td>
      <td>1029</td>
      <td>57</td>
      <td>4</td>
      <td>60</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>178395</th>
      <td>2018-12-31 23:00:00+01:00</td>
      <td>Seville</td>
      <td>283.970</td>
      <td>282.150</td>
      <td>285.150</td>
      <td>1029</td>
      <td>70</td>
      <td>3</td>
      <td>50</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
  </tbody>
</table>
<p>178396 rows × 17 columns</p>
</div>



## Checking data types

Using the method `info`:

### Energy data


```python
energy.info()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 35064 entries, 0 to 35063
    Data columns (total 29 columns):
     #   Column                                       Non-Null Count  Dtype  
    ---  ------                                       --------------  -----  
     0   time                                         35064 non-null  object 
     1   generation biomass                           35045 non-null  float64
     2   generation fossil brown coal/lignite         35046 non-null  float64
     3   generation fossil coal-derived gas           35046 non-null  float64
     4   generation fossil gas                        35046 non-null  float64
     5   generation fossil hard coal                  35046 non-null  float64
     6   generation fossil oil                        35045 non-null  float64
     7   generation fossil oil shale                  35046 non-null  float64
     8   generation fossil peat                       35046 non-null  float64
     9   generation geothermal                        35046 non-null  float64
     10  generation hydro pumped storage aggregated   0 non-null      float64
     11  generation hydro pumped storage consumption  35045 non-null  float64
     12  generation hydro run-of-river and poundage   35045 non-null  float64
     13  generation hydro water reservoir             35046 non-null  float64
     14  generation marine                            35045 non-null  float64
     15  generation nuclear                           35047 non-null  float64
     16  generation other                             35046 non-null  float64
     17  generation other renewable                   35046 non-null  float64
     18  generation solar                             35046 non-null  float64
     19  generation waste                             35045 non-null  float64
     20  generation wind offshore                     35046 non-null  float64
     21  generation wind onshore                      35046 non-null  float64
     22  forecast solar day ahead                     35064 non-null  float64
     23  forecast wind offshore eday ahead            0 non-null      float64
     24  forecast wind onshore day ahead              35064 non-null  float64
     25  total load forecast                          35064 non-null  float64
     26  total load actual                            35028 non-null  float64
     27  price day ahead                              35064 non-null  float64
     28  price actual                                 35064 non-null  float64
    dtypes: float64(28), object(1)
    memory usage: 7.8+ MB


Except for the column *time*, which is of the object type, all the columns are of the numeric type. 

We will fix the *time* column by converting it to datetime.


```python
energy['time'] = pd.to_datetime(energy['time'], format='%Y-%m-%d', utc=True)
print(energy.info())
energy.head()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 35064 entries, 0 to 35063
    Data columns (total 29 columns):
     #   Column                                       Non-Null Count  Dtype              
    ---  ------                                       --------------  -----              
     0   time                                         35064 non-null  datetime64[ns, UTC]
     1   generation biomass                           35045 non-null  float64            
     2   generation fossil brown coal/lignite         35046 non-null  float64            
     3   generation fossil coal-derived gas           35046 non-null  float64            
     4   generation fossil gas                        35046 non-null  float64            
     5   generation fossil hard coal                  35046 non-null  float64            
     6   generation fossil oil                        35045 non-null  float64            
     7   generation fossil oil shale                  35046 non-null  float64            
     8   generation fossil peat                       35046 non-null  float64            
     9   generation geothermal                        35046 non-null  float64            
     10  generation hydro pumped storage aggregated   0 non-null      float64            
     11  generation hydro pumped storage consumption  35045 non-null  float64            
     12  generation hydro run-of-river and poundage   35045 non-null  float64            
     13  generation hydro water reservoir             35046 non-null  float64            
     14  generation marine                            35045 non-null  float64            
     15  generation nuclear                           35047 non-null  float64            
     16  generation other                             35046 non-null  float64            
     17  generation other renewable                   35046 non-null  float64            
     18  generation solar                             35046 non-null  float64            
     19  generation waste                             35045 non-null  float64            
     20  generation wind offshore                     35046 non-null  float64            
     21  generation wind onshore                      35046 non-null  float64            
     22  forecast solar day ahead                     35064 non-null  float64            
     23  forecast wind offshore eday ahead            0 non-null      float64            
     24  forecast wind onshore day ahead              35064 non-null  float64            
     25  total load forecast                          35064 non-null  float64            
     26  total load actual                            35028 non-null  float64            
     27  price day ahead                              35064 non-null  float64            
     28  price actual                                 35064 non-null  float64            
    dtypes: datetime64[ns, UTC](1), float64(28)
    memory usage: 7.8 MB
    None





<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>generation biomass</th>
      <th>generation fossil brown coal/lignite</th>
      <th>generation fossil coal-derived gas</th>
      <th>generation fossil gas</th>
      <th>generation fossil hard coal</th>
      <th>generation fossil oil</th>
      <th>generation fossil oil shale</th>
      <th>generation fossil peat</th>
      <th>generation geothermal</th>
      <th>...</th>
      <th>generation waste</th>
      <th>generation wind offshore</th>
      <th>generation wind onshore</th>
      <th>forecast solar day ahead</th>
      <th>forecast wind offshore eday ahead</th>
      <th>forecast wind onshore day ahead</th>
      <th>total load forecast</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>447.0</td>
      <td>329.0</td>
      <td>0.0</td>
      <td>4844.0</td>
      <td>4821.0</td>
      <td>162.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>196.0</td>
      <td>0.0</td>
      <td>6378.0</td>
      <td>17.0</td>
      <td>NaN</td>
      <td>6436.0</td>
      <td>26118.0</td>
      <td>25385.0</td>
      <td>50.10</td>
      <td>65.41</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>449.0</td>
      <td>328.0</td>
      <td>0.0</td>
      <td>5196.0</td>
      <td>4755.0</td>
      <td>158.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>195.0</td>
      <td>0.0</td>
      <td>5890.0</td>
      <td>16.0</td>
      <td>NaN</td>
      <td>5856.0</td>
      <td>24934.0</td>
      <td>24382.0</td>
      <td>48.10</td>
      <td>64.92</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>448.0</td>
      <td>323.0</td>
      <td>0.0</td>
      <td>4857.0</td>
      <td>4581.0</td>
      <td>157.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>196.0</td>
      <td>0.0</td>
      <td>5461.0</td>
      <td>8.0</td>
      <td>NaN</td>
      <td>5454.0</td>
      <td>23515.0</td>
      <td>22734.0</td>
      <td>47.33</td>
      <td>64.48</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>438.0</td>
      <td>254.0</td>
      <td>0.0</td>
      <td>4314.0</td>
      <td>4131.0</td>
      <td>160.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>191.0</td>
      <td>0.0</td>
      <td>5238.0</td>
      <td>2.0</td>
      <td>NaN</td>
      <td>5151.0</td>
      <td>22642.0</td>
      <td>21286.0</td>
      <td>42.27</td>
      <td>59.32</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>428.0</td>
      <td>187.0</td>
      <td>0.0</td>
      <td>4130.0</td>
      <td>3840.0</td>
      <td>156.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>189.0</td>
      <td>0.0</td>
      <td>4935.0</td>
      <td>9.0</td>
      <td>NaN</td>
      <td>4861.0</td>
      <td>21785.0</td>
      <td>20264.0</td>
      <td>38.41</td>
      <td>56.04</td>
    </tr>
  </tbody>
</table>
<p>5 rows × 29 columns</p>
</div>



### Weather Features


```python
weather.info()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 178396 entries, 0 to 178395
    Data columns (total 17 columns):
     #   Column               Non-Null Count   Dtype  
    ---  ------               --------------   -----  
     0   dt_iso               178396 non-null  object 
     1   city_name            178396 non-null  object 
     2   temp                 178396 non-null  float64
     3   temp_min             178396 non-null  float64
     4   temp_max             178396 non-null  float64
     5   pressure             178396 non-null  int64  
     6   humidity             178396 non-null  int64  
     7   wind_speed           178396 non-null  int64  
     8   wind_deg             178396 non-null  int64  
     9   rain_1h              178396 non-null  float64
     10  rain_3h              178396 non-null  float64
     11  snow_3h              178396 non-null  float64
     12  clouds_all           178396 non-null  int64  
     13  weather_id           178396 non-null  int64  
     14  weather_main         178396 non-null  object 
     15  weather_description  178396 non-null  object 
     16  weather_icon         178396 non-null  object 
    dtypes: float64(6), int64(6), object(5)
    memory usage: 23.1+ MB


Most of the columns are numeric. *dt_iso*, *city_name*, *weather_main*, *weather_description*, and *weather_icon* are of the object type. We will convert *dt_iso* to the datetime type and rename it as *time*:


```python
weather['dt_iso'] = pd.to_datetime(weather['dt_iso'], format='%Y-%m-%d', utc=True)
weather.rename(columns={'dt_iso':'time'}, inplace=True)
print(weather.info())
weather.head()
```

    <class 'pandas.core.frame.DataFrame'>
    RangeIndex: 178396 entries, 0 to 178395
    Data columns (total 17 columns):
     #   Column               Non-Null Count   Dtype              
    ---  ------               --------------   -----              
     0   time                 178396 non-null  datetime64[ns, UTC]
     1   city_name            178396 non-null  object             
     2   temp                 178396 non-null  float64            
     3   temp_min             178396 non-null  float64            
     4   temp_max             178396 non-null  float64            
     5   pressure             178396 non-null  int64              
     6   humidity             178396 non-null  int64              
     7   wind_speed           178396 non-null  int64              
     8   wind_deg             178396 non-null  int64              
     9   rain_1h              178396 non-null  float64            
     10  rain_3h              178396 non-null  float64            
     11  snow_3h              178396 non-null  float64            
     12  clouds_all           178396 non-null  int64              
     13  weather_id           178396 non-null  int64              
     14  weather_main         178396 non-null  object             
     15  weather_description  178396 non-null  object             
     16  weather_icon         178396 non-null  object             
    dtypes: datetime64[ns, UTC](1), float64(6), int64(6), object(4)
    memory usage: 23.1+ MB
    None





<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>city_name</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
      <th>weather_id</th>
      <th>weather_main</th>
      <th>weather_description</th>
      <th>weather_icon</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>Valencia</td>
      <td>270.475</td>
      <td>270.475</td>
      <td>270.475</td>
      <td>1001</td>
      <td>77</td>
      <td>1</td>
      <td>62</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>Valencia</td>
      <td>270.475</td>
      <td>270.475</td>
      <td>270.475</td>
      <td>1001</td>
      <td>77</td>
      <td>1</td>
      <td>62</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>Valencia</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>1002</td>
      <td>78</td>
      <td>0</td>
      <td>23</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>Valencia</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>1002</td>
      <td>78</td>
      <td>0</td>
      <td>23</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>Valencia</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>269.686</td>
      <td>1002</td>
      <td>78</td>
      <td>0</td>
      <td>23</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0</td>
      <td>800</td>
      <td>clear</td>
      <td>sky is clear</td>
      <td>01n</td>
    </tr>
  </tbody>
</table>
</div>




```python
print('Date range for Energy data:')
print(energy['time'].min())
print(energy['time'].max())

```

    Date range for Energy data:
    2014-12-31 23:00:00+00:00
    2018-12-31 22:00:00+00:00



```python
print('Date range for Weather data:')
print(weather['time'].min())
print(weather['time'].max())

```

    Date range for Weather data:
    2014-12-31 23:00:00+00:00
    2018-12-31 22:00:00+00:00


Both data have the same date range.

### Weather

Before extracting year, month, and day from the weather dataframe, we will understand it better. How many different cities there are in the data?


```python
print(weather['city_name'].unique())
print('Number of cities: ', weather['city_name'].nunique())

```

    ['Valencia' 'Madrid' 'Bilbao' ' Barcelona' 'Seville']
    Number of cities:  5


There are 5 different cities in the data (Valencia, Madrid, Bilbao, Barcelona, Seville) meaning that the weather information are from these locations. However, the generation data (energy) contains the total energy production in Spain.

To match the structure of the files we have, we can average the weather columns (the numeric ones) over the dates and assume that they are the mean weather of Spain for that specific time.


```python
print(energy.shape[0])
print(weather.shape[0]/5)
```

    35064
    35679.2


Apparently, at least one of the cities may have more dates than the production data.

### Check, for all cities, how many rows of data they have


```python
weather['city_name'][weather['city_name']==' Barcelona'] = 'Barcelona'
weather.groupby(weather['city_name'])['city_name'].count()
```




    city_name
    Barcelona    35476
    Bilbao       35951
    Madrid       36267
    Seville      35557
    Valencia     35145
    Name: city_name, dtype: int64



Apparently, all the cities have at least slight more data than the energy production data. We need further analysis to understand the reason.

### Grouping the Weather Data

Now, the next step is to average the numeric weather info for each date. So, we just need to `groupby` the data by *time* and compute the mean.


```python
new_weather = weather.groupby(weather['time'], as_index=False).mean()
new_weather.head()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
      <th>weather_id</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>272.491463</td>
      <td>272.491463</td>
      <td>272.491463</td>
      <td>1016.4</td>
      <td>82.4</td>
      <td>2.0</td>
      <td>135.2</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>800.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>272.512700</td>
      <td>272.512700</td>
      <td>272.512700</td>
      <td>1016.2</td>
      <td>82.4</td>
      <td>2.0</td>
      <td>135.8</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>800.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>272.099137</td>
      <td>272.099137</td>
      <td>272.099137</td>
      <td>1016.8</td>
      <td>82.0</td>
      <td>2.4</td>
      <td>119.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>800.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>272.089469</td>
      <td>272.089469</td>
      <td>272.089469</td>
      <td>1016.6</td>
      <td>82.0</td>
      <td>2.4</td>
      <td>119.2</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>800.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>272.145900</td>
      <td>272.145900</td>
      <td>272.145900</td>
      <td>1016.6</td>
      <td>82.0</td>
      <td>2.4</td>
      <td>118.4</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>800.0</td>
    </tr>
  </tbody>
</table>
</div>




```python
print(new_weather.shape[0])
print(energy.shape[0])
```

    35064
    35064


Now the number of rows is the same for both data files.

## Sum columns

In this part, to make the analysis easier, let's sum together, in the energy dataframe, the production of fossils derivative in one column, renewable in others, and so on.

First, let's select all the column names that contain the word *fossil*. To extract the columns names from a dataframe:

```python
df.columns

or

list(df)
```

Let's use the second option, as we are sure that they will be extracted to a list.


```python
cols = list(energy)
cols
```




    ['time',
     'generation biomass',
     'generation fossil brown coal/lignite',
     'generation fossil coal-derived gas',
     'generation fossil gas',
     'generation fossil hard coal',
     'generation fossil oil',
     'generation fossil oil shale',
     'generation fossil peat',
     'generation geothermal',
     'generation hydro pumped storage aggregated',
     'generation hydro pumped storage consumption',
     'generation hydro run-of-river and poundage',
     'generation hydro water reservoir',
     'generation marine',
     'generation nuclear',
     'generation other',
     'generation other renewable',
     'generation solar',
     'generation waste',
     'generation wind offshore',
     'generation wind onshore',
     'forecast solar day ahead',
     'forecast wind offshore eday ahead',
     'forecast wind onshore day ahead',
     'total load forecast',
     'total load actual',
     'price day ahead',
     'price actual']



First, let's only select the elements of the list that contain the word *generation* using conditions in a *list comprehension*.


```python
cols_gen = [col for col in cols if 'generation' in col]
cols_gen
```




    ['generation biomass',
     'generation fossil brown coal/lignite',
     'generation fossil coal-derived gas',
     'generation fossil gas',
     'generation fossil hard coal',
     'generation fossil oil',
     'generation fossil oil shale',
     'generation fossil peat',
     'generation geothermal',
     'generation hydro pumped storage aggregated',
     'generation hydro pumped storage consumption',
     'generation hydro run-of-river and poundage',
     'generation hydro water reservoir',
     'generation marine',
     'generation nuclear',
     'generation other',
     'generation other renewable',
     'generation solar',
     'generation waste',
     'generation wind offshore',
     'generation wind onshore']



Now we can separate the elements that contain the word *fossil* and the ones that don't (which are the renewable energy).


```python
cols_fossil = [col for col in cols_gen if 'fossil' in col]
cols_fossil

```




    ['generation fossil brown coal/lignite',
     'generation fossil coal-derived gas',
     'generation fossil gas',
     'generation fossil hard coal',
     'generation fossil oil',
     'generation fossil oil shale',
     'generation fossil peat']




```python
cols_renew = [col for col in cols_gen if 'fossil' not in col]
cols_renew
```




    ['generation biomass',
     'generation geothermal',
     'generation hydro pumped storage aggregated',
     'generation hydro pumped storage consumption',
     'generation hydro run-of-river and poundage',
     'generation hydro water reservoir',
     'generation marine',
     'generation nuclear',
     'generation other',
     'generation other renewable',
     'generation solar',
     'generation waste',
     'generation wind offshore',
     'generation wind onshore']



- Now we can sum these columns using the pandas method `sum` with the parameter `axis = 1`.
- Create a new column for fossil generation and another one for renewable generation.
- Finally drop the previous columns.


```python
energy['fossil_generation'] = energy[cols_fossil].sum(axis=1)
energy.head()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>generation biomass</th>
      <th>generation fossil brown coal/lignite</th>
      <th>generation fossil coal-derived gas</th>
      <th>generation fossil gas</th>
      <th>generation fossil hard coal</th>
      <th>generation fossil oil</th>
      <th>generation fossil oil shale</th>
      <th>generation fossil peat</th>
      <th>generation geothermal</th>
      <th>...</th>
      <th>generation wind offshore</th>
      <th>generation wind onshore</th>
      <th>forecast solar day ahead</th>
      <th>forecast wind offshore eday ahead</th>
      <th>forecast wind onshore day ahead</th>
      <th>total load forecast</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>447.0</td>
      <td>329.0</td>
      <td>0.0</td>
      <td>4844.0</td>
      <td>4821.0</td>
      <td>162.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>6378.0</td>
      <td>17.0</td>
      <td>NaN</td>
      <td>6436.0</td>
      <td>26118.0</td>
      <td>25385.0</td>
      <td>50.10</td>
      <td>65.41</td>
      <td>10156.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>449.0</td>
      <td>328.0</td>
      <td>0.0</td>
      <td>5196.0</td>
      <td>4755.0</td>
      <td>158.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>5890.0</td>
      <td>16.0</td>
      <td>NaN</td>
      <td>5856.0</td>
      <td>24934.0</td>
      <td>24382.0</td>
      <td>48.10</td>
      <td>64.92</td>
      <td>10437.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>448.0</td>
      <td>323.0</td>
      <td>0.0</td>
      <td>4857.0</td>
      <td>4581.0</td>
      <td>157.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>5461.0</td>
      <td>8.0</td>
      <td>NaN</td>
      <td>5454.0</td>
      <td>23515.0</td>
      <td>22734.0</td>
      <td>47.33</td>
      <td>64.48</td>
      <td>9918.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>438.0</td>
      <td>254.0</td>
      <td>0.0</td>
      <td>4314.0</td>
      <td>4131.0</td>
      <td>160.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>5238.0</td>
      <td>2.0</td>
      <td>NaN</td>
      <td>5151.0</td>
      <td>22642.0</td>
      <td>21286.0</td>
      <td>42.27</td>
      <td>59.32</td>
      <td>8859.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>428.0</td>
      <td>187.0</td>
      <td>0.0</td>
      <td>4130.0</td>
      <td>3840.0</td>
      <td>156.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>0.0</td>
      <td>4935.0</td>
      <td>9.0</td>
      <td>NaN</td>
      <td>4861.0</td>
      <td>21785.0</td>
      <td>20264.0</td>
      <td>38.41</td>
      <td>56.04</td>
      <td>8313.0</td>
    </tr>
  </tbody>
</table>
<p>5 rows × 30 columns</p>
</div>




```python
energy['renewable_generation'] = energy[cols_renew].sum(axis=1)
energy.head()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>generation biomass</th>
      <th>generation fossil brown coal/lignite</th>
      <th>generation fossil coal-derived gas</th>
      <th>generation fossil gas</th>
      <th>generation fossil hard coal</th>
      <th>generation fossil oil</th>
      <th>generation fossil oil shale</th>
      <th>generation fossil peat</th>
      <th>generation geothermal</th>
      <th>...</th>
      <th>generation wind onshore</th>
      <th>forecast solar day ahead</th>
      <th>forecast wind offshore eday ahead</th>
      <th>forecast wind onshore day ahead</th>
      <th>total load forecast</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>447.0</td>
      <td>329.0</td>
      <td>0.0</td>
      <td>4844.0</td>
      <td>4821.0</td>
      <td>162.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>6378.0</td>
      <td>17.0</td>
      <td>NaN</td>
      <td>6436.0</td>
      <td>26118.0</td>
      <td>25385.0</td>
      <td>50.10</td>
      <td>65.41</td>
      <td>10156.0</td>
      <td>18095.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>449.0</td>
      <td>328.0</td>
      <td>0.0</td>
      <td>5196.0</td>
      <td>4755.0</td>
      <td>158.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>5890.0</td>
      <td>16.0</td>
      <td>NaN</td>
      <td>5856.0</td>
      <td>24934.0</td>
      <td>24382.0</td>
      <td>48.10</td>
      <td>64.92</td>
      <td>10437.0</td>
      <td>17381.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>448.0</td>
      <td>323.0</td>
      <td>0.0</td>
      <td>4857.0</td>
      <td>4581.0</td>
      <td>157.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>5461.0</td>
      <td>8.0</td>
      <td>NaN</td>
      <td>5454.0</td>
      <td>23515.0</td>
      <td>22734.0</td>
      <td>47.33</td>
      <td>64.48</td>
      <td>9918.0</td>
      <td>16878.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>438.0</td>
      <td>254.0</td>
      <td>0.0</td>
      <td>4314.0</td>
      <td>4131.0</td>
      <td>160.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>5238.0</td>
      <td>2.0</td>
      <td>NaN</td>
      <td>5151.0</td>
      <td>22642.0</td>
      <td>21286.0</td>
      <td>42.27</td>
      <td>59.32</td>
      <td>8859.0</td>
      <td>16364.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>428.0</td>
      <td>187.0</td>
      <td>0.0</td>
      <td>4130.0</td>
      <td>3840.0</td>
      <td>156.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>4935.0</td>
      <td>9.0</td>
      <td>NaN</td>
      <td>4861.0</td>
      <td>21785.0</td>
      <td>20264.0</td>
      <td>38.41</td>
      <td>56.04</td>
      <td>8313.0</td>
      <td>16307.0</td>
    </tr>
  </tbody>
</table>
<p>5 rows × 31 columns</p>
</div>



Let's also create a column with the total energy generation.


```python
energy['total_generation'] = energy['fossil_generation'] + \
    energy['renewable_generation']
energy.head()

```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>generation biomass</th>
      <th>generation fossil brown coal/lignite</th>
      <th>generation fossil coal-derived gas</th>
      <th>generation fossil gas</th>
      <th>generation fossil hard coal</th>
      <th>generation fossil oil</th>
      <th>generation fossil oil shale</th>
      <th>generation fossil peat</th>
      <th>generation geothermal</th>
      <th>...</th>
      <th>forecast solar day ahead</th>
      <th>forecast wind offshore eday ahead</th>
      <th>forecast wind onshore day ahead</th>
      <th>total load forecast</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>447.0</td>
      <td>329.0</td>
      <td>0.0</td>
      <td>4844.0</td>
      <td>4821.0</td>
      <td>162.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>17.0</td>
      <td>NaN</td>
      <td>6436.0</td>
      <td>26118.0</td>
      <td>25385.0</td>
      <td>50.10</td>
      <td>65.41</td>
      <td>10156.0</td>
      <td>18095.0</td>
      <td>28251.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>449.0</td>
      <td>328.0</td>
      <td>0.0</td>
      <td>5196.0</td>
      <td>4755.0</td>
      <td>158.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>16.0</td>
      <td>NaN</td>
      <td>5856.0</td>
      <td>24934.0</td>
      <td>24382.0</td>
      <td>48.10</td>
      <td>64.92</td>
      <td>10437.0</td>
      <td>17381.0</td>
      <td>27818.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>448.0</td>
      <td>323.0</td>
      <td>0.0</td>
      <td>4857.0</td>
      <td>4581.0</td>
      <td>157.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>8.0</td>
      <td>NaN</td>
      <td>5454.0</td>
      <td>23515.0</td>
      <td>22734.0</td>
      <td>47.33</td>
      <td>64.48</td>
      <td>9918.0</td>
      <td>16878.0</td>
      <td>26796.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>438.0</td>
      <td>254.0</td>
      <td>0.0</td>
      <td>4314.0</td>
      <td>4131.0</td>
      <td>160.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>2.0</td>
      <td>NaN</td>
      <td>5151.0</td>
      <td>22642.0</td>
      <td>21286.0</td>
      <td>42.27</td>
      <td>59.32</td>
      <td>8859.0</td>
      <td>16364.0</td>
      <td>25223.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>428.0</td>
      <td>187.0</td>
      <td>0.0</td>
      <td>4130.0</td>
      <td>3840.0</td>
      <td>156.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>...</td>
      <td>9.0</td>
      <td>NaN</td>
      <td>4861.0</td>
      <td>21785.0</td>
      <td>20264.0</td>
      <td>38.41</td>
      <td>56.04</td>
      <td>8313.0</td>
      <td>16307.0</td>
      <td>24620.0</td>
    </tr>
  </tbody>
</table>
<p>5 rows × 32 columns</p>
</div>



Now that we have the summarized columns, we can drop the *generation* ones:


```python
energy.drop(columns = cols_gen, inplace=True)
energy.head()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>forecast solar day ahead</th>
      <th>forecast wind offshore eday ahead</th>
      <th>forecast wind onshore day ahead</th>
      <th>total load forecast</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>17.0</td>
      <td>NaN</td>
      <td>6436.0</td>
      <td>26118.0</td>
      <td>25385.0</td>
      <td>50.10</td>
      <td>65.41</td>
      <td>10156.0</td>
      <td>18095.0</td>
      <td>28251.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>16.0</td>
      <td>NaN</td>
      <td>5856.0</td>
      <td>24934.0</td>
      <td>24382.0</td>
      <td>48.10</td>
      <td>64.92</td>
      <td>10437.0</td>
      <td>17381.0</td>
      <td>27818.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>8.0</td>
      <td>NaN</td>
      <td>5454.0</td>
      <td>23515.0</td>
      <td>22734.0</td>
      <td>47.33</td>
      <td>64.48</td>
      <td>9918.0</td>
      <td>16878.0</td>
      <td>26796.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>2.0</td>
      <td>NaN</td>
      <td>5151.0</td>
      <td>22642.0</td>
      <td>21286.0</td>
      <td>42.27</td>
      <td>59.32</td>
      <td>8859.0</td>
      <td>16364.0</td>
      <td>25223.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>9.0</td>
      <td>NaN</td>
      <td>4861.0</td>
      <td>21785.0</td>
      <td>20264.0</td>
      <td>38.41</td>
      <td>56.04</td>
      <td>8313.0</td>
      <td>16307.0</td>
      <td>24620.0</td>
    </tr>
  </tbody>
</table>
</div>



Let's also drop the *forecast* columns as we are not doing any modeling to compare.


```python
cols_forecast = [col for col in list(energy) if 'forecast' in col]
cols_forecast
```




    ['forecast solar day ahead',
     'forecast wind offshore eday ahead',
     'forecast wind onshore day ahead',
     'total load forecast']




```python
energy.drop(columns=cols_forecast, inplace=True)
energy.head()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>25385.0</td>
      <td>50.10</td>
      <td>65.41</td>
      <td>10156.0</td>
      <td>18095.0</td>
      <td>28251.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>24382.0</td>
      <td>48.10</td>
      <td>64.92</td>
      <td>10437.0</td>
      <td>17381.0</td>
      <td>27818.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>22734.0</td>
      <td>47.33</td>
      <td>64.48</td>
      <td>9918.0</td>
      <td>16878.0</td>
      <td>26796.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>21286.0</td>
      <td>42.27</td>
      <td>59.32</td>
      <td>8859.0</td>
      <td>16364.0</td>
      <td>25223.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>20264.0</td>
      <td>38.41</td>
      <td>56.04</td>
      <td>8313.0</td>
      <td>16307.0</td>
      <td>24620.0</td>
    </tr>
  </tbody>
</table>
</div>



## Drop `weather_id` column


```python
new_weather.drop(columns=['weather_id'], inplace=True)
new_weather.head()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>272.491463</td>
      <td>272.491463</td>
      <td>272.491463</td>
      <td>1016.4</td>
      <td>82.4</td>
      <td>2.0</td>
      <td>135.2</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>272.512700</td>
      <td>272.512700</td>
      <td>272.512700</td>
      <td>1016.2</td>
      <td>82.4</td>
      <td>2.0</td>
      <td>135.8</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>272.099137</td>
      <td>272.099137</td>
      <td>272.099137</td>
      <td>1016.8</td>
      <td>82.0</td>
      <td>2.4</td>
      <td>119.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>272.089469</td>
      <td>272.089469</td>
      <td>272.089469</td>
      <td>1016.6</td>
      <td>82.0</td>
      <td>2.4</td>
      <td>119.2</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>272.145900</td>
      <td>272.145900</td>
      <td>272.145900</td>
      <td>1016.6</td>
      <td>82.0</td>
      <td>2.4</td>
      <td>118.4</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
  </tbody>
</table>
</div>



## Merging Dataframes

Merging dataframes on *time*.


```python
data = energy.merge(new_weather, on='time', how='inner')
data
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014-12-31 23:00:00+00:00</td>
      <td>25385.0</td>
      <td>50.10</td>
      <td>65.41</td>
      <td>10156.0</td>
      <td>18095.0</td>
      <td>28251.0</td>
      <td>272.491463</td>
      <td>272.491463</td>
      <td>272.491463</td>
      <td>1016.4</td>
      <td>82.4</td>
      <td>2.0</td>
      <td>135.2</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015-01-01 00:00:00+00:00</td>
      <td>24382.0</td>
      <td>48.10</td>
      <td>64.92</td>
      <td>10437.0</td>
      <td>17381.0</td>
      <td>27818.0</td>
      <td>272.512700</td>
      <td>272.512700</td>
      <td>272.512700</td>
      <td>1016.2</td>
      <td>82.4</td>
      <td>2.0</td>
      <td>135.8</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015-01-01 01:00:00+00:00</td>
      <td>22734.0</td>
      <td>47.33</td>
      <td>64.48</td>
      <td>9918.0</td>
      <td>16878.0</td>
      <td>26796.0</td>
      <td>272.099137</td>
      <td>272.099137</td>
      <td>272.099137</td>
      <td>1016.8</td>
      <td>82.0</td>
      <td>2.4</td>
      <td>119.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015-01-01 02:00:00+00:00</td>
      <td>21286.0</td>
      <td>42.27</td>
      <td>59.32</td>
      <td>8859.0</td>
      <td>16364.0</td>
      <td>25223.0</td>
      <td>272.089469</td>
      <td>272.089469</td>
      <td>272.089469</td>
      <td>1016.6</td>
      <td>82.0</td>
      <td>2.4</td>
      <td>119.2</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015-01-01 03:00:00+00:00</td>
      <td>20264.0</td>
      <td>38.41</td>
      <td>56.04</td>
      <td>8313.0</td>
      <td>16307.0</td>
      <td>24620.0</td>
      <td>272.145900</td>
      <td>272.145900</td>
      <td>272.145900</td>
      <td>1016.6</td>
      <td>82.0</td>
      <td>2.4</td>
      <td>118.4</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>...</th>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <th>35059</th>
      <td>2018-12-31 18:00:00+00:00</td>
      <td>30653.0</td>
      <td>68.85</td>
      <td>77.02</td>
      <td>10440.0</td>
      <td>15975.0</td>
      <td>26415.0</td>
      <td>284.470000</td>
      <td>283.350000</td>
      <td>285.550000</td>
      <td>1029.2</td>
      <td>73.6</td>
      <td>1.4</td>
      <td>151.4</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>35060</th>
      <td>2018-12-31 19:00:00+00:00</td>
      <td>29735.0</td>
      <td>68.40</td>
      <td>76.16</td>
      <td>9981.0</td>
      <td>15232.0</td>
      <td>25213.0</td>
      <td>282.294000</td>
      <td>280.950000</td>
      <td>283.350000</td>
      <td>1030.0</td>
      <td>68.0</td>
      <td>1.8</td>
      <td>160.4</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>35061</th>
      <td>2018-12-31 20:00:00+00:00</td>
      <td>28071.0</td>
      <td>66.88</td>
      <td>74.30</td>
      <td>9615.0</td>
      <td>14372.0</td>
      <td>23987.0</td>
      <td>280.850000</td>
      <td>280.350000</td>
      <td>281.350000</td>
      <td>1029.8</td>
      <td>71.4</td>
      <td>2.6</td>
      <td>226.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>35062</th>
      <td>2018-12-31 21:00:00+00:00</td>
      <td>25801.0</td>
      <td>63.93</td>
      <td>69.89</td>
      <td>9018.0</td>
      <td>13730.0</td>
      <td>22748.0</td>
      <td>279.718000</td>
      <td>278.750000</td>
      <td>280.750000</td>
      <td>1030.2</td>
      <td>70.0</td>
      <td>2.8</td>
      <td>230.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
    <tr>
      <th>35063</th>
      <td>2018-12-31 22:00:00+00:00</td>
      <td>24455.0</td>
      <td>64.27</td>
      <td>69.88</td>
      <td>9255.0</td>
      <td>13350.0</td>
      <td>22605.0</td>
      <td>278.798000</td>
      <td>277.550000</td>
      <td>279.950000</td>
      <td>1030.2</td>
      <td>82.4</td>
      <td>2.6</td>
      <td>224.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
    </tr>
  </tbody>
</table>
<p>35064 rows × 18 columns</p>
</div>



Now we have a new dataframe with 35064 rows and 21 columns.

## Extracting ``year`` and ``month`` from date columns
After we converted the dates from *object* to *datetime*, now we can use methods inside Pandas to get the year, the month and add them to new columns.
### Data


```python
data['year'] = data['time'].dt.year
data['month'] = data['time'].dt.month_name()
data.loc[:3,['year', 'month']]
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>year</th>
      <th>month</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014</td>
      <td>December</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015</td>
      <td>January</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015</td>
      <td>January</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015</td>
      <td>January</td>
    </tr>
  </tbody>
</table>
</div>



### Checking for duplicated rows


```python
data.duplicated().sum()
```




    0



## Grouping the data

This analysis can be simplified by averaging the columns by year/month.


```python
data_month = data.groupby(['year', 'month'], as_index=False).mean()
data_month.head()

```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>year</th>
      <th>month</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2014</td>
      <td>December</td>
      <td>25385.000000</td>
      <td>50.100000</td>
      <td>65.410000</td>
      <td>10156.000000</td>
      <td>18095.000000</td>
      <td>28251.000000</td>
      <td>272.491463</td>
      <td>272.491463</td>
      <td>272.491463</td>
      <td>1016.400000</td>
      <td>82.400000</td>
      <td>2.000000</td>
      <td>135.200000</td>
      <td>0.000000</td>
      <td>0.000000e+00</td>
      <td>0.000000</td>
      <td>0.000000</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015</td>
      <td>April</td>
      <td>27438.268156</td>
      <td>48.900778</td>
      <td>58.402806</td>
      <td>10544.502778</td>
      <td>17737.369444</td>
      <td>28281.872222</td>
      <td>287.221759</td>
      <td>287.221759</td>
      <td>287.221759</td>
      <td>1014.331111</td>
      <td>69.419167</td>
      <td>2.287778</td>
      <td>162.444444</td>
      <td>0.119417</td>
      <td>2.966667e-03</td>
      <td>0.000000</td>
      <td>33.368056</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015</td>
      <td>August</td>
      <td>27723.881720</td>
      <td>52.767984</td>
      <td>64.022231</td>
      <td>11684.162634</td>
      <td>17178.002688</td>
      <td>28862.165323</td>
      <td>298.509490</td>
      <td>295.351299</td>
      <td>301.929703</td>
      <td>1015.289126</td>
      <td>59.527311</td>
      <td>2.648637</td>
      <td>170.447798</td>
      <td>0.064443</td>
      <td>5.376344e-07</td>
      <td>0.000000</td>
      <td>20.297888</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015</td>
      <td>December</td>
      <td>27656.080754</td>
      <td>50.335766</td>
      <td>61.881895</td>
      <td>11188.764785</td>
      <td>16619.870968</td>
      <td>27808.635753</td>
      <td>284.339451</td>
      <td>283.042610</td>
      <td>285.839638</td>
      <td>1028.561559</td>
      <td>75.803175</td>
      <td>1.915931</td>
      <td>166.347683</td>
      <td>0.017137</td>
      <td>5.653226e-04</td>
      <td>0.000000</td>
      <td>20.615854</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015</td>
      <td>February</td>
      <td>29478.727685</td>
      <td>44.206295</td>
      <td>56.412991</td>
      <td>9355.761905</td>
      <td>22093.273810</td>
      <td>31449.035714</td>
      <td>281.200904</td>
      <td>281.145523</td>
      <td>281.275672</td>
      <td>3822.709524</td>
      <td>71.226786</td>
      <td>3.528274</td>
      <td>208.155060</td>
      <td>0.233661</td>
      <td>0.000000e+00</td>
      <td>0.215982</td>
      <td>38.500000</td>
    </tr>
  </tbody>
</table>
</div>



Now we reduced the data to 48 rows.

Note that the first row, for December 2014, comes from the average of a single day. Let's remove it.


```python
data_month.drop(0, axis=0, inplace=True)  # Dropping first row
data_month.reset_index(inplace=True, drop=True)  # Reseting indexes
data_month.head()
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>year</th>
      <th>month</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>2015</td>
      <td>April</td>
      <td>27438.268156</td>
      <td>48.900778</td>
      <td>58.402806</td>
      <td>10544.502778</td>
      <td>17737.369444</td>
      <td>28281.872222</td>
      <td>287.221759</td>
      <td>287.221759</td>
      <td>287.221759</td>
      <td>1014.331111</td>
      <td>69.419167</td>
      <td>2.287778</td>
      <td>162.444444</td>
      <td>0.119417</td>
      <td>2.966667e-03</td>
      <td>0.000000</td>
      <td>33.368056</td>
    </tr>
    <tr>
      <th>1</th>
      <td>2015</td>
      <td>August</td>
      <td>27723.881720</td>
      <td>52.767984</td>
      <td>64.022231</td>
      <td>11684.162634</td>
      <td>17178.002688</td>
      <td>28862.165323</td>
      <td>298.509490</td>
      <td>295.351299</td>
      <td>301.929703</td>
      <td>1015.289126</td>
      <td>59.527311</td>
      <td>2.648637</td>
      <td>170.447798</td>
      <td>0.064443</td>
      <td>5.376344e-07</td>
      <td>0.000000</td>
      <td>20.297888</td>
    </tr>
    <tr>
      <th>2</th>
      <td>2015</td>
      <td>December</td>
      <td>27656.080754</td>
      <td>50.335766</td>
      <td>61.881895</td>
      <td>11188.764785</td>
      <td>16619.870968</td>
      <td>27808.635753</td>
      <td>284.339451</td>
      <td>283.042610</td>
      <td>285.839638</td>
      <td>1028.561559</td>
      <td>75.803175</td>
      <td>1.915931</td>
      <td>166.347683</td>
      <td>0.017137</td>
      <td>5.653226e-04</td>
      <td>0.000000</td>
      <td>20.615854</td>
    </tr>
    <tr>
      <th>3</th>
      <td>2015</td>
      <td>February</td>
      <td>29478.727685</td>
      <td>44.206295</td>
      <td>56.412991</td>
      <td>9355.761905</td>
      <td>22093.273810</td>
      <td>31449.035714</td>
      <td>281.200904</td>
      <td>281.145523</td>
      <td>281.275672</td>
      <td>3822.709524</td>
      <td>71.226786</td>
      <td>3.528274</td>
      <td>208.155060</td>
      <td>0.233661</td>
      <td>0.000000e+00</td>
      <td>0.215982</td>
      <td>38.500000</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015</td>
      <td>January</td>
      <td>29997.428765</td>
      <td>47.419395</td>
      <td>64.898763</td>
      <td>10975.498656</td>
      <td>20265.599462</td>
      <td>31241.098118</td>
      <td>280.161853</td>
      <td>280.161853</td>
      <td>280.161853</td>
      <td>1011.519848</td>
      <td>74.269220</td>
      <td>2.773566</td>
      <td>208.266711</td>
      <td>0.140726</td>
      <td>2.419355e-04</td>
      <td>0.019456</td>
      <td>26.796057</td>
    </tr>
  </tbody>
</table>
</div>



Now we have the data ready for plotting.

# Data Visualization

We organized our data and now we can start the visualization step.

Let's start by checking the columns statistics.


```python
data_month.describe().T
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>count</th>
      <th>mean</th>
      <th>std</th>
      <th>min</th>
      <th>25%</th>
      <th>50%</th>
      <th>75%</th>
      <th>max</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>year</th>
      <td>48.0</td>
      <td>2016.500000</td>
      <td>1.129865</td>
      <td>2015.000000</td>
      <td>2015.750000</td>
      <td>2016.500000</td>
      <td>2017.250000</td>
      <td>2018.000000</td>
    </tr>
    <tr>
      <th>total load actual</th>
      <td>48.0</td>
      <td>28701.324430</td>
      <td>930.483892</td>
      <td>27068.497222</td>
      <td>27979.676600</td>
      <td>28757.848790</td>
      <td>29439.689695</td>
      <td>30508.004032</td>
    </tr>
    <tr>
      <th>price day ahead</th>
      <td>48.0</td>
      <td>49.856492</td>
      <td>8.564444</td>
      <td>31.183042</td>
      <td>46.299614</td>
      <td>50.740506</td>
      <td>54.765082</td>
      <td>66.797167</td>
    </tr>
    <tr>
      <th>price actual</th>
      <td>48.0</td>
      <td>57.861657</td>
      <td>10.320096</td>
      <td>32.608194</td>
      <td>51.526020</td>
      <td>59.603322</td>
      <td>64.943411</td>
      <td>79.505524</td>
    </tr>
    <tr>
      <th>fossil_generation</th>
      <td>48.0</td>
      <td>10616.019117</td>
      <td>1786.559628</td>
      <td>6895.573611</td>
      <td>9469.786559</td>
      <td>10689.189516</td>
      <td>11874.556967</td>
      <td>15000.159722</td>
    </tr>
    <tr>
      <th>renewable_generation</th>
      <td>48.0</td>
      <td>18013.033975</td>
      <td>1898.831184</td>
      <td>15066.966667</td>
      <td>16701.720833</td>
      <td>17650.509702</td>
      <td>19110.867944</td>
      <td>23622.677419</td>
    </tr>
    <tr>
      <th>total_generation</th>
      <td>48.0</td>
      <td>28629.053091</td>
      <td>1290.822528</td>
      <td>26572.448611</td>
      <td>27759.122984</td>
      <td>28321.575605</td>
      <td>29384.842545</td>
      <td>31542.150538</td>
    </tr>
    <tr>
      <th>temp</th>
      <td>48.0</td>
      <td>289.640068</td>
      <td>6.183956</td>
      <td>280.161853</td>
      <td>284.305202</td>
      <td>289.135518</td>
      <td>295.726926</td>
      <td>300.382456</td>
    </tr>
    <tr>
      <th>temp_min</th>
      <td>48.0</td>
      <td>288.359164</td>
      <td>5.964690</td>
      <td>278.979017</td>
      <td>283.245527</td>
      <td>287.637851</td>
      <td>293.587372</td>
      <td>298.372781</td>
    </tr>
    <tr>
      <th>temp_max</th>
      <td>48.0</td>
      <td>291.104105</td>
      <td>6.482340</td>
      <td>280.161853</td>
      <td>285.585002</td>
      <td>290.259110</td>
      <td>297.119886</td>
      <td>303.429085</td>
    </tr>
    <tr>
      <th>pressure</th>
      <td>48.0</td>
      <td>1074.874655</td>
      <td>405.089653</td>
      <td>998.742742</td>
      <td>1014.127211</td>
      <td>1015.888361</td>
      <td>1019.347961</td>
      <td>3822.709524</td>
    </tr>
    <tr>
      <th>humidity</th>
      <td>48.0</td>
      <td>68.238709</td>
      <td>7.100903</td>
      <td>55.703313</td>
      <td>61.914662</td>
      <td>68.592803</td>
      <td>73.407268</td>
      <td>82.455741</td>
    </tr>
    <tr>
      <th>wind_speed</th>
      <td>48.0</td>
      <td>2.470812</td>
      <td>0.492745</td>
      <td>1.623118</td>
      <td>2.202493</td>
      <td>2.384306</td>
      <td>2.623697</td>
      <td>4.126827</td>
    </tr>
    <tr>
      <th>wind_deg</th>
      <td>48.0</td>
      <td>166.722118</td>
      <td>18.077149</td>
      <td>122.671013</td>
      <td>156.652464</td>
      <td>166.047431</td>
      <td>172.275942</td>
      <td>209.786258</td>
    </tr>
    <tr>
      <th>rain_1h</th>
      <td>48.0</td>
      <td>0.073568</td>
      <td>0.067199</td>
      <td>0.011290</td>
      <td>0.030858</td>
      <td>0.058919</td>
      <td>0.086169</td>
      <td>0.350887</td>
    </tr>
    <tr>
      <th>rain_3h</th>
      <td>48.0</td>
      <td>0.000384</td>
      <td>0.000798</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000013</td>
      <td>0.000401</td>
      <td>0.003648</td>
    </tr>
    <tr>
      <th>snow_3h</th>
      <td>48.0</td>
      <td>0.005195</td>
      <td>0.031248</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.000000</td>
      <td>0.215982</td>
    </tr>
    <tr>
      <th>clouds_all</th>
      <td>48.0</td>
      <td>24.794366</td>
      <td>6.288097</td>
      <td>16.672670</td>
      <td>19.359981</td>
      <td>23.646221</td>
      <td>29.367044</td>
      <td>38.500000</td>
    </tr>
  </tbody>
</table>
</div>



* Data goes from 2015 to 2018
* Mean and median of all columns seem to have close values, suggesting a symmetric distribution

## Checking data distribution

Distribution of the features can be checked with the boxplot and histograms.

### Fossil Energy


```python
plt.figure(figsize=(10,3))
sns.boxplot(data=data_month, x='fossil_generation');
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_67_0.png)
    



```python
plt.figure(figsize=(10,5))
sns.histplot(data=data_month, x='fossil_generation', bins=10);
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_68_0.png)
    


For the fossil energy production, the distribution is close fo *normal* with no outliers.

A first comment is that we will keep using the boxplot and the histogram for all the features. To make it easier, let's create a function to help us.


```python
def hist_box(data, feature, figsize=(12, 7)):

    # Subplot canvas
    fig, (ax_box, ax_hist) = plt.subplots(nrows=2, sharex=True,
                                          gridspec_kw={"height_ratios": (0.25, 0.75)}, figsize=figsize)

    # Boxplot on top
    # boxplot will be created and a triangle will indicate the mean value of the column
    sns.boxplot(data=data, x=feature, ax=ax_box, showmeans=True, color="pink")

    # Histogram on bottom
    # histogram will be created
    sns.histplot(data=data, x=feature, ax=ax_hist)

    # Add mean and median to histogram
    ax_hist.axvline(data[feature].mean(), color="green")  # mean
    ax_hist.axvline(data[feature].median(), color="orange")  # median

    # Title
    fig.suptitle("Distribution of " + feature, fontsize=16)

```


```python
hist_box(data_month, "fossil_generation")

```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_71_0.png)
    


We can confirm that the mean (green) and and median (orange) are close to each other.

### Renewable Energy


```python
hist_box(data_month, "renewable_generation")
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_74_0.png)
    


The distribution is right skewed with outliers.


```python
# Filtering data for outlier
data_month[data_month["renewable_generation"] > 23000]

```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>year</th>
      <th>month</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>43</th>
      <td>2018</td>
      <td>March</td>
      <td>29434.467742</td>
      <td>44.802433</td>
      <td>48.260013</td>
      <td>7502.173387</td>
      <td>23622.677419</td>
      <td>31124.850806</td>
      <td>284.202454</td>
      <td>283.313167</td>
      <td>285.14394</td>
      <td>1007.586145</td>
      <td>68.337927</td>
      <td>4.126827</td>
      <td>209.786258</td>
      <td>0.120227</td>
      <td>0.000018</td>
      <td>0.0</td>
      <td>33.891644</td>
    </tr>
  </tbody>
</table>
</div>



March 2018 is shown as an outlier, with a higher average renewable energy generation.

### Total Energy


```python
hist_box(data_month, "total_generation")
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_79_0.png)
    


The distribution is right skewed with no outliers.

### Total Load


```python
hist_box(data_month, "total load actual")

```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_82_0.png)
    


The total usage of all types of energy has a symmetric distribution.

### Temperature

#### Temp


```python
hist_box(data_month, "temp")
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_86_0.png)
    


Temperature seems to be bi-modal (two peaks). Probably Summer and Winter effects.

#### Min and max temperatures


```python
hist_box(data_month, "temp_min")
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_89_0.png)
    



```python
hist_box(data_month, "temp_max")
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_90_0.png)
    


Same observation as *temp*.

### Pressure


```python
hist_box(data_month, "pressure")
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_93_0.png)
    


Pressure has a huge outlier. Let's look at it closer.


```python
data_month[data_month['pressure'] > 1500]
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>year</th>
      <th>month</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>3</th>
      <td>2015</td>
      <td>February</td>
      <td>29478.727685</td>
      <td>44.206295</td>
      <td>56.412991</td>
      <td>9355.761905</td>
      <td>22093.27381</td>
      <td>31449.035714</td>
      <td>281.200904</td>
      <td>281.145523</td>
      <td>281.275672</td>
      <td>3822.709524</td>
      <td>71.226786</td>
      <td>3.528274</td>
      <td>208.15506</td>
      <td>0.233661</td>
      <td>0.0</td>
      <td>0.215982</td>
      <td>38.5</td>
    </tr>
  </tbody>
</table>
</div>



February 2015 is the outlier for pressure, with an average pressure more than 3 times larger than any other month, pointing to something wrong. We can't check which day, but we can replace the value with the average for the month of February:


```python
data_month.loc[3, 'pressure'] = data_month[(data_month['month'] == 'February') & (data_month['year'] != 2015)]['pressure'].mean()
```


```python
hist_box(data_month, "pressure")

```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_98_0.png)
    


The distribution for the pressure is right skewed with outliers that are now, apparently, possible to happen.

### Humidity


```python
hist_box(data_month, "humidity")
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_101_0.png)
    


Humidity has a symmetric distribution with no outliers.

### Wind

#### Wind Speed


```python
hist_box(data_month, "wind_speed")
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_105_0.png)
    


A right skewed distribution with outliers over 3.2.


```python
data_month[data_month["wind_speed"] > 3.2]
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>year</th>
      <th>month</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>3</th>
      <td>2015</td>
      <td>February</td>
      <td>29478.727685</td>
      <td>44.206295</td>
      <td>56.412991</td>
      <td>9355.761905</td>
      <td>22093.273810</td>
      <td>31449.035714</td>
      <td>281.200904</td>
      <td>281.145523</td>
      <td>281.275672</td>
      <td>1015.109317</td>
      <td>71.226786</td>
      <td>3.528274</td>
      <td>208.155060</td>
      <td>0.233661</td>
      <td>0.000000</td>
      <td>0.215982</td>
      <td>38.500000</td>
    </tr>
    <tr>
      <th>15</th>
      <td>2016</td>
      <td>February</td>
      <td>29274.227011</td>
      <td>31.431897</td>
      <td>36.732601</td>
      <td>7968.311782</td>
      <td>21615.405172</td>
      <td>29583.716954</td>
      <td>283.927434</td>
      <td>282.761944</td>
      <td>285.371025</td>
      <td>1018.282916</td>
      <td>70.140852</td>
      <td>3.804098</td>
      <td>205.579687</td>
      <td>0.067562</td>
      <td>0.000309</td>
      <td>0.000779</td>
      <td>29.264915</td>
    </tr>
    <tr>
      <th>43</th>
      <td>2018</td>
      <td>March</td>
      <td>29434.467742</td>
      <td>44.802433</td>
      <td>48.260013</td>
      <td>7502.173387</td>
      <td>23622.677419</td>
      <td>31124.850806</td>
      <td>284.202454</td>
      <td>283.313167</td>
      <td>285.143940</td>
      <td>1007.586145</td>
      <td>68.337927</td>
      <td>4.126827</td>
      <td>209.786258</td>
      <td>0.120227</td>
      <td>0.000018</td>
      <td>0.000000</td>
      <td>33.891644</td>
    </tr>
  </tbody>
</table>
</div>



These outliers are from months with higher production on renewable energy, probably driven by the wind power.

#### Wind Direction


```python
hist_box(data_month, "wind_deg")
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_110_0.png)
    


Wind direction has a close to normal distribution with outliers.


```python
data_month[data_month["wind_deg"] > 190]
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>year</th>
      <th>month</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>3</th>
      <td>2015</td>
      <td>February</td>
      <td>29478.727685</td>
      <td>44.206295</td>
      <td>56.412991</td>
      <td>9355.761905</td>
      <td>22093.273810</td>
      <td>31449.035714</td>
      <td>281.200904</td>
      <td>281.145523</td>
      <td>281.275672</td>
      <td>1015.109317</td>
      <td>71.226786</td>
      <td>3.528274</td>
      <td>208.155060</td>
      <td>0.233661</td>
      <td>0.000000</td>
      <td>0.215982</td>
      <td>38.500000</td>
    </tr>
    <tr>
      <th>4</th>
      <td>2015</td>
      <td>January</td>
      <td>29997.428765</td>
      <td>47.419395</td>
      <td>64.898763</td>
      <td>10975.498656</td>
      <td>20265.599462</td>
      <td>31241.098118</td>
      <td>280.161853</td>
      <td>280.161853</td>
      <td>280.161853</td>
      <td>1011.519848</td>
      <td>74.269220</td>
      <td>2.773566</td>
      <td>208.266711</td>
      <td>0.140726</td>
      <td>0.000242</td>
      <td>0.019456</td>
      <td>26.796057</td>
    </tr>
    <tr>
      <th>15</th>
      <td>2016</td>
      <td>February</td>
      <td>29274.227011</td>
      <td>31.431897</td>
      <td>36.732601</td>
      <td>7968.311782</td>
      <td>21615.405172</td>
      <td>29583.716954</td>
      <td>283.927434</td>
      <td>282.761944</td>
      <td>285.371025</td>
      <td>1018.282916</td>
      <td>70.140852</td>
      <td>3.804098</td>
      <td>205.579687</td>
      <td>0.067562</td>
      <td>0.000309</td>
      <td>0.000779</td>
      <td>29.264915</td>
    </tr>
    <tr>
      <th>16</th>
      <td>2016</td>
      <td>January</td>
      <td>29309.133065</td>
      <td>41.462016</td>
      <td>45.562594</td>
      <td>10227.041667</td>
      <td>19091.509409</td>
      <td>29318.551075</td>
      <td>284.129075</td>
      <td>282.928775</td>
      <td>285.545507</td>
      <td>1020.828479</td>
      <td>75.343255</td>
      <td>3.129423</td>
      <td>190.388003</td>
      <td>0.053508</td>
      <td>0.000800</td>
      <td>0.000000</td>
      <td>33.686744</td>
    </tr>
    <tr>
      <th>19</th>
      <td>2016</td>
      <td>March</td>
      <td>28014.223118</td>
      <td>33.255121</td>
      <td>36.806882</td>
      <td>7784.805108</td>
      <td>20797.026882</td>
      <td>28581.831989</td>
      <td>284.688246</td>
      <td>283.555722</td>
      <td>286.258105</td>
      <td>1015.590751</td>
      <td>67.571646</td>
      <td>2.923739</td>
      <td>193.838191</td>
      <td>0.060453</td>
      <td>0.000460</td>
      <td>0.000429</td>
      <td>27.978136</td>
    </tr>
    <tr>
      <th>43</th>
      <td>2018</td>
      <td>March</td>
      <td>29434.467742</td>
      <td>44.802433</td>
      <td>48.260013</td>
      <td>7502.173387</td>
      <td>23622.677419</td>
      <td>31124.850806</td>
      <td>284.202454</td>
      <td>283.313167</td>
      <td>285.143940</td>
      <td>1007.586145</td>
      <td>68.337927</td>
      <td>4.126827</td>
      <td>209.786258</td>
      <td>0.120227</td>
      <td>0.000018</td>
      <td>0.000000</td>
      <td>33.891644</td>
    </tr>
  </tbody>
</table>
</div>




```python
data_month[data_month["wind_deg"] < 130]
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>year</th>
      <th>month</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>14</th>
      <td>2016</td>
      <td>December</td>
      <td>28935.895161</td>
      <td>52.637527</td>
      <td>67.601304</td>
      <td>12118.568548</td>
      <td>16562.985215</td>
      <td>28681.553763</td>
      <td>283.366049</td>
      <td>281.471074</td>
      <td>285.822994</td>
      <td>1026.353176</td>
      <td>82.455741</td>
      <td>1.809381</td>
      <td>122.671013</td>
      <td>0.047861</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>27.027717</td>
    </tr>
  </tbody>
</table>
</div>



Wind direction seems to have correlation with the renewable energy production, as higher angles suggest higher production.

### Rain


```python
hist_box(data_month, 'rain_1h')
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_116_0.png)
    



```python
hist_box(data_month, 'rain_3h')
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_117_0.png)
    


Both distributions are right skewed and contain outliers.

### Snow


```python
hist_box(data_month, 'snow_3h')
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_120_0.png)
    


For most of the days, the quantity of snowfall is zero.

### Clouds


```python
hist_box(data_month, 'clouds_all')
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_123_0.png)
    


It is a right skewed distribution without outliers.

### Energy Price


```python
hist_box(data_month, 'price actual')
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_126_0.png)
    


The price of the energy is left skewed with no outliers.

## Pairs Plot

Let's quickly check the scatter plot of the features with each other using the `pairplot`.


```python
sns.pairplot(data_month);
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_129_0.png)
    


* Temperature features are highly related to each other.
* Humidity seems to have significant correlation with temperature.
* Wind speed and direction seem to influence the renewable energy production.


```python
# Converting columns year and month to categorical
data_month["month"] = data_month["month"].astype('category')
data_month["year"] = data_month["year"].astype('category')
```


```python
sns.pairplot(data_month, hue="year");
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_132_0.png)
    


Price, load, and energy generation changes over the years.

## Energy Generation in Time

### Energy data

We can visualize energy generation, load, and price over the years.


```python
plt.figure(figsize=(17, 7))
sns.lineplot(data=data, x="time", y="price actual");
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_136_0.png)
    



```python
data[data['price actual'] == data['price actual'].max()]
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>time</th>
      <th>total load actual</th>
      <th>price day ahead</th>
      <th>price actual</th>
      <th>fossil_generation</th>
      <th>renewable_generation</th>
      <th>total_generation</th>
      <th>temp</th>
      <th>temp_min</th>
      <th>temp_max</th>
      <th>pressure</th>
      <th>humidity</th>
      <th>wind_speed</th>
      <th>wind_deg</th>
      <th>rain_1h</th>
      <th>rain_3h</th>
      <th>snow_3h</th>
      <th>clouds_all</th>
      <th>year</th>
      <th>month</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>24642</th>
      <td>2017-10-23 17:00:00+00:00</td>
      <td>31103.0</td>
      <td>71.42</td>
      <td>116.8</td>
      <td>18599.0</td>
      <td>13686.0</td>
      <td>32285.0</td>
      <td>295.064</td>
      <td>294.55</td>
      <td>295.55</td>
      <td>1023.4</td>
      <td>47.0</td>
      <td>2.6</td>
      <td>123.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>0.0</td>
      <td>2017</td>
      <td>October</td>
    </tr>
  </tbody>
</table>
</div>



We can see how the price of energy has changed in the dataset, with a higher peak in October 23th 2017, and a low period from January to June 2016.


```python
plt.figure(figsize=(23, 7))
sns.lineplot(data=energy, x="time", y="total load actual");
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_139_0.png)
    


The total load has a fairly high range (20000 to 40000), but is relatively steady over the years.


```python
plt.figure(figsize=(17, 7))
sns.lineplot(data=energy, x="time", y="fossil_generation");
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_141_0.png)
    


Energy from fossil sources has kept relatively steady over time.


```python
plt.figure(figsize = (17, 7))
sns.lineplot(data = energy, x = "time", y = "renewable_generation");
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_143_0.png)
    


Same for the renewable energy.

Let's now check the production, load, and price average per month and per year.

#### Price


```python
plt.figure(figsize = (15,8))
sns.barplot(data = data_month, x = "year", y = "price actual");
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_146_0.png)
    



```python
months = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']

plt.figure(figsize = (15,8))
sns.barplot(data = data_month, x = "month", y = "price actual", order = months);
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_147_0.png)
    


Price suffered a considerable drop in 2016, but has maintaining the same price over the years. And prices are lower by the end of Winter and during the Spring.

#### Load


```python
plt.figure(figsize = (15,8))
sns.barplot(data = data_month, x = "year", y = "total load actual");
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_150_0.png)
    



```python
sns.lineplot(data = data_month, x='year', y='total load actual', marker='o');
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_151_0.png)
    



```python
plt.figure(figsize=(15, 8))
sns.barplot(data=data_month, x="month", y="total load actual", order=months)

```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_152_0.png)
    


Demand for energy is slightly increasing over the years. As per months, end of Winter and Spring are the periods with lower demand of energy, which may explain the lower price during that time of the year.

#### Fossil Generation


```python
plt.figure(figsize=(15, 8))
sns.barplot(data=data_month, x="year", y="fossil_generation");
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_155_0.png)
    



```python
plt.figure(figsize=(15, 8))
sns.barplot(data=data_month, x="month", y="fossil_generation", order=months);
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_156_0.png)
    


Fossil generation has fluctuated over the years, and follow the same trend as price and load for the months.

#### Renewable Generation


```python
plt.figure(figsize=(15, 8))
sns.barplot(data=data_month, x="year", y="renewable_generation");
```


    
![png](energy-analysis/Energy_Analysis_Leo_159_0.png)
    



```python
plt.figure(figsize = (15,8))
sns.barplot(data = data_month, x = "month", y = "fossil_generation", order = months);
```


    
![png](/assets/img/posts/energy-analysis/Energy_Analysis_Leo_160_0.png)
    


Same trend as per the fossil generation.

# Summary

Insights from the analysis:

1. There is a correlation between wind speed and direction with renewable energy generation
2. We could find an outlier (pressure) that might be an error, and we replaced it by the average of the months from others years
3. Energy demand, price, and production follow the same trend over the months, with lower valuer by the end of Winter and during Spring
4. Energy demand haven't changed much over the years
5. Generation, for both fossil and renewable, fluctuate over the year
6. Price had a signifcant drop in 2016, and it requires further research to learn the reason.
