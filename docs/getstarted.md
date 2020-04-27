---
layout: page
title: Getting started
subtitle: How to use Beautiful Jekyll
bigimg: /assets/img/start.jpg
css: /assets/css/demo.css
---

**Beautiful Jekyll** is a ready-to-use template to make help you create an awesome Jekyll or GitHub Pages website quickly. 

To learn how you can use **Beautiful Jekyll** to create your website in minutes, go to the [Beautiful Jekyll project page](https://github.com/daattali/beautiful-jekyll#readme).


<div class="get-started-wrap">
  <a class="btn btn-success btn-lg get-started-btn" href="https://github.com/daattali/beautiful-jekyll#readme">Get Started!</a>
</div>
<br/>

## Installation steps (recommended way)

There are only three simple steps, so using **Beautiful Jekyll** is *literally* as easy as 1-2-3 :)    

Here is a 40-second video showing how to get started, with the specific steps below.  For a more complete installation guide, [visit the Beautiful Jekyll page](https://github.com/daattali/beautiful-jekyll#readme).

<img src="../assets/img/install-steps.gif" style="width:100%;" alt="Installation steps" />

#### 1. Fork (copy) the Beautiful Jekyll project 

#### 2. Rename the project to `yourusername.github.io`

#### 3. Customize settings in the `config.yml` file to personalize your website

That's it! You can now visit your shiny new website.

---

See how easy that is? I wasn't lying - it really can be done in two minutes.

<div class="get-started-wrap">
  <a class="btn btn-success btn-lg get-started-btn" href="https://github.com/daattali/beautiful-jekyll#readme">Get Started!</a>
</div>

<br/><br/>

<div id="install-steps-hard"></div>

## Installation steps (as a ruby gem - the hard way)

**For most people (including myself!), I suggest using the easy way and ignoring this section**. If you're an advanced user and want to use beautiful-jekyll as a ruby gem, then follow these steps.

Beautiful-Jekyll was initially developed as a GitHub Pages theme that was meant to be used via forking as described above, but due to high demand it's now also available as a Github "remote_theme" and as a Ruby Gem.

There are three other ways of using beautiful-jekyll. These are advanced uses and you should only use one of these methods if you know how to write jekyll sites from scratch. You should look up the official documentation for whichever method you want to use, but here are the basics:

- Using `remote_theme` with a GitHub repository

    - Create a new GitHub repository or go to an existing repository
    - Add `remote_theme: daattali/beautiful-jekyll@2.0.1` to your `_config.yml` file (make sure to remove any previous `theme` or `remote_theme` parameters that may have been there before)
    - Go to _Settings_, scroll down to the _GitHub Pages_ section, and choose "master branch" as the source
    - Your website will be at `https://<yourusername>.github.io\<projectname>`

- Using `remote_theme` with a Ruby Jekyll site

    - Install Ruby and Jekyll (`sudo apt-get install ruby ruby-dev make gcc` and `sudo gem install jekyll bundler`)
    - Create a new jekyll site (e.g. `jekyll new mysite`)
    - Add `gem "jekyll-remote-theme"` to your Gemfile and then run `bundle install` to install the plugin
    - Add `remote_theme: daattali/beautiful-jekyll@2.0.1` to your `_config.yml` file (make sure to remove any previous `theme` or `remote_theme` parameters that may have been there before)
    - Add `- jekyll-remote-theme` to the plugins section of your `_config.yml` file to activate the plugin

- Using the Beautiful-Jekyll theme gem

    - Install Ruby and Jekyll (`sudo apt-get install ruby ruby-dev make gcc` and `sudo gem install jekyll bundler`)
    - Create a new jekyll site (e.g. `jekyll new mysite`)
    - Add `gem "beautiful-jekyll-theme", "2.0.1"` to your Gemfile
    - Add `theme: beautiful-jekyll-theme` to your `_config.yml`
    - Run `bundle`

If you're developing using a local ruby gem (as opposed to on GitHub), you can preview your site by running `bundle exec jekyll serve` (optionally with `-H 0.0.0.0` if needed).

When you use beautiful-jekyll with the "easy way", you'll have direct access to all the theme's files because you'll be literally copying the project. But if you use one of these three "hard" methods, many of the theme's files and folders will be hidden from you, so you'll need to:

- Go through beautiful-jekyll's [`_config.yml`](https://github.com/daattali/beautiful-jekyll/blob/master/_config.yml) file and copy any settings you want to use into your project's config file.
- Some config features will not work immediately because of missing files that you'll need to copy from beautiful-jekyll into your project
    - To enable the `link-tags` feature, you need to copy [`tags.html`](https://github.com/daattali/beautiful-jekyll/blob/master/tags.html)
    - To enable the RSS feed, copy [`feed.xml`](https://github.com/daattali/beautiful-jekyll/blob/master/feed.xml)
    - If you use staticman comments, copy `staticman.yml` and `_data/ui-text.yml`.
- If you want the home page to include a feed of all blog posts, create an index.html file and use `layout: home` in its YAML.
- If you want to replace any file served from beautiful-jekyll (such as a CSS file, a layout, or an include), you'll need to place it with the exact same path in your own jekyll repo (e.g. /assets/css/main.css)

If at any point in the future you want to update to a newer version of beautiful-jekyll, you can come back to this page and see if there's a new version. If there is, you can simply update the `remote_theme` or `gem` fields accordingly.

After setting up your site, you still need to go through the rest of the beautiful-jekyll documentation to learn about all its features and how to use it.

<div class="get-started-wrap">
  <a class="btn btn-success btn-lg get-started-btn" href="https://github.com/daattali/beautiful-jekyll#add-your-own-content">Read Documentation</a>
</div>
