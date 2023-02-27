---
layout: post
title:  "Code Analysis Rules to watch out for while coding"
date:   2023-02-25 11:57:21 AM
categories: [CodeAnalyzers]
---

Recently I had to fix a bunch of Code Analysis warning in the code base. I started to wonder these are some of the common mistakes in the code that are made and would be just better to keep in mind before we start coding.

| Code Analysis Rule Code  | Code Analysis Rule Explanation  |
|---|---|
|  CA1304 |  Specify CultureInfo. When doing string comparisons or  doing some other string operations is always best to use the Culture info otherwise it leads to inconsistent results in different languages/locales.|
|  CA2007 |  Do not directly await a Task. When adding the await statement always use the .configureawait(false) at the end, otherwise this may lead to deadlocks especially on the UI centric apps.|
|  CA1062 |  Validate arguments of public methods. For any method thats exposed publicly, best to validate the parameters before starting using them. |
|  CA1707 |  Identifiers should not contain underscores. I am always guilty of this. underscores should be avoided when declaring identifiers.|
|  CA1805 |  Do not initialize unnecessarily. Class member field and variables are initialized to null by default. No need to set them to null explicitly.|
|  CA1052 |  Static holder types should be Static or NotInheritable. If a class contains all static methods, best to mark the class as a static class or sealed. |


I would be updating this list as I go through more warnings. But please TreatWarningsAsErrors in your codebase as this will help the code quality and hence helps in maintaining the code.

!Happy Learning and improving one day at a time!
