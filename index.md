---
title: "Jekyll Doc Project: A Jekyll theme for documentation"
permalink: index.html
sidebar: jekyllhowto
type: homepage
class: first
custom_breadcrumb: Getting Started

---
<head>
<div class="banner" style="padding:5px; text-align:center;">
<div class="banner-content">
<p>This webpage is a simple collection of detailed resources and information I use for my phd work, as part of the statistics network and other research projects. The resources here are open-source and can be accessed <a href="https://github.com/davan690/" class="btn btn-primary">here</a>. I hope with time these resources will develop into a learning resource for researchers and small business owners, regardless of statistical knowledge. I post some of the interesting social media posts <a href="https://www.facebook.com/StatisticsNetwork/" class="btn btn-primary">here</a></p>
</div>
</div>
</head>
<body>
  
Here is the [webpage]("https://github.com/davan690/davan690.github.io/") repository for more computer minded (open-source resources and my research), and a [facebook]("https://www.facebook.com/StatisticsNetwork/")/[twitter]("") feed for new blog posts about statistics and ecology (not all from me).

# Current website

So far on the website I have four simple pages:

- [General statistics]("")
    - resources I use for statistics support

- [Ecological statistics]("")
    - resources I use for my PhD

- [Invasive species research]("")
    - my phd drafts

# Coming soon

- [Reproducibility]("")

- [Coding Sessions]("")

- [Bio-informatics]("")

<h2>Blog posts</h2>

<div class="posts-list">
  {% for post in paginator.posts %}
  <article class="post-preview">
    <a href="{{ post.url | prepend: site.baseurl }}">
	  <h2 class="post-title">{{ post.title }}</h2>

	  {% if post.subtitle %}
	  <h3 class="post-subtitle">
	    {{ post.subtitle }}
	  </h3>
	  {% endif %}
    </a>

    <p class="post-meta">
      Posted on {{ post.date | date: "%B %-d, %Y" }}
    </p>

    <div class="post-entry-container">
      {% if post.image %}
      <div class="post-image">
        <a href="{{ post.url | prepend: site.baseurl }}">
          <img src="{{ post.image }}">
        </a>
      </div>
      {% endif %}
      <div class="post-entry">
        {{ post.excerpt | strip_html | xml_escape | truncatewords: site.excerpt_length }}
        {% assign excerpt_word_count = post.excerpt | number_of_words %}
        {% if post.content != post.excerpt or excerpt_word_count > site.excerpt_length %}
          <a href="{{ post.url | prepend: site.baseurl }}" class="post-read-more">[Read&nbsp;More]</a>
        {% endif %}
      </div>
    </div>

    {% if post.tags.size > 0 %}
    <div class="blog-tags">
      Tags:
      {% if site.link-tags %}
      {% for tag in post.tags %}
      <a href="{{ site.baseurl }}/tags#{{- tag -}}">{{- tag -}}</a>
      {% endfor %}
      {% else %}
        {{ post.tags | join: ", " }}
      {% endif %}
    </div>
    {% endif %}

   </article>
  {% endfor %}
</div>

{% if paginator.total_pages > 1 %}
<ul class="pager main-pager">
  {% if paginator.previous_page %}
  <li class="previous">
    <a href="{{ paginator.previous_page_path | prepend: site.baseurl | replace: '//', '/' }}">&larr; Newer Posts</a>
  </li>
  {% endif %}
  {% if paginator.next_page %}
  <li class="next">
    <a href="{{ paginator.next_page_path | prepend: site.baseurl | replace: '//', '/' }}">Older Posts &rarr;</a>
  </li>
  {% endif %}
</ul>
{% endif %}  

# Contact

*Contact me* if you have any ideas or would like can contribute in any way

[Comment]("") on social media

**or**

[Email]("anthony.davidson@canberra.edu.au") any points that don't make sense.

**or even better**

[Fork]("https://github.com/davan690") the repository and add any comments via git commits.

Welcome to the "Pit of Success!" ^[Wickham quote]

[Image from a great talk Hadley wickham gave last year]("")

<h2>Feedback and comments</h2>

<p><a href="">Draft for comments</a> Here is the first chapter draft finally.</p>



The Jekyll Doc Project theme is intended for technical documentation projects, such as user guides for software, hardware, and APIs. This Jekyll theme (which has an Apache 2.0 open source license) uses pages exclusively and features robust multi-level navigation. It includes both web and PDF output. The GitHub repo is here: [amzn/jekyll-theme-doc-project](https://github.com/amzn/jekyll-theme-doc-project).

* TOC
{:toc}

## Installation

Before you can install the project, you may need to install Jekyll.

1.  Install Jekyll:
    * [Install Jekyll on Mac][jekyllhowto-install-jekyll-on-mac]
    * [Install Jekyll on Windows][jekyllhowto-install-jekyll-on-windows]

    You can check if you already have Jekyll installed by running `jekyll -v`. If you don't have the latest version, run `gem update jekyll`.

2.  Download the theme from the [amzn/jekyll-theme-doc-project](https://github.com/amzn/jekyll-theme-doc-project) repo.
3.  Configure the values in the **\_config.yml** file based on the inline code comments in that file.
4.  Serve or build the Jekyll site:

    ```
    jekyll serve
    ```

## Overwriting Theme Files

You'll most likely want to add some of your own styles, esp. to style the top navigation bar and other elements. There are three files specifically set up for this:

* **assets/css/pdf/user_defined_web_styles.css** (web styles)
* **assets/css/pdf/user_defined_pdf_styles.css** (print styles)
* **assets/js/user_defined_javascript.js** (web javascript)

These files are blank but are referenced in the theme's layout files. By adding these files in your project and defining your styles, they will automatically be included in the layout.

## Content Types

This theme uses collections exclusively (instead of posts). Collections are a content type, like a page or post. In this case, the content type is a document within the "docs" folder. Documents function just like pages, for the most part. (When referring to them in this documentation,  "pages" and "documents" are used interchangeably.) Organize your pages inside the **\_docs** folder.

Organize your pages with the folder structure that you want displayed in the [breadcrumb](#breadcrumbsection). Use the spacing and capitalization in your folder names that you want reflected in your breadcrumb path. For example, "Getting Started" instead of "getting_started".

The folder structure informs the breadcrumb display only. Upon build, the site output will pull all of the pages out of their folders, subfolders, etc., and put them into the root directory of \_site. This "flattening" of the page hierarchy enables relative linking in the project. Relative links allow you to view the built site offline or to push it from one environment or directory structure to the next without worrying about valid paths to theme assets or other links.

## Breadcrumbs {#breadcrumbsection}

If you want breadcrumbs in your project, set these properties in the \_config.yml file:

```yaml
# Display breadcrumbs at all?
breadcrumb_display: true

# Display Home path in breadcrumb?
breadcrumb_home_display: true

# Url for Home path to point to
breadcrumb_home_url: http://yourcompanysite.com

# Display name for "Home" path
breadcrumb_home_name: Home
```

Jekyll projects require an index.html (or index.md) file in your root directory. This is the page that loads by default. Because this page lives outside your regular \_docs directory, you have to manually define the breadcrumb path (after Home) that you want there.

Note that clicking the folder paths in the breadcrumb doesn't do anything except for Home. Visually, all paths look the same, but no logic is configured to dynamically render a list of items contained in file path folders.


## Images

You can store your images either inside or outside your project. In both cases, use the [image include][jekyllhowto-content-and-formatting#images_section] to insert images in your pages.

### Storing Images Inside the Project

If you want to store your images inside your Jekyll project, store the images in the \_docs/images folder. In the \_config.yml file, set the image path that will be prepended to the image file name. By default, the output will show the images in the same folder structure as you have in your Jekyll project source directory. If you put your images in **\/images**, then when your Jekyll site builds, your images will be in **\/images**. Rather than writing **images/myfile.png** in the `file` parameter of the image include, you can put the image path in the config file's `image_path` parameter:

```
image_path: images
```

This path will be prepended before image file names. (Note that a trailing slash is added automatically in the image include.)

This way, when you use the image include to insert images, you can simply write **myfile.png** for the `file` parameter.

### Storing Images Outside Your Project

Sometimes you might want to store your images outside your Jekyll build. Git repos don't handle large numbers of images well (your .git files become huge), since images are binaries. If you want to store images outside your project, open **.gitignore** and add **images** to it.


In the `image_path` property in the \_config.yml file, define the path where the images will be available:

```
image_path: https://s3-us-west-1.amazonaws.com/my-bucket-name/my-project-images
```

If you're using AWS S3, you can transfer images to your server from the command line. See [AWS Command Line Interface](http://docs.aws.amazon.com/cli/latest/userguide/cli-install-macos.html) for details. After installing the aws cli, you'll need to [configure your credentials](http://docs.aws.amazon.com/cli/latest/userguide/cli-config-files.html) and determine the right [commands to transfer files](http://docs.aws.amazon.com/cli/latest/userguide/using-s3-commands.html) to your bucket.

Within your Jekyll project, you could add a shell script that contains the command needed to transfer files to your bucket, like this:

```
aws s3 sync images s3://my-bucket-name/my-project-images
```

The images_upload.sh contains this generic AWS CLI command. The S3 bucket will store the images in a structure like this:

```
my-bucket-name > my-project-images > image1.png

├── my-bucket-name
│   ├── my-project-images
│      ├── image1.png
```

## Frontmatter

Make sure each page has frontmatter at the top like this:

```yaml
---
title: "Sample 1: The Beginning"
permalink: sample.html
sidebar: generic
product: Generic Product
---
```

(Even if it's a Markdown file, the `permalink` property should specify the .html extension, since this is how the file will appear in the output.)

<table>
   <colgroup>
      <col width="30%" />
      <col width="70%" />
   </colgroup>
   <thead>
      <tr>
         <th markdown="span">Property</th>
         <th markdown="span">Description</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td markdown="span">title</td>
         <td markdown="span">The title for the page. If you want to use a colon in your page title, you must enclose the title’s value in quotation marks. Note that titles in your pages' frontmatter are not synced with the titles in your sidebar data file. If you change it in one place, remember to change it in the other too.</td>
      </tr>
      <tr>
         <td markdown="span">permalink</td>
         <td markdown="span">Use the same name as your file name, but use ".html" instead of ".md" in the permalink property. Do not put forward slashes around the permalink (this makes Jekyll put the file inside a folder in the output). When Jekyll builds the site, it will put the page into the root directory rather than leaving it in a subdirectory or putting it inside a folder and naming the file index.html. </td>
      </tr>
      <tr>
         <td markdown="span">sidebar</td>
         <td markdown="span">The name of the sidebar that this page should use (don't include ".yml" in the name). </td>
      </tr>
      <tr>
         <td markdown="span">product</td>
         <td markdown="span">The product for this content. This appears in search and could be used in integrations with more robust search services.</td>
      </tr>
   </tbody>
</table>

{% include tip.html content="You can store the `sidebar` and `product` frontmatter as defaults in your project's \_config.yml file." %}

```
defaults:

  -
    scope:
      path: ""
      type: docs/myproject
    values:
      product: My Project
      sidebar: myprojectsidebar
```

In this example, all documents in the \_docs/myproject file will automatically have `product: My Project` and `sidebar: myprojectsidebar` as values in the frontmatter when the site builds.

## Sidebar Configuration

To configure the sidebar, copy the format shown in \_data/generic.yml into a new sidebar file. (Keep generic.yml as an example in your project, because YAML syntax can be picky and sometimes frustrating to get right. Generic.yml shows an example of content at every level.)

Each of your pages should reference the appropriate sidebar either in the page's frontmatter or as defined in the defaults in your \_config.yml file. See [Sidebar Navigation][jekyllhowto-sidebar-navigation] for more details.

## Top Navigation Bar

You configure the top navigation bar through the \_data/topnav.yml file. You can configure single links or links with drop downs. If you want the search to appear in the sidebar rather than the top nav, see these options in the \_config.yml file:

```yaml
search_in_topnav: true
search_in_sidebar: false
```

Placing the search in the top navigation bar gives the theme more visual balance.

When you shrink the browser size, the navbar options change to a couple of icons. You can control whether those icons appear with these settings in \_config.yml:

```yaml
toggle-sidebar-button: none
navbar-toggle: none
```

(You might want to hide these buttons if your nav bar doesn't have any links or options, or if the sidebar is empty.)

## Configure the Footer

You configure the footer through the options in \_data/footer.yml.

{% include links.html %}

</body>
