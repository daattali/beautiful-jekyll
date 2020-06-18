---
title: "Is UFC Judging Fair?"
author: "Sam Edwardes"
categories: ["data-science"]
tags: ["sports"]
date: "2020-05-31"
type: "post"
---

When a UFC match ends with a knock-out or submission there is never any
doubt who the better fighter was. But only 54% of fights end with a
knock-out or submission. The other 45% of fights go to the judges score
cards.

![](https://i.imgur.com/h66XXPU.png)

Given that the outcome of so many fights are determined by the judges
their ability to fairly score a fight is an important part of the sport.
One win or loss can make or break a fighter’s career. But judging is
tricky business. It is frequently the subject of public scrutiny:

  - [The Bleacher Report’s 10 Most Controversial Judging Decisions in
    UFC History
    (2014)](https://bleacherreport.com/articles/2072171-the-10-most-controversial-judging-decisions-in-ufc-history#slide0)
  - [UFC commentator Joe Rogan on the issues with
    judging](https://www.youtube.com/watch?v=U8ZO5k5Gykk)

How can we assess if judging in the UFC is fair? Are the judges really
selecting the better performing fighter? Are they correctly applying the
UFC rules to select the winner?

### Assessing fairness

To answer this question we must first understand what the rules are. How
are the judges supposed to pick a winner? Then we can use statistical
tools to compare what the judges are actually scoring compared to what
they should be scoring.

#### What are the rules?

The system is confusing, but here are the basics. Judges score each
round on a “*10-Point Must System*”. The [official MMA
rules](http://www.abcboxing.com/wp-content/uploads/2016/08/juding_criteriascoring_rev0816.pdf)
describe scoring as follows:

>   - “*A 10 –10 round in MMA is when both fighters have competed for
>     whatever duration of time in the round and there is no difference
>     or advantage between either fighter.*”
>   - “*A 10 –9 Round in MMA is when one combatant wins the round by a
>     close margin.*”
>   - "“*A 10 –8 Round in MMA is when one fighter wins the round by a
>     large margin.*”

The official rules also provide additional guidance on what constitutes
winning:

> “*Effective Striking/Grappling shall be considered the first priority
> of round assessments. Effective Aggressiveness is a ‘Plan B’ and
> should not be considered unless the judge does not see ANY advantage
> in the Effective Striking/Grappling realm. Cage/Ring Control (‘Plan
> C’) should only be needed when ALL other criteria are 100% even for
> both competitors. This will be an extremely rare occurrence.*”

#### What are the judges scoring?

We can never know what was going on in a judges head. But by using the
data from every UFC fight, we can identify which features are strongly
correlated with winning or losing.

Logistic regression will be used to model the data. Logistic regression
will assign a weight to each feature, with larger weights signalling
greater importance. My hypothesis is that if the judging is fair, the
weights assigned by logistic regression should be aligned with what the
judges are supposed to score.

For example, based on my reading of the rules *effective striking*
should be very important criteria for a judge in selecting the winner.
Although there is no perfect way to report effective striking as a
single number, the number of strikes landed is probably a good proxy.

The data collected has several features including:

  - `Stirkes` - The number of strikes landed
  - `Take-downs` - The number of successful take-downs
  - `Submissions` - The number of submissions attempted
  - `Pass` - The number of of guard passes

Below is an example of the data:

| fighter\_1\_name | fighter\_2\_name | fighter\_1\_str | fighter\_2\_str | fighter\_1\_td | fighter\_2\_td | fighter\_1\_sub | fighter\_2\_sub | fighter\_1\_pass | fighter\_2\_pass | winner     |
| :--------------- | :--------------- | --------------: | --------------: | -------------: | -------------: | --------------: | --------------: | ---------------: | ---------------: | :--------- |
| Alistair Overeem | Walt Harris      |              68 |              25 |              1 |              0 |               0 |               0 |                3 |                0 | fighter\_1 |
| Claudia Gadelha  | Angela Hill      |              84 |              90 |              1 |              0 |               0 |               0 |                1 |                0 | fighter\_1 |
| Dan Ige          | Edson Barboza    |              79 |              80 |              1 |              0 |               0 |               0 |                0 |                0 | fighter\_1 |
| Krzysztof Jotko  | Eryk Anders      |              66 |              41 |              0 |              0 |               0 |               0 |                0 |                0 | fighter\_1 |
| Song Yadong      | Marlon Vera      |             101 |              92 |              0 |              2 |               0 |               0 |                0 |                1 | fighter\_1 |
| Miguel Baeza     | Matt Brown       |              37 |              33 |              0 |              0 |               0 |               0 |                1 |                0 | fighter\_1 |

#### Assessing Fairness Visually

If the model is to work, we would expect to see that more strikes,
take-downs, submissions, and passes is correlated with winning. For each
feature, we can plot the relationship to visually compare.

The box plots show the median (the purple line), and the 25th and 75th
percentile (the left and right hand side of the box). Each dot
represents the outcome of a fight for each fighter.

![](https://i.imgur.com/4SM3Wib.png)<!-- -->

For striking, take downs, and passes it appears that at least visually
the better performing fighter usually wins. The relationship between
submissions and winning is not as clear.

#### Assessing Fairness with Logistic Regression

##### Using fighter performance features

To better understand the relationship between a fighters performance and
the judges decision we can fit a logistic regression model to the data.
The model will tell us which features in the data are the strongest
predictor of the outcome. In this case, we have set the outcome to
whether the blue fighter wins or losses. The first model will only use
the features that the judges should consider: striking, take-downs,
passes, and submissions.

| term       | estimate | p.value |
| :--------- | -------: | ------: |
| blue\_str  |     2.28 |    0.00 |
| red\_str   |   \-2.31 |    0.00 |
| blue\_td   |     0.60 |    0.00 |
| red\_td    |   \-0.34 |    0.00 |
| blue\_sub  |     0.05 |    0.52 |
| red\_sub   |     0.00 |    0.96 |
| blue\_pass |     0.62 |    0.00 |
| red\_pass  |   \-0.68 |    0.00 |

The table above is the output of the logistic regression model. The
estimate (also known as the coefficient) tells us the effect each
feature has on the odds of winning. For example, for each additional 1
standard deviation increase in the number of strikes landed by blue,
they increase their **log odds** of winning by 2.28. Another way to
interpret the coefficient is that for each additional 1 standard
deviation increase in the number of strikes landed by blue, they
increase their **odds** of winning by 877.67% (*(e^2.28 - 1) x 100*).
The p-value tells us whether or not each coefficient is statistically
significant (smaller p-values mean the model is more confident the
relationship is not due to chance).

The table above can help us finally answer the question “is UFC judging
fair?”. The results of the logistic regression reveal that:

  - As you might expect, the **most important feature is striking**. The
    more strikes you can land, the more likely you are to win over your
    opponent. Conversely, the more you get hit, the more likely you are
    to lose.
  - The next most important feature associated with winning are
    **passes**, and then **take-downs**.
  - **Submissions** were identified as not being statistically
    significant at significance level of 0.05.

We can think of the results of the logistic regression as a proxy for
what judges actually care about. Further we can test the model to see
how well it generalizes to the actual data.

When I fit the model above I used a random sample of 80% of the fights.
We can test how well the model generalizes to the remaining 20% of the
data by generating predictions. A high prediction accuracy would suggest
fair judging. Or at least judging that is applied consistently.

On the training data, the model accurately predicts the correct winner
83.47% of the time. On the test data the model accurately predicts the
correct winner 85.32% of the time.

##### Using other features

The model that was fit above used only features that the judges should
use to make their decision. What will happen to the model if we add data
that the judges should not be considering, but could influence their
decision? For example will a fighter being taller bias the judges to
reward them based on their appearance?

To test this theory we can fit the same model as before, but this time
add three additional features: weight, height, and reach. If the judges
are being fair, theses features should not effect the outcome of the
fight.

| term                 | estimate | p.value |
| :------------------- | -------: | ------: |
| blue\_str            |     2.23 |    0.00 |
| red\_str             |   \-2.21 |    0.00 |
| blue\_td             |     0.60 |    0.00 |
| red\_td              |   \-0.32 |    0.00 |
| blue\_sub            |     0.04 |    0.63 |
| red\_sub             |   \-0.03 |    0.75 |
| blue\_pass           |     0.69 |    0.00 |
| red\_pass            |   \-0.66 |    0.00 |
| blue\_height\_inches |   \-0.02 |    0.70 |
| red\_height\_inches  |     0.01 |    0.85 |
| blue\_weight\_lbs    |     0.00 |    0.99 |
| red\_weight\_lbs     |   \-0.01 |    0.48 |
| blue\_reach\_inches  |     0.02 |    0.65 |
| red\_reach\_inches   |     0.03 |    0.50 |

Interestingly, the three “unfair” features are all considered the least
important. They have a small coefficient, and a high p-value suggesting
that these variables are not good predictors. This can give us some
comfort that the judges are actually only considering fighter
performance.

## Conclusion

So is the UFC fair?

  - Judges do reward striking, passes.
  - Judges do not reward submission attempts.
  - Judges do not reward height, reach, or weight.
  - 85.32% of the times the judges are applying the rules consistently.

The analysis above is an attempt to answer the question, but I think the
results are far from conclusive:

  - Does rewarding striking, passes, and take-downs in that order align
    with judging rules?
  - Is 85.32% consistency good enough?
  - Are there other confounding variables that judges are considering
    that are not present in the model (fighter reputation, audience
    reaction, etc.)?

Personally, I think this analysis provides comfort that the judges are
doing an OK job. If you land more strikes, you will probably win. If you
earn more take-downs, and do a better job of passing guard you will
probably win.

But I do not know if 85.32% consistency is good enough. Is it poor
judging, or something that cannot be observed in the data we have?
Hopefully further analysis and the collection of additional data can
help better answer this question.

-----

### Reference

  - You can find the complete code behind the analysis here:
    <https://github.com/SamEdwardes/ufc-fairness/blob/master/blog/is_the_ufc_fair.Rmd>.
  - The data used can be found here:
    <https://github.com/SamEdwardes/ufc-data>.
