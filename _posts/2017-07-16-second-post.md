---
layout: post
title: How I changed my Jekyll theme
image: /img/avatar-icon.png
tags: [jekyll, website]
---

After months of having the `minima` Jekyll theme since I started having a website, I was finally able to change it to something a little less boring. Just to record the steps I did to do this, I am writing this post. 

1. After picking the theme, I followed the theme's instruction on how to adapt it. That is, I forked its repository and changed its name on GitHub. But instead of using `username.github.io` as name of the repo, I used `test` or something like that.

2. I then modified the `_config.yml` file accordingly on GitHub. It turned out that this repo is already set as published (this can be checked by looking at the settings for the repo on GitHub). I could then check to see if the published site is working properly. The url for this was `http://username.github.io/test`.

3. I proceeded to clone this repo in my machine and tested whether I could serve it there using the `jekyll serve` command. This worked after I had to do a `gem install jekyll bundler` command.

4. After making sure everything worked on my local environment and that it can be published on my site, I created a new repository on GitHub for the old website, which I named `oldsite`. I'm ready to transfer the files from the test repo to the `username.github.io` repo, which is needed to publish the site.

5. On my terminal, I went to my old website's folder and changed its remote url. To do this, I googled "hot to change remote repository git" and found the GitHub documentation on [changing a remote's URL](https://help.github.com/articles/changing-a-remote-s-url/). On the terminal, while on the old website's folder, I did the following:

    ```
    git remote set-url origin <url for oldsite repo>
    ```

6. I pushed the old website folder (I did not have to rename it) to the remote so I have a record of it both in my computer and on GitHub, just in case.

7. On GitHub, I deleted the `username.github.io` repo. This is after making sure I did step 6. I had the confidence to do this since the contents of this repo were pushed into another repo (named `oldsite` as I mentioned above.)

8. I then went to the `test` folder on GitHub which contained the new theme. I went to the settings and changed its name from `test` to `username.github.io`. 

9. This meant that my cloned `test` folder in my machine does not have the right remote url for it. Instead of changing this I just cloned the `username.github.io` just in case I need to use the `test` folder again.

10. I now have a `username.github.io` folder locally. Checking my website by serving it locally made me see that I needed to change some configuration settings in `_config.yml`, such as the url and baseurl. I then pushed these changes to GitHub.

Everything worked after these. 