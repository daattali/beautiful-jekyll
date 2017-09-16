---
layout: post
title: Quantum Teleportation - II
subtitle: The Teleportation Protocol
bigimg: "/img/teleport.jpg"	
image: "/img/teleport.jpg"
share-img: "/img/teleport.jpg"
tags: physics thesis 
---
In the [previous article](https://adivijaykumar.github.io/2017-09-09-teleportation-1/), I briefly described what entanglement is, and also discussed how one can send a classical message. Just to remind you of the takeaways :-

* Entangled particles cannot be described independently of each other. Describing one amounts to describing the other.

* Theoretically, every classical message sending protocol can be hacked, and hence is not secure.

Cool?

![](https://media.giphy.com/media/DfdbTJZx6Yjra/giphy.gif)

Okay. Anyway, let's proceed.

Before talking about what the protocol for quantum teleportation is, I would like to briefly talk about -

# Measurements in Quantum Mechanics

Let us consider, like in the previous post, the state of a single particle 

$$ |\psi \rangle = \frac{1}{\sqrt{2}} |0 \rangle + \frac{1}{\sqrt{2}} |1 \rangle $$

Recall that measuring this particle would yield $0$ or $1$ with equal probability. One thing to note is that, after measurement, the state of the particle collapses to the measured state. For example if $\psi$ is measured, and we find the outcome to be $0$, the state of the particle after the measurement 

$$ |\psi \rangle_{post-measurement} =|0 \rangle$$

We can also construct our measurement apparatus so as to measure $\psi$ in a different basis states. we could use the basis :-

$$ |B_1 \rangle = \frac{1}{\sqrt{2}} |0 \rangle + \frac{1}{\sqrt{2}} |1 \rangle $$

$$ |B_2 \rangle = \frac{1}{\sqrt{2}} |0 \rangle - \frac{1}{\sqrt{2}} |1 \rangle $$

This would imply that $\psi$ is always measured as $B_1$.

#Enough with Math, get me teleported!

Okay, but really, you can't escape the math! There is a lot it ahead.

![](https://media.giphy.com/media/l0K4cW9NQjrOlhy2Q/giphy.gif)

Instead of classical bits of information, we consider quantum bits or qubits. Lets say, without loss of generality, Alice and Bob have a qubit each in the normalized entangled state

$$\frac{1}{\sqrt{2}}|00 \rangle + \frac{1}{\sqrt{2}}|11 \rangle$$

Alice and Bob are currently far away from each other. Alice has one more qubit in the state

$$|\phi \rangle = \alpha |0 \rangle + \beta |1 \rangle$$

We call this qubit the _teleportee_ qubit. An important thing to note is that all 'information' about the teleportee qubit is contained in the numbers $\alpha$ and $\beta$. We shall consider the teleportation successful if the state $\phi$ somehow appears on Bob's side.

We can write the combined state of the three qubits by taking a tensor product as follows

$$\frac{\alpha}{\sqrt{2}}|000 \rangle + \frac{\alpha}{\sqrt{2}}|011 \rangle + \frac{\beta}{\sqrt{2}}|100 \rangle + \frac{\beta}{\sqrt{2}}|111 \rangle \label{combstate}

with the first entry denoting the teleportee, second denoting Alice's qubit and third denoting Bob's qubit.

We shall now measure the two qubits in Alice's possession (ie. first and second entries) in a basis called the Bell Basis. The normalized Bell basis vectors are given by

$$|B_1 \rangle = \frac{1}{\sqrt{2}}|00 \rangle + \frac{1}{\sqrt{2}}|11 \rangle $$

$$|B_2 \rangle = \frac{1}{\sqrt{2}}|01 \rangle + \frac{1}{\sqrt{2}}|10 \rangle $$

$$|B_3 \rangle = \frac{1}{\sqrt{2}}|00 \rangle - \frac{1}{\sqrt{2}}|11 \rangle $$

$$|B_4 \rangle = \frac{1}{\sqrt{2}}|01 \rangle - \frac{1}{\sqrt{2}}|10 \rangle $$

We can relate the normal basis to the Bell basis as

$$|00 \rangle = \frac{|B_1 \rangle + |B_3 \rangle}{\sqrt{2}} $$

$$|10 \rangle = \frac{|B_2 \rangle + |B_4 \rangle}{\sqrt{2}} $$

$$|01 \rangle = \frac{|B_2 \rangle - |B_4 \rangle}{\sqrt{2}} $$

$$|11 \rangle = \frac{|B_1 \rangle - |B_3 \rangle}{\sqrt{2}} $$

Substituting these expressions in \ref{combstate}, one can write the combined state as 

$$\frac{|B_1 \rangle(\alpha|0 \rangle + \beta |1 \rangle) + |B_2 \rangle (\alpha |1 \rangle + \beta |0 \rangle) + |B_3 \rangle (\alpha|0 \rangle - \beta |1 \rangle) + |B_4\rangle (\alpha|1 \rangle - \beta |0 \rangle)}{2}$$

We can clearly see from this state that any measurement in the Bell basis will give $B_1, B_2, B_3$ or $|B_4 \rangle$ with equal probability (25 percent). After the measurement, Bob's qubit is left in the state

$$\alpha|0 \rangle + \beta |1 \rangle $$

$$\alpha|1 \rangle + \beta |0 \rangle $$

$$\alpha|0 \rangle - \beta |1 \rangle $$ and 

$$\alpha|1 \rangle - \beta |0 \rangle $$ respectively.

Note that by this measurement, we have sent across the numbers $\alpha$ and $\beta$. But the state on Bob's side need not be the same as the state of the  teleportee qubit, as is evident from above. So what now?

![](https://media.giphy.com/media/3og0ICZh82LEsNjHoc/giphy.gif)

We still haven't done one thing we did in the classical messaging protocol - sending across the result of the measurement. Alice, through a classical message, sends the result of her measurement to Bob. Bob, depending on the classical message, applies an appropriate action on his state to take it to the state $\phi$. For example, let's say that Alice measured her qubits in the basis state $B_2$. Corresponding to $B_2$, Bob's qubit is in the state,

$$\alpha|1 \rangle + \beta |0 \rangle $$

Bob just needs to change the $1$ to $0$ and the $0$ to $1$. He can achieve this by applying a unitary operation on his state. Mathematically, a unitary operator is one which preserves lengths, or basically, doesn't change the information content of the system.

Similarly, corresponding to different classical messages from Alice, Bob can use different unitary operations such that the final state of his qubit is 

$$\alpha|0 \rangle + \beta |1 \rangle $$

So cool, no? 

![](https://media.giphy.com/media/xT4uQkpdmRXh4iIxTG/giphy.gif)

So this post would have seemed very mathematical, but that is how all of physics is! Next week, I shall discuss why we did all this math, and why really quantum teleportation is so interesting. I have dropped some clues along the way, see if you can figure it out!

Until then, stay tuned. Tada!