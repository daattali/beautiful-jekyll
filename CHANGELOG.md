## Unreleased version
- BREAKING CHANGE: Allow changing the order of the social network links that appear in the footer (#1152)
- BREAKING CHANGE: `google-scholar` social network link no longer requires the prefix `citations?user=`; if you previously set this parameter, it needs to be updated (#1189)
- Added explicit support for favicons, you only need to add a `favicon.ico` file to the root directory
- The footer of a page always sticks to the bottom, even on short pages (#576)
- Added `author` YAML parameter to allow specifying the author(s) of a post (#1220)
- Fixed bug where hovering over search results showed the text "{desc}" (#1156)
- Added social network links for GitLab, Bluesky (#1168, #1218)
- Added instructions and example on how to fix image links in project sites (#1171)
- Pagination buttons: use nicer arrows, and don't show text on small screens (#1221)

## v6.0.1 (2023-06-08)

This version has been in the works for a few years. It includes several new features that were highly requested, numerous bug fixes, new documentation, and aggresively encourages migrating from the old Google Universal Analytics to the new Analytics 4.

#### Breaking changes

- As of July 2023, Google Universal Analytics is going away and being replaced by Google Analytics 4. Beautiful Jekyll sites that still use the old analytics tag will show a warning to encourage them to move to Analytics 4 (#1096).
- More control over RSS feed sharing: previously, an RSS feed was *always* generated, and if the config setting `rss-description` was set then there was an RSS icon in the footer. Now, an RSS feed is only generated when the config setting `rss-description` exists, and an RSS footer icon is only shown if `rss: true` is set in the `social-network-links` config settings.

#### New parameters and settings

- Added `navbar-var-length` config setting that allows the navigation menu to be the same length as the longest sub-menu, so that long words in the submenu are not cut off (#765) 
- Added `post_search` config setting that creates a Search button in the navbar (#770)
- Added `edit_page_button` config setting that adds a "Edit page" button to the footer (to edit the current page on GitHub) (#1004)
- Added `footer-hover-col` config setting to customize the hover colour of links in the footer (#848)

#### New features and improvements

- Made the home page feed more accessible for screen readers (#950)
- Added support for giscus comments (#886) and CommentBox (#960)
- Added support for Cloudflare Analytics (#797)
- Added Reddit in share options of posts (#815)

#### Bug fixes

- Fixed page titles, subtitles, and excerpts rendering correctly when there are special characeters in them (#856) 
- Fixed bug where navbar secondary level dropdown items didn't inherit the same colour as the primary navbar links
- Fixed bug where the navbar "burger" collapsed button didn't always revert back to a light colour
- Fixed bug where using an image as a navbar title did not render in GitHub Project pages that did not have a custom domain
- Fixed bug where image thumbnails on the feed page were always forced into a square rather than maintaining a proper image aspect ratio
- Fixed bug where special characters in the title led to broken share tags (#744)
- Fixed bug where staticman didn't work jQuery slim version is used (#766)
- Fixed very long strings to wrap around the next line rather than go off-screen (#787)

#### Small changes

- Updated staticman from using v2 (public servers) to v3 (private servers) due to the public servers becoming obsolete (#775)
- Added social network links for Patreon, Medium, Itch.io, Discord, Kaggle, Hackerrank (#783, #788, #907, #961, #978)
- Slightly reworked margins and position for avatar image to resolve an alignment issue on Safari
- Changed the width at which the navbar collapses to a higher threshold because most modern non-mobile browsers are >1000px


## v5.0.0 (2020-09-15)

One of the major changes in this version is that a lot of time was spent on rethinking the entire SEO and social media sharing model (how a page looks on eg. Google, Twitter, Facebok). It was redesigned to be more simple and customizable. The new documentation has a section dedicated to SEO and social media sharing of a page. Unfortunately some changes that are not backwards-compatible had to be made.

#### Breaking changes

- Renamed `description` YAML parameter to `share-description` to be more clear
- Renamed `description` config setting to `rss-description` since it was only used in RSS (the FAQ explains the difference between YAML parameters and config settings if you're confused)
- Removed YAML parameter `use-site-title` (you can now specify the exact title using `share-title`)
- Removed undocumented YAML parameters `meta-title` and `meta-description`
- Removed `link-tags` config setting because it wasn't necessary. If you use tags, there will now always be a tags page created; if you don't use tags there won't be a tags page.
- The YAML parameter `show-avatar` is now true by default. This has always been the case for GitHub Pages users, but not for `remote_theme` users. For consistency, it's now the default for everyone. (#715)

#### New parameters and settings

- Added `full-width` YAML parameter to allow having full-width pages
- Added `feed_show_excerpt` config setting to show/hide the post excerpts on the feed page
- Added `feed_show_tags` config setting to show/hide the list of tags on post previews on the feed page
- Added `share-title` YAML parameter to give control over the search engine/social media title
- Added `last-updated` YAML parameter to show a "Last Updated on" date for blog posts
- Added `before-content` and `after-content` YAML parameters that allow you to add some common HTML before the main content of a page (below the title) or after the main content (above the footer). Works in a similar way to `footer-extra`.
- Added `head-extra` YAML parameter which is similar to `footer-extra` but is used to include custom HTML code in a page's `<head>` tag
- Added `site-js` config setting to provide JavaScript files that are used on all pages in the site

#### New features and improvements

- Improved the `footer-extra` YAML parameter to support multiple files instead of only a single file
- Added automatic navbar color detection (#702)
- When `nav-short` is turned on, the avatar will also be shorter
- Changed navbar and footer background colour to be slightly darker, for better contrast with the default white page background for accessibility reasons
- Changed the behaviour of `site-css` to include site-wide CSS file **before** instead of after page-specific files
- Renamed internal css/js files from "main" to "beautifuljekyll" to make it easier for users to troubleshoot
- Added alt text to all images for better accessibility
- Made thumbnail images square instead of circles, as users reported that circles cut off important parts of images

#### Bug fixes

- Fixed rendering issues with `nav-short` parameter that caused the body of the page to start too low
- Fixed some CSS styles that broke during the bootstrap 4 migration (#716)

#### Library upgrades

- Upgraded kramdown to version 2.3.0 to fix security issues
- Upgraded jQuery to version 3.5.1 to fix a couple security vulnerabilities with the previous version

## v4.1.0 (2020-08-08)

- Added Open Graph `site_name` meta field to pages automatically
- Added `text-col` config setting  for main text color (#694)
- Added `keywords` config setting to set the meta keywords on all pages (for SEO purposes) (#691)
- Added `mobile-theme-col` config setting to allow a mobile theme colour (#692)
- Added `site-css` config setting in the config file to provide CSS files that are used on all pages in the site (#695)
- Added YAML parameter `description`: creates the meta description on a page, intended to provide a brief description of the page for search engines and when the page is shared (#690)

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

- Added YAML parameter `footer-extra` for including custom content in the footer
- Fixed issue: linking to a specific part of a page resulted in scrolling too far (#69)
- Added YAML parameter `nav-short` to have navbar permanently collapsed
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

