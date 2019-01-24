---
layout: post
title: 2D Convolution for image processing
date:   2019-01-06 14:34:25
tags: [Image]
permalink: /_convolution_/
---
# Input Image 

At first we need an image . In the given example we see a image as a matrix . 
Basically, images are represented as a 2D matrix .

![image](https://user-images.githubusercontent.com/35966401/51075430-6facd480-16b5-11e9-9cb7-f28c0b91f39f.png)

# Kernel
## What is a kernel ?
![image](https://user-images.githubusercontent.com/35966401/51075310-e8129600-16b3-11e9-9a91-9b8485d9611b.png)
## We use this kernel for this example given below :
![image](https://user-images.githubusercontent.com/35966401/51075442-9539de00-16b5-11e9-874e-e4b030ab14d2.png)

At first flip/rotate the kernel into 180 degrees .

![image](https://user-images.githubusercontent.com/35966401/51075568-691f5c80-16b7-11e9-9ad8-86d5d27bac0a.png)

Then apply zero padding into the image .
Then multiply and sum all the things to find a value . 

## An example to find the value

![image](https://user-images.githubusercontent.com/35966401/51075520-90c1f500-16b6-11e9-9674-0b1a74c9ac0e.png)

Put it into the output image are given below . That's we calculate our convoution operation into image processing .


# Output image
## Using the operation we found the output image .

![image](https://user-images.githubusercontent.com/35966401/51075448-b995ba80-16b5-11e9-969f-a198994a796b.png)


### References : 
[Definition in Bangla](https://www.youtube.com/watch?v=iK_C8ORGS2M)
 [Convolution 2D](http://www.songho.ca/dsp/convolution/convolution2d_example.html) 
 [Convolution FAQ](https://cs.stackexchange.com/questions/11591/2d-convolution-flipping-the-kernel)

