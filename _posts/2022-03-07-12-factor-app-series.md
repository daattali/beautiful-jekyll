---
layout: post
title: 12 Factor App Series
subtitle: Introduction
comments: true
---
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
I was working in the midwest for an enterprise during the early 2010's that was struggling to modernize its enormous
data catalog.  Scaling, searching, and data portability were all in the early stages as these datasets were starting
their first migrations out of mainframes and into web services.  What became apparent was how ill prepared these
webservice tools were with handling these massive datasets.  But how on earth were our competitors able to do this?
They did not seem to struggle with the scaling, searching, and data portability concerns that most of our engineering
team struggled with.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
During my search, I discovered there was quite a radical shift going on in enterprise software
engineering.  'Microservices' and 'Cloud' were beginning to take hold as the new way to build web applications for high
volume web services.   I was introduced to [The 12 Factor App](https://12factor.net/) along with 'Spring Boot',
and the rest is history.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
As a developer, suddenly I had a roadmap and a toolset to build almost anything on the web.  It was also fast
and scalable, and I was no longer asking _how and what_ can we build, but _**where and when**_ can we build it?

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
This marks the start of a series of musings exploring each of the twelve factors and how they
have related to my journey through enterprise software development.  Next time I will discuss the importance of
[codebase](https://12factor.net/codebase) tracing and how difficult development can be if we fall short of this factor. 
