---
created: 2021-04-23T12:54:03+05:30
modified: 2021-04-23T12:54:27+05:30
tags: [tech]
---
[[cs_learning]]
https://www.reddit.com/r/sysadmin/comments/mwe43u/containers_docker_oh_my_an_intro_to_docker_for/

Hello, and welcome to my TED talk about containers and why you, as a sysadmin, will find them to be extremely handy. This intro is meant for system administrators who haven't dipped their toes into the Docker waters just yet. This will focus on **Linux Systems** primarily.

As an IT professional, you probably already know all about the following concepts:

-   Ports
    
-   IPs
    
-   Processes and Process IDs
    
-   DNS
    
-   Users and groups
    
-   Filesystems
    
-   Environment Variables
    
-   Networks
    
-   Filesystem Mounts
    

What do all these have in common? **They can live entirely inside the kernel / OS, independent of hardware**. This is opposed to say, SSDs and network cards, which talk to the kernel via drivers. From a sysadmin perspective, this is the difference between VMs and Containers: VMs deal hands-on with hardware, Containers deals hands-on with software.

What else do they have in common? **Your server application, whatever it may be, depends on these things, not on hardware**. Sure, eventually your application will write logs to the HDD or NAS attached to the server, but it doesn't really notice this: to your application it's writing to `/var/log/somefile.log`

This might not make a ton of sense right away, it didn't for me, but it's important background info for later!

Lets quickly talk about what VMs brought us from the world of bare-metal servers:

-   Multiple servers running on one bare-metal server
    
-   The ability to run these servers anywhere
    
-   The ability to independently configure these servers
    
-   The ability to start / stop / migrate these virtual servers without actually powering down a physical computer
    

That's great! Super handy. Containers do kinda the same thing. And the easiest way I can think of to describe it is that **containers allow you to run multiple operating systems on your server**. Pretty crazy right? When you really think about it, what really allows your application to run? All the software things we talked about earlier, like ports, IPs, filesystems, environment variable, and the like. Since these concepts are not tied directly to hardware, we can basically create multiple copies of them (in the kernel) **on one VM / Bare metal PC**, and run our applications in them. One kernel, one machine, multiple operating systems. As it turns out, this has some really handy properties. As an example, we're going to use nginx, but this really could be almost any server-side software you care about.

What _defines_ nginx:

-   The nginx binary (`/usr/sbin/nginx`)
    
-   The nginx config files (`/etc/nginx/*`)
    
-   The nginx logs (`/var/logs/nginx/*`)
    
-   The nginx port (`80/tcp, 443/tcp`)
    
-   The nginx listening IP address (e.g. `0.0.0.0/0`)
    
-   The website itself (`/usr/share/nginx/html/index.html`)
    
-   The user / group nginx runs as (`nginx / nginx`)
    

That's really not all too much. And there's nothing extra in there - it's **only** the things Nginx cares about. Nginx doesn't care how many NICs there are, what kind of disk it's using, (to a point) which kernel version its running, what distro it's running - as long as the above listed things are present and configured correctly, nginx will run.

So some clever people realized this and thought, why are we hefting around these massive VMs with disks and CPUs and kernels just to run a simple nginx? I just want to run nginx on my server. Actually, I want to run 10 differently configured nginx's on my server, and also not have to worry about `/var/logs` getting messy, and not have 10 different VMs running all consuming large amounts of RAM and CPU for the kernel. So containers were invented.

On the first day, a clever person made it so you could have multiple process _namespaces_ on a single OS. This means you could log into your server, do a `ps -aux` to see what's running, run a special command to switch namespaces, and do another `ps -aux` and see an entirely different set of processes running. They also did similar things with filesystem mounts, hostnames, users and groups, and networking things. This is the **isolation** part of containers. It helps ensure containers run where ever they're put. These changes were put into the Linux kernel, then the clever person rested.

On the second day, another clever person made it really easy to define and create these namespaces. They called it Docker, and people used it because it was easy. They also made it really easy to save these things into things called images, which can be shared distributed and run on any machine.

On the third day, some interested party made an Debian image by installing Debian (basically copying an existing Debian filesystem) in a container. They shared this with everyone, so that everyone could run Debian in a container.

**As a systems administrator, this is key / the value add**: On the forth day, someone from the nginx developer team downloaded that Debian image and installed nginx. They did all of this boring work, of running `apt-get update && apt-get install nginx`. They put config files in the right places, and set some really handy defaults in the config files. Because they were really smart and knew nginx inside and out, they did this the right way: They used the latest version of nginx, with all the security patches. They updated the OS so that the base was secure. They changed the permissions of directories and files so that everything wasn't running as root. They tested this image, over and over again, until it was perfect for everybody to use. It ran exactly the same, every single time they started the container. Finally, they told the container to run `/usr/share/nginx` by default when it started. Then they saved this image and shared it with everyone.

**This is where the value add pays off:** On the fifth day, **you** came along and wanted to run a simple webserver using nginx. You had never installed nginx before, but this didn't matter: The nginx developer had installed it for you in a container image, and shared the image with you. You already knew how webservers worked, you have files you want to serve, and a server that listens on an address and port. That's all you really care about anyways, you don't really care about how exactly nginx is installed. You wrote a little YAML file named `docker-compose.yml` to define these things that you care about. It goes a little something like this (the below is a complete docker-compose file):

```
version: "3"

services:
    nginx-container-1: 
        image: nginx   # The nginx dev made this image for you!
        ports:
            - 8000:80   # For reasons, you need to run nginx on host port 8000.
        volumes:
            - ./src:/usr/share/nginx/html   # You put your files in /src on the host
```

Then your boss came along and asked for another nginx server on port 8001. So what did you do, as a lazy sysadmin? Open up the containers `nginx.conf` and add another virtual server? Hell no, you don't have time to learn how to do that! You made another `docker-compose.yml` file, and in it you put this:

```
version: "3"

services:
    nginx-container-2: 
        image: nginx
        ports:
            - 8001:80
        volumes:
            - ./src-2:/usr/share/nginx/html
```

This container is literally an **exactly copy** of the above container, but it listens on port 8001 and it grabs its files from `/src-2` on the host instead. It also has a different name. It works just fine, because containers are isolated and don't interfere with each other in strange ways.

Are you getting it? Docker has a lot of cool things for developers, but as a system administrator, one of the key benefits you get is that **someone has already done the hard work of getting the software \*working\* for you.** They typically also maintain these images with security updates and new updates and the like. They left the important details of _what and how_ for you to decide. Not only that, they let you define all of this in a single yaml file that takes up about 300 bytes in text form. Put it in git, along with your html files! When you run this text file, it downloads the whole image (small! e.g. Debian is 50MB, and that's a full-fledged OS) and runs the container according to the config that you (and the image maintainer) specified.

Of course, nginx is a trivial example. A docker container could contain a massive CRM software solution that would take a seasoned sysadmin days to finally install correctly. Who wants to do that? Let the CRM software vendor install it for you in a docker container, you'll just download and run that. Easy!

This makes it **SUPER SIMPLE** to test out and run software in prod, really quickly! You don't need a specific OS, you don't need to learn how to configure it, you don't need to download a bulky VM image that takes up a toooon of resources just running the kernel and systemd. Just plop in the pre-made image, forward the necessary ports to the container, and away you go. Extra resource usage? Containers have practically no overhead - **containers only run the software** **directly related to the software at hand**. Containers don't need to virtualize resources such as CPUs, disk and RAM - the host deals with all of those details. No need for a whole kernel, systemd, DNS, etc. to be running in the background - the host / docker itself / other docker containers can take care of that. And when you're done with the container (maybe you were just testing it)?: delete it. Everything is gone. No weird directories left laying about, no logs left behind, no side effects of files being left configured. It's just gone.

Things you can also handle with docker:

-   Setting resource limits (RAM / CPU)
    
-   Networking (DNS resolution is built in, it's magic)
    
-   Making your own containers (duh!)
    
-   And many more...
    

There's a lot of other benefits of Docker that I won't go into. I just wanted to explain how they might be handy to you, as a sysadmin, right now.

Anyways, I hope this helps some people. Sorry for rambling. Have a good one!