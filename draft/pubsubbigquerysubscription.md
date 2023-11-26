---
layout: post
title: Simplifying data ingestion with Google Cloud Pub/Sub's BigQuery Subscriptions
subtitle: In this blog I cover how to implement a simple data ingestion and analytics pipeline using Google Cloud Pub/Sub's BigQuery Subscription service.
#cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/gcpdiag/gcpdiag-stethoscope.png
share-img: /assets/img/gcpdiag/gcpdiag-stethoscope.png
readtime: true
share-title: "Simplifying data ingestion with Google Cloud Pub/Sub's BigQuery Subscription"
share-description: "In this blog I cover how to implement a simple data ingestion and analytics pipeline using Google Cloud Pub/Sub's BigQuery Subscription service."
tags: [BigQuery Subscription, Pub/Sub, Data Ingestion, ELT, Analytics]
---

* toc
{:toc}

# Google Cloud's Pub/Sub BigQuery Subscriptions
Google Cloud's Pub/Sub BigQuery subscriptions simplify data ingestion pipelines that require little or no data transformation. Applications performing extract, load and transform (ELT) data pipelines no longer need to make use of Cloud Functions or Dataflow to subscribe to a Pub/Sub topic and load data into BigQuery. Instead Pub/Sub BigQuery subscriptions send messages directly to BigQuery as they are received in one of two ways.

The default method is loading the messages in their raw format, in the BigQuery table under a data column.
<insert diagram of default data ingestion>

Alternatively, a schema can be defined on the Pub/Sub topic to define the format of message fields. The BigQuery subscription then uses this schema to load the defined message fields into corresponding BigQuery table columns. In addition, metadata can be populated to help track information such as message ingestion time etc. 

<insert diagram of bigQuery JSON data table>
<insert diagram of schema, and BigQuery populated table>

<Insert table detailing addional metadata attributes>
With write additional metadata enabled, the BigQuery needs to have the following fields defined. However, these fields must not be defined within the Topic schema. 

REVIEW TABLE AS THESE DON'T APPEAR TO ALIGN WITH WHAT I WAS EXPECTING.

| Parameters        	| Value                                                                                                                                                                                                                    	|
|-------------------	|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	|
| subscription_name 	| STRING Name of a subscription.                                                                                                                                                                                      	|
| message_id        	| STRING ID of a message                                                                                                                                                                                              	|
| publish_time      	| TIMESTAMP The time of publishing a message.                                                                                                                                                                         	|
| data              	| BYTES, STRING, or JSON The message body. The data field is required for all destination BigQuery tables that don't select Use topic schema. If the field is of type JSON, then the message body must be valid JSON. 	|
| attributes        	| STRING or JSON A JSON object containing all message attributes. It also contains additional fields that are part of the Pub/Sub message including the ordering key, if present.                                     	|



If a message is received with additional fields not defined within the schema, BigQuery subscriptions can be configured to drop the message. If the BigQuery subscription doesn't enable drop unknown fields, the messages with extra fields remain in the subscription backlog. The subscription will then end up in an error state.

To mitigate this, Pub/Sub Topic schemas should be configured to automatically drop unknown fields. This ensures the data is still written to BigQuery, but any additional message fields not defined within the schema are dropped.

Once data is loaded into BigQuery, simple SQL transformation can be performed on the raw data. With BigQuery scheduled queries you can automate SQL tranformation tasks based on a cron schedule you define.

Pub/Sub BigQuery subscriptions also remove the requirement to have Pub/Sub Topic clients configured as subscribers. The Pub/Sub BigQuery subscription defines the BigQuery table data will be loaded into and is automatically pushed to BigQuery.

Messages target the BigQuery Write API- upon successful write to BigQuery table, the Pub/Sub message is ackowledged. If the message fails to be written to the table, it is negatively acknowledged to Pub/Sub and Pub/Sub will attempt to write the data to BigQuery again. By configuring an exponential backoff, Pub/Sub will wait the defined amount of time before attempting to write a previously failed message, incrementing the wait period until it reaches the defined threshold for failed delivery attempts. Once this threshold has been met, the message can then be sent to a Dead Letter queue for manual review and intervention. The messages sent to the Dead Letter Queue include an additional CloudPubSubDeadLetterSourceDeliveryErrorMessage attribute which defines the reason the message couldn't be written to BigQuery.

<Architecture diagram demonstrating exponential backoff and forwarding to dead letter queu>

# What IAM permissions do Pub/Sub BigQuery Subscriptions require?
The Pub/Sub service account requires write access to the BigQuery target table, and read access to the table metadata. These permissions can be granted by applying the following Terraform or gcloud commands.

<Example code applying permissions to table. Update previous sentence to clarify tf or gcloud cmd>

# Defining Pub/Sub Topic Schema
The Pub/Sub Topic schema defines the fields within the message that correspond to the columns within the BigQuery table. For this to work, the Topic Schema names and value types must match the BigQuery schema names and value types. Any optional fields within the Topic schema must also be optional within BigQuery schema. However required fields within the Topic schema do not need to be required within the BigQuery schema. If there are any fields within the BigQuery schema that are not present within the Topic schema, this fields must be in nullable mode within BigQuery schema.

```
<Example code creating pub/sub topic schema>

```
***Code Example: Creating a Pub/Sub topic schema with Terraform***

# Creating BigQuery Subscription


# Defining Exponential Backoff


# Configuring Dead Letter Topic

