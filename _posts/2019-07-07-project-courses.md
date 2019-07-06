---
layout: post
title: Teaching Data Science using project-based courses in the UBC Master of Data Science program
---

### Outline

Data Science is the act of extracting value from data through reproducible and auditable processes. This definition is intentionally broad such that it may encompasses all the different things Data Scientists do to gain insights and knowledge from data, and the things that need to be done can be very different depending on the application of knowledge or insights needed to be garnered from the data. How can we teach aspiring Data Scientists "what things need to be done" to answer their data question? Typical lecture and lab based courses are one way to give prescribed and well-defined examples, and at the beginning of a Data Science education these are necessary. But only ever being exposed to prescribed and  well-defined problem sets hardly prepares the aspiring data scientist for real world data science work in either industry or the research lab, where projects are more like snowflakes than cookies (Figure 1). Project-based courses where data is messy, the task is not perfectly defined and people are required to collaborate and work together to extract value from the data is a more real-world-like setting where students have the opportunity try, have successes and failures across many more axes of Data Science than are typically available in a focused lecture/lab-based course. 

- A brief history/context of project-based courses in MDS

- Outline what project-based courses in MDS look like (at a high level, and then link to workflows course site) for both small courses, and for Capstone

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

- Caveats
  - Advanced/intermediate GitHub skills required by students means this is not great as is for lower level undergraduate courses:
    - Git/GitHub is too advanced of a tool (as well as the way we use it in these projects) for an intro ugrad course. Solution, have students take a course to learn Git/GitHub beforehand, or use a simpler collaboration tool (e.g., Google Colab and/or Kaggle kernels) and some simple GitHub features (issues for collaboration and use the GitHub website upload tool to upload a version of the project for peer review session and the final submission).

- Future Directions (for masters courses)
  - require master branch protection (so students are physically forced to worked via pull requests)

  - Conclusion/recommendations
    - project-based courses are necessary for a well-rounded Data Science education (again link back to real world skills needed)
    - > 1 project is ideal within a program
    - Students should be given the opportunity to do at least one smaller project course before completing a Capstone (or thesis) project
