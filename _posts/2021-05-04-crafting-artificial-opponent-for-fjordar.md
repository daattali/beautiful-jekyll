---
layout: post
title: Crafting an artificial opponent for Fjordar
date: '2021-05-04T22:42:00.005+02:00'
author: Morten
tags:
- Programming
- simulations
- boardgaming
- Python
- game
- boardgame design
- solitaire
modified_time: '2021-05-04T23:57:09.235+02:00'
thumbnail: https://lh3.googleusercontent.com/-KPJVf2dm9bc/YJGpwlA5RpI/AAAAAAADoZ8/xde4Zuo2V5s-SJAvawgm1ZMRWddf5OwOQCLcBGAsYHQ/s72-w400-c-h400/pic5038580.webp
blogger_id: tag:blogger.com,1999:blog-6967032375013519080.post-8545203759529375320
blogger_orig_url: https://m635j520.blogspot.com/2021/05/crafting-artificial-opponent-for-fjordar.html
cover-img: https://lh3.googleusercontent.com/-KPJVf2dm9bc/YJGpwlA5RpI/AAAAAAADoZ8/xde4Zuo2V5s-SJAvawgm1ZMRWddf5OwOQCLcBGAsYHQ/pic5038580.webp
thumbnail-img: https://lh3.googleusercontent.com/-KPJVf2dm9bc/YJGpwlA5RpI/AAAAAAADoZ8/xde4Zuo2V5s-SJAvawgm1ZMRWddf5OwOQCLcBGAsYHQ/pic5038580.webp
share-img: https://lh3.googleusercontent.com/-KPJVf2dm9bc/YJGpwlA5RpI/AAAAAAADoZ8/xde4Zuo2V5s-SJAvawgm1ZMRWddf5OwOQCLcBGAsYHQ/pic5038580.webp
---
[![](https://lh3.googleusercontent.com/-KPJVf2dm9bc/YJGpwlA5RpI/AAAAAAADoZ8/xde4Zuo2V5s-SJAvawgm1ZMRWddf5OwOQCLcBGAsYHQ/w400-h400/pic5038580.webp)](https://lh3.googleusercontent.com/-KPJVf2dm9bc/YJGpwlA5RpI/AAAAAAADoZ8/xde4Zuo2V5s-SJAvawgm1ZMRWddf5OwOQCLcBGAsYHQ/pic5038580.webp)  

`Fjordar is an epic, tactical strategy game for 1 to 4 players, set during the Norwegian Civil War. The game begins in the year 1130, when the old king Sigurd Jorsalfar dies. Each player begins the game as one of Sigurd's heirs or one of the other influential people in Norway at the time, who is vying for power in the vacuum left by the old king's death.` – [Fjordar, BGG](https://boardgamegeek.com/boardgame/292707/fjordar)

A while back, after a lengthy exchange on ideas around this topic, the designer of Fjordar, Frode Brændø, asked me if I would be interested in helping out with designing a solitaire variant for this upcoming game. Of course I would!

Here are some brief notes on some from the design process.

Idea
----

We wanted to make an artificial opponent based the following criteria:

1.  **Non-fiddlyness**
    *   Running the opponent should not lead to _a lot_ of overhead for the player.
2.  **Readability**
    *   The player should _to some extent_ be able to read the artificial player enough to predict future actions and react to them.
3.  **Keep gameplay**
    *   The gameplay loop should not change for the player.
4.  **No player decisions**
    *   The player should not have to make decisions on behalf of artificial player.
5.  **Keep scoring system**
    *   The artificial opponent should score points in the same way a regular player would during the game to recreate the race aspects of the game.

... and, on top of all this, it should be fun to play _and_ be able to put up a good fight – even against Frode himself.

Inspirations
------------

Even before “the current hygienic situation”, [I’ve gravitated more and more towards solo games, or solo variants, for a fair share of my boardgaming](https://boardgamegeek.com/geeklist/209441/adventures-solo-gaming), so a lot of the solutions to problems encountered creating an artificial opponent for Fjordar has, obviously, been inspired by other games.

Recently I have been particularly impressed with games by [Shem Phillips](https://boardgamegeek.com/boardgamedesigner/12547/shem-phillips) and [SJ Macdonald](https://boardgamegeek.com/boardgamedesigner/103821/s-j-macdonald). And it is fascinating to follow the evolution of solitaire modes in games from Garphill games in general. Ranging from pure beat your own score of [Explorers of the North Sea](https://boardgamegeek.com/boardgame/176371/explorers-north-sea), via the simple “Automa”-deck of [Raiders](https://boardgamegeek.com/boardgame/170042/raiders-north-sea), and [Architects](https://boardgamegeek.com/boardgame/236457/architects-west-kingdom), to the even more fascinating systems of [Paladins](https://boardgamegeek.com/boardgame/266810/paladins-west-kingdom) and [Viscounts](https://boardgamegeek.com/boardgame/296151/viscounts-west-kingdom) where you can to a larger extent _read_ the Automa player.

A lot of the resulting work is inspired by Morten Monrad Pedersen’s Automa concept – summed up in [this short article](https://boardgamegeek.com/blogpost/109521/what-automa). (That I, sadly, didn’t came across before a couple of weeks ago…)  

Solution
--------

From the onset we wanted a deck of action cards with a notion of deck building so that the artificial player would, like other players, get stronger through the game. This also lead to one of the ways we constructed more difficult-to-beat opponents – by adding a higher number of upgraded cards. (These cards are also inspired by the Automa _focus_ concept from Viscounts of the West Kingdom.)

One of the most interesting mechanisms in Fjordar is the card play. Each round you play a card from your hand to your mini-tableau that gives you movement points and other bonuses as well as ways to break the regular rules, like the fan favorite “Winter” card where you can ski your units down mountains. On subsequent turns you can add cards to your mini-tableau, if you can afford it, or pick up all cards and restart it. This leads to these build ups of waves of powerful turns where you have a lot of movement points, before reseting back to less powerful ones. We thought that would be good to keep as a central component of the Automa player, if it was possible to do without adding too much cognitive load or fiddlyness.

Another important aspect in the regular game is, obviously, the units on the map. This, we figured we could leverage to improve readability, or predictability, of what the artificial opponent can do. The Automa has a range of operation around certain units based on its current movement range.

So, to kick off the testing process, after a lot of brainstorming, planning, writing, some simulations, and back and forth with Frode, I created a simple Automa deck based on the cards of the regular players – matching actions with movement ranges that seemed fitting.

[![](https://lh3.googleusercontent.com/-jU81gKmO82Q/YJGp5x5dyYI/AAAAAAADoaA/WJ6YfLFFrikCRSBLuPdeDvGZ2Kj8ohrHgCLcBGAsYHQ/first-iteration.jpg)](https://lh3.googleusercontent.com/-jU81gKmO82Q/YJGp5x5dyYI/AAAAAAADoaA/WJ6YfLFFrikCRSBLuPdeDvGZ2Kj8ohrHgCLcBGAsYHQ/first-iteration.jpg)

Each action in the game is translated to actions of the Automa, with simple rules to follow, in classic [MMP](https://boardgamegeek.com/boardgamedesigner/71006/morten-monrad-pedersen)\-style. This early in the process it had only one moving unit, the Hird, that moved around and performed actions based on it’s range (movement points). And, it was already fun to play! (Mainly due to the strength of the Fjordar game itself, of course.)  

But how balanced was it? And could we streamline it further?

Simulations
-----------

I’ve always applied math and simulation to game ideas and puzzles – mine or the ones of others – to see if they… hold water. (I was happy to hear that the good folks of Garphill games does so too. (At least the math part, according to [this great podcast interview at Board Game Design Lab](https://boardgamedesignlab.com/designing-worker-placement-games-with-shem-phillips-and-sam-macdonald/). (They also reveal that they often design the solo mode at a very early stage for balancing purposes – and it shows in the resulting solo modes! (But I digress.))))

An example of where I applied simulations in this process is in the balancing of the battles between the player and Automa. Our first system for battles was that the player would chose and play a card as per usual, and then the Automa would draw two random cards and pick the one that would give him the most strength against the player.

(This clearly does not simulate all the bluffing, pushing of luck, and reading of opponents that goes on in the regular game, but is close, and “unfiddly” enough for our purposes here and it still leads to tense and exiting battles.)

My first simulation was around the hand size of the Automa. Are two cards enough? Too many? I fired up my Jupyter Notebook, created a representation of all the battle cards in Fjordar, and their interaction, before simulating how often the player would win in an even fight, given various hand sizes of the artificial opponent. And, lo and behold, after a mere 10000 virtual battles:

[![](https://lh3.googleusercontent.com/-y9gXmEaYIu0/YJGp-4PJxBI/AAAAAAADoaE/WpVGjkRmZO8lANP9r2aI25vnl-zoe0mkACLcBGAsYHQ/fjordar-ai-hand-size.png)](https://lh3.googleusercontent.com/-y9gXmEaYIu0/YJGp-4PJxBI/AAAAAAADoaE/WpVGjkRmZO8lANP9r2aI25vnl-zoe0mkACLcBGAsYHQ/fjordar-ai-hand-size.png)

So, if the Automa, with a hand size of 2, is on equal footing to the player going into a battle the latter would win about 42% of the fights. That sounds good. But! the most important thing is that it is fun and _feels_ fair, so, back to testing.

We realized that it was sometimes slightly fiddly to calculate strength for _both_ Automa cards before comparing. Also, it could lead to the player having to make a choice on its behalf. Something we wanted to avoid.

What if we rather gave the artificial opponent bonus swords? Intuitively that would result in a similar shift. Back to the notebook, and after 10000 further fights (oh, the poor post-vikings…), it resulted in:

[![](https://lh3.googleusercontent.com/-2JD_7_9h5BQ/YJGqB6XlG5I/AAAAAAADoaI/PZh4_0QKE_0ifpPf7xcktjEl8qUR0_acgCLcBGAsYHQ/fjordar-ai-swords.png)](https://lh3.googleusercontent.com/-2JD_7_9h5BQ/YJGqB6XlG5I/AAAAAAADoaI/PZh4_0QKE_0ifpPf7xcktjEl8qUR0_acgCLcBGAsYHQ/fjordar-ai-swords.png)

So, giving the Automa a one sword head start and drawing one card is fairly similar, baseline probability-wise, to giving it a hand size of two.

There are other aspects of battles I simulated to make sure that this system works, but I won’t go into more details here. (Maybe it could warrant another post at some point…)

Conclusion
----------

And now, after many iterations and a lot of testing we have a version that is ready for other players to sink their teeth into.

The game will launch on [Kickstarter](https://www.kickstarter.com/projects/fjordar/fjordar) by [Go to Pieces Games](https://www.gotopiecesgames.com/) the 28th of May but/and if you want to try out this beautiful euro- meets war-game for yourself (for free), Frode has made an excellent [mod for Tabletop Simulator](https://steamcommunity.com/sharedfiles/filedetails/?id=2109550970). As of Thursday last week this also includes a beta version of this solitaire variant!

[![](https://lh3.googleusercontent.com/-r71OLVxjga0/YJGqEkNHT3I/AAAAAAADoaM/V10UgFydT5A8Rl8rJEpO6JzyVilkDOnnwCLcBGAsYHQ/fjordar-tts.jpg)](https://lh3.googleusercontent.com/-r71OLVxjga0/YJGqEkNHT3I/AAAAAAADoaM/V10UgFydT5A8Rl8rJEpO6JzyVilkDOnnwCLcBGAsYHQ/fjordar-tts.jpg)

It has been great fun to work, or, perhaps, rather, jam, with Frode on this project and I’m looking forward to hear what you all think…

Links
-----

*   [Fjordar on BoardGameGeek](https://boardgamegeek.com/boardgame/292707/fjordar)
*   [Fjordar Tabletop Simulator mod](https://steamcommunity.com/sharedfiles/filedetails/?id=2109550970)
*   [Beta version of Fjordar solitaire mode rules](https://www.dropbox.com/s/xowb0g98bn038hx/Fjordar_bot_living_rules.pdf?dl=0)
*   [Fjordar game rulebook](https://www.dropbox.com/s/sduo28evs3sza02/Fjordar_Living_Rules.pdf?dl=0)
*   [Kickstarter campaign](https://www.kickstarter.com/projects/fjordar/fjordar).
*   [Go To Pieces Games](https://www.gotopiecesgames.com/)