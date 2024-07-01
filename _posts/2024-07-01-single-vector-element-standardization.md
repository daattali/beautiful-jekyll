---  
layout: post  
title: Single Vector Element Standardization  
subtitle: Finding harmony within oneself  
image: /assets/img/inner-harmony.png  
cover-img: /assets/img/inner-harmony.png  
share-img: /assets/img/inner-harmony.png  
tags: [data, R, tricks]  
---  

Standardizing data vectors is an important step in data science. For
example, different data sources often represent the same entity, such as
country names, in different ways or with different spellings. In
addition, small errors or formatting inconsistencies can complicate
joins and lead to difficulties in downstream analysis. While excellent
resources do exist to solve this problem for individual use cases, such
as the [countries](https://github.com/fbellelli/countries) package in R,
it can be useful to understand general methods to self-standardize
categorical vectors. There are three approaches that I’ve used to
standardize character vectors. I’ve written scripts below to illustrate
each method.

## The vector to standardize

Note: this data is fictional!

| disease_name       | outbreaks |
|:-------------------|----------:|
| Influenza          |        15 |
| Inflenza           |        10 |
| COVID-19           |        95 |
| sars-covid-19      |        90 |
| Malaria            |        20 |
| Maleria            |        22 |
| malaria            |        20 |
| Diabetes           |        30 |
| Diabetis           |        28 |
| HIV/AIDS           |        75 |
| HIV                |        70 |
| AIDS               |        65 |
| Tuberculosis       |        40 |
| Tuberclosis        |        38 |
| Alzheimers         |        23 |
| Alzheimers Disease |        27 |
| Heart Disease      |        60 |
| Heart Diease       |        58 |

# Standardization by string distance

The most straight forward way to standardize a character vector is use
string distance. String distance is a measure of how different two
strings are. The method I tend to use is
[Jaro–Winkler](https://en.wikipedia.org/wiki/Jaro%E2%80%93Winkler_distance)
distance. The distance returned is normalized so that a score of 0
represents an exact match between two strings and a 1 maximal
difference. This kind of operation involves so called `fuzzy` logic
which, unlike boolean definitions of true and false, handles the case of
partial matches. In R, the main package for calculating string distance
is the [stringdist](https://github.com/markvanderloo/stringdist)
package. For this use case we need to come up with an algorith that will
sequentially move down a vector, finding the best match within a given
string distance and adopting it as the new standard. Graphically the
algorithm should essentially do the following.

<figure>
<img src="/assets/img/fuzzy_harmonize_stringdist.png"
alt="Harmonize vector using stringdist" />
<figcaption aria-hidden="true">Harmonize vector using
stringdist</figcaption>
</figure>

To walk down the step the vector we could either use for loops or a
recursive function. However there is a function specifically for this
kind of recursion in the purrr package,
[reduce](https://blog.zhaw.ch/datascience/r-reduce-applys-lesser-known-brother/)!
In order to use either approach we need to first define the function we
want to apply between each element and the vector. I’m going to call the
function `fmatch` though that may already exist elsewhere.

``` r
# This is pretty cool!
fmatch <- function(vector, element, max_dist = 0.1) {
  
  # return the closest matching element in the vector 
  key <- vector[vector != element]
  dist <- stringdist::stringdist(element, key, method = "jw")
  if(!is.null(element)) {
    if(!is.na(element)) {
      if(length(dist) > 0 & any(!is.na(dist))) {
        if(min(dist, na.rm = T) < max_dist) return(c(vector, key[which.min(dist)]))
      }
    }
  }

  # or if no match within the appropriate distance is found, add the original element to the standardized vector
  return(c(vector, element))
}
```

Now we just need to invoke it using the reduce function as so:

``` r
outbreak_data <- outbreak_data |> mutate(standardized_disease_name = reduce(disease_name, fmatch, max_dist = 0.1))
```

which produces the following:

| disease_name       | outbreaks | standardized_disease_name |
|:-------------------|----------:|:--------------------------|
| Influenza          |        15 | Influenza                 |
| Inflenza           |        10 | Influenza                 |
| COVID-19           |        95 | COVID-19                  |
| sars-covid-19      |        90 | sars-covid-19             |
| Malaria            |        20 | Malaria                   |
| Maleria            |        22 | Malaria                   |
| malaria            |        20 | Malaria                   |
| Diabetes           |        30 | Diabetes                  |
| Diabetis           |        28 | Diabetes                  |
| HIV/AIDS           |        75 | HIV/AIDS                  |
| HIV                |        70 | HIV                       |
| AIDS               |        65 | AIDS                      |
| Tuberculosis       |        40 | Tuberculosis              |
| Tuberclosis        |        38 | Tuberculosis              |
| Alzheimers         |        23 | Alzheimers                |
| Alzheimers Disease |        27 | Alzheimers Disease        |
| Heart Disease      |        60 | Heart Disease             |
| Heart Diease       |        58 | Heart Disease             |

Notice how not everything was standardized? That’s because we chose a
relatively stringent maximum disease distance. If we instead set
`max_dist = 0.2` we get the following:

| disease_name       | outbreaks | standardized_disease_name |
|:-------------------|----------:|:--------------------------|
| Influenza          |        15 | Influenza                 |
| Inflenza           |        10 | Influenza                 |
| COVID-19           |        95 | COVID-19                  |
| sars-covid-19      |        90 | sars-covid-19             |
| Malaria            |        20 | Malaria                   |
| Maleria            |        22 | Malaria                   |
| malaria            |        20 | Malaria                   |
| Diabetes           |        30 | Diabetes                  |
| Diabetis           |        28 | Diabetes                  |
| HIV/AIDS           |        75 | HIV/AIDS                  |
| HIV                |        70 | HIV/AIDS                  |
| AIDS               |        65 | AIDS                      |
| Tuberculosis       |        40 | Tuberculosis              |
| Tuberclosis        |        38 | Tuberculosis              |
| Alzheimers         |        23 | Alzheimers                |
| Alzheimers Disease |        27 | Alzheimers                |
| Heart Disease      |        60 | Heart Disease             |
| Heart Diease       |        58 | Heart Disease             |

The weakness of this approach is that it is not always clear what the
best maximum distance to use is. If you set the maximum distance high
enough you might be able to match difficult cases, such as
`COVID-19 and sars-covid-19` but you run the risk of accidentally
changing something to far, like changing `Heart Disease to Malaria`.
It’s is not always clear where the border should be drawn.

2.  Clustering
3.  Natural Language Processing (NLP)
