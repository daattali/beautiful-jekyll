---
layout: post
title:  "Programmatic Personalized Notification Design"
date:   2019-03-09 11:10:00 AM
categories: Technical
---

Below is the design of Personalized Notification Feature that I am working on in my free time. This design heavily leverages the ChangeFeed feature provided by the Azure CosmosDb and it nicely fits in how notifications can be sent in a programmatic manner.

![alt text][DesignDiagram]

[DesignDiagram]: https://loneshark99.github.io/images/PersonalizedNotificationServiceDesign1.PNG "Programmatic Personalized Notification Design"


In this design the core components are  

1. App Service -- This service handles the registration of the devices for both Personalized Notification and WebPush. When devices/WebBrowser registers with the service, the registration is persisted in the Document DB.

2. Azure Function -- This azure function handles the change feed. i.e whenever the userData is modified,this azure function gets triggered.

    This Azure function handles 2 important scenarios

    * Persists a mapping of the UserId (PartitionKey in DocDb)  into a StorageTable. The use of the StorageTable here is to keep the easy way to access all the users who are registred for a particular feature. The PartitionKey and RowKey of this Storage Table can be changed as per the Application requirement.
    * When the Trigger Azure Function updates the User Document, this function will handle the sending of the notification. Based on the changed document it will either trigger the WebPush Scenario or the Personalized Notification Scenario.

3. Trigger Azure Function -- There are 2 trigger function in this design, One for Personalized Notification and another one for WebPush Notification. The Trigger Azure function role is the Read the Storage Table and update the UserDocument in the DocumentDb.  

**The advantages of this design are**

1. Leverages the services provided by Azure which can be scaled as needed.
2. Rapid application development as it restricts the application development part to just the business logic.
3. Will help in reducing cost as the Azure Functions are charged only when they are used.
4. This provides a very easy way to gather telemetry data on the Notifications sent.

**The disadvantages of this design are**

1. Having seperate storage for mapping but this can be changed.
