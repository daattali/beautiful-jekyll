# create pub/sub schema
resource "google_pubsub_schema" "cloudbabbleschema01" {
  name = "cloudbabbleschema01"
  type = "AVRO"
  definition = "{\n  \"type\" : \"record\",\n  \"name\" : \"Avro\",\n  \"fields\" : [\n    {\n      \"name\" : \"Username\",\n      \"type\" : \"string\"\n    },\n    {\n      \"name\" : \"Age\",\n      \"type\" : \"int\"\n    },\n    {\n      \"name\" : \"ActiveMember\",\n      \"type\" : \"boolean\"\n    }\n  ]\n}\n"
}

# create pub/sub topic, with defined schema
resource "google_pubsub_topic" "cloudbabbletopic01" {
  name = "cloudbabbletopic01"

  depends_on = [google_pubsub_schema.cloudbabbleschema01]
  schema_settings {
    schema = "projects/${data.google_project.project.number}/schemas/cloudbabbleschema01"
    encoding = "JSON"
  }
}

# create dead letter topic
resource "google_pubsub_topic" "cloudbabble_dead_letter" {
  name = "cloudbabble-dead-letter"
}

#create pub/sub bigquery subscription for defined topic
resource "google_pubsub_subscription" "cloudbabblesubscription01" {
  name  = "cloudbabblesubscription01"
  topic = google_pubsub_topic.cloudbabbletopic01.name

  bigquery_config {
    table = "${google_bigquery_table.cloudbabbletable01.project}.${google_bigquery_table.cloudbabbletable01.dataset_id}.${google_bigquery_table.cloudbabbletable01.table_id}"
    use_topic_schema = true
  }
# configure dead letter policy
  dead_letter_policy {
    dead_letter_topic = google_pubsub_topic.cloudbabble_dead_letter.id
    max_delivery_attempts = 10
  }

  depends_on = [google_bigquery_table_iam_member.viewer, google_bigquery_table_iam_member.editor]
}

data "google_project" "project" {
}

# grant pub/sub service account metadataViewer permissions on BigQuery target table
resource "google_bigquery_table_iam_member" "viewer" {
  dataset_id = google_bigquery_dataset.cloudbabbledataset01.dataset_id
  table_id = google_bigquery_table.cloudbabbletable01.table_id
  role   = "roles/bigquery.metadataViewer"
  member = "serviceAccount:service-${data.google_project.project.number}@gcp-sa-pubsub.iam.gserviceaccount.com"
}

# grant pub/sub service account dataeditor permissions on BigQuery target table
resource "google_bigquery_table_iam_member" "editor" {
  dataset_id = google_bigquery_dataset.cloudbabbledataset01.dataset_id
  table_id = google_bigquery_table.cloudbabbletable01.table_id
  role   = "roles/bigquery.dataEditor"
  member = "serviceAccount:service-${data.google_project.project.number}@gcp-sa-pubsub.iam.gserviceaccount.com"
}

# create bigquery destination dataset for pub/sub subscription
resource "google_bigquery_dataset" "cloudbabbledataset01" {
  dataset_id = "cloudbabbledataset01"
}

# create bigquery destination table for pub/sub subscription
resource "google_bigquery_table" "cloudbabbletable01" {
  deletion_protection = false
  table_id   = "cloudbabbletable01"
  dataset_id = google_bigquery_dataset.cloudbabbledataset01.dataset_id
#define schema of bigquery table to match pubsub topic schema
  schema = <<EOF
[
  {
    "name": "Username",
    "type": "STRING",
    "mode": "NULLABLE",
    "description": "Username description"
  },
  {
    "name": "Age",
    "type": "INTEGER",
    "mode": "NULLABLE",
    "description": "User's age"
  },
  {
    "name": "ActiveMember",
    "type": "BOOLEAN",
    "mode": "NULLABLE",
    "description": "Is the user an active member"
  }
]
EOF
}

