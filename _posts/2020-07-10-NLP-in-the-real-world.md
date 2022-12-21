---
layout: post
title: "NLP in the Real World: A Reflection on a Two-Month Capstone"
subtitle: by Serena Huang
share-img: "https://miro.medium.com/max/1400/1*t_l9RMNgrG7wafwiUMOSTw.png"
---

Recently, my team and I wrapped up our two-month long capstone project with [Unbounce](https://unbounce.com/). 
The completion of the capstone marks the end of my [Master of Data Science — Computational Linguistics program](https://masterdatascience.ubc.ca/programs/computational-linguistics) (MDS-CL) at the University of British Columbia, as well as the transition from being a student, the encapsulation of my identity for the past seventeen years, to being a new graduate, a new identity that still takes a little getting used to. 
In between job hunting and trying to maintain a semblance of a normal life in the midst of a global pandemic, I'd like to reflect on these past two months and the lessons that I've gained.

After eight months of intense coursework, the capstone was our chance to apply our newly-learned data science and computational linguistics skills to a real-world problem provided by an external partner. 
My team, consisting of Zoe Xu, [Chidera Okoma](https://www.linkedin.com/in/chidera-okoma/), [Varun Tulasi](https://www.linkedin.com/in/varuntulasi/), and I, along with our UBC faculty advisor, [Miikka Silfverberg](https://mpsilfve.github.io/), were paired with Unbounce, a landing page builder. Our task was to use natural language processing (NLP) techniques on the three years' of customer feedback data that they had previously categorized manually. 
By automating this categorization process using topic modelling and unsupervised machine learning techniques, our capstone project aimed to extract actionable insights from the data while saving the company time and employee energy. 
Along the way, my team celebrated our successes, tackled our challenges, and gained some valuable insight for our next data science or computational linguistics project.

### The Highlights

For our first NLP project in a real-world setting, there were plenty of successes to celebrate. 
As the MDS-CL program included only one course on unsupervised machine learning, our capstone project provided the opportunity to further our knowledge in this area. 
Both our UBC faculty advisor and the Unbounce team who worked with us were valuable sources of expertise, exposing us to [DBSCAN clustering](https://en.wikipedia.org/wiki/DBSCAN) and dimensionality reduction through [UMAP](https://umap-learn.readthedocs.io/en/latest/), among other techniques. 
We held regular meetings three times a week to share progress updates and receive feedback, and listened to different perspectives and ideas.

In addition to technical skills, we learned to work within a real business context. 
We were no longer analyzing data and building models for a course grade — our final product would be used by stakeholders in the company. 
With this in mind, we discussed how to cater our results to both technical and non-technical audiences, and how to present our insights such that they could be immediately understood and acted upon. 
We learned to ask ourselves: These are interesting results, but what narrative do they convey? What are the next steps that the business should take when presented with these results?

At the end of our two months, we were to present our capstone project to an audience of around thirty Unbounce employees. 
My team and I gathered on campus to practice our presentation, which we delivered as a video recording over Zoom a week later. 
Employees from a variety of teams, from Product to Data, gathered virtually to watch our presentation and to ask us questions. I was relieved and excited by how much interest and enthusiasm they showed. 
A few of them declared that they couldn't wait to start digging into our results, and later our Unbounce partners assured us that our presentation had been very well-received.

### The Tricky Parts

The capstone project included its fair share of challenges, however. 
A major one had swept across the world months before we even began our capstone project: we were in the middle of a global pandemic, which meant that the weekly meetings that we were supposed to have in Unbounce's downtown office, and the campus classrooms that we were planning to work in, were no longer options. 
Instead, we found ourselves in front of our laptops for Zoom calls, asking, "Can you hear me? Can you see my screen?" 
We had not initially prepared to work remotely, and we had to quickly adapt to this new normal.

Our dataset presented unexpected challenges as well. 
There were fewer pieces of feedback than we had expected, especially since we were using NLP techniques that rely on large amounts of data. 
Diving into the dataset revealed a surprising amount of noise: I hadn't realized that some of this feedback consisted solely of emoticons or strings of random letters. 
After filtering out the noisy feedback, we had removed almost 20% of our original dataset.

Evaluating our model was another major challenge. 
How could we assess the results produced by our model? Since we couldn't rely on numerical scores, we reverted to manual evaluation, examining our results and discussing as a group. We met with stakeholders and asked them the same question: Do these results make sense? Gradually, we tuned our model and improved our results until we could comfortably say, _Yes, these results make sense._

### Some Final Thoughts

At the end of the two months, we asked ourselves, What could we do better next time? 
There were some practical suggestions: An improved structure and organization to our project. 
More frequent communication with various stakeholders. 
More synchronous working sessions so that we could bounce ideas off of each other and provide ongoing feedback. Not dealing with a pandemic would have helped, too.

A week ago, leaving campus with one of my teammates after another day of presentation practice, I asked her, "What do you think has been your biggest takeaway from this capstone project?" She answered, "When you study these topics in class, they all seem so abstract. 
But we got to use them in a real setting. We got real results. And now our knowledge doesn't seem so abstract anymore."

Two months, four MDS-CL students, and one end-to-end product which transforms raw data into actionable insights. 
I couldn't have asked for a better capstone project to finish off this degree.

---------

[Serena Huang](https://www.linkedin.com/in/serenashuang/) graduated from the MDS - Computational Linguistics program in 2020.

This blog post also appears on medium.com [here](https://medium.com/@serena.hng/nlp-in-the-real-world-a-reflection-on-a-two-month-capstone-c5617ea15a6e).
