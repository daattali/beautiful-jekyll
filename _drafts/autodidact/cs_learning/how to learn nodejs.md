---
tags: [tech]
created: 2021-04-08T09:34:41+05:30
modified: 2021-04-08T09:34:42+05:30
---
[[cs_learning]]
you're starting out, and want to get into back-end, I'd recommend Go. Go is very hot right now, and I personally like some features that are baked in.
As for node.js, the syntax is ECMAScript only. It's almost similar to how it works in the browser, but your mental model is different when writing server side code. 

Express.js is the primary web framework, almost everyone uses it.
For database, you can try a query builder like knex.js and there's ORMs like Sequelize and TypeORM. But before this, you'd need to understand databases. I've worked with MySQL and PostgreSQL mainly, not much of an experience with NoSQL databases. For your API layers, you can check out GraphQL or a simple REST API using express. If it's super simple stuff, just make a JSON RPC. 

At this point, I realised I'm rambling. Just go through the official node.js guides are you're good to go