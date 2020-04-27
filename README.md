# Beautiful Jekyll

![Beautiful Jekyll CI](https://github.com/daattali/beautiful-jekyll/workflows/Beautiful%20Jekyll%20CI/badge.svg)
[![Gem Version](https://badge.fury.io/rb/beautiful-jekyll-theme.svg)](https://badge.fury.io/rb/beautiful-jekyll-theme)

> *Copyright 2020 [Dean Attali](https://deanattali.com)*

**Beautiful Jekyll** is a ready-to-use template to help you create an awesome website quickly. Perfect for personal sites, blogs, or simple project websites.  [Check out a demo](https://deanattali.com/beautiful-jekyll) of what you'll get after just two minutes.  You can also look at [my personal website](https://deanattali.com) to see it in use, or see examples of websites other people created using this theme [below](#showcased-users-success-stories).

**If you enjoy this theme, please consider [supporting me](http://paypal.me/daattali) or [sponsoring me](https://github.com/sponsors/daattali) for developing and maintaining it for over 5 years.**

<p align="center">
  <a style="display: inline-block;" href="https://paypal.me/daattali">
    <img height="40" src="https://camo.githubusercontent.com/0e9e5cac101f7093336b4589c380ab5dcfdcbab0/68747470733a2f2f63646e2e6a7364656c6976722e6e65742f67682f74776f6c66736f6e2f70617970616c2d6769746875622d627574746f6e40312e302e302f646973742f627574746f6e2e737667" />
  </a>&nbsp;&nbsp;
  <a style="display: inline-block;" href="https://github.com/sponsors/daattali">
    <img height="40" src="https://i.imgur.com/034B8vq.png" />
  </a>
</p>

### Table of contents

- [Build your website in 3 steps](#build-your-website-in-3-steps)
  - [The easy way (recommended!)](#the-easy-way-recommended)
  - [The hard way (skip this section if you followed the easy way)](#the-hard-way-skip-this-section-if-you-followed-the-easy-way)
- [Add your own content](#add-your-own-content)
- [Last important thing: parameters for each page](#last-important-thing-parameters-for-each-page)
- [Features](#features)
- [Supported YAML front matter parameters](#supported-yaml-front-matter-parameters)
- [Showcased users (success stories!)](#showcased-users-success-stories)
- [FAQ and support](#faq-and-support)
- [Credits and contributions](#credits)

## Build your website in 3 steps

There's a very easy way to use this theme, and there's a hard way. If you're an advanced user and want to tinker with the hard way, feel free to [skip this section and jump down](#the-hard-way-skip-this-section-if-you-followed-the-easy-way). I suggest going the easy route.  

### The easy way (recommended!)

Getting started is *literally* as easy as 1-2-3 :smile:

Scroll down to see the steps involved, but here is a 40-second video just as a reference as you work through the steps. If you don't already have a [GitHub account](https://github.com/join), you'll need to sign up.

![Installation steps](assets/img/install-steps.gif)

#### 1. Fork this project

Fork this project by clicking the __*Fork*__ button at the top right corner of this page. Forking means that you now copied this entire project and all the files into your account.

#### 2. Rename the project to `<yourusername>.github.io`

Click on __*Settings*__ at the top (the cog icon) and on that page you'll have an option to rename the project (*repository name*). This will create a website with the **Beautiful Jekyll** template that will be available at `https://<yourusername>.github.io` within a couple minutes. Check out the [FAQ](#faq-and-support) if you want to use a different project name. 

#### 3. Customize your website settings

Edit the `_config.yml` file to change any settings you want. To edit the file, click on it to view the file and then click on the pencil icon to edit it (watch the video tutorial above if you're confused).  The settings in the file are self-explanatory and I added comments inside the file to help you understand what each setting does. Any line that begins with a hashtag (`#`) is a comment, and the other lines are actual settings.

#### 4. Congratulations! You have a website!

After you save your changes to the config file (by clicking on *Commit changes* as the video tutorial shows), your website should be ready in a minute or two at `https://<yourusername>.github.io`. Every time you make a change to any file, your website will get rebuilt and should be updated in about a minute or so. Your website will be initialized with several sample blog posts and a couple other pages.

Note that in the video above I only edited one setting in the `_config.yml` file. **You should actually go through the rest of the settings as well. Don't be lazy, go through all the settings :)**

*** If you've reached this point, you should skip over the next section (the hard way of setting up a website) and jump straight to [Add your own content](#add-your-own-content). ***

### The hard way (skip this section if you followed the easy way)

Beautiful-Jekyll was initially developed as a GitHub Pages theme that was meant to be used via forking as described above, but due to high demand it's also available as a Github "remote_theme" and as a Ruby Gem. Apart from the method mentioned above, there are three other ways of using beautiful-jekyll. These are advanced uses and you should only use one of these methods if you know how to write jekyll sites from scratch. You should look up the official documentation for whichever method you want to use, but here are the basics:

- Using `remote_theme` with a GitHub repository

    - Create a new GitHub repository or go to an existing repository
    - Go to _Settings_, scroll down to the _GitHub Pages_ section, and choose "master branch" as the source
    - Add `remote_theme: daattali/beautiful-jekyll@2.0.0` to your `_config.yml` file (make sure to remove any previous `theme` or `remote_theme` parameters that may have been there before)

- Using `remote_theme` with a Ruby Jekyll site

    - Install Ruby and Jekyll (`sudo apt-get install ruby ruby-dev make gcc` and `sudo gem install jekyll bundler`)
    - Create a new jekyll site (e.g. `jekyll new mysite`)
    - Add `gem "jekyll-remote-theme"` to your Gemfile and then run `bundle install` to install the plugin
    - Add `remote_theme: daattali/beautiful-jekyll@2.0.0` to your `_config.yml` file (make sure to remove any previous `theme` or `remote_theme` parameters that may have been there before)
    - Add `- jekyll-remote-theme` to the plugins section of your `_config.yml` file to activate the plugin

- Using the Beautiful-Jekyll theme gem

    - Install Ruby and Jekyll (`sudo apt-get install ruby ruby-dev make gcc` and `sudo gem install jekyll bundler`)
    - Create a new jekyll site (e.g. `jekyll new mysite`)
    - Add `gem "beautiful-jekyll-theme", "2.0.0"` to your Gemfile
    - Add `theme: beautiful-jekyll-theme` to your `_config.yml`
    - Run `bundle`
    - You can preview the site using `bundle exec jekyll serve` (optionally with `-H 0.0.0.0` if needed)

If you use beautiful-jekyll with the "easy way", you'll have direct access to all the files because you'll be copying the project. But if you use one of these three "hard" methods, many of the theme's files and folders will be hidden from you, so you'll need to:

- Go through beautiful-jekyll's `_config.yml` file and copy any settings you want to use into your project's config file.
- Some config features will not work because of missing files that you'll need to copy from beautiful-jekyll into your project. To enable the `link-tags` feature, you need to copy `tags.html`. To enable the RSS feed, copy `feed.xml`. If you use staticman comments, copy `staticman.yml` and `_data/ui-text.yml`.
- If you want the home page to include a feed of all blog posts, create an index.html file and use `layout: home` in its YAML.
- If you want to replace any file served from beautiful-jekyll (such as a CSS file, a layout, or an include), you'll need to place it with the exact same path in your own jekyll repo (e.g. /assets/css/main.css)

---

## Add your own content

To add pages to your site, you can either write a markdown file (`.md`) or you can write an HTML file directly.  It's much easier to write markdown than HTML, so I suggest you do that (use [this great tutorial](https://markdowntutorial.com/) if you need to learn markdown in 5 minutes). You can look at some files on this site to get an idea of how to write markdown. To look at existing files, click on any file that ends in `.md`, for example [`aboutme.md`](./aboutme.md). On the next page you can see some nicely formatted text (there's a word in bold, a link, a few bullet points), and if you click on the pencil icon to edit the file, you'll see the markdown that generated the pretty text. Very easy!

In contrast, look at [`tags.html`](./tags.html). That's how your write HTML - not as pretty. So stick with markdown if you don't know HTML.

Files you create inside the [`_posts`](./_posts) directory will be treated as blog entries. You can look at the existing files there to get an idea of how to write blog posts. Note the format of the blog post files - they must follow the naming convention of `YEAR-MONTH-DAY-title.md`. After you successfully add your own post, you can delete the existing files inside [`_posts`](./_posts) to remove the sample posts, as those are just demo posts to help you learn.

## Last important thing: parameters for each page

In order to have your new pages use this template and not just be plain HTML pages, **you must add [YAML front matter](https://jekyllrb.com/docs/front-matter/) to the top of each page**. This is where you'll be able to give each page some extra parameters such as a title, a subtitle, or an image. [Below is a list of all available parameters](#supported-yaml-front-matter-parameters). If you don't want to use any parameters on a page (this also means having no title), then use the empty YAML front matter:

```
---
---
```

If you do want to use any parameters, write them between these two lines. For example, you can have this at the top of a page:

```
---
title: Contact me
subtitle: Here you'll find all the ways to get in touch with me
---
```

You can look at the top of [`aboutme.md`](https://raw.githubusercontent.com/daattali/beautiful-jekyll/master/aboutme.md) as an example.

**Important takeaway: ALWAYS add the YAML front matter, which is two lines with three dashes, to EVERY page. If you have any parameters, they go between the two lines.**

If you don't include YAML then your file will not use this template.

## Features

### Mobile-first

**Beautiful Jekyll** is designed to look great on both large-screen and small-screen (mobile) devices. Load up your site on your phone or your gigantic iMac, and the site will work well on both, though it will look slightly different.

### Highly customizable

Many personalization settings in `_config.yml`, such as setting your name and site's description, changing the background colour/image, setting your avatar to add a little image in the navigation bar, and many more.

### Two-level navigation menu

If you have too many pages and your menu is getting cluttered, **Beautiful Jekyll** allows you to separate your menu into two levels for  better page organization.

### Links to your social media

You can easily add links to your email, phone, and all your social media accounts in the footer of every page. You can show as much or as little information as you want.

### Adding Google Analytics to track page views

Beautiful Jekyll lets you easily add Google Analytics to all your pages. This will let you track all sorts of information about visits to your website, such as how many times each page is viewed and where (geographically) your users come from.  To add Google Analytics, simply sign up to [Google Analytics](https://www.google.com/analytics/) to obtain your Google Tracking ID, and add this tracking ID to the `google_analytics` parameter in `_config.yml`.

### Sharing blog posts on social media

By default, all blog posts will have buttons at the bottom of the post to allow people to share the current page on Twitter/Facebook/LinkedIn.  You can choose to enable/disable specific social media websites in the `_config.yml` file. You can also turn off the social media buttons on specific blog posts using `social-share: false` in the YAML front matter.

### Advanced features (including how to use a custom URL address for your site)

I wrote [a blog post](https://deanattali.com/2015/03/12/beautiful-jekyll-how-to-build-a-site-in-minutes/) describing some more advanced features that I used in my website that are applicable to any Jekyll site.  It describes how I used a custom URL for my site (deanattali.com instead of daattali.github.io), how to add a Google-powered search into your site, and provides a few more details about having an RSS feed.

### Allowing users to leave comments

If you want to enable comments on your site, Beautiful Jekyll supports several different commenting platforms you can choose from: [Disqus](https://disqus.com/), [Facebook](https://developers.facebook.com/docs/plugins/comments), [Utterances](https://utteranc.es/), and [Staticman](https://staticman.net). If any of these are set in the configuration file, then all blog posts will have comments turned on by default. To turn off comments on a particular blog post, add `comments: false` to the YAML front matter. If you want to add comments on the bottom of a non-blog page, add `comments: true` to the YAML front matter.

#### Disqus comments

To use Disqus, simply sign up to [Disqus](https://disqus.com/) and add your Disqus shortname to the `disqus` parameter in the `_config.yml` file.

#### Facebook comments

To use Facebook comments, create a Facebook app using [Facebook developers](https://developers.facebook.com/docs/apps/register), and add the Facebook App ID to the `fb_comment_id` parameter in `_config.yml`.

#### Utterances comments 

To use [Utterances comments](https://utteranc.es/), follow these steps: (1) Enable Issues in your GitHub repository, (2) Install the Utterances app in your repository (go to https://github.com/apps/utterances), (3) Fill in the `repository` parameter in the utterances section of the `_config.yml` file.

#### Staticman comments

To use Staticman, you first need to invite `staticmanlab` as a collaborator to your repository (by going to your repository **Settings** page, navigate to the **Collaborators** tab, and add the username `staticmanlab`), and then accept the invitation by going to `https://staticman3.herokuapp.com/v3/connect/github/<username>/<repo-name>`. Lastly, fill in the `staticman` parameters in the Staticman section of `_config.yml`. You may also choose a different Staticman instance other than `staticmanlab`.

Optional: You may want to configure a webhook to prevent old inactive branches (representing approved comments) from stacking up.  You can refer to [Staticman's documentation](https://staticman.net/docs/webhooks) for details.  Make sure to input the **Payload URL** according to your chosen `endpoint`.  For example, the default `endpoint` is `https://staticman3.herokuapp.com/v3/entry/github/`, so the corresponding **Payload URL** should be `https://staticman3.herokuapp.com/v1/webhook`.

## Supported YAML front matter parameters

These are the main parameters you can place inside a page's YAML front matter that **Beautiful Jekyll** supports.

Parameter   | Description
----------- | -----------
title       | Page or blog post title
subtitle    | Short description of page or blog post that goes under the title
tags        | List of tags to categorize the post. Separate the tags with commas and place them inside square brackets. Example: `[personal, self help, finance]`
bigimg      | Include a large full-width image at the top of the page.  You can either give the path to a single image, or provide a list of images to cycle through (see [my personal website](https://deanattali.com/) as an example).
comments    | If you want do add comments to a specific page, use `comments: true`. Comments are automatically enabled on blog posts; to turn comments off for a specific post, use `comments: false`. Comments only work if you enable at least one provider(Facebook, disqus, staticman) in `_config.yml` file.
show-avatar | If you have an avatar configured in the `_config.yml` but you want to turn it off on a specific page, use `show-avatar: false`. If you want to turn it off by default, locate the line `show-avatar: true` in the file `_config.yml` and change the `true` to `false`; then you can selectively turn it on in specific pages using `show-avatar: true`.
image       | If you want to add a personalized image to your blog post that will show up next to the post's excerpt and on the post itself, use `image: /path/to/img`.
readtime    | If you want to show how many minutes it will take to read a post in the header, add `readtime: true`.
share-img   | If you want to specify an image to use when sharing the page on Facebook or Twitter, then provide the image's full URL here.
social-share | If you don't want to show buttons to share a blog post on social media, use `social-share: false` (this feature is turned on by default).
use-site-title | If you want to use the site title rather than page title as HTML document title (ie. browser tab title), use `use-site-title: true`. When set, the document title will take the format `Site Title - Site Description` (eg. `My website - A virtual proof that name is awesome!`). By default, it will use `Page Title` if it exists, or `Site Title` otherwise.
language    | HTML language code to be set on &lt;html&gt; element (see [W3Schools website](https://www.w3schools.com/tags/ref_language_codes.asp) for more info on this topic).  Language can also be set site-wide in `_config.yml`.
layout      | What type of page this is (default is `post` for blog posts and `page` for other pages). See _Page types_ section below for more information. 
gh-repo   | If you want to show GitHub buttons at the top of a post, this sets the GitHub repo name (eg. `daattali/beautiful-jekyll`). You must also use the `gh-badge` parameter to specify what buttons to show.
gh-badge  | Select which GitHub buttons to display. Available options are: [star, watch, fork, follow]. You must also use the `gh-repo` parameter to specify the GitHub repo.
js          | List of local JavaScript files to include in the page (eg. `/assets/js/mypage.js`)
ext-js      | List of external JavaScript files to include in the page (eg. `//cdnjs.cloudflare.com/ajax/libs/underscore.js/1.8.2/underscore-min.js`). External JavaScript files that support [Subresource Integrity (SRI)](https://developer.mozilla.org/en-US/docs/Web/Security/Subresource_Integrity) can be specified using the `href` and `sri` parameters eg.<br/>`href: "//code.jquery.com/jquery-3.1.1.min.js"`<br/>`sri: "sha256-hVVnYaiADRTO2PzUGmuLJr8BLUSjGIZsDYGmIJLv2b8="`
css         | List of local CSS files to include in the page
ext-css      | List of external CSS files to include in the page. External CSS files using SRI (see `ext-js` parameter) are also supported.
googlefonts | List of Google fonts to include in the page (eg. `["Monoton", "Lobster"]`)

### Page types

- **post** - To write a blog post, add a markdown or HTML file in the `_posts` folder. As long as you give it YAML front matter (the two lines of three dashes), it will automatically be rendered like a blog post. Look at the existing blog post files to see examples of how to use YAML parameters in blog posts.
- **page** - Any page outside the `_posts` folder that uses YAML front matter will have a very similar style to blog posts.
- **home** - The home layout is meant to act as the homepage of your blog posts - it will display all your blog posts, sorted from newest to oldest. A file using the `home` layout must be named `index.html` (not `index.md` or anything else!).
- **minimal** - If you want to create a page with minimal styling (ie. without the bulky navigation bar and footer), assign `layout: minimal` to the YAML front matter.
- If you want to completely bypass the template engine and just write your own HTML page, simply omit the YAML front matter. Only do this if you know how to write HTML!

## Showcased users (success stories!)

Beautiful Jekyll has been used in over 500 websites in its first 6 months, and tens of thousands of times since its inception.  Here is a sample of some websites that use Beautiful Jekyll.

### Project/company websites

| Website | Description |
| :------ |:----------- |
| [repidemicsconsortium.org/](https://www.repidemicsconsortium.org/) | R Epidemics Consortium |
| [vaccineimpact.org](https://www.vaccineimpact.org/) | Vaccine Impact Modelling Consortium |
| [derekogle.com/fishR](http://derekogle.com/fishR/) | Using R for Fisheries Analyses |
| [bigdata.juju.solutions](http://bigdata.juju.solutions) | Creating Big Data solutions Juju Solutions |
| [joecks.github.io/clipboard-actions](http://joecks.github.io/clipboard-actions/) | Clipboard Actions - an Android app |
| [deanattali.com/shinyjs](http://deanattali.com/shinyjs/) | shinyjs - an R package |
| [blabel.github.io](http://blabel.github.io) | Library for canonicalising blank node labels in RDF graphs |
| [reactionic.github.io](http://reactionic.github.io) | Create iOS and Android apps with React and Ionic |
| [ja2-stracciatella.github.io](http://ja2-stracciatella.github.io) | Jagged Alliance 2 Stracciatella |
| [ddocent.com](http://ddocent.com/) | RADSeq Bioinformatics and Beyond |
| [guitarlessons.org](https://www.guitarlessons.org/) | Free online guitar lessons for all |
| [terremotocentroitalia.info](https://www.terremotocentroitalia.info/) | Information about the 2016 Italy earthquake |


### Personal websites

| Website | Who | What |
| :------ |:--- | :--- |
| [deanattali.com](https://deanattali.com) | Dean Attali | Creator of Beautiful Jekyll |
| [ouzor.github.io](http://ouzor.github.io) | Juuso Parkkinen | Data scientist |
| [derekogle.com](http://derekogle.com/) | Derek Ogle | Professor of Mathematical Sciences and Natural Resources |
| [melyanna.github.io](http://melyanna.github.io/) | Melyanna | Shows off her nice art |
| [chauff.github.io](http://chauff.github.io/) | Claudia Hauff | Professor at Delft University of Technology |
| [kootenpv.github.io](http://kootenpv.github.io/) | Pascal van Kooten | Data analytics |
| [sjackman.ca](http://sjackman.ca) | Shaun Jackman | PhD candidate in bioinformatics |
| [anudit.in](http://www.anudit.in/) | Anudit Verma | Engineering student |
| [sharepointoscar.github.io](http://sharepointoscar.github.io) | Oscar Medina | Independent Hacker |
| [ocram85.com](https://ocram85.com) | Marco Blessing | A personal blog about PowerShell and automation |
| [khanna.cc](https://khanna.cc/) | Harry Khanna | Law and software |

## FAQ and support

If you need any help, I suggest heading over to the [Jekyll support forum](https://talk.jekyllrb.com/).

Beautiful Jekyll is actively used by thousands of people with wildly varying degrees of competency, so it's impossible to answer all the questions that may arise. Below are answers to a few very common questions. Most questions that I get asked are not directly related to this theme, and instead are more general questions about Jekyll or web development. Many such questions can be answered by reading the [Jekyll documentation](https://jekyllrb.com/) or with Google.

#### What if I don't want the website to be `https://<yourusername>.github.io`?

Every GitHub user can have one repository (repository = project) named `<yourusername>.github.io` and the website for that repository will be `https://<yourusername>.github.io`. 

If you want your project to be named something else, for example `MyAwesomeProject`, that's no problem! All you have to do is go to _Settings_ at the top right corner of the page, and rename your repository to `MyAwesomeProject` (remember to click on the _Rename_ button to confirm). Then you need to scroll down to the _GitHub Pages_ section and choose "master branch" as the source (not "master branch /docs folder"!).

Now your website will be at `https://<yourusername>.github.io\MyAwesomeProject`.

#### How do I change the number of posts per page OR the colour of the navigation bar OR the image in the navigation bar OR ...?

Beautiful Jekyll is built to be very customizable, and as such, many questions about "how do I change ..." can be answered by looking at the `_config.yml` file. The configuration file has many adjustable parameters to customize your site.

#### How do I add a favicon to my site?

Easy! Just place a valid `favicon.ico` in the root directory of your project. And then wait! It can take a while to update.

#### How do I move the blog to another page instead of having it on the home page?

The default style of Beautiful Jekyll is to feature the blog feed on the front page. But for many sites that's not the ideal structure, and you may want to have a separate dedicated page for the blog posts. To have the blog hosted on a different URL (for example at `<mysite.com>/blog`), copy the `index.html` file into a folder with the same name as the desired page (for example, to `blog/index.html`), and in the `_config.yml` file you need to add a parameter `paginate_path: "/<page name>/page:num/"` (for example `paginate_path: "/blog/page:num/"`).

#### What size do you recommend using for the `bigimg` photos?

Unfortunately, this is a no-answer! There isn't a one-size-fits-all solution to this, because every person will view your site on a different browser with different dimensions. Some browsers will have very wide aspect ratio, some will be narrower, some will be vertical (such as phones), different phones have different screens, etc. The image will always be centered, so the only tip I can give is that you should make sure the important part of the image is in the middle so that it'll always show. Other than that, every browser will show a different clipping of the image.

#### How do I use MathJax equations in my posts?

MathJax can be easily integrated into your website with a one-line addition. You can see [this discussion](https://github.com/daattali/beautiful-jekyll/issues/195) for more information.

## Credits

This template was not made entirely from scratch. I would like to give special thanks to:
- [Barry Clark](https://github.com/barryclark) and his project [Jekyll Now](https://github.com/barryclark/jekyll-now), from whom I've taken several ideas and code snippets, as well as some documenation tips.
- [Iron Summit Media](https://github.com/IronSummitMedia) and their project [Bootstrap Clean Blog](https://github.com/IronSummitMedia/startbootstrap-clean-blog), from which I've used some design ideas and some of the templating code for posts and pagination.

I'd also like to thank [Dr. Jekyll's Themes](https://drjekyllthemes.github.io/), [Jekyll Themes](http://jekyllthemes.org/), and another [Jekyll Themes](http://jekyllrc.github.io/jekyllthemes/) for featuring Beautiful Jekyll in their Jekyll theme directories.

## Contributions

If you find anything wrong or would like to contribute in any way, feel free to create a pull request/open an issue/send me a message.  Any comments are welcome!

Thank you to [all contributors](https://github.com/daattali/beautiful-jekyll/graphs/contributors). Special thanks to  [@OCram85](https://github.com/OCram85) and [@abelcheung](https://github.com/abelcheung) for contributing multiple times as well as helping with discussions.

If you do fork or clone this project to use as a template for your site, I would appreciate if you keep the link in the footer to this project.  I've noticed that several people who forked this repo removed the attribution and I would prefer to get the recognition if you do use this :)

## Known limitations

- If there are many navigation bar links and an avatar, some of the links may get partially hidden behind the avatar. I suggest either re-thinking the number of links, or not using an avatar.
