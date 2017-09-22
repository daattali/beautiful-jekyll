---
layout: post
title: Quantum Teleportation - III
subtitle: Why Quantum Teleportation is Important
bigimg: "/img/teleport.jpg"	
image: "/img/teleport.jpg"
share-img: "/img/teleport.jpg"
tags: physics thesis 
---

[Last week](https://adivijaykumar.github.io/2017-09-16-teleportation-2/), I described how one can achieve quantum teleportation in principle. Okay, so teleportation is possible. But why should one be worried about it?

![](https://media.giphy.com/media/ttoX8zGGjlE8E/giphy.gif)

To see this, let's go back to my [first article](https://adivijaykumar.github.io/2017-09-09-teleportation-1), particularly the discussion on how a classical message sending protocol is not _secure_ in principle. Let us consider an analogous system in the quantum teleportation protocol. Lets say Eve manages to intercept the message by hook or crook. She still cannot extract any information about the qubits. Now comes the interesting part - Eve cannot extract any information about the qubits even by probing the environment! Let that sink in for a second and think what that implies.

![](https://media.giphy.com/media/4cUCFvwICarHq/giphy.gif)

The reason why that the environment cannot provide information is because it contains none in the first place. The entangled state of qubits that we started out with was _maximally entangled_. It helps to think of entanglement as a quantity that has a certain limiting maximum value - the state that we had has entanglement  exactly equal to that limiting value. This means that neither of the qubits can be entanhgled with any other entity, which in turn implies that there is no correlation between the environment and the qubits. Hence, the environment does not have any information to give away too.

The implication of this is quite mind-boggling. This means that quantum teleportation helps us send a message without any possibility of it being intercepted!

![](https://media.giphy.com/media/tITfss8cqzTO0/giphy.gif)

The fact that maximally entangled qubits cannot be entangled with anything else is called the _monogamy principle_ of entanglement. This principle has caused a stir among people studying the Black Hole Information Paradox, when a group of scientists suggested the [firewall resolution](https://www.quantamagazine.org/black-hole-firewalls-confound-theoretical-physicists-20121221/) to the paradox. I strongly encourage you read up about it, for getting a flavour of what is happening at the forefront of theoretical physics in the current day.

There is one more point to note about the quantum teleportation protocol. The monogamy principle also implies that the teleportee qubit got teleported to Bob with no information about it existing anywhere in between Alice and Bob. This tells us that information in quantum mechanics is non-local - it is shared between the states at any given point of time.

This concludes the series on quantum teleportation - I do hope to write further on this topic soon!

![](https://media.giphy.com/media/lD76yTC5zxZPG/giphy.gif)
