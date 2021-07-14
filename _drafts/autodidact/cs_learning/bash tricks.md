---
created: 2021-04-01T14:36:55+05:30
modified: 2021-04-01T18:08:15+05:30
tags: [tech]
---
[cs_learning]]
https://news.ycombinator.com/item?id=26650721

For fast iteration with pipes, using only basic unix tools, and arguably less risky to fat-fingering, I write it in a file, and use watch -n1. Easy to modify, temporarily comment parts of it, etc...

Also, I wrote this plog function (for pipe-log, or something):

    plog() {
      local msg=${1:-plog}
      tee >(sed -e "s/^/[$msg] /" | cat 1>&2 )
    } 

That allows me to see what's happening in the middle steps of the pipeline.

I ended up compiling a list of tricks like that in https://raimonster.com/scripting-field-guide/ , in case anyone is interested (and feedback is appreciated)

https://github.com/akavel/up
[[cs_learning]]
