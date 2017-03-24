# Contributing to www.tx10indivisible.us

**WARNING - this is a draft in progress. This is not at all ready for use.**

## Setting up a working repository.

First, setup your own copy of our website repository. (That's called a "forked" version.)

* Create a [Github](https://github.com) account.

* Navigate to: https://github.com/tx10indivisible/tx10indivisible.github.io

* Click the "Fork" button near the top-right of the page.

* If prompted where to fork it to, select your personal repository.

* Wait for the fork to complete. You'll get a copy of the original repository in your personal account.

* FIXME - delete CNAME file

* Select: Settings

* Scroll to the "GitHub Pages" section.

* Change the "Source" dropdown to "master branch" and click "Save".

* Scroll back down to the "GithHub Pages" section.

* Click on the link in the "Your site is ready to be published" line.

That should bring up a copy of the TX-10 Indivisible website, but in your private github.io address.


## Making changes to the website.

The website is built with the Jekyll template system.

For more information read the [Jekyll documentation](https://jekyllrb.com/docs/home/).

You can edit the files on Github by bringing up a file and clicking the edit icon (it's a pencil).

When you save the changes they should be published immediately to your github.io site.

Once you are happy with your changes and want to submit them for
publication on the live site, create a "pull request" (discussed below).


## Adding a news article.

Here is how to create a news article.

* Go into the "_posts" subdirectory.

* Click "Create a new file"

* Name the file in the format: YYYY-MM-DD-This_is_the_article_title.md

* Copy and paste this into the file:

```yaml
---
layout: post
title: Article title here
subtitle: Optional subtitle (delete if you don't need one)
tags: [tag1, tag2, or_delete_line_if_no_tags]
---

Just type in your article, using simple "markdown" syntax.
```
* Click "Commit new file".

* Browse to your github.io website. Your new article should be posted!

If you want to make any corrections, just pull up your article in the
Github editor. Commit your changes and they should appear on your site.

Once you are happy with your changes and want to submit them for
publication on the live site, create a "pull request" (discussed below).


## Creating a pull request.

TO DO


## Updating your repository.

TO DO


