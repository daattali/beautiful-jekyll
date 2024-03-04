---
layout: post
title: Database designathon
subtitle: Practice for making data modeling
cover-img: /assets/img/blackboard.jpeg
thumbnail-img: /assets/img/designathon/coverdesginathon.png
# share-img: /assets/img/path.jpg
tags: [database, desginthon, database, modeling, conceptual modeling]
comments: true
author: Lantana Park
---

## 1. Soccer team

![seccer team](/assets/img/designathon/mermaid-diagram-2024-02-26-102446.png)

```bash
erDiagram
    PLAYER ||--|| TEAM : "belong"
    TEAM ||--o{ PLAYERS : "has many"
    MATCHES }o--o{ TEAM : "participate"
    MATCHES ||--o{ PLAYERS : "have many"
```

- A player belongs a team
- A team participates many matches
- A team has many players
- Players have many matches

## 2. The companyDB

![company](/assets/img/designathon/mermaid-diagram-2024-03-04-094749.png)

```bash
erDiagram
    COMPANY ||--o{ EMPLOYEE : "has many"
    COMPANY ||--o{ PROJECT : "has many"
    COMPANY {
        string CompanyID PK
        string Name
        number Zip
        string Country
        string Address1
        string State
        number Employed_staff_number

    }
    EMPLOYEE ||--o{ PROJECT : "involved in many"
    EMPLOYEE {
        string EmployeeID PK
        string ProjectMangerID
        string Name
        string role
        string Team
    }
    PROJECT ||--o{ EMPLOYEE : "has many"
    PROJECT {
        string ProjectID PK
        string ProjectName
        string EmployeeID FK
        string Location
        string Budget
    }
    EMPLOYEE ||--|| MANAGER : "reports to"
    MANAGER {
          string ManagerID PK
          string EmployeeID FK
    }
    EMPLOYEE ||--|{ PROJECT : "manages"
```

1. COMPANY: This entity represents a company. It has attributes such as CompanyID (Primary Key), Name, Zip, Country, Address1, State, and Employed_staff_number.

2. EMPLOYEE: This entity represents an employee. It has attributes like EmployeeID (Primary Key), ProjectManagerID, Name, Role, and Team. An employee "has many" projects.

3. PROJECT: This entity represents a project. It has attributes such as ProjectID (Primary Key), ProjectName, EmployeeID (Foreign Key), Location, and Budget. A project "has many" employees involved in it.

4. MANAGER: This entity represents a manager. It has attributes like ManagerID (Primary Key) and EmployeeID (Foreign Key). An employee "reports to" a manager.
