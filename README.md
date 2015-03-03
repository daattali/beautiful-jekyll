# Beautiful Jekyll

[Jekyll](http://jekyllrb.com/) is a simple site generator that is used for hosting [GitHub Pages](https://pages.github.com/) and specializes in blogging-type websites, although it can work with any site.

GitHub pages makes it extremely simple to host your own website or a website for a GitHub repository within minutes **for free**.  While it's very easy to get started with GitHub Pages, you will get very basic looking pages and basic functionality.

**Beautiful Jekyll** is a ready-to-use template to make help you create an awesome Jekyll or GitHub Page website quickly.  [Check out a demo](http://deanattali.com/beautiful-jekyll) of what you'll get after just two minutes or look at [my personal website](http://deanattali.com) to see it in use.

## Build your website in 3 steps

Getting started is *literally* as easy as 1-2-3 :smile:

### 1. Fork this repository 

Fork this repository by clicking the Fork button on the top right corner.

### 2. Rename the repository to `yourusername.github.io`

This will create a GitHub User page ready with the Beautiful Jekyll template that will be available at http://yourusername.github.io (sometimes it takes a few minutes).

### 3. Customize settings

Edit the `_config.yml` file to change all the settings to reflect your site.  The settings in the file are fairly self-explanatory and I added comments inside the file to help you further.  Every time you make a change to any file, your website will get rebuilt and should be updated at `yourusername.github.io` within a minute.

You can now visit your shiny new website, which will be seeded with several sample blog posts and a couple other pages.


![Installation steps](img/install-steps.gif)

### Add your own content

To add pages to your site, you can either write a markdown file (`.md`) which will automatically get converted to HTML, or you can write an HTML file directly.  It is much easier to write mardown; you write normal text with a few styling identifiers, and Jekyll will know how to automatically render it as a pretty HTML page. Markdown is extremely easy to use, just [look at the reference](http://daringfireball.net/projects/markdown/syntax) and at  some files on the site to get an idea.

Any markdown or HTML file you add to the root directory will be immediately available on your site. Take a look at the `aboutme.md` and `index.html` files as examples. Any file inside the `_posts` directory will be treated as a blog entry.  You can look at the existing files there to get an idea of how to write blog posts, and delete them when you feel ready.

### Features
- mobile
- avatar
- footer links
- navbar links
- YAML params
- page types


### Project page vs user page

If you want to use this as a project page for a specific repository instead of your main GitHub user page, th


### Credits

This template was not made entirely from scratch. I would like to give special thanks to:
- [Barry Clark](https://github.com/barryclark) and his project [Jekyll Now](https://github.com/barryclark/jekyll-now), from whom I've taken several ideas and code snippets, as well as some documenation tips.
- [Iron Summit Media](https://github.com/IronSummitMedia) and their project [Bootstrap Clean Blog](https://github.com/IronSummitMedia/startbootstrap-clean-blog), from which I've used some design ideas and some of the templating code for posts and pagination.

### Contributions

If you find anything wrong or would like to contribute it any way, feel free to create a pull request/open an issue/send me a message.  Any comments are welcome!

### Known bugs

- If you have a project page and you want a custom 404 page, you must have a custom domain.  See https://help.github.com/articles/custom-404-pages/.  This means that if you have a regular User Page you can use the 404 page from this theme, but if it's a website for a specific repository, the 404 page will not be used.
