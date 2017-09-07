---
layout: page
title: General lab instructions
---

All submitted labs **MUST** do the following:

1. You should have a well organized lab repo/directory structure, where:
  - all code files (`.R`, `.py`, `.Rmd`, `.ipynb`) live in the src directory, except for the driver scripts (Shell script and Makefile which call your `analysis` scripts).
  - all rendered documents and visualizations you create live in the `results` directory
  - any data present goes in the `data` directory
  - answers to written questions should be in the `doc` directory

2. In the main `README.md` file in the lab/assignment repo, you must make it clear where all files are for all assignments, as well as explain anything the we need to know to understand your homework submission.

3. Your work must be reproducible from beginning to end. That means:
  - all data must be in the repo, or linked to and grabbed by your code (*e.g.,* `curl`, `wget`, `read_csv("<URL>")` etc)
  - all data cleaning/wrangling must be done programmatically (*i.e.,* in R, Python, etc) so that it is reproducible
  - you MUST list all dependencies (using a package or environment management strategy could make this easier in some cases... up to you!)

4. Make it easy for others to run your code:
  - At the beginning of each code source file, load any necessary packages, so your dependencies are obvious.
  - At the beginning of each code source file, import anything coming from an external file. This will make it easy for someone to see which data files are required, edit to reflect their locals paths if necessary, etc. There are situations where you might not keep data in the repo itself (*e.g.,* you are downloading data from a website).
  - Pretend you are someone else. Clone a fresh copy of your own repo from GitHub, read your instructions to re-run your code. Does it “just work”? It should!
