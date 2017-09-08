---
layout: post
title: Quantum Teleportation - I
subtitle: Entanglement and Classical Messaging
bigimg: "/img/angamaly.jpg"
image: "/img/angamaly.jpg"
share-img: "/img/angamaly.jpg"
tags: physics thesis 
---

This marks the start to a series of posts about entanglement in quantum mechanics and its applcations to teleportation.

Looking at the title, you might have thought this would be about 

<iframe src="https://giphy.com/embed/l9NWUY0X6ULRK" width="480" height="340" frameBorder="0" class="giphy-embed" allowFullScreen></iframe><p><a href="https://giphy.com/gifs/wiki-vlad-teleportationgif-l9NWUY0X6ULRK"></a></p>

It is, and it isn't. Quantum Teleportation is very peculiar and gives rise to loads of paradoxes. I hope to explain it as clearly as possible, so stay tuned!
# Entanglement? What's that?

Quantum Mechanics is weird. It contradicts numerous classical notions of the world as we know it. But what's remarkable about QM is that despite being weird, it is the best description one has of nature.

One weird feature of QM is **entanglement**. Entanglement basically refers to a correlation between the measured properties of two separate particles. What this means is that a single particle cannot be described independently of the other particle. One cannot write the state of each individual particle separately - the only description one has in such a situation is the _combined_ state of both the particles.

To get a clearer view of entaglement, it is worth understanding how a single particle in quantum mechanics is described. Lets say we want to measure the spin of this particle - whether it is _up_ or _down_. As you [might know already](https://en.wikipedia.org/wiki/Schr%C3%B6dinger%27s_cat), the spin of the particle at any given instant is neither _up_ nor _down_, but in fact a **superposition** of the two configurations. It is only the act of measuring that makes the spin take either of the values. If we prepare a large ensemble of identical particles and start measuring their spins one by one, we'll get _up_ and _down_ as the spin values with equal probability. This can be represented mathematically by a state $$ |\psi \rangle $$ as

$$ |\psi \rangle = \frac{1}{\sqrt{2}} |0 \rangle + \frac{1}{\sqrt{2}} |1 \rangle $$

where $ |0 \rangle $ represents spin _up_ and $ |1 \rangle $ represents spin _down_. The coefficients in front of $ |0 \rangle $ and $ |1 \rangle $ are fixed such that the square of the coefficients gives the probability of finding the particle in the corresponding state. Obviously, the squares of all the coefficients should add up to one, as the sum of probabilities should be one.

How do we write the combined state for two independent particles in this prescription? We take something called the **tensor product**. I illustrate it below :-

$$(\frac{1}{\sqrt{2}}|0 \rangle + \frac{1}{\sqrt{2}}|1 \rangle) (\frac{1}{\sqrt{2}}|0 \rangle + \frac{1}{\sqrt{2}}|1 \rangle) = \frac{1}{2}|00 \rangle + \frac{1}{2}|01 \rangle + \frac{1}{2}|10 \rangle + \frac{1}{2}|11 \rangle $$

But now lets consider the  state 

$$ \frac{1}{\sqrt{2}}|00 \rangle + \frac{1}{\sqrt{2}}|11 \rangle $$

One can not imagine taking the tensor product of any two state to obtain the above state. This is an example of an entangled state. The description cannot be decomposed into two separate states, and the states can only be defined **together**.

Note that we can still independently measure the particles. But the interesting part is that the measurement on any one particle _fixes_ the state in which the other particle is measured. The measurements are correlated!

![](https://media.giphy.com/media/5aLrlDiJPMPFS/giphy.gif)

Entanglement is contrary to anything classical, and is often referred to as the **essence of quantum mechanics**.

# How do I send a secure message classically?
Let's suppose Alice and Bob are far away from each other and have one classical bit of information each. They also have a channel to communicate messages. Each bit can take value 0 or 1, but lets say that both bits have the same value. Alice and Bob could have met at some time in the past, created their bits, assigned them the same value and then moved on to their respective present positions.

Alice has one more bit with her - and she wishes to send the configuration of this bit to Bob. Lets call the bit the _teleportee_ bit. She proceeds to compare both bits in her possession. If both the bits in her possession are of the same value she sends Bob a classical message reading _same_; if the bits have different value the message reads _different_. Bob, on looking at the message, flips the value of the bit if the message reads _different_ and does not if it reads _same_. So, whatever the initial value of Bob's bit, he always ends up with his bit in the same state as that of the teleportee bit.

Now lets suppose Eve wants to snoop in and know the respective configurations in the protocol. She intercepts the communication channel sent from Alice to Bob. Obviously, she cannot know anything about the original state of the teleportee bit solely from this information. But, in principle, she can probe the brain waves or the gravitational waves around Alice and in the environment to know exactly what the state of the bit was. So, in a sense, we could say that the information about the teleportee bit did in fact exist in the environment between Alice and Bob and we can measure it in principle.
\item This also implies that the teleportee qubit got teleported to Bob with no information about it existing anywhere in between Alice and Bob. This tenet of non-locality of information is crucial to quantum mechanics.
\item The process of measuring the qubits destroys the existing entanglement between the qubits.
\end{itemize}