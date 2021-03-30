---
title: 'Design Inputs: #1 - Requirements'
layout: post
readtime: true
tags: [architecture]
before-content: old-post-warn.html
---

This might be the first post in a series discussing four key inputs into a solution design: the **Requirements**, **Assumptions**, **Risks**, and **Constraints**. During the series we’ll look at each of these inputs, their purpose, and some examples as it pertains to Infrastructure design. When initially defining a project or opportunity, focus must be given to defining each of these four areas in detail, and garnering agreement of the key stakeholders. These inputs describe the _guard rails_ for the design, and outline the key criteria which must be evaluated during the design process. 

Often, these terms are misused or misunderstood, especially when working with highly-technical teams as they can sometimes gravitate toward an immediate focus on the technical minutia, and not on the desired business-driven outcomes.

Each organisation has its own procedures for documenting these design inputs; however, I tend to ensure that at the very least, _architecturally significant_ requirements, assumptions, risks, and constraints are documented in the design artefact to ensure the reader is afforded sufficient context if the document is acquired in isolation.

## Requirements

Arguably the most important of all inputs into a design, the requirements outline what the system or design is intended to accomplish. A clearly defined requirement results in a clearly defined outcome for the design. A requirement is a need that must be met or fulfilled by the design, and the system it produces. Depending on the size of the organisation, requirements may be collected by a Business Analyst (or similar) during the project's Initiation phase, but it's the responsibility of the Architect to be intimately familiar with them. If no Business Analyst is available, requirements are often gathered by the project Architect as required.

Requirements are typically defined by the project or solution stakeholders and come in two varieties as they pertain to a solution architecture: functional, and non-functional.

#### Functional Requirements

Functional requirements describe _what_ a system or design will _do_. They describe the _features_ of a design, and typically speak to the Business objectives of a given project. Requirements characterise a need that must be met, or a capability that must be provided, for example:

  * The solution must allow a user in the northern branch office to download a 1GB video file from the regional data centre

A functional requirement maps directly to an outcome - in the example above, the user must be able to download a file from the regional data centre to their branch office. As you can see, the requirement did not list a specific technology which must be utilised, but simply outlined a need that must be fulfilled.

Some trigger words to consider when defining the functional requirements are:

  * Capability
  * Function
  * Feature
  * Process
  * Business Logic

#### Non-functional Requirements

Non-functional requirements describe the <u>characteristics</u> of _how_ a system will perform the desired function. Often, these requirements speak to the performance characteristics of the solution, in terms of speed or reliability. There is often a hazy distinction between non-functional requirements and constraints, but ideally a non-functional requirement still avoids defining specific technologies, vendors, or protocols. The topic of constraints will be elaborated in a future post.

Expanding on the example above, a couple of sample non-functional requirements which might accompany the functional requirement might be:

  * A user must be able to download the 1GB file in under 5 minutes
  * Access to the file must be available 99.9% of the time

As above, the non-functional requirement does not mention the technology which is to be used to meet the objective, but defines the attributes of the system or solution.

Some examples of trigger words for use when discussing non-functional requirements are as follows:

  * Reliability
  * Performance (latency, throughput)
  * Security
  * Usability
  * Uptime

### Conclusion

Building a list of clearly defined outcome-based requirements is a vital first step in the creation of a successful design or architecture. As an Architect, your role is to assist the project’s stakeholders in translating their business objectives into an actionable set of outcomes, and then creating a design to fulfil and meet those objectives. Few successful projects bypass this crucial first phase of architecture.

Thanks for reading, and check back soon as we continue the discussion of Design Inputs, with a post digging into Assumptions!