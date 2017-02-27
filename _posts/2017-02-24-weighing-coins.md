---
layout: post
published: true
title: Weighing Coins
date: '2017-02-24'
---
> You have 12 gold coins — or so you think! One is fake and is known to have a different weight than the others. It could be heavier or lighter; you only know it’s wrong. Using the same simple balance scale, how do you determine the incorrect coin, and whether it is heavier or lighter, in only three weighings? 

<!--more-->

([fivethirtyeight](https://fivethirtyeight.com/features/two-mysteries-of-the-gold-coins/))

Solution:
=========

First, a method based on evaluating the outcomes of weighings as we go.

Weigh two groups of four coins.

-   If they are equal in weight, weigh a pair of the remaining 4 coins (A and B) against another of those (C) and one of the original 8 (which we know is genuine).

    -   If they are even, the remaining coin (D) is the fake; weigh it against one of the original 8 to determine if it is heavy or light.

    -   If A and B are heavier, weigh A against B; if one is heavier, it’s heavy, and if they are even, C is light.

    -   Proceed similarly if A and B are lighter.

-   Now suppose the two sets of four coins originally weighed are not equal in weight. Call the heavier coins A, B, C, and D, call the lighter ones E, F, G, and H, and let I be one of the remaining (known-genuine) coins. Weigh A, B and E against C, F, and I.

    -   If they are even, then either D is heavy or one of G and H is light. Weigh D and G against (known-genuine) A and B; if they are heavier, D is heavy; if lighter, G is light; otherwise H is light.

    -   If A, B, and E are heavier, then either F is light or one of A and B is heavy. Weigh A and F against (known-genuine) C and D. If they are heavier, A is heavy; if lighter, F is light; otherwise B is heavy.

    -   If A, B, and E are lighter, then either E is light or C is heavy. Weigh C against (known-genuine) A. If C is heavier, it’s heavy; otherwise E is light.

Extension:
==========

As an extension, let’s find a method that doesn’t require a decision tree. In other words, we have to say at the start which coins go where in all 3 weighings.

For 3 weighings with 3 possible outcomes each there are 27 possible overall outcomes. Each possible outcome can be coded by a base-3 numeral; for instance, "102" codes having the left side heavier in the first weighing, then both sides even, then right side heavier. We want to devise weighings so that for each coin there are two outcomes, corresponding to its being heavy or light.

Suppose the outcome 102 would show that coin 7 is heavy; then it must be that it is on the left in the first weighing, not involved in the second, and on the right in the third. This means the mirror outcome 201 (swapping 1s and 2s) codes coin 7 being light.

If we assign distinct pairs of mirrored outcomes to the 12 coins (eliminating 000, of course) such that there are always as many coins on the left as there are on the right when we place the coins according to their "heavy codes," then the code of the actual outcome will tell us which coin is heavy, or which is light.

Here is one way to achieve that, weighing 4 versus 4 coins each time:

Coin  | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  | 11  | 12
--  | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | --
Heavy | 101 | 222 | 100 | 001 | 011 | 220 | 102 | 021 | 210 | 122 | 010 | 212
Light | 202 | 111 | 200 | 002 | 022 | 110 | 201 | 012 | 120 | 211 | 020 | 121

$~$

Weighing | Left | Right
-- | -- | --
1 | 1 3 7 10 | 2 6 8 12
2 | 5  9 11 12 | 2 6 8 10
2 | 1 4 5 8 | 2 7 10 12
