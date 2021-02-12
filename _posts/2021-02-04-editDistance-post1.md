---
layout : post
title : Understanding the Dynamic Programming Problem in Edit Distances
---

I have been recently dealing with string matching algorithms for a project I'm working on. I wanted to provide a brief explainer for how to interpret the dynamic programming problem in the simplest edit distance case.

# Edit Distance Problem

We have two strings $S_{1}$ and $S_{2}$, which have lengths $n$ and $m$. We want to calculate the minimum number of edits to transform $S_{1}$ into $S_{2}$.  

As a very simple case, say we want to compute the minimum number of edits it takes to transform $vine$ into $vines$: 

\begin{align}
    S\_{1} &= vine \\\\\\
    S\_{2} &= vines
\end{align}

We formalize this minimum distance using the function $D$, taking two arguments $(i,j)$, where $i$ and $j$ represent the last letter index in substrings (or suffixes) of $S_{1}[1,..,i]$ and $S_{2}[1,..,j]$:

\begin{equation}
    D(i,j) = \text{Minimum Edit Distance b\w}\;S_{1}[1,..,i]\;\text{and}\;S_{2}[1,..,j]
\end{equation}

Note, that $D$ is just a value function in the language of dynamic programming. For our application, $D(4,5)$ is the minimum edits needed to convert $vine$ into $vines$. 

# Dynamic Programming Problem

For this specific edit distance setup, we allow four operations. It is best to think about comparing the last letters in the sub-strings defined above. Our four operations are: 

1. Insertion : letter inserted at the end of $S_{1}[1,..,i]$
2. Deletion : letter deleted from the end of $S_{1}[1,..,i]$ 
3. Substitution : letter $S_{1}[i]$ is subsituted by $S_{2}[j]$
4. Exact Match : letter $S_{1}[i]$ is already the same as $S_{2}[j]$, and thus nothing is done.

To solve this problem, we will use a dynamic programming setup. We define the following recurrence relation with the initial conditions. Note an index of 0 is equivalent to the empty string. 

To define this setup, we need to define some cost of performing the operations. We will use the following costs:

1. c(Insertion) = 1
2. c(Deletion) = 1
3. c(Substitution) = 2
4. c(Exact Match) = 0

<b><u> Initial Conditions </u></b>

$$
\begin{align}
    D(i,0) &= i\;\; \forall i \in \{1,..,m\} \\
    D(0,j) &= j\;\; \forall j \in \{1,..,n\} \\
\end{align}
$$

<b><u> Recurrence Relation </u></b>

$\forall \; i,j > 0$, $i \leq n$, $j \leq m$, we have the following recurrence relation:

$$
\begin{align}
    D(i,j) &= \min\Big\{\;D(i-1,j) + 1,\;D(i,j-1) + 1,\;D(i-1,j-1) + t(i,j) \Big\} \\
           &= \min\Big\{\;Insertion,\;Deletion,\;Substitution\;or\;Exact \Big\}
\end{align}
$$


## Intution for the Indices : Think Backwards

It took me a bit of time to understand what was happening to the indices. Let's start with the very last letters in both strings, this is equivalent to finding the minimum distance $D(4,5)$. This problem is the following:

$$
\begin{align}
D(4,5) &= \min\Big\{D(4,4) + 1, D(3,5) + 1, D(3,4) + t(i,j) \Big\}
\end{align}
$$

Now let's briefly think through why the indices change in the way they do. I will highlight the current letter our index is pointing to. 

<b> Insertion </b> 

Insertion is equivalent to the following transformation:

\begin{align}
    S_{1}[1,..i] = vin{\bf{e}} \to vin{\bf{e}}s = S_{1}[1,..,i] + s
\end{align}

What happens to our pointers in the previous iteration. We basically fill in a "gap" or empty space at the end of $S_{1}$, this "gap" is paired with the $s$ at the end of $S_{2}$. Thus, we iterate backwards for our index for $S_{2}$ but not for $S_{1}$.

Thus, with insertation the new indices are $(i,j-1)$.

<b> Deletion </b>

Deletion is equivalent to:

\begin{align}
    S_{1}[1,..i] = vin{\bf{e}} \to vi{\bf{n}} = S_{1}[1,..,i-1]
\end{align}

If we are thinking about "gaps", deletion is the "inverse" operation of insertion. We now insert a "gap" at the end of $S_{2}$, this gap is paired with the $e$ at the end of $S_{1}$. 

Thus, with deletion the new indices as $(i-1,j)$.

As an aside, why might we delete? Remember, the recursion depends on prior decisions. So if the last letter in $S_{1}[1,..,i-1]$ is the same as the last letter $S_{2}[1,..,j]$, then maybe we are willing to sacrifice a high cost deletion for a low cost exact match. 

<b> Substitution or Exact Match </b>

This case is the easiest, we can see that the indices will just decrement $(i-1,j-1)$. 

## What is the best solution?

It depends on on the values of prior searchers. In the case above, it's pretty obvious that $D(4,4)=0$ because the two strings are equivalent, so deletion is the optimal choice. 


