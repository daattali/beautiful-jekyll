---
layout: post
title: Tryhackme - RootMe
subtitle: tryhackme RootMe walkthrough
thumbnail-img: /assets/img/rootMe/11d59cb34397e986062eb515f4d32421.png
tags: [linux, priviliege escalation, tryhackme, rootMe]
comments: true
author: Lantana Park
---

In this post, I mention several IP addresses that I am attacking due to terminating and restarting the server multiple times.

1. Scan the machine, how many ports are open?

   Answer: 2

   I performed a quick scan of the ports running on this machine.

   ![portscan](/assets/img/rootMe/Screenshot%202024-03-19%20at%2009.18.42.png)

2. What version of Apache is running?

   Answer: 2.4.29

   I added the `-sV` option to the nmap scanning command to check the service version.

   ![nmap](/assets/img/rootMe/Screenshot%202024-03-19%20at%2013.50.22.png)

3. What service is running on port 22?

   Answer: ssh

   Yes, I used this ssh port to get the root shell at the end.

   ![nmap](/assets/img/rootMe/Screenshot%202024-03-19%20at%2013.50.22.png)

4. What is the hidden directory?

   Answer: /panel/

   I used `gobuster` to find the hidden directories by brute-forcing. I found several directories, including `/css`, `/index.php`, `/panel/`, `/uploads/`, and `/js`.

   ![gobuster](/assets/img/rootMe/Screenshot%202024-03-19%20at%2009.18.42.png)

5. Find a form to upload and get a reverse shell, and find the flag in user.txt

   Answer: THM{y0u_g0t_a_sh3ll}

   To begin with, I visited the found pages. And then I found there is a page for input form. It seems that I can upload something and php is not permitted.
   ![main](/assets/img/rootMe/Screenshot%202024-03-19%20at%2010.59.47.png)
   ![form](/assets/img/rootMe/Screenshot%202024-03-19%20at%2009.47.22.png)

   It was a tricky question because the concept of a reverse shell was new to me. However I could guess this http website can be developed by php because there was `/index.php`. So I searched about php reverse shell. I found useful information to do the php reverse shell. `https://pentestmonkey.net/tools/web-shells/php-reverse-shell`

   Initially, I downloaded a PHP reverse shell file (`git clone https://github.com/pentestmonkey/php-reverse-shell.git`).Additionally, configured my local machine ip address (not target ip address) and specific port because these are necessary to establish a connection back to my machine from a remote system. And then I uploaded the file to the form, since php file is not allowed, I changed `php` into `php5`.
   ![configuration](/assets/img/rootMe/Untitled%20design.png)
   ![upload](/assets/img/rootMe/Screenshot%202024-03-19%20at%2009.49.02.png)
   ![php5](/assets/img/rootMe/Screenshot%202024-03-19%20at%2010.57.04.png)

   At second, I opend the port to listen outcomes of the connection between my local machine and remote target system. Please keep in mind, when the port is open and then run the php file again by clicking the php file in the `/uploads`.

   Finally, after listening port, I could accessa a shell and then used the `find . -type f -name "user.txt"` command to find the user.txt file somewhere else.
   ![findfile](/assets/img/rootMe/Screenshot%202024-03-19%20at%2011.22.45.png)
   ![gotshell](/assets/img/rootMe/Screenshot%202024-03-19%20at%2011.23.26.png)

6. Search for files with SUID permission, which file is weird?

   Answer: /usr/bin/python

   To find files with SUID permission, which means executing a file with the file owner's permissions, I used the following command:

   I executed `sudo find / -perm /4000 2>/dev/null`. `-perm /4000` filters the search in include only files with the SUID bit set.
   `2>/dev/null` hides all error messages that might occur during the search, such as "Permission denied" messages.

   According to the result, I could know which files have SUID bit and then, since I have experience of using SUID in python scripting from pwn.college and bandit, I decided to use `/usr/bin/python`.

   **What is Set User ID(SUID) bit?**

   - It is a special type of file permission. When the SUID bit is set on an executable file, users who run that executable file obtain the permissions of the file owner to execute the file.

   ![suid](/assets/img/rootMe/Screenshot%202024-03-20%20at%2009.10.36.png)
   ![suid2](/assets/img/rootMe/Screenshot%202024-03-20%20at%2009.10.52.png)

7. root.txt

   Answer: THM{pr1v1l3g3_3sc4l4t10n}

   I executed the command python -c `'import os; os.execl("/bin/sh", "sh", "-p")'` to exploit the SUID permission of the Python script. `python` calls the python interpreter, `'-c` tells python to execute the string, `import os` imports os modules, which provides a way of using operating system dependent functionality. And `os.execl("/bin/sh", "sh","-p")` replace the current executing process with a new process and privileges of the process.

   ![final](/assets/img/rootMe/Screenshot%202024-03-20%20at%2009.26.05.png)

   ![success](/assets/img/rootMe/Screenshot%202024-03-20%20at%2010.50.21.png)
