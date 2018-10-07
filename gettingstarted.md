---
layout: page
title: Getting Started
use-site-title: true
---

# Requirements

## Install Docker
This tool has been fully containerized with Docker to ensure easy deployment and portability. To add the Docker repository to your Linux machine, execute the following commands in a terminal window.
```shell
$ sudo apt-get update
$ sudo apt-get install apt-transport-https ca-certificates curl software-properties-common
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
$ sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
```

Install Docker Community Edition.
```shell
$ sudo apt-get update
$ sudo apt-get install docker-ce
```


Add your user to the docker group to setup its permissions. **Make sure to restart your machine after executing this command.**
```shell
$ sudo usermod -a -G docker <username>
```




## Install Docker Compose
Execute the following command in a terminal window.
```shell
$ sudo apt install docker-compose
```


---




# Setup Your Instance


## Create Configuration Files
Based on the template below, create a text file named `.env` at the root of the project. This file is used by Docker Compose to load configuration parameters into environment variables. This is typically used to manage file paths, logins, passwords, etc. Make sure to update the `postgres` user password for both `POSTGRES_PASSWORD` and `DATABASE_URL` parameters.
```ini
# DB
POSTGRES_USER=postgres
POSTGRES_PASSWORD=password

# GRAPHQL
DATABASE_URL=postgres://postgres:password@db:5432/mobydq

# SCRIPTS
GRAPHQL_URL=http://graphql:5433/graphql
MAIL_HOST=smtp.server.org
MAIL_PORT=25
MAIL_SENDER=change@me.com

# APP PARAMS
NODE_ENV=development
REACT_APP_FLASK_API_URL=http://localhost:5434/mobydq/api/v1/graphql
```




## Create Docker Network
This custom network is used to connect the different containers between each others. It is used in particular to connect the ephemeral containers ran when executing batches of indicators.
```shell
$ docker network create mobydq-network
```




## Create Docker Volume
Due to Docker compatibility issues on Windows machines, we recommend to manually create a Docker volume instead of directly mounting external folders in `docker-compose.yml`. This volume will be used to persist the data stored in the PostgreSQL database. Execute the following command.
```shell
$ docker volume create mobydq-db-volume
```




## Build Docker Images
Go to the project root and execute the following command in your terminal window.
```shell
$ cd mobydq
$ docker-compose build --no-cache
```




## Run Docker Containers
To start all the Docker containers as deamons, go to the project root and execute the following command in your terminal window.
```shell
$ cd mobydq
$ docker-compose up -d db graphql api app
```

Individual components can be accessed at the following addresses:
* Web application: `http://localhost`
* Flask API Swagger Documentation: `http://localhost:5434/mobydq/api/doc`
* GraphiQL Documentation: `http://localhost:5433/graphiql`
* PostgreSQL database `host: localhost, port: 5432`

Note access to GraphiQL and the PostgreSQL database is restricted by default to avoid intrusions. In order to access these addresses directly, you must run them with the following command to open their ports:
```shell
$ cd mobydq
$ docker-compose -f docker-compose.yml -f docker-compose.dev.yml up -d db graphql
```
