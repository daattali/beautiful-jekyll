---
layout: post
title: "Communication in data science: more than just the final report"
subtitle: by David Laing
---

When people stress the importance of good communication in data science, they are usually saying something like what Hadley Wickham says in his book [R for Data Science](http://r4ds.had.co.nz/communicate-intro.html): "[It] doesn’t matter how great your analysis is unless you can explain it to others: you need to communicate your results." In other words, good communication is crucial to data science because it is the final step, without which all prior work would be wasted.

But communication is even more important than that. If you fail to communicate well with your client at the beginning of a project, you may waste your efforts answering the wrong question. If you fail to communicate well with your team, you may create inefficiencies in your workflow. And if you fail to communicate well with your future self, through careful documentation and clean code, you may find yourself circling back to redo old work. Communication is of course important at the end of the project too, but it's more than just a final bottleneck; it's important at every stage.

I had in mind this view of communication in data science when I designed DSCI 542: Communication & Argumentation, a four-week course that students take in their first month of the [UBC Master of Data Science](https://masterdatascience.science.ubc.ca/) (MDS) program. My goal was to prepare students for the wide variety of communication-related challenges they will face as data scientists. This was hard because these challenges vary in so many ways – by medium, by audience, by purpose. One day you're explaining a new algorithm to your manager; another day you're messaging a co-worker over Slack to try to fix a bug; another day you're presenting the results of your analysis to a room full of decision-makers. So, rather than trying to prescribe specific strategies for communicating well in every conceivable scenario, I aimed to help the students discover a few key principles that apply across all data science communication.

The most important of these principles is a consequence of what psychologists call the [curse of knowledge](https://en.wikipedia.org/wiki/Curse_of_knowledge): the fact that when you know something, it is nearly impossible to imagine what it is like not to know it. In a classic experiment, subjects are privately told the title of a popular song, and asked to clap (but not sing or hum) its chorus. They then predict whether another person in the room, who wasn’t told the title of the song, would be able to guess it. Time and again, the people who clap the song overestimate other people's ability to guess it. The clapper can hear the music in their head; the listener can hear only a disconnected, rhythmic skeleton.

Because of the curse of knowledge, a communicator's first instinct is often to provide their audience with precise but abstract details about the subject at hand. The communicator queries their own mind for the phrase, "confidence interval", and they come up with something like, "an interval estimate of a parameter of a statistical model." This is fine if the audience already knows what a confidence interval is, but it's gibberish if they don’t. Herein lies the biggest challenge in communication. It’s not enough to simply understand a subject and be able to produce true sentences about it. A skilled communicator must be able to craft each part of their message in anticipation of the audience’s state of mind.

So, what is the principle here? "Know about the curse of knowledge, and don't let it get you"? Unfortunately, naming the problem is not the same as solving it. In our class this year, the best solution that the students and I discovered was to explain concepts from the bottom up rather than from the top down. Let me show you two examples to illustrate what I mean. Here is a top-down explanation of the difference between statistics and probability:

> Statistical inference aims to characterize data-generating processes, usually based on samples of observations. In contrast, probabilistic inference aims to determine how likely it is that an event will occur. While statistical inference works backward from data to say something about the conditions that produced it, probabilistic inference works forward from a supposed set of conditions to predict which data will be produced next.

A top-down explanation provides information that is mentally proximate to the concept. The information is general and abstract – a Platonic approach.

In contrast, here is a bottom-up explanation:

> Suppose I have a bag that contains 1000 balls, and each ball is either blue or red. If I know the proportion of balls that are red, then I can compute the probability that a randomly selected ball will turn out to be red. But if I don't know the proportion of red balls, I will have to estimate it through repeated samples, using statistics. Probabilistic inference uses my assumptions to predict my observations; statistical inference uses my observations to refine my assumptions.

A bottom-up explanation starts with examples, allowing the abstraction and generality to emerge out of concreteness and specificity.

There are tradeoffs between these approaches, of course. Top-down explanations are useful within intellectual communities because they make it easier to build on prior abstractions. But data science is so interdisciplinary, and has so much contact with people outside the field, that bottom-up explanations are almost always best. 

The students put this insight to use by writing blog posts to explain technical data science concepts. Here are two examples of what they came up with:

* [What is a Website Address?](https://danielraff.com/data_science/What-is-a-website-address.html), by Daniel Raff
* [The Travelling Sales Person Problem](http://indiedata.io/02-04-2018/the-traveling-salesperson-problem/), by Indiana Nikel

Throughout the four weeks of the course, we examined other communication-related challenges that frequently occur across data science work:

* how to be an effective consumer of data science communication
* how to apply principles of narrative, and how to reason about its risks
* how spot the advantages and disadvantages of a given medium of communication, such as prose, speech, code, or mathematical notation
* how to connect the statistical language of variables and values to the practical concerns of decision-makers
* how to connect the quantified form of uncertainty that results from statistical modelling to the subjective form of uncertainty that people experience in everyday life

It was a privilege to teach this course. The students approached the lessons and assignments with enthusiasm and insight, and I am proud of what they achieved. I hope that they will begin their data science careers with not just the ability to share the results of their analyses, but with the ability to approach all data science communication with sound strategies and a good understanding of the principles at play.


---------

[David Laing](https://davidklaing.github.io/) graduated from the [UBC MDS program](https://masterdatascience.science.ubc.ca/) in 2017 and is currently a Data Scientist at the [Centre for Teaching, Learning and Technology](https://ctlt.ubc.ca) at UBC.
