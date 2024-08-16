---
layout: post
title: Sample blog post to learn markdown tips
subtitle: There's lots to learn!
gh-repo: daattali/beautiful-jekyll
gh-badge: [star, fork, follow]
tags: [test]
comments: true
mathjax: true
author: Bill Smith
---


For macOS users, rbenv is a popular and lightweight Ruby version manager. This guide will walk you through the process of installing rbenv, using it to install Ruby, and setting up a global Ruby version.

## Prerequisites

Ensure you have Homebrew installed. If not, install it by running:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## Step 1: Install rbenv

1. Install rbenv using Homebrew:

```bash
brew install rbenv
```

2. Set up rbenv in your shell:

```bash
rbenv init
```

3. Add rbenv to your ~/.zshrc file to load it automatically:

```bash
echo 'eval "$(rbenv init - zsh)"' >> ~/.zshrc
```

4. Restart your terminal or run:

```bash
source ~/.zshrc
```

5. Verify that rbenv is properly installed:

```bash
curl -fsSL https://github.com/rbenv/rbenv-installer/raw/main/bin/rbenv-doctor | bash
```

## Step 2: Install Ruby

Install the latest stable version of Ruby:

```bash
rbenv install $(rbenv install -l | grep -v - | tail -1)
```

## Step 3: Set Ruby Version Globally

Set the global Ruby version:

```bash
rbenv global $(rbenv install -l | grep -v - | tail -1)
```

## Step 4: Verify Installation

To make sure everything is set up correctly, run:

```bash
ruby -v
```

This command should output the Ruby version you just installed.

## Bonus: Installing colorls

Now that Ruby is installed, you can install colorls:

1. Install the colorls gem:

```bash
gem install colorls
```

2. Add colorls tab completion to your ~/.zshrc file:

{% highlight bash linenos %}
echo 'source $(dirname $(gem which colorls))/tab_complete.sh' >> ~/.zshrc
source ~/.zshrc
{% endhighlight %}

## Conclusion

You've now successfully installed rbenv, used it to install the latest version of Ruby, and set a global Ruby version. This setup allows you to easily manage different Ruby versions for different projects on your macOS system.
