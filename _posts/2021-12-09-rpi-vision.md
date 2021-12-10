---
layout: post
title: Computer Vision with Raspberry Pi
subtitle: Project in CIS521
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/rpi-cv.png
share-img: /assets/img/rpi-cv.jpg
tags: [raspberry pi, computer vision]
---


In this project, students were given the opportunity to apply computer vision to both real-world and highly-relevant problems.  Face Recognition is a common technology in modern smartphones and laptops with webcams.  These systems extract visual keypoints on a person's face and match those features against an existing representation of the user's face.  In state of the art applications, these systems are driven by intricate deep computer vision.  In this project, we tackled two related vision problems and deployed our algorithms/networks on a raspberry pi with camera.

### Face Detection

In the first part of this project, I used PCA on a large dataset of people's faces to determine the L2-distance between a sample face image projected in the PCA-space, and the so-called **eigen-faces** (eigen-vectors in the PCA-space).  By thresholding the distance between a sample projection and the eigen-vectors of the PCA-space, we can create a classifier for whether or not there is a face present in the picture.  A smaller L2-distance would mean that whatever pattern is in the image, is has features that resemble a human face, while a larger L2-distance would indicate that whatever is in the image does not have much similarity to a human face.  Shown below is a sample video of my detector deployed on a Raspberry Pi camera:

<video width="450" height="360" controls>
  <source type="video/mp4" src="/assets/img/facedetection.mp4">
</video>

### Mask Detection

<video width="450" height="360" controls>
  <source type="video/mp4" src="/assets/img/maskdetection.mp4">
</video>
