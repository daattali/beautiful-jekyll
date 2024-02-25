---
layout: post
title: pwn college Intro to Cybersecurity - Talking Web (class)
# subtitle: How to Read Sensitive Files with SUID bit on the Commands and How to Escalate Privilege
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/pwnCollege.jpeg
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

What is URI (Uniform Resource Identifier)

- The primary purpose of a URI is to identify a resource either by location, or a name, or both `https://www.example.com/page.html` is a URI that is also a URL because it locates a resource on the internet. `urn:isbn:0451450523` is a URI that is a URN, which names a resource (in this case, the book with the `ISBN 0451450523`) without specifying its location.

### What is URL (Uniform Resource Locator)

- A URL is to provide the address of a resource on the web, making it accessible via the internet.
  ![HTTPscheme](/assets/img/talkingWeb/Screenshot%202024-02-24%20at%2022.39.49.png)

### Encoding in URLs

- Encoding within URLs is crucial due to the limitations in the characters that can be safely used in URLs and HTTP requests. Characters such as spaces and certain symbols have special meanings or are not allowed in URLs. To include these characters, they must be percent-encoded. This process involves replacing the character with a percent sign % followed by two hexadecimal digits representing the character's ASCII code. For example, a space is encoded as %20.

- This encoding ensures that the server can correctly parse the HTTP request and the URL, avoiding misunderstandings caused by special characters. For instance, in an HTTP request, spaces and other disallowed characters in URLs are replaced with their percent-encoded equivalents to maintain the integrity of the request.

![hex](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2009.22.52.png)

![encodedrequest](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2009.23.02.png)

### Content Type

- In HTTP requests, the Content-Type header is crucial as it tells the server the type of data the client is sending.

#### Content-Type: application/x-www-form-urlencoded

- This content type is used when submitting simple data forms. Data sent with this content type is encoded as key-value pairs, similar to query parameters in the URL.
  Content-Type: application/json

![urlencoded](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2009.22.52.png)

#### Content-Type: application/json

- It is indicating that the body of my HTTP request is formatted as a JSON string. JSON (JavaScript Object Notation) is a lightweight data-interchange format that is easy for humans to read and write and easy for machines to parse and generate. It is often used in RESTful APIs for communicating complex structures because it can easily represent objects and arrays.

![json](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2009.23.02.png)

## State in the HTTP request

- The HTTP protocol is inherently stateless, meaning that it does not inherently remember or track the state of the communication between a client and a server. This characteristic implies that, without additional mechanisms, the server cannot recognize if a client has previously logged in or performed any other action that alters their interaction state.

### solution for maintaing state

#### using HTTP headers for maintaining state

- One common solution to overcome the statelessness of HTTP is the use of cookies.

1. Setting a Cookie: The server initiates state management by sending a `Set-Cookie` header in its response. This header contains the cookie data that the client's browser should store.

![basiccookie1](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2010.17.06.png)
![basiccookie2](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2010.17.13.png)

2. Sending the Cookie: On subsequent requests to the same server, the client’s browser automatically includes the cookie with the `Cookie` header, thus informing the server of the client's previous interactions.

![authcookie1](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2010.17.36.png)
![authcookie2](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2010.17.45.png)

### Session IDs for Enhanced Security

- To further secure the communication and ensure that session identifiers (like cookies) are not easily hijacked or guessed by malicious actors, it's important to use secure, hard-to-guess session IDs.

![session1](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2010.23.16.png)
![session2](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2010.23.24.png)
![session3](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2010.23.31.png)
![session4](/assets/img/talkingWeb/Screenshot%202024-02-25%20at%2010.23.37.png)
