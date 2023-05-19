---
layout: post
title: Data Scientist Joining CI/CD party, Part 2
subtitle: From prototype to production - a data scientist's journey in CI/CD
thumbnail-img: /assets/img/2023-04-15-thumb.png
tags: [devops, github actions, CI/CD, software development, workflows, version control, automated testing]
comments: true
---
This blog post is the second in a series discussing the closely related notions of version control, dependency management, and continuous integration/continuous deployment practices. In the [first part](https://zhenev.github.io/2023-04-08-data-scientist-joining-ci-cd-party/), I walked the reader through the basics of version control and dependency management. In the current post, I show how a continuous integration / continuous delivery (CI/CD) pipeline can be set up using GitHub. I also guide the reader through a specific use case that involves automated failure of a pull request check triggered by the absence of a version update.

## Introduction

In the previous blog post, I discussed the benefits of introducing good software development practices in the data scientists' workflow. In brief, it makes the data scientist's professional life much easier and the whole team happier, ultimately contributing to the success of their project and creating value. I listed 10 easy-to-follow practices, that I picked up along the way, and introduced version control and dependency management. Additional topics, like employing unit tests are mentioned in my other posts (see, for [example](https://zhenev.github.io/2022-07-16-real-life-sensor-data-modeling/)). 

## Why Continuous Integration / Continuous Delivery?

One of the most efficient and easy-to-follow software development practices is using branches to protect the main codebase. Pushing the code to a separate branch and integrating it into the main branch by opening a pull request allows for imposing various checks on the new parts of code before the merge, both automatic (via the CI part of the pipeline) and manual (via code review). While lacking the code review when working alone, the automatic checks still are of great help. Additionally, the CD part of the pipeline ensures that the tested (and approved!) code changes are automatically deployed, allowing for a seamless and reliable delivery of new features and fixes to the end users. One example of this flow can be [publishing a library](https://zhenev.github.io/2022-10-15-label-filtering-in-github-workflows/).


## Setting Up CI[/CD] Pipeline

I will continue to build upon the GitHub repository, I created in the first part of this series. I have completed the following steps there:
1. Created a repository using the Web interface and a project folder within it.
2. Set up a basic dependency management framework by adding a `pyproject.toml` file to the folder.
3. Cloned the repository locally.
4. Set up the interpreter using `Poetry Environment`.
5. Applied dependencies by running poetry update for the specified project folder.

Now, we can add the newly created (or updated) `poetry.lock` file to Git and commit the changes. However, at this point, we stop and realize that we intended to prevent pushing into the `main` branch to ensure the security and stability of our codebase.

To prohibit pushing into the `main` branch, I go to the `Settings` menu for our repository and choose `Branches`. From here I proceed to `Add branch protection rule`:

![branches-1](/assets/data/2023-04-15-ci-pic-1.png){: .mx-auto.d-block :}

### Enabeling CI Tests

The first two checkboxes, `Require a pull request before merging` and `Require status checks to pass before merging`, represent two ways to protect a branch. If you are unsure whether you will have collaborators on the repository to provide a code review, the first option will prevent you from merging pull requests in general, as [you cannot be a reviewer of your own pull request](https://github.com/orgs/community/discussions/6292):

**If you enable required reviews, collaborators can only push changes to a protected branch via a pull request that is approved by the required number of reviewers with write permissions.** ([link](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches#require-pull-request-reviews-before-merging))

Thus, while usually it will be marked, we jump over the first option and continue to the second one, `Require status checks to pass before merging`:

**Required status checks ensure that all required CI tests are passing before collaborators can make changes to a protected branch.** ([link](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches#require-status-checks-before-merging))

![branches-2](/assets/data/2023-04-15-ci-pic-2.png){: .mx-auto.d-block :}

Here, after setting the `Branch name pattern` to `main`, we mark `Require branches to be up to date before merging` to allow pull requests to be tested with the latest code and to prohibit bypassing the settings for any roles by choosing the `Do not allow bypassing the above settings` option:

![branches-3](/assets/data/2023-04-15-ci-pic-3.png){: .mx-auto.d-block :}

![branches-4](/assets/data/2023-04-15-ci-pic-4.png){: .mx-auto.d-block :}

Thus, I enabled the CI tests to be run on top of the changes before merging them into the main branch; however, I have no status checks set up for my repository yet.


### Creating First Status Check

On GitHub, status checks refer to one type of workflows. A [workflow](https://docs.github.com/en/actions/learn-github-actions/understanding-github-actions#workflows) is an automated process that will run one or more jobs after being triggered by an event, manually, or at a defined schedule. In our case, we are interested in a workflow which will be triggered by an event, specifically by one particular type of events called opening a pull request. Workflows are defined by a YAML file checked in to the `.github/workflows` directory in the repository. Usually, repositories have multiple workflows, each of which performs a different set of tasks on different subsets of the code, while one workflow can be even referenced in another workflow. That is the [GitHub Actions CI/CD platform](https://docs.github.com/en/actions/learn-github-actions/understanding-github-actions) in a nutshell. It allows automating the build, test, and deployment pipeline.

Thus, to create a status check I add a corresponding config file to the repository, specifically under the `.githib/workflows` folder. It may take a few attempts, I succeeded on the third try:

![branches-5](/assets/data/2023-04-15-ci-pic-5.png){: .mx-auto.d-block :}

The full version of the code can be found [here](https://github.com/Zhenev/better-python-with-ci-cd/blob/main/.github/workflows/test-on-pr.yml).

The provided YAML code represents a GitHub Actions workflow that automates testing operations for a project named "fizz_buzz" within the "better-python-with-ci-cd" repository. The workflow is triggered on push events to the "main" branch and pull requests being opened or synchronized for the "main" branch.

The workflow consists of a single job named `test-fizz_buzz` that runs on an `ubuntu-latest` environment. It includes a matrix strategy that specifies the Python version `3.10.5` to be used for testing.

The steps within the job are as follows:

1. actions/checkout@v3: Checks out the repository's code.
2. tj-actions/changed-files@v34.3.0: Retrieves the list of changed files in the repository.
3. Check for changes: Determines if specific files or directories have been modified and sets environment variables accordingly.
4. Exit if version unchanged: Exits the workflow with an error (exit code 1) if the "fizz_buzz" directory has changed but the "pyproject.toml" file remains unchanged.
5. Set up Python ${{ matrix.python-version }}: Sets up the specified Python version for subsequent steps.
6. Install poetry: Installs the Poetry package manager if the "fizz_buzz" directory has changed.
7. Build fizz_buzz project: Installs dependencies for the "fizz_buzz" project using Poetry if the directory has changed.
8. Run lint on fizz_buzz: Runs the Flake8 linter on the "fizz_buzz" directory to check for code style violations if the directory has changed.
9. Test fizz_buzz with pytest: Runs pytest to execute tests located in the "fizz_buzz/tests" directory if the "fizz_buzz" directory has changed.

In this workflow, several steps are conditional (if: `env.PROJECT_CHANGED == 'true'`) and depend on whether changes have occurred in the `fizz_buzz` directory. These steps are skipped if no changes are detected, avoiding unnecessary operations and optimizing the workflow execution. One step, labeling the PR, was temporally disabled. We also remember that we do not have any real tests in the `fizz_buzz/tests` directory yet, since only initial test file set up was performed during the creation of the `fizz_buzz` project directory:

![branches-9](/assets/data/2023-04-15-ci-pic-9.png){: .mx-auto.d-block :}

Now, we are ready to set up a rule for our `main` branch.

### Activating a Status Check

I navigate to `Settings -> Branches` and access the `Branch protection rules` section. Here, I can observe the newly created `test-fizz_buzz (3.10.5)` status check listed under the `Require branches to be up to date before merging` checkbox.:

![branches-6](/assets/data/2023-04-15-ci-pic-6.png){: .mx-auto.d-block :}

### Protected Branch Update Failed

Now, let’s see if I can push our `poetry.lock` file to the main branch.


```python

Total 4 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas:   0% (0/1)        
remote: Resolving deltas: 100% (1/1)        
remote: Resolving deltas: 100% (1/1), completed with 1 local object.        
remote: error: GH006: Protected branch update failed for refs/heads/main.        
remote: error: Required status check "test-fizz_buzz (3.10.5)" is expected.        
error: failed to push some refs to 'https://github.com/Zhenev/better-python-with-ci-cd.git'
To https://github.com/Zhenev/better-python-with-ci-cd.git
!	refs/heads/main:refs/heads/main	[remote rejected] (protected branch hook declined)
Done

```

The commit is rejected since a status check needs to be run on a separate branch. Thus, I have no choice but to create a feature branch.


## Standing on CI Shoulders

In what follows, I will outline a specific use case for integrating changes that involves initially bypassing versioning and subsequently addressing it.

### Merging Changes by the Book

Let’s create a feature branch locally and then on the remote repository:

```bash
git checkout -b poetry-update
git push origin poetry-update
```

The first command, `git checkout -b poetry-update`, creates a new branch named `poetry-update` and switches to that branch. The `-b` flag indicates that a new branch is being created, and `poetry-update` is the name of the branch. By executing this command, I create a new branch and move to that branch to start making changes.

The second command, `git push origin poetry-update`, pushes the newly created `poetry-update` branch to the remote repository. The push command is used to send the local branch and its commits to the remote repository, making it accessible to everyone having access to it.

Now, a new branch called `poetry-update` is created on the remote repository: 

![branches-7](/assets/data/2023-04-15-ci-pic-7.png){: .mx-auto.d-block :}

When I switch to this branch, I see that it is `1 commit ahead` of the `main` branch:

![branches-8](/assets/data/2023-04-15-ci-pic-8.png){: .mx-auto.d-block :}

I also can proceed with pushing the changes to the `main` branch by creating a pull request:

![branches-10](/assets/data/2023-04-15-ci-pic-10.png){: .mx-auto.d-block :}

To demonstrate the process, I will continue by using the web browser and clicking on the `Compare & pull request` button. By default, pull requests are based on the default branch of the parent repository, which in our case is `main`.

![branches-11](/assets/data/2023-04-15-ci-pic-11.png){: .mx-auto.d-block :}

**When thinking about branches, remember that the base branch is where changes should be applied, the head branch contains what you would like to be applied.** ([link](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request#changing-the-branch-range-and-destination-repository))

Usually, you and your team will also use a naming convention for pull requests, so you will need to provide a proper title and perhaps add a short description:

![branches-12](/assets/data/2023-04-15-ci-pic-12.png){: .mx-auto.d-block :}

Now, I click `Create pull request`.... wait ...

![branches-13](/assets/data/2023-04-15-ci-pic-13.png){: .mx-auto.d-block :}

...and fail! :)


![branches-14](/assets/data/2023-04-15-ci-pic-14.png){: .mx-auto.d-block :}


### Investigating Errors

Our status check failed, so now I proceed to investigate the details:

![branches-15](/assets/data/2023-04-15-ci-pic-15.png){: .mx-auto.d-block :}

Here I see the annotation `Process completed with exit code 1.`. As we remember, the `test-fizz_buzz (3.10.5)` workflow includes checking that particular conditions are met:
1. There are changes in the code.
2. The version is updated.

Since we are adding a new piece of code, the only reason for getting the error should be bypassing the version update.

### Fixing Errors

What I need to do now, is to return to the `pyproject.toml` file on my local copy of the branch and raise the version. The moment I push this update to the remote origin, the `test-fizz_buzz (3.10.5)` workflow starts running again automatically:

![branches-16](/assets/data/2023-04-15-ci-pic-16.png){: .mx-auto.d-block :}

You can also see that now we have another commit recorded by Git.

When all checks are passed, we get the green light to merge the changes into the base branch:

![branches-17](/assets/data/2023-04-15-ci-pic-17.png){: .mx-auto.d-block :}

### Merging Approved Changes

**You can merge pull requests by retaining all the commits in a feature branch, squashing all commits into a single commit, or by rebasing individual commits from the head branch onto the base branch.** ([link](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/incorporating-changes-from-a-pull-request/about-pull-request-merges))

The `Squash and merge` approach is commonly employed to create a more streamlined Git history in a repository when it is not always necessary to retain all the small commits added in sequence in the Git history. It is important to exercise caution though, when utilizing this method and avoid continuing work on the same head branch after the current PR is merged. With `Squash and merge`, a commit on the base branch is generated that encompasses all the changes made on the head branch since the most recent commit present in both branches. This commit exists solely on the base branch and not the head branch; thus, the common ancestor of the two branches remains unaltered which can potentially lead to [merge conflicts](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/addressing-merge-conflicts/about-merge-conflicts) when additional PR is opened on the same head branch.

[Rebasing individual commits from the head branch onto the base](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/configuring-pull-request-merges/about-merge-methods-on-github#rebasing-and-merging-your-commits), when permitted by the repository owner, involves adding each commit from the head branch onto the base branch without a merge commit. This process also involves rewriting the commit history on the base branch with the inclusion of the new commits.

For this specific use case, we adopt a straightforward approach by merging the pull request and subsequently deleting the head branch:

![branches-18](/assets/data/2023-04-15-ci-pic-18.png){: .mx-auto.d-block :}

Now, what is left is to incorporate the latest updates into my local development environment. To this end, I fetch the changes locally and update the local copy of the `main` branch. To fetch the changes from the remote repository:
```bash
git fetch
```
To update the local copy of the main branch:
```bash
git checkout main
git pull
```
The first command, `git checkout main`, switches to the `main` branch. The second command, `git pull`, fetches the latest changes from the remote `main` branch and merges them into your local copy of the `main` branch.

## Conclusion

In this blog post, I continue to discuss some easy-to-follow good software development practices. This post is the second in a series discussing the closely related notions of version control, dependency management, and continuous integration/continuous deployment practices. It introduces the basics of setting up a CI/CD pipeline and demonstrates the power of automated checks. To this end, I establish the CI leg of the CI/CD pipeline using GitHub and provide guidance on a specific use case involving a pull request check failure due to a missing version update.
