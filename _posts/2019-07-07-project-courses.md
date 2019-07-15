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

## Challenges of running project-based courses

- Challenges (and our solutions) for teaching Data Science using a project-based format:
  - the jump from going from concepts in lecture slides to doing the thing in the project can be a huge cognitive leap, solutions:
    - toy examples that students work through in lecture (active learning)
  - getting students to generalize or practice concepts learnt in the course more than once (e.g., once your particular data set is read into R/Python you don't have to do that again for your project), solutions:
    - again, toy examples worked through (active learning) in lectures
    - students are required to send code to the project repo via pull requests that must be reviewed by someone else
    - presentation of code and peer review session
  - matching the lectures materials to the stages of the project development
    - reverse/backwards course design is necessary (plan out project and then work lecture schedule around that)
    - everything you want them to learn needs to be assessed, and so for this kind of course, it needs to be explicitly required as part of the project
  - facilitating people to work well together
    - group work contract & code of conduct at beginning of project
    - create motivation by having the project be "real" enough to be part of their portfolio and have them develop in public
    - require project-related communication via GitHub issues (so they can be seen by the whole group as well as the instructional team)
    - team work document (and holding a significant portion of the grade towards this)
  - giving sufficient and timely feedback (especially for larger class sizes) as well as grading
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
