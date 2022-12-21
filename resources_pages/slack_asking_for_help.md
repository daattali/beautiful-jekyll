---
layout: page
title: Using Slack and asking for help
---


#### Asking about the course content

One reason we use Slack is so that you can ask for help. If you have a general question that is not about your specific situation or work, **we strongly encourage you to post it in a public course channel or the #general channel.** If you message us privately we may ask you to re-post in a public channel.
The reason for this is that often many students have the same question and it is much more efficient to have them answered in a public forum. Beyond that, it's often comforting for students to see other students asking questions,
and generally encourages a vibrant Slack ecosystem.

#### Anonymity

If you want to ask a question anonymously, you can invoke the "Anonymous bot" with `/anon`.

#### Asking a procedural question

If you want to ask a procedural question (not about the material, for example asking to reschedule a quiz due to an important event or job interview) then you can leave out the TA(s) and just communicate with the lab instructor.


#### Asking about your marks

If you have a question about how your lab or quiz was marked, please contact the TA who marked it. Typically, this will be the person who opens the notification issue in your personal grades repository.

#### How to ask

We illustrate best practices via two examples.


##### Example of a problematic post

> @instructor For question 1(b) I get an error when I run the code, should I try removing missing data? Error: computer$ python test.py
Traceback (most recent call last):
  File "test.py", line 1, in <module>
    hello, world
NameError: name 'hello' is not defined

This post is problematic for the following reasons:

- it tags the instructor. This tends to discourage others (TAs or students) from responding, which increases response time and instructor workload.
- it does not provide context, or a link to the lab in question.
- it asks whether something should be tried, even though the student could have tried this before asking.
- the code and error message are not formatted properly with `code font`.
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
> I tried the approach suggested by @otherstudent above, and I also tried removing missing data but the problem wasn't solved. Any help appreciated. Link: https://github.ubc.ca/mds-org/DSCI_513_database-data-retr_students/blob/master/labs/lab2/lab2.md#1b

This post is well-crafted for the following reasons:

- a link to the lab is provided. Note that if the lab is an `.md` or `.Rmd` file then you can link to the actual question itself, but if it's a `.pdf` or other formats then you can only link to the top of the document.
- the specific error message is given.
- the student made a reasonable effort to solve the problem but still encountered difficulties.
- it indicates that the student has read the preceding conversation and is still stuck.
- The code and error message are formatted properly.
- the actual command used to run the code (`python test.py`) is specified.

.

#### Where to ask

Slack is intended for ephemeral content. If you have a question/post/comment that may be useful in the long-term, please
instead open an Issue in the students repo of the relevant course on GitHub. Examples of content that is better posted on GitHub include:

- useful resources/readings that the instructor may want to add to the course README for future years.
- hints/workarounds/fixes for the labs that the instructor may want to incorporate into the lab for current/future years.

Examples of content that are better posted on Slack include:

- a conceptual question about something covered in lecture/lab.
- asking for help with a bug in your code.

.

#### Multi-post questions/comments

Keep in mind that when you post in Slack, people may get notifications. Therefore, it is often best to write out your whole message before posting. For example, if you write

> Hi there

(10 seconds later)

> I have a question about DSCI 551

(10 seconds later)

> Your question here

Then other users will receive a notification at the start, which will potentially pull their attention to Slack before there is anything meaningful to read. Thus, it is more efficient if there is enough content for someone to read and digest before posting the first time. This applies both to direct messages and channel posts.

#### Professionalism

MDS takes pride in creating a close and inclusive environment in our teaching and learning spaces including our Slack community. We encourage participation in all private, public and direct messaging channels, however, we ask that you follow the Code of Conduct while doing so.

Although Slack is a great tool and is constantly available, we expect you to maintain a respectful and professional relationship with your peers and the academic team. Generally, instructors and TAs will attempt to respond to your questions in a timely manner, but it's important to understand they do have other responsibilities outside of the program. An example of unprofessional Slack usage is messaging an instructor late at night and asking for /expecting an immediate response.

We have added an Anonymous bot `/anon` to the Slack workspace to give students an opportunity to ask questions anonymously if they feel uncomfortable doing so publicly. We kindly ask that you maintain this feature for its designated purpose and continue to follow the code of conduct while applying it.
