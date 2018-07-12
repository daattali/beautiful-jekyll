# Learning From Real Data
##### Six lessons I have learned from my first "real" project as a data scientist.

Originally, I wanted to call this blog post "More Data, More Problems". Clearly, this hip-hop reference would have been a cool start for my first blog post - but then again as a data scientist, I probably should not complain about having *too much* available data. So jokes aside. For the past three months, I have been part of a team of students of UBC's [Master of Data Science](https://ubc-mds.github.io/) that developed a data science product to help the course-creators of the e-learning platform [Thinkific](thinkific.com) to improve their online courses. Unsurprisingly, working on the improvement of online learning was a great learning experience for ourselves. Therefore, to share some of my experiences, and as a reminder to my future self, I will summarize the six most important lessons I learned in my past three months in this post. But first - to give some context - I'll quickly describe the client and the project.

### The Project

Thinkific is a web platform that gives anyone the opportunity to create online courses and sell their knowledge to an audience. In our project, we created a Python package that gives smart "data-driven" advice to course-creators based on the current features of the course. In this context, the target variable was "student-success". Our package's recommendations should boost student success and have a positive impact on Thinkfic's customers by attracting more students. Thinkific would also benefit from increased satisfaction among its course-creators. The below image that describes Thinkfic's business model:

![business model](../img/blog/business_model.JPG)

To approach the described problem, we created a Python package which conceptually works as follows:

Using the percentage of content-completion as our measure of student-success, we predicted this target variable using [sklearn's Gradient Boosting Regressor](http://scikit-learn.org/stable/modules/generated/sklearn.ensemble.GradientBoostingRegressor.html) with around 50 features that describe the "current state" of a course. Next, we predicted student success *given an incremental increase in one of the features*. By iterating over all the possible feature changes and calculating their respective predicted success score we identified the most successful strategy for each course. Finally, given a "course_id" our package returns the action with the highest increase in predicted student success.

Here's an image of a sample output of our package:

![recommendations_co](../img/blog/recommendations_co.JPG)


**Note:** The above concept is simplified for reasons of comprehensibility.

### Lessons Learned

Now that the setting is clear, here comes my list of advice to my future self.


1. Communicate with your team!

Make sure everyone is on the same page - ideally on a daily basis. Both, the distribution of daily tasks as well as the understanding of conceptual ideas related to the project should be discussed among the team members frequently. This way, the team is more productive when working towards the common goal while making a good impression towards the client in meetings. Although we generally did an excellent job at this, there were a few misunderstandings that became clear in meetings with the client. This could have been prevented by better communication.

2. Listen to the client and domain experts.

Frequently meet with the project's stakeholders and adjust your plans according to their feedback, especially in the early stages of the project. From our experience in the past months, more feedback is always better. For example, after presenting the conceptual framework of our project one of Thinkific's employees mentioned that our measure of student success might be biased towards early chapters in a course (rating early chapters as more successful). This was something we had overlooked until this point and could be fixed with a slight adjustment.   

3. Know the Database

Get an overview of the database and where things can be found - whether they are directly related to the project or not. At the very beginning of our project, Maud, one of our team members, spent two days creating a database schema. Throughout the project, her knowledge was extremely useful to the team and at times, I wished I had spent two days scanning the database myself.

4. Wrangle Data in SQL.

Do as much data wrangling as possible in SQL to decrease processing times and use of storage memory. We initially did a lot of the data wrangling in Python. This turned out to be very time-consuming and  would sometimes fail because the imported data was too big. Later, we included as many data wrangling tasks as possible into the SQL queries that extracted the data from the database significantly reducing the runtime of our scripts.

5. Keep an open mind.

If your initial plan does not work out don't panic - stay creative and flexible and adjust to changes. Throughout the course of our project, we had several moments in which our conceptual framework seemed to fail. For example, we had initially planned to follow a linear regression approach due to the easy interpretability of weights as feature-importance. However, the validation-accuracy when trying to predict student-success was disappointing. At the same time, we noticed that non-linear machine learning approaches such as a "Random Forest Regressor" and "Gradient Boosting Regressor" performed significantly better. Therefore to make use of the better accuracy and create interpretability, we decided to use "Gradient Boosting Regressor" and implement the conceptual framework described at the beginning of this post - a solution based on a lot of assumptions, but an actionable solution.


6. Be aware of the assumptions and communicate them.

Any model is based on assumptions - make sure that the client is aware of them. Generally, it is dangerous if the end-user of a data science product has no intuition as to how the results are produced. In our model, one fundamental assumption is that the current features of a course determine the current level of student success. This is a strong assumption. Consider a successful course-creator who has never used any video content for her courses. Now, this course-creator has added lengthy videos to her course one day before our model is trained. Clearly, our model will attribute the course's success partly to the new video-content and will falsely be more inclined to recommend adding long videos to this, and other course-creators. However, we assume that this type of error is rare and overall insignificant. To prevent misunderstandings and false expectations, it is important that the user of the model is aware of existing assumptions and knows the type of biases that may exist in a model.


Surely, there are many more lessons that we have learned throughout this project and this list is 100% subjective. What is your advice to aspiring data scientist working on their first projects - I would love to hear from you! You can find me on Twitter as @akleefel.

Finally, a big THANK YOU to my team members Esteban Angel (@esetebanangelm91), Maud Boucherit, and Prash Medirattaa (@prashm16) for an exciting time together as well as Thinkific for being such an amazing host.
