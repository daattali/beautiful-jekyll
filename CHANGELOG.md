## v3.0.0

Date: TBD

- **BREAKING CHANGE** Upgraded from Bootstrap 3.3.2 to 4.4.1. This involved a major rewrite of most components. This shouldn't affect any users unless you have custom HTML/CSS code which the new Bootstrap could have broken.
- **BREAKING CHANGE** Renamed `bigimg` YAML parameter to `cover-img`.
- **BREAKING CHANGE** Removed `googlefonts` YAML parameter since googlefonts are just CSS so they can be loaded via `ext-css`. 
- **BREAKING CHANGE** Upgraded from jQuery 1.11.2 to 3.4.2. This should not affect most people.
- Added `navbar-border-col` setting in the config file.
- Made the theme completely responsive by rewriting all CSS to use 'rem' instead of 'px.
- Rewrite and simplify some JavaScript code to use CSS or Bootstrap alternatives that weren't available in 2015.
- Improvements to the README instructions.

## v2.3.0 

2020-04-29

- Add YAML option `footer-extra` for including custom content in the footer
- Fix issue: linking to a specific part of a page resulted in scrolling too far (#69)
- Add YAML option `nav-short` to have navbar permanently collapsed
- Add social network link: Calendly
- Fix bug where RSS link in footer was showing even when turned off

## v2.2.0

2020-04-27

- Add social network link: Telegram (#625) (thanks @mashed-potatoes) 
- Moved the demo site to an independent URL: https://beautifuljekyll.com 
- Major documentation overhaul and cleanup of old files 
- Fix a few bugs from the remote_theme migration

## v2.0.0

2020-04-26

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
