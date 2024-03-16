---
layout: post
title: Tryhackme - SimpleCTF
subtitle: tryhackme simpleCTF walkthrough
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/tryhackme/simpleCTF/logo.png
# share-img: /assets/img/path.jpg
tags: [linux, priviliege escalation, tryhackme, simpleCTF]
comments: true
author: Lantana Park
---

Let's start attacking the IP address `10.10.108.94`.

![ipaddress](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2020.23.35.png)

1. How many services are running under port 1000?

   ![first](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2023.36.40.png)

   Answer: 2

   `nmap -sTU -p 1000 10.10.108.94`

   `nmap -sTU` performs a service version detection scan for both TCP and UDP, and `-p 1000` specifies the port number.

   **What is TCP(Transmission Control Protocol)?**

   - it is a connection-oriented protocol that establishes a two-way communication between hosts. It ensures the delivery of packets in the order they were sent, which is critical for applications where data must be received reliably and in order, such as web pages (HTTP), file transfers (FTP), and email (SMTP).

   **What is UDP(User Datagram Protocol)?**

   - It is a connectionless protocol that sends messages, called datagrams, without establishing a prior connection. This is useful for services that require speed and efficiency over reliability, such as video streaming or online gaming.

2. What is running on the higher port?

   ![portscan](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2020.19.55.png)

   Answer: ssh

   `nmap -sV 10.10.108.94` scans hosts and services with this IP address. `-sV` attempts version detection for each open port found during the scan.

3. What's the CVE you're using against the application?

   Answer: CVE-2019-9053

   Upon scanning the target IP address with `nmap`, a web application is indicated by the presence of an HTTP service. Thus, I visited the website using the IP address in the browser.

   ![website](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-16%20at%2009.36.16.png)

   And then I wanted to find hidden directories of this website. So, I used `gobuster` to find its directories.

   ![finddir](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2020.54.56.png)

   When using tools like `Gobuster` to find hidden directories on a web server, a wordlist is essential because `Gobuster` operates by brute-forcing URLs on the target server. It does not inherently know what directories might exist on the target; instead, it relies on trying a series of potential directory names provided in a wordlist.

   As a result, I could find there are `/index.html` and `robots.txt` with a 200 status and `/simple/` with a 301 status.

   So I visited these pages and found that, on the `/simple` page, it was using `CMS Made Simple version 2.2.8`.

   ![simplepage](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2020.49.46.png)

   ![cms](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2020.49.34.png)

   Let's find what vulnerabilities this CMS version has. I visited the CVE `cve.mitre.org` website to find its weaknesses.

   ![cve](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2020.49.24.png)

   To be honest, I corrected this task by inputting every CVE of `CMS Made Simple version 2.2.8`. Fortunately, I found `CVE-2019-9053` was the correct answer and recognized it has an SQL injection vulnerability.

4. To what kind of vulnerability is the application vulnerable?

   It was really tricky to find the correct answer. Because I knew it has an SQL injection vulnerability, though, it was hard to guess the abbreviation of SQL injection.

   Answer: sqli

   ![sqli](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2021.17.29.png)

   ![gpt](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2021.22.13.png)

5. What's the password?

   Answer: secret

   To find the password, I tried to perform SQL injection. At first, I downloaded the python source code of its vulnerability on the CVE website and then ran the python code with the IP address and wordlist to crack the password.

   ![python](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2020.54.56.png)

   While running the python to perform the SQL injection, I had to edit the python code because I bumped into some errors.

   ![error1](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2022.12.44.png)

   ![error2](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2022.12.55.png)

   Finally, after revising some lines and resolving these errors, I could get the password.

   ![password](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2022.17.47.png)

6. Where can you login with the details obtained?

   Answer: ssh

   Since I knew there was an SSH service running on port `2222`, I tried to log in with SSH and the username.

   In this situation, I got this shell. However, it is not enough to control this system entirely. I had to obtain the root account.

   ![ssh](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2022.25.27.png)

7. What's the user flag?

   Answer: G00d j0b, keep up!

   To solve this task, I checked which directories and files were in it. I found there was a user.txt and attempted to read this text file.

   ![textfilereading](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2022.26.40.png)

8. Is there any other user in the home directory? What's its name?

   Answer: sunbath

   I went to the `home` directory to find something. In the home directory, there were `mitch` and `sunbath` folders.

   ![sunbath](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2022.28.43.png)

9. What can you leverage to spawn a privileged shell?

   Answer: vim

   Sorry, I did not capture the terminal command. I used `sudo -l` to list the permissions granted to the privileged user (or to a specified user) in the sudoers file.

   I could know `/usr/bin/vim`. It indicates that the admin user has sudo privileges to run the Vim text editor with root privileges.

   ![vim](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2022.48.10.png)

10. What's the root flag?

    Answer: W3ll d0n3. You made it!

    To read the flag with the root user id, I had to change the sign from `$` to `#`. I just executed `sudo vim -c ":!/bin/sh"`

    `sudo`: This allows permitted users to execute a command as the superuser or another user, as specified in the sudoers file.

    `vim`: Since root user can run the vim command, I invoked ths `vim` command.

    `-c`: This option allows me to pass a command to Vim that is executed after the first file is read. If no file is specified, the command is executed before anything else is done.

    `":!/bin/sh"`: This is the command being passed to Vim with the -c option. It tells Vim to execute the shell found at `/bin/sh` using Vim's command-line mode. The `:!` prefix is used in Vim to execute external commands. So, `:/bin/sh` attempts to execute the shell specified by `/bin/sh`.

    And then went to `/root`, checked out the directory and then found there is `root.txt`.

    Using `cat root.txt`, I attempted to read the text file.

    ![final](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-15%20at%2022.48.10.png)

![result](/assets/img/tryhackme/simpleCTF/Screenshot%202024-03-16%20at%2011.07.09.png)
