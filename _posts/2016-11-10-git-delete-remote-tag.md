---
layout: post
title: How to delete a remote Git tag
published: true
subtitle: null
date: "2016-11-09"
---

This is how you delete a remote git tag. Always be weary of deleting things on your git server if you work on the project with a team. Others may be using the tag, so ask them first!

If your tag name is 'hello-tag' do this:

```
git tag -d hello-tag
git push origin :refs/tags/hello-tag
```

That will remove 'hello-tag' from your remote repository.

Happy tagging!
