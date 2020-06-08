---
title: Data Science Setup (Mac OS)
---

One of the funnest (and most frustrating) parts of data science is the vast array of tools available to us. It can be overwhelming where to start. Every now and then I like to complety wipe my computer clean, and then reinstall everything from scratch. This helps clean up my computer, and make sure everything is running smoothly.

This is a living document that captures my most up to date set up. My set up is inspired by the University of British Columbia Data Science Program which provides two helpful setup guides:

- [macOS](https://ubc-mds.github.io/resources_pages/install_ds_stack_mac/)
- [Windows](https://ubc-mds.github.io/resources_pages/install_ds_stack_windows/)
- [Ubuntu](https://ubc-mds.github.io/resources_pages/install_ds_stack_ubuntu/)


## Python

I choose to use the python distirbution [Miniconda](https://docs.conda.io/en/latest/miniconda.html) from [Anaconda](https://www.anaconda.com/). Follow the [official instructions](https://docs.conda.io/en/latest/miniconda.html) to install.

I use miniconda as opposed to Anaconda because it is a stripped down version of Anaconda comes with a lot of software that I do not play to use such as [Spyder](https://www.spyder-ide.org/) and [Orange](https://orange.biolab.si/).

After I have miniconda installed I then work on setting up my python environment. I like to leave the root environment as is, and create a new environment call `ds_base` (data science base). I then load in my favourite data science libraries.

```bash
conda ds_base create -f environment_ds_base.yml
```

<script src="https://gist.github.com/SamEdwardes/ae9fd4582d5fe213c5e2c43b68a78e12.js"></script>

Note that I never use `pip install` in the `ds_base`. If there is a package that I can not install through conda I will clone `ds_base` and then install the desired package. I do this to avoid breaking the installation of `ds_base`. [Conda recommends](https://docs.conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html?highlight=pip#using-pip-in-an-environment):

- Use `pip` only after `conda`.
- Care should be taken to avoid running `pip` in the root environment.