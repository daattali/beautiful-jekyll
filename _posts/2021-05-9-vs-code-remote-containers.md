---
layout: post
title: Getting Started With VS Code Remote Containers
subtitle: Creating development environments in VS Code
tags: [containers, docker, tools, 'vs code']
readtime: true
---

One of the beautiful things about leveraging containers within the context of development is that containers abstract away the dependencies from the host system, and allow you to manage those dependency versions right alongside the code itself. This abstraction has many benefits, for example, it allows you to simultaneously maintain multiple versions of a particular language, package, or library. 


## Development Environments

If you're using macOS, it's likely that your host machine comes pre-installed with an old version of PHP, i.e.,: `php 7.3.24`; however, you likely want to work with a more recent version for your particular use-case. 

Alternatively, you could be working on multiple projects, each of which require a different version of Python, e.g.,: One project uses `python 3.7.1`, while the other is built on `python 3.8.6`.

There are many ways to handle installing these different versions on a macOS workstation, like using [Homebrew](/2013/07/homebrew/), but containers not only make it simple to stand up new software for development with little effort, they do it without leaving artefacts littered across your development workstation. It's common to want to experiment with a new stack, and containers can reduce the friction of getting started.

## Remote - Containers

I've [written before](2016/09/blog-2-0/) about the use of destructible development environments, and the proliferation of containerized runtimes make this more and more simple every day; however, getting the environment set up, and potentially sharing that recipe with a coworker/colleague could be daunting, or time consuming.

This is where Microsoft's [Remote - Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension for [Visual Studio Code](https://code.visualstudio.com) attempts to streamline the process. 


The **Remote - Containers** extension allows you to quickly spin up development environments for your project based on either its library of first-party (or community built) templates, or your own. It also gives VS Code (and its extensions) a direct line-of-sight into container, and manages the mounting (or copying) of your project files into the container instance.

Now that we've discussed _what_ it is, how do we get started?

### Installing the Extension

There are two key prerequisites for working with the **Remote - Containers** extension for VS Code, and they are:

1. VS Code 😅 (of course!)
2. Docker Desktop

{: .box-note}
**Note:** This article is within the context of a macOS environment. If you're working on Linux or Windows, please refer to the documentation.

Installing the extension directly from Visual Studio Code can be done through the **Extensions** panel, accessible by entering **⌘-⇧-X**, or by selecting **Extensions: Install Extensions** from the command palette (⌘-⇧-P). Alternatively, you can install the Remote: Containers extension directly from the [Visual Studio Code Marketplace](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers), by pressing the **Install** button directly from your browser.

[If you still have the sidebar enabled](https://makevscodeawesome.com), you should now see the **Remote Explorer** button.

![VS Code Sidebar](/assets/img/remote-explorer-vs-code.png){: .mx-auto.d-block style="height: 300px" :}

### Creating A New Environment

Now that you've got the extension installed, we can create a new containerized development environment directly from VS Code. Microsoft maintains a number of [container definitions](https://github.com/Microsoft/vscode-dev-containers) themselves, but there are also a large number of community-maintained definitions.

A huge part of the value prop here is the selection of _curated_ environments that you can effortlessly begin working with, which make it simple to test out new technologies without struggling to try and determine which packages and dependencies are required to get _started_.

Examples of pre-built development environments include:

* Azure Ansible
* Azure Bicep
* Azure Functions for Node.js
* PHP
* Python 3
* Python 3 w/ Anaconda
* R
* Vue.js

There are even examples of development environments that leverage _multiple_ containers, such as **Python 3 + PostgreSQL, which allows you to quickly get setup with a Python environment along with a PostgreSQL database in matter of seconds.

The full list of curated environments is available here on the project's [GitHub Repo](https://github.com/microsoft/vscode-dev-containers/tree/master/containers).

For this example, let's create a simple Python 3 workspace which could be used to work with a typical Python project.

#### 1. Open A New Project Folder

First, create an empty project folder, and open it in VS Code (⌘-O).

#### 2. Add the Development Container Configuration Files

Once the empty project folder is opened in VS Code, we can add the configuration files that define our development environment.  From the command palette (⌘-⇧-P), select **Remote-Containers: Add Development Environment Configuration Files...**.

![Adding remote container config settings to a project](/assets/img/remote-container-settings.png){: .mx-auto.d-block :}


Next, you'll be presented with a dropdown which lists some common container types. We'll select the one labeled **Python 3**. 

![Selecting a remote container type](/assets/img/remote-container-python3.png){: .mx-auto.d-block :}

The next prompt will ask you to select the version of Python 3 you'd like to work with, which is one of the _huge_ benefits to working with a containerized environment. For this article I'll select version **3.8**, but feel free to choose any Python version you'd like to work with.

![Select a Python version](/assets/img/remote-container-python-version.png){: .mx-auto.d-block :}

Finally, you'll be asked whether you'd like to include Node.js in your development environment -- I'll omit Node from our settings.

![Installing node.js within the environment](/assets/img/remote-container-install-node.png){: .mx-auto.d-block :}

#### 3. Review the Configuration Settings

Now that we've added the configuration settings, you'll see that VS Code created a new folder within our project, `.devcontainer`, which contains two files: `devcontainer.json`, and `Dockerfile`.

* **`devcontainer.json`** - This file contains your project specific configuration files. It can be used to define things such as your Python language server, formatting options, or which extensions are installed locally within the container.
* **`Dockerfile`** - The Dockerfile contains the _instructions_ to build the actual environment itself. As you'll notice, the  `Dockerfile` pulls from a pre-built image stored within the [Microsoft Container Registry](https://github.com/microsoft/ContainerRegistry); therefore, this file allows you to add additional steps to the container image build process.

#### 4. Start the Development Environment

To start the environment, we can now open our workspace within the container itself, which will cause the VS Code window to reload. This process does a few things for us, such as:

1. Building our Docker image by pulling the base image from the Microsoft Container Registry
2. Instantiating our container
3. Mapping our project folder _into_ the container
4. Installing our desired extensions within the container

![Building the remote container image](/assets/img/remote-container-build.png){: .mx-auto.d-block :}

You can watch the progress of the container image build through VS Code's built-in terminal.

<div class="box-note">
    <strong>Info: </strong>The first time you start the container environment, it might take a few minutes as it's building the container image. Subsequent runs should be much quicker.
</div>

Additionally, it allows us to conveniently map ports from our container instance to our local workstation, for example mapping port 443 through to our container so that we can preview a web service.

#### 5. Get Coding

Once the container has been instantiated, all of your project files are _mounted_ into the running container instance. All of your loaded extensions will also be running from _within_ the container image, therefore minimizing any of the additional steps that are typically required to make your extensions _container-aware_.

While you're working within the remote container, VS Code will automatically open all of your built-in terminal windows _inside_ the container itself, so you have direct access to your container's console.

![VS Code terminal window](/assets/img/remote-container-terminal.png){: .mx-auto.d-block :}

For example, executing the `python` command within the VS Code terminal will now run whatever version of Python you selected during the configuration process.

From my local machine, executing `python --verison` returns `Python 2.7.16`, because the default Python version in macOS Catalina is Python 2.7; however, if I execute the command from within the VS Code terminal, I can see that I'm now using the container's Python runtime, which is `Python 3.8.9`.

<div class="box-note">
    <strong>A Note About Git: </strong>If you're planning on using Git from within the remote container environment, and you use SSH keys to authenticate your repo, you'll have share your keys <em>into</em> the container. You can do this easily from your local machine's terminal by running the command <code>ssh-add</code>. For more info on the <code>ssh-add</code> command, see <a href="https://www.ssh.com/academy/ssh/add">here</a>.
</div>

### Possibilities

As you can imagine, there are many opportunities to make use of the **Remote - Containers** extension within your workflow, as this post barely scratches the surface. The extension allows you to harness the power of containerized development environments, without having to be a Docker Captain from day one. Even if you _are_, there's lots to love about how the curated container settings can accelerate your new projects.

Will you use it to test out a new language or framework? Or simply create a clean environment for your favourite language? There are lots of exciting possibilities with VS Code's **Remote - Containers** extension.