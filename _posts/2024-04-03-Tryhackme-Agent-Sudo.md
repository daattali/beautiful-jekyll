---
layout: post
title: Tryhackme - Agent Sudo
subtitle: tryhackme agent sudo walkthrough
# cover-img: /assets/img/banditlogo.png
thumbnail-img: /assets/img/tryhackme/agentSudo/agent.png
# share-img: /assets/img/path.jpg
tags: [linux, priviliege escalation, tryhackme, sudo agent, image reversing]
comments: true
author: Lantana Park
---

![agent](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2009.32.41.png)

1. How many open ports?

   Answer: 3

   I initially conducted an `nmap` scan to identify open ports.

   ![nmap](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2011.48.39.png)

2. How you redirect yourself to a secret page?

   Answer: user-agent

   Knowing there was an `http` service, I accessed the website. There was information about the secret page.

   **What is user-agent?**

   ![userAgent](/assets/img/tryhackme/agentSudo/User-Agent.png)

   - A user-agent is text that informs a website about the user's device and browser type. This information helps the website understand how to show the page correctly on your device. For example, if you're using a phone, the website might want to show you a version that looks good on a small screen.

   ![secretPage](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2009.38.26.png)

3. What is the agent name?

   Answer: chris

   Using Burp Suite, I changed the user-agent to various codenames (A, B, C...) to gather any information about the agent's name.

   First, I made an repeater on the `GET` request for sending repeating `GET` requests by changing `user-agent` under `A`, `B`, `C`.

   When I changed it is `A` and `B`, there was no different response with `200` status.

   ![A](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2010.38.57.png)

   Fortunately, once I sent a request under `user-agent` `C`, I could get different response with `302` status.

   ![C](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2012.49.32.png)

   In this response above, I found that there was a `agent_C_attention.php` hidden redirected location. So, I visited this page on the browser.

   ![chris](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2023.42.54.png)

   Agent's name (Not codename) was chris.

4. FTP password?

   Answer: crystal

   I used `hydra` for brute-force password cracking, knowing the username was `chris`.

   `-l` is for username, the reason for using `-l` (lowercase) specifically is that I needed to specify a single username - `chris` to try

   `-P` is for password, the reason for using `-P` (uppercase) specifically is that I needed to specify a file containing a list of password wordlist to attemp the brute-forcing.

   As it was FTP(File Transfer Protocol), I needed to set `ftp://` and then appended ip number of target machine.

   I set the thread count to `-t 16`, the maximum for Kali Linux, to expedite the process, and optionally added the verbose `-V` option.

   ![hydra](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2015.45.42.png)

   ![hydra2](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2015.45.21.png)

5. Zip file password?

   Answer: alien

   From this question, it made me take a lot of time to solve problems. Because reversing image file was new to me.

   First, I entered FTP service of this target machine.

   ![ftp](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2012.02.13.png)

   Second, I found there are useful files to investigate.

   ![files](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2012.22.23.png)

   To analyze the files available via `FTP (File Transfer Protocol)`, I downloaded them to my local system for examination. I used `mget *` to download all files in this machine.

   In my local system, I could find the downloaded files in the `/Download` directory.

   ![imageFiles](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2012.30.55.png)

   ![textFile](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2012.31.06.png)

   Upon reading the txt file, I noticed useful information within the image files.

   ![clue](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2021.07.45.png)

   To investigate these image files, I used `binwalk` because I found that it is a tool for searching a given image for embeded files and executable code.

   In `cute-alien.jpg`, there was no hidden codes and files.

   ![cute-alien](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2020.31.12.png)

   In `cutie.png`, there are compressed data, and encrypted and compressed zip file in it. Let's extract this embeded files in this png file.

   I used option `-e` for extraction and then `--run-as-root` for indicating that I am aware of the security implications.

   ![extraction](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2021.55.02.png)

   ![extraction2](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2021.55.02.png)

   ![extraction3](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2021.55.15.png)

   And then I went to the `_cutie.png.extracted` folder and checked the files in this directory.

   ![extracted](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2022.37.17.png)

   Since I needed to find the zip password, I tried to unzip this file.

   First attempt to unzip `8702.zip` was failed,

   ![failedUnzip](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2013.01.19.png)

   I noticed that there was version incompatibility of `unzip` tool. So I decided to use tool - `7z` to unzip this file.

   ![7z](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2014.32.30.png)

   Yes, I needed to crack the password of a `8702.zip` file at first.

   For cracking the password of the `8702.zip` file, I used `John the Ripper` because it is a popular tool for cracking hashed password and handles different types of encrypted zip files.

   I initially tried to extract the hash from the zip file. Because `John the Ripper` does not work directly with `zip` files. Instead, I tried to extract hash of the password from the `zip` file. `zip2john 8702.zip > 8702.hash` creates a file named `8702.hash` containing the hash extracted from `8702.zip`

   ![crackPassword1](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2015.44.34.png)

   With the hash file prepared, I can now use the `John the Ripper` to attempt to crack the password using `john`.

   ![crackPassword2](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2022.12.27.png)

6. steg password

   Answer: Area51

   To get the clue, I needed to upzip the `8702.zip` files. Since I already cracked the password using `John the Ripper` from the previous task, I thought it will be easy to check the files in the zip file. However there are issues (version incompatibility) during unzipping the zip file. I decided to use `7z`, which is new tool to unzip.

   ![errorUnzip](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2013.01.19.png)

   ![7z](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2014.32.30.png)

   ![extracted](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2015.54.56.png)

   Once I unzip the file, I could ge the `To_agentR.txt` file and then attempted to read this file.

   ![readingAgentR](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2015.55.06.png)

   I deduced that `QXJlYTUx` was encoded using Base64. There are a reason for that. Typically encoded BS64 ends with one or two `=` characters as padding though, the length of a BS64 encoded string is typically a multiple of 4, if not, it is padded with `=` to make until it is. Since the length of `QXJlYTUx` is 8 characters, I recognized it is encoded using BS64.

   ![encoding](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2016.25.14.png)

7. Who is the other agent (in full name)?

   Answer: james

   This task was really tricky because `steghide` was new to me.

   **What is steghide?**

   It allows you to hide data within various kinds of image and audio files without noticeable alterations to the file. This can be used to communicate in a completely invisible manner. So, when you dwonload files (including image and audio files), you should be careful and have to check if there is concealed executable codes or files.

   ![steg](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2022.51.03.png)

   First I checked the given image files using `steghide` tool. `--extract` option to extract data from the image file and then `-sf` option to specify the steg file that I will be extracing data from.

   ![passwordhacker](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-02%20at%2022.51.21.png)

8. SSH password

   Answer: hackerrules!

   So that, I could get username `james` and password `hackerrules!`

   Let's go to get root user of this target machine.

9. What is the user flag?

   Answer: b03d975e8c92a7c04146cfa7a5a313c7

   It was really easy. Login with the discovered information and then just read the file `user_flag.txt`

   ![reading1](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2017.04.59.png)

   ![reading2](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2017.05.13.png)

10. What is the incident of the photo called?

    Answer: Roswell alien autopsy

    ![hind](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2017.09.15.png)

    According to the hint, I needed to reverse the given image file and then do something related to foxnews.

    In order to view this photo, I saved the image file to my local system.

    Saving an image or any file from a remote system to my local machine via SSH could be done using `SCP` (Secure Copy Protocol). Sinc one line is just required to save the files of SSH. I choose to use `SCP`.

    ![saving](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2009.11.10.png)

    ![saved](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2017.26.02.png)

    Appended `-r` to copy directories, including files. And then specified the source location and then `.` represents that the destination location for the copies should be saved to the current directory on my local machine.

    And then used google to search what the image file is about and then found foxnews related to this image file.

    ![alien](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2009.10.54.png)

11. CVE number for the escalation

    Answer: CVE-2019-14287

    Let's break the root user from now on.

    I used `sudo -l` command because `sudo -l` is used to list the sudo privileges for the invoking user.

    ![sudo](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2017.39.38.png)

    I aimed to identify specific commands for privilege escalation. I commanded `sudo -l`.

    ![privilege](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2017.42.09.png)

    The results indicated that to escalate privileges, I needed to utilize `/bin/bash`.

    I googled how can I gain root user using `(ALL, !root) /bin/bash`

    I could find vulnerability in Exploit db website. `https://www.exploit-db.com/exploits/47502`

    ![explot1](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2017.46.27.png)

    ![explot2](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2017.46.50.png)

12. What is the root flag?

    Answer: b53a02f55b57d4439e3341834d70c062

    Following the instructions from the identified exploit, the root flag `b53a02f55b57d4439e3341834d70c062` was obtained.

    ![root](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2009.20.15.png)

    And reading the file.

    ![readingFile](/assets/img/tryhackme/agentSudo/Screenshot%202024-04-03%20at%2009.21.58.png)

13. (Bonus) Who is Agent R?

    Answer: DesKel

    Agent R was identified as DesKel.
