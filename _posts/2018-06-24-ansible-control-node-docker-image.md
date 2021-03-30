---
title: 'Ansible Docker Image'
subtitle: Creating a Docker image to work with Ansible automation
layout: post
tags: [automation, ansible, docker]
readtime: true
before-content: old-post-warn.html
---
If you’re part of a team that’s working on network automation with tools such as Ansible, managing package versions and dependencies can sometimes be a challenge. For example, if you’ve updated your playbook to take advantage of Ansible 2.5’s [network_cli connection type](https://mrtheplague.github.io/2018/network_cli/) but your coworker still has Ansible 2.4 installed on their local workstation, they will not be able to properly run the workflow.

Enter the **Ansible Docker Image**.

## Concept {#concept}

One potential solution to this problem is to package all of the tools together, and version control them along with your playbooks. Packaging the tools in a portable manner also allows team members running different operating systems such as MacOS, Linux, or Windows, to be able to work with the appropriate tooling.

The above is a perfect use-case for containers, and more specifically the [Docker](https://www.docker.com) platform. By creating a Docker image containing Ansible and any additional modules or libraries you require, your team can choose to build the image locally from the `Dockerfile`, or can store the pre-built image in a container registry such as the [Azure Container Registry](https://azure.microsoft.com/en-us/services/container-registry/) or Amazon’s [Elastic Container Registry](https://aws.amazon.com/ecr/). Additionally, by packaging up the tools used in your network automation, it becomes easy to integrate into some sort of CI/CD pipeline.

## Initial Build {#initial-build}

_This blog post makes the assumption that Docker is already installed on the host workstation. For more information on installing Docker, reference Docker’s [online documentation](https://docs.docker.com/install/)._

Docker images are created from a [`Dockerfile`](https://docs.docker.com/engine/reference/builder/), which is a text document containing a list of imperative steps to build the desired output image, such as installing packages, creating files, etc.

Create a new folder to house the project artefacts, and create a blank `Dockerfile`:

```
$ mkdir ansible-docker
$ touch Dockerfile
```

Open the `Dockerfile` in your text-editor of choice.

The first decision to be made is to select the base image used as the seed OS. For this project we’ll use [Alpine Linux](https://www.alpinelinux.org/), a lightweight distribution, in order to maintain an efficient file-size of the image once built; however, other base images such as Ubuntu, Fedora, or CoreOS are potential options. Adding a `label` to the `Dockerfile` with the contact information is a common practice.

```dockerfile
FROM alpine:3.7

LABEL maintainer="mrtheplague"
```

The next step is to add a group of dependencies required to install Ansible. Alpine uses the `apk` package manager, with the syntax `apk add`. Prior to adding the packages, it’s worthwhile to update the fetch the latest package list by using the `apk update`. Docker uses the syntax `RUN` to run commands once the base image has been instantiated, for example `RUN apk update`.


```dockerfile
RUN apk update
RUN apk add gcc \
    musl-dev \
    libffi-dev \
    python \
    python-dev \
    py-pip \
    make \
    openssl-dev \
    py-lxml
```

## Python Packages {#python-packages}

Now that we have a base `Dockerfile` we can instantiate a container. One of the our goals is to version control our packages, so in order to do this we’ll take advantage of Python’s `pip` package tool and its `freeze` parameter. To gather the list of Python packages and their appropriate versions, build a base Docker image on which to install Ansible, and then the packages are “frozen” to a text file.

Building the base Docker image is done by using the `docker build` command, specifying a name for the image using the `-t` switch, and identifying the location of the `Dockerfile`. The `docker images` command displays a list of locally cached images, and can be used to verify that the image has been built.

```
$ docker build -t mrtheplague/ansible-docker ./
Sending build context to Docker daemon  90.11kB
Step 1/9 : FROM alpine:3.7
 ---> 3fd9065eaf02
Step 2/9 : LABEL maintainer="mrtheplague"
 ---> Using cache
 ---> 5a32760ae2ba
<-- Output excluded for brevity -->
Successfully built 682b0091b98f
Successfully tagged mrtheplague/ansible:latest
```
<br>
```
$ docker images
REPOSITORY                   TAG                 IMAGE ID            CREATED              SIZE
mrtheplague/ansible-docker   latest              a1511ef40f0a        About a minute ago   286MB
alpine                       3.7                 3fd9065eaf02        5 months ago         4.15MB
```

From here, instantiate a container and drop into a shell.

```
$ docker run -i -t mrtheplague/ansible-docker:latest /bin/sh
```

Once in the shell, proceed to install Ansible using Python `pip`. `pip` will determine the necessary Python package dependencies, and will install them along with Ansible.

```
# pip install ansible
Collecting ansible
  Downloading https://files.pythonhosted.org/packages/93/53/925881db1049134679908698115752ad0b0fe95c82b3055a632476cd3687/ansible-2.5.5.tar.gz (10.2MB)
    100% |████████████████████████████████| 10.2MB 123kB/s
Collecting jinja2 (from ansible)
  Downloading https://files.pythonhosted.org/packages/7f/ff/ae64bacdfc95f27a016a7bed8e8686763ba4d277a78ca76f32659220a731/Jinja2-2.10-py2.py3-none-any.whl (126kB)
    100% |████████████████████████████████| 133kB 5.3MB/s
<-- Output excluded for brevity -->
Installing collected packages: MarkupSafe, jinja2, PyYAML, pyasn1, pycparser, cffi, six, bcrypt, idna, asn1crypto, enum34, ipaddress, cryptography, pynacl, paramiko, ansible
  Running setup.py install for MarkupSafe ... done
  Running setup.py install for PyYAML ... done
  Running setup.py install for pycparser ... done
  Running setup.py install for cffi ... done
  Running setup.py install for bcrypt ... done
  Running setup.py install for cryptography ... done
  Running setup.py install for pynacl ... done
  Running setup.py install for ansible ... done
Successfully installed MarkupSafe-1.0 PyYAML-3.12 ansible-2.5.5 asn1crypto-0.24.0 bcrypt-3.1.4 cffi-1.11.5 cryptography-2.2.2 enum34-1.1.6 idna-2.7 ipaddress-1.0.22 jinja2-2.10 paramiko-2.4.1 pyasn1-0.4.3 pycparser-2.18 pynacl-1.2.1 six-1.11.0
``` 

Next, follow the same process to install additional packages and libraries, such as [`napalm`](https://napalm-automation.net/), `napalm-ansible`, `napalm-ios`, `napalm-nxos`, etc.

```
# pip install napalm napalm-ansible
Collecting napalm
  Downloading https://files.pythonhosted.org/packages/3c/c9/836a3083bb03d1b1dc49cd1be97f5d232cf0de3e9f1a64b4b9df6b24ac2e/napalm-2.3.1.tar.gz (149kB)
    100% |████████████████████████████████| 153kB 2.7MB/s
Collecting napalm-ansible
  Downloading https://files.pythonhosted.org/packages/28/46/bb64de924810255e2e698d3f48472a1d2ba6c497db28ecff21b11431d0d7/napalm-ansible-0.9.1.tar.gz
Collecting setuptools>=38.4.0 (from napalm)
  Downloading https://files.pythonhosted.org/packages/7f/e1/820d941153923aac1d49d7fc37e17b6e73bfbd2904959fffbad77900cf92/setuptools-39.2.0-py2.py3-none-any.whl (567kB)
    100% |████████████████████████████████| 573kB 1.6MB/s
  Running setup.py install for napalm ... done
  Running setup.py install for napalm-ansible ... done
Successfully installed certifi-2018.4.16 chardet-3.0.4 future-0.16.0 jtextfsm-0.3.1 junos-eznc-2.1.8 napalm-2.3.1 napalm-ansible-0.9.1 ncclient-0.5.3 netaddr-0.7.19 netmiko-2.1.1 pyIOSXR-0.53 pyeapi-0.8.2 pynxos-0.0.3 pyserial-3.4 requests-2.19.1 scp-0.11.0 setuptools-39.2.0 textfsm-0.4.1 urllib3-1.23
```

With Ansible and some additional packages now installed, the current list of Python packages and their respective versions can be output to a file by using `pip freeze` and redirecting the output. We’ll call our text file `requirements.txt`.

```
# pip freeze > requirements.txt
```

The output of the `requirements.txt` can be viewed and then copied into your text editor, and saved to the same location as your `Dockerfile`. This file will serve as our master package inventory.


```
# cat requirements.txt
ansible==2.5.5
asn1crypto==0.24.0
bcrypt==3.1.4
certifi==2018.4.16
cffi==1.11.5
chardet==3.0.4
cryptography==2.2.2
enum34==1.1.6
future==0.16.0
idna==2.7
ipaddress==1.0.22
Jinja2==2.10
jtextfsm==0.3.1
junos-eznc==2.1.8
lxml==4.1.1
MarkupSafe==1.0
napalm==2.3.1
napalm-ansible==0.9.1
ncclient==0.5.3
netaddr==0.7.19
netmiko==2.1.1
paramiko==2.4.1
pyasn1==0.4.3
pycparser==2.18
pyeapi==0.8.2
pyIOSXR==0.53
PyNaCl==1.2.1
pynxos==0.0.3
pyserial==3.4
PyYAML==3.12
requests==2.19.1
scp==0.11.0
six==1.11.0
textfsm==0.4.1
urllib3==1.23
```

Now that we have a list of Python packages, we can reference this list in our `Dockerfile`. First, we need to tell Docker to copy the local folder into the image when it’s being built, which allows the Docker image to access a copy of the `requirements.txt`. The local files will be copied to the `/tmp` folder, and then Docker will be instructed to `cd` to the `/tmp` folder, ie: change the working directory.

```dockerfile
ADD . /tmp
WORKDIR /tmp
```

The final step in the creation of the `Dockerfile` is to `RUN` the `pip` command and reference the `requirements.txt`, telling `pip` to install all of the packages in the file at their noted versions.

```dockerfile
RUN pip install -r requirements.txt
```

## Final Image Build {#final-image-build}

With our complete Dockerfile, we can now run the build process again to rebuild the image with the additional step of installing the python packages.

```
$ docker build -t mrtheplague/ansible-docker ./
```

## Testing the Control Node {#testing-the-control-node}

As the Docker image is now complete, it can be tested by running a container and testing the `ansible` command.

```
$ docker run -i -t mrtheplague/ansible-docker:latest /bin/sh
# ansible --version
ansible 2.5.5
config file = None
configured module search path = [u'/root/.ansible/plugins/modules', u'/usr/share/ansible/plugins/modules']
ansible python module location = /usr/lib/python2.7/site-packages/ansible
executable location = /usr/bin/ansible
python version = 2.7.14 (default, Dec 14 2017, 15:51:29) [GCC 6.4.0]
```

As you can see, Ansible is available once our container has been created!

## Using the Control Node {#using-the-control-node}

The final step in making the control node useful is to make the Ansible playbooks on the operator’s local workstation available within the instantiated container. To do this, use the `-v` switch when running the `docker build` command, specify the _absolute_ path to the playbook, and where you’d like it mounted once in the container, eg: `/tmp`.

```
$ docker run -v /Users/rchambers/network_standardisation/:/tmp -i -t mrtheplague/ansible-docker:latest /bin/sh
# ls /tmp/
README.md          gather-facts.yml   host_vars          roles              set-logging.yml    set-users.yml
ansible.cfg        gather-serial.yml  lab.ini            set-aaa.yml        set-ntp.yml        templates
facts              group_vars         production.ini     set-dns.yml        set-snmp.yml
```

And there you have it, the local playbooks are now available inside the container. By using the `-v` switch, the specified path is mounted as a volume; therefore, any changes made to the files on the local workstation are passed into the live container, allowing you to edit your playbooks without having to re-run the container.

## Final Thoughts {#final-thoughts}

As you can see, the process of creating the Docker image is straightforward, but there are many possibilities. The Dockerfile could easily be modified to always pull the latest versions of these packages, for use in a development environment.

The final Dockerfile is located on [GitHub](https://github.com/MrThePlague/ansible-docker), so feel free to clone or fork.