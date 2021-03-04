---
layout: post
title: Secure multi-party computation and oblivious transfer
subtitle: By Olivier Binette and Andy Demma
tags: [oblivious computation]
---

## Secure multi-party computation

**The problem is the following.** A set of $n$ parties, let's call them  $P_1, P_2, \dots, P_n$, wish to evaluate a function $\mathcal{F}$ based on their respective inputs $x_1, x_2, \dots, x_n$. That is, each party brings its own input $x_i$ , and the group's goal is to compute $\mathcal{F}(x_1, x_2, \dots, x_n)$. The constraint of secure multi-party computation is that each party's input $x_i$ is kept "private" in a sense which will be explained.


This problem is relevant to a variety of practical applications:

- **Secret ballot elections.** In a secret ballot election, the goal is to tally individual votes without revealing who voted for whom. Here $x_i$ is the $i$th individual's vote and the function $\mathcal{F}$ counts the votes for each candidate. Preserving the privacy of voters can protect against voter intimidation and retaliation.
- **Secure auctions.** Bidders may want to keep their bids private and only reveal the winner using secure multi-party computation.
- **Machine learning.** Data holders, such as health care providers, may be interested in statistics obtained from integrated databases. However, they are required by law to keep health records private. Secure multi-party computation can allow them to compute summaries of joint datasets without revealing individual records.

These applications each have specific requirements regarding the kind of privacy required and realistic threat models. In this post, we discuss the generic framework of secure multi-party computation (MPC), which can be used as a building block for these applications.

### Generic framework of MPC

#### What do we mean by privacy?

We presented MPC as preserving the "privacy" of the individual inputs $x_i$, but this is misleading. To be more precise, the goal of MPC is to ensure that no party (or group of parties) can learn more about an input $x_i$ than what **can be inferred** through their own inputs and the result $\mathcal{F}(x_1, x_2, \dots, x_n)$.

**This is a rather weak notion of privacy:** In many cases, inputs can be recovered from the result of the computation. For example, consider the conjunction function $\mathcal{F}(x_1, x_2) = x_1\hat{}x_2$ where $x_1, x_2 \in \{0,1\}$. If my input is $x_1 = 1$ and your input is $x_2$, then the result of the computation is equal to $x_2$ and thus necessarily revals your input to me. Protecting inputs from information leaked through $\mathcal{F}$ requires techniques such as **differential privacy**. We do still need MPC, however, as a primitive to carry out computations securely.

#### MPC protocols

Computation of the function $\mathcal{F}$ is carried out collaboratively through what is called an MPC protocol. This protocol dictates how parties share information to provide secure computation. We assume that pairs of parties can synchronously communicate on authenticated and secure channels. 

Through execution of a given protocol, each party obtains what is called a **view**: this contains the party's own input as well as the record of the execution of each protocol step. As previously stated, the goal of MPC is to ensure that each party's view, or any subset of party's views, reveals no more information than what can be infered through their inputs and the function's output. The threat model under which this must hold is discussed next.


#### Threat models

Here we assume the **semi-honest**, also called **honest-but-curious**, adversary model. That is, we assume that each party follows the prescribed protocol without any deviation. They may, however, use their view (and aggregate multiple parties' views) to attempt to learn about other parties' inputs. This is realistic in the scenario where parties are assumed to be honest, but their data storage could be compromised. Furthermore, we assume that there is a fixed set of possibly compromised parties which does not change through the execution of the protocol.

This semi-honest adversary model can be contrasted with the broader *malicious* adversary model. In this case, compromised parties can deviate arbitrarily from the given protocol. A particular feature of this model is that an adversary may obtain the result of the computation but refuse to share it with other parties. Ensuring that all parties necessarily receive the result of the computation is called **guaranteed delivery**; ensuring that all parties receive the result if at least one does is called **output fairness**.

<!-- https://www.ccs.neu.edu/home/rancohen/Papers/CL14.pdf-->
An important **feasability result** states that, under the malicious adversary model, fairness can be achieved if the number of compromised parties is a strict minority. If the number of compromised parties is a majority, then not all functions can be securely computed with fairness.



### Ideal/Real World Paradigm

Let us now precise the security framework which we consider. 

For simplicity, we can consider **information-theoretic security** where adversaries have unbounded computational power. We assume the existence of random functions, and of secure public and private key encryption. These two primitives are sufficient for this post. 

As discussed earlier, in the ideal world, parties can share their inputs with a trusted third party which returns the result of the computation to each of them. In the real world, instead, a protocol $\pi$ is executed collaboratively, resulting in a view $V_i$ for each party.

Now suppose that a set of parties $C$ is corrupted and semi-honest. In the real world, these parties each have a view $\{V_i\}_  {i \in C}$. In the ideal world, the behavior of these parties can be **simulated** as to result in a set of views $\{V_i'\}_  {i \in C}$. The simulated views $V_i'$ necessarily respect our notion of privacy since, in the ideal world, there is no communication between parties.

A protocol $\pi$ is said to be **secure** if, for any given set of inputs, the distribution of $\{V_i\}_  {i \in C}$ is equal to the distribution of $\{V_i'\}_  {i \in C}$. In other words, for any boolean function $D$ which attempts to determine whether a set of view was generated in the real world or in the ideal world, we have

$$
    \mathbb{P}(D(\{V_i\}_  {i \in C}) = 1) = \mathbb{P}(D(\{V_i'\}_  {i \in C}) = 1)
$$

**Note:** Within a computational security framework, we would require the two probabilities to be computationally indistinguishable rather than exactly the same. We would also rely on the weaker primitives of cryptographically secure pseudo-random functions and computationally secure encryption.

## Oblivious transfer

Consider the problem of secure 2-party computation of a function $\mathcal{F} : X\times Y \rightarrow Z.$
Given its input $x_1$, party 1 can compute all possibilities for the result of the computation as

$$
    \left(\mathcal{F}(x_1, y)\right)_ {y \in Y}
$$

If party 2 could obtain the value $\mathcal{F}(x_1, x_2)$ from party 1 without revealing its input $x_2$ and without learning about any other value $\mathcal{F}(x_1, y)$, $y \not = x_2$, this would solve the secure 2-party computation problem. Doing so is called **oblivious transfer**.

That is, suppose party 1, referred to as the **sender**, has a set of secrets $s_1, s_2, \dots, s_k$. The goal of oblivious transfer is to allow party 2, the **receiver**, to obtain any secret $s_i$ of their choice under the two following constraints:
- the sender does not know which secret $s_i$ was obtained, and 
- the receiver does not learn about any other secret $s_j$, $j\not = i$.

This is one way to enable multi-party computation.

### Simple protocol for oblivious transfer

We now introduce a very simple protocol for oblivious transfer in the context of two secrets ($k=2$) for simplicity. The sender has two secrets $s_1$ and $s_2$, while the receiver selects $i \in \{1,2\}$. 

The protocol is as follows. First, the sender generates two keys $k_1$ and $k_2$. It encrypts its secrets as $c_i = \text{Enc}_  {k_i}(s_i)$ and sends both pairs of keys and cyphertexts to the receiver. The receiver can then decrypt the secret of its choice and discard the other key. This process is secure as long as the receiver follows the protocol and does not decrypt the other secret.

The fact that the receiver must be trusted to discard a key is a major concern here. It can be fixed as follows:

1. The sender generates a random secret key $k_1$ and the receiver generates a random secret key $k_2$.
2. The sender shares the encryption function $\text{Enc}_ {k_1}$ to the receiver. Here we assume that the key $k_1$ cannot be inferred from $\text{Enc}_  {k_1}$.
3. The receiver chooses $i\in\{1,2\}$. If $i=1$, then the receiver shares the value $A = k_2$; otherwise they share $A = \text{Enc}_  {k_1}(k_2)$.
4. The sender shares the tuple $(B_1, B_2) = (\text{Enc}_ A(s_1), \text{Enc}_  {\text{Dec}_  {k_1}(A)}(s_2))$.
5. The receiver attempts to decrypt $B_1$ and $B_2$ using its secret key $k_2$. Only $B_i$ can be decrypted in this case. Indeed, if $i=1$, then $B_1 = \text{Dec}_  {k_2}(\text{Enc}_ A(s_1)) = s_1$ and  $B_2 = \text{Dec}_  {k_2}(\text{Enc}_  {\text{Dec}_  {k_1}(k_2)}(s_2))$ is meaningless. If $i=2$, then similarly only $s_2$ can be decrypted.

This can be implemented (in a computational security framework) by adapting the Diffie-Hellman key exchange protocol [(see Chou & Orlandi, 2015)](https://eprint.iacr.org/2015/267.pdf).

### Security analysis

The security of this protocol can be analysed using the real-world/ideal world paradigm. In the context of two parties, the goal is to show that the view of each party can be simulated in the ideal world as to be indistinguishable from its view in the real world.

Let's start by simulating the sender with secrets $s_1$ and $s_2$, where the view in the real world only contains $A$ (the key $k_1$ is inconsequential here). We simulate the reception of $A$ by sampling $A$ uniformly at random. This is indistinguishable from the real world where, by property of the encryption mechanism with a random key, $A$ is uniformly distributed at random.

Now let's simulate the view of the receiver. In the real world, their view contains the key $k_2$, the encryption function $\text{Enc}_  {k_1}$, and the values $B_1$ and $B_2$. In the simulation, we let $k_2$ and the encryption function be random. If $i=1$, then we set $B_1 = \text{Enc}_  {k_2}(s_1)$ and $B_2$ be random. If $i=2$, then we set $B_2 = \text{Enc}_  {k_2}(s_2)$ and $B_1$ be random. Again by known properties of the encryption function with random key, this is indistinguishable from the real world.

This proof may not cover all bases, but it roughly illustrates the concepts of the simulator and of indinstinguishability. A full detail of simulation proof for Oblivious Transfer for Semi-Honest Adversaries is explained in Section 4.3 from *How To Simulate It - A Tutorial on the Simulation Proof Technique* [(see Lindell, 2018)](https://eprint.iacr.org/2016/046.pdf)


## References

- [Evans, Kolesnikov & Rosulek (2018) A Pragmatic Introduction to Secure Multi-Party Computation](https://securecomputation.org/docs/pragmaticmpc.pdf).
