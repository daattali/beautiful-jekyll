---
layout: post
title: JimmysClassList
subtitle: An idea
tags: [timetable, schedule, idea]
comments: true
---

It's always Little Jimmy this, Little Jimmy that. Poor Jimmy can't catch a break.

Codenamed JimmysClassList, I think I have come up with my second project.

JimmysClassList is an auto-timetabling application. Now you may say "But sevenem, there are loads of free timetable applications on GitHub!". Well, I looked at the most popular apps, and none of them seem to have features to **restrict certain classes to certain days or times**. Some of them actually require you to make the timetable by filling in a .json file, and the application simply reproduces the timetable in a table. These are not what I had in mind when I was imagining how it would look and run.

**This is my desired output:**

![Timetable produced](/assets/img/jimmy01.jpg)

The user interface should be as simplistic as possible without compromising customisation. The user must enter:

- classes to schedule (e.g. German) (default to 60 min length)
- restrictions (if any, e.g. German restricted to only Y5/6 on Thursdays and Fridays)
- year levels (default to 4 classes per year level, but adjustable with + or - buttons)

The user can also adjust the available slots with + or - buttons.

This will produce a timetable in table format. Each scheduled class can then be moved around by dragging it.
Dragging it on top of another class will swap those two classes.
Dragging it to the side will remove it temporarily.

This way, it will always have all classes in it (except for classes put to the side). It will automatically colour code same year level classes, but this can be turned off for printing.

JimmysClassList will then allow the user to export the timetable in .pdf, .doc or spreadsheet format. It can also be shared with others directly. Others may choose to remove other classes from it so only their class is showing.

Regarding language, I don't know what to start writing it in. Ideally it becomes a web app. I'm just going to have a go!