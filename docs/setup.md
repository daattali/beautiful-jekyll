# Setup

## Environment

Before starting, make sure you have [Ruby](https://www.ruby-lang.org/en/documentation/installation/) and [NodeJS](https://nodejs.org/) installed.

Then install Jekyll:

```
$ gem install jekyll
```

And install Gulp client:

```
$ npm install gulp-cli -g
```

## Installing template

1. Fork the [Jekflix Template](https://github.com/thiagorossener/jekflix-template/fork)
2. Clone the repo you just forked:
```
$ git clone https://github.com/<your-github-username>/jekflix-template.git
```
3. Access the local project:
```
$ cd path/to/jekyll-template
```
4. Install npm packages:
```
$ npm install
```
5. Install Ruby dependencies:
```
$ bundle install
```
6. Build Jekyll:
```
$ bundle exec jekyll build
```
7. Then run Gulp:
```
$ gulp
```

## Running local

After the steps above, to run Jekyll locally, you'll just need to run Gulp:
```
$ gulp
```

## Customization

*Jekflix Template* allows you to personalize your site with several settings. See the [docs](settings.md#settings) for more details.

For advanced theme customization, check the directory `_sass` for style files.

## Translations

In order to translate texts throughout the theme, create a `translations.yml` file in `src/yml` and add the settings below.

> **Note:** If you're using the `gem`, just add it into your `_config.yml`.

```
translations:
  text:
    new_post: "New Post"
    see_also: "See also"
    search: "Search"
    author: "Author"
    share: "Share"
    comments: "Comments"
  button:
    read_now: "Read Now"
    share_on_twitter: "Share on Twitter"
    share_on_facebook: "Share on Facebook"
  pagination:
    page: "Page"
    of: "of"
    next_page: "Next Page"
    next_post: "Previous Page"
  recommendation:
    text: "Why don't you read something next?"
    back_btn: "Go back to top"
  error_404:
    title: "Page not found :("
    message: "I'm sorry. We couldn't find the page you are looking for."
    image_alt: "404 - Page not found"
  contact:
    title: "Talk to me"
    subject: "New contact!"
    submit_btn: "Send"
    placeholders:
      name: "Your name"
      email: "Your e-mail"
      message: "Your message"
    errors:
      locale: "en"
      empty_name: "Name is required"
      empty_email: "Email is required"
      invalid_email: "Email is invalid"
      empty_message: "Message is required"
    after_send:
      title: "Message sent!"
      message: "Thank you for sending me a message. I'm going to answer ASAP."
```