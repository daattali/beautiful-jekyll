
Basically, this article based on ***Today I Learned*** category and it’s a tutorial based article where it tells about, how to use AsyncTask in RecyclerView. So, Let’s started.

I am new in Android development. A few days ago, I was working on an application where I have a task that downloaded the image from the internet through URL. After some research, I got no proper solution to that task. This is basically for the learning purpose, and how AsyncTask works.
>  AsyncTask is a class that performs an operation in the background and publish results on UIThread without blocking it. In AsyncTask class there is a main method **doInBackground,** that helps to perform the operation in the background.

So, Let’s started with simple AsyncTask code where it has three parameters. First one is for performing the operation in the background in ***doInBackground*** method. Second one is for show any progress on screen until work in background is finished in doInBackground method. And the last one is for showing the result of doInBackground method on the main thread means UIThread.

![](https://cdn-images-1.medium.com/max/2000/1*YZ9EXpaphAcRawrvUoWMiQ.png)

Now I have to download a single image from the Internet using AsyncTask class and post it on the main thread. Below code creates a link with the URL and download image from the internet and put into an ImageView.

![](https://cdn-images-1.medium.com/max/2000/1*rJNiLQZOTcw8AAhS_7gXxg.png)

After that, Now execute the task in , MainActivity using **execute()** method of AsyncTask class.

![](https://cdn-images-1.medium.com/max/2000/1*OnAm30Bk4zlc89f399b0gg.png)

So here the process of downloading a single image from the internet is complete. The image is downloaded by clicking the download button. See below the output of the above code.

![](https://cdn-images-1.medium.com/max/2000/1*j9jAuh7WKn_ESo24W6osCQ.gif)

Now let’s move to next task, that is downloading multiple images from the internet and setting in RecyclerView. After some research on the internet, the references are doing the same task by using **Picasso** and **Glide** and some of the references they are using AsyncTask to perform this work are very difficult to understand for beginners. I have to find simple way to perform this task.

So, we have to create an external class of AsyncTask and download images for each item in it.

## **Why create an external class of AsyncTask:**

In RecyclerView adapter there is a method onBindViewHolder that is called every item in the list. For downloading multiple images, we have to keep in mind that there is also multiple calling of AsyncTask class. So, that’s why we will create an external class that extends AsyncTask class and use it in OnBindViewHolder method.

So, create an external class that extends AsyncTask and pass two parameters: one is for ImageView type and other is for Context.

![](https://cdn-images-1.medium.com/max/2000/1*8SusOJYf4EJXw-2UF-fihw.png)

Now create an object of this class in **onBindViewHolder** method and call **execute** method.

![](https://cdn-images-1.medium.com/max/2000/1*YnaRZTS_3iPHe1h-0_KgrA.png)

The **DataClass.java **is a data placeholder and contains image url to download for each item.

![](https://cdn-images-1.medium.com/max/2000/1*isD5a8OnGnyyU23LpcuWTA.png)

Now set RecyclerView and LayoutManager in MainActivity. Here shown below the code **MainActivity.java**

![](https://cdn-images-1.medium.com/max/2000/1*c8yRQKFol_rHI7pv89ppgA.png)

Here is the Final output of the task.

![](https://cdn-images-1.medium.com/max/2000/1*_KHx41OYpmHjkRFmfZ6FMg.gif)

