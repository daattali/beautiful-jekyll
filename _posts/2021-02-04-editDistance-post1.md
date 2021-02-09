---
layout : post
title : Understanding the Dynamic Programming Problem in Edit Distances
---

I have been recently dealing with string matching algorithms for a project I'm working on. I wanted to provide a brief explainer for how to interpret the dynamic programming problem in the simplest edit distance case.

# Edit Distance Problem

We have two strings $S_{1}$ and $S_{2}$, which have lengths $n$ and $m$. We want to calculate the minimum number of edits to transform $S_{1}$ into $S_{2}$.  We formalize this minimum distance using the function $D$, taking two arguments $(i,j)$, where $i$ and $j$ represent the last letter index in substrings of $S_{1}[1,..,i]$ and $S_{2}[1,..,j]$.

\begin{equation}
    D(i,j) = \text{Minimum Edit Distance b\w}\;S_{1}[1,..,i]\;\text{and}\;S_{2}[1,..,j]
\end{equation}

As an example, let's work with this very simple problem:

$$
\begin{align}
    S\_{1} &= vine \\
    S\_{2} &= vines
\end{align}
$$

Then $D(3,2)$ is the minimum edits needed to convert $vin$ into $vi$. 

# Dynamic Programming Problem

To solve this problem, we will use a dynamic programming setup. We define the following recurrence relation with the initial conditions. Note an index of 0 is equivalent to the empty string. 

<b><u> Initial Conditions </u></b>

$$
\begin{align}
    D(i,0) &= i\;\; \forall i \in \{1,..,m\} \\
    D(0,j) &= j\;\; \forall j \in \{1,..,n\} \\
\end{align}
$$

<b><u> Recurrence Relation </u></b>

$\forall \; i,j > 0$, $i \leq n$, $j \leq m$, we have the following recurrence relation:

<span>
$$
\begin{align}
    D(i,j) = \min\Big\{\underbrace{D(i-1,j) + 1}\_{Insertion}, \underbrace{D(i,j-1) + 1}\_{Deletion}, \underbrace{D(i-1,j-1) + t(i,j)}\_{Substitution} \Big\}
\end{align}
$$
</span>

We allow four operations. It is best to think about comparing the last letters in the sub-strings defined above. Our four operations are: 

1. Insertion : letter inserted at the end of $S_{1}[1,..,i]$
2. Deletion : letter deleted from the end of $S_{1}[1,..,i]$ 
3. Substitution : letter $S_{1}[i]$ is subsituted by $S_{2}[j]$
4. Exact Match : letter $S_{1}[i]$ is already the same as $S_{2}[j]$, and thus nothing is done.

## Intution for the Indices : Think Backwards

It took me a bit of time to understand what was happening to the indices. Let's start with the very last letters in both strings, this is equivalent to finding the minimum distance $D(4,5)$. This problem is the following:

$$
\begin{align}
D(4,5) = \min\Big\{\underbrace{D(4,4) + 1}\_{\text{Insertion}}, \underbrace{D(3,5) + 1}\_{\text{Deletion}}, \underbrace{D(3,4) + t(i,j)}\_{\text{Replace or March}} \Big\}
\end{align}
$$

Now let's briefly think through why the indices change in the way they do. I will highlight the current letter our index is pointing to. 

<b> Insertion </b> 

Insertion is equivalent to the following transformation:

\begin{align}
    S_{1}[1,..i] = vin{\bf{e}} \to vin{\bf{e}}s = S_{1}[1,..,i] + s
\end{align}

What happens to our pointers in the previous iteration, the idea is that we have now matched the added $s$ to the $S_{2}[5]=s$, so we iterate backwards for our index for $S_{2}$ but not for $S_{1}$.

Thus, with insertation the new indices are $(i,j-1)$.

<b> Deletion </b>

Deletion is equivalent to:

\begin{align}
    S_{1}[1,..i] = vin{\bf{e}} \to vi{\bf{n}} = S_{1}[1,..,i-1]
\end{align}

Now why might we delete? Remember, the recursion depends on prior decisions. So if the last letter in $S_{1}[1,..,i-1]$ is the same as the last letter $S_{2}[1,..,j]$, then maybe we are willing to sacrifice a high cost deletion for a low cost exact match. 

Thus, with deletion the new indices as $(i-1,j)$.

<b> Substitution or Exact Match </b>

This case is the easiest, we can see that the indices will just decrement $(i-1,j-1)$. 

## What is the best solution?

It depends on on the values of prior searchers. In the case above, it's pretty obvious that $D(4,4)=0$ because the two strings are equivalent, so deletion is the optimal choice. 


