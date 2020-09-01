## Unreleased version

One of the major changes in this version is that a lot of time was spent on rethinking the entire SEO and social media sharing model (how a page looks on eg. Google, Twitter, Facebok). It was redesigned to be more simple and customizable. The new documentation has a section dedicated to SEO and social media sharing of a page. Unfortunately some changes had to be made that are not backwards-compatible.

- **BREAKING CHANGE** Renamed `description` YAML option to `share-description` to be more clear
- **BREAKING CHANGE** Renamed `description` config parameter to `rss-description` since it was only used in RSS (the FAQ in the README explains the difference between YAML options and config parameters if you're confused!)
- **BREAKING CHANGE** Removed YAML option `use-site-title` (you can now specify the exact title using `share-title`)
- **BREAKING CHANGE** Removed undocumented YAML options `meta-title` and `meta-description`
- **BREAKING CHANGE** Removed `link-tags` config parameter because it wasn't necessary. If you use tags, there will be a tags page created; if you don't use tags there is no tags page.
- **BREAKING CHANGE** The YAML setting `show-avatar` is now true by default. This has always been the case for GitHub Pages users, but not for `remote_theme` users. For consistency, it's now the default for everyone. (#715)
- Added `share-title` YAML option to give control over the search engine/social media title
- Added `before-content` and `after-content` YAML options that allow you to add some common HTML before the main content of a page (below the title) or after the main content (above the footer). Works in a similar way to `footer-extra`.
- Added `head-extra` YAML option which i s similar to `footer-extra` but is used to include custom HTML code in a page's `<head>` tag
- Added `full-width` YAML option to allow having full-width pages
- Added `feed_show_excerpt` config option to show/hide the post excerpts on the feed page
- Added `feed_show_tags` config option to show/hide the list of tags on post previews on the feed page
- When `nav-short` is turned on, the avatar will also be shorter
- Fixed rendering issues with `nav-short` option that caused the body of the page to start too low
- Improved the `footer-extra` YAML option to support multiple files instead of only a single file
- Upgraded kramdown to version 2.3.0 to fix security issues
- Upgraded jQuery to version 3.5.1 to fix a couple security vulnerabilities with the previous version
- Added automatic navbar color detection (#702)
- Changed navbar and footer background colour to be slightly darker, for better contrast with the default white page background
- Changed the behaviour of `site-css` to include site-wide CSS file **before** page-specific files 
- Renamed internal css/js files from "main" to "beautifuljekyll" to make it easier for users to troubleshoot
- Added alt text to all images for better accessibility
- Fixed some CSS styles that broke during the bootstrap 4 migration (#716)

## v4.1.0 (2020-08-08)

- Added Open Graph `site_name` meta field to pages automatically
- Added `text-col `config setting for main text color (#694)
- Added `keywords` config setting to set the meta keywords on all pages (for SEO purposes) (#691)
- Added `mobile-theme-col` config setting to allow a mobile theme colour (#692)
- Added `site-css` config setting in the config file to provide CSS files that are used on all pages in the site (#695)
- Added YAML option `description`: creates the meta description on a page, intended to provide a brief description of the page for search engines and when the page is shared (#690)

## v4.0.1 (2020-07-13)

- Fixed staticman comments UI that was broken since the migration to bootstrap 4

## v4.0.0 (2020-07-12)

- **BREAKING CHANGE** Replace `image` YAML parameter with `thumbnail-img` to be more clear
- **MAJOR BEHAVIOUR CHANGE** Don't use the thumbnail as the avatar image
- Cover image will automatically be used as thumbnail if none is provided
- Image to share on social media will use the cover image or thumbnail if none is provided
- All images (social media share, thumbnail, cover) can use either relative or absoluate paths.
- Fixed issue where if a dropdown menu was the last item in the menu bar, it did not have a proper margin on the right
- Added social network links: Mastodon (#646), Google Scholar, ORCID (#670)
- Added support for sharing pages on new social network: VK (#657)
- Use Open Graph type 'article' for blog posts (#669)
- Use Twitter's large sumary card (large image) when there is a cover image, thumbnail image, or share image specified (#668)
- Made post images in the feed page smaller on smaller devices
- Fixed jQuery version in staticman (#671)

## v3.0.0 (2020-05-07)

- **BREAKING CHANGE** Upgraded from Bootstrap 3.3.2 to 4.4.1. This involved a major rewrite of most components. This shouldn't affect any users unless you have custom HTML/CSS code which the new Bootstrap could have broken.
- **BREAKING CHANGE** Renamed `bigimg` YAML parameter to `cover-img`
- **BREAKING CHANGE** Removed `googlefonts` YAML parameter since googlefonts are just CSS so they can be loaded via `ext-css`
- **BREAKING CHANGE** Upgraded from jQuery 1.11.2 to 3.4.2. This should not affect most people
- Added `navbar-border-col` setting in the config file
- Added accessibility features where possible
- Made the theme completely responsive by rewriting all CSS to use 'rem' instead of 'px'
- Rewrote and simplified some JavaScript code to use CSS or Bootstrap alternatives that weren't available in 2015
- Removed most of the sample posts so that users only have two sample posts to learn from
- Improvements to the README instructions

## v2.3.0 (2020-04-29)

- Added YAML option `footer-extra` for including custom content in the footer
- Fixed issue: linking to a specific part of a page resulted in scrolling too far (#69)
- Added YAML option `nav-short` to have navbar permanently collapsed
- Added social network link: Calendly
- Fixed bug where RSS link in footer was showing even when turned off

## v2.2.0 (2020-04-27)

- Added social network link: Telegram (#625) (thanks @mashed-potatoes)
- Moved the demo site to an independent URL: https://beautifuljekyll.com
- Major documentation overhaul and cleanup of old files
- Fixed a few bugs from the remote_theme migration

## v2.0.0 (2020-04-26)

- Beautiful-Jekyll v2.0.0 available as an official Ruby gem
- Beautifull-Jekyll now supports the `remote_theme` config (#339) (thanks @gpotter2 and @skalee)
- Consolidated the demo site, the ruby gem, and the master branch into one
- Added a `home` layout and used it in the index page
- Added readtime support for the post header (#622) (thanks @MutMatt and @rubyreads)
- Removed the dependency on `_data` folder since it doesn't get copied when using `remote_theme` (#614)
- Added support for configuring lang attribute on `html` tag (#608) (thanks @skalee)
- Added ability to disable round logo (thanks @gpotter2)
- Added support for Utterances comments (#596) (thanks @colynn)
- Removed 'just-comments' as it's getting killed at the end of the year
- Upgraded font-awesome to 5.12.1 (#587) (thanks @cketti)

## Prior to 2020

**2018-12-24** Add support for Staticman comments (#440) (thanks @VincentTam)

**2018-10-19** Move Google Analytics to the head (#419) (thanks @jpvicari)

**2018-06-08** Add support for Facebook comments (#350) (thanks @npes87184)

**2018-02-22** Automatically generate sitemap (#323) (thanks @JosemyDuarte)

**2018-01-18** Add clickable tags to each post and a tags index page, works for GitHub sites (#307) (thanks @OCram85)

**2018-01-14** Redo Dockerfile (#302) (thanks @jennydaman)

**2018-01-06** More color personalization options (#297 and #299) (thanks @jennydaman)

**2018-01-05** Abstract the social networks logic (thanks @OCram85)

**2018-01-03** Avatar image no longer causes a ghost click (thanks @alefi87)

**2017-10-16** Add GitHub buttons to posts (#265) (thanks @yonicd)

**2017-09-04** Ability to change colour/image of navbar/footer/body

**2017-08-17** Add support for notification, error, and warning boxes in markdown (#227) (thanks @OCram85)

**2017-08-12** Add social buttons for twitch, yelp, and steam (#234) (thanks @TheRealBenForce)

**2017-03-30** Make the footer contact links friendly for screen readers (thanks @eugenius1)

**2017-03-30** Started a CHANGELOG file (thanks @eugenius1)

**2017-01-28** Add Subresource Integrity (SRI) support (#164) (thanks @tony-ho)

**2017-01-09** Add Google Tag Manager Integration (#157) (thanks @csarigoz)

**2017-01-06** Add options to configure HTML document title (#154) (thanks @tony-ho)

**2016-12-25** Allow dynamic images on each blog post (#143) (thanks @bbritten)

**2016-12-15** Support `title-img` config param to have image in the navbar instead of text

**2016-12-08** Add support for phone numbers in footer; fix #136

**2016-12-06** Update gemfile (#134) (thanks @stephentuso)

**2016-10-09** Add Docker deployment (#114) (thanks @mangar)

**2016-08-06** Add social share buttons for posts (thanks @rtlee9)

**2016-07-29** Add CSS styling to code chunks

**2016-07-27** Add clickable tags that lead to a tag page (doesn't work for GitHub hosted sites) (thanks @epwalsh)

**2016-07-21** Add support for twitter cards (sharing on Twitter will be better); fixes #70

**2016-03-18** Support full-width images in page headers; fixes #37

**2016-03-18** Support menus in navigation bar

**2016-02-07** Avatar is now conditional (thanks @hristoyankov)

**2016-02-02** Migrate (forced to...) to jekyll 3

**2016-01-22** Make sure not to include JQuery twice, fixes #29

**2015-11-19** Support external links in navigation bar; fixes #3

... Many small changes because the site was in its infancy

**2015-03-12** Beautiful Jekyll version 0.0000001 is released!

