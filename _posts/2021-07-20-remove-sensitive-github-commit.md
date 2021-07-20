---
layout: post
published: true
title: Keep your secrets out of your source code 
date: '2021-07-20'
subtitle: Protect your secrets and clean up if you accidentally over share  
---

## Problem
We accidentally committed our secrets (password or secret key) to GitHub

## Solution
1. Prevent secrets from being committed: [avoid accidental commits](https://docs.github.com/en/github/authenticating-to-github/keeping-your-account-and-data-secure/removing-sensitive-data-from-a-repository#avoiding-accidental-commits-in-the-future)
2. Clean up: Either use [BFG](https://stuarteggerton.com/2021-07-20-remove-sensitive-github-commit/) or see other methods to [remove sensitive data using](https://docs.github.com/en/github/authenticating-to-github/keeping-your-account-and-data-secure/removing-sensitive-data-from-a-repository)

