---
layout: post
title: Introduction to Oblivious RAM
subtitle: Andrew Demma and Anurag Kashyap
tags: [oblivious computation]
---

In several settings, an eavesdropping adversary can learn sensitive information just from the memory access patterns in a computer/network. An access pattern is defined as a sequence $[A_1, A_2, \ldots ]$ of memory addresses that a user/client wants to access in the exact order in which they appear in the list.

Consider the scenario where a client wants to access a large collection of files in the cloud, which are stored in a distributed manner across many computers, and the files are organized by topic in this cluster of computers. The router or Internet Service Provider will be able to see the IP addresses in every request and may be able to deduce sensitive information regarding the program being executed by the client. Analogously, consider the scenario where a malicious program/device has access to the bus connecting the CPU and RAM in a computer and can see the memory locations being accessed by the CPU. Even in this case, sensitive information about the program being executed on the CPU can be leaked to the malicious third party observing the memory access patterns. The solution to this problem that we discuss in this article is called Oblivious RAM or ORAM. Oblivious here means that the specific sequence of memory locations accessed during the execution of the program is independent of the program. Such obfuscation must necessarily have a price in terms of time and space complexity, but what does that cost? How much slowdown must the program incur to hide the access patterns? Moreover, does such a model of computation even exist?

The seminal paper in this field was published by Ostrovsky where he constructed an Oblivious RAM computer. In this article, we'll see his construction in detail and the Square-Root solution.

## Square-Root Solution

The problem is formulated as follows: There is a client/CPU (with access to a PRF, call it F) that wants to obliviously execute a program and access servers/RAM during the course of its execution. The goal is to run the program in a way that the access pattern is independent of the input for any two inputs of the same size.

To see that constructing an ORAM is possible, consider the situation where the CPU scans the whole memory for every instruction in the program. This is clearly an oblivious protocol since the access pattern is independent of the input. However, this protocol is also likely to be very slow and infeasible. The square-root solution is a significant improvement over this model and we will see its construction now.

Suppose we know the amount of memory required by the program in advance, call it $latex N$. Henceforth, the term 'virtual memory address' will mean an address in the RAM. The construction can be broken down into 3 parts: Setup, Read Protocol, and the Write Protocol.

**Setup**. In this step, the CPU generates two keys $K_1$ and $K_2$. The first key is used to encrypt the data on the RAM and the second key is used to generate the tags for every memory location.

Now, the CPU goes over memory locations 1 to N and augments every memory location in the RAM as follows:

$RAM_{2}[i] = RAM[i], i, tag_{i}>$

That is, every memory location now contains its virtual address and a tag along with its original content. The $latex tag_i$ is the tag for the $i$-th virtual address, generated as follows $latex tag_i = F_{K_2}(i)$. The tag will be used to permute the RAM and lookup the contents of the permuted RAM.

Now, we create a new memory $latex RAM_3$ which contains all of $latex RAM_2$ but also contains $latex \sqrt{N}$ extra memory locations. For $latex N+1 \leq j \leq N + \sqrt{N}$, let $latex RAM_3[j] = <0, \infty_{1}, tag_j>$ where $latex \infty_1 >N + 2\sqrt{N}$. We call this region of $latex \sqrt{N}$ memory cells the 'dummy region'.

Since the tags are pseudorandom, if the RAM were to be sorted by the tags, it would be a pseudorandom permutation! This is exactly the next step in the construction, we sort the RAM by the tag values. For any two memory locations $latex i,j$ memory location $latex i$ is 'lesser' than location $latex j$ if $latex tag_i < tag_j$. In the subsection on Bitonic sort, we will see how this step can be done obliviously.

The next step is to encrypt all of RAM using the secret key $latex K_1$ as follows. For $latex 1 \leq i \leq N+\sqrt{N} $

$latex RAM_4[i] = Enc_{K_{1}}(RAM_3[i])$

Finally, it appends $latex \sqrt{N}$ elements to $latex RAM_4$, each of which contains an encryption of 0 under key $latex K_1$. We call this region the 'shelter' or the 'cache'.

Now our setup is complete. The CPU can read any virtual address i by obtaining its tag and then doing an interactive binary search with the RAM to find the location in memory which had virtual address i.

The RAM is reshuffled and encrypted again after every $latex \sqrt{N}$ I/O operations. A register counter variable keeps track of the number of I/O operations completed.

There are two operations that need to be defined before we explain how read and write protocols work. 

The **GET** operation takes as input a virtual memory address i and obtains $latex tag_i$ and finds the tag in RAM through an interactive binary search. This is possible because the RAM is sorted by tags. In other words, it asks the server for the item stored at location N/2 (assume N is even) decrypts it and compares its tag with $latex tag_i$. If $latex tag_i$ is less than the tag of item ORAM[N/2], then it asks for the item at location N/4; else it asks for the item at location 3N/4; and so on.

Once the item with $latex tag_i$ has been fetched from ORAM, the CPU decrypts it locally. It then re-encrypts item i (possibly to something different) and asks the memory to store it at the same location. The **PUT** operation takes as input a virtual memory address and a value $latex v$ to be inserted in that location. It first calls GET(i) as above and then encrypts $latex v$ and stores it at the same location from which GET(i) returned the search result. For the sake of simplicity, we also define another operation **FETCH** that takes a physical address in the ORAM as an argument and just returns its contents.

We have enough machinery to make one oblivious memory access, but no more. Why? Because if the client were to request the same virtual memory address twice, the RAM would access the same memory location twice too, thereby revealing some information to the attacker. Thus, we must ensure that even if a virtual address is requested twice, the same memory location must not be accessed twice. For this, we will make use of the cache, which will store any contents that have been accessed in the previous $latex \sqrt{N}$ IO cycles/rounds. In every IO cycle/round, if the command executed is a read (resp. write) command, then the read (resp. write) protocol is executed.

**Read protocol.** Client requests server for virtual address $latex i$ by encrypting it and sending the tag. However, it works a little differently compared to the GET function above. The client first computes $latex tag_i$ and fetches every location in the cache and checks for equality with $latex tag_i$. If the item is found in the cache, we perform a dummy lookup. If not, we call GET[i] and update the cache. The pseudocode below explains how the read protocol works.

**Write protocol.** The write protocol is similar to the read protocol except for 3 small changes. It also takes a value $latex v$ along with an address $latex i$. If the item is found in the cache, it sets $latex z = v$ instead of $latex z = temp$. If the item is not found in the cache i.e., $latex found$=FALSE, we also execute PUT[i,v] and set $latex z=v$ before exiting the if-block.

Note that if an item $latex i$ has already been read before, then a subsequent write to address $latex i$ will update only the version in the cache and not the one in main memory. The invalid versions in main memory have updated virtual memory addresses of the form $latex \infty_j$, which will help to mark and remove them in the restructuring step.

**Restructuring.** Whenever a new memory location is accessed for the first time, it is added to the cache. Thus, after $latex \sqrt{N}$ cycles, the cache could be full and the ORAM will need to restructured. This is done by sorting the entire ORAM based on the virtual memory address stored in each memory location. This performs the task of storing the $latex N$ memory locations which are either unaccessed or in the cache in the first $latex N$ locations, since all invalidated and dummy memory locations have their virtual addresses set to $latex \infty_j$ and so they will occupy the last $latex 2\sqrt{N}$ memory locations. Now the whole memory can be decrypted and encrypted using a new key again, with new tags (also generated using a new key). Now the ORAM is reset and the whole process can be repeated.

The proof that this protocol is oblivious was discussed in class and can be seen in the paper linked in the references. The key idea, however, is that the memory accesses are the same (from the server's point of view) regardless of the input and contents of the cache.

**Bitonic sort.** To sort the ORAM obliviously, we can use a sorting algorithm called Bitonic sort. Bitonic sort has the property that the memory access pattern remains the same for any input of the same length. This is exactly the obliviousness property! Moreover, since our CPU/client only has constant memory, it can copy two memory locations at a time and compare them, which is sufficient for Bitonic sort. Bitonic sort has a time complexity of $latex O(n$ $latex \log^{2}n)$.

**Analysis**

Restructuring the ORAM requires calling Bitonic sort which takes $latex O(N$ $latex \log^{2}N)$ time. Every read or write operation takes $latex O(\sqrt{N})$ to search the whole cache and $latex O(\log N)$ for the binary search and $latex O(\sqrt{N}+\log N)$ = $latex O(\sqrt{N})$. The initial setup also has a time complexity of $latex O(N$ $latex \log^{2}N)$. Thus, the amortized cost of the whole protocol is $latex O(\sqrt{N}$ $latex \log^{2}N)$.

## Tree-based ORAMs

The focus of Tree ORAM is to reduce the amortized cost that is increased with each memory access. This method will especially decrease the time for the worst-case accesses. Most methods for ORAM built directly off Ostrovsky’s method, would keep the fundamental permuting of the memory and oblivious sorting. These techniques were highly expensive and primitive. To restructure the ORAM, the data would be in small portions of memory called buckets. These buckets would be laid out in a binary tree on the data server. To reduce the amount of client storage required for access to that tree, the data can be stored recursively on the server. For simplicity, we do not describe the recursive version and assume the client stores the metadata needed to access the tree.

**Differences between Tree ORAM Compared to Other Methods**

A fundamental change to the interaction in ORAM is the exclusion of Read and Write interfaces. These operations are modified in this method to be a ReadAndRemove along with Add. Another operation, called Pop, is added to the method. The ReadAndRemove function requires a block identifier, which will find the block and remove it from the tree, supplying the block to the client. The Add operation will take a block and its identifier that will place the block in the tree with its identifier. The Pop operation will search for a data block but will return a dummy block if the real block is never found.

The reason for ReadAndRemove and Add to be implemented instead of the normal operations is to always change the location of an accessed block of data whether it is simply accessed as unchanged data, modified and returned, or a completely new block of data.

**Construction of the Tree.** A binary tree is constructed with a depth of $latex \log{N}$, which leaves the tree with N leaf nodes. Each Node will have a capacity of $O(\log(N))$. When this capacity is filled, the node will then evict the data block that is at the end of its storage to one of its child buckets.

A note about data blocks. When a data block is ever added to the tree, it is assigned a path that is chosen independently at random. This path is a number associated with a leaf node. Whenever a block is evicted, it is put down the path toward its associated leaf node. This is how a block can be found when ReadAndRemove is enacted upon the block. The data structure indicates what block has what leaf node is stored by the client.

**Proof of Security and Efficiency**

For ReadAndRemove, each bucket is along a certain path where each of its log(N) blocks has a different destination leaf node. Whenever this function is called, the data block that is accessed is always uniformly randomly given a new leaf destination. Whenever the function Add is invoked, the root is the bucket that is accessed every time but will always invoke eviction, which moves its data in a random position down the tree.

Due to the nature of the Trivial Bucket O-Ram that undergoes the same type and intense process for each access and writeback of data, which includes scanning down the tree, adding to the top of the tree with re-encrypted data which includes a new path, and evicting down the tree randomly to allow more blank space for new data blocks in each bucket, the amortized cost of use is the same as the Worst-case cost, which simplifies to $O(\log^3 (N))$.

**References**

Tree ORAM paper

Wikipedia link for Bitonic sort.
