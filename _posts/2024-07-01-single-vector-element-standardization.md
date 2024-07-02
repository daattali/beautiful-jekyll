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

  

## Standardization by string distance

The most straight forward way to standardize a character vector is to
use string distance. String distance is a measure of how different two
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

![](/assets/img/fuzzy_harmonize_stringdist.png)

To walk down the vector we could either use for loops or some kind of
recursive function. Fortunately there is a function specifically for
this kind of recursion in the purrr package,
[reduce](https://blog.zhaw.ch/datascience/r-reduce-applys-lesser-known-brother/)!
In order to use either approach we first need to define the function we
want to apply between each element and the vector. I’m going to call the
function `fuzzy_match` though that name may already be in use elsewhere.

``` r
library(stringdist)
```

    ## 
    ## Attaching package: 'stringdist'

    ## The following object is masked from 'package:tidyr':
    ## 
    ##     extract

``` r
# This is pretty cool!
fuzzy_match <- function(vector, element, max_dist = 0.1) {
  
  # Return the closest matching element in the vector 
  # Add in a few guards against failure to match
  key <- vector[vector != element]
  dist <- stringdist::stringdist(element, key, method = "jw")
  if(!is.null(element)) {
    if(!is.na(element)) {
      if(length(dist) > 0 & any(!is.na(dist))) {
        if(min(dist, na.rm = T) < max_dist) return(c(vector, key[which.min(dist)]))
      }
    }
  }

  # If no match within max_dist is found, return the original element
  return(c(vector, element))
}
```

Now we just need to invoke it using the reduce function as so:

``` r
# Slick right?
outbreak_data <- outbreak_data |> 
  mutate(standardized_disease_name = reduce(disease_name, fuzzy_match, max_dist = 0.1)) |>
  select(contains("name"), outbreaks)
```

which produces the following:

| disease_name       | standardized_disease_name | outbreaks |
|:-------------------|:--------------------------|----------:|
| Influenza          | Influenza                 |        15 |
| Inflenza           | Influenza                 |        10 |
| COVID-19           | COVID-19                  |        95 |
| sars-covid-19      | sars-covid-19             |        90 |
| Malaria            | Malaria                   |        20 |
| Maleria            | Malaria                   |        22 |
| malaria            | Malaria                   |        20 |
| Diabetes           | Diabetes                  |        30 |
| Diabetis           | Diabetes                  |        28 |
| HIV/AIDS           | HIV/AIDS                  |        75 |
| HIV                | HIV                       |        70 |
| AIDS               | AIDS                      |        65 |
| Tuberculosis       | Tuberculosis              |        40 |
| Tuberclosis        | Tuberculosis              |        38 |
| Alzheimers         | Alzheimers                |        23 |
| Alzheimers Disease | Alzheimers Disease        |        27 |
| Heart Disease      | Heart Disease             |        60 |
| Heart Diease       | Heart Disease             |        58 |

Notice how not everything was standardized? That’s because we chose a
relatively stringent maximum string distance. If we instead set
`max_dist = 0.3` we get the following:

| disease_name       | standardized_disease_name | outbreaks |
|:-------------------|:--------------------------|----------:|
| Influenza          | Influenza                 |        15 |
| Inflenza           | Influenza                 |        10 |
| COVID-19           | COVID-19                  |        95 |
| sars-covid-19      | sars-covid-19             |        90 |
| Malaria            | Malaria                   |        20 |
| Maleria            | Malaria                   |        22 |
| malaria            | Malaria                   |        20 |
| Diabetes           | Diabetes                  |        30 |
| Diabetis           | Diabetes                  |        28 |
| HIV/AIDS           | HIV/AIDS                  |        75 |
| HIV                | HIV/AIDS                  |        70 |
| AIDS               | AIDS                      |        65 |
| Tuberculosis       | Tuberculosis              |        40 |
| Tuberclosis        | Tuberculosis              |        38 |
| Alzheimers         | Alzheimers                |        23 |
| Alzheimers Disease | Alzheimers                |        27 |
| Heart Disease      | Heart Disease             |        60 |
| Heart Diease       | Heart Disease             |        58 |

The weakness of this approach is that it is not always clear what the
best maximum distance to use is. If you set the maximum distance high
enough you might be able to match difficult cases, such as
`COVID-19 and sars-covid-19` but you run the risk of accidentally
changing something too far, like matching `Heart Disease to Malaria`.
It’s is not always clear where that border should be drawn. Another
problem is that this algorithm just chooses the first match to
standardize on, not the best match. It could just as easily settle on
converting everything to `melaria instead of Malaria`. It doesn’t know
which of the two strings is *better* just how different two strings are
from each other.

## Clustering

Another way to do essentially the same thing is through hierarchical
clustering.

## Natural Language Processing (NLP)

Finally we can turn to Natural Language Processing to standardize things
for us. This approach has both advantages and dis-advantages. One of the
advantages is that large language models like chatGPT may have an idea
of which of two strings is better, given the context. That’s a pretty
big bonus. A disadvantage is that the results you get from these models
are not as reproducible as a purely rules-based, or algorithmic
approach.

There is also an element of trust that the results returned were not
altered or biased in any way by the model. This isn’t an issue with
small datasets but could be a real concern when dealing with tables with
millions of rows. Then it can be very difficult to tell if the model
just happens to be biased against some of the results. Perhaps it is
much more stringent about matching names starting with the letter ‘J’
than those that start with ‘S’.

To perform vector harmonization using NLP in R we can turn to the
[openai](https://irudnyts.github.io/openai/) package in R, which is a
wrapper around OpenAI’s API. In order to have a conversation with one of
OpenAI’s models we first have to set up the conversation including
choosing which model we want to use, telling the model who it should be,
and formatting our query appropriately. This involves a series of lists.

``` r
library(openai)
```
