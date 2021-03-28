---
title: 'Ansible Control Node - Docker Image'
layout: post
tags:
  - automation
  - ansible
  - docker
---
{: .box-warning}
**Warning:** This post is over a year old, and may not be up-to-date. Please read with its age in mind.

If you’re part of a team that’s working on network automation with tools such as Ansible, managing package versions and dependencies can sometimes be a challenge. For example, if you’ve updated your playbook to take advantage of Ansible 2.5’s [network_cli connection type](https://mrtheplague.github.io/2018/network_cli/) but your coworker still has Ansible 2.4 installed on her/his local workstation, they will not be able to properly run the workflow.

Enter the **Control Node**.

## Concept {#concept}

One potential solution to this problem is to package all of the tools together, and version control them along with your playbooks. Packaging the tools in a portable manner also allows team members running different operating systems such as MacOS, Linux, or Windows, to be able to work with the appropriate tooling.

The above is a perfect use-case for containers, and more specifically the [Docker](https://www.docker.com) platform. By creating a Docker image containing Ansible and any additional modules or libraries you require, your team can choose to build the image locally from the `Dockerfile`, or can store the pre-built image in a container registry such as the [Azure Container Registry](https://azure.microsoft.com/en-us/services/container-registry/) or Amazon’s [Elastic Container Registry](https://aws.amazon.com/ecr/). Additionally, by packaging up the tools used in your network automation, it becomes easy to integrate into some sort of CI/CD pipeline.

## Initial Build {#initial-build}

_This blog post makes the assumption that Docker is already installed on the host workstation. For more information on installing Docker, reference Docker’s [online documentation](https://docs.docker.com/install/)._

Docker images are created from a [`Dockerfile`](https://docs.docker.com/engine/reference/builder/), which is a text document containing a list of imperative steps to build the desired output image, such as installing packages, creating files, etc.

Create a new folder to house the project artefacts, and create a blank `Dockerfile`:

<pre class="wp-block-code"><div>
  <code class="hljs">$ mkdir ansible-docker
  $ touch Dockerfile</code>
</div></pre>

Open the `Dockerfile` in your text-editor of choice.

The first decision to be made is to select the base image used as the seed OS. For this project we’ll use [Alpine Linux](https://www.alpinelinux.org/), a lightweight distribution, in order to maintain an efficient file-size of the image once built; however, other base images such as Ubuntu, Fedora, or CoreOS are potential options. Adding a `label` to the `Dockerfile` with the contact information is a common practice.

<pre class="wp-block-code" aria-describedby="shcb-language-38" data-shcb-language-name="JavaScript" data-shcb-language-slug="javascript"><div>
  <code class="hljs language-javascript">FROM alpine:&lt;span class="hljs-number">3.7&lt;/span>
  
  LABEL maintainer=&lt;span class="hljs-string">"mrtheplague"&lt;/span></code>
</div>

<small class="shcb-language" id="shcb-language-38"><span class="shcb-language__label">Code language:</span> <span class="shcb-language__name">JavaScript</span> <span class="shcb-language__paren">(</span><span class="shcb-language__slug">javascript</span><span class="shcb-language__paren">)</span></small></pre>

The next step is to add a group of dependencies required to install Ansible. Alpine uses the `apk` package manager, with the syntax `apk add`. Prior to adding the packages, it’s worthwhile to update the fetch the latest package list by using the `apk update`. Docker uses the syntax `RUN` to run commands once the base image has been instantiated, for example `RUN apk update`.

<pre class="wp-block-code"><div>
  <code class="hljs">RUN apk update
  RUN apk add gcc \
      musl-dev \
      libffi-dev \
      python \
      python-dev \
      py-pip \
      make \
      openssl-dev \
      py-lxml</code>
</div></pre>

## Python Packages {#python-packages}

Now that we have a base `Dockerfile` we can instantiate a container. One of the our goals is to version control our packages, so in order to do this we’ll take advantage of Python’s `pip` package tool and its `freeze` parameter. To gather the list of Python packages and their appropriate versions, build a base Docker image on which to install Ansible, and then the packages are “frozen” to a text file.

Building the base Docker image is done by using the `docker build` command, specifying a name for the image using the `-t` switch, and identifying the location of the `Dockerfile`. The `docker images` command displays a list of locally cached images, and can be used to verify that the image has been built.

<pre class="wp-block-code" aria-describedby="shcb-language-39" data-shcb-language-name="HTML, XML" data-shcb-language-slug="xml"><div>
  <code class="hljs language-xml">$ docker build -t mrtheplague/ansible-docker ./
  Sending build context to Docker daemon  90.11kB
  Step 1/9 : FROM alpine:3.7
   ---&gt; 3fd9065eaf02
  Step 2/9 : LABEL maintainer="mrtheplague"
   ---&gt; Using cache
   ---&gt; 5a32760ae2ba
  &lt;span class="hljs-tag">&lt;&lt;span class="hljs-name">--&lt;/span> &lt;span class="hljs-attr">Output&lt;/span> &lt;span class="hljs-attr">excluded&lt;/span> &lt;span class="hljs-attr">for&lt;/span> &lt;span class="hljs-attr">brevity&lt;/span> &lt;span class="hljs-attr">--&lt;/span>&gt;&lt;/span>
  Successfully built 682b0091b98f
  Successfully tagged mrtheplague/ansible:latest
  
  $ docker images
  REPOSITORY                   TAG                 IMAGE ID            CREATED              SIZE
  mrtheplague/ansible-docker   latest              a1511ef40f0a        About a minute ago   286MB
  alpine                       3.7                 3fd9065eaf02        5 months ago         4.15MB</code>
</div>

<small class="shcb-language" id="shcb-language-39"><span class="shcb-language__label">Code language:</span> <span class="shcb-language__name">HTML, XML</span> <span class="shcb-language__paren">(</span><span class="shcb-language__slug">xml</span><span class="shcb-language__paren">)</span></small></pre>

From here, instantiate a container and drop into a shell.

<pre class="wp-block-code"><div>
  <code class="hljs">$ docker run -i -t mrtheplague/ansible-docker:latest /bin/sh</code>
</div></pre>

Once in the shell, proceed to install Ansible using Python `pip`. `pip` will determine the necessary Python package dependencies, and will install them along with Ansible.

<pre class="wp-block-code" aria-describedby="shcb-language-40" data-shcb-language-name="PHP" data-shcb-language-slug="php"><div>
  <code class="hljs language-php">&lt;span class="hljs-comment"># pip install ansible&lt;/span>
  Collecting ansible
    Downloading https:&lt;span class="hljs-comment">//files.pythonhosted.org/packages/93/53/925881db1049134679908698115752ad0b0fe95c82b3055a632476cd3687/ansible-2.5.5.tar.gz (10.2MB)&lt;/span>
      &lt;span class="hljs-number">100&lt;/span>% |████████████████████████████████| &lt;span class="hljs-number">10.2&lt;/span>MB &lt;span class="hljs-number">123&lt;/span>kB/s
  Collecting jinja2 (from ansible)
    Downloading https:&lt;span class="hljs-comment">//files.pythonhosted.org/packages/7f/ff/ae64bacdfc95f27a016a7bed8e8686763ba4d277a78ca76f32659220a731/Jinja2-2.10-py2.py3-none-any.whl (126kB)&lt;/span>
      &lt;span class="hljs-number">100&lt;/span>% |████████████████████████████████| &lt;span class="hljs-number">133&lt;/span>kB &lt;span class="hljs-number">5.3&lt;/span>MB/s
  &lt;-- Output excluded &lt;span class="hljs-keyword">for&lt;/span> brevity --&gt;
  Installing collected packages: MarkupSafe, jinja2, PyYAML, pyasn1, pycparser, cffi, six, bcrypt, idna, asn1crypto, enum34, ipaddress, cryptography, pynacl, paramiko, ansible
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> MarkupSafe ... done
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> PyYAML ... done
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> pycparser ... done
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> cffi ... done
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> bcrypt ... done
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> cryptography ... done
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> pynacl ... done
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> ansible ... done
  Successfully installed MarkupSafe&lt;span class="hljs-number">-1.0&lt;/span> PyYAML&lt;span class="hljs-number">-3.12&lt;/span> ansible&lt;span class="hljs-number">-2.5&lt;/span>&lt;span class="hljs-number">.5&lt;/span> asn1crypto&lt;span class="hljs-number">-0.24&lt;/span>&lt;span class="hljs-number">.0&lt;/span> bcrypt&lt;span class="hljs-number">-3.1&lt;/span>&lt;span class="hljs-number">.4&lt;/span> cffi&lt;span class="hljs-number">-1.11&lt;/span>&lt;span class="hljs-number">.5&lt;/span> cryptography&lt;span class="hljs-number">-2.2&lt;/span>&lt;span class="hljs-number">.2&lt;/span> enum34&lt;span class="hljs-number">-1.1&lt;/span>&lt;span class="hljs-number">.6&lt;/span> idna&lt;span class="hljs-number">-2.7&lt;/span> ipaddress&lt;span class="hljs-number">-1.0&lt;/span>&lt;span class="hljs-number">.22&lt;/span> jinja2&lt;span class="hljs-number">-2.10&lt;/span> paramiko&lt;span class="hljs-number">-2.4&lt;/span>&lt;span class="hljs-number">.1&lt;/span> pyasn1&lt;span class="hljs-number">-0.4&lt;/span>&lt;span class="hljs-number">.3&lt;/span> pycparser&lt;span class="hljs-number">-2.18&lt;/span> pynacl&lt;span class="hljs-number">-1.2&lt;/span>&lt;span class="hljs-number">.1&lt;/span> six&lt;span class="hljs-number">-1.11&lt;/span>&lt;span class="hljs-number">.0&lt;/span></code>
</div>

<small class="shcb-language" id="shcb-language-40"><span class="shcb-language__label">Code language:</span> <span class="shcb-language__name">PHP</span> <span class="shcb-language__paren">(</span><span class="shcb-language__slug">php</span><span class="shcb-language__paren">)</span></small></pre>

Next, follow the same process to install additional packages and libraries, such as [`napalm`](https://napalm-automation.net/), `napalm-ansible`, `napalm-ios`, `napalm-nxos`, etc.

<pre class="wp-block-code" aria-describedby="shcb-language-41" data-shcb-language-name="PHP" data-shcb-language-slug="php"><div>
  <code class="hljs language-php">&lt;span class="hljs-comment"># pip install napalm napalm-ansible&lt;/span>
  Collecting napalm
    Downloading https:&lt;span class="hljs-comment">//files.pythonhosted.org/packages/3c/c9/836a3083bb03d1b1dc49cd1be97f5d232cf0de3e9f1a64b4b9df6b24ac2e/napalm-2.3.1.tar.gz (149kB)&lt;/span>
      &lt;span class="hljs-number">100&lt;/span>% |████████████████████████████████| &lt;span class="hljs-number">153&lt;/span>kB &lt;span class="hljs-number">2.7&lt;/span>MB/s
  Collecting napalm-ansible
    Downloading https:&lt;span class="hljs-comment">//files.pythonhosted.org/packages/28/46/bb64de924810255e2e698d3f48472a1d2ba6c497db28ecff21b11431d0d7/napalm-ansible-0.9.1.tar.gz&lt;/span>
  Collecting setuptools&gt;=&lt;span class="hljs-number">38.4&lt;/span>&lt;span class="hljs-number">.0&lt;/span> (from napalm)
    Downloading https:&lt;span class="hljs-comment">//files.pythonhosted.org/packages/7f/e1/820d941153923aac1d49d7fc37e17b6e73bfbd2904959fffbad77900cf92/setuptools-39.2.0-py2.py3-none-any.whl (567kB)&lt;/span>
      &lt;span class="hljs-number">100&lt;/span>% |████████████████████████████████| &lt;span class="hljs-number">573&lt;/span>kB &lt;span class="hljs-number">1.6&lt;/span>MB/s
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> napalm ... done
    Running setup.py install &lt;span class="hljs-keyword">for&lt;/span> napalm-ansible ... done
  Successfully installed certifi&lt;span class="hljs-number">-2018.4&lt;/span>&lt;span class="hljs-number">.16&lt;/span> chardet&lt;span class="hljs-number">-3.0&lt;/span>&lt;span class="hljs-number">.4&lt;/span> future&lt;span class="hljs-number">-0.16&lt;/span>&lt;span class="hljs-number">.0&lt;/span> jtextfsm&lt;span class="hljs-number">-0.3&lt;/span>&lt;span class="hljs-number">.1&lt;/span> junos-eznc&lt;span class="hljs-number">-2.1&lt;/span>&lt;span class="hljs-number">.8&lt;/span> napalm&lt;span class="hljs-number">-2.3&lt;/span>&lt;span class="hljs-number">.1&lt;/span> napalm-ansible&lt;span class="hljs-number">-0.9&lt;/span>&lt;span class="hljs-number">.1&lt;/span> ncclient&lt;span class="hljs-number">-0.5&lt;/span>&lt;span class="hljs-number">.3&lt;/span> netaddr&lt;span class="hljs-number">-0.7&lt;/span>&lt;span class="hljs-number">.19&lt;/span> netmiko&lt;span class="hljs-number">-2.1&lt;/span>&lt;span class="hljs-number">.1&lt;/span> pyIOSXR&lt;span class="hljs-number">-0.53&lt;/span> pyeapi&lt;span class="hljs-number">-0.8&lt;/span>&lt;span class="hljs-number">.2&lt;/span> pynxos&lt;span class="hljs-number">-0.0&lt;/span>&lt;span class="hljs-number">.3&lt;/span> pyserial&lt;span class="hljs-number">-3.4&lt;/span> requests&lt;span class="hljs-number">-2.19&lt;/span>&lt;span class="hljs-number">.1&lt;/span> scp&lt;span class="hljs-number">-0.11&lt;/span>&lt;span class="hljs-number">.0&lt;/span> setuptools&lt;span class="hljs-number">-39.2&lt;/span>&lt;span class="hljs-number">.0&lt;/span> textfsm&lt;span class="hljs-number">-0.4&lt;/span>&lt;span class="hljs-number">.1&lt;/span> urllib3&lt;span class="hljs-number">-1.23&lt;/span></code>
</div>

<small class="shcb-language" id="shcb-language-41"><span class="shcb-language__label">Code language:</span> <span class="shcb-language__name">PHP</span> <span class="shcb-language__paren">(</span><span class="shcb-language__slug">php</span><span class="shcb-language__paren">)</span></small></pre>

With Ansible and some additional packages now installed, the current list of Python packages and their respective versions can be output to a file by using `pip freeze` and redirecting the output. We’ll call our text file `requirements.txt`.

<pre class="wp-block-code" aria-describedby="shcb-language-42" data-shcb-language-name="CSS" data-shcb-language-slug="css"><div>
  <code class="hljs language-css"># &lt;span class="hljs-selector-tag">pip&lt;/span> &lt;span class="hljs-selector-tag">freeze&lt;/span> &gt; &lt;span class="hljs-selector-tag">requirements&lt;/span>&lt;span class="hljs-selector-class">.txt&lt;/span></code>
</div>

<small class="shcb-language" id="shcb-language-42"><span class="shcb-language__label">Code language:</span> <span class="shcb-language__name">CSS</span> <span class="shcb-language__paren">(</span><span class="shcb-language__slug">css</span><span class="shcb-language__paren">)</span></small></pre>

The output of the `requirements.txt` can be viewed and then copied into your text editor, and saved to the same location as your `Dockerfile`. This file will serve as our master package inventory.

<pre class="wp-block-code" aria-describedby="shcb-language-43" data-shcb-language-name="PHP" data-shcb-language-slug="php"><div>
  <code class="hljs language-php">&lt;span class="hljs-comment"># cat requirements.txt&lt;/span>
  ansible==&lt;span class="hljs-number">2.5&lt;/span>&lt;span class="hljs-number">.5&lt;/span>
  asn1crypto==&lt;span class="hljs-number">0.24&lt;/span>&lt;span class="hljs-number">.0&lt;/span>
  bcrypt==&lt;span class="hljs-number">3.1&lt;/span>&lt;span class="hljs-number">.4&lt;/span>
  certifi==&lt;span class="hljs-number">2018.4&lt;/span>&lt;span class="hljs-number">.16&lt;/span>
  cffi==&lt;span class="hljs-number">1.11&lt;/span>&lt;span class="hljs-number">.5&lt;/span>
  chardet==&lt;span class="hljs-number">3.0&lt;/span>&lt;span class="hljs-number">.4&lt;/span>
  cryptography==&lt;span class="hljs-number">2.2&lt;/span>&lt;span class="hljs-number">.2&lt;/span>
  enum34==&lt;span class="hljs-number">1.1&lt;/span>&lt;span class="hljs-number">.6&lt;/span>
  future==&lt;span class="hljs-number">0.16&lt;/span>&lt;span class="hljs-number">.0&lt;/span>
  idna==&lt;span class="hljs-number">2.7&lt;/span>
  ipaddress==&lt;span class="hljs-number">1.0&lt;/span>&lt;span class="hljs-number">.22&lt;/span>
  Jinja2==&lt;span class="hljs-number">2.10&lt;/span>
  jtextfsm==&lt;span class="hljs-number">0.3&lt;/span>&lt;span class="hljs-number">.1&lt;/span>
  junos-eznc==&lt;span class="hljs-number">2.1&lt;/span>&lt;span class="hljs-number">.8&lt;/span>
  lxml==&lt;span class="hljs-number">4.1&lt;/span>&lt;span class="hljs-number">.1&lt;/span>
  MarkupSafe==&lt;span class="hljs-number">1.0&lt;/span>
  napalm==&lt;span class="hljs-number">2.3&lt;/span>&lt;span class="hljs-number">.1&lt;/span>
  napalm-ansible==&lt;span class="hljs-number">0.9&lt;/span>&lt;span class="hljs-number">.1&lt;/span>
  ncclient==&lt;span class="hljs-number">0.5&lt;/span>&lt;span class="hljs-number">.3&lt;/span>
  netaddr==&lt;span class="hljs-number">0.7&lt;/span>&lt;span class="hljs-number">.19&lt;/span>
  netmiko==&lt;span class="hljs-number">2.1&lt;/span>&lt;span class="hljs-number">.1&lt;/span>
  paramiko==&lt;span class="hljs-number">2.4&lt;/span>&lt;span class="hljs-number">.1&lt;/span>
  pyasn1==&lt;span class="hljs-number">0.4&lt;/span>&lt;span class="hljs-number">.3&lt;/span>
  pycparser==&lt;span class="hljs-number">2.18&lt;/span>
  pyeapi==&lt;span class="hljs-number">0.8&lt;/span>&lt;span class="hljs-number">.2&lt;/span>
  pyIOSXR==&lt;span class="hljs-number">0.53&lt;/span>
  PyNaCl==&lt;span class="hljs-number">1.2&lt;/span>&lt;span class="hljs-number">.1&lt;/span>
  pynxos==&lt;span class="hljs-number">0.0&lt;/span>&lt;span class="hljs-number">.3&lt;/span>
  pyserial==&lt;span class="hljs-number">3.4&lt;/span>
  PyYAML==&lt;span class="hljs-number">3.12&lt;/span>
  requests==&lt;span class="hljs-number">2.19&lt;/span>&lt;span class="hljs-number">.1&lt;/span>
  scp==&lt;span class="hljs-number">0.11&lt;/span>&lt;span class="hljs-number">.0&lt;/span>
  six==&lt;span class="hljs-number">1.11&lt;/span>&lt;span class="hljs-number">.0&lt;/span>
  textfsm==&lt;span class="hljs-number">0.4&lt;/span>&lt;span class="hljs-number">.1&lt;/span>
  urllib3==&lt;span class="hljs-number">1.23&lt;/span></code>
</div>

<small class="shcb-language" id="shcb-language-43"><span class="shcb-language__label">Code language:</span> <span class="shcb-language__name">PHP</span> <span class="shcb-language__paren">(</span><span class="shcb-language__slug">php</span><span class="shcb-language__paren">)</span></small></pre>

Now that we have a list of Python packages, we can reference this list in our `Dockerfile`. First, we need to tell Docker to copy the local folder into the image when it’s being built, which allows the Docker image to access a copy of the `requirements.txt`. The local files will be copied to the `/tmp` folder, and then Docker will be instructed to `cd` to the `/tmp` folder, ie: change the working directory.

<pre class="wp-block-code"><div>
  <code class="hljs">ADD . /tmp
  WORKDIR /tmp</code>
</div></pre>

The final step in the creation of the `Dockerfile` is to `RUN` the `pip` command and reference the `requirements.txt`, telling `pip` to install all of the packages in the file at their noted versions.

<pre class="wp-block-code" aria-describedby="shcb-language-44" data-shcb-language-name="CSS" data-shcb-language-slug="css"><div>
  <code class="hljs language-css">&lt;span class="hljs-selector-tag">RUN&lt;/span> &lt;span class="hljs-selector-tag">pip&lt;/span> &lt;span class="hljs-selector-tag">install&lt;/span> &lt;span class="hljs-selector-tag">-r&lt;/span> &lt;span class="hljs-selector-tag">requirements&lt;/span>&lt;span class="hljs-selector-class">.txt&lt;/span></code>
</div>

<small class="shcb-language" id="shcb-language-44"><span class="shcb-language__label">Code language:</span> <span class="shcb-language__name">CSS</span> <span class="shcb-language__paren">(</span><span class="shcb-language__slug">css</span><span class="shcb-language__paren">)</span></small></pre>

## Final Image Build {#final-image-build}

With our complete Dockerfile, we can now run the build process again to rebuild the image with the additional step of installing the python packages.

<pre class="wp-block-code"><div>
  <code class="hljs">$ docker build -t mrtheplague/ansible-docker ./</code>
</div></pre>

## Testing the Control Node {#testing-the-control-node}

As the Docker image is now complete, it can be tested by running a container and testing the `ansible` command.

<pre class="wp-block-code" aria-describedby="shcb-language-45" data-shcb-language-name="PHP" data-shcb-language-slug="php"><div>
  <code class="hljs language-php">$ docker run -i -t mrtheplague/ansible-docker:latest /bin/sh
  &lt;span class="hljs-comment"># ansible --version&lt;/span>
  ansible &lt;span class="hljs-number">2.5&lt;/span>&lt;span class="hljs-number">.5&lt;/span>
  config file = None
  configured module search path = [u&lt;span class="hljs-string">'/root/.ansible/plugins/modules'&lt;/span>, u&lt;span class="hljs-string">'/usr/share/ansible/plugins/modules'&lt;/span>]
  ansible python module location = /usr/lib/python2&lt;span class="hljs-number">.7&lt;/span>/site-packages/ansible
  executable location = /usr/bin/ansible
  python version = &lt;span class="hljs-number">2.7&lt;/span>&lt;span class="hljs-number">.14&lt;/span> (&lt;span class="hljs-keyword">default&lt;/span>, Dec &lt;span class="hljs-number">14&lt;/span> &lt;span class="hljs-number">2017&lt;/span>, &lt;span class="hljs-number">15&lt;/span>:&lt;span class="hljs-number">51&lt;/span>:&lt;span class="hljs-number">29&lt;/span>) [GCC &lt;span class="hljs-number">6.4&lt;/span>&lt;span class="hljs-number">.0&lt;/span>]
  </code>
</div>

<small class="shcb-language" id="shcb-language-45"><span class="shcb-language__label">Code language:</span> <span class="shcb-language__name">PHP</span> <span class="shcb-language__paren">(</span><span class="shcb-language__slug">php</span><span class="shcb-language__paren">)</span></small></pre>

As you can see, Ansible is available once our container has been created!

## Using the Control Node {#using-the-control-node}

The final step in making the control node useful is to make the Ansible playbooks on the operator’s local workstation available within the instantiated container. To do this, use the `-v` switch when running the `docker build` command, specify the _absolute_ path to the playbook, and where you’d like it mounted once in the container, eg: `/tmp`.

<pre class="wp-block-code" aria-describedby="shcb-language-46" data-shcb-language-name="PHP" data-shcb-language-slug="php"><div>
  <code class="hljs language-php">$ docker run -v /Users/rchambers/network_standardisation/:/tmp -i -t mrtheplague/ansible-docker:latest /bin/sh
  &lt;span class="hljs-comment"># ls /tmp/&lt;/span>
  README.md          gather-facts.yml   host_vars          roles              set-logging.yml    set-users.yml
  ansible.cfg        gather-serial.yml  lab.ini            set-aaa.yml        set-ntp.yml        templates
  facts              group_vars         production.ini     set-dns.yml        set-snmp.yml
  </code>
</div>

<small class="shcb-language" id="shcb-language-46"><span class="shcb-language__label">Code language:</span> <span class="shcb-language__name">PHP</span> <span class="shcb-language__paren">(</span><span class="shcb-language__slug">php</span><span class="shcb-language__paren">)</span></small></pre>

And there you have it, the local playbooks are now available inside the container. By using the `-v` switch, the specified path is mounted as a volume; therefore, any changes made to the files on the local workstation are passed into the live container, allowing you to edit your playbooks without having to re-run the container.

## Final Thoughts {#final-thoughts}

As you can see, the process of creating the Docker image is straightforward, but there are many possibilities. The Dockerfile could easily be modified to always pull the latest versions of these packages, for use in a development environment.

The final Dockerfile is located on [GitHub](https://github.com/MrThePlague/ansible-docker), so feel free to clone or fork.