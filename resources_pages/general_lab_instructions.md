---
layout: page
title: General lab instructions
---

### Student repositories

For every lab, we will create a repository (repo) for each student. For example,
if your CWL is `goatcabin` then for DSCI 521 lab 1 there will be a repository called
`DSCI_521_lab1_goatcabin`. To see a list of all repositories that you have access to,
navigate to the homepage of your year's organization; for example, for the 2021-22 cohort,
go to <https://github.ubc.ca/mds-2021-22>.

NOTE: please do not confuse your personal lab-specific repository with the general course
repository, which will be named something like `DSCI_521_platforms-dsci_students`. That
repo is public to all students and is where you can access lectures, due dates, readings, etc.

### How to submit

We anticipate that you will clone your lab-specific repository and do your work from
within there. To submit your labs you must **both** push your work to <https://github.ubc.ca/> 
**and** submit to Gradescope. It is your responsibility to make sure
your lab is submitted to both places and failure to do so will result in a deduction of mechanics marks.

You can submit (to both places) as many times as you want before the deadline; only the final version will be graded.

### Your submission on GitHub

#### Commits

For your lab submission to GitHub, you are expected to commit regularly, **not** just once when you are done.
You are required to make at least 3 commits per lab, and expected to make many more than that in practice.
You will lose mechanics marks from your lab if you fail to meet this minimum requirement. 

#### Repo structure

You should have a well organized lab repo/directory structure, where your files are organized in a sane directory structure. In cases where your lab repo is already organized into a directory structure (this is most cases), you can assume that structure is acceptable and you don't need to change it. 

#### Reproducibility

Your work must be reproducible from beginning to end. This requirement will become more relevant in the later parts of the program as you progress to more advanced analyses. A reproducible lab submission means:

  - For Jupyter notebooks, you must restart the kernel and run all cells in order before submitting.
    Notebooks with cell execution numbers out of order or not starting from "1" will have submission marks deducted.
  - All data must be in the repo, or linked to and grabbed by your code (*e.g.,* `curl`, `wget`, `read_csv("<URL>")` etc) unless you are specifically instructed in the lab to not push your data to the repo.
  - All data cleaning/wrangling must be done programmatically (*i.e.,* in R, Python, etc) so that it is reproducible.

#### Make it easy for others to run your code

  - At the beginning of each code source file, load any necessary packages, so your dependencies are obvious.
  - At the beginning of each code source file, import anything coming from an external file. This will make it easy for someone to see which data files are required, edit to reflect their locals paths if necessary, etc. There are situations where you might not keep data in the repo itself (*e.g.,* you are downloading data from a website).
  - Pretend you are someone else. Clone a fresh copy of your own repo from GitHub, read your instructions to re-run your code. Does it "just work"? It should!

### Deadline

The lab deadlines are given on the course repo and/or MDS calendar.  The default deadline for labs is
Saturday at 6pm, but there may be some exceptions. For the policy on late submissions, see the
[MDS policies page](https://ubc-mds.github.io/policies/).

### Grades

You will receive your lab grades through Gradescope.

### Privacy notes

* Your lab repos are visible to yourself, your TAs, all the core MDS staff, and some github.ubc.ca system administrators.

* Although only the final version will be graded, _all_ of your commits will be viewable, so don't commit something
private (like your email password) to your lab repo. Committing something and then removing it
with another commit doesn't remove it from the git history! It is theoretically possible to pull all traces of
something out of the git history, but it's not fun and uses more advanced git features.

* <https://github.ubc.ca>, <https://gradescope.ca> and <https://canvas.ubc.ca/> are run on Canadian servers, so all your data will be kept within Canada.
