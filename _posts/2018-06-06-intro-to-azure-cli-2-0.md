---
title: Intro to Azure CLI 2.0
subtitle: Microsoft Azure's command-line interface
layout: post
tags: [azure, cloud, automation, azure-cli]
readtime: true
---
{: .box-warning}
**Warning:** This post is over a year old, and may not be up-to-date. Please read with its age in mind.

One advantage of Cloud services being built in an _API-centric_ manner is that there are multiple different ways to interact with them, and **Microsoft Azure** is no exception. Whether instantiating services, gathering data, or ensuring compliance, a wealth of options are available for Microsoft Azure such as Vagrant, Terraform, PowerShell, and the Azure Portal.

An example of such an option aimed at consumers and administrators more comfortable with a terminal is the **Azure CLI**, which this post will serve as a brief introduction to.

## Azure CLI {#azure-cli}

The Azure CLI is tool that allows you to interface with the Azure public cloud and interact in a more traditional way. One of the many advantages of the Azure CLI is that it can be used to retrieve structured data from an Azure subscription. Additionally, like other terminal-based tools, the Azure CLI can be scripted with shell scripts.

Azure CLI can be accessed in two ways: a local installation, or via the Azure Cloud Shell.

## Cloud Shell {#cloud-shell}

The first way to access the Azure CLI is directly through the Azure portal. Microsoft has conveniently made the Azure CLI available through a containerized terminal called Cloud Shell. Cloud shell can be accessed by clicking the terminal icon in the top right of any Azure portal page, and selecting Bash as the choice of shell.

![Microsoft Azure Portal](/assets/img/azure_portal.png){: .mx-auto.d-block :}

The Azure Cloud Shell presents you with a familiar Bash terminal window, where Azure CLI commands can be run directly, with no local installation necessary. Additionally, other common tools are available in the Cloud Shell such as `vim`, `wget`, `curl`, `git`, and notably, `ansible`. By attaching to an Azure Storage Account, it’s possible to upload and store files such as Ansible playbooks, ARM templates, or Bash scripts.

![Microsoft Azure Cloud Shell CLI](/assets/img/azure_portal_cloud_shell.png){: .mx-auto.d-block :}

As the Azure Cloud Shell is accessed directly through the Azure web portal, authentication is passed directly through to the terminal.

## Installing Azure CLI on MacOS {#installing-azure-cli-on-macos}

Performing a local installation on MacOS is pretty straightforward using [Homebrew](https://mrtheplague.github.io/2013/Homebrew/), as Azure CLI is available as a bottle. Simply use the `brew install azure-cli` commend to install the latest version of Azure CLI.

```
$ brew install azure-cli
==> Downloading https://homebrew.bintray.com/bottles/azure-cli-2.0.33.high_sierra.bottle.tar.gz
Already downloaded: /Users/<username>/Library/Caches/Homebrew/azure-cli-2.0.33.high_sierra.bottle.tar.gz
==> Pouring azure-cli-2.0.33.high_sierra.bottle.tar.gz
==> Caveats
Bash completion has been installed to:
  /usr/local/etc/bash_completion.d
==> Summary
🍺  /usr/local/Cellar/azure-cli/2.0.33: 12,192 files, 60.9MB
Code language: PHP (php)
```

All Azure CLI commands begin with `az`; for example, a list of available Azure CLI commands can be viewed by simply running the `az` command. You can confirm that Azure CLI has been successfully installed, and verify the installed version by using `az --version`.

```
$ az --version
azure-cli (2.0.35)

!-- removed for brevity --!

Python location '/usr/local/opt/python/bin/python3.6'
Extensions directory '/Users/<username>/.azure/cliextensions'

Python (Darwin) 3.6.5 (default, Apr 25 2018, 14:23:58)
[GCC 4.2.1 Compatible Apple LLVM 9.1.0 (clang-902.0.39.1)]

Legal docs and information: aka.ms/AzureCliLegal
```

## Authenticating Azure CLI {#authenticating-azure-cli}

Azure CLI must be associated to an Azure account, and the login process is initiated from the terminal by inputting `az login` – a URL and authentication code are displayed in the terminal.

```
$ az login
To sign in, use a web browser to open the page https://microsoft.com/devicelogin and enter the code BW8X2L9T6 to authenticate.
```

Enter the code presented in the CLI, and follow the login procedure to login with your Microsoft account credentials.

![Microsoft Azure CLI device authentication](/assets/img/azure_cli_auth.png){: .mx-auto.d-block :}

Once the login is completed, the Azure CLI will respond with a collection key/value pairs describing the Azure subscriptions to which you have access, formatted as a JSON data structure.

```json
[
  {
    "cloudName": "AzureCloud",
    "id": "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx",
    "isDefault": true,
    "name": "MSDN Platforms",
    "state": "Enabled",
    "tenantId": "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxx",
    "user": {
      "name": "robert@employer.com",
      "type": "user"
    }
  },
  {
    "cloudName": "AzureCloud",
    "id": "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx",
    "isDefault": false,
    "name": "Subscription 2",
    "state": "Enabled",
    "tenantId": "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxx",
    "user": {
      "name": "robert@employer.com",
      "type": "user"
    }
  },
  {
    "cloudName": "AzureCloud",
    "id": "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx",
    "isDefault": false,
    "name": "Subscription 3",
    "state": "Enabled",
    "tenantId": "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxx",
    "user": {
      "name": "robert@employer.com",
      "type": "user"
    }
  }
]
```

When working with multiple subscriptions, the active subscription must be set as the `default` subscription for Azure CLI commands.

To quickly view a list of your Azure subscriptions, you use the `az account` command. By using the `--output table` parameter, you view the list of subscriptions formatted as a neat table:

```
$ az account list --output table
Name                      CloudName    SubscriptionId                        State    IsDefault
------------------------  -----------  ------------------------------------  -------  -----------
MSDN Platforms            AzureCloud   xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx  Enabled  True
Subscription 2       AzureCloud   xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx  Enabled  False
Subscription 3              AzureCloud   xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx  Enabled  False
```

Set the active account by using `az account set`:

```
$ az account set --subscription xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
```

## Putting It To Use {#putting-it-to-use}

Now that an active Azure subscription has been selected, we can perform a few simple Azure operations.

First, let’s take a look at what resource groups are configured in our current subscription, and view the output as a table:

```
$ az group list --output table
Name                      Location    Status
------------------------  ----------  ---------
DefaultResourceGroup-EUS  eastus      Succeeded
Teast                     westus2     Succeeded
Test                      westus2     Succeeded
TestCloudFlare            westus      Succeeded
```

Evidently, it looks as though I misspelled the name of a resource group, “`Teast`”, and as I know it’s empty, let’s just delete it. This operation is straightforward with the `az group delete` command.

```
$ az group delete --name Teast
Are you sure you want to perform this operation? (y/n): y
```

New resource groups are created just as easily, by specifying the resource group name, and the location where you’d like to deploy.

```json
$ az group create --name MyResourceGroup --location westus2
{
  "id": "/subscriptions/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx/resourceGroups/MyResourceGroup",
  "location": "westus2",
  "managedBy": null,
  "name": "MyResourceGroup",
  "properties": {
    "provisioningState": "Succeeded"
  },
  "tags": null
}
```

Azure CLI commands return JSON objects with the configuration information of the configured Azure object.

Another benefit of Azure CLI is that the configurations are idempotent; therefore, the state is tracked, and running the `az group create` command again does not repeat the tasks if the desired state is unchanged.

```json
$ az group create --name MyResourceGroup --location westus2
{
  "id": "/subscriptions/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx/resourceGroups/MyResourceGroup",
  "location": "westus2",
  "managedBy": null,
  "name": "MyResourceGroup",
  "properties": {
    "provisioningState": "Succeeded"
  },
  "tags": null
}
```

Like any other shell commands, using the `\` allows multiple lines to be entered into the terminal. Let’s instantiate an Azure Virtual Network in our newly created resource group in West US 2, and assign it the `10.4.0.0/16` address space:

```
$ az network vnet create --name MyVNET \
--resource-group MyResourceGroup \
--address-prefixes 10.4.0.0/16 \
--location westus2
```

Once again, the Azure CLI returns a JSON object with our configuration data.

```json
{
  "newVNet": {
    "addressSpace": {
      "addressPrefixes": [
        "10.4.0.0/16"
      ]
    },
    "ddosProtectionPlan": null,
    "dhcpOptions": {
      "dnsServers": []
    },
    "enableDdosProtection": false,
    "enableVmProtection": false,
    "etag": "W/\"c354e185-db0f-469c-ace6-91a88be98603\"",
    "id": "/subscriptions/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx/resourceGroups/MyResourceGroup/providers/Microsoft.Network/virtualNetworks/MyVNET",
    "location": "westus2",
    "name": "MyVNET",
    "provisioningState": "Succeeded",
    "resourceGroup": "MyResourceGroup",
    "resourceGuid": "b8bab037-8bad-4f08-b565-1e2bccacd2ee",
    "subnets": [],
    "tags": {},
    "type": "Microsoft.Network/virtualNetworks",
    "virtualNetworkPeerings": []
  }
}
```

Finally, we can quickly perform verification of our newly configured VNET by using the `az network vnet list` command:

```
$ az network vnet list --output table
EnableDdosProtection    EnableVmProtection    Location    Name    ProvisioningState    ResourceGroup    ResourceGuid
----------------------  --------------------  ----------  ------  -------------------  ---------------  ------------------------------------
False                   False                 westus2     MyVNET  Succeeded            MyResourceGroup  b8bab037-8bad-4f08-b565-1e2bccacd2ee
```

## Next Steps {#next-steps}

That was just a brief overview of what is a pretty powerful, and barely scratches the surface of what is possible using Azure CLI. Some possible next-steps to explore are:

### Automation {#automation}

Azure CLI is a prime candidate for shell scripting, for example, multiple Virtual Networks, Network Security Groups, etc. could be created from a list of inputs.

### Visual Studio Code Plugin {#visual-studio-code-plugin}

If you’re a user of Microsoft’s awesome open-source text editor, [Visual Studio Code](https://code.visualstudio.com), there’s an excellent plugin which offers IntelliSense for Azure CLI commands. The **Azure CLI Tools** plugin is available from within VS Code, or from [here](https://marketplace.visualstudio.com/items?itemName=ms-vscode.azurecli)

### Documentation {#documentation}

Additional Azure CLI documentation can be found here:

  * [Azure CLI 2.0](https://docs.microsoft.com/en-us/cli/azure/?view=azure-cli-latest)
  * [Get Started with Azure CLI 2.0](https://docs.microsoft.com/en-us/cli/azure/get-started-with-azure-cli?view=azure-cli-latest)
  * [Install Azure CLI 2.0](https://docs.microsoft.com/en-us/cli/azure/install-azure-cli?view=azure-cli-latest)
  * [Azure CLI examples for Linux virtual machines](https://docs.microsoft.com/en-us/azure/virtual-machines/linux/cli-samples?toc=%2fcli%2fazure%2ftoc.json&bc=%2fcli%2fazure%2fbreadcrumb%2ftoc.json&view=azure-cli-latest)

## Conclusion {#conclusion}

As you can see, the Azure CLI provides a versatile interface with which to interact with the Microsoft Azure Public Cloud, and is yet another awesome tool available to Architects and Administrators of Microsoft Azure.