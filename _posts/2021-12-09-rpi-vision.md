---
layout: post
title: Computer Vision with Raspberry Pi
subtitle: Project in CIS521
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/rpi-cv.png
share-img: /assets/img/rpi-cv.jpg
tags: [raspberry pi, computer vision]
---


In this project, students were given the opportunity to apply computer vision to both real-world and highly-relevant problems.  Face Recognition is a common technology in modern smartphones and laptops with webcams.  These systems extract visual keypoints on a person's face and match those features against an existing representation of the user's face.  In state of the art applications, these systems are driven by deep computer vision.  In this project, we tackled two related, but simpler vision problems and deployed our algorithms and networks on a Raspberry Pi with camera.

### Face Detection

In the first part of this project, I used PCA on a large dataset of people's faces to determine the L2-distance between a sample face image projected in the PCA-space, and the so-called **eigen-faces** (eigen-vectors in the PCA-space).  By thresholding the distance between a sample projection and the eigen-vectors of the PCA-space, we can create a classifier for whether or not there is a face present in the picture.  A smaller L2-distance would mean that whatever pattern is in the image, is has features that resemble a human face, while a larger L2-distance would indicate that whatever is in the image does not have much similarity to a human face.  Shown below is a sample video of my detector deployed on a Raspberry Pi camera:

<video width="450" height="360" controls>
  <source type="video/mp4" src="/assets/img/facedetection.mp4">
</video>

The first step, as with any ML/CV project, was preprocessing.  The dataset prepared for students contained 2000 images of different human faces at various scales, all of which are 64x64 grayscaled images.  I vectorized all of the images in the dataset, and then computed the average for each pixel over all vectorized faces.  In order to make the data 0 centered, I subtract the average face vector from all samples.  Then, we can use our resultant data matrix to compute the covariance matrix using the following formula:

### Mask Detection

<video width="450" height="360" controls>
  <source type="video/mp4" src="/assets/img/maskdetection.mp4">
</video>
