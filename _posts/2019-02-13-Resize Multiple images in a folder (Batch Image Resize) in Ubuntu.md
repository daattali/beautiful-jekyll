---
layout: post
title: Resize Multiple images in a folder (Batch Image Resize) in Ubuntu
subtitle: Excerpt from Soulshaping by Jeff Brown
cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/thumb.png
share-img: /assets/img/path.jpg
gh-badge: [star, fork, follow]
tags: [Ubuntu, Linux, Image resize, Imagemagick]
---
 
You can resize multiple image files (jpg/png/gif….) stored in a folder by the imagemagick package. Here is step-by-step guideline:
Install ImageMagick

- Install imagemagick from Ubuntu Software Center

Or, in the terminal:

```bash
sudo apt-get install imagemagick
```

Copy all of your images to a folder

- Put all your image files in a single directory.

And don’t forget to take backup of your photos in a separate location.

- Open a terminal and go to this directory:

cd <directory-location>

- Now, enter following command to resize all of the images to a specific percentage. For examples, for the following command, all of the images will be reduced to 50% of their dimension maintaining the ratio.

~~~
mogrify -resize 50% -format jpg *
~~~

Where -format jpg specifies: the resultant format will be JPG.
Specify exact width & height

You may also specify width and height by the following command:

~~~
mogrify -resize 800x600 -format jpg *
~~~

You can easily guess, the resultant images will be of width 800 px and height of 600 px, keeping the original ratio.
Just mention width

Just mention width and the height will be automatically calculated, maintaining aspect ratio:

~~~
mogrify -resize 800x -format jpg *
~~~

That is, we told imagemagick that we want the images to be 800 pixels width. Height will be calculated automatically.
