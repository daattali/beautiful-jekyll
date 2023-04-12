---
layout: post
title: Identifying and troubleshooting issues in GCP Projects with GCPDiag.
subtitle: In this blog I cover the open source tool GCPDiag that helps identify misconfigurations and best practices across a range of Google Cloud offerings including GCE, GKE, BiqQuery...
#description: ""
#cover-img: /assets/img/path.jpg
#thumbnail-img: /assets/img/pca/googlecloudprofessionalcloudarchitectbadge.png
#share-img: /assets/img/pca/googlecloudprofessionalcloudarchitectbadge.png
readtime: true
share-title: "Identifying and troubleshooting issues in GCP Projects with GCP Diag"
share-description: "In this blog I cover the open source tool GCPDiag that helps identify misconfigurations and best practices across a range of Google Cloud offerings including GCE, GKE, BiqQuery..."
#share-img: /assets/img/pca/googlecloudprofessionalcloudarchitectbadge.png
tags: [GCPDiag, Troubleshooting, Best Practice, Misconfiguration, Security]
---

* toc
{:toc}

# What is the GCPDiag tool?
GCPDiag is an opensource tool that can detect configuration issues within your Google Cloud Project. It is a command line tool that runs a series of automated checks against Google Cloud API's to identify a range of issues including errors (ERR) for things that are very likely misconfigured, warnings (WAR) things that are possibly wrong, best practices/opionionated recommendations (BP) and potential security (SEC) issues. 

You run GCPDiag against your project to detect issues against a series of rules and generate a corresponding report. The report highlights where the project deviates from the list of expected conditions.

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

The tool is maintained by the Google Cloud Support team, based on their troubleshooting experience for Google Cloud customers with contributions from the open source community.

# What IAM Permissions does GCPDiag require?
The credentials used to run GCPDiag need to have the following minimum roles on the inspected project:

- Viewer on the inspected project
- Service Usage Consumer on the project used for billing/quota enforcement, which is per default the project being inspected, but can be explicitely set using the --billing-project option

# What API's does GCPDiag require?
GCPDiag requires the following API's to be enabled on the GCP project you are checking:

- cloudresourcemanager.googleapis.com (Cloud Resource Manager API)
- iam.googleapis.com (Identity and Access Management API)
- logging.googleapis.com (Cloud Logging API)
- serviceusage.googleapis.com (Service Usage API)

You can enable these APIs using Cloud Console or via command-line:

```
gcloud --project=MYPROJECT services enable \
    cloudresourcemanager.googleapis.com \
    iam.googleapis.com \
    logging.googleapis.com \
    serviceusage.googleapis.com
```

# How to authenticate GCPDiag
GCPDiag supports three methods of authenticaiton:

1.  OAuth user consent flow
2.  Application default credentials
3.  Service account key

gcpdiag uses by default the OAuth user authentication flow, similarly to what gcloud does. It will print a URL that you need to access with a browser, and ask you to enter the token that you receive after you authenticate there.

The credentials will be cached on disk, so that you can keep running it for 1 hour. To remove cached authentication credentials, you can delete the $HOME/.cache/gcpdiag directory.

Note: if your organization has the “Block all third-party API access” policy set, you will need to either ask an organization admin to add gcpdiag to the list of trusted applications (client id: 539612726288-l17ksc9k8f0d63tfs53i45op9nel9h74.apps.googleusercontent.com), or use another authentication mechanism (such as application default credentials).

gcpdiag can use Cloud SDK’s Application Default Credentials. This might require that you first run gcloud auth login --update-adc to update the cached credentials. This is the default in Cloud Shell because in that environment, ADC credentials are automatically provisioned.

You can also use the --auth-key parameter to specify the private key of a service account.




GCPDiag only checks configurations, it doesn't make any changes to resources even when detecting misconfigurations. 


# How to install GCPDiag
The tool is preinstsalled to the Google Cloud Shell and can be run with the following command replacing MYPROJECT with the Google Cloud Project ID:

```
gcpdiag lint --project=MYPROJECT
```

Alternatively, you can run gcpdiag using a shell wrapper that starts gcpdiag in a Docker container with the following code:

```
curl https://gcpdiag.dev/gcpdiag.sh >gcpdiag
chmod +x gcpdiag
./gcpdiag lint --project=MYPROJECT
```


# How do i use the GCPDiag tool?

Once you have enabled the relevant API's as per [What API's does GCPDiag require?](/gcpdiag.md#what-apis-does-gcpdiag-require) to run GCPDiag in its default form, simply run the following command from the Google Cloud Shell:

```
gcpdiag lint --project=MYPROJECT
```

By default this will ru

![GCPDiag Open Source Tool](/assets/img/gcpdiag/gcpdiag-stethoscope.png "GCPDiag Open Source Tool")
 
*GCPDiag (source: [GCPDiag](https://gcpdiag.dev))*
