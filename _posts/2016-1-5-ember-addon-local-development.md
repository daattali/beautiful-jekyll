---
layout: post
title: Developing An Ember Addon Locally
published: true
subtitle: null
date: ""
---


## Introduction

These instructions will also work for developing npm packages locally.

You may want to develop your ember addon locally and test it in a project to see it actually working. You have two options :

- You can use the ember dummy application that is created when you first initialize the addon folder. So all you have to do is `ember serve` in your addon directory.

- You can test your addon locally in a separate project.

The rest of this tutorial will discuss the second approach.

## Setup

```sh
cd path/to/your/ember/addon

npm link
```

This will setup a global symbolic link so that **local** projects that are trying to install this addon will be directed to this folder.

Now we will need to tell your project to gain reference globally **linked** project which is your addon project. So do the following :

```sh
cd path/to/some/app/using/the/addon

npm link name-of-your-addon
```

Notice : `name-of-your-addon` corresponds the the name that is in in your `package.json`, specifically the `name` field.

## Teardown

Once you are done developing your new feature or whatever, you want to unlink your symbolic link. Just do the following :

```sh
cd path/to/your/ember/addon

npm unlink
```
