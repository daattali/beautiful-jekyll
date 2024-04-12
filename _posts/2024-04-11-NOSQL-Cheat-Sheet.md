---
layout: post
title: NOSQL assessment cheat sheet
subtitle: Let's getting prepared to NOSQL database (particularly MongoDB)
# cover-img: /assets/img/banditlogo.png
# thumbnail-img: /assets/img/crypto/crypto.png
# share-img: /assets/img/path.jpg
tags: [Nosql, database, assessment]
comments: true
author: Lantana Park
---

# The concepts, characteristics and significance of NoSQL

- It was developed from open-source project to deal with limitation of SQL database

- It provides a free schema structure and are easily scalable.

- It is suited for hierarchical data storage.

# Different type of Nosql database and its advantages and disadvantages

1. Document data

   Data and metadata are stored hirearchically in JSON-based documents inside the database. **MongoDB**

   ![document-based](/assets/img/mongodb/MongoDB%20document%20based.png)

2. Key Value data

   data is represented as a collection of key-value pairs. **Redis**

   ![keyandvalue](/assets/img/mongodb/key-value.png)

   ### Difference between docuemtn based data and key value data

   Document databased store data in Json document, which allows for a complex structure compared to the simple key-value pairs. Each document can contain nested/embeded structure like arrays and sub-documents.

3. Wide-Column data

   A wide-column stores data in tables, where the names and formats of individual attributes can vary from row to row. **Apache Cassandra**

   ![column](/assets/img/mongodb/Wide-column-Database.webp)

4. Graph data

   Graph is stored in a graph structure as node, edge, and data properties. **Noe4j**

   ![neo4j](/assets/img/mongodb/Neo4j-graph.png)

# The advantages and disadvantages of NoSQL compared to relational databases

## advantages of Nosql

1.  **Scalability (Horizontal)**

    NoSQL, especially MongoDB, designed for horizontal scalability. That means NoSQL database like MongoDB can handle large volumes of data by distributing it across multiple servers (sharding). That makes it easier to scale out (horizontal scaling). Thus, since it provides horizontal scalability, it allows me to use of **cheaper** and standard machines and can be more cost-efficient at scale.

2.  **Schema flexibility**

    NoSQL, especially MongoDB, provides flexible schema model. Which allows me to easily add or remove data fields without modifying the exsting database schema to affecting other data records. So records in the same collection can have different structures

3.  **Fast queries(fast reading)**

    Queries in Nosql database can be faster than SQL database. Since Data in SQL database is typically normalized, so queries for a single object or entity require to join data from multiple tables. So it takes costs when the tables are growing. However, data in Nosql databases should be access and stored together(denormalized). So queries typically do not require joins, so **the queries are very fast and readings are very fast.**

## The disadvantages of NoSQL

1. No standarized language and interface to complex queries

   There is no standarized query languages to conduct complex queries.

2. Data retrieval inconsistency

   NoSQL databases prioritize speed and availability due to their distributed nature, which can lead to inconsistencies in data retrieval. This occurs because data might not be updated simultaneously across all servers, resulting in different responses based on the server accessed.

   Unlike traditional databases that follow ACID principles (Atomicity, Consistency, Isolation, Durability) to ensure data integrity, NoSQL databases often do not meet the consistency requirement. This means they might not provide the same data consistency as seen in ACID-compliant databases.

   Instead of ACID, many NoSQL databases use the BASE (Basically Available, Soft state, Eventual consistency) model. Here, consistency is achieved eventually, meaning that while immediate consistency is not guaranteed, the data will become consistent after a short delay, which is generally acceptable in many real-world applications like social media or online shopping.

# CAP theorem and its implications for selecting a NoSQL database

distrubution is important in Nosql because of its characteristics. It relys on horizontal scaling out to handle growth. CAP theorem provides fundamental understanding to complexities of distributed system design. It helps in making informed decisions that align with the application's requirements and the system's architectural goals.

![mongoDB](/assets/img/mongodb/CAP_Theorem_Venn_Diagram.png)

- **Consistency**: all clients see the same data at the same time. For making this to fulfill, whenever data is written to one node, it should be instantly forwarded or replicated to all the other nodes in the system. That means all nodes in the system continue to cooperatively provide service, even when nodes become unavailable. Consistency supports modern workloads that are less dependent on a strong consistency, but rely heavily on availability.

- **Availability**: any client making a request for data gets a response, even if one or more nodes are down. That means all working nodes in the distributed system return a valid response for any request, without exception.

- **Partition tolerance**: it is a communications break within a distributed system—a lost or temporarily delayed connection between two nodes. Partition tolerance means that the cluster must continue to work despite any number of communication breakdowns between nodes in the system.

**a distributed database system can only fully satisfy two out of the three gaurantess**

- CP database: it delivers **consistency** and **partition tolerance** at the expense of availability. When a partition occurs between any two nodes, **the system has to shut down the non-consistent node until the partition is resolved**.

- AP database: it delivers **availability** and **partition tolerance** at the expense of consistency. When a partition occurs, all nodes remain available but those at the wrong end of a partition might **return an older version of data than others**.

- CA database: it delivers **consistency** and **availability** across all nodes. It can’t do this if there is a partition between any two nodes in the system, however, and therefore **can’t deliver fault tolerance**.

## MongoDB and the CAP theorem

MongoDB is classified as a **CP** data store. Because it resolves network partitions by maintaining consistency, while compromising on availability.

MongoDB uses the single master node that receives all write operations. The primary node is the source of truth for all data writes. When the primary node becomes unavailable, the secondary node, replicated from the primary node(Consistency), will be elected as the new primary node.

# Optimize the respective data structure for huge amounts of data, performance and efficiency in Nosql

It involves serveral strategies tailored to the specific type of Nosql database.

