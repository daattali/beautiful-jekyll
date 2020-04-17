---
layout: post
title: The Ultimate Beginners Guide To Web Development
subtitle: Lessons from the Web Lead of an Amazon Web Service
permalink: beginners-guide-web-dev
image: https://github.com/fxchen/frankc/raw/master/2014%20October/selfie.jpg
modified-date: Sep 16, 2018
---

My friends love learning. This guide is an amalgamation of emails I have sent friends and things I have picked up in my journey to learn web development [<a href="#frontend-notes">1</a>]. By the end of this guide you’ll be able to answer the following questions:
<ul>
  <li>“How might I build a personal website in an afternoon?”</li>
  <li>“How might I start web development as a career?”</li>
  <li>“How might I become a future expert in web development?”</li>
</ul>
Here’s a summary of what you’ll learn by section:
<ol>
  <li><strong><a href="#the-basics">How to understand the basics</a></strong> of a webpage and the internet</li>
  <li><strong><a href="#diving-deeper">How to structure learning</a></strong> on web development fundamentals</li>
  <li><strong><a href="#future-experts">How to engage and grow</a></strong> your expertise</li>
</ol>
These lessons are pulled from how I have learned. At the end of this guide, you’ll have the resources necessary to grow in your desired web development expertise (even if it is just for an afternoon).
<blockquote>Everything in life either grows or dies

<em>Anthony Robbins</em></blockquote>
Web development is centered around communities of developers sharing and collaborating together to build software. You’ll see links to <a href="https://github.com/about">Github</a>, the world’s leading open community to share code with “friends, colleagues, classmates, and complete strangers.”

<img src="https://github.com/fxchen/frankc/raw/master/2014%20October/new-repos.png" alt="" />
<em>Graph of github.com repositories. Image credit <a href="http://j.mp/Z7SoyA">RedMonk</a></em>

In the remainder of this guide, you’ll learn how you can grow from a beginniner to an expert in web development. This is by no means a comprehensive list of resources. Constraints are powerful in forcing maximum results with minimal investment. This guide lists resources useful for results. This guides teaches an approach on learning and exploring that <strong>you</strong>, <strong>web developer</strong>, will be able to use for what you’re trying to do.

I want to emphasize action:
<ul>
  <li>If you have an interest in web development, you should <strong>block two hours</strong> for <a href="#the-basics">The Basics</a> section and return to reading this guide at that time. For beginners, it’s important to have the right expectations. At the end of these hours, you should have a basic understanding of web development and a web presence.</li>
  <li>Else, if you’re looking to learn web development as a hobby or as a career, you may want to print this document (<a href="https://github.com/fxchen/frankc/raw/master/2014%20October/learning-frontend-software.pdf">pdf</a>) and bookmark it for easy reference. The most important part of <strong>learning a craft</strong> is building a consistent habit, for more on structuring <a href="http://frankc.wordpress.com/2014/08/03/design-your-personal-operating-system-habits/">habits</a>, see [<a href="#frontend-notes">2</a>]. At the end of this reading, you will have a baseline for qualified resources on how to start. This prevents the choice analysis paralysis (when too many choices makes the choice difficult).</li>
</ul>
The following sections are ordered by increasing difficulty.
<h2 id="the-basics">The Basics</h2>
<a id="the-basics"></a>
I have sent various emails to friends who want to learn web development. HOWEVER, my results over the past 10 years show about 75% who want to learn web development actually want to do something quite different. They want to build a web presence and register a domain name. To complete this section, you’ll need a web browser and at least two hours to set up a web presence and do some reading.

If this is your goal, you should use a site generator that lets you share your site without touching any code. Use <strong>one</strong> of the following site generators to get started:
<ul>
  <li><a href="http://about.me/">about.me</a></li>
  <li><a href="http://wordpress.org/">Wordpress</a></li>
  <li><a href="http://www.weebly.com/">Weebly</a></li>
  <li><a href="http://www.wix.com/">Wix</a></li>
  <li><a href="http://www.webs.com/">Webs</a></li>
</ul>
<em>Note: You might ask yourself why more than one generator is <a href="#frontend-limit">listed</a>. Each has a different strength and are very straight forward to test. These are listed by my ease of use, e.g. I found about.me to be extremely easy to use, but you may find Weebly fits your needs better</em>

But wait, how does the internet work? <a href="https://docs.google.com/presentation/d/1ruLiICsmBwZ3KFBkmOjQcQZAPS85BWImQu71MMcDs6w/edit#slide=id.i0">Introduction on how the browser and internet</a> (by Google researchers).

Excerpt:
<blockquote>The internet is a global network of computers. It is millions of computers around the world, all connected. People often think of the internet as a cloud in space. In reality, every computer in the “inter-network”, or internet, is connected by actual wires – ethernet cables, phone lines, and fiber optic wiring on the ocean floor!</blockquote>
<strong>Detailed links</strong>
<ul>
  <li>What makes Chrome or Firefox or Internet Explorer work? What is HTML and CSS?
<ul>
  <li>Follow tutorials on <a href="http://www.htmldog.com/">HTML Dog</a></li>
  <li>Search Quora. Quora is a resource to find guides to start. E.g. <a href="https://www.quora.com/What-are-some-best-practices-for-CSS">On CSS</a>; <a href="https://www.quora.com/What-is-the-best-way-to-educate-yourself-on-HTML-CSS-JavaScript-and-AJAX">On Learning HTML / CSS / AJAX</a></li>
  <li>Search <a href="http://stackoverflow.com">StackOverflow</a>. StackOverflow is the go to resource for many developers. As you start to search for detailed questions, you’ll find a StackOverflow page with the answer. These are often more technical in nature than Quora</li>
</ul>
</li>
  <li>Want a more in-depth look on the internet? <a href="http://web.stanford.edu/class/msande91si/www-spr04/readings/week1/InternetWhitepaper.htm">A white paper from Stanford</a></li>
</ul>
<h2 id="diving-deeper">Diving Deeper</h2>
The resources in this section are meant for those who want to start learning the fundamentals of web development and dive deeper than the basics. This is perhaps the <strong>most important part</strong> of this article. These resources are part of a long term learning process that starts with learning how to structure your learning. At the completion of this section, you should have a basic knowledge of how to deconstruct and play with most web sites you use. Furthermore, you will have a set of resources to continually learn web development.
<h4 id="set-up-your-development-environment">Set up your development environment</h4>
Learning a new environment is hard. This is a walk through of my basic environment set up. Whenever I have a new machine. I download <a href="http://sublimetext.com">SublimeText</a>, <a href="http://chrome.com">Google Chrome</a>, <a href="http://iterm2.com">iTerm2</a>
<ul>
  <li><strong>Chrome Extensions</strong>: Each of these extensions enhance the Chrome user experience
<ul>
  <li><a href="https://chrome.google.com/webstore/detail/pagespeed-insights-by-goo/gplegfbjlmmehdoakndmohflojccocli?hl=en">PageSpeed</a>. This is an extension to allow you to use Google’s pagespeed insights to make your website faster <a href="https://developers.google.com/speed/pagespeed/">Google Developer’s Guide</a></li>
  <li><a href="https://chrome.google.com/webstore/detail/angularjs-batarang/ighdmehidhipcmcojjgiloacoafjmpfk?hl=en">AngularJS Batarang</a>. This is an extension to debug AngularJS applications. AngularJS is a Javascript framework I describe later in this guide</li>
  <li><a href="http://www.editthiscookie.com">EditThisCookie</a>. Cookies are a way to keep information about a website you’re using. This is the technology that lets you open gmail without logging in each time</li>
</ul>
</li>
  <li><strong>Plugins for Sublime</strong>: Each of these plugins enhance the Sublime user experience
<ul>
  <li><a href="https://sublime.wbond.net/installation">Package Control</a></li>
  <li><a href="http://www.jshint.com/install/">jshint</a></li>
  <li><a href="http://www.sublimelinter.com/en/latest/">sublimelinter</a></li>
  <li><a href="https://github.com/titoBouzout/SideBarEnhancements">sidebarenhancements</a></li>
  <li><a href="https://github.com/facelessuser/BracketHighlighter">brackethighlighter</a></li>
  <li><a href="https://github.com/buymeasoda/soda-theme/">theme-soda</a></li>
  <li><a href="https://github.com/angular-ui/AngularJS-sublime-package">Angularjs</a></li>
  <li><a href="https://www.google.com/search?q=git%20gutter%20sublime%20text">GitGutter</a></li>
  <li><a href="https://github.com/spadgos/sublime-jsdocs">DocBlockr</a></li>
  <li><a href="https://github.com/SublimeText-Markdown/MarkdownEditing/">Markdown-editor</a></li>
  <li><a href="https://github.com/condemil/Gist">Gist</a></li>
</ul>
</li>
  <li><strong>More?</strong>
<ul>
  <li>Sublime Text Customization Guides: <a href="http://www.hongkiat.com/blog/sublime-text-plugins/">From Scotch.io</a>; <a href="http://scotch.io/bar-talk/best-of-sublime-text-3-features-plugins-and-settings">From Hongkiat</a></li>
  <li>Web Development Environment Set-up Guides: <a href="https://github.com/nicolashery/mac-dev-setup">From @nicolashery</a>; <a href="http://www.damln.com/log/setup/">From damln</a></li>
</ul>
</li>
</ul>
Note: I don’t dive deep on all the tools mentioned as they are beyond the scope of this guide (and others do a much better job of it).
<h4 id="learn-your-web-console">Learn your web console</h4>
The console allows you to interact with HTML and Javascript interactively. This will let you change what you see and see what is happening behind the scenes as you go through a web page.
<ul>
  <li><a href="https://www.ng-book.com/p/Debugging-AngularJS/">On ng-book</a></li>
  <li><a href="http://blog.teamtreehouse.com/mastering-developer-tools-console">By Team Tree House</a></li>
  <li><a href="https://developer.chrome.com/devtools">By Google Devtools</a></li>
</ul>
Read these guides for a basic understanding of the console. You’ll return to the console often as you continue to develop. If you master the basics of inspecting HTML and debugging Javascript, you’ll reap progressively larger benefits as you continue to learn. Especially as you develop more complex applications, you will have huge dividends in time savings if you master the console.

<img src="https://github.com/fxchen/frankc/raw/master/2014%20October/quicksilver.jpg" alt="" />

<em>Knowing how to use the debugger is like having Quicksilver’s superpower from X-Men. You can stop Javascript execution, change variables, manipulate HTML, and much more. Image credit <a href="http://www.inentertainment.co.uk/">EW</a></em>
<h4 id="structure-your-learning">Structure your learning</h4>
A critical juncture in learning is a habit to jump start your learning process. For example, I like to learn in the mornings. I describe my morning routine <a href="http://frankc.wordpress.com/2014/08/03/playlist-your-morning-routine-beat-complexity-like-a-boss/">here</a>. When I am learning a new craft, I will block at least 30 minutes every morning to learn and practice this craft prior to leaving for work. For more on building a habit see: <a href="#frontend-notes">[2]</a>

Courses:
<ul>
  <li>Udacity: <a href="https://www.udacity.com/course/ud304">HTML &amp; CSS</a>; <a href="https://www.udacity.com/course/ud804">Javascript</a>; <a href="http://www.udacity.com/overview/Course/cs253">Web Development</a></li>
  <li>Codeacademy: <a href="http://www.codecademy.com/en/tracks/web">Basics HTML &amp; CSS</a>; <a href="http://www.codecademy.com/tracks/jquery">JQuery</a>; <a href="http://www.codecademy.com/skills/make-an-interactive-website">Interactive Website</a></li>
  <li>NetTutorials: <a href="http://code.tutsplus.com/categories/web-development">Web Development</a></li>
  <li>CodeCombat: <a href="http://codecombat.com/">Learn to Code By Playing a Game</a></li>
  <li>Coursera: <a href="https://www.coursera.org/course/hciucsd">Human-Computer Interaction</a>; <a href="https://www.coursera.org/course/webapplications">Web Applications</a> Note: these two are limited to when they are offered on Coursera</li>
</ul>
<a id="frontend-limit"></a>For structured courses or books: <strong>limit what doesn’t work</strong>. Use this list as a list to sample from, and sample the course or book to learn what learning style works for you. For a book, you only need to read 30-40 pages to decide if a programming book’s author’s style works for you. Even if someone else recommended a book, it may not be ideal for you, everyone’s learning style and background is different. The same thing applies for courses. Programming books and courses vary in quality of learning depending on your learning style and skillset. For example, <a href="https://www.packtpub.com/web-development/mastering-web-application-development-angularjs">Mastering AngularJS</a> is great if you have experience in Javascript and AngularJS. This book jumps from high level concepts for beginners to specific solutions to detailed pain points geared for experts. This type of jump may be disorienting if you’re new to AngularJS.
<table>
<thead>
<tr>
<th>Don’t do this</th>
<th>Do this</th>
</tr>
</thead>
<tbody>
<tr>
<td><img src="https://github.com/fxchen/frankc/raw/master/2014%20October/junior.png" alt="" /></td>
<td><img src="https://github.com/fxchen/frankc/raw/master/2014%20October/senior.png" alt="" /></td>
</tr>
</tbody>
</table>
<em>When It comes to your learning, use this technique of sampling then eliminating what doesn’t work. Image Credit <a href="https://twitter.com/joulee">Julie Zhou</a>, originally used in a fantastic article on <a href="https://medium.com/the-year-of-the-looking-glass/junior-designers-vs-senior-designers-fbe483d3b51e">Junior versus Senior Designers</a></em>
<h2 id="future-experts">Future Experts</h2>
This section is related to a base set of resources are critical to specializing in Javascript and AngularJS.
<h4 id="step-1:-on-javascript-and-web-technologies">Step 1: On Javascript and Web Technologies</h4>
Read these resources as you’re developing your project (or are going through the courses listed in the Structured Learning Section).
<ul>
  <li><a href="http://j.mp/1C1H18k">Crockford: JavaScript The Good Parts</a></li>
  <li><a href="https://bonsaiden.github.io/JavaScript-Garden/">Javascript Garden</a></li>
  <li><a href="http://addyosmani.com/resources/essentialjsdesignpatterns/book/">Essential Javascript Design Patterns</a></li>
  <li><a href="https://developer.chrome.com/apps/angular_framework">Google Developer’s Guide for Angular</a></li>
  <li><a href="http://www.learningjquery.com/">Learning JQuery</a> &amp; <a href="http://getbootstrap.com">Bootstrap</a></li>
  <li><a href="https://developer.mozilla.org/en-US/docs/Web/JavaScript/A_re-introduction_to_JavaScript">Reintroduction to Javascript from Mozilla</a></li>
  <li><a href="http://www.amazon.com/Secrets-JavaScript-Ninja-John-Resig/dp/193398869X">Secrets of the Javascript Ninja</a></li>
</ul>
<h4 id="step-2:-on-angular-js">Step 2: On Angular JS</h4>
There are many flavors of Javascript frameworks [<a href="#frontend-notes">3</a>]. The one I am most familiar with is AngularJS. As of this writing, AngularJS has one of most active communities on Github and <a href="https://www.google.com/search?q=why+angularjs&amp;oq=why+angularjs">many developers swear by it</a>. For a showcase of applications built on AngularJS: <a href="https://builtwith.angularjs.org/">https://builtwith.angularjs.org/</a>. This framework introduces language constructs that engineers familiar with iOS and Android development use that are traditionally missing in Javascript. AngularJS is the right framework for many teams that want to rapidly iterate and maintain a single page application.

<strong>Must reads</strong>
<ul>
  <li><a href="http://docs.angularjs.org/">Official Documentation</a></li>
  <li><a href="http://www.amazon.com/AngularJS-Brad-Green/dp/1449344852/ref=sr_1_1?ie=UTF8&amp;qid=1372874049&amp;sr=8-1&amp;keywords=angularjs">O'Reilly AngularJS book</a></li>
  <li><a href="https://www.packtpub.com/web-development/mastering-web-application-development-angularjs">Mastering AngularJS</a> - for intermediate developers</li>
</ul>
<strong>Diving deeper</strong>
<ul>
  <li>A <strong>very</strong> comprehensive <a href="https://github.com/jmcunningham/AngularJS-Learning">list of resources on AngularJS</a>. This collection is constantly updated</li>
  <li>Tutorials + videos: <a href="https://thinkster.io/angulartutorial/a-better-way-to-learn-angularjs/">Organized tutorial</a> via Thinkster.io (uses Egghead.io tutorials) + <a href="https://thinkster.io/angulartutorial/mean-stack-tutorial/">part 2</a> with full stack components. Individual video tutorials: <a href="https://egghead.io/">https://egghead.io/</a></li>
  <li><a href="https://fdietz.github.io/recipes-with-angular-js/">Angular Recipes</a></li>
</ul>
<h4 id="step-3:-on-becoming-a-browser-whisperer">Step 3: On becoming a Browser Whisperer</h4>
<strong>Reads</strong>
<ul>
  <li>On Testing: <a href="http://www.amazon.com/Beautiful-Testing-Professionals-Software-Practice/dp/0596159811">Beautiful Testing</a>; <a href="http://www.yearofmoo.com/2013/01/full-spectrum-testing-with-angularjs-and-karma.html">Application testing via yearofmoo</a></li>
  <li>Mozilla Developer’s <a href="https://developer.mozilla.org/en/JavaScript/Guide">Guide to Javascript</a></li>
  <li><a href="http://queue.acm.org/detail.cfm?id=2507894">ACM: Best Practices on the Move: Building Web Apps for Mobile Devices</a> while this essay is a collection of recommendations for making websites better for mobile devices, it serves as a nice template for modern performant web applications</li>
  <li><a href="http://queue.acm.org/detail.cfm?id=2446236">ACM: How Fast is Your Website</a> this essay gives a nice overview for how to understand performance within web applications</li>
  <li>Cross-Origin Resource Sharing: This <a href="https://en.wikipedia.org/wiki/Same-origin_policy">wikipedia article</a> has a great set of links related to how to understand why this is important and methods to perform Cross Origin Resource Sharing for your website.</li>
  <li><a href="http://www.geeksforgeeks.org/fundamentals-of-algorithms/">Fundamentals of Algorithms by GeeksForGeeks</a> has my favorite collection of algorithms on the web. It has details on run time for you to remember computer science fundamentals (and a great primer if you are interviewing)</li>
</ul>
<strong>Specific to AngularJS</strong>
<ul>
  <li><a href="http://angular-ui.github.io/">Angular UI</a>: set of useful tools built for Angular. For example, this project has a subproject for integration of Twitter’s <a href="http://angular-ui.github.io/bootstrap/">Bootstrap components</a></li>
  <li><a href="https://stackoverflow.com/questions/9682092/databinding-in-angularjs/9693933#9693933">Understand data binding</a> via StackOverflow by one of the creators of Angular</li>
  <li>Improving performance with data bound components with <a href="https://github.com/Pasvaz/bindonce">BindOnce</a></li>
  <li>Approaches on Combining Facebook React with AngularJS [<a href="https://www.quora.com/Pete-Hunt/Posts/Facebooks-React-vs-AngularJS-A-Closer-Look">1</a>] ; [<a href="http://davidandsuzi.com/ngreact-react-components-in-angular/">2</a>]</li>
  <li>Another approach to <a href="http://www.williambrownstreet.net/blog/2013/07/angularjs-my-solution-to-the-ng-repeat-performance-problem/">improving performance for ngRepeats</a></li>
</ul>
<strong>What is the hardest part of developing for the web? What are pitfalls that every web developer should know?</strong>

The hardest part of developing on the web is constant change. To succeed in delivering a great customer experience, you sometimes feel like you’re hitting a flying target with a bow and arrow while on horseback. Browsers / browser versions / frameworks change all the time. For example, something that worked last week may not work this week due to a dependency change in your framework that seemingly has nothing to do with a tool you’re using within your project, and this problem only pops up in IE 10.

The easiest pitfall of development is not testing. At the highest levels, testing can be a critical piece to ensure customer success. Entire books are dedicated to the topic of testing and beyond the scope of this beginners guide. Testing may be often overlooked in young development teams. Browser tests are particularly hard because browsers are interpretations of how the web protocols should work. There is no guarantee of consistency between browsers and browser versions.

<strong>How can I practice development everyday or reinforce my learning?</strong>

<em>Learn widely</em>. Web development is a moving target with many different areas to specialize in. Here are some ways to stay engaged with different communities
<ul>
  <li>Newsletters: <a href="https://groups.google.com/forum/#!forum/angular">Official Mailing List</a>, <a href="http://www.angularjsdaily.com/">AngularJS Daily</a>, <a href="http://www.ng-newsletter.com/">ng-newsletter</a></li>
  <li>Engineering Blogs: <a href="http://googledevelopers.blogspot.com/">Google</a>, <a href="http://feeds.feedburner.com/AmazonWebServicesBlog">AWS</a>, <a href="https://engineering.linkedin.com/blog">LinkedIn</a>, <a href="https://blog.twitter.com/">Twitter</a>, <a href="https://code.facebook.com/posts/">Facebook</a>, <a href="https://github.com/blog">Github</a>, <a href="http://highscalability.com">High Scalability Blog</a>, <a href="http://nerds.airbnb.com/">AirBNB</a></li>
</ul>
<em>Find a mentor</em>. Chances are you know someone who does this professionally or unprofessionally. Ask them for code reviews or problems you’re having. Talking aloud is an incredibly powerful way to solve problems. Thinking as an engineer means moving between different levels of abstraction. Someone who has 20 years of experience sees an entirely different set of problems when I ask this person a question than I do when someone asks me the same question.

<em>Build something and stretch your skills</em>. You can choose the tools in what you build every day in your practice. Github has a variety of codebaes for you to play with that are a “<a href="http://git-scm.com/book/en/Getting-Started-Git-Basics">checkout</a>” away. Even if you never end up releasing or integrating someone else’s project into your development projects, you have the opportunity to play with something cool.

<img src="https://github.com/fxchen/frankc/raw/master/2014%20October/selfie.jpg" alt="" height="500px" />

<strong>I’m smiling because I hope you’ll send me feedback!</strong> Send me an email at <a href="mailto:hello@frankc.net">hello@frankc.net</a> on what worked or didn’t work for you!

Special thanks to <a href="http://abhishekmantha.com/">Abhishek Mantha</a> for critical insights on how he learned development, <a href="http://www.linkedin.com/pub/jeffrey-song/4/651/760">Jeffrey Song</a> for a beginner’s narrative on using this guide for learning web development, and <a href="http://amaanp.com">Amaan Penang</a>, <a href="http://www.linkedin.com/in/ngerebara">Nate Ngerebara</a> for feedback on early drafts of this guide.

<hr />

<strong>Notes</strong><a id="frontend-notes"></a>

[1] <strong>Why am I writing this?</strong> I have learned a lot in the past few years and wanted to share a set of resources with my friends who wanted to learn web development and internet friends.

I started web development at 12—at that time, people “surfed the world wide web.” For most of my academic and professional career, I was a researcher where I created software as part of my research. I built systems to study <a href="http://www.rand.org/pubs/tools/expertlens.html">social influence on opinion</a> at RAND, <a href="http://cens.ucla.edu/">mobile environmental impact</a> at UCLA, and <a href="http://med.stanford.edu/news/all-news/2011/08/eat-a-carrot-and-get-out-of-that-chair-or-your-ibird-dies.html">behavioral theories on mobile phones</a> at Stanford).

Development at a company or startup requires a different set of skills. I studied Computer Science and researched in Human-Computer Interaction, both of which required development. Yet, the craft of development is very different from academia. The focus of development is much more team oriented. From early 2013, I led the web team on <a href="http://aws.amazon.com/zocalo">Amazon Zocalo</a>. Zocalo is a secure enterprise sharing and collaboration service that uses AngularJS as its Javascript frontend framework.

[2] <strong>On developing habits for learning</strong> I have found these to be good systems to model for learning new skills:
<ul>
  <li>Tim Ferriss’s <a href="http://www.amazon.com/The-4-Hour-Chef-Learning-Anything/dp/0547884591">4 Hour Chef</a> - this is a book on learning, that also teaches cooking</li>
  <li><a href="http://tinyhabits.com">BJ Fogg’s Tiny Habits</a> - this is a habit program on learning how to develop simple habits</li>
  <li><a href="http://lift.com">Lift</a> - this is a social network for habits</li>
</ul>
[3] <strong>On picking the right Javascript framework</strong> I focus on AngularJS in this guide. To prevent frontend framework choice paralysis, AngularJS is the only Javascript framework presented. AngularJS has been hugely popular and useful for many developers who use it. If you’re interested in what else is out there, I would suggest <strong><a href="http://todomvc.com">TodoMVC</a></strong> TodoMVC implements the same To-do application using many popular Javascript frontend frameworks. This allows for a comparison and bootstraps the ability for people to prototype in different flavors of frontend frameworks.


<img src="https://ga-beacon.appspot.com/UA-36961797-1/sheets/2014-oct-learning-frontend-software" alt="" width="0" height="0" />
