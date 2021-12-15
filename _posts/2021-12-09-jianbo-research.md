---
layout: post
title: Towards a Visual Understanding of Human Behavior
subtitle: Research Project led by Dr. Jianbo Shi
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
tags: [research, computer vision]
---

## Primer

As animals that are capable of a high level understanding of the world, vision is one of our most powerful senses.  Every second, huge amounts of dense information are streamed from the world through our eyes, among other percepts.  In fact, looking more holistically, we can think of the human brain as taking in sensory information from many different sources, including vision, and building a model of the world around us.  Each of us has our own little internal metaverse, if you will.  In AI and psychology, we call this phenomenon **multimodality**, or **multi-modal perception**.  

I come from a primarily AI and robotics background, so I often find it useful to relate concepts of psychology back to these disciplines.  The brain is a highly efficient computational device which can take in many different signals, such as sound, vision, body orientation, etc, and is still able to filter out noise to create a unified model of our own bodies and our surrounding environment.  I like to imagine that if my laptop tried to do that, it might burn down my apartment.

## Project Outline

In my work with [Dr. Jianbo Shi](https://www.cis.upenn.edu/~jshi/) at the [University of Pennsylvania](https://highlights.cis.upenn.edu/cis-research-areas/), we are using **deep learning**, **computer vision**, and **reinforcement learning** to computationally model human focus and attention.  Humans are innately good at solving problems using both high-level common sense and low-level technical reasoning.  In our experiments, we seek to place human subjects in an unfamiliar environment that requires them to use their instincts, common sense, and technical reasoning.  But how do we achieve all three of these abstract human factors?  Our group has settled on using an [Escape-the-Room](https://en.wikipedia.org/wiki/Escape_room) (or escape-room) as our experimental setting because this presents a unique opportunity to observe human behavior when presented with problem-solving tasks in an unfamiliar environment.  Furthermore, an escape-room presents an explicitly defined goal with minimal instruction on how to accomplish said goal, rendering the domain of possible human behaviors highly diverse.  By explaining the scenario minimally to our subjects, we can maximize their creative potential in decision-making.  In this sense, the idea that everyone approaches problems differently comes strongly in to play.  By using deep learning, we hope to characterize the human capacity for diverse exploration and problem-solving behaviors.

## Data Collection

So I've framed the experimental question our group is exploring, but how do we even observe subjects in this environment?  Data collection procedures was a big focus of my work this summer, so hopefully I can convey our setup clearly.  In the same way that it is not ideal for humans to be missing one of their senses, we need to be able to record data from many different sources in order to build a complete picture of an experiment.  This all starts with using 3D scanning technology to develop an accurate model of the experimental setup before any subject has entered.  Using a [Matterport scanner and the Matterport API](https://matterport.com/), we are able to develop a highly detailed 3D model of the escape-room without visual occlusions.  Matterport scanners and the associated software are capable of high quality (99% dimensional accuracy) 3D reconstructions and 3D renderings.  The scanner uses LIDAR and high quality images to build the 3D reconstruction, but beyond this I can't say much because the SDK is proprietary.  Shown below is an example 3D model of a room in which I collected Matterport scans (don't get dizzy).

<video width="680" controls autoplay loop>
  <source type="video/mp4" src="/assets/img/matterport-env.mp4">
</video>

Once we have scanned the environment, we record experimental subject data using multiple synchronized MS Azure Kinect 3D cameras, Insta360 spherical capture cameras, a GoPro camera, and Tobii gaze tracking glasses.  Yes, that's a lot of data, but let's look briefly at what each source of data does.  The [Azure Kinect](https://azure.microsoft.com/en-us/services/kinect-dk/) is a highly advanced 3D-imaging camera commonly used in robotics and autonomous vehicle research.  The Kinect camera can record RGB-D data, which means that it captures an RGB image from a 12MP camera and a Depth image from a 1MP depth sensor.  One of the powerful utilities of the Kinect camera is its ability to externally sync with other wired Kinects.  We leverage this utility by synchronizing two Kinect cameras which are stationed in adjacent corners of a room, close to the ceiling for isometric views of the scene.  The [Insta360 spherical capture camera](https://www.insta360.com/product/insta360-onex2) uses two high-resolution fisheye lenses to capture two very wide-angle images, which can then be stitched together almost seamlessly to create a spherical image.  The Insta360 camera is also capable of undistorting its spherical images into flat images, as well as person tracking.  We have collected data using a single centrally located Insta360 camera as well as two centrally located Insta360 cameras (for stereo vision).  The GoPro we have been collecting data with is the [HERO4 SESSION](https://www.cnet.com/reviews/gopro-hero4-session-review/) model.  If you're unfamiliiar, GoPro is one of the leaders of the wifi-enabled, action camera industry.  We selected the GoPro Session line of cameras because of their small size and weight, which couples well with their modularity for first-person video recording.  We mount the GoPro on the head of a subject and angle it down to give a good view of the subject's hands.  The GoPro is a low-cost but integral sensor to data collection because it captures the subject's direct interactions with their environment, from their own perspective.  [Tobii](https://www.tobiipro.com/) is another leader of the specialized camera industry, focusing mostly on eye-tracking technology as well as other bio-sensors.  Our group has acquired a pair of [Tobii Pro Glasses 2](https://www.tobiipro.com/product-listing/tobii-pro-glasses-2/) which are research-grade gaze-tracking glasses.  These glasses, although not very stylish, are incredibly powerful; using four cameras facing the wearers eyes (two for each eye) and an outward facing camera, the glasses+software can determine what the wearer is looking at in real-time.  This is extremely powerful in our data collection stack because it adds another degree of freedom, so in sum we can track:

   1. the global position of a subject's body within the room (using the Kinect/Insta360 cameras)
   2. the orientation of the subject's head at their current global position (using the GoPro camera)
   3. the direction of the subject's current gaze given their current global position and orientation (Tobii Glasses)

Synchronizing all of these cameras was challenging.  I was able to properly synchronize the Azure Kinect cameras in order to prevent interference from their depth sensors.  Once this was complete, it was simple to integrate and synchronize the GoPro camera using it's unofficial Python API.  Similarly for the Tobii glasses, the recording is started remotely from Tobii's command line, which is also integrated into our recording pipeline.  Unfortunately, I have yet to find a suitable API to control the Insta360 cameras.  As such, I have found that using the Insta360 iphone app to start recording wirelessly, but still manually.  In order to manage the problem of synchronizing the Insta360 with GoPro, Kinect, and Tobii glasses, we use a visual cue on a screen in the field of view of all cameras, which lets us to trim all videos to the same exact start frame.  This technique also gives an added layer of protection against asynchronicity that might have come from the pipeline I designed, though I haven't looked at this very deeply.

## Post-processing

So that's a lot of data, as a single 5 minute recording from all cameras totals to about 15GB of data.  We have video data from 4-6 cameras, all of which have been synchronized via the above trimming method.  For brevity, I will try to highlight some of the interesting post-processing techniques I explored.

#### GoPro

For recording, we used the wide angle recording setting, which resulted in some distortion in the image (Fisheye model).  As lame as it sounds, learning how to properly calibrate a camera using one or a variety of tools is crucial.  Thus, I spend a good deal of time attempting to calibrate find the camera intrinsics (including distortion coefficients).  I explored a variety of tools such as OpenCV, COLMAP, and MATLAB for this task, and I found that COLMAP yielded the best visual results, while MATLAB was by far the most intuitive.  That being said, OpenCV has the most functionality, meaning that instead of calibrating tediously by taking many images, we can take a short video of a calibration object, extract frames, find corners, estimate fisheye camera parameters, undistort the frames, and produce the same video without distortion.  Shown below is an example result from calibrating the GoPro using this method in OpenCV:

<p align="middle">
<video width="300" controls autoplay loop>
  <source type="video/mp4" src="/assets/img/gopro-calibration-demo.mp4">
</video>
<video width="300" controls autoplay loop>
  <source type="video/mp4" src="/assets/img/gopro-calibration-undistorted-demo.mp4">
</video>
</p>

As you can see above, in the left video there is significant distortion of the checkerboard calibration pattern.  After estimating the camera intrinsic parameters using OpenCV, the resulting undistorted video shows significant improvement.  The resulting frame still retains some distortion close to the corners and edges of the frame, which can be the result of not giving enough variation to the views of the calibration pattern.  For another application of the GoPro data, I ran inference using a pre-trained hand-dectection model.  Shown below is the result of running the trained model on a sample video.

<p align="middle">
<video width="600" controls autoplay loop>
  <source type="video/mp4" src="/assets/img/100-doh-demo.mp4">
</video>
</p>

The model can correctly detect hands, denoting detections with a bounding box.  Red boxes indicate a right-hand class prediction, while blue boxes indicate a left-hand class prediction.  The model also attempts to detect an object in contact if there is one, and furthermore the second letter above each hand-box indicates the type of contact with an object if there is one detected.  One use of this model's output's might be to use them to detect and predict intention, ie predict how someone might interact with an object if it appears there is some intention of manipulating an object.  That being said, the contact detection and classification outputs of this model might be noisy in real-time motion.

#### Azure Kinect

The Azure Kinect has a much more extensive SDK than the GoPro API, in addition to being a more complex sensor device.  As a result, synchronizing multiple Azure Kinects was not too difficult, most of the work was reading through a pretty sizable chunk of the SDK documentation to understand the task of synchronization.  Honestly, using this camera is pretty fun; the software has great visualization options and all the controls are right there for you to tweak.  The one thing that's pretty annoying is that the file type is .mkv, so you'll need a special tool to extract the different 'tracks' (RGB, Depth, IR, Audio).  Because this device captures RGB-D data, it makes a good candidate for 3D reconstruction.  The depth and RGB data can be extracted into frames, which can be fused using an algorithm like [Kinect Fusion]().  Shown below is a reconstruction generated by TSDF Fusion, which is another common reconstruction algorithm, and is actually a subprocess of the Kinect Fusion algorithm.

<p align="middle">
  <img src="/assets/img/fusion.jpg" width="500" />
</p>

Not yet up to date!
