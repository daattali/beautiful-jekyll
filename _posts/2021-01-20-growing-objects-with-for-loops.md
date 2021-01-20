Growing objects (for loops)
================
W. A. Corrales
17-09-2020

When we make operations inside for loops, for instance, compute the mean
of each row in a data frame. There is a huge difference in computation
time between generating a growing object (for example, with **c()**
function) and pre-allocating the object before running the for loop.

``` r
install.packages("tictoc")
```

*Note: The R package tictoc, allow us to measure execution time in an
easy way.*

``` r
library(tictoc)
```

**For large datasets, the impact in run time is really considerable.**

### Create a large matrix (10^8 elements) to work with

``` r
# Create data
mat <- matrix(1:100000000, nrow = 1000, ncol = 100000, byrow = F)
```

### Example 1: Growing object with c()

``` r
tic()

# Create empty vector to hold results
result_1 <- c()

# Compute mean for each column within a for loop
for (i in 1:ncol(mat)){
  result_1 <- c(result_1, mean(mat[,i]))
}

toc()
```

    ## 11.541 sec elapsed

### Example 2: Pre-allocating the recipient object

``` r
tic()

# Create a vector with size 10.000 to hold the results
result_2 <- vector("numeric", ncol(mat))

# Compute mean for each column within a for loop
for (i in 1:ncol(mat)){
  result_2[i] <- mean(mat[,i])
}

toc()
```

    ## 0.683 sec elapsed

As you can see, pre-allocating the space needed to hold the results is
in this case at least **10 times faster**

![OMG](/assets/img/omg_cat.jpg){: .mx-auto.d-block :}
