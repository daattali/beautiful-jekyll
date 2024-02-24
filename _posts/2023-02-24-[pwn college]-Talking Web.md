---
layout: post
title: pwn college Intro to Cybersecurity - Talking Web
# subtitle: How to Read Sensitive Files with SUID bit on the Commands and How to Escalate Privilege
# cover-img: /assets/img/banditlogo.png
# thumbnail-img: /assets/img/overthewire.jpeg
# share-img: /assets/img/path.jpg
tags: [web, security, www, pwn, college]
comments: true
author: Lantana Park
---

Introduction

## World Wide Web (WWW)

- The World Wide Web (WWW) is **a vast network of interconnected documents and other resources**, linked by hyperlinks and URLs. It operates over the Internet, a global network of networks, providing access to a wealth of information through web browsers.
- The WWW is not the Internet itself but a service that uses the Internet to enable data and information to be distributed and accessed. It is one of the many services available on the Internet.
- The WWW is based on three fundamental technologies: HTML (HyperText Markup Language), which defines the structure and layout of web pages; URI (Uniform Resource Identifier), which provides addresses for resources on the web; and HTTP (HyperText Transfer Protocol), which is the protocol for transferring web content.

## HTTP (HyperText Transfer Protocol)

- HTTP is a **protocol** used for transmitting web pages and other content over the Internet. It is the foundation of any data exchange on the Web and a client-server protocol, which means requests are initiated by the recipient, usually the web browser.
- It is a **universal and standardized system** that enables the communication between clients (users' web browsers) and servers (where web pages are hosted), allowing for the fetching of resources such as HTML documents.
- HTTP operates through a request-response model, where the client sends an HTTP request message to the server, which then returns an HTTP response, containing the requested content or a status code indicating the outcome of the request.

![first www](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2020.56.43.png)

## Static HTTP Request / Dynamic HTTP Request

- Static HTTP request return a fixed and unchanging resouces. This can be an HTML file, an image or a stylesheet.

- Dynamic HTTP request is processed by the server in a way that allows it to generate a tailored response based on the request's parameters, user session data, or inputs. The content returned by a dynamic request can change with each request, providing personalized content for the user.

## The Internet

- The Internet serves as the infrastructure upon which the World Wide Web (WWW) operates. It facilitates the transmission of data necessary for accessing web content and services.

- This is a distributed system and it can be network of networks

- The Internet itself is structured in several layers of abstraction, each responsible for different aspects of data transmission and communication.

![layers of internet](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2021.33.41.png)

- Link layer(bottom): it is some physical connection between computers, transmitting data. (Ethernet cables, fiber optics, and wireless technologies, including satellite)
- Internet layer: This layer is crucial for routing data packets across networks to ensure they reach the correct destination. It uses the Internet Protocol (IP) to assign addresses to each device and to find the optimal path for data to travel between the source and destination. This layer is what allows the Internet to be a fluid and interconnected system, capable of routing data across the globe.
- Transport layer: The transport layer is responsible for delivering data to the appropriate application on a target device. It introduces the concept of ports, which function as endpoints to which data can be sent or from which it can be received. Protocols like TCP (Transmission Control Protocol) and UDP (User Datagram Protocol) operate at this layer, managing the reliability, order, and integrity of the data packets as they are transported.
- Application layer(top): This layer interacts directly with the software applications that users operate. It defines the protocols and communication methods that applications use to exchange data over the network. Common protocols at this layer include HTTP (HyperText Transfer Protocol) for web browsing, FTP (File Transfer Protocol) for file transfers, SSH (Secure Shell) for secure remote access, and SMTP (Simple Mail Transfer Protocol) for email transmission.

## RFC1945

- RFC 1945 officially defines HTTP/1.0, which is an early version of the Hypertext Transfer Protocol (HTTP).

![request](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.23.26.png)
![respond](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.23.39.png)

![status1](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.23.56.png)
![status2](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.24.04.png)

### Simple HTTP Request Methods

`GET` - retrieve information identified by the Request-URI.
![getrequest](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.25.12.png)
![getrespond](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.24.31.png)

`HEAD` - is identical to GET in every way, except that the server must not return a message body in the response.
![headrequest](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.24.38.png)
![headrespond](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.24.46.png)

`POST` - s used to submit an entity to the specified resource, often causing a change in state or side effects on the server.
![postrequest](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.24.54.png)
![postrespond](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.25.00.png)

## URLs and encoding

What is URL

- It is composed of a number of things.
  ![HTTPscheme](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.39.49.png)



  State
  HTTP is stateless protocol.

solution: use HTTP headers for maintaining state
http cookies
