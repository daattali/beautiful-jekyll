---
layout: post
title: Image Proceesing
date: 2017-06-08 16:47:14 +0530
categories: image_processing
tags: [image_processing]
bigimg: 
  - /img/multiclass-5.png
---

# Introduction to Image Processing with Scikit-Image

#### TLDR;

**Image Processing** is the process of applying mathematical functions or operations to an image, in order to transform it according to the problem requirements. 

It is closely related to **Computer Graphics** and **Computer Vision**. 

According to [Wikipedia](https://en.wikipedia.org/wiki/Image_processing),

> In **computer graphics**, images are manually made from physical models of objects, environments, and lighting, instead of being acquired (via imaging devices such as cameras) from natural scenes, as in most animated movies. 

> In **computer vision**, on the other hand, is often considered high-level image processing out of which a machine/computer/software intends to decipher the physical contents of an image or a sequence of images (e.g., videos or 3D full-body magnetic resonance scans).


### What is an image?

There are two ways to look at an image. 

1. Human's Perspective
2. Computer's Perspective


#### 1. Human's Perspective

##### How do we perceive an image?

According to [kenrockwell](http://www.kenrockwell.com/tech/how-we-see.htm),

> Our eyes don't send images to our brains. Images are constructed in our brains based on very simple signals sent from our eyes.

> The nerve signals from our eyes are still the subject of much study, and mostly represent edges, shapes and motion. They do not send images. 

>"Seeing" is a very complex higher-order brain function, and a huge percentage of our brains (the largest, in fact, of any brain function) is required for doing nothing other than recognize what's in front of us.

>Our brains form images based on pattern recognition. We don't see images; our eyes see line and motion, our brains interpret that to attempt to recognize to what sort of thing those lines and motion might represent, and then our brains seamlessly cause us to perceive whatever that object might be.

#### 2. Computer's Perspective

##### How does a Computer perceive an image?

For a computer an image is nothing but a bunch of numbers, but in a particular structure. Either a 2D or a 3D matrix of numbers. 

Consider the above example of a cat, let's see how a computer views this image. 

> Images can be either **binary**, **grayscale** or **multi channel** like **RGB** or **HSV**. 

> In case of a **binary** image, the value of each pixel can be either 0 or 1. 

> Binary - (0) or (1)

> In case of a **grayscale** image, the value of each pixel is in the range of 0 to 255, as it's going to be a 8 bit value. 

> Grayscale - (255)

> In case of **multi channel** image, the value of each pixel is composed of multiple values, in case of RGB, each pixel will have a value for Red, Blue and Green and each value will range from 0 to 255. 

> RGB - (255, 255, 255)

Credits to [Bob Fisher](https://homepages.inf.ed.ac.uk/rbf/HIPR2/glossary.htm) for providing great resource on Image Processing.

Topics to be covered in this post: 

1. **Input/Output operations and  datatype**
2. **Colorspaces**
3. **Image Processing**  
a. **Local Filters**  
b. **Non Local Filters**  
c. **Mathematical Morphology**  
    1. **Dilation**  
    2. **Erosion**
4. **Image Segmentation**  

### 1. Input/Output operations and datatype

The first and the foremost step in any image processing pipeline is to read the image(s). 

In scikit-image we can perform the I/O opertions as shown below. 

But, before that let's import the necessary libraries to support the above I/O operations. 



```python
# imports

from skimage.io import imread, imshow, imsave
import matplotlib.pyplot as plt
%matplotlib inline

img = imread('golden-gateway-bridge.jpeg')

plt.imshow(img)
```




    <matplotlib.image.AxesImage at 0x98c7fb00>




![png](output_1_1.png)


Skimage also contains others features such as saving an image, reading an image collection and much more. 


```python
# saving an image

imsave('image-name.jpg', img) # img - image matrix
```

** Image data types**

Image numpy ndarrays can be represented either by integers (signed or un-signed) or floating point values. 


```python
img.dtype
```




    dtype('uint8')



The image is of **integer** type. 

### 2. Colorspaces

Color images are of shape (rows, columns, channels).  
E.g., RGB  

Let's have a look at the colorspace of the input image. 

The input image contains:  
Rows: 2323  
Columns: 3484  
Channels: 3  


```python
img.shape
```




    (2323L, 3484L, 3L)



Skimage also supports conversion of images from one colorspace to other. 

The list below shows only the frequently used colorspace convertions. 

1. **rgb2hsv**  
    The is used to convert from RGB to HSV space. 
2. **rgb2gray**  
    This is used to convert from RGB to Grayscale space. 
3. **hsv2rgb**  
    This is used to convert from HSV to RGB space.
    
Let's look at the implementations for the above convertions. 


```python
from skimage.color import rgb2gray, rgb2hsv, hsv2rgb

# rgb2hsv

rgb_to_hsv = rgb2hsv(img)

plt.imshow(rgb_to_hsv)
```




    <matplotlib.image.AxesImage at 0x992194e0>




![png](output_9_1.png)



```python
# rgb2gray

rgb_to_gray = rgb2gray(img)

plt.imshow(rgb_to_gray, cmap='gray')
```




    <matplotlib.image.AxesImage at 0x9e576908>




![png](output_10_1.png)



```python
# hsv2rgb

hsv_to_rgb = hsv2rgb(rgb_to_hsv)

plt.imshow(hsv_to_rgb)
```




    <matplotlib.image.AxesImage at 0x9e215cf8>




![png](output_11_1.png)


### 3. Image Preprocessing


In image preprocessing, the input input images will be enchanced according to the problem requirements. 

Image preprocessing can include noise reduction, local filters, non-local filters and different kinds of morphological methods such as dilation or erosion. 

**Local Filters**

Local filters replace the value of pixels by a function of the values of the neighbouring pixels. The process can consider either 4-neighbours or 8-neighbours. 

Neighbourhood pixels will be chosen in the form of a structuring element such as a disk, square or a rectange.

Example for local filters is shown below: 


```python
from skimage.filters import sobel

sobel_img = sobel(rgb_to_gray)

plt.imshow(sobel_img)
```




    <matplotlib.image.AxesImage at 0x9dfe3208>




![png](output_13_1.png)


**Non-Local Filters**

Non-local filters use a large region of the image to transform the value of one pixel. 


```python
from skimage import exposure
from skimage.io import imread

img_to_gray = rgb2gray(img)
img_equalized = exposure.equalize_hist(img_to_gray)

plt.imshow(img_equalized, cmap='gray')
```




    <matplotlib.image.AxesImage at 0x9918e828>




![png](output_15_1.png)


**Mathematical morphology**

In the simplest form, morphology is the study of shape. It mostly deals with the mathematical theory of describing shapes using sets. 

Most common mathematical morphological methods are:

**Dilation**

The purpose of dilation is to expand a particular shape in the image by making use of a structural element. This is usually applied to binary images. 




```python
from skimage.data import coins
from skimage.filters import threshold_otsu
from skimage.morphology import disk, dilation

coins = coins()

seg = threshold_otsu(coins)
mask = coins > seg

plt.imshow(mask, cmap='gray')
```




    <matplotlib.image.AxesImage at 0x9ecb5550>




![png](output_17_1.png)



```python
dilated_img = dilation(mask, selem=disk(4))

plt.imshow(dilated_img, cmap='gray')
```




    <matplotlib.image.AxesImage at 0x9ebc4908>




![png](output_18_1.png)


The difference between the above two images, shows how dilation works. 

**Erosion**

The purpose of erosion is to erode away the boundaries of regions of foreground pixels. Thus areas of foreground pixels shrink in size. 



```python
from skimage.morphology import erosion

plt.imshow(mask, cmap='gray')
```




    <matplotlib.image.AxesImage at 0x9ee9d208>




![png](output_21_1.png)



```python
eroded_img = erosion(mask, selem=disk(4))

plt.imshow(eroded_img, cmap='gray')
```




    <matplotlib.image.AxesImage at 0x995dbcc0>




![png](output_22_1.png)


Erosion process eroded the white pixels in the above images. 

### 4. Image Segmentation

Image Segmentation is one of the most fascinating topics in Image Processing, with the increasing demand for self-driving research, image segmentation has become the hot topic, segmenting different objects in a given scence for the car to understand and act accordingly is a real challenge.

Few image segmentation techniques:

**Histogram based method: Otsu thresholding**

The Otsu method is a simple heuristic to find the threshold to seperate the foreground from the background, to understand different components in the image. 


```python
from skimage.data import coins
from skimage.filters import threshold_otsu

coins = coins()

seg = threshold_otsu(coins)
mask = coins > seg

plt.imshow(mask, cmap='gray')
```




    <matplotlib.image.AxesImage at 0xd3cbff98>




![png](output_25_1.png)


**Label connected components**

This step is taken into consideration when there is a need to seperate or label the discrete components that were created after thresholding. 


```python
from skimage.morphology import label

all_labels = label(mask)

plt.imshow(all_labels)
```




    <matplotlib.image.AxesImage at 0xd35a6780>




![png](output_27_1.png)


This was just an introduction to basic image processing techniques, for more in-depth information refer to the below mentioned resources. 

1. [PyImageSearch](http://www.pyimagesearch.com)
2. [Scikit-Image](http://scikit-image.org/)
3. [Robert Fisher](http://homepages.inf.ed.ac.uk/rbf/HIPR2/)


```python

```
