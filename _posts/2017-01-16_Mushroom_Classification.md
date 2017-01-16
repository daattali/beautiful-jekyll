---
layout: post
title: "Mushroom Classification - What makes them edible?"
tags: [CART, RandomForest, Classification, SVM]
---
-   [Import the data](#import-the-data)
-   [Tidy the data](#tidy-the-data)
-   [Understand the data](#understand-the-data)
    -   [A. Transform the data](#a.-transform-the-data)
    -   [A. Visualize the data](#a.-visualize-the-data)
    -   [A. Modeling](#a.-modeling)
        -   [A. Use of Regression Tree](#a.-use-of-regression-tree)
        -   [A. Use of Random Forest](#a.-use-of-random-forest)
        -   [A. Use of SVM](#a.-use-of-svm)

This article is about classifying mushroom as edible or not.
[This blog post](https://stoltzmaniac.com/random-forest-classification-of-mushrooms/) gave us first the idea and we followed most of it. We also noticed that Kaggle has put online the same data set and classification exercise. We have taken inspiration from some posts [here](https://www.kaggle.com/abhishekheads/d/uciml/mushroom-classification/walk-through-of-different-classification-models) and [here](https://www.kaggle.com/jhuno137/d/uciml/mushroom-classification/classification-tree-using-rpart-100-accuracy)

The data set is available on the [Machine Learning Repository](http://archive.ics.uci.edu/ml/datasets/Mushroom) of the UC Irvine website.

Import the data
===============

The data set is given to us in a bit of a rough form and quite a bit of editing is necessary.

``` r
# Load the data - we downloaded the data from the website and saved it into a .csv file
library(readr)
library(dplyr)

mushroom <- read_csv("Mushroom.csv", col_names = FALSE) 

glimpse(mushroom)
```

    ## Observations: 8,124
    ## Variables: 23
    ## $ X1  <chr> "p", "e", "e", "p", "e", "e", "e", "e", "p", "e", "e", "e"...
    ## $ X2  <chr> "x", "x", "b", "x", "x", "x", "b", "b", "x", "b", "x", "x"...
    ## $ X3  <chr> "s", "s", "s", "y", "s", "y", "s", "y", "y", "s", "y", "y"...
    ## $ X4  <chr> "n", "y", "w", "w", "g", "y", "w", "w", "w", "y", "y", "y"...
    ## $ X5  <chr> "t", "t", "t", "t", "f", "t", "t", "t", "t", "t", "t", "t"...
    ## $ X6  <chr> "p", "a", "l", "p", "n", "a", "a", "l", "p", "a", "l", "a"...
    ## $ X7  <chr> "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f", "f"...
    ## $ X8  <chr> "c", "c", "c", "c", "w", "c", "c", "c", "c", "c", "c", "c"...
    ## $ X9  <chr> "n", "b", "b", "n", "b", "b", "b", "b", "n", "b", "b", "b"...
    ## $ X10 <chr> "k", "k", "n", "n", "k", "n", "g", "n", "p", "g", "g", "n"...
    ## $ X11 <chr> "e", "e", "e", "e", "t", "e", "e", "e", "e", "e", "e", "e"...
    ## $ X12 <chr> "e", "c", "c", "e", "e", "c", "c", "c", "e", "c", "c", "c"...
    ## $ X13 <chr> "s", "s", "s", "s", "s", "s", "s", "s", "s", "s", "s", "s"...
    ## $ X14 <chr> "s", "s", "s", "s", "s", "s", "s", "s", "s", "s", "s", "s"...
    ## $ X15 <chr> "w", "w", "w", "w", "w", "w", "w", "w", "w", "w", "w", "w"...
    ## $ X16 <chr> "w", "w", "w", "w", "w", "w", "w", "w", "w", "w", "w", "w"...
    ## $ X17 <chr> "p", "p", "p", "p", "p", "p", "p", "p", "p", "p", "p", "p"...
    ## $ X18 <chr> "w", "w", "w", "w", "w", "w", "w", "w", "w", "w", "w", "w"...
    ## $ X19 <chr> "o", "o", "o", "o", "o", "o", "o", "o", "o", "o", "o", "o"...
    ## $ X20 <chr> "p", "p", "p", "p", "e", "p", "p", "p", "p", "p", "p", "p"...
    ## $ X21 <chr> "k", "n", "n", "k", "n", "k", "k", "n", "k", "k", "n", "k"...
    ## $ X22 <chr> "s", "n", "n", "s", "a", "n", "n", "s", "v", "s", "n", "s"...
    ## $ X23 <chr> "u", "g", "m", "u", "g", "g", "m", "m", "g", "m", "g", "m"...

The data frame doesn't look very meaningfull. We'll have to go back to the source to bring meaning to each of the variables and to the various levels of the categorical variables.

Tidy the data
=============

This is the least fun part of the workflow.
We'll start by giving names to each of the variables, then we specify the category for each variable. It is not necessary to do so but it does add meaning to what we do.

``` r
# Rename the variables
colnames(mushroom) <- c("edibility", "cap_shape", "cap_surface", 
                        "cap_color", "bruises", "odor", 
                        "gill_attachement", "gill_spacing", "gill_size", 
                        "gill_color", "stalk_shape", "stalk_root", 
                        "stalk_surface_above_ring", "stalk_surface_below_ring", "stalk_color_above_ring", 
                        "stalk_color_below_ring", "veil_type", "veil_color", 
                        "ring_number", "ring_type", "spore_print_color", 
                        "population", "habitat")

# Defining the levels for the categorical variables 
## We make each variable as a factor
library(purrr)
mushroom <- mushroom %>% map_df(function(.x) as.factor(.x))

## We redefine each of the category for each of the variables
levels(mushroom$edibility) <- c("edible", "poisonous")
levels(mushroom$cap_shape) <- c("bell", "conical", "flat", "knobbed", "sunken", "convex")
levels(mushroom$cap_color) <- c("buff", "cinnamon", "red", "gray", "brown", "pink", 
                                "green", "purple", "white", "yellow")
levels(mushroom$cap_surface) <- c("fibrous", "grooves", "scaly", "smooth")
levels(mushroom$bruises) <- c("no", "yes")
levels(mushroom$odor) <- c("almond", "creosote", "foul", "anise", "musty", "none", "pungent", "spicy", "fishy")
levels(mushroom$gill_attachement) <- c("attached", "free")
levels(mushroom$gill_spacing) <- c("close", "crowded")
levels(mushroom$gill_size) <- c("broad", "narrow")
levels(mushroom$gill_color) <- c("buff", "red", "gray", "chocolate", "black", "brown", "orange", 
                                 "pink", "green", "purple", "white", "yellow")
levels(mushroom$stalk_shape) <- c("enlarging", "tapering")
levels(mushroom$stalk_root) <- c("missing", "bulbous", "club", "equal", "rooted")
levels(mushroom$stalk_surface_above_ring) <- c("fibrous", "silky", "smooth", "scaly")
levels(mushroom$stalk_surface_below_ring) <- c("fibrous", "silky", "smooth", "scaly")
levels(mushroom$stalk_color_above_ring) <- c("buff", "cinnamon", "red", "gray", "brown", "pink", 
                                "green", "purple", "white", "yellow")
levels(mushroom$stalk_color_below_ring) <- c("buff", "cinnamon", "red", "gray", "brown", "pink", 
                                "green", "purple", "white", "yellow")
levels(mushroom$veil_type) <- "partial"
levels(mushroom$veil_color) <- c("brown", "orange", "white", "yellow")
levels(mushroom$ring_number) <- c("none", "one", "two")
levels(mushroom$ring_type) <- c("evanescent", "flaring", "large", "none", "pendant")
levels(mushroom$spore_print_color) <- c("buff", "chocolate", "black", "brown", "orange", 
                                        "green", "purple", "white", "yellow")
levels(mushroom$population) <- c("abundant", "clustered", "numerous", "scattered", "several", "solitary")
levels(mushroom$habitat) <- c("wood", "grasses", "leaves", "meadows", "paths", "urban", "waste")


glimpse(mushroom)
```

    ## Observations: 8,124
    ## Variables: 23
    ## $ edibility                <fctr> poisonous, edible, edible, poisonous...
    ## $ cap_shape                <fctr> convex, convex, bell, convex, convex...
    ## $ cap_surface              <fctr> scaly, scaly, scaly, smooth, scaly, ...
    ## $ cap_color                <fctr> brown, yellow, white, white, gray, y...
    ## $ bruises                  <fctr> yes, yes, yes, yes, no, yes, yes, ye...
    ## $ odor                     <fctr> pungent, almond, anise, pungent, non...
    ## $ gill_attachement         <fctr> free, free, free, free, free, free, ...
    ## $ gill_spacing             <fctr> close, close, close, close, crowded,...
    ## $ gill_size                <fctr> narrow, broad, broad, narrow, broad,...
    ## $ gill_color               <fctr> black, black, brown, brown, black, b...
    ## $ stalk_shape              <fctr> enlarging, enlarging, enlarging, enl...
    ## $ stalk_root               <fctr> equal, club, club, equal, equal, clu...
    ## $ stalk_surface_above_ring <fctr> smooth, smooth, smooth, smooth, smoo...
    ## $ stalk_surface_below_ring <fctr> smooth, smooth, smooth, smooth, smoo...
    ## $ stalk_color_above_ring   <fctr> purple, purple, purple, purple, purp...
    ## $ stalk_color_below_ring   <fctr> purple, purple, purple, purple, purp...
    ## $ veil_type                <fctr> partial, partial, partial, partial, ...
    ## $ veil_color               <fctr> white, white, white, white, white, w...
    ## $ ring_number              <fctr> one, one, one, one, one, one, one, o...
    ## $ ring_type                <fctr> pendant, pendant, pendant, pendant, ...
    ## $ spore_print_color        <fctr> black, brown, brown, black, brown, b...
    ## $ population               <fctr> scattered, numerous, numerous, scatt...
    ## $ habitat                  <fctr> urban, grasses, meadows, urban, gras...

Understand the data
===================

This is the circular phase of our dealing with data. This is where each of the transforming, visualizing and modeling stage reinforce each other to create a better understanding.
![data workflow](/img/Mushroom_files/figure-markdown_github/data_workflow.png)

A. Transform the data
---------------------

We noticed from the previous section an issue with the veil\_type variable. It has only one factor. So basically, it does not bring any information. Furthermore, factor variable with only one level do create issues later on at the modeling stage. R will throw out an error for the categorical variable that has only one level.
So let's take away that column.

``` r
mushroom <- mushroom %>% select(- veil_type)
```

Do we have any missing data? Most ML algorithms won't work if we have missing data.

``` r
library(purrr)
map_dbl(mushroom, function(.x) {sum(is.na(.x))})
```

    ##                edibility                cap_shape              cap_surface 
    ##                        0                        0                        0 
    ##                cap_color                  bruises                     odor 
    ##                        0                        0                        0 
    ##         gill_attachement             gill_spacing                gill_size 
    ##                        0                        0                        0 
    ##               gill_color              stalk_shape               stalk_root 
    ##                        0                        0                        0 
    ## stalk_surface_above_ring stalk_surface_below_ring   stalk_color_above_ring 
    ##                        0                        0                        0 
    ##   stalk_color_below_ring               veil_color              ring_number 
    ##                        0                        0                        0 
    ##                ring_type        spore_print_color               population 
    ##                        0                        0                        0 
    ##                  habitat 
    ##                        0

Lucky us! We have no missing data.

A. Visualize the data
---------------------

This is one of the most important step in the DS process. This stage can gives us unexpected insights and often allows us to ask the right questions.

``` r
library(ggplot2)
ggplot(mushroom, aes(x = cap_surface, y = cap_color, col = edibility)) + 
  geom_jitter(alpha = 0.5) + 
  scale_color_manual(breaks = c("edible", "poisonous"), 
                     values = c("green", "red"))
```

![](/img/Mushroom_files/figure-markdown_github/unnamed-chunk-5-1.png) 
If we want to stay safe, better bet on *fibrous* surface. Stay especially away from *smooth* surface, except if they are purple or green.

``` r
ggplot(mushroom, aes(x = cap_shape, y = cap_color, col = edibility)) + 
  geom_jitter(alpha = 0.5) + 
  scale_color_manual(breaks = c("edible", "poisonous"), 
                     values = c("green", "red"))
```

![](/img/Mushroom_files/figure-markdown_github/unnamed-chunk-6-1.png) 
Again, in case one don't know about mushroom, it is better to stay away from all shapes except maybe for *bell* shape mushrooms.

``` r
ggplot(mushroom, aes(x = gill_color, y = cap_color, col = edibility)) + 
  geom_jitter(alpha = 0.5) + 
  scale_color_manual(breaks = c("edible", "poisonous"), 
                     values = c("green", "red"))
```

![](/img/Mushroom_files/figure-markdown_github/unnamed-chunk-7-1.png)

``` r
ggplot(mushroom, aes(x = edibility, y = odor, col = edibility)) + 
  geom_jitter(alpha = 0.5) + 
  scale_color_manual(breaks = c("edible", "poisonous"), 
                     values = c("green", "red"))
```

![](/img/Mushroom_files/figure-markdown_github/unnamed-chunk-7-2.png) 
Odor is defintely quite an informative predictor. Basically, if it smells *fishy*, *spicy* or *pungent* just stay away. If it smells like *anise* or *almond* you can go ahead. If it doesn't smell anything, you have better chance that it is edible than not.

TO DO: put a comment on what we see TO DO: put a mosaic graph

A. Modeling
-----------

At this stage, we should have gather enough information and insights on our data to choose appropriate modeling techniques.

Before we go ahead, we need to split the data into training and testing set

``` r
set.seed(1810)
mushsample <- caret::createDataPartition(y = mushroom$edibility, times = 1, p = 0.8, list = FALSE)
train_mushroom <- mushroom[mushsample, ]
test_mushroom <- mushroom[-mushsample, ]
```

We can check the quality of the splits in regards to our predicted (dependent) variable.

``` r
round(prop.table(table(mushroom$edibility)), 2)
```

    ## 
    ##    edible poisonous 
    ##      0.52      0.48

``` r
round(prop.table(table(train_mushroom$edibility)), 2)
```

    ## 
    ##    edible poisonous 
    ##      0.52      0.48

``` r
round(prop.table(table(test_mushroom$edibility)), 2)
```

    ## 
    ##    edible poisonous 
    ##      0.52      0.48

It seems like we have the right split.

### A. Use of Regression Tree

As we have many categorical variables, regression tree is an ideal classification tools for such situation.
We'll use the `rpart` package.

``` r
library(rpart)
library(rpart.plot)
set.seed(1810)
model_tree <- rpart(edibility ~ ., data = train_mushroom, method = "class", cp=0.00001)
model_tree
```

    ## n= 6500 
    ## 
    ## node), split, n, loss, yval, (yprob)
    ##       * denotes terminal node
    ## 
    ##  1) root 6500 3133 edible (0.518000000 0.482000000)  
    ##    2) odor=almond,anise,none 3463   96 edible (0.972278371 0.027721629)  
    ##      4) spore_print_color=buff,chocolate,black,brown,orange,purple,white,yellow 3407   40 edible (0.988259466 0.011740534)  
    ##        8) stalk_color_below_ring=red,gray,brown,pink,green,purple 3388   21 edible (0.993801653 0.006198347)  
    ##         16) stalk_color_below_ring=red,gray,pink,green,purple 3321    7 edible (0.997892201 0.002107799)  
    ##           32) habitat=wood,grasses,meadows,paths,urban,waste 3160    0 edible (1.000000000 0.000000000) *
    ##           33) habitat=leaves 161    7 edible (0.956521739 0.043478261)  
    ##             66) cap_surface=scaly 154    0 edible (1.000000000 0.000000000) *
    ##             67) cap_surface=grooves,smooth 7    0 poisonous (0.000000000 1.000000000) *
    ##         17) stalk_color_below_ring=brown 67   14 edible (0.791044776 0.208955224)  
    ##           34) stalk_root=bulbous 53    0 edible (1.000000000 0.000000000) *
    ##           35) stalk_root=missing 14    0 poisonous (0.000000000 1.000000000) *
    ##        9) stalk_color_below_ring=white 19    0 poisonous (0.000000000 1.000000000) *
    ##      5) spore_print_color=green 56    0 poisonous (0.000000000 1.000000000) *
    ##    3) odor=creosote,foul,musty,pungent,spicy,fishy 3037    0 poisonous (0.000000000 1.000000000) *

We set up a low `cp` (that is we'll have a deep tree). The idea is that we then prune it later.

``` r
printcp(model_tree)
```

    ## 
    ## Classification tree:
    ## rpart(formula = edibility ~ ., data = train_mushroom, method = "class", 
    ##     cp = 1e-05)
    ## 
    ## Variables actually used in tree construction:
    ## [1] cap_surface            habitat                odor                  
    ## [4] spore_print_color      stalk_color_below_ring stalk_root            
    ## 
    ## Root node error: 3133/6500 = 0.482
    ## 
    ## n= 6500 
    ## 
    ##          CP nsplit rel error    xerror       xstd
    ## 1 0.9693584      0 1.0000000 1.0000000 0.01285833
    ## 2 0.0178742      1 0.0306416 0.0306416 0.00310416
    ## 3 0.0060645      2 0.0127673 0.0127673 0.00201247
    ## 4 0.0022343      3 0.0067028 0.0067028 0.00146032
    ## 5 0.0011171      5 0.0022343 0.0022343 0.00084402
    ## 6 0.0000100      7 0.0000000 0.0022343 0.00084402

``` r
plotcp(model_tree)
```

![](/img/Mushroom_files/figure-markdown_github/unnamed-chunk-12-1.png)

``` r
model_tree$cptable[which.min(model_tree$cptable[, "xerror"]), "CP"]
```

    ## [1] 0.00111714

So now we can start pruning our tree with the `cp` that gives the lowest corss-validation error.

``` r
bestcp <- round(model_tree$cptable[which.min(model_tree$cptable[, "xerror"]), "CP"], 4)
model_tree_pruned <- prune(model_tree, cp = bestcp)
```

Let's have a quick look at the tree as it stands

``` r
rpart.plot(model_tree_pruned, extra = 104, box.palette = "GnBu", 
           branch.lty = 3, shadow.col = "gray", nn = TRUE)
```

![](/img/Mushroom_files/figure-markdown_github/unnamed-chunk-15-1.png)

How does the model perform on the train data?

``` r
#table(train_mushroom$edibility, predict(model_tree, type="class"))

caret::confusionMatrix(data=predict(model_tree_pruned, type = "class"), 
                       reference = train_mushroom$edibility, 
                       positive="edible")
```

    ## Confusion Matrix and Statistics
    ## 
    ##            Reference
    ## Prediction  edible poisonous
    ##   edible      3367         0
    ##   poisonous      0      3133
    ##                                      
    ##                Accuracy : 1          
    ##                  95% CI : (0.9994, 1)
    ##     No Information Rate : 0.518      
    ##     P-Value [Acc > NIR] : < 2.2e-16  
    ##                                      
    ##                   Kappa : 1          
    ##  Mcnemar's Test P-Value : NA         
    ##                                      
    ##             Sensitivity : 1.000      
    ##             Specificity : 1.000      
    ##          Pos Pred Value : 1.000      
    ##          Neg Pred Value : 1.000      
    ##              Prevalence : 0.518      
    ##          Detection Rate : 0.518      
    ##    Detection Prevalence : 0.518      
    ##       Balanced Accuracy : 1.000      
    ##                                      
    ##        'Positive' Class : edible     
    ## 

It seems like we have a perfect accuracy on our training set. It is quite rare to have such perfect accuracy.

Let's check how it fares on the testing set.

``` r
test_tree <- predict(model_tree, newdata = test_mushroom)
caret::confusionMatrix(data = predict(model_tree, newdata = test_mushroom, type = "class"), 
                       reference = test_mushroom$edibility, 
                       positive = "edible")
```

    ## Confusion Matrix and Statistics
    ## 
    ##            Reference
    ## Prediction  edible poisonous
    ##   edible       841         0
    ##   poisonous      0       783
    ##                                      
    ##                Accuracy : 1          
    ##                  95% CI : (0.9977, 1)
    ##     No Information Rate : 0.5179     
    ##     P-Value [Acc > NIR] : < 2.2e-16  
    ##                                      
    ##                   Kappa : 1          
    ##  Mcnemar's Test P-Value : NA         
    ##                                      
    ##             Sensitivity : 1.0000     
    ##             Specificity : 1.0000     
    ##          Pos Pred Value : 1.0000     
    ##          Neg Pred Value : 1.0000     
    ##              Prevalence : 0.5179     
    ##          Detection Rate : 0.5179     
    ##    Detection Prevalence : 0.5179     
    ##       Balanced Accuracy : 1.0000     
    ##                                      
    ##        'Positive' Class : edible     
    ## 

Perfect prediction here as well.

### A. Use of Random Forest

We usually use random forest if a tree is not enough. In this case, as we have perfect prediction using a single tree, it is not really necessary to use a Random Forest algorithm. We just use for learning sake without tuning any of the parameters.

``` r
library(randomForest)
model_rf <- randomForest(edibility ~ ., ntree = 50, data = train_mushroom)
plot(model_rf)
```

![](/img/Mushroom_files/figure-markdown_github/unnamed-chunk-18-1.png) The default number of trees for the random forest is 500; we just use 50 here. As we can see on the plot, above 20 trees, the error isn't decreasing anymore. And actually, the error seems to be 0 or almost 0.
The next step can tell us this more accurately.

``` r
print(model_rf)
```

    ## 
    ## Call:
    ##  randomForest(formula = edibility ~ ., data = train_mushroom,      ntree = 50) 
    ##                Type of random forest: classification
    ##                      Number of trees: 50
    ## No. of variables tried at each split: 4
    ## 
    ##         OOB estimate of  error rate: 0%
    ## Confusion matrix:
    ##           edible poisonous class.error
    ## edible      3367         0           0
    ## poisonous      0      3133           0

Altough it is not really necessary to this here as we have a perfect prediction, we can use the `confusionMatrix` function from the `caret` pacakge.

``` r
caret::confusionMatrix(data = model_rf$predicted, reference = train_mushroom$edibility , 
                       positive = "edible")
```

    ## Confusion Matrix and Statistics
    ## 
    ##            Reference
    ## Prediction  edible poisonous
    ##   edible      3367         0
    ##   poisonous      0      3133
    ##                                      
    ##                Accuracy : 1          
    ##                  95% CI : (0.9994, 1)
    ##     No Information Rate : 0.518      
    ##     P-Value [Acc > NIR] : < 2.2e-16  
    ##                                      
    ##                   Kappa : 1          
    ##  Mcnemar's Test P-Value : NA         
    ##                                      
    ##             Sensitivity : 1.000      
    ##             Specificity : 1.000      
    ##          Pos Pred Value : 1.000      
    ##          Neg Pred Value : 1.000      
    ##              Prevalence : 0.518      
    ##          Detection Rate : 0.518      
    ##    Detection Prevalence : 0.518      
    ##       Balanced Accuracy : 1.000      
    ##                                      
    ##        'Positive' Class : edible     
    ## 

If we want to look at the most important variable in terms of predicting edibility in our model, we can do that using the *Mean Decreasing Gini*

``` r
varImpPlot(model_rf, sort = TRUE, 
           n.var = 10, main = "The 10 variables with the most predictive power")
```

![](Mushroom_files/figure-markdown_github/unnamed-chunk-21-1.png)

Another way to look at the predictible power of the variables is to use the `importance` extractor function.

``` r
library(tibble)
x <- importance(model_rf) %>% data.frame() %>% rownames_to_column(var = "Variable") %>% 
       arrange(desc(MeanDecreaseGini))
head(x, 10)
```

    ##                    Variable MeanDecreaseGini
    ## 1                      odor       1175.48356
    ## 2         spore_print_color        480.99068
    ## 3                gill_color        304.69323
    ## 4                 gill_size        267.12978
    ## 5                 ring_type        162.93938
    ## 6  stalk_surface_below_ring        147.64475
    ## 7  stalk_surface_above_ring        132.72946
    ## 8                   habitat         90.18568
    ## 9                stalk_root         77.34850
    ## 10               population         71.01217

Now we apply our model to our testing set.

``` r
test_rf <- predict(model_rf, newdata = test_mushroom)

# Quick check on our prediction
table(test_rf, test_mushroom$edibility)
```

    ##            
    ## test_rf     edible poisonous
    ##   edible       841         0
    ##   poisonous      0       783

### A. Use of SVM

``` r
library(e1071)
model_svm <- svm(edibility ~. , data=train_mushroom, cost = 1000, gamma = 0.01)
```

Check the prediction

``` r
test_svm <- predict(model_svm, newdata = test_mushroom)

table(test_svm, test_mushroom$edibility)
```

    ##            
    ## test_svm    edible poisonous
    ##   edible       841         0
    ##   poisonous      0       783
