---
layout: post
title: Database buzzwords and their meaning
subtitle: A guideline of the database types and their use cases
gh-repo: shafi-/shafi
gh-badge: [star, fork, follow]
tags: [database, architecture, engineering, oltp, olap, columnar db]
comments: true
author: Md Abdullahil Shafi
---

## What are OLTP and OLAP
### OLTP
OLTP - *on-line transaction processing*.
OLTP databases are designed to perform queries and other operations on a database server without affecting other users. OLTP databases can be used for online transactions.

### OLAP
OLAP - *on-line analytical processing*.
OLAP databases are designed to perform queries and other operations on a database server while affecting other users. OLAP databases can be used for online analytical processing.

## When to use OLTP and OLAP
### OLTP
If you need to perform transactional queries on your database, your choice is OLTP.

### Example
When processing an order from your customer, you need to perform transactions on your database - create order, payment, notification etc. Here if some of the step fails, you need to rollback. Thus either commit or rollback. It is a transaction.

Another example, transfering money from one account to another. It is a transaction.

### OLAP
If you need to perform analytical queries on your database, your choice is OLAP.

### Example
For example, you are collecting user clicks on your website. If some of the clicks are failed to be saved in database, you don't need to rollback others. And while performing analytical queries, those missing clicks won't impact much. Here OLAP is the right choice.

## Row-based and Column-based databases
### What's the difference
Row-based - when data is accessed by row for update or select
Column-based - when data is accessed to get analytics based on some criteria or column

### Purpose of these
 
## Reference
https://www.youtube.com/watch?v=b5E-8YkutJY

## ClickHouse
- Stores data per column
- can apply different strategy based on data type of that column
- can apply different compression algo for each column
