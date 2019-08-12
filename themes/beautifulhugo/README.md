# Beautiful Hugo - A port of Beautiful Jekyll Theme

![Beautiful Hugo Theme Screenshot](https://github.com/halogenica/beautifulhugo/blob/master/images/screenshot.png)

## Installation

    $ mkdir themes
    $ cd themes
    $ git submodule add https://github.com/halogenica/beautifulhugo.git beautifulhugo
    

See [the Hugo documentation](https://gohugo.io/themes/installing/) for more information.

## Extra Features

### Responsive

This theme is designed to look great on both large-screen and small-screen (mobile) devices.

### Syntax highlighting

This theme has support for either Hugo's lightning fast Chroma, or both server side and client side highlighting. See [the Hugo docs for more](https://gohugo.io/content-management/syntax-highlighting/).

#### Chroma - New server side syntax highlighting

To enable Chroma, add the following to your site parameters:

```
pygmentsCodeFences = true
pygmentsUseClasses = true
```

Then, you can generate a different style by running:

```
hugo gen chromastyles --style=trac > static/css/syntax.css
```

#### Pygments - Old server side syntax highlighting

To use this feature install Pygments (`pip install Pygments`) and add the following to your site parameters:

```
pygmentsStyle = "trac"
pygmentsUseClassic = true
```

Pygments is mostly compatable with the newer Chroma. It is slower but has some additional theme options. I recommend Chroma over Pygments. Pygments will use `syntax.css` for highlighting, unless you also set the config `pygmentsUseClasses = false` which will generate the style code directly in the HTML file. 

#### Highlight.js - Client side syntax highlighting
```
[Params]
    useHLJS = true
```

Client side highlighting does not require pygments to be installed. This will use `highlight.min.css` instead of `syntax.css` for highlighting (effectively disabling Chroma). Highlight.js has a wider range of support for languages and themes, and an alternative highlighting engine.

### Disqus support

To use this feature, uncomment and fill out the `disqusShortname` parameter in `config.toml`.

### Staticman support

Add *staticman* configuration section in `config.toml` or `config.yaml`

Sample `config.yaml` configuration

```
  staticman:
    api: https://api.staticman.net/v2/entry/<USERNAME>/<REPOSITORY-BLOGNAME>/master/comments
    pulls: https://github.com/<USERNAME>/<REPOSITORY-BLOGNAME>/pulls
    recaptcha:
      sitekey: "6LeGeTgUAAAAAAqVrfTwox1kJQFdWl-mLzKasV0v"
      secret: "hsGjWtWHR4HK4pT7cUsWTArJdZDxxE2pkdg/ArwCguqYQrhuubjj3RS9C5qa8xu4cx/Y9EwHwAMEeXPCZbLR9eW1K9LshissvNcYFfC/b8KKb4deH4V1+oqJEk/JcoK6jp6Rr2nZV4rjDP9M7nunC3WR5UGwMIYb8kKhur9pAic="
```

You must also configure the `staticman.yml` in you blog website.

```
comments:
  allowedFields: ["name", "email", "website", "comment"]
  branch            : "master"
  commitMessage     : "New comment in {options.slug}"
  path: "data/comments/{options.slug}"
  filename          : "comment-{@timestamp}"
  format            : "yaml"
  moderation        : true
  requiredFields    : ['name', 'email', 'comment']
  transforms:
    email           : md5
  generatedFields:
    date:
      type          : "date"
      options:
        format      : "iso8601"
  reCaptcha:
    enabled: true
    siteKey: "6LeGeTgUAAAAAAqVrfTwox1kJQFdWl-mLzKasV0v"
    secret: "hsGjWtWHR4HK4pT7cUsWTArJdZDxxE2pkdg/ArwCguqYQrhuubjj3RS9C5qa8xu4cx/Y9EwHwAMEeXPCZbLR9eW1K9LshissvNcYFfC/b8KKb4deH4V1+oqJEk/JcoK6jp6Rr2nZV4rjDP9M7nunC3WR5UGwMIYb8kKhur9pAic="
```



### Google Analytics

To add Google Analytics, simply sign up to [Google Analytics](https://www.google.com/analytics/) to obtain your Google Tracking ID, and add this tracking ID to the `googleAnalytics` parameter in `config.toml`.

### Commit SHA on the footer

If the source of your site is in a Git repo, the SHA corresponding to the commit the site is built from can be shown on the footer. To do so, two environment variables have to be set (`GIT_COMMIT_SHA` and `GIT_COMMIT_SHA_SHORT`) and parameter `commit` has to be defined in the config file:

```
[Params]
  commit = "https://github.com/<username>/<siterepo>/tree/"
```
  
This can be achieved by running the next command prior to calling Hugo:

```
  GIT_COMMIT_SHA=`git rev-parse --verify HEAD` GIT_COMMIT_SHA_SHORT=`git rev-parse --short HEAD`
```
  
See at [xor-gate/xor-gate.org](https://github.com/xor-gate/xor-gate.org) an example of how to add it to a continuous integration system.
 
### Extra shortcodes

There are two extra shortcodes provided (along with the customized figure shortcode):

#### Details

This simply adds the html5 detail attribute, supported on all *modern* browsers. Use it like this:

```
{{% details "This is the details title (click to expand)" %}}
This is the content (hidden until clicked).
{{% /details %}}
```

#### Split

This adds a two column side-by-side environment (will turn into 1 col for narrow devices):

```
{{< columns >}}
This is column 1.
{{< column >}}
This is column 2.
{{< endcolumn >}}
```

## About

This is a port of the Jekyll theme [Beautiful Jekyll](https://deanattali.com/beautiful-jekyll/) by [Dean Attali](https://deanattali.com/aboutme#contact). It supports most of the features of the original theme.

## License

MIT Licensed, see [LICENSE](https://github.com/halogenica/Hugo-BeautifulHugo/blob/master/LICENSE).
