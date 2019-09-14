---
layout: post
title: Разница между Process и Thread (C#)
category: .net
tags: [.net, development, theory]
---

A thread is analogous to the operating system process in which your application runs. Just as processes run in parallel on a computer, threads run in parallel within a single process. 

Processes are fully isolated from each other; threads have just a limited degree of isolation. In particular, threads share (heap) memory with other threads running in the same application. 

This, in part, is why threading is useful: one thread can fetch data in the background, for instance, while another thread can display the data as it arrives.