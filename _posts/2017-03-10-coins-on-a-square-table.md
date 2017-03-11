---
layout: post
published: false
title: Coins on a Square Table
date: 2017/03/10
---
> Two players are seated at a square table. The first player places a coin on the table, the second places a coin on the table, and they carry on placing coins one after another, with the only condition being that the coins are not allowed to touch. The winner is the person who places the final coin on the table, meaning that he or she fills the last remaining space between the other coins.
>
>The table has to be larger than a single coin, and all the coins placed must be identically sized.
>
>One player is always guaranteed to win if they use a certain strategy. Which one is it — the one who starts or the one who goes second? And what is his or her strategy?

<!--more-->

([fivethirtyeight](https://fivethirtyeight.com/features/who-will-win-the-space-race/))

## Solution:

The first player (X) always wins. X places the first coin in the center of the table. After that, whenever Y places a coin, X places the next one symmetrically, so that the two coins are the same distance from the center coin and all three of those coins are in the same line.  After each of X's moves, the table is symmetric (it has a 180 degree rotational symmetry), so that any open spot for Y to place a coin is mirrored by a spot for X's next coin. It follows that Y will be first to be unable to place a coin.

<br>
