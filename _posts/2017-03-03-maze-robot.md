---
layout: post
published: true
title: Maze Robot
date: 2017/03/03
---
> You’re so tired that you can no longer walk. Luckily, though, you remembered to bring your robot pal along. The robot must be given a list of directions as instructions, and will attempt to read each instruction in order and move that direction. For example, “NNWES” will instruct the robot to move north, north, west, east, south. If an instruction is impossible to carry out (i.e., there is a wall in that direction), the robot will bump into the wall then move on to the next instruction as if nothing happened. The robot can’t do any computation or communicate with you after it leaves — it blindly follows the instructions given until it reaches the finish or it runs out of instructions. However, you can do as much computation as you want before sending the robot on its merry way. (Hint: The robot has lots, and lots, and lots of memory.)
>
>What instructions do you feed your robot to guarantee that it will reach the end square somewhere along its journey?
>
>Extra credit: What’s an upper bound for the minimum number of instructions you must feed your robot to guarantee that it reaches the end square?

<!--more-->

([fivethirtyeight](https://fivethirtyeight.com/features/can-your-robot-friend-solve-the-corn-maze/))

## Solution:

An N by N maze has $2N^2-2N$ possible walls between cells.  Why? There are $N^2$ cells. If we count 4 walls per cell, getting $4N^2$, we'll have double-counted all of the interior walls, and we'll have single-counted the $4N$ perimeter walls, which we don't want to count at all. So $2N^2$ single-counts the interior walls and still half-counts perimeter ones, and thus there are $2N^2-2N$ possible interior walls. For $N=10$, that's 180. Since each possible wall can either be there or not, and the finish cell can be any of the 100 cells, there are at most $100 \times 2^{180}$ possible mazes Obviously, the every-wall-up "maze" and the many "mazes" where the finish cell is completely walled-off are not real possibilities, but for simplicity we'll be over-counting.

Not every cell in a given maze has a path to the finish cell. The up to 99 cells that do are the possible starting cells for that maze. For each starting cell there is a solution: a sequence of moves that reaches the finish cell. For each maze, then, we generate a list by starting cell number (where the top row is 1 to 10 and the bottom is 91 to 100) of the up to 99 solutions.

We'll generate our instructions by going through the possible mazes one by one, and ensuring for each that, if we're in it, we'll find the finish. 

When we get to a given possible maze we consult our list of starting cells and corresponding solutions. We try the solution for the first starting cell, which will succeed if we started there (and are actually in that maze). Then, and here's the tricky bit, we try the solution for the cell that we would have ended up in if we'd started in the second starting cell and tried the first solution. That will succeed if we in fact started in the second starting cell. Then we try the solution for the cell we'd have ended up in if we started in the third starting cell and tried the first and second solutions. And so on. 

So we string together solutions, up to 99 for each starting cell in a maze, for the up to $100 \times 2^180$ possible mazes, guaranteeing that the robot will at some point reach the finish.

A solution is at most 99 moves, and it's not a terribly bold conjecture to assume that the average is below 50 moves. So a conservative upper bound on the number of moves contained in our instructions to the robot would be the product of:

$(100 \times 2^{180}) \times 99 \times 50 = 495,000 \times 2^{180}$

<br>
