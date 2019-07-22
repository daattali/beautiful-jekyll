---
layout: post
title: What's for Dinner? Predicting customer order probabilities
subtitle: An MDS capstone project reflection
---

<img src="../img/blog/capstone_freshprep/Logo.png" class="fit image">

One of the things that drew to me data science is its applicability to pretty much any field you can name: technology, healthcare, finance, retail, education, government, entertainment, agriculture, real estate, etc. There's no domain too large or small and no organization that would not benefit from having a data scientist (or a team of them!) on staff to solve interesting problems.

I recently completed a [Masters Degree in Data Science](https://ubc-mds.github.io/about/) at the University of British Columbia, a 10-month intensive program focused on computing, statistics, and machine learning. After 8 months of coursework, the program concludes with an 2-month industry [capstone project](https://ubc-mds.github.io/capstone/about/). My capstone team worked with Vancouver-based meal prep delivery company [Fresh Prep](https://www.freshprep.ca/?r=awfu-9uvc0) to build a predictive model for customer ordering. Fresh Prep can use our model to understand which customers are likely to order or not, and target their marketing strategies in an attempt to increase order rates.

It is one thing to take coursework in data science concepts, such as wrangling, regression, supervised learning, or feature selection & engineering. It is a far more enlightening experience to actually apply these methods to real-world data for an actual company. The capstone project allowed me to have a much more solid understanding of these techniques, how to apply and interpret them, and how to choose which tools are the right ones for the problem you want to solve.

## Some background about the project

A Fresh Prep customer has a status of either **active** or **paused.** Orders are automatically generated for all customers regardless of status; however, for paused customers these orders are also automatically skipped. Here's an example from my account, which is active:

<img src="../img/blog/capstone_freshprep/order_page_hztl2.jpg" class="fit image">

Our task was to determine which active customers skip their orders (opt-out) and which paused customers unskip (place) their orders. Answering this question provided Fresh Prep with more than just the number of orders predicted for a given week. By having greater insight into which customers are ordering rather than simply how many, the company has the ability to target those who are uncertain and see if they can increase the likelihood of these undecided customers placing an order.

## The meat and potatoes

Our work was focused in four main areas to address the project’s objective:

1. Data Wrangling
2. Exploratory Data Analysis (EDA)
3. Feature Engineering
4. Predictive Model

In parallel with wrangling the raw data into a usable dataset, we visualized it. EDA allowed us to uncover a series of insights. For example, active customers tend to plan further out than paused customers do. This is illustrated in the following plot, which shows the number of days prior to the Sunday starting a Fresh Prep week that a customer chooses to skip or place their order:

<img src="../img/blog/capstone_freshprep/figure08-cumulative.png" class="fit image">

A significant component of this project involved creating the features that were used in our model, given a rather large amount of raw data. It was necessary to determine which elements had the strongest ability in estimating a customer’s order probability. From the insights we gleaned via our EDA we built features for our model to train and predict on. After testing weights and model performance we settled on 14 features, with the most predictive ones being:

- **smoothed billed order rate:** Each customer's historical billed order rate up to a given order, smoothed with an [empirical Bayes method](http://varianceexplained.org/r/empirical_bayes_baseball/) to account for newer clients with a small number of orders in their histories.
- **weekly billed rate:** To capture seasonality, this weekly billed rate is the average rate for the corresponding week the year prior. We made an assumption that there is no trend, from last year to this year, in the billing rate.
- **lag one:** Whether or not the customer ordered 1 week prior. In our work we discovered that customers do have a tendency towards their same behavior from the previous week.
- **number of email types:** The number of different email categories a customer is subscribed to.

There is a simpler question and a more difficult question at play here. The simple question is: _**how many**_ orders will there be each week? The harder question, which is the problem we tackled, is: _**who**_ will order each week? Answering the harder question also provides a solution to the easier one.

We trained two [Logistic Regression](https://towardsdatascience.com/logistic-regression-b0af09cdb8ad) models on the data – one for active customers and one for paused. We chose this type of model because it provided more interpretable weights as well as more trustworthy probabilities than other models. This decision was key as it allowed us to explain to our partner what was driving the predictions.

The models output a probability of ordering for each customer and these are summed up to provide the expected number of orders for a given week. Our model gives predictions for one, two, or three weeks out, and thus allows Fresh Prep to plan for ingredients, delivery drivers, and other factors accordingly.

The performance of the model is visualized in the following figure:

<img src="../img/blog/capstone_freshprep/model-performance.png" class="fit image">

Our model has 4.6 mean absolute percentage error ([MAPE](https://www.dataquest.io/blog/understanding-regression-error-metrics/)) on the total number of actual orders from June 2018 to June 2019. What this translates to: for a week in which Fresh Prep expects 1000 orders, the error is around 46 orders. If we concentrate on dates only in 2019 the model has just 1.5 MAPE. These later predictions have the benefit of being trained on more data. Translation: for a week in which Fresh Prep expects 1000 orders, the error is around 15 orders.

The interactive [Tableau](https://www.tableau.com/) dashboard we developed visualizes the predictions. (All credit for building the dashboard goes to my teammate [Hayley Boyce](https://www.hayleyfboyce.com/).) Fresh Prep can utilize this in their communication strategy to their customers by seeing which customers have which probabilities of ordering.

We provided a descriptive dashboard, displaying customer histories:

<img src="../img/blog/capstone_freshprep/dash-descriptive.png" class="fit image">

And we provided a predictive dashboard, displaying future predictions:

<img src="../img/blog/capstone_freshprep/dash-predictive.png" class="fit image">

Note: the customer data presented in these images is fabricated, due to a non-disclosure agreement.

## What I learned

For me, the capstone project was the ideal opportunity to revisit many of the concepts taught in the program's coursework. Throughout the 10-week project I found myself returning to lecture notes and lab work from various courses, solidifying my knowledge of what had been learned earlier, and applying it to authentic data. The pace of the program in its first 8 months is quite intense, and in some cases I hadn't fully grasped some of the material. Capstone gave me the opportunity to return to these topics, and in a real-world applicable context, reinforce them tangibly. It demonstrated how the insights our team discovered might be used by the company. Lastly, the capstone experience made me feel on the whole much more confident in my skills as a data scientist. I found the experience to be genuinely rewarding and enjoyable.

## Acknowledgements

I want to thank my team members, [Hayley Boyce](https://www.hayleyfboyce.com/), [Orphelia Ellogne](https://ellognea.github.io/), & [Maninder Kohli](https://github.ubc.ca/mani), Joseph Goldes and Philip Nelson from Fresh Prep, as well as our faculty mentor, [Mike Gelbart](https://www.mikegelbart.com/).
