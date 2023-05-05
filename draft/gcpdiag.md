---
layout: post
title: Identifying and troubleshooting issues in GCP Projects with gcpdiag.
subtitle: In this blog I cover the open source tool gcpdiag that helps identify misconfigurations and best practices across a range of Google Cloud offerings including GCE, GKE, BigQuery, GCS, Cloud Run, Cloud SQL...
#description: "In this blog I cover the open source tool gcpdiag that helps identify misconfigurations and best practices across a range of Google Cloud offerings including GCE, GKE, BigQuery, GCS, Cloud Run, Cloud SQL..."
#cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/gcpdiag/gcpdiag-stethoscope.png
share-img: /assets/img/gcpdiag/gcpdiag-stethoscope.png
readtime: true
share-title: "Identifying and troubleshooting issues in GCP Projects with gcpdiag"
share-description: "In this blog I cover the open source tool gcpdiag that helps identify misconfigurations and best practices across a range of Google Cloud offerings including GCE, GKE, BigQuery, GCS, Cloud Run, CloudSQL..."
tags: [gcpdiag, Troubleshooting, Best Practice, Misconfiguration, Security]
---

* toc
{:toc}

# What is the gcpdiag tool?
gcpdiag is an opensource tool that can detect configuration issues within Google Cloud Projects. It is a command line tool that runs a series of automated checks against Google Cloud API's to identify a range of issues including errors (ERR) for things that are very likely misconfigured, warnings (WAR) for things that are possibly wrong, opinionated recommendations/best practices (BP) and potential security (SEC) issues. 

gcpdiag runs against a GCP project detecting issues against a series of rules, and generating a corresponding report that highlights any deviations from the list of expected conditions.

The tool can be targetted to run against all, or a selection of the following services:

- Apigee
- BigQuery
- CloudRun
- CloudSQL
- Composer
- DataFusion
- DataProc
- Google App Engine
- Google Cloud Build
- Google Compute Engine
- Google Cloud Funtions
- Google Cloud Storage
- Google Kubernetes Engine
- Identity and Access Management (IAM)
- Load balancing (LB)
- Notebooks (Vertex AI Workbench Notebooks)
- TPU
- VPC

gcpdiag is maintained by the Google Cloud Support team, based on their troubleshooting experience for Google Cloud customers, with contributions from the open source community.

# What IAM permissions does gcpdiag require?
The credentials used to run gcpdiag need to have the following minimum roles on the inspected project:

- roles/viewer basic role on the inspected project.
- roles/serviceusage.serviceUsageConsumer predefined role on the project used for billing/quota enforcement.

If the billing project differs from the project being inspected, this can be set using the --billing-project option.

# What API's does gcpdiag require?
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

# How to authenticate gcpdiag
gcpdiag supports three methods of authentication:

1.  OAuth user consent flow
2.  Application default credentials
3.  Service account key

By default, gcpdiag uses the OAuth user authentication flow, similarly to how gcloud does. gcpdiag prints a URL to access with a browser, prompting for the token returned after authenticating with the URL.

The credentials are then cached on disk for 1 hour. To remove cached authentication credentials, you can delete the $HOME/.cache/gcpdiag directory.

Note: if your organization has the “Block all third-party API access” policy set, you will need to add gcpdiag to the list of trusted applications (client id: 539612726288-l17ksc9k8f0d63tfs53i45op9nel9h74.apps.googleusercontent.com), or use another authentication mechanism (such as application default credentials).

gcpdiag can also use Cloud SDK’s Application Default Credentials. This is the default in Cloud Shell because within that environment, ADC credentials are automatically provisioned.

Alternatively, gcpdiag can authenticate with the private key of a service account using the --auth-key parameter.


# How to install gcpdiag
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
