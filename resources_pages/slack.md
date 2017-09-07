---
layout: page
title: Slack usage guidelines
---

## The Slack app

We will be using [Slack](www.slack.com) as our primary means of electronic communication in the MDS program. We will invite you to our Slack team when the program starts.

#### Channels

Our Slack team, `UBC-MDS`, contains many _channels_ for conversation. We will enrol you in the channels for the 25 MDS courses, as well as [#data-science-careers](https://ubc-mds.slack.com/messages/data-science-careers/details/), [#git-general](https://ubc-mds.slack.com/messages/git-general/details/), [#python-general](https://ubc-mds.slack.com/messages/python-general/details/) and [#r-general](https://ubc-mds.slack.com/messages/r-general/details/). You should be automatically enrolled in the [#general](https://ubc-mds.slack.com/messages/general/details/) and [#random](https://ubc-mds.slack.com/messages/random/details/) channels when you join Slack.

These channels are all public. You can create private channels as well. For example, each year the students
typically create a private channel for students only. After you graduate from the program, we will invite you to the UBC MDS Alumni Slack team.

#### Direct Messages

A direct message thread is different from a private channel. To open a direct message, go to `DIRECT MESSAGES` on the left-hand sidebar and click on the little `+` sign. Then, type in the names of the people who should be part of the direct message thread.


#### Formatting

Slack has a lot of nice features for formatting text, links, etc. For MDS, one important feature is for formatting code within Slack.
To do this, we use the single backtick (`` ` ``) and triple backtick (```` ``` ````), for inline code and code blocks respectively. As it
turns out, these conventions are the same in Markdown! Here is a `some inline code` and here is a code block:

```
First line
Second line
etc.
```

#### Browser vs. desktop app
Slack can be accessed via the [web interface](https://ubc-mds.slack.com) or via the [desktop app](https://slack.com/downloads/). You are free to decide which one you prefer. We do suggest that you consider the desktop version, however, since we will be using Slack so much in the program. There is also a mobile app for your phone, if you want to be extra connected.

#### Notifications
We don't want to wake you up with our Slack annoucements! You can edit your notification settings by clicking on the "UBC-MDS" at the upper-left and selecting "Preferences". From here you can decide how invasive you want Slack to be. One useful feature is the Do Not Disturb period, which by default is from 10 PM to 8 AM. If you have different hours you may want to adjust this accordingly.

Sometimes we will use `@students` when we make announcements that we want all students to receive. This has the same effect as directly mentioning everyone in the `students` user group and will make it more likely for you to receive a notification. However, once again, we don't want to wake you up to read these announcements immediately! We just want you receive them reasonably soon. Please set your notification preferences accordingly.

## Asking for help

#### Asking about the course content

One reason we use Slack is so that you can ask for help. If you have a general question that is not about your specific situation or work, **we strongly encourage you to post it in a public course channel or the #general channel.** If you message us privately we may ask you to re-post in a public channel.
The reason for this is that often many students have the same question and it is much more efficient to have them answered in a public forum. Beyond that, it's often comforting for students to see other students asking questions,
and generally encourages a vibrant Slack ecosystem.

If you need to ask a course-related question privately, please open up a direct message thread with both teaching fellows _and_ the TA(s) for the relevant course. This allows the most qualified/available person to answer, and also
keeps the others up to date on what is happening in the course.

#### Asking a procedural question

If you want to ask a procedural question (not about the material, for example asking to reschedule a quiz due to an important event or job interview) then you can leave out the TA(s) and just communicate with the teaching fellows. In this case, please direct message _both_ teaching fellows as we make these decisions together anyway and it's much simpler if we are both part of the message thread.

#### Asking about your marks

If you have a question about how your lab or quiz was marked, please contact the TA who marked it. Typically, this will be the person who opens the notification issue in your personal grades repository.

Note: if you can't remember who your TA is for a particular course, this information is available at https://github.ubc.ca/orgs/ubc-mds-2016/teams. The team for a particular course will consist of the instructor, the MDS teaching fellows, and the TA(s). Although their Slack username may not be the same as their GitHub username, there is hopefully enough information to figure it out

#### How to ask

We illustrate best practices via two examples.

##### Example of a bad post

> @teachingfellow For question 1(b) I get an error when I run the code, should I try removing missing data? Error: computer$ python test.py
Traceback (most recent call last):
  File "test.py", line 1, in <module>
    hello, world
NameError: name 'hello' is not defined

Explanation: this post is problematic for the following reasons...

- it tags the teaching fellow for no particular reason. The question could just as likely be answered by the TA(s) or other students.
- it does not provide context, or a link to the lab in question.
- it asks whether something should be tried, even though the student could have tried this before asking.
- it indicates that the student has not read the preceding conversation about this topic.
- code and error message not formatted properly with `code font`.
- the actual command used to run the code is not specified.

##### Example of a good post

> For question 1(b) I get the following error when I run the code with `python test.py`:
```
computer$ python test.py
Traceback (most recent call last):
  File "test.py", line 1, in <module>
    hello, world
NameError: name 'hello' is not defined
```
> I tried the approach suggested by @otherstudent above, and I also tried removing missing data but the problem wasn't solved. Any help appreciated. Link: https://github.ubc.ca/ubc-mds-2016/DSCI_513_database-data-retr_students/blob/master/labs/lab2/lab2.md#1b

Explanation: this post is well-crafted for the following reasons...

- link to the lab is provided. Note that if the lab is an `.md` or `.Rmd` file then you can link to the actual question itself, but if it's a `.pdf` or other formats then you can only link to the top of the document.
- specific error message is given.
- student made a reasonable effort to solve the problem but still encountered difficulties.
- it indicates that the student has read the preceding conversation and is still stuck.
- code and error message formatted properly.
- the actual command used to run the code (`python test.py`) is specified.

#### Privacy

Slack is not hosted on Canadian servers, and thus we recommend keeping the discussions and private messages on Slack to those related to course content, organization, etc. For personal and sensitive issues, we recommend that communications between MDS students and instructional staff be carried out using UBC email.
