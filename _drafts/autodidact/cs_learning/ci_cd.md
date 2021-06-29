---
created: 2021-04-01T18:06:24+05:30
modified: 2021-04-01T18:07:11+05:30
tags: [tech]
---
[[cs_learning]]
 CI and CD is automated builds and tests, when you merge something on the master, you run a tool that does every step necessary to deploy. For a website it might be doing installing vendors, installing assets, clearing caches, etc. Everything that you'd do by hand to update your application is done automatically

CI is more about automated tests and CD about releasing updates

At work we have tests, security checks and linters running when we commit to a branch and the build will fail if something doesn't pass. Then once your branch is good, you push it to the branch, launch a build on Jenkins,which fetches the source, builds everything, creates a new directory on the server and finally creates a symbolic link on the latest release (we keep 5 releases) 

TBH I'm not good at it and other people in the team are managing it, but you still have to understand how it works. 
