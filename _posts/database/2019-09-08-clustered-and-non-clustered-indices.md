---
layout: post
title: Clustered and non-clustered indices
category: database
tags: [education, development]
---

With the clustered index the rows are stored physically on the disk in the same order as the index. Therefore, there can be only one clustered index.

With a non-clustered index, there is a second list that has pointers to the physical rows. You can have many non-clustered indices, although each new index will increase the time it takes to write new record.

It is generally faster to read from a clustered index if you want to get all the columns. Yu do not have to go first to the index and then to the table. Writing to a table with a clustered index can be slower, if there is a need to rearrange the data.