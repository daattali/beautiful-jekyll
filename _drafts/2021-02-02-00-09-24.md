---
created: 2021-02-02T00:09:24+05:30
modified: 2021-02-02T00:12:36+05:30
tags: [tech]
---

# don't use mongodb??

Once we started doing ugly MongoDB joins manually in the Diaspora code, we knew it was the first sign of trouble. It was a sign that our data was actually relational, that there was value to that structure, and that we were going against the basic concept of a document data store.

Whether you’re duplicating critical data (ugh), or using references and doing joins in your application code (double ugh), when you have links between documents, you’ve outgrown MongoDB.

Schema flexibility sounds like a great idea, but the only time it’s actually useful is when the structure of your data has no value. If you have an implicit schema — meaning, if there are things you are expecting in that JSON — then MongoDB is the wrong choice. I suggest taking a look at PostgreSQL’s hstore
