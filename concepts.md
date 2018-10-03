---
layout: page
title: Concepts
use-site-title: true
---

# Data Model
![Data Model](/img/data_model.png)

# Indicator
Indicators compute data sets on one or several data sources in order to evaluate the quality of their data. 

**Table:** `indicator`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the indicator, used as a primary key.</td>
  </tr>
  <tr>
    <td>name</td><td>Text</td><td>Name of the indicator, must be unique.</td>
  </tr>
  <tr>
    <td>description</td><td>Text</td><td>Description of the indicator.</td>
  </tr>
  <tr>
    <td>execution_order</td><td>Integer</td><td>Numeric value to indicate in which order the indicator should be executed within a batch.</td>
  </tr>
  <tr>
    <td>flag_active</td><td>Boolean</td><td>Boolean value to indicate if the indicator is active or inactive. Inactive indicators are not computed when a batch is executed. Default value is False.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>updated_date</td><td>Timestamp</td><td>Record last updated date.</td>
  </tr>
  <tr>
    <td>indicator_type_id</td><td>Integer</td><td>Foreign key of the indicator_type table, to indicate which type is the indicator.</td>
  </tr>
  <tr>
    <td>indicator_group_id</td><td>Integer</td><td>Foreign key of the indicator_group table, to indicate to which group belongs the indicator.</td>
  </tr>
</table>

# Indicator Group
Indicator groups define collections of indicators to be computed in the same batch.

**Table:** `indicator_group` <br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the group, used as a primary key.</td>
  </tr>
  <tr>
    <td>name</td><td>Text</td><td>Name of the group, must be unique.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>updated_date</td><td>Timestamp</td><td>Record last updated date.</td>
  </tr>
</table>

# Indicator Type
Indicator types determine which class and method is used to compute indicators. Supported types of indicators are:
* [Completeness](https://#)
* [Freshness](https://#)
* [Latency](https://#)
* [Validity](https://#)

**Table:** `indicator_type`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the type of indicator, used as a primary key.</td>
  </tr>
  <tr>
    <td>name</td><td>Text</td><td>Type of indicator, must be unique.</td>
  </tr>
  <tr>
    <td>module</td><td>Text</td><td>Python module (file) used to compute this indicator type.</td>
  </tr>
  <tr>
    <td>class</td><td>Text</td><td>Python class used to compute this indicator type.</td>
  </tr>
  <tr>
    <td>method</td><td>Text</td><td>Python method used to compute this indicator type.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>updated_date</td><td>Timestamp</td><td>Record last updated date.</td>
  </tr>
</table>

## List of values
<table>
  <tr>
    <th>id</th><th>name</th><th>module</th><th>class</th><th>method</th>
  </tr>
  <tr>
    <td>1</td><td>Completeness</td><td>completeness</td><td>Completeness</td><td>execute</td>
  </tr>
  <tr>
    <td>2</td><td>Freshness</td><td>freshness</td><td>Freshness</td><td>execute</td>
  </tr>
  <tr>
    <td>3</td><td>Latency</td><td>latency</td><td>Latency</td><td>execute</td>
  </tr>
  <tr>
    <td>4</td><td>Validity</td><td>validity</td><td>Validity</td><td>execute</td>
  </tr>
</table>

## Completeness
A completeness indicator connects to two different data sources, a **source** and a **target**. It computes a data set on each of the data sources and compares their results. For each measure of each record in both data sets, the framework computes the **difference in percentage** as follow:

`(Measure from target request - Measure from source request) / Measure from source request`.

It compares the difference with the alert operator and alert threshold parameters defined for the indicator and triggers an alert if the condition is met. The comparison with the alert threshold is done in **absolute value**.

**Example:**
To be documented

## Freshness
A freshness indicator connects to one single **target** data source. It computes its last updated timestamp and compares it to the current timestamp. For each record in the data set, the framework computes the **difference in minutes** as follow:

`Current Timestamp - Last updated timestamp from target request`. 

It compares the difference with the alert operator and alert threshold parameters defined for the indicator and triggers an alert if the condition is met. The measure parameter must be set to `last_update`.

**Example:**
To be documented

## Latency
A latency indicator connects to two different data sources, a **source** and a **target**. It computes the last updated timestamp on each of them and compares the results. For each record in both data sets, the framework computes the **difference in minutes** as follow:

`Last updated timestamp from source request - Last updated timestamp from target request`.

It compares the difference with the alert operator and alert threshold parameters defined for the indicator and triggers an alert if the condition is met. The measure parameter should be set to `last_update`.

**Example:**
To be documented

## Validity
A validity indicator connects to one single **target** data source and computes a data set on it. For each measure of each record, it compares the result with the alert operator and alert threshold parameters defined for the indicator and triggers an alert if the condition is met.

**Example:**
To be documented

# Parameter
Parameters used to compute indicators.

**Table:** `parameter` <br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the indicator parameter, used as a primary key.</td>
  </tr>
  <tr>
    <td>value</td><td>Text</td><td>Indicator parameter value.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>updated_date</td><td>Timestamp</td><td>Record last updated date.</td>
  </tr>
  <tr>
    <td>parameter_type_id</td><td>Integer</td><td>Type of parameter, the combination of parameter_type_id and indicator_id must be unique.</td>
  </tr>
  <tr>
    <td>indicator_id</td><td>Integer</td><td>Foreign key of the indicator table, to indicate to which indicator belongs the parameter. The combination of parameter_type_id and indicator_id must be unique.</td>
  </tr>
</table>

# Parameter Type
Parameter types determine which types of parameters can be used to compute indicators.

**Table:** `parameter_type` <br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the parameter type, used as a primary key.</td>
  </tr>
  <tr>
    <td>name</td><td>Text</td><td>Type of indicator parameter.</td>
  </tr>
  <tr>
    <td>description</td><td>Text</td><td>Description of the parameter type.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>updated_date</td><td>Timestamp</td><td>Record last updated date.</td>
  </tr>
</table>

## List of Values
<table>
  <tr>
    <th>id</th><th>name</th><th>description</th>
  </tr>
  <tr>
    <td>1</td><td>Alert operator</td><td>Operator used to compare the results of the indicator with the alert threshold. Example: ==, >, >=, &lt;, &lt;=, &lt;&gt;</td>
  </tr>
  <tr>
    <td>2</td><td>Alert threshold</td><td>Numeric value used to evaluate the results of the indicator and determine if an alert must be sent.</td>
  </tr>
  <tr>
    <td>3</td><td>Distribution list</td><td>List of e-mail addresses to which alerts must be sent. Example: ['email_1', 'email_2', 'email_3']</td>
  </tr>
  <tr>
    <td>4</td><td>Dimension</td><td>List of values to indicate dimensions in the results of the indicator. Example: ['dimension_1', 'dimension_2', 'dimension_3']</td>
  </tr>
  <tr>
    <td>5</td><td>Measure</td><td>List of values to indicate measures in the results of the indicator. Example: ['measure_1', 'measure_2', 'measure_3']</td>
  </tr>
  <tr>
    <td>6</td><td>Source</td><td>Name of the data source which serves as a reference to evaluate the quality of the data.</td>
  </tr>
  <tr>
    <td>7</td><td>Source request</td><td>SQL query used to compute the indicator on the source system.</td>
  </tr>
  <tr>
    <td>8</td><td>Target</td><td>Name of the data source on which to evaluate the quality of the data.</td>
  </tr>
  <tr>
    <td>9</td><td>Target request</td><td>SQL query used to compute the indicator on the target system.</td>
  </tr>
</table>

## Matrix of Indicator Types and Parameter Types
<table>
  <tr>
    <th>Parameter Type</th><th>Completeness</th><th>Freshness</th><th>Latency</th><th>Validity</th>
  </tr>
  <tr>
    <td>Alert operator</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td>
  </tr>
  <tr>
    <td>Alert threshold</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td>
  </tr>
  <tr>
    <td>Distribution list</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td>
  </tr>
  <tr>
    <td>Dimension</td><td>Optional</td><td>Optional</td><td>Optional</td><td>Optional</td>
  </tr>
  <tr>
    <td>Measure</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td>
  </tr>
  <tr>
    <td>Source</td><td>Mandatory</td><td>N/A</td><td>Mandatory</td><td>N/A</td>
  </tr>
  <tr>
    <td>Source request</td><td>Mandatory</td><td>N/A</td><td>Mandatory</td><td>N/A</td>
  </tr>
  <tr>
    <td>Target</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td>
  </tr>
  <tr>
    <td>Target request</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td><td>Mandatory</td>
  </tr>
</table>

# Data Source
Data sources are systems containing or exposing data on which the the tool can compute indicators.

**Table:** `data_source`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the data source, used as a primary key.</td>
  </tr>
  <tr>
    <td>name</td><td>Text</td><td>Name of the data source, must be unique.</td>
  </tr>
  <tr>
    <td>connection_string</td><td>Text</td><td>Connection string used to connect to the data source.</td>
  </tr>
  <tr>
    <td>login</td><td>Text</td><td>Login used to connect to the data source.</td>
  </tr>
  <tr>
    <td>password</td><td>Text</td><td>Password used to connect to the data source.</td>
  </tr>
  <tr>
    <td>connectivity_status</td><td>Text</td><td>Status to indicate if the connection to the data source works.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>updated_date</td><td>Timestamp</td><td>Record last updated date.</td>
  </tr>
  <tr>
    <td>data_source_type_id</td><td>Integer</td><td>Foreign key of the data_source_type table, to indicate which type is the data source.</td>
  </tr>
</table>

# Data Source Type
Data source types describe the types of a data sources the tool can connect to.

**Table:** `data_source_type`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the type of data source, used as a primary key.</td>
  </tr>
  <tr>
    <td>name</td><td>Text</td><td>Type of data source.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>updated_date</td><td>Timestamp</td><td>Record last updated date.</td>
  </tr>
</table>

## List of values
<table>
  <tr>
    <th>id</th><th>name</th>
  </tr>
  <tr>
    <td>1</td><td>Hive</td>
  </tr>
  <tr>
    <td>2</td><td>Impala</td>
  </tr>
  <tr>
    <td>3</td><td>MariaDB</td>
  </tr>
  <tr>
    <td>4</td><td>Microsoft SQL Server</td>
  </tr>
  <tr>
    <td>5</td><td>MySQL</td>
  </tr>
  <tr>
    <td>6</td><td>Oracle</td>
  </tr>
  <tr>
    <td>7</td><td>PostgreSQL</td>
  </tr>
  <tr>
    <td>8</td><td>SQLite</td>
  </tr>
  <tr>
    <td>9</td><td>Teradata</td>
  </tr>
</table>

# Batch
Batches record the execution of groups of indicators.

**Table:** `batch`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the batch, used as a primary key.</td>
  </tr>
  <tr>
    <td>status</td><td>Text</td><td>Indicate the current state of the batch.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>updated_date</td><td>Timestamp</td><td>Record last updated date.</td>
  </tr>
  <tr>
    <td>indicator_group_id</td><td>Integer</td><td>Foreign key of the indicator_group table, to indicate to which group belongs the batch.</td>
  </tr>
</table>

# Session
Sessions record the execution of indicators within a batch.

**Table:** `session`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the session, used as a primary key.</td>
  </tr>
  <tr>
    <td>status</td><td>Text</td><td>Indicate the current state of the session.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>updated_date</td><td>Timestamp</td><td>Record last updated date.</td>
  </tr>
  <tr>
    <td>batch_id</td><td>Integer</td><td>Foreign key of the batch table, to indicate during which batch the session was executed.</td>
  </tr>
  <tr>
    <td>indicator_id</td><td>Integer</td><td>Foreign key of the indicator table, to indicate for which indicator the session was executed.</td>
  </tr>
</table>

# Session Result
Session results contain a summary of indicators execution.

**Table:** `indicator_result`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the indicator result, used as a primary key.</td>
  </tr>
  <tr>
    <td>alert_operator</td><td>Text</td><td>Operator used to compare the result data set of the indicator with the alert threshold.</td>
  </tr>
  <tr>
    <td>alert_threshold</td><td>Float</td><td>Numeric value used to evaluate the result data set of the indicator.</td>
  </tr>
  <tr>
    <td>nb_records</td><td>Integer</td><td>Number of records in the result data set of the indicator.</td>
  </tr>
  <tr>
    <td>nb_records_alert</td><td>Integer</td><td>Number of records which triggered an alert in the result data set of the indicator.</td>
  </tr>
  <tr>
    <td>nb_records_no_alert</td><td>Integer</td><td>Number of records which did not trigger an alert in the result data set of the indicator.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>session_id</td><td>Integer</td><td>Foreign key of the session table, to indicate in which session the result was computed.</td>
  </tr>
</table>
