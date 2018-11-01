---
layout: page
title: Roles & Permissions
use-site-title: true
---

In progress

# Roles & Permissions
Roles and permissions are managed using the internal PostgreSQL role concepts.

<p>There are 2 main roles defined for users:</p>
<table>
  <tr>
    <th>Role</th>
    <th>Description</th>
    <th>Naming</th>
  </tr>
  <tr>
    <td>Superadmin</td>
    <td>
      All rights on all tables</br>
      Rights granted on all user groups
    </td>
    <td>super_admin</td>
  </tr>
  <tr>
    <td>User</td>
    <td>
      Full rights on indicator, indicator_group and parameter</br>
      Select rights on data_source, data_source_type, parameter_type, indicator_type, batch, session, session_result</br>
      Rights granted on specific user groups
    </td>
    <td>"user_group_" + user_group_name</td>
  </tr>
  <tr>
    <td>Admin</td>
    <td>
      Same as User, but additional update right on data_source</br>
      Rights granted on specific user groups
    </td>
    <td>"user_group_" + user_group_name + "_admin"</td>
  </tr>
</table>


---


# Row Level Security
