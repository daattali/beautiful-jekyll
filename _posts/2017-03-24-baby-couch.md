---
layout: post
published: true
title: Couch Baby
date: 2017/03/10
---
>Your baby is learning to walk. The baby begins by holding onto a couch. Whenever she is next to the couch, there is a 25 percent chance that she will take a step forward and a 75 percent chance that she will stay clutching the couch. If the baby is one or more steps away from the couch, there’s a 25 percent chance that she will take a step forward, a 25 percent chance she’ll stay in place and a 50 percent chance she’ll take one step back toward the couch.
>
>In the long run, what percent of the time does the baby choose to clutch the couch?

<!--more-->

([fivethirtyeight](https://fivethirtyeight.com/features/will-the-baby-walk-away-will-the-troll-kill-the-dwarves/))

## Solution:

Let $E_1$ be the expected number of turns it takes for the baby to return to the couch from one step away. Then $E_1$ includes one step for sure, with .25 chance of then being in the same situation and expecting $E_1$ more turns, and .25 chance of being two steps away. At two steps away we expect $E_1$ turns before returning to one step away and expecting $E_1$ more turns from there. So:

$E_1 = 1 + .25 \times E_1 + .25 \times (E_1 + E_1)$
$E_1 = 4$

Letting $E_0$ be the expected number of turns it takes for the baby to return to (or remain at) the couch starting at the couch itself:

$E_0 = 1 + .25 \times E_1 = 2$

Now, the expected ratio of turns the baby spends at the couch (that is, turns at the end of which she is at the couch) is the inverse of that, or 1/2, because we expect between turns at the couch for the baby to be away from the couch for $E_0-1$, or 1 turn.

Verified by numerical simulation.

<br>
