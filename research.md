---
layout: page
title: Research
# subtitle: 
---

## Publications

{% include publications.html %}

## Projects

### Sentry: Proactive Agent Execution with State Lineage
Oct 2025 – Present; Supervisor: [Fan Lai](https://www.fanlai.me/) @ GAEA Lab

- Designed a lineage-based control plane for stateful LLM agents, combining cost-aware checkpoint loading and replay to selectively recover from late-detected errors while preserving independent work.
- Combined execution-graph matching with periodic tool-call speculation to prepare state and execute tools during model reasoning, validating action equivalence and input-state versions before reusing results.
- Designed demand-driven KV cache write-back and GPU-memory lending during tool stalls, with prediction-guided prefetch and page reclamation to admit new requests and restore paused contexts.
- Designed guarded asynchronous execution and sandbox colocation using learned dependency contracts, private state versions, and ordered commits, with conflict-triggered recovery and workspace splitting.

### CacheFlow: Efficient LLM Serving via Automated 3D-Parallel KV Cache Restoration
Aug 2024 – Sept 2026; Supervisor: [Fan Lai](https://www.fanlai.me/) @ GAEA Lab

- Formulated KV cache restoration as a multidimensional scheduling problem, coordinating recomputation and cache loading across tokens, layers, and GPUs.
- Developed a batch-aware dynamic-programming planner that jointly selects recomputation boundaries across requests and layers, accounting for heterogeneous full-attention and recurrent-layer costs.
- Enabled concurrent restoration across model shards by caching lightweight boundary activations, removing sequential recomputation dependencies between GPUs.
- Implemented CacheFlow atop vLLM and LMCache, reducing TTFT by 10%–62% across diverse models, chatbot and agentic workloads, and hardware configurations.

### JITServe: SLO-aware LLM Serving with Imprecise Request Information
Jul 2024 – Sept 2025; Supervisor: [Fan Lai](https://www.fanlai.me/) @ GAEA Lab

- Developed an SLO-aware scheduler for latency-sensitive, throughput-sensitive, and compound requests, allocating resources to meet heterogeneous performance requirements.
- Represented multi-agent workflows as DAGs and applied graph matching to predict execution dependencies and remaining workload; used quantile regression forests to estimate response lengths.
- Designed service-density-based prioritization to maximize service gain while preserving capacity for other requests and preventing starvation of lower-priority workloads.
- Achieved 1.3–8.3× higher service gain and 4.0–10.3× higher SLO goodput than existing serving systems across diverse workloads and models.

### Andes: Defining and Enhancing Quality-of-Experience in LLM-Based Text Streaming Services
May 2023 – April 2024; Supervisors: [Mosharaf Chowdhury](https://www.mosharaf.com/), [Amber Liu](https://websites.umich.edu/~amberljc/) @ Symbiotic Lab

- Identified the mismatch between conventional serving metrics and streaming user experience, highlighting the importance of delivering text at a pace that matches user reading speed.
- Defined a Quality-of-Experience (QoE) metric that tracks token delivery throughout generation and captures its impact on the user's reading experience.
- Formulated online scheduling as a knapsack optimization problem, allocating serving resources to maximize overall QoE across concurrent requests.
- Built Andes atop vLLM and integrated the QoE-aware scheduler into the serving runtime to improve the responsiveness of LLM text streaming.
