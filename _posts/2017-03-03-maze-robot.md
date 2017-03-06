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

An N by N maze has $2N^2-2N$ possible walls between cells.  Why? There are $N^2$ cells. If we count 4 walls per cell, getting $4N^2$, we'll have double-counted all of the interior walls, and we'll have single-counted the $4N$ perimeter walls, which we don't want to count at all. So $2N^2$ single-counts the interior walls and still half-counts perimeter ones, and thus there are $2N^2-2N$ possible interior walls. For $N=10$, that's 180. Since each possible wall can either be there or not, and the finish cell can be any of the 100 cells, there are at most $100 \times 2^{180}$ possible mazes. 

The "mazes" where the finish cell is completely walled-off are not real possibilities. There are 

$(4\times 2^{178}) + (32\times 2^{177}) + (64\times 2^{176}) = 9\times2^{180}$ 

of these, corresponding to whether the finish cell is a corner, on the sides, or in the interior. So there are $91 \times 2^{180}$ genuinely possible mazes.

Not every cell in a given maze has a path to the finish cell. The up to 99 cells that do are the possible starting cells for that maze. For each starting cell we choose a solution: a sequence of instructions for moves that reach the finish cell. A solution is at most 99 moves, and in the worst case in which a solution does have 99 moves, the average length of a solution in the maze is 50. For each maze, then, we generate a list by starting cell number (where the top row is 1 to 10 and the bottom is 91 to 100) of the up to 99 solutions.

We generate our instructions by going through the possible mazes one by one, and ensuring for each that, if we're in it, no matter which starting cell we start in, we'll find the finish. 

When we get to a given possible maze we consult our list of starting cells and corresponding solutions. We tack onto our instructions the solution for the first starting cell, which will succeed if we started there (and are actually in that maze). Then, and here's the tricky bit, we tack on the solution for the cell that we would have ended up in if we'd started in the second starting cell and tried the first solution. That will succeed if we in fact started in the second starting cell. Then we tack on the solution for the cell we'd have ended up in if we started in the third starting cell and tried the first and second solutions. And so on. 

So we string together, for each of the  $91 \times 2^{180}$ possible mazes, up to 99 solutions, averaging no more than 50 moves each, guaranteeing that the robot will at some point reach the finish.  That gives us a conservative upper bound on the number of moves contained in our instructions to the robot:

$(91 \times 2^{180}) \times 99 \times 50 = 450,450 \times 2^{180}$

$ = 690312616383039636247517418379856771761061037587603600179200$

$ \approx 6.90 \times 10^{58} $

\ldots or about 690 octodecillion instructions.

To automate the generation of these instructions, the only non-trivial question is how to determine whether a cell in a maze is a starting cell, and what its alphabetically-first shortest solution is. This can be done (inefficiently, but we don't care about that) simply by trying, in alphabetical order, every 1-move sequence, every 2-move sequence, and so on up to 99-move sequences, stopping if you reach the finish. If you do reach the finish cell, that's your solution; if you never do, it's not a starting cell.

<br>
