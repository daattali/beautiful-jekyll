---
layout: post
title: Teaching with GitHub
tags: [github]
---

by [Mike Gelbart](http://www.cs.ubc.ca/~mgelbart/)

---------

In this post I will describe the system we use for delivering courses via GitHub in the [UBC MDS program](https://ubc-mds.github.io). I will first describe our high level goals and how we tackled them, and then discuss some implementation details. This post assumes the reader is familiar with git and GitHub and focuses more on the technical setup than the pedagogical implications.

Our main goals for this project were as follows:

- help students gain experience with version control systems
- eliminate all paper submissions
- facilitate peer review amongst the students
- facilitate group projects/assignments
- allow course staff to view and comment on work-in-progress remotely 
- have a single place where most/all course content lives

When we were starting to think this through (around May 2016) there were already several existing solutions, such as [GitHub Classroom](https://classroom.github.com/), but none met all of our needs. We were committed to using GitHub rather than GitLab/Stash/etc because one of our team members, [Jenny Bryan](https://github.com/jennybc), had already been using GitHub to deliver [STAT 545](http://stat545.com/) and we wanted to build on her experience. The general approach is that students submit their work via GitHub and the TAs view/grade it there as well. 

Before launching, we were faced with some design decisions, such as...

1. Should we have a repository (repo) per student, or per student per course, or per student per assignment?
2. Who owns these repositories, the GitHub organization (org) or the students?
3. How do we sync the instructors' private course development repos with the student-facing course repos?
3. What happens when an assignment is posted?
4. Will students be able to see each other's work?
5. How is grading handled?
6. What happens at an assignment deadline?
7. What happens if we need to change an assignment after it is posted?

The remainder of this post is structured as answers to the above questions, in order. 

#### Should we have a repository (repo) per student, or per student per course, or per student per assignment?

We settled on one repo per student per assignment, because it gives us the greatest flexibility and fine-grained control. For example, we can set up peer review and give students read access to the work of students they are reviewing. At a deadline, we can revoke the student's write access to their own repo. These steps would not be possible with a coarser-grained repo structure. The downside of our decision is that we end up with thousands of repos in the org, but this has not caused any serious problems.

#### Who owns these repositories, the GitHub organization (org) or the students?

This was an easy one. All repos are owned by the org. This prevents strange things from happening like a student renaming their repo or revoking their group members' access to the repo.

#### How do we sync the instructors' private course development repos with the student-facing course repos?

Our approach here was to have one "instructors repo" and one "students repo" per course (these are separate from the assignment repos which are per student per assignment). The course staff develops material in the instructors repo and copies the relevant info to the students repo (visible to the students) when ready. We also set up a GitHub/Slack integration so that the students are notified in the appropriate Slack channel whenever a commit is made to the students repo for a particular course. Overall this solution isn't perfect as it requires some manual copying and redundancy between the two repos (voilating the [DRY principle](https://en.wikipedia.org/wiki/Don%27t_repeat_yourself)). We've noticed that some instructors (myself included) develop lecture materials in the students repo (allowing the students to see the incremental progress and commit history) whereas others develop materials in the instructors repo and then copy over the final version shortly before the lecture. In either case, some things like exams need to stay private in the instructors repo until they are ready to be deployed.

#### What happens when an assignment is posted?

Our assignments tend to contain some "seed" content such as partially written code which the student needs to complete (this often takes the form of a [Jupyter notebook](http://jupyter.org/) or [R Markdown](http://rmarkdown.rstudio.com/) document). GitHub Classroom uses a template repository that is copied for each student at the start of an assignment. In hindsight this model would have worked too, but we decided that we wanted to keep all course materials in a single instructors repo, with different directories for different assignments. In order to create copies of a template repo one can use the [Source Imports API](https://developer.github.com/v3/migration/source_imports/). However, to implement our system of seeing the assignment repos with just a subdirectory of a repo, I had to use the [Contents API](https://developer.github.com/v3/repos/contents/). This comes with its own difficulties, like a 1 MB limit on file size, but has a lot of advantages like the fact that the commit history is not preserved in the student copies. (It should also be possible to wipe the commit history and then use the Source Imports API, but I haven't looked into it.)

#### Will students be able to see each other's work?

We let students see each other's work for each assignment once the deadline has passed. It's not clear yet how valuable this is and whether it's worth it. But this is definitely more useful for open-ended assignments since students can refer to the official solution set as well. The main disadvantages are that some students may not be comfortable with it, and that each student ends up with lots of repositories to sort through which makes searching for their own repos just slightly more cumbersome.

#### How is grading handled?

After an assignment deadline, we automatically generate a (Markdown) table for the TAs. Each row has a student's name, a link to their submission repo, and a link to a JSON file in which the TA enters grades. The JSON form is not particularly convenient because it's easy for the JSON to get corrupted. Some of my colleagures are working on something better/faster for the TAs.

#### What happens at an assignment deadline?

There are two main approaches here. The first is to remove the students' write access to their assignment repositories after the deadline passes. This requires manually running a script (what we have been doing, for now) at the deadline or else setting up a server with [cron](https://en.wikipedia.org/wiki/Cron) to do this automatically. The other solution is to rely on timestamps so that no particular code needs to run at the deadline. This is a bit tricky because students can manipulate their git commit timestamps, so they can't be relied on. However, the GitHub [Events API](https://developer.github.com/v3/activity/events/) exposes the GitHub push timestamps which (I believe!) cannot be manipulated. If the timestamps are known, one can make late assignments as such. Or, even better, the auto-generated links made for the TAs can point to the last commit before the deadline, so that any student work after the deadline is simply ignored. One problem I've encountered with the Events API is that events seem to disappear after some length of time; that is, using the Events API I can access recent Events but not necessarily older ones. This is not a problem if the timestamps are accessed somewhat promptly, but doing so partially defeats the purpose of the timestamp-based approach, which was to avoid having to run any code at the deadline. Still, in this case the exact time the code is run is no longer critical, which is nice. 

The one approach I know doesn't work well is to reject assignments that have a commit after the deadline. From my experience students will sometimes ignore the instructions and make extra commits. Therefore I recommend either removing write access or grading based on the last commit before the deadline. 

#### What happens if we need to change an assignment after it is posted?

This is a fun one, and an important one given that new assignments in a new program are bound to contain bugs (the MDS program was launched in September 2016). The difficulty with updating these provided code files is that students may have already started to make changes to the files. Thus we want to merge our instructor changes with the student changes. Luckily we've just built everything on version control! The particular solution I used is to create a branch (which I called _instructor-updates_) in each assignment repo. Initially, the instructor-updates branch just contains a copy of the original materials. When I want to update something, the updates are applied to instructor-updates and then a pull request (PR) is created from that branch to the student's master branch. This works fairly well, although things improved when I realized I could make instructor-updates a [protected branch](https://help.github.com/articles/about-protected-branches/) with the GitHub API and thus prevent students from doing bad things like deleting instructor-updates after merging a pull request (this is fine at first but causes problems later if there's later a second PR on the same repo).

Well, that's about it. Overall, the system worked fairly smoothly in its first year of operation. If you are interested in more detail please see [my code](https://github.com/mgelbart/rhomboid) and the [video demo of the system](https://www.youtube.com/watch?v=zgiaBS4uUk0). The public code is a more general-purpose version with the MDS-specific features removed. It is meant to be used for a single course and does not take advantage of having a suite of courses that fit together. An example of an MDS-specific feature is the "home table" for each student, which looks something like this:

![](mds-student-home.png)

With this table, the students have easy access to their assignments/quizzes/grades for all of their MDS courses in one central location. 

### References

- [GitHub Classroom](https://classroom.github.com/)
- ["How I implemented GitHub in my classroom" (SIGCSE 2017)](https://www.youtube.com/watch?v=3j1BaUw53pM)
- [UBC ClassPortal](https://github.com/ubccpsc/classportal-backend) (in progress)
- [My code](https://github.com/mgelbart/rhomboid) and [video demo of our system](https://www.youtube.com/watch?v=zgiaBS4uUk0)
