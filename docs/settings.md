# Settings

Customize your website theme colors, layout, titles and more. The settings files can be found in `src/yml`.

## Site

The general settings can be found in [`src/yml/site.yml`](https://github.com/thiagorossener/jekflix-template/blob/master/src/yml/site.yml).

> **IMPORTANT:** Only when cloning the repo. If you're using the `gem`, modify those properties in your `_config.yml`.

#### `name`

Type: *string*

The website name will appear in several places, the most important one is at the header.

Example:

```yaml
# site.yml
name: Jekflix
```

#### `title`

Type: *string*

The website title is used for SEO purposes and set the home page title.

Example:

```yaml
# site.yml
title: Jekflix | A blog theme for Jekyll
```

#### `description`

Type: *string*

The website description is used for SEO purposes only.

Example:

```yaml
# site.yml
description: Jekflix is a template for Jekyll inspired by Netflix and made by Thiago Rossener.
```

#### `tags`

Type: *list*

The website tags are used as keywords for SEO purposes.

Example:

```yaml
# site.yml
tags:
  - blog
  - template
  - jekyll
  - theme
  - netlify
```

#### `email`

Type: *string*

The email is used for the Contact page with legacy [Formspree](https://formspree.io/) forms.

Leaving this and `formspree_form_id` blank won't show a Contact page.

> **Warning:** This will become obsolete in v4

Example:

```yaml
# site.yml
email: youremail@xyz.com
```

#### `formspree_form_id `

Type: *string*

The [Formspree](https://formspree.io/) ID is used in Contact page.

Leaving this and `email` blank won't show a Contact page.

Example:

```yaml
# site.yml
formspree_form_id: your_formspree_form_id
```

#### `disqus_username`

Type: *string*

Set your [Disqus](https://disqus.com) username to add comments to your posts. Leave it blank if you don't want enable comments.

Example:

```yaml
# site.yml
disqus_username: disqus_username
```

#### `show_hero`

Type: *boolean*

Show/hide hero in the home page. It accepts the values `true` or `false`.

Example with hero:

```yaml
# site.yml
show_hero: true
```

![Home page with hero screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566477681/page-with-hero-screenshot_ixyjzp.jpg)

Example without hero:

```yaml
# site.yml
show_hero: false
```

![Home page without hero screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566477862/page-without-hero-screenshot_gobnva.jpg)

#### `paginate`

Type: *integer*

Add pagination to the home page.

Set an integer > 0 to the amount of posts to show per page. Leave it blank if you don't want pagination.

```yaml
# site.yml
paginate: 12
```

## Social

The social settings can be found in [`src/yml/social.yml`](https://github.com/thiagorossener/jekflix-template/blob/master/src/yml/social.yml). Social media icons appear in the footer of every page.

> **IMPORTANT:** Only when cloning the repo. If you're using the `gem`, modify those properties in your `_config.yml`.

#### `github_username`

Type: *string*

Set the GitHub username for the website.

```yaml
# social.yml
github_username: github_username
```

#### `facebook_username`

Type: *string*

Set the Facebook username for the website.

```yaml
# social.yml
facebook_username: facebook_username
```

#### `twitter_username`

Type: *string*

Set the Twitter username for the website.

```yaml
# social.yml
twitter_username: twitter_username
```

#### `instagram_username`

Type: *string*

Set the Instagram username for the website.

```yaml
# social.yml
instagram_username: instagram_username
```

#### `linkedin_username`

Type: *string*

Set the LinkedIn username for the website.

```yaml
# social.yml
linkedin_username: linkedin_username
```

#### `medium_username`

Type: *string*

Set the Medium username for the website.

```yaml
# social.yml
medium_username: medium_username
```

## Theme

The theme settings are in [`src/yml/theme.yml`](https://github.com/thiagorossener/jekflix-template/blob/master/src/yml/theme.yml). You just need to change this file and run `gulp build`.

> **IMPORTANT:** Only when cloning the repo. If you're using the `gem`, follow [these instructions](https://github.com/thiagorossener/jekflix-template#theme-colors).

### GitHub pages

It's a known issue that you can't run Gulp when deploying the website into GitHub pages. So, you must change the theme colors and run `gulp build` locally, then push the changes into your repo, there is no other way.

To see how your website is going to look like when you deploy it, run `bundle exec jekyll serve` and access `http://127.0.0.1:4000/`.

#### `themeColor`

Type: *hexadecimal*

Default: ![#ff0a16](https://placehold.it/15/ff0a16/000000?text=+) `#FF0A16`

Color used in links, icons and some custom elements.

```yaml
# theme.yml
themeColor: "#ff0a16"
```

#### `primaryDark`

Type: *hexadecimal*

Default: ![#141414](https://placehold.it/15/141414/000000?text=+) `#141414`

Color used in dark backgrounds and some texts.

```yaml
# theme.yml
primaryDark: "#141414"
```

#### `accentDark`

Type: *hexadecimal*

Default: ![#ffffff](https://placehold.it/15/ffffff/000000?text=+) `#FFFFFF`

Color used in light backgrounds and as contrast to dark backgrounds.

```yaml
# theme.yml
accentDark: "#ffffff"
```

#### `lightGray`

Type: *hexadecimal*

Default: ![#f2f2f2](https://placehold.it/15/f2f2f2/000000?text=+) `#F2F2F2`

Color used in borders, contrast to light backgrounds, some links and subtitles.

```yaml
# theme.yml
lightGray: "#f2f2f2"
```

#### `texts`

Type: *hexadecimal*

Default: ![#333333](https://placehold.it/15/333333/000000?text=+) `#333333`

Color used in texts overall.

```yaml
# theme.yml
texts: "#333333"
```

## Posts

The posts settings can be found in [`src/yml/posts.yml`](https://github.com/thiagorossener/jekflix-template/blob/master/src/yml/posts.yml).

> **IMPORTANT:** Only when cloning the repo. If you're using the `gem`, modify those properties in your `_config.yml`.

#### `show_time_bar`

Type: *boolean*

Show/hide the reading progress bar. It accepts the values `true` or `false`.

```yaml
# posts.yml
show_time_bar: true
```

![Reading Progress Bar Screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566425470/progress-bar-screenshot_gem7xb.jpg)

#### `show_modal_on_exit`

Type: *boolean*

Show/hide recommendation modal when visitor is leaving the page. It accepts the values `true` or `false`.

```yaml
# posts.yml
show_modal_on_exit: false
```

![Modal screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566478245/before-you-go-screenshot_prrplk.jpg)

#### `show_modal_on_finish_post`

Type: *boolean*

Show/hide recommendation modal when visitor reaches the end of the post. It accepts the values `true` or `false`.

```yaml
# posts.yml
show_modal_on_finish_post: false
```

![Modal screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566478245/before-you-go-screenshot_prrplk.jpg)

#### `two_columns_layout`

Type: *boolean*

Switch posts layout between one and two column. It accepts the values `true` or `false`.

Example with two columns:

```yaml
# posts.yml
two_columns_layout: true
```

![Post with two columns screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566476793/two-columns-screenshot_phumrl.jpg)

Example with one column:

```yaml
# posts.yml
two_columns_layout: false
```

![Post with one column screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566476792/one-column-screenshot_m1k0xt.jpg)

## Advanced

The advanced settings can be found in [`src/yml/advanced.yml`](https://github.com/thiagorossener/jekflix-template/blob/master/src/yml/advanced.yml).

> **IMPORTANT:** Only when cloning the repo. If you're using the `gem`, modify those properties in your `_config.yml`.

#### `baseurl`

Type: *string*

Set the subpath of your site, e.g. `/blog`.

```yaml
# advanced.yml
baseurl: ""
```

#### `url`

Type: *string*

Set the base hostname and protocol for your site, e.g. `https://rossener.com`

```yaml
# advanced.yml
url: ""
```

#### `google_analytics`

Type: *string*

Set your Google Analytics [tracking ID](https://www.youtube.com/watch?v=Mtzl4tkVdbI).

```yaml
# advanced.yml
google_analytics: "UA-XXXXXXXX-X"
```

#### `language`

Type: *string*

Set your website language. It's used for SEO purposes (e.g. `pt-BR`, `en`, `es`, `fr`)

```yaml
# advanced.yml
language: "en"
```