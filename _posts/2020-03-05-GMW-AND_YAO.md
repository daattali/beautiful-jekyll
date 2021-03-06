---
layout: post
title: Oblivious Parallel RAM
subtitle: By Anurag Kashyap and Rahul Ramesh
tags: [GMW, Yao's Garbled Circuits]
---

# Yao's Garbled Circuits

### Introduction
The fundamental problem in secure multiparty computation is to compute a function $F(x_1,x_2,\ldots)$ where the input $ x_i $ is known only to party $P_i$, in a way that no party should learn anything that they couldn't have deduced from their own input and the value of $ F(x_1, x_2, \ldots) $.
For now, we assume there are only two parties $P_1, P_2$.

1.  Assume both $P_1$ and $P_2$ mutually agree upon a circuit $C$ that represents $F$.
2. Without loss of generality, assume circuit $C$ only contains XOR, NOT, and AND gates.
3.  P1 has access to a random oracle or a pseudorandom function.

### Setup
Here, $P_1$ generates a garbled circuit and sends it to $P_2$ to compute.
Suppose that the circuit $C$ consisted of a single logic gate $G$. $G(x,y)$ is a boolean function of the type $Bool * Bool \rightarrow Bool$. Since a boolean variable can only take 2 values, the domain of $G$ has size 4. We can just represent $G$ as a lookup table of size 4. For example, the lookup table of an AND gate would be:


| x | y | AND(x,y) |
| -------- | -------- | -------- |
| 0     | 0     | 0     |
| 0     | 1     | 0     |
| 1     | 0     | 0     |
| 1     | 1     | 1     |


In fact, this is exactly what $P_1$ does for the NOT, XOR, and AND gates. It creates a lookup table. 
The next step is to 'garble' the circuit. For each possible value of $x$ and $y$, $v_x$ and $v_y$, $P_1$ generates random keys $k_x^0$, $k_x^1$, $k_y^0$,  and $k_y^1$. Then it encrypts the values $G(v_x, v_y)$ with both $k_y^{v_y}$ and $k_x^{v_x}$ such that it can only be decrypted with both keys but not with any one. Thus, the new table looks as follows:



| x | y | Enc(AND(x,y)) |
| -------- | -------- | -------- |
| 0     | 0     | $Enc_{k_x^{0}, k_y^{0}}(0)$     |
| 0     | 1     | $Enc_{k_x^{0}, k_y^{1}}(0)$      |
| 1     | 0     | $Enc_{k_x^{1}, k_y^{0}}(0)$      |
| 1     | 1     | $Enc_{k_x^{1}, k_y^{1}}(1)$      |


Keep in mind that every possible output of $G$ is encrypted with a different pair of keys. Now, to compute $G$ together, $P_1$ and $P_2$ must know both the keys without knowing each other's inputs. 
This is accomplished in the following manner:
1. $P_1$ sends the last column of the table (containing only the garbled values) to $P_2$.
2. Since $P_1$ knows the value of $x$, she sends $k_x^{v_x}$ to $P_2$.
3. $P_2$ obtains $k_y^{v_y}$ by Oblivious Transfer from $P_1$. Thus, $P_1$ doesn't learn $v_y$.
4. $P_2$ can now use both $k_x^{v_x}$ and $k_y^{v_y}$ to decrypt the corresponding entry in the table.

A subtle point here is that $P_2$ must know which entry to decrypt and decryption must not reveal the $v_x$. To accomplish  the latter, $P_1$ permutes the table. This can be done by generating random tags for each entry in the table and then sorting the table by the random tags. For the former, we ensure that the last bit of each key is a pointer to the permuted table telling $P_2$ which entry to decrypt. This method is called point-and-permute.


### Composing Gates

The circuit $C$ which represents $F$ will typically contain more than one gate. If we recursively apply the same procedure above to each layer of the circuit $C$, then the intermediate values of the circuit will be revealed to both parties, which undermines the security of Yao's protocol. Thus, the secure computation of these gates must be composed in a way that preserves the secrecy of intermediate outputs. Yao's protocol accomplishes this in a very clever way. 

1. For every wire $w_i$ in $C$, $P_1$ creates keys for both values that $w_i$ can take.
2. For every gate $G\epsilon C$, with input wires $x,y$ and output wire $w$, the permuted lookup table now stores $Enc_{k_x, k_y}(k_w)$.
3. $P_2$ computes each input gate as explained above, using Oblivious Transfer.
4. For any intermediate gate, $P_2$ knows both the keys (but not the values) because it has decrypted the keys from the lookup table.
5. $P_2$ recursively computes every subsequent gate/layer in the circuit until it has obtained the key of the output wire.
6. $P_1$ shares a lookup table with $P_2$ which maps the keys of the output wire to the corresponding values. This table could also be shared in the initial phase of the protocol to avoid another round of communication.

### Security
Yao's protocol is secure in the semi-honest model.
$P_1$ never communicates with $P_2$ after sending the garbled circuit and output decoding table. The only communication that happens besides this is the oblivious transfer, which is already known to be secure. Even if $P_2$ is corrupt, the protocol is secure because $P_2$ never sees 2 keys for the same wire. Hence, the protocol is secure.


### Analysis
Yao's protocol runs in constant rounds but the number of Oblivious transfers required is linear in the number of input gates in the circuit. Thus, the communication complexity can be high.

# Goldreich-Micali-Wigderson (GMW) Protocol

### Motivation

Yao's Garbled circuits does not generalize easily to more than three parties. It is unclear how parties would be assigned generator or evaluator roles, without significant modifications to the protocol. The GMW approach is an alternate framework in which the two player themselves hold shares of the final answer to a logic gate. Thus, GMW more directly extends to a variable amount of parties.


### Protocol

Two players, $P_1$ and $P_2$, each provide a single input ($x$ and $y$ respectively). We assume these are boolean inputs, though the protocol can be generalized to arithmetic expressions, as well as circuits with more than two parties. 

Each player generates a random bit mask $r$ of the same length as their inputs. If $x_i \in \{0,1\}$, $r_1 = \{0,1\}^n$ where $n$ is the length of the original input in bits, and each bit is chosen uniformly at random. 

Each player exchanges the random mask generated with the other player. Player 1 obtains a secret sharing of each of their own inputs $x_i$ with $x_i \oplus r_{1,i}$. Player 2 obtains their own share with $y_i \oplus r_{2,i}$.

In the below diagram, $x$ and $y$ are the respective inputs of the players. $x_1$ and $y_1$ are the shares generated by $x \oplus r_1$ and $y \oplus r_2$. Finally $x_2$ and $y_2$ are the random bit masks themselves $r_1$ and $r_2$ being sent over. This is an example of how the XOR operation can be calculated securely.

Demonstration of XOR, courtesy Olivier Binette.

![test](../_images/XOR_diagram.PNG)


To prove this works for an XOR gate, remember we are trying to calculate $x \oplus y$. We know $x = (x \oplus r_1) \oplus r_1$ by the associativity of XOR. Similarly, $y = (y \oplus r_2) \oplus r_2$. Consequently, $x \oplus y = ((x \oplus r_1) \oplus r_2) \oplus ((y \oplus r_2) \oplus r_1)$. This concludes GMW gives each party a secret share of the original computation.

We can replicate a similar proof for the AND operation, albeit with more steps and some clever use of Oblivious Transfer (OT). Specifically, the protocol utilizes the 1-out-of-4 OT, which provides Player 2 the opportunity to securely look at one of four values Player 1 provides (the table of OT secrets). Player 2 does not see the other three values, and Player 1 does not see which value Player 2 looked at.

For $P_1$, its shares do not change. They know that $P_2$ has two of their own Boolean input shares, which means that there are four possible options for the pair of $P_2$ shares. $P_1$ thus prepares a secret share that corresponds with each possible combination of $P_2$'s share.

Let $s_i = x_i \oplus r_{1,i}$, which Player 1 generates, and $s_j = r_{2,i}$, which Player 1 receives from Player 2.

Each row of the secret table is $r_{1,i} \oplus (s_i^1 \oplus i)  ^ (s_j \oplus j)$, where $(i, j) \in \{(0, 0), (0, 1), (1, 0), (1, 1) \}$

$P_2$ indexes this table based on its own bit shares, and chooses the corresponding row to continue with the calculation. Both players end up with a share of the final answer which can be revealed. 



# Generalization

### Arithmetic Gates}

Arithmetic gates can easily be reconstructed through combinations of the logic gates of AND, NOT, and XOR. For any additional gate, each player can generate an additional random bit mask and the two players can exchange them, to each build a share of the final answer.

### >2 parties}

A similar procedure can be used to apply the GMW idea to a setting with $l$ players. Consider the case where players $P_1, P_2, P_3, ..., P_l$ want to evaluate a boolean circuit. Each player $P_j$ secret-shared its own input by generating $l-1$ random bit masks of length $n$, and sending each mask to all other $P_{i \ne j}$.

Addition is slightly more complicated. For some AND gate $c = a ^ b$, each player $l$ has two shares, $a_l$ and $b_l$. 

$c = a ^ b = (a_1 \oplus ... \oplus a_l) ^ (b_1 \oplus ... \ \oplus b_1)$

$= (a_i \oplus b_i) \forall\ i\ \oplus (a_i \oplus b_j) \forall\ i \ne j$

Each step of this process can be computed pairwise by implenting the two player game as described above.


# Notes

### Adversaries

GMW remains secure for any amount of semi-honest adversaries. Professor Benny Pinkas proves this through constructing a simulation of the protocol. The goal of the simulation is that, given the input and output, the view of an adversary can be determined. This would prove the adversary learns nothing from the execution of the protocol. Assume, as a worst case, that an adversary controls all $l$ players except, without loss of generality, Player 1. The simulation attempts to find out if the adversary can learn $P_1$'s input through the various secrets. The simulation is given all of the inputs and outputs for players $1 < j \leq l$. Since each step of the simulation is uniform random or unknown (the random shares sent to $P_1$, the random outputs, the unknown OT, or the random output wire from $P_i$), the output of the simulation is distributed identically to the adversary's view. 

GMW protocol remains secure with any number of malicious adversaries, given that they cannot abort and stop communication/computation. If they can, however, abort, then, GMW can still remain secure against a minority of malicious parties. 


### Setting

Communication between parties can occur in a number of ways. However, It is critical that between any pair of parties, communication must be private (encrypted). Otherwise, 

### Performance

Implementation of this protocol is quite slow. An oblivious transfer must be used for every AND (multiplication) gate. Communication must be done between all parties every round, which adds an additional layer of complexity. However, there are ways to optimize AND gate computation. If input wires between parties are already shared, multiple AND gates can be processed together, which implies that the number of rounds is proportional to the depth of the circuit.

