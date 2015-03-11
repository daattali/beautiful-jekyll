# Beautiful Jekyll

**Beautiful Jekyll** is a ready-to-use template to help you create an awesome website quickly.  [Check out a demo](http://deanattali.com/beautiful-jekyll) of what you'll get after just two minutes or look at [my personal website](http://deanattali.com) to see it in use.

It is built on top of [Jekyll](http://jekyllrb.com/) and can be used for any [GitHub Pages](https://pages.github.com/) website.  If you don't know what Jekyll and GitHub Pages are, you can still use these instructions to build a site quickly, but it might make a little more sense if you read up on them just a little bit.

## Prerequisites

- You need to have a GitHub account. If you don't have one, [sign up here](https://github.com/join) - it takes one minute. This is where your website will live - if you sign up with username `johnsmith` then your website will be `johnsmith.github.io`.  
- It would be helpful to understand what Markdown is and how to write it. Markdown is just a way to take a piece of text and format it to look a little nicer.  For example, this whole instruction set that you're reading is written in markdown - it's just text with some words being bold/larger/part of bullet points. If you want, take 5 minutes to learn markdown [with this tutorial](http://markdowntutorial.com/).

## Build your website in 3 steps

Getting started is *literally* as easy as 1-2-3 :smile:   
Scroll down to see the steps involved, but here is a 45-second GIF just as a reference as you work through the steps. You might need to wait a few seconds until the "video" gets back to its beginning.

![Installation steps](img/install-steps.gif)

### 1. Fork this repository 

(Assuming you are on this page and logged in to GitHub) Fork this repository by clicking the Fork button on the top right corner. Forking means that you now copied this whole project and all the files into your account.

### 2. Rename the repository to `yourusername.github.io`

This will create a GitHub User page ready with the **Beautiful Jekyll** template that will be available at `http://yourusername.github.io` within a couple minutes.  To do this, click on "Settings" on the right (the tools icon) and there you'll have an option to rename.

### 3. Customize your website settings

Edit the `_config.yml` file to change all the settings to reflect your site. To edit the file, click on it and then click on the pencil icon (watch the GIF tutorial above if you're confused).  The settings in the file are fairly self-explanatory and I added comments inside the file to help you further. Any line that begins with a pound sign (`#`) is a comment, and the rest of the lines are settings.

After you save your changes to the config file (by clicking on "Commit changes" as the GIF tutorial shows), your website should be ready in a minute or two at `yourusername.github.io`. Every time you make a change to any file, your website will get rebuilt and should be updated in about a minute or so.

You can now visit your shiny new website, which will be seeded with several sample blog posts and a couple other pages. Your website is at `http://yourusername.github.io` (replace `yourusername` with your user name). Do not add `www` to the URL - it will not work!

**Note:** The GIF above goes through the setup for a user with username `daattalitest`. I only edited one setting in the `_config.yml` file in the video, but **you should actually go through the rest of the settings as well. Don't be lazy, go through all the settings :)**


### Add your own content

To add pages to your site, you can either write a markdown file (`.md`) or you can write an HTML file directly.  It is much easier to write mardown than HTML, so I suggest you do that (use the tutorial above if you need). You can look at some files on the site to get an idea of how to write markdown. To look at existing files, click on any file that ends in `.md`, for example [`aboutme.md`](./aboutme.md). On the next page you can see some nicely formatted text (there is a word in bold, a link, bullet points), and if you click on the pencil icon to edit the file, you will see the markdown that generated the pretty text. Very easy!

In contrast, look at [`index.html`](./index.html). That's how your write HTML - not as pretty. So stick with markdown if you don't know HTML.

Any file that you add inside the [`_posts`](./_posts) directory will be treated as a blog entry.  You can look at the existing files there to get an idea of how to write blog posts.

### Last important thing: YAML front matter

In order to have your new pages use this template and not just be plain pages, you need to add [YAML front matter](http://jekyllrb.com/docs/frontmatter/) to the top of each page. This is where you'll give each page some parameters that I made available, such as a title and subtitle. I'll go into more detail about what parameters are available later. If you don't want to use any parameters on your new page (this also means having no title), then use the empty YAML front matter:

```
---
---
```

If you want to use any parameters, write them between the two lines. For example, you can have this at the top of a page:

```
---
title: Contact me
subtitle: Here you'll find all the ways to get in touch with me
---
```

You can look at the top of [`aboutme.md`](./aboutme.md) or [`index.html`](./index.html) as more examples.

**Important takeaway: always add the YAML front matter to every page, which is two lines with three dashes. If you have any parameters, they go between the two lines.**    
If you don't include YAML then your file will not use the template.

## Features

#### Mobile-first
**Beautiful Jekyll** is designed to look great on both large-screen and small-screen (mobile) devices. Load up your site on your phone and your gigantic iMac, and the site will work well on both, though it will look slightly different.

#### Personalization

Many personalization settings in `_config.yml`, such as setting your avatar to add a little image in the navbar or customizing what social media links to show in the footer

#### Page types

- **post** - To write a blog post, place a file in the `_posts` folder and assign `layout: post` in the YAML front matter. Look at the existing blog post files to see the YAML parameters that blog posts can use.
- **page** - To add a non-blog page, place it in the root directory and assign `layout: page` in the YAML front matter. Look at `aboutme.md` and `index.html` as examples.
- **minimal** - To add a random page with minimal styling (ie. without the bulky navigation bar and footer), assign `layout: minimal`.
- To write your own HTML page and completely bypass the Jekyll engine, simply omit the YAML front matter.

#### YAML front matter parameters

There are all the parameters you can place inside a page's YAML front matter that **Beautiful Jekyll** supports.

Parameter   | Description
----------- | -----------
layout      | What type of page this is (recommended options are `page`, `post`, or `minimal`)
title       | Page or blog post title
subtitle    | Short description of page or blog post
js          | List of local JavaScript files to include in the page (eg. `/js/mypage.js`)
ext-js      | List of external JavaScript files to include in the page (eg. `//cdnjs.cloudflare.com/ajax/libs/underscore.js/1.8.2/underscore-min.js`)
css         | List of local CSS files to include in the page
ex-css      | List of external CSS files to include in the page
googlefonts | List of Google fonts to include in the page (eg. `["Monoton", "Lobster"]`)

### GitHub Project page vs user page

If you're not sure what the difference is, then ignore this section.

If you want to use this theme for a project page for a specific repository instead of your main GitHub user page, that's no problem. The demo for this site ([daattali.github.io/beautiful-jekyll](http://deanattali.com/beautiful-jekyll)) is actually set up as a project page while my personal site ([daattali.github.io](http://deanattali.com)) is a regular user page.  The only difference is that in the `_config.yml`, you should set `baseurl` to be `/projectname` instead of `""`.

---

### Credits

This template was not made entirely from scratch. I would like to give special thanks to:
- [Barry Clark](https://github.com/barryclark) and his project [Jekyll Now](https://github.com/barryclark/jekyll-now), from whom I've taken several ideas and code snippets, as well as some documenation tips.
- [Iron Summit Media](https://github.com/IronSummitMedia) and their project [Bootstrap Clean Blog](https://github.com/IronSummitMedia/startbootstrap-clean-blog), from which I've used some design ideas and some of the templating code for posts and pagination.

### Contributions

If you find anything wrong or would like to contribute in any way, feel free to create a pull request/open an issue/send me a message.  Any comments are welcome!

### Known limitations

- If you have a project page and you want a custom 404 page, you must have a custom domain.  See https://help.github.com/articles/custom-404-pages/.  This means that if you have a regular User Page you can use the 404 page from this theme, but if it's a website for a specific repository, the 404 page will not be used.
