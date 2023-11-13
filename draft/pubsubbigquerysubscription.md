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
Google Cloud's Pub/Sub BigQuery subscriptions simplify data ingestion pipelines that require little or no data transformation. Applications performing extract, load and transform (ELT) pipelines no longer need to make use of Cloud Functions or Dataflow to subscribe to your Pub/Sub topic and load data into BigQuery. Pub/Sub BigQuery subscriptions enable you to send messages to BigQuery directly as they are received.

Messages can be loaded into BigQuery in two ways. The default method is loading the messages in their raw format. Within BigQuery, the messages are stored in the defined table in JSON format under a data column. Alternatively, a schema can be defined on the Pub/Sub topic to define the format of message fields. The BigQuery subscription then uses this schema to load the defined message fields into corresponding BigQuery table columns. In addition, metadata can be populated to help track information such as message ingestion time etc. 

<insert diagram of bigQuery JSON data table>
<insert diagram of schema, and BigQuery populated table>

If a message is received with additional fields not defined within the schema, BigQuery subscriptions can be configured to drop the message. If the BigQuery subscription doesn't enable dropping unknown message fields, the messages with extra fields remain in the subscription backlog. <test if it drops only the unknown message fields and pushes to BigQuery still, or drops entire message>

<check true statement> To mitigate this, Pub/Sub Topics (or schema?) should be configured to automatically drop unknown fields. This ensures the data is still written to BigQuery, but any additional message fields not defined within the schema are dropped.

Once data is loaded into BigQuery, simple SQL transformation can be performed on the raw data. With BigQuery scheduled queries you can automate SQL tranformation tasks based on a cron schedule you define.

Pub/Sub BigQuery subscriptions also remove the requirement to have Pub/Sub Topic clients configured as subscribers. The Pub/Sub BigQuery subscription defines the BigQuery table data will be loaded into and is automatically pushed to BigQuery.

Messages target the BigQuery Write API- upon successful write to BigQuery table, the Pub/Sub message is ackowledged. If the message fails to be written to the table, it is negatively acknowledged to Pub/Sub and Pub/Sub will attempt to write the data to BigQuery again. By configuring an exponential backoff, Pub/Sub will wait the defined amount of time before attempting to write a previously failed message, incrementing the wait period until it reaches the defined threshold for failed delivery attempts. Once this threshold has been met, the message can then be sent to a Dead Letter queue for manual review and intervention. 

# What IAM permissions do Pub/Sub BigQuery Subscriptions require?
The Pub/Sub service account requires write access to the BigQuery target table, and read access to the table metadata. These permissions can be granted by applying the following 

<Example code applying permissions to table>

# Defining Pub/Sub Topic Schema
The Pub/Sub Topic schema

<Example code creating pub/sub topic schema>

# Creating BigQuery Subscription

gcpdiag requires the following API's to be enabled on the GCP project to inspect:

- cloudresourcemanager.googleapis.com (Cloud Resource Manager API)
- iam.googleapis.com (Identity and Access Management API)
- logging.googleapis.com (Cloud Logging API)
- serviceusage.googleapis.com (Service Usage API)

These APIs can be enabled using Cloud Console or via the following gcloud command-line:

```
gcloud --project=MYPROJECT services enable \
    cloudresourcemanager.googleapis.com \
    iam.googleapis.com \
    logging.googleapis.com \
    serviceusage.googleapis.com
```
***Code Example: Enabling gcpdiag's required API's with gcloud command line***

# Defining Exponential Backoff
gcpdiag supports three methods of authentication:

1.  OAuth user consent flow
2.  Application default credentials
3.  Service account key

By default, gcpdiag uses the OAuth user authentication flow, similarly to how gcloud does. gcpdiag prints a URL to access with a browser, prompting for the token returned after authenticating with the URL.

The credentials are then cached on disk for 1 hour. To remove cached authentication credentials, you can delete the $HOME/.cache/gcpdiag directory.

Note: if your organization has the “Block all third-party API access” policy set, you will need to add gcpdiag to the list of trusted applications (client id: 539612726288-l17ksc9k8f0d63tfs53i45op9nel9h74.apps.googleusercontent.com), or use another authentication mechanism (such as application default credentials).

gcpdiag can also use Cloud SDK’s Application Default Credentials. This is the default in Cloud Shell because within that environment, ADC credentials are automatically provisioned.

Alternatively, gcpdiag can authenticate with the private key of a service account using the --auth-key parameter.


# Configuring Dead Letter Topic
gcpdiag is preinstalled to the Google Cloud Shell and can be run with the following command replacing MYPROJECT with the Google Cloud Project ID to inspect:

```
gcpdiag lint --project=MYPROJECT
```
***Code Example: Running gcpdiag lint***

Alternatively, you can run gcpdiag using a shell wrapper that starts gcpdiag in a Docker container with the following code:

```
curl https://gcpdiag.dev/gcpdiag.sh >gcpdiag
chmod +x gcpdiag
./gcpdiag lint --project=MYPROJECT
```
***Code Example: Example shell wrapper for starting gcpdiag within a docker container***

# How do I use the gcpdiag tool?

Once you have enabled the relevant API's as per '[What API's does gcpdiag require?](/gcpdiag#what-apis-does-gcpdiag-require)' to run gcpdiag in its default form, simply run the following command from the Google Cloud Shell replacing MYPROJECT with your GCP project's ID:

```
gcpdiag lint --project=MYPROJECT
```
***Code Example: Running gcpdiag***

This will run all the default checks (Error, Warning, Best Practice, Security checks...) against all services within the targeted project, generating a summary of the tests performed including total skipped rules, ok rules, and failed rules within the terminal window. Scrolling back through the terminal output enables you to identify what checks failed and provides guidance on how to align with the recommended best practices. 

gcpdiag does not provide the functionality to remediate detected issues, it only highlights misconfigurations.

```
gcpdiag lint --help
```
***Code Example: gcpdiag lint help command***

--help returns all the configurable options available to customise the checks the tool performs. This can be configured to only check select GCP products and services e.g. limit checks to GKE only, to only check certain rule sets e.g. Best Practices only, and to filter what information is returned for checks that pass. Similarly, you can define whether the results are presented in the terminal window, JSON or CSV format.

The default settings for gcpdiag runs Auth-ADC for authentication, searches logs from the last 3 days, and outputs the results within the terminal.

![gcpdiag Open Source Tool](/assets/img/gcpdiag/gcpdiag-stethoscope.png "gcpdiag Open Source Tool")
 
*gcpdiag (source: [gcpdiag](https://gcpdiag.dev))*

