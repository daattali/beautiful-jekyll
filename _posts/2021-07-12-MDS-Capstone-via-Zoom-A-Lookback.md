---
layout: post
title: MDS Capstone via Zoom: A lookback
subtitle: by Alex Truong Hai Yen, Ifeanyi Anene, Tran Doan Khanh Vu and Tanmay Sharma
---

Hello dear reader,

This blogpost aims to share some of our learnings from the MDS Capstone project. If you’re a new student or a current student reading
this after completing your block 6 coursework, congratulations! We wish you the very best in your capstone journey and hope that some
of the following tips might serve you well during your project. Put on your data science hats and read on!

## Project Management
### Have a realistic timeline, give a buffer for your intended timeline

8-weeks for capstone projects is double the time of your earlier group projects in MDS, and it may make you think you have more time.
However, more often than not, people tend to overestimate their productivity. Furthermore, from our experience, the first week for the
hackathon and the last two weeks for presentation, testing & documentation went by much quicker than we realized, hence the core time
for the project development was actually around 5 weeks.

![Timeline](../img/blog/AITT/unsplash_photo.jpg)

[Photo obtained from Unsplash](https://unsplash.com/photos/oYmxe7sCitg)

Therefore, having a realistic timeline is key to a successful and engaging capstone experience. This involves having an honest and open
discussion on what your team can realistically accomplish in the middle 5 weeks at the very start of the project, which may result in
moderating the intended scope set by the Capstone partner. Also, don’t feel compelled to fulfill all of the partner's requirements. We
believe the Capstone partner would be more appreciative that we spend time thinking about attainable objectives, be upfront to them on
this and over-deliver, than promise the sky and under-deliver in the end. This has worked out well for us.
 
Moreover, as unexpected requirements or analyses may arise as you progress through your project development phase, our next two-cents
are that you should also consider adding a buffer to your intended timeline. For our project, we always tried to set a benchmark
timeline with a buffer based on initial estimates and continuously track our progress and adjust them along the way.


### Have an agenda and a meeting moderator for each meeting with the faculty mentor/Capstone partner

![Agenda](../img/blog/AITT/agenda_photo.jpg)

[Photo obtained from Unsplash](https://unsplash.com/photos/RLw-UC03Gwc)


You’ll be surprised at how quickly time flies in those meetings. Moreover, both your faculty mentor and Capstone partner have a full
time work schedule to keep up, so make those minutes count when you get to meet them. What our group did was to always prepare and send
out agendas to those involved before each meeting and stick to the agenda during the meeting. We also ordered the discussion points by
priority so the crucial points get to be discussed and resolved first in case we do not have time to address all items during the
meeting. In addition, our team members took turns to be the meeting moderator who was in charge of ensuring the discussion moved along
in the right direction and at the right pace. Such practices help everyone set the right frame of mind before joining the meeting, and
be on the topic during it. Productivity point: check, professionalism point: double-check! 😉


### "If you want to go fast, go alone; but if you want to go far, go together."

![going far](../img/blog/AITT/going_far_together.png)

[Photo obtained from Unsplash](https://unsplash.com/photos/Dph00R2SwFo)

This African wisdom applies beautifully to our capstone experience. As people come from different backgrounds with various skill sets,
one’s weakness can be someone else’s strength, thus we are stronger as a unified team. For example, members with more programming
experience can guide and assist others with less experience to reduce individual struggle and increase team productivity. Similarly,
those who are familiar with project management can shed some light on best practices which the rest can learn from. Our team found
those group working sessions, even via Zoom, where we can leverage on all our members' skills, not only brought us together but also
allowed us to “go farther” in terms of learning during our capstone project. So do lend a hand when your teammates need help! 


## Communication

### Agree with the Capstone partner on expected products

Be clear and realistic from the beginning. It is imperative to have a project schedule which caters to the team’s capabilities and the
two month capstone timeline. Focus on the main part of your project such as the data science workflow instead of complementary
components like an overcomplicated UI. Therefore, it is very beneficial to have a well thought out project plan and clearly defined
deliverables and ensure that the Capstone partner agrees and consents to the same by the end of the first week. For projects which have
evolving goals, ensure that the team’s vision is aligned with the capstone partner’s expectations through continuous communication. 

![communication](../img/blog/AITT/communication.png)

[Photo Source](https://giphy.com/explore/communication)


### Hold regular meetings with your faculty mentor and Capstone partner 

If feasible, it is advisable to split your 1-hour weekly meeting with your faculty mentor into two 30-minute sessions, one early and
one later in the week. Depending on everyone’s time schedules, one of these sessions can be online. Doing so is more effective towards
iterative development by receiving more frequent and timely feedback from the faculty mentor on your progress. Also, make sure you give
a weekly update to your Capstone partner in which you talk about the data science methods, incremental findings and next steps. Weekly
meetings with the Capstone partner can be a great platform for you to discuss ideas, clarify questions and seek their expert inputs.


### Ask for more data if needed 

During the EDA stage, if you observe that the data provided is unrealistic or insufficient for your model, do not hesitate to clarify
with the Capstone partner and ask for more data if needed. Though it is harder to gather more data during later stages of the project,
make sure to continue to evaluate your data needs during model development. Having sufficient and appropriate data is crucial for
obtaining robust results. 


![more data](../img/blog/AITT/more_data_photo.png)

[Photo Source](https://makeameme.org/meme/yeahim-gonna-need-c45pbd)


## Coding

### Plan and refactor your code on a regular basis

![plan refactor code](../img/blog/AITT/plan_refactor_code.png)

**Make your code DRY, meaning Don’t Repeat Yourself**: More often than not, you will encounter pieces of code that appear repetitively
throughout the project. The same lines of code used to initialize or tune hyperparameters for a Ridge model can be used for
RandomForest, XGBoost, CatBoost… By leveraging the power of inheritance, you can significantly reduce the amount of code written, and
subsequently the time to review and test the same. Instead of rushing to write code, a more enlightened path would be to first think
about how you can define a base class (BaseModel) with the necessary methods, and all other child classes (AdvancedModel) inheriting
from this base class. Sometimes, a simple act of grouping codes into a separate function can help as you may realize that the same
function can be used in another place. On top of that, reviewing and removing redundant code makes your code easier to follow and
probably run faster.

**Develop a habit of splitting your code into notebooks and scripts separately**: Although Jupyter notebooks are useful to display your
results or any graphs plotted, they are extremely challenging when it comes to testing, merging or reviewing the code. On top of that,
putting a lot of code in a notebook can distract the audience from the main flow of the analysis as they may want to pay more attention
to the result, rather than the specific details on how it was done. As a result, you should include only the essential code in the
notebook, and abstract major functionality to the Python/R scripts.


### Make your code maintainable

![write maintainable code](../img/blog/AITT/write_maintainable_code.png)


**Write simple documentation or tests at first**: Documentation helps users understand how to use your functions, and tests help verify
that the functions are working as expected. Without the existence of these two components, future users will be puzzled and get lost in
your maze of code, increasing the chance that they discard anything done before and start from scratch. Having said that, do not write
detailed documentation and complicated tests from the beginning, as it takes time and the code may need to be modified on a regular
basis. Hence start simple first, and try to add more details to documentation and tests as the project progresses.

**Have another teammate review your code**: Your code may be intuitive to you, the author, yet, it might be an insurmountable task for
another person to comprehend. Hence, your teammates can play the role of future users to provide feedback in case your code takes too
much time to digest. On top of that, they can help identify bugs or mistakes in those lines of code, which definitely help your team in
the long run. You can enforce main branch protection to make sure that another teammate needs to review your code before it can be
merged into the main branch.


### Rerun code often to discover errors early, and commit often.

![rerun code](../img/blog/AITT/rerun_code_meme.png)

**Run tests in the branches to make sure they pass, merge approved code into the main branch, pull down the latest change and run tests again**: You may never know if that single tiny innocent line of code can do a ton of damage to the whole project, especially if it
affects the data used for analysis. Besides, a change in one file can have an unintended effect on another file. As a result, the only
way for us to find out is to run pytest tests in those branches first to make sure they do not break the main code. Once they all
passed, merge this code into the main branch and test them thoroughly via pytest one more time.

**Make use of free time to rerun the whole project regularly**: Sometimes, code takes a long time to run, especially if your dataset is
huge or the simulation is massive. Your team can write an automated script to rerun the whole project from scratch and just let it run,
while you can still do errands in the meantime. If needed, these automated scripts can be let to run overnight or over the weekend.
Even if your team finishes the whole project well in advance, just spend some more time rerunning it again to avoid any last minute
panic.














--------

## Authors:
[Alex Truong Hai Yen](https://www.linkedin.com/in/alextruong91/)

[Ifeanyi Anene](https://www.linkedin.com/in/ifeanyianene/)

[Tran Doan Khanh Vu](https://www.linkedin.com/in/tdkhanhvu/)

[Tanmay Sharma](https://www.linkedin.com/in/tanmaysharma19/)
