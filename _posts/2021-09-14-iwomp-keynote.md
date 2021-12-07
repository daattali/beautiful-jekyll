---
layout: post
title: DSL keynote at IWOMP
subtitle: xDSL's Paul Kelly gives keynote talk at IWOMP 2021
thumbnail-img: /assets/img/xdsl_bof_sc21.jpeg
tags: [keynote]
comments: true
---

IWOMP is a popular annual conference focussed on parallel programming using OpenMP. It's success has grown from the fact that there are always numerous interesting and innovative ideas being discussed. A major cornerstone of any conference is the keynote talk which this year was delivered by Paul Kelly, who is also co-I on XDSL. Paul was talking about how we might go about achieving the elusive goals of programmer productivity, performance and portability across architectures, with DSLs having an important role to play here. However the languages themselves are not enough and Paul's message was that the key to success here, and wide spread adoption of DSLs, is the underlying compiler architecture. Commonly DSL implementations (the compilers) are standalone, sharing little common infrastructure and ultimately relying on the support of a small developer base. With limited, if any, shared components this makes the job of the DSL developer far more difficult. Building on MLIR, as we aim to do in this project, is one way in which this situation can be improved, and Paul describes how this can establish community support for code generation tools which then can underpin multiple front-end DSLS.s Ultimately this approach results in a more mature ecosystem and reduced barrier to entry for DSL developers. 

[![Productivity, performance and portability: towards cross-domain DSL compiler architecture (IWOMP'21)](http://img.youtube.com/vi/b0SYsG0-od4/0.jpg)](http://www.youtube.com/watch?v=b0SYsG0-od4 "Productivity, performance and portability: towards cross-domain DSL compiler architecture (IWOMP'21)")
