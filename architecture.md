---
layout: page
title: Architecture
use-site-title: true
gh-repo: mobydq/mobydq
gh-badge:
  - star
  - watch
  - fork
  - follow
---


# Architecture Diagram
![Architecture](/img/architecture.png)


---


# Database
The database `mobydq` uses [PostgreSQL 10.4](https://www.postgresql.org). It contains configuration data required to execute indicators and stores the result of their executions. The database runs into an independent Docker container named `mobydq-db`.


When running the project locally, it is accessible on `host: 0.0.0.0` and `port:5432`.


Note access to the database is restricted by default to avoid intrusions. In order to access it you must run it with the following command to open the container ports:
```
$ cd mobydq
$ docker-compose -f docker-compose.yml -f docker-compose.dev.yml up -d db
```


---


# GraphQL API
GraphQL is used as a thin layer on top of the database in order to facilitate CRUD operations. It is powered by the excellent [Postgraphile](https://www.graphile.org/postgraphile) which introspects the database schema to create queries and mutations. The GraphQL API runs into an independent Docker container named `mobydq-graphql`.


When running the project locally, the GraphiQL interactive documentation is accessible from [http://0.0.0.0:5433/graphiql](http://0.0.0.0:5433/graphiql).


Note access to GraphiQL is restricted by default to avoid intrusions. In order to access it you must run it with the following command to open the container ports:
```
$ cd mobydq
$ docker-compose -f docker-compose.yml -f docker-compose.dev.yml up -d graphql
```


---


# Flask API
The Flask API is built on top of GraphQL in order to centralize custom operations performed by the application. For instance to manage permissions, encryption, trigger the execution of indicators, etc. It is built using [Python 3.6.6](https://www.python.org) and is powered by [Flask](http://flask.pocoo.org) and [Flask-Restplus](https://flask-restplus.readthedocs.io).


The API runs into an independent Docker container named `mobydq-api`. When running the project locally, it is accessible on [http://0.0.0.0:5434/mobydq/api/doc](http://0.0.0.0:5434/mobydq/api/doc).


---


# Web Application
The web application provides a user-friendly interface to configure and monitor indicators. It is built using [React JS](https://reactjs.org/) and runs into an independent Docker container named `mobydq-app`.


When running the project locally, it is accessible on http://localhost.
