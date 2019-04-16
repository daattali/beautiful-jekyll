---
services: active-directory-b2c
platforms: javascript
author: jmprieur
---

# Single-Page Application built on MSAL.js with Azure AD B2C

:warning: Silent renewing of access tokens is not supported by all social identity providers.

This simple sample demonstrates how to use the [Microsoft Authentication Library Preview for JavaScript (msal.js)](https://github.com/AzureAD/microsoft-authentication-library-for-js) to get an access token and call an API secured by Azure AD B2C.

## How to run this sample

There are two ways to run this sample:
1. **Using the demo environment** - The sample is already configured to use a demo environment and can be run simply by downloading this repository and running the app on your machine. See steps below for Running with demo environment.
2. **Using your own Azure AD B2C tenant** - If you would like to use your own Azure AD B2C configuration, follow the steps listed below for Using your own Azure AD B2C tenant.

## Using the demo environment

This sample demonstrates how to sign in or sign up for an account at "Wingtip Toys" - the demo environment for this sample. Once signed-in, clicking on the **Call Web API** button shows the display name you used when you created your account. 

### Step 1: Clone or download this repository

From your shell or command line:

```
git clone https://github.com/Azure-Samples/active-directory-b2c-javascript-msal-singlepageapp.git
```

### Step 2: Run the application

Make sure you've [installed Node](https://nodejs.org/en/download/).

From your shell or command line: 

```
cd active-directory-b2c-javascript-msal-singlepageapp
npm install && npm update
node server.js
```

The console window shows the port number for the web application

```
Listening on port 6420...
```

You can visit `http://localhost:6420` and perform the following actions:
1. Click the **Login** button to start the Azure AD B2C sign in or sign up workflow.  
2. Once signed in, you can click the **Call Web API** button to have your display name returned from the Web API call as a JSON object. 
3. Click **Logout** to logout from the application. 

## Using your own Azure AD B2C Tenant

In the previous section, you learned how to run the sample application using the demo environment. In this section, you'll learn how to configure this single page application sample and the related [Node.js Web API with Azure AD B2C sample](https://github.com/Azure-Samples/active-directory-b2c-javascript-nodejs-webapi) to work with your own Azure AD B2C Tenant. 

### Step 1: Get your own Azure AD B2C tenant

First, you'll need an Azure AD B2C tenant. If you don't have an existing Azure AD B2C tenant that you can use for testing purposes, you can create your own by following [these instructions](https://azure.microsoft.com/documentation/articles/active-directory-b2c-get-started).

### Step 2: Create your own policies

This sample uses a unified sign-up/sign-in policy.  You can create [your own unified sign-up/sign-in policy](https://azure.microsoft.com/documentation/articles/active-directory-b2c-reference-policies).  You may choose to include as many or as few identity providers as you wish.

If you already have existing policies in your Azure AD B2C tenant, feel free to re-use those policies in this sample.  

### Step 3: Register your own Web API with Azure AD B2C

As you saw in the demo environment, this sample calls a Web API at https://fabrikamb2chello.azurewebsites.net. This demo Web API uses the same code found in the sample [Node.js Web API with Azure AD B2C](https://github.com/Azure-Samples/active-directory-b2c-javascript-nodejs-webapi), in case you need to reference it for debugging purposes. 

You must replace the demo environment Web API with your own Web API. If you do not have your own Web API, you can clone the [Node.js Web API with Azure AD B2C](https://github.com/Azure-Samples/active-directory-b2c-javascript-nodejs-webapi) sample and register it with your tenant. 

#### How to setup and register the Node.js Web API sample

First, clone the Node.js Web API sample repository into its own directory, for example:  

```
cd ..
git clone https://github.com/Azure-Samples/active-directory-b2c-javascript-nodejs-webapi.git
```

so the two folders `active-directory-b2c-javascript-nodejs-webapi` and `active-directory-b2c-javascript-msal-singlepageapp` are located side by side. 

Second, follow the instructions at [register a Web API with Azure AD B2C](https://docs.microsoft.com/azure/active-directory-b2c/active-directory-b2c-app-registration#register-a-web-api) to register the Node.js Web API sample with your tenant. Registering your Web API allows you to define the scopes that your single page application will request access tokens for. 

Provide the following values for the Node.js Web API registration: 

- Provide a descriptive Name for the Node.js Web API, for example, `My Test Node.js Web API`. You will identify this application by its Name whenever working in the Azure portal.
- Mark **Yes** for the **Web App/Web API** setting for your application.
- Set the **Reply URL** to `http://localhost:5000`. This is the port number that the Node.js Web API sample is configured to run on. 
- Set the **AppID URI** to `hello`. This AppID URI is a unique identifier representing this Node.jS Web API. The AppID URI is used to construct the scopes that are configured in you single page application's code. For example, in this Node.js Web API sample, the scope will have the value `https://<your-tenant-name>.onmicrosoft.com/hello/demo.read` 
- Create the application. 
- Once the application is created, open your `My Test Node.js Web API` application and then open the **Published Scopes** window (in the left nav menu) and add the scope `demo.read` followed by a description `demoing a read scenario`. Click **Save**.

Third, in the `index.html` file of the Node.js Web API sample, update the following variables to refer to your Web API registration.  

```
var tenantID = "<your-tenant-name>.onmicrosoft.com";
var clientID = "<Application ID for your Node.js Web API - found on Properties page in Azure portal>";
var policyName = "<Name of your sign in / sign up policy, e.g. B2C_1_SiUpIn>";
```

Lastly, to run your Node.js Web API, run the following command from your shell or command line

```
npm install && npm update
node index.js
```

Your Node.js Web API sample is now running on Port 5000. 

### Step 4: Register your own Web Application with Azure AD B2C

Next, you need to [register your single page application in your B2C tenant](https://docs.microsoft.com/azure/active-directory-b2c/active-directory-b2c-app-registration#register-a-web-application). 

Provide the following values for the Single Page Application registration: 

- Provide a descriptive Name for the single page application, for example, `My Test SPA`. You will identify this application by its Name whenever working in the Azure portal.
- Mark **Yes** for the **Web App/Web API** setting for your application.
- Set the **Reply URL** for your app to `http://localhost:6420`. This sample provided in this repository is configured to run on port 6420.
- Create the application. 
- Once the application is created, open your `My Test SPA` and open the **API Access** window (in the left nav menu). Click **Add** and select the name of the Node.js Web API you registered previously, `My Test Node.js Web API`. Select the scope(s) you defined previously, for example, `demo.read` and hit **Save**.

### Step 5: Configure the sample code to use your Azure AD B2C tenant

Now in the sample code, you can replace the single page application's demo environment configuration with your own tenant.  

1. Open the `index.html` file.
1. Find the assignment for `ClientID` and replace the value with the Application ID for the single page application you registered in Step 4, for example the Application ID found in `My Test SPA` application in the Azure portal. 
1. Find the assignment for `authority` and replacing `b2c_1_susi` with the name of the policy you created in Step 2, and `fabrikamb2c.onmicrosoft.com` by the name of your Azure AD B2C tenant, for example `https://login.microsoftonline.com/tfp/<your-tenant-name>.onmicrosoft.com/<your-sign-in-sign-up-policy>`
1. Find the assignment for the scopes `b2cScopes` replacing the URL by the scope URL you created for the Web API, e.g. `b2cScopes: ["https://<your-tenant-name>.onmicrosoft.com/hello/demo.read"]`
2. Find the assignment for API URL `webApi` replacing the current URL by the URL where you deployed your Web API in Step 4, e.g. `webApi: 'http://localhost:5000/hello'`

Your resulting code should look as follows:

```javascript
<script class="pre">
  // The current application coordinates were pre-registered in a B2C tenant.
  var applicationConfig = {
    clientID: '<Application ID for your single page application>',
    authority: "https://login.microsoftonline.com/tfp/<your-tenant-name>.onmicrosoft.com/<your-sign-in-sign-up-policy>",
    b2cScopes: ["https://<your-tenant-name>.onmicrosoft.com/hello/demo.read"],
    webApi: 'http://localhost:5000/hello',
  };
</script>
```

### Step 7: Run the sample

1. Install the node dependencies if this is your first time running the app (e.g. if you skipped running in the demo environment):        
    ```
    cd active-directory-b2c-javascript-msal-singlepageapp
    npm install && npm update
    ```       
2. Run the Web application       
    ```
    node server.js
    ```      
3. Go to `http://localhost:6420`.
4. Click the **login** button at the top of the application screen. The sample works exactly in the same way regardless of the account type you choose, apart from some visual differences in the authentication and consent experience. Upon successful sign in, the application screen will show buttons that allow you to call an API and sign out.
5. Click on the **Call Web API** and see the textual representation of the JSON object that is returned. Make sure your Node.js Web API sample is still running on port 5000. 
6. Sign out by clicking the **Logout** button.  

## More information
For more information on Azure B2C, see [the Azure AD B2C documentation homepage](http://aka.ms/aadb2c). 

## Community Help and Support
We use Stack Overflow with the [msal](https://stackoverflow.com/questions/tagged/msal) and [azure-ad-b2c](https://stackoverflow.com/questions/tagged/azure-ad-b2c) tags to provide support. We highly recommend you ask your questions on Stack Overflow first and browse existing issues to see if someone has asked your question before. Make sure that your questions or comments are tagged with [msal.js].

If you find and bug or have a feature request, please raise the issue on [GitHub Issues](../../issues). 

To provide a recommendation, visit our [Feedback Forum](http://aka.ms/aadb2cuv).

## Contributing
If you'd like to contribute to this sample, see [CONTRIBUTING.MD](/CONTRIBUTING.md).

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
