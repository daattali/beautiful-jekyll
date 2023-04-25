# Post

## Creating a post

You can use the `initpost.sh` script to generate new posts when you clone the repo (the script isn't available in the `gem`).

To do so, in your project directory, just run:

```
./initpost.sh -c "Your Post Title"
```

The new file will be created in `_posts` with the format `YYYY-MM-DD-your-post-title.md`.

## Front Matter properties

If you don't know what these are, check the Jekyll [documentation](https://jekyllrb.com/docs/front-matter/).

A *Jekflix* post file looks like:

```yaml
# _posts/2010-01-01-welcome-to-the-desert-of-the-real.md
---
date: 2019-05-16 23:48:05
layout: post
title: Welcome to the desert of the real
subtitle: Lorem ipsum dolor sit amet, consectetur adipisicing elit.
description: >-
  Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
  tempor incididunt ut labore et dolore magna aliqua.
image: https://res.cloudinary.com/dm7h7e8xj/image/upload/v1559821647/theme6_qeeojf.jpg
optimized_image: https://res.cloudinary.com/dm7h7e8xj/image/upload/c_scale,w_380/v1559821647/theme6_qeeojf.jpg
category: blog
tags:
  - welcome
  - blog
author: thiagorossener
paginate: true
---

bla bla bla
```

Below is a full list of the template Front Matter properties explained:

#### `date`

Type: *datetime*

The post publishing date. Format: `YYYY-MM-DD hh:mm:ss`

Example:

```yaml
# _posts/2019-08-22-example.md
---
...
date: 2019-05-16 23:48:05
...
---
```

#### `layout`

Type: *string*

The layout file that will be used. The template has only one valid layout for posts, which is `post`.

```yaml
# _posts/2019-08-22-example.md
---
...
layout: post
...
---
```

#### `title`

Type: *string*

The post title.

Example:

```yaml
# _posts/2019-08-22-example.md
---
...
title: Welcome to the desert of the real
...
---
```

#### `subtitle`

*(Optional)*

Type: *string*

The post subtitle. It appears below the title.

Example:

```yaml
# _posts/2019-08-22-example.md
---
...
subtitle: Lorem ipsum dolor sit amet, consectetur adipisicing elit.
...
---
```

#### `description`

Type: *string*

The post description. It's used in the home and category pages, in meta description tag for SEO purposes and for social media sharing.

Example:

```yaml
# _posts/2019-08-22-example.md
---
...
description: >-
  Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
  tempor incididunt ut labore et dolore magna aliqua.
...
---
```

#### `image`

Type: *url*

The featured image. It's used in the home and category pages and for social media sharing.

**Tip:** Use a media server to provide images for your website, like [Cloudinary](https://cloudinary.com)

*Obs: The recommended image resolution is 760x399*

Example:

```yaml
# _posts/2019-08-22-example.md
---
...
image: https://res.cloudinary.com/dm7h7e8xj/image/upload/v1559821647/theme6_qeeojf.jpg
...
---
```

#### `optimized_image`

*(Optional*)

Type: *url*

The optimized featured image. Set a smaller image to appear in the home and category pages, they will load faster.

In case there is no `optimized_image` set, the pages show the one in the `image` property.

*Obs: The recommended image resolution is 380x200*

Example:

```yaml
# _posts/2019-08-22-example.md
---
...
optimized_image: https://res.cloudinary.com/dm7h7e8xj/image/upload/c_scale,w_380/v1559821647/theme6_qeeojf.jpg
...
---
```

#### `category`

Type: *string*

Only one category is allowed. Make sure to create a `<category>.md` file in `category` directory if it's a new one.

Example:

```yaml
# _posts/2019-08-22-example.md
---
...
category: blog
...
---
```

#### `tags`

Type: *list*

A list of the post keywords. It's used in the home, category and tags pages, and as meta keywords for SEO purposes.

Example:

```yaml
# _posts/2019-08-22-example.md
---
...
tags:
  - welcome
  - blog
...
---
```

#### `author`

*(Optional)*

Type: *string*

The post author. Set the author filename used in the `_authors` folder.

Every time you create a new author, make sure to create a file in there too.

Leave it blank if there is no author.

Example:

```yaml
# _posts/2019-08-22-example.md
---
...
author: thiagorossener
...
---
```

#### `paginate`

*(Optional)*

Type: *boolean*

To break your post into pages, set the property `paginate` to `true` and use the divider `--page-break--` where you want to break it.

**Note:** The template uses the `jekyll-paginate-content`, which is [not supported for GitHub Pages](https://pages.github.com/versions/). If you need that feature, please deploy somewhere else like Netlify.

Example:

```yaml
# 2019-08-20-ten-skills-you-need-to-have-to-become-a-good-developer.md
---
...
paginate: true
...
---

Skill 1

--page-break--

Skill 2
```

It would look like:

![Paginated Page Screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566430021/paginated-page-screenshot_zx4xjn.jpg)