---
geometry: margin=25mm
linkcolor: blue
---
# UBC MDS self-test

## How to use this document

If you are a prospective or entering MDS student and you are not sure about your preparation, try the
questions below. After some review of topics not recently encountered, a prepared student should be able to
do all of the questions below with limited effort in 1-3 hours. These exercises are not meant to represent the
level of MDS content (which will be much higher!); rather, the intent is that if you cannot do these questions
easily, you are likely to struggle in the program without additional preparation. To acquire this preparation,
please see [**our page of suggested learning resources**](https://ubc-mds.github.io/resources_pages/learning_resources/).

### Probability

1. You flip 5 coins. What is the probability of observing 4 heads?

Answer: $5/32$

2. You are offered the opportunity to play the following game: your opponent rolls 2 regular 6-sided dice. If the difference between the two rolls is at least 4, you win \$20. Otherwise, you get nothing. What is a fair price for a ticket to play this game once? In other words, what is the expected earnings of playing the game?

Answer: The possibilities are (1,5), (5,1), (2,6), (6,2), (1,6), (6,1). So in total there are 6 ways out of 36 or $1/6$. Thus the fair price is \$$20/6$.

3. Consider two events $A$ and $B$ such that $\Pr(A \cap B)=0$. If $\Pr(A) = 0.4$ and $\Pr(A \cup B) = 0.95$, what is $\Pr(B)$? Note: $A \cap B$ means "$A$ and $B$" and $A \cup B$ means "$A$ or $B$". It may be helpful to draw a Venn diagram.

Answer: $0.55$

### Statistics

1. You measure the weights of 10 randomly chosen rocks at the beach. The average weight from the rocks you collected is 200 grams. Does this imply that at least 4 of the rocks weigh less than 200 grams? If so, explain why. If not, provide a counterexample.

Answer: No. Counterexample: 100, 210, 210, 210, 210, 210, 210, 210, 210, 220.

2. You decide to study the correlation between the rocks' weight and smoothness. Of your 10 randomly chosen rocks, you notice that the top 3 heaviest rocks are smooth whereas the two lightest rocks are rough. You tentatively conclude that heavier rocks are smoother than lighter rocks. What are two ways in which you could improve this study?

Answer:

 - use all 10 weights in the analysis
 - collect a larger sample (more rocks)
 - come up with a quantitative measure of smoothness

<!-- end answer -->

### Programming

We strongly recommend using Python or R for these programming exercises. Or, even better, do them in both languages!

1. Solve one of the Project Euler problems (<https://projecteuler.net/archives>) of your choice.

Answer:

Problem 1 is 
_If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23. Find the sum of all the multiples of 3 or 5 below 1000._

```python
print(sum(i for i in range(1000) if i % 3 == 0 or i % 5 == 0))
```

<!-- end answer -->

1. Download the file `gapminder_Canada.csv` at <https://github.com/UBC-MDS/public/blob/master/gapminder_Canada.csv>. Then, write a program that reads in this file and computes the mean and variance of each of the four numeric columns. 

Answer:

```r
# R
df <- read_csv("gapminder_Canada.csv")
lapply(df[2:5], mean)
lapply(df[2:5], var)
```

```python
# Python
df = pd.read_csv('gapminder_Canada.csv')
df.agg(['mean', 'var'])
```

<!-- end answer -->

### General math

1. $\log_{10}(x) = -3$. What is $x$? 

Answer: $0.001$

2. True or False: $\exp(x) > 0$ for all $x$.

Answer: True

3. How many different 4-letter "words" can you make using the 26 letters of the alphabet? For example, two of them are `aaaa`, `bzbg`, etc.

Answer: $26^4$

4. Compute $\displaystyle \sum_{m=2}^5 m^2$

Answer: $4+9+16+25=54$

### Linear Algebra

1. Under what conditions on $k$, $l$, $m$, and/or $n$ does it make sense to multiply a $k$-by-$l$ matrix by a $m$-by-$n$ matrix? What is the size of the resulting matrix?

Answer: $l=m$. The size is $k$-by-$n$.

2. Perform the matrix multiplication below:

$$ \begin{bmatrix} 
1 & 0 \\ 
-1 & 1 
\end{bmatrix} \times
\begin{bmatrix} 
0 & 1 \\ 
-1 & 4 
\end{bmatrix}\;=\; \ldots$$

Answer:

$$ \begin{bmatrix} 
0 & 1 \\ 
-1 & 3 
\end{bmatrix} $$

<!-- end answer -->

### Calculus

1. Compute $\int_{-1}^2 \left( x^2 + 5 \right) dx$

Answer: $3\times 5 + \int_{-1}^2 x^2  dx = 15+\frac{9}{3}=18$

2. The figure below depicts the trajectory (distance vs. time) of a moving object. Using this figure, draw a picture showing the _velocity_ vs. time; in other words, draw the derivative of the function shown below. You should label the tick marks on the $x$ axis and the location of $v=0$ on the $y$-axis, but don't worry about drawing the $y$-axis to scale otherwise.

![distance vs. time](calcQ.pdf)
\ 

Answer:

![velocity vs. time](calcA.pdf)
\ 

<!-- end answer -->
