---
layout: post
title: Writing Workflow
subtitle: Building a System that Lasts
permalink: writing-workflow
image: https://raw.githubusercontent.com/fxchen/frankc/master/2014%20August/screenshot.png
modified-date: Sep 16, 2018
---
<h1 id="writingworkflow:buildingasystemthatlasts"></h1>
This article is about the steps I’ve taken to iterate upon my writing workflow. I’m writing this partially as documentation of how to structure a writing project in the same way as a software project.

This <a href="http://j.mp/1tJ7Gnq">workflow</a> is one under development. I have had problems with writing cadence and writing over the past few months. Writing this workflow is a means to increase the quality and the frequency with which I publish.

<a href="http://www.jamierubin.net">Jamie Todd Rubin</a> is an inspiration with detailed articles on his craft of writing. Jamie is a science fiction author and developer at RAND, who has written consistently about processes for writing and evernote for years [1]. The art of creating process is essential for producing great work in the long term. <a href="http://j.mp/1tnMQNv">Habits</a> that reduce decisions into processes are critical to long term success.

In recent months, I have been writing consistently about 6–8 hours a week, most weeks. However, there have been weeks that I’ve written nothing.

Learning a new skill is hard and uncomfortable. This article is documentation on what’s worked recently and follow-up experiments I’m going to conduct on learning how to write better and more consistently.
<h2 id="tools">Tools</h2>
<img src="https://raw.githubusercontent.com/fxchen/frankc/master/2014%20August/screenshot.png" alt="" />

<em>Screenshot of my writing environment with Marked / Sublime Text</em>
<ul>
  <li><strong><a href="http://git-scm.com">Git</a></strong> is typically used by developers to share and collaborate on code. It provides a nice interface between changes by individual developers and changes to be shared with a group. <strong>Why do I use git for writing?</strong> It gives me the ability to easily pare what articles are published and not yet published, I have nice versioning, and best of all, <a href="https://github.com/fxchen/frankc">github</a> displays Markdown beautifully.</li>
  <li><strong><a href="http://daringfireball.net/projects/markdown">Markdown</a></strong> is a language for writing in plain text that converts to beautiful html. This lets me jot ideas down quickly without the formatting necessary in other formats. Markdown looks like a .txt file with</li>
  <li><strong><a href="http://marked2app.com">Marked</a></strong> is a Markdown tool (by <a href="http://brettterpstra.com">Brett Terpstra</a>) that previews live with every save. This feedback loop has been the most seemless of all the editors I had experimented with. I have the analysis tool open—this gives me a word count and rough complexity metrics.</li>
  <li><strong><a href="http://sublimetext.com">Sublime Text</a></strong> is my favorite editor for development and Markdown. It’s lightweight and infinitely extendible.</li>
</ul>
<h2 id="drafting">Drafting</h2>
<ol>
  <li><strong>Inception</strong> I’ll start a small note inside of /working folder. This start of an article is sometimes placed into the working folder then fleshed out at a later date. Typically, this is a sentence or a paragraph.</li>
  <li><strong>Creation</strong> 2 –3 hour chunk to flesh out this original tiny idea. My goal is to have about 600 - 1000 words initially. Typically I’ll have Marked open and be looking at readability statistics occassionally.</li>
  <li><strong>Editing</strong> I’ll spend another 2 hours to revise the idea for my reader. The initial draft is typically framed for what I find interesting. I frame this writing session for what is interesting for another person.</li>
  <li><strong>Review</strong> I’ll send this out to a few friends for review. Also, I’ll make two fiverr requests for feedback. Fiverr is a service where small tasks (e.g. editing a blog post) can be done for five dollars. Within a few days (as the fiverr requests return), I will integrate the feedback from a fiverr editor.</li>
</ol>
<img src="https://raw.githubusercontent.com/fxchen/frankc/master/2014%20August/gitflow-2x.jpg" alt="" />

<em>Initial sketch of my git workflow for publishing</em>

<strong>Git Flow: (defn) a strict way to use git for project release</strong>. I keep two branches of my git project (development / master) checked out simultaneously. The development branch is private whereas the master branch is public and accessible on github. The only common markdown file is the README.md which lists the <a href="https://github.com/fxchen/frankc">index of my site</a>. [2]
<h2 id="publishing">Publishing</h2>
This is a two part process:
<ol>
  <li>On Github:
<ol>
  <li>Move the article from my /working folder (development branch) to a specific month (the master branch) for organization purposes.</li>
  <li>Check the urls / images. Resize large images and adjust the formatting.</li>
  <li>Push to mainline. This makes the article public!</li>
</ol>
</li>
  <li>On Wordpress:
<ol>
  <li>Export html from Marked and copy paste into Wordpress. This allows Wordpress to do the css styling and allow for an easy transition between Markdown and another blogging platform.</li>
  <li>Correct image urls to final remote locations</li>
  <li>Hit publish!</li>
</ol>
</li>
</ol>
<h2 id="futurework">Future Work</h2>
<ul>
  <li><strong>Automatic daily email / analysis</strong> My initial workflow does not have a good feedback loop outside of the time I spend writing. Since I save each revision on git, it <em>should</em> very easy be able to run analysis on things like word count, complexity (see the above image for Marked application’s reading analysis). Jamie Rubin <a href="http://j.mp/1r671xw">receives an email</a> once a day that summarizes his writing for the day, streak length (currently 400+) and progress towards a goal. I plan to create something similar for my private development git branch.</li>
  <li><strong>Faster feedback loop for external editors</strong> My initial experiment using fiverr as external editors has been too slow. The two editor requests came back in 4 and 8 days, which slows down my publication process. I hoped for a more immediate feedback loop as a forcing function to publish. I plan to try this same process on Amazon’s Mechanical Turk sometime soon.</li>
</ul>
<h2 id="morereading">More Reading</h2>
I have read each of these books recently and have enjoyed them immensely.
<ul>
  <li>Zinsser: <a href="http://j.mp/1BSWRoz">On Writing Well</a></li>
  <li>Stephen King: <a href="http://j.mp/1BSWNVS">On Writing</a></li>
  <li>Austin Kleon: <a href="http://j.mp/1lqRc4o">Steal Like an Artist</a></li>
  <li>John Trimble: <a href="http://j.mp/1BSWQkt">Writing with Style</a></li>
  <li>Ernest Hemingway: <a href="http://j.mp/1lqRjNk">On Writing</a></li>
  <li>Strunk and White: <a href="http://j.mp/1lqRicd">Elements of Style</a></li>
</ul>

<hr />

<h2 id="references">References</h2>
[1] Many of Jamie’s articles focus on the development of processes, such as automation or writing consistently. His transparency in the iteration of certain processes (such as his Google Docs scripts) are really insightful and can provide a nice model for anyone trying to learn and develop habits. Here are some awesome articles:

- <a href="http://99u.com/articles/30801/how-i-kept-a-373-day-productivity-streak-unbroken">How I kept a 373 day productivity streak unbroken</a>
- <a href="http://www.jamierubin.net/2014/08/08/how-i-use-google-docs-for-writing">How I use Google Docs for Writing</a>
- <a href="http://www.jamierubin.net/2014/05/20/going-paperless-whiteboards-webmeetings-evernote-and-skitch">Going paperless in Meetings</a>

[2] Read the guides on gitflow by <a href="https://www.atlassian.com/git/workflows#!workflow-gitflow">Atlassian</a> &amp; <a href="http://nvie.com/posts/a-successful-git-branching-model/">@Nvie</a>

<hr />

<img style="width:0;height:0;" src="https://ga-beacon.appspot.com/UA-36961797-1/sheets/2014-aug-writing-workflow" alt="" />
