---
layout: post
title: "Introduction to ARM Templates"
subtitle: Using Azure Resource Manager to automate Cloud resources
tags: [arm, automation, azure, cloud]
readtime: true
---

Automation is at the heart of everything that happens within the Public Cloud, and can be a big part of the value proposition for an organization's Cloud adoption. There are many benefits to automation, but one of the best initial use-cases is to achieve consistency when deploying resources, and reduce the opportunities for a human to reduce errors. As [Gregor Hohpe](https://architectelevator.com/) eloquently stated in his book [The Software Architect Elevator](https://www.amazon.ca/Software-Architect-Elevator-Redefining-Architects/dp/1492077542/), **Never send a human to do a machine's job**; therefore, standardizing our deployment process  can be a simple way to add value and attack some of the low-hanging fruit.

> Never send a human to do a machine's job[^1] -- Gregor Hohpe

The wonderful thing about Public Cloud tooling is that there are so many options to choose from. The terrible thing about Public Cloud tooling is that _there are so many options to choose from_. Automation tools have become a bit like standards, in that there is always another springing up claiming to be the answer. In addition to it's native **Azure Resource Manager** (ARM), Microsoft Azure supports a number of automation tools as first-class citizens, such as the ever lovable [Ansible](https://docs.ansible.com/ansible/latest/scenario_guides/guide_azure.html)[^2], and more recently HashiCorp's [Terraform](https://www.terraform.io/docs/providers/azurerm/index.html)[^3].
<br>
<br>

![XKCD on Standards](https://imgs.xkcd.com/comics/standards.png){: .mx-auto.d-block :}
<br>

While the benefits and/or impacts of adding yet another layer of abstraction by using third-party tools is a contentious rabbit-hole for another post, here we'll be discussing the use of Microsoft's [ARM](https://docs.microsoft.com/en-us/azure/azure-resource-manager/templates/) templates.

## What is Azure Resource Manager?

Within Azure, Resource Manager is the centralised _management plane_ responsible for performing all of the Create, Read, Update, and Delete (CRUD) operations. It provides a collection of APIs which can be used to interact with all of the _resource providers_, which are the individual services that can be created, for example databases, DNS records, virtual machines, etc. Any time a CRUD operation is performed on an Azure resource, such as provisioning a new App Service through the portal or viewing a list of subsets via the Azure CLI, we are interacting with Resource Manager.
<br>
<br>

![Azure Resource Manager Architecture](/assets/img/arm-architecture.jpeg){: .mx-auto.d-block :}
<br>

## Resource Manager Templates

Now that we understand Resource Manager’s role as the management plane controlling Azure resources, Resource Manager _Templates_ give us a declarative way of defining what the resources should _look_ like. Where an _imperative_ operation would list out a series of steps, such as “draw a line 3cm to the right, then 3cm down, then 3cm to the left, then 3cm up”, a _declarative_ operation would say “draw me a 9cm^2 square”.

### Lower Friction

Because everything done in Azure is interacting with the Resource Manager in one way or another, every time a new service is created you can immediately declare that resource in an ARM template. This is fantastic, as teams are often eager to leverage new capabilities that are offered within Azure, but  are forced to wait until their tooling catches up.

### Consistent Results

When a deployment is performed using an ARM template, the template itself is converted to an API call directed to the Resource Manager API. Deployments are _idempotent_, meaning the same template can be processed against a resource with the same result. Only _required_ changes are performed by Resource Manager; therefore, it’s possible to define a particular resource state, and Resource Manager will only make changes if necessary to bring the resource back in line with the desired state. Because of this, using ARM templates allows you to perform `what-if` operations, asking Resource Manager to tell you what changes it _would_ make if you were to run the deployment against your resources.

### A Layer Deeper

ARM templates are defined in easy to read JSON notation, and consist of a mixture of required and optional fields. Resources are declared within a JSON object, which is a dictionary of _key:value_ pairs.

```json
{
    "$schema": "https://schema.management.azure.com/schemas/2019-04-01/deploymentTemplate.json#",
    "contentVersion": "1.0.0.0",
    "parameters": {},
    "functions": [],
    "variables": {},
    "resources": [],
    "outputs": {}
}
```   

#### Required Fields

The required ARM template fields include:

* **`$schema`** — A link to a Microsoft resource which outlines the details of the language, specific to the particular ARM version we’re using
* **`contentVersion`** — Allows us to define our own version number for the template we’ve created. This is not tied to the schema in any way, and is just a user-defined value to make tracking changes to a template easier
* **`resources`** — This is the meat and veg of the template, and is the section used to define our resources, and their desired state
<br>
<br>

#### Optional Fields

The optional fields of an ARM template are where the _true_ power lies, giving us the ability to make our templates modular, and reusable. The optional fields include:

* **`parameters`** — Give you the ability to pass a value into template on deployment, such as the name you’d like to assign a resource
* **`functions`** — Permit you to create user-defined expressions that can be called during the deployment of your template
* **`variables`** — Just like with any other language, allow us to store values to be retrieved by elements of the template
* **`outputs`** — Values and objects returned once a template has been deployed allowing us, among other things, to _nest_ our templates

### Putting It Together

With the structure of an ARM template now clear, let’s take a look at an example. The following ARM template is a simple definition of a public DNS zone through Azure DNS:

```json
{
    "$schema": "https://schema.management.azure.com/schemas/2019-04-01/deploymentTemplate.json#",
    "contentVersion": "1.0.0.0",
    "resources": [
        {
            "type": "Microsoft.Network/dnsZones",
            "apiVersion": "2018-05-01",
            "name": "example.org",
            "location": "global",
            "properties": {
                "zoneType": "Public"
            }
        },
    ],
}
```

We won’t get into all of the details in this post, but as you can see, we’re able to define the desired state of the DNS zone as a _Public_ DNS zone called _example.org_.

## Summary

Azure Resource Manager and Azure Resource Manager Templates are a powerful tool for Architects, Administrators, and Developers to consistently describe and deploy a desired state of resources within Microsoft Azure. In a future post we’ll discuss how to actually build and deploy ARM templates, but if you’re looking for more information be sure to check out the [Azure documentation](https://docs.microsoft.com/en-us/azure/azure-resource-manager/templates/).

[^1]: [The Software Architect Elevator: Redefining the Architect's Role in the Digital Enterprise](https://www.amazon.ca/Software-Architect-Elevator-Redefining-Architects/dp/1492077542/)
[^2]: [A great developer experience for Ansible](https://azure.microsoft.com/en-us/blog/a-great-developer-experience-for-ansible/)
[^3]: [Announcing the Terraform AzureRM 2.0 Provider release](https://cloudblogs.microsoft.com/opensource/2020/03/02/announcing-the-terraform-azurerm-2-0-provider-release/)