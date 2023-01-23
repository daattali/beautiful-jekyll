---
layout: post
title: Implementing Label Filtering in a GitHub Workflow
subtitle: Python package automated publishing example
tags: [devops, github actions, package publishing, filtering]
comments: true
---

When building workflows while runnig multiple projects in one repository, it is crucial to filter PRs based on specific labels, given that each PR can receive labels of different projects. The documentation did not cover our case specifically; thus, it took some trial and error to figure out the proper syntax. 

This is our implementation of the filter itself:

```yaml
contains(github.event.pull_request.labels.*.name, 'your_project_name')
```

And below is that filter within a workflow which publishes a Python package to PYPI:

```yaml
name: Upload your_project_name package

on:
  pull_request:
    types: [closed]
    branches: [ "main" ]

permissions:
  contents: read

jobs:
  deploy:
    runs-on: ubuntu-latest

    if: contains(github.event.pull_request.labels.*.name, 'your_project_name') &&
    github.event.pull_request.merged == true
    
    steps:
    - uses: actions/checkout@v3
    - name: Set up Python
      uses: actions/setup-python@v3
      with:
        python-version: '3.x'
    - name: Install dependencies
      run: |
        python -m pip install --upgrade pip
        pip install build
    - name: Build your_project_name package
      working-directory: ./your_project_name
      run: |
        pip install poetry
        poetry build -f wheel
    - name: Publish your_project_name package
      uses: pypa/gh-action-pypi-publish@release/v1
      with:
        user: __token__
        password: YOUR_PYPI_API_TOKEN_FOR_YOUR_PROJECT
        packages_dir: ./your_project_name/dist
```
Note: `YOUR_PYPI_API_TOKEN_FOR_YOUR_PROJECT` should be replaced with the actual expression used to access a secret stored in GitHub Actions.

Copyright © 2021 Zheniya Mogilevski
