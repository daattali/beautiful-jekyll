---
layout: post
title: Project courses in MDS
subtitle: by Tiffany Timbers and Mike Gelbart
share-img: "https://github.com/UBC-MDS/UBC-MDS.github.io/blob/master/img/mds-group-contract.jpg?raw=true"
---

How can we train effective data scientists? Traditional lecture/lab-based courses typically involve prescribed and well-defined examples, and we found this format very effective for foundational courses that focus on a particular area of statistics, machine learning or computer programming. However,  real-world data science differs greatly from these courses: data is messy, the tasks are not perfectly defined, knowledge must be integrated from various areas of data science, and collaboration with others is typically required. Our [Master of Data Science](https://ubc-mds.github.io/about/) (MDS) program ends with an [8-week full-time Capstone course](https://ubc-mds.github.io/capstone/about/), which provides much of the needed hands-on experience. However, based on student and instructor feedback, it was evident that we needed to do more. Thus, to augment and prepare students for Capstone, we have started transforming some of our traditional lecture/lab-based courses into smaller project-based courses as well.

For the last two years we have run four project-based courses and have iteratively refined what, for us, constitutes a successful project course in data science. The remainder of this post describes the structure and content of our project-based courses, as well as the challenges we faced along the way.

## Project-based course design & logistics

All MDS courses (except Capstone) are one month long, with students taking four courses at a time. Like the traditional courses, our project courses include eight 80-minute lectures. However, instead of four weekly lab assignments, the project courses have four _project milestones_, each building on the previous. All MDS project courses are done in groups of 3-4 students, which are randomly assigned for each course. For the project topic, students are given free reign to choose a topic that fits within the constraints of the course's learning objectives. For example, in our Data Visualization II course, which focuses on interactive visualizations, the students could develop a data visualization dashboard with a data set and functionality of their choosing. 

All projects are developed openly on GitHub.com. Students are required to communicate via GitHub Issues and submit contributions via pull requests that are reviewed and accepted by another teammate. This way, students practice standard version control workflows, gain exposure to open source development, and at the same time build their personal data science portfolios. We also use GitHub to give feedback to the students: the instructional team files Issues after each milestone. Additionally, just before the third project milestone, students participate in a face-to-face peer review session, after which they provide constructive feedback to other groups by opening GitHub issues in their respective GitHub repositories.

## The project-based courses in the Master of Data Science program

Below we briefly describe the project courses in the MDS program. The courses titles link to our [publicly available teaching materials](https://github.com/ubc-mds/public) for each course. 

#### 1. [DSCI 522: Data Science Workflows](https://github.com/UBC-MDS/DSCI_522_dsci-workflows)
Here the project involves a complete data analysis, from data import to communication of results, with emphasis on reproducibility and transparency. Students are asked to identify a data set, question and hypothesis for the analysis. To complete the analysis they write 4-5 R and Python scripts, as well as a reproducible report (in [Jupyter](https://jupyter.org/) or [R Markdown](https://rmarkdown.rstudio.com/)), and they automate their data analysis workflow using GNU Make. Software and environment dependencies are made shippable and shareable via containerization with Docker.

#### 2. [DSCI 532: Data Visualization II](https://github.com/UBC-MDS/DSCI_532_viz-2)
Here the project involves creating an interactive data visualization app. Students are asked to identify a data set and use an interactive data visualization tool (e.g., R Shiny or Plotly Dash) to create and deploy an interactive dashboard for exploratory data analysis. Emphasis is placed on iterative improvements of the interactive dashboard based upon user feedback. 

#### 3. [DSCI 524: Collaborative Software Development](https://github.com/UBC-MDS/DSCI_524_collab-sw-dev)
Here the project involves developing parallel software packages in R and Python. By writing their package in both languages, students learn about the similarities and differences between the two frameworks. Students choose the package topic from one of the following themes:  1) functions that are new to the R or Python ecosystem 2) improving upon pre-existing functions in either language or 3) re-implementing existing code/functions that they wish to deepen their understanding of (e.g., write a linear regression package from scratch). Emphasis is placed on robust software engineering practices (e.g., continuous integration testing, documentation, licensing) and collaboration (e.g., advanced version control). 

#### 4. [DSCI 525: Web and Cloud Computing](https://github.com/UBC-MDS/DSCI_525_web-cloud-comp)
Here the project involves training a machine learning model on a large data set in the cloud using a cloud computing service (e.g., Amazon EC2) and Apache Spark, as well as building and deploying the trained model as REST API (e.g., using Flask) for predictions in production. Emphasis in this project is placed on shippable environments for remote computing (e.g., Docker), computing at scale and front-end creation for data products. *Note: the project version of this course is currently in development and will be first offered in 2021.*

We also tried a project version of [DSCI 554: Experimentation and Causal Inference](https://github.com/UBC-MDS/DSCI_554_exper-causal-inf) but ultimately decided to switch it back to a traditional course based on student feedback. 


## Project course challenges

From running 8 project-based Data Science courses over two years we have run into our fair share of challenges. Through student feedback, consultation with other educators and trial and error we have arrived at solutions to several of these. The next section presents some challenges we have faced in these courses, along with solutions that have worked for us in the MDS program.

#### 1. Using lecture time effectively

Many of our project courses cover data science tools and workflows, topics which lend themselves to hands-on project-based assignments. When teaching students how to use data science tools, how does one design an engaging lecture? We have found success using guided toy examples. After a general overview of the concept/tool, students spend lecture time working through these toy examples. After class, the instructor provides the students with the working solution. For an example, see the in-class exercise on automated data analysis pipelines [here](https://github.com/ttimbers/data_analysis_pipeline_eg/tree/v1.3) and the solution [here](https://github.com/ttimbers/data_analysis_pipeline_eg/tree/v3.0). Following these toy examples in lecture, students put these methods into practice in a more complex setting, as part of their projects.

#### 2. Providing useful feedback and grades in a timely manner

Feedback can extremely useful to students, but only if given within a useful time frame. Feedback given too late is often ignored by students, as they have moved onto other tasks and have no immediate use for it. Providing timely feedback in a project course is challenging because each project is different, thus requiring a deep dive by the TA or instructor for each group. Our program's fast pace adds additional time pressure.

Over time, we have developed several approaches to help us meet this challenge. First, we give our students and TAs clear rubrics and expectations for each project milestone. In doing this, we help the TAs focus their efforts. Second, we ask the TAs to limit their feedback to 3-5 key points that map onto the rubrics and expectations for each project milestone. This prevents the TAs from going overboard on feedback, helps ensure that all groups receive similar amounts of feedback, as well as avoids situations where the students are overwhelmed by so much feedback that they lose motivation and cannot remember and implement the feedback when they are working on similar tasks in the future. Third, we assign each reviewer to the same projects for each milestone. While this saves time and enables the TA or instructor to follow the development of their assigned projects, it also opens the door to unfair grading if some TAs are more strict or generous than others. To mitigate this issue, all the TAs and instructors work together on a round of calibration review and grading for each milestone. Finally, as discussed above, we also run peer feedback sessions which result in timely feedback. Additionally, the students gain valuable knowledge and insight into other ways the project could be done by reviewing the work of their peers.

#### 3. Collaboration and team dynamics

To facilitate and help our students collaborate effectively with each other on the projects we employ several strategies. First, at the start of the course, teams work together to develop a [team work contract and code of conduct](https://github.com/UBC-MDS/DSCI_591_capstone-proj/blob/master/coc_n_teamwork.md#1-team-work-contract). Second, by having students develop the projects in public repositories, the commits of each team member are tracked and visible to the outside world. Furthermore, because all project-related communication must happen via GitHub issues, all communications can be seen by the whole group, thus avoiding the possibility of leaving some group members out of certain conversations. Finally, we assign 20% of the students' grade to team work. This sends a strong signal to the students that collaboration is a critical part of the success of their project. To assess each students' team work, we review the project's GitHub history and have all the students fill out out [team work report](https://github.com/UBC-MDS/DSCI_591_capstone-proj/blob/master/deliverables/team_work/team_work.pdf). In this report, students rate each member of the team, including themselves, on preparation, participation and communication, effectiveness, and cooperation. Students also state the roles of each of the group members in the project, and discuss what went well and what went poorly during their team project experience. The GitHub history and the team work reports form the basis for the students' team work grades.

## Conclusion

Our project courses are fairly new, and we are still refining them. However, we have already observed significant improvements in student Capstone projects since launching these new project courses. In particular, recent Capstone projects include much less [technical debt](https://en.wikipedia.org/wiki/Technical_debt) and have been much easier for the Capstone partner organizations to start using and extending. Through student course evaluations, surveys and anecdotal discussions with students and alumni we have also observed improved student satisfaction and perceived value from the project-based versions of these course vs. the traditional paradigm.

Although our project courses seem to be effective, a caveat to consider before implementing similar courses at your institution is that our students explicitly taught and exposed to repeated practice using version control via git and GitHub before their first project course (see [this post](https://ubc-mds.github.io/2017-08-24-teaching-with-github/) on how we use these tools in MDS). For courses or programs where this is not the case, alternative collaboration platforms may be able to replace Git and GitHub, especially for courses based on Jupyter notebooks. Examples include: [CoCalc](https://cocalc.com/), [Google Colab](https://colab.research.google.com/), [Kaggle Kernels](https://www.kaggle.com/kernels) or [RStudio Server Pro](https://www.rstudio.com/products/rstudio-server-pro/). These tools could be combined with some simple GitHub features such as issues for collaborative communication and use the GitHub website upload tool to upload a version of the project for peer review session and the final submission.

Overall, from our experience with the UBC MDS program, we believe that project-based courses are necessary for a well-rounded data science education. These courses give students the opportunity to work in more real-world situations where the "right" answer is less well-defined, collaboration is required and many aspects of data science are brought together. We also believe that students should have the opportunity to do more than one project in their data science program so that they can repeatedly practice an entire project from beginning to end in a lower stakes environment before they are required to do so on the job. 

--------

## Authors:
[Tiffany Timbers](https://www.tiffanytimbers.com/) is Option Co-Director of the MDS Vancouver program and an Instructor in the UBC Department of Statistics.

[Mike Gelbart](https://www.mikegelbart.com/) is Option Co-Director of the MDS Vancouver program and an Instructor in the UBC Department of Computer Science.

## Acknowledgements: 
We would like to acknowledge [Tiffany Timbers](https://www.tiffanytimbers.com/), [Vincenzo Coia](https://vincenzocoia.github.io/), [Varada Kolhatkar](https://kvarada.github.io/), [Meghan Allen](https://www.cs.ubc.ca/~meghana/), [Tamara Munzner](https://www.cs.ubc.ca/~tmm/), [Cydney Neilson](http://www.cydney.org/Home.html) and [Paul Gustafson](http://www.paulgstf.com/) as the Instructors who developed, shaped and delivered the project-based courses in MDS over the last two years. 
