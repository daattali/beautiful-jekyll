---
layout: page
title: Projects
# subtitle: 
---

### Triton GPU Programming and Attention Kernels
April 2026 – July 2026; ByteDance AML

- Extended the official Triton tutorials into a structured learning resource, with detailed explanations and implementation walkthroughs for GPU kernel programming.
- Wrote in-depth tutorials on FlashAttention and other attention variants, connecting algorithmic design to Triton kernel implementations and performance considerations.
- Co-developed and delivered an eight-session internal lecture series for the ByteDance AML group on Triton fundamentals and attention kernel implementation.

### ML.ENERGY.LEADERBOARD
May 2023 – Sept. 2023; Symbiotic Lab

- Developed the [ML.ENERGY Leaderboard](https://ml.energy/leaderboard/?__theme=light), an open-source platform for benchmarking the energy efficiency and NLP performance of LLM models.
- Defined performance metrics and implemented scripts for optimized batched inference, ensuring precise energy and performance measurements.
- Contributed to the online Chatbot Arena, gathering data on models' energy consumption and performance.

### Building a Toy Operating System
- Created a toy operating system with physical memory and disk management.
- Implemented read-write locks using mutexes to manage multi-threading.
- Developed virtual memory management with a page table and a network file server using sockets.
- Built a custom file system for networked access.

### Out-of-order Execution Pipeline for the MIPS R10K Microprocessor
- Developed an out-of-order execution pipeline with six stages on the MIPS R10K microprocessor.
- Implemented key components including register renaming, reservation station, reorder buffer, and a common data bus for enhanced parallelism.
- Applied Tomasulo’s algorithm for dynamic scheduling and reducing pipeline stalls.
- Added a Load Store Queue and a Branch Target Buffer to further optimize execution efficiency and improve instruction throughput.

### Video Streaming via CDN
- Developed a proxy server for handling video streaming across multiple clients and servers, ensuring scalability and reliability.
- Implemented adaptive bitrate streaming to minimize buffering and enhance user experience based on real-time network conditions.
- Used DNS load balancing with round-robin and distance-based server selection, utilizing Dijkstra's algorithm to optimize server choices based on proximity and load.

### Static Router
- Built a static router with basic packet forwarding capabilities to route real packets to HTTP servers.
- Implemented layer 2 and layer 3 protocols, including ARP, ICMP, and Ethernet, for routing and handling network traffic.

### Embedded Device for Keystroke Timing and Acoustic Attack Protection
- Designed the device to intercept keystrokes and introduce random delays before sending to the PC.
- Implemented keystroke sound playback to counter acoustic attacks using recorded sounds.
- Based the system on the STM32F405 microcontroller with Embedded Rust for secure and efficient performance.
- Delivered a compact, user-friendly design with production costs around $24.50 per unit.
- Utilized SD card for storing custom keystroke sounds and USB peripherals for communication with keyboard and host PC.
