---
layout: post
published: true
title: Timing by Burning Ropes
date: 2017/02/24
---
The Puzzle:
===========

> Suppose you have four ropes and a lighter. Each rope burns at a nonconstant rate but takes exactly one hour to burn completely from one end to the other. You can only light the ropes at either of their ends but can decide when to light each end as you see fit. If you’re strategic in how you burn the ropes, how many specific lengths of time can you measure? (For example, if you had one rope, you could measure two lengths of time: one hour, by simply burning the entire rope from one end, and half an hour, by burning the rope from both ends and marking when the flames meet.)
>
> Extra credit: What if you had N ropes?

Solution:
=========

“Being able to measure" a given length of time might mean being able to tell when that length of time has passed from the get-go, or more liberally, being able to produce a sequence of events such that that length is the period between some two of them. We’ll find answers for both interpretations of the problem (Oliver Roeder clarifies on Twitter that the more liberal interpretation is intended). Also, in the problem statement it is clearly assumed that there is not a “length" of zero hours.

With 1 rope, we can measure 2 durations: 1/2 and 1 hour.

With 2 ropes (call them 1 and 2), we can measure 5 durations from the start:

-   4 half-hour-multiple durations.

-   Measure 3/4hr: light both ends of 1 and one end of 2; at 1/2hr, light the other end of 2.

This allows us also to measure 1/4hr, so there are 6 in all.

With 3 ropes (1, 2, and 3) we get 11 durations from the start:

-   6 half-hour-multiple durations.

-   Using two of the ropes to measure 3/4hr, we get 3 more durations for each of the ways of using rope 3 from there.

-   Measure 7/8hr: proceed as in measuring 3/4hr, and light 3 at the start and 3/4hr.

-   Measure 9/8hr: proceed as in measuring 3/4hr, and light 3 at 1/2hr and 3/4hr.

If we count durations between extinguishings as well, we get 16 in all.

With 4 ropes we have 23 durations from the start:

-   8 half-hour-multiples.

-   Using one pair to measure 3/4hr, we have 5 options for the other two ropes starting from there (the half-hour multiples).

-   Using three ropes to measure 7/8 gives 3 options for the remaining rope starting from there.

-   Using three ropes to measure 9/8hr similarly gives 3 new options starting from there.

-   Measure 15/16hr: proceed as in measuring 7/8hr, and light 4 at the start and 7/8hr.

-   Measure 19/16hr: proceed as in measuring 7/8hr, and light 4 at 1/2hr and 7/8hr.

-   Measure 21/16hr: proceed as in measuring 7/8hr, and light 4 at 3/4hr and 7/8hr. (Alternatively, proceed as in measuring 9/8hr, and light 4 at 1/2hr and 9/8hr.)

-   Measure 23/16hr: proceed as in measuring 9/8hr, and light 4 at 3/4hr and 9/8hr.

If we count durations between extinguishings as well, there are 37 in all.

These figures are confirmed by a Python program available at:

https://gist.github.com/hectorpefo/db9b302f4d33474216da6a81cda28580

Here’s the output of that program for N=5:

        87
    [0.03125, 0.0625, 0.09375, 0.125, 0.15625, 0.1875, 0.21875, 0.25, 0.28125, 0.3125, 0.34375, 0.375, 0.40625, 0.4375, 0.46875, 0.5, 0.53125, 0.5625, 0.59375, 0.625, 0.65625, 0.6875, 0.71875, 0.75, 0.78125, 0.8125, 0.84375, 0.875, 0.90625, 0.9375, 0.96875, 1, 1.03125, 1.0625, 1.09375, 1.125, 1.1875, 1.21875, 1.25, 1.28125, 1.3125, 1.34375, 1.375, 1.40625, 1.4375, 1.46875, 1.5, 1.53125, 1.5625, 1.59375, 1.625, 1.6875, 1.71875, 1.75, 1.78125, 1.8125, 1.875, 1.9375, 2, 2.0625, 2.125, 2.1875, 2.25, 2.3125, 2.375, 2.4375, 2.5, 2.625, 2.75, 2.875, 3, 3.125, 3.25, 3.375, 3.5, 3.5625, 3.625, 3.6875, 3.75, 3.8125, 3.875, 4, 4.0625, 4.125, 4.25, 4.5, 5]
    [Finished in 182560.2s]