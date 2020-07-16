---
layout: post
title: MDS 2019/2020 Capstone Seminar Series
subtitle: by Tomas Beuzen
share-img: "https://github.com/UBC-MDS/UBC-MDS.github.io/blob/master/img/blog/seminar.png?raw=true"
---

During the last two months of the UBC Master of Data Science program (typically May & June each year) we have [Capstone projects](https://ubc-mds.github.io/capstone/about/), in which our students work in teams of ~4 students with an external capstone partner and a UBC mentor to address a question facing the capstone partner’s organization using data science. In 2019 we added in a weekly “capstone seminar series” where we invite data science experts from academia and industry to give a seminar on a relevant data science topic. In this blog post I'll provide a short description and some key take-aways from each of this year's seminars. The schedule for the 2020 capstone seminar series is shown in Table 1 below.

**Table 1.** *Capstone seminar series schedule.*

| Seminar | Date      | Topic                                                               | Speaker                                                                                              |
| :------ | :-------- | :------------------------------------------------------------------ | :--------------------------------------------------------------------------------------------------- |
| 1       | 15th May  | Supervised learning for time series data                            | [Tomas Beuzen](https://www.tomasbeuzen.com/) (MDS)                                                   |
| 2       | 15th May  | Bayesian hyperparameter optimization                                | [Mike Gelbart](https://www.mikegelbart.com/) (MDS)                                                   |
| 3       | 22nd May  | How to build a shinyR app                                           | [Vincenzo Coia](https://vincenzocoia.com/) (MDS)                                                     |
| 4       | 29th May  | Scalable Automatic Machine Learning with H2O AutoML                 | [Erin LeDell](https://www.linkedin.com/in/erin-ledell/) (H2O)                                        |
| 5       | 5th June  | Big Data in the Earth Sciences: Data sciences for academic research | [Simon Goring](http://www.goring.org/) (MDS)                                                         |
| 6       | 5th June  | Tableau for Data Science                                            | [Firas Moosvi](https://firas.moosvi.com/) & [Hayley Boyce](https://www.hayleyfboyce.com/) (MDS)      |
| 7       | 12th June | Navigating Cross-functional Teams and Roles                         | [Morten Rand-Hendriksen](https://mor10.com/) (LinkedIn Learning)                                     |
| 8       | 26th June | Artificial Intelligence for Wildlife Conservation                   | [Tanya Berger-Wolf](https://tdai.osu.edu/faculty/members/tanya-berger-wolf/) (Ohio State University) |

## Seminar 1: Supervised learning for time series data ([Tomas Beuzen](https://www.tomasbeuzen.com/))

If you take a look at any recent [Kaggle competition involving time series](https://www.kaggle.com/search?q=time+series+in%3Acompetitions) you'll find most winning solutions are based on supervised learning. The basic premise of time series modelling is to use observations of the past to predict the future. Classical time series models (e.g., ARIMA, exponential models, etc.) are relatively simple frameworks that leverage this concept by making predictions of a response as a weighted combination of some number of past observations. With a bit of clever wrangling, we can use the same idea with supervised learning - by creating our feature matrix *X* (rows are observatons, columns are features) in a way that encodes temporal dependence with the response vector *y*. For example, and most simply, features can be created as lagged versions of the response variable to be predicted - Table 2 shows an example of creating two features (`y-1` and `y-2`) which are lagged versions of the response `y`. This wrangled data can then be used to train a model with supervised learning.

**Table 2.** *Wrangling data for supervised learning.*

| y    | y - 1 | y - 2 |
| :--- | :---- | :---- |
| 3    | NaN   | NaN   |
| 1    | 3     | NaN   |
| 6    | 1     | 3     |
| 5    | 6     | 1     |

In this seminar, I discussed key concepts related to wrangling, modelling and forecasting time series using supervised learning. The seminar is available [here](https://github.com/TomasBeuzen/machine-learning-tutorials/blob/master/ml-timeseries/notebooks/supervised_time_series_intro.ipynb) as a Jupyter notebook.

## Seminar 2: Bayesian hyperparameter optimization ([Mike Gelbart](https://www.mikegelbart.com/))

Hyperparameter optimization (HPO) is a key element of the machine learning pipeline. Mike nicely summarized some of the main problems with HPO:

- There may be many hyperparameters to optimize;
- Nobody knows how to choose them (typically only heuristcs are available);
- Hyperparameters may interact with each other in unexpected ways;
- The best hyperparameter settings depend on the specific data/problem at hand;
- Evaluating hyperparameter settings takes (a long) time.

If you're at all familiar with machine learning and HPO, you've probably heard of the grid search or random search strategies. In a grid search, you simply train and evaluate a model on all possible combinations of hyperparameters you wish to explore. The number of models required to be trained in this kind of brute-force strategy increases exponentially with the number of hyperparameters and settings. A popular alternative, randomized search, offers more control on the number of models explored, and also avoids the need for a pre-defined grid of values for continuous hyperparameters. However, neither of these methods is really "optimization" in the sense of using an iterative procedure to improve results. Imagine if, during HPO, we could identify that particular hyperparameter setting(s) were not having any meaningful impact on our model, then we could spend less time on them and focus our attention on other more important hyperparameters. This is pretty much what Bayesian HPO does! As Mike discussed in this seminar, Bayesian HPO uses machine learning to predict what hyperparameters will be useful to optimize - it's machine learning within machine learning! If you're interested in learning more about Bayesian HPO, the Python package [scikit-optimize](https://scikit-optimize.github.io/stable/) offers functionality for doing [Bayesian HPO](https://scikit-optimize.github.io/stable/modules/generated/skopt.BayesSearchCV.html) with a familiar `scikit-learn` interface.

## Seminar 3: How to build a shinyR app ([Vincenzo Coia](https://vincenzocoia.com/))

The ability to build interactive web apps is a key tool in a data scientists toolbox. Interactive web apps can be incredibly useful for conveying large amounts of information in an efficient and aesthetic framework. [Shiny](https://shiny.rstudio.com/) is an R package for making web apps directly from R - no web development skills are required! In this seminar Vincenzo walked through a demonstration of building a web app with Shiny showing that even a beginner can get a simple web app up and running in less than an hour. I recommend taking a look at the [Shiny gallery](https://shiny.rstudio.com/gallery/) to see what's possible with Shiny. Prefer Python? In MDS we teach [Dash](https://plotly.com/dash/) as an analagous framework for building web apps with Python (or R).

## Seminar 4: Scalable Automatic Machine Learning with H2O AutoML ([Erin LeDell](https://www.linkedin.com/in/erin-ledell/))

Automatic Machine Learning ("AutoML") refers to the automation of applying machine learning to real-world problems and data. This automation can include feature engineering, model selection, hyperparameter optimization and model interpretability. In this seminar, Erin LeDell from [H2O](https://www.h2o.ai/) provided a brief overview of the field of AutoML, followed by a detailed look inside H2O's AutoML algorithm. H2O is an open source, distributed machine learning platform designed to scale to very large datasets that may not fit into RAM on a single machine. H2O AutoML provides an easy-to-use interface which automates data pre-processing, training and tuning a large selection of candidate models (including multiple stacked ensemble models for superior model performance). The result of the AutoML run is a "leaderboard" of H2O models which can be easily exported for use in production.

H2O's vision is "...to democratize AI for everyone" (that quote from the [H2O](https://www.h2o.ai/) website). Perhaps unsurprisingly, given this mission, many MDS students were interested in the question, "Will AutoML replace the need for data scientists in the future?". This question was answered by Erin with a resounding "No" and I would have to agree - tools like AutoML are just that, tools. While a more comprehensive discussion of that question and answer is better saved for a future blog post, I will briefly say that, to me, a data scientist's job is to responsibly and accurately extract, interpret and disseminate information from data. Products like AutoML are a tool to support this mission, not replace it (at least not yet...).

## Seminar 5: Big Data in the Earth Sciences ([Simon Goring](http://www.goring.org/))

When working in cross-disciplinary fields there is often no standardised format or storage for data and databases, which makes it incredibly difficult to manage, catalogue and leverage all of this potentially useful data. The Earth sciences are one example of a highly cross-disciplinary field - think geologists, ecologists, climate scientists, seismologists, paleontologists, etc. - all of whom may be collecting and storing data in different ways, despite this data being cross-disciplinary and useful across the range of Earth science disciplines. In this seminar, Simon discussed the challenges of working with databases in the highly cross-displinary Earth sciences and describes tools such as [GeoDeepDive](https://geodeepdive.org/) and [Neotoma](https://www.neotomadb.org/) that are being developed and utilised to automatically catalogue data from across the Earth sciences and accumulate it into a standardised, useable and functional format.

An interesting side-product of this talk was a discussion on whether it is better to be a data scientist first before moving into another discipline (e.g., Earth sciences), or to be, for example, an Earth scientist first who then learns data science. As a coastal engineer turned data scientist I've often asked myself the same question - and obviously there's no clear answer to this question. What is clear however, is that great things come from the intersection of fields such as data science and Earth science - onwards and upwards!

## Seminar 6: Tableau for Data Science ([Firas Moosvi](https://firas.moosvi.com/) & [Hayley Boyce](https://www.hayleyfboyce.com/))

[Tableau](https://www.tableau.com/) is a popular visualization software used in industry to create static and dynamic plots/dashboards that can easily be shared within and across organizations. While we do not teach Tableau in MDS due to our preference for free, open-source tools, our students can apply their visualisation and dashboarding experience to Tableau, which is built around its own language and syntax. In this seminar, Firas and Hayley provided an overview of Tableau and built a simple dashboard using open data about the City of Vancouver - they also showed how it's possible to integrate programming languages we do teach in MDS, such as Python, into the Tableau pipeline. Their tutorial is available [here](https://github.com/firasm/mds_tableau_workshop).

## Seminar 7: Navigating Cross-functional Teams and Roles ([Morten Rand-Hendriksen](https://mor10.com/))

Data scientists often find themselves working in cross-functional teams and dealing with various other contributors with a wide range of goals and interests. Knowing what these teams and roles are, what they care about and focus on, knowing their language, strengths, weaknesses, and what they perceive as threats is key to successfully working with others. Morten's capstone seminar series talk focused on these concepts and provided a rundown of some of the key roles data scientists work with in academia and industry and how to fit in while claiming your space.

Notably in this time of COVID-19 where we are all working remotely, Morten (who has been working remotely for the better part of 10 years) provided valuable insights in how to work effectively with remote teams. One piece of advice that stuck with me was that when working remotely, it helps to actively make an effort to engage with your team in social activites and catch-ups - this kind of effort and support goes a long way to fostering friendly and effective relationships within your team and helps keep you up to date with what your colleagues are working on.

## Seminar 8: Artificial Intelligence for Wildlife Conservation ([Tanya Berger-Wolf](https://tdai.osu.edu/faculty/members/tanya-berger-wolf/))

Photographs, taken by field scientists, tourists, automated cameras, and incidental photographers, are one of the most abundant sources of data on wildlife today. In this talk, Tanya showed how data science and machine learning methods can be used to turn massive collections of images into a high resolution information database to be used for scientific inquiry, wildlife conservation efforts, and policy decisions. Tanya showed her team's work on using computational data science methods to collect images from online social media, detect various species of animals and even identify individual animals. The result of Tanya's (and her collaborators) work is [Wildbook](https://www.wildbook.org/), a tech project for the conservation non-profit [Wild Me](https://www.wildme.org/). The work Tanya and her team are doing is simply amazing and really makes you, as a data scientist, feel like you can change the world! I encourage you to take a look at some Wildbook projects such as <flukebook.org> (whales and dolphins), <whaleshark.org> (whale sharks), and <giraffespotter.org> (giraffes) - this is becoming the data foundation for wildlife science, conservation, and policy and has even been featured in [National Geographic](https://www.nationalgeographic.com/animals/2018/11/artificial-intelligence-counts-wild-animals/).

## Fin

I'll round out this blog post by saying a big congratulations to the MDS 2019/2020 cohort. We had a phenomenal and talented group of students in MDS this year and it was an absolute pleasure to work with them all. Special mention must be made to the way students (and instructors) were able to adapt to remote learning during COVID-19 - it was a wild ride but I like to think that we are all stronger and closer because of it.

--------

## Authors:
[Tomas Beuzen](https://www.tomasbeuzen.com/) is a Postdoctoral Teaching and Learning Fellow of the MDS Vancouver program.

## Acknowledgements: 
I would like to acknowledge this year's capstone coordinator Tiffany Timbers, all the other MDS core teaching team members (current and past) and founders, and our capstone industry partners who have all helped shape the MDS program and the capstone experience.
