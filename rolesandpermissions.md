---
layout: page
title: Roles & Permissions
use-site-title: true
---


# Roles
Roles and permissions are managed using the internal PostgreSQL role concepts. MobyDQ uses two roles which define to which database objects users can access to (object level security).

## Standard
The `standard` role grants permissions to read, write and delete the following objects:
* Indicators
* Indicator groups
* Indicator parameters

In addition the `standard` role grants permissions to read data sources, except their password attribute.

## Admin
The `admin` role grants the same permissions as the `standard` role, plus the permissions to read, write and delete the following objects:
* Data sources (including the password attribute)
* Data source types
* Indicator types
* Indicator parameter types
* Users
* User groups


---


# Row Level Security
In addition to roles and permissions, MobyDQ also implements the row level security feature of PostgreSQL. It is used to manage visibility rules on the data so that users only see the data of the groups they belong to. Row level security is implemented for the following objects:
* Data sources
* Indicators
* Indicator groups
* Indicator parameters
* Batches
* Sessions
* Session results
