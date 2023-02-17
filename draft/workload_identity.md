---
layout: post
title: GKE Workload Identity
subtitle: In this blog I provide an overview of why Google Kubernetes Engine (GKE) Workload Identity is the recommended method for accessing Google Cloud resources from a GKE cluster, how to configure Workload Identity and call out some of the risks associated with alternate methods accessing Google Cloud resources.
#cover-img: /assets/img/path.jpg
#thumbnail-img: /assets/img/anthos/anthoslogo.png
readtime: true
share-title: Google Kubernetes Engine (GKE) Workload Identity
share-description: In this blog I provide an overview of why Google Kubernetes Engine (GKE) Workload Identity is the recommended method for accessing Google Cloud resources from a GKE cluster, how to configure Workload Identity and call out some of the risks associated with alternate methods accessing Google Cloud resources.
#share-img: /assets/img/anthos/anthoslogo.png
tags: [GKE, Workload Identity, containers, security, best practices, kubernetes, google kubernetes engine]
---

* toc
{:toc}

# Accessing Google Cloud Resources From Google Kubernetes Engine (GKE)

Application workloads running on Google Kubernetes Engine frequently need to access Google Cloud resources and API’s. For this to work, the workload needs to authenticate with Google Cloud’s IAM service to verify they are authorised to access the desired resource.

There are several ways this can be achieved, however the recommended approach is via Workload Identity. Before going into detail on Workload Identity, I would like to highlight some of the risks associated with accessing these resources without using Workload Identity with non-recommended approaches including exporting service account keys, and using Compute Engine service accounts.

# Exporting Service Account Keys

The main issues with exporting service account keys and storing them in a secure vault like Google Cloud’s Secret Manager are:

1. Service account keys don’t expire. Once the key has been created, it remains the same indefinitely unless it is manually updated.
1. Manually updating service account keys constitutes toil, it doesn’t scale well and is likely to be forgotten or not performed frequently enough.
1. Attackers who gain access to the service account key may go undetected for a significant period of time, during which they will be able to successfully authenticate as the service account, potentially expanding the scope of the security breach.

# Using Compute Engine Service Account

The main issue with using the Compute Engine service account of your nodes is violating the principle of least privilege. Service accounts should be limited in scope to the least privileges required to perform their role and no more. By allowing your cluster to use the Compute Engine service account, you are granting more privileges than required. If this account becomes compromised there is a much greater blast radius than if a dedicated service account with reduced scope and privileges was compromised. 

Furthermore, if each application workload is using the Compute Engine service account, it complicates auditing and visibility of what workloads used the service account to make the API calls.

In the event the Compute Engine service account becomes compromised and you need to revoke it, you are no longer revoking just the service account for a single application, you are revoking the service account for all application workloads, introducing more toil and an outage to multiple applications.

It’s also worthwhile calling out at this stage your Google Kubernete Engine/GKE cluster nodes should not be running under the default Compute Engine service account for the same reasons regarding principle of least privilege. The default Compute Engine service account has significantly more permissions than a GKE node service account requires. For this reason, run your GKE nodes under a dedicated GKE Node service account.

There is a predefined IAM role for GKE node service accounts that has the minimum required permissions under [roles/container.nodeServiceAccount]( https://cloud.google.com/iam/docs/understanding-roles#container.nodeServiceAccount).

# Workload Identity

Workload Identity is the recommended method to access Google Cloud API’s from a Google Kubernetes Engine (GKE) hosted application workload. With Workload Identity, your workload is able to impersonate a predefined Google Cloud IAM service account to gain access to the required resources. Pods that use the configured Kubernetes service account, impersonate the IAM service account when they access the GCP API’s. This enables you to define distinct, fine-grained identities and authorisation for each application in your cluster.

Each GKE cluster with Workload identity enabled is assigned a workload identity pool name in the format: PROJECT_ID.svc.id.goog. IAM uses this naming format to trust the Kubernetes service account credentials. This is made possible due to all Google Cloud Project ID’s being globally unique, across all organisations.

When you configure a Kubernetes service account in a namespace to use Workload Identity, IAM authenticates the credentials using the following member name:

> *serviceAccount:PROJECT_ID.svc.id.goog[KUBERNETES_NAMESPACE/KUBERNETES_SERVICE_ACCOUNT]*

This member name has an IAM policy binding to the corresponding IAM Service Account, granting the workload access to the resources it requires. By creating dedicated service accounts per workload, and corresponding IAM service accounts, you can limit access to GCP API’s to only those required by said workload.

# Identity Sameness

The member name used to identify the workload’s Kubernetes service account doesn’t reference the GKE cluster running the workload. For this reason, it is important that you only deploy multiple GKE clusters within the same GCP project if you trust all the workloads that will be running.

The workload identity pool is derived from the GCP project ID, and therefore if two teams manage their own GKE cluster within the same project, and they both create matching namespaces and Kubernetes service account names, they will potentially be able to access additional GCP API’s. IAM doesn’t distinguish between the clusters making the call.

![Workload Identity Sameness Across Clusters](/assets/img/gke/wi/workloadidentitysameness.svg "Workload Identity Sameness Across Clusters")
 
*Workload Identity Sameness Across Clusters (source: [Google Cloud](https://cloud.google.com/kubernetes-engine/docs/concepts/workload-identity#identity_sameness))*

# Using Workload Identity

Configuring Workload Identity is a two stage process, the first stage is to enable Workload Identity on the GKE cluster. The second stage is to configure application workloads to use Workload Identity.

# Enabling Workload Identity

The following IAM roles are required to enable Workload Identity:

- roles/container.admin
- roles/iam.serviceAccountAdmin

Workload Identity must be enabled at the cluster level before you can enable Workload Identity on node pools. The cluster can be enabled during provisioning, or updated at a later date.

## Create A Google Kubernetes Engine (GKE) Cluster with Workload Identity Enabled

The following gcloud command creates a new cluster with Workload Identity enabled:

```
gcloud container clusters create CLUSTER_NAME \
    --region=COMPUTE_REGION \
    --workload-pool=PROJECT_ID.svc.id.goog
```
Replace the following:

- CLUSTER_NAME: the name of your new cluster.
- COMPUTE_REGION: the Compute Engine region of your cluster. For zonal clusters, use --zone=COMPUTE_ZONE.
- PROJECT_ID: your Google Cloud project ID.

When using the [Terraform Google Kubernetes-Engine module](https://registry.terraform.io/modules/terraform-google-modules/kubernetes-engine/google/latest?tab=inputs) to create a new cluster, Workload Identify is enabled by default.

Alternatively, if you’re creating your cluster and defining your resources under the [google_container_cluster resource](https://registry.terraform.io/providers/hashicorp/google/latest/docs/resources/container_cluster), including the following code will enable Workload Identity on your cluster:

```
workload_identity_config {
    workload_pool = "${var.project}.svc.id.goog"
  }
```

## Enable Workload Identity On An Existing Google Kubernetes Engine (GKE) Standard Cluster

The following gcloud command updates an existing Google Kubernetes Engine cluster to use Workload Identity. 

```
gcloud container clusters update CLUSTER_NAME \
    --region=COMPUTE_REGION \
    --workload-pool=PROJECT_ID.svc.id.goog
```

Replace the following:

- CLUSTER_NAME: the name of your existing cluster.
- COMPUTE_REGION: the Compute Engine region of your cluster. For zonal clusters, use --zone=COMPUTE_ZONE.
- PROJECT_ID: your Google Cloud project ID.

The following Terraform code will also enable Workload Identity on an existing Google Kubernetes Engine cluster as part of the [google_container_cluster resource](https://registry.terraform.io/providers/hashicorp/google/latest/docs/resources/container_cluster):

```
workload_identity_config {
    workload_pool = "${var.project}.svc.id.goog"
  }
```

**Existing node pools are unaffected, but any new node pools in the cluster will be configured to use Workload Identity.**

# Configuring Application Workloads To Use Workload Identity

After enabling Workload Identity at the Google Kubernetes Engine cluster level, the application workload must be configured to use Workload Identity. A Kubernetes service account must be assigned to each application which is then configured to impersonate an IAM service account. The following steps detail how to enable Workload Identity authentication for an application workload using gcloud commands.

## GCloud Command: Application Workload Configuration

1. The first step is to get credentials for your cluster:

```
gcloud container clusters get-credentials CLUSTER_NAME \
    --region=COMPUTE_REGION
```

Replace the following:

- CLUSTER_NAME: the name of your cluster that has Workload Identity enabled.
- COMPUTE_REGION: the Compute Engine region of your cluster.

2. Create a namespace to use for the Kubernetes service account. You can also use the default namespace or any existing namespace.

```
kubectl create namespace NAMESPACE
```

3. Create a Kubernetes service account for your application to use. You can also use the default Kubernetes service account in the default or any existing namespace.

```
kubectl create serviceaccount KSA_NAME \
    --namespace NAMESPACE
```

Replace the following:

- KSA_NAME: the name of your new Kubernetes service account.
- NAMESPACE: the name of the Kubernetes namespace for the service account.

4. Create an IAM service account for your application or use an existing IAM service account instead. You can use any IAM service account in any project in your organization. For Config Connector, apply the IAMServiceAccount object for your selected service account.

```
gcloud iam service-accounts create GSA_NAME \
    --project=GSA_PROJECT
```
Replace the following:

- GSA_NAME: the name of the new IAM service account.
- GSA_PROJECT: the project ID of the Google Cloud project for your IAM service account.

5. Ensure that your IAM service account has the roles you need. You can grant additional roles using the following command:

```
gcloud projects add-iam-policy-binding PROJECT_ID \
    --member "serviceAccount:GSA_NAME@GSA_PROJECT.iam.gserviceaccount.com" \
    --role "ROLE_NAME"
```

Replace the following:
- PROJECT_ID: your Google Cloud project ID.
- GSA_NAME: the name of your IAM service account.
- GSA_PROJECT: the project ID of the Google Cloud project of your IAM service account.
- ROLE_NAME: the IAM role to assign to your service account, like roles/spanner.viewer.

6. Allow the Kubernetes service account to impersonate the IAM service account by adding an IAM policy binding between the two service accounts. This binding allows the Kubernetes service account to act as the IAM service account.

```
gcloud iam service-accounts add-iam-policy-binding GSA_NAME@GSA_PROJECT.iam.gserviceaccount.com \
    --role roles/iam.workloadIdentityUser \
    --member "serviceAccount:PROJECT_ID.svc.id.goog[NAMESPACE/KSA_NAME]"
```

7. Annotate the Kubernetes service account with the email address of the IAM service account.

```
YAML: apiVersion: v1
kind: ServiceAccount
metadata:
  annotations:
    iam.gke.io/gcp-service-account: GSA_NAME@PROJECT_ID.iam.gserviceaccount.com
  name: KSA_NAME
  namespace: NAMESPACE
```

Note: This annotation by itself does not grant access to impersonate the IAM service account. If the IAM binding does not exist, the Pod will not be able to use the IAM service account.

8. Update your Pod spec to schedule the workloads on nodes that use Workload Identity and to use the annotated Kubernetes service account.
Note: Omit spec.serviceAccountName if you annotate the default Kubernetes service account. For Autopilot clusters, omit the nodeSelector field. Autopilot rejects this nodeSelector because all nodes use Workload Identity.

```
spec:
  serviceAccountName: KSA_NAME
  nodeSelector:
    iam.gke.io/gke-metadata-server-enabled: "true"
```

9. Apply the updated configuration to your cluster:

```
kubectl apply -f DEPLOYMENT_FILE
```

Replace DEPLOYMENT_FILE with the path to the updated Pod spec.
VERIFY?

## Terraform Code Application Workload Configuration

GKE Workload Identity Terraform module is a submodule of the google_kubernetes_engine module and is available here: https://registry.terraform.io/modules/terraform-google-modules/kubernetes-engine/google/latest/submodules/workload-identity

The following steps guide you through enabling the application workload to use Workload Identity using Terraform.

```
module "cloud-babble-demo-app-workload-identity" {
  source     = "terraform-google-modules/kubernetes-engine/google//modules/workload-identity"
  name       = "cloud-babble-demo-app"
  namespace  = "demonamespace"
  project_id = var.project
  roles      = ["roles/storage.admin", "roles/compute.admin"]
}
```

This will create:

- Google Service Account named: my-application-name@my-gcp-project-name.iam.gserviceaccount.com
- Kubernetes Service Account named: my-application-name in the default namespace
- IAM Binding (roles/iam.workloadIdentityUser) between the service accounts

Usage from a Kubernetes deployment:

```
metadata:
  namespace: default
  # ...
spec:
  # ...
  template:
    spec:
      serviceAccountName: my-application-name
```

### Using an existing Google Service Account

An existing Google service account can optionally be used.

```
resource "google_service_account" "preexisting" {
  account_id   = "preexisting-sa"
}

module "my-app-workload-identity" {
  source              = "terraform-google-modules/kubernetes-engine/google//modules/workload-identity"
  use_existing_gcp_sa = true
  name                = google_service_account.preexisting.account_id
  project_id          = var.project_id

  # wait for the custom GSA to be created to force module data source read during apply
  # https://github.com/terraform-google-modules/terraform-google-kubernetes-engine/issues/1059
  depends_on = [google_service_account.preexisting]
}
```

### Using an existing Kubernetes Service Account
An existing Kubernetes service account can optionally be used.

```
resource "kubernetes_service_account" "preexisting" {
  metadata {
    name      = "preexisting-sa"
    namespace = "prod"
  }
}

module "my-app-workload-identity" {
  source              = "terraform-google-modules/kubernetes-engine/google//modules/workload-identity"
  use_existing_k8s_sa = true
  name                = kubernetes_service_account.preexisting.metadata[0].name
  namespace           = kubernetes_service_account.preexisting.metadata[0].namespace
  project_id          = var.project_id
}
```

If annotation is disabled (via annotate_k8s_sa = false), the existing Kubernetes service account must already bear the "iam.gke.io/gcp-service-account" annotation.
