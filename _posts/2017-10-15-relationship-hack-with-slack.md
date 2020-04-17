---
layout: post
title: Relationship Hack with Slack
subtitle: A Six Month Experiment
permalink: relationship-hack-with-slack
image: /img-posts/slack-0-icon.png
modified-date: Sep 16, 2018
---

Haley and I have been using Slack as a primary way to communicate in the past 6 months, and its been an authenticity and delight creating relationship hack.

![Mind blown][image-slack-9-brand]
<p class="text-muted">via <a href="https://giphy.com/gifs/mind-blown-kVA5mbyY6Z6AU">giphy</a></p>

## Problem: Getting in sync was hard

Before Slack, my girlfriend and I used a combination of iMessage / SMS and email. We found we didn't know where some detail was kept and did not have a good way to search on multiple platforms. While we both had WhatsApp, WeChat, Instagram, and Facebook messengers, they were somewhat overloaded with other messages.

### 3 Frequently (Un) Answered Questions
We are two New Yorkers with different work / social groups. These groups have shifting priorities and place constraints on our time. We found it difficult to stay in touch and in sync while on the move.

![Not in New Yorker][image-slack-1-message]
<p class="text-muted">It was not in New Yorker, though it was delicious.</p>

![From a trip][image-slack-2-message]
<p class="text-muted">From a trip to the New York Natural History Museum.</p>

![Because eating is important][image-slack-3-message]
<p class="text-muted">Because eating is important.</p>

"Sweetheart, this may sound nuts… but we should use an enterprise messaging platform for our relationship."

Here's what we did to kick this off:

 A year ago, I started using Slack at work. Slack was a replacement for a few enterprise messaging platforms [^1] and I found Slack solved many knowledge and communication problems. It is searchable and allows discussions to be organized into topics (with channels, detailed below). Slack has web/mobile/mac applications and confirms if messages are delivered. Slack also integrates many other platforms [^2].

[^1]: Enterprise messaging platforms are used to share knowledge and information within an organization. "Slack is where work flows. It's where the people you need, the information you share, and the tools you use come together to get things done" via https://slack.com/

[^2]: Integrations allow some other application to work with Slack. At work, our organization leverages the integration with GitHub (for code updates) and PagerDuty (for alerts notification) . At home, we leverage todoist (for collaborative todo lists) and IFTTT (for home automation), which we describe below.

### We signed up for a Slack as a "Shared Interest Group" of each other

🔑 Relationships are just another form of organization. We started to experiment with moving our communication to Slack and found good use cases (e.g. taking care of our cat, which I'll describe later).

![Sign up for Slack][image-slack-4-signup]

## Creating a Hypothesis to Test

We started off by agreeing this would be a hypothesis and we would likely get all the conventions wrong at first. If we felt this was not working or was too burden-some (what comes to mind when I say "enterprise messaging"), we'd stop.

To kick it off, we renamed the auto-generated `#general` channel to `#misc` and created channels for:

- `#date-night`, for weekly date nights
- `#home-projects` for various projects around the house
- `#sunday-dinner` for planning dinners with friends
- `#travel` for planning travel (we've been using TripIt for organizing boarding passes, AirBNB/hotel and car reservations, etc.).

Our communications were a bit chaotic at first because we posted a lot to `#misc`. Since then, we've been gradually adding more channels for concrete topics (`#cooking`, `#ops`, etc).

## Creating A Consistent Shared State

> It's the little details that are vital. Little things make big things happen." - John Wooden

I imagine John Wooden would love talking with modern health behaviorists / digital technologists about how to use technology to help with little details. We now do our best to share detailed messages, using Slack as a external brain, even if the contents of the message do not directly affect the other. Placing these little details in Slack helps coordinate what needs to happen now, and allows us to search for these details in the future.

Two recent threads (from Slack message to → outcome)

- `#misc` @f: "Hey, I'm planning to head to K-Town for dinner. Would you like anything from the market?" → Haley messages me and I buy a delicious savory pancake from Woorjip (a Korean market in Manhattan).
- `#ops` @h: "I'm going to do laundry this evening. Is there anything you'd like washed that isn't in the laundry bag?" → I message about an outfit I had left in my bag. Haley finds it to machine wash.

## Automation of notifications and reminders
After a month, we discovered we had shared to-do list items, and thought to try out a Slack todo list ("[todobot][link-todobot]"). 
 
 We could type "`/todo @f "Sand down wood block" Saturday 9 AM`" in `#home-projects`. We would get reminded on Friday that this was due.
 
This made regularly occurring tasks easier to schedule and to remember (e.g. "`/todo clean the house weekly`"). These tasks could be completed by either of us. When one of us marked the task as complete, we would both be notified it was completed.

We could also say "Alexa trigger Claude food" that would notify both of us in Slack and record this data in Google drive.


## The `#claude` Use case.
**Deep dive!** Before dating Haley, I had not lived with a cat before. Then, Claude moved in in June. Claude is a unique creature who loves chasing imaginary bunnies, watching TV, and using his paws to open doors.

![Claude][image-slack-5-claude]
<p class="text-muted">This looks like Claude is saying "please give me a belly rub", but he's really saying "please touch my belly so that I can claw your hand until it's burger".So… We created a channel for `#claude` the cat. (That's him in the photo.)</p>
 
`#claude` is filled with:

- Fun photos of cat antics.
- Notifying each other regarding regular ops. We share food / play to this channel and collect this data in Google Drive (see below). We collect this data by sending an SMS using Workflow (a one-click SMS sender). IFTTT interprets this SMS to post the information to the `#claude` channel. With our busy schedules, this helps us make sure that Claude has been fed breakfast and dinner each day, and that he doesn't trick us into doubling up on one of his meals.
- Developing hypotheses. We talk about experiments to try to make Claude / our lives happier. Claude has been pulling out fur for a while (we know he's been getting over a fear of large windows) and we've been testing ways to help this. We also recently installed an automated dry-food feeder / water faucet / toys, all of which seem to help.
- Data collection for eventual analysis. As we feed and play with Claude every day, we use the Workflow mentioned above to collect information on feed and play times in Google Drive. We also collect behavior information with this same medium. In addition to posting to Slack, IFTTT interprets this SMS to append a pre-formmated row to a spreadsheet in Google Drive. We hope to use a combination of daily data points, hypothesis testing, and behavior to see if there are behavior trends upon testing a new hypothesis or feed / play data points.

![Meditation bros][image-slack-6-meditation]
<p class="text-muted">@h: "Meditation bros." When I sit down to meditate, Claude often sits down next to me and joins.</p>
!["Squirrel hunt is on"][image-slack-7-search]
<p class="text-muted">@h: "The squirrel hunt is on!" Claude trying to figure out where the squirrels are when we play Cat TV.</p>

## Surprises

### Planning around the house
This was a surprise when I was looking at how we used Slack together. We got a lot more organized without either 1) suffering miscommunication or 2) needing extra apps for complex planning. E.g. while there are many collaborative to-do lists, we did not need to install an extra application on our phones by using an integration.
 
For example, we incrementally built on a "guest resources" Google Doc for friends / family when they stayed our place. This guide started as post-it for the wifi network. We slowly added more, such as things to know to navigate the neighborhood / home (like where to park or how the automated blinds work).

- In the past, this might be information that we would tell people individually by text because we forgot to mention it earlier.
- We had an easy way to add missing items to this resource guide.
- We had a central place to plan for when people joined us.
- We pinned this doc to be able to find it easily.

### Give me a minute to Slack this…

*(So we can let the machine remember and we can forget it.)*
 
Slack has become an external memory and trigger for us.

- When writing this up, I looked back at our Claude threads and found many hypotheses we've tested for cat behavior training, food choices, and general well-being in Slack. For example, we could make notes of food that the cat did not enjoy, which informed future choices.
- I also find it great at providing reminders along with context. We frequently add a reminder to a slack link like this: "`/todo @f @h "Cat ideas <Link to a thread on links for improving litter boxes hygiene>" Saturday 9 AM`"

### Sharing Weirdness

![On coming home from work][image-slack-8-catana]
<p class="text-muted">On coming home from work (from <a href="https://www.instagram.com/p/BYbJxD5A7zG/">catanacomics</a>)</p>

Our relationship feels new and interesting as we discover ourselves and each other. I feel delighted when reading the threads we shared on cat / dog memes, news articles, books, places to explore, etc.
 
I make about 80% of the posts in `#home-projects`, while Haley makes about 80% of the posts in `#cooking`. We both found this heteronormativity interesting - these are two areas we ***separately* do** and ***jointly* enjoy**. I love building home projects and she loves baking desserts. We found this sharing to be an authentic, non-invasive way to share the details of how some experience is put together, whether it's a wiring diagram for our Alexa-enabled three-switch lights or a recipe for spinach goat cheese quiche.


---

## Takeaways
We continue to use and enjoy using Slack. This technology has been a fun addition and communication-compounding addition to our relationship. We use it for areas that machines excel at and humans do not excel at - e.g., recording data perfectly / reminding us about this data - and we expect our usage to evolve in the future!
 
If anyone out there uses enterprise messaging for their relationship communications (or starts to do so after reading this), I'd love to hear from you!

---

[link-brand]: https://giphy.com/gifs/mind-blown-kVA5mbyY6Z6AU
[link-todobot]: http://todobot.io/
[image-slack-0-icon]: /img-posts/slack-0-icon.png  
<!-- https://icons8.com/icon/set/slack/all -->
[image-slack-1-message]: /img-posts/slack-1-message.png
[image-slack-2-message]: /img-posts/slack-2-message.png
[image-slack-3-message]: /img-posts/slack-3-message.png
[image-slack-4-signup]: /img-posts/slack-4-signup.png
[image-slack-5-claude]: /img-posts/slack-5-claude.png
[image-slack-6-meditation]: /img-posts/slack-6-meditation.jpeg
[image-slack-7-search]: /img-posts/slack-7-search.jpeg
[image-slack-8-catana]: /img-posts/slack-8-catana.jpeg
[image-slack-9-brand]: /img-posts/slack-9-brand.gif
