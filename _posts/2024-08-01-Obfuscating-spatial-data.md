---
layout: post
title: Obfuscating spatial data
subtitle: How can we protect sensitive information while still ensuring reproducibility?
image: /assets/img/spatial_obfuscation.png
cover-img: /assets/img/spatial_obfuscation.png
share-img: /assets/img/spatial_obfuscation.png
tags: [data, R, tricks]
---

First the awesome graphic from this post comes from this really
interesting
[project](https://www.redblobgames.com/x/1843-planet-generation/) to
construct model planets by procedurally generating maps on a sphere.

Okay now on to spatial obfuscation! There are a number of reasons why it
might be important to obfuscate latitude and longitude data. Issues of
privacy and security may make it a bad idea to reveal the precise
location data was collected. I wanted to make a quick and dirty way to
obfuscate latitutde and longitude data for a study while at the same
time retaining the ability to share the raw data with collaborators.

The simplest way to do this is to take advantage of how random numbers
are generated. As it turns out random numbers are not truly random. In
fact it is quite hard to generate a truly random number. While there are
some very creative
[methods](https://blog.cloudflare.com/randomness-101-lavarand-in-production)
to try and attain true randomness, in general, random numbers are
generated using psuedo-random number generating (PRNG) algorithms that
start with a seed and generate a series of numbers from that starting
point. What this means is that high-quality PRNGs produce sequences of
numbers that pass various statistical tests for randomness but they
**don’t** ensure randomness *between* sequences. What you get is a
guarentee that the next number returned from subsequent calls to runif
is random as long as you don’t reset the algorithm or change the seed.

In R we can generate numbers using the function `runif`.

``` r
runif(1)
```

    ## [1] 0.4642937

If you want to ensure that you get the same number each time you can set
the psuedo-random number seed before generating random number.

``` r
set.seed(10)
runif(1)
```

    ## [1] 0.5074782

This will ensure that every time you run the code you will get the same
result. But what about if someone else runs your code on another
comptuer? As it turns out that unless you specify the specific PRNG,
even when you set the same seed, it is possible to get a different
result when using a different machine. To fix that we can specify which
number we want to use as a seed *and* what algorithm to use to convert
that seed into a random number. This can be done like this:

``` r
set.seed(10, kind = "Mersenne-Twister", normal.kind = "Inversion")
runif(1)
```

    ## [1] 0.5074782

Now if we use the same seed we can generate the same set of random
numbers. This relates to spatial obfuscation because it gives us a
method to generate random numbers using a secret key and then to undo
the obfuscation operation for analysis or when sharing data with
collaborators. This would look something like this.

``` r
obfuscate_latlong <- function(x, secret_seed, fuzz = 1, direction = 0) {

set.seed(secret_seed, kind = "Mersenne-Twister", normal.kind = "Inversion")
shift <- runif(length(x), min = -fuzz, max = fuzz)

x <- x + ifelse(!direction, -1, 1)*shift
x
} 

secret_seed <- 12345

x <- 48.8566
obfuscated <- obfuscate_latlong(x, secret_seed, direction = 0)
print(obfuscated)
```

    ## [1] 48.41479

``` r
unobfuscated <- obfuscate_latlong(obfuscated, secret_seed, direction = 1)

print(paste("Original value:", x))
```

    ## [1] "Original value: 48.8566"

``` r
print(paste("Obfuscated value:", obfuscated))
```

    ## [1] "Obfuscated value: 48.414792207478"

``` r
print(paste0("Unobfuscated value:", unobfuscated))
```

    ## [1] "Unobfuscated value:48.8566"

Now if you want to obfuscate latitude or longitude values in a
reversable way all you have to do is share the secret_seed and the
direction the data was originally encryped in!

Obfuscation techniques might include aggregating data to larger
geographic units, adding random noise as we did here, or using spatial
masking methods. The goal is to balance data utility with the need to
protect sensitive information. This can be challenging when we also want
to ensure that analyses are open and reproducible. The gold standard of
reproducibility is to share all code and data involved in an analsyis.
With this, and similar methods, data can be publicly shared so that the
method can be reproduced and the secret_seed shared with trusted
collaborators to exactly reproduce the analysis results ensuring that
the anonymnity of the data can be preserved.
