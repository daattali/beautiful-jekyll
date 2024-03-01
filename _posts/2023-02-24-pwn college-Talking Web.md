---
layout: post
title: pwn college Intro to Cybersecurity - Talking Web (class)
subtitle: Sending HTTP requests using nc and curl
cover-img: /assets/img/pwnCollege.jpeg
thumbnail-img: /assets/img/pwnCollege.jpeg
# share-img: /assets/img/path.jpg
tags: [web, security, www, pwn, college]
comments: true
author: Lantana Park
---

# Introduction

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

In summary, (after solving the dojos)

- **For simplicity and direct HTTP/HTTPS interactions**: `curl` is the go-to tool due to its ease of use and extensive feature set for web protocols.
- **For low-level network interactions**: `nc` is useful, though not specifically designed for HTTP, it shines in custom or educational networking scenarios.
- **For programming and automation within larger applications**: `Python` (especially with libraries like requests) offers the most flexibility and power, allowing for sophisticated request handling, data processing, and integration into applications or data pipelines.

Level 1 - Send an HTTP request using curl

Answer: pwn.college{sF9Oa9stL-78VlBWpBns1Z1p7bT.dhjNyMDL0MjM3QzW}

`curl` allows data transfer to ro from a server and it is designed to work without user interaction.

```bash
curl http://localhost:80
```

Level 2 - Send an HTTP request using nc

Answer: pwn.college{Ius0FneVO0ONejUoCiJ4e2CL--O.dljNyMDL0MjM3QzW}

`nc` can be used to establish a simple network connection.

```bash
printf "GET / HTTP/1.0\r\n\r\n" | nc localhost 80
```

Level 3 - Send an HTTP request using python

Answer: pwn.college{0qZDIIurK5i34hcDLH9VIFztKG9.dBzNyMDL0MjM3QzW}

I made a file \_ password.py, and input this script to print the response.text

```bash
import requests
# First, I need to make sure if requests library is installed

url = 'http://localhost:80'
# second, I need to input the url that I want to make a request to

response = requests.get(url)
# third, I am making a GET reqeust

print(response.text)
# Print the response
```

And then

```bash
python password.py
# Executing the file
```

Level 4 - Set the host header in an HTTP request using curl

Answer: pwn.college{EYe66lsgLvadoXImXYNocZI8FgE.dFzNyMDL0MjM3QzW}

`curl -h` command is used to display information about the HTTP headers in a request or response.

```bash
curl -H "Host: 18870d24d0ea39d48596c23222ca9251" http://localhost:80
```

I could know about the host name by this process. This value has been changed over the quests. I want to know how to get the value beforehand...

```bash
hacker@talking-weblevel4:$ curl -H "User-Agent:admin" http://localhost:80
Incorrect host: value localhost, should be 18870d24d0ea39d48596c23222ca9251
```

Level 5 - Set the host header in an HTTP request using nc

Answer: pwn.college{cDghuH-Opdkyofiiv1zj0H-QjUY.dJzNyMDL0MjM3QzW}

```bash
hacker@talking-weblevel5:$ nc localhost 80
GET / HTTP/1.1
Host: 9f74083f3fff6de9d7642f65073b47ba
Connection:close
# And twice enter to make sure the request
```

Level 6 - Set the host header in an HTTP request using python

Answer: pwn.college{48RdtN--DAM2_Nw9sPIIMG4t_Rm.dNzNyMDL0MjM3QzW}

1. I revised the password.py to set the host header

```bash
import requests

url = 'http://localhost:80'
headers = {"Host":"c1ea0a2936bbbf142aa34cc19a03f4c3"}


response = requests.get(url, headers=headers)

print(response.text)
```

2. And the run the python file

```bash
python password.py
```

Level 7 - Set the path in an HTTP request using curl

Answer: pwn.college{0woYeC-dLbfeVHcluF1SZ-Z8YNh.dRzNyMDL0MjM3QzW}

```bash
curl http://localhost:80/0d03ee73b35284664fc7011ac1943c63
```

Level 8 - Set the path in an HTTP request using nc

Answer: pwn.college{sHyWXhM2iQJZpxtzhT-7FalInGE.dVzNyMDL0MjM3QzW}

```bash
nc localhost 80

GET /00b14d85e680a2d0d14e8e79298011af HTTP/1.0
Host: pwn.college

HTTP/1.1 200 OK
Server: Werkzeug/3.0.1 Python/3.8.10
Date: Tue, 27 Feb 2024 08:59:20 GMT
Content-Length: 58
Server: pwn.college
Connection: close
```

Level 9 - Set the path in an HTTP request using python

Answer: pwn.college{QMewxOSkIc0\_\_\_G1rc2vmFs83re.dZzNyMDL0MjM3QzW}

In the python script,

```bash
import requests

url = 'http://localhost:80/f92e810f03ce1e7772fa138748b595d8'

headers = {"Host":"pwn.college"}

response = requests.get(url, headers=headers)

print(response.text)
```

```bash
python password.py
```

Level 10 - URL encode a path in an HTTP request using curl

Answer: pwn.college{ICTwKToaWyu9Ya6j9uVahOGyU33.ddzNyMDL0MjM3QzW}

```bash
curl "http://localhost:80/fe805947%209c8d33ec/2c2fd66c%20fcce0b09"
```

Level 11 - URL encode a path in an HTTP request using nc

Answer: pwn.college{QAtBVzTgsdMDs8uiqsq4y8lxrYj.dhzNyMDL0MjM3QzW}

```bash
nc localhost 80

GET /2641977c%20473c3a5f/4381b7b6%20c0adb5bf HTTP/1.1

HTTP/1.1 200 OK
Server: Werkzeug/3.0.1 Python/3.8.10
Date: Tue, 27 Feb 2024 09:48:07 GMT
Content-Length: 58
Server: pwn.college
Connection: close
```

Level 12 - URL encode a path in an HTTP request using python

Answer: pwn.college{gpAQlgO1ouZb7T_piqZxgNXWncG.dlzNyMDL0MjM3QzW}

In the python script,

```bash
import requests

url = 'http://localhost:80/aacc060a%20cd9077b4/fc46353e%208561b879'

headers = {"Host":"pwn.college"}

response = requests.get(url, headers=headers)

print(response.text)
```

```bash
python password.py
```

Level 13 - Specify an argument in an HTTP request using curl

Answer: pwn.college{8AGJOnqazr4TgNWC1I6DGar9n_c.dBDOyMDL0MjM3QzW}

`-G` tells `curl` to send the data specified with the `-d` option in the URL's query string. `-d` specifies the data to be sent with the request. In order to send arguments in the query string of a GET request, combining `-G` with `-d` is necessary.

```bash
curl -G -d'a=f83adfc329b071d0f9a2909758f8caf8' http://localhost:80
```

Level 14 - Specify an argument in an HTTP request using nc

Answer: pwn.college{QjGW5sTSXTN7OnbXWO_0IMIR4l9.dFDOyMDL0MjM3QzW}

```bash
nc localhost 80

GET /?a=004699053d33b5ac054e70f3c8236621 HTTP/1.1
Host: pwn.college

HTTP/1.1 200 OK
Server: Werkzeug/3.0.1 Python/3.8.10
Date: Tue, 27 Feb 2024 15:27:10 GMT
Content-Length: 58
Server: pwn.college
Connection: close
```

Level 15 - Specify an argument in an HTTP request using python

Answer: pwn.college{M172kHnaNc8eiYCEk2Om3lPcpRx.dJDOyMDL0MjM3QzW}

In the python script,

```bash
import requests

url = 'http://localhost:80/?a=bb9701210ad49e697a3abe5344782ace'

headers = {"Host":"pwn.college"}

response = requests.get(url, headers=headers)

print(response.text)
```

```bash
python password.py
```

Level 16 - Specify multiple arguments in an HTTP request using curl

Answer: pwn.college{80WJwGjNmqFelLUcQmU5-OY9zrb.dNDOyMDL0MjM3QzW}

`curl -d` allows users to send the POST request. This option is used when I want to make submit form data or make a POST request to a web server.

```bash
curl -G -d'a=7e2ba0ce4f17f9bcfd4a0a0df7b67ddb' -d 'b=80d0fb21%20f50d2be7%26079486a0%23807223ff' http://localhost:80
```

Level 17 - Specify multiple arguments in an HTTP request using nc

Answer: pwn.college{USWHwf0zOF3gWc4cEfUWxYiJbS-.dRDOyMDL0MjM3QzW}

```bash
nc localhost 80

GET /?a=bf7c80ab95cf875ca77990b868f50fc3&b=410b771e%20c27f8533%26e39f3a1a%2357d327cf HTTP/1.1
Host: pwn.college
```

Level 18 - Specify multiple arguments in an HTTP request using python

Answer: pwn.college{kCUaYjqVxauC1hjQ8hwd1qkdciG.dVDOyMDL0MjM3QzW}

In the python, still I need to know how I can know the argument key beforehead. Because, after having error, I am getting the proper argument values.

```bash
import requests

url = 'http://localhost:80/?a=c98f25f0613252265f0f0ac8352466c9&b=ffd1fbbd%2011485d1c%265a5b6b3e%23b4e28b4f'

headers = {"Host":"pwn.college"}
```

```bash
python password.py
```

Level 19 - Include form data in an HTTP request using curl

Answer: pwn.college{UQRKdiPciCArkTaJ-\_nzFtNweSO.dZDOyMDL0MjM3QzW}

`curl -F` allows me to interact with the web forms that require complex data or files. It is typically a POST request that submits form data, specifically `multipart/form-data` which is often used for file uploads but can be used for any form data.

```bash
curl -F a=61c6252329f744855af0785f27072c61 http://localhost:80
```

Level 20 - Include form data in an HTTP request using nc

Answer: pwn.college{U6nr9yNlv7GXeRyiOR-lawNHIfN.ddDOyMDL0MjM3QzW}

In the content content length, I should include the length of `a=`. So it should be 34. Due to that, I got many request error messages.

By default, `echo` outputs its arguments to standard output without modification. When `-e` is used, it interprets backslash-escaped characters in the arguments.

`\n` for a newline
`\t` for a tab
`\r` for a carriage return

```bash
echo -e "POST / HTTP/1.1\r\nHost: 127.0.0.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 34\r\n\r\na=5d75e8b6d224cfc0e9ff76897c1f5ea0" | nc localhost 80
```

Level 21 - Include form data in an HTTP request using python

Answer: pwn.college{sLNc7olxe02Da3bj8bggUCjZBTE.dhDOyMDL0MjM3QzW}

In the python script,

```bash
import requests

url = 'http://localhost:80'

form_data = {'a': 'd3eca9842d7c55eda0c15eb31c980dee'}

response = requests.post(url, data=form_data)
```

And then

```bash
python password.py
```

Level 22 - Include form data with multiple fields in an HTTP request using curl

I set `''` in the `b` value because it should be transmitted as a string. If I want to delete `''`, I need to encode the url.

Answer: pwn.college{oloebTWo_1BdDZ_vyUVLnw5MVSP.dlDOyMDL0MjM3QzW}

```bash
curl -F a=b7faa3a289b8ca44f0c637173d888229 -F b='c1f3aede 2ddc2692&0f1959ef#1025ccb6' http://localhost:80
```

Level 23 - Include form data with multiple fields in an HTTP request using nc

Answer: pwn.college{svPiyEzOPq4XxyJn3_YC9qTKPUb.dBTOyMDL0MjM3QzW}

```bash
echo -e 'POST / HTTP/1.1\r\nHost: 127.0.0.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 78\r\n\r\na=34b9e8db82feb5cb73e0f376bf0056e7&b=760da8be%20f606ec84%266c2e1f05%23842bf776' | nc 127.0.0.1 80

HTTP/1.1 200 OK
Server: Werkzeug/3.0.1 Python/3.8.10
Date: Thu, 29 Feb 2024 09:26:57 GMT
Content-Length: 58
Server: pwn.college
Connection: close
```

Level 24 - Include form data with multiple fields in an HTTP request using python

Answer: pwn.college{gA2rft2lExO6AteejzHsWDu9r56.dFTOyMDL0MjM3QzW}

```bash
import requests

url = 'http://localhost:80'

form_data = {
        'a': '99dbc6ff6ad5d852d239f17106948c5e',
        'b': '56cf540b 559ea0b9&83033239#5ca77e82'}

response = requests.post(url, data=form_data)

print(response.text)
```

```bash
python password.py
```

Level 25 - Include json data in an HTTP request using curl

Answer: pwn.college{MksPhQxpAWT6RyCTGBgYwBInBCy.dJTOyMDL0MjM3QzW}

In this command I set the application/json as content-type.

```bash
curl -X POST -H "Content-Type: application/json" -d '{"a": "64194cf6b2140c8ae8f4f51263cc702a"}' http://127.0.0.1:80
```

Level 26 - Include json data in an HTTP request using nc

Answer: pwn.college{Y0h1OcDY10P1kQOIppst2d2WF1q.dNTOyMDL0MjM3QzW}

```bash
echo -e "POST / HTTP/1.1\r\nHost: localhost\r\nContent-Type: application/json\r\nContent-Length: $(echo -n '{"a": "425c8817be2901a7ef9e58e371d6dcf4"}' | wc -c)\r\n\r\n{\"a\": \"425c8817be2901a7ef9e58e371d6dcf4\"}" | nc localhost 80

HTTP/1.1 200 OK
Server: Werkzeug/3.0.1 Python/3.8.10
Date: Thu, 29 Feb 2024 09:51:50 GMT
Content-Length: 58
Server: pwn.college
Connection: close
```

Level 27 - Include json data in an HTTP request using python

Answer: pwn.college{s5eZ_YvEkSHLmaggh7vU6xPespg.dRTOyMDL0MjM3QzW}

In the python script,

```bash
import requests
import json

url = 'http://localhost:80'

headers = {
        'Content-Type': 'application/json'}

data = {
        'a': 'c8dc31316eb08bd197cc36a6cca58e64'}

response = requests.post(url, headers=headers, json=data)

print(response.text)
```

```bash
python password.py
```

Level 28 - Include complex json data in an HTTP request using curl

Answer: pwn.college{UlADu70-J-Mtjqzb74nToeUvmgK.dVTOyMDL0MjM3QzW}

```bash
curl -X POST -H "Content-Type: application/json" -d '{"a": "e66a8e8b496bcf6844192de6235a2f6c", "b": {"c": "e24744e3", "d": ["3d7c54ca", "799690c7 dc8c9f88&c27473d7#ee8dba9a"]}}' http://127.0.0.1:80
```

Level 30 - Include complex json data in an HTTP request using python

Answer: pwn.college{Ec64Er8CbVnN6h57DI7GiU8MFeZ.ddTOyMDL0MjM3QzW}

In the python script,

```bash
import requests
import json

url = 'http://localhost:80'

headers = {
        'Content-Type': 'application/json'}

data = {
        'a': '368740ea70f261538ae7ec115ece14d3',
        'b': {'c': '728c88d8', 'd': ['61ef16c4', 'f6c6a682 b867b715&5e8372c6#098a04c8']}}

response = requests.post(url, headers=headers, json=data)

print(response.text)
```

```bash
python password.py
```

Level 31 - Follow an HTTP redirect from HTTP response using curl

Answer: pwn.college{k2vM_zuuL_EQlcTBKbOBoGJFANK.dhTOyMDL0MjM3QzW}

`-L` tells `curl` to follow any redirects.

```bash
curl -L http://localhost:80
```

Level 32 - Follow an HTTP redirect from HTTP response using nc

Answer: pwn.college{wGa6qiYynjNN13FBajPuCU_BuRT.dlTOyMDL0MjM3QzW}

```bash
echo -e "GET /d2d1b4f4fe80b991df81fa547365e9ab HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n" | nc 127.0.0.1 80
```

Level 33 - Follow an HTTP redirect from HTTP response using python

Answer: pwn.college{s89JjbXIvdW0notLs6Ph2xHeg63.dBDMzMDL0MjM3QzW}

In python script,

```bash
import requests

url = 'http://localhost:80'

response = requests.get(url)

print(response.text)
print(response.url)
print(response.status_code)
```

```bash
python password.py
```

Level 34 - Include a cookie from HTTP response using curl

Answer: pwn.college{oruIxp4lB1cj5sj_ANXt-XwH3tN.dFDMzMDL0MjM3QzW}

`-v` stands for "verbose". When used, `curl` will provide additional details about the request and reponse process.
`--cookie` allows me to send a cookie with the request.

```bash
curl -v --cookie "cookie=7db39f47473ac8cd4c34a07f49c7861b" http://localhost:80
```

Level 35 - Include a cookie from HTTP response using nc

Answer: pwn.college{c2e9nK_s7qWM1_Gn5DM3VAohghl.dJDMzMDL0MjM3QzW}

In this command, I made/saved the response in response.txt.

```bash
echo -e "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n" | nc 127.0.0.1 80 > response.txt

cat response.txt

HTTP/1.1 302 FOUND
Server: Werkzeug/3.0.1 Python/3.8.10
Date: Fri, 01 Mar 2024 08:51:48 GMT
Content-Length: 189
Location: /
Set-Cookie: cookie=4cdc8da9406b7d70d39edd6a230a8f1b; Path=/
Server: pwn.college
Connection: close

<!doctype html>
<html lang=en>
<title>Redirecting...</title>
<h1>Redirecting...</h1>
<p>You should be redirected automatically to the target URL: <a href="/">/</a>. If not, click the link.

nc localhost 80
GET / HTTP/1.1
Host: 127.0.0.1
Cookie: cookie=4cdc8da9406b7d70d39edd6a230a8f1b
Connection: close

HTTP/1.1 200 OK
Server: Werkzeug/3.0.1 Python/3.8.10
Date: Fri, 01 Mar 2024 08:54:27 GMT
Content-Length: 58
Server: pwn.college
Connection: close
```

Level 36 - Include a cookie from HTTP response using python

Answer: pwn.college{s8Jr6pQ9FocXcxD0NUV0hvK2hdW.dNDMzMDL0MjM3QzW}

In the python script,

```bash
import requests

url = 'http://localhost:80'

response = requests.get(url)

cookies = response.cookies

print(cookies)

print(response.text)
print(response.url)
print(response.status_code)
```

```bash
python password.py
```

Level 37 - Make multiple requests in response to stateful HTTP responses using curl

Answer: pwn.college{Uo4BatEKm20JfYpBf_KzJK_0r0U.dRDMzMDL0MjM3QzW}

Initially, `cookies.txt` can be empty or contain the initial session cookie. `curl` will update `cookies.txt` with new cookies from responses and use them in subsequent requests as it follows redirects.

```bash
curl -v --cookie "session=eyJzdGF0ZSI6MX0.ZeGcog.fmzIQCWo1dMYwZS2gbSitec_8Ok" http://localhost:80

Trying 127.0.0.1:80...
TCP_NODELAY set
Connected to localhost (127.0.0.1) port 80 (#0)
> GET / HTTP/1.1
> Host: localhost
> User-Agent: curl/7.68.0
> Accept: /
> Cookie: session=eyJzdGF0ZSI6Mn0.ZeGdSA.xv03oCAPPiTE06-q8_ffZicWlsY
>
Mark bundle as not supporting multiuse
< HTTP/1.1 302 FOUND
< Server: Werkzeug/3.0.1 Python/3.8.10
< Date: Fri, 01 Mar 2024 14:16:29 GMT
< Content-Length: 9
< Location: /
< Server: pwn.college
< Vary: Cookie
< Set-Cookie: session=eyJzdGF0ZSI6M30.ZeHjPQ.fIYV9kKFlY0QGELiP4Lz_WgfgsA; HttpOnly; Path=/
< Connection: close
<
state: 2
# It shows the progression of the session
Closing connection 0

curl -v -L -c cookies.txt -b cookies.txt http://localhost:80
# I used `-L` option in `curl` to follow the redirects and `-b`(to read cookies from a file)/`-c`(to save cookies to a file) to handle cookies automatically.

Trying 127.0.0.1:80...
TCP_NODELAY set
Connected to localhost (127.0.0.1) port 80 (#0)
> GET / HTTP/1.1
> Host: localhost
> User-Agent: curl/7.68.0
> Accept: /
> Cookie: session=eyJzdGF0ZSI6NH0.ZeGdlg.UxH1HyiEOENvasKxuDvJxxQFEQU
>
Mark bundle as not supporting multiuse
< HTTP/1.1 200 OK
< Server: Werkzeug/3.0.1 Python/3.8.10
< Date: Fri, 01 Mar 2024 14:16:41 GMT
< Content-Length: 58
< Server: pwn.college
< Vary: Cookie
Replaced cookie session="eyJzdGF0ZSI6NX0.ZeHjSQ.bpV7lHedxDsoTRwb7jEuz-jh0D4" for domain localhost, path /, expire 0
< Set-Cookie: session=eyJzdGF0ZSI6NX0.ZeHjSQ.bpV7lHedxDsoTRwb7jEuz-jh0D4; HttpOnly; Path=/
< Connection: close
<
pwn.college{Uo4BatEKm20JfYpBf_KzJK_0r0U.dRDMzMDL0MjM3QzW}
Closing connection 0
```

Level 38 - Make multiple requests in response to stateful HTTP responses using nc

Answer: pwn.college{8AdjSf5opJ7TUJhxB6ZIjJYfNXY.dVDMzMDL0MjM3QzW}

```bash
nc localhost 80

GET / HTTP/1.1
Host: localhost
Cookie: session=eyJzdGF0ZSI6M30.ZeGlQA.JYiEYNElFPaPOZ-g3ETDI5pdc74

HTTP/1.1 200 OK
Server: Werkzeug/3.0.1 Python/3.8.10
Date: Fri, 01 Mar 2024 09:54:27 GMT
Content-Length: 58
Server: pwn.college
Vary: Cookie
Set-Cookie: session=eyJzdGF0ZSI6NH0.ZeGl0w.4L9TIn7Vie6chL6tVYgPZIUFOSM; HttpOnly; Path=/
Connection: close
```

Level 39 - Make multiple requests in response to stateful HTTP responses using python

Answer: pwn.college{EW7_SK2K0Ut1BB0ukXcyLjHG7zS.dZDMzMDL0MjM3QzW}

```bash
python password.py
```
