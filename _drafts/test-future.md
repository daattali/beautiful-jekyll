---
layout: post
title: test future
subtitle: abracadabra
category: general
tags:
  - misc
---

# Test test

<div markdown="1" style="float:left; width:50%;">

<h3 style="text-align: center;" markdown="1"> Python </h3>  

~~~python
print "hello"
print "world"
~~~


</div>


<div markdown="1" style="float:left; width:50%;">

<h3 style="text-align: center;" markdown="1"> R </h3>  

~~~R
# Goal: To do nonlinear regression, in three ways
#       By just supplying the function to be fit,
#       By also supplying the analytical derivatives, and
#       By having him analytically differentiate the function to be fit.
#
# John Fox has a book "An R and S+ companion to applied regression"
# (abbreviated CAR).
# An appendix associated with this book, titled
#   "Nonlinear regression and NLS"
# is up on the web, and I strongly recommend that you go read it.
#
# This file is essentially from there (I have made slight changes).

# First take some data - from the CAR book --
library(car)
data(US.pop)
attach(US.pop)
plot(year, population, type="l", col="blue")

# So you see, we have a time-series of the US population. We want to
# fit a nonlinear model to it.

library(stats)                            # Contains nonlinear regression
time <- 0:20
pop.mod <- nls(population ~ beta1/(1 + exp(beta2 + beta3*time)),
  start=list(beta1=350, beta2=4.5, beta3=-0.3), trace=TRUE)
# You just write in the formula that you want to fit, and supply
# starting values. "trace=TRUE" makes him show iterations go by.

summary(pop.mod)
# Add in predicted values into the plot
lines(year, fitted.values(pop.mod), lwd=3, col="red")

# Look at residuals
plot(year, residuals(pop.mod), type="b")
abline(h=0, lty=2)

# Using analytical derivatives:
model <- function(beta1, beta2, beta3, time) {
  m <- beta1/(1+exp(beta2+beta3*time))
  term <- exp(beta2 + beta3*time)
  gradient <- cbind((1+term)^-1,
                    -beta1*(1+term)^-2 * term,
                    -beta1*(1+term)^-2 * term * time)
  attr(m, 'gradient') <- gradient
  return(m)
}

summary(nls(population ~ model(beta1, beta2, beta3, time),
            start=list(beta1=350, beta2=4.5, beta3=-0.3)))

# Using analytical derivatives, using automatic differentiation (!!!):
model <- deriv(~ beta1/(1 + exp(beta2+beta3*time)), # rhs of model
               c('beta1', 'beta2', 'beta3'), # parameter names
               function(beta1, beta2, beta3, time){} # arguments for result
               )
summary(nls(population ~ model(beta1, beta2, beta3, time),
            start=list(beta1=350, beta2=4.5, beta3=-0.3)))

~~~
</div>
