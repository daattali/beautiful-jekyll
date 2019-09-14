---
layout: post
title: Что такое AppDomain
category: .net
tags: [.net, development, theory]
---

Ответ одного чела на StackOverflow ([https://stackoverflow.com/a/12233139](https://stackoverflow.com/a/12233139))

---

An App-domain implements the concept of a contiguous virtual memory space that holds the code and the in-memory resources that can be directly accesses or referenced.

Separate AppDomains do not share memory space and, consequently, one AppDomain cannot directly reference contents in another. In particular, data must be passed between AppDomains through a copy-by-value process. In particular, reference objects, which rely on pointers and therefore memory addresses, must first be serialized from the source and then deserialization into the destination AppDomain.

Previously on Windows systems, memory boundaries were implemented by processes; however, constructing processes is resource intensive. They also serve a dual purpose as thread boundaries. App-domains, on the other hand, are concerned only with memory boundary or address space. Threads can 'flow' across AppDomains (that is, a procedure can invoke an entry point in another AppDomain and wait for it to return. The thread is said to 'continue' execution within the other AppDomain).

One significant benefit of this architecture is that communication patterns between App-domains remain substantially unchanged whether the AppDomains are in the same process, different processes, or on a different machines all together: namely the process of serialization and deserialization (marshaling) of parameter data.

Note 1: the meaning of a thread crossing an AppDomain is that of a blocking or synchronous method call into another AppDomain (versus a non-blocking or asynchronous call which would spawn another thread to continue execution in the target AppDomain and continue in it's current AppDomain without awaiting response).

Note 2: there is such a thing as Thread Local Storage. However, a better name would have been App-Domain Thread Local Storage since threads leave their data behind as they cross App-Domains but pick them back up when they return: [http://msdn.microsoft.com/en-us/library/6sby1byh.aspx](http://msdn.microsoft.com/en-us/library/6sby1byh.aspx)

Note3: A .Net Runtime is a Windows Process application with an associated heap. It may host one or more AppDomains in that heap. However, the AppDomains are design to be oblivious of each other and to communicate with each other via marshaling. It is conceivable that an optimization can be performed that bypasses marshaling between communicating AppDomains sharing the same .Net Runtime and therefore the same Windows Process heap.