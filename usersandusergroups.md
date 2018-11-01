---
layout: page
title: Users & User Groups
use-site-title: true
---


# User
The `user` table stores authentication information of the users registered in MobyDQ. It is also used to automate database roles management in PostgreSQL. When a user is created in the `user` table, the following operations are triggered:
* A new user role `user_<id>` is created in the `pg_roles` table.
* If `flag_admin` is set to `True`, the `user_<id>` role is granted the `admin` role.
* If `flag_admin` is set to `False`, the `user_<id>` role is granted the default `standard` role.
* The `user_<id>` role is automatically granted the default Public user group role `user_group_0`.

**Table:** `user`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the user, used as a primary key.</td>
  </tr>
  <tr>
    <td>email</td><td>Text</td><td>E-mail of the user, must be unique.</td>
  </tr>
  <tr>
    <td>oauth_type</td><td>Text</td><td>Third party provider used for user authentication.</td>
  </tr>
  <tr>
    <td>access_token</td><td>Text</td><td>Token provided by the third party for user authentication.</td>
  </tr>
  <tr>
    <td>refresh_token</td><td>Text</td><td>Refresh token provided by the third party to renew user authentication.</td>
  </tr>
  <tr>
    <td>expiry_date</td><td>Text</td><td>Expiration date of token provided by the third party.</td>
  </tr>
  <tr>
    <td>flag_admin</td><td>Boolean</td><td>Boolean value to indicate if the user has admin role.</td>
  </tr>
  <tr>
    <td>flag_active</td><td>Boolean</td><td>Boolean value to indicate if the user is active or inactive. Inactive users cannot login to MobyDQ (WIP).</td>
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
</table>


---


# User Group
User groups define a set of users who can access a common set of indicators and data sources. The user group concept is used to manage row level security on the data which means users can only see the records which belongs to their groups. When a user group is created in the `user_group` table, a new user group role `user_group_<id>` is created in the `pg_roles` table.

**Table:** `user_group`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the user, used as a primary key.</td>
  </tr>
  <tr>
    <td>name</td><td>Text</td><td>Name of the user group, must be unique.</td>
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
</table>


---


# User Group User
The table `user_group_user` is used to managed the assignment of users to user groups. When a user is associated to a user group in the `user_group_user` table, the user group role `user_group_<id>` is automatically granted to the `user_<id>` role in the `pg_roles` table.

**Table:** `user_group`<br/>
<table>
  <tr>
    <th>Attribute</th><th>Type</th><th>Description</th>
  </tr>
  <tr>
    <td>id</td><td>Integer</td><td>Unique identifier of the user, used as a primary key.</td>
  </tr>
  <tr>
    <td>created_date</td><td>Timestamp</td><td>Record created date.</td>
  </tr>
  <tr>
    <td>created_by_id</td><td>Integer</td><td>Foreign key of the user table, to indicate which user created the record.</td>
  </tr>
  <tr>
    <td>user_group_id</td><td>Integer</td><td>Foreign key of the user_group table, to indicate to which user group the user belongs to.</td>
  </tr>
  <tr>
    <td>user_id</td><td>Integer</td><td>Foreign key of the user table, to indicate to which user is assigned to the user group.</td>
  </tr>
</table>
