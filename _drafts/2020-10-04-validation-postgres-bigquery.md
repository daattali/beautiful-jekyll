---
layout: post
title:  "A Guide to Validation Postgres Data and BigQuery Data"
---

In today's world of handling massive amounts of data, it is essential to validate data between various data storage platforms to ensure that all changes made in one storage application are correctly reflected in the other. In this blog post, we delve into how we at GoCardless validated data between Postgres Data and Google's BigQuery.

# Architecture

Initially, one might intuitively query the rows based on the `updated at` column. However, this is not a reliable approach as we cannot assume that all tables have an `updated at,` and sometimes changes could be made to a row without necessarily updating it. Additionally, if a row is deleted from Postgres data, it will not be visible in a query based on the `updated at` column. Therefore, this blog post will explore two solutions to validate data between Postgres data and BigQuery datasets that are more reliable: Logical Replication and MVCC Xmin based selection.

Logical Replication

Logical replication works by streaming the changes made in Postgres data into another database instance using the logical replication mechanism that comes with new Postgres versions. This mechanism allows additional information to be added to the transaction or look up table. As indicated, a primary advantage of this approach is that as the data streams directly, it should itself be valid as a copy. It allows validation and scaling moderately well as we remove data that is no longer needed. Also, it captures all kinds of changes, including deletions. The disadvantage of this solution is that logical replication can only be used in Stolon clusters as CloudSQL does not yet support logical replication mechanism.

MVCC Xmin Based Selection

Multiversion concurrency control (MVCC) is the mechanism used by Postgres Data to maintain various versions of a row as new transactions run against it. Postgres Data attaches an Xmin value to each row, which identifies the transaction that initially inserted the row. Therefore, each new transaction creates a new row version with a new Xmin. As such, we can query Postgres Data to find which changes occurred since a specific point in time based on the Xmin and timestamp column. However, there is a limitation to using Xmin values: they are stored as unsigned 32-bit integers, meaning they wrap around back to zero after some four billion transactions. When a transaction reaches the `distance` from the current transaction ID, Postgres Data marks them as a frozen transaction, and its Xmin is not compared with the current transaction ID. Thus, we can use the Xmin value to validate Postgres data against BigQuery datasets with some caveats.

Calculating the Row Closest to Target Time

Finally, to validate Postgres data against BigQuery datasets, we need to calculate the row closest to the target time. This process could be complicated by the large size and lack of indexes on some tables. The solution to this problem is to select the IDs from the pg_stats histogram information. With this approach, we can obtain the minimum and maximum bounds of a particular timestamp. Getting more clever and utilizing the LAG() function, we can obtain both boundaries of the timestamp more efficiently. This leads to the successful validation of Postgres data against BigQuery datasets.

Conclusion

Validation of data between Postgres Data and BigQuery datasets is necessary because data can fail to be accurately reflected, leading to malfunctions in data storage and management. An optimal way to carry out this validation is either through utilizing logical replication or MVCC Xmin-based selection. Despite the limitations of using Xmin values, calculating the closest row to the target time provides reliable data validation."
