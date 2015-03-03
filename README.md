# Beautiful Jekyll

[Jekyll](http://jekyllrb.com/) is a simple site generator that is used for hosting [GitHub Pages](https://pages.github.com/) and specializes in blogging-type websites, although it can work with any site.

GitHub pages makes it extremely simple to host your own website or a website for a GitHub repository within minutes **for free**.  While it's very easy to get started with GitHub Pages, you will get very basic looking pages and basic functionality.

**Beautiful Jekyll** is a ready-to-use template to make help you create an awesome Jekyll or GitHub Page website quickly.  [Check out a demo](http://deanattali.com/beautiful-jekyll) of what you'll get after just two minutes or look at [my personal website](http://deanattali.com) to see it in use.

## Build your website in 3 steps

Getting started is *literally* as easy as 1-2-3 :smile: Scroll down to see the steps involved, but here is a 45-second GIF just as a reference as you work through the steps.

![Installation steps](img/install-steps.gif)

### 1. Fork this repository 

Fork this repository by clicking the Fork button on the top right corner.

### 2. Rename the repository to `yourusername.github.io`

This will create a GitHub User page ready with the **Beautiful Jekyll** template that will be available at http://yourusername.github.io (sometimes it takes a few minutes).

### 3. Customize settings

Edit the `_config.yml` file to change all the settings to reflect your site.  The settings in the file are fairly self-explanatory and I added comments inside the file to help you further.  Every time you make a change to any file, your website will get rebuilt and should be updated at `yourusername.github.io` within a minute.

You can now visit your shiny new website, which will be seeded with several sample blog posts and a couple other pages.

**Note:** The GIF above goes through the setup for a user with username `daattalitest`. I only edited one setting in the `_config.yml` file in the video, but you should actually go through the rest of the settings as well.


### Add your own content

To add pages to your site, you can either write a markdown file (`.md`) which will automatically get converted to HTML, or you can write an HTML file directly.  It is much easier to write mardown; you write normal text with a few styling identifiers, and Jekyll will know how to automatically render it as a pretty HTML page. Markdown is extremely easy to use, just [look at the reference](http://daringfireball.net/projects/markdown/syntax) and at  some files on the site to get an idea.

Any markdown or HTML file you add to the root directory will be immediately available on your site. Take a look at the `aboutme.md` and `index.html` files as examples. Any file inside the `_posts` directory will be treated as a blog entry.  You can look at the existing files there to get an idea of how to write blog posts, and delete them when you feel ready.

### YAML front matter
YAML is a way to use parameters to make the templating more useful. To take advantage of the template, you need to add [YAML front matter](http://jekyllrb.com/docs/frontmatter/) to the top of each page. If you don't want to use any special paramters, use the empty YAML front matter:

```
---
---
```

If you want to use any parameters, write them between the two lines. Look at `aboutme.md` or `index.html` as examples.

### Features

#### Mobile-first
**Beautiful Jekyll** is designed to look great on both large-screen and small-screen (mobile) devices. Load up your site on your phone and your gigantic iMac, and the site will work well on both, though it will look slightly different.

#### Personalization

Many personalization settings in `_config.yml`, such as setting your avatar to add a little image in the navbar or customizing what social media links to show in the footer

#### Page types

- To write a blog post, place a file in the `_posts` folder and assign `layout: post` in the YAML front matter. Look at the existing blog post files to see the YAML parameters that blog posts can use.
- To add a non-blog page, place it in the root directory and assign `layout: page` in the YAML front matter. Look at `aboutme.md` and `index.html` as examples.
- To add a random page with minimal styling (ie. without the bulky navigation bar and footer), assign `layout: minimal`.
- To write your own HTML page and completely bypass the Jekyll engine, simply omit the YAML front matter.

#### YAML front matter parameters

There are all the parameters you can place inside a page's YAML front matter that **Beautiful Jekyll** supports.

Parameter   | Page types supported | Description
------------| -------------------- | -----------
layout      | all                  | What type of page this is
title       | all                  | Page title
subtitle    | post                 | Short subtitle
description | page                 | Short description of page
date        | minimal              | Date to show in the mini footer
js          | all                  | List of local JavaScript files to include in the page (eg. `/js/mypage.js`)
ext-js      | all                  | List of external JavaScript files to include in the page (eg. `//cdnjs.cloudflare.com/ajax/libs/underscore.js/1.8.2/underscore-min.js`)
css         | all                  | List of local CSS files to include in the page
ex-css      | all                  | List of external CSS files to include in the page
googlefonts | all                  | List of Google fonts to include in the page (eg. `["Monoton", "Lobster"]`)

### Project page vs user page

If you're not sure what the difference is, then ignore this section.

If you want to use this theme for a project page for a specific repository instead of your main GitHub user page, that's no problem. The demo for this site ([daattali.github.io/beautiful-jekyll](http://deanattali.com/beautiful-jekyll)) is actually set up as a project page while my personal site ([daattali.github.io](http://deanattali.com)) is a regular user page.  The only difference is that in the `_config.yml`, you should set `baseurl` to be `/projectname` instead of `""`.


### Credits

This template was not made entirely from scratch. I would like to give special thanks to:
- [Barry Clark](https://github.com/barryclark) and his project [Jekyll Now](https://github.com/barryclark/jekyll-now), from whom I've taken several ideas and code snippets, as well as some documenation tips.
- [Iron Summit Media](https://github.com/IronSummitMedia) and their project [Bootstrap Clean Blog](https://github.com/IronSummitMedia/startbootstrap-clean-blog), from which I've used some design ideas and some of the templating code for posts and pagination.

### Contributions

If you find anything wrong or would like to contribute in any way, feel free to create a pull request/open an issue/send me a message.  Any comments are welcome!

### Known limitations

- If you have a project page and you want a custom 404 page, you must have a custom domain.  See https://help.github.com/articles/custom-404-pages/.  This means that if you have a regular User Page you can use the 404 page from this theme, but if it's a website for a specific repository, the 404 page will not be used.
