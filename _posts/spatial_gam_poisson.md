# GAM splines now easy in JAGS. An example on 2D spatial data
Petr Keil  
03/02/2015  

Last week I met Simon Wood, creator of `mgcv` package, which is THE tool for
fitting Generalized Additive Models (GAM) in R. 

Simon brought my attention to function `jagam` which he has just
added to `mgcv`. The function allows to transform the 'spline' or 'smooth'
component of GAM model formula into BUGS code, meaning that the flexibility of
GAMs is now available for routine MCMC model fitting.

I often deal with geographically structured (spatially explicit) data, and 
so I am excited by the prospect of using `jagam` to build spatially explicit
hierarchical models. 

# Why should spatial statisticians care about `jagam`?

Because fitting of spatial splines in JAGS and OpenBUGS has so far been a pain.
Yet from my experience and from personal communication with others
(e.g. C. Dormann, B. O'Hara, C. Beale, S. Wood), **splines are a well-behaved
way to model spatial autocorrelation** that can be easily examined and
visualized separatedly from the rest of the model.

Splines can also be a handy alternative to the popular Conditional Autoregressive
Models (CAR) that are available in OpenBUGS, but unavailable in JAGS. Hence, 
the clarity and portability of JAGS is now available to spatial modellers. 

# The aim of this post

Here I will demonstrate the `jagam` function in action. I will fit a simple Poisson GAM (with X and Y coordinates as predictors) to spatially explicit count data. 
I will also check if I get the same expected values
from `mgcv` and `JAGS`, given the same model.

These are the packages that I will need:


```r
  library(mgcv)   # fits GAMs
  library(spatstat) # the source of the example data
  library(raster) # for operations with rasters
  library(R2jags) # interface between R and JAGS
```

# The data

I will use example dataset `bei` from `spatstat` package. The data 
are positions of 3605 individual trees of *Beilschmiedia pendula* (Lauraceae) in 
a 1000 by 500 metre rectangular sampling region in the tropical rainforest of
Barro Colorado Island. The data are stored in a point process pattern `ppp`
object.

Let's plot the data:


```r
  par(mai=c(0.5,0.3,0.3,0))
  plot(bei, cex=0.1, main=NULL)
```

![](spatial_gam_poisson_files/figure-html/unnamed-chunk-2-1.png) 

I will fit the data into a raster of 25 x 50 grid cells; each grid cell gives
the count of individual trees that fall within the cell:


```r
  # cropping the data so that they have exactly 500 x 1000 cells
  ext <- extent(0, 1000, 0, 500)         # spatial extent of the raster
  empty <- raster(ext, nrow=25, ncol=50) # empty raster
  
  # aggregating the point data into the raster
  xy <- data.frame(x = bei$x, y = bei$y)
  rst <- rasterize(xy, empty, fun = "count")
  
  # replacing the NA values by 0
  rst[is.na(rst)] <- 0
  
  # extracting the cell values and their coordinates to a data.frame
  coord <- xyFromCell(rst,1:ncell(rst))
  count <- extract(rst, 1:ncell(rst))
  all.data <- data.frame(coord, count=count)
```

This is the resulting rasterized dataset, with point locations of the trees
plotted on top. The color gradient shows counts of trees in each grid cell.


```r
  plot(rst, axes=FALSE)
  points(xy, cex=0.1)
```

![](spatial_gam_poisson_files/figure-html/unnamed-chunk-4-1.png) 

# Standard GAM in `mgcv`

This is the standard way to fit X- and Y- splines in `mgcv`:


```r
  # the gam model with s() indicating that I fit splines
  space.only <- gam(count~s(x, y), data=all.data, family = "poisson")
  # extraction of the predictions
  preds.mgcv <- as.vector(predict(space.only, type = "response"))

  # putting the predictions into a raster
  rst.mgcv <- rst
  rst.mgcv[] <- preds.mgcv
```

This is the predicted surface on a map:


```r
  plot(rst.mgcv, axes=FALSE)
  points(xy, cex=0.1)
```

![](spatial_gam_poisson_files/figure-html/unnamed-chunk-6-1.png) 

# The `jagam` function in action

The main point here is that **the new `jagam` function takes the GAM
formula and converts it into a piece of BUGS code**. The resulting code can 
then be run in JAGS, or even in OpenBUGS. Here it is in action:


```r
  jags.ready <- jagam(count~s(x, y), 
                      data=all.data, 
                      family="poisson", 
                      file="jagam.bug")
```

The `jagam` function does two things: **(1)** it creates an object that contains the data in the list format that can be readily used in the `jags` function 
(package `R2jags`), and **(2)** it writes the BUGS model definition into a file. That makes it really easy to fit GAM splines in JAGS. The idea is that
more complex hierarchical structures can then be added directly into the BUGS
code.

Let's have a look into the `jagam.bug` file:


```r
  readLines("jagam.bug")
```

```
##  [1] "model {"                                                        
##  [2] "  eta <- X %*% b ## linear predictor"                           
##  [3] "  for (i in 1:n) { mu[i] <-  exp(eta[i]) } ## expected response"
##  [4] "  for (i in 1:n) { y[i] ~ dpois(mu[i]) } ## response "          
##  [5] "  ## Parameteric effect priors CHECK tau is appropriate!"       
##  [6] "  for (i in 1:1) { b[i] ~ dnorm(0,0.001) }"                     
##  [7] "  ## prior for s(x,y)... "                                      
##  [8] "  K1 <- S1[1:29,1:29] * lambda[1]  + S1[1:29,30:58] * lambda[2]"
##  [9] "  b[2:30] ~ dmnorm(zero[2:30],K1) "                             
## [10] "  ## smoothing parameter priors CHECK..."                       
## [11] "  for (i in 1:2) {"                                             
## [12] "    lambda[i] ~ dgamma(.05,.005)"                               
## [13] "    rho[i] <- log(lambda[i])"                                   
## [14] "  }"                                                            
## [15] "}"
```

# Fitting the model in JAGS

Here I fit the Bayesian model by calling `jags` function from package `R2jags`. 
I will monitor the expected values (`mu`) in each grid cell of the raster.


```r
  model.fit <- jags(data=jags.ready$jags.data, 
               model.file="jagam.bug",
               parameters.to.save=c("mu"),
               n.chains=3,
               n.iter=1000,
               n.burnin=500)
```

```
## module glm loaded
```

```
## Compiling model graph
##    Resolving undeclared variables
##    Allocating nodes
##    Graph Size: 42982
## 
## Initializing model
```

```r
  # extracting the fitted means
  preds.mu <- as.vector(model.fit$BUGSoutput$mean$mu)

  # inserting the fitted means to the raster
  rst.jags <- rst
  rst.jags[] <- preds.mu
```

Let's plot the JAGS results:


```r
  plot(rst.jags, axes=FALSE)
  points(xy, cex=0.1) # adding the positions of individual trees
```

![](spatial_gam_poisson_files/figure-html/unnamed-chunk-10-1.png) 

It looks almost identical to the `mgcv` output. Let's have a closer look.

# `mgcv` vs JAGS

Here I compare the modelled counts from the two models. 


```r
  plot(preds.mgcv, preds.mu,
       xlab="Counts from mgcv",
       ylab="Counts from JAGS")
  abline(a=0, b=1, col="red", lwd=2)
```

![](spatial_gam_poisson_files/figure-html/unnamed-chunk-11-1.png) 

The predicted counts are not identical, JAGS predicts relatively higher 
counts than `mgcv`. I am not sure if this is important -- maybe it has something
to do with my priors, I don't know. But I guess that I don't 
care that much, as long as the predictions are roughly similar.



