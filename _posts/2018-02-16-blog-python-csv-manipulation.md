---
layout: post
title: CSV Manipulation (Dict, List to/from CSV)
show-avatar: true
tags:
  - blogs
  - python
  - CSV
  - Dict
  - List
published: true
---


## Dict, List to/from CSV



* [Read CSV file as Dictionary in Python](#csv2dict)
* [Write CSV from Dictionary in Python](#dict2csv)
* [Read CSV file as Lists in Python](#csv2list)
* [Write CSV from List in Python](#list2csv)


Here is a CSV File Example:

|Row|Name|Age|Country|
| ---|--- | ---|-------- |
|1|John|20|Australia|
|2|Peter|20|USA|
|3|Simon|25|China|
|4|Alex|21|Germany|


### Read CSV file as Dictionary in Python <a id="csv2dict"></a>
Define correct path of the csv file in `csv_file` variable.

``` python
import csv
import os

def ReadCSVasDict(csv_file):
    try:
        with open(csv_file) as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                print row['Row'], row['Name'], row['Country']
    except IOError as err:
            print("I/O error({0})".format(err))    
    return

currentPath = os.getcwd()
csv_file = currentPath + "/csv/Names.csv"

ReadCSVasDict(csv_file)
```
----

### Write CSV from Dictionary in Python <a id="dict2csv"></a>
Define correct path of the csv file in csv_file variable, CSV column names and dict data.

``` python
import csv
import os

def WriteDictToCSV(csv_file,csv_columns,dict_data):
    try:
        with open(csv_file, 'w') as csvfile:
            writer = csv.DictWriter(csvfile, fieldnames=csv_columns)
            writer.writeheader()
            for data in dict_data:
                writer.writerow(data)
    except IOError as err:
            print("I/O error({0})".format(err)    
    return            

csv_columns = ['Row','Name', 'Age', 'Country']
dict_data = [
    {'Row': 1, 'Name': 'John', 'Age': 20, 'Country': 'Australia'},
    {'Row': 2, 'Name': 'Peter', 'Age': 20, 'Country': 'USA'},
    {'Row': 3, 'Name': 'Simon', 'Age': 25, 'Country': 'China'},
    {'Row': 4, 'Name': 'Alex', 'Age': 21, 'Country': 'Germany'},
    ]

currentPath = os.getcwd()
csv_file = currentPath + "/csv/Names.csv"

WriteDictToCSV(csv_file,csv_columns,dict_data)
```
----

### Read CSV file as Lists in Python <a id="csv2list"></a>
Define correct path of the csv file in `csv_file` variable. We may perform some additional operations like append additional data to list, removing csv headings(1st row) by doing a pop operation on the list like below.

``` python
import csv
import os

def ReadCSVasList(csv_file):
    try:
        with open(csv_file) as csvfile:
            reader = csv.reader(csvfile, dialect='excel', quoting=csv.QUOTE_NONNUMERIC)
            datalist = []
            datalist = list(reader)
            return datalist
    except IOError as err:
            print("I/O error({0})".format(err))    
    return        


currentPath = os.getcwd()
csv_file = currentPath + "/csv/Names.csv"

csv_data_list = ReadCSVasList(csv_file)
print(csv_data_list)

# To Ignore 1st Row (Headers)          
csv_data_list.pop(0)
print(csv_data_list)

# append to list
csv_data_list.append(['5', 'Jim', 18, 'USA'])

print(csv_data_list)
```
----

### Write CSV from List in Python <a id="list2csv"></a>

Define correct path of the csv file in `csv_file` variable, CSV column names and list data.
``` python
import csv
import os

def WriteListToCSV(csv_file,csv_columns,data_list):
    try:
        with open(csv_file, 'w') as csvfile:
            writer = csv.writer(csvfile, dialect='excel', lineterminator = '\n', 
                                quoting=csv.QUOTE_NONNUMERIC)
            writer.writerow(csv_columns)
            for data in data_list:
                writer.writerow(data)
    except IOError as err:
            print("I/O error({0})".format(err))    
    return              

csv_columns = ['Row','Name', 'Age', 'Country']
csv_data_list = [
    [1, 'John', 20, 'Australia'],
    [2, 'Peter', 20, 'USA'],
    [3, 'Simon', 25, 'China'],
    [4, 'Alex', 21, 'Germany']
    ]
    
currentPath = os.getcwd()
csv_file = currentPath + "/csv/Names.csv"

WriteListToCSV(csv_file,csv_columns,csv_data_list)
```
----

