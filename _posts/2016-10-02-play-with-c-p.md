---
layout: post
title: Predict where you are indoors
subtitle: (WiFi + Machine Learning)
---

I just wanted to give a shoutout to a project I think is very awesome:

[https://github.com/schollz/find](https://github.com/schollz/find)

"High-precision indoor positioning framework for most wifi-enabled devices."

It used to be in Python, but moved to Go for I assume speed and ease of porting
to other platforms.
Also, I wanted to tell you about a light variation, purely python/OSX based,
just for fun:

[https://github.com/kootenpv/whereami](https://github.com/kootenpv/whereami)

It can really nicely make use of [DictVectorizer and
RandomForest](https://github.com/kootenpv/whereami/blob/master/whereami/pipeline.py)
in sklearn :)

Here's what you can expect (after `pip install whereami`):

```bash
# in your bedroom, takes 100 samples
whereami learn -l bedroom -n 100

# in your kitchen, takes 100 samples
whereami learn -l kitchen  # default is n=100

# cross-validated accuracy on historic data
whereami crossval
# 0.99319

# use in other applications, e.g. by piping the most likely answer:
whereami predict | say
# Computer Voice says: "bedroom"

# probabilities per class
whereami predict_proba
# {"bedroom": 0.99, "kitchen": 0.01}
```

For those interested: when you have ~8 different WiFi networks nearby, scanning
to find out how well the connection is for each (or whether it is "missing") are
great features in distinguishing whether you are in place A or place B.

It works with 99% accuracy for me based on 10 meters, and around 75% between
Couch 1 and Couch 2 (2 meters apart).
