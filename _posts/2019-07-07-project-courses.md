---
layout: post
title: Teaching Data Science using project-based courses in the UBC Master of Data Science program
---

## Introduction

Data Science is the act of extracting value from data through reproducible and auditable processes. This definition is intentionally broad such that it may encompasses all the different things Data Scientists do to gain insights and knowledge from data, and the things that need to be done can be very different depending on the application of knowledge or insights needed to be garnered from the data. How can we teach aspiring Data Scientists "what things need to be done" to answer their particular data question? Typical lecture and lab based courses are one way to give prescribed and well-defined examples, and at the beginning of a Data Science education these are very necessary. However, only ever being exposed to prescribed and well-defined problem sets hardly prepares the aspiring data scientist for real world data science work in either industry or the research lab, where projects are more like snowflakes than cookies (Figure 1). Project-based courses where data is messy, the task is not perfectly defined and people are required to collaborate and work together to extract value from the data is a more real-world-like setting where students have the opportunity to have both successes and failures across many more axes of Data Science than are typically available in a focused lecture/lab-based course. The student's learning experiences in these courses are rich and memorable, making this a key part of any wholistic Data Science curriculum.

The project-based Data Science courses that will be used as tangible data points for the discussion herein exist as part of the University of British Columbia (UBC)'s Master of Data Science (MDS) program. This program is an intensive 10-month-long program whose vision is to teach the creative, responsible, and reproducible practice of Data Science. The program consists of 8 months of 24 short, 1-credit courses (4 taken concurrently in 4 weeks blocks) and a two-month-long capstone project. A more detailed description of the program can be found [here](https://ubc-mds.github.io/about/), and background information on its design and history [here](https://ubc-mds.github.io/2019-02-19-designing-mds/).

In the first year of the MDS program the only project-based course that was offered was the two-month-long capstone project at the end of the program ([course description](https://ubc-mds.github.io/capstone/about/) and [public version of the course](https://github.com/UBC-MDS/DSCI_591_capstone-proj)), all other courses used a standard format which consisted of: eight 90 minute lectures,  four two hour labs (each with an assignments worth 12.5% of the students’ grade) and two quizzes (each worth 25% of the students’ grade). This standard format worked very well for many courses, particularly for the introductory courses and the courses deeply focused on a particular area of statistics, machine learning or computer programming. However, this format did not fare well with courses that required more writing, critical thinking and integration of knowledge from other (previously taken) Data Science courses.

Specifically, using student feedback (from the MDS interim and year-end surveys, student block-representative reports and informal discussions with Alumni) we identified that at least 4 courses would benefit from an alternative format and be suitable as project-based courses. In addition to improving these four courses individually, these changes also meant that our students would be able to gain experience in a project-based setting four times before embarking on their final capstone project. Thus for the last two years we have run these 4 project-based courses (in addition to the capstone project) and have iteratively refined what, for us, constitutes a successful project course in Data Science. For the remainder of this article we will share what our project-based courses look like (both the short one credit, as well as the final capstone project) and discuss challenges that we faced in making these courses successful as well as discuss what solutions we have arrived at to solve some of these challenges.

## Project-based course design & logistics

The one-credit project-based courses in the MDS program all follow the same general operational and pedagogical structure. Similar to the standard format the course still have eight 90 minute lectures, however the four two hour labs are not divided into separable lab assessments. Instead they are utilized for students to be able to work on the project proposal and milestones - each building on the previous, responding to feedback received from the instructional team (and peers, see the next point). In particular in the third lab, students work through a face-to-face peer review session, after which they provide their constructive feedback to other groups by opening GitHub issues in the other groups GitHub repositories.

All project-based courses are group projects in MDS of 3-4 students, where we students are randomly assigned to a different group for each course. For the project topic, students are given free reign to choose a project topic that fits within the constraints of the course's learning objectives and the groups' pre-requisite knowledge (i.e., what has been covered so far in the MDS program). We encourage practice of version control, practice of open source development and building of their public portfolio. All projects are developed openly on GitHub.com (feedback is also given to students there as filed issues), communication between teammates relevant to the project is required to be done via GitHub issues, and students are required to submit project contributions via pull requests that are reviewed and accepted by another teammate. For an example of a one-credit project-based courses in the MDS program please see [the DSCI 522: Data Science Workflows course's public GitHub repository](https://github.com/UBC-MDS/DSCI_522_dsci-workflows)

## The project-based courses in the Master of Data Science program

Almost all Data Science courses could benefit from having a project component, but only some fit the model where the entire course assessment is a project (i.e., there are no other graded homework questions or quizzes/exams). In the Master of Data Science program we have 5 such courses, which we list below and provide a summary description of the project for each course. 

#### 1.[DSCI 522 - Data Science Workflows](https://github.com/UBC-MDS/DSCI_522_dsci-workflows)
Here the project involves a complete data analysis, from data import to communication of results, with emphasis on reproducibility and transparency. Students are asked to identify a data set, question and hypothesis for that analysis. To complete the analysis they write 4-5 R and Python scripts, as well as a reproducible report (in Jupyter or R Markdown) whose running they automate via a data analysis pipeline written in GNU Make. Software and environmental dependencies are made shippable and shareable via containerization with Docker. All development is done using version control using Git & GitHub.

#### 2. [DSCI 532 - Data Visualization II](https://github.com/UBC-MDS/DSCI_532_viz-2)
Here the project involves creating an interactive data visualization app. Students are asked to identify a data set, and use a reproducible interactive data visualization tool (e.g., R Shiny or Plotly Dash) to create and deploy an interactive dashboard to be used for exploratory data analysis purposes. Emphasis in this project is placed on iteratative improvements of the interactive dashboard based upon user feedback. 

#### 3. [DSCI 524 - Collaborative Software Development](https://github.com/UBC-MDS/DSCI_524_collab-sw-dev)
Here the project involves developing a Python and a R software package. The two packages should do essentially the same thing (they make one in each language so that can learn how to do both, and learn to generalize about software pacakges) and the students are guided to choose the package topic from one of the following themes:  1) functions that are entirely new to the R or Python ecosystem, 2) improve upon pre-existing functions in either language or 3) re-implement existing code/functions that you wish to deepen your understanding of (e.g., write a linear regression package from scratch). Emphasis is placed on robust software engineering (e.g., continuous integration testing, documentation, licensing) and collaboration (e.g., advanced version control control).

#### 4. [DSCI 554 - Experimentation and Causal Inference](https://github.com/UBC-MDS/DSCI_554_exper-causal-inf)
Here the project involves developing and analyzing observational data from a survey to try to answer a question the students are interested in. The aim of the survey is to try to answer one specific question, and thus it needs to ask additional questions to indentify confounders that will help make the analysis of the survey as causal as possible. Emphasis on survey design is placed to protect individual survey respondent's privacy. The students present the findings from the survey as a reproducible report (in Jupyter or R Markdown). Emphasis is placed on the survey data analysis in regards to statistical correctness, reproducibility and transparency. 

#### 5. [DSCI 525 - Web and Cloud Computing](https://github.com/UBC-MDS/DSCI_525_web-cloud-comp)
Here the project involves training a machine learning project on a large data set in the cloud using an elastic computing service (e.g., Amazon's EC2) and Apache Spark, as well as building and deploying the trained model as REST API (e.g., using Flask) for predictions in production. Emphasis in this project is placed on shippable environments for remote computing (e.g., Docker), computing at scale and front-end creation for data products.

## Challenges of running project-based courses

From running 8 project-based Data Science courses over 2 years we have run into our fair share of challenges. Through student feedback, consultation with other educators and trial and error we have arrived at solutions to several of these. Below we discuss the 5 greatest challenges we have faced in these courses and present solutions that have worked for us in the MDS program.

#### 1. Putting concepts learned in lecture into practice
There is a sizable leap in cognition required to take a concept learned in a controlled class setting to application of that concept in an uncontroled and realistic setting, such as in a project. For example, in [DSCI 522 - Data Science Workflows](https://github.com/UBC-MDS/DSCI_522_dsci-workflows) students learn about automating analysis pipelines using build tools, such as GNU Make. With this topic, students learn both a new concepts (stitching scripts together with a pipeline, dependency chains and automation) as well as a new tool to put those concepts into practice (e.g., GNU Make). For many students the jump from an explanation of this concept and demo of this tool in lecture does not sufficiently prepare them to easily? build an automated data analysis pipeline in a project setting that differs from the example shown in class, and where there are mutliple potentially correct solutions and way to arrive at the solutions. 

One solution we have come to help students make this leap is the use of guided toy/contained examples ([e.g., starting point for automated data analysis pipelines toy example](https://github.com/ttimbers/data_analysis_pipeline_eg/tree/v1.3)) that students work through in lecture after learning more geerally about the concept and/or tool. After the class, the instructor then provides the students with the working solution ([e.g., solution for automated data analysis pipelines toy example](https://github.com/ttimbers/data_analysis_pipeline_eg/tree/v3.0)) in case the students were not able to get the toy/contained example up and running in the allotted time. We think that this active learning approach where the students are encouraged and expected to get a small working example of the thing does three things, 1. reinforces the concepts presented in-class, 2. gives them practice and confidence applying the concepts and tools and 3. gives them a working example they can refer back too. 

*Something about chunking - breaking a project into discrete chunks like this that they can practice, lets the students learn the chunks, and then use the project to reinforce these things, as well learn how to put the differnet chunks together (less cognitively overwhelming than trying to learn and do everything at once in a project).*

#### 2. Practice doing something more than once, and building a generalization of that concept/thing
A related, but still separable challenge of teaching Data Science using a project-based course format is to give the students repeated practice and exposure to tasks needed to complete the project. For example, in a project where students are required to write a script that downloads data from the web, once the script is written, this task doesn't have to be done again, and as a consequence without intentional course design, there could easily be is no additional practice or reinforcement of this part of doing a data analysis.

In lecture toy-examples, as described above, are one possible ...


- again, toy examples worked through (active learning) in lectures
- students are required to send code to the project repo via pull requests that must be reviewed by someone else
- presentation of code and peer review session

#### 3. Aligning lecture topics with project timeline
- reverse/backwards course design is necessary (plan out project and then work lecture schedule around that)
- everything you want them to learn needs to be assessed, and so for this kind of course, it needs to be explicitly required as part of the project

#### 4. Getting people to work well together 
- group work contract & code of conduct at beginning of project
- create motivation by having the project be "real" enough to be part of their portfolio and have them develop in public
- require project-related communication via GitHub issues (so they can be seen by the whole group as well as the instructional team)
- team work document (and holding a significant portion of the grade towards this)

#### 5. Giving sufficient and timely feedback and grades
- TA training/guidance
- peer feedback sessions where groups collectively see and recevie feedback from 6 other projects
- calibrate feedback as a group on several projects for each feedback/grading milestone
- limit feedback to 3-5 key points (more is overwhelming anyways, and equal but timely feedback to all is better than lengthy feedback that is unevenly distributed over time across groups)

## Discussion

- Caveats
  - Advanced/intermediate GitHub skills required by students means this is not great as is for lower level undergraduate courses:
    - Git/GitHub is too advanced of a tool (as well as the way we use it in these projects) for an intro ugrad course. Solution, have students take a course to learn Git/GitHub beforehand, or use a simpler collaboration tool (e.g., Google Colab and/or Kaggle kernels) and some simple GitHub features (issues for collaboration and use the GitHub website upload tool to upload a version of the project for peer review session and the final submission).

- Future Directions (for masters courses)
  - require master branch protection (so students are physically forced to worked via pull requests)

  - Conclusion/recommendations
    - project-based courses are necessary for a well-rounded Data Science education (again link back to real world skills needed)
    - > 1 project is ideal within a program
    - Students should be given the opportunity to do at least one smaller project course before completing a Capstone (or thesis) project
