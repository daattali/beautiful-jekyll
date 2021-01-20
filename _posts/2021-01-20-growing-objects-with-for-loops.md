Growing objects (for loops)
================
W. A. Corrales
17-09-2020

``` r
knitr::opts_chunk$set(echo = TRUE)

# Load package to measure time
library(tictoc)
```

When we make operations inside for loops, for instance, compute the mean
of each row in a data frame. There is a huge difference in computation
time between generating a growing object (for example, with **c()**
function) and pre-allocating the object before running the for loop.

**For larger datasets, the impact in run time is really considerable.**

### Create a large matrix (100 million elements)

``` r
# Create data
mat <- matrix(1:100000000, nrow = 1000, ncol = 100000, byrow = F)
```

### Example 1: Growing object with c()

``` r
# Start time
tic()

# Create empty vector to hold results
result_1 <- c()

# Compute mean for each column within a for loop
for (i in 1:ncol(mat)){
  result_1 <- c(result_1, mean(mat[,i]))
}

# Finish time
toc()
```

    ## 11.881 sec elapsed

### Example 2: Allocating the recipient object first

``` r
# Start time
tic()

# Create a vector with size 10.000 to hold the results
result_2 <- vector("numeric", ncol(mat))

# Compute mean for each column within a for loop
for (i in 1:ncol(mat)){
  result_2[i] <- mean(mat[,i])
}

# Finish time
toc()
```

    ## 0.638 sec elapsed
