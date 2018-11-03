---
layout: page
title: Batches & Sessions
use-site-title: true
---


# Batch
Batches record the execution of indicator groups.

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
    <td>created_by_id</td><td>Integer</td><td>Foreign key of the user table, to indicate which user created the record.</td>
  </tr>
  <tr>
    <td>updated_by_id</td><td>Integer</td><td>Foreign key of the user table, to indicate which user updated the record.</td>
  </tr>
  <tr>
    <td>user_group_id</td><td>Integer</td><td>Foreign key of the user_group table, to indicate to which user group the record belongs to.</td>
  </tr>
  <tr>
    <td>indicator_group_id</td><td>Integer</td><td>Foreign key of the indicator_group table, to indicate for which indicator group the batch was executed.</td>
  </tr>
</table>


---


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
    <td>created_by_id</td><td>Integer</td><td>Foreign key of the user table, to indicate which user created the record.</td>
  </tr>
  <tr>
    <td>updated_by_id</td><td>Integer</td><td>Foreign key of the user table, to indicate which user updated the record.</td>
  </tr>
  <tr>
    <td>user_group_id</td><td>Integer</td><td>Foreign key of the user_group table, to indicate to which user group the record belongs to.</td>
  </tr>
  <tr>
    <td>batch_id</td><td>Integer</td><td>Foreign key of the batch table, to indicate during which batch the session was executed.</td>
  </tr>
  <tr>
    <td>indicator_id</td><td>Integer</td><td>Foreign key of the indicator table, to indicate for which indicator the session was executed.</td>
  </tr>
</table>


---


# Session Result
Session results contain a summary of indicators executions. In particular the number of alerts detected in the result data set of each session.

**Table:** `session_result`<br/>
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
    <td>created_by_id</td><td>Integer</td><td>Foreign key of the user table, to indicate which user created the record.</td>
  </tr>
  <tr>
    <td>user_group_id</td><td>Integer</td><td>Foreign key of the user_group table, to indicate to which user group the record belongs to.</td>
  </tr>
  <tr>
    <td>session_id</td><td>Integer</td><td>Foreign key of the session table, to indicate in which session the result was computed.</td>
  </tr>
</table>
