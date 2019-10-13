---
layout : post
title : Flask, AWS and MySQL
---

## Introduction

The growth of easy to spin up servers and databases has made my research life much easier...most of the time. I still find myself spending inordinate amounts of times on relatively trivial problems. This is one such case. Recently, I have been creating web portals using Flask for data entry. Before using Flask, the process would be this. I have a trove of documents I need entered, I drop the documents and an excel sheet into a dropbox folder and share it with different individuals entering the data. These people would put the data in the excel and send it back to me. Now if you've ever experienced the joy of someone telling you they're all done and then looking at some shared folder and nothing's there, you can understand my pain. The basic problem with this data entry model is two fold. First, it relies on not only the other person saving their work, but also syncing their work to some shared drive. Second, this process of saving and syncing usually means it is very hard for me to QA their work in real time. Enter Flask, you can build a simple web portal to allow users to enter the data and the data gets saved to some database in the backend in real time. The key point of this framework is separating where the data lives from where the data is being entered.

This post today is going to walk through how to set up a flask application and connect it to MySQL database on AWS. The purpose of this post is not to build the website, this would be tedious and there are other great tutorials for building the [website](https://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-i-hello-world). Instead, this post is about getting AWS MySQL to play nice with your Flask application. I am writing this post as both a reminder to myself of how to do this process, as well as, a guide for others in the future.

## Flask Application

I am going to create a barebones Flask application called "flask_backed_with_aws". The folder structure for the application is as follows:

```shell
flask_backend_with_aws/
|
|-flask_backend_with_aws.py
|-config.py
|-env
|--app/
|--|
   |-__init__.py
   |-models.py
```
   

We can see from this that we have only 4 scripts (and one environmental file), which I can describe in words:

* `flask_backend_with_aws.py` : Launches your flask application, this is what you will set the `FLASK_APP` variable to.
* `config.py` : Configures parameters for flask application, specifically the locaion of your database.
* `.env` : Holds environmental variables called by config.py
* `__init__.py` : Runs when you launch your flask application. This will create the function called "create_app", which will initialize our database and migration repo.
* `models.py` : Creates your database schema. Only one table is created in this file called `testDB`.

Let's quickly walk through how to create this application in a python virtual environment. In order to step through this code, python must be callable from your command line and you must have the venv package. You need to create a directory for your project and then launch the virtual environment from within that directory:

```shell
# ~ Make directory and launch virtual environment ~ #
mkdir flask_backend_with_aws
python3 venv venv

# ~ Launch virtual environment (on Windows) ~ #
venv\Scripts\activate
```

The two files that are most important for the application structure are `config.py` and `__init__.py`. We will first focus on `__init__.py`. We will be using SQLAlchemy and Migrate, both from flask specific modules. The nice thing about these two modules is they allow us to easily create databases from within our flask application, but also any changes we make to our database in our scripts can be easily pushed to whereever our database lives. 

```python

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# File Name: __init__.py  
# 
# Initializes database objects and creates method to launch
#  flask application
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate

# ~ Databases ~ #
db = SQLAlchemy()   #<-Initialize database object
migrate = Migrate() #<-Initialize migration object

def create_app():
    """Construct core application"""
    application = Flask(__name__)

    # Pull from config file
    application.config.from_object('config.Config')

    # Initailize database
    db.init_app(application)          #<- This will get called in our models.py file
    migrate.init_app(application, db) #<- Migration directory
    
    # If this was a real flask app, you'd probably
    # add some routes to pages here

    return(application)

# ~ Import database schemas ~ # 
from app import models
```

We can see in the code above that we are pulling some configurations from 'config.Config' this is a nice method in flask that allows us to specify configurations in a separate file that flask knows to find. The specific configurations we care about here are going to be the Universal Resource Identifier (URI), or address, of our database. The nice thing about flask is we can specify separate addresses for our testing database and for our production database. Below I have my `config.py`, the only special thing I am doing here is using the **dotenv** package to load environmental variables from my `.env` file. 

```python

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# File Name: config.py  
# 
# Sets sqlalchemy uri variable to value specified in .env
#  file
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

import os
from dotenv import load_dotenv

# Absolute directory path
basedir = os.path.abspath(os.path.dirname(__file__))

# Looks for and loads .env file
# Can access env variables using os.environ.get(<VARNAME>)
load_dotenv(os.path.join(basedir, '.env'))

# ~ Create config object ~ #
class Config(object):
    # ~~ Migration Repository ~~ #
    SQLALCHEMY_MIGRATE_REPO = os.path.join(basedir, 'db_repository')
    SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL')
    SQLALCHEMY_TRACK_MODIFICATIONS = False
    
 ```   

The `.env` file configuration is below. Our local repository is using sqlite, as it's a bit annoying to setup a MySQL server locally on your computer.  

```python
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
# File: .env
# 
# Environmental file to hold environmental variables
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #

DATABASE_URL="sqlite:///path/to/temp.db"

```

We only need to create one more script, which is the script to create the tables that we want for this database. This exercise is not about SQL, so the tables I am going to make is relatively simple. Notice how to create a testDB, we extend the db.Model class, this is another nice feature of flask. It already has a pre-build table class, and each table simply extends these classes.

```python

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# File Name: models.py  
# 
# Creates sql tables for use by flask
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# ~ App specific modules ~ #
from app import db

# ~ Datetime Module ~ #
from datetime import datetime

class testDB(db.Model):
    """testDB extends db.Model class, or creates a database from 
        db.Model class


       Columns
         string_column  : column with strings
         integer_column : column with integers
         date_column    : column with dates, default is current date

    """

    # ~~ String Column ~~ #
    #
    # This is the primary key of the database
    # It is of type = string with max characters = 140
    string_column = db.Column(db.String(140),primary_key=True)

    # ~~ Integer Column ~~ #
    integer_column = db.Column(db.Integer)

    # ~~ Date Column ~~ #
    date_column = db.Column(db.DateTime, default=datetime.utcnow)
    
```

We finally make a script to launch our application:

```python

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# File Name: flask_backend_with_aws.py  
# 
# Script to call from command line to launch application
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

from app import create_app 

# ~~~ Create application ~~~ #
application = create_app()
```

To launch our application, in the command line, you have to set the `FLASK_APP` variable to the file that launces our application and then call flask run.

```shell

# ~ Set flask application location ~ #
set FLASK_APP=flask_backend_with_aws

# ~ Launch flask ~ #
flask run
```

Your flask application should now be running. To create your database, and then migrate any changes to the database, you have to run three commands. These commands are similar to gits commands for staging, committing and pushing changes to a repository:

* flask db init : creates a python script for making all the changes to the database in models.py
* flask db migrate : creates a migration script
* flask db upgrade : executes the migration script to upgrade database schema

You can see these three calls in action:

```shell

# ~ Initialize database changes ~ #
flask db init

# ~ Migrate database changes ~ #
flask db migrate -m "testDB table"

# ~ Upgrade database changes ~ #
flask db upgrade
```

## Adding Data to Database

We have successfully created a database locally available on your computer that we can access using any program that can talk to your local sqlite database. I have an example script below to add, then delete, then add, then read in data to a pandas dataframe. 

```python
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
# Example script to add data and extract
#  data from testDB table
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #

import sqlite3

# ~ Local URI ~ #
local_uri="/path/to/temp.db"

# ~ Connect to database ~ #
conn=sqlite3.connect(local_uri)
c=conn.cursor()

# ~~~ Add data ~~~ #
def insert_row_to_tbl(cursor,table_name,column_names,data_to_add,data_types):
    # Form query
    query = ''' INSERT INTO ''' + table_name + '(' + ','.join(column_names) + ') ' + \
                'VALUES(' + ','.join(data_types) + ')' 
    # Execute query
    cursor.execute(query,data_to_add)

# ~ Data to add ~ #
colNames=['string_column','integer_column','date_column']
data_to_enter=[('test1',1,'01-01-1989 10:00:00'),
               ('test2',2,'01-01-1989 10:10:00')]

# ~ Add data ~ #
for row in data_to_enter:
    insert_row_to_tbl(c,'testDB',colNames,row,['?','?','?'])

# ~~~ Select data from sql table ~~~ #
c.execute('SELECT * FROM testDB')

```

## Bringing in AWS

The last section was about simply creating our database. The nice thing about the section is once we have our MySQL database on AWS *correctly* set up, then all we will have to do is change the 'URI' in the environment file and we are basically all done. It turns out that while AWS is amazing, there a few gotcha's that you should know when setting up your database. As I stated previously, I will be setting up a MySQL database. Given that I'm a student and not rolling in dough, I'm going to use AWS' free tier for this exercise. The entire process I have in a series of screenshots available on my github. However, I can summarize the exact process you need to do. 

You first need to log in to your AWS console, and navigate to Amazon's Relational Database System Service (RDS for short). You will create the database. T

### During Database Creation

To create your database, you need to make sure you do these two things:

* Create an "Initial Database Name" - this is different than the "DB Instance Identifier"
* Make your database public - this is in the "Connectivity" tab.
* Create a Master Password 

I set the following for my setup:

* Master Username = admin <-this is the default
* Master Password = flaskexample
* DB Instance Identifier = flaskexampledatabase2
* Initial Database Name = testFlask


Both of these actions can not be undone once you have created your database. If you fail to do these two things, you will have to recreate your database.

### After Database Creation

#### Set Security Groups

Once your database is created, you need to change your security group settings to allow your machine (or server) to talk with the database on AWS. This simply means changing both the `inbound` and `outbound` rules to include either your IP (AWS has an option for that), or all IP traffic. 

### Setting the URI variable in Flask Python Code

Once you have created your database and properly change the security group settings, all you have to do is set the right location for your database. To set your uri variable it will be in the following form:

mysql+pymysql://MasterUsername:MasterPassword@URL/databaseName

Some things to note about the above, the MasterUsername may not be the Username you use to login into AWS. Often, the MasterUsername='admin'. The next thing to know is the MasterPassword is either the randomly generated one created during Create Database, or one you set while creating the database.

```python
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
# File: .env
# 
# Environmental file to hold environmental variables
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #

DATABASE_URL='mysql+pymysql://admin:flaskexample@flaskexampledatabase2.cj0bkf46sdda.us-east-2.rds.amazonaws.com/testFlask'
```

Once these things are all setup, you can now run flask db init, migrate and update again. Note, you will have to also change the location of the flask migration directory. Now this database lives on AWS! To access it, I can use a similar MySQL script from above.

### Connecting and Interacting with Data on AWS

Here is a short script using `pymysql` to interact with the AWS database. As you can see from above, we use all the information from our `DATABASE_URL` variable with the addition of the port number. Once these things are all setup, you can now run flask db init, migrate and upgrade again. Now this database lives on AWS! To access it, I can use a similar MySQL script from above. This new script uses `pymysql` a python library to interact with MySQL databases.

```python
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
# Connect + Add Data to Table on AWS
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #

import pymysql
import pandas as pd

# ~ Connect to Database ~ #
host = 'flaskexampledatabase2.cj0bkf46sdda.us-east-2.rds.amazonaws.com'
dbname = 'testFlask'
user = 'admin'
password='flaskexample'
port=3306
conn = pymysql.connect(host, user=user, port=port, passwd=password,db=dbname)
c = conn.cursor()

# ~ Data to add ~ #
colNames=['string_column','integer_column','date_column']
data_to_enter=[('test1',1,'01-01-1989 10:00:00'),
               ('test2',2,'01-01-1989 10:10:00')]

# ~ Add data ~ #
for row in data_to_enter:
    insert_row_to_tbl(c,'testDB',colNames,row,['?','?','?'])

# ~~~ Select data from sql table ~~~ #
c.execute('SELECT * FROM testDB')
```

## Conclusion

This framework of separating your application from its database is not novel, as this is how most modern architecture for web apps live. Having said that, learning how to do this for an individual and bespoke process was a bit hard for someone with very little web dev experience. Hopefully, this will provide a blueprint for those trying a similar approach in the future.
