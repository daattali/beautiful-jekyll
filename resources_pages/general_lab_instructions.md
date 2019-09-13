---
layout: page
title: General lab instructions
---

All submitted labs **MUST** do the following:

1. You should have a well organized lab repo/directory structure, where your files are organized in a sane directory structure, e.g., data in a `data` directory, results in a `results` directory, etc. In cases where your lab repo is already organized into a directory structure, you can assume that structure is acceptable unless notified otherwise. 


    If the lab contains any autograded content (this would be a Jupyter notebook with "autograde" rubrics in it), please _do not rename the main lab file or move it into a subdirectory_ as this causes problems for the autograding scripts.

2. In the main `README.md` file in the lab/assignment repo, you must make it clear where all files are for all assignments, as well as explain anything that we need to know to understand your submission. Your README must also include a clickable link to your main report. Please link to the most readable rendered version of your report; in other words, the version you want the grader to look at if viewing everything through the web browser. This may be an .ipynb, .md, .Rmd, .pdf, etc. depending on the situation. For example, if there are lots of LaTeX equations then .pdf will look better than .Rmd in the browser.

    Note: before the deadline, we recommend that you review your submission from within GitHub in a web browser. It occasionally happens that parts of one's work, such as LaTeX equations, look fine in Jupyter but become corrupted when rendered in GitHub. In these situations there is usually a quick fix; you can/should seek help from the course staff if you need help resolving such issues. It is important that your submission renders faithfully in GitHub because that is typically how the grader will be viewing it.

3. Your work must be reproducible from beginning to end. That means:
  - all data must be in the repo, or linked to and grabbed by your code (*e.g.,* `curl`, `wget`, `read_csv("<URL>")` etc)
  - all data cleaning/wrangling must be done programmatically (*i.e.,* in R, Python, etc) so that it is reproducible
  - all dependencies are listed (using a package or environment management strategy could make this easier in some cases... up to you!)

4. Make it easy for others to run your code:
  - At the beginning of each code source file, load any necessary packages, so your dependencies are obvious.
  - At the beginning of each code source file, import anything coming from an external file. This will make it easy for someone to see which data files are required, edit to reflect their locals paths if necessary, etc. There are situations where you might not keep data in the repo itself (*e.g.,* you are downloading data from a website).
  - Pretend you are someone else. Clone a fresh copy of your own repo from GitHub, read your instructions to re-run your code. Does it “just work”? It should!
 
