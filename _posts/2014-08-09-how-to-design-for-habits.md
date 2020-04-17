---
layout: post
title: How to Design for Habit
subtitle: The Secret to Making Great Products
permalink: behavioral-antipatterns-product-design
image: https://raw.githubusercontent.com/fxchen/frankc/master/2014%20July/spiral.jpg
modified-date: Sep 16, 2018
---

Let’s say you created a product. A product that solves a common specific problem for many people. Yet, after a sign-up or an application download for your solution, people continue to have the same problem and <em>do not use your product</em>.
<h2 id="why">“Why?!”</h2>
Why might someone continue to have a problem or use an inferior solution? These people <em>already</em> have routines based around their current solution. They may not even recognize they have a default routine. Help them use your product by developing new habits around <strong>what they already do</strong>. [1]
<blockquote>Design is making the unintuitive intuitive.

<em>John Maeda</em></blockquote>
Designing products that people use is a process. Ideally, this process starts as a small conscious change in their routine and incrementally grows until the product becomes the individual’s go-to. At this point, the individual will have developed a new default <em>routine</em> for their use case.

Any new product trying to solve a person’s existing problem is in a tough position. This person regularly encounters a problem, has noticed it, and does not go out of their way to solve it. This problem has been part of their routine. Part of your solution must make this new behavior intuitive. Your product <em>must</em> fit into what an individual does regularly.

<img src="https://raw.githubusercontent.com/fxchen/frankc/master/2014%20July/spiral.jpg" alt="Penrose stairs are impossible stairs, they descend or ascend to form a continuous loop. This photograph (not Penrose stairs) is beautiful yet disorienting. People probably take these!" />

<em>Penrose stairs are impossible stairs, they descend or ascend to form a continuous loop. This photograph (not Penrose stairs) is beautiful yet disorienting. People probably take these!</em>

This article is about how to best design software products into the routine of what users already do.
<h2 id="whatdopeoplealreadydo">What do people already do?</h2>
Designers should be thinking about how their solution fits into the workflow that <strong>already exists</strong>. Let’s take Evernote, one of my favorite applications. Evernote is a suite of software and services for taking notes that act as “an external brain.”

Bob is a student who has a problem with synchronizing notes across devices. He currently uses Microsoft Word for class notes. Microsoft Word works pretty well on his Mac, but doesn’t work on his iPhone and doesn’t have a way to synchronize online between his two computers. He wants to address some pain points:
<ul>
  <li>Bob wants to take notes.</li>
  <li>Bob wants to synchonize his notes online.</li>
  <li>Bob wants to be able to change devices and take notes.</li>
  <li>Bob wants to be able to take notes with consistent formatting.</li>
</ul>
<strong>The principal of least surpise:</strong> the person using the application should not be surprised by a software’s behavior.

The note taking process in Evernote is straightforward (see the “Getting Started” guide <a href="https://evernote.com/getting_started">here</a>). Bob might install Evernote on each device (PC, Mac, iPhones). Notes synchronize automatically between each of these devices (without the person needing to worry about copying or emailing the document). When Bob opens any note, the formatting stays consistent (Evernote looks the same and does not add additional “paper” formatting Word might).

The best software software should delight in only making small suprises— surprises that are subtle and seem <em>intuitive</em>. Intuition = non-intrusiveness. Design should give the right amount of information to guide the user through their interface.

A few years ago, Evernote released a usage graph they called the smile graph:

<img src="https://raw.githubusercontent.com/fxchen/frankc/master/2014%20July/evernote-smile-graph.png" alt="Evernote Smile Graph" />

In this graph, during the first year of install, the number of users that use Evernote on a monthly basis drops off from over 40% to 20% . Then over the course of the next two years, the percentage of individuals that use this tool increases. Many software products have a graph that is strictly decreasing. Evernote’s monthly user graph is different— over the course of the tool’s lifetime, the number of people actually increases over time. Interpretation: people start to recognize how useful Evernote. Bob may start using the tool even though they did not use the tool at first.

Software designers should design their tools to be adopted by hooking into what the user already does.
<h2 id="fitintoworkflows">Fit into workflows</h2>
<blockquote>We are what we repeatedly do

<em>Aristotle</em></blockquote>
Starting to use a new application requires you to think about how to start a new habit. Experts say it generally takes 21 days to establish a new habit [2]. In the world today, the world of applications, tv, consistent and constant notifications, and a bleed between work and non-work situations, new software products live in a tenuous spot. These habits compete with the automatic and established habits we already have.

Similar to creating <a href="http://j.mp/1tnMQNv">new habits</a> [3], there are effective patterns for software designers to create consistency:
<ul>
  <li><strong>Change environment</strong> Software should change parts of the user’s environment to help them use this new tool.
<ul>
  <li>Software automatically start at system boot-up, so it is consistently at the taskbar.</li>
  <li>Software can add extensions to applications that are already used, such as browsers plug-ins or integrations.</li>
</ul>
</li>
  <li><strong>Notifications</strong> Software can add notifications to mobile phones so users can have another interface to its functionality</li>
  <li><strong>Import</strong> Software should import existing data. With any habit, there is always a bit of inertia to keep using the same pattern as before. Importing data from previous tools should help users bridge the gap between new and old by having all of the older data inside.</li>
  <li><strong>Trigger</strong> Software can change the operating system hook. Upon install, a software can ask a user to change this default to open your product.</li>
</ul>
Exceptions to the rule:
<ul>
  <li><strong>Disruptive technologies</strong> Software may create an entire new market and value network based around some value prior work did not have. <a href="http://j.mp/1tnQwyO">Wiki link</a>. Because no prior behavior or habits existed, this type of software establishes an entire new set of habits.</li>
  <li><strong>Inertia</strong> Software may have a high inertia that makes movement very difficult. Services and platforms build ecosystems around use, and switching is hard. For example, I’ve heard many twenty-somethings whine about Facebook and their dislike of the privacy controls, yet many of these individuals still use the service. “It’s what my friends use.”</li>
</ul>
<h2 id="buildingproductsashabits">Building Products as Habits</h2>
The most innovative and useful products of the future will be those that create lasting behaviors. Designers that understand how products fit into workflows can then better help their users find success in solving problems.

Now I want to ask you all a question:
<ul>
  <li>What tools do you use do you use everyday? What makes them indispensible? (Extra credit: Is it for the same reason you used it in the first place?)</li>
</ul>

Email me! hello [at] frankc.net

<hr />

<strong>References</strong>

[1] BJ Fogg, my mentor and Stanford professor who started the Persuasive Technologies lab, describes a simple model for changing behaviors here <a href="http://j.mp/1zqTGCt">behaviormodel.org</a>. Relying on epiphanies is hard, instead, use these methods to help your users do what they want to do.

[2] Dean, Jeremy, Making Habits, Breaking Habits: Why we do things, why we don’t, and How to Make Any Change Stick. <a href="http://j.mp/UIESiN">Amazon link</a>

[3] Design your Personal Operating System: habits. I discuss the basics of <a href="http://j.mp/1tnMQNv">habit design</a> with lots of references to things I like to read.

<strong>Images</strong>
<ul>
  <li>Spiral of Mind (Flickr) <a href="http://j.mp/1gws4GG">http://j.mp/1gws4GG</a></li>
  <li>Evernote Smile Graph (TechCrunch) <a href="http://j.mp/1xuKiuG">http://j.mp/1xuKiuG</a></li>
</ul>

<figure><img src="https://ga-beacon.appspot.com/UA-36961797-1/sheets/2014-july-design-for-habit" alt="" width="0" height="0" /></figure>
