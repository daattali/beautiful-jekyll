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
Google Cloud's Pub/Sub BigQuery subscriptions simplify data ingestion pipelines that require little or no data transformation. Applications performing extract, load and transform (ELT) data pipelines no longer need to make use of Cloud Functions or Dataflow to subscribe to a Pub/Sub topic and load data into BigQuery. Instead Pub/Sub BigQuery subscriptions send messages directly to BigQuery as they are received.

************insert architecture diagram***********

Messages are sent to BigQuery in one of two ways. The default method loads the messages in their raw format, into the BigQuery table under a data field.

************insert diagram of default data ingestion***************88

Alternatively, a schema can be defined on the Pub/Sub topic to define the format of message fields. The BigQuery subscription then uses this schema to load the defined message fields into corresponding BigQuery table fields. In addition, metadata can be populated to help track information such as message ingestion time etc. 

**************insert diagram of bigQuery JSON data table>**************
***************insert diagram of schema, and BigQuery populated table***************

**************Insert table detailing addional metadata attributes>***************
With write additional metadata enabled, the BigQuery schema needs to have the following fields defined. However, these fields must not be defined within the Topic schema itself. 

**************REVIEW TABLE AS THESE DON'T APPEAR TO ALIGN WITH WHAT I WAS EXPECTING.**************8

| Parameters        	| Value                                                                                                                                                                                                                    	|
|-------------------	|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	|
| subscription_name 	| STRING Name of a subscription.                                                                                                                                                                                      	|
| message_id        	| STRING ID of a message                                                                                                                                                                                              	|
| publish_time      	| TIMESTAMP The time of publishing a message.                                                                                                                                                                         	|
| data              	| BYTES, STRING, or JSON The message body. The data field is required for all destination BigQuery tables that don't select Use topic schema. If the field is of type JSON, then the message body must be valid JSON. 	|
| attributes        	| STRING or JSON A JSON object containing all message attributes. It also contains additional fields that are part of the Pub/Sub message including the ordering key, if present.                                     	|



If a message is received with additional fields not defined within the schema, BigQuery subscriptions can be configured to drop the message. If the BigQuery subscription doesn't enable drop unknown fields, the messages with extra fields remain in the subscription backlog. The subscription will then end up in an error state.

To mitigate this, Pub/Sub Topic schemas should be configured to automatically drop unknown fields. This ensures the data is still written to BigQuery, but any additional message fields not defined within the schema are dropped.

Once data is loaded into BigQuery, simple SQL transformations can be performed on the raw data. With BigQuery scheduled queries you can automate SQL tranformation tasks based on a cron schedule you define.

Pub/Sub BigQuery subscriptions also remove the requirement to have Pub/Sub Topic clients configured as subscribers. The Pub/Sub BigQuery subscription defines the BigQuery table data will be loaded into and is automatically pushed directly to BigQuery.

Messages target the BigQuery Write API- upon successful write to the BigQuery table, the Pub/Sub message is ackowledged. If the message fails to be written to the table, it is negatively acknowledged to Pub/Sub and Pub/Sub will attempt to write the data to BigQuery again. By configuring an exponential backoff, Pub/Sub will wait the defined amount of time before attempting to write a previously failed message, incrementing the wait period until it reaches the defined threshold for failed delivery attempts. Once this threshold has been met, the message can then be sent to a Dead Letter queue for manual review and intervention. The messages sent to the Dead Letter Queue include an additional CloudPubSubDeadLetterSourceDeliveryErrorMessage attribute which defines the reason the message couldn't be written to BigQuery.

**************Architecture diagram demonstrating exponential backoff and forwarding to dead letter queu>**************

# What IAM permissions do Pub/Sub BigQuery Subscriptions require?
The Pub/Sub service account requires write access to the BigQuery target table, and read access to the table metadata. These permissions can be granted by applying the following Terraform code. The google_bigquery_table_iam_member resource creates a non authoritative update to the IAM bindings, preserving any existing table bindings.

```
resource "google_bigquery_table_iam_member" "member" {
  project = google_bigquery_table.test.project
  dataset_id = google_bigquery_table.test.dataset_id
  table_id = google_bigquery_table.test.table_id
  role = "roles/bigquery.dataEditot"
  member = "user:jane@example.com"
}

resource "google_project_iam_member" "viewer" {
  project = data.google_project.project.project_id
  role   = "roles/bigquery.metadataViewer"
  member = "serviceAccount:service-${data.google_project.project.number}@gcp-sa-pubsub.iam.gserviceaccount.com"
}

resource "google_project_iam_member" "editor" {
  project = data.google_project.project.project_id
  role   = "roles/bigquery.dataEditor"
  member = "serviceAccount:service-${data.google_project.project.number}@gcp-sa-pubsub.iam.gserviceaccount.com"
}
```
***Code Example: Applying required permissions to BigQuery table with Terraform***


# Defining Pub/Sub Topic Schema
The Pub/Sub Topic schema defines the fields within the message that correspond to the columns within the BigQuery table. For this to work, the Topic Schema names and value types must match the BigQuery schema names and value types. Any optional fields within the Topic schema must also be optional within the BigQuery schema. However, required fields within the Topic schema do not need to be required within the BigQuery schema. If there are any fields within the BigQuery schema that are not present within the Topic schema, these fields must be in a nullable mode within the BigQuery schema.

```
resource "google_pubsub_schema" "cloudbabbleschema" {
  name = "cloudbabbleschema"
  type = "AVRO"
  definition = "{\n  \"type\" : \"record\",\n  \"name\" : \"Avro\",\n  \"fields\" : [\n    {\n      \"name\" : \"StringField\",\n      \"type\" : \"string\"\n    },\n    {\n      \"name\" : \"IntField\",\n      \"type\" : \"int\"\n    }\n  ]\n}\n"
}

resource "google_pubsub_topic" "cloudbabbletopic" {
  name = "cloud-babble-topic"

  depends_on = [google_pubsub_schema.cloudbabbleschema]
  schema_settings {
    schema = "projects/my-project-name/schemas/example"
    encoding = "JSON"
  }
}
```
***Code Example: Creating a Pub/Sub topic schema with Terraform***

# Creating BigQuery Subscription
The following Terraform code provisions a BigQuery subscription.

```
resource "google_pubsub_topic" "cloudbabbletopic" {
  name = "cloudbabble-topic"
}

resource "google_pubsub_subscription" "cloudbabblesubscription" {
  name  = "cloudbabble-subscription"
  topic = google_pubsub_topic.cloudbabbletopic.name

  bigquery_config {
    table = "${google_bigquery_table.test.project}.${google_bigquery_table.test.dataset_id}.${google_bigquery_table.test.table_id}"
  }

  depends_on = [google_project_iam_member.viewer, google_project_iam_member.editor]
}

data "google_project" "project" {
}

resource "google_project_iam_member" "viewer" {
  project = data.google_project.project.project_id
  role   = "roles/bigquery.metadataViewer"
  member = "serviceAccount:service-${data.google_project.project.number}@gcp-sa-pubsub.iam.gserviceaccount.com"
}

resource "google_project_iam_member" "editor" {
  project = data.google_project.project.project_id
  role   = "roles/bigquery.dataEditor"
  member = "serviceAccount:service-${data.google_project.project.number}@gcp-sa-pubsub.iam.gserviceaccount.com"
}

resource "google_bigquery_dataset" "test" {
  dataset_id = "example_dataset"
}

resource "google_bigquery_table" "test" {
  deletion_protection = false
  table_id   = "example_table"
  dataset_id = google_bigquery_dataset.test.dataset_id

  schema = <<EOF
[
  {
    "name": "data",
    "type": "STRING",
    "mode": "NULLABLE",
    "description": "The data"
  }
]
EOF
}
```
***Code Example: Creating a BigQuery subscription with Terraform***

# Defining Exponential Backoff
The following terraform code defines an exponential backoff for messages that fail to write to the BigQuery table and are negatively acknowledged.

```
<Example code defining exponential backoff>

```
***Code Example: Defining exponential backoff for failed message publishing with Terraform***

# Configuring Dead Letter Topic
The following terraform code provides an example Dead Letter Topic configuration for messages that fail to write to BigQuery within the defined threshold for failed delivery attempts. 
```
<Example code creating Dead Letter Topic>

```
***Code Example: Creating a Dead Letter Topic with Terraform***
