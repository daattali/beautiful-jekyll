---
layout: post
title: AWS Deep Learning with GPU AMI
subtitle: A lightweight AWS image with GPU support
tags: [deep learning, machine learning, tensorflow, keras, GPU]
---
Recently I was experimenting with using AWS GPU instances in order to accelerate some Tensorflow and Keras models that I was working on.  Unfortunately I wasn't able to find a community/free AMI that was deep learning oriented, had GPU support, and also worked. I was able to find a few, including Amazon's own Deep Learning AMI but it didn't work out of the box.

After a bit of effort I was able to get a p2.xlarge instance working with Annaconda Jupyter, tensorflow-gpu, and keras-gpu.  With a bit more effort I was able to make a public image of the same.  It has worked for me making new instances but please let me know if you try it and how it goes.

If you're interested in trying an AMI to quick start a p2.xlarge instance with GPU support then please search for:

*annaconda_tensorflow_keras_gpu*

Currently it appears that only the exact AMI name results in a match while searching. It should also be noted that this AMI has only been published to the US-West (Oregon) zone so it probably will not appear in other zones at this time. (Due to the way that Amazon has AMIs deploying at this time.)
