---
layout: post
title: PyTorch Notes
subtitle: Notes on picking up PyTorch
tags: [framework, deeplearning]
---

Torch tensors are the same as numpy's nd-array in terms of functionality. Numpy nd-arrays' popularity comes from it being faster than 
python's lists because it is actually [implemented in C](https://github.com/numpy/numpy/tree/master/numpy/core/src) underneath python wrappers. 
Torch tensors are originally implemented in C++ with support for parallel computation leveraging muliple cores in GPU.

Pytorch comes with built-in libraries that makes creating [custom datasets and dataloaders](https://github.com/utkuozbulak/pytorch-custom-dataset-examples) very easy.
