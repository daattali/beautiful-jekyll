---
layout: post
title: A Timeless Software Developer Reading List
subtitle: The 24 books that I recommend to software developers
permalink: dev-reading-list
image: /img-posts/devreadinglist-0-thumb.png
modified-date:
---

Learning software development is a fundamental skill in today's world.
I hoped to share a list of books for understanding and growing in software development. I have shared parts of this list with team members who join my team or who I mentor.

----

I grouped these books by area of growth, as opposed to specific language or facet of software development. There's a continuium of experience and facets of software engineering touched by each book (e.g. [Javascript: The Good Parts][link-devreadinglist-Javascript-The-Good-Parts] is in the "Everyone" section. This language specific book shares Javascript principles that backend developers (that may never touch Javascript) would find interesting).


> “Learning to write programs stretches your mind, and helps you think better, creates a way of thinking about things that I think is helpful in all domains.”
—Bill Gates

How this article is organized:

- [For Everyone](#for-everyone) - I'd recommend for every man, woman and child who's learning about software
- [For Career Growth](#for-career-growth) - I'd recommend for people thinking about their career growth
- [For Technical Growth](#for-technical-growth) - I'd recommend for people thinking about their technical growth

{::options parse_block_html="true" /}

----

## For Everyone

Most of these books have a higher level of legibility and I believe are great introductions to subjects relevant to software development.

##### Cal Newport: [So Great They Can't Ignore You][link-devreadinglist-So-Great-They-Cant-Ignore-You]

{% capture Intro-So-Great-They-Cant-Ignore-You %}
In this eye-opening account, Cal Newport debunks the long-held belief that "follow your passion" is good advice. Not only is the cliché flawed -- preexisting passions are rare and have little to do with how most people end up loving their work -- but it can also be dangerous, leading to anxiety and chronic job hopping.

After making his case against passion, Newport sets out on a quest to discover the reality of how people end up loving what they do. Spending time with organic farmers, venture capitalists, screenwriters, freelance computer programmers, and others who admitted to deriving great satisfaction from their work, Newport uncovers the strategies they used and the pitfalls they avoided in developing their compelling careers.

Matching your job to a preexisting passion does not matter, he reveals. Passion comes after you put in the hard work to become excellent at something valuable, not before.
In other words, what you do for a living is much less important than how you do it.

With a title taken from the comedian Steve Martin, who once said his advice for aspiring entertainers was to "be so good they can't ignore you," Cal Newport's clearly written manifesto is mandatory reading for anyone fretting about what to do with their life, or frustrated by their current job situation and eager to find a fresh new way to take control of their livelihood. He provides an evidence-based blueprint for creating work you love.
SO GOOD THEY CAN'T IGNORE YOU will change the way we think about our careers, happiness, and the crafting of a remarkable life.
{% endcapture %}

<div class="alexa-link">

| {{ Intro-So-Great-They-Cant-Ignore-You | truncatewords: 80 }} | ![So Great They Can't Ignore You][image-devreadinglist-So-Great-They-Cant-Ignore-You] |

</div>

##### Peter Thiel: [Zero to One][link-devreadinglist-Zero-to-One]
{% capture Intro-Zero-to-One %}
If you want to build a better future, you must believe in secrets.

The great secret of our time is that there are still uncharted frontiers to explore and new inventions to create. In Zero to One, legendary entrepreneur and investor Peter Thiel shows how we can find singular ways to create those new things.

Thiel begins with the contrarian premise that we live in an age of technological stagnation, even if we’re too distracted by shiny mobile devices to notice. Information technology has improved rapidly, but there is no reason why progress should be limited to computers or Silicon Valley. Progress can be achieved in any industry or area of business. It comes from the most important skill that every leader must master: learning to think for yourself.

Doing what someone else already knows how to do takes the world from 1 to n, adding more of something familiar. But when you do something new, you go from 0 to 1. The next Bill Gates will not build an operating system. The next Larry Page or Sergey Brin won’t make a search engine. Tomorrow’s champions will not win by competing ruthlessly in today’s marketplace. They will escape competition altogether, because their businesses will be unique.

Zero to One presents at once an optimistic view of the future of progress in America and a new way of thinking about innovation: it starts by learning to ask the questions that lead you to find value in unexpected places.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Zero-to-One | truncatewords: 80}} | ![Zero to One][image-devreadinglist-Zero-to-One] |

</div>

##### Gang of Four: [Design Patterns][link-devreadinglist-Design-Patterns]
{% capture Intro-Design-Patterns %}
Capturing a wealth of experience about the design of object-oriented software, four top-notch designers present a catalog of simple and succinct solutions to commonly occurring design problems. Previously undocumented, these 23 patterns allow designers to create more flexible, elegant, and ultimately reusable designs without having to rediscover the design solutions themselves.

The authors begin by describing what patterns are and how they can help you design object-oriented software. They then go on to systematically name, explain, evaluate, and catalog recurring designs in object-oriented systems. With Design Patterns as your guide, you will learn how these important patterns fit into the software development process, and how you can leverage them to solve your own design problems most efficiently.

Each pattern describes the circumstances in which it is applicable, when it can be applied in view of other design constraints, and the consequences and trade-offs of using the pattern within a larger design. All patterns are compiled from real systems and are based on real-world examples. Each pattern also includes code that demonstrates how it may be implemented in object-oriented programming languages like C++ or Smalltalk.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Design-Patterns | truncatewords: 60}} | ![War of Art][image-devreadinglist-Design-Patterns] |

</div>

##### Thomas Cormen, et al.: [Introduction To Algorithms][link-devreadinglist-Introduction-To-Algorithms]
{% capture Intro-Introduction-To-Algorithms %}
The latest edition of the essential text and professional reference, with substantial new material on such topics as vEB trees, multithreaded algorithms, dynamic programming, and edge-based flow.
Some books on algorithms are rigorous but incomplete; others cover masses of material but lack rigor. Introduction to Algorithms uniquely combines rigor and comprehensiveness. The book covers a broad range of algorithms in depth, yet makes their design and analysis accessible to all levels of readers. Each chapter is relatively self-contained and can be used as a unit of study. The algorithms are described in English and in a pseudocode designed to be readable by anyone who has done a little programming. The explanations have been kept elementary without sacrificing depth of coverage or mathematical rigor.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Introduction-To-Algorithms | truncatewords: 60}} | ![Introduction To Algorithms][image-devreadinglist-Introduction-To-Algorithms] |

</div>

##### Joshua Blochs: [Effective Java][link-devreadinglist-Effective-Java]
{% capture Intro-Effective-Java %}
The Definitive Guide to Java Platform Best Practices–Updated for Java 7, 8, and 9
Java has changed dramatically since the previous edition of Effective Java was published shortly after the release of Java 6. This Jolt award-winning classic has now been thoroughly updated to take full advantage of the latest language and library features. The support in modern Java for multiple paradigms increases the need for specific best-practices advice, and this book delivers.
As in previous editions, each chapter of Effective Java, Third Edition, consists of several “items,” each presented in the form of a short, stand-alone essay that provides specific advice, insight into Java platform subtleties, and updated code examples. The comprehensive descriptions and explanations for each item illuminate what to do, what not to do, and why.
The third edition covers language and library features added in Java 7, 8, and 9, including the functional programming constructs that were added to its object-oriented roots. Many new items have been added, including a chapter devoted to lambdas and streams.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Effective-Java | truncatewords: 60}} | ![Design Patterns][image-devreadinglist-Effective-Java] |

</div>

##### Steven Pressfield: [War of Art][link-devreadinglist-War-of-Art]
{% capture Intro-War-of-Art %}
Think of The War of Art as tough love... for yourself.

Since 2002, The War of Art has inspired people around the world to defeat "Resistance"; to recognize and knock down dream-blocking barriers and to silence the naysayers within us.Resistance kicks everyone's butt, and the desire to defeat it is equally as universal. The War of Art identifies the enemy that every one of us must face, outlines a battle plan to conquer this internal foe, then pinpoints just how to achieve the greatest success.Though it was written for writers, it has been embraced by business entrepreneurs, actors, dancers, painters, photographers, filmmakers, military service members and thousands of others around the world.
{% endcapture %}
<div class="alexa-link">

| {{Intro-War-of-Art | truncatewords: 60}} | ![Effective Java][image-devreadinglist-War-of-Art] |

</div>

##### Steve Krug: [Don't Make Me Think][link-devreadinglist-Dont-Make-Me-Think]
{% capture Intro-Dont-Make-Me-Think %}
Since Don’t Make Me Think was first published in 2000, hundreds of thousands of Web designers and developers have relied on usability guru Steve Krug’s guide to help them understand the principles of intuitive navigation and information design. Witty, commonsensical, and eminently practical, it’s one of the best-loved and most recommended books on the subject.

Now Steve returns with fresh perspective to reexamine the principles that made Don’t Make Me Think a classic–with updated examples and a new chapter on mobile usability. And it’s still short, profusely illustrated…and best of all–fun to read.

If you’ve read it before, you’ll rediscover what made Don’t Make Me Think so essential to Web designers and developers around the world. If you’ve never read it, you’ll see why so many people have said it should be required reading for anyone working on Web sites.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Dont-Make-Me-Think | truncatewords: 60}} | ![Don't Make Me Think][image-devreadinglist-Dont-Make-Me-Think] |

</div>

##### Douglas Crockford: [Javascript: The Good Parts][link-devreadinglist-Javascript-The-Good-Parts]
{% capture Intro-Javascript-The-Good-Parts %}
Most programming languages contain good and bad parts, but JavaScript has more than its share of the bad, having been developed and released in a hurry before it could be refined. This authoritative book scrapes away these bad features to reveal a subset of JavaScript that's more reliable, readable, and maintainable than the language as a whole—a subset you can use to create truly extensible and efficient code.

Considered the JavaScript expert by many people in the development community, author Douglas Crockford identifies the abundance of good ideas that make JavaScript an outstanding object-oriented programming language-ideas such as functions, loose typing, dynamic objects, and an expressive object literal notation. Unfortunately, these good ideas are mixed in with bad and downright awful ideas, like a programming model based on global variables.

When Java applets failed, JavaScript became the language of the Web by default, making its popularity almost completely independent of its qualities as a programming language.
{% endcapture %}

<div class="alexa-link">

| {{Intro-Javascript-The-Good-Parts | truncatewords: 60}} | ![Javascript: The Good Parts][image-devreadinglist-Javascript-The-Good-Parts] |

</div>

##### Paul Graham: [Hackers and Painters][link-devreadinglist-Hackers-and-Painters]
{% capture Intro-Hackers-and-Painters %}
We are living in the computer age, in a world increasingly designed and engineered by computer programmers and software designers, by people who call themselves hackers. Who are these people, what motivates them, and why should you care?

Consider these facts: Everything around us is turning into computers. Your typewriter is gone, replaced by a computer. Your phone has turned into a computer. So has your camera. Soon your TV will. Your car was not only designed on computers, but has more processing power in it than a room-sized mainframe did in 1970. Letters, encyclopedias, newspapers, and even your local store are being replaced by the Internet.

Hackers & Painters: Big Ideas from the Computer Age, by Paul Graham, explains this world and the motivations of the people who occupy it. In clear, thoughtful prose that draws on illuminating historical examples, Graham takes readers on an unflinching exploration into what he calls "an intellectual Wild West."
{% endcapture %}
<div class="alexa-link">

| {{Intro-Hackers-and-Painters | truncatewords: 60}} | ![Hackers and Painters][image-devreadinglist-Hackers-and-Painters] |

</div>

##### Robert Martin: [Clean Code][link-devreadinglist-Clean-Code]
{% capture Intro-Clean-Code %}
Even bad code can function. But if code isn’t clean, it can bring a development organization to its knees. Every year, countless hours and significant resources are lost because of poorly written code. But it doesn’t have to be that way.

Noted software expert Robert C. Martin presents a revolutionary paradigm with Clean Code: A Handbook of Agile Software Craftsmanship . Martin has teamed up with his colleagues from Object Mentor to distill their best agile practice of cleaning code 'on the fly' into a book that will instill within you the values of a software craftsman and make you a better programmer–but only if you work at it.

What kind of work will you be doing? You’ll be reading code–lots of code. And you will be challenged to think about what’s right about that code, and what’s wrong with it. More importantly, you will be challenged to reassess your professional values and your commitment to your craft.

Clean Code is divided into three parts. The first describes the principles, patterns, and practices of writing clean code. The second part consists of several case studies of increasing complexity. Each case study is an exercise in cleaning up code–of transforming a code base that has some problems into one that is sound and efficient. The third part is the payoff: a single chapter containing a list of heuristics and “smells” gathered while creating the case studies. The result is a knowledge base that describes the way we think when we write, read, and clean code.

Readers will come away from this book understanding
How to tell the difference between good and bad code
How to write good code and how to transform bad code into good code
How to create good names, good functions, good objects, and good classes
How to format code for maximum readability
How to implement complete error handling without obscuring code logic
How to unit test and practice test-driven development
This book is a must for any developer, software engineer, project manager, team lead, or systems analyst with an interest in producing better code.
{% endcapture %}
<div class="alexa-link">

| {{ Intro-Clean-Code | truncatewords: 70 }} | ![Clean Code][image-devreadinglist-Clean-Code] |

</div>

----

## For Career Growth

Most of the books here should be legible for those who have worked in software for a (few) years.

##### Michael Lopp: [Being Geek: The Software Developer's Career Handbook ][link-devreadinglist-Being-Geek]
{% capture Intro-Being-Geek %}
As a software engineer, you recognize at some point that there's much more to your career than dealing with code. Is it time to become a manager? Tell your boss he’s a jerk? Join that startup? Author Michael Lopp recalls his own make-or-break moments with Silicon Valley giants such as Apple, Netscape, and Symantec in Being Geek -- an insightful and entertaining book that will help you make better career decisions.
With more than 40 standalone stories, Lopp walks through a complete job life cycle, starting with the job interview and ending with the realization that it might be time to find another gig.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Being-Geek | truncatewords: 60}} | ![Being Geek: The Software Developer's Career Handbook][image-devreadinglist-Being-Geek] |

</div>

##### Reid Hoffman, Ben Casnocha: [Start-up of You][link-devreadinglist-Start-up-of-You]
{% capture Intro-Start-up-of-You %}
A blueprint for thriving in your job and building a career by applying the lessons of Silicon Valley’s most innovative entrepreneurs.
LinkedIn cofounder and chairman Reid Hoffman and author Ben Casnocha show how to accelerate your career in today’s competitive world. The key is to manage your career as if it were a start-up business: a living, breathing, growing start-up of you.
Why? Start-ups—and the entrepreneurs who run them—are nimble. They invest in themselves. They build their professional networks. They take intelligent risks. They make uncertainty and volatility work to their advantage.
These are the very same skills professionals need to get ahead today.
{% endcapture %}

<div class="alexa-link">

| {{Intro-Start-up-of-You | truncatewords: 60}} | ![Start-up of You][image-devreadinglist-Start-up-of-You] |

</div>

##### Tom DeMarco, Tim Lister: [Peopleware Productive Projects and Teams][link-devreadinglist-Peopleware]
{% capture Intro-Peopleware %}
Few books in computing have had as profound an influence on software management as Peopleware . The unique insight of this longtime best seller is that the major issues of software development are human, not technical. They’re not easy issues; but solve them, and you’ll maximize your chances of success.
For this third edition, the authors have added six new chapters and updated the text throughout, bringing it in line with today’s development environments and challenges. For example, the book now discusses pathologies of leadership that hadn’t previously been judged to be pathological; an evolving culture of meetings; hybrid teams made up of people from seemingly incompatible generations; and a growing awareness that some of our most common tools are more like anchors than propellers. Anyone who needs to manage a software project or software organization will find invaluable advice throughout the book.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Peopleware | truncatewords: 60}} | ![Peopleware Productive Projects and Teams][image-devreadinglist-Peopleware] |

</div>

##### Michael Lopp: [Managing Humans Biting and Humorous Tales of a Software Engineering Manager][link-devreadinglist-Managing-Humans]
{% capture Intro-Managing-Humans %}
Read hilarious stories with serious lessons that Michael Lopp extracts from his varied and sometimes bizarre experiences as a manager at Apple, Pinterest, Palantir, Netscape, Symantec, Slack, and Borland. Many of the stories first appeared in primitive form in Lopp’s perennially popular blog, Rands in Repose. The Third Edition of Managing Humans contains a whole new season of episodes from the ongoing saga of Lopp's adventures in Silicon Valley, together with classic episodes remastered for high fidelity and freshness.
Whether you're an aspiring manager, a current manager, or just wondering what the heck a manager does all day, there is a story in this book that will speak to you—and help you survive and prosper amid the general craziness of dysfunctional bright people caught up in the chase of riches and power. Scattered in repose among these manic misfits are managers, an even stranger breed of people who, through a mystical organizational ritual, have been given power over the futures and the bank accounts of many others.
Lopp's straight-from-the-hip style is unlike that of any other writer on management and leadership. He pulls no punches and tells stories he probably shouldn't. But they are magically instructive and yield Lopp’s trenchant insights on leadership that cut to the heart of the matter—whether it's dealing with your boss, handling a slacker, hiring top guns, or seeing a knotty project through to completion.
Writing code is easy. Managing humans is not. You need a book to help you do it, and this is it.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Managing-Humans | truncatewords: 60}} | ![Managing Humans Biting and Humorous Tales of a Software Engineering Manager][image-devreadinglist-Managing-Humans] |

</div>

##### Patrick Lencioni: [Five Dysfunctions of Teams][link-devreadinglist-Five-Dysfunctions-of-Teams]
{% capture Intro-Five-Dysfunctions-of-Teams %}
In The Five Dysfunctions of a Team Patrick Lencioni once again offers a leadership fable that is as enthralling and instructive as his first two best-selling books, The Five Temptations of a CEO and The Four Obsessions of an Extraordinary Executive. This time, he turns his keen intellect and storytelling power to the fascinating, complex world of teams.
Kathryn Petersen, Decision Tech's CEO, faces the ultimate leadership crisis: Uniting a team in such disarray that it threatens to bring down the entire company. Will she succeed? Will she be fired? Will the company fail? Lencioni's utterly gripping tale serves as a timeless reminder that leadership requires as much courage as it does insight.
Throughout the story, Lencioni reveals the five dysfunctions which go to the very heart of why teams even the best ones-often struggle. He outlines a powerful model and actionable steps that can be used to overcome these common hurdles and build a cohesive, effective team. Just as with his other books, Lencioni has written a compelling fable with a powerful yet deceptively simple message for all those who strive to be exceptional team leaders.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Five-Dysfunctions-of-Teams | truncatewords: 60}} | ![Five Dysfunctions of Teams][image-devreadinglist-Five-Dysfunctions-of-Teams] |

</div>

##### Patrick Lencioni: [The Advantage][link-devreadinglist-The-Advantage]
{% capture Intro-The-Advantage %}
There is a competitive advantage out there, arguably more powerful than any other. Is it superior strategy? Faster innovation? Smarter employees? No, New York Times best-selling author, Patrick Lencioni, argues that the seminal difference between successful companies and mediocre ones has little to do with what they know and how smart they are and more to do with how healthy they are. In this book, Lencioni brings together his vast experience and many of the themes cultivated in his other best-selling books and delivers a first: a cohesive and comprehensive exploration of the unique advantage organizational health provides.
Simply put, an organization is healthy when it is whole, consistent and complete, when its management, operations and culture are unified.  Healthy organizations outperform their counterparts, are free of politics and confusion and provide an environment where star performers never want to leave. Lencioni’s first non-fiction book provides leaders with a groundbreaking, approachable model for achieving organizational health—complete with stories, tips and anecdotes from his experiences consulting to some of the nation’s leading organizations. In this age of informational ubiquity and nano-second change, it is no longer enough to build a competitive advantage based on intelligence alone. The Advantage provides a foundational construct for conducting business in a new way—one that maximizes human potential and aligns the organization around a common set of principles.
{% endcapture %}

<div class="alexa-link">

| {{Intro-The-Advantage | truncatewords: 60}} | ![The Advantage][image-devreadinglist-The-Advantage] |

</div>

----

## For Technical Growth

Most of the books here should be legible for those who have worked in software for a (few) years.

##### Jason Fried, DHH: [Rework][link-devreadinglist-Rework]
{% capture Intro-Rework %}
Most business books give you the same old advice: Write a business plan, study the competition, seek investors, yadda yadda. If you're looking for a book like that, put this one back on the shelf.
Read it and you'll know why plans are actually harmful, why you don't need outside investors, and why you're better off ignoring the competition. The truth is, you need less than you think. You don't need to be a workaholic. You don't need to staff up. You don't need to waste time on paperwork or meetings. You don't even need an office. Those are all just excuses.
What you really need to do is stop talking and start working. This book shows you the way. You'll learn how to be more productive, how to get exposure without breaking the bank, and tons more counterintuitive ideas that will inspire and provoke you.
With its straightforward language and easy-is-better approach, Rework is the perfect playbook for anyone who’s ever dreamed of doing it on their own. Hardcore entrepreneurs, small-business owners, people stuck in day jobs they hate, victims of "downsizing," and artists who don’t want to starve anymore will all find valuable guidance in these pages.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Rework | truncatewords: 60}} | ![Rework][image-devreadinglist-Rework] |

</div>

##### Martin Fowler, et al.: [Refactoring][link-devreadinglist-Refactoring]
{% capture Intro-Refactoring %}
As the application of object technology--particularly the Java programming language--has become commonplace, a new problem has emerged to confront the software development community. Significant numbers of poorly designed programs have been created by less-experienced developers, resulting in applications that are inefficient and hard to maintain and extend. Increasingly, software system professionals are discovering just how difficult it is to work with these inherited, "non-optimal" applications. For several years, expert-level object programmers have employed a growing collection of techniques to improve the structural integrity and performance of such existing software programs. Referred to as "refactoring," these practices have remained in the domain of experts because no attempt has been made to transcribe the lore into a form that all developers could use. . .until now. In Refactoring: Improving the Design of Existing Code, renowned object technology mentor Martin Fowler breaks new ground, demystifying these master practices and demonstrating how software practitioners can realize the significant benefits of this new process.
With proper training a skilled system designer can take a bad design and rework it into well-designed, robust code. In this book, Martin Fowler shows you where opportunities for refactoring typically can be found, and how to go about reworking a bad design into a good one. Each refactoring step is simple--seemingly too simple to be worth doing. Refactoring may involve moving a field from one class to another, or pulling some code out of a method to turn it into its own method, or even pushing some code up or down a hierarchy. While these individual steps may seem elementary, the cumulative effect of such small changes can radically improve the design. Refactoring is a proven way to prevent software decay.
In addition to discussing the various techniques of refactoring, the author provides a detailed catalog of more than seventy proven refactorings with helpful pointers that teach you when to apply them; step-by-step instructions for applying each refactoring; and an example illustrating how the refactoring works. The illustrative examples are written in Java, but the ideas are applicable to any object-oriented programming language.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Refactoring | truncatewords: 60}} | ![Refactoring][image-devreadinglist-Refactoring] |

</div>

##### Andrew Hunt, David Thomas: [Pragmatic Programmer][link-devreadinglist-Pragmatic-Programmer]
{% capture Intro-Pragmatic-Programmer %}
Straight from the programming trenches, The Pragmatic Programmer cuts through the increasing specialization and technicalities of modern software development to examine the core process--taking a requirement and producing working, maintainable code that delights its users. It covers topics ranging from personal responsibility and career development to architectural techniques for keeping your code flexible and easy to adapt and reuse. Read this book, and youll learn how to *Fight software rot; *Avoid the trap of duplicating knowledge; *Write flexible, dynamic, and adaptable code; *Avoid programming by coincidence; *Bullet-proof your code with contracts, assertions, and exceptions; *Capture real requirements; *Test ruthlessly and effectively; *Delight your users; *Build teams of pragmatic programmers; and *Make your developments more precise with automation. Written as a series of self-contained sections and filled with entertaining anecdotes, thoughtful examples, and interesting analogies, The Pragmatic Programmer illustrates the best practices and major pitfalls of many different aspects of software development.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Pragmatic-Programmer | truncatewords: 60}} | ![Pragmatic Programmer][image-devreadinglist-Pragmatic-Programmer] |

</div>

##### Robert Martin: [Clean Architecture][link-devreadinglist-Clean-Architecture]
{% capture Intro-Clean-Architecture %}
Clean Architecture is essential reading for every current or aspiring software architect, systems analyst, system designer, and software manager–and for every programmer who must execute someone else’s designs.
By applying universal rules of software architecture, you can dramatically improve developer productivity throughout the life of any software system. Now, building upon the success of his best-selling books Clean Code and The Clean Coder, legendary software craftsman Robert C. Martin (“Uncle Bob”) reveals those rules and helps you apply them.
Martin’s Clean Architecture doesn’t merely present options. Drawing on over a half-century of experience in software environments of every imaginable type, Martin tells you what choices to make and why they are critical to your success. As you’ve come to expect from Uncle Bob, this book is packed with direct, no-nonsense solutions for the real challenges you’ll face–the ones that will make or break your projects.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Clean-Architecture | truncatewords: 60}} | ![Clean Architecture][image-devreadinglist-Clean-Architecture] |

</div>

##### Martin Kleppman: [Designing Data-Intensive Applications][link-devreadinglist-Designing-Data-Intensive-Applications]
{% capture Intro-Designing-Data-Intensive-Applications %}
Data is at the center of many challenges in system design today. Difficult issues need to be figured out, such as scalability, consistency, reliability, efficiency, and maintainability. In addition, we have an overwhelming variety of tools, including relational databases, NoSQL datastores, stream or batch processors, and message brokers. What are the right choices for your application? How do you make sense of all these buzzwords?
In this practical and comprehensive guide, author Martin Kleppmann helps you navigate this diverse landscape by examining the pros and cons of various technologies for processing and storing data. Software keeps changing, but the fundamental principles remain the same. With this book, software engineers and architects will learn how to apply those ideas in practice, and how to make full use of data in modern applications.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Designing-Data-Intensive-Applications | truncatewords: 60}} | ![Designing Data-Intensive Applications][image-devreadinglist-Designing-Data-Intensive-Applications] |

</div>

##### Niall Richard Murphy, et al.: [Site Reliability Engineering][link-devreadinglist-Site-Reliability-Engineering]
{% capture Intro-Site-Reliability-Engineering %}
The overwhelming majority of a software system’s lifespan is spent in use, not in design or implementation. So, why does conventional wisdom insist that software engineers focus primarily on the design and development of large-scale computing systems?
In this collection of essays and articles, key members of Google’s Site Reliability Team explain how and why their commitment to the entire lifecycle has enabled the company to successfully build, deploy, monitor, and maintain some of the largest software systems in the world. You’ll learn the principles and practices that enable Google engineers to make systems more scalable, reliable, and efficient—lessons directly applicable to your organization.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Site-Reliability-Engineering | truncatewords: 60}} | ![Site Reliability Engineering][image-devreadinglist-Site-Reliability-Engineering] |

</div>

##### Gregor Hohpe, Bobby Woolf: [Enterprise Integration Patterns][link-devreadinglist-Enterprise-Integration-Patterns]
{% capture Intro-Enterprise-Integration-Patterns %}
Enterprise Integration Patterns provides an invaluable catalog of sixty-five patterns, with real-world solutions that demonstrate the formidable of messaging and help you to design effective messaging solutions for your enterprise.
The authors also include examples covering a variety of different integration technologies, such as JMS, MSMQ, TIBCO ActiveEnterprise, Microsoft BizTalk, SOAP, and XSL. A case study describing a bond trading system illustrates the patterns in practice, and the book offers a look at emerging standards, as well as insights into what the future of enterprise integration might hold.
This book provides a consistent vocabulary and visual notation framework to describe large-scale integration solutions across many technologies. It also explores in detail the advantages and limitations of asynchronous messaging architectures. The authors present practical advice on designing code that connects an application to a messaging system, and provide extensive information to help you determine when to send a message, how to route it to the proper destination, and how to monitor the health of a messaging system. If you want to know how to manage, monitor, and maintain a messaging system once it is in use, get this book.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Enterprise-Integration-Patterns | truncatewords: 60}} | ![Enterprise Integration Patterns][image-devreadinglist-Enterprise-Integration-Patterns] |

</div>

##### Gene Kim, et al.: [Phonenix Project][link-devreadinglist-Phoenix-Project]
{% capture Intro-Phoenix-Project %}
Five years after this sleeper hit took on the world of IT and flipped it on its head, the 5th Anniversary Edition of The Phoenix Project continues to guide IT in the DevOps revolution. In this newly updated and expanded edition of the bestselling The Phoenix Project, co-author Gene Kim includes a new afterword and a deeper delve into the Three Ways as described in The DevOps Handbook.
Bill, an IT manager at Parts Unlimited, has been tasked with taking on a project critical to the future of the business, code named Phoenix Project. But the project is massively over budget and behind schedule. The CEO demands Bill must fix the mess in ninety days or else Bill's entire department will be outsourced.
With the help of a prospective board member and his mysterious philosophy of The Three Ways, Bill starts to see that IT work has more in common with a manufacturing plant work than he ever imagined. With the clock ticking, Bill must organize work flow streamline interdepartmental communications, and effectively serve the other business functions at Parts Unlimited.
In a fast-paced and entertaining style, three luminaries of the DevOps movement deliver a story that anyone who works in IT will recognize. Readers will not only learn how to improve their own IT organizations, they'll never view IT the same way again.
{% endcapture %}
<div class="alexa-link">

| {{Intro-Phoenix-Project | truncatewords: 60}} | ![Phonenix Project][image-devreadinglist-Phoenix-Project] |

</div>

All book images from amazon.com.

<!--
  Startup [not linked]
- Hard thing about Hard Things
- How to Fight a Hydra
Hardware: https://www.goodreads.com/book/show/44882.Code -->

[image-devreadinglist-So-Great-They-Cant-Ignore-You]: /img-posts/devreadinglist-So-Great-They-Cant-Ignore-You.jpg
[image-devreadinglist-So-Great-They-Cant-Ignore-You]: /img-posts/devreadinglist-So-Great-They-Cant-Ignore-You.jpg
[image-devreadinglist-Zero-to-One]: /img-posts/devreadinglist-Zero-to-One.jpg
[image-devreadinglist-Zero-to-One]: /img-posts/devreadinglist-Zero-to-One.jpg
[image-devreadinglist-Design-Patterns]: /img-posts/devreadinglist-Design-Patterns.jpg
[image-devreadinglist-Design-Patterns]: /img-posts/devreadinglist-Design-Patterns.jpg
[image-devreadinglist-Effective-Java]: /img-posts/devreadinglist-Effective-Java.jpg
[image-devreadinglist-Effective-Java]: /img-posts/devreadinglist-Effective-Java.jpg
[image-devreadinglist-War-of-Art]: /img-posts/devreadinglist-War-of-Art.jpg
[image-devreadinglist-War-of-Art]: /img-posts/devreadinglist-War-of-Art.jpg
[image-devreadinglist-Dont-Make-Me-Think]: /img-posts/devreadinglist-Dont-Make-Me-Think.jpg
[image-devreadinglist-Dont-Make-Me-Think]: /img-posts/devreadinglist-Dont-Make-Me-Think.jpg
[image-devreadinglist-Javascript-The-Good-Parts]: /img-posts/devreadinglist-Javascript-The-Good-Parts.jpg
[image-devreadinglist-Javascript-The-Good-Parts]: /img-posts/devreadinglist-Javascript-The-Good-Parts.jpg
[image-devreadinglist-Hackers-and-Painters]: /img-posts/devreadinglist-Hackers-and-Painters.jpg
[image-devreadinglist-Hackers-and-Painters]: /img-posts/devreadinglist-Hackers-and-Painters.jpg
[image-devreadinglist-Introduction-To-Algorithms]: /img-posts/devreadinglist-Introduction-To-Algorithms.jpg
[image-devreadinglist-Introduction-To-Algorithms]: /img-posts/devreadinglist-Introduction-To-Algorithms.jpg
[image-devreadinglist-Clean-Code]: /img-posts/devreadinglist-Clean-Code.jpg
[image-devreadinglist-Clean-Code]: /img-posts/devreadinglist-Clean-Code.jpg
[image-devreadinglist-Being-Geek]: /img-posts/devreadinglist-Being-Geek.jpg
[image-devreadinglist-Being-Geek]: /img-posts/devreadinglist-Being-Geek.jpg
[image-devreadinglist-Peopleware]: /img-posts/devreadinglist-Peopleware.jpg
[image-devreadinglist-Peopleware]: /img-posts/devreadinglist-Peopleware.jpg
[image-devreadinglist-Managing-Humans]: /img-posts/devreadinglist-Managing-Humans.jpg
[image-devreadinglist-Managing-Humans]: /img-posts/devreadinglist-Managing-Humans.jpg
[image-devreadinglist-Start-up-of-You]: /img-posts/devreadinglist-Start-up-of-You.jpg
[image-devreadinglist-Start-up-of-You]: /img-posts/devreadinglist-Start-up-of-You.jpg
[image-devreadinglist-Five-Dysfunctions-of-Teams]: /img-posts/devreadinglist-Five-Dysfunctions-of-Teams.jpg
[image-devreadinglist-Five-Dysfunctions-of-Teams]: /img-posts/devreadinglist-Five-Dysfunctions-of-Teams.jpg
[image-devreadinglist-The-Advantage]: /img-posts/devreadinglist-The-Advantage.jpg
[image-devreadinglist-The-Advantage]: /img-posts/devreadinglist-The-Advantage.jpg
[image-devreadinglist-Rework]: /img-posts/devreadinglist-Rework.jpg
[image-devreadinglist-Rework]: /img-posts/devreadinglist-Rework.jpg
[image-devreadinglist-Refactoring]: /img-posts/devreadinglist-Refactoring.jpg
[image-devreadinglist-Refactoring]: /img-posts/devreadinglist-Refactoring.jpg
[image-devreadinglist-Pragmatic-Programmer]: /img-posts/devreadinglist-Pragmatic-Programmer.jpg
[image-devreadinglist-Pragmatic-Programmer]: /img-posts/devreadinglist-Pragmatic-Programmer.jpg
[image-devreadinglist-Clean-Architecture]: /img-posts/devreadinglist-Clean-Architecture.jpg
[image-devreadinglist-Clean-Architecture]: /img-posts/devreadinglist-Clean-Architecture.jpg
[image-devreadinglist-Designing-Data-Intensive-Applications]: /img-posts/devreadinglist-Designing-Data-Intensive-Applications.jpg
[image-devreadinglist-Designing-Data-Intensive-Applications]: /img-posts/devreadinglist-Designing-Data-Intensive-Applications.jpg
[image-devreadinglist-Site-Reliability-Engineering]: /img-posts/devreadinglist-Site-Reliability-Engineering.jpg
[image-devreadinglist-Site-Reliability-Engineering]: /img-posts/devreadinglist-Site-Reliability-Engineering.jpg
[image-devreadinglist-Enterprise-Integration-Patterns]: /img-posts/devreadinglist-Enterprise-Integration-Patterns.jpg
[image-devreadinglist-Enterprise-Integration-Patterns]: /img-posts/devreadinglist-Enterprise-Integration-Patterns.jpg
[image-devreadinglist-Phoenix-Project]: /img-posts/devreadinglist-Phoenix-Project.jpg
[image-devreadinglist-Phoenix-Project]: /img-posts/devreadinglist-Phoenix-Project.jpg

[link-devreadinglist-So-Great-They-Cant-Ignore-You]: https://www.amazon.com/Good-They-Cant-Ignore-You-ebook/dp/B0076DDBJ6/
[link-devreadinglist-Zero-to-One]: https://www.amazon.com/Zero-One-Notes-Startups-Future-ebook/dp/B00J6YBOFQ/
[link-devreadinglist-Design-Patterns]: https://www.amazon.com/Design-Patterns-Object-Oriented-Addison-Wesley-Professional-ebook/dp/B000SEIBB8/
[link-devreadinglist-Effective-Java]: https://www.amazon.com/Effective-Java-Joshua-Bloch-ebook/dp/B078H61SCH/
[link-devreadinglist-War-of-Art]: https://www.amazon.com/War-Art-Steven-Pressfield-ebook/dp/B007A4SDCG
[link-devreadinglist-Dont-Make-Me-Think]: https://www.amazon.com/Dont-Make-Think-Revisited-Usability-ebook/dp/B00HJUBRPG/
[link-devreadinglist-Javascript-The-Good-Parts]: https://www.amazon.com/JavaScript-Good-Parts-ebook/dp/B0026OR2ZY/
[link-devreadinglist-Hackers-and-Painters]: https://www.amazon.com/Hackers-Painters-Big-Ideas-Computer-ebook/dp/B0026OR2NQ/
[link-devreadinglist-Introduction-To-Algorithms]: https://www.amazon.com/Introduction-Algorithms-Press-Thomas-Cormen-ebook/dp/B007CNRCAO/
[link-devreadinglist-Clean-Code]: https://www.amazon.com/Clean-Code-Handbook-Software-Craftsmanship-ebook/dp/B001GSTOAM/
[link-devreadinglist-Being-Geek]: https://www.amazon.com/Being-Geek-Software-Developers-Handbook-ebook/dp/B003XDUCEU/
[link-devreadinglist-Peopleware]: https://www.amazon.com/Peopleware-Productive-Projects-Tom-DeMarco-ebook/dp/B00DY5A8X2/
[link-devreadinglist-Managing-Humans]: https://www.amazon.com/Managing-Humans-Humorous-Software-Engineering-ebook/dp/B01J53IE1O
[link-devreadinglist-Start-up-of-You]: https://www.amazon.com/Start-up-You-Future-Yourself-Transform-ebook/dp/B0050DIWHU
[link-devreadinglist-Five-Dysfunctions-of-Teams]: https://www.amazon.com/Five-Dysfunctions-Team-Leadership-Lencioni-ebook/dp/B006960LQW/
[link-devreadinglist-The-Advantage]: https://www.amazon.com/Advantage-Enhanced-Organizational-Everything-Business-ebook/dp/B006ORWT3Y/
[link-devreadinglist-Rework]: https://www.amazon.com/Rework-Jason-Fried-ebook/dp/B002MUAJ2A/
[link-devreadinglist-Refactoring]: https://www.amazon.com/Refactoring-Improving-Existing-Addison-Wesley-Technology-ebook/dp/B007WTFWJ6/
[link-devreadinglist-Pragmatic-Programmer]: https://www.amazon.com/Pragmatic-Programmer-Journeyman-Master/dp/020161622X
[link-devreadinglist-Clean-Architecture]: https://www.amazon.com/Clean-Architecture-Craftsmans-Software-Structure-ebook/dp/B075LRM681
[link-devreadinglist-Designing-Data-Intensive-Applications]: https://www.amazon.com/Designing-Data-Intensive-Applications-Reliable-Maintainable-ebook/dp/B06XPJML5D/
[link-devreadinglist-Site-Reliability-Engineering]: https://www.amazon.com/Site-Reliability-Engineering-Production-Systems-ebook/dp/B01DCPXKZ6
[link-devreadinglist-Enterprise-Integration-Patterns]: https://www.amazon.com/Enterprise-Integration-Patterns-Designing-Addison-Wesley-ebook/dp/B007MQLL4E/
[link-devreadinglist-Phoenix-Project]: https://www.amazon.com/Phoenix-Project-DevOps-Helping-Business-ebook/dp/B078Y98RG8/ref=sr_1_1?s=digital-

